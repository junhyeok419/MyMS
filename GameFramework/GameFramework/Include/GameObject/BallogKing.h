#pragma once
#include "Monster.h"

enum class EFireBallState
{
	Shoot,
	Fly,
	None
};

// 선공형
class CBallogKing :
	public CMonster
{
private:
	EFireBallState m_fireBallState; // 파이어볼 상태
public:
	virtual bool Init();
	virtual void Update(float _deltaTime);
	virtual void PostUpdate(float _deltaTime);
	virtual void Render(HDC _hDC, float _deltaTime);
	virtual float InflictDamage(float _damage, int _dir = 1);
public:
	void SetFireBallState(EFireBallState _state);
private:
	// 충돌 함수
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
	// 애니메이션 엔드 함수
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

	friend class CScene;	// 씬 변수에 씬 정보를 넘겨받기 위해
};

