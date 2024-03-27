#include "TextureManager.h"
#include "Texture.h"

bool CTextureManager::Init()
{
	return true;
}

/*
	LoadTexture : 텍스쳐(이미지)를 로드한다. 
	-> 리소스 파일을 가져와 텍스쳐 map에 넣는다.

	1. 텍스쳐 이름(별칭) 
	2. 실제 파일 이름 
	3. PATH 이름 (default : TexturePath)
*/
bool CTextureManager::LoadTexture(const std::string& _name, const TCHAR* _fileName, 
	const std::string& _pathName)
{
	// 같은 이름으로 저장된 텍스쳐가 이미 있다면 리턴한다.
	CTexture* texture = FindTexture(_name);

	if (texture)
		return true;

	// 텍스쳐 객체를 생성한다.
	texture = new CTexture;

	// 텍스쳐 객체에 텍스쳐를 로드한다.
	if (!texture->LoadTexture(_fileName, _pathName))
	{
		// 실패했다면 지운다.
		SAFE_RELEASE(texture);
		return false;
	}

	// 텍스쳐 로드가 완료된 텍스쳐 객체를 map에 추가한다.
	m_mapTexture.insert(std::make_pair(_name, texture));

	return true;
}

bool CTextureManager::LoadTextureFullPath(const std::string& _name, const TCHAR* _fullPath)
{
	// 같은 이름으로 저장된 텍스쳐가 이미 있다면 리턴한다.
	CTexture* texture = FindTexture(_name);

	if (texture)
		return true;

	// 텍스쳐 객체를 생성한다.
	texture = new CTexture;

	// 텍스쳐 객체에 텍스쳐를 로드한다.
	if (!texture->LoadTextureFullPath(_fullPath))
	{
		// 실패했다면 지운다.
		SAFE_RELEASE(texture);
		return false;
	}

	// 텍스쳐 로드가 완료된 텍스쳐 객체를 map에 추가한다.
	m_mapTexture.insert(std::make_pair(_name, texture));

	return true;
}

#ifdef UNICODE

bool CTextureManager::LoadTexture(const std::string& _name, const std::vector<std::wstring>& _vecFileName, const std::string& _pathName)
{
	// 같은 이름으로 저장된 텍스쳐가 이미 있다면 리턴한다.
	CTexture* texture = FindTexture(_name);

	if (texture)
		return true;

	// 텍스쳐 객체를 생성한다.
	texture = new CTexture;

	// 텍스쳐 객체에 텍스쳐를 로드한다.
	if (!texture->LoadTexture(_vecFileName, _pathName))
	{
		// 실패했다면 지운다.
		SAFE_RELEASE(texture);
		return false;
	}

	// 텍스쳐 로드가 완료된 텍스쳐 객체를 map에 추가한다.
	m_mapTexture.insert(std::make_pair(_name, texture));

	return true;
}

bool CTextureManager::LoadTextureFullPath(const std::string& _name, const std::vector<std::wstring>& _vecFullPath)
{
	// 같은 이름으로 저장된 텍스쳐가 이미 있다면 리턴한다.
	CTexture* texture = FindTexture(_name);

	if (texture)
		return true;

	// 텍스쳐 객체를 생성한다.
	texture = new CTexture;

	// 텍스쳐 객체에 텍스쳐를 로드한다.
	if (!texture->LoadTexture(_vecFullPath))
	{
		// 실패했다면 지운다.
		SAFE_RELEASE(texture);
		return false;
	}

	// 텍스쳐 로드가 완료된 텍스쳐 객체를 map에 추가한다.
	m_mapTexture.insert(std::make_pair(_name, texture));

	return true;
}

#else

bool CTextureManager::LoadTexture(const std::string& _name, const std::vector<std::string>& _vecFileName, const std::string& _pathName)
{
	// 같은 이름으로 저장된 텍스쳐가 이미 있다면 리턴한다.
	CTexture* texture = FindTexture(_name);

	if (texture)
		return true;

	// 텍스쳐 객체를 생성한다.
	texture = new CTexture;

	// 텍스쳐 객체에 텍스쳐를 로드한다.
	if (!texture->LoadTexture(_vecFileName, _pathName))
	{
		// 실패했다면 지운다.
		SAFE_RELEASE(texture);
		return false;
	}

	// 텍스쳐 로드가 완료된 텍스쳐 객체를 map에 추가한다.
	m_mapTexture.insert(std::make_pair(_name, texture));

	return true;
}

bool CTextureManager::LoadTextureFullPath(const std::string& _name, const std::vector<std::string>& _vecFullPath)
{
	// 같은 이름으로 저장된 텍스쳐가 이미 있다면 리턴한다.
	CTexture* texture = FindTexture(_name);

	if (texture)
		return true;

	// 텍스쳐 객체를 생성한다.
	texture = new CTexture;

	// 텍스쳐 객체에 텍스쳐를 로드한다.
	if (!texture->LoadTexture(_vecFullPath))
	{
		// 실패했다면 지운다.
		SAFE_RELEASE(texture);
		return false;
	}

	// 텍스쳐 로드가 완료된 텍스쳐 객체를 map에 추가한다.
	m_mapTexture.insert(std::make_pair(_name, texture));

	return true;
}

#endif // UNICODE

CTexture* CTextureManager::FindTexture(const std::string& _name)
{
	auto iter = m_mapTexture.find(_name);

	if(iter == m_mapTexture.end())
		return nullptr;

	return iter->second;
}

void CTextureManager::ReleaseTexture(const std::string& _name)
{
	auto iter = m_mapTexture.find(_name);

	if (iter == m_mapTexture.end())
		return;

	// 텍스쳐의 레퍼런스 카운트가 1이라면 완전 삭제한다. 
	if (iter->second->GetRefCount() == 1)
		m_mapTexture.erase(iter);
}

bool CTextureManager::SetColorKey(const std::string& _name, unsigned char _r, unsigned char _g, unsigned char _b, int _index)
{
	// 키에 해당하는 텍스쳐를 찾는다.
	CTexture* texture = FindTexture(_name);

	// 없다면 나간다.
	if (!texture)
		return false;

	// 해당 텍스쳐의 컬러키를 변경해준다.
	texture->SetColorKey(_r, _g, _b);

	return true;
}

bool CTextureManager::SetColorKeyAll(const std::string& _name, unsigned char _r, unsigned char _g, unsigned char _b)
{
	// 키에 해당하는 텍스쳐를 찾는다.
	CTexture* texture = FindTexture(_name);

	// 없다면 나간다.
	if (!texture)
		return false;

	// 해당 텍스쳐의 모든 이미지의 컬러키를 변경해준다.
	texture->SetColorKeyAll(_r, _g, _b);

	return true;
}

CTextureManager::CTextureManager()
{
}

CTextureManager::~CTextureManager()
{
}
