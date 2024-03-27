#pragma once
#include "GameObject.h"
class CMPPotion :
	public CGameObject
{
public:
	virtual bool Init();
	virtual void Update(float _deltaTime);
	virtual void PostUpdate(float _deltaTime);
	virtual void Render(HDC _hDC, float _deltaTime);
private:
	// �浹 �Լ�
	virtual void CollisionBegin(CCollider* _src, CCollider* _dest);
	virtual void CollisionEnd(CCollider* _src, CCollider* _dest);
protected:
	CMPPotion();
	CMPPotion(const CMPPotion& obj);
	virtual ~CMPPotion();

	friend class CScene;	// �� ������ �� ������ �Ѱܹޱ� ����

};

