#include <ctime>
#include "Player.h"
#include "WildCargo.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderCircle.h"
#include "Effect.h"
#include "Effect_2.h"
#include "FireBall.h"
#include "../UI/Number.h"
#include "../GameObject/Item.h"
#include "../UI/ImageWidget.h"
bool CWildCargo::Init()
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
	AddAnimation("WildCargoLeftStand", true, 1.f);   // ���� ��������
	AddAnimation("WildCargoLeftDie", false, 2.f);   // ���� ���
	AddAnimation("WildCargoLeftHit", false, 1.2f);   // ���� �ǰ�
	AddAnimation("WildCargoLeftMove", true, 0.8f);   // ���� �ȱ�

	AddAnimation("WildCargoRightStand", true, 1.f);   // ������ ��������
	AddAnimation("WildCargoRightDie", false, 2.f);   // ������ ���
	AddAnimation("WildCargoRightHit", false, 1.2f);   // ������ �ǰ�
	AddAnimation("WildCargoRightMove", true, 0.8f);   // ������ �ȱ�

	// ���� �Լ��� �����Ѵ�.
	SetEndFunction<CWildCargo>("WildCargoLeftDie", this, &CWildCargo::Die);
	SetEndFunction<CWildCargo>("WildCargoLeftHit", this, &CWildCargo::HitEnd);

	SetEndFunction<CWildCargo>("WildCargoRightDie", this, &CWildCargo::Die);
	SetEndFunction<CWildCargo>("WildCargoRightHit", this, &CWildCargo::HitEnd);

	// Ű��Ʈ�� �����ʰ� �������� ������ �����Ѵ�.
	m_vecSequenceKey[1].push_back("WildCargoLeftStand");		// ����[0]
	m_vecSequenceKey[1].push_back("WildCargoLeftDie");			// ���[1]	
	m_vecSequenceKey[1].push_back("WildCargoLeftHit");			// �ǰ�[2]
	m_vecSequenceKey[1].push_back("WildCargoLeftMove");			// �̵�[3]

	m_vecSequenceKey[0].push_back("WildCargoRightStand");		// ����[0]
	m_vecSequenceKey[0].push_back("WildCargoRightDie");			// ���[1]	
	m_vecSequenceKey[0].push_back("WildCargoRightHit");			// �ǰ�[2]
	m_vecSequenceKey[0].push_back("WildCargoRightMove");		// �̵�[3]

	// ������ �浹ü�� �ڽ� �浹ü�� �Ѵ�.
	CColliderBox* box = AddCollider<CColliderBox>("WildCargo");

	box->SetExtent(100.f, 100.f);
	box->SetOffset(-15, -68);
	box->SetCollisionProfile("Monster");

	// �浹(�浹 ����) ���� �� ���� �� ȣ������ �Լ��� ����Ѵ�.
	box->SetCollisionBeginFunction<CWildCargo>(this, &CWildCargo::CollisionBegin);
	box->SetCollisionEndFunction<CWildCargo>(this, &CWildCargo::CollisionEnd);

	box->SetMouseCollisionBeginFunction<CWildCargo>(this, &CWildCargo::CollisionMouseBegin);
	box->SetMouseCollisionEndFunction<CWildCargo>(this, &CWildCargo::CollisionMouseEnd);

	m_box = box;


	// ����
	// ���� �ν� �浹ü�� �ڽ��� �����.
	box = AddCollider<CColliderBox>("Cognition");

	box->SetExtent(400.f, 250.f);
	box->SetOffset(0.f, -100.f);
	box->SetCollisionProfile("Cognition");




	// Cognition�� �浹 �� ȣ���� �Լ� ���
	box->SetCollisionBeginFunction<CWildCargo>(this, &CWildCargo::CollisionCognitionBegin);
	box->SetCollisionEndFunction<CWildCargo>(this, &CWildCargo::CollisionCognitionEnd);

	// �̸�ǥ ����
	m_nameBarFrame = CreateWidgetComponent<CImageWidget>("NameBarWildCargo");
	m_nameBarFrame->GetWidget<CImageWidget>()->SetTexture("NameBarWildCargo", TEXT("Maple/UI/Basic/Name/NameBar_WildCargo.bmp"));
	m_nameBarFrame->GetWidget<CImageWidget>()->SetColorKey(255, 0, 255);
	m_nameBarFrame->GetWidget<CImageWidget>()->SetSize(56.f, 15.f);
	m_nameBarFrame->SetPos(-25.f, 0.f);

	m_flag = true;

	// �߷� ���� on
	SetPhysicsSimulate(true);

	// ���� �ӵ� ����
	SetJumpVelocity(30.f);

	

	return true;
}

void CWildCargo::Update(float _deltaTime)
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

		if (m_moveTime > 3.f)
			m_basicPattern = EBasicPattern::None;
	}
	else if (m_basicPattern == EBasicPattern::MoveRight)
	{
		m_moveTime += _deltaTime;

		MoveRight();

		if (m_moveTime > 3.f)
			m_basicPattern = EBasicPattern::None;
	}
	else if (m_basicPattern == EBasicPattern::Stop)
	{
		m_moveTime += _deltaTime;

		if (m_moveTime > 2.f)
			m_basicPattern = EBasicPattern::None;
	}


	// ���� ���� ����
	if (m_alert && !m_hit && !m_attack)
	{
		if (m_combatPattern == ECombatPattern::None)
		{
			m_moveTime = 0.f;

			m_combatPattern = ECombatPattern::MoveToTarget;
		}

		if (m_combatPattern == ECombatPattern::MoveToTarget)
		{
			m_moveTime += _deltaTime;

			// ���Ͱ� Ÿ���� �����ʿ� �ִٸ�
			if (m_flag)
			{
				// Ÿ�ٺ��� 280�ȼ���ŭ �� �������� ��ȯ�� ����
				if (m_pos.x < (m_target->GetPos().x - 280.f))
					m_flag = false;

				// Ÿ���� ���� �������� �̵�
				MoveLeft();
			}
			// ���Ͱ� Ÿ���� ���ʿ� �ִٸ�
			else if (!m_flag)
			{
				// Ÿ�ٺ��� 280�ȼ���ŭ �� �������� ��ȯ�� ����
				if (m_pos.x > (m_target->GetPos().x + 280.f))
					m_flag = true;

				// Ÿ���� ���� ���������� �̵�
				MoveRight();
			}

			if (m_moveTime > 1.f)
			{
				m_combatPattern = ECombatPattern::None;
			}

		}


	}

	// �ǰ� �� 0.4�ʰ� �˹� 
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

		if (m_hitTime >= 0.4f)	
		{
			m_hitTime = 0.f;
			m_hit = false;
		}
	}
}

void CWildCargo::PostUpdate(float _deltaTime)
{
	CCharacter::PostUpdate(_deltaTime);

	// ���Ͱ� ������ ������ ���
	if (m_dir == 1)
	{
		// �̵����� ���̳ʽ���� ���� �������� �̵����̶�� ��.
		if (m_move.x < 0.f)
		{
			m_dir = -1;
			m_box->SetOffset(0.f, -45.f);
		}
	}
	// ���Ͱ� ���� ������ ���
	else
	{
		// �̵����� �÷������ ���� ���������� �̵����̶�� ��.
		if (m_move.x > 0.f)
		{
			m_dir = 1;
			m_box->SetOffset(0.f, -45.f);
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

void CWildCargo::Render(HDC _hDC, float _deltaTime)
{
	
	CCharacter::Render(_hDC, _deltaTime);
}

float CWildCargo::InflictDamage(float _damage, int _dir)
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
	m_scene->GetSceneResource()->SoundPlay("WildCargoDamage");

	// �߰�Ÿ�� ���� �ǰ� ����� ���ŵ��� �ʵ��� ��. ���Ͱ� �Ӽ���å���� ���ϹǷ� 
	// ���ݸ���� ������ �ʵ��� �����߿� �ǰ� ��� ��� ����
	if (!m_hit && !m_attack)
	{
		// �ǰ� ������� ��ȯ
		if (m_dir == -1)
			ChangeAnimation("WildCargoLeftHit");
		else
			ChangeAnimation("WildCargoRightHit");

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
		FindCollider("WildCargo")->SetCollisionProfile("Default");

		// ��� �� �ִϸ��̼����� ��ȯ
		if (m_dir == -1)
			ChangeAnimation("WildCargoLeftDie");
		else
			ChangeAnimation("WildCargoRightDie");

		// ��� �� ���带 ���
		m_scene->GetSceneResource()->SoundPlay("WildCargoDie");

		// 30���� Ȯ���� �� ����
		int random = (rand() % 10) + 1;  // 1~10

		if (random >= 1 && random <= 6) // 30%
		{
			CItem* item = m_scene->CreateObject<CItem>("Item");
			item->SetPos(m_pos.x, m_pos.y);
			item->SetFallStartY(m_pos.y - 40.f);
		}
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

void CWildCargo::CollisionBegin(CCollider* _src, CCollider* _dest)
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

	// �÷��̾� �����浹ü�� �浹�� ���� �÷��̾�� �������� �ִ°� �ƴϴ�.
	if (_dest->GetName() == "PlayerAttack")
		return;

	_dest->GetOwner()->InflictDamage(m_ability.DamageMax);
}

void CWildCargo::CollisionEnd(CCollider* _src, CCollider* _dest)
{

}

void CWildCargo::CollisionMouseBegin(CCollider* _src, const Vector2& _mousePos)
{
	int a = 0;
}

void CWildCargo::CollisionMouseEnd(CCollider* _src, const Vector2& _mousePos)
{
}

void CWildCargo::CollisionCognitionBegin(CCollider* _src, CCollider* _dest)
{
	// �ν� ������ �÷��̾ ���� ��� ����Ǵ� �Լ�

	// �ӵ� ���
	m_moveSpeed = 220;

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
		// �̹� ���� ������� ����
		if (*iter == _dest->GetName())
			return;
	}

	// ���ο� ������� �ν� ������ �ø���, ����Ʈ�� �߰�
	_src->SetExtent(1200.f, 250.f);
	m_targetNameList.push_back(_dest->GetName());


}

void CWildCargo::CollisionCognitionEnd(CCollider* _src, CCollider* _dest)
{
	// �ӵ� ����
	m_moveSpeed = 120;


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
		_src->SetExtent(400.f, 250.f);
		// ��� ���¸� �����Ѵ�.
		m_alert = false;
	}


}

void CWildCargo::CollisionBeginAttack(CCollider* _src, CCollider* _dest)
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
		if (m_dir == 1)
		{
			// �浹�� ���ÿ� ��Ʈ ����Ʈ�� �����Ѵ�. Once�̹Ƿ� 1�� ��� �� ������ ���̴�.
			CEffect_2* effect = m_scene->CreateObject<CEffect_2>("WildCargoRightAttackHit");

			// ����Ʈ�� ��ġ�� ��Ʈ ����Ʈ(�浹 ���� �߰�)�� �� ���̴�.
			// �� �浹ü�� �ݹ� ������� ������ ��Ʈ ����Ʈ�� _dest �浹ü�� ������ �Ѵ�.
			effect->SetPos(_dest->GetHitPoint() + Vector2(m_dir * 15.f, 20.f));

			// �ִϸ��̼� �߰� (�ִϸ��̼� �̸�, ��������, �÷���Ÿ��)
			effect->AddAnimation("WildCargoRightAttackHit", false, 0.4f);
		}
		else
		{
			CEffect_2* effect = m_scene->CreateObject<CEffect_2>("WildCargoLeftAttackHit");

			effect->SetPos(_dest->GetHitPoint() + Vector2(m_dir * 15.f, 20.f));

			effect->AddAnimation("WildCargoLeftAttackHit", false, 0.4f);
		}

		_dest->GetOwner()->InflictDamage(m_ability.DamageMax);
	}

}

void CWildCargo::CollisionEndAttack(CCollider* _src, CCollider* _dest)
{
}

void CWildCargo::Die()
{
	SetActive(false);
}

void CWildCargo::HitEnd()
{
	m_hit = false;
}

void CWildCargo::MoveLeft()
{
	MoveDir(Vector2(-1.f, 0.f));	// �ش� �������� �̵���Ų��. (��)
}

void CWildCargo::MoveRight()
{
	MoveDir(Vector2(1.f, 0.f));	// �ش� �������� �̵���Ų��. (��)
}

CWildCargo::CWildCargo()
	: CMonster()
{
	SetTypeID<CWildCargo>();

	m_renderLayer = ERenderLayer::Monster;

	m_ability.HP = 2000;
	m_ability.HPMax = 2000;
	m_ability.DamageMin = 200;
	m_ability.DamageMax = 300;
	m_ability.EXPDrop = 100;
	m_ability.MoneyDrop = 500;
}

CWildCargo::CWildCargo(const CWildCargo& obj)
{

}

CWildCargo::~CWildCargo()
{

}
