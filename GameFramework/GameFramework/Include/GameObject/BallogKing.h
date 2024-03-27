#pragma once
#include "Monster.h"

enum class EFireBallState
{
	Shoot,
	Fly,
	None
};

// ������
class CBallogKing :
	public CMonster
{
private:
	EFireBallState m_fireBallState; // ���̾ ����
public:
	virtual bool Init();
	virtual void Update(float _deltaTime);
	virtual void PostUpdate(float _deltaTime);
	virtual void Render(HDC _hDC, float _deltaTime);
	virtual float InflictDamage(float _damage, int _dir = 1);
public:
	void SetFireBallState(EFireBallState _state);
private:
	// �浹 �Լ�
	virtual void CollisionBegin(CCollider* _src, CCollider* _dest);
	virtual void CollisionEnd(CCollider* _src, CCollider* _dest);
	virtual void CollisionMouseBegin(CCollider* _src, const Vector2& _mousePos);
	virtual void CollisionMouseEnd(CCollider* _src, const Vector2& _mousePos);
	virtual void CollisionCognitionBegin(CCollider* _src, CCollider* _dest);
	virtual void CollisionCognitionEnd(CCollider* _src, CCollider* _dest);
	virtual void CollisionBeginAttack(CCollider* _src, CCollider* _dest);
	virtual void CollisionEndAttack(CCollider* _src, CCollider* _dest);
private:
	void Attack();
	void Attack2();
	void AttackEnd();
private:
	// �ִϸ��̼� ���� �Լ�
	virtual void Die();
	virtual void HitEnd();
private:
	virtual void MoveLeft();
	virtual void MoveRight();
	void Skill1();
	void Skill2();
	void Skill3();
protected:
	CBallogKing();
	CBallogKing(const CBallogKing& obj);
	virtual ~CBallogKing();

	friend class CScene;	// �� ������ �� ������ �Ѱܹޱ� ����
};

