#include "Button.h"
#include "../Resource/Texture/Texture.h"
#include "../Resource/Sound/Sound.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "WidgetWindow.h"
#include "../Input.h"
#include "../GameObject/GameObject.h"
bool CButton::Init()
{
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

	return true;
}

void CButton::Update(float _deltaTime)
{
	// �� ������Ʈ���� ��ư�� ����� ���� 
	m_size = m_stateData[(int)m_buttonState].End 
		- m_stateData[(int)m_buttonState].Start;

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
				if (m_stateSound[(int)EButtonSoundState::Click])
					m_stateSound[(int)EButtonSoundState::Click]->Play();
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

void CButton::PostUpdate(float _deltaTime)
{
}

void CButton::Render(HDC _hDC, float _deltaTime)
{
	/*
		ui�� ���� ������(owner) ���� ��ư ������ ��ġ�� ���ε�,
		��ư�� ��ġ�� ���� �����츦 ��������
		������� ��ġ�� ���� ���̴�.

		���� owner�� ��ġ�� ��ư ��ġ�� ���� ��ġ��
		���� ��µ� ��ư ��ġ�̴�.
	*/
	Vector2	renderPos = m_pos + m_owner->GetPos();

	// �ؽ��İ� ���� ��� 
	if (m_texture)
	{
		// �ؽ��İ� sprite ������ �̹����� ���
		if (m_texture->GetTextureType() == ETextureType::Sprite)
		{
			// �÷�Ű�� �����ϸ�
			if (m_texture->GetEnableColorKey())
			{
				TransparentBlt(_hDC, (int)renderPos.x, (int)renderPos.y,
					(int)m_size.x, (int)m_size.y,
					m_texture->GetDC(),
					(int)m_stateData[(int)m_buttonState].Start.x,
					(int)m_stateData[(int)m_buttonState].Start.y,
					(int)m_size.x, (int)m_size.y,
					m_texture->GetColorKey());
			}
			// �÷�Ű�� ���ٸ�
			else
			{
				BitBlt(_hDC, (int)renderPos.x, (int)renderPos.y,
					(int)m_size.x, (int)m_size.y,
					m_texture->GetDC(),
					(int)m_stateData[(int)m_buttonState].Start.x,
					(int)m_stateData[(int)m_buttonState].Start.y, SRCCOPY);
			}
		}
		// frame �̹����� ���?
		else
		{
			if (m_texture->GetEnableColorKey())
			{
				TransparentBlt(_hDC, (int)renderPos.x, (int)renderPos.y,
					(int)m_size.x, (int)m_size.y,
					m_texture->GetDC(),
					(int)m_stateData[(int)m_buttonState].Start.x,
					(int)m_stateData[(int)m_buttonState].Start.y,
					(int)m_size.x, (int)m_size.y,
					m_texture->GetColorKey());
			}

			else
			{
				BitBlt(_hDC, (int)renderPos.x, (int)renderPos.y,
					(int)m_size.x, (int)m_size.y,
					m_texture->GetDC(),
					(int)m_stateData[(int)m_buttonState].Start.x,
					(int)m_stateData[(int)m_buttonState].Start.y, SRCCOPY);
			}
		}
	}
	// �ؽ��İ� ���� ��� �簢�� ���
	else
	{
		Rectangle(_hDC, (int)renderPos.x, (int)renderPos.y,
			(int)(renderPos.x + m_size.x), (int)(renderPos.y + m_size.y));
	}
}

void CButton::Render(HDC _hDC, const Vector2& _pos, float _deltaTime)
{
	Vector2	renderPos = _pos;

	// �ؽ��İ� ���� ��� 
	if (m_texture)
	{
		// �ؽ��İ� sprite ������ �̹����� ���
		if (m_texture->GetTextureType() == ETextureType::Sprite)
		{
			// �÷�Ű�� �����ϸ�
			if (m_texture->GetEnableColorKey())
			{
				TransparentBlt(_hDC, (int)renderPos.x, (int)renderPos.y,
					(int)m_size.x, (int)m_size.y,
					m_texture->GetDC(),
					(int)m_stateData[(int)m_buttonState].Start.x,
					(int)m_stateData[(int)m_buttonState].Start.y,
					(int)m_size.x, (int)m_size.y,
					m_texture->GetColorKey());
			}
			// �÷�Ű�� ���ٸ�
			else
			{
				BitBlt(_hDC, (int)renderPos.x, (int)renderPos.y,
					(int)m_size.x, (int)m_size.y,
					m_texture->GetDC(),
					(int)m_stateData[(int)m_buttonState].Start.x,
					(int)m_stateData[(int)m_buttonState].Start.y, SRCCOPY);
			}
		}
		// frame �̹����� ���?
		else
		{
			if (m_texture->GetEnableColorKey())
			{
				TransparentBlt(_hDC, (int)renderPos.x, (int)renderPos.y,
					(int)m_size.x, (int)m_size.y,
					m_texture->GetDC(),
					m_stateData[(int)m_buttonState].Start.x,
					m_stateData[(int)m_buttonState].Start.y,
					(int)m_size.x, (int)m_size.y,
					m_texture->GetColorKey());
			}

			else
			{
				BitBlt(_hDC, (int)renderPos.x, (int)renderPos.y,
					(int)m_size.x, (int)m_size.y,
					m_texture->GetDC(),
					(int)m_stateData[(int)m_buttonState].Start.x,
					(int)m_stateData[(int)m_buttonState].Start.y, SRCCOPY);
			}
		}
	}
	// �ؽ��İ� ���� ��� �簢�� ���
	else
	{
		Rectangle(_hDC, (int)renderPos.x, (int)renderPos.y,
			(int)(renderPos.x + m_size.x), (int)(renderPos.y + m_size.y));
	}
}

void CButton::SetTexture(const std::string& _name, const TCHAR* _fileName, const std::string& _pathName)
{
	// ���ϴ� �ؽ��ĸ� �ε��ϰ�
	m_scene->GetSceneResource()->LoadTexture(_name, _fileName, _pathName);
	// �����´�.
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

void CButton::SetTextureFullPath(const std::string& _name, const TCHAR* _fullPath)
{
	// ���ϴ� �ؽ��ĸ� �ε��ϰ�
	m_scene->GetSceneResource()->LoadTextureFullPath(_name, _fullPath);
	// �����´�.
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

#ifdef UNICODE

void CButton::SetTexture(const std::string& _name, const std::vector<std::wstring>& _vecFileName, const std::string& _pathName)
{
	m_scene->GetSceneResource()->LoadTexture(_name, _vecFileName, _pathName);
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

void CButton::SetTextureFullPath(const std::string& _name, const std::vector<std::wstring>& _vecFullPath)
{
	m_scene->GetSceneResource()->LoadTextureFullPath(_name, _vecFullPath);
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

#else

void CButton::SetTexture(const std::string& _name, const std::vector<std::string>& _vecFileName, const std::string& _pathName)
{
	m_scene->GetSceneResource()->LoadTexture(_name, _vecFileName, _pathName);
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

void CButton::SetTextureFullPath(const std::string& _name, const std::vector<std::string>& _vecFullPath)
{
	m_scene->GetSceneResource()->LoadTextureFullPath(_name, _vecFullPath);
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

#endif // UNICODE

void CButton::SetButtonStateData(EButtonState _state, const Vector2& _start, const Vector2& _end)
{
	// ���ϴ� ��ư ���¿�, �ִϸ��̼� ����� ���� ������ ��ǥ�� �ִ´�.
	m_stateData[(int)_state].Start = _start;
	m_stateData[(int)_state].End = _end;
}

void CButton::EnableButton(bool _enable)
{
	// ��ư�� Ȱ��ȭ Ȥ�� ��Ȱ��ȭ �Ѵ�.
	m_buttonState = _enable ? EButtonState::Normal : EButtonState::Disable;
}

void CButton::SetSound(EButtonSoundState _state, const std::string& _name)
{
	// ���ϴ� ��ư ���¿� ���ϴ� �̸��� ���带 �ִ´�.
	m_stateSound[(int)_state]
		= m_scene->GetSceneResource()->FindSound(_name);
}

void CButton::CollisionMouseHoveredCallback(const Vector2& _pos)
{
	// ���� �̰��� ���� ��ư ���¸� �ٲ��ְ�
	CWidget::CollisionMouseHoveredCallback(_pos);

	// ���� ��ư�� ����(MouseHovered)�� ���� ���带 ����Ѵ�. 
	if (m_stateSound[(int)EButtonSoundState::MouseHovered])
		m_stateSound[(int)EButtonSoundState::MouseHovered]->Play();

	// ���� ��ư�� ����(MouseHovered)�� ���� �ݹ� �Լ��� ȣ���Ѵ�.  
	if (m_callback[(int)EButtonSoundState::MouseHovered])
		m_callback[(int)EButtonSoundState::MouseHovered]();
}

void CButton::CollisionMouseReleaseCallback()
{
	CWidget::CollisionMouseReleaseCallback();
}

CButton::CButton()
	: m_buttonState(EButtonState::Normal)
	, m_stateData{}
{
}

CButton::CButton(const CButton& _widget)
	: CWidget(_widget)
{
}

CButton::~CButton()
{
}

