#pragma once
#include "GameObject.h"

/*
    ��4�� ���1 (�޹��)
*/
class CScene2Back1 :
    public CGameObject
{
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
protected:
    CScene2Back1();
    CScene2Back1(const CScene2Back1& _obj);
    virtual ~CScene2Back1();

    friend class CScene;
};

