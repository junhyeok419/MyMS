#pragma once

#include "../../GameInfo.h"

class CTextureManager
{
private:
	// 공유 포인터 타입으로 텍스쳐 map을 갖는다.
	std::unordered_map<std::string, CSharedPtr<class CTexture>> m_mapTexture;
public:
	bool Init();

	// 텍스쳐를 로드한다(이미지를 가져온다).
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

	// 키에 해당하는 텍스쳐를 맵에서 찾는다.
	class CTexture* FindTexture(const std::string& _name);
	// 키에 해당하는 텍스쳐를 삭제한다.
	void ReleaseTexture(const std::string& _name);

	// 키에 해당하는 텍스쳐의 이미지의 컬러키를 지정한다.
	bool SetColorKey(const std::string& _name,
		unsigned char _r, unsigned char _g, unsigned char _b, int _index = 0);
	// 키에 해당하는 텍스쳐의 모든 이미지의 컬러키를 지정한다.
	bool SetColorKeyAll(const std::string& _name,
		unsigned char _r, unsigned char _g, unsigned char _b);
private:
	CTextureManager();
	~CTextureManager();

	friend class CResourceManager;
};

