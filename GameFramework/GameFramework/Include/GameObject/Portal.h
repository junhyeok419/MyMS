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
	virtual	void CollisionBegin(CCollider* _src, CCollider* _dest);	// 충돌 시작 시 호출될 함수
	virtual void CollisionEnd(CCollider* _src, CCollider* _dest);   // 충돌 종료 시 호출될 함수
protected:
	CPortal();
	CPortal(const CPortal& obj);
	virtual ~CPortal();

	friend class CScene;	// 씬 변수에 씬 정보를 넘겨받기 위해  
 };
 
