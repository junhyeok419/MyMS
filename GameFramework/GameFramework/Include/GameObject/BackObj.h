#pragma once
#include "GameObject.h"

/*
    배경 오브젝트 클래스이다.
*/

class CBackObj :
    public CGameObject
{
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
protected:
    CBackObj();
    CBackObj(const CBackObj& _obj);
    virtual ~CBackObj();

    friend class CScene;
};

