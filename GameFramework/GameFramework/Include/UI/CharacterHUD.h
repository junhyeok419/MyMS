#pragma once
#include "WidgetWindow.h"

/*
    ĳ������ ���¸� ��Ÿ���� ���� �������̴�.
    ����� �켱 hpBar�� BarFrame�� ���� hp�� ǥ���� ���̴�.
*/
class CCharacterHUD :
    public CWidgetWindow
{
protected:
    CSharedPtr<class CProgressBar>  m_HPBar;        // ���� �����̴� ��
    CSharedPtr<class CImageWidget>  m_HPBarFrame;   // �� ������
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

