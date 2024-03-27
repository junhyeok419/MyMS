#pragma once
#include "../../GameInfo.h"

/*
    여러 폰트들을 관리하는 매니저 클래스이다.
	원하는 폰트를 이용한 텍스트의 출력을 위해, 폰트 관련 클래스를 만든다.
*/
class CFontManager
{
private:
	std::unordered_map<std::string, CSharedPtr<class CFont>> m_mapFont;  // 폰트들
public:
	bool Init();
public:
	// 폰트를 로드한다. / 2. 가져온 폰트파일로 폰트 객체를 생성하여 세팅한다.
	bool LoadFont(const std::string& _name, const TCHAR* _fontName,
		int _width, int _height);
	// 폰트파일을 로드한다. / 1. 실제 폰트 파일을 가져와 사용할 수 있게한다.
	bool LoadFont(const TCHAR* _fontFileName,
		const std::string& _pathName = FONT_PATH);
	// 인자의 DC에 키(_name)에 해당하는 폰트 지정을 요청한다.
	void SetFont(const std::string& _name, HDC _hDC);
	// 인자의 DC에 지정된 폰트를 이전으로 되돌린다.
	void ResetFont(const std::string& _name, HDC _hDC);
	// 키(_name)에 해당하는 폰트를 찾는다.
	class CFont* FindFont(const std::string& _name);
	// 키(_name)에 해당하는 폰트를 map에서 지운다. (refCnt가 1일 경우에만 지운다)
	void ReleaseFont(const std::string& _name);
private:
	CFontManager();
	~CFontManager();

	friend class CResourceManager;
};

