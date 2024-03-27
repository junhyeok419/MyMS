#pragma once
#include "Scene.h"

class CStartScene :
    public CScene
{
public:
    bool Init();

protected:
    CStartScene();
    virtual ~CStartScene();

    friend class CSceneManager;
};

