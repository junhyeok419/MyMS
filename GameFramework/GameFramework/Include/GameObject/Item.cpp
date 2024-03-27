#include <ctime>
#include "Player.h"
#include "Item.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderCircle.h"
#include "Effect.h"
#include "Effect_2.h"
#include "FireBall.h"
#include "../UI/Number.h"
bool CItem::Init()
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
	AddAnimation("Item", true, 0.8f);   // ������ �յ���


	// �������� �浹ü�� �ڽ� �浹ü�� �Ѵ�.
	CColliderBox* box = AddCollider<CColliderBox>("Item");

	box->SetExtent(25.f, 25.f);
	box->SetOffset(-1.f, 0.f);
	box->SetCollisionProfile("Item");

	// �浹(�浹 ����) ���� �� ���� �� ȣ������ �Լ��� ����Ѵ�.
	box->SetCollisionBeginFunction<CItem>(this, &CItem::CollisionBegin);
	box->SetCollisionEndFunction<CItem>(this, &CItem::CollisionEnd);


	// �߷� ���� on
	SetPhysicsSimulate(true);

	// ���� �ӵ� ����
	SetJumpVelocity(35.f);

	SetJump(true);

	return true;
}

void CItem::Update(float _deltaTime)
{
	CGameObject::Update(_deltaTime);
}

void CItem::PostUpdate(float _deltaTime)
{
	CGameObject::PostUpdate(_deltaTime);
}

void CItem::Render(HDC _hDC, float _deltaTime)
{
	CGameObject::Render(_hDC, _deltaTime);
}

void CItem::CollisionBegin(CCollider* _src, CCollider* _dest)
{

}

void CItem::CollisionEnd(CCollider* _src, CCollider* _dest)
{

}


CItem::CItem()
	: CGameObject()
{
	SetTypeID<CItem>();

	m_renderLayer = ERenderLayer::Player;
}

CItem::CItem(const CItem& obj)
{

}

CItem::~CItem()
{

}
