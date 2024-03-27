#include "Sound.h"
#include "../../PathManager.h"

bool CSound::LoadSound(FMOD::System* _system, FMOD::ChannelGroup* _group, bool _loop, const char* _fileName, const std::string& _pathName)
{
	// 받아온 시스템 정보, 사운드가 포함될 채널 그룹 정보, 시운드 루프 정보를 세팅
	m_system = _system;
	m_group = _group;
	m_loop = _loop;

	char	fullPath[MAX_PATH] = {};

	// 받아온 사운드 파일의 경로를 찾는다.
	const PathInfo* Info = CPathManager::GetInst()->FindPath(_pathName);

	// 경로가 존재한다면
	if (Info)
		// 멀티바이트 버전 경로를 복사한다.
		strcpy_s(fullPath, Info->pathMultibyte);

	// 복사한 경로에 사운드 파일 이름을 붙여 완전한 경로를 만든다.
	strcat_s(fullPath, _fileName);

	// FMOD_MODE 를 DEFALUT로 받아온다.
	FMOD_MODE	Mode = FMOD_DEFAULT;

	// 사운드가 loop 라면 FMOD_MODE를 NORMAL로 변경한다.
	if (_loop)
		Mode = FMOD_LOOP_NORMAL;

	// 만든 fullpath를 이용해 사운드를 찾아 m_sound에 생성해준다.
	// 3번째 인자는 필요없다.
	if (m_system->createSound(fullPath, Mode, nullptr, &m_sound) != FMOD_OK)
		return false;

	return true;
}

void CSound::Play()
{
	/*
		playSound : 플레이 할 사운드, 사운드가 속한 그룹, 일시정지 상태로
		시작할 것인지 여부, 반환받을 사운드 채널 주소를 인자로 받는다.

		사운드를 플레이한다.
	*/
	m_system->playSound(m_sound, m_group, false, &m_channel);
	m_play = true;
	m_pause = false;
}

void CSound::Stop()
{
	// 채널이 존재한다는 것은 사운드가 재생되었었다는 의미이므로
	if (m_channel)
	{
		bool playing = false;

		// isPlaying : 해당 채널의 사운드가 재생되고 있는지 판단하여 인자로 반환해줌
		m_channel->isPlaying(&playing);

		// true(재생)라면
		if (playing)
		{
			// 해당 채널 사운드 정지
			m_channel->stop();
			// nullptr
			m_channel = nullptr;

			m_play = false;
			m_pause = false;
		}
	}
}

void CSound::Pause()
{
	if (m_channel)
	{
		bool playing = false;

		m_channel->isPlaying(&playing);

		if (playing)
			// setPaused : true 전달하면 해당 채널 사운드 일시정지. 반대는 재개		
			m_channel->setPaused(true);

		m_play = false;
		m_pause = true;
	}
}

void CSound::Resume()
{
	if (m_channel)
	{
		bool playing = false;

		m_channel->isPlaying(&playing);

		if (playing)
		{
			m_channel->setPaused(false);

			m_play = true;
			m_pause = false;
		}
	}
}

bool CSound::GetPlay() const
{
	return m_play;
}

bool CSound::GetLoop() const
{
	return m_loop;
}

CSound::CSound()
	: m_system(nullptr)
	, m_sound(nullptr)
	, m_group(nullptr)
	, m_channel(nullptr)
	, m_play(false)
	, m_loop(false)
	, m_pause(false)
{
}

CSound::~CSound()
{
	// fmod에서 제공하는 release 함수를 이용
	if (m_sound)
	{
		m_sound->release();
	}
}
