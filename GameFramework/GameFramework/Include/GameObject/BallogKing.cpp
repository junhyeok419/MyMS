//#include <ctime>
//#include "BallogKing.h"
//#include "../Scene/Scene.h"
//#include "../Scene/SceneResource.h"
//#include "../Collision/ColliderBox.h"
//#include "../Collision/ColliderCircle.h"
//#include "Effect.h"
//#include "Effect_2.h"
//#include "FireBall.h"
//#include "../UI/Number.h"
//#include "Item.h"
//
//bool CBallogKing::Init()
//{
//	m_moveSpeed = 80.f;
//	m_fireTime = 0.f;
//	// �⺻ ���� ���� ����.
//	m_dir = -1;
//
//	// ���� ��ġ, ũ��, �Ǻ� ����
//	SetPos(900.f, 200.f);
//	SetSize(300.f, 300.f);
//	SetPivot(0.5f, 1.f);
//
//	SetColorKey(255, 0, 255);
//
//	// �� ������Ʈ�� �ִϸ��̼��� �����Ѵ�.
//	CreateAnimation();
//
//	// �ִϸ��̼��� �߰��Ѵ�. 
//	AddAnimation("BallogKingLeftStand", true, 0.3f);   // ���� ��������
//	AddAnimation("BallogKingLeftDie", false, 1.2f);   // ���� ���
//	AddAnimation("BallogKingLeftHit", false, 1.6f);   // ���� �ǰ�
//	AddAnimation("BallogKingLeftWalk", true, 1.f);   // ���� �ȱ�
//	AddAnimation("BallogKingLeftAttack1", false, 1.8f);   // ���� ����1
//	AddAnimation("BallogKingLeftAttack2", false, 1.f);   // ���� ����2
//	AddAnimation("BallogKingLeftAttack3", false, 1.f);   // ���� ����3
//
//	AddAnimation("BallogKingRightStand", true, 0.3f);   // ������ ��������
//	AddAnimation("BallogKingRightDie", false, 1.2f);   // ������ ���
//	AddAnimation("BallogKingRightHit", false, 1.6f);   // ������ �ǰ�
//	AddAnimation("BallogKingRightWalk", true, 1.f);   // ������ �ȱ�
//	AddAnimation("BallogKingRightAttack1", false, 1.8f);   // ������ ����1
//	AddAnimation("BallogKingRightAttack2", false, 1.f);   // ������ ����3
//	AddAnimation("BallogKingRightAttack3", false, 1.f);   // ������ ����3
//
//	// ���� �Լ��� �����Ѵ�.
//	SetEndFunction<CBallogKing>("BallogKingLeftDie", this, &CBallogKing::Die);
//	SetEndFunction<CBallogKing>("BallogKingLeftHit", this, &CBallogKing::HitEnd);
//	SetEndFunction<CBallogKing>("BallogKingLeftAttack1", this, &CBallogKing::AttackEnd);
//	SetEndFunction<CBallogKing>("BallogKingLeftAttack2", this, &CBallogKing::AttackEnd);
//	SetEndFunction<CBallogKing>("BallogKingLeftAttack3", this, &CBallogKing::AttackEnd);
//
//	SetEndFunction<CBallogKing>("BallogKingRightDie", this, &CBallogKing::Die);
//	SetEndFunction<CBallogKing>("BallogKingRightHit", this, &CBallogKing::HitEnd);
//	SetEndFunction<CBallogKing>("BallogKingRightAttack1", this, &CBallogKing::AttackEnd);
//	SetEndFunction<CBallogKing>("BallogKingRightAttack2", this, &CBallogKing::AttackEnd);
//	SetEndFunction<CBallogKing>("BallogKingRightAttack3", this, &CBallogKing::AttackEnd);
//
//	// Attack�� ��Ƽ���̷� �����Ͽ� ����ġ�� �����ӿ� ���� ������ ������ �Ѵ�.
//	AddNotify<CBallogKing>("BallogKingLeftAttack1", 4, this, &CBallogKing::Attack);
//	AddNotify<CBallogKing>("BallogKingRightAttack1", 4, this, &CBallogKing::Attack);
//	AddNotify<CBallogKing>("BallogKingLeftAttack2", 4, this, &CBallogKing::Attack);
//	AddNotify<CBallogKing>("BallogKingRightAttack2", 4, this, &CBallogKing::Attack);
//	AddNotify<CBallogKing>("BallogKingLeftAttack3", 5, this, &CBallogKing::Attack);
//	AddNotify<CBallogKing>("BallogKingRightAttack3", 5, this, &CBallogKing::Attack);
//
//	// Ű��Ʈ�� �����ʰ� �������� ������ �����Ѵ�.
//	m_vecSequenceKey[1].push_back("BallogKingLeftStand");		// ����[0]
//	m_vecSequenceKey[1].push_back("BallogKingLeftDie");			// ���[1]	
//	m_vecSequenceKey[1].push_back("BallogKingLeftHit");			// �ǰ�[2]
//	m_vecSequenceKey[1].push_back("BallogKingLeftWalk");		// �̵�[3]
//
//	m_vecSequenceKey[0].push_back("BallogKingRightStand");		// ����[0]
//	m_vecSequenceKey[0].push_back("BallogKingRightDie");		// ���[1]	
//	m_vecSequenceKey[0].push_back("BallogKingRightHit");		// �ǰ�[2]
//	m_vecSequenceKey[0].push_back("BallogKingRightWalk");		// �̵�[3]
//
//	// ������ �浹ü�� �ڽ� �浹ü�� �Ѵ�.
//	CColliderBox* box = AddCollider<CColliderBox>("BallogKing");
//
//	box->SetExtent(110.f, 140.f);
//	box->SetOffset(0, -70);
//	box->SetCollisionProfile("Monster");
//
//	// �浹(�浹 ����) ���� �� ���� �� ȣ������ �Լ��� ����Ѵ�.
//	box->SetCollisionBeginFunction<CBallogKing>(this, &CBallogKing::CollisionBegin);
//	box->SetCollisionEndFunction<CBallogKing>(this, &CBallogKing::CollisionEnd);
//
//	box->SetMouseCollisionBeginFunction<CBallogKing>(this, &CBallogKing::CollisionMouseBegin);
//	box->SetMouseCollisionEndFunction<CBallogKing>(this, &CBallogKing::CollisionMouseEnd);
//
//	//// ������ �浹ü�� �� �浹ü�� �Ѵ�.
//	//CColliderCircle* circle = AddCollider<CColliderCircle>("BallogKing");
//
//	//circle->SetRadius(70.f);
//	//circle->SetOffset(0,-60);
//	//circle->SetCollisionProfile("Monster");
//
//	//// �浹(�浹 ����) ���� �� ���� �� ȣ������ �Լ��� ����Ѵ�.
//	//circle->SetCollisionBeginFunction<CBallogKing>(this, &CBallogKing::CollisionBegin);
//	//circle->SetCollisionEndFunction<CBallogKing>(this, &CBallogKing::CollisionEnd);
//
//	//circle->SetMouseCollisionBeginFunction<CBallogKing>(this, &CBallogKing::CollisionMouseBegin);
//	//circle->SetMouseCollisionEndFunction<CBallogKing>(this, &CBallogKing::CollisionMouseEnd);
//
//
//	// ���� �ν� �浹ü�� �ڽ��� �����.
//	box = AddCollider<CColliderBox>("Cognition");
//
//	box->SetExtent(450.f, 250.f);
//	box->SetOffset(0.f, -100.f);
//	box->SetCollisionProfile("Cognition");
//
//	// Cognition�� �浹 �� ȣ���� �Լ� ���
//	box->SetCollisionBeginFunction<CBallogKing>(this, &CBallogKing::CollisionCognitionBegin);
//	box->SetCollisionEndFunction<CBallogKing>(this, &CBallogKing::CollisionCognitionEnd);
//
//	m_flag = true;
//
//	// �߷� ���� on
//	SetPhysicsSimulate(true);
//
//	// ���� �ӵ� ����
//	SetJumpVelocity(30.f);
//
//	return true;
//}
//
//void CBallogKing::Update(float _deltaTime)
//{
//	CCharacter::Update(_deltaTime);
//
//
//
//	// �÷��̾ ���� �ӵ��� ����Ǿ�����, �ǰ��� ������ �ٽ� �����ֱ� ����
//	if (!m_hit)
//	{
//		m_moveSpeed = 80.f;
//	}
//
//	m_objDir = m_dir;
//
//	// ���̾ ����
//	if (m_fireBallState == EFireBallState::Shoot)
//	{
//		// ���̾ ����
//		CFireBall* fireBall = m_scene->CreateObject<CFireBall>("FireBall");
//
//		if (m_dir == -1)
//			fireBall->ChangeAnimation("BallogKingLeftFireBall");
//		else
//			fireBall->ChangeAnimation("BallogKingRightFireBall");
//
//		// ���̾�� �浹ü ����
//		CCollider* ballCol = fireBall->FindCollider("FireBall");
//
//		ballCol->SetCollisionProfile("MonsterAttack");
//		ballCol->SetOffset(m_dir * 16.f, -17.f);
//		ballCol->SetCollisionBeginFunction<CBallogKing>(this, &CBallogKing::CollisionBeginAttack);
//		ballCol->SetCollisionEndFunction<CBallogKing>(this, &CBallogKing::CollisionEndAttack);
//
//		m_vecAttackCollider.push_back(ballCol);
//
//		// x���� ������ ��� �����ְ�, y���� ������ pos�� ����.
//		fireBall->SetPos(m_pos.x, m_pos.y - 65.f);
//		// ���̾�� �������� �����Ѵ�.
//		fireBall->SetDamage(20.f);
//
//		/*
//			�÷��̾� �������� �߻��� ������ ���Ѵ�.
//			���� �Ѿ��� ��ġ�� �������� �÷��̾��� ��ġ�� ���� �����̴�.
//		*/
//		float angle = fireBall->GetPos().Angle(m_scene->GetPlayer()->GetPos());
//
//		// ���� ������ �Ҹ��� �߻�Ǵ� ������ �ٲ��ش�.
//		fireBall->SetAngle(angle);
//
//		// �߻� �� ���ư����ִ� ����
//		m_fireBallState = EFireBallState::Fly;
//	}
//
//	// ���� ���¿��� �������� ���ϵ���
//	if (m_die)
//		return;
//
//	// �⺻ ���� ����
//	if (m_basicPattern == EBasicPattern::None && !m_alert && !m_attack)
//	{
//		m_moveTime = 0.f;
//
//		int random = (rand() % 100) + 1;
//
//		if (random >= 1 && random <= 40)
//			m_basicPattern = EBasicPattern::MoveLeft;
//		else if (random >= 41 && random <= 80)
//			m_basicPattern = EBasicPattern::MoveRight;
//		else if (random >= 81 && random <= 100)
//			m_basicPattern = EBasicPattern::Stop;
//	}
//
//	if (m_basicPattern == EBasicPattern::MoveLeft)
//	{
//		m_moveTime += _deltaTime;
//
//		MoveLeft();
//
//		if (m_moveTime > 2.f)
//			m_basicPattern = EBasicPattern::None;
//	}
//	else if (m_basicPattern == EBasicPattern::MoveRight)
//	{
//		m_moveTime += _deltaTime;
//
//		MoveRight();
//
//		if (m_moveTime > 2.f)
//			m_basicPattern = EBasicPattern::None;
//	}
//	else if (m_basicPattern == EBasicPattern::Stop)
//	{
//		m_moveTime += _deltaTime;
//
//		if (m_moveTime > 3.f)
//			m_basicPattern = EBasicPattern::None;
//	}
//
//
//	// ���� ���� ����
//	if (m_alert && !m_hit && !m_attack)
//	{
//		if (m_combatPattern == ECombatPattern::None)
//		{
//			m_moveTime = 0.f;
//
//			int random = (rand() % 100) + 1;
//
//			if (random >= 1 && random <= 10)
//				m_combatPattern = ECombatPattern::MoveToTarget;
//			else if (random >= 11 && random <= 25)
//				m_combatPattern = ECombatPattern::Skill1;
//			else if (random >= 26 && random <= 65)
//				m_combatPattern = ECombatPattern::Skill2;
//			else if (random >= 66 && random <= 100)
//				m_combatPattern = ECombatPattern::Skill3;
//		}
//
//		if (m_combatPattern == ECombatPattern::MoveToTarget)
//		{
//			m_moveTime += _deltaTime;
//
//			// ���Ͱ� Ÿ���� �����ʿ� �ִٸ�
//			if (m_flag)
//			{
//				// Ÿ�ٺ��� 50�ȼ���ŭ �� �������� ��ȯ�� ����
//				if (m_pos.x < (m_target->GetPos().x - 50.f))
//					m_flag = false;
//
//				// Ÿ���� ���� �������� �̵�
//				MoveLeft();
//			}
//			// ���Ͱ� Ÿ���� ���ʿ� �ִٸ�
//			else if (!m_flag)
//			{
//				// Ÿ�ٺ��� 50�ȼ���ŭ �� �������� ��ȯ�� ����
//				if (m_pos.x > (m_target->GetPos().x + 50.f))
//					m_flag = true;
//
//				// Ÿ���� ���� ���������� �̵�
//				MoveRight();
//			}
//
//			if (m_moveTime > 1.f)
//			{
//				m_combatPattern = ECombatPattern::None;
//			}
//
//		}
//		else if (m_combatPattern == ECombatPattern::Skill1)
//		{
//			Skill1();
//		}
//		else if (m_combatPattern == ECombatPattern::Skill2)
//		{
//			Skill2();
//		}
//		else if (m_combatPattern == ECombatPattern::Skill3)
//		{
//			Skill3();
//		}
//
//	}
//
//	// �ǰ� �� 0.4�ʰ� �˹� ����
//	if (m_hit)
//	{
//		m_hitTime += _deltaTime;
//
//		if (m_hitDir == -1)
//		{
//			MoveRight();
//		}
//		else
//		{
//			MoveLeft();
//		}
//
//		if (m_hitTime >= 0.4f)
//		{
//			m_hitTime = 0.f;
//			m_hit = false;
//		}
//	}
//}
//
//void CBallogKing::PostUpdate(float _deltaTime)
//{
//	CCharacter::PostUpdate(_deltaTime);
//
//	// ���Ͱ� ������ ������ ���
//	if (m_dir == 1)
//	{
//		// �̵����� ���̳ʽ���� ���� �������� �̵����̶�� ��.
//		if (m_move.x < 0.f)
//			m_dir = -1;
//	}
//	// ���Ͱ� ���� ������ ���
//	else
//	{
//		// �̵����� �÷������ ���� ���������� �̵����̶�� ��.
//		if (m_move.x > 0.f)
//			m_dir = 1;
//	}
//
//
//	int	AnimDirIndex = 0;
//
//	if (m_dir == -1)
//		AnimDirIndex = 1;
//
//	// '���� �ʾҰų�', '�ǰ� ����� ��� ���� ���'���� ��� ��ȯ
//	if (!m_die && !m_hit && !m_attack)
//	{
//		// �̵����� 0�� �ƴ� ��� = �����̰� ���� ��� 
//		if (m_move.x != 0.f)
//		{
//			// �̵� ������� ��ȯ
//			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][3]);
//		}
//		// �������� �ƴϸ� ����������� ��ȯ
//		else if (!m_attack)
//			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][0]);
//	}
//}
//
//void CBallogKing::Render(HDC _hDC, float _deltaTime)
//{
//	CCharacter::Render(_hDC, _deltaTime);
//
//}
//
//float CBallogKing::InflictDamage(float _damage, int _dir)
//{
//	_damage = CCharacter::InflictDamage(_damage);
//
//	/*�÷��̾�� ���ֺ����� �ٲ۴����� �ǰݸ���� ����ؾ� �ݴ�� �ȹз���
//	�ٵ� ������Ʈ���� ���������... �� ���� �ذ��ϱ� ���� ������Ʈ�ϋ��� �̰� ���� x�ϸ� ��*/
//	// �÷��̾� �޾ƿͼ�!!
//	if (m_scene->GetPlayer()->GetUseSkill() != ESkill::Judgement)
//	{
//		if (_dir == m_dir)
//			m_dir = (-1) * _dir;
//	}
//
//	// �ǰ� ���� ���
//	m_scene->GetSceneResource()->SoundPlay("BallogKingDamage");
//
//	// �߰�Ÿ�� ���� �ǰ� ����� ���ŵ��� �ʵ��� ��. ���Ͱ� �Ӽ���å���� ���ϹǷ� 
//	// ���ݸ���� ������ �ʵ��� �����߿� �ǰ� ��� ��� ����
//	if (!m_hit && !m_attack)
//	{
//		// �ǰ� ������� ��ȯ
//		if (m_dir == -1)
//			ChangeAnimation("BallogKingLeftHit");
//		else
//			ChangeAnimation("BallogKingRightHit");
//
//		m_hitDir = m_dir;
//
//		m_hit = true;
//	}
//
//
//
//	// ���� ��������ŭ hp���� �����Ѵ�.
//	m_ability.HP -= (int)_damage;
//
//	// hp�� 0�� �Ǿ��� ��, ���͸� �����ϱ� ���� �� ���� �ִ�.
//	// ���� ���Ŵ� ��� Ʈ���Ÿ� �̿��� ������Ʈ���� �� ����.
//	if (m_ability.HP <= 0)
//	{
//		m_die = true;
//
//		// �÷��̾��� ����ġ�� ���� ��½�Ų��.
//		m_scene->GetPlayer()->AddEXP(m_ability.EXPDrop);
//		m_scene->GetPlayer()->AddMoney(m_ability.MoneyDrop);
//
//		// ���̻� ���ݹ��� �� ������ �浹 ���������� default�� �ٲ���
//		FindCollider("BallogKing")->SetCollisionProfile("Default");
//
//		// ��� �� �ִϸ��̼����� ��ȯ
//		if (m_dir == -1)
//			ChangeAnimation("BallogKingLeftDie");
//		else
//			ChangeAnimation("BallogKingRightDie");
//
//		// ��� �� ���带 ���
//		m_scene->GetSceneResource()->SoundPlay("BallogKingDie");
//
//
//		// 80���� Ȯ���� �� ����
//		int random = (rand() % 10) + 1;  // 1~10
//
//		if (random >= 1 && random <= 8)
//		{
//			CItem* item = m_scene->CreateObject<CItem>("Item");
//			item->SetPos(m_pos.x, m_pos.y);
//			item->SetFallStartY(m_pos.y - 40.f);
//		}
//
//	}
//
//
//	// ���� ������ ��ŭ �Ӹ� ���� ������ ����.
//	std::vector<std::wstring> vecFileName;
//	for (int i = 0; i <= 9; ++i)
//	{
//		TCHAR	FileName[MAX_PATH] = {};
//		// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
//		wsprintf(FileName, TEXT("Maple/UI/Damage/NoRed1.%d.bmp"), i);
//		vecFileName.push_back(FileName);
//	}
//
//	++widgetCnt;
//
//	if (widgetCnt > 4)
//	{
//		// ���������� �ʱ�ȭ
//		widgetCnt = 1;
//		m_damageWidget.clear();
//	}
//
//	if (widgetCnt == 1)
//	{
//		m_damageWidget.push_back(CreateWidgetComponent<CNumber>("DamageNo"));
//		m_damageWidget[0]->GetWidget<CNumber>()->SetTexture("BallogKingDamageNo", vecFileName);
//		m_damageWidget[0]->GetWidget<CNumber>()->SetColorKey(255, 0, 255);
//		m_damageWidget[0]->GetWidget<CNumber>()->SetSize(37.f, 39.f);
//
//		m_damageWidget[0]->SetPos(-60.f, -160.f);
//
//		m_damageWidget[0]->GetWidget<CNumber>()->SetNumber(_damage);
//	}
//	else if (widgetCnt == 2)
//	{
//		m_damageWidget.push_back(CreateWidgetComponent<CNumber>("DamageNo1"));
//		m_damageWidget[1]->GetWidget<CNumber>()->SetTexture("BallogKingDamageNo", vecFileName);
//		m_damageWidget[1]->GetWidget<CNumber>()->SetColorKey(255, 0, 255);
//		m_damageWidget[1]->GetWidget<CNumber>()->SetSize(37.f, 39.f);
//
//		m_damageWidget[1]->SetPos(-60.f, -150.f);
//
//		m_damageWidget[1]->GetWidget<CNumber>()->SetNumber(_damage);
//	}
//	else if (widgetCnt == 3)
//	{
//		m_damageWidget.push_back(CreateWidgetComponent<CNumber>("DamageNo2"));
//		m_damageWidget[2]->GetWidget<CNumber>()->SetTexture("BallogKingDamageNo", vecFileName);
//		m_damageWidget[2]->GetWidget<CNumber>()->SetColorKey(255, 0, 255);
//		m_damageWidget[2]->GetWidget<CNumber>()->SetSize(37.f, 39.f);
//
//		m_damageWidget[2]->SetPos(-60.f, -140.f);
//
//		m_damageWidget[2]->GetWidget<CNumber>()->SetNumber(_damage);
//	}
//	else
//	{
//		m_damageWidget.push_back(CreateWidgetComponent<CNumber>("DamageNo3"));
//		m_damageWidget[3]->GetWidget<CNumber>()->SetTexture("BallogKingDamageNo", vecFileName);
//		m_damageWidget[3]->GetWidget<CNumber>()->SetColorKey(255, 0, 255);
//		m_damageWidget[3]->GetWidget<CNumber>()->SetSize(37.f, 39.f);
//
//		m_damageWidget[3]->SetPos(-60.f, -130.f);
//
//		m_damageWidget[3]->GetWidget<CNumber>()->SetNumber(_damage);
//	}
//
//
//	return _damage;
//}
//
//void CBallogKing::SetFireBallState(EFireBallState _state)
//{
//	m_fireBallState = _state;
//}
//
//void CBallogKing::CollisionBegin(CCollider* _src, CCollider* _dest)
//{
//
//
//	// ���� �ھҴٸ� ���� �Ѵ�
//	if (_dest->GetOwner()->GetTypeName() == "class CWall")
//	{
//		// �÷��̾�� ������ ������
//		if (m_alert)
//			_src->GetOwner()->SetFlag(!GetFlag());
//		// �������� �ƴ� ���
//		else if (m_basicPattern == EBasicPattern::MoveLeft)
//			m_basicPattern = EBasicPattern::MoveRight;
//		else
//			m_basicPattern = EBasicPattern::MoveLeft;
//	}
//
//	// �÷��̾� �����浹ü�� �浹�� ���� �������� �ִ°� �ƴϴ�.
//	if (_dest->GetName() == "PlayerAttack")
//		return;
//
//	_dest->GetOwner()->InflictDamage(m_ability.DamageMax);
//}
//
//void CBallogKing::CollisionEnd(CCollider* _src, CCollider* _dest)
//{
//
//}
//
//void CBallogKing::CollisionMouseBegin(CCollider* _src, const Vector2& _mousePos)
//{
//}
//
//void CBallogKing::CollisionMouseEnd(CCollider* _src, const Vector2& _mousePos)
//{
//}
//
//void CBallogKing::CollisionCognitionBegin(CCollider* _src, CCollider* _dest)
//{
//	// �ν� ������ �÷��̾ ���� ��� ����Ǵ� �Լ�
//
//	// �����·�
//	m_alert = true;
//
//	// �⺻ ���� ����
//	m_basicPattern = EBasicPattern::None;
//
//	m_target = _dest->GetOwner();
//
//
//	/*
//		�ν� ������ ���� �÷��̾� �浹ü�� �̸��� ����
//		�̹� ���� ����(�Ӹ�, ���� ��)���� �Ǵ�.
//	*/
//	auto iter = m_targetNameList.begin();
//	auto iterEnd = m_targetNameList.end();
//
//	for (; iter != iterEnd; ++iter)
//	{
//		// �̹� ���� �������� ����
//		if (*iter == _dest->GetName())
//			return;
//	}
//
//	// ���ο� ������� �ν� ������ �ø���, ����Ʈ�� �߰�
//	_src->SetExtent(1000.f, 250.f);
//	m_targetNameList.push_back(_dest->GetName());
//}
//
//void CBallogKing::CollisionCognitionEnd(CCollider* _src, CCollider* _dest)
//{
//	/*
//		�������� �÷��̾� �浹ü ������ ����Ʈ���� �����Ѵ�.
//	*/
//	auto iter = m_targetNameList.begin();
//	auto iterEnd = m_targetNameList.end();
//
//	for (; iter != iterEnd;)
//	{
//		if (*iter == _dest->GetName())
//		{
//			iter = m_targetNameList.erase(iter);
//			iterEnd = m_targetNameList.end();
//			continue;
//		}
//		++iter;
//	}
//
//	/*
//		��� Ÿ�� �浹ü�� �ν��� ����� ���� ������ �ǵ�����.
//		�ϳ��� ���� ���� �������;� �Ѵٴ� ���̴�.
//	*/
//	if (m_targetNameList.size() == 0)
//	{
//		_src->SetExtent(400.f, 250.f);
//		// ��� ���¸� �����Ѵ�.
//		m_alert = false;
//	}
//
//
//}
//
//void CBallogKing::CollisionBeginAttack(CCollider* _src, CCollider* _dest)
//{
//	// �Ѹ��� ������(���� ����) ����������
//	if (m_attackCheck)
//		return;
//
//	// �����̸� �׳� ����
//	if (m_scene->GetGrace())
//		return;
//
//	m_attackCheck = true;
//
//	if (m_combatPattern == ECombatPattern::Skill1)
//	{
//		// ��Ʈ ���� ���
//		m_scene->GetSceneResource()->SoundPlay("BallogKingSkill1Hit");
//
//		if (m_dir == 1)
//		{
//			// �浹�� ���ÿ� ��Ʈ ����Ʈ�� �����Ѵ�. Once�̹Ƿ� 1�� ��� �� ������ ���̴�.
//			CEffect_2* effect = m_scene->CreateObject<CEffect_2>("BallogKingRightAttack1Hit");
//
//			// ����Ʈ�� ��ġ�� ��Ʈ ����Ʈ(�浹 ���� �߰�)�� �� ���̴�.
//			// �� �浹ü�� �ݹ� ������� ������ ��Ʈ ����Ʈ�� _dest �浹ü�� ������ �Ѵ�.
//			effect->SetPos(_dest->GetHitPoint() + Vector2(m_dir * 15.f, 20.f));
//
//			// �ִϸ��̼� �߰� (�ִϸ��̼� �̸�, ��������, �÷���Ÿ��)
//			effect->AddAnimation("BallogKingRightAttack1Hit", false, 0.8f);
//		}
//		else
//		{
//			CEffect_2* effect = m_scene->CreateObject<CEffect_2>("BallogKingLeftAttack1Hit");
//
//			effect->SetPos(_dest->GetHitPoint() + Vector2(m_dir * 15.f, 20.f));
//
//			effect->AddAnimation("BallogKingLeftAttack1Hit", false, 0.8f);
//		}
//
//		_dest->GetOwner()->InflictDamage(m_ability.DamageMax);
//	}
//	else if (m_combatPattern == ECombatPattern::Skill3)
//	{
//		// ��Ʈ ���� ���
//		m_scene->GetSceneResource()->SoundPlay("BallogKingSkill3Hit");
//
//		if (m_dir == 1)
//		{
//			// �浹�� ���ÿ� ��Ʈ ����Ʈ�� �����Ѵ�. Once�̹Ƿ� 1�� ��� �� ������ ���̴�.
//			CEffect_2* effect = m_scene->CreateObject<CEffect_2>("BallogKingLeftAttack3Hit");
//
//			// ����Ʈ�� ��ġ�� ��Ʈ ����Ʈ(�浹 ���� �߰�)�� �� ���̴�.
//			// �� �浹ü�� �ݹ� ������� ������ ��Ʈ ����Ʈ�� _dest �浹ü�� ������ �Ѵ�.
//			effect->SetPos(_dest->GetHitPoint() + Vector2(m_dir * 15.f, 5.f));
//
//			// �ִϸ��̼� �߰� (�ִϸ��̼� �̸�, ��������, �÷���Ÿ��)
//			effect->AddAnimation("BallogKingLeftAttack3Hit", false, 0.5f);
//		}
//		else
//		{
//			CEffect_2* effect = m_scene->CreateObject<CEffect_2>("BallogKingRightAttack3Hit");
//
//			effect->SetPos(_dest->GetHitPoint() + Vector2(m_dir * 15.f, 5.f));
//
//			effect->AddAnimation("BallogKingRightAttack3Hit", false, 0.5f);
//		}
//
//		_dest->GetOwner()->InflictDamage(m_ability.DamageMax);
//	}
//	// �̰� �߰��� �ۼ��ϸ� ���̾ ���󰡴� ���߿� ��ų 2�� ���� ����� �͹���..
//	else if (m_fireBallState == EFireBallState::Fly)
//	{
//		// ��Ʈ ���� ���
//		m_scene->GetSceneResource()->SoundPlay("BallogKingSkill2Hit");
//
//		// ���̾�� �浹�ϸ� ������Ų��, �浹ü�� �ƴ϶� ��ü ��ü�� ���־��Ѵ�.
//		_src->GetOwner()->SetActive(false);
//
//		if (m_combatPattern != ECombatPattern::Skill2)
//		{
//			// ���� �浹ü ���� �� ���� �浹��Ͽ��� ����
//			size_t size = m_vecAttackCollider.size();
//
//			for (int i = 0; i < size; ++i)
//			{
//				m_vecAttackCollider[i]->SetActive(false);
//				m_vecAttackCollider[i]->ClearCollisionList();
//			}
//			m_vecAttackCollider.clear();
//		}
//
//		if (m_dir == 1)
//		{
//			// �浹�� ���ÿ� ��Ʈ ����Ʈ�� �����Ѵ�. Once�̹Ƿ� 1�� ��� �� ������ ���̴�.
//			CEffect_2* effect = m_scene->CreateObject<CEffect_2>("BallogKingRightAttack2Hit");
//
//			// ����Ʈ�� ��ġ�� ��Ʈ ����Ʈ(�浹 ���� �߰�)�� �� ���̴�.
//			// �� �浹ü�� �ݹ� ������� ������ ��Ʈ ����Ʈ�� _dest �浹ü�� ������ �Ѵ�.
//			effect->SetPos(_dest->GetHitPoint() + Vector2(0.f, 60.f));
//
//			// �ִϸ��̼� �߰� (�ִϸ��̼� �̸�, ��������, �÷���Ÿ��)
//			effect->AddAnimation("BallogKingRightAttack2Hit", false, 0.4f);
//		}
//		else
//		{
//			CEffect_2* effect = m_scene->CreateObject<CEffect_2>("BallogKingLeftAttack2Hit");
//
//			effect->SetPos(_dest->GetHitPoint() + Vector2(0.f, 60.f));
//
//			effect->AddAnimation("BallogKingLeftAttack2Hit", false, 0.4f);
//		}
//		m_fireBallState = EFireBallState::None;
//		_dest->GetOwner()->InflictDamage(m_ability.DamageMax);
//	}
//
//}
//
//void CBallogKing::CollisionEndAttack(CCollider* _src, CCollider* _dest)
//{
//}
//
//void CBallogKing::Attack()
//{
//	// �߷��� �����ϴ� Ÿ�ֿ̹� ȣ��Ǵ� �Լ�
//
//	if (m_combatPattern == ECombatPattern::Skill1)
//	{
//		// ���� ���
//		m_scene->GetSceneResource()->SoundPlay("BallogKingSkill1Use");
//
//		// ���⿡ ���� �ٸ� ���� ����Ʈ ����
//		if (m_dir == -1)
//		{
//			CEffect* effect = m_scene->CreateObject<CEffect>("BallogKingLeftAttack1Effect");
//			effect->SetPos(m_pos + Vector2(10.f, -100.f));
//			effect->AddAnimation("BallogKingLeftAttack1Effect", false, 0.6f);
//
//			effect->AddNotify<CBallogKing>("BallogKingLeftAttack1Effect", 7, this, &CBallogKing::Attack2);
//		}
//		else
//		{
//			CEffect* effect = m_scene->CreateObject<CEffect>("BallogKingRightAttack1Effect");
//			effect->SetPos(m_pos + Vector2(-10.f, -100.f));
//			effect->AddAnimation("BallogKingRightAttack1Effect", false, 0.6f);
//
//			effect->AddNotify<CBallogKing>("BallogKingRightAttack1Effect", 7, this, &CBallogKing::Attack2);
//		}
//
//
//	}
//	else if (m_combatPattern == ECombatPattern::Skill2)
//	{
//		// ���� ���
//		m_scene->GetSceneResource()->SoundPlay("BallogKingSkill2Use");
//
//		// ���⿡ ���� �ٸ� ���� ����Ʈ ����
//		if (m_dir == -1)
//		{
//			CEffect* effect = m_scene->CreateObject<CEffect>("BallogKingLeftAttack2Effect");
//			effect->SetPos(m_pos + Vector2(-50.f, -90.f));
//			effect->AddAnimation("BallogKingLeftAttack2Effect", false, 0.4f);
//		}
//		else
//		{
//			CEffect* effect = m_scene->CreateObject<CEffect>("BallogKingRightAttack2Effect");
//			effect->SetPos(m_pos + Vector2(50.f, -90.f));
//			effect->AddAnimation("BallogKingRightAttack2Effect", false, 0.4f);
//		}
//
//		// ���̾ �߻� on
//		m_fireBallState = EFireBallState::Shoot;
//
//	}
//	else if (m_combatPattern == ECombatPattern::Skill3)
//	{
//		// ���� ���
//		m_scene->GetSceneResource()->SoundPlay("BallogKingSkill3Use");
//
//		// ���⿡ ���� �ٸ� ���� ����Ʈ ����
//		if (m_dir == -1)
//		{
//			CEffect* effect = m_scene->CreateObject<CEffect>("BallogKingLeftAttack3Effect");
//			effect->SetPos(m_pos + Vector2(30.f, -5.f));
//			effect->AddAnimation("BallogKingLeftAttack3Effect", false, 0.4f);
//		}
//		else
//		{
//			CEffect* effect = m_scene->CreateObject<CEffect>("BallogKingRightAttack3Effect");
//			effect->SetPos(m_pos + Vector2(-30.f, -5.f));
//			effect->AddAnimation("BallogKingRightAttack3Effect", false, 0.4f);
//		}
//
//		// ���� �浹ü�� ������.
//		CColliderBox* collider = AddCollider<CColliderBox>("MonsterAttack");
//		collider->SetExtent(400.f, 250.f);
//		collider->SetOffset(m_dir * 150.f, -80.f);
//		collider->SetCollisionProfile("MonsterAttack");
//
//		collider->SetCollisionBeginFunction<CBallogKing>(this, &CBallogKing::CollisionBeginAttack);
//		collider->SetCollisionEndFunction<CBallogKing>(this, &CBallogKing::CollisionEndAttack);
//
//		m_vecAttackCollider.push_back(collider);
//	}
//
//
//}
//
//void CBallogKing::Attack2()
//{
//	// ���� �浹ü�� ������.
//	CColliderBox* collider = AddCollider<CColliderBox>("MonsterAttack");
//	collider->SetExtent(400.f, 250.f);
//	collider->SetOffset(m_dir * 250.f, -80.f);
//	collider->SetCollisionProfile("MonsterAttack");
//
//	collider->SetCollisionBeginFunction<CBallogKing>(this, &CBallogKing::CollisionBeginAttack);
//	collider->SetCollisionEndFunction<CBallogKing>(this, &CBallogKing::CollisionEndAttack);
//
//	m_vecAttackCollider.push_back(collider);
//}
//
//void CBallogKing::AttackEnd()
//{
//	// ���� �浹ü ���� �� ���� �浹��Ͽ��� ����
//	size_t size = m_vecAttackCollider.size();
//
//	for (int i = 0; i < size; ++i)
//	{
//		// ���̾�� �̶� ó���ϸ� �����
//		if (m_vecAttackCollider[i]->GetName() == "FireBall")
//			continue;
//
//		m_vecAttackCollider[i]->SetActive(false);
//		m_vecAttackCollider[i]->ClearCollisionList();
//	}
//	m_vecAttackCollider.clear();
//
//	// ��������
//	m_attack = false;
//
//	// ��� �ʱ�ȭ 
//	m_attackCheck = false;
//
//	// ���� ����
//	// ���ݽ�ų ��� �ڿ� �̵� �ϵ���.
//	// �̰� none���� �ϸ� �̻��� ���� ����... (�����Ÿ�)
//	m_combatPattern = ECombatPattern::MoveToTarget;
//
//
//}
//
//void CBallogKing::Die()
//{
//	SetActive(false);
//}
//
//void CBallogKing::HitEnd()
//{
//	m_hit = false;
//}
//
//void CBallogKing::MoveLeft()
//{
//	MoveDir(Vector2(-1.f, 0.f));	// �ش� �������� �̵���Ų��. (��)
//}
//
//void CBallogKing::MoveRight()
//{
//	MoveDir(Vector2(1.f, 0.f));	// �ش� �������� �̵���Ų��. (��)
//}
//
//void CBallogKing::Skill1()
//{
//	// �̹� �������̶�� ����
//	if (m_attack)
//		return;
//
//	m_combatPattern = ECombatPattern::Skill1;
//
//	// ���������� �ٲ�
//	m_attack = true;
//
//	// �����
//	m_alert = true;
//
//	// ������ �����̶��
//	if (m_dir == -1)
//		ChangeAnimation("BallogKingLeftAttack1");
//	else
//		ChangeAnimation("BallogKingRightAttack1");
//}
//
//void CBallogKing::Skill2()
//{
//	// �̹� �������̶�� ����
//	if (m_attack)
//		return;
//
//	m_combatPattern = ECombatPattern::Skill2;
//
//	// ���������� �ٲ�
//	m_attack = true;
//
//	// �����
//	m_alert = true;
//
//	// ������ �����̶��
//	if (m_dir == -1)
//		ChangeAnimation("BallogKingLeftAttack2");
//	else
//		ChangeAnimation("BallogKingRightAttack2");
//}
//
//void CBallogKing::Skill3()
//{
//	// �̹� �������̶�� ����
//	if (m_attack)
//		return;
//
//	m_combatPattern = ECombatPattern::Skill3;
//
//	// ���������� �ٲ�
//	m_attack = true;
//
//	// �����
//	m_alert = true;
//
//	// ������ �����̶��
//	if (m_dir == -1)
//		ChangeAnimation("BallogKingLeftAttack3");
//	else
//		ChangeAnimation("BallogKingRightAttack3");
//
//}
//CBallogKing::CBallogKing()
//	: CMonster()
//	, m_fireBallState(EFireBallState::None)
//{
//	SetTypeID<CBallogKing>();
//
//	m_renderLayer = ERenderLayer::Monster;
//
//	m_ability.HP = 8500;
//	m_ability.HPMax = 8500;
//	m_ability.DamageMin = 700; // 700
//	m_ability.DamageMax = 1000; // 1200
//	m_ability.EXPDrop = 600;  // 600
//	m_ability.MoneyDrop = 2500;
//}
//
//CBallogKing::CBallogKing(const CBallogKing& obj)
//{
//
//}
//
//CBallogKing::~CBallogKing()
//{
//
//}
