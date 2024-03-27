#include <ctime>
#include "Player.h"
#include "Machine.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderCircle.h"
#include "Effect.h"
#include "Effect_2.h"
#include "FireBall.h"
#include "../UI/Number.h"
#include "../GameObject/Item.h"
#include "../GameObject/HPPotion.h"
#include "../GameObject/MPPotion.h"
#include "../UI/ImageWidget.h"

bool CMachine::Init()
{
	CGameObject::Init();

	m_moveSpeed = 150.f;	// 기본이동속도 150, 전투시 220까지 증가
	m_fireTime = 0.f;
	// 기본 왼쪽 보고 있음.
	m_dir = -1;

	// 몬스터 위치, 크기, 피봇 설정

	SetSize(300.f, 300.f);
	SetPivot(0.5f, 1.f);
	SetColorKey(255, 0, 255);

	// 이 오브젝트의 애니메이션을 생성한다.
	CreateAnimation();

	// 애니메이션을 추가한다. 
	AddAnimation("MachineStand", true, 2.f);   // 왼쪽 정지상태
	AddAnimation("MachineHit", true, 0.3f);   // 왼쪽 피격

	// 엔드 함수를 세팅한다.

	SetEndFunction<CMachine>("MachineHit", this, &CMachine::HitEnd);

	// 몬스터의 충돌체를 박스 충돌체로 한다.
	CColliderBox* box = AddCollider<CColliderBox>("Machine");

	box->SetExtent(200.f, 300.f);
	box->SetOffset(0.f, -150.f);
	box->SetCollisionProfile("Monster");

	// 충돌(충돌 공격) 시작 및 종료 시 호출해줄 함수를 등록한다.
	box->SetCollisionBeginFunction<CMachine>(this, &CMachine::CollisionBegin);
	box->SetCollisionEndFunction<CMachine>(this, &CMachine::CollisionEnd);

	box->SetMouseCollisionBeginFunction<CMachine>(this, &CMachine::CollisionMouseBegin);
	box->SetMouseCollisionEndFunction<CMachine>(this, &CMachine::CollisionMouseEnd);

	m_box = box;

	// 이름표 설정
	m_nameBarFrame = CreateWidgetComponent<CImageWidget>("NameBarMachine");
	m_nameBarFrame->GetWidget<CImageWidget>()->SetTexture("NameBarMachine", TEXT("Maple/UI/Basic/Name/NameBar_Machine.bmp"));
	m_nameBarFrame->GetWidget<CImageWidget>()->SetColorKey(255, 0, 255);
	m_nameBarFrame->GetWidget<CImageWidget>()->SetSize(81, 17.f);
	m_nameBarFrame->SetPos(-25.f, 0.f);


	// 중력 적용 on
	SetPhysicsSimulate(true);

	// 점프 속도 지정
	SetJumpVelocity(0.f);



	return true;
}

void CMachine::Update(float _deltaTime)
{
	CCharacter::Update(_deltaTime);

	// 플레이어에 의해 속도가 변경되었을때, 피격이 끝나면 다시 돌려주기 위함
	if (!m_hit)
	{
		m_moveSpeed = 150.f;
	}

	m_objDir = m_dir;

	// 죽은 상태에서 움직이지 못하도록
	if (m_die)
		return;



	
}

void CMachine::PostUpdate(float _deltaTime)
{
	CCharacter::PostUpdate(_deltaTime);


	// '죽지 않았거나', '피격 모션이 모두 끝난 경우'에만 모션 전환
	if (!m_die && !m_hit && !m_attack)
	{
	
		ChangeAnimation("MachineStand");
	}
}

void CMachine::Render(HDC _hDC, float _deltaTime)
{

	CCharacter::Render(_hDC, _deltaTime);
}

float CMachine::InflictDamage(float _damage, int _dir)
{
	_damage = CCharacter::InflictDamage(_damage);

	/*플레이어와 마주보도록 바꾼다음에 피격모션을 재생해야 반대로 안밀려남
	 근데 저지먼트에서 문제생기네... 이 문제 해결하기 위해 저지먼트일떄만 이거 적용 x하면 됨*/
	 // 플레이어 받아와서!!
	/*if (m_scene->GetPlayer()->GetUseSkill() != ESkill::Judgement)
	{
		if (_dir == m_dir)
			m_dir = (-1) * _dir;
	}*/

	// 추가타에 의해 피격 모션이 갱신되지 않도록 함. 몬스터가 속수무책으로 당하므로 
	// 공격모션이 끊기지 않도록 공격중엔 피격 모션 재생 안함
	
	ChangeAnimation("MachineHit");
	m_hit = true;
	

	if (PlayerAbility::ItemCnt < 1)
	{
		m_scene->GetSceneResource()->SoundPlay("MachineDeny");
		return 0.f;
	}

	--PlayerAbility::ItemCnt;

	int random = (rand() % 10) + 1;
	if (random == 1)
	{
		m_scene->GetSceneResource()->SoundPlay("MachineFailHit");
		m_scene->GetSceneResource()->SoundPlay("MachineGoodHit");
		
		// 3개떨굼
		for (int i = 0; i < 3; ++i)
		{
			int random2 = (rand() % 2) + 1;

			if (random2 == 1)
			{
				// hp 포션떨굼
				int randomPosX = (rand() % 4) + 1;
				int randomPosY = (rand() % 4) + 1;

				CHPPotion* item = m_scene->CreateObject<CHPPotion>("HPPotion");
				item->SetPos(m_pos.x - 20 + randomPosX * 30, m_pos.y);
				item->SetFallStartY(m_pos.y - 20.f - randomPosY * 30);
			}
			else
			{
				// mp 포션떨굼
				int randomPosX = (rand() % 4) + 1;
				int randomPosY = (rand() % 4) + 1;

				CMPPotion* item = m_scene->CreateObject<CMPPotion>("MPPotion");
				item->SetPos(m_pos.x - 20 + randomPosX * 30, m_pos.y);
				item->SetFallStartY(m_pos.y - 20.f - randomPosY * 30);
			}
		}
	}
	else if (random >= 2 && random <= 5)
	{
		m_scene->GetSceneResource()->SoundPlay("MachineFailHit");
		m_scene->GetSceneResource()->SoundPlay("MachineNormalHit");

		int random2 = (rand() % 2) + 1;

		if (random2 == 1)
		{
			// hp 포션떨굼
			int randomPosX = (rand() % 4) + 1;
			int randomPosY = (rand() % 4) + 1;

			CHPPotion* item = m_scene->CreateObject<CHPPotion>("HPPotion");
			item->SetPos(m_pos.x - 20 + randomPosX * 30, m_pos.y);
			item->SetFallStartY(m_pos.y - 20.f - randomPosY * 30);
		}
		else
		{
			// mp 포션떨굼
			int randomPosX = (rand() % 4) + 1;
			int randomPosY = (rand() % 4) + 1;

			CMPPotion* item = m_scene->CreateObject<CMPPotion>("MPPotion");
			item->SetPos(m_pos.x - 20 + randomPosX * 30, m_pos.y);
			item->SetFallStartY(m_pos.y - 20.f - randomPosY * 30);
		}
	}
	else 
	{
		m_scene->GetSceneResource()->SoundPlay("MachineFailHit");
	}

	//// 30프로 확률로 템 떨굼
	//int random = (rand() % 10) + 1;  // 1~10

	//if (random >= 1 && random <= 3)
	//{
	//	CItem* item = m_scene->CreateObject<CItem>("Item");
	//	item->SetPos(m_pos.x, m_pos.y);
	//	item->SetFallStartY(m_pos.y - 40.f);
	//}

	

	return _damage;
}

void CMachine::CollisionBegin(CCollider* _src, CCollider* _dest)
{
}

void CMachine::CollisionEnd(CCollider* _src, CCollider* _dest)
{

}

void CMachine::CollisionMouseBegin(CCollider* _src, const Vector2& _mousePos)
{
}

void CMachine::CollisionMouseEnd(CCollider* _src, const Vector2& _mousePos)
{
}


void CMachine::CollisionBeginAttack(CCollider* _src, CCollider* _dest)
{
}

void CMachine::CollisionEndAttack(CCollider* _src, CCollider* _dest)
{
}

void CMachine::Die()
{
	SetActive(false);
}

void CMachine::HitEnd()
{
	m_hit = false;
}

CMachine::CMachine()
	: CMonster()
{
	SetTypeID<CMachine>();

	m_renderLayer = ERenderLayer::Monster;

}

CMachine::CMachine(const CMachine& obj)
{

}

CMachine::~CMachine()
{

}
