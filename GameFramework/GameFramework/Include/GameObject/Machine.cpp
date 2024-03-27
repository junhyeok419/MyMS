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

	m_moveSpeed = 150.f;	// �⺻�̵��ӵ� 150, ������ 220���� ����
	m_fireTime = 0.f;
	// �⺻ ���� ���� ����.
	m_dir = -1;

	// ���� ��ġ, ũ��, �Ǻ� ����

	SetSize(300.f, 300.f);
	SetPivot(0.5f, 1.f);
	SetColorKey(255, 0, 255);

	// �� ������Ʈ�� �ִϸ��̼��� �����Ѵ�.
	CreateAnimation();

	// �ִϸ��̼��� �߰��Ѵ�. 
	AddAnimation("MachineStand", true, 2.f);   // ���� ��������
	AddAnimation("MachineHit", true, 0.3f);   // ���� �ǰ�

	// ���� �Լ��� �����Ѵ�.

	SetEndFunction<CMachine>("MachineHit", this, &CMachine::HitEnd);

	// ������ �浹ü�� �ڽ� �浹ü�� �Ѵ�.
	CColliderBox* box = AddCollider<CColliderBox>("Machine");

	box->SetExtent(200.f, 300.f);
	box->SetOffset(0.f, -150.f);
	box->SetCollisionProfile("Monster");

	// �浹(�浹 ����) ���� �� ���� �� ȣ������ �Լ��� ����Ѵ�.
	box->SetCollisionBeginFunction<CMachine>(this, &CMachine::CollisionBegin);
	box->SetCollisionEndFunction<CMachine>(this, &CMachine::CollisionEnd);

	box->SetMouseCollisionBeginFunction<CMachine>(this, &CMachine::CollisionMouseBegin);
	box->SetMouseCollisionEndFunction<CMachine>(this, &CMachine::CollisionMouseEnd);

	m_box = box;

	// �̸�ǥ ����
	m_nameBarFrame = CreateWidgetComponent<CImageWidget>("NameBarMachine");
	m_nameBarFrame->GetWidget<CImageWidget>()->SetTexture("NameBarMachine", TEXT("Maple/UI/Basic/Name/NameBar_Machine.bmp"));
	m_nameBarFrame->GetWidget<CImageWidget>()->SetColorKey(255, 0, 255);
	m_nameBarFrame->GetWidget<CImageWidget>()->SetSize(81, 17.f);
	m_nameBarFrame->SetPos(-25.f, 0.f);


	// �߷� ���� on
	SetPhysicsSimulate(true);

	// ���� �ӵ� ����
	SetJumpVelocity(0.f);



	return true;
}

void CMachine::Update(float _deltaTime)
{
	CCharacter::Update(_deltaTime);

	// �÷��̾ ���� �ӵ��� ����Ǿ�����, �ǰ��� ������ �ٽ� �����ֱ� ����
	if (!m_hit)
	{
		m_moveSpeed = 150.f;
	}

	m_objDir = m_dir;

	// ���� ���¿��� �������� ���ϵ���
	if (m_die)
		return;



	
}

void CMachine::PostUpdate(float _deltaTime)
{
	CCharacter::PostUpdate(_deltaTime);


	// '���� �ʾҰų�', '�ǰ� ����� ��� ���� ���'���� ��� ��ȯ
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

	/*�÷��̾�� ���ֺ����� �ٲ۴����� �ǰݸ���� ����ؾ� �ݴ�� �ȹз���
	 �ٵ� ������Ʈ���� ���������... �� ���� �ذ��ϱ� ���� ������Ʈ�ϋ��� �̰� ���� x�ϸ� ��*/
	 // �÷��̾� �޾ƿͼ�!!
	/*if (m_scene->GetPlayer()->GetUseSkill() != ESkill::Judgement)
	{
		if (_dir == m_dir)
			m_dir = (-1) * _dir;
	}*/

	// �߰�Ÿ�� ���� �ǰ� ����� ���ŵ��� �ʵ��� ��. ���Ͱ� �Ӽ���å���� ���ϹǷ� 
	// ���ݸ���� ������ �ʵ��� �����߿� �ǰ� ��� ��� ����
	
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
		
		// 3������
		for (int i = 0; i < 3; ++i)
		{
			int random2 = (rand() % 2) + 1;

			if (random2 == 1)
			{
				// hp ���Ƕ���
				int randomPosX = (rand() % 4) + 1;
				int randomPosY = (rand() % 4) + 1;

				CHPPotion* item = m_scene->CreateObject<CHPPotion>("HPPotion");
				item->SetPos(m_pos.x - 20 + randomPosX * 30, m_pos.y);
				item->SetFallStartY(m_pos.y - 20.f - randomPosY * 30);
			}
			else
			{
				// mp ���Ƕ���
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
			// hp ���Ƕ���
			int randomPosX = (rand() % 4) + 1;
			int randomPosY = (rand() % 4) + 1;

			CHPPotion* item = m_scene->CreateObject<CHPPotion>("HPPotion");
			item->SetPos(m_pos.x - 20 + randomPosX * 30, m_pos.y);
			item->SetFallStartY(m_pos.y - 20.f - randomPosY * 30);
		}
		else
		{
			// mp ���Ƕ���
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

	//// 30���� Ȯ���� �� ����
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
