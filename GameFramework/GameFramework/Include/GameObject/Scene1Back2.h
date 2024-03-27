#pragma once
#include "GameObject.h"

/*
    씬1의 배경2 (지형)
*/
class CScene1Back2 :
    public CGameObject
{
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
protected:
    CScene1Back2();
    CScene1Back2(const CScene1Back2& _obj);
    virtual ~CScene1Back2();

    friend class CScene;
};

