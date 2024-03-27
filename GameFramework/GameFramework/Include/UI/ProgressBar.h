#pragma once
#include "Widget.h"


enum class EProgressBar_Texture_Type
{
    Back,   // �� ���
    Bar,    // ��
    End
};

// �ٰ� �þ�� ����
enum class EProgressBar_Dir
{
    LeftToRight,    // ����   ->   ������
    RightToLeft,    // ������ ->   ����
    BottomToTop,    // �Ʒ�   ->   ��
    TopToBottom,    // ��     ->   �Ʒ�
    End
};

/*
    hp, ����ġ �� ���� ǥ���ϴ� '���α׷��� ��' Ŭ�����̴�.
    �ٸ� ���� ������ ������ �Դ� ���� �ϴ� �ٿ�,
    �� ������ ��� �̹����� �ʿ��ϴ�.
*/
class CProgressBar :
    public CWidget
{
protected:
    CSharedPtr<class CTexture>  m_texture[(int)EProgressBar_Texture_Type::End];  // ���� �ؽ���. �ִ� 2��(���, ��)
    EProgressBar_Dir    m_dir;      // �ٰ� ä������ ����
    float               m_value;    // �ٰ� ä���� ��. 0 ~ 1 ������ ��
    Vector2             m_barSize;  // �����Ǵ� ���� ũ�� (���� : m_size)
    Vector2             m_barPos;   // ��ġ
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
    // sprite �ؽ��ĸ� �ε�
    void SetTexture(EProgressBar_Texture_Type _type, const std::string& _name, const TCHAR* _fileName,
        const std::string& _pathName = TEXTURE_PATH);
    void SetTextureFullPath(EProgressBar_Texture_Type _type, const std::string& _name, const TCHAR* _fullPath);

#ifdef UNICODE
    // frame �ؽ��ĸ� �ε�
    void SetTexture(EProgressBar_Texture_Type _type, const std::string& _name, const std::vector<std::wstring>& _vecFileName,
        const std::string& _pathName = TEXTURE_PATH);
    void SetTextureFullPath(EProgressBar_Texture_Type _type, const std::string& _name, const std::vector<std::wstring>& _vecFullPath);

#else
    // frame �ؽ��ĸ� �ε� (��Ƽ����Ʈ ȯ��)
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

