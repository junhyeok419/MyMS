#pragma once

#include "../../GameInfo.h"

/*
	사운드를 관리하는 클래스이다.
	사운드를 이용할 때에는 winapi함수가 아닌
	fmod를 이용할 것이다.

	사운드를 생성하면 해당 사운드 채널이 반환된다. 
	그룹을 이용해 채널을 묶어서 관리할 수 있도록 한다. (종류별 사운드 컨트롤 가능)

	** fmod 는 무조건 멀티바이트로 처리된다.	
*/
class CSoundManager
{
private:
	/*
		FMOD::System : fmod에서 제공하는 메인 시스템 클래스이다.
		이것을 이용하여 사운드의 로딩 및 재생을 할 것이다.
	*/
	FMOD::System* m_system;
	// 모든 채널 그룹의 최상단인 마스터 채널 그룹이다. 	
	FMOD::ChannelGroup* m_masterGroup;
	// 모든 사운드를 관리하기 위한 map이다.
	std::unordered_map<std::string, CSharedPtr<class CSound>>	m_mapSound;
	// 마스터 채널 그룹을 포함한 모든 채널 그룹을 관리하기 위한 map이다. 
	// 채널 그룹은 당연히 여러개 존재할 수 있다.
	std::unordered_map<std::string, FMOD::ChannelGroup*>	m_mapChannelGroup;
public:
	bool Init();
	void Update();
public:

public:
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
private:
	CSoundManager();
	~CSoundManager();

	friend class CResourceManager;
};

