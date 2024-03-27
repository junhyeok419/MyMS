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

	// �� ������Ʈ�� �ִϸ��̼��� �����Ѵ�.
	CreateAnimation();

	// �ִϸ��̼��� �߰��Ѵ�. 
	AddAnimation("MuyeongGloomy", false, 1.5f);	 // ��� 
	AddAnimation("MuyeongSay", false, 1.5f);	  // ��ȭ 
	AddAnimation("MuyeongStand", true);	  // ��������

	CColliderBox* box = AddCollider<CColliderBox>("Npc");
	box->SetExtent(80.f, 70.f);
	box->SetOffset(0.f, -30.5f);
	box->SetCollisionProfile("Npc");


	// �̸�ǥ ����
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

	// �������� �ִϸ��̼��� ��ȭ��Ų��.
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

	// ��ư�� Ȱ��ȭ ���� ������ '��ư Ŭ��'�� ���� ó���� �� ���̴�.
	if (m_buttonState != EButtonState::Disable)
	{
		// ���콺�� ��ư�� �ö� ���� ���
		if (m_mouseHovered)
		{
			// ���콺 ��ư�� �����ִٸ�, '��ư Ŭ�� ����'�� ����
			if (CInput::GetInst()->GetMouseLDown())
			{

				m_buttonState = EButtonState::Click;
			}
			/*
				��ư�� ������ �ôٸ� ����� �����ϰ� �� ���̴�.

				���� ��ư�� ������ ���� �� �������� �ʰ�
				������ ���� ���� �����ϱ� �����̴�.
			*/
			else if (m_buttonState == EButtonState::Click &&
				CInput::GetInst()->GetMouseLUp())
			{
				// ��ư ���尡 �ִٸ� ���
			/*	if (m_stateSound[(int)EButtonSoundState::Click])
					m_stateSound[(int)EButtonSoundState::Click]->Play();*/
				// ��ư �ݹ� �Լ��� �ִٸ� ȣ��
				if (m_callback[(int)EButtonSoundState::Click])
					m_callback[(int)EButtonSoundState::Click]();

				// ���콺�� ��ư�� �ö� ���·� ����
				m_buttonState = EButtonState::MouseHovered;
			}
			// ���� ���� �ʰ� ������ ���̶��
			else if (m_buttonState == EButtonState::Click &&
				CInput::GetInst()->GetMouseLPush())
				// '��ư Ŭ�� ����'�� �����Ѵ�.
				m_buttonState = EButtonState::Click;
			// �̵����� �ƴ϶�� �׳� ���콺�� ��ư�� �ø��⸸ �� ���¶�� ��
			else
			{
				// ���콺�� ��ư�� �ö� ���·� ����
				m_buttonState = EButtonState::MouseHovered;
			}

		}
		// ���콺�� ��ư�� �ö����� ���� ���
		else
		{
			// ��ư�� �ƹ� ���µ� �ƴ�
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
	// ������ ���콺 ���� �浹 üũ.

	// �浹�� �ƴ� ��츦 ���� �Ÿ���. (�� �� �簢��)
	if (_pos.x < m_pos.x)
		return false;

	else if (_pos.x > m_pos.x + m_size.x)
		return false;

	else if (_pos.y < m_pos.y)
		return false;

	else if (_pos.y > m_pos.y + m_size.y)
		return false;

	/*
		�浹�� ���,
		m_mouseHovered�� false��� ��� �� �浹�ߴٴ� �ǹ��̹Ƿ�
		�ݹ� �Լ��� ȣ���Ѵ�.
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
