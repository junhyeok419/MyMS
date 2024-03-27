#pragma once
#include "WidgetWindow.h"

/*
    캐릭터의 상태를 나타내는 위젯 윈도우이다.
    멤버로 우선 hpBar와 BarFrame을 가져 hp를 표현할 것이다.
*/
class CMainHUD :
    public CWidgetWindow
{
protected:
    CSharedPtr<class CImageWidget>  m_mainFrame;   // 메인 프레임
    CSharedPtr<class CText>     m_FPSText;

    CSharedPtr<class CProgressBar>  m_HPBar;       // 바
    CSharedPtr<class CProgressBar>  m_MPBar;
    CSharedPtr<class CProgressBar>  m_EXPBar;

    CSharedPtr<class CNumber>     m_HPNumber;       // 바 수치를 나타내는 숫자
    CSharedPtr<class CNumber>     m_HPMaxNumber;
    CSharedPtr<class CNumber>     m_MPNumber;
    CSharedPtr<class CNumber>     m_MPMaxNumber;
    CSharedPtr<class CNumber>     m_EXPNumber;
    CSharedPtr<class CNumber>     m_EXPRatioNumber;
    CSharedPtr<class CNumber>     m_levelNumber;    // 레벨

    CSharedPtr<class CImageWidget> m_skill1;        // 퀵슬롯 스킬 아이콘
    CSharedPtr<class CImageWidget> m_skill2;
    CSharedPtr<class CImageWidget> m_skill3;
    CSharedPtr<class CImageWidget> m_skill4;

    CSharedPtr<class CNumber> m_HPPotionCnt;        // hp 포션 개수
    CSharedPtr<class CNumber> m_MPPotionCnt;        // mp 포션 개수
    CSharedPtr<class CNumber> m_itemCnt;            // ㅅ



    bool m_HPbarAdjust;   // 바 조정해야하는 상태인지
    float m_HPadjustTime; // 조정시간
    float m_HP;           // 현재 비율
    float m_prevHP;       // 이전 비율

    bool m_MPbarAdjust;  
    float m_MPadjustTime;
    float m_MP;        
    float m_prevMP;    

    bool m_EXPbarAdjust;   
    float m_EXPadjustTime;
    float m_EXP;        
    float m_prevEXP;     
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
public:
    void SetHP(float _HP, float _prev);
    void SetMP(float _MP, float _prev);
    void SetEXP(float _EXP, float _prev);
    void SetHP2(float _HP);
    void SetMP2(float _MP);
    void SetEXP2(float _EXP);
protected:
    CMainHUD();
    virtual ~CMainHUD();

    friend class CScene;
};

