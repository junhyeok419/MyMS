#pragma once
#include "Collider.h"
/*
    �ڽ�(Box)�� �浹ü�� ��Ÿ���� Ŭ�����̴�.
*/
class CColliderBox :
    public CCollider
{
protected:
    // Data
    float   m_width;    // ���� ����
    float   m_height;   // ���� ����
    BoxInfo m_info;     // �»��, ���ϴ� ��ǥ
public:
    // Logic
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void PostUpdate(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
    virtual bool Collision(CCollider* _dest);     // ���� �浹ü�� ��纰�� �浹 ó���� �Ѵ�.
    virtual bool CollisionMouse(const Vector2& _mouse); // ���콺 Ŀ���� ��ǥ�� �޾� �浹 ó���� �Ѵ�.
public:
    // Access
    BoxInfo GetInfo() const;
    void SetInfo(const Vector2& _lt, const Vector2& _rb);
    virtual const BoxInfo& GetBoxInfo() const;
    virtual void SetExtent(float _width, float _height);  // ���� ���� ũ�⸦ ����
    virtual void SetExtent(const Vector2& _size);  // ���� ���� ũ�⸦ ����
    virtual const Vector2& GetExtent() const;
protected:
    // Constructor, destructor
    CColliderBox();
    CColliderBox(const CColliderBox& _collider);
    virtual ~CColliderBox();

    friend class CGameObject;
};

