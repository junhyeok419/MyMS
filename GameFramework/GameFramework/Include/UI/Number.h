#pragma once
#include "Widget.h"

/*
    숫자를 위젯으로 표현하기 위한 클래스이다.
    
    예를 들어, number에 123이 들어오면 1, 2, 3을 각각 잘라
    잘라낸 값들을 이미지로 출력할 것이다.
*/
class CNumber :
    public CWidget
{
protected:
    CSharedPtr<class CTexture>  m_texture;  // 숫자 텍스쳐
    int                 m_number;           // 들어온 숫자
    std::vector<int>    m_vecNumber;        // number를 잘라낸 값의 벡터
    float m_lifeTime;   // 숫자가 살아있는 1초 (데미지위젯)
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void PostUpdate(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
    virtual void Render(HDC _hDC, const Vector2& _pos, float _deltaTime);
public:
    void SetNumber(int _number);
    void AddNumber(int _number);
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
    void SetColorKey(unsigned char _r, unsigned char _g, unsigned char _b);
protected:
    CNumber();
    CNumber(const CNumber& _widget);
    virtual ~CNumber();

    friend class CWidgetComponent;
    friend class CWidgetWindow;
};

