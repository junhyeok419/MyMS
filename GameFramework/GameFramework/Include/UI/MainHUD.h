#pragma once
#include "WidgetWindow.h"

/*
    ĳ������ ���¸� ��Ÿ���� ���� �������̴�.
    ����� �켱 hpBar�� BarFrame�� ���� hp�� ǥ���� ���̴�.
*/
class CMainHUD :
    public CWidgetWindow
{
protected:
    CSharedPtr<class CImageWidget>  m_mainFrame;   // ���� ������
    CSharedPtr<class CText>     m_FPSText;

    CSharedPtr<class CProgressBar>  m_HPBar;       // ��
    CSharedPtr<class CProgressBar>  m_MPBar;
    CSharedPtr<class CProgressBar>  m_EXPBar;

    CSharedPtr<class CNumber>     m_HPNumber;       // �� ��ġ�� ��Ÿ���� ����
    CSharedPtr<class CNumber>     m_HPMaxNumber;
    CSharedPtr<class CNumber>     m_MPNumber;
    CSharedPtr<class CNumber>     m_MPMaxNumber;
    CSharedPtr<class CNumber>     m_EXPNumber;
    CSharedPtr<class CNumber>     m_EXPRatioNumber;
    CSharedPtr<class CNumber>     m_levelNumber;    // ����

    CSharedPtr<class CImageWidget> m_skill1;        // ������ ��ų ������
    CSharedPtr<class CImageWidget> m_skill2;
    CSharedPtr<class CImageWidget> m_skill3;
    CSharedPtr<class CImageWidget> m_skill4;

    CSharedPtr<class CNumber> m_HPPotionCnt;        // hp ���� ����
    CSharedPtr<class CNumber> m_MPPotionCnt;        // mp ���� ����
    CSharedPtr<class CNumber> m_itemCnt;            // ��



    bool m_HPbarAdjust;   // �� �����ؾ��ϴ� ��������
    float m_HPadjustTime; // �����ð�
    float m_HP;           // ���� ����
    float m_prevHP;       // ���� ����

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

