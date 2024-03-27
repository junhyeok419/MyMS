#include "Sound.h"
#include "../../PathManager.h"

bool CSound::LoadSound(FMOD::System* _system, FMOD::ChannelGroup* _group, bool _loop, const char* _fileName, const std::string& _pathName)
{
	// �޾ƿ� �ý��� ����, ���尡 ���Ե� ä�� �׷� ����, �ÿ�� ���� ������ ����
	m_system = _system;
	m_group = _group;
	m_loop = _loop;

	char	fullPath[MAX_PATH] = {};

	// �޾ƿ� ���� ������ ��θ� ã�´�.
	const PathInfo* Info = CPathManager::GetInst()->FindPath(_pathName);

	// ��ΰ� �����Ѵٸ�
	if (Info)
		// ��Ƽ����Ʈ ���� ��θ� �����Ѵ�.
		strcpy_s(fullPath, Info->pathMultibyte);

	// ������ ��ο� ���� ���� �̸��� �ٿ� ������ ��θ� �����.
	strcat_s(fullPath, _fileName);

	// FMOD_MODE �� DEFALUT�� �޾ƿ´�.
	FMOD_MODE	Mode = FMOD_DEFAULT;

	// ���尡 loop ��� FMOD_MODE�� NORMAL�� �����Ѵ�.
	if (_loop)
		Mode = FMOD_LOOP_NORMAL;

	// ���� fullpath�� �̿��� ���带 ã�� m_sound�� �������ش�.
	// 3��° ���ڴ� �ʿ����.
	if (m_system->createSound(fullPath, Mode, nullptr, &m_sound) != FMOD_OK)
		return false;

	return true;
}

void CSound::Play()
{
	/*
		playSound : �÷��� �� ����, ���尡 ���� �׷�, �Ͻ����� ���·�
		������ ������ ����, ��ȯ���� ���� ä�� �ּҸ� ���ڷ� �޴´�.

		���带 �÷����Ѵ�.
	*/
	m_system->playSound(m_sound, m_group, false, &m_channel);
	m_play = true;
	m_pause = false;
}

void CSound::Stop()
{
	// ä���� �����Ѵٴ� ���� ���尡 ����Ǿ����ٴ� �ǹ��̹Ƿ�
	if (m_channel)
	{
		bool playing = false;

		// isPlaying : �ش� ä���� ���尡 ����ǰ� �ִ��� �Ǵ��Ͽ� ���ڷ� ��ȯ����
		m_channel->isPlaying(&playing);

		// true(���)���
		if (playing)
		{
			// �ش� ä�� ���� ����
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
			// setPaused : true �����ϸ� �ش� ä�� ���� �Ͻ�����. �ݴ�� �簳		
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
	// fmod���� �����ϴ� release �Լ��� �̿�
	if (m_sound)
	{
		m_sound->release();
	}
}
