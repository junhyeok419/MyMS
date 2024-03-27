#pragma once
#include "WidgetWindow.h"
/*
    게임 실행 시, 시작 버튼 등을 위젯으로 갖는
    스타트 위젯 윈도우다.
*/
class CStartWindow :
    public CWidgetWindow
{
private:
    CSharedPtr<class CText> m_text;   // 텍스트 위젯
    TCHAR       m_addText[32];        // 추가할 텍스트 문자열
    float       m_textTime;           // 텍스트가 추가되는 시간값
    int         m_addCount;           // 텍스트가 추가된 개수
    /*
        숫자 위젯을 이용해 스타트 윈도우에 시간을 출력할 것이다.
    */
    CSharedPtr<class CNumber>   m_hour;     // 시
    CSharedPtr<class CNumber>   m_minute;   // 분
    CSharedPtr<class CNumber>   m_second;   // 초

    CSharedPtr<class CText>     m_FPSText;  // FPS출력용
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
public:
    // 스타트 버튼을 눌렀을 때 호출할 함수
    void StartButtonCallback();
    // 엔드 버튼을 눌렀을 때 호출할 함수
    void EndButtonCallback();
protected:
    CStartWindow();
    virtual ~CStartWindow();

    friend class CScene;
};

