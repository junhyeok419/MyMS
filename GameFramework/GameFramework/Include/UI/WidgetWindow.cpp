#include "WidgetWindow.h"

bool CWidgetWindow::Init()
{
	return true;
}

void CWidgetWindow::Update(float _deltaTime)
{
	// ���� ������ ���� ������ ��� ������Ʈ�Ѵ�.
	size_t	size = m_vecWidget.size();

	for (size_t i = 0; i < size; ++i)
	{
		m_vecWidget[i]->Update(_deltaTime);
	}
}

void CWidgetWindow::PostUpdate(float _deltaTime)
{
	// ���� ������ ���� ������ ��� post-������Ʈ�Ѵ�.
	size_t	size = m_vecWidget.size();

	for (size_t i = 0; i < size; ++i)
	{
		m_vecWidget[i]->PostUpdate(_deltaTime);
	}
}

void CWidgetWindow::Render(HDC _hDC, float _deltaTime)
{
	size_t	size = m_vecWidget.size();

	// ���� ������ ���� ������ ��� �������� �����Ѵ�.
	if (size > 1)
	{
		std::sort(m_vecWidget.begin(), m_vecWidget.end(), CWidgetWindow::SortWidget);
	}

	// ���� ������ ���� ������ ��� �������Ѵ�.
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
		���� ���콺�� ���� �����찣 �浹���� Ȯ���� ���̴�.
		���⼭ �浹�� �ƴ϶��,
		���콺�� �������� �浹 üũ�� �� �ʿ䰡 ��������.
		(����ȭ�� ���)
	*/

	/*
		���콺�� ���� �����찣�� �浹 üũ
		��ǥ������ ���� �浹�� �ƴ� ��츦 ���� �ɷ��ش�.
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
		���� ������� ���콺�� �浹�̶��
	    ���� ������ ���� ���� ���͸� ��ȸ�ϸ鼭
		���콺�� �������� �浹�� üũ�Ѵ�.

		���콺�� �ߺ� �浹�� �ȵǹǷ�
		1���� �浹�̾ �ٷ� �Լ��� ����������.

		call-by-adress �Լ��μ�,
		���콺�� �浹�� ������ _widget�� �־� �� ���̴�.
	*/
	size_t	widgetCount = m_vecWidget.size();

	for (size_t i = 0; i < widgetCount; ++i)
	{
		// enable false�� �浹üũ����
		if (!m_vecWidget[i]->GetEnable())
			continue;

		// ������ ���콺�� �浹 üũ
		if (m_vecWidget[i]->CollisionMouse(_pos))
		{
			// �浹�̸� �ٷ� �����Ѵ�
			*_widget = m_vecWidget[i];
			return true;
		}
	}

	return false;
}

void CWidgetWindow::SortCollision()
{
	// ������ �������� zOrder�� ū ������ �������� �����Ѵ�.
	if (m_vecWidget.size() > 1)
		std::sort(m_vecWidget.begin(), m_vecWidget.end(), 
			CWidgetWindow::SortCollisionWidget);
}

bool CWidgetWindow::SortCollisionWidget(const CSharedPtr<class CWidget>& _src, const CSharedPtr<class CWidget>& _dest)
{
	/*
		�浹 üũ�� ���� ����
        ���� �浹 üũ�� zOrder�� ū ������ üũ�ؾ� �ϹǷ�
        zOrder�� ū ������ �������� �����Ͽ� ���Ϳ� ���� ���̴�.
	*/
	return _src->GetZOrder() > _dest->GetZOrder();
}

bool CWidgetWindow::SortWidget(const CSharedPtr<class CWidget>& _src, const CSharedPtr<class CWidget>& _dest)
{
	/*
		�������� ���� ����
        zOrder�� ū ������ ���� �������� �׷����Ƿ�,
        �׸� ���� zOrder�� ���� �������� ������������ �׷��� �Ѵ�.
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
