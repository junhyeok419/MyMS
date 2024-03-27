#pragma once
#include "Character.h"
class CNpc
    : public CCharacter
{
private:
    EButtonState m_buttonState;  // 현재 버튼의 상태
    bool m_mouseHovered;         // 마우스가 올라가있는지 여부
    std::function<void()>   m_callback[(int)EButtonSoundState::Max];  // 버튼 상태에 따라 호출할 함수
    CSharedPtr<class CSound>    m_stateSound[(int)EButtonSoundState::Max];
    float m_aniChangeTime;       // 애니메이션이 바뀌는 주기
    CSharedPtr<class CWidgetComponent>	m_nameBarFrame;  // 이름 프레임
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void PostUpdate(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
public:

public:
    // 마우스와의 충돌 체크
    bool CollisionMouse(const Vector2& _pos);
public:
    // 커서가 올라갔을 때 호출
    void CollisionMouseHoveredCallback(const Vector2& _pos);
    // 커서가 떨어졌을 때 호출
    void CollisionMouseReleaseCallback();
public:
    virtual void OpenUIWindow();
public:
    // 버튼 상태에 따라 호출할 함수를 등록한다.
    template <typename T>
    void SetCallback(EButtonSoundState _state, T* _obj, void(T::* _func)())
    {
        m_callback[(int)_state] = std::bind(_func, _obj);
    }
public:
    CNpc();
    ~CNpc();
};

