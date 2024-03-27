#include "SceneCollision.h"
#include "../Collision/Collider.h"
#include "../Input.h"
#include "../UI/WidgetWindow.h"
#include "../UI/Widget.h"

void CSceneCollision::AddCollider(CCollider* _collider)
{
	m_vecCollider.push_back(_collider);
}

void CSceneCollision::AddWidgetWindow(CWidgetWindow* _window)
{
	m_vecWidgetWindow.push_back(_window);
}

void CSceneCollision::Collision(float _deltaTime)
{
	/*
		실시간으로 현재 살아있는 모든 충돌체를 m_vecCollider에 넣고,
		전체 정렬하듯이 매번 충돌 체크(충돌 로직)를 할 것이다.

		충돌체 벡터는 매 프레임마다 갱신되어 새로 채워진다.
		매 프레임마다 지워지거나 추가되는 충돌체가 발생할 수 있기 때문이다.
	*/
	size_t	size = m_vecCollider.size();

	// 씬에 충돌체가 둘 이상 존재한다면 충돌 체크한다.
	if (size > 1)
	{
		for (size_t i = 0; i < size - 1; ++i)
		{
			CCollider* src = m_vecCollider[i];

			for (size_t j = i + 1; j < size; ++j)
			{
				CCollider* dest = m_vecCollider[j];

				// 같은 오브젝트에 속한 충돌체 끼리는 비교할 필요 없다.
				if (src->GetOwner() == dest->GetOwner())
					continue;

				// 충돌 프로파일을 가져와서 충돌시켜야 하는 물체인지 판단한다.
				const CollisionProfile* srcProfile = src->GetProfile();
				const CollisionProfile* destProfile = dest->GetProfile();

				// 프로파일에는 다른 채널과 상호작용을 어떻게 해야되는지가 정해져있다.
				// 그러므로 상대방 채널번째의 상호작용을 얻어와서 무시인지 충돌인지를 알아내야 한다.
				ECollisionInteraction	srcInteraction = srcProfile->VecCollisionInteraction[(int)destProfile->Channel];
				ECollisionInteraction	destInteraction = destProfile->VecCollisionInteraction[(int)srcProfile->Channel];

				// 둘중 하나라도 무시하기로 되어 있다면 충돌을 멈춘다.
				if (srcInteraction == ECollisionInteraction::Ignore ||
					destInteraction == ECollisionInteraction::Ignore)
					continue;

				/*
					위에서 충돌이 아닌 경우를 다 걸러냈으므로,
					이제 Collision을 호출하여 좌표상 충돌을 체크한다.
				*/
				if (src->Collision(dest))
				{
					/*
					    충돌 체크 후,
						'충돌된 충돌체 목록 리스트'가 비어있을 경우,
						'이제 막 충돌을 시작했다'는 의미이다.
					*/
					if (!src->CheckCollisionList(dest))
					{
						// 서로에게 상대방 충돌체를 충돌목록에 등록한다.
						src->AddCollisionList(dest);
						dest->AddCollisionList(src);

						// 충돌 시작 함수를 호출한다.
						src->CallCollisionBegin(dest);
						dest->CallCollisionBegin(src);
					}
				}

				/*
				    좌표상으로 충돌 상태가 아닌데
					'충돌된 목록 리스트'에 상대방 충돌체가 있다면,
					'충돌이 종료된 직후'(충돌된 물체가 서로 떨어짐)라는 의미이다.
				*/
				else if (src->CheckCollisionList(dest))
				{
					// 서로 목록에서 상대방 충돌체를 지워준다.
					src->DeleteCollisionList(dest);
					dest->DeleteCollisionList(src);

					// 충돌 종료 함수를 호출한다.
					src->CallCollisionEnd(dest);
					dest->CallCollisionEnd(src);
				}
			}
		}
	}
	// 매 프레임마다 오브젝트 벡터를 새로 채울 것이므로 모두 지워준다.
	m_vecCollider.clear();	
	// 매 프레임마다 위젯 윈도우 벡터를 새로 채울 것이므로 모두 지워준다.
	m_vecWidgetWindow.clear();

	/*
		장판 스킬과 같이 충돌을 지속적으로 확인해야 하는 경우,
		begin 함수에서 트리거를 true, end 함수에서 트리거를 false로
		하는 방법 등으로 계속 충돌을 확인할 수 있다.
	*/
}

void CSceneCollision::CollisionMouse(float _deltaTime)
{
	/*
		마우스 대 충돌체 체크를 하기 전에,
		당연히 마우스 대 ui 체크를 먼저 할 것이다.
	*/

	// 현재 씬의 위젯 윈도우의 개수를 받아온다.
	size_t	windowCount = m_vecWidgetWindow.size();

	bool	mouseCollision = false;

	// 위젯 윈도우가 존재하면
	if (windowCount >= 1)
	{
		// 위젯 윈도우가 2개 이상 존재하면 먼저 정렬해준다.
		if (windowCount > 1)
			std::sort(m_vecWidgetWindow.begin(), m_vecWidgetWindow.end(), CSceneCollision::SortWidget);
		
		// ui충돌은 '월드' 마우스 위치와 관련이 없으므로, 클라이언트 기준 마우스 위치를 가져온다.
		Vector2	mousePos = CInput::GetInst()->GetMousePos();

		// 충돌한 위젯이 있다면 이곳에 담길 것이다.
		CWidget* result = nullptr;

		// 반복 돌면서 모든 위젯에 대해 마우스와 충돌 체크를 한다.
		for (size_t i = 0; i < windowCount; ++i)
		{
			// 먼저 모든 위젯 윈도우를 zOrder가 큰 순으로 내림차순 정렬한다.
		    m_vecWidgetWindow[i]->SortCollision(); 

			/*
				위젯 윈도우별로 마우스와 충돌 체크를한다.
			    위젯 윈도우와 마우스가 충돌이라면, 
			    내부에서 이어서 해당 위젯 윈도우의 위젯과 마우스간의 
				충돌 체크를 할 것이다.
				
				충돌한 위젯이 있다면 result에 담길 것이다.
			*/

			// 마우스가 위젯과 충돌이라면
			if (m_vecWidgetWindow[i]->CollisionMouse(&result, mousePos))
			{
				/*
					기존에 마우스와 충돌한 '위젯'이 존재하는데 그것이 방금 충돌한 
					위젯이 아니라는 것은, 바로 전 까지 다른 위젯과 충돌 중이었다는 뜻이므로
				*/
				if (m_mouseCollisionWidget && m_mouseCollisionWidget!= result)
					// 이전 물체와의 hovered를 false로 바꿔준다.
					m_mouseCollisionWidget->CollisionMouseReleaseCallback();

				// 기존에 마우스와 충돌한 '충돌체'가 존재할 경우
				if (m_mouseCollision)
				{
					// 기존 충돌체의 마우스와의 충돌상태를 false로 바꿔준다.
					m_mouseCollision->SetMouseCollision(false);
					// 기존 충돌체의 마우스 충돌 종료 함수를 호출한다.
					m_mouseCollision->CallMouseCollisionEnd(CInput::GetInst()->GetMouseWorldPos());
					// 현재 마우스와 충돌한 충돌체를 '없음'으로 설정한다.
					m_mouseCollision = nullptr;
				}

				// 마우스와 충돌한 위젯을 담는다.
				m_mouseCollisionWidget = result;

				mouseCollision = true;

				break;
			}
		}
	}


	/*
		마우스와 위젯 충돌이 일어나지 않을 경우에만 
		마우스대 충돌체의 충돌 체크를 한다!!
	*/
	if (!mouseCollision)
	{
		/*
			마우스 대 위젯 충돌이 false인데 마우스와 충돌한 위젯이 있다는 것은,
			바로 전까지 충돌이었단 뜻이므로
		*/
		if (m_mouseCollisionWidget)
		{
			// 위젯에서 커서가 떨어졌을 때의 함수를 호출
			m_mouseCollisionWidget->CollisionMouseReleaseCallback();
			// 충돌중인 위젯 멤버를 '없음'으로
			m_mouseCollisionWidget = nullptr;
		}

		/*
			우리는 겹쳐있는 물체들을 y소팅을 사용해 오름차순으로
			정렬하여, y값이 클 수록 나중에 그려지도록 하였다.

			그러나 마우스 충돌 체크에서는 반대이다.
			y값이 클 수록(위에 그려질수록) 가장 먼저 충돌을 체크한다.
			(상태창 ui를 클릭했는데 뒤에있는 몬스터가 클릭되는거 자체가 말이 안된다.)
			따라서 마우스 충돌은 y소팅을 내림차순으로 해야 한다.
		*/

		// 씬에 존재하는 충돌체 전체 개수를 받아온다.
		size_t	size = m_vecCollider.size();

		if (size >= 1)
		{
			// 충돌체가 2개 이상일 경우, 마우스와 충돌 체크를 할 것이다.
			if (size > 1)
				// 벡터의 경우 algorithm에 존재하는 std::sort를 이용해 y좌표가 큰 순서로 정렬하여 충돌 체크를 한다. 
				std::sort(m_vecCollider.begin(), m_vecCollider.end(), CSceneCollision::SortY);

			// 마우스 커서의 월드상 좌표와 충돌 프로파일을 받아온다.
			Vector2	mouseWorldPos = CInput::GetInst()->GetMouseWorldPos();
			CollisionProfile* mouseProfile = CInput::GetInst()->GetMouseProfile();

			//// 기본 상태로 만들어준다.
			//bool mouseCollision = false;

			// 모든 충돌체를 순회하면서 마우스 커서와 충돌이 일어났는지 체크 할 것이다.
			for (size_t i = 0; i < size; ++i)
			{
				// 충돌체를 순서대로 받아온다.
				CCollider* dest = m_vecCollider[i];

				// 충돌 프로파일을 가져와서 충돌시켜야 하는 물체인지 판단한다.
				const CollisionProfile* srcProfile = mouseProfile;
				const CollisionProfile* destProfile = dest->GetProfile();

				// 프로파일에는 다른 채널과 상호작용을 어떻게 해야되는지가 정해져있다.
				// 그러므로 상대방 채널번째의 상호작용을 얻어와서 무시인지 충돌인지를 알아내야 한다.
				ECollisionInteraction	srcInteraction = srcProfile->VecCollisionInteraction[(int)destProfile->Channel];
				ECollisionInteraction	destInteraction = destProfile->VecCollisionInteraction[(int)srcProfile->Channel];

				// 둘중 하나라도 무시하기로 되어 있다면 충돌을 멈춘다.
				if (srcInteraction == ECollisionInteraction::Ignore ||
					destInteraction == ECollisionInteraction::Ignore)
					continue;

				// 여기까지 왔다면 서로 충돌이 가능하므로, 충돌을 체크한다.
				if (dest->CollisionMouse(mouseWorldPos))
				{
					// 충돌이니까
					// 마우스는 충돌 상태이다.
					mouseCollision = true;

					// 상대방의 mouseCollision 이 false 라면 '이제 막 충돌을 시작했다'는 의미이므로
					if (!dest->GetMouseCollision())
					{
						// 기존에 마우스와 충돌되던 충돌체가 있을 경우 충돌을 해제하고,
						if (m_mouseCollision)
							m_mouseCollision->SetMouseCollision(false);

						// 상대방 충돌체의 마우스와의 충돌 상태를 true로 만든다.
						dest->SetMouseCollision(true);

						// 충돌 시작 함수를 호출한다.
						dest->CallMouseCollisionBegin(mouseWorldPos);
					}

					// 마우스와 충돌한 충돌체(m_mouseCollision)로 dest를 넣어준다.
					m_mouseCollision = dest;

					break;
				}

				// 충돌이 아니지만 상대방의 마우스 충돌체가 존재(true)한다는 것은
				// '충돌이 되던 물체가 서로 떨어질 때'라는 뜻 이므로
				else if (dest->GetMouseCollision())
				{
					// 마우스와 충돌한 충돌체의, 마우스 충돌 상태를 false로 바꿔주고
					m_mouseCollision->SetMouseCollision(false);

					// '마우스와 충돌한 충돌체'도 이제 없기때문에 nullptr로 비워준다.
					m_mouseCollision = nullptr;
				}
			}

			/*
				mouseCollision 변수가 false를 유지하고 있다면, 마우스가 어떤 물체와도
				충돌이 아니라는 뜻이다.
				그러므로 이 경우엔 기존에 충돌되고 있던 물체가 있을 경우 지금은 충돌이
				안되고 있는 상황이므로 따로 예외처리를 한다.
			*/
			if (!mouseCollision)
			{
				// 그럼에도 '마우스와 충돌한 충돌체'가 존재한다면 
				if (m_mouseCollision)
				{
					// 마우스와 충돌한 충돌체의, 마우스 충돌 상태를 false로 바꿔주고
					m_mouseCollision->SetMouseCollision(false);

					// '마우스와 충돌한 충돌체'도 없기때문에 nullptr로 비워준다.
					m_mouseCollision = nullptr;
				}
			}
		}
	}
}

bool CSceneCollision::SortY(CCollider* _src, CCollider* _dest)
{
	// bottom이 큰 순서(y좌표가 큰 순서)로 정렬한다.
	return _src->GetBottom() > _dest->GetBottom();
}

bool CSceneCollision::SortWidget(CWidgetWindow* _src, CWidgetWindow* _dest)
{
	// zOrder이 큰 순서로 정렬한다. Scene의 SortWidget과 반대이다.
	return _src->GetZOrder() > _dest->GetZOrder();
}

CSceneCollision::CSceneCollision()
	: m_mouseCollision(nullptr)
	, m_mouseCollisionWidget(nullptr)
{
	// 충돌체 벡터에 여유공간을 500만큼 미리 할당한다.
	m_vecCollider.reserve(500);
}

CSceneCollision::~CSceneCollision()
{
}
