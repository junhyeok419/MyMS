#pragma once
#include "../../Ref.h"

/*
    폰트를 로딩해서 사용할 수 있도록 하는, 각각의 폰트를 담은 클래스이다.
    폰트 관련은 api에서 제공하는 정해진 방식으로 한다.
*/
class CFont :
    public CRef
{
private:
    LOGFONT m_fontInfo;     // 폰트 정보
    HFONT   m_hFont;        // 폰트 핸들
    HFONT   m_hPrevFont;    // 이전 폰트 핸들
public:
    // 폰트를 로드한다. / 폰트 파일 없이 직접 info를 작성하여 로드한다.
    bool LoadFont(const TCHAR* _fontName, int _width, int _height);
    // 인자의 DC에 폰트 지정을 요청한다.
    void SetFont(HDC _hDC);
    // 인자의 DC에 지정된 폰트를 되돌린다.
    void ResetFont(HDC _hDC);
private:
    CFont();
    ~CFont();

    friend class CFontManager;
};

