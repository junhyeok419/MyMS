#pragma once
#include "Widget.h"

/*
    ���ڸ� �������� ǥ���ϱ� ���� Ŭ�����̴�.
    
    ���� ���, number�� 123�� ������ 1, 2, 3�� ���� �߶�
    �߶� ������ �̹����� ����� ���̴�.
*/
class CNumber :
    public CWidget
{
protected:
    CSharedPtr<class CTexture>  m_texture;  // ���� �ؽ���
    int                 m_number;           // ���� ����
    std::vector<int>    m_vecNumber;        // number�� �߶� ���� ����
    float m_lifeTime;   // ���ڰ� ����ִ� 1�� (����������)
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

