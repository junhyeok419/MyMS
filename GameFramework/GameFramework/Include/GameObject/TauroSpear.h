#pragma once
#include "Monster.h"

// �İ���
class CTauroSpear :
	public CMonster
{
private:
	// ���� ũ�Ⱑ ���߳����ؼ� ���⿡ ���� �浹ü offset�� �������ֱ� ����
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
	virtual void CollisionCognitionBegin(CCollider* _src, CCollider* _dest);
	virtual void CollisionCognitionEnd(CCollider* _src, CCollider* _dest);
	virtual void CollisionBeginAttack(CCollider* _src, CCollider* _dest);
	virtual void CollisionEndAttack(CCollider* _src, CCollider* _dest);
private:
	void Attack();
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
protected:
	CTauroSpear();
	CTauroSpear(const CTauroSpear& obj);
	virtual ~CTauroSpear();

	friend class CScene;	// �� ������ �� ������ �Ѱܹޱ� ����
};

