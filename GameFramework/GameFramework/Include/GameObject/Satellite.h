#pragma once
#include "GameObject.h"
class CSatellite :
    public CGameObject
{
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
protected:
    CSatellite();
    CSatellite(const CSatellite& _obj);
    virtual ~CSatellite();

    friend class CScene;
};

