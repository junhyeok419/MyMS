#pragma once

#include "../SingletonMacro.h"
#include "../GameInfo.h"

class CResourceManager
{
	DECLARE_SINGLE(CResourceManager)
private:
	class CTextureManager* m_textureManager;
	class CAnimationManager* m_animationManager;
	class CSoundManager* m_soundManager;
	class CFontManager* m_fontManager;
public:
	bool Init();
	// 리소스를 갱신할 경우를 대비해 만들어놓는다.
	void Update();	

public: // ========================= Texture ============================
	// 하나의 이미지로 텍스쳐를 구성하는 경우 -> sprite
	bool LoadTexture(const std::string& _name, const TCHAR* _fileName,
		const std::string& _pathName = TEXTURE_PATH);
	// 처음부터 완전한 경로(Full Path)를 이용해 텍스쳐를 로드할 경우
	bool LoadTextureFullPath(const std::string& _name, const TCHAR* _fullPath);

#ifdef UNICODE
	// 여러 이미지로 텍스쳐를 구성하는 경우 -> frame (유니코드 환경), wstring : 2byte string
	bool LoadTexture(const std::string& _name, const std::vector<std::wstring>& _vecFileName,
		const std::string& _pathName = TEXTURE_PATH);
	// 처음부터 완전한 경로(Full Path)를 이용해 텍스쳐를 로드할 경우
	bool LoadTextureFullPath(const std::string& _name, const std::vector<std::wstring>& _vecFullPath);

#else
	// 여러 이미지로 텍스쳐를 구성하는 경우 -> frame (멀티바이트 환경)
	bool LoadTexture(const std::string& _name, const std::vector<std::string>& _vecFileName,
		const std::string& _pathName = TEXTURE_PATH);
	// 처음부터 완전한 경로(Full Path)를 이용해 텍스쳐를 로드할 경우
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

public: // =================== Animation Sequence ========================
	// 한 개의 텍스쳐로 바로 애니메이션 시퀀스를 등록하는 경우 -> sprite
	bool CreateAnimationSequence(const std::string& _name, class CTexture* _texture);
	// 한 개의 텍스쳐를 키(_name)를 이용해 찾고 애니메이션 시퀀스를 등록하는 경우
	bool CreateAnimationSequence(const std::string& _name, const std::string& _texName);
	// 한 개의 텍스쳐를 로딩하고 애니메이션 시퀀스를 등록하는 경우
	bool CreateAnimationSequence(const std::string& _name, const std::string& _texName,
		const TCHAR* _fileName, const std::string& _pathName);
	// 완전한 경로로 한 개의 텍스쳐를 로딩하고 애니메이션 시퀀스를 등록하는 경우
	bool CreateAnimationSequenceFullPath(const std::string& _name, const std::string& _texName,
		const TCHAR* _fullPath);

#ifdef UNICODE

	// 여러 개의 텍스쳐를 로딩하고 애니메이션 시퀀스를 등록하는 경우 -> frame (유니코드 환경)
	bool CreateAnimationSequence(const std::string& _name, const std::string& _texName,
		const std::vector<std::wstring>& _vecFileName, const std::string& _pathName);
	// 완전한 경로로 여러 개의 텍스쳐를 로딩하고 애니메이션 시퀀스를 등록하는 경우
	bool CreateAnimationSequenceFullPath(const std::string& _name, const std::string& _texName,
		const std::vector<std::wstring>& _vecFullPath);

#else

	// 여러 개의 텍스쳐를 로딩하고 애니메이션 시퀀스를 등록하는 경우 -> frame (멀티바이트 환경)
	bool CreateAnimationSequence(const std::string& _name, const std::string& _texName,
		const std::vector<std::string>& _vecFileName, const std::string& _pathName);
	// 완전한 경로로 여러 개의 텍스쳐를 로딩하고 애니메이션 시퀀스를 등록하는 경우
	bool CreateAnimationSequenceFullPath(const std::string& _name, const std::string& _texName,
		const std::vector<std::string>& _vecFullPath);

#endif // UNICODE

	bool AddAnimationFrame(const std::string& _name, const Vector2& _start,
		const Vector2& _end);
	bool AddAnimationFrame(const std::string& _name,
		float _posX, float _posY, float _sizeX, float _sizeY);
	bool AddAnimationFramePivot(const std::string& _name, const Vector2& _pivot);
	bool AddAnimationFramePivot(const std::string& _name, float _pivotX, float _pivotY);

	class CAnimationSequence* FindAnimation(const std::string& _name);
	void ReleaseAnimation(const std::string& _name);

public: // ============================ Sound ================================
	// 새로운 채널 그룹을 만든다.
	bool CreateSoundChannel(const std::string& _name);
	// 채널 그룹을 찾는다.
	FMOD::ChannelGroup* FindChannelGroup(const std::string& _name);
	// 사운드를 찾는다.
	class CSound* FindSound(const std::string& _name);
	// 사운드를 로드한다.
	bool LoadSound(const std::string& _groupName, const std::string& _name,
		bool _loop, const char* _fileName, const std::string& _pathName = SOUND_PATH);
	void ReleaseSound(const std::string& _name);
public:
	// 마스터 그룹(전체 그룹) 볼륨 조절
	bool SetVolume(int _volume);
	// 그룹별 볼륨 조절
	bool SetVolume(const std::string& _groupName, int _volume);
	// 원하는 사운드 재생
	bool SoundPlay(const std::string& _name);
	// 원하는 사운드 중지
	bool SoundStop(const std::string& _name);
	// 원하는 사운드 일시정지
	bool SoundPause(const std::string& _name);
	// 원하는 사운드 재개
	bool SoundResume(const std::string& _name);

public:	// =========================== Font ==============================
	bool LoadFont(const std::string& _name, const TCHAR* _fontName,
		int _width, int _height);
	bool LoadFont(const TCHAR* _fontFileName,
		const std::string& _pathName = FONT_PATH);
	void SetFont(const std::string& _name, HDC _hDC);
	void ResetFont(const std::string& _name, HDC _hDC);
	class CFont* FindFont(const std::string& _name);
	void ReleaseFont(const std::string& _name);
};