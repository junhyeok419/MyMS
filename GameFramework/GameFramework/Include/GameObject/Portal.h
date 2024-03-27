#pragma once
#include "GameObject.h"

class CPortal :
	public CGameObject
{
public:
	virtual bool Init();
	virtual void Update(float _deltaTime);
	virtual void PostUpdate(float _deltaTime);
	virtual void Render(HDC _hDC, float _deltaTime);
private:
	virtual	void CollisionBegin(CCollider* _src, CCollider* _dest);	// �浹 ���� �� ȣ��� �Լ�
	virtual void CollisionEnd(CCollider* _src, CCollider* _dest);   // �浹 ���� �� ȣ��� �Լ�
protected:
	CPortal();
	CPortal(const CPortal& obj);
	virtual ~CPortal();

	friend class CScene;	// �� ������ �� ������ �Ѱܹޱ� ����  
 };
 
