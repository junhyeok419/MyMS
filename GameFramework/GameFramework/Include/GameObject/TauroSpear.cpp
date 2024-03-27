#include <ctime>
#include "TauroSpear.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderCircle.h"
#include "Effect.h"
#include "Effect_2.h"
#include "FireBall.h"
#include "../UI/Number.h"
#include "Item.h"
#include "../UI/ImageWidget.h"

bool CTauroSpear::Init()
{
	m_moveSpeed = 120.f;
	m_fireTime = 0.f;
	// �⺻ ���� ���� ����.
	m_dir = -1;


	// ���� ��ġ, ũ��, �Ǻ� ����
	SetPos(900.f, 200.f);
	SetSize(300.f, 300.f);
	SetPivot(0.5f, 1.f);

	SetColorKey(255, 0, 255);

	// �� ������Ʈ�� �ִϸ��̼��� �����Ѵ�.
	CreateAnimation();

	// �ִϸ��̼��� �߰��Ѵ�. 
	AddAnimation("TauroSpearLeftStand", true, 1.f);   // ���� ��������
	AddAnimation("TauroSpearLeftDie", false, 2.f);   // ���� ���
	AddAnimation("TauroSpearLeftHit", false, 1.2f);   // ���� �ǰ�
	AddAnimation("TauroSpearLeftMove", true, 0.8f);   // ���� �ȱ�
	AddAnimation("TauroSpearLeftAttack1", false, 0.8f);   // ���� ����1
	AddAnimation("TauroSpearLeftAttack2", false, 2.f);   // ���� ����2

	AddAnimation("TauroSpearRightStand", true, 1.f);   // ������ ��������
	AddAnimation("TauroSpearRightDie", false, 2.f);   // ������ ���
	AddAnimation("TauroSpearRightHit", false, 1.2f);   // ������ �ǰ�
	AddAnimation("TauroSpearRightMove", true, 0.8f);   // ������ �ȱ�
	AddAnimation("TauroSpearRightAttack1", false, 0.8f);   // ������ ����1
	AddAnimation("TauroSpearRightAttack2", false, 2.f);   // ������ ����2

	// ���� �Լ��� �����Ѵ�.
	SetEndFunction<CTauroSpear>("TauroSpearLeftDie", this, &CTauroSpear::Die);
	SetEndFunction<CTauroSpear>("TauroSpearLeftHit", this, &CTauroSpear::HitEnd);
	SetEndFunction<CTauroSpear>("TauroSpearLeftAttack1", this, &CTauroSpear::AttackEnd);
	SetEndFunction<CTauroSpear>("TauroSpearLeftAttack2", this, &CTauroSpear::AttackEnd);

	SetEndFunction<CTauroSpear>("TauroSpearRightDie", this, &CTauroSpear::Die);
	SetEndFunction<CTauroSpear>("TauroSpearRightHit", this, &CTauroSpear::HitEnd);
	SetEndFunction<CTauroSpear>("TauroSpearRightAttack1", this, &CTauroSpear::AttackEnd);
	SetEndFunction<CTauroSpear>("TauroSpearRightAttack2", this, &CTauroSpear::AttackEnd);

	// Attack�� ��Ƽ���̷� �����Ͽ� ����ġ�� �����ӿ� ���� ������ ������ �Ѵ�.
	AddNotify<CTauroSpear>("TauroSpearLeftAttack1", 3, this, &CTauroSpear::Attack);
	AddNotify<CTauroSpear>("TauroSpearLeftAttack2", 4, this, &CTauroSpear::Attack);
	AddNotify<CTauroSpear>("TauroSpearRightAttack1", 3, this, &CTauroSpear::Attack);
	AddNotify<CTauroSpear>("TauroSpearRightAttack2", 4, this, &CTauroSpear::Attack);

	// Ű��Ʈ�� �����ʰ� �������� ������ �����Ѵ�.
	m_vecSequenceKey[1].push_back("TauroSpearLeftStand");		// ����[0]
	m_vecSequenceKey[1].push_back("TauroSpearLeftDie");			// ���[1]	
	m_vecSequenceKey[1].push_back("TauroSpearLeftHit");			// �ǰ�[2]
	m_vecSequenceKey[1].push_back("TauroSpearLeftMove");		// �̵�[3]

	m_vecSequenceKey[0].push_back("TauroSpearRightStand");		// ����[0]
	m_vecSequenceKey[0].push_back("TauroSpearRightDie");		// ���[1]	
	m_vecSequenceKey[0].push_back("TauroSpearRightHit");		// �ǰ�[2]
	m_vecSequenceKey[0].push_back("TauroSpearRightMove");		// �̵�[3]

	// ������ �浹ü�� �ڽ� �浹ü�� �Ѵ�.
	CColliderBox* box = AddCollider<CColliderBox>("TauroSpear");

	box->SetExtent(90.f, 140.f);
	box->SetOffset(-25, -68);
	box->SetCollisionProfile("Monster");

	// �浹(�浹 ����) ���� �� ���� �� ȣ������ �Լ��� ����Ѵ�.
	box->SetCollisionBeginFunction<CTauroSpear>(this, &CTauroSpear::CollisionBegin);
	box->SetCollisionEndFunction<CTauroSpear>(this, &CTauroSpear::CollisionEnd);

	box->SetMouseCollisionBeginFunction<CTauroSpear>(this, &CTauroSpear::CollisionMouseBegin);
	box->SetMouseCollisionEndFunction<CTauroSpear>(this, &CTauroSpear::CollisionMouseEnd);

	m_box = box;

	// �̸�ǥ ����
	m_nameBarFrame = CreateWidgetComponent<CImageWidget>("NameBarTauroSpear");
	m_nameBarFrame->GetWidget<CImageWidget>()->SetTexture("NameBarTauroSpear", TEXT("Maple/UI/Basic/Name/NameBar_TauroSpear.bmp"));
	m_nameBarFrame->GetWidget<CImageWidget>()->SetColorKey(255, 0, 255);
	m_nameBarFrame->GetWidget<CImageWidget>()->SetSize(56.f, 15.f);
	m_nameBarFrame->SetPos(-25.f, 0.f);

	// �İ��̹Ƿ�
	//// ���� �ν� �浹ü�� �ڽ��� �����.
	//box = AddCollider<CColliderBox>("Cognition");

	//box->SetExtent(400.f, 250.f);
	//box->SetOffset(0.f, -100.f);
	//box->SetCollisionProfile("Cognition");

	// Cognition�� �浹 �� ȣ���� �Լ� ���

	/*box->SetCollisionBeginFunction<CTauroSpear>(this, &CTauroSpear::CollisionCognitionBegin);
	box->SetCollisionEndFunction<CTauroSpear>(this, &CTauroSpear::CollisionCognitionEnd);*/

	m_flag = true;

	// �߷� ���� on
	SetPhysicsSimulate(true);

	// ���� �ӵ� ����
	SetJumpVelocity(30.f);

	return true;
}

void CTauroSpear::Update(float _deltaTime)
{
	CCharacter::Update(_deltaTime);

	// �÷��̾ ���� �ӵ��� ����Ǿ�����, �ǰ��� ������ �ٽ� �����ֱ� ����
	if (!m_hit)
	{
		m_moveSpeed = 120.f;
	}

	m_objDir = m_dir;

	// ���� ���¿��� �������� ���ϵ���
	if (m_die)
		return;

	// �⺻ ���� ����
	if (m_basicPattern == EBasicPattern::None && !m_alert && !m_attack)
	{
		m_moveTime = 0.f;

		int random = (rand() % 100) + 1;

		if (random >= 1 && random <= 40)
			m_basicPattern = EBasicPattern::MoveLeft;
		else if (random >= 41 && random <= 80)
			m_basicPattern = EBasicPattern::MoveRight;
		else if (random >= 81 && random <= 100)
			m_basicPattern = EBasicPattern::Stop;
	}

	if (m_basicPattern == EBasicPattern::MoveLeft)
	{
		m_moveTime += _deltaTime;

		MoveLeft();

		if (m_moveTime > 2.f)
			m_basicPattern = EBasicPattern::None;
	}
	else if (m_basicPattern == EBasicPattern::MoveRight)
	{
		m_moveTime += _deltaTime;

		MoveRight();

		if (m_moveTime > 2.f)
			m_basicPattern = EBasicPattern::None;
	}
	else if (m_basicPattern == EBasicPattern::Stop)
	{
		m_moveTime += _deltaTime;

		if (m_moveTime > 3.f)
			m_basicPattern = EBasicPattern::None;
	}


	// ���� ���� ����
	if (m_alert && !m_hit && !m_attack)
	{
		if (m_combatPattern == ECombatPattern::None)
		{
			m_moveTime = 0.f;

			int random = (rand() % 100) + 1;

			if (random >= 1 && random <= 30)
				m_combatPattern = ECombatPattern::MoveToTarget;
			else if (random >= 31 && random <= 55)
				m_combatPattern = ECombatPattern::Skill1;
			else if (random >= 56 && random <= 100)
				m_combatPattern = ECombatPattern::Skill2;
		}

		if (m_combatPattern == ECombatPattern::MoveToTarget)
		{
			m_moveTime += _deltaTime;

			// ���Ͱ� Ÿ���� �����ʿ� �ִٸ�
			if (m_flag)
			{
				// Ÿ�ٺ��� 50�ȼ���ŭ �� �������� ��ȯ�� ����
				if (m_pos.x < (m_target->GetPos().x - 50.f))
					m_flag = false;

				// Ÿ���� ���� �������� �̵�
				MoveLeft();
			}
			// ���Ͱ� Ÿ���� ���ʿ� �ִٸ�
			else if (!m_flag)
			{
				// Ÿ�ٺ��� 50�ȼ���ŭ �� �������� ��ȯ�� ����
				if (m_pos.x > (m_target->GetPos().x + 50.f))
					m_flag = true;

				// Ÿ���� ���� ���������� �̵�
				MoveRight();
			}

			if (m_moveTime > 1.f)
			{
				m_combatPattern = ECombatPattern::None;
			}

		}
		else if (m_combatPattern == ECombatPattern::Skill1)
		{
			Skill1();
		}
		else if (m_combatPattern == ECombatPattern::Skill2)
		{
			Skill2();
		}
	}

	// �ǰ� �� 0.4�ʰ� �˹� ����
	if (m_hit)
	{
		m_hitTime += _deltaTime;

		if (m_hitDir == -1)
		{
			MoveRight();
		}
		else
		{
			MoveLeft();
		}

		if (m_hitTime >= 0.3f)
		{
			m_hitTime = 0.f;
			m_hit = false;
		}
	}
}

void CTauroSpear::PostUpdate(float _deltaTime)
{
	CCharacter::PostUpdate(_deltaTime);

	// ���Ͱ� ������ ������ ���
	if (m_dir == 1)
	{
		// �̵����� ���̳ʽ���� ���� �������� �̵����̶�� ��.
		if (m_move.x < 0.f)
		{
			m_dir = -1;
			m_box->SetOffset(-0.f, -68.f);
		}
	}
	// ���Ͱ� ���� ������ ���
	else
	{
		// �̵����� �÷������ ���� ���������� �̵����̶�� ��.
		if (m_move.x > 0.f)
		{
			m_dir = 1;
			m_box->SetOffset(0.f, -68.f);
		}
	}


	int	AnimDirIndex = 0;

	if (m_dir == -1)
		AnimDirIndex = 1;

	// '���� �ʾҰų�', '�ǰ� ����� ��� ���� ���'���� ��� ��ȯ
	if (!m_die && !m_hit && !m_attack)
	{
		// �̵����� 0�� �ƴ� ��� = �����̰� ���� ��� 
		if (m_move.x != 0.f)
		{
			// �̵� ������� ��ȯ
			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][3]);
		}
		// �������� �ƴϸ� ����������� ��ȯ
		else if (!m_attack)
		{
			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][0]);
		}
	}
}

void CTauroSpear::Render(HDC _hDC, float _deltaTime)
{
	CCharacter::Render(_hDC, _deltaTime);
}

float CTauroSpear::InflictDamage(float _damage, int _dir)
{
	_damage = CCharacter::InflictDamage(_damage);

	/*�÷��̾�� ���ֺ����� �ٲ۴����� �ǰݸ���� ����ؾ� �ݴ�� �ȹз���
	 �ٵ� ������Ʈ���� ���������... �� ���� �ذ��ϱ� ���� ������Ʈ�ϋ��� �̰� ���� x�ϸ� ��*/
	 // �÷��̾� �޾ƿͼ�!!
	if (m_scene->GetPlayer()->GetUseSkill() != ESkill::Judgement)
	{
		if (_dir == m_dir)
			m_dir = (-1) * _dir;
	}

	// �ǰ� ���� ���
	m_scene->GetSceneResource()->SoundPlay("TauroSpearDamage");

	// �߰�Ÿ�� ���� �ǰ� ����� ���ŵ��� �ʵ��� ��. ���Ͱ� �Ӽ���å���� ���ϹǷ� 
	// ���ݸ���� ������ �ʵ��� �����߿� �ǰ� ��� ��� ����
	if (!m_hit && !m_attack)
	{
		// �ǰ� ������� ��ȯ
		if (m_dir == -1)
			ChangeAnimation("TauroSpearLeftHit");
		else
			ChangeAnimation("TauroSpearRightHit");

		m_hitDir = m_dir;

		m_hit = true;
	}

	// ���� ��������ŭ hp���� �����Ѵ�.
	m_ability.HP -= (int)_damage;

	// hp�� 0�� �Ǿ��� ��, ���͸� �����ϱ� ���� �� ���� �ִ�.
	// ���� ���Ŵ� ��� Ʈ���Ÿ� �̿��� ������Ʈ���� �� ����.
	if (m_ability.HP <= 0)
	{
		m_die = true;

		m_scene->GetPlayer()->AddEXP(m_ability.EXPDrop);
		m_scene->GetPlayer()->AddMoney(m_ability.MoneyDrop);

		// ���̻� ���ݹ��� �� ������ �浹 ���������� default�� �ٲ���
		FindCollider("TauroSpear")->SetCollisionProfile("Default");

		// ��� �� �ִϸ��̼����� ��ȯ
		if (m_dir == -1)
			ChangeAnimation("TauroSpearLeftDie");
		else
			ChangeAnimation("TauroSpearRightDie");

		// ��� �� ���带 ���
		m_scene->GetSceneResource()->SoundPlay("TauroSpearDie");

		// 50���� Ȯ���� �� ����
		int random = (rand() % 10) + 1;  // 1~10

		if (random >= 1 && random <= 6) // 50%
		{
			CItem* item = m_scene->CreateObject<CItem>("Item");
			item->SetPos(m_pos.x, m_pos.y);
			item->SetFallStartY(m_pos.y - 40.f);
		}
	}

	// �ǰ� ���ؾ� �ν� �浹ü �о����� ������
	if (!m_alert)
	{
		// ���� �ν� �浹ü�� �ڽ��� �����.
		CColliderBox* box = AddCollider<CColliderBox>("Cognition");

		box->SetExtent(650.f, 250.f);
		box->SetOffset(0.f, -100.f);
		box->SetCollisionProfile("Cognition");

		box->SetCollisionBeginFunction<CTauroSpear>(this, &CTauroSpear::CollisionCognitionBegin);
		box->SetCollisionEndFunction<CTauroSpear>(this, &CTauroSpear::CollisionCognitionEnd);
	}

	// ���� ������ ��ŭ �Ӹ� ���� ������ ����.
	std::vector<std::wstring> vecFileName;
	for (int i = 0; i <= 9; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
		wsprintf(FileName, TEXT("Maple/UI/Damage/NoRed1.%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	++widgetCnt;

	if (widgetCnt > 4)
	{
		// ���������� �ʱ�ȭ
		widgetCnt = 1;
		m_damageWidget.clear();
	}

	if (widgetCnt == 1)
	{
		m_damageWidget.push_back(CreateWidgetComponent<CNumber>("DamageNo"));
		m_damageWidget[0]->GetWidget<CNumber>()->SetTexture("BallogDamageNo", vecFileName);
		m_damageWidget[0]->GetWidget<CNumber>()->SetColorKey(255, 0, 255);
		m_damageWidget[0]->GetWidget<CNumber>()->SetSize(37.f, 39.f);

		m_damageWidget[0]->SetPos(-60.f, -160.f);

		m_damageWidget[0]->GetWidget<CNumber>()->SetNumber(_damage);
	}
	else if (widgetCnt == 2)
	{
		m_damageWidget.push_back(CreateWidgetComponent<CNumber>("DamageNo1"));
		m_damageWidget[1]->GetWidget<CNumber>()->SetTexture("BallogDamageNo", vecFileName);
		m_damageWidget[1]->GetWidget<CNumber>()->SetColorKey(255, 0, 255);
		m_damageWidget[1]->GetWidget<CNumber>()->SetSize(37.f, 39.f);

		m_damageWidget[1]->SetPos(-60.f, -150.f);

		m_damageWidget[1]->GetWidget<CNumber>()->SetNumber(_damage);
	}
	else if (widgetCnt == 3)
	{
		m_damageWidget.push_back(CreateWidgetComponent<CNumber>("DamageNo2"));
		m_damageWidget[2]->GetWidget<CNumber>()->SetTexture("BallogDamageNo", vecFileName);
		m_damageWidget[2]->GetWidget<CNumber>()->SetColorKey(255, 0, 255);
		m_damageWidget[2]->GetWidget<CNumber>()->SetSize(37.f, 39.f);

		m_damageWidget[2]->SetPos(-60.f, -140.f);

		m_damageWidget[2]->GetWidget<CNumber>()->SetNumber(_damage);
	}
	else
	{
		m_damageWidget.push_back(CreateWidgetComponent<CNumber>("DamageNo3"));
		m_damageWidget[3]->GetWidget<CNumber>()->SetTexture("BallogDamageNo", vecFileName);
		m_damageWidget[3]->GetWidget<CNumber>()->SetColorKey(255, 0, 255);
		m_damageWidget[3]->GetWidget<CNumber>()->SetSize(37.f, 39.f);

		m_damageWidget[3]->SetPos(-60.f, -130.f);

		m_damageWidget[3]->GetWidget<CNumber>()->SetNumber(_damage);
	}

	return _damage;
}

void CTauroSpear::CollisionBegin(CCollider* _src, CCollider* _dest)
{
	// ���� �ھҴٸ� ���� �Ѵ�
	if (_dest->GetOwner()->GetTypeName() == "class CWall")
	{
		// �÷��̾�� ������ ������
		if (m_alert)
			_src->GetOwner()->SetFlag(!GetFlag());
		// �������� �ƴ� ���
		else if (m_basicPattern == EBasicPattern::MoveLeft)
			m_basicPattern = EBasicPattern::MoveRight;
		else
			m_basicPattern = EBasicPattern::MoveLeft;
	}

	// �÷��̾� �����浹ü�� �浹�� ���� �������� �ִ°� �ƴϴ�.
	if (_dest->GetName() == "PlayerAttack")
		return;

	_dest->GetOwner()->InflictDamage(m_ability.DamageMax);
}

void CTauroSpear::CollisionEnd(CCollider* _src, CCollider* _dest)
{

}

void CTauroSpear::CollisionMouseBegin(CCollider* _src, const Vector2& _mousePos)
{
}

void CTauroSpear::CollisionMouseEnd(CCollider* _src, const Vector2& _mousePos)
{
}

void CTauroSpear::CollisionCognitionBegin(CCollider* _src, CCollider* _dest)
{
	// �ν� ������ �÷��̾ ���� ��� ����Ǵ� �Լ�

	// �����·�
	m_alert = true;

	// �⺻ ���� ����
	m_basicPattern = EBasicPattern::None;

	m_target = _dest->GetOwner();


	/*
		�ν� ������ ���� �÷��̾� �浹ü�� �̸��� ����
		�̹� ���� ����(�Ӹ�, ���� ��)���� �Ǵ�.
	*/
	auto iter = m_targetNameList.begin();
	auto iterEnd = m_targetNameList.end();

	for (; iter != iterEnd; ++iter)
	{
		// �̹� ���� �������� ����
		if (*iter == _dest->GetName())
			return;
	}

	// ���ο� ������� �ν� ������ �ø���, ����Ʈ�� �߰�
	_src->SetExtent(700.f, 250.f);
	m_targetNameList.push_back(_dest->GetName());


}

void CTauroSpear::CollisionCognitionEnd(CCollider* _src, CCollider* _dest)
{
	/*
		�������� �÷��̾� �浹ü ������ ����Ʈ���� �����Ѵ�.
	*/
	auto iter = m_targetNameList.begin();
	auto iterEnd = m_targetNameList.end();

	for (; iter != iterEnd;)
	{
		if (*iter == _dest->GetName())
		{
			iter = m_targetNameList.erase(iter);
			iterEnd = m_targetNameList.end();
			continue;
		}
		++iter;
	}

	/*
		��� Ÿ�� �浹ü�� �ν��� ����� ���� ������ �ǵ�����.
		�ϳ��� ���� ���� �������;� �Ѵٴ� ���̴�.
	*/
	if (m_targetNameList.size() == 0)
	{
		// �İ����̹Ƿ�
		_src->SetActive(false);
		//_src->SetExtent(400.f, 250.f);
		// ��� ���¸� �����Ѵ�.
		m_alert = false;
	}


}

void CTauroSpear::CollisionBeginAttack(CCollider* _src, CCollider* _dest)
{
	// �Ѹ��� ������(���� ����) ����������
	if (m_attackCheck)
		return;

	// �����̸� �׳� ����
	if (m_scene->GetGrace())
		return;

	m_attackCheck = true;

	

	if (m_combatPattern == ECombatPattern::Skill1)
	{
		m_scene->GetSceneResource()->SoundPlay("TauroSpearSkill1Hit");

		if (m_dir == 1)
		{
			//// �浹�� ���ÿ� ��Ʈ ����Ʈ�� �����Ѵ�. Once�̹Ƿ� 1�� ��� �� ������ ���̴�.
			//CEffect_2* effect = m_scene->CreateObject<CEffect_2>("TauroSpearRightAttack1Hit");

			//// ����Ʈ�� ��ġ�� ��Ʈ ����Ʈ(�浹 ���� �߰�)�� �� ���̴�.
			//// �� �浹ü�� �ݹ� ������� ������ ��Ʈ ����Ʈ�� _dest �浹ü�� ������ �Ѵ�.
			//effect->SetPos(_dest->GetHitPoint() + Vector2(m_dir * 15.f, 20.f));

			//// �ִϸ��̼� �߰� (�ִϸ��̼� �̸�, ��������, �÷���Ÿ��)
			//effect->AddAnimation("TauroSpearRightAttack1Hit", false, 0.4f);
		}
		else
		{
			/*CEffect_2* effect = m_scene->CreateObject<CEffect_2>("TauroSpearLeftAttack1Hit");

			effect->SetPos(_dest->GetHitPoint() + Vector2(m_dir * 15.f, 20.f));

			effect->AddAnimation("TauroSpearLeftAttack1Hit", false, 0.4f);*/
		}

		_dest->GetOwner()->InflictDamage(m_ability.DamageMax);
	}
	else if (m_combatPattern == ECombatPattern::Skill2)
	{
		m_scene->GetSceneResource()->SoundPlay("TauroSpearSkill2Hit");
		_dest->GetOwner()->InflictDamage(m_ability.DamageMax);
	}

}

void CTauroSpear::CollisionEndAttack(CCollider* _src, CCollider* _dest)
{
}

void CTauroSpear::Attack()
{
	// �߷��� �����ϴ� Ÿ�ֿ̹� ȣ��Ǵ� �Լ�

	if (m_combatPattern == ECombatPattern::Skill1)
	{
		// ���� ���
		m_scene->GetSceneResource()->SoundPlay("TauroSpearSkill1");

		// ���� �浹ü�� ������.
		CColliderBox* collider = AddCollider<CColliderBox>("MonsterAttack");
		collider->SetExtent(200.f, 250.f);
		collider->SetOffset(m_dir * 100.f, -80.f);
		collider->SetCollisionProfile("MonsterAttack");

		collider->SetCollisionBeginFunction<CTauroSpear>(this, &CTauroSpear::CollisionBeginAttack);
		collider->SetCollisionEndFunction<CTauroSpear>(this, &CTauroSpear::CollisionEndAttack);

		m_vecAttackCollider.push_back(collider);
	}
	else if (m_combatPattern == ECombatPattern::Skill2)
	{
		// ���� ���
		m_scene->GetSceneResource()->SoundPlay("TauroSpearSkill2");

		// ���� �浹ü�� ������.
		CColliderBox* collider = AddCollider<CColliderBox>("MonsterAttack");
		collider->SetExtent(260.f, 100.f);
		collider->SetOffset(m_dir * 140.f, -50.f);
		collider->SetCollisionProfile("MonsterAttack");

		collider->SetCollisionBeginFunction<CTauroSpear>(this, &CTauroSpear::CollisionBeginAttack);
		collider->SetCollisionEndFunction<CTauroSpear>(this, &CTauroSpear::CollisionEndAttack);

		m_vecAttackCollider.push_back(collider);
	}
}


void CTauroSpear::AttackEnd()
{
	// ���� �浹ü ���� �� ���� �浹��Ͽ��� ����
	size_t size = m_vecAttackCollider.size();

	for (int i = 0; i < size; ++i)
	{
		m_vecAttackCollider[i]->SetActive(false);
		m_vecAttackCollider[i]->ClearCollisionList();
	}
	m_vecAttackCollider.clear();

	// ��������
	m_attack = false;

	// ��� �ʱ�ȭ 
	m_attackCheck = false;

	// ���� ����
	// ���ݽ�ų ��� �ڿ� �̵� �ϵ���.
	// �̰� none���� �ϸ� �̻��� ���� ����... (�����Ÿ�)
	m_combatPattern = ECombatPattern::MoveToTarget;
}

void CTauroSpear::Die()
{
	SetActive(false);
}

void CTauroSpear::HitEnd()
{
	m_hit = false;
}

void CTauroSpear::MoveLeft()
{
	MoveDir(Vector2(-1.f, 0.f));	// �ش� �������� �̵���Ų��. (��)
}

void CTauroSpear::MoveRight()
{
	MoveDir(Vector2(1.f, 0.f));	// �ش� �������� �̵���Ų��. (��)
}

void CTauroSpear::Skill1()
{
	// �̹� �������̶�� ����
	if (m_attack)
		return;

	m_combatPattern = ECombatPattern::Skill1;

	// ���������� �ٲ�
	m_attack = true;

	// �����
	m_alert = true;

	// ������ �����̶��
	if (m_dir == -1)
		ChangeAnimation("TauroSpearLeftAttack1");
	else
		ChangeAnimation("TauroSpearRightAttack1");
}

void CTauroSpear::Skill2()
{
	// �̹� �������̶�� ����
	if (m_attack)
		return;

	m_combatPattern = ECombatPattern::Skill2;

	// ���������� �ٲ�
	m_attack = true;

	// �����
	m_alert = true;

	// ������ �����̶��
	if (m_dir == -1)
		ChangeAnimation("TauroSpearLeftAttack2");
	else
		ChangeAnimation("TauroSpearRightAttack2");
}

CTauroSpear::CTauroSpear()
	: CMonster()
{
	SetTypeID<CTauroSpear>();

	m_renderLayer = ERenderLayer::Monster;

	m_ability.HP = 4000;
	m_ability.HPMax = 4000;
	m_ability.DamageMin = 400;
	m_ability.DamageMax = 600;
	m_ability.EXPDrop = 220;
	m_ability.MoneyDrop = 1000;
}

CTauroSpear::CTauroSpear(const CTauroSpear& obj)
{

}

CTauroSpear::~CTauroSpear()
{

}
