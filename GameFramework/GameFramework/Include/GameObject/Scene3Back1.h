#pragma once
#include "GameObject.h"

/*
    ��4�� ���1 (�޹��)
*/
class CScene3Back1 :
    public CGameObject
{
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
protected:
    CScene3Back1();
    CScene3Back1(const CScene3Back1& _obj);
    virtual ~CScene3Back1();

    friend class CScene;
};

