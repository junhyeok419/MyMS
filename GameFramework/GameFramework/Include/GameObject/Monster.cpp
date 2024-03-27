#include "Monster.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "Bullet.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderCircle.h"
#include "Effect.h"

bool CMonster::Init()
{
	CGameObject::Init();

	m_moveSpeed = 300.f;
	m_fireTime = 0.f;
	m_dir = -1;
	m_fireCount = 0;

	// 몬스터 위치, 크기, 피봇 설정
	
	SetSize(160.f, 156.f);
	SetPivot(0.5f, 0.5f);
	
	// 몬스터의 텍스쳐를 지정해준다.
	// Monster라는 이름을 가진 stand.0.bmp파일로 지정한다.
	SetTexture("Monster", TEXT("Maple/Monster/Ballog/Left/stand.0.bmp"));

	SetColorKey(255, 0, 255);

	// 몬스터의 충돌체를 원 충돌체로 한다.
	CColliderCircle* circle = AddCollider<CColliderCircle>("Body");

	circle->SetRadius(70.f);
	circle->SetCollisionProfile("Monster");

	// 충돌 시작 및 종료 시 호출해줄 함수를 등록한다.
	circle->SetCollisionBeginFunction<CMonster>(this, &CMonster::CollisionBegin);
	circle->SetCollisionEndFunction<CMonster>(this, &CMonster::CollisionEnd);

	circle->SetMouseCollisionBeginFunction<CMonster>(this, &CMonster::CollisionMouseBegin);
	circle->SetMouseCollisionEndFunction<CMonster>(this, &CMonster::CollisionMouseEnd);
	
	return true;
}

void CMonster::Update(float _deltaTime)
{
	CGameObject::Update(_deltaTime);

	 /// MoveDir(m_dir);	 // 해당 방향으로 이동시킨다.

	// 몬스터(의 pos)가 아래 경계를 넘어갈 때
	if (m_pos.y + (1.f - m_pivot.y) * m_size.y >= 720.f)
	{
		// 아래 경계를 넘어간 만큼 보정해준다.
		m_pos.y = 720.f - (1.f - m_pivot.y) * m_size.y;

		// 방향을 위로 바꿔준다.
		m_dir *= -1;
	}
	// 몬스터(의 pos)가 위 경계를 넘어갈 때
	else if (m_pos.y - (m_pivot.y * m_size.y) <= 0.f)
	{
		// 위 경계를 넘어간 만큼 보정해준다.
		m_pos.y = m_pivot.y * m_size.y;
		
		// 방향을 아래로 바꿔준다.
		m_dir *= 1;
	}
	
	// 델타 타임을 누적시켜, 0.5초마다 1발씩 발사하게 한다.
	m_fireTime += _deltaTime;

	if (m_fireTime >= 0.5f)
	{
		m_fireTime -= 0.5f;

		++m_fireCount;

		// 불릿 생성
		CBullet* bullet = m_scene->CreateObject<CBullet>("Bullet");
		
		// 불릿의 충돌체 얻어옴
		CCollider* bulletCol = bullet->FindCollider("Body");

		// 충돌 프로파일 설정
		bulletCol->SetCollisionProfile("MonsterAttack");

		/*
			불릿의 위치 :
			m_pos.x - (m_pivot.x * m_size.x) ---> 몬스터의 가장 왼쪽
			몬스터의 왼쪽에서부터 불릿의 x좌표를 구한다. (y좌표는 몬스터와 같으므로)
		*/
		float bulletX = m_pos.x - (m_pivot.x * m_size.x) -
			(1.f - bullet->GetPivot().x) * bullet->GetSize().x;

		// x축은 위에서 계속 구해주고, y축은 몬스터의 pos와 같다.
		bullet->SetPos(bulletX, m_pos.y);
		// 몬스터가 발사하는 불릿의 데미지를 설정한다.
		bullet->SetDamage(20.f);

		// 3발째마다 플레이어 방향으로 발사한다.
		if (m_fireCount == 3)
		{
			m_fireCount = 0;

			/*
				플레이어 방향으로 발사할 각도를 구한다.
				현재 총알의 위치를 기준으로 플레이어의 위치에 대한 각도이다.
			*/
			float angle = bullet->GetPos().Angle(m_scene->GetPlayer()->GetPos());
			
			// 구한 각도로 불릿이 발사되는 각도를 바꿔준다.
			bullet->SetAngle(angle);
		}
	}
}

void CMonster::PostUpdate(float _deltaTime)
{
	CCharacter::PostUpdate(_deltaTime);
}

void CMonster::Render(HDC _hDC, float _deltaTime)
{
	CCharacter::Render(_hDC, _deltaTime);
}

float CMonster::InflictDamage(float _damage, int _dir)
{
	_damage = CCharacter::InflictDamage(_damage);

	// 받은 데미지만큼 hp에서 차감한다.
	m_ability.HP -= (int)_damage;

	// hp가 0이되면 오브젝트를 제거한다.
	if (m_ability.HP <= 0)
	{
		SetActive(false);
	}

	return _damage;
}

bool CMonster::GetFlag() const
{
	return m_flag;
}

void CMonster::SetFlag(bool _flag)
{
	m_flag = _flag;
}

void CMonster::CollisionBegin(CCollider* _src, CCollider* _dest)
{
	m_scene->GetSceneResource()->SoundPlay("BallogDamage");
	// 잘 호출되는지 확인용
	//MessageBox(nullptr, TEXT("죽어라!!"), TEXT("^모^"), MB_OK);
}

void CMonster::CollisionEnd(CCollider* _src, CCollider* _dest)
{
	
	// 잘 호출되는지 확인용
	//MessageBox(nullptr, TEXT("관통."), TEXT("^모^"), MB_OK);
}

void CMonster::CollisionMouseBegin(CCollider* _src, const Vector2& _mousePos)
{
	//// 잘 호출되는지 확인 및 마우스 충돌 확인용
	//CEffect* effect = m_scene->CreateObject<CEffect>("HitEffect");

	//effect->SetPivot(0.5f, 0.5f);
	//effect->SetPos(_mousePos);

	//effect->AddAnimation("LeftHitEffect", false, 0.3f);
}

void CMonster::CollisionMouseEnd(CCollider* _src, const Vector2& _mousePos)
{
}

void CMonster::CollisionCognitionBegin(CCollider* _src, CCollider* _dest)
{
}

void CMonster::CollisionCognitionEnd(CCollider* _src, CCollider* _dest)
{
}

void CMonster::Die()
{
}

void CMonster::HitEnd()
{
}

void CMonster::CollisionBeginAttack(CCollider* _src, CCollider* _dest)
{
}

void CMonster::CollisionEndAttack(CCollider* _src, CCollider* _dest)
{
}

void CMonster::MoveLeft()
{
}

void CMonster::MoveRight()
{
}

CMonster::CMonster()
	: m_attack(false)
	, m_die(false)
	, m_hit(false)
	, m_basicPattern(EBasicPattern::None)
{
}

CMonster::CMonster(const CMonster& obj)
	: CCharacter(obj)
	, m_dir(obj.m_dir)
	, m_fireTime(obj.m_fireTime)
	, m_fireCount(obj.m_fireCount)
{
}

CMonster::~CMonster()
{

}
