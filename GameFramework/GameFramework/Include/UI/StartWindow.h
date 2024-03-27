#pragma once
#include "WidgetWindow.h"
/*
    ���� ���� ��, ���� ��ư ���� �������� ����
    ��ŸƮ ���� �������.
*/
class CStartWindow :
    public CWidgetWindow
{
private:
    CSharedPtr<class CText> m_text;   // �ؽ�Ʈ ����
    TCHAR       m_addText[32];        // �߰��� �ؽ�Ʈ ���ڿ�
    float       m_textTime;           // �ؽ�Ʈ�� �߰��Ǵ� �ð���
    int         m_addCount;           // �ؽ�Ʈ�� �߰��� ����
    /*
        ���� ������ �̿��� ��ŸƮ �����쿡 �ð��� ����� ���̴�.
    */
    CSharedPtr<class CNumber>   m_hour;     // ��
    CSharedPtr<class CNumber>   m_minute;   // ��
    CSharedPtr<class CNumber>   m_second;   // ��

    CSharedPtr<class CText>     m_FPSText;  // FPS��¿�
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
public:
    // ��ŸƮ ��ư�� ������ �� ȣ���� �Լ�
    void StartButtonCallback();
    // ���� ��ư�� ������ �� ȣ���� �Լ�
    void EndButtonCallback();
protected:
    CStartWindow();
    virtual ~CStartWindow();

    friend class CScene;
};

