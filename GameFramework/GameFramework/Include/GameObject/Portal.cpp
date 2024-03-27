#include "Portal.h"
#include "../Scene/Scene.h"
#include "../GameObject/Player.h"
#include "../Collision/ColliderBox.h"

bool CPortal::Init()
{
	CreateAnimation();
	AddAnimation("Portal", true, 1.5f);

	CColliderBox* box = AddCollider<CColliderBox>("Portal");
	box->SetExtent(100.f, 150.f);
	box->SetCollisionProfile("Ground");  // 충돌 프로파일 설정 : Ground
	box->SetCollisionBeginFunction<CPortal>(this, &CPortal::CollisionBegin);
	box->SetCollisionEndFunction<CPortal>(this, &CPortal::CollisionEnd);
	box->SetOffset(0, -80.f);

	return true;
}

void CPortal::Update(float _deltaTime)
{
	CGameObject::Update(_deltaTime);
}

void CPortal::PostUpdate(float _deltaTime)
{
	CGameObject::PostUpdate(_deltaTime);
}

void CPortal::Render(HDC _hDC, float _deltaTime)
{
	CGameObject::Render(_hDC, _deltaTime);
}


void CPortal::CollisionBegin(CCollider* _src, CCollider* _dest)
{
	// 플레이어를 상호작용 가능 상태로 만들어서, 방향키 입력을 활성화한다
	_dest->GetOwner()->SetEnableUpKey_Portal(true);

	// 현재 포탈의 이름을 전해준다.
	_dest->GetOwner()->SetPortalEnable(GetName());
	
}

void CPortal::CollisionEnd(CCollider* _src, CCollider* _dest)
{
	_dest->GetOwner()->SetEnableUpKey(false);
}

CPortal::CPortal()
{
	SetTypeID<CPortal>();
	m_renderLayer = ERenderLayer::Default;
}

CPortal::CPortal(const CPortal& obj)
{
}

CPortal::~CPortal()
{
}
