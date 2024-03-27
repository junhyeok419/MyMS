#include "FontManager.h"
#include "Font.h"
#include "../../PathManager.h"

bool CFontManager::Init()
{
	// ��Ʈ������ �ε��Ѵ�.
	LoadFont(TEXT("NotoSansKR-Black.otf"));

	// ������ ������ ��Ʈ�� ����Ʈ��Ʈ�� �����Ѵ�.
	LoadFont("DefaultFont", TEXT("NotoSansKR-Black.otf"), 0, 0);

	return true;
}

bool CFontManager::LoadFont(const std::string& _name, const TCHAR* _fontName, int _width, int _height)
{
	// Ű(_name)�� �ش��ϴ� ��Ʈ�� �̹� �ִٸ� �����Ѵ�.
	CFont* font = FindFont(_name);

	if (font)
		return true;

	// ��Ʈ ��ü�� �����Ѵ�.
	font = new CFont;

	// ���۷��� �̸��� �����Ѵ�.
	font->SetName(_name);

	// ��Ʈ�� �ε��Ѵ�.
	if (!font->LoadFont(_fontName, _width, _height))
	{
		SAFE_DELETE(font);
		return false;
	}

	// ��Ʈ�� �ʿ� �߰��Ѵ�.
	m_mapFont.insert(std::make_pair(_name, font));

	return true;
}

bool CFontManager::LoadFont(const TCHAR* _fontFileName, const std::string& _pathName)
{
	// ������ ��θ� �ޱ� ���� �� ���ڿ��� �����Ѵ�.
	TCHAR	fullPath[MAX_PATH] = {};

	// �⺻ ��Ʈ ��θ� �޾ƿ´�.
	const PathInfo* info = CPathManager::GetInst()->FindPath(FONT_PATH);

	// �⺻ ��Ʈ ��θ� �� ���ڿ��� �����Ѵ�.
	if (info)
		lstrcpy(fullPath, info->path);

	// ��Ʈ ������ �̸��� ���ٿ��ָ�, ������ ��ΰ� �����ȴ�.
	lstrcat(fullPath, _fontFileName);

	// ������ ��θ� ������ ��Ʈ�� �߰��Ͽ� ������ �� �� �ְ� �����.
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
