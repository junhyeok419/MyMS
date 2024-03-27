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
	// 오브젝트 리스트를 순회한다.
	for (int i = 0; i < (int)ERenderLayer::Max; ++i)
	{
		/*
		auto : 대입한 타입으로 타입이 선언된다.
		선언과 동시에 대입(초기화)할 경우에만 사용 가능하다.
		*/
		auto	iter = m_objList[i].begin();
		auto	iterEnd = m_objList[i].end();

		// 오브젝트 리스트를 순회한다.
		for (; iter != iterEnd;)
		{
			// 오브젝트가 죽어있다면
			if (!(*iter)->GetActive())
			{
				/*
					리스트에서 제거한다.
					제거하는 순간 공유포인터의 소멸자가 호출되어
					레퍼런스 카운트가 1 감소한다.
				*/
				iter = m_objList[i].erase(iter);
				iterEnd = m_objList[i].end();
				continue;
			}
			// 죽은건 아니고 단지 비활성화 상태라면
			else if (!(*iter)->GetEnable())
			{
				// 업데이트 대상에서 제외한다.
				++iter;
				continue;
			}
			// 이외의 경우(활성화 상태)만 업데이트 한다.
			(*iter)->Update(_deltaTime);
			++iter;
		}
	}

	auto	iter2 = m_monsterList.begin();
	auto	iter2End = m_monsterList.end();


	// 몬스터 지워주기
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

	// 위젯 벡터를 순회한다.
	for (; iter1 != iter1End;)
	{
		// 위젯이 죽어있다면
		if (!(*iter1)->GetActive())
		{
			/*
				벡터에서 제거한다.
				제거하는 순간 공유포인터의 소멸자가 호출되어
				레퍼런스 카운트가 1 감소한다.
			*/
			iter1 = m_vecWidgetWindow.erase(iter1);
			iter1End = m_vecWidgetWindow.end();
			continue;
		}
		// 죽은건 아니고 단지 비활성화 상태라면
		else if (!(*iter1)->GetEnable())
		{	
			// 업데이트 대상에서 제외한다.
			++iter1;
			continue;
		}
		// 이외의 경우(활성화 상태)만 업데이트 한다.
		(*iter1)->Update(_deltaTime);
		++iter1;
	}

	// 카메라를 업데이트한다. 
	m_camera->Update(_deltaTime);
}

void CScene::PostUpdate(float _deltaTime)
{
	// 오브젝트
	for (int i = 0; i < (int)ERenderLayer::Max; ++i)
	{
		auto	iter = m_objList[i].begin();
		auto	iterEnd = m_objList[i].end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				// 리스트에서 제거하는 순간 SharedPtr의 소멸자가 호출되어
				// 카운트가 감소한다.
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


	// 몬스터 지워주기
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


	// 위젯
	auto	iter1 = m_vecWidgetWindow.begin();
	auto	iter1End = m_vecWidgetWindow.end();

	for (; iter1 != iter1End;)
	{
		// 위젯이 죽어있다면
		if (!(*iter1)->GetActive())
		{
			/*
				벡터에서 제거한다.
				제거하는 순간 공유포인터의 소멸자가 호출되어
				레퍼런스 카운트가 1 감소한다.
			*/
			iter1 = m_vecWidgetWindow.erase(iter1);
			iter1End = m_vecWidgetWindow.end();
			continue;
		}
		// 죽은건 아니고 단지 비활성화 상태라면
		else if (!(*iter1)->GetEnable())
		{
			// 업데이트 대상에서 제외한다.
			++iter1;
			continue;
		}
		// 이외의 경우(활성화 상태)만 포스트-업데이트 한다.
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

		// 업데이트가 완료된 활성화 위젯들을 벡터에 추가한다.
		m_collision->AddWidgetWindow(*iter1);
		++iter1;
	}

	m_collision->CollisionMouse(_deltaTime); // 마우스 충돌 먼저 체크
	m_collision->Collision(_deltaTime);	
}

void CScene::Render(HDC _hDC, float _deltaTime)
{
	// 오브젝트 리스트를 순회한다.
	for (int i = 0; i < (int)ERenderLayer::Max; ++i)
	{
		///*
		//	플레이어 가까이 있는 오브젝트와 먼저 충돌 상호작용이
		//	가능하도록 하기 위함이다.
		//*/
		//if (m_player)
		//{
		//	if (m_player->m_dir == 1)
		//		// 출력 목력을 오름차순 정리한다 (x소팅)
		//		m_objList[i].sort(SortX_Up);
		//	else if (m_player->m_dir == -1)
		//		// 출력 목력을 내림차순 정리한다 (x소팅)
		//		m_objList[i].sort(SortX_Down);
		//}
		//else 
			m_objList[i].sort(SortY);

		/*
			auto : 대입한 타입으로 타입이 선언된다.
			선언과 동시에 대입(초기화)할 경우에만 사용 가능하다.
		*/
		auto	iter = m_objList[i].begin();
		auto	iterEnd = m_objList[i].end();
		
		// 오브젝트 리스트를 순회한다.
		for (; iter != iterEnd;)
		{
			// 오브젝트가 죽어있다면
			if (!(*iter)->GetActive())
			{
				/*
					리스트에서 제거한다.
					제거하는 순간 공유포인터의 소멸자가 호출되어
					레퍼런스 카운트가 1 감소한다.
				*/
				iter = m_objList[i].erase(iter);
				iterEnd = m_objList[i].end();
				continue;
			}
			// 죽은건 아니고 단지 비활성화 상태라면
			else if (!(*iter)->GetEnable())
			{
				// 렌더링 대상에서 제외한다.
				++iter;
				continue;
			}
			// 이외의 경우(활성화 상태)만 렌더링 한다.
			(*iter)->Render(_hDC, _deltaTime);
			++iter;
		}
	}

	
	{
		// 위젯 컴포넌트를 출력하면서, 제거될 위젯 컴포넌트를 제거한다.
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

		// 정렬한다.
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


	// 몬스터에 지워줄 놈이 있는지 갱신한다.
	auto	iter2 = m_monsterList.begin();
	auto	iter2End = m_monsterList.end();

	// 몬스터 지워주기
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


	// 월드공간의 물체가 출력된 이후에 UI를 출력한다.
	if (m_vecWidgetWindow.size() > 1)
		// zOrder가 작은것부터 벡터에 넣어 큰녀석을 나중에 그리도록 함.
		std::sort(m_vecWidgetWindow.begin(), m_vecWidgetWindow.end(), CScene::SortWidget);
	
	// 위젯이 활성화 상태인 것만 render를 진행한다.
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

	// UI를 출력한 이후에 마우스를 출력한다.
	
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
	// 발밑 기준으로 정렬을 진행해야 하기 때문에 발밑의 Y를 구해준다.
	float	srcY = _src->GetPos().y + (1.f - _src->GetPivot().y) * _src->GetSize().y;
	float	destY = _dest->GetPos().y + (1.f - _dest->GetPivot().y) * _dest->GetSize().y;

	return srcY < destY;
}

bool CScene::SortX_Down(const CSharedPtr<class CGameObject>& _src, const CSharedPtr<class CGameObject>& _dest)
{
	float	srcX = _src->GetPos().x;
	float	destX = _dest->GetPos().x;

	// 플레이어가 왼쪽을 보고 있을 경우, 몬스터는 x좌표가 큰 순으로 정렬
	return srcX > destX;
}

bool CScene::SortX_Up(const CSharedPtr<class CGameObject>& _src, const CSharedPtr<class CGameObject>& _dest)
{
	float	srcX = _src->GetPos().x;
	float	destX = _dest->GetPos().x;

	// 플레이어가 오른쪽을 보고 있을 경우, 몬스터는 x좌표가 작은 순으로 정렬
	return srcX < destX;	
}

bool CScene::SortYWidgetComponent(const CSharedPtr<class CWidgetComponent>& _src, const CSharedPtr<class CWidgetComponent>& _dest)
{
	// 위젯 컴포넌트의 bottom 좌표(가장 아래의 y좌표)가 큰 순서대로 출력하기 위한 정렬함수이다.
	return _src->GetBottom() < _dest->GetBottom();
}

bool CScene::SortWidget(const CSharedPtr<CWidgetWindow>& _src, const CSharedPtr<CWidgetWindow>& _dest)
{
	return _src->GetZOrder() < _dest->GetZOrder();
}

CScene::CScene()
	: m_collision(nullptr)
{

	// 씬 리소스를 생성한다.
	m_resource = new CSceneResource;
	// 카메라를 생성한다.
	m_camera = new CCamera;
	// 씬 컬리젼을 생성한다.
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
