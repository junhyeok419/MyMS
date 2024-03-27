#include "Collider.h"
#include "CollisionManager.h"

// Logic

bool CCollider::Init()
{
	// 충돌체 생성 시 디폴트로 가지고 있는 충돌 프로파일이다.
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
	// 키(_name)에 해당하는 충돌 프로파일로 세팅한다
	m_profile = CCollisionManager::GetInst()->FindProfile(_name);
}

void CCollider::AddCollisionList(CCollider* _collider)
{
	// '이전에 충돌한 충돌체 목록'에 충돌체 추가
	m_collisionList.push_back(_collider);
}

bool CCollider::CheckCollisionList(CCollider* _collider)
{
	// 해당 충돌체(_collider)가 '이전에 충돌한 충돌체 목록'에 존재하는지 판단 
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
	// 보통 a와 b충돌체가 있을 때, a->func(b)의 형태로 호출한다. (상대방 목록에 있는 자신을 제거하기 위함)
	
	// 해당 충돌체(_collider)를 '이전에 충돌한 충돌체 목록'에서 찾아 삭제
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
		충돌 목록을 제거하기 전에, 
		다른 충돌체의 충돌 목록에서 자신을 제거해야 한다.
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
	// 충돌 시작에 따른 함수를 호출
	if (m_collisionBegin)
		m_collisionBegin(this, _dest);
}

void CCollider::CallCollisionEnd(CCollider* _dest)
{
	// 충돌 종료에 따른 함수를 호출
	if (m_collisionEnd)
		m_collisionEnd(this, _dest);
}

void CCollider::CallMouseCollisionBegin(const Vector2& _mousePos)
{
	// 마우스 충돌 시작에 따른 함수를 호출
	if (m_mouseCollisionBegin)
		m_mouseCollisionBegin(this, _mousePos);
}

void CCollider::CallMouseCollisionEnd(const Vector2& _mousePos)
{
	// 마우스 충돌 종료에 따른 함수를 호출
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
		충돌 목록을 제거하기 전에,
		다른 충돌체의 충돌 목록에서 자신을 제거해야 한다.
	*/
	auto	iter = m_collisionList.begin();
	auto	iterEnd = m_collisionList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->DeleteCollisionList(this);
	}
}