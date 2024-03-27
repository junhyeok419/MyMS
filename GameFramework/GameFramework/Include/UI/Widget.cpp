#include "Widget.h"

bool CWidget::Init()
{
	return true;
}

void CWidget::Update(float _deltaTime)
{
}

void CWidget::PostUpdate(float _deltaTime)
{
}

void CWidget::Render(HDC _hDC, float _deltaTime)
{
}

void CWidget::Render(HDC _hDC, const Vector2& _pos, float _deltaTime)
{
}

const Vector2& CWidget::GetPos() const
{
	return m_pos;
}

const Vector2& CWidget::GetSize() const
{
	return m_size;
}

int CWidget::GetZOrder() const
{
	return m_zOrder;
}

void CWidget::SetPos(float _x, float _y)
{
	m_pos.x = _x;
	m_pos.y = _y;
}

void CWidget::SetPos(const Vector2& _pos)
{
	m_pos = _pos;
}

void CWidget::SetSize(float _x, float _y)
{
	m_size.x = _x;
	m_size.y = _y;
}

void CWidget::SetSize(const Vector2& _size)
{
	m_size = _size;
}

void CWidget::SetZOrder(int _zOrder)
{
	m_zOrder = _zOrder;
}

bool CWidget::CollisionMouse(const Vector2& _pos)
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

void CWidget::CollisionMouseHoveredCallback(const Vector2& _pos)
{
	m_mouseHovered = true;
}

void CWidget::CollisionMouseReleaseCallback()
{
	m_mouseHovered = false;
}

CWidget::CWidget()
	: m_scene(nullptr)
	, m_owner(nullptr)
	, m_zOrder(0)
	, m_mouseHovered(false)
{
}

CWidget::CWidget(const CWidget& widget)
	: CRef(widget)
	, m_zOrder(widget.m_zOrder)
	, m_mouseHovered(widget.m_mouseHovered)
{
}

CWidget::~CWidget()
{
}
