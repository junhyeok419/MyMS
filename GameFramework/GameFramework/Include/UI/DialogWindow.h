#pragma once
#include "WidgetWindow.h"

/*
    ĳ������ ���¸� ��Ÿ���� ���� �������̴�.
    ����� �켱 hpBar�� BarFrame�� ���� hp�� ǥ���� ���̴�.
*/
class CDialogWindow :
    public CWidgetWindow
{
protected:
    CSharedPtr<class CImageWidget>  m_mainBox;   // ���� �ڽ�
    CSharedPtr<class CButton>  m_exitButton; // ������ ��ư
    
  
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
public:
    // ��ŸƮ ��ư�� ������ �� ȣ���� �Լ�
    void StartButtonCallback();
protected:
    CDialogWindow();
    virtual ~CDialogWindow();

    friend class CScene;
};

