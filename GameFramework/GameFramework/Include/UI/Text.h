#pragma once
#include "Widget.h"

/*
    �ε��� ��Ʈ�� �̿��� �ؽ�Ʈ�� ����ϴ� ���� Ŭ�����̴�.
    �ؽ�Ʈ ������ �̹����� ���� ���� �ʴ�.
*/
class CText :
    public CWidget
{
protected:
    TCHAR*      m_text;              // ��µ� �ؽ�Ʈ ���ڿ�
    int         m_count;             // ���� �ؽ�Ʈ ����
    int         m_capacity;          // �ִ� �ؽ�Ʈ ����
    COLORREF    m_textColor;         // �ؽ�Ʈ ����
   /*
       �ؽ�Ʈ�� �׸��ڸ� ���� �� �ִ�.
       �׸����� �������� �̿��� ���� �ȼ���ŭ ������, �Ʒ���
       �׸��ڸ� ���� ����ϰ� �� ���� �ؽ�Ʈ�� ���� �׸���
       ȿ���� ������.
   */
    COLORREF    m_shadowColor;       // �׸��� ���� 
    bool        m_shadow;            // �׸��� Ȱ��ȭ ����
    Vector2     m_shadowOffset;      // �ؽ�Ʈ�� �׸��ڰ� �Ÿ�
    CSharedPtr<class CFont> m_font;  // �ؽ�Ʈ ��Ʈ
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void PostUpdate(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
    virtual void Render(HDC _hDC, const Vector2& _pos, float _deltaTime);
public:
    void SetTextColor(unsigned char _r, unsigned char _g, unsigned char _b);
    void SetTextShadowColor(unsigned char _r, unsigned char _g, unsigned char _b);
    void EnableShadow(bool _shadow);
    void SetShadowOffset(float _x, float _y);
    // �ؽ�Ʈ�� �����Ѵ�. (���� �ؽ�Ʈ�� ����)
    void SetText(const TCHAR* _text);
    // �ؽ�Ʈ�� �����δ�. *�ѱ��ھ� �߰��ϱ� ���� �Լ�
    void AddText(const TCHAR _text);
    // �ؽ�Ʈ�� �����δ�. (���� �ؽ�Ʈ ������) ��簡 �� ���ھ� ������ �ϴ� �� �� ���� ����.
    void AddText(const TCHAR* _text);
    // ���� �� �ؽ�Ʈ�� �����.
    void pop_back();
    // �ؽ�Ʈ�� ��� ����.
    void clear();
    // ��Ʈ�� �����Ѵ�.
    void SetFont(const std::string& _name);
protected:
    CText();
    CText(const CText& _widget);
    virtual ~CText();

    friend class CWidgetWindow;
    friend class CWidgetComponent;
};

