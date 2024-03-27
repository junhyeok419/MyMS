#pragma once
#include "../Ref.h"

/*
    ui�� ���� �����찡 �ƴ� ����󿡼� ����ؾ� �ϴ� ��쵵 �ִ�.
    �÷��̾� �Ӹ� ���� hp�� �����, �÷��̾� ���� �̸��̶����,
    ���� �������� �Ӹ� ���� �������� ��� �شٴ���..

    �׷��� ����� �����ϱ� ����, �������� ���� ������Ʈ�� �߰��� �� �� �ִ�
    �߰��� ������ �ϴ� Ŭ�����̴�.
*/
class CWidgetComponent :
    public CRef
{
private:
    class CGameObject* m_owner;            // �� ������ ������ ���ӿ�����Ʈ
    class CScene* m_scene;                 // �� ������ ���� ��
    CSharedPtr<class CWidget>   m_widget;  // ����
    Vector2     m_pos;                     // ��ġ 
    float m_lifeTime;
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void PostUpdate(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
public:
    Vector2 GetPos() const;
    float GetBottom() const;
    void SetPos(float _x, float _y);
    void SetPos(const Vector2& _pos);
    void SetWidget(class CWidget* _widget);
    class CWidget* GetWidget()  const;
public:
    // ���� ����
    template <typename T>
    T* GetWidget()  const
    {
        return (T*)m_widget.Get();
    }

    // ���� ����
    template <typename T>
    T* CreateWidget(const std::string& _name)
    {
        T* Widget = new T;

        Widget->SetName(_name);
        Widget->m_scene = m_scene;

        if (!Widget->Init())
        {
            SAFE_DELETE(Widget);
            return nullptr;
        }

        m_widget = Widget;

        return (T*)Widget;
    }
protected:
    CWidgetComponent();
    CWidgetComponent(const CWidgetComponent& _widget);
    virtual ~CWidgetComponent();

    friend class CGameObject;
};

