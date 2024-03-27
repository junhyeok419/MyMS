#include "GameObject.h"
#include "../Resource/Texture/Texture.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/SceneManager.h"
#include "../Scene/SceneCollision.h"
#include "../Resource/Animation/AnimationSequence.h"
#include "../GameManager.h"
#include "../Scene/Camera.h"
#include "../Collision/Collider.h"
#include "Player.h"
#include "../UI/DialogWindow.h"
bool CGameObject::Init()
{
	return true;
}

void CGameObject::Update(float _deltaTime)
{
	// �ȵǼ� �ӽ÷�,.,
	// m_jumpVelocity = 35; 
	
	// �߷� ���� (���� ���� �ʰ��ְ�, �߷� ������ on�϶���)
	if (!m_ground && m_physicsSimulate)
	{
		// �������� �ð��� ���������ش�. 10�� ���� 10��� �þ�� �Ѵ�. 
		// (�������� �ð��� ����� ���߿� ���� �ӵ��� ������ �ϱ� ����)
		m_fallTime += _deltaTime * m_gravityAccel;

		// 9.8 m/s^2 (�߷� ���ӵ�)
		
		/*
			��ü�� �������� t�� ���� y���� ���Ҷ�,
			�ӵ�(V), ���ӵ�(A), �߷�(G) ��� �ϸ�,

			y = V * A - 0.5 * G * t * t   �̴�.	
		*/
		float Velocity = 0.f;

		// ���� ���� ���, ���� �ӵ�(V) * ���ӵ�(A)�� ���Ѵ�.
		/*
			fallTime(������ �ð�)�� ���ӵ�(A) ��ſ� �־��ش�.
			��, �Ϻ��� ���������� �ƴϰ� api��ǥ�迡 ���� �۾��ϴ� ���̴�.
			�׷��� ���� ������ ���´�.
		*/
		if (m_jump)
			Velocity = m_jumpVelocity * m_fallTime;

		// ������ ���� Velocity ���� - 0.5 * �߷�(G) * t * t �� �Ѵ�.
		// ������ ���������� ���ָ� t������ y���� ���°� �ȴ�.
		m_pos.y = m_fallStartY - (Velocity - 0.5f * GRAVITY * m_fallTime * m_fallTime);
		
	}


	// �ִϸ��̼� ������Ʈ
	if (m_animation)
		m_animation->Update(_deltaTime * m_timeScale);

	{
		// �浹ü ������Ʈ
		auto	iter = m_colliderList.begin();
		auto	iterEnd = m_colliderList.end();

		for (; iter != iterEnd;)
		{
			// ���� �浹ü�� �����ش�.
			if (!(*iter)->GetActive())
			{
				iter = m_colliderList.erase(iter);
				iterEnd = m_colliderList.end();
				continue;
			}
			// ��Ȱ��ȭ�� �浹ü�� ������Ʈ ��󿡼� �����Ѵ�.
			else if (!(*iter)->GetEnable())
			{
				++iter;
				continue;
			}

			// �� 2������ �ش����� �ʴ� �浹ü�� ������Ʈ�Ѵ�.
			(*iter)->Update(_deltaTime);
			++iter;
		}
	}

	{
		// ������Ʈ�� ���� ����������Ʈ�� ������Ʈ�Ѵ�.
		auto	iter = m_widgetComponentList.begin();
		auto	iterEnd = m_widgetComponentList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				iter = m_widgetComponentList.erase(iter);
				iterEnd = m_widgetComponentList.end();
				continue;
			}

			else if (!(*iter)->GetEnable())
			{
				++iter;
				continue;
			}

			(*iter)->Update(_deltaTime);
			++iter;
		}
	}
}

void CGameObject::PostUpdate(float _deltaTime)
{
	// �̵��� ���
	m_move = m_pos - m_prevPos;

	/*
		�ִϸ��̼��� ������ ���, �̹��� ������� ������Ʈ�� ����� 
		�����ϱ� ������ ���⿡�� �ٽ� �����ֵ��� �Ѵ�.
	*/
	if (m_animation)
	{
		CAnimationInfo* Current = m_animation->m_currentAnimation;

		const AnimationFrameData& FrameData = Current->m_sequence->GetFrame(Current->m_frame);

		m_size = FrameData.End - FrameData.Start;
	}

	{
		// �浹ü�� ����Ʈ ������Ʈ
		auto	iter = m_colliderList.begin();
		auto	iterEnd = m_colliderList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				iter = m_colliderList.erase(iter);
				iterEnd = m_colliderList.end();
				continue;
			}

			else if (!(*iter)->GetEnable())
			{
				++iter;
				continue;
			}

			(*iter)->PostUpdate(_deltaTime);


			if (nullptr==m_scene->GetCollision())
			{
				++iter;
				continue;
			}
			// �̷��� ������Ʈ�� �浹ü���� ���ø����� ä���ִ´�.
			m_scene->GetCollision()->AddCollider(*iter);

			++iter;
		}
	}

	{
		// ������Ʈ�� ���� ����������Ʈ�� ������Ʈ�Ѵ�.
		auto	iter = m_widgetComponentList.begin();
		auto	iterEnd = m_widgetComponentList.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				iter = m_widgetComponentList.erase(iter);
				iterEnd = m_widgetComponentList.end();
				continue;
			}

			else if (!(*iter)->GetEnable())
			{
				++iter;
				continue;
			}

			(*iter)->PostUpdate(_deltaTime);
			++iter;
		}
	}
}

void CGameObject::Render(HDC _hDC, float _deltaTime)
{
	/*
		ī�޶� �߰��� ��������
		�÷��̾��� ��ġ�� �� �̻� ������ �ƴϴ�.
		�÷��̾��� '��ü ����� ��ġ'���� 'ī�޶� ��ġ(ī�޶� ���� �»��)'�� ����
		������ â���� ������ �÷��̾��� ������� ��ġ�� ������ �� ���̴�.

		�� �̴ֿ��� (100,100)���� �����ص� �װ��� ��ü ���� ������ ��ġ�̱� ������
		�ٽ� ������־�� �Ѵ�.
	*/
	Vector2	pos;
	Vector2	cameraPos;	// ī�޶� ��ġ
	Vector2	resolution; // ��ü ����

	// ������Ʈ�� ���� ���� ������ ���� �����ش�. 
	if (m_scene)
	{
		pos = m_pos - m_scene->GetCamera()->GetPos();
		cameraPos = m_scene->GetCamera()->GetPos();
		resolution = m_scene->GetCamera()->GetResolution();
		
		// ���� ����� ����
		// 1�� ����� �÷��̾�� ���� �����̰� �ϴ� ����
		if (m_renderLayer == ERenderLayer::Back1)
		{
			pos = pos + m_scene->GetCamera()->GetPos();
			/*pos.x = pos.x + m_scene->GetCamera()->GetPos().x;
			pos.y = pos.y + m_scene->GetCamera()->GetPos().y;*/
		}
	}
	// �׷��� �ʴٸ� ���� ���� ���� �Ŀ� ���Ѵ�.
	else
	{
		CScene* scene = CSceneManager::GetInst()->GetScene();
		pos = m_pos - scene->GetCamera()->GetPos();
		cameraPos = scene->GetCamera()->GetPos();
		resolution = scene->GetCamera()->GetResolution();
	}
	
	
	

	


	// ������Ʈ�� �ִϸ��̼��� �����Ѵٸ�
	if (m_animation)
	{
		// ���� �ִϸ��̼��� �����´�.
		CAnimationInfo* current = m_animation->m_currentAnimation;

		// �ִϸ��̼��� ���� ������ ����(�� �����ӱ��� ����ߴ���)�� �����´�.
		const AnimationFrameData& frameData = current->m_sequence->GetFrame(current->m_frame);

		// ����� �»�� ��ġ�� ���Ѵ�.
		Vector2	size = frameData.End - frameData.Start;

		Vector2	renderLT;
		renderLT = pos - m_pivot * size;

		/*
			����ȭ�� ���� ī�޶� ���� �ٱ��� �ִ� ������Ʈ��
			�׸��� �ʱ�(�ø�) ���� �ڵ��̴�.

			��ü�� �ø���ġ(ī�޶� ������� ���� ��ġ**�߿�)�� ���ϰ�, 
			�� ��ġ�� ī�޶� ������ ����� return �����ν� �����Ѵ�. 
			(Rect �浹�� ����ϴ�)
		*/
		Vector2	cullPos = m_pos - m_pivot * size;

		if (cullPos.x > cameraPos.x + resolution.x)
			return;

		else if (cullPos.x + size.x < cameraPos.x)
			return;

		else if (cullPos.y > cameraPos.y + resolution.y)
			return;

		else if (cullPos.y + size.y < cameraPos.y)
			return;


		if (current->m_sequence->IsFramePivot())
		{
			renderLT = pos - 
				(current->m_sequence->GetFramePivot(current->m_frame))*size;
		}
		else
		{
			renderLT = pos - m_pivot * size;
		}

		// �ִϸ��̼� �ؽ��İ� sprite ������ �̹����� ���
		if (current->m_sequence->GetTextureType() == ETextureType::Sprite)
		{
			// �÷�Ű�� �����ϸ�
			if (current->m_sequence->GetTexture()->GetEnableColorKey())
			{
				/*
				TransparentBlt : BitBlt�� 1~6�����ڴ� ����.
				1. �̹����� ������� DC
				2. ������� DC������ x��ǥ
				3. ������� DC������ y��ǥ
				4. �׷��� �̹����� ����ũ��
				5. �׷��� �̹����� ����ũ��
				6. �̹����� ����� DC
				7.  ����� �̹��������� ���� x��ǥ
				8.  ����� �̹��������� ���� y��ǥ
				9.  ����� �̹����� ����ũ��
				10. ����� �̹����� ���� ũ��
				11. ����� �̹����� ���� �÷�Ű

				sprite�̹��� �������� �̹������� �̾ƿ��� �������� �޶��� ���̴�.
				�Ź� �������� �ٸ��� �Ͽ� �̹����� �ٸ��� �����;� �Ѵ�.

				�׷��� �ϴ��� sprite�̹����� ��ü�� ����ϵ��� �Ѵ�.(<- �ִϸ��̼� �ȹ�� ����)
			*/
				TransparentBlt(_hDC, (int)renderLT.x, (int)renderLT.y,
					(int)size.x, (int)size.y,
					current->m_sequence->GetTexture()->GetDC(),
					(int)frameData.Start.x, (int)frameData.Start.y,
					(int)size.x, (int)size.y,
					current->m_sequence->GetTexture()->GetColorKey());
			}
			// �÷�Ű�� ���ٸ�
			else
			{
				BitBlt(_hDC, (int)renderLT.x, (int)renderLT.y,
					(int)size.x, (int)size.y,
					current->m_sequence->GetTexture()->GetDC(),
					(int)frameData.Start.x, (int)frameData.Start.y, SRCCOPY);
			}
		}
		// �ִϸ��̼� �ؽ��İ� frame �̹����� ���
		else
		{
			/*
				�� sprite�� ���� �������� ����.

				sprite�� ��� GetDC�� 1���� �ؽ��Ŀ� ���ؼ��� �������� �Ǳ� ������
				GetDC�� ����Ʈ ���ڸ� �����Ͽ�����,
				frame�� ��� ���ӵ� �Ź� �ٸ� �ؽ��Ŀ� ���� DC�� ���;� �ϱ� ������.
				GetDC�� m_frame�� ���ڷ� �����Ѵ�.

			*/
			if (current->m_sequence->GetTexture()->GetEnableColorKey())
			{
				TransparentBlt(_hDC, (int)renderLT.x, (int)renderLT.y,
					(int)size.x, (int)size.y,
					current->m_sequence->GetTexture()->GetDC(current->m_frame),
					(int)frameData.Start.x, (int)frameData.Start.y,
					(int)size.x, (int)size.y,
					current->m_sequence->GetTexture()->GetColorKey());
			}
			// �÷�Ű�� ���ٸ�
			else
			{
				BitBlt(_hDC, (int)renderLT.x, (int)renderLT.y,
					(int)size.x, (int)size.y,
					current->m_sequence->GetTexture()->GetDC(current->m_frame),
					(int)frameData.Start.x, (int)frameData.Start.y, SRCCOPY);
			}
		}
	}
	// �ִϸ��̼��� ���� ������Ʈ�� ���
	else
	{
		// ���� ������Ʈ�� �������ִ� �ؽ��ķ� ����ϵ��� �Ѵ�.
		if (m_texture)
		{
			Vector2	RenderLT;

			RenderLT = pos - m_pivot * m_size;

			/*
			����ȭ�� ���� ī�޶� ���� �ٱ��� �ִ� ������Ʈ��
			�׸��� �ʱ�(�ø�) ���� �ڵ��̴�.

			��ü�� �ø���ġ(ī�޶� ������� ���� ��ġ**�߿�)�� ���ϰ�,
			�� ��ġ�� ī�޶� ������ ����� return �����ν� �����Ѵ�.
			(Rect �浹�� ����ϴ�)
			*/
			Vector2	cullPos = m_pos - m_pivot * m_size;

			if (cullPos.x > cameraPos.x + resolution.x)
				return;

			else if (cullPos.x + m_size.x < cameraPos.x)
				return;

			else if (cullPos.y > cameraPos.y + resolution.y)
				return;

			else if (cullPos.y + m_size.y < cameraPos.y)
				return;
			/*
				TransparentBlt : BitBlt�� 1~6�����ڴ� ����.
				7.  ����� �̹��������� ���� x��ǥ
				8.  ����� �̹��������� ���� y��ǥ
				9.  ����� �̹����� ����ũ��
				10. ����� �̹����� ���� ũ��
				11. ����� �̹����� ���� �÷�Ű

				sprite�̹��� �������� �̹������� �̾ƿ��� �������� �޶��� ���̴�.
				�Ź� �������� �ٸ��� �Ͽ� �̹����� �ٸ��� �����;� �Ѵ�.

				�׷��� �ϴ��� sprite�̹����� ��ü�� ����ϵ��� �Ѵ�.(<- �ִϸ��̼� �ȹ�� ����)
			*/
			// �÷�Ű�� Ȱ��ȭ �Ǿ����� ���
			if (m_texture->GetEnableColorKey())
			{
				TransparentBlt(_hDC, (int)RenderLT.x, (int)RenderLT.y,
					(int)m_size.x, (int)m_size.y, m_texture->GetDC(),
					0, 0, (int)m_size.x, (int)m_size.y, m_texture->GetColorKey());
			}

			/*
				BitBlt : �̹����� ���ϴ� DC�� ������ش�.
				1. �̹����� ������� DC
				2. ������� DC������ x��ǥ
				3. ������� DC������ y��ǥ
				4. �׷��� �̹����� ����ũ��
				5. �׷��� �̹����� ����ũ��
				6. �̹����� ����� DC
				7. ����� DC������ ���� x��ǥ
				8. ����� DC������ ���� y��ǥ
				9. �׸��� ��� ���� (SRCCOPY : ��� ����)
			*/
			// �÷�Ű�� Ȱ��ȭ���� �ʾ��� ���
			else
			{
				BitBlt(_hDC, (int)RenderLT.x, (int)RenderLT.y,
					(int)m_size.x, (int)m_size.y, m_texture->GetDC(),
					0, 0, SRCCOPY);
			}
		}
	}

	// �浹ü�� render�� ȣ���Ѵ�.
	auto	iter = m_colliderList.begin();
	auto	iterEnd = m_colliderList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			iter = m_colliderList.erase(iter);
			iterEnd = m_colliderList.end();
			continue;
		}

		else if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Render(_hDC, _deltaTime);
		++iter;
	}

	// ���� ��ġ�� �����Ѵ�.
	m_prevPos = m_pos;
}

float CGameObject::InflictDamage(float _damage, int _dir)
{
	return _damage;
}

CCollider* CGameObject::FindCollider(const std::string& _name)
{
	auto	iter = m_colliderList.begin();
	auto	iterEnd = m_colliderList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == _name)
			return *iter;
	}

	return nullptr;
}

ESkillState CGameObject::GetPowerStrikeState()
{
	return ESkillState();
}

ESkillState CGameObject::GetSlashBlastState()
{
	return ESkillState();
}

ESkillState CGameObject::GetJudgementState()
{
	return ESkillState();
}

ESkillState CGameObject::GetJusticeState()
{
	return ESkillState();
}


float CGameObject::GetHP() const
{
	return 0.0f;
}

float CGameObject::GetHPMax() const
{
	return 0.0f;
}

float CGameObject::GetMP() const
{
	return 0.0f;
}

float CGameObject::GetMPMax() const
{
	return 0.0f;
}

float CGameObject::GetEXP() const
{
	return 0.0f;
}

float CGameObject::GetEXPMax() const
{
	return 0.0f;
}

float CGameObject::GetLevel() const
{
	return 0.0f;
}

int CGameObject::GetHPPotionCnt() const
{
	return 0;
}

int CGameObject::GetMPPotionCnt() const
{
	return 0;
}

int CGameObject::GetItemCnt() const
{
	return 0;
}

ESkill CGameObject::GetUseSkill() const
{
	return ESkill();
}

bool CGameObject::GetFlag() const
{
	return true;
}

int CGameObject::GetDir() const
{
	return m_objDir;
}

bool CGameObject::GetGround() const
{
	return m_ground;
}

bool CGameObject::GetJump() const
{
	return m_jump;
}

ERenderLayer CGameObject::GetRenderLayer() const
{
	return m_renderLayer;
}

float CGameObject::GetTimeScale() const
{
	return m_timeScale;
}

const Vector2& CGameObject::GetPos() const
{
	return m_pos;
}



const Vector2& CGameObject::GetSize() const
{
	return m_size;
}

const Vector2& CGameObject::GetPivot() const
{
	return m_pivot;
}

bool CGameObject::GetLadder() const
{
	return m_ladder;
}

void CGameObject::SetPortalEnable(std::string _portalName)
{
}

void CGameObject::SetMoveSpeed(float _speed)
{
	m_moveSpeed = _speed;
}

void CGameObject::SetFlag(bool _flag)
{
}

void CGameObject::SetLadder(bool _ladder)
{
	m_ladder = _ladder;
}

void CGameObject::SetEnableUpKey(bool _enable)
{
	m_enableUpKey = _enable;
}

void CGameObject::SetEnableUpKey_Portal(bool _enable)
{
	m_enableUpKey_Portal = _enable;
}

void CGameObject::SetEnableDownKey(bool _enable)
{
	m_enableDownKey = _enable;
}

void CGameObject::SetFallTime(float _time)
{
	m_fallTime = _time;
}

void CGameObject::SetFallStartY(float _y)
{
	m_fallStartY = _y;
}

void CGameObject::SetGround(bool _ground)
{
	m_ground = _ground;
}

void CGameObject::SetJump(bool _jump)
{
	m_jump = _jump;
}

void CGameObject::SetRenderLayer(ERenderLayer _layer)
{
	m_renderLayer = _layer;
}

void CGameObject::SetPhysicsSimulate(bool _physics)
{
	m_physicsSimulate = _physics;
}

void CGameObject::SetGravityAccel(float _accel)
{
	m_gravityAccel = _accel;
}

void CGameObject::SetJumpVelocity(float _jumpVelocity)
{
	m_jumpVelocity = _jumpVelocity;
}

void CGameObject::SetTimeScale(float _scale)
{
	m_timeScale = _scale;
}

void CGameObject::SetPos(const Vector2& _pos) 
{
	m_pos = _pos;
}

void CGameObject::SetPos(float _x, float _y) 
{
	m_pos.x = _x;
 	m_pos.y = _y;
}

void CGameObject::SetSize(const Vector2& _size) 
{
	m_size = _size;
}

void CGameObject::SetSize(float _x, float _y) 
{
	m_size.x = _x;
	m_size.y = _y;
}

void CGameObject::SetPivot(const Vector2& _pivot) 
{
	m_pivot = _pivot;
}

void CGameObject::SetPivot(float _x, float _y) 
{
	m_pivot.x = _x;
	m_pivot.y = _y;
}

void CGameObject::OpenUIWindow()
{
}

void CGameObject::SetTexture(const std::string& _name)
{
	// �ش� �̸��� ���� �ؽ��ĸ� ã�� ������Ʈ�� ����Ѵ�. 
	// �� ������Ʈ�� ���� ���� �����ҽ��� ���� ã�°� �����ϴ�.
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

void CGameObject::SetTexture(CTexture* _texture)
{
	m_texture = _texture;
}

void CGameObject::SetTexture(const std::string& _name, const TCHAR* _fileName, const std::string& _pathName)
{
	// ���� �ؽ��ĸ� �ε��Ͽ�, �����ҽ��� ��´�.
	m_scene->GetSceneResource()->LoadTexture(_name, _fileName, _pathName);
	
	// �����ҽ��� �����ϴ� �ؽ��ĸ� �����´�.
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

void CGameObject::SetTextureFullPath(const std::string& _name, const TCHAR* _fullPath)
{
	// ���� �ؽ��ĸ� �ε��Ͽ�, �����ҽ��� ��´�.
	m_scene->GetSceneResource()->LoadTextureFullPath(_name, _fullPath);

	// �����ҽ��� �����ϴ� �ؽ��ĸ� �����´�.
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

#ifdef UNICODE

void CGameObject::SetTexture(const std::string& _name, const std::vector<std::wstring>& _vecFileName, const std::string& _pathName)
{
	// ���� �ؽ��ĸ� �ε��Ͽ�, �����ҽ��� ��´�.
	m_scene->GetSceneResource()->LoadTexture(_name, _vecFileName, _pathName);

	// �����ҽ��� �����ϴ� �ؽ��ĸ� �����´�.
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

void CGameObject::SetTextureFullPath(const std::string& _name, const std::vector<std::wstring>& _vecFullPath)
{
	// ���� �ؽ��ĸ� �ε��Ͽ�, �����ҽ��� ��´�.
	m_scene->GetSceneResource()->LoadTextureFullPath (_name, _vecFullPath);

	// �����ҽ��� �����ϴ� �ؽ��ĸ� �����´�.
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

#else

void CGameObject::SetTexture(const std::string& _name, const std::vector<std::string>& _vecFileName, const std::string& _pathName)
{
	// ���� �ؽ��ĸ� �ε��Ͽ�, �����ҽ��� ��´�.
	m_scene->GetSceneResource()->LoadTexture(_name, _vecFileName, _pathName);

	// �����ҽ��� �����ϴ� �ؽ��ĸ� �����´�.
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}


void CGameObject::SetTextureFullPath(const std::string& _name, const std::vector<std::string>& _vecFullPath)
{
	// ���� �ؽ��ĸ� �ε��Ͽ�, �����ҽ��� ��´�.
	m_scene->GetSceneResource()->LoadTextureFullPath(_name, _vecFullPath);

	// �����ҽ��� �����ϴ� �ؽ��ĸ� �����´�.
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

#endif // UNICODE

bool CGameObject::SetColorKey(unsigned char _r, unsigned char _g, unsigned char _b, int _index)
{
	// ���� ������Ʈ�� ���� �ؽ��İ� �����ϴ���. ������ ����
	if (!m_texture)
		return false;

	// �ε����� �ش��ϴ� �̹����� �÷�Ű�� �����Ѵ�.
	m_texture->SetColorKey(_r, _g, _b, _index);

	return true;
}

bool CGameObject::SetColorKeyAll(unsigned char _r, unsigned char _g, unsigned char _b)
{
	// ���� ������Ʈ�� ���� �ؽ��İ� �����ϴ���. ������ ����
	if (!m_texture)
		return false;

	// �ؽ����� ��� �̹����� �÷�Ű�� �����Ѵ�.
	m_texture->SetColorKeyAll(_r, _g, _b);

	return true;
}

void CGameObject::CreateAnimation()
{
	// �ִϸ��̼� ����
	m_animation = new CAnimation;

	// �ִϸ��̼��� ���� ������Ʈ�� �� ����
	m_animation->m_owner = this;
	m_animation->m_scene = m_scene;
}

void CGameObject::AddAnimation(const std::string& _sequenceName, bool _loop, float _playTime, float _playScale, bool _reverse)
{
	m_animation->AddAnimation(_sequenceName, _loop, _playTime, _playScale, _reverse);
}

void CGameObject::SetPlayTime(const std::string& _name, float _playTime)
{
	m_animation->SetPlayTime(_name, _playTime);
}

void CGameObject::SetPlayScale(const std::string& _name, float _playScale)
{
	m_animation->SetPlayScale(_name, _playScale);
}

void CGameObject::SetPlayLoop(const std::string& _name, bool _loop)
{
	m_animation->SetPlayLoop(_name, _loop);
}

void CGameObject::SetPlayReverse(const std::string& _name, bool _reverse)
{
	m_animation->SetPlayReverse(_name, _reverse);
}

void CGameObject::SetCurrentAnimation(std::string& _name)
{
	m_animation->SetCurrentAnimation(_name);
}

void CGameObject::AddEXP(float _exp)
{
}

void CGameObject::AddMoney(int _money)
{
}

void CGameObject::ChangeAnimation(const std::string& _name)
{
	m_animation->ChangeAnimation(_name);
}

bool CGameObject::CheckCurrentAnimation(const std::string& _name)
{
	return m_animation->CheckCurrentAnimation(_name);
}

void CGameObject::MoveDir(const Vector2& _dir)
{
	// ������ ���� �̵��ӵ� ��ŭ Ư�� �������� �̵���Ų��.
	m_pos += _dir * m_moveSpeed * DELTA_TIME * m_timeScale;
}

void CGameObject::Move(const Vector2& _moveValue)
{
	// ���� ���뷮��ŭ(�׷��� ��ŸŸ���� ������ �ʴ´�.) �̵���Ų��. 
	m_pos += _moveValue * m_timeScale;
}

void CGameObject::Move(float _angle)
{
	// ������ ���� �̵��ӵ� ��ŭ Ư�� ������ �̵���Ų��.
	Vector2	Dir;
	Dir.x = cosf(DegreeToRadian(_angle));
	Dir.y = sinf(DegreeToRadian(_angle));

	m_pos += Dir * m_moveSpeed * DELTA_TIME * m_timeScale;
}

void CGameObject::Jump()
{
	// ���������� �������� ���ư���.
	if (!m_jump)
	{
		m_jump = true;
		m_ground = false;

		m_fallTime = 0.f;
		m_fallStartY = m_pos.y;
	}
}

CGameObject::CGameObject()
	: m_scene(nullptr)
	, m_animation(nullptr)
	, m_timeScale(1.f)
	, m_moveSpeed(0.f)
	, m_renderLayer(ERenderLayer::Default)
	, m_physicsSimulate(false)
	, m_ground(false)
	, m_gravityAccel(10.f)
	, m_fallTime(0.f)
	, m_fallStartY(0.f)
	, m_jump(false)
	, m_jumpVelocity(0.f)
{
	// ��ü ���� �� Ÿ�� ���̵�(���۷��� Ŭ������ ���)�� �ʱ�ȭ
	SetTypeID<CGameObject>();
}

CGameObject::CGameObject(const CGameObject& _obj)
	: CRef(_obj)
	, m_scene(nullptr)
	, m_pos(_obj.m_pos)
	, m_size(_obj.m_size)
	, m_pivot(_obj.m_pivot)
	, m_timeScale(_obj.m_timeScale)
	, m_physicsSimulate(_obj.m_physicsSimulate)
	, m_ground(false)
	, m_gravityAccel(_obj.m_gravityAccel)
	, m_fallTime(_obj.m_fallTime)
	, m_fallStartY(_obj.m_fallStartY)
	, m_jump(false)
	, m_jumpVelocity(_obj.m_jumpVelocity)
{
}

CGameObject::~CGameObject()
{
	{
		/*
			�浹ü���� �浹�� ���� CCollider�� �Ҹ��ڿ�
			������ �ʾ� ���� �����.
			���۷��� ī��Ʈ�� 0�� ���� ���� ���¿���
			���� ������Ʈ�� ���� �����Ǳ� �����̴�.

			���� �̰����� ���ӿ�����Ʈ�� ������ ��, ��ü
			�ݺ��� ���鼭 �浹ü ����Ʈ�� �� ���� ���̴�.
		*/
		auto	iter = m_colliderList.begin();
		auto	iterEnd = m_colliderList.end();

		for (; iter != iterEnd; ++iter)
		{
			(*iter)->ClearCollisionList();
		}
	}

	{
		// ���������̴�.
		auto	iter = m_widgetComponentList.begin();
		auto	iterEnd = m_widgetComponentList.end();

		for (; iter != iterEnd; ++iter)
		{
			(*iter)->SetActive(false);
		}
	}

	SAFE_DELETE(m_animation);
}
