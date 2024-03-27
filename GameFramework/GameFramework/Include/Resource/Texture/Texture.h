#pragma once
#include "../../Ref.h"

/*
    이미지 로딩에서, 지금처럼 1장의 이미지만을 로딩하는 경우도 있지만
    여러 장의 이미지로 하나의 애니메이션을 표현해야 하는 경우도 있을 수 
    있다.

    따라서 dc와 비트맵 등도 여러개여야 하므로, 이들을 묶어서 구조체로 
    만든 뒤 텍스쳐 클래스에서 이 구조체를 벡터로 들고있게 할 것이다.
*/
struct ImageInfo
{
    /*
        이전까지 사용했던 DC는 화면에 직접 그려내는 dc였다.
        이제 사용할 메모리DC는 비어있는 DC이다.
        메모리DC에 이미지를 채워서 마치 '도장'처럼 찍어낼 수 있게 한다.

        비트맵은 메모리DC에 도장을 팔 도구라고 생각하면 된다.
        메모리DC가 아직 파지 않은 도장이라면, 비트맵은 내가 원하는 모양으로
        파이게 하는 도구이다.
        비트맵을 만들어 메모리DC에 넣어주면, 최종적으로 원하는 모양의 도장(메모리DC)이 생성된다.
        이후 메모리DC를 이용해 이미지를 찍어내듯이 할 수 있다.
    */
    HDC hMemDC;       // 메모리 DC
    HBITMAP hBmp;     // 비트맵
    HBITMAP hPrevBmp; // DC가 기존에 가지고 있던 도구를 담을 임시 비트맵
    BITMAP  bmpInfo;  // 비트맵의 정보를 담는 구조체

    /*
        colorKey : 텍스쳐에서 원하는 색상을 제외하고 출력하는 것이다.
        보통 잘 쓰지 않는 마젠타(255,0,255) 색상을 컬러키로 지정한다.
        
        텍스쳐의 배경을 마젠타 색상으로 만들면, 배경을 제외한 실제 
        필요한 텍스쳐만 출력 될 것이다.
    */
    COLORREF colorKey;      // 컬러 키 색상
    bool enableColorKey;    // 컬러 키 활성화 여부

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
        // 메모리 DC가 원래 가지고 있던 도구를 돌려준다.
        SelectObject(hMemDC, hPrevBmp);
        // 비트맵을 삭제한다.
        DeleteObject(hBmp);
        // 메모리 DC를 삭제한다.
        DeleteDC(hMemDC);
    }
};

/*
    텍스쳐와 같은 리소스들은 공유해서 사용할 일이 많으므로,
    레퍼런스 카운트로 관리하며 사용하는게 낫다.
    따라서 레퍼런스 클래스를 상속한다.
*/
class CTexture :
    public CRef
{
private:
    ETextureType m_type;    // 텍스쳐의 타입 (sprite or frame)
    std::vector<ImageInfo*> m_vecImageInfo;     // 이미지의 dc, 비트맵 등 정보.
public:
    HDC GetDC(int _index = 0) const;
    bool GetEnableColorKey(int _index = 0) const;
    COLORREF GetColorKey(int _index = 0) const;
    ETextureType GetTextureType() const;

    // 하나의 이미지로 텍스쳐를 구성하는 경우 -> sprite
    bool LoadTexture(const TCHAR* _fileName,
        const std::string& _pathName = TEXTURE_PATH);
    // 처음부터 완전한 경로(Full Path)를 이용해 텍스쳐를 로드할 경우
    bool LoadTextureFullPath(const TCHAR* _fullPath);

#ifdef UNICODE
    // 여러 이미지로 텍스쳐를 구성하는 경우 -> frame (유니코드 환경), wstring : 2byte string
    bool LoadTexture(const std::vector<std::wstring>& _vecFileName,
        const std::string& _pathName = TEXTURE_PATH);
    // 처음부터 완전한 경로(Full Path)를 이용해 텍스쳐를 로드할 경우
    bool LoadTextureFullPath(const std::vector<std::wstring>& _vecFullPath);

#else
    // 여러 이미지로 텍스쳐를 구성하는 경우 -> frame (멀티바이트 환경)
    bool LoadTexture(const std::vector<std::string>& _vecFileName,
        const std::string& _pathName = TEXTURE_PATH);
    // 처음부터 완전한 경로(Full Path)를 이용해 텍스쳐를 로드할 경우
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

