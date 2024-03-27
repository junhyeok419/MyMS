#pragma once
#include "GameObject.h"

/*
    ¾À1ÀÇ ¹è°æ1 (µÞ¹è°æ)
*/
class CScene1Back1 :
    public CGameObject
{
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
protected:
    CScene1Back1();
    CScene1Back1(const CScene1Back1& _obj);
    virtual ~CScene1Back1();

    friend class CScene;
};

