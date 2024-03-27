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
	// ���ҽ��� ������ ��츦 ����� �������´�.
	void Update();	

public: // ========================= Texture ============================
	// �ϳ��� �̹����� �ؽ��ĸ� �����ϴ� ��� -> sprite
	bool LoadTexture(const std::string& _name, const TCHAR* _fileName,
		const std::string& _pathName = TEXTURE_PATH);
	// ó������ ������ ���(Full Path)�� �̿��� �ؽ��ĸ� �ε��� ���
	bool LoadTextureFullPath(const std::string& _name, const TCHAR* _fullPath);

#ifdef UNICODE
	// ���� �̹����� �ؽ��ĸ� �����ϴ� ��� -> frame (�����ڵ� ȯ��), wstring : 2byte string
	bool LoadTexture(const std::string& _name, const std::vector<std::wstring>& _vecFileName,
		const std::string& _pathName = TEXTURE_PATH);
	// ó������ ������ ���(Full Path)�� �̿��� �ؽ��ĸ� �ε��� ���
	bool LoadTextureFullPath(const std::string& _name, const std::vector<std::wstring>& _vecFullPath);

#else
	// ���� �̹����� �ؽ��ĸ� �����ϴ� ��� -> frame (��Ƽ����Ʈ ȯ��)
	bool LoadTexture(const std::string& _name, const std::vector<std::string>& _vecFileName,
		const std::string& _pathName = TEXTURE_PATH);
	// ó������ ������ ���(Full Path)�� �̿��� �ؽ��ĸ� �ε��� ���
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

public: // =================== Animation Sequence ========================
	// �� ���� �ؽ��ķ� �ٷ� �ִϸ��̼� �������� ����ϴ� ��� -> sprite
	bool CreateAnimationSequence(const std::string& _name, class CTexture* _texture);
	// �� ���� �ؽ��ĸ� Ű(_name)�� �̿��� ã�� �ִϸ��̼� �������� ����ϴ� ���
	bool CreateAnimationSequence(const std::string& _name, const std::string& _texName);
	// �� ���� �ؽ��ĸ� �ε��ϰ� �ִϸ��̼� �������� ����ϴ� ���
	bool CreateAnimationSequence(const std::string& _name, const std::string& _texName,
		const TCHAR* _fileName, const std::string& _pathName);
	// ������ ��η� �� ���� �ؽ��ĸ� �ε��ϰ� �ִϸ��̼� �������� ����ϴ� ���
	bool CreateAnimationSequenceFullPath(const std::string& _name, const std::string& _texName,
		const TCHAR* _fullPath);

#ifdef UNICODE

	// ���� ���� �ؽ��ĸ� �ε��ϰ� �ִϸ��̼� �������� ����ϴ� ��� -> frame (�����ڵ� ȯ��)
	bool CreateAnimationSequence(const std::string& _name, const std::string& _texName,
		const std::vector<std::wstring>& _vecFileName, const std::string& _pathName);
	// ������ ��η� ���� ���� �ؽ��ĸ� �ε��ϰ� �ִϸ��̼� �������� ����ϴ� ���
	bool CreateAnimationSequenceFullPath(const std::string& _name, const std::string& _texName,
		const std::vector<std::wstring>& _vecFullPath);

#else

	// ���� ���� �ؽ��ĸ� �ε��ϰ� �ִϸ��̼� �������� ����ϴ� ��� -> frame (��Ƽ����Ʈ ȯ��)
	bool CreateAnimationSequence(const std::string& _name, const std::string& _texName,
		const std::vector<std::string>& _vecFileName, const std::string& _pathName);
	// ������ ��η� ���� ���� �ؽ��ĸ� �ε��ϰ� �ִϸ��̼� �������� ����ϴ� ���
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
	// ���ο� ä�� �׷��� �����.
	bool CreateSoundChannel(const std::string& _name);
	// ä�� �׷��� ã�´�.
	FMOD::ChannelGroup* FindChannelGroup(const std::string& _name);
	// ���带 ã�´�.
	class CSound* FindSound(const std::string& _name);
	// ���带 �ε��Ѵ�.
	bool LoadSound(const std::string& _groupName, const std::string& _name,
		bool _loop, const char* _fileName, const std::string& _pathName = SOUND_PATH);
	void ReleaseSound(const std::string& _name);
public:
	// ������ �׷�(��ü �׷�) ���� ����
	bool SetVolume(int _volume);
	// �׷캰 ���� ����
	bool SetVolume(const std::string& _groupName, int _volume);
	// ���ϴ� ���� ���
	bool SoundPlay(const std::string& _name);
	// ���ϴ� ���� ����
	bool SoundStop(const std::string& _name);
	// ���ϴ� ���� �Ͻ�����
	bool SoundPause(const std::string& _name);
	// ���ϴ� ���� �簳
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