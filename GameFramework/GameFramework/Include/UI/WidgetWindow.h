#pragma once
#include "../Ref.h"
#include "Widget.h"

/*
    위젯 윈도우 : 여러 위젯을 모아 하나의 '위젯 윈도우'를 구성한다. 

    ui들은 출력시 카메라의 영향을 받아서는 안된다.
    위치 그대로를 이용해 출력을 해야한다.

    이 클래스를 상속해 여러 위젯 윈도우를 만든다.
*/
class CWidgetWindow :
    public CRef
{
protected:
    class CScene* m_scene;      // 위젯 윈도우가 속한 씬
    int         m_zOrder;       // 위젯 끼리의 출력 순서를 정하기 위함
    std::vector<CSharedPtr<class CWidget>>  m_vecWidget; // 이 위젯 윈도우에 속한 위젯들
    Vector2     m_pos;          // 위젯 윈도우의 위치
    Vector2     m_size;         // 위젯 윈도우의 크기
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
    // 위젯 윈도우와 마우스간 충돌체크
    bool CollisionMouse(class CWidget** _widget, const Vector2& _pos);
public:
    void SortCollision();
private:
    // SortCollision 내의 std::sort의 인자로 사용하기 위해 static으로 선언한 듯 함.
    /*
        위젯 정렬 :
        * SortCollisionWidget : 충돌 체크를 위한 정렬
        위젯 충돌 체크는 zOrder가 큰 순서로 체크해야 하므로
        zOrder가 큰 순으로 내림차순 정렬하여 벡터에 넣을 것이다.

        * SortWidget : 렌더링을 위한 정렬
        단, zOrder가 큰 위젯이 가장 마지막에 그려지므로,
        그릴 때는 zOrder가 작은 순서부터 오름차순으로 그려야 한다.
    */
    static bool SortCollisionWidget(const CSharedPtr<class CWidget>& _src,
        const CSharedPtr<class CWidget>& _dest);
    static bool SortWidget(const CSharedPtr<class CWidget>& _src,
        const CSharedPtr<class CWidget>& _dest);
public:
    // 이름에 해당하는 위젯을 찾는다. 어떤 위젯인지 모르므로 템플릿으로.
    template <typename T>
    T* FindWidget(const std::string& _name)
    {
        size_t  size = m_vecWidget.size();

        // 원하는 이름을 가진 위젯을 찾아 반환한다.
        for (size_t i = 0; i < size; ++i)
        {
            if (m_vecWidget[i]->GetName() == _name)
                return (T*)m_vecWidget[i];
        }

        return nullptr;
    }

    // 이름으로 위젯을 만든다. 어떤 위젯인지 모르므로 템플릿으로.
    template <typename T>
    T* CreateWidget(const std::string& _name)
    {
        // 위젯 객체 생성
        T* widget = new T;

        widget->SetName(_name);
        widget->m_scene = m_scene;
        widget->m_owner = this;

        // 초기화
        if (!widget->Init())
        {
            SAFE_DELETE(widget);
            return nullptr;
        }

        // 벡터에 추가
        m_vecWidget.push_back(widget);

        // 위젯 리턴
        return (T*)widget;
    }
protected:
    CWidgetWindow();
    virtual ~CWidgetWindow();

    friend class CScene;
};

