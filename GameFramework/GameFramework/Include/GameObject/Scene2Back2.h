#pragma once
#include "GameObject.h"

/*
    씬6의 배경2 (지형)
*/
class CScene2Back2 :
    public CGameObject
{
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
protected:
    CScene2Back2();
    CScene2Back2(const CScene2Back2& _obj);
    virtual ~CScene2Back2();

    friend class CScene;
};

