#pragma once
#include "GameObject.h"

/*
    ��� ������Ʈ Ŭ�����̴�.
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

