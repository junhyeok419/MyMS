#include "FontManager.h"
#include "Font.h"
#include "../../PathManager.h"

bool CFontManager::Init()
{
	// 폰트파일을 로딩한다.
	LoadFont(TEXT("NotoSansKR-Black.otf"));

	// 위에서 가져온 폰트를 디폴트폰트로 지정한다.
	LoadFont("DefaultFont", TEXT("NotoSansKR-Black.otf"), 0, 0);

	return true;
}

bool CFontManager::LoadFont(const std::string& _name, const TCHAR* _fontName, int _width, int _height)
{
	// 키(_name)에 해당하는 폰트가 이미 있다면 리턴한다.
	CFont* font = FindFont(_name);

	if (font)
		return true;

	// 폰트 객체를 생성한다.
	font = new CFont;

	// 레퍼런스 이름을 지정한다.
	font->SetName(_name);

	// 폰트를 로드한다.
	if (!font->LoadFont(_fontName, _width, _height))
	{
		SAFE_DELETE(font);
		return false;
	}

	// 폰트를 맵에 추가한다.
	m_mapFont.insert(std::make_pair(_name, font));

	return true;
}

bool CFontManager::LoadFont(const TCHAR* _fontFileName, const std::string& _pathName)
{
	// 완전한 경로를 받기 위한 빈 문자열을 생성한다.
	TCHAR	fullPath[MAX_PATH] = {};

	// 기본 폰트 경로를 받아온다.
	const PathInfo* info = CPathManager::GetInst()->FindPath(FONT_PATH);

	// 기본 폰트 경로를 빈 문자열에 복사한다.
	if (info)
		lstrcpy(fullPath, info->path);

	// 폰트 파일의 이름을 덧붙여주면, 완전한 경로가 생성된다.
	lstrcat(fullPath, _fontFileName);

	// 완전한 경로를 전달해 폰트를 추가하여 가져다 쓸 수 있게 만든다.
	AddFontResource(fullPath);

	return true;
}

void CFontManager::SetFont(const std::string& _name, HDC _hDC)
{
	CFont* font = FindFont(_name);

	if (!font)
		return;

	font->SetFont(_hDC);
}

void CFontManager::ResetFont(const std::string& _name, HDC _hDC)
{
	CFont* font = FindFont(_name);

	if (!font)
		return;

	font->ResetFont(_hDC);
}

CFont* CFontManager::FindFont(const std::string& _name)
{
	auto	iter = m_mapFont.find(_name);

	if (iter == m_mapFont.end())
		return nullptr;

	return iter->second;
}

void CFontManager::ReleaseFont(const std::string& _name)
{
	auto	iter = m_mapFont.find(_name);

	if (iter == m_mapFont.end())
		return;

	if (iter->second->GetRefCount() == 1)
		m_mapFont.erase(iter);
}

CFontManager::CFontManager()
{
}

CFontManager::~CFontManager()
{
}
