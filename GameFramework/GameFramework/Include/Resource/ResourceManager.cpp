#include "ResourceManager.h"
#include "Texture/TextureManager.h"
#include "Animation/AnimationManager.h"
#include "Sound/SoundManager.h"
#include "Font/FontManager.h"

DEFINITION_SINGLE(CResourceManager)

bool CResourceManager::Init()
{
	return true;
}

void CResourceManager::Update()
{
	m_soundManager->Update();
}

bool CResourceManager::LoadTexture(const std::string& _name, const TCHAR* _fileName, const std::string& _pathName)
{
	return m_textureManager->LoadTexture(_name, _fileName, _pathName);
}

bool CResourceManager::LoadTextureFullPath(const std::string& _name, const TCHAR* _fullPath)
{
	return m_textureManager->LoadTexture(_name, _fullPath);
}

#ifdef UNICODE

bool CResourceManager::LoadTexture(const std::string& _name, const std::vector<std::wstring>& _vecFileName, const std::string& _pathName)
{
	return m_textureManager->LoadTexture(_name, _vecFileName, _pathName);
}

bool CResourceManager::LoadTextureFullPath(const std::string& _name, const std::vector<std::wstring>& _vecFullPath)
{
	return m_textureManager->LoadTexture(_name, _vecFullPath);
}

#else

bool CResourceManager::LoadTexture(const std::string& _name, const std::vector<std::string>& _vecFileName, const std::string& _pathName)
{
	return m_textureManager->LoadTexture(_name, _vecFileName, _pathName);
}

bool CResourceManager::LoadTextureFullPath(const std::string& _name, const std::vector<std::string>& _vecFullPath)
{
	return m_textureManager->LoadTexture(_name, _vecFullPath);
}

#endif // UNICODE
CTexture* CResourceManager::FindTexture(const std::string& _name)
{
	return m_textureManager->FindTexture(_name);
}

void CResourceManager::ReleaseTexture(const std::string& _name)
{
	m_textureManager->ReleaseTexture(_name);
}

bool CResourceManager::SetColorKey(const std::string& _name, unsigned char _r, unsigned char _g, unsigned char _b, int _index)
{
	return m_textureManager->SetColorKey(_name, _r, _g, _b, _index);
}

bool CResourceManager::SetColorKeyAll(const std::string& _name, unsigned char _r, unsigned char _g, unsigned char _b)
{
	return m_textureManager->SetColorKeyAll(_name, _r, _g, _b);
}

bool CResourceManager::CreateAnimationSequence(const std::string& _name, CTexture* _texture)
{
	// 키(_name)와 텍스쳐로 생성한다.
	return m_animationManager->CreateAnimationSequence(_name, _texture);
}

bool CResourceManager::CreateAnimationSequence(const std::string& _name, const std::string& _texName)
{
	// 텍스쳐 키(_texName)로 텍스쳐를 찾는다.
	CTexture* texture = FindTexture(_texName);

	// 키(_name)와 텍스쳐로 생성한다.
	return m_animationManager->CreateAnimationSequence(_name, texture);
}

bool CResourceManager::CreateAnimationSequence(const std::string& _name, const std::string& _texName, const TCHAR* _fileName, const std::string& _pathName)
{
	CTexture* texture = FindTexture(_texName);
	
	// 같은 이름의 텍스쳐가 있을 경우 바로 시퀀스를 생성한다.
	if(texture)
		return m_animationManager->CreateAnimationSequence(_name, texture);
	
	// 같은 이름의 텍스쳐가 없을 경우, 텍스쳐를 먼저 로딩하고 시퀀스를 생성한다.
	if (!m_textureManager->LoadTexture(_texName, _fileName, _pathName))
		return false;

	texture = FindTexture(_texName);

	return m_animationManager->CreateAnimationSequence(_name, texture);
}

bool CResourceManager::CreateAnimationSequenceFullPath(const std::string& _name, const std::string& _texName, const TCHAR* _fullPath)
{
	CTexture* texture = FindTexture(_texName);

	// 같은 이름의 텍스쳐가 있을 경우 바로 시퀀스를 생성한다.
	if (texture)
		return m_animationManager->CreateAnimationSequence(_name, texture);

	// 같은 이름의 텍스쳐가 없을 경우, 텍스쳐를 먼저 로딩하고 시퀀스를 생성한다.
	if (!m_textureManager->LoadTextureFullPath(_texName, _fullPath))
		return false;

	texture = FindTexture(_texName);

	return m_animationManager->CreateAnimationSequence(_name, texture);
}

#ifdef UNICODE

bool CResourceManager::CreateAnimationSequence(const std::string& _name, const std::string& _texName,
	const std::vector<std::wstring>& _vecFileName, const std::string& _pathName)
{
	CTexture* texture = FindTexture(_texName);

	// 같은 이름의 텍스쳐가 있을 경우 바로 시퀀스를 생성한다.
	if (texture)
		return m_animationManager->CreateAnimationSequence(_name, texture);

	// 같은 이름의 텍스쳐가 없을 경우, 텍스쳐를 먼저 로딩하고 시퀀스를 생성한다.
	if (!m_textureManager->LoadTexture(_texName, _vecFileName, _pathName))
		return false;

	texture = FindTexture(_texName);

	return m_animationManager->CreateAnimationSequence(_name, texture);
}

bool CResourceManager::CreateAnimationSequenceFullPath(const std::string& _name, const std::string& _texName, 
	const std::vector<std::wstring>& _vecFullPath)
{
	CTexture* texture = FindTexture(_texName);

	// 같은 이름의 텍스쳐가 있을 경우 바로 시퀀스를 생성한다.
	if (texture)
		return m_animationManager->CreateAnimationSequence(_name, texture);

	// 같은 이름의 텍스쳐가 없을 경우, 텍스쳐를 먼저 로딩하고 시퀀스를 생성한다.
	if (!m_textureManager->LoadTextureFullPath(_texName, _vecFullPath))
		return false;

	texture = FindTexture(_texName);

	return m_animationManager->CreateAnimationSequence(_name, texture);
}

#else

bool CResourceManager::CreateAnimationSequence(const std::string& _name, const std::string& _texName,
	const std::vector<std::string>& _vecFileName, const std::string& _pathName)
{
	CTexture* texture = FindTexture(_texName);

	// 같은 이름의 텍스쳐가 있을 경우 바로 시퀀스를 생성한다.
	if (texture)
		return m_animationManager->CreateAnimationSequence(_name, texture);

	// 같은 이름의 텍스쳐가 없을 경우, 텍스쳐를 먼저 로딩하고 시퀀스를 생성한다.
	if (!m_textureManager->LoadTexture(_texName, _vecFileName, _pathName))
		return false;

	texture = FindTexture(_texName);

	return m_animationManager->CreateAnimationSequence(_name, texture);
}

bool CResourceManager::CreateAnimationSequenceFullPath(const std::string& _name, const std::string& _texName,
	const std::vector<std::string>& _vecFullPath)
{
	CTexture* texture = FindTexture(_texName);

	// 같은 이름의 텍스쳐가 있을 경우 바로 시퀀스를 생성한다.
	if (texture)
		return m_animationManager->CreateAnimationSequence(_name, texture);

	// 같은 이름의 텍스쳐가 없을 경우, 텍스쳐를 먼저 로딩하고 시퀀스를 생성한다.
	if (!m_textureManager->LoadTextureFullPath(_texName, _vecFullPath));
	return false;

	texture = FindTexture(_texName);

	return m_animationManager->CreateAnimationSequence(_name, texture);
}

#endif // UNICODE

bool CResourceManager::AddAnimationFrame(const std::string& _name, const Vector2& _start, const Vector2& _end)
{
	return m_animationManager->AddAnimationFrame(_name, _start, _end);
}

bool CResourceManager::AddAnimationFrame(const std::string& _name, float _posX, float _posY, float _sizeX, float _sizeY)
{
	return m_animationManager->AddAnimationFrame(_name, _posX, _posY, _sizeX, _sizeY);
}

bool CResourceManager::AddAnimationFramePivot(const std::string& _name, const Vector2& _pivot)
{
	return m_animationManager->AddAnimationFramePivot(_name, _pivot);
}

bool CResourceManager::AddAnimationFramePivot(const std::string& _name, float _pivotX, float _pivotY)
{
	return m_animationManager->AddAnimationFramePivot(_name, _pivotX, _pivotY);
}

CAnimationSequence* CResourceManager::FindAnimation(const std::string& _name)
{
	return m_animationManager->FindAnimation(_name);
}

void CResourceManager::ReleaseAnimation(const std::string& _name)
{
	return m_animationManager->ReleaseAnimation(_name);
}

bool CResourceManager::CreateSoundChannel(const std::string& _name)
{
	return m_soundManager->CreateSoundChannel(_name);
}

FMOD::ChannelGroup* CResourceManager::FindChannelGroup(const std::string& _name)
{
	return m_soundManager->FindChannelGroup(_name);
}

CSound* CResourceManager::FindSound(const std::string& _name)
{
	return m_soundManager->FindSound(_name);
}

bool CResourceManager::LoadSound(const std::string& _groupName, const std::string& _name, bool _loop, const char* _fileName, const std::string& _pathName)
{
	return m_soundManager->
		LoadSound(_groupName, _name, _loop, _fileName, _pathName);
}

void CResourceManager::ReleaseSound(const std::string& _name)
{
	m_soundManager->ReleaseSound(_name);
}

bool CResourceManager::SetVolume(int _volume)
{
	return m_soundManager->SetVolume(_volume);
}

bool CResourceManager::SetVolume(const std::string& _groupName, int _volume)
{
	return m_soundManager->SetVolume(_groupName, _volume);
}

bool CResourceManager::SoundPlay(const std::string& _name)
{
	return m_soundManager->SoundPlay(_name);
}

bool CResourceManager::SoundStop(const std::string& _name)
{
	return m_soundManager->SoundStop(_name);
}

bool CResourceManager::SoundPause(const std::string& _name)
{
	return m_soundManager->SoundPause(_name);
}

bool CResourceManager::SoundResume(const std::string& _name)
{
	return m_soundManager->SoundResume(_name);
}

bool CResourceManager::LoadFont(const std::string& _name, const TCHAR* _fontName, int _width, int _height)
{
	return m_fontManager->LoadFont(_name, _fontName, _width, _height);
}

bool CResourceManager::LoadFont(const TCHAR* _fontFileName, const std::string& _pathName)
{
	return m_fontManager->LoadFont(_fontFileName, _pathName);
}

void CResourceManager::SetFont(const std::string& _name, HDC _hDC)
{
	m_fontManager->SetFont(_name, _hDC);
}

void CResourceManager::ResetFont(const std::string& _name, HDC _hDC)
{
	m_fontManager->ResetFont(_name, _hDC);
}

CFont* CResourceManager::FindFont(const std::string& _name)
{
	return m_fontManager->FindFont(_name);
}

void CResourceManager::ReleaseFont(const std::string& _name)
{
	m_fontManager->ReleaseFont(_name);
}

CResourceManager::CResourceManager()
{
	// 텍스쳐 매니저를 생성하고 초기화한다.
	m_textureManager = new CTextureManager;
	m_textureManager->Init();

	// 애니메이션 매니저를 생성하고 초기화한다.
	m_animationManager = new CAnimationManager;
	m_animationManager->Init();

	// 사운드 매니저를 생성하고 초기화한다.
	m_soundManager = new CSoundManager;
	m_soundManager->Init();

	// 폰트 매니저를 생성하고 초기화한다.
	m_fontManager = new CFontManager;
	m_fontManager->Init();
}

CResourceManager::~CResourceManager()
{
	SAFE_DELETE(m_fontManager);
	SAFE_DELETE(m_soundManager);
	SAFE_DELETE(m_animationManager);
	SAFE_DELETE(m_textureManager);
}