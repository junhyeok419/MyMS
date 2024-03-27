#pragma once
#include "Widget.h"

/*
    �̹����� ������ ��Ÿ���� Ŭ�����̴�.
    �ִϸ��̼� ����� ���� �ʴ� �̹��� ��¿��̴�.
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

