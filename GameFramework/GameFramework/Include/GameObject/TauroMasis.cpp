#include <ctime>
#include "TauroMasis.h"
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

bool CTauroMasis::Init()
{
	m_moveSpeed = 120.f;
	m_fireTime = 0.f;
	// 기본 왼쪽 보고 있음.
	m_dir = -1;


	// 몬스터 위치, 크기, 피봇 설정
	SetPos(900.f, 200.f);
	SetSize(300.f, 300.f);
	SetPivot(0.5f, 1.f);

	SetColorKey(255, 0, 255);

	// 이 오브젝트의 애니메이션을 생성한다.
	CreateAnimation();

	// 애니메이션을 추가한다. 
	AddAnimation("TauroMasisLeftStand", true, 1.f);   // 왼쪽 정지상태
	AddAnimation("TauroMasisLeftDie", false, 2.f);   // 왼쪽 사망
	AddAnimation("TauroMasisLeftHit", false, 1.2f);   // 왼쪽 피격
	AddAnimation("TauroMasisLeftMove", true, 0.8f);   // 왼쪽 걷기
	AddAnimation("TauroMasisLeftAttack", false, 0.6f);   // 왼쪽 공격1

	AddAnimation("TauroMasisRightStand", true, 1.f);   // 오른쪽 정지상태
	AddAnimation("TauroMasisRightDie", false, 2.f);   // 오른쪽 사망
	AddAnimation("TauroMasisRightHit", false, 1.2f);   // 오른쪽 피격
	AddAnimation("TauroMasisRightMove", true, 0.8f);   // 오른쪽 걷기
	AddAnimation("TauroMasisRightAttack", false, 0.6f);   // 오른쪽 공격1

	// 엔드 함수를 세팅한다.
	SetEndFunction<CTauroMasis>("TauroMasisLeftDie", this, &CTauroMasis::Die);
	SetEndFunction<CTauroMasis>("TauroMasisLeftHit", this, &CTauroMasis::HitEnd);
	SetEndFunction<CTauroMasis>("TauroMasisLeftAttack", this, &CTauroMasis::AttackEnd);

	SetEndFunction<CTauroMasis>("TauroMasisRightDie", this, &CTauroMasis::Die);
	SetEndFunction<CTauroMasis>("TauroMasisRightHit", this, &CTauroMasis::HitEnd);
	SetEndFunction<CTauroMasis>("TauroMasisRightAttack", this, &CTauroMasis::AttackEnd);

	// Attack을 노티파이로 세팅하여 내려치는 프레임에 공격 판정이 들어가도록 한다.
	AddNotify<CTauroMasis>("TauroMasisLeftAttack", 3, this, &CTauroMasis::Attack);
	AddNotify<CTauroMasis>("TauroMasisRightAttack", 3, this, &CTauroMasis::Attack);

	// 키세트를 오른쪽과 왼쪽으로 나누어 세팅한다.
	m_vecSequenceKey[1].push_back("TauroMasisLeftStand");		// 정지[0]
	m_vecSequenceKey[1].push_back("TauroMasisLeftDie");			// 사망[1]	
	m_vecSequenceKey[1].push_back("TauroMasisLeftHit");			// 피격[2]
	m_vecSequenceKey[1].push_back("TauroMasisLeftMove");		// 이동[3]

	m_vecSequenceKey[0].push_back("TauroMasisRightStand");		// 정지[0]
	m_vecSequenceKey[0].push_back("TauroMasisRightDie");		// 사망[1]	
	m_vecSequenceKey[0].push_back("TauroMasisRightHit");		// 피격[2]
	m_vecSequenceKey[0].push_back("TauroMasisRightMove");		// 이동[3]

	// 몬스터의 충돌체를 박스 충돌체로 한다.
	CColliderBox* box = AddCollider<CColliderBox>("TauroMasis");

	box->SetExtent(90.f, 140.f);
	box->SetOffset(-25, -68);
	box->SetCollisionProfile("Monster");

	// 충돌(충돌 공격) 시작 및 종료 시 호출해줄 함수를 등록한다.
	box->SetCollisionBeginFunction<CTauroMasis>(this, &CTauroMasis::CollisionBegin);
	box->SetCollisionEndFunction<CTauroMasis>(this, &CTauroMasis::CollisionEnd);

	box->SetMouseCollisionBeginFunction<CTauroMasis>(this, &CTauroMasis::CollisionMouseBegin);
	box->SetMouseCollisionEndFunction<CTauroMasis>(this, &CTauroMasis::CollisionMouseEnd);

	m_box = box;


	// 이름표 설정
	m_nameBarFrame = CreateWidgetComponent<CImageWidget>("NameBarTauroMasis");
	m_nameBarFrame->GetWidget<CImageWidget>()->SetTexture("NameBarTauroMasis", TEXT("Maple/UI/Basic/Name/NameBar_TauroMasis.bmp"));
	m_nameBarFrame->GetWidget<CImageWidget>()->SetColorKey(255, 0, 255);
	m_nameBarFrame->GetWidget<CImageWidget>()->SetSize(56.f, 15.f);
	m_nameBarFrame->SetPos(-25.f, 0.f);

	// 후공이므로
	//// 몬스터 인식 충돌체를 박스로 만든다.
	//box = AddCollider<CColliderBox>("Cognition");

	//box->SetExtent(400.f, 250.f);
	//box->SetOffset(0.f, -100.f);
	//box->SetCollisionProfile("Cognition");

	// Cognition와 충돌 시 호출할 함수 등록
	
	/*box->SetCollisionBeginFunction<CTauroMasis>(this, &CTauroMasis::CollisionCognitionBegin);
	box->SetCollisionEndFunction<CTauroMasis>(this, &CTauroMasis::CollisionCognitionEnd);*/

	m_flag = true;

	// 중력 적용 on
	SetPhysicsSimulate(true);
	
	// 점프 속도 지정
	SetJumpVelocity(30.f);

	return true;
}

void CTauroMasis::Update(float _deltaTime)
{
	CCharacter::Update(_deltaTime);

	// 플레이어에 의해 속도가 변경되었을때, 피격이 끝나면 다시 돌려주기 위함
	if (!m_hit)
	{
		m_moveSpeed = 120.f;
	}

	m_objDir = m_dir;

	// 죽은 상태에서 움직이지 못하도록
	if (m_die)
		return;

	// 기본 패턴 실행
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


	// 전투 패턴 실행
	if (m_alert && !m_hit && !m_attack)
	{
		if (m_combatPattern == ECombatPattern::None)
		{
			m_moveTime = 0.f;

			int random = (rand() % 100) + 1;

			if (random >= 1 && random <= 30)
				m_combatPattern = ECombatPattern::MoveToTarget;
			else if (random >= 31 && random <= 100)
				m_combatPattern = ECombatPattern::Skill1;
		}

		if (m_combatPattern == ECombatPattern::MoveToTarget)
		{
			m_moveTime += _deltaTime;

			// 몬스터가 타겟의 오른쪽에 있다면
			if (m_flag)
			{
				// 타겟보다 50픽셀만큼 더 간다음에 반환점 돌기
				if (m_pos.x < (m_target->GetPos().x - 50.f))
					m_flag = false;

				// 타겟을 향해 왼쪽으로 이동
				MoveLeft();
			}
			// 몬스터가 타겟의 왼쪽에 있다면
			else if (!m_flag)
			{
				// 타겟보다 50픽셀만큼 더 간다음에 반환점 돌기
				if (m_pos.x > (m_target->GetPos().x + 50.f))
					m_flag = true;

				// 타겟을 향해 오른쪽으로 이동
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


	}

	// 피격 시 0.4초간 넉백 구현
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

void CTauroMasis::PostUpdate(float _deltaTime)
{
	CCharacter::PostUpdate(_deltaTime);

	// 몬스터가 오른쪽 방향일 경우
	if (m_dir == 1)
	{
		// 이동량이 마이너스라는 뜻은 왼쪽으로 이동중이라는 뜻.
		if (m_move.x < 0.f)
		{
			m_dir = -1;
			m_box->SetOffset(-0.f, -68.f);
		}
	}
	// 몬스터가 왼쪽 방향일 경우
	else
	{
		// 이동량이 플러스라는 뜻은 오른쪽으로 이동중이라는 뜻.
		if (m_move.x > 0.f)
		{
			m_dir = 1;
			m_box->SetOffset(0.f, -68.f);
		}
	}


	int	AnimDirIndex = 0;

	if (m_dir == -1)
		AnimDirIndex = 1;

	// '죽지 않았거나', '피격 모션이 모두 끝난 경우'에만 모션 전환
	if (!m_die && !m_hit && !m_attack)
	{
		// 이동량이 0이 아닐 경우 = 움직이고 있을 경우 
		if (m_move.x != 0.f)
		{
			// 이동 모션으로 전환
			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][3]);
		}
		// 공격중이 아니면 정지모션으로 전환
		else if (!m_attack)
		{
			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][0]);
		}
	}
}

void CTauroMasis::Render(HDC _hDC, float _deltaTime)
{
	CCharacter::Render(_hDC, _deltaTime);
}

float CTauroMasis::InflictDamage(float _damage, int _dir)
{
	_damage = CCharacter::InflictDamage(_damage);

	// 플레이어와 마주보도록 바꾼다음에 피격모션을 재생해야 반대로 안밀려남
	if (m_scene->GetPlayer()->GetUseSkill() != ESkill::Judgement)
	{
		if (_dir == m_dir)
			m_dir = (-1) * _dir;
	}

	// 피격 사운드 재생
	m_scene->GetSceneResource()->SoundPlay("TauroMasisDamage");

	// 추가타에 의해 피격 모션이 갱신되지 않도록 함. 몬스터가 속수무책으로 당하므로 
	// 공격모션이 끊기지 않도록 공격중엔 피격 모션 재생 안함
	if (!m_hit && !m_attack)
	{
		// 피격 모션으로 전환
		if (m_dir == -1)
			ChangeAnimation("TauroMasisLeftHit");
		else
			ChangeAnimation("TauroMasisRightHit");

		m_hitDir = m_dir;

		m_hit = true;
	}

	// 받은 데미지만큼 hp에서 차감한다.
	m_ability.HP -= (int)_damage;

	// hp가 0이 되었을 때, 몬스터를 제거하기 전에 할 일이 있다.
	// 몬스터 제거는 사망 트리거를 이용해 업데이트에서 할 것임.
	if (m_ability.HP <= 0)
	{
		m_die = true;

		m_scene->GetPlayer()->AddEXP(m_ability.EXPDrop);
		m_scene->GetPlayer()->AddMoney(m_ability.MoneyDrop);

		// 더이상 공격받을 수 없도록 충돌 프로파일을 default로 바꿔줌
		FindCollider("TauroMasis")->SetCollisionProfile("Default");

		// 사망 시 애니메이션으로 전환
		if (m_dir == -1)
			ChangeAnimation("TauroMasisLeftDie");
		else
			ChangeAnimation("TauroMasisRightDie");

		// 사망 시 사운드를 재생
		m_scene->GetSceneResource()->SoundPlay("TauroMasisDie");

		// 40프로 확률로 템 떨굼
		int random = (rand() % 10) + 1;  // 1~10

		if (random >= 1 && random <= 6) // 40%
		{
			CItem* item = m_scene->CreateObject<CItem>("Item");
			item->SetPos(m_pos.x, m_pos.y);
			item->SetFallStartY(m_pos.y - 40.f);
		}
	}


	// 피격 당해야 인식 충돌체 넓어져서 추적함
	if (!m_alert)
	{
		// 몬스터 인식 충돌체를 박스로 만든다.
		CColliderBox* box = AddCollider<CColliderBox>("Cognition");

		box->SetExtent(650.f, 250.f);
		box->SetOffset(0.f, -100.f);
		box->SetCollisionProfile("Cognition");

		box->SetCollisionBeginFunction<CTauroMasis>(this, &CTauroMasis::CollisionCognitionBegin);
		box->SetCollisionEndFunction<CTauroMasis>(this, &CTauroMasis::CollisionCognitionEnd);
	}

	// 받은 데미지 만큼 머리 위에 위젯을 띄운다.
	std::vector<std::wstring> vecFileName;
	for (int i = 0; i <= 9; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
		wsprintf(FileName, TEXT("Maple/UI/Damage/NoRed1.%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	++widgetCnt;

	if (widgetCnt > 4)
	{
		// 데미지위젯 초기화
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

void CTauroMasis::CollisionBegin(CCollider* _src, CCollider* _dest)
{
	// 벽에 박았다면 돌게 한다
	if (_dest->GetOwner()->GetTypeName() == "class CWall")
	{
		// 플레이어와 전투중 돌게함
		if (m_alert)
			_src->GetOwner()->SetFlag(!GetFlag());
		// 전투중이 아닐 경우
		else if (m_basicPattern == EBasicPattern::MoveLeft)
			m_basicPattern = EBasicPattern::MoveRight;
		else
			m_basicPattern = EBasicPattern::MoveLeft;
	}

	// 플레이어 공격충돌체와 충돌한 것은 데미지를 주는게 아니다.
	if (_dest->GetName() == "PlayerAttack")
		return;

	_dest->GetOwner()->InflictDamage(m_ability.DamageMax);
}

void CTauroMasis::CollisionEnd(CCollider* _src, CCollider* _dest)
{

}

void CTauroMasis::CollisionMouseBegin(CCollider* _src, const Vector2& _mousePos)
{
}

void CTauroMasis::CollisionMouseEnd(CCollider* _src, const Vector2& _mousePos)
{
}

void CTauroMasis::CollisionCognitionBegin(CCollider* _src, CCollider* _dest)
{
	// 인식 영역에 플레이어가 들어올 경우 실행되는 함수

	// 경계상태로
	m_alert = true;

	// 기본 패턴 해제
	m_basicPattern = EBasicPattern::None;

	m_target = _dest->GetOwner();


	/*
		인식 영역에 들어온 플레이어 충돌체의 이름을 통해
		이미 들어온 부위(머리, 몸통 등)인지 판단.
	*/
	auto iter = m_targetNameList.begin();
	auto iterEnd = m_targetNameList.end();

	for (; iter != iterEnd; ++iter)
	{
		// 이미 들어온 부위리먄 리턴
		if (*iter == _dest->GetName())
			return;
	}

	// 새로운 부위라면 인식 영역을 늘리고, 리스트에 추가
	_src->SetExtent(700.f, 250.f);
	m_targetNameList.push_back(_dest->GetName());

	
}

void CTauroMasis::CollisionCognitionEnd(CCollider* _src, CCollider* _dest)
{
	/*
		빠져나간 플레이어 충돌체 부위를 리스트에서 제거한다.
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
		모든 타겟 충돌체가 인식을 벗어나는 순간 범위를 되돌린다.
		하나라도 빠짐 없이 빠져나와야 한다는 뜻이다.
	*/
	if (m_targetNameList.size() == 0)
	{
		// 후공형이므로
		_src->SetActive(false);
		//_src->SetExtent(400.f, 250.f);
		// 경계 상태를 해제한다.
		m_alert = false;
	}


}

void CTauroMasis::CollisionBeginAttack(CCollider* _src, CCollider* _dest)
{
	// 한명이 여러번(여러 부위) 못떄리도록
	if (m_attackCheck)
		return;

	// 무적이면 그냥 리턴
	if (m_scene->GetGrace())
		return;

	m_attackCheck = true;

	if (m_combatPattern == ECombatPattern::Skill1)
	{
		if (m_dir == 1)
		{
			// 충돌과 동시에 히트 이펙트를 생성한다. Once이므로 1번 재생 후 삭제될 것이다.
			CEffect_2* effect = m_scene->CreateObject<CEffect_2>("TauroMasisRightAttackHit");

			// 이펙트의 위치는 히트 포인트(충돌 영역 중간)로 할 것이다.
			// 이 충돌체는 금방 사라지기 때문에 히트 포인트는 _dest 충돌체의 것으로 한다.
			effect->SetPos(_dest->GetHitPoint() + Vector2(m_dir * 15.f, 20.f));

			// 애니메이션 추가 (애니메이션 이름, 루프여부, 플레이타임)
			effect->AddAnimation("TauroMasisRightAttackHit", false, 0.4f);
		}
		else
		{
			CEffect_2* effect = m_scene->CreateObject<CEffect_2>("TauroMasisLeftAttackHit");

			effect->SetPos(_dest->GetHitPoint() + Vector2(m_dir * 15.f, 20.f));

			effect->AddAnimation("TauroMasisLeftAttackHit", false, 0.4f);
		}

		_dest->GetOwner()->InflictDamage(m_ability.DamageMax);
	}

}

void CTauroMasis::CollisionEndAttack(CCollider* _src, CCollider* _dest)
{
}

void CTauroMasis::Attack()
{
	// 발록이 공격하는 타이밍에 호출되는 함수

	if (m_combatPattern == ECombatPattern::Skill1)
	{
		// 사운드 재생
		m_scene->GetSceneResource()->SoundPlay("TauroMasisSkill1");
	
		// 공격 충돌체를 만들어낸다.
		CColliderBox* collider = AddCollider<CColliderBox>("MonsterAttack");
		collider->SetExtent(470.f, 250.f);
		collider->SetOffset(m_dir * 150.f, -80.f);
		collider->SetCollisionProfile("MonsterAttack");

		collider->SetCollisionBeginFunction<CTauroMasis>(this, &CTauroMasis::CollisionBeginAttack);
		collider->SetCollisionEndFunction<CTauroMasis>(this, &CTauroMasis::CollisionEndAttack);

		m_vecAttackCollider.push_back(collider);
	}
}


void CTauroMasis::AttackEnd()
{
	// 공격 충돌체 삭제 및 상대방 충돌목록에서 제거
	size_t size = m_vecAttackCollider.size();

	for (int i = 0; i < size; ++i)
	{
		m_vecAttackCollider[i]->SetActive(false);
		m_vecAttackCollider[i]->ClearCollisionList();
	}
	m_vecAttackCollider.clear();

	// 공격종료
	m_attack = false;

	// 대상 초기화 
	m_attackCheck = false;

	// 패턴 종료
	// 공격스킬 사용 뒤엔 이동 하도록.
	// 이거 none으로 하면 이상한 오류 생김... (버벅거림)
	m_combatPattern = ECombatPattern::MoveToTarget;
}

void CTauroMasis::Die()
{
	SetActive(false);
}

void CTauroMasis::HitEnd()
{
	m_hit = false;
}

void CTauroMasis::MoveLeft()
{
	MoveDir(Vector2(-1.f, 0.f));	// 해당 방향으로 이동시킨다. (좌)
}

void CTauroMasis::MoveRight()
{
	MoveDir(Vector2(1.f, 0.f));	// 해당 방향으로 이동시킨다. (우)
}

void CTauroMasis::Skill1()
{
	// 이미 공격중이라면 리턴
	if (m_attack)
		return;

	m_combatPattern = ECombatPattern::Skill1;

	// 공격중으로 바꿈
	m_attack = true;

	// 경계모드
	m_alert = true;

	// 방향이 왼쪽이라면
	if (m_dir == -1)
		ChangeAnimation("TauroMasisLeftAttack");
	else
		ChangeAnimation("TauroMasisRightAttack");
}

CTauroMasis::CTauroMasis()
	: CMonster()
{
	SetTypeID<CTauroMasis>();

	m_renderLayer = ERenderLayer::Monster;

	m_ability.HP = 3500;
	m_ability.HPMax = 3500;
	m_ability.DamageMin = 300;
	m_ability.DamageMax = 500;
	m_ability.EXPDrop = 150;
	m_ability.MoneyDrop = 800;
}

CTauroMasis::CTauroMasis(const CTauroMasis& obj)
{

}

CTauroMasis::~CTauroMasis()
{

}
