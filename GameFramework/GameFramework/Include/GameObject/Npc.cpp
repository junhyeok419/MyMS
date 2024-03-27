#include "Npc.h"
#include "../Input.h"
#include "../UI/ImageWidget.h"
#include "Effect.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Resource/Sound/Sound.h"
#include "../Collision/ColliderBox.h"
#include "../UI/DialogWindow.h"

bool CNpc::Init()
{
	CGameObject::Init();

	if (!m_scene->GetSceneResource()->FindSound("Click"))
	{
		m_scene->GetSceneResource()->LoadSound("UI", "Click", false, "Maple/Mouse/NpcClick.mp3");
	}

	if (!m_scene->GetSceneResource()->FindSound("Hovered"))
	{
		m_scene->GetSceneResource()->LoadSound("UI", "Hovered", false, "Maple/Mouse/BtMouseOver.mp3");
	}

	m_stateSound[(int)EButtonSoundState::Click] = m_scene->GetSceneResource()->FindSound("Click");
	m_stateSound[(int)EButtonSoundState::MouseHovered] = m_scene->GetSceneResource()->FindSound("Hovered");

	// 이 오브젝트의 애니메이션을 생성한다.
	CreateAnimation();

	// 애니메이션을 추가한다. 
	AddAnimation("MuyeongGloomy", false, 1.5f);	 // 우울 
	AddAnimation("MuyeongSay", false, 1.5f);	  // 대화 
	AddAnimation("MuyeongStand", true);	  // 정지상태

	CColliderBox* box = AddCollider<CColliderBox>("Npc");
	box->SetExtent(80.f, 70.f);
	box->SetOffset(0.f, -30.5f);
	box->SetCollisionProfile("Npc");


	// 이름표 설정
	m_nameBarFrame = CreateWidgetComponent<CImageWidget>("NameBarMuyeong");
	m_nameBarFrame->GetWidget<CImageWidget>()->SetTexture("NameBarMuyeong", TEXT("Maple/UI/Basic/Name/NameBar_Muyeong.bmp"));
	m_nameBarFrame->GetWidget<CImageWidget>()->SetColorKey(255, 0, 255);
	m_nameBarFrame->GetWidget<CImageWidget>()->SetSize(56.f, 15.f);
	m_nameBarFrame->SetPos(-28.f, 0.f);




	return true;
}

void CNpc::Update(float _deltaTime)
{
	CCharacter::Update(_deltaTime);

	// 랜덤으로 애니메이션을 변화시킨다.
	if (m_aniChangeTime > 3.f)
	{
		m_aniChangeTime = 0.f;

		int random = rand() % 100;
		if (random >= 0 && random <= 30)
		{
			ChangeAnimation("MuyeongGloomy");

			CEffect* effect = m_scene->CreateObject<CEffect>("MuyeongBalloon1");
			effect->SetPos(m_pos + Vector2(5.f, -84.f));
			effect->AddAnimation("MuyeongBalloon1", false, 3.f);
		}
		else if (random >= 31 && random <= 59)
		{
			ChangeAnimation("MuyeongSay");

			CEffect* effect = m_scene->CreateObject<CEffect>("MuyeongBalloon2");
			effect->SetPos(m_pos + Vector2(5.f, -84.f));
			effect->AddAnimation("MuyeongBalloon2", false, 3.f);
		}
		else if (random >= 60 && random <= 99)
			ChangeAnimation("MuyeongStand");
	}
	else
		m_aniChangeTime += _deltaTime;

	if (m_buttonState == EButtonState::Click)
	{
		CInput::GetInst()->GetMouseObj()->ChangeAnimation("MouseClicked");
	}
	else if (m_buttonState == EButtonState::MouseHovered)
	{
		CInput::GetInst()->GetMouseObj()->ChangeAnimation("MouseHovered");
	}

	// 버튼이 활성화 중일 때에만 '버튼 클릭'에 대한 처리를 할 것이다.
	if (m_buttonState != EButtonState::Disable)
	{
		// 마우스가 버튼에 올라가 있을 경우
		if (m_mouseHovered)
		{
			// 마우스 버튼이 눌려있다면, '버튼 클릭 상태'로 변경
			if (CInput::GetInst()->GetMouseLDown())
			{

				m_buttonState = EButtonState::Click;
			}
			/*
				버튼을 눌렀다 뗐다면 기능을 동작하게 할 것이다.

				보통 버튼은 누르고 있을 때 동작하지 않고
				눌렀다 떼는 순간 동작하기 때문이다.
			*/
			else if (m_buttonState == EButtonState::Click &&
				CInput::GetInst()->GetMouseLUp())
			{
				// 버튼 사운드가 있다면 재생
			/*	if (m_stateSound[(int)EButtonSoundState::Click])
					m_stateSound[(int)EButtonSoundState::Click]->Play();*/
				// 버튼 콜백 함수가 있다면 호출
				if (m_callback[(int)EButtonSoundState::Click])
					m_callback[(int)EButtonSoundState::Click]();

				// 마우스가 버튼에 올라간 상태로 변경
				m_buttonState = EButtonState::MouseHovered;
			}
			// 아직 떼지 않고 누르는 중이라면
			else if (m_buttonState == EButtonState::Click &&
				CInput::GetInst()->GetMouseLPush())
				// '버튼 클릭 상태'를 유지한다.
				m_buttonState = EButtonState::Click;
			// 이도저도 아니라면 그냥 마우스를 버튼에 올리기만 한 상태라는 뜻
			else
			{
				// 마우스가 버튼에 올라간 상태로 변경
				m_buttonState = EButtonState::MouseHovered;
			}

		}
		// 마우스가 버튼에 올라가있지 않은 경우
		else
		{
			// 버튼은 아무 상태도 아님
			m_buttonState = EButtonState::Normal;
		}
	}
}

void CNpc::PostUpdate(float _deltaTime)
{
	CCharacter::PostUpdate(_deltaTime);
}

void CNpc::Render(HDC _hDC, float _deltaTime)
{
	CCharacter::Render(_hDC, _deltaTime);
}

bool CNpc::CollisionMouse(const Vector2& _pos)
{
	// 위젯과 마우스 간의 충돌 체크.

	// 충돌이 아닌 경우를 먼저 거른다. (점 대 사각형)
	if (_pos.x < m_pos.x)
		return false;

	else if (_pos.x > m_pos.x + m_size.x)
		return false;

	else if (_pos.y < m_pos.y)
		return false;

	else if (_pos.y > m_pos.y + m_size.y)
		return false;

	/*
		충돌일 경우,
		m_mouseHovered가 false라면 방금 막 충돌했다는 의미이므로
		콜백 함수를 호출한다.
	*/
	if (!m_mouseHovered)
		CollisionMouseHoveredCallback(_pos);

	return true;
}

void CNpc::CollisionMouseHoveredCallback(const Vector2& _pos)
{
	m_mouseHovered = true;
}

void CNpc::CollisionMouseReleaseCallback()
{
	m_mouseHovered = false;
}

void CNpc::OpenUIWindow()
{
	m_scene->CreateWidgetWindow<CDialogWindow>("DialogWindow");
}

CNpc::CNpc()
{
}

CNpc::~CNpc()
{
}
