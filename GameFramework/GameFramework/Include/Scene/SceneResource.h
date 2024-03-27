#pragma once
#include "../GameInfo.h"
/*
	CSceneResource : �� ������ �ؽ��Ŀ� ���� ���ҽ����� �����ϱ� 
	���ؼ� ���� Ŭ�����̴�.

	A->B�� ���� �Ѿ� �� ��, A�� B�� �������� ����ϴ� �ؽ��ĸ� �����ϰ��
	A���� �ؽ��Ĵ� ��� ������ ���̴�. �̷��� �� ������ ���ҽ��� ������ �� �־�� 
	�ϹǷ�, �� Ŭ������ �ʿ��ϴ�.
*/
class CSceneResource
{
private:
	// ������ �ؽ��ĸ� �����ϹǷ� �翬�� ������ ����� �ؽ���, �ִϸ��̼�, ���带 ����� ���´�.
	std::unordered_map < std::string, CSharedPtr<class CTexture>> m_mapTexture;
	std::unordered_map<std::string, CSharedPtr<class CAnimationSequence>>	m_mapAnimationSequence;
	std::unordered_map<std::string, CSharedPtr<class CSound>>	m_mapSound;
	std::unordered_map<std::string, CSharedPtr<class CFont>>	m_mapFont;
public:		// ==================== Texture ====================
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

	class CTexture* FindTexture(const std::string& _name);

	// Ű�� �ش��ϴ� �ؽ����� �̹����� �÷�Ű�� �����Ѵ�.
	bool SetColorKey(const std::string& _name,
		unsigned char _r, unsigned char _g, unsigned char _b, int _index = 0);
	// Ű�� �ش��ϴ� �ؽ����� ��� �̹����� �÷�Ű�� �����Ѵ�.
	bool SetColorKeyAll(const std::string& _name,
		unsigned char _r, unsigned char _g, unsigned char _b);

public:	   // ==================== Animation Sequence ====================
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

	// �ִϸ��̼� �������� ������ ��ǥ�� ����Ѵ�.
	bool AddAnimationFrame(const std::string& _name, const Vector2& _start,
		const Vector2& _end);
	bool AddAnimationFrame(const std::string& _name,
		float _posX, float _posY, float _sizeX, float _sizeY);
	// �ִϸ��̼� �������� ������ �Ǻ��� ����Ѵ�.
	bool AddAnimationFramePivot(const std::string& _name, const Vector2& _pivot);
	bool AddAnimationFramePivot(const std::string& _name, float _pivotX, float _pivotY);
	
	class CAnimationSequence* FindAnimation(const std::string& _name);

public:	// ============================ Sound ================================
	// ���ο� ä�� �׷��� �����.
	bool CreateSoundChannel(const std::string& _name);
	// ä�� �׷��� ã�´�.
	FMOD::ChannelGroup* FindChannelGroup(const std::string& _name);
	// ���带 ã�´�.
	class CSound* FindSound(const std::string& _name);
	// ���带 �ε��Ѵ�.
	bool LoadSound(const std::string& _groupName, const std::string& _name,
		bool _loop, const char* _fileName, const std::string& _pathName = SOUND_PATH);
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
private:
	CSceneResource();
	~CSceneResource();
	
	friend class CScene;
};

