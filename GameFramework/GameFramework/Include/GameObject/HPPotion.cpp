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

	m_moveSpeed = 150.f;	// �⺻�̵��ӵ� 150, ������ 220���� ����

	// ���� ��ġ, ũ��, �Ǻ� ����

	SetSize(300.f, 300.f);
	SetPivot(0.5f, 1.f);

	SetColorKey(255, 0, 255);

	// �� ������Ʈ�� �ִϸ��̼��� �����Ѵ�.
	CreateAnimation();

	// �ִϸ��̼��� �߰��Ѵ�. 
	AddAnimation("HPPotion", true, 0.8f);   // ������ �յ���


	// �������� �浹ü�� �ڽ� �浹ü�� �Ѵ�.
	CColliderBox* box = AddCollider<CColliderBox>("HPPotion");

	box->SetExtent(25.f, 25.f);
	box->SetOffset(-1.f, 0.f);
	box->SetCollisionProfile("Item");

	// �浹(�浹 ����) ���� �� ���� �� ȣ������ �Լ��� ����Ѵ�.
	box->SetCollisionBeginFunction<CHPPotion>(this, &CHPPotion::CollisionBegin);
	box->SetCollisionEndFunction<CHPPotion>(this, &CHPPotion::CollisionEnd);


	// �߷� ���� on
	SetPhysicsSimulate(true);

	// ���� �ӵ� ����
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
