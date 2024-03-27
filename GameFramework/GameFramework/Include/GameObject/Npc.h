#pragma once
#include "Character.h"
class CNpc
    : public CCharacter
{
private:
    EButtonState m_buttonState;  // ���� ��ư�� ����
    bool m_mouseHovered;         // ���콺�� �ö��ִ��� ����
    std::function<void()>   m_callback[(int)EButtonSoundState::Max];  // ��ư ���¿� ���� ȣ���� �Լ�
    CSharedPtr<class CSound>    m_stateSound[(int)EButtonSoundState::Max];
    float m_aniChangeTime;       // �ִϸ��̼��� �ٲ�� �ֱ�
    CSharedPtr<class CWidgetComponent>	m_nameBarFrame;  // �̸� ������
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void PostUpdate(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
public:

public:
    // ���콺���� �浹 üũ
    bool CollisionMouse(const Vector2& _pos);
public:
    // Ŀ���� �ö��� �� ȣ��
    void CollisionMouseHoveredCallback(const Vector2& _pos);
    // Ŀ���� �������� �� ȣ��
    void CollisionMouseReleaseCallback();
public:
    virtual void OpenUIWindow();
public:
    // ��ư ���¿� ���� ȣ���� �Լ��� ����Ѵ�.
    template <typename T>
    void SetCallback(EButtonSoundState _state, T* _obj, void(T::* _func)())
    {
        m_callback[(int)_state] = std::bind(_func, _obj);
    }
public:
    CNpc();
    ~CNpc();
};

