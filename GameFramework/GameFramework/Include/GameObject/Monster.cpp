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

	// ���� ��ġ, ũ��, �Ǻ� ����
	
	SetSize(160.f, 156.f);
	SetPivot(0.5f, 0.5f);
	
	// ������ �ؽ��ĸ� �������ش�.
	// Monster��� �̸��� ���� stand.0.bmp���Ϸ� �����Ѵ�.
	SetTexture("Monster", TEXT("Maple/Monster/Ballog/Left/stand.0.bmp"));

	SetColorKey(255, 0, 255);

	// ������ �浹ü�� �� �浹ü�� �Ѵ�.
	CColliderCircle* circle = AddCollider<CColliderCircle>("Body");

	circle->SetRadius(70.f);
	circle->SetCollisionProfile("Monster");

	// �浹 ���� �� ���� �� ȣ������ �Լ��� ����Ѵ�.
	circle->SetCollisionBeginFunction<CMonster>(this, &CMonster::CollisionBegin);
	circle->SetCollisionEndFunction<CMonster>(this, &CMonster::CollisionEnd);

	circle->SetMouseCollisionBeginFunction<CMonster>(this, &CMonster::CollisionMouseBegin);
	circle->SetMouseCollisionEndFunction<CMonster>(this, &CMonster::CollisionMouseEnd);
	
	return true;
}

void CMonster::Update(float _deltaTime)
{
	CGameObject::Update(_deltaTime);

	 /// MoveDir(m_dir);	 // �ش� �������� �̵���Ų��.

	// ����(�� pos)�� �Ʒ� ��踦 �Ѿ ��
	if (m_pos.y + (1.f - m_pivot.y) * m_size.y >= 720.f)
	{
		// �Ʒ� ��踦 �Ѿ ��ŭ �������ش�.
		m_pos.y = 720.f - (1.f - m_pivot.y) * m_size.y;

		// ������ ���� �ٲ��ش�.
		m_dir *= -1;
	}
	// ����(�� pos)�� �� ��踦 �Ѿ ��
	else if (m_pos.y - (m_pivot.y * m_size.y) <= 0.f)
	{
		// �� ��踦 �Ѿ ��ŭ �������ش�.
		m_pos.y = m_pivot.y * m_size.y;
		
		// ������ �Ʒ��� �ٲ��ش�.
		m_dir *= 1;
	}
	
	// ��Ÿ Ÿ���� ��������, 0.5�ʸ��� 1�߾� �߻��ϰ� �Ѵ�.
	m_fireTime += _deltaTime;

	if (m_fireTime >= 0.5f)
	{
		m_fireTime -= 0.5f;

		++m_fireCount;

		// �Ҹ� ����
		CBullet* bullet = m_scene->CreateObject<CBullet>("Bullet");
		
		// �Ҹ��� �浹ü ����
		CCollider* bulletCol = bullet->FindCollider("Body");

		// �浹 �������� ����
		bulletCol->SetCollisionProfile("MonsterAttack");

		/*
			�Ҹ��� ��ġ :
			m_pos.x - (m_pivot.x * m_size.x) ---> ������ ���� ����
			������ ���ʿ������� �Ҹ��� x��ǥ�� ���Ѵ�. (y��ǥ�� ���Ϳ� �����Ƿ�)
		*/
		float bulletX = m_pos.x - (m_pivot.x * m_size.x) -
			(1.f - bullet->GetPivot().x) * bullet->GetSize().x;

		// x���� ������ ��� �����ְ�, y���� ������ pos�� ����.
		bullet->SetPos(bulletX, m_pos.y);
		// ���Ͱ� �߻��ϴ� �Ҹ��� �������� �����Ѵ�.
		bullet->SetDamage(20.f);

		// 3��°���� �÷��̾� �������� �߻��Ѵ�.
		if (m_fireCount == 3)
		{
			m_fireCount = 0;

			/*
				�÷��̾� �������� �߻��� ������ ���Ѵ�.
				���� �Ѿ��� ��ġ�� �������� �÷��̾��� ��ġ�� ���� �����̴�.
			*/
			float angle = bullet->GetPos().Angle(m_scene->GetPlayer()->GetPos());
			
			// ���� ������ �Ҹ��� �߻�Ǵ� ������ �ٲ��ش�.
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

	// ���� ��������ŭ hp���� �����Ѵ�.
	m_ability.HP -= (int)_damage;

	// hp�� 0�̵Ǹ� ������Ʈ�� �����Ѵ�.
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
	// �� ȣ��Ǵ��� Ȯ�ο�
	//MessageBox(nullptr, TEXT("�׾��!!"), TEXT("^��^"), MB_OK);
}

void CMonster::CollisionEnd(CCollider* _src, CCollider* _dest)
{
	
	// �� ȣ��Ǵ��� Ȯ�ο�
	//MessageBox(nullptr, TEXT("����."), TEXT("^��^"), MB_OK);
}

void CMonster::CollisionMouseBegin(CCollider* _src, const Vector2& _mousePos)
{
	//// �� ȣ��Ǵ��� Ȯ�� �� ���콺 �浹 Ȯ�ο�
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
