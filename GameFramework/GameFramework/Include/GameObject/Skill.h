#pragma once
#include "GameObject.h"

class CSkill :
	public CGameObject
{
protected:
	float m_damage;
public:
	virtual bool Init();
	virtual void Update(float _deltaTime);
	virtual void PostUpdate(float _deltaTime);
	virtual void Render(HDC _hDC, float _deltaTime);
private:
	virtual void CollisionBegin(CCollider* _src, CCollider* _dest) = 0;
	virtual void CollisionEnd(CCollider* _src, CCollider* _dest) = 0;
public:
	void SetDamage(int _damage);
protected:
	CSkill();
	~CSkill();

	friend class CScene;
};

