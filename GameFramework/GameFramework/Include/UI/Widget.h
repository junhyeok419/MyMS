#pragma once
#include "../Ref.h"
/*
    ������ ui�� �����ϴ� '��ǰ'����, ��ư, ��, �ؽ�Ʈ ���� �ִ�.
    �� ������ �� Ŭ������ ����Ѵ�.

    '���� ������'�� �� ������ ��ġ�Ǵ� �����̴�.
*/
class CWidget :
    public CRef
{
protected:
    class CScene* m_scene;          // ������ ���� ��
    class CWidgetWindow* m_owner;   // ������ ���� ���� ������
    int     m_zOrder;               // ���� ������ ��� ������ ���ϱ� ����
    Vector2 m_pos;                  // ������ ��ġ (���� ������ ��������)
    Vector2 m_size;                 // ������ ũ��
    bool    m_mouseHovered;         // ������ ���콺�� �ö��ִ��� ����
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void PostUpdate(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
    // ��ġ ������ �߰��� �޾� ó���ϴ� Render �̴�.
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
    // ������ ���콺 �浹 üũ
    bool CollisionMouse(const Vector2& _pos);
public:
    // ������ Ŀ���� �ö��� �� ȣ��
    virtual void CollisionMouseHoveredCallback(const Vector2& _pos);
    // ������ Ŀ���� �������� �� ȣ��
    virtual void CollisionMouseReleaseCallback();
protected:
    CWidget();
    CWidget(const CWidget& widget);
    virtual ~CWidget();

    friend class CWidgetWindow;
    friend class CWidgetComponent;
};

