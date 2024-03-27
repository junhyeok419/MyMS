#pragma once
#include "GameObject.h"

class CCharacter
	: public CGameObject
{
public:
	virtual bool Init();
	virtual void Update(float _deltaTime);
	virtual void PostUpdate(float _deltaTime);
	virtual void Render(HDC _hDC, float _deltaTime);
	virtual float InflictDamage(float _damage, int _dir = 1);

	CCharacter();
	CCharacter(const CCharacter& Obj);
	virtual ~CCharacter();

	friend class CScene;	// 씬 변수에 씬 정보를 넘겨받기 위해
};

