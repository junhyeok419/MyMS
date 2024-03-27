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
	// 매 업데이트에서 버튼의 사이즈를 갱신 
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
				if (m_stateSound[(int)EButtonSoundState::Click])
					m_stateSound[(int)EButtonSoundState::Click]->Play();
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

void CButton::PostUpdate(float _deltaTime)
{
}

void CButton::Render(HDC _hDC, float _deltaTime)
{
	/*
		ui용 위젯 윈도우(owner) 내에 버튼 위젯을 배치할 것인데,
		버튼의 위치는 위젯 윈도우를 기준으로
		상대적인 위치로 구할 것이다.

		따라서 owner의 위치에 버튼 위치를 더한 위치가
		실제 출력될 버튼 위치이다.
	*/
	Vector2	renderPos = m_pos + m_owner->GetPos();

	// 텍스쳐가 있을 경우 
	if (m_texture)
	{
		// 텍스쳐가 sprite 형식의 이미지일 경우
		if (m_texture->GetTextureType() == ETextureType::Sprite)
		{
			// 컬러키가 존재하면
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
			// 컬러키가 없다면
			else
			{
				BitBlt(_hDC, (int)renderPos.x, (int)renderPos.y,
					(int)m_size.x, (int)m_size.y,
					m_texture->GetDC(),
					(int)m_stateData[(int)m_buttonState].Start.x,
					(int)m_stateData[(int)m_buttonState].Start.y, SRCCOPY);
			}
		}
		// frame 이미지일 경우?
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
	// 텍스쳐가 없을 경우 사각형 출력
	else
	{
		Rectangle(_hDC, (int)renderPos.x, (int)renderPos.y,
			(int)(renderPos.x + m_size.x), (int)(renderPos.y + m_size.y));
	}
}

void CButton::Render(HDC _hDC, const Vector2& _pos, float _deltaTime)
{
	Vector2	renderPos = _pos;

	// 텍스쳐가 있을 경우 
	if (m_texture)
	{
		// 텍스쳐가 sprite 형식의 이미지일 경우
		if (m_texture->GetTextureType() == ETextureType::Sprite)
		{
			// 컬러키가 존재하면
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
			// 컬러키가 없다면
			else
			{
				BitBlt(_hDC, (int)renderPos.x, (int)renderPos.y,
					(int)m_size.x, (int)m_size.y,
					m_texture->GetDC(),
					(int)m_stateData[(int)m_buttonState].Start.x,
					(int)m_stateData[(int)m_buttonState].Start.y, SRCCOPY);
			}
		}
		// frame 이미지일 경우?
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
	// 텍스쳐가 없을 경우 사각형 출력
	else
	{
		Rectangle(_hDC, (int)renderPos.x, (int)renderPos.y,
			(int)(renderPos.x + m_size.x), (int)(renderPos.y + m_size.y));
	}
}

void CButton::SetTexture(const std::string& _name, const TCHAR* _fileName, const std::string& _pathName)
{
	// 원하는 텍스쳐를 로드하고
	m_scene->GetSceneResource()->LoadTexture(_name, _fileName, _pathName);
	// 가져온다.
	m_texture = m_scene->GetSceneResource()->FindTexture(_name);
}

void CButton::SetTextureFullPath(const std::string& _name, const TCHAR* _fullPath)
{
	// 원하는 텍스쳐를 로드하고
	m_scene->GetSceneResource()->LoadTextureFullPath(_name, _fullPath);
	// 가져온다.
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
	// 원하는 버튼 상태에, 애니메이션 재생을 위한 프레임 좌표를 넣는다.
	m_stateData[(int)_state].Start = _start;
	m_stateData[(int)_state].End = _end;
}

void CButton::EnableButton(bool _enable)
{
	// 버튼을 활성화 혹은 비활성화 한다.
	m_buttonState = _enable ? EButtonState::Normal : EButtonState::Disable;
}

void CButton::SetSound(EButtonSoundState _state, const std::string& _name)
{
	// 원하는 버튼 상태에 원하는 이름의 사운드를 넣는다.
	m_stateSound[(int)_state]
		= m_scene->GetSceneResource()->FindSound(_name);
}

void CButton::CollisionMouseHoveredCallback(const Vector2& _pos)
{
	// 먼저 이곳을 통해 버튼 상태를 바꿔주고
	CWidget::CollisionMouseHoveredCallback(_pos);

	// 현재 버튼의 상태(MouseHovered)에 따른 사운드를 재생한다. 
	if (m_stateSound[(int)EButtonSoundState::MouseHovered])
		m_stateSound[(int)EButtonSoundState::MouseHovered]->Play();

	// 현재 버튼의 상태(MouseHovered)에 따른 콜백 함수를 호출한다.  
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

