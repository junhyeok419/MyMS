#include "SceneResource.h"
#include "../Resource/Texture/Texture.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Animation/AnimationSequence.h"
#include "../Resource/Sound/Sound.h"
#include "../Resource/Font/Font.h"

bool CSceneResource::LoadTexture(const std::string& _name, const TCHAR* _fileName, const std::string& _pathName)
{
	// ã�� �ؽ��İ� �̹� �ִٸ� ����
	if(FindTexture(_name))
		return false;

	// �ؽ��� �ε忡 �����ߴٸ� ����
	if (!CResourceManager::GetInst()->LoadTexture(_name, _fileName, _pathName))
		return false;

	// �ε��� �̹����� ã�Ƽ� ��������
	CTexture* texture = CResourceManager::GetInst()->FindTexture(_name);

	// �����ҽ��� map�� �߰��Ѵ�.
	m_mapTexture.insert(std::make_pair(_name, texture));

	return true;
}

bool CSceneResource::LoadTextureFullPath(const std::string& _name, const TCHAR* _fullPath)
{
	// ã�� �ؽ��İ� �̹� �ִٸ� ����
	if (FindTexture(_name))
		return false;

	// �ؽ��� �ε忡 �����ߴٸ� ����
	if (!CResourceManager::GetInst()->LoadTexture(_name, _fullPath))
		return false;

	// �ε��� �̹����� ã�Ƽ� ��������
	CTexture* texture = CResourceManager::GetInst()->FindTexture(_name);

	// �����ҽ��� map�� �߰��Ѵ�.
	m_mapTexture.insert(std::make_pair(_name, texture));

	return true;
}

#ifdef UNICODE
bool CSceneResource::LoadTexture(const std::string& _name, const std::vector<std::wstring>& _vecFileName, const std::string& _pathName)
{
	// ã�� �ؽ��İ� �̹� �ִٸ� ����
	if (FindTexture(_name))
		return false;

	// �ؽ��� �ε忡 �����ߴٸ� ����
	if (!CResourceManager::GetInst()->LoadTexture(_name, _vecFileName, _pathName))
		return false;

	// �ε��� �̹����� ã�Ƽ� ��������
	CTexture* texture = CResourceManager::GetInst()->FindTexture(_name);

	// �����ҽ��� map�� �߰��Ѵ�.
	m_mapTexture.insert(std::make_pair(_name, texture));

	return true;
}

bool CSceneResource::LoadTextureFullPath(const std::string& _name, const std::vector<std::wstring>& _vecFullPath)
{
	// ã�� �ؽ��İ� �̹� �ִٸ� ����
	if (FindTexture(_name))
		return false;

	// �ؽ��� �ε忡 �����ߴٸ� ����
	if (!CResourceManager::GetInst()->LoadTexture(_name, _vecFullPath))
		return false;

	// �ε��� �̹����� ã�Ƽ� ��������
	CTexture* texture = CResourceManager::GetInst()->FindTexture(_name);

	// �����ҽ��� map�� �߰��Ѵ�.
	m_mapTexture.insert(std::make_pair(_name, texture));

	return true;
}
#else
bool CSceneResource::LoadTexture(const std::string& _name, const std::vector<std::string>& _vecFileName, const std::string& _pathName)
{
	// ã�� �ؽ��İ� �̹� �ִٸ� ����
	if (FindTexture(_name))
		return false;

	// �ؽ��� �ε忡 �����ߴٸ� ����
	if (!CResourceManager::GetInst()->LoadTexture(_name, _vecFileName, _pathName))
		return false;

	// �ε��� �̹����� ã�Ƽ� ��������
	CTexture* texture = CResourceManager::GetInst()->FindTexture(_name);

	// �����ҽ��� map�� �߰��Ѵ�.
	m_mapTexture.insert(std::make_pair(_name, texture));

	return true;
}

bool CSceneResource::LoadTextureFullPath(const std::string& _name, const std::vector<std::string>& _vecFullPath)
{
	// ã�� �ؽ��İ� �̹� �ִٸ� ����
	if (FindTexture(_name))
		return false;

	// �ؽ��� �ε忡 �����ߴٸ� ����
	if (!CResourceManager::GetInst()->LoadTexture(_name, _vecFullPath))
		return false;

	// �ε��� �̹����� ã�Ƽ� ��������
	CTexture* texture = CResourceManager::GetInst()->FindTexture(_name);

	// �����ҽ��� map�� �߰��Ѵ�.
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
	// Ű(_name)�� �ش��ϴ� �ִϸ��̼��� �ִٸ� �����Ѵ�
	if(FindAnimation(_name))
		return false;

	// �ִϸ��̼� �������� �����Ѵ�.
	if (!CResourceManager::GetInst()->CreateAnimationSequence(_name, _texture))
		return false;

	// ���� �ִϸ��̼��� �����ͼ�
	CAnimationSequence* animation = CResourceManager::GetInst()->FindAnimation(_name);

	// map�� �߰��Ѵ�.
	m_mapAnimationSequence.insert(std::make_pair(_name, animation));

	return true;
}

bool CSceneResource::CreateAnimationSequence(const std::string& _name, const std::string& _texName)
{
	// Ű(_name)�� �ش��ϴ� �ִϸ��̼��� �ִٸ� �����Ѵ�
	if (FindAnimation(_name))
		return false;

	// �ִϸ��̼� �������� �����Ѵ�.
	if (!CResourceManager::GetInst()->CreateAnimationSequence(_name, _texName))
		return false;

	// ���� �ִϸ��̼��� �����ͼ�
	CAnimationSequence* animation = CResourceManager::GetInst()->FindAnimation(_name);

	// map�� �߰��Ѵ�.
	m_mapAnimationSequence.insert(std::make_pair(_name, animation));

	return true;
}

bool CSceneResource::CreateAnimationSequence(const std::string& _name, 
	const std::string& _texName, const TCHAR* _fileName, const std::string& _pathName)
{
	// Ű(_name)�� �ش��ϴ� �ִϸ��̼��� �ִٸ� �����Ѵ�
	if (FindAnimation(_name))
		return false;

	// �ִϸ��̼� �������� �����Ѵ�.
	if (!CResourceManager::GetInst()->CreateAnimationSequence(_name, _texName,
		_fileName, _pathName))
		return false;

	// ���� �ִϸ��̼��� �����ͼ�
	CAnimationSequence* animation = CResourceManager::GetInst()->FindAnimation(_name);

	// map�� �߰��Ѵ�.
	m_mapAnimationSequence.insert(std::make_pair(_name, animation));

	return true;
}

bool CSceneResource::CreateAnimationSequenceFullPath(const std::string& _name, const std::string& _texName, const TCHAR* _fullPath)
{
	// Ű(_name)�� �ش��ϴ� �ִϸ��̼��� �ִٸ� �����Ѵ�
	if (FindAnimation(_name))
		return false;

	// �ִϸ��̼� �������� �����Ѵ�.
	if (!CResourceManager::GetInst()->CreateAnimationSequenceFullPath(_name, _texName,
		_fullPath))
		return false;

	// ���� �ִϸ��̼��� �����ͼ�
	CAnimationSequence* animation = CResourceManager::GetInst()->FindAnimation(_name);

	// map�� �߰��Ѵ�.
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
	// Ű(_name)�� �̿��� �����ҽ��� �ִϸ��̼��� �����´�.
	auto	iter = m_mapAnimationSequence.find(_name);

	// �����ҽ��� ��ġ�ϴ� �ִϸ��̼��� ���ٸ�
	if (iter == m_mapAnimationSequence.end())
	{
		// ��ü �ִϸ��̼� ��Ͽ��� �����´�. 
		CAnimationSequence* animation = CResourceManager::GetInst()->FindAnimation(_name);

		// ���⵵ �ƿ� ���ٸ� ����
		if (!animation)
			return nullptr;

		// ������ �ִϸ��̼��� map�� �߰��Ѵ�.
		m_mapAnimationSequence.insert(std::make_pair(_name, animation));

		return animation;
	}

	// ��ġ�ϴ� �ִϸ��̼��� �ִٸ� ����
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
	// ���ϴ� ���带 ã�´�.
	auto	iter = m_mapSound.find(_name);

	// ���尡 ���ٸ�
	if (iter == m_mapSound.end())
	{
		// ���� �ƴ� ��ü ���ҽ����� ã�´�.
		CSound* Sound = CResourceManager::GetInst()->FindSound(_name);

		// �׷��� ���ٸ� �����Ѵ�.
		if (!Sound)
			return nullptr;

		// �ִٸ� ���� ���� map�� �߰��ϰ�  
		m_mapSound.insert(std::make_pair(_name, Sound));

		// ���带 ��ȯ�Ѵ�.
		return Sound;
	}

	// ���尡 �ִٸ� ��ȯ�Ѵ�.
	return iter->second;
}

bool CSceneResource::LoadSound(const std::string& _groupName, const std::string& _name, bool _loop, const char* _fileName, const std::string& _pathName)
{
	// ���� �ִٸ� �ε��� �ʿ䰡 �����Ƿ� �����Ѵ�.
	if (FindSound(_name))
		return false;

	// ��ü ���ҽ��� ���忡�� �ε��Ѵ�. 
	if (!CResourceManager::GetInst()
		->LoadSound(_groupName, _name, _loop, _fileName, _pathName))
		return false;

	// �ε��� ���带 �޾ƿ´�.
	CSound* sound = CResourceManager::GetInst()->FindSound(_name);

	// ���� ���� map�� �߰��Ѵ�.
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
				�ؽ��ĸ� �����ϴ°� �ƴ϶�, ���� ������Ÿ�� ���Ҹ�
				�ϳ� ���������ν�, �ؽ��Ŀ��� ������ ���� ���̴�.
			*/
			iter = m_mapTexture.erase(iter);
			iterEnd = m_mapTexture.end();

			/*
				�ؽ��ĸŴ����� �����ҽ��� �� �� ������ �ؽ��ĸ� ��� �ְ�,
				�����ҽ��� �ؽ��ĸ� erase���� ��, �ؽ��Ŀ� ���� ���۷��� ī��Ʈ��
				1�� �����ִٴ� �ǹ̴�, �����ҽ��� �ش� �ؽ��İ� �ʿ� ��� ������� ������
				�ؽ��� �Ŵ����� ��� �ִ� ��Ȳ�̴�. (��𿡵� ������ �ʴ� ��Ȳ)

				���� �ؽ��ĸŴ����� ���� �ؽ��ĸ� ������ �����ؾ� �Ѵ�.
			*/
			CResourceManager::GetInst()->ReleaseTexture(key); // ���θ� ����, ���۷��� ī��Ʈ�� 1�ϰ�� ���� ������
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
