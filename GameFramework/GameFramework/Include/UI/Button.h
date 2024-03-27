#pragma once
#include "Widget.h"
#include "../Resource/Texture/Texture.h"
class CButton :
    public CWidget
{
protected:
    CSharedPtr<class CTexture>  m_texture;  // 버튼의 텍스쳐 
    AnimationFrameData      m_stateData[(int)EButtonState::Max]; // 버튼 애니메이션을 위한 프레임 데이터
    EButtonState           m_buttonState;  // 현재 버튼의 상태
    std::function<void()>   m_callback[(int)EButtonSoundState::Max];  // 버튼 상태에 따라 호출할 함수
    CSharedPtr<class CSound>    m_stateSound[(int)EButtonSoundState::Max];  // 버튼 상태에 따라 재생될 사운드
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
    // 특정 버튼 상태의 프레임 데이터를 넣는다.
    void SetButtonStateData(EButtonState _state, const Vector2& _start, const Vector2& _end);
    // 버튼을 활성화 / 비활성화 한다.
    void EnableButton(bool _enable);
    // 특정 버튼 상태에서 재생할 사운드를 넣는다.
    void SetSound(EButtonSoundState _state, const std::string& _name);

public:
    // 버튼과 마우스가 충돌했을 때 호출
    virtual void CollisionMouseHoveredCallback(const Vector2& _pos);
    // 버튼과 마우스가 충돌했다가 떨어졌을 때 호출
    virtual void CollisionMouseReleaseCallback();

public:
    bool SetColorKeyAll(unsigned char _r, unsigned char _g, unsigned char _b)
    {
        // 현재 오브젝트에 대한 텍스쳐가 존재하는지. 없으면 리턴
        if (!m_texture)
            return false;

        // 텍스쳐의 모든 이미지의 컬러키를 지정한다.
        m_texture->SetColorKeyAll(_r, _g, _b);

        return true;
    }
public:
    // 버튼 상태에 따라 호출할 함수를 등록한다.
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

