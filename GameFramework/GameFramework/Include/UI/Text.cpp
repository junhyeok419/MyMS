#include "Text.h"
#include "../Resource/Font/Font.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "WidgetWindow.h"

bool CText::Init()
{
	// 텍스트 위젯이 디폴트 폰트를 무조건 갖고 있게 한다.
	m_font = m_scene->GetSceneResource()->FindFont("DefaultFont");
	
	return true;
}

void CText::Update(float _deltaTime)
{
}

void CText::PostUpdate(float _deltaTime)
{
}

void CText::Render(HDC _hDC, float _deltaTime)
{
	// DC에 폰트를 설정한다
	m_font->SetFont(_hDC);

	Vector2	RenderPos = m_pos + m_owner->GetPos();

	/*
		SetBkMode : 텍스트는 출력된 영역만큼 흰색 박스가 출력되는데,
		이 함수에 인자로 TRANSPARENT를 전달하면 흰색 박스를 빼고
		출력이 된다.(텍스트를 제외한 배경이 빠짐)
	*/
	SetBkMode(_hDC, TRANSPARENT);

	// 그림자를 출력해야 한다면 그림자 먼저 출력한다.
	if (m_shadow)
	{
		// 그림자의 위치는 텍스트 위치에 오프셋을 더한다.
		Vector2	ShadowPos = RenderPos + m_shadowOffset;

		/*
			SetTextColor : 텍스트 색상을 변경하는 전역함수이다.

			우리가 정의한 함수와 이름이 같기 때문에
			::를 붙여 전역함수의 호출을 명시한다.
		*/
		::SetTextColor(_hDC, m_shadowColor);
		TextOut(_hDC, (int)ShadowPos.x, (int)ShadowPos.y, m_text, m_count);
	}

	// 그림자를 출력하고 난 뒤 원본 텍스트를 덮는다.
	::SetTextColor(_hDC, m_textColor);
	TextOut(_hDC, (int)RenderPos.x, (int)RenderPos.y, m_text, m_count);

	// 폰트를 원래대로 되돌린다.
	m_font->ResetFont(_hDC);
}

void CText::Render(HDC _hDC, const Vector2& _pos, float _deltaTime)
{
	// DC에 폰트를 설정한다
	m_font->SetFont(_hDC);

	Vector2	RenderPos = _pos;

	/*
		SetBkMode : 텍스트는 출력된 영역만큼 흰색 박스가 출력되는데,
		이 함수에 인자로 TRANSPARENT를 전달하면 흰색 박스를 빼고
		출력이 된다.(텍스트를 제외한 배경이 빠짐)
	*/
	SetBkMode(_hDC, TRANSPARENT);

	// 그림자를 출력해야 한다면 그림자 먼저 출력한다.
	if (m_shadow)
	{
		// 그림자의 위치는 텍스트 위치에 오프셋을 더한다.
		Vector2	ShadowPos = RenderPos + m_shadowOffset;

		/*
			SetTextColor : 텍스트 색상을 변경하는 전역함수이다.

			우리가 정의한 함수와 이름이 같기 때문에
			::를 붙여 전역함수의 호출을 명시한다.
		*/
		::SetTextColor(_hDC, m_shadowColor);
		TextOut(_hDC, (int)ShadowPos.x, (int)ShadowPos.y, m_text, m_count);
	}

	// 그림자를 출력하고 난 뒤 원본 텍스트를 덮는다.
	::SetTextColor(_hDC, m_textColor);
	TextOut(_hDC, (int)RenderPos.x, (int)RenderPos.y, m_text, m_count);

	// 폰트를 원래대로 되돌린다.
	m_font->ResetFont(_hDC);
}

void CText::SetTextColor(unsigned char _r, unsigned char _g, unsigned char _b)
{
	m_textColor = RGB(_r, _g, _b);
}

void CText::SetTextShadowColor(unsigned char _r, unsigned char _g, unsigned char _b)
{
	m_shadowColor = RGB(_r, _g, _b);
}

void CText::EnableShadow(bool _shadow)
{
	m_shadow = _shadow;
}

void CText::SetShadowOffset(float _x, float _y)
{
	m_shadowOffset = Vector2(_x, _y);
}

void CText::SetText(const TCHAR* _text)
{
	// 텍스트 길이를 받아온다.
	int Length = lstrlen(_text);

	// 텍스트 길이가 최대 용량보다 크면
	if (Length + 1 > m_capacity)
	{
		// 기존 텍스트멤버를 지우고 원하는 길이 + 1만큼 재할당한다.
		// 1은 널문자를 위항 공간
		m_capacity = Length + 1;

		SAFE_DELETE_ARRAY(m_text);

		m_text = new TCHAR[m_capacity];

		/*
		memset : 메모리를 원하는 크기만큼, 원하는 값으로 채운다.

		1번인자의 메모리주소부터, 2번인자의 값으로, 3번인자 바이트
		크기만큼 채움.
		*/
		// 텍스트 문자열을 0으로 밀어준다.
		memset(m_text, 0, sizeof(TCHAR) * m_capacity);
	}

	// 원하는 텍스트를 재할당한 빈 텍스트 문자열 멤버에 복사한다.
	lstrcpy(m_text, _text);

	// 현재 텍스트 개수를 증가시킨다.
	m_count = lstrlen(m_text);
}

void CText::AddText(const TCHAR _text)
{
	// 최종 텍스트 길이를 받아올 필요없이, 1글자 이므로 무조건 +1이다.
	int Length = m_count + 1;

	// 텍스트 길이가 최대 용량보다 크면
	if (Length + 1 > m_capacity)
	{
		/*
			원하는 길이 + 1만큼 '새로운 공간을' 할당한다.

			이것은 기존 텍스트 멤버를 바로 지우지 않고,
			새 공간에 복사를 해서 살려야 하기 때문에
			SetText랑 조금 다르다.
		*/
		m_capacity = Length + 1;

		// 새로운 공간 할당
		TCHAR* newText = new TCHAR[m_capacity];

		// 0으로 밀어준다
		memset(newText, 0, sizeof(TCHAR) * m_capacity);

		// 새로운 공간에 기존 텍스트 멤버를 복사한다.
		lstrcpy(newText, m_text);

		// 기존 텍스트 멤버를 지운다.
		SAFE_DELETE_ARRAY(m_text);

		// 새로운 공간을 텍스틀 멤버로 한다.
		m_text = newText;
	}

	// 원하는 텍스트 문자를 재할당한 텍스트 문자열 멤버에 대입한다.
	// 문자열이 아니므로 복사까지 필요없다
	m_text[m_count] = _text;

	// 현재 텍스트 개수를 1 증가시킨다.
	++m_count;
}

void CText::AddText(const TCHAR* _text)
{
	// 최종 텍스트 길이를 받아온다.
	int Length = m_count + lstrlen(_text);

	// 텍스트 길이가 최대 용량보다 크면
	if (Length + 1 > m_capacity)
	{
		/*
			원하는 길이 + 1만큼 '새로운 공간을' 할당한다.

			이것은 기존 텍스트 멤버를 바로 지우지 않고,
			새 공간에 복사를 해서 살려야 하기 때문에 
			SetText랑 조금 다르다.
		*/
		m_capacity = Length + 1;

		// 새로운 공간 할당
		TCHAR* newText = new TCHAR[m_capacity];

		// 0으로 밀어준다
		memset(newText, 0, sizeof(TCHAR) * m_capacity);

		// 새로운 공간에 기존 텍스트 멤버를 복사한다.
		lstrcpy(newText, m_text);

		// 기존 텍스트 멤버를 지운다.
		SAFE_DELETE_ARRAY(m_text);

		// 새로운 공간을 텍스틀 멤버로 한다.
		m_text = newText;
	}

	// 원하는 텍스트를 재할당한 텍스트 문자열 멤버에 복사한다.
	lstrcpy(m_text, _text);

	// 현재 텍스트 개수를 증가시킨다.
	m_count += lstrlen(m_text);
}

void CText::pop_back()
{
	--m_count;

	m_text[m_count] = 0;
}

void CText::clear()
{
	m_count = 0;

	m_text[m_count] = 0;
}

void CText::SetFont(const std::string& _name)
{
	m_font = m_scene->GetSceneResource()->FindFont(_name);
}

CText::CText()
{
	m_count = 0;
	m_capacity = 32;	

	m_text = new TCHAR[m_capacity]; // 최대 32개의 문자를 가지는 텍스트

	/*
		memset : 메모리를 원하는 크기만큼, 원하는 값으로 채운다.

		1번인자의 메모리주소부터, 2번인자의 값으로, 3번인자 바이트
		크기만큼 채움.
	*/
	// 텍스트 문자열을 0으로 밀어준다.
	memset(m_text, 0, sizeof(TCHAR) * m_capacity);

	m_textColor = RGB(0, 0, 0);
	m_shadowColor = RGB(30, 30, 30);
	m_shadow = false;
	m_shadowOffset = Vector2(1.f, 1.f);  
}

CText::CText(const CText& _widget)
	: CWidget(_widget)
{
}

CText::~CText()
{
	SAFE_DELETE_ARRAY(m_text);
}
