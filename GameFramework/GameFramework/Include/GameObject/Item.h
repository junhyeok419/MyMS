#pragma once
#include "GameObject.h"

// 선공형
class CItem :
	public CGameObject
{
public:
	virtual bool Init();
	virtual void Update(float _deltaTime);
	virtual void PostUpdate(float _deltaTime);
	virtual void Render(HDC _hDC, float _deltaTime);
private:
	// 충돌 함수
	virtual void CollisionBegin(CCollider* _src, CCollider* _dest);
	virtual void CollisionEnd(CCollider* _src, CCollider* _dest);
protected:
	CItem();
	CItem(const CItem& obj);
	virtual ~CItem();

	friend class CScene;	// 씬 변수에 씬 정보를 넘겨받기 위해
};


