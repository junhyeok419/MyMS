#include "SceneResource.h"
#include "../Resource/Texture/Texture.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Animation/AnimationSequence.h"
#include "../Resource/Sound/Sound.h"
#include "../Resource/Font/Font.h"

bool CSceneResource::LoadTexture(const std::string& _name, const TCHAR* _fileName, const std::string& _pathName)
{
	// 찾는 텍스쳐가 이미 있다면 리턴
	if(FindTexture(_name))
		return false;

	// 텍스쳐 로드에 실패했다면 리턴
	if (!CResourceManager::GetInst()->LoadTexture(_name, _fileName, _pathName))
		return false;

	// 로드한 이미지를 찾아서 가져오고
	CTexture* texture = CResourceManager::GetInst()->FindTexture(_name);

	// 씬리소스의 map에 추가한다.
	m_mapTexture.insert(std::make_pair(_name, texture));

	return true;
}

bool CSceneResource::LoadTextureFullPath(const std::string& _name, const TCHAR* _fullPath)
{
	// 찾는 텍스쳐가 이미 있다면 리턴
	if (FindTexture(_name))
		return false;

	// 텍스쳐 로드에 실패했다면 리턴
	if (!CResourceManager::GetInst()->LoadTexture(_name, _fullPath))
		return false;

	// 로드한 이미지를 찾아서 가져오고
	CTexture* texture = CResourceManager::GetInst()->FindTexture(_name);

	// 씬리소스의 map에 추가한다.
	m_mapTexture.insert(std::make_pair(_name, texture));

	return true;
}

#ifdef UNICODE
bool CSceneResource::LoadTexture(const std::string& _name, const std::vector<std::wstring>& _vecFileName, const std::string& _pathName)
{
	// 찾는 텍스쳐가 이미 있다면 리턴
	if (FindTexture(_name))
		return false;

	// 텍스쳐 로드에 실패했다면 리턴
	if (!CResourceManager::GetInst()->LoadTexture(_name, _vecFileName, _pathName))
		return false;

	// 로드한 이미지를 찾아서 가져오고
	CTexture* texture = CResourceManager::GetInst()->FindTexture(_name);

	// 씬리소스의 map에 추가한다.
	m_mapTexture.insert(std::make_pair(_name, texture));

	return true;
}

bool CSceneResource::LoadTextureFullPath(const std::string& _name, const std::vector<std::wstring>& _vecFullPath)
{
	// 찾는 텍스쳐가 이미 있다면 리턴
	if (FindTexture(_name))
		return false;

	// 텍스쳐 로드에 실패했다면 리턴
	if (!CResourceManager::GetInst()->LoadTexture(_name, _vecFullPath))
		return false;

	// 로드한 이미지를 찾아서 가져오고
	CTexture* texture = CResourceManager::GetInst()->FindTexture(_name);

	// 씬리소스의 map에 추가한다.
	m_mapTexture.insert(std::make_pair(_name, texture));

	return true;
}
#else
bool CSceneResource::LoadTexture(const std::string& _name, const std::vector<std::string>& _vecFileName, const std::string& _pathName)
{
	// 찾는 텍스쳐가 이미 있다면 리턴
	if (FindTexture(_name))
		return false;

	// 텍스쳐 로드에 실패했다면 리턴
	if (!CResourceManager::GetInst()->LoadTexture(_name, _vecFileName, _pathName))
		return false;

	// 로드한 이미지를 찾아서 가져오고
	CTexture* texture = CResourceManager::GetInst()->FindTexture(_name);

	// 씬리소스의 map에 추가한다.
	m_mapTexture.insert(std::make_pair(_name, texture));

	return true;
}

bool CSceneResource::LoadTextureFullPath(const std::string& _name, const std::vector<std::string>& _vecFullPath)
{
	// 찾는 텍스쳐가 이미 있다면 리턴
	if (FindTexture(_name))
		return false;

	// 텍스쳐 로드에 실패했다면 리턴
	if (!CResourceManager::GetInst()->LoadTexture(_name, _vecFullPath))
		return false;

	// 로드한 이미지를 찾아서 가져오고
	CTexture* texture = CResourceManager::GetInst()->FindTexture(_name);

	// 씬리소스의 map에 추가한다.
	m_mapTexture.insert(std::make_pair(_name, texture));

	return true;
}
#endif // UNICODE

CTexture* CSceneResource::FindTexture(const std::string& _name)
{
	auto	iter = m_mapTexture.find(_name);

	if (iter == m_mapTexture.end())
	{
		CTexture* texture = CResourceManager::GetInst()->FindTexture(_name);

		if (!texture)
			return nullptr;

		m_mapTexture.insert(std::make_pair(_name, texture));

		return texture;
	}

	return iter->second;
}

bool CSceneResource::SetColorKey(const std::string& _name, unsigned char _r, unsigned char _g, unsigned char _b, int _index)
{
	return CResourceManager::GetInst()->SetColorKey(_name, _r, _g, _b, _index);
}

bool CSceneResource::SetColorKeyAll(const std::string& _name, unsigned char _r, unsigned char _g, unsigned char _b)
{
	return CResourceManager::GetInst()->SetColorKeyAll(_name, _r, _g, _b);
}

bool CSceneResource::CreateAnimationSequence(const std::string& _name, CTexture* _texture)
{
	// 키(_name)에 해당하는 애니메이션이 있다면 리턴한다
	if(FindAnimation(_name))
		return false;

	// 애니메이션 시퀀스를 생성한다.
	if (!CResourceManager::GetInst()->CreateAnimationSequence(_name, _texture))
		return false;

	// 만든 애니메이션을 가져와서
	CAnimationSequence* animation = CResourceManager::GetInst()->FindAnimation(_name);

	// map에 추가한다.
	m_mapAnimationSequence.insert(std::make_pair(_name, animation));

	return true;
}

bool CSceneResource::CreateAnimationSequence(const std::string& _name, const std::string& _texName)
{
	// 키(_name)에 해당하는 애니메이션이 있다면 리턴한다
	if (FindAnimation(_name))
		return false;

	// 애니메이션 시퀀스를 생성한다.
	if (!CResourceManager::GetInst()->CreateAnimationSequence(_name, _texName))
		return false;

	// 만든 애니메이션을 가져와서
	CAnimationSequence* animation = CResourceManager::GetInst()->FindAnimation(_name);

	// map에 추가한다.
	m_mapAnimationSequence.insert(std::make_pair(_name, animation));

	return true;
}

bool CSceneResource::CreateAnimationSequence(const std::string& _name, 
	const std::string& _texName, const TCHAR* _fileName, const std::string& _pathName)
{
	// 키(_name)에 해당하는 애니메이션이 있다면 리턴한다
	if (FindAnimation(_name))
		return false;

	// 애니메이션 시퀀스를 생성한다.
	if (!CResourceManager::GetInst()->CreateAnimationSequence(_name, _texName,
		_fileName, _pathName))
		return false;

	// 만든 애니메이션을 가져와서
	CAnimationSequence* animation = CResourceManager::GetInst()->FindAnimation(_name);

	// map에 추가한다.
	m_mapAnimationSequence.insert(std::make_pair(_name, animation));

	return true;
}

bool CSceneResource::CreateAnimationSequenceFullPath(const std::string& _name, const std::string& _texName, const TCHAR* _fullPath)
{
	// 키(_name)에 해당하는 애니메이션이 있다면 리턴한다
	if (FindAnimation(_name))
		return false;

	// 애니메이션 시퀀스를 생성한다.
	if (!CResourceManager::GetInst()->CreateAnimationSequenceFullPath(_name, _texName,
		_fullPath))
		return false;

	// 만든 애니메이션을 가져와서
	CAnimationSequence* animation = CResourceManager::GetInst()->FindAnimation(_name);

	// map에 추가한다.
	m_mapAnimationSequence.insert(std::make_pair(_name, animation));

	return true;
}

#ifdef UNICODE

bool CSceneResource::CreateAnimationSequence(const std::string& _name, 
	const std::string& _texName, const std::vector<std::wstring>& _vecFileName, 
	const std::string& _pathName)
{
	if (FindAnimation(_name))
		return false;

	if (!CResourceManager::GetInst()->CreateAnimationSequence(_name, _texName,
		_vecFileName, _pathName))
		return false;

	CAnimationSequence* animation = CResourceManager::GetInst()->FindAnimation(_name);

	m_mapAnimationSequence.insert(std::make_pair(_name, animation));

	return true;
}

bool CSceneResource::CreateAnimationSequenceFullPath(const std::string& _name, const std::string& _texName, const std::vector<std::wstring>& _vecFullPath)
{
	if (FindAnimation(_name))
		return false;

	if (!CResourceManager::GetInst()->CreateAnimationSequenceFullPath(_name, _texName,
		_vecFullPath))
		return false;

	CAnimationSequence* animation = CResourceManager::GetInst()->FindAnimation(_name);

	m_mapAnimationSequence.insert(std::make_pair(_name, animation));

	return true;
}

#else

bool CSceneResource::CreateAnimationSequence(const std::string& _name, const std::string& _texName, const std::vector<std::wstring>& _vecFileName, const std::string& _pathName)
{
	if (FindAnimation(_name))
		return false;

	if (!CResourceManager::GetInst()->CreateAnimationSequence(_name, _texName,
		_vecFileName, _pathName))
		return false;

	CAnimationSequence* animation = CResourceManager::GetInst()->FindAnimation(_name);

	m_mapAnimationSequence.insert(std::make_pair(_name, animation));

	return true;
}

bool CSceneResource::CreateAnimationSequenceFullPath(const std::string& _name, const std::string& _texName, const std::vector<std::wstring>& _vecFullPath)
{
	if (FindAnimation(_name))
		return false;

	if (!CResourceManager::GetInst()->CreateAnimationSequenceFullPath(_name, _texName,
		_vecFullPath))
		return false;

	CAnimationSequence* animation = CResourceManager::GetInst()->FindAnimation(_name);

	m_mapAnimationSequence.insert(std::make_pair(_name, animation));

	return true;
}

#endif // UNICODE

bool CSceneResource::AddAnimationFrame(const std::string& _name, 
	const Vector2& _start, const Vector2& _end)
{
	return CResourceManager::GetInst()->AddAnimationFrame(_name, _start, _end);
}

bool CSceneResource::AddAnimationFrame(const std::string& _name, 
	float _posX, float _posY, float _sizeX, float _sizeY)
{
	return CResourceManager::GetInst()->AddAnimationFrame(_name, _posX, _posY, _sizeX, _sizeY);
}

bool CSceneResource::AddAnimationFramePivot(const std::string& _name, const Vector2& _pivot)
{
	return CResourceManager::GetInst()
		->AddAnimationFramePivot(_name, _pivot);
}

bool CSceneResource::AddAnimationFramePivot(const std::string& _name, float _pivotX, float _pivotY)
{
	return CResourceManager::GetInst()
		->AddAnimationFramePivot(_name, _pivotX, _pivotY);
}

CAnimationSequence* CSceneResource::FindAnimation(const std::string& _name)
{
	// 키(_name)를 이용해 씬리소스의 애니메이션을 가져온다.
	auto	iter = m_mapAnimationSequence.find(_name);

	// 씬리소스에 일치하는 애니메이션이 없다면
	if (iter == m_mapAnimationSequence.end())
	{
		// 전체 애니메이션 목록에서 가져온다. 
		CAnimationSequence* animation = CResourceManager::GetInst()->FindAnimation(_name);

		// 여기도 아예 없다면 리턴
		if (!animation)
			return nullptr;

		// 가져온 애니메이션을 map에 추가한다.
		m_mapAnimationSequence.insert(std::make_pair(_name, animation));

		return animation;
	}

	// 일치하는 애니메이션이 있다면 리턴
	return iter->second;
}

bool CSceneResource::CreateSoundChannel(const std::string& _name)
{
	return CResourceManager::GetInst()->CreateSoundChannel(_name);
}

FMOD::ChannelGroup* CSceneResource::FindChannelGroup(const std::string& _name)
{
	return CResourceManager::GetInst()->FindChannelGroup(_name);
}

CSound* CSceneResource::FindSound(const std::string& _name)
{
	// 원하는 사운드를 찾는다.
	auto	iter = m_mapSound.find(_name);

	// 사운드가 없다면
	if (iter == m_mapSound.end())
	{
		// 씬이 아닌 전체 리소스에서 찾는다.
		CSound* Sound = CResourceManager::GetInst()->FindSound(_name);

		// 그래도 없다면 리턴한다.
		if (!Sound)
			return nullptr;

		// 있다면 씬의 사운드 map에 추가하고  
		m_mapSound.insert(std::make_pair(_name, Sound));

		// 사운드를 반환한다.
		return Sound;
	}

	// 사운드가 있다면 반환한다.
	return iter->second;
}

bool CSceneResource::LoadSound(const std::string& _groupName, const std::string& _name, bool _loop, const char* _fileName, const std::string& _pathName)
{
	// 씬에 있다면 로드할 필요가 없으므로 리턴한다.
	if (FindSound(_name))
		return false;

	// 전체 리소스의 사운드에서 로드한다. 
	if (!CResourceManager::GetInst()
		->LoadSound(_groupName, _name, _loop, _fileName, _pathName))
		return false;

	// 로드한 사운드를 받아온다.
	CSound* sound = CResourceManager::GetInst()->FindSound(_name);

	// 씬의 사운드 map에 추가한다.
	m_mapSound.insert(std::make_pair(_name, sound));

	return true;
}

bool CSceneResource::SetVolume(int _volume)
{
	return CResourceManager::GetInst()->SetVolume(_volume);
}

bool CSceneResource::SetVolume(const std::string& _groupName, int _volume)
{
	return CResourceManager::GetInst()->SetVolume(_groupName, _volume);
}

bool CSceneResource::SoundPlay(const std::string& _name)
{
	return CResourceManager::GetInst()->SoundPlay(_name);
}

bool CSceneResource::SoundStop(const std::string& _name)
{
	return CResourceManager::GetInst()->SoundStop(_name);
}

bool CSceneResource::SoundPause(const std::string& _name)
{
	return CResourceManager::GetInst()->SoundPause(_name);
}

bool CSceneResource::SoundResume(const std::string& _name)
{
	return CResourceManager::GetInst()->SoundResume(_name);
}

bool CSceneResource::LoadFont(const std::string& _name, const TCHAR* _fontName, int _width, int _height)
{
	if (FindFont(_name))
		return false;

	if (!CResourceManager::GetInst()->LoadFont(_name, _fontName, _width, _height))
		return false;

	CFont* Font = CResourceManager::GetInst()->FindFont(_name);

	m_mapFont.insert(std::make_pair(_name, Font));

	return true;
}

bool CSceneResource::LoadFont(const TCHAR* _fontFileName, const std::string& _pathName)
{
	return CResourceManager::GetInst()->LoadFont(_fontFileName, _pathName);
}

void CSceneResource::SetFont(const std::string& _name, HDC _hDC)
{
	return CResourceManager::GetInst()->SetFont(_name, _hDC);
}

void CSceneResource::ResetFont(const std::string& _name, HDC _hDC)
{
	return CResourceManager::GetInst()->ResetFont(_name, _hDC);
}

CFont* CSceneResource::FindFont(const std::string& _name)
{
	auto	iter = m_mapFont.find(_name);

	if (iter == m_mapFont.end())
	{
		CFont* Font = CResourceManager::GetInst()->FindFont(_name);

		if (!Font)
			return nullptr;

		m_mapFont.insert(std::make_pair(_name, Font));

		return Font;
	}

	return iter->second;
}

CSceneResource::CSceneResource()
{
}

CSceneResource::~CSceneResource()
{
	{
		auto iter = m_mapTexture.begin();
		auto iterEnd = m_mapTexture.end();

		for (; iter != iterEnd;)
		{
			std::string key = iter->first;

			/*
				텍스쳐를 삭제하는게 아니라, 공유 포인터타입 원소를
				하나 삭제함으로써, 텍스쳐와의 연결을 끊는 것이다.
			*/
			iter = m_mapTexture.erase(iter);
			iterEnd = m_mapTexture.end();

			/*
				텍스쳐매니저와 씬리소스가 둘 다 공통의 텍스쳐를 들고 있고,
				씬리소스가 텍스쳐를 erase했을 때, 텍스쳐에 대한 레퍼런스 카운트가
				1이 남아있다는 의미는, 씬리소스는 해당 텍스쳐가 필요 없어서 들고있지 않지만
				텍스쳐 매니저만 들고 있는 상황이다. (어디에도 쓰이지 않는 상황)

				따라서 텍스쳐매니저를 통해 텍스쳐를 완전히 제거해야 한다.
			*/
			CResourceManager::GetInst()->ReleaseTexture(key); // 내부를 보면, 레퍼런스 카운트가 1일경우 완전 삭제함
		}
	}

	{
		auto	iter = m_mapAnimationSequence.begin();
		auto	iterEnd = m_mapAnimationSequence.end();

		for (; iter != iterEnd;)
		{
			std::string	key = iter->first;

			iter = m_mapAnimationSequence.erase(iter);
			iterEnd = m_mapAnimationSequence.end();

			CResourceManager::GetInst()->ReleaseAnimation(key);
		}
	}

	{
		auto	iter = m_mapSound.begin();
		auto	iterEnd = m_mapSound.end();

		for (; iter != iterEnd;)
		{
			std::string	key = iter->first;

			iter = m_mapSound.erase(iter);
			iterEnd = m_mapSound.end();

			CResourceManager::GetInst()->ReleaseSound(key);
		}
	}

	{
		auto	iter = m_mapFont.begin();
		auto	iterEnd = m_mapFont.end();

		for (; iter != iterEnd;)
		{
			std::string	key = iter->first;

			iter = m_mapFont.erase(iter);
			iterEnd = m_mapFont.end();

			CResourceManager::GetInst()->ReleaseFont(key);
		}
	}
}
