#include "Font.h"

bool CFont::LoadFont(const TCHAR* _fontName, int _width, int _height)
{
    /*
    ��Ʈ ���⿡ ���� ��ũ��
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
    m_fontInfo.lfCharSet = HANGEUL_CHARSET; // ���� ��Ʈ(�ѱ���)
    m_fontInfo.lfWeight = FW_NORMAL;    // ����
    m_fontInfo.lfItalic = 0;            // ����
    m_fontInfo.lfEscapement = 1;        // ����
    m_fontInfo.lfUnderline = 0;         // ����
    m_fontInfo.lfStrikeOut = 0;         // ��Ҽ�
    m_fontInfo.lfPitchAndFamily = 2;    // �ڰ� (2�� ������)

    lstrcpy(m_fontInfo.lfFaceName, _fontName);  // ��Ʈ �̸� ��������

    
    // ������ ������� ��Ʈ ������ �����Ͽ� hFont�� ä���.
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
