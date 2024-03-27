#include "SoundManager.h"
#include "Sound.h"

bool CSoundManager::Init()
{
	/*
		FMOD_RESULT : fmod에서 제공하는 타입으로, fmod관련 함수를
		사용할 때, 함수의 성공/실패 여부를 판단하기 위한 타입이다.

		FMOD_OK가 아니면 다 실패이다.
	*/

	// fmod 시스템을 생성한다.
	FMOD_RESULT result = FMOD::System_Create(&m_system);

	// 실패시 리턴
	if (result != FMOD_OK)
		return false;

	/*
		fmod 시스템을 초기화한다.
		최대 채널 수는 500개,
		normal 모드 (일반적)로 인자를 전달한다.
		3번째 인자는 필요없다.
	*/
	result = m_system->init(500, FMOD_INIT_NORMAL, nullptr);

	if (result != FMOD_OK)
		return false;

	// 기본적으로 존재하는 마스터 채널 그룹을 얻어온다.
	result = m_system->getMasterChannelGroup(&m_masterGroup);

	if (result != FMOD_OK)
		return false;

	// 마스터 채널 그룹을 채널 그룹 map에 추가한다.
	m_mapChannelGroup.insert(std::make_pair("Master", m_masterGroup));

	// 채널 그룹을 만든다.
	CreateSoundChannel("BGM");
	CreateSoundChannel("Effect");
	CreateSoundChannel("UI");

	return true;
}

void CSoundManager::Update()
{
	// 필수
	m_system->update();
}

bool CSoundManager::CreateSoundChannel(const std::string& _name)
{
	// 이미 존재하는 채널 그룹이라면 리턴한다.
	if (FindChannelGroup(_name))
		return false;

	// 빈 채널 그룹을 만든다.
	FMOD::ChannelGroup* group = nullptr;

	/*
		createChannelGroup : 채널 그룹을 생성을 요청한다.

		이름을 const char*로 받기 때문에 변환하여 전달한다.
		채널 그룹이 group에 생성될 수 있도록 &group을 전달한다.
	*/
	FMOD_RESULT	result = m_system->createChannelGroup(_name.c_str(), &group);

	if (result != FMOD_OK)
		return false;

	// 생성한 그룹을 마스터 그룹에 추가해준다. (마스터 그룹으로 컨트롤하기 위해)
	// 2번째 인자는 필요없다.
	m_masterGroup->addGroup(group, false);

	// 생성한 그룹을 채널 그룹 map에 추가한다.
	m_mapChannelGroup.insert(std::make_pair(_name, group));

	return true;
}

FMOD::ChannelGroup* CSoundManager::FindChannelGroup(const std::string& _name)
{
	// 키(_name)에 해당하는 채널 그룹을 찾는다.
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
	// 키(_name)에 해당하는 사운드가 존재하는지 찾는다.
	CSound* sound = FindSound(_name);
	 
	// 존재한다면 로드할 필요가 없으므로 리턴한다
	if (sound)
		return true;

	// 로드할 사운드를 넣을 채널 그룹이 존재하는 지 찾는다.
	FMOD::ChannelGroup* group = FindChannelGroup(_groupName);

	// 없다면 리턴한다.
	if (!group)
		return false;

	// 사운드를 객체를 생성하고
	sound = new CSound;

	// 이름을 넣어주고
	sound->SetName(_name);

	// 사운드를 로드한다.
	if (!sound->LoadSound(m_system, group, _loop, _fileName, _pathName))
	{
		// 실패하면 삭제 후 리턴
		SAFE_DELETE(sound);
		return false;
	}

	// 사운드 map에 추가한다.
	m_mapSound.insert(std::make_pair(_name, sound));

	return true;
}

void CSoundManager::ReleaseSound(const std::string& _name)
{
	// 원하는 사운드를 찾는다.
	auto iter = m_mapSound.find(_name);

	// 없으면 리턴
	if (iter == m_mapSound.end())
		return;

	// 사운드의 레퍼런스 카운트가 1이면 완전 삭제한다.
	if (iter->second->GetRefCount() == 1)
		m_mapSound.erase(iter);
}

bool CSoundManager::SetVolume(int _volume)
{
	/*
		볼륨은 0~1사이의 float 값으로 조절한다.
		그러나 이 함수 호출 시에는 1~100 사이의 값을 
		전달하고, 그 값을 100으로 나누어 조절할 것이다.
	*/
	// 해당 그룹의 볼륨을 조절한다.
	m_masterGroup->setVolume(_volume / 100.f);
	return true;
}

bool CSoundManager::SetVolume(const std::string& _groupName, int _volume)
{
	// 원하는 그룹을 찾는다.
	FMOD::ChannelGroup* group = FindChannelGroup(_groupName);

	if (!group)
		return false;

	// 해당 그룹의 볼륨을 조절한다. 
	group->setVolume(_volume / 100.f);

	return true;
}

bool CSoundManager::SoundPlay(const std::string& _name)
{
	// 원하는 사운드를 찾는다.
	CSound* sound = FindSound(_name);

	if (!sound)
		return false;

	// 사운드의 Play 함수를 호출해준다.
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
		// fmod 에서 제공하는 release 함수를 이용한다.
		iter->second->release();
	}

	if (m_system)
	{
		// 시스템은 release뒤에 반드시 close해준다.
		m_system->release();
		m_system->close();
	}
}
