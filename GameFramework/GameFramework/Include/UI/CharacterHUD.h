#pragma once
#include "WidgetWindow.h"

/*
    캐릭터의 상태를 나타내는 위젯 윈도우이다.
    멤버로 우선 hpBar와 BarFrame을 가져 hp를 표현할 것이다.
*/
class CCharacterHUD :
    public CWidgetWindow
{
protected:
    CSharedPtr<class CProgressBar>  m_HPBar;        // 실제 움직이는 바
    CSharedPtr<class CImageWidget>  m_HPBarFrame;   // 바 테투리
    CSharedPtr<class CText>     m_FPSText;
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
public:
    void SetHP(float _HP);
protected:
    CCharacterHUD();
    virtual ~CCharacterHUD();

    friend class CScene;
};

