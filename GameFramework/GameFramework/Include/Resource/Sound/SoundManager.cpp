#include "SoundManager.h"
#include "Sound.h"

bool CSoundManager::Init()
{
	/*
		FMOD_RESULT : fmod���� �����ϴ� Ÿ������, fmod���� �Լ���
		����� ��, �Լ��� ����/���� ���θ� �Ǵ��ϱ� ���� Ÿ���̴�.

		FMOD_OK�� �ƴϸ� �� �����̴�.
	*/

	// fmod �ý����� �����Ѵ�.
	FMOD_RESULT result = FMOD::System_Create(&m_system);

	// ���н� ����
	if (result != FMOD_OK)
		return false;

	/*
		fmod �ý����� �ʱ�ȭ�Ѵ�.
		�ִ� ä�� ���� 500��,
		normal ��� (�Ϲ���)�� ���ڸ� �����Ѵ�.
		3��° ���ڴ� �ʿ����.
	*/
	result = m_system->init(500, FMOD_INIT_NORMAL, nullptr);

	if (result != FMOD_OK)
		return false;

	// �⺻������ �����ϴ� ������ ä�� �׷��� ���´�.
	result = m_system->getMasterChannelGroup(&m_masterGroup);

	if (result != FMOD_OK)
		return false;

	// ������ ä�� �׷��� ä�� �׷� map�� �߰��Ѵ�.
	m_mapChannelGroup.insert(std::make_pair("Master", m_masterGroup));

	// ä�� �׷��� �����.
	CreateSoundChannel("BGM");
	CreateSoundChannel("Effect");
	CreateSoundChannel("UI");

	return true;
}

void CSoundManager::Update()
{
	// �ʼ�
	m_system->update();
}

bool CSoundManager::CreateSoundChannel(const std::string& _name)
{
	// �̹� �����ϴ� ä�� �׷��̶�� �����Ѵ�.
	if (FindChannelGroup(_name))
		return false;

	// �� ä�� �׷��� �����.
	FMOD::ChannelGroup* group = nullptr;

	/*
		createChannelGroup : ä�� �׷��� ������ ��û�Ѵ�.

		�̸��� const char*�� �ޱ� ������ ��ȯ�Ͽ� �����Ѵ�.
		ä�� �׷��� group�� ������ �� �ֵ��� &group�� �����Ѵ�.
	*/
	FMOD_RESULT	result = m_system->createChannelGroup(_name.c_str(), &group);

	if (result != FMOD_OK)
		return false;

	// ������ �׷��� ������ �׷쿡 �߰����ش�. (������ �׷����� ��Ʈ���ϱ� ����)
	// 2��° ���ڴ� �ʿ����.
	m_masterGroup->addGroup(group, false);

	// ������ �׷��� ä�� �׷� map�� �߰��Ѵ�.
	m_mapChannelGroup.insert(std::make_pair(_name, group));

	return true;
}

FMOD::ChannelGroup* CSoundManager::FindChannelGroup(const std::string& _name)
{
	// Ű(_name)�� �ش��ϴ� ä�� �׷��� ã�´�.
	auto iter = m_mapChannelGroup.find(_name);

	if (iter == m_mapChannelGroup.end())
		return nullptr;

	return iter->second;
}

CSound* CSoundManager::FindSound(const std::string& _name)
{
	auto	iter = m_mapSound.find(_name);

	if (iter == m_mapSound.end())
		return nullptr;

	return iter->second;
}

bool CSoundManager::LoadSound(const std::string& _groupName, 
	const std::string& _name, bool _loop, const char* _fileName, const std::string& _pathName)
{
	// Ű(_name)�� �ش��ϴ� ���尡 �����ϴ��� ã�´�.
	CSound* sound = FindSound(_name);
	 
	// �����Ѵٸ� �ε��� �ʿ䰡 �����Ƿ� �����Ѵ�
	if (sound)
		return true;

	// �ε��� ���带 ���� ä�� �׷��� �����ϴ� �� ã�´�.
	FMOD::ChannelGroup* group = FindChannelGroup(_groupName);

	// ���ٸ� �����Ѵ�.
	if (!group)
		return false;

	// ���带 ��ü�� �����ϰ�
	sound = new CSound;

	// �̸��� �־��ְ�
	sound->SetName(_name);

	// ���带 �ε��Ѵ�.
	if (!sound->LoadSound(m_system, group, _loop, _fileName, _pathName))
	{
		// �����ϸ� ���� �� ����
		SAFE_DELETE(sound);
		return false;
	}

	// ���� map�� �߰��Ѵ�.
	m_mapSound.insert(std::make_pair(_name, sound));

	return true;
}

void CSoundManager::ReleaseSound(const std::string& _name)
{
	// ���ϴ� ���带 ã�´�.
	auto iter = m_mapSound.find(_name);

	// ������ ����
	if (iter == m_mapSound.end())
		return;

	// ������ ���۷��� ī��Ʈ�� 1�̸� ���� �����Ѵ�.
	if (iter->second->GetRefCount() == 1)
		m_mapSound.erase(iter);
}

bool CSoundManager::SetVolume(int _volume)
{
	/*
		������ 0~1������ float ������ �����Ѵ�.
		�׷��� �� �Լ� ȣ�� �ÿ��� 1~100 ������ ���� 
		�����ϰ�, �� ���� 100���� ������ ������ ���̴�.
	*/
	// �ش� �׷��� ������ �����Ѵ�.
	m_masterGroup->setVolume(_volume / 100.f);
	return true;
}

bool CSoundManager::SetVolume(const std::string& _groupName, int _volume)
{
	// ���ϴ� �׷��� ã�´�.
	FMOD::ChannelGroup* group = FindChannelGroup(_groupName);

	if (!group)
		return false;

	// �ش� �׷��� ������ �����Ѵ�. 
	group->setVolume(_volume / 100.f);

	return true;
}

bool CSoundManager::SoundPlay(const std::string& _name)
{
	// ���ϴ� ���带 ã�´�.
	CSound* sound = FindSound(_name);

	if (!sound)
		return false;

	// ������ Play �Լ��� ȣ�����ش�.
	sound->Play();

	return true;
}

bool CSoundManager::SoundStop(const std::string& _name)
{
	CSound* sound = FindSound(_name);

	if (!sound)
		return false;

	sound->Stop();

	return true;
}

bool CSoundManager::SoundPause(const std::string& _name)
{
	CSound* sound = FindSound(_name);

	if (!sound)
		return false;

	sound->Pause();

	return true;
}

bool CSoundManager::SoundResume(const std::string& _name)
{
	CSound* sound = FindSound(_name);

	if (!sound)
		return false;

	sound->Resume();

	return true;
}

CSoundManager::CSoundManager()
	: m_system(nullptr)
	, m_masterGroup(nullptr)
{
}


CSoundManager::~CSoundManager()
{
	m_mapSound.clear();

	auto	iter = m_mapChannelGroup.begin();
	auto	iterEnd = m_mapChannelGroup.end();

	for (; iter != iterEnd; ++iter)
	{
		// fmod ���� �����ϴ� release �Լ��� �̿��Ѵ�.
		iter->second->release();
	}

	if (m_system)
	{
		// �ý����� release�ڿ� �ݵ�� close���ش�.
		m_system->release();
		m_system->close();
	}
}
