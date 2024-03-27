#pragma once
#include "../Ref.h"
/*
    위젯은 ui를 구성하는 '부품'으로, 버튼, 바, 텍스트 등이 있다.
    각 위젯은 이 클래스를 상속한다.

    '위젯 윈도우'에 각 위젯이 배치되는 구조이다.
*/
class CWidget :
    public CRef
{
protected:
    class CScene* m_scene;          // 위젯이 속한 씬
    class CWidgetWindow* m_owner;   // 위젯이 속한 위젯 윈도우
    int     m_zOrder;               // 위젯 끼리의 출력 순서를 정하기 위함
    Vector2 m_pos;                  // 위젯의 위치 (위젯 윈도우 내에서의)
    Vector2 m_size;                 // 위젯의 크기
    bool    m_mouseHovered;         // 위젯에 마우스가 올라가있는지 여부
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void PostUpdate(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
    // 위치 정보를 추가로 받아 처리하는 Render 이다.
    virtual void Render(HDC _hDC, const Vector2& _pos, float _deltaTime);
public:
    const Vector2& GetPos()	const;
    const Vector2& GetSize() const;
    int GetZOrder() const;
    void SetPos(float _x, float _y);
    void SetPos(const Vector2& _pos);
    void SetSize(float _x, float _y);
    void SetSize(const Vector2& _size);
    void SetZOrder(int _zOrder);
public:
    // 위젯과 마우스 충돌 체크
    bool CollisionMouse(const Vector2& _pos);
public:
    // 위젯에 커서가 올라갔을 때 호출
    virtual void CollisionMouseHoveredCallback(const Vector2& _pos);
    // 위젯과 커서가 떨어졌을 때 호출
    virtual void CollisionMouseReleaseCallback();
protected:
    CWidget();
    CWidget(const CWidget& widget);
    virtual ~CWidget();

    friend class CWidgetWindow;
    friend class CWidgetComponent;
};

