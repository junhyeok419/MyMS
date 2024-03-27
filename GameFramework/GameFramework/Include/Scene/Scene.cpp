#include "Scene.h"
#include "../GameObject/GameObject.h"
#include "SceneResource.h"
#include "Camera.h"
#include "SceneCollision.h"
#include "../GameObject/Monster.h"
bool CScene::Init()
{
	return true;
}

void CScene::Update(float _deltaTime)
{
	// ������Ʈ ����Ʈ�� ��ȸ�Ѵ�.
	for (int i = 0; i < (int)ERenderLayer::Max; ++i)
	{
		/*
		auto : ������ Ÿ������ Ÿ���� ����ȴ�.
		����� ���ÿ� ����(�ʱ�ȭ)�� ��쿡�� ��� �����ϴ�.
		*/
		auto	iter = m_objList[i].begin();
		auto	iterEnd = m_objList[i].end();

		// ������Ʈ ����Ʈ�� ��ȸ�Ѵ�.
		for (; iter != iterEnd;)
		{
			// ������Ʈ�� �׾��ִٸ�
			if (!(*iter)->GetActive())
			{
				/*
					����Ʈ���� �����Ѵ�.
					�����ϴ� ���� ������������ �Ҹ��ڰ� ȣ��Ǿ�
					���۷��� ī��Ʈ�� 1 �����Ѵ�.
				*/
				iter = m_objList[i].erase(iter);
				iterEnd = m_objList[i].end();
				continue;
			}
			// ������ �ƴϰ� ���� ��Ȱ��ȭ ���¶��
			else if (!(*iter)->GetEnable())
			{
				// ������Ʈ ��󿡼� �����Ѵ�.
				++iter;
				continue;
			}
			// �̿��� ���(Ȱ��ȭ ����)�� ������Ʈ �Ѵ�.
			(*iter)->Update(_deltaTime);
			++iter;
		}
	}

	auto	iter2 = m_monsterList.begin();
	auto	iter2End = m_monsterList.end();


	// ���� �����ֱ�
	for (; iter2 != iter2End;)
	{
		if (!(*iter2)->GetActive())
		{
			iter2 = m_monsterList.erase(iter2);
			iter2End = m_monsterList.end();
			continue;
		}
		++iter2;
	}


	auto	iter1 = m_vecWidgetWindow.begin();
	auto	iter1End = m_vecWidgetWindow.end();

	// ���� ���͸� ��ȸ�Ѵ�.
	for (; iter1 != iter1End;)
	{
		// ������ �׾��ִٸ�
		if (!(*iter1)->GetActive())
		{
			/*
				���Ϳ��� �����Ѵ�.
				�����ϴ� ���� ������������ �Ҹ��ڰ� ȣ��Ǿ�
				���۷��� ī��Ʈ�� 1 �����Ѵ�.
			*/
			iter1 = m_vecWidgetWindow.erase(iter1);
			iter1End = m_vecWidgetWindow.end();
			continue;
		}
		// ������ �ƴϰ� ���� ��Ȱ��ȭ ���¶��
		else if (!(*iter1)->GetEnable())
		{	
			// ������Ʈ ��󿡼� �����Ѵ�.
			++iter1;
			continue;
		}
		// �̿��� ���(Ȱ��ȭ ����)�� ������Ʈ �Ѵ�.
		(*iter1)->Update(_deltaTime);
		++iter1;
	}

	// ī�޶� ������Ʈ�Ѵ�. 
	m_camera->Update(_deltaTime);
}

void CScene::PostUpdate(float _deltaTime)
{
	// ������Ʈ
	for (int i = 0; i < (int)ERenderLayer::Max; ++i)
	{
		auto	iter = m_objList[i].begin();
		auto	iterEnd = m_objList[i].end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				// ����Ʈ���� �����ϴ� ���� SharedPtr�� �Ҹ��ڰ� ȣ��Ǿ�
				// ī��Ʈ�� �����Ѵ�.
				iter = m_objList[i].erase(iter);
				iterEnd = m_objList[i].end();
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

	auto	iter2 = m_monsterList.begin();
	auto	iter2End = m_monsterList.end();


	// ���� �����ֱ�
	for (; iter2 != iter2End;)
	{
		
		if (!(*iter2)->GetActive())
		{
			iter2 = m_monsterList.erase(iter2);
			iter2End = m_monsterList.end();
			continue;
		}
		++iter2;
	}


	// ����
	auto	iter1 = m_vecWidgetWindow.begin();
	auto	iter1End = m_vecWidgetWindow.end();

	for (; iter1 != iter1End;)
	{
		// ������ �׾��ִٸ�
		if (!(*iter1)->GetActive())
		{
			/*
				���Ϳ��� �����Ѵ�.
				�����ϴ� ���� ������������ �Ҹ��ڰ� ȣ��Ǿ�
				���۷��� ī��Ʈ�� 1 �����Ѵ�.
			*/
			iter1 = m_vecWidgetWindow.erase(iter1);
			iter1End = m_vecWidgetWindow.end();
			continue;
		}
		// ������ �ƴϰ� ���� ��Ȱ��ȭ ���¶��
		else if (!(*iter1)->GetEnable())
		{
			// ������Ʈ ��󿡼� �����Ѵ�.
			++iter1;
			continue;
		}
		// �̿��� ���(Ȱ��ȭ ����)�� ����Ʈ-������Ʈ �Ѵ�.
		(*iter1)->PostUpdate(_deltaTime);
		++iter1;
	}

	iter1 = m_vecWidgetWindow.begin();
	iter1End = m_vecWidgetWindow.end();

	for (; iter1 != iter1End;)
	{
		if (!(*iter1)->GetActive())
		{
			iter1 = m_vecWidgetWindow.erase(iter1);
			iter1End = m_vecWidgetWindow.end();
			continue;
		}

		else if (!(*iter1)->GetEnable())
		{
			++iter1;
			continue;
		}

		// ������Ʈ�� �Ϸ�� Ȱ��ȭ �������� ���Ϳ� �߰��Ѵ�.
		m_collision->AddWidgetWindow(*iter1);
		++iter1;
	}

	m_collision->CollisionMouse(_deltaTime); // ���콺 �浹 ���� üũ
	m_collision->Collision(_deltaTime);	
}

void CScene::Render(HDC _hDC, float _deltaTime)
{
	// ������Ʈ ����Ʈ�� ��ȸ�Ѵ�.
	for (int i = 0; i < (int)ERenderLayer::Max; ++i)
	{
		///*
		//	�÷��̾� ������ �ִ� ������Ʈ�� ���� �浹 ��ȣ�ۿ���
		//	�����ϵ��� �ϱ� �����̴�.
		//*/
		//if (m_player)
		//{
		//	if (m_player->m_dir == 1)
		//		// ��� ����� �������� �����Ѵ� (x����)
		//		m_objList[i].sort(SortX_Up);
		//	else if (m_player->m_dir == -1)
		//		// ��� ����� �������� �����Ѵ� (x����)
		//		m_objList[i].sort(SortX_Down);
		//}
		//else 
			m_objList[i].sort(SortY);

		/*
			auto : ������ Ÿ������ Ÿ���� ����ȴ�.
			����� ���ÿ� ����(�ʱ�ȭ)�� ��쿡�� ��� �����ϴ�.
		*/
		auto	iter = m_objList[i].begin();
		auto	iterEnd = m_objList[i].end();
		
		// ������Ʈ ����Ʈ�� ��ȸ�Ѵ�.
		for (; iter != iterEnd;)
		{
			// ������Ʈ�� �׾��ִٸ�
			if (!(*iter)->GetActive())
			{
				/*
					����Ʈ���� �����Ѵ�.
					�����ϴ� ���� ������������ �Ҹ��ڰ� ȣ��Ǿ�
					���۷��� ī��Ʈ�� 1 �����Ѵ�.
				*/
				iter = m_objList[i].erase(iter);
				iterEnd = m_objList[i].end();
				continue;
			}
			// ������ �ƴϰ� ���� ��Ȱ��ȭ ���¶��
			else if (!(*iter)->GetEnable())
			{
				// ������ ��󿡼� �����Ѵ�.
				++iter;
				continue;
			}
			// �̿��� ���(Ȱ��ȭ ����)�� ������ �Ѵ�.
			(*iter)->Render(_hDC, _deltaTime);
			++iter;
		}
	}

	
	{
		// ���� ������Ʈ�� ����ϸ鼭, ���ŵ� ���� ������Ʈ�� �����Ѵ�.
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

			++iter;
		}

		// �����Ѵ�.
		m_widgetComponentList.sort(SortYWidgetComponent);

		iter = m_widgetComponentList.begin();
		iterEnd = m_widgetComponentList.end();

		for (; iter != iterEnd; ++iter)
		{
			if (!(*iter)->GetEnable())
			{
				continue;
			}

			(*iter)->Render(_hDC, _deltaTime);
		}
	}


	// ���Ϳ� ������ ���� �ִ��� �����Ѵ�.
	auto	iter2 = m_monsterList.begin();
	auto	iter2End = m_monsterList.end();

	// ���� �����ֱ�
	for (; iter2 != iter2End;)
	{
		
		if (!(*iter2)->GetActive())
		{
			iter2 = m_monsterList.erase(iter2);
			iter2End = m_monsterList.end();
			continue;
		}
		
		++iter2;
	}


	// ��������� ��ü�� ��µ� ���Ŀ� UI�� ����Ѵ�.
	if (m_vecWidgetWindow.size() > 1)
		// zOrder�� �����ͺ��� ���Ϳ� �־� ū�༮�� ���߿� �׸����� ��.
		std::sort(m_vecWidgetWindow.begin(), m_vecWidgetWindow.end(), CScene::SortWidget);
	
	// ������ Ȱ��ȭ ������ �͸� render�� �����Ѵ�.
	auto	iter1 = m_vecWidgetWindow.begin();
	auto	iter1End = m_vecWidgetWindow.end();

	for (; iter1 != iter1End;)
	{
		if (!(*iter1)->GetActive())
		{
			iter1 = m_vecWidgetWindow.erase(iter1);
			iter1End = m_vecWidgetWindow.end();
			continue;
		}

		else if (!(*iter1)->GetEnable())
		{
			++iter1;
			continue;
		}

		(*iter1)->Render(_hDC, _deltaTime);
		++iter1;
	}

	// UI�� ����� ���Ŀ� ���콺�� ����Ѵ�.
	
}

void CScene::SetGrace(bool _grace)
{
	m_playerGrace = _grace;
}

bool CScene::GetGrace()
{
	return m_playerGrace;
}

CSceneCollision* CScene::GetCollision() const
{
	return m_collision;
}

void CScene::SetEffect(CGameObject* _effect)
{

}

void CScene::SetPlayer(CGameObject* _player)
{
	m_player = _player;
}

CCamera* CScene::GetCamera() const
{
	return m_camera;
}

CGameObject* CScene::GetPlayer() const
{
	return m_player;
}

CSceneResource* CScene::GetSceneResource() const
{
	return m_resource;
}

void CScene::AddWidgetComponent(CWidgetComponent* _widget)
{
	m_widgetComponentList.push_back(_widget);
}

bool CScene::SortY(const CSharedPtr<class CGameObject>& _src, const CSharedPtr<class CGameObject>& _dest)
{
	// �߹� �������� ������ �����ؾ� �ϱ� ������ �߹��� Y�� �����ش�.
	float	srcY = _src->GetPos().y + (1.f - _src->GetPivot().y) * _src->GetSize().y;
	float	destY = _dest->GetPos().y + (1.f - _dest->GetPivot().y) * _dest->GetSize().y;

	return srcY < destY;
}

bool CScene::SortX_Down(const CSharedPtr<class CGameObject>& _src, const CSharedPtr<class CGameObject>& _dest)
{
	float	srcX = _src->GetPos().x;
	float	destX = _dest->GetPos().x;

	// �÷��̾ ������ ���� ���� ���, ���ʹ� x��ǥ�� ū ������ ����
	return srcX > destX;
}

bool CScene::SortX_Up(const CSharedPtr<class CGameObject>& _src, const CSharedPtr<class CGameObject>& _dest)
{
	float	srcX = _src->GetPos().x;
	float	destX = _dest->GetPos().x;

	// �÷��̾ �������� ���� ���� ���, ���ʹ� x��ǥ�� ���� ������ ����
	return srcX < destX;	
}

bool CScene::SortYWidgetComponent(const CSharedPtr<class CWidgetComponent>& _src, const CSharedPtr<class CWidgetComponent>& _dest)
{
	// ���� ������Ʈ�� bottom ��ǥ(���� �Ʒ��� y��ǥ)�� ū ������� ����ϱ� ���� �����Լ��̴�.
	return _src->GetBottom() < _dest->GetBottom();
}

bool CScene::SortWidget(const CSharedPtr<CWidgetWindow>& _src, const CSharedPtr<CWidgetWindow>& _dest)
{
	return _src->GetZOrder() < _dest->GetZOrder();
}

CScene::CScene()
	: m_collision(nullptr)
{

	// �� ���ҽ��� �����Ѵ�.
	m_resource = new CSceneResource;
	// ī�޶� �����Ѵ�.
	m_camera = new CCamera;
	// �� �ø����� �����Ѵ�.
	m_collision = new CSceneCollision;
}

CScene::~CScene()
{
	for (int i = 0; i < (int)ERenderLayer::Max; ++i)
	{
		m_objList[i].clear();
	}

	m_monsterList.clear();

	SAFE_DELETE(m_collision);
	SAFE_DELETE(m_resource);
	SAFE_DELETE(m_camera);
}
