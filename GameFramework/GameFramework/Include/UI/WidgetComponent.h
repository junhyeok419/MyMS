#pragma once
#include "../Ref.h"

/*
    ui를 위젯 윈도우가 아닌 월드상에서 출력해야 하는 경우도 있다.
    플레이어 머리 위의 hp바 라던지, 플레이어 밑의 이름이라던지,
    숫자 위젯으로 머리 위에 데미지를 띄워 준다던지..

    그러한 기능을 수행하기 위해, 위젯들을 게임 오브젝트에 추가해 줄 수 있는
    중계자 역할을 하는 클래스이다.
*/
class CWidgetComponent :
    public CRef
{
private:
    class CGameObject* m_owner;            // 이 위젯을 소유한 게임오브젝트
    class CScene* m_scene;                 // 이 위젯이 속한 씬
    CSharedPtr<class CWidget>   m_widget;  // 위젯
    Vector2     m_pos;                     // 위치 
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
    // 위젯 얻어옴
    template <typename T>
    T* GetWidget()  const
    {
        return (T*)m_widget.Get();
    }

    // 위젯 생성
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

