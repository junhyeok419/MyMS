#pragma once
#include "../../Ref.h"

/*
    �̹��� �ε�����, ����ó�� 1���� �̹������� �ε��ϴ� ��쵵 ������
    ���� ���� �̹����� �ϳ��� �ִϸ��̼��� ǥ���ؾ� �ϴ� ��쵵 ���� �� 
    �ִ�.

    ���� dc�� ��Ʈ�� � ���������� �ϹǷ�, �̵��� ��� ����ü�� 
    ���� �� �ؽ��� Ŭ�������� �� ����ü�� ���ͷ� ����ְ� �� ���̴�.
*/
struct ImageInfo
{
    /*
        �������� ����ߴ� DC�� ȭ�鿡 ���� �׷����� dc����.
        ���� ����� �޸�DC�� ����ִ� DC�̴�.
        �޸�DC�� �̹����� ä���� ��ġ '����'ó�� �� �� �ְ� �Ѵ�.

        ��Ʈ���� �޸�DC�� ������ �� ������� �����ϸ� �ȴ�.
        �޸�DC�� ���� ���� ���� �����̶��, ��Ʈ���� ���� ���ϴ� �������
        ���̰� �ϴ� �����̴�.
        ��Ʈ���� ����� �޸�DC�� �־��ָ�, ���������� ���ϴ� ����� ����(�޸�DC)�� �����ȴ�.
        ���� �޸�DC�� �̿��� �̹����� ������ �� �� �ִ�.
    */
    HDC hMemDC;       // �޸� DC
    HBITMAP hBmp;     // ��Ʈ��
    HBITMAP hPrevBmp; // DC�� ������ ������ �ִ� ������ ���� �ӽ� ��Ʈ��
    BITMAP  bmpInfo;  // ��Ʈ���� ������ ��� ����ü

    /*
        colorKey : �ؽ��Ŀ��� ���ϴ� ������ �����ϰ� ����ϴ� ���̴�.
        ���� �� ���� �ʴ� ����Ÿ(255,0,255) ������ �÷�Ű�� �����Ѵ�.
        
        �ؽ����� ����� ����Ÿ �������� �����, ����� ������ ���� 
        �ʿ��� �ؽ��ĸ� ��� �� ���̴�.
    */
    COLORREF colorKey;      // �÷� Ű ����
    bool enableColorKey;    // �÷� Ű Ȱ��ȭ ����

    ImageInfo()
        : hMemDC(0)
        , hBmp(0)
        , hPrevBmp()
        , bmpInfo{}
        , colorKey(RGB(255, 0, 255))
        , enableColorKey(false)
    {}

    ~ImageInfo()
    {
        // �޸� DC�� ���� ������ �ִ� ������ �����ش�.
        SelectObject(hMemDC, hPrevBmp);
        // ��Ʈ���� �����Ѵ�.
        DeleteObject(hBmp);
        // �޸� DC�� �����Ѵ�.
        DeleteDC(hMemDC);
    }
};

/*
    �ؽ��Ŀ� ���� ���ҽ����� �����ؼ� ����� ���� �����Ƿ�,
    ���۷��� ī��Ʈ�� �����ϸ� ����ϴ°� ����.
    ���� ���۷��� Ŭ������ ����Ѵ�.
*/
class CTexture :
    public CRef
{
private:
    ETextureType m_type;    // �ؽ����� Ÿ�� (sprite or frame)
    std::vector<ImageInfo*> m_vecImageInfo;     // �̹����� dc, ��Ʈ�� �� ����.
public:
    HDC GetDC(int _index = 0) const;
    bool GetEnableColorKey(int _index = 0) const;
    COLORREF GetColorKey(int _index = 0) const;
    ETextureType GetTextureType() const;

    // �ϳ��� �̹����� �ؽ��ĸ� �����ϴ� ��� -> sprite
    bool LoadTexture(const TCHAR* _fileName,
        const std::string& _pathName = TEXTURE_PATH);
    // ó������ ������ ���(Full Path)�� �̿��� �ؽ��ĸ� �ε��� ���
    bool LoadTextureFullPath(const TCHAR* _fullPath);

#ifdef UNICODE
    // ���� �̹����� �ؽ��ĸ� �����ϴ� ��� -> frame (�����ڵ� ȯ��), wstring : 2byte string
    bool LoadTexture(const std::vector<std::wstring>& _vecFileName,
        const std::string& _pathName = TEXTURE_PATH);
    // ó������ ������ ���(Full Path)�� �̿��� �ؽ��ĸ� �ε��� ���
    bool LoadTextureFullPath(const std::vector<std::wstring>& _vecFullPath);

#else
    // ���� �̹����� �ؽ��ĸ� �����ϴ� ��� -> frame (��Ƽ����Ʈ ȯ��)
    bool LoadTexture(const std::vector<std::string>& _vecFileName,
        const std::string& _pathName = TEXTURE_PATH);
    // ó������ ������ ���(Full Path)�� �̿��� �ؽ��ĸ� �ε��� ���
    bool LoadTextureFullPath(const std::vector<std::string>& _vecFullPath);

#endif // UNICODE

    void SetColorKey(unsigned char _r, unsigned char _g, unsigned char _b,
        int _index = 0);
    void SetColorKeyAll(unsigned char _r, unsigned char _g, unsigned char _b);

private:
    CTexture();
    ~CTexture();

    friend class CTextureManager;
};

