#pragma once
#include "Widget.h"

/*
    로드한 폰트를 이용해 텍스트를 출력하는 위젯 클래스이다.
    텍스트 위젯은 이미지를 갖고 있지 않다.
*/
class CText :
    public CWidget
{
protected:
    TCHAR*      m_text;              // 출력될 텍스트 문자열
    int         m_count;             // 현재 텍스트 개수
    int         m_capacity;          // 최대 텍스트 개수
    COLORREF    m_textColor;         // 텍스트 색상
   /*
       텍스트로 그림자를 만들 수 있다.
       그림자의 오프셋을 이용해 일정 픽셀만큼 오른쪽, 아래로
       그림자를 먼저 출력하고 그 위에 텍스트를 덮어 그림자
       효과를 만들어낸다.
   */
    COLORREF    m_shadowColor;       // 그림자 색상 
    bool        m_shadow;            // 그림자 활성화 여부
    Vector2     m_shadowOffset;      // 텍스트와 그림자간 거리
    CSharedPtr<class CFont> m_font;  // 텍스트 폰트
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
    // 텍스트를 설정한다. (기존 텍스트를 지움)
    void SetText(const TCHAR* _text);
    // 텍스트를 덧붙인다. *한글자씩 추가하기 위한 함수
    void AddText(const TCHAR _text);
    // 텍스트를 덧붙인다. (기존 텍스트 안지움) 대사가 한 글자씩 나오게 하는 것 등 구현 가능.
    void AddText(const TCHAR* _text);
    // 가장 뒤 텍스트를 지운다.
    void pop_back();
    // 텍스트를 모두 비운다.
    void clear();
    // 폰트를 설정한다.
    void SetFont(const std::string& _name);
protected:
    CText();
    CText(const CText& _widget);
    virtual ~CText();

    friend class CWidgetWindow;
    friend class CWidgetComponent;
};

