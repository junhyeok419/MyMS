#pragma once
#include "Monster.h"
class CMachine :
    public CMonster
{
private:
	class CColliderBox* m_box;
	CSharedPtr<class CWidgetComponent>	m_nameBarFrame;  // �̸� ������
public:
	virtual bool Init();
	virtual void Update(float _deltaTime);
	virtual void PostUpdate(float _deltaTime);
	virtual void Render(HDC _hDC, float _deltaTime);
	virtual float InflictDamage(float _damage, int _dir = 1);
private:
	// �浹 �Լ�
	virtual void CollisionBegin(CCollider* _src, CCollider* _dest);
	virtual void CollisionEnd(CCollider* _src, CCollider* _dest);
	virtual void CollisionMouseBegin(CCollider* _src, const Vector2& _mousePos);
	virtual void CollisionMouseEnd(CCollider* _src, const Vector2& _mousePos);
	virtual void CollisionBeginAttack(CCollider* _src, CCollider* _dest);
	virtual void CollisionEndAttack(CCollider* _src, CCollider* _dest);
private:
	// �ִϸ��̼� ���� �Լ�
	virtual void Die();
	virtual void HitEnd();
protected:
	CMachine();
	CMachine(const CMachine& obj);
	virtual ~CMachine();

	friend class CScene;	// �� ������ �� ������ �Ѱܹޱ� ����
};

