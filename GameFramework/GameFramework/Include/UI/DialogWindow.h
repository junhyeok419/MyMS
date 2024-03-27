#pragma once
#include "WidgetWindow.h"

/*
    캐릭터의 상태를 나타내는 위젯 윈도우이다.
    멤버로 우선 hpBar와 BarFrame을 가져 hp를 표현할 것이다.
*/
class CDialogWindow :
    public CWidgetWindow
{
protected:
    CSharedPtr<class CImageWidget>  m_mainBox;   // 메인 박스
    CSharedPtr<class CButton>  m_exitButton; // 나가기 버튼
    
  
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
public:
    // 스타트 버튼을 눌렀을 때 호출할 함수
    void StartButtonCallback();
protected:
    CDialogWindow();
    virtual ~CDialogWindow();

    friend class CScene;
};

