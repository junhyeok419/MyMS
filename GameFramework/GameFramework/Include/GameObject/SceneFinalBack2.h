#pragma once
#include "GameObject.h"
class CSceneFinalBack2 :
    public CGameObject
{
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
protected:
    CSceneFinalBack2();
    CSceneFinalBack2(const CSceneFinalBack2& _obj);
    virtual ~CSceneFinalBack2();

    friend class CScene;
};

