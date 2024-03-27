#pragma once
#include "Widget.h"


enum class EProgressBar_Texture_Type
{
    Back,   // 바 배경
    Bar,    // 바
    End
};

// 바가 늘어나는 방향
enum class EProgressBar_Dir
{
    LeftToRight,    // 왼쪽   ->   오른쪽
    RightToLeft,    // 오른쪽 ->   왼쪽
    BottomToTop,    // 아래   ->   위
    TopToBottom,    // 위     ->   아래
    End
};

/*
    hp, 경험치 바 등을 표현하는 '프로그레스 바' 클래스이다.
    바를 만들 때에는 실제로 왔다 갔다 하는 바와,
    바 뒤편의 배경 이미지가 필요하다.
*/
class CProgressBar :
    public CWidget
{
protected:
    CSharedPtr<class CTexture>  m_texture[(int)EProgressBar_Texture_Type::End];  // 바의 텍스쳐. 최대 2개(배경, 바)
    EProgressBar_Dir    m_dir;      // 바가 채워지는 방향
    float               m_value;    // 바가 채워진 양. 0 ~ 1 사이의 값
    Vector2             m_barSize;  // 변동되는 바의 크기 (원본 : m_size)
    Vector2             m_barPos;   // 위치
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void PostUpdate(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
    virtual void Render(HDC _hDC, const Vector2& _pos, float _deltaTime);
public:
    void SetBarDir(EProgressBar_Dir _dir);
    void SetValue(float _value);
    void AddValue(float _value);
public:
    // sprite 텍스쳐를 로드
    void SetTexture(EProgressBar_Texture_Type _type, const std::string& _name, const TCHAR* _fileName,
        const std::string& _pathName = TEXTURE_PATH);
    void SetTextureFullPath(EProgressBar_Texture_Type _type, const std::string& _name, const TCHAR* _fullPath);

#ifdef UNICODE
    // frame 텍스쳐를 로드
    void SetTexture(EProgressBar_Texture_Type _type, const std::string& _name, const std::vector<std::wstring>& _vecFileName,
        const std::string& _pathName = TEXTURE_PATH);
    void SetTextureFullPath(EProgressBar_Texture_Type _type, const std::string& _name, const std::vector<std::wstring>& _vecFullPath);

#else
    // frame 텍스쳐를 로드 (멀티바이트 환경)
    void SetTexture(EProgressBar_Texture_Type _type, const std::string& _name, const std::vector<std::string>& _vecFileName,
        const std::string& _pathName = TEXTURE_PATH);
    void SetTextureFullPath(EProgressBar_Texture_Type _type, const std::string& _name, const std::vector<std::string>& _vecFullPath);

#endif

    void SetColorKey(EProgressBar_Texture_Type _type, unsigned char _r, unsigned char _g, unsigned char _b);
protected:
    CProgressBar();
    CProgressBar(const CProgressBar& _widget);
    virtual ~CProgressBar();

    friend class CWidgetWindow;
    friend class CWidgetComponent;
};

