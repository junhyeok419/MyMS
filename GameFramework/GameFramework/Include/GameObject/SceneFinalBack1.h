#pragma once
#include "GameObject.h"
class CSceneFinalBack1 :
    public CGameObject
{
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
protected:
    CSceneFinalBack1();
    CSceneFinalBack1(const CSceneFinalBack1& _obj);
    virtual ~CSceneFinalBack1();

    friend class CScene;
};

