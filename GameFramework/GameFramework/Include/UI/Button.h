#pragma once
#include "Widget.h"
#include "../Resource/Texture/Texture.h"
class CButton :
    public CWidget
{
protected:
    CSharedPtr<class CTexture>  m_texture;  // ��ư�� �ؽ��� 
    AnimationFrameData      m_stateData[(int)EButtonState::Max]; // ��ư �ִϸ��̼��� ���� ������ ������
    EButtonState           m_buttonState;  // ���� ��ư�� ����
    std::function<void()>   m_callback[(int)EButtonSoundState::Max];  // ��ư ���¿� ���� ȣ���� �Լ�
    CSharedPtr<class CSound>    m_stateSound[(int)EButtonSoundState::Max];  // ��ư ���¿� ���� ����� ����
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void PostUpdate(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
    virtual void Render(HDC _hDC, const Vector2& _pos, float _deltaTime);
public:
    void SetTexture(const std::string& _name, const TCHAR* _fileName,
        const std::string& _pathName = TEXTURE_PATH);
    void SetTextureFullPath(const std::string& _name, const TCHAR* _fullPath);

#ifdef UNICODE

    void SetTexture(const std::string& _name, const std::vector<std::wstring>& _vecFileName,
        const std::string& _pathName = TEXTURE_PATH);
    void SetTextureFullPath(const std::string& _name, const std::vector<std::wstring>& _vecFullPath);

#else

    void SetTexture(const std::string& _name, const std::vector<std::string>& _vecFileName,
        const std::string& _pathName = TEXTURE_PATH);
    void SetTextureFullPath(const std::string& _name, const std::vector<std::string>& _vecFullPath);

#endif
    // Ư�� ��ư ������ ������ �����͸� �ִ´�.
    void SetButtonStateData(EButtonState _state, const Vector2& _start, const Vector2& _end);
    // ��ư�� Ȱ��ȭ / ��Ȱ��ȭ �Ѵ�.
    void EnableButton(bool _enable);
    // Ư�� ��ư ���¿��� ����� ���带 �ִ´�.
    void SetSound(EButtonSoundState _state, const std::string& _name);

public:
    // ��ư�� ���콺�� �浹���� �� ȣ��
    virtual void CollisionMouseHoveredCallback(const Vector2& _pos);
    // ��ư�� ���콺�� �浹�ߴٰ� �������� �� ȣ��
    virtual void CollisionMouseReleaseCallback();

public:
    bool SetColorKeyAll(unsigned char _r, unsigned char _g, unsigned char _b)
    {
        // ���� ������Ʈ�� ���� �ؽ��İ� �����ϴ���. ������ ����
        if (!m_texture)
            return false;

        // �ؽ����� ��� �̹����� �÷�Ű�� �����Ѵ�.
        m_texture->SetColorKeyAll(_r, _g, _b);

        return true;
    }
public:
    // ��ư ���¿� ���� ȣ���� �Լ��� ����Ѵ�.
    template <typename T>
    void SetCallback(EButtonSoundState _state, T* _obj, void(T::* _func)())
    {
        m_callback[(int)_state] = std::bind(_func, _obj);
    }
protected:
    CButton();
    CButton(const CButton& _widget);
    virtual ~CButton();

    friend class CWidgetWindow;
    friend class CWidgetComponent;
};

