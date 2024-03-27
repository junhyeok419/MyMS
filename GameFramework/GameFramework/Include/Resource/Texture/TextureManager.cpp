#include "TextureManager.h"
#include "Texture.h"

bool CTextureManager::Init()
{
	return true;
}

/*
	LoadTexture : �ؽ���(�̹���)�� �ε��Ѵ�. 
	-> ���ҽ� ������ ������ �ؽ��� map�� �ִ´�.

	1. �ؽ��� �̸�(��Ī) 
	2. ���� ���� �̸� 
	3. PATH �̸� (default : TexturePath)
*/
bool CTextureManager::LoadTexture(const std::string& _name, const TCHAR* _fileName, 
	const std::string& _pathName)
{
	// ���� �̸����� ����� �ؽ��İ� �̹� �ִٸ� �����Ѵ�.
	CTexture* texture = FindTexture(_name);

	if (texture)
		return true;

	// �ؽ��� ��ü�� �����Ѵ�.
	texture = new CTexture;

	// �ؽ��� ��ü�� �ؽ��ĸ� �ε��Ѵ�.
	if (!texture->LoadTexture(_fileName, _pathName))
	{
		// �����ߴٸ� �����.
		SAFE_RELEASE(texture);
		return false;
	}

	// �ؽ��� �ε尡 �Ϸ�� �ؽ��� ��ü�� map�� �߰��Ѵ�.
	m_mapTexture.insert(std::make_pair(_name, texture));

	return true;
}

bool CTextureManager::LoadTextureFullPath(const std::string& _name, const TCHAR* _fullPath)
{
	// ���� �̸����� ����� �ؽ��İ� �̹� �ִٸ� �����Ѵ�.
	CTexture* texture = FindTexture(_name);

	if (texture)
		return true;

	// �ؽ��� ��ü�� �����Ѵ�.
	texture = new CTexture;

	// �ؽ��� ��ü�� �ؽ��ĸ� �ε��Ѵ�.
	if (!texture->LoadTextureFullPath(_fullPath))
	{
		// �����ߴٸ� �����.
		SAFE_RELEASE(texture);
		return false;
	}

	// �ؽ��� �ε尡 �Ϸ�� �ؽ��� ��ü�� map�� �߰��Ѵ�.
	m_mapTexture.insert(std::make_pair(_name, texture));

	return true;
}

#ifdef UNICODE

bool CTextureManager::LoadTexture(const std::string& _name, const std::vector<std::wstring>& _vecFileName, const std::string& _pathName)
{
	// ���� �̸����� ����� �ؽ��İ� �̹� �ִٸ� �����Ѵ�.
	CTexture* texture = FindTexture(_name);

	if (texture)
		return true;

	// �ؽ��� ��ü�� �����Ѵ�.
	texture = new CTexture;

	// �ؽ��� ��ü�� �ؽ��ĸ� �ε��Ѵ�.
	if (!texture->LoadTexture(_vecFileName, _pathName))
	{
		// �����ߴٸ� �����.
		SAFE_RELEASE(texture);
		return false;
	}

	// �ؽ��� �ε尡 �Ϸ�� �ؽ��� ��ü�� map�� �߰��Ѵ�.
	m_mapTexture.insert(std::make_pair(_name, texture));

	return true;
}

bool CTextureManager::LoadTextureFullPath(const std::string& _name, const std::vector<std::wstring>& _vecFullPath)
{
	// ���� �̸����� ����� �ؽ��İ� �̹� �ִٸ� �����Ѵ�.
	CTexture* texture = FindTexture(_name);

	if (texture)
		return true;

	// �ؽ��� ��ü�� �����Ѵ�.
	texture = new CTexture;

	// �ؽ��� ��ü�� �ؽ��ĸ� �ε��Ѵ�.
	if (!texture->LoadTexture(_vecFullPath))
	{
		// �����ߴٸ� �����.
		SAFE_RELEASE(texture);
		return false;
	}

	// �ؽ��� �ε尡 �Ϸ�� �ؽ��� ��ü�� map�� �߰��Ѵ�.
	m_mapTexture.insert(std::make_pair(_name, texture));

	return true;
}

#else

bool CTextureManager::LoadTexture(const std::string& _name, const std::vector<std::string>& _vecFileName, const std::string& _pathName)
{
	// ���� �̸����� ����� �ؽ��İ� �̹� �ִٸ� �����Ѵ�.
	CTexture* texture = FindTexture(_name);

	if (texture)
		return true;

	// �ؽ��� ��ü�� �����Ѵ�.
	texture = new CTexture;

	// �ؽ��� ��ü�� �ؽ��ĸ� �ε��Ѵ�.
	if (!texture->LoadTexture(_vecFileName, _pathName))
	{
		// �����ߴٸ� �����.
		SAFE_RELEASE(texture);
		return false;
	}

	// �ؽ��� �ε尡 �Ϸ�� �ؽ��� ��ü�� map�� �߰��Ѵ�.
	m_mapTexture.insert(std::make_pair(_name, texture));

	return true;
}

bool CTextureManager::LoadTextureFullPath(const std::string& _name, const std::vector<std::string>& _vecFullPath)
{
	// ���� �̸����� ����� �ؽ��İ� �̹� �ִٸ� �����Ѵ�.
	CTexture* texture = FindTexture(_name);

	if (texture)
		return true;

	// �ؽ��� ��ü�� �����Ѵ�.
	texture = new CTexture;

	// �ؽ��� ��ü�� �ؽ��ĸ� �ε��Ѵ�.
	if (!texture->LoadTexture(_vecFullPath))
	{
		// �����ߴٸ� �����.
		SAFE_RELEASE(texture);
		return false;
	}

	// �ؽ��� �ε尡 �Ϸ�� �ؽ��� ��ü�� map�� �߰��Ѵ�.
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

	// �ؽ����� ���۷��� ī��Ʈ�� 1�̶�� ���� �����Ѵ�. 
	if (iter->second->GetRefCount() == 1)
		m_mapTexture.erase(iter);
}

bool CTextureManager::SetColorKey(const std::string& _name, unsigned char _r, unsigned char _g, unsigned char _b, int _index)
{
	// Ű�� �ش��ϴ� �ؽ��ĸ� ã�´�.
	CTexture* texture = FindTexture(_name);

	// ���ٸ� ������.
	if (!texture)
		return false;

	// �ش� �ؽ����� �÷�Ű�� �������ش�.
	texture->SetColorKey(_r, _g, _b);

	return true;
}

bool CTextureManager::SetColorKeyAll(const std::string& _name, unsigned char _r, unsigned char _g, unsigned char _b)
{
	// Ű�� �ش��ϴ� �ؽ��ĸ� ã�´�.
	CTexture* texture = FindTexture(_name);

	// ���ٸ� ������.
	if (!texture)
		return false;

	// �ش� �ؽ����� ��� �̹����� �÷�Ű�� �������ش�.
	texture->SetColorKeyAll(_r, _g, _b);

	return true;
}

CTextureManager::CTextureManager()
{
}

CTextureManager::~CTextureManager()
{
}
