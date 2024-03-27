#pragma once
#include "../../Ref.h"

/*
    ��Ʈ�� �ε��ؼ� ����� �� �ֵ��� �ϴ�, ������ ��Ʈ�� ���� Ŭ�����̴�.
    ��Ʈ ������ api���� �����ϴ� ������ ������� �Ѵ�.
*/
class CFont :
    public CRef
{
private:
    LOGFONT m_fontInfo;     // ��Ʈ ����
    HFONT   m_hFont;        // ��Ʈ �ڵ�
    HFONT   m_hPrevFont;    // ���� ��Ʈ �ڵ�
public:
    // ��Ʈ�� �ε��Ѵ�. / ��Ʈ ���� ���� ���� info�� �ۼ��Ͽ� �ε��Ѵ�.
    bool LoadFont(const TCHAR* _fontName, int _width, int _height);
    // ������ DC�� ��Ʈ ������ ��û�Ѵ�.
    void SetFont(HDC _hDC);
    // ������ DC�� ������ ��Ʈ�� �ǵ�����.
    void ResetFont(HDC _hDC);
private:
    CFont();
    ~CFont();

    friend class CFontManager;
};

