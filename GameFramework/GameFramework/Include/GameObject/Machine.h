#pragma once
#include "Monster.h"
class CMachine :
    public CMonster
{
private:
	class CColliderBox* m_box;
	CSharedPtr<class CWidgetComponent>	m_nameBarFrame;  // 이름 프레임
public:
	virtual bool Init();
	virtual void Update(float _deltaTime);
	virtual void PostUpdate(float _deltaTime);
	virtual void Render(HDC _hDC, float _deltaTime);
	virtual float InflictDamage(float _damage, int _dir = 1);
private:
	// 충돌 함수
	virtual void CollisionBegin(CCollider* _src, CCollider* _dest);
	virtual void CollisionEnd(CCollider* _src, CCollider* _dest);
	virtual void CollisionMouseBegin(CCollider* _src, const Vector2& _mousePos);
	virtual void CollisionMouseEnd(CCollider* _src, const Vector2& _mousePos);
	virtual void CollisionBeginAttack(CCollider* _src, CCollider* _dest);
	virtual void CollisionEndAttack(CCollider* _src, CCollider* _dest);
private:
	// 애니메이션 엔드 함수
	virtual void Die();
	virtual void HitEnd();
protected:
	CMachine();
	CMachine(const CMachine& obj);
	virtual ~CMachine();

	friend class CScene;	// 씬 변수에 씬 정보를 넘겨받기 위해
};

