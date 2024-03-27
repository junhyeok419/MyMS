#include "WidgetWindow.h"

bool CWidgetWindow::Init()
{
	return true;
}

void CWidgetWindow::Update(float _deltaTime)
{
	// 위젯 윈도우 내의 위젯을 모두 업데이트한다.
	size_t	size = m_vecWidget.size();

	for (size_t i = 0; i < size; ++i)
	{
		m_vecWidget[i]->Update(_deltaTime);
	}
}

void CWidgetWindow::PostUpdate(float _deltaTime)
{
	// 위젯 윈도우 내의 위젯을 모두 post-업데이트한다.
	size_t	size = m_vecWidget.size();

	for (size_t i = 0; i < size; ++i)
	{
		m_vecWidget[i]->PostUpdate(_deltaTime);
	}
}

void CWidgetWindow::Render(HDC _hDC, float _deltaTime)
{
	size_t	size = m_vecWidget.size();

	// 위젯 윈도우 내의 위젯을 모두 오름차순 정렬한다.
	if (size > 1)
	{
		std::sort(m_vecWidget.begin(), m_vecWidget.end(), CWidgetWindow::SortWidget);
	}

	// 위젯 윈도우 내의 위젯을 모두 렌더링한다.
	for (size_t i = 0; i < size; ++i)
	{
		m_vecWidget[i]->Render(_hDC, _deltaTime);
	}
}

CWidget* CWidgetWindow::GetWidget(int _index)
{
	return m_vecWidget[_index];
}

int CWidgetWindow::GetWidgetCount() const
{
	return (int)m_vecWidget.size();

}
const Vector2& CWidgetWindow::GetPos() const
{
	return m_pos;
}

const Vector2& CWidgetWindow::GetSize() const
{
	return m_size;
}

int CWidgetWindow::GetZOrder() const
{
	return m_zOrder;
}

void CWidgetWindow::SetPos(float _x, float _y)
{
	m_pos.x = _x;
	m_pos.y = _y;
}

void CWidgetWindow::SetPos(const Vector2& _pos)
{
	m_pos = _pos;
}

void CWidgetWindow::SetSize(float _x, float _y)
{
	m_size.x = _x;
	m_size.y = _y;
}

void CWidgetWindow::SetSize(const Vector2& _size)
{
	m_size = _size;
}

void CWidgetWindow::SetZOrder(int _zOrder)
{
	m_zOrder = _zOrder;
}

bool CWidgetWindow::CollisionMouse(CWidget** _widget, const Vector2& _pos)
{
	/*
		먼저 마우스와 위젯 윈도우간 충돌인지 확인할 것이다.
		여기서 충돌이 아니라면,
		마우스와 위젯간의 충돌 체크도 할 필요가 없어진다.
		(최적화를 고려)
	*/

	/*
		마우스와 위젯 윈도우간의 충돌 체크
		좌표상으로 절대 충돌이 아닌 경우를 먼저 걸러준다.
	*/
	if (_pos.x < m_pos.x)
		return false;

	else if (_pos.y < m_pos.y)
		return false;

	else if (_pos.x > m_pos.x + m_size.x)
		return false;

	else if (_pos.y > m_pos.y + m_size.y)
		return false;

	/*
		위젯 윈도우와 마우스가 충돌이라면
	    위젯 윈도우 내의 위젯 벡터를 순회하면서
		마우스와 위젯간의 충돌을 체크한다.

		마우스는 중복 충돌이 안되므로
		1개만 충돌이어도 바로 함수를 빠져나간다.

		call-by-adress 함수로서,
		마우스와 충돌한 위젯을 _widget에 넣어 줄 것이다.
	*/
	size_t	widgetCount = m_vecWidget.size();

	for (size_t i = 0; i < widgetCount; ++i)
	{
		// enable false면 충돌체크안함
		if (!m_vecWidget[i]->GetEnable())
			continue;

		// 위젯과 마우스간 충돌 체크
		if (m_vecWidget[i]->CollisionMouse(_pos))
		{
			// 충돌이면 바로 리턴한다
			*_widget = m_vecWidget[i];
			return true;
		}
	}

	return false;
}

void CWidgetWindow::SortCollision()
{
	// 벡터의 위젯들을 zOrder가 큰 순으로 내림차순 정렬한다.
	if (m_vecWidget.size() > 1)
		std::sort(m_vecWidget.begin(), m_vecWidget.end(), 
			CWidgetWindow::SortCollisionWidget);
}

bool CWidgetWindow::SortCollisionWidget(const CSharedPtr<class CWidget>& _src, const CSharedPtr<class CWidget>& _dest)
{
	/*
		충돌 체크를 위한 정렬
        위젯 충돌 체크는 zOrder가 큰 순서로 체크해야 하므로
        zOrder가 큰 순으로 내림차순 정렬하여 벡터에 넣을 것이다.
	*/
	return _src->GetZOrder() > _dest->GetZOrder();
}

bool CWidgetWindow::SortWidget(const CSharedPtr<class CWidget>& _src, const CSharedPtr<class CWidget>& _dest)
{
	/*
		렌더링을 위한 정렬
        zOrder가 큰 위젯이 가장 마지막에 그려지므로,
        그릴 때는 zOrder가 작은 순서부터 오름차순으로 그려야 한다.
	*/
	return _src->GetZOrder() < _dest->GetZOrder();
}

CWidgetWindow::CWidgetWindow()
	: m_scene(nullptr)
	, m_zOrder(0)
{
}

CWidgetWindow::~CWidgetWindow()
{
}
