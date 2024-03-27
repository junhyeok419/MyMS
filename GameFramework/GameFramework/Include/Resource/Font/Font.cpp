#include "Font.h"

bool CFont::LoadFont(const TCHAR* _fontName, int _width, int _height)
{
    /*
    폰트 굵기에 대한 매크로
    #define FW_DONTCARE         0
    #define FW_THIN             100
    #define FW_EXTRALIGHT       200
    #define FW_LIGHT            300
    #define FW_NORMAL           400
    #define FW_MEDIUM           500
    #define FW_SEMIBOLD         600
    #define FW_BOLD             700
    #define FW_EXTRABOLD        800
    #define FW_HEAVY            900
    */
    m_fontInfo.lfWidth = (LONG)_width;
    m_fontInfo.lfHeight = (LONG)_height;
    m_fontInfo.lfCharSet = HANGEUL_CHARSET; // 문자 세트(한국어)
    m_fontInfo.lfWeight = FW_NORMAL;    // 굵기
    m_fontInfo.lfItalic = 0;            // 기울기
    m_fontInfo.lfEscapement = 1;        // 방향
    m_fontInfo.lfUnderline = 0;         // 밑줄
    m_fontInfo.lfStrikeOut = 0;         // 취소선
    m_fontInfo.lfPitchAndFamily = 2;    // 자간 (2가 적당함)

    lstrcpy(m_fontInfo.lfFaceName, _fontName);  // 폰트 이름 복사해줌

    
    // 위에서 만들어준 폰트 정보를 전달하여 hFont를 채운다.
    m_hFont = CreateFontIndirect(&m_fontInfo);  

    return m_hFont == nullptr ? false : true;
}

void CFont::SetFont(HDC _hDC)
{
    m_hPrevFont = (HFONT)SelectObject(_hDC, m_hFont);
}

void CFont::ResetFont(HDC _hDC)
{
    SelectObject(_hDC, m_hPrevFont);
}

CFont::CFont()
	: m_fontInfo{}
	 ,m_hFont(0)
	 ,m_hPrevFont(0)
{
}

CFont::~CFont()
{
	if (m_hFont)
		DeleteObject(m_hFont);
}
