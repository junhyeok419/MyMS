#include <ctime>
#include "Player.h"
#include "HPPotion.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderCircle.h"
#include "Effect.h"
#include "Effect_2.h"
#include "FireBall.h"
#include "../UI/Number.h"
bool CHPPotion::Init()
{
	CGameObject::Init();

	m_moveSpeed = 150.f;	// 기본이동속도 150, 전투시 220까지 증가

	// 몬스터 위치, 크기, 피봇 설정

	SetSize(300.f, 300.f);
	SetPivot(0.5f, 1.f);

	SetColorKey(255, 0, 255);

	// 이 오브젝트의 애니메이션을 생성한다.
	CreateAnimation();

	// 애니메이션을 추가한다. 
	AddAnimation("HPPotion", true, 0.8f);   // 아이템 둥둥이


	// 아이템의 충돌체를 박스 충돌체로 한다.
	CColliderBox* box = AddCollider<CColliderBox>("HPPotion");

	box->SetExtent(25.f, 25.f);
	box->SetOffset(-1.f, 0.f);
	box->SetCollisionProfile("Item");

	// 충돌(충돌 공격) 시작 및 종료 시 호출해줄 함수를 등록한다.
	box->SetCollisionBeginFunction<CHPPotion>(this, &CHPPotion::CollisionBegin);
	box->SetCollisionEndFunction<CHPPotion>(this, &CHPPotion::CollisionEnd);


	// 중력 적용 on
	SetPhysicsSimulate(true);

	// 점프 속도 지정
	SetJumpVelocity(35.f);

	SetJump(true);

	return true;
}

void CHPPotion::Update(float _deltaTime)
{
	CGameObject::Update(_deltaTime);
}

void CHPPotion::PostUpdate(float _deltaTime)
{
	CGameObject::PostUpdate(_deltaTime);
}

void CHPPotion::Render(HDC _hDC, float _deltaTime)
{
	CGameObject::Render(_hDC, _deltaTime);
}

void CHPPotion::CollisionBegin(CCollider* _src, CCollider* _dest)
{

}

void CHPPotion::CollisionEnd(CCollider* _src, CCollider* _dest)
{

}


CHPPotion::CHPPotion()
	: CGameObject()
{
	SetTypeID<CHPPotion>();

	m_renderLayer = ERenderLayer::Player;
}

CHPPotion::CHPPotion(const CHPPotion& obj)
{

}

CHPPotion::~CHPPotion()
{

}
