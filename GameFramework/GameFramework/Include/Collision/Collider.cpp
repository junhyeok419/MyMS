#include "Collider.h"
#include "CollisionManager.h"

// Logic

bool CCollider::Init()
{
	// �浹ü ���� �� ����Ʈ�� ������ �ִ� �浹 ���������̴�.
	m_profile = CCollisionManager::GetInst()->FindProfile("Default");

	return true;
}

void CCollider::Update(float _deltaTime)
{

}

void CCollider::PostUpdate(float _deltaTime)
{
}

void CCollider::Render(HDC hDC, float _deltaTime)
{
}

bool CCollider::Collision(CCollider* _dest)
{
	return false;
}

bool CCollider::CollisionMouse(const Vector2& _mouse)
{
	return false;
}

// Access

void CCollider::SetExtent(float _width, float _height)
{
}

void CCollider::SetExtent(const Vector2& _size)
{
}

void CCollider::SetLength(const float _length)
{
}

void CCollider::SetMouseCollision(bool _collision)
{
	m_mouseCollision = _collision;
}

void CCollider::SetOffset(const Vector2& _offset)
{
	m_offset = _offset;
}

void CCollider::SetOffset(float _x, float _y)
{
	m_offset = Vector2(_x, _y);
}

const Vector2& CCollider::GetOffset() const
{
	return m_offset;
}

bool CCollider::GetMouseCollision() const
{
	return m_mouseCollision;
}

float CCollider::GetBottom() const
{
	return m_bottom;
}

const Vector2& CCollider::GetExtent() const
{
	return Vector2();
}

const LineInfo& CCollider::GetLineInfo() const
{
	return LineInfo();
}

const BoxInfo& CCollider::GetBoxInfo() const
{
	return BoxInfo();
}

const float& CCollider::GetLength() const
{
	return 0.f;
}

const Vector2& CCollider::GetHitPoint() const
{
	return m_hitPoint;
}

CGameObject* CCollider::GetOwner() const
{
	return m_owner;
}

CScene* CCollider::GetScene() const
{
	return m_scene;
}

EColliderType CCollider::GetColliderType() const
{
	return m_colliderType;
}

const CollisionProfile* CCollider::GetProfile() const
{
	return m_profile;
}

// Collision profile & List

void CCollider::SetCollisionProfile(const std::string& _name)
{
	// Ű(_name)�� �ش��ϴ� �浹 �������Ϸ� �����Ѵ�
	m_profile = CCollisionManager::GetInst()->FindProfile(_name);
}

void CCollider::AddCollisionList(CCollider* _collider)
{
	// '������ �浹�� �浹ü ���'�� �浹ü �߰�
	m_collisionList.push_back(_collider);
}

bool CCollider::CheckCollisionList(CCollider* _collider)
{
	// �ش� �浹ü(_collider)�� '������ �浹�� �浹ü ���'�� �����ϴ��� �Ǵ� 
	auto	iter = m_collisionList.begin();
	auto	iterEnd = m_collisionList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (*iter == _collider)
			return true;
	}
	
	return false;
}

void CCollider::DeleteCollisionList(CCollider* _collider)
{
	// ���� a�� b�浹ü�� ���� ��, a->func(b)�� ���·� ȣ���Ѵ�. (���� ��Ͽ� �ִ� �ڽ��� �����ϱ� ����)
	
	// �ش� �浹ü(_collider)�� '������ �浹�� �浹ü ���'���� ã�� ����
	auto	iter = m_collisionList.begin();
	auto	iterEnd = m_collisionList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (*iter == _collider)
		{
			m_collisionList.erase(iter);
			return;
		}
	}
}

void CCollider::ClearCollisionList()
{
	/*
		�浹 ����� �����ϱ� ����, 
		�ٸ� �浹ü�� �浹 ��Ͽ��� �ڽ��� �����ؾ� �Ѵ�.
	*/
	auto	iter = m_collisionList.begin();
	auto	iterEnd = m_collisionList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->DeleteCollisionList(this);
	}

	m_collisionList.clear();
}

// CallBack

void CCollider::CallCollisionBegin(CCollider* _dest)
{
	// �浹 ���ۿ� ���� �Լ��� ȣ��
	if (m_collisionBegin)
		m_collisionBegin(this, _dest);
}

void CCollider::CallCollisionEnd(CCollider* _dest)
{
	// �浹 ���ῡ ���� �Լ��� ȣ��
	if (m_collisionEnd)
		m_collisionEnd(this, _dest);
}

void CCollider::CallMouseCollisionBegin(const Vector2& _mousePos)
{
	// ���콺 �浹 ���ۿ� ���� �Լ��� ȣ��
	if (m_mouseCollisionBegin)
		m_mouseCollisionBegin(this, _mousePos);
}

void CCollider::CallMouseCollisionEnd(const Vector2& _mousePos)
{
	// ���콺 �浹 ���ῡ ���� �Լ��� ȣ��
	if (m_mouseCollisionEnd)
		m_mouseCollisionEnd(this, _mousePos);
}

// Constructor, destructor

CCollider::CCollider()
	: m_scene(nullptr)
	 ,m_owner(nullptr)
	 ,m_profile(nullptr)
	 ,m_mouseCollision(false)
	 ,m_bottom(0.f)
{
}

CCollider::CCollider(const CCollider& _collider)
	: CRef(_collider)
	 ,m_colliderType(_collider.m_colliderType)
     ,m_offset(_collider.m_offset)
     ,m_scene(nullptr)
     ,m_owner(nullptr)
     ,m_profile(_collider.m_profile)
	 ,m_mouseCollision(false)
	 ,m_bottom(0.f)
{
}

CCollider::~CCollider()
{
	/*
		�浹 ����� �����ϱ� ����,
		�ٸ� �浹ü�� �浹 ��Ͽ��� �ڽ��� �����ؾ� �Ѵ�.
	*/
	auto	iter = m_collisionList.begin();
	auto	iterEnd = m_collisionList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->DeleteCollisionList(this);
	}
}