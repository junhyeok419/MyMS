#include "Text.h"
#include "../Resource/Font/Font.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "WidgetWindow.h"

bool CText::Init()
{
	// �ؽ�Ʈ ������ ����Ʈ ��Ʈ�� ������ ���� �ְ� �Ѵ�.
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
	// DC�� ��Ʈ�� �����Ѵ�
	m_font->SetFont(_hDC);

	Vector2	RenderPos = m_pos + m_owner->GetPos();

	/*
		SetBkMode : �ؽ�Ʈ�� ��µ� ������ŭ ��� �ڽ��� ��µǴµ�,
		�� �Լ��� ���ڷ� TRANSPARENT�� �����ϸ� ��� �ڽ��� ����
		����� �ȴ�.(�ؽ�Ʈ�� ������ ����� ����)
	*/
	SetBkMode(_hDC, TRANSPARENT);

	// �׸��ڸ� ����ؾ� �Ѵٸ� �׸��� ���� ����Ѵ�.
	if (m_shadow)
	{
		// �׸����� ��ġ�� �ؽ�Ʈ ��ġ�� �������� ���Ѵ�.
		Vector2	ShadowPos = RenderPos + m_shadowOffset;

		/*
			SetTextColor : �ؽ�Ʈ ������ �����ϴ� �����Լ��̴�.

			�츮�� ������ �Լ��� �̸��� ���� ������
			::�� �ٿ� �����Լ��� ȣ���� ����Ѵ�.
		*/
		::SetTextColor(_hDC, m_shadowColor);
		TextOut(_hDC, (int)ShadowPos.x, (int)ShadowPos.y, m_text, m_count);
	}

	// �׸��ڸ� ����ϰ� �� �� ���� �ؽ�Ʈ�� ���´�.
	::SetTextColor(_hDC, m_textColor);
	TextOut(_hDC, (int)RenderPos.x, (int)RenderPos.y, m_text, m_count);

	// ��Ʈ�� ������� �ǵ�����.
	m_font->ResetFont(_hDC);
}

void CText::Render(HDC _hDC, const Vector2& _pos, float _deltaTime)
{
	// DC�� ��Ʈ�� �����Ѵ�
	m_font->SetFont(_hDC);

	Vector2	RenderPos = _pos;

	/*
		SetBkMode : �ؽ�Ʈ�� ��µ� ������ŭ ��� �ڽ��� ��µǴµ�,
		�� �Լ��� ���ڷ� TRANSPARENT�� �����ϸ� ��� �ڽ��� ����
		����� �ȴ�.(�ؽ�Ʈ�� ������ ����� ����)
	*/
	SetBkMode(_hDC, TRANSPARENT);

	// �׸��ڸ� ����ؾ� �Ѵٸ� �׸��� ���� ����Ѵ�.
	if (m_shadow)
	{
		// �׸����� ��ġ�� �ؽ�Ʈ ��ġ�� �������� ���Ѵ�.
		Vector2	ShadowPos = RenderPos + m_shadowOffset;

		/*
			SetTextColor : �ؽ�Ʈ ������ �����ϴ� �����Լ��̴�.

			�츮�� ������ �Լ��� �̸��� ���� ������
			::�� �ٿ� �����Լ��� ȣ���� ����Ѵ�.
		*/
		::SetTextColor(_hDC, m_shadowColor);
		TextOut(_hDC, (int)ShadowPos.x, (int)ShadowPos.y, m_text, m_count);
	}

	// �׸��ڸ� ����ϰ� �� �� ���� �ؽ�Ʈ�� ���´�.
	::SetTextColor(_hDC, m_textColor);
	TextOut(_hDC, (int)RenderPos.x, (int)RenderPos.y, m_text, m_count);

	// ��Ʈ�� ������� �ǵ�����.
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
	// �ؽ�Ʈ ���̸� �޾ƿ´�.
	int Length = lstrlen(_text);

	// �ؽ�Ʈ ���̰� �ִ� �뷮���� ũ��
	if (Length + 1 > m_capacity)
	{
		// ���� �ؽ�Ʈ����� ����� ���ϴ� ���� + 1��ŭ ���Ҵ��Ѵ�.
		// 1�� �ι��ڸ� ���� ����
		m_capacity = Length + 1;

		SAFE_DELETE_ARRAY(m_text);

		m_text = new TCHAR[m_capacity];

		/*
		memset : �޸𸮸� ���ϴ� ũ�⸸ŭ, ���ϴ� ������ ä���.

		1�������� �޸��ּҺ���, 2�������� ������, 3������ ����Ʈ
		ũ�⸸ŭ ä��.
		*/
		// �ؽ�Ʈ ���ڿ��� 0���� �о��ش�.
		memset(m_text, 0, sizeof(TCHAR) * m_capacity);
	}

	// ���ϴ� �ؽ�Ʈ�� ���Ҵ��� �� �ؽ�Ʈ ���ڿ� ����� �����Ѵ�.
	lstrcpy(m_text, _text);

	// ���� �ؽ�Ʈ ������ ������Ų��.
	m_count = lstrlen(m_text);
}

void CText::AddText(const TCHAR _text)
{
	// ���� �ؽ�Ʈ ���̸� �޾ƿ� �ʿ����, 1���� �̹Ƿ� ������ +1�̴�.
	int Length = m_count + 1;

	// �ؽ�Ʈ ���̰� �ִ� �뷮���� ũ��
	if (Length + 1 > m_capacity)
	{
		/*
			���ϴ� ���� + 1��ŭ '���ο� ������' �Ҵ��Ѵ�.

			�̰��� ���� �ؽ�Ʈ ����� �ٷ� ������ �ʰ�,
			�� ������ ���縦 �ؼ� ����� �ϱ� ������
			SetText�� ���� �ٸ���.
		*/
		m_capacity = Length + 1;

		// ���ο� ���� �Ҵ�
		TCHAR* newText = new TCHAR[m_capacity];

		// 0���� �о��ش�
		memset(newText, 0, sizeof(TCHAR) * m_capacity);

		// ���ο� ������ ���� �ؽ�Ʈ ����� �����Ѵ�.
		lstrcpy(newText, m_text);

		// ���� �ؽ�Ʈ ����� �����.
		SAFE_DELETE_ARRAY(m_text);

		// ���ο� ������ �ؽ�Ʋ ����� �Ѵ�.
		m_text = newText;
	}

	// ���ϴ� �ؽ�Ʈ ���ڸ� ���Ҵ��� �ؽ�Ʈ ���ڿ� ����� �����Ѵ�.
	// ���ڿ��� �ƴϹǷ� ������� �ʿ����
	m_text[m_count] = _text;

	// ���� �ؽ�Ʈ ������ 1 ������Ų��.
	++m_count;
}

void CText::AddText(const TCHAR* _text)
{
	// ���� �ؽ�Ʈ ���̸� �޾ƿ´�.
	int Length = m_count + lstrlen(_text);

	// �ؽ�Ʈ ���̰� �ִ� �뷮���� ũ��
	if (Length + 1 > m_capacity)
	{
		/*
			���ϴ� ���� + 1��ŭ '���ο� ������' �Ҵ��Ѵ�.

			�̰��� ���� �ؽ�Ʈ ����� �ٷ� ������ �ʰ�,
			�� ������ ���縦 �ؼ� ����� �ϱ� ������ 
			SetText�� ���� �ٸ���.
		*/
		m_capacity = Length + 1;

		// ���ο� ���� �Ҵ�
		TCHAR* newText = new TCHAR[m_capacity];

		// 0���� �о��ش�
		memset(newText, 0, sizeof(TCHAR) * m_capacity);

		// ���ο� ������ ���� �ؽ�Ʈ ����� �����Ѵ�.
		lstrcpy(newText, m_text);

		// ���� �ؽ�Ʈ ����� �����.
		SAFE_DELETE_ARRAY(m_text);

		// ���ο� ������ �ؽ�Ʋ ����� �Ѵ�.
		m_text = newText;
	}

	// ���ϴ� �ؽ�Ʈ�� ���Ҵ��� �ؽ�Ʈ ���ڿ� ����� �����Ѵ�.
	lstrcpy(m_text, _text);

	// ���� �ؽ�Ʈ ������ ������Ų��.
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

	m_text = new TCHAR[m_capacity]; // �ִ� 32���� ���ڸ� ������ �ؽ�Ʈ

	/*
		memset : �޸𸮸� ���ϴ� ũ�⸸ŭ, ���ϴ� ������ ä���.

		1�������� �޸��ּҺ���, 2�������� ������, 3������ ����Ʈ
		ũ�⸸ŭ ä��.
	*/
	// �ؽ�Ʈ ���ڿ��� 0���� �о��ش�.
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
