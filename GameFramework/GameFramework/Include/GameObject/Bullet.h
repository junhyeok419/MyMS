#pragma once
#include "GameObject.h"

/* 
	불릿은 캐릭터에 속하지 않기 때문에,
	캐릭터가 아닌 게임 오브젝트를 상속한다.

	몬스터 객체가 불릿을 직접 생성하게 할 것이다.

	씬은 불릿을 포함한 오브젝트 정보를 가지고 있으므로,
	모든 오브젝트들은 씬을 멤버변수로 두고 씬에서 오브젝트를 
	생성할 때 this를 전달하여 오브젝트가 자신이 속한 씬을 알게 함으로써,
	몬스터 객체에서 씬을 통해 불릿의 생성이 가능해진다.
*/
class CBullet :
    public CGameObject
{
private:
	float m_angle;		// 각도
	float m_distance;	// (삭제를 위한)사거리 
	float	m_damage;   // 불릿이 입히는 데미지 
public:
	virtual bool Init();
	virtual void Update(float _deltaTime);
	virtual void PostUpdate(float _deltaTime);
	virtual void Render(HDC _hDC, float _deltaTime);
	void SetDamage(float _damage);
	void SetAngle(float _angle);
	void SetDistance(float _distance);
private:
	void CollisionBegin(CCollider* _src, CCollider* _dest);
	void CollisionEnd(CCollider* _src, CCollider* _dest);
protected:
	CBullet();
	CBullet(const CBullet& _obj);
	~CBullet();

	friend class CScene;	// 씬 변수에 씬 정보를 넘겨받기 위해
};

