#pragma once
#include "GameObject.h"

/*
    ��4�� ���1 (�޹��)
*/
class CScene4Back1 :
    public CGameObject
{
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
protected:
    CScene4Back1();
    CScene4Back1(const CScene4Back1& _obj);
    virtual ~CScene4Back1();

    friend class CScene;
};

