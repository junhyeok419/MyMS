#pragma once
#include "Widget.h"

/*
    이미지형 위젯을 나타내는 클래스이다.
    애니메이션 출력을 하지 않는 이미지 출력용이다.
*/
class CImageWidget :
    public CWidget
{
protected:
    CSharedPtr<class CTexture>  m_texture;
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

#endif // UNICODE
    void SetColorKey(unsigned char _r, unsigned char _g, unsigned char _b);
protected:
    CImageWidget();
    CImageWidget(const CImageWidget& _widget);
    virtual ~CImageWidget();

    friend class CWidgetWindow;
    friend class CWidgetComponent;
};

