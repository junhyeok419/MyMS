#include "ColliderLine.h"
#include "../GameObject/GameObject.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "CollisionManager.h"
#include "ColliderCircle.h" // �� �� �� �浹 ó���� ����
#include "ColliderBox.h" // �� �� �ڽ� �浹 ó���� ����

bool CColliderLine::Init()
{
	if (!CCollider::Init())
		return false;

	return true;
}

void CColliderLine::Update(float _deltaTime)
{
	CCollider::Update(_deltaTime);
}

void CColliderLine::PostUpdate(float _deltaTime)
{
	CCollider::PostUpdate(_deltaTime);
}

void CColliderLine::Render(HDC _hDC, float _deltaTime)
{
	/*
		����� ����� ��쿡�� �浹ü�� ���� ���̰� �� ���̴�.
		ifdef _DEBUG : ����� ����� ���� ����ȴ�.
		ifdef NDEBUG : ������ ����� ���� ����ȴ�.
	*/

	/*
		�ڽ� �浹ü�� �簢����  �����ӷ�Ʈ (����� ����ִ�,
		�����θ� �̷����) ������� �׸� ���̴�.

		�����ӷ�Ʈ ����� Hbrush ��� ���� �̿��� ���� � ������ �� ��
		�����Ѵ�.
	*/
	
#ifdef _DEBUG

	// �⺻����, ���ӸŴ������� �ʷϻ� �귯���� ���� �׸� ���̴�..
	HPEN pen = CGameManager::GetInst()->GetPen(EBrushType::Green);
	
	/*
		'�浹 ��� ����Ʈ'�� ������� �ʴٴ� ���� ���� �浹���̶�� ���̴�.
		�浹���� ��쿣 ������ �귯���� ���� �׸� ���̴�.
	*/
	if (!m_collisionList.empty() || m_mouseCollision)  // ���콺 �浹�� ��쿡�� ���������� �ٲ��ش�.
 		pen = CGameManager::GetInst()->GetPen(EBrushType::Red);

	// ������ ����ִ� �⺻ ������ �޾Ƴ���, �ʷ�(����)������ �ٲ۴�.
	HPEN	PrevPen = (HPEN)SelectObject(_hDC, pen);

	// ������� ��ġ�� �׷��� �Ѵ�. (�̰� ���ϸ� ����ٴ�)
	CCamera* camera = m_scene->GetCamera();

	//RECT	renderRC;

	//renderRC.left = (long)(m_info.Point1.x - camera->GetPos().x);
	//renderRC.top = (long)(m_info.Point1.y - camera->GetPos().y);
	//renderRC.right = (long)(m_info.Point2.x - camera->GetPos().x);
	//renderRC.bottom = (long)(m_info.Point2.y - camera->GetPos().y);

	//// 2��° ������ ������ 3��° ������ �귯�� �������� �׸���.
	//FrameRect(_hDC, &renderRC, brush);

	// ���� �ȹٲ� �̰ŷ� �ϸ� �ȵɵ�
	MoveToEx(_hDC, m_info.Point1.x - camera->GetPos().x, m_info.Point1.y - camera->GetPos().y, nullptr);
	LineTo(_hDC, m_info.Point2.x - camera->GetPos().x, m_info.Point2.y - camera->GetPos().y);

	SelectObject(_hDC, PrevPen);

#endif // _DEBUG
}

bool CColliderLine::Collision(CCollider* _dest)
{
	// ���� �浹ü(_dest)�� ��翡 ���� �ٸ��� �浹 ó���� �Ѵ�.
	switch (_dest->GetColliderType())
	{
	case EColliderType::Box:
		return CCollisionManager::GetInst()->
			CollisionBoxToLine(m_hitPoint, (CColliderBox*)_dest, this);
		// Line to Line
	/*case EColliderType::Line:
		return CCollisionManager::GetInst()->
			CollisionLineToLine(m_hitPoint, this, (CColliderLine*)_dest);*/
		// Line to Circle
	/*case EColliderType::Circle:
		return CCollisionManager::GetInst()->CollisionLineToCircle(m_hitPoint, this, (CColliderCircle*)_dest);*/
	}

	return false;
}

//bool CColliderLine::CollisionMouse(const Vector2& _mouse)
//{
//	// �浹 �������� '�� �� �簢�� �浹' üũ �Լ��� ȣ��
//	/*return CCollisionManager::GetInst()->
//		CollisionPointToLine(m_hitPoint, _mouse, m_info);*/
//}

const LineInfo& CColliderLine::GetLineInfo() const
{
	return m_info;
}

ELineType CColliderLine::GetType() const
{
	return m_type;
}

LineInfo CColliderLine::GetInfo() const
{
	return m_info;
}

void CColliderLine::SetType(ELineType _type)
{
	m_type = _type;
}

void CColliderLine::SetInfo(const Vector2& _pos1, const Vector2& _pos2)
{
	m_info.Point1 = _pos1;
	m_info.Point2 = _pos2;
}

void CColliderLine::SetLength(float _length)
{
	m_length = _length;
}

const float& CColliderLine::GetLength() const
{
	return m_length;
}

CColliderLine::CColliderLine()
	: m_length(0.f)
{
	// ù �ʱ�ȭ�� ���۷��� Ŭ������ �̸��� ����Ѵ�.
	SetTypeID<CColliderLine>();

	// �浹 Ÿ���� '�ڽ�'�� �����Ѵ�.
	m_colliderType = EColliderType::Line;
}

CColliderLine::CColliderLine(const CColliderLine& _collider)
	: CCollider(_collider)
	, m_length(_collider.m_length)
	, m_info(_collider.m_info)
{
}

CColliderLine::~CColliderLine()
{
}
