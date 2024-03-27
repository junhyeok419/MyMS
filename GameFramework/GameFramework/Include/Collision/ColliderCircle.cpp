#include "ColliderCircle.h"
#include "../GameObject/GameObject.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "CollisionManager.h"
#include "ColliderBox.h"	// �� �� �ڽ� �浹 ó���� ����

bool CColliderCircle::Init()
{
	if (!CCollider::Init())
		return false;

	return true;
}

void CColliderCircle::Update(float _deltaTime)
{
	CCollider::Update(_deltaTime);
}

void CColliderCircle::PostUpdate(float _deltaTime)
{
	CCollider::PostUpdate(_deltaTime);

	/*
	   �浹ü�� ������ ��� ������Ʈ ���ش�. 
	
	   �� �浹ü�� ������ �浹ü�� ���� ������Ʈ(Owner)�� pos OffSet�� 
       ���� ���̴�. 
	*/
	Vector2	pos = m_owner->GetPos();
	m_info.Center = pos + m_offset;

	// ���콺 �浹 üũ�� ���� bottom�� ���� (�� �浹ü)
	m_bottom = m_info.Center.y + m_info.Radius;
}

void CColliderCircle::Render(HDC _hDC, float _deltaTime)
{
	/*
		�� �浹ü�� ���� LineTo�� �̿��� ������ �׸� ���̴�.
		ellipse�� ���ΰ� ä���� �ִ� ���̱� ������,
		LineTo�� �׷����� ���� HPEN�� �̿��� ������ �����Ѵ�.

		** ���� MoveToEx�� �̿��� �������� 0�� ������ ������ ��ŭ
		   ������ ���� ��ġ�� ��´�. 
		   ���� �ݺ������� ������ ������ŭ �̵��ϸ鼭 ��� ���� �׸���.
		   ����� �� �浹ü�� ���� �ƴ϶� '�ٰ���'�� ���̴�.
	*/
#ifdef _DEBUG

	// �ʷϻ� �� ������ ���´�.
	HPEN	Pen = CGameManager::GetInst()->GetPen(EBrushType::Green);

	// �浹���̶�� ������ �� ������ ���´�.
	if (!m_collisionList.empty() || m_mouseCollision) // ���콺 �浹�� ��쿡�� ���������� �ٲ��ش�.
		Pen = CGameManager::GetInst()->GetPen(EBrushType::Red);

	// ������ ����ִ� �⺻ ������ �޾Ƴ���, �ʷ�(����)������ �ٲ۴�.
	HPEN	PrevPen = (HPEN)SelectObject(_hDC, Pen);

	// ī�޶� ���� �浹ü�� ������� �� ��ġ�� ���Ѵ�.
	CCamera* Camera = m_scene->GetCamera();

	Vector2	Pos = m_info.Center - Camera->GetPos();

	// �� �浹ü�� �׷��� ù ��ǥ�� ��´�. 0���̹Ƿ� y��ǥ�� ���� �״�� ����Ѵ�.
	MoveToEx(_hDC, (long)(Pos.x + m_info.Radius), (long)Pos.y, nullptr);

	// �ݺ��� ���� 12���� ������Ű�鼭 ���� �׸���.
	for (int i = 12; i <= 360; i += 12)
	{
		Vector2	Target;
		Target.x = Pos.x + cosf(DegreeToRadian((float)i)) * m_info.Radius;
		Target.y = Pos.y + sinf(DegreeToRadian((float)i)) * m_info.Radius;

		LineTo(_hDC, (long)Target.x, (long)Target.y);
	}

	// ����� �������� ���� ������ �����־�� �Ѵ�.
	SelectObject(_hDC, PrevPen);

#endif // _DEBUG
}

bool CColliderCircle::Collision(CCollider* _dest)
{
	switch (_dest->GetColliderType())
	{
		// Circle to Box 
	case EColliderType::Box:
		return CCollisionManager::GetInst()->CollisionBoxToCircle(m_hitPoint, (CColliderBox*)_dest, this);
		break;
		// Circle to Circle
	case EColliderType::Circle:
		return CCollisionManager::GetInst()->CollisionCircleToCircle(m_hitPoint, this, (CColliderCircle*)_dest);
	}
	return false;
}

bool CColliderCircle::CollisionMouse(const Vector2& _mouse)
{
	// �浹 �������� '�� �� �� �浹' üũ �Լ��� ȣ��
	return CCollisionManager::GetInst()->
		CollisionPointToCircle(m_hitPoint, _mouse, m_info);
}

CircleInfo CColliderCircle::GetInfo() const
{
	return m_info;
}

void CColliderCircle::SetRadius(float _radius)
{
	m_info.Radius = _radius;
}

CColliderCircle::CColliderCircle()
{
	// ���۷��� Ŭ������ �̸� ���
	SetTypeID<CColliderCircle>();

	// �浹ü Ÿ�� : ��
	m_colliderType = EColliderType::Circle;

	// ������ �ʱ�ȭ
	m_info.Radius = 30.f;
}

CColliderCircle::CColliderCircle(const CColliderCircle& _collider)
	: CCollider(_collider)
	, m_info(_collider.m_info)
{

}

CColliderCircle::~CColliderCircle()
{
}
