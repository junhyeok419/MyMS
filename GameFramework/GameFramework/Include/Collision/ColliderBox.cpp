#include "ColliderBox.h"
#include "../GameObject/GameObject.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "CollisionManager.h"
#include "ColliderCircle.h" // �ڽ� �� �� �浹 ó���� ����
#include "ColliderLine.h"

bool CColliderBox::Init()
{
	if (!CCollider::Init())
		return false;

	return true;
}

void CColliderBox::Update(float _deltaTime)
{
	CCollider::Update(_deltaTime);
}

void CColliderBox::PostUpdate(float _deltaTime)
{
	CCollider::PostUpdate(_deltaTime);

	/*
		�浹ü�� ���� ������Ʈ(owner)�� ��ġ�� offset ��ŭ
		���� ��ġ�� �ڽ� �浹ü�� �߽��̴�. 
		�׷��� ���� �߽ɿ� �ڽ� �������� ���ݸ�ŭ +-���ָ�
		�ڽ��� leftTop, rightBottom �� ���� �� �ִ�.
	*/
	Vector2	pos = m_owner->GetPos();
	Vector2	size(m_width, m_height);

	m_info.Lt = pos + m_offset - size / 2.f;
	m_info.Rb = pos + m_offset + size / 2.f;

	// ���콺 �浹 üũ�� ���� bottom�� ���� (�簢�� �浹ü)
	m_bottom = m_info.Rb.y;
}

void CColliderBox::Render(HDC _hDC, float _deltaTime)
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
	HBRUSH	brush = CGameManager::GetInst()->GetBrush(EBrushType::Green);

	/*
		'�浹 ��� ����Ʈ'�� ������� �ʴٴ� ���� ���� �浹���̶�� ���̴�.
		�浹���� ��쿣 ������ �귯���� ���� �׸� ���̴�.
	*/
	if (!m_collisionList.empty() || m_mouseCollision)  // ���콺 �浹�� ��쿡�� ���������� �ٲ��ش�.
		brush = CGameManager::GetInst()->GetBrush(EBrushType::Red);

	/*
		�浹ü�� ��ġ�� ����������, ī�޶� ��ġ�� ���� 
		������� ���� �浹ü�� ��ġ�� ���Ѵ�.
	*/
	CCamera* camera = m_scene->GetCamera();

	RECT	renderRC;

	renderRC.left = (long)(m_info.Lt.x - camera->GetPos().x);
	renderRC.top = (long)(m_info.Lt.y - camera->GetPos().y);
	renderRC.right = (long)(m_info.Rb.x - camera->GetPos().x);
	renderRC.bottom = (long)(m_info.Rb.y - camera->GetPos().y);

	// 2��° ������ ������ 3��° ������ �귯�� �������� �׸���.
	FrameRect(_hDC, &renderRC, brush);

#endif // _DEBUG
}

bool CColliderBox::Collision(CCollider* _dest)
{
	// ���� �浹ü(_dest)�� ��翡 ���� �ٸ��� �浹 ó���� �Ѵ�.
	switch (_dest->GetColliderType())
	{
		// Box to Box
	case EColliderType::Box:
		return CCollisionManager::GetInst()->
			CollisionBoxToBox(m_hitPoint, this, (CColliderBox*)_dest);
		// Box to Circle
	case EColliderType::Circle:
		return CCollisionManager::GetInst()->CollisionBoxToCircle(m_hitPoint, this, (CColliderCircle*)_dest);
	case EColliderType::Line:
		return CCollisionManager::GetInst()->CollisionBoxToLine(m_hitPoint, this, (CColliderLine*)_dest);
	}

	return false;
}

bool CColliderBox::CollisionMouse(const Vector2& _mouse)
{
	// �浹 �������� '�� �� �簢�� �浹' üũ �Լ��� ȣ��
	return CCollisionManager::GetInst()->
		CollisionPointToBox(m_hitPoint, _mouse, m_info);
}

BoxInfo CColliderBox::GetInfo() const
{
	return m_info;
}

void CColliderBox::SetInfo(const Vector2& _lt, const Vector2& _rb)
{
	m_info.Lt = _lt;
	m_info.Rb = _rb;
}

const BoxInfo& CColliderBox::GetBoxInfo() const
{
	return m_info;
}

void CColliderBox::SetExtent(float _width, float _height)
{
	m_width = _width;
	m_height = _height;
}

void CColliderBox::SetExtent(const Vector2& _size)
{
	m_width = _size.x;
	m_height = _size.y;
}

const Vector2& CColliderBox::GetExtent() const
{
	return Vector2(m_width, m_height);
}

CColliderBox::CColliderBox()
	: m_width(100.f)
	, m_height(100.f)
{
	// ù �ʱ�ȭ�� ���۷��� Ŭ������ �̸��� ����Ѵ�.
	SetTypeID<CColliderBox>();

	// �浹 Ÿ���� '�ڽ�'�� �����Ѵ�.
	m_colliderType = EColliderType::Box;
}

CColliderBox::CColliderBox(const CColliderBox& _collider)
	: CCollider(_collider)
	 ,m_width(_collider.m_width)
	 ,m_height(_collider.m_height)
	 ,m_info(_collider.m_info)
{
}

CColliderBox::~CColliderBox()
{
}
