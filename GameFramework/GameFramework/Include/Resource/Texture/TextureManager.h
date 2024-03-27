#pragma once

#include "../../GameInfo.h"

class CTextureManager
{
private:
	// ���� ������ Ÿ������ �ؽ��� map�� ���´�.
	std::unordered_map<std::string, CSharedPtr<class CTexture>> m_mapTexture;
public:
	bool Init();

	// �ؽ��ĸ� �ε��Ѵ�(�̹����� �����´�).
	bool LoadTexture(const std::string& _name, const TCHAR* _fileName,
		const std::string& _pathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& _name, const TCHAR* _fullPath);

#ifdef UNICODE

	bool LoadTexture(const std::string& _name, const std::vector<std::wstring>& _vecFileName,
		const std::string& _pathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& _name, const std::vector<std::wstring>& _vecFullPath);

#else

	bool LoadTexture(const std::string& _name, const std::vector<std::string>& _vecFileName,
		const std::string& _pathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& _name, const std::vector<std::string>& _vecFullPath);

#endif // UNICODE

	// Ű�� �ش��ϴ� �ؽ��ĸ� �ʿ��� ã�´�.
	class CTexture* FindTexture(const std::string& _name);
	// Ű�� �ش��ϴ� �ؽ��ĸ� �����Ѵ�.
	void ReleaseTexture(const std::string& _name);

	// Ű�� �ش��ϴ� �ؽ����� �̹����� �÷�Ű�� �����Ѵ�.
	bool SetColorKey(const std::string& _name,
		unsigned char _r, unsigned char _g, unsigned char _b, int _index = 0);
	// Ű�� �ش��ϴ� �ؽ����� ��� �̹����� �÷�Ű�� �����Ѵ�.
	bool SetColorKeyAll(const std::string& _name,
		unsigned char _r, unsigned char _g, unsigned char _b);
private:
	CTextureManager();
	~CTextureManager();

	friend class CResourceManager;
};

