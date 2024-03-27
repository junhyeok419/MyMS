#pragma once
#include "GameObject.h"

/*
    씬6의 배경2 (지형)
*/
class CScene3Back2 :
    public CGameObject
{
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
protected:
    CScene3Back2();
    CScene3Back2(const CScene3Back2& _obj);
    virtual ~CScene3Back2();

    friend class CScene;
};

