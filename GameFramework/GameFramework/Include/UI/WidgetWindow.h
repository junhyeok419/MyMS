#pragma once
#include "../Ref.h"
#include "Widget.h"

/*
    ���� ������ : ���� ������ ��� �ϳ��� '���� ������'�� �����Ѵ�. 

    ui���� ��½� ī�޶��� ������ �޾Ƽ��� �ȵȴ�.
    ��ġ �״�θ� �̿��� ����� �ؾ��Ѵ�.

    �� Ŭ������ ����� ���� ���� �����츦 �����.
*/
class CWidgetWindow :
    public CRef
{
protected:
    class CScene* m_scene;      // ���� �����찡 ���� ��
    int         m_zOrder;       // ���� ������ ��� ������ ���ϱ� ����
    std::vector<CSharedPtr<class CWidget>>  m_vecWidget; // �� ���� �����쿡 ���� ������
    Vector2     m_pos;          // ���� �������� ��ġ
    Vector2     m_size;         // ���� �������� ũ��
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void PostUpdate(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
public:
    class CWidget* GetWidget(int _index);
    int GetWidgetCount()    const;
    const Vector2& GetPos()	const;
    const Vector2& GetSize() const;
    int GetZOrder() const;
    void SetPos(float _x, float _y);
    void SetPos(const Vector2& _pos);
    void SetSize(float _x, float _y);
    void SetSize(const Vector2& _size);
    void SetZOrder(int _zOrder);
public:
    // ���� ������� ���콺�� �浹üũ
    bool CollisionMouse(class CWidget** _widget, const Vector2& _pos);
public:
    void SortCollision();
private:
    // SortCollision ���� std::sort�� ���ڷ� ����ϱ� ���� static���� ������ �� ��.
    /*
        ���� ���� :
        * SortCollisionWidget : �浹 üũ�� ���� ����
        ���� �浹 üũ�� zOrder�� ū ������ üũ�ؾ� �ϹǷ�
        zOrder�� ū ������ �������� �����Ͽ� ���Ϳ� ���� ���̴�.

        * SortWidget : �������� ���� ����
        ��, zOrder�� ū ������ ���� �������� �׷����Ƿ�,
        �׸� ���� zOrder�� ���� �������� ������������ �׷��� �Ѵ�.
    */
    static bool SortCollisionWidget(const CSharedPtr<class CWidget>& _src,
        const CSharedPtr<class CWidget>& _dest);
    static bool SortWidget(const CSharedPtr<class CWidget>& _src,
        const CSharedPtr<class CWidget>& _dest);
public:
    // �̸��� �ش��ϴ� ������ ã�´�. � �������� �𸣹Ƿ� ���ø�����.
    template <typename T>
    T* FindWidget(const std::string& _name)
    {
        size_t  size = m_vecWidget.size();

        // ���ϴ� �̸��� ���� ������ ã�� ��ȯ�Ѵ�.
        for (size_t i = 0; i < size; ++i)
        {
            if (m_vecWidget[i]->GetName() == _name)
                return (T*)m_vecWidget[i];
        }

        return nullptr;
    }

    // �̸����� ������ �����. � �������� �𸣹Ƿ� ���ø�����.
    template <typename T>
    T* CreateWidget(const std::string& _name)
    {
        // ���� ��ü ����
        T* widget = new T;

        widget->SetName(_name);
        widget->m_scene = m_scene;
        widget->m_owner = this;

        // �ʱ�ȭ
        if (!widget->Init())
        {
            SAFE_DELETE(widget);
            return nullptr;
        }

        // ���Ϳ� �߰�
        m_vecWidget.push_back(widget);

        // ���� ����
        return (T*)widget;
    }
protected:
    CWidgetWindow();
    virtual ~CWidgetWindow();

    friend class CScene;
};

