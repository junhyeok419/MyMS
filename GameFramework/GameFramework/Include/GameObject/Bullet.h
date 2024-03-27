#pragma once
#include "GameObject.h"

/* 
	�Ҹ��� ĳ���Ϳ� ������ �ʱ� ������,
	ĳ���Ͱ� �ƴ� ���� ������Ʈ�� ����Ѵ�.

	���� ��ü�� �Ҹ��� ���� �����ϰ� �� ���̴�.

	���� �Ҹ��� ������ ������Ʈ ������ ������ �����Ƿ�,
	��� ������Ʈ���� ���� ��������� �ΰ� ������ ������Ʈ�� 
	������ �� this�� �����Ͽ� ������Ʈ�� �ڽ��� ���� ���� �˰� �����ν�,
	���� ��ü���� ���� ���� �Ҹ��� ������ ����������.
*/
class CBullet :
    public CGameObject
{
private:
	float m_angle;		// ����
	float m_distance;	// (������ ����)��Ÿ� 
	float	m_damage;   // �Ҹ��� ������ ������ 
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

	friend class CScene;	// �� ������ �� ������ �Ѱܹޱ� ����
};

