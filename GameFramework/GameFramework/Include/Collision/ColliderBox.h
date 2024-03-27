#pragma once
#include "Collider.h"
/*
    박스(Box)형 충돌체를 나타내는 클래스이다.
*/
class CColliderBox :
    public CCollider
{
protected:
    // Data
    float   m_width;    // 가로 길이
    float   m_height;   // 세로 길이
    BoxInfo m_info;     // 좌상단, 우하단 좌표
public:
    // Logic
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void PostUpdate(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
    virtual bool Collision(CCollider* _dest);     // 상대방 충돌체의 모양별로 충돌 처리를 한다.
    virtual bool CollisionMouse(const Vector2& _mouse); // 마우스 커서의 좌표를 받아 충돌 처리를 한다.
public:
    // Access
    BoxInfo GetInfo() const;
    void SetInfo(const Vector2& _lt, const Vector2& _rb);
    virtual const BoxInfo& GetBoxInfo() const;
    virtual void SetExtent(float _width, float _height);  // 가로 세로 크기를 지정
    virtual void SetExtent(const Vector2& _size);  // 가로 세로 크기를 지정
    virtual const Vector2& GetExtent() const;
protected:
    // Constructor, destructor
    CColliderBox();
    CColliderBox(const CColliderBox& _collider);
    virtual ~CColliderBox();

    friend class CGameObject;
};

