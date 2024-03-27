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
	// 안되서 임시로,.,
	// m_jumpVelocity = 35; 
	
	// 중력 적용 (땅을 밟지 않고있고, 중력 적용이 on일때만)
	if (!m_ground && m_physicsSimulate)
	{
		// 떨어지는 시간을 누적시켜준다. 10을 곱해 10배로 늘어나게 한다. 
		// (떨어지는 시간이 길수록 나중에 낙하 속도를 빠르게 하기 위함)
		m_fallTime += _deltaTime * m_gravityAccel;

		// 9.8 m/s^2 (중력 가속도)
		
		/*
			물체가 낙하한지 t초 후의 y값을 구할때,
			속도(V), 가속도(A), 중력(G) 라고 하면,

			y = V * A - 0.5 * G * t * t   이다.	
		*/
		float Velocity = 0.f;

		// 점프 중일 경우, 먼저 속도(V) * 가속도(A)를 구한다.
		/*
			fallTime(떨어진 시간)을 가속도(A) 대신에 넣어준다.
			즉, 완벽한 물리공식이 아니고 api좌표계에 맞춰 작업하는 것이다.
			그래도 나름 괜찮게 나온다.
		*/
		if (m_jump)
			Velocity = m_jumpVelocity * m_fallTime;

		// 위에서 구한 Velocity 에서 - 0.5 * 중력(G) * t * t 를 한다.
		// 떨어진 시작점에서 뺴주면 t초후의 y값이 나온게 된다.
		m_pos.y = m_fallStartY - (Velocity - 0.5f * GRAVITY * m_fallTime * m_fallTime);
		
	}


	// 애니메이션 업데이트
	if (m_animation)
		m_animation->Update(_deltaTime * m_timeScale);

	{
		// 충돌체 업데이트
		auto	iter = m_colliderList.begin();
		auto	iterEnd = m_colliderList.end();

		for (; iter != iterEnd;)
		{
			// 죽은 충돌체는 지워준다.
			if (!(*iter)->GetActive())
			{
				iter = m_colliderList.erase(iter);
				iterEnd = m_colliderList.end();
				continue;
			}
			// 비활성화된 충돌체는 업데이트 대상에서 제외한다.
			else if (!(*iter)->GetEnable())
			{
				++iter;
				continue;
			}

			// 위 2가지에 해당하지 않는 충돌체만 업데이트한다.
			(*iter)->Update(_deltaTime);
			++iter;
		}
	}

	{
		// 오브젝트에 속한 위젯컴포넌트를 업데이트한다.
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
	// 이동량 계산
	m_move = m_pos - m_prevPos;

	/*
		애니메이션이 동작할 경우, 이미지 사이즈로 오브젝트의 사이즈를 
		결정하기 때문에 여기에서 다시 구해주도록 한다.
	*/
	if (m_animation)
	{
		CAnimationInfo* Current = m_animation->m_currentAnimation;

		const AnimationFrameData& FrameData = Current->m_sequence->GetFrame(Current->m_frame);

		m_size = FrameData.End - FrameData.Start;
	}

	{
		// 충돌체의 포스트 업데이트
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
			// 이렇게 업데이트한 충돌체들을 씬컬리젼에 채워넣는다.
			m_scene->GetCollision()->AddCollider(*iter);

			++iter;
		}
	}

	{
		// 오브젝트에 속한 위젯컴포넌트를 업데이트한다.
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
		카메라를 추가한 시점부터
		플레이어의 위치는 더 이상 고정이 아니다.
		플레이어의 '전체 월드상 위치'에서 '카메라 위치(카메라 영역 좌상단)'를 빼야
		윈도우 창으로 부터의 플레이어의 상대적인 위치가 나오게 될 것이다.

		즉 이닛에서 (100,100)으로 설정해도 그것은 전체 월드 기준의 위치이기 때문에
		다시 계산해주어야 한다.
	*/
	Vector2	pos;
	Vector2	cameraPos;	// 카메라 위치
	Vector2	resolution; // 전체 영역

	// 오브젝트가 속한 씬이 존재할 때만 구해준다. 
	if (m_scene)
	{
		pos = m_pos - m_scene->GetCamera()->GetPos();
		cameraPos = m_scene->GetCamera()->GetPos();
		resolution = m_scene->GetCamera()->GetResolution();
		
		// 이중 배경을 위함
		// 1단 배경을 플레이어랑 같이 움직이게 하는 것임
		if (m_renderLayer == ERenderLayer::Back1)
		{
			pos = pos + m_scene->GetCamera()->GetPos();
			/*pos.x = pos.x + m_scene->GetCamera()->GetPos().x;
			pos.y = pos.y + m_scene->GetCamera()->GetPos().y;*/
		}
	}
	// 그렇지 않다면 현재 씬을 얻어온 후에 구한다.
	else
	{
		CScene* scene = CSceneManager::GetInst()->GetScene();
		pos = m_pos - scene->GetCamera()->GetPos();
		cameraPos = scene->GetCamera()->GetPos();
		resolution = scene->GetCamera()->GetResolution();
	}
	
	
	

	


	// 오브젝트에 애니메이션이 존재한다면
	if (m_animation)
	{
		// 현재 애니메이션을 가져온다.
		CAnimationInfo* current = m_animation->m_currentAnimation;

		// 애니메이션의 현재 프레임 정보(몇 프레임까지 재생했는지)를 가져온다.
		const AnimationFrameData& frameData = current->m_sequence->GetFrame(current->m_frame);

		// 출력할 좌상단 위치를 구한다.
		Vector2	size = frameData.End - frameData.Start;

		Vector2	renderLT;
		renderLT = pos - m_pivot * size;

		/*
			최적화를 위해 카메라 영역 바깥에 있는 오브젝트를
			그리지 않기(컬링) 위한 코드이다.

			물체의 컬링위치(카메라가 적용되지 않은 위치**중요)를 구하고, 
			이 위치가 카메라 영역을 벗어나면 return 함으로써 구현한다. 
			(Rect 충돌과 비슷하다)
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

		// 애니메이션 텍스쳐가 sprite 형식의 이미지일 경우
		if (current->m_sequence->GetTextureType() == ETextureType::Sprite)
		{
			// 컬러키가 존재하면
			if (current->m_sequence->GetTexture()->GetEnableColorKey())
			{
				/*
				TransparentBlt : BitBlt와 1~6번인자는 같다.
				1. 이미지를 출력해줄 DC
				2. 출력해줄 DC에서의 x좌표
				3. 출력해줄 DC에서의 y좌표
				4. 그려낼 이미지의 가로크기
				5. 그려낼 이미지의 세로크기
				6. 이미지를 출력할 DC
				7.  출력할 이미지에서의 시작 x좌표
				8.  출력할 이미지에서의 시작 y좌표
				9.  출력할 이미지의 가로크기
				10. 출력할 이미지의 세로 크기
				11. 출력할 이미지에 대한 컬러키

				sprite이미지 기준으로 이미지에서 뽑아오는 시작점은 달라질 것이다.
				매번 시작점을 다르게 하여 이미지를 다르게 가져와야 한다.

				그러나 일단은 sprite이미지의 전체를 출력하도록 한다.(<- 애니메이션 안배운 상태)
			*/
				TransparentBlt(_hDC, (int)renderLT.x, (int)renderLT.y,
					(int)size.x, (int)size.y,
					current->m_sequence->GetTexture()->GetDC(),
					(int)frameData.Start.x, (int)frameData.Start.y,
					(int)size.x, (int)size.y,
					current->m_sequence->GetTexture()->GetColorKey());
			}
			// 컬러키가 없다면
			else
			{
				BitBlt(_hDC, (int)renderLT.x, (int)renderLT.y,
					(int)size.x, (int)size.y,
					current->m_sequence->GetTexture()->GetDC(),
					(int)frameData.Start.x, (int)frameData.Start.y, SRCCOPY);
			}
		}
		// 애니메이션 텍스쳐가 frame 이미지일 경우
		else
		{
			/*
				위 sprite일 때와 차이점을 보자.

				sprite일 경우 GetDC로 1장의 텍스쳐에 대해서만 가져오면 되기 때문에
				GetDC에 디폴트 인자를 전달하였지만,
				frame일 경우 연속된 매번 다른 텍스쳐에 대한 DC를 얻어와야 하기 때문에.
				GetDC에 m_frame을 인자로 전달한다.

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
			// 컬러키가 없다면
			else
			{
				BitBlt(_hDC, (int)renderLT.x, (int)renderLT.y,
					(int)size.x, (int)size.y,
					current->m_sequence->GetTexture()->GetDC(current->m_frame),
					(int)frameData.Start.x, (int)frameData.Start.y, SRCCOPY);
			}
		}
	}
	// 애니메이션이 없는 오브젝트일 경우
	else
	{
		// 게임 오브젝트가 가지고있는 텍스쳐로 출력하도록 한다.
		if (m_texture)
		{
			Vector2	RenderLT;

			RenderLT = pos - m_pivot * m_size;

			/*
			최적화를 위해 카메라 영역 바깥에 있는 오브젝트를
			그리지 않기(컬링) 위한 코드이다.

			물체의 컬링위치(카메라가 적용되지 않은 위치**중요)를 구하고,
			이 위치가 카메라 영역을 벗어나면 return 함으로써 구현한다.
			(Rect 충돌과 비슷하다)
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
				TransparentBlt : BitBlt와 1~6번인자는 같다.
				7.  출력할 이미지에서의 시작 x좌표
				8.  출력할 이미지에서의 시작 y좌표
				9.  출력할 이미지의 가로크기
				10. 출력할 이미지의 세로 크기
				11. 출력할 이미지에 대한 컬러키

				sprite이미지 기준으로 이미지에서 뽑아오는 시작점은 달라질 것이다.
				매번 시작점을 다르게 하여 이미지를 다르게 가져와야 한다.

				그러나 일단은 sprite이미지의 전체를 출력하도록 한다.(<- 애니메이션 안배운 상태)
			*/
			// 컬러키가 활성화 되어있을 경우
			if (m_texture->GetEnableColorKey())
			{
				TransparentBlt(_hDC, (int)RenderLT.x, (int)RenderLT.y,
					(int)m_size.x, (int)m_size.y, m_texture->GetDC(),
					0, 0, (int)m_size.x, (int)m_size.y, m_texture->GetColorKey());
			}

			/*
				BitBlt : 이미지를 원하는 DC에 출력해준다.
				1. 이미지를 출력해줄 DC
				2. 출력해줄 DC에서의 x좌표
				3. 출력해줄 DC에서의 y좌표
				4. 그려낼 이미지의 가로크기
				5. 그려낼 이미지의 세로크기
				6. 이미지를 출력할 DC
				7. 출력할 DC에서의 시작 x좌표
				8. 출력할 DC에서의 시작 y좌표
				9. 그리는 방법 지정 (SRCCOPY : 고속 복사)
			*/
			// 컬러키가 활성화되지 않았을 경우
			else
			{
				BitBlt(_hDC, (int)RenderLT.x, (int)RenderLT.y,
					(int)m_size.x, (int)m_size.y, m_texture->GetDC(),
					0, 0, SRCCOPY);
			}
		}
	}

	// 충돌체의 render를 호출한다.
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

	// 이전 위치를 갱신한다.
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
	// 해당 이름을 가진 텍스쳐를 찾아 오브젝트에 등록한다. 
	// 이 오브젝트가 속한 씬의 씬리소스를 통해 찾는게 마땅하다.
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

void CGameObject::SetTexture(CTexture* _texture)
{
	m_texture = _texture;
}

void CGameObject::SetTexture(const std::string& _name, const TCHAR* _fileName, const std::string& _pathName)
{
	// 먼저 텍스쳐를 로드하여, 씬리소스에 담는다.
	m_scene->GetSceneResource()->LoadTexture(_name, _fileName, _pathName);
	
	// 씬리소스에 존재하는 텍스쳐를 가져온다.
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

void CGameObject::SetTextureFullPath(const std::string& _name, const TCHAR* _fullPath)
{
	// 먼저 텍스쳐를 로드하여, 씬리소스에 담는다.
	m_scene->GetSceneResource()->LoadTextureFullPath(_name, _fullPath);

	// 씬리소스에 존재하는 텍스쳐를 가져온다.
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

#ifdef UNICODE

void CGameObject::SetTexture(const std::string& _name, const std::vector<std::wstring>& _vecFileName, const std::string& _pathName)
{
	// 먼저 텍스쳐를 로드하여, 씬리소스에 담는다.
	m_scene->GetSceneResource()->LoadTexture(_name, _vecFileName, _pathName);

	// 씬리소스에 존재하는 텍스쳐를 가져온다.
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

void CGameObject::SetTextureFullPath(const std::string& _name, const std::vector<std::wstring>& _vecFullPath)
{
	// 먼저 텍스쳐를 로드하여, 씬리소스에 담는다.
	m_scene->GetSceneResource()->LoadTextureFullPath (_name, _vecFullPath);

	// 씬리소스에 존재하는 텍스쳐를 가져온다.
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

#else

void CGameObject::SetTexture(const std::string& _name, const std::vector<std::string>& _vecFileName, const std::string& _pathName)
{
	// 먼저 텍스쳐를 로드하여, 씬리소스에 담는다.
	m_scene->GetSceneResource()->LoadTexture(_name, _vecFileName, _pathName);

	// 씬리소스에 존재하는 텍스쳐를 가져온다.
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}


void CGameObject::SetTextureFullPath(const std::string& _name, const std::vector<std::string>& _vecFullPath)
{
	// 먼저 텍스쳐를 로드하여, 씬리소스에 담는다.
	m_scene->GetSceneResource()->LoadTextureFullPath(_name, _vecFullPath);

	// 씬리소스에 존재하는 텍스쳐를 가져온다.
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

#endif // UNICODE

bool CGameObject::SetColorKey(unsigned char _r, unsigned char _g, unsigned char _b, int _index)
{
	// 현재 오브젝트에 대한 텍스쳐가 존재하는지. 없으면 리턴
	if (!m_texture)
		return false;

	// 인덱스에 해당하는 이미지의 컬러키를 지정한다.
	m_texture->SetColorKey(_r, _g, _b, _index);

	return true;
}

bool CGameObject::SetColorKeyAll(unsigned char _r, unsigned char _g, unsigned char _b)
{
	// 현재 오브젝트에 대한 텍스쳐가 존재하는지. 없으면 리턴
	if (!m_texture)
		return false;

	// 텍스쳐의 모든 이미지의 컬러키를 지정한다.
	m_texture->SetColorKeyAll(_r, _g, _b);

	return true;
}

void CGameObject::CreateAnimation()
{
	// 애니메이션 생성
	m_animation = new CAnimation;

	// 애니메이션이 속한 오브젝트와 씬 설정
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
	// 방향을 곱해 이동속도 만큼 특정 방향으로 이동시킨다.
	m_pos += _dir * m_moveSpeed * DELTA_TIME * m_timeScale;
}

void CGameObject::Move(const Vector2& _moveValue)
{
	// 정한 절대량만큼(그래서 델타타임을 곱하지 않는다.) 이동시킨다. 
	m_pos += _moveValue * m_timeScale;
}

void CGameObject::Move(float _angle)
{
	// 각도를 곱해 이동속도 만큼 특정 각도로 이동시킨다.
	Vector2	Dir;
	Dir.x = cosf(DegreeToRadian(_angle));
	Dir.y = sinf(DegreeToRadian(_angle));

	m_pos += Dir * m_moveSpeed * DELTA_TIME * m_timeScale;
}

void CGameObject::Jump()
{
	// 점프중이지 않을때만 돌아간다.
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
	// 객체 생성 시 타입 아이디(레퍼런스 클래스의 멤버)를 초기화
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
			충돌체끼리 충돌한 이후 CCollider의 소멸자에
			들어오지 않아 릭이 생긴다.
			레퍼런스 카운트가 0이 되지 않은 상태에서
			게임 오브젝트가 먼저 삭제되기 때문이다.

			따라서 이곳에서 게임오브젝트가 지워질 때, 전체
			반복을 돌면서 충돌체 리스트를 다 지울 것이다.
		*/
		auto	iter = m_colliderList.begin();
		auto	iterEnd = m_colliderList.end();

		for (; iter != iterEnd; ++iter)
		{
			(*iter)->ClearCollisionList();
		}
	}

	{
		// 마찬가지이다.
		auto	iter = m_widgetComponentList.begin();
		auto	iterEnd = m_widgetComponentList.end();

		for (; iter != iterEnd; ++iter)
		{
			(*iter)->SetActive(false);
		}
	}

	SAFE_DELETE(m_animation);
}
