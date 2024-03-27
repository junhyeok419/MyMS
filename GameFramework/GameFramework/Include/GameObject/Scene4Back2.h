#pragma once
#include "GameObject.h"

/*
    씬6의 배경2 (지형)
*/
class CScene4Back2 :
    public CGameObject
{
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
protected:
    CScene4Back2();
    CScene4Back2(const CScene4Back2& _obj);
    virtual ~CScene4Back2();

    friend class CScene;
};

