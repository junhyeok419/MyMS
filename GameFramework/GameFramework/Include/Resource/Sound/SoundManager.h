#pragma once

#include "../../GameInfo.h"

/*
	���带 �����ϴ� Ŭ�����̴�.
	���带 �̿��� ������ winapi�Լ��� �ƴ�
	fmod�� �̿��� ���̴�.

	���带 �����ϸ� �ش� ���� ä���� ��ȯ�ȴ�. 
	�׷��� �̿��� ä���� ��� ������ �� �ֵ��� �Ѵ�. (������ ���� ��Ʈ�� ����)

	** fmod �� ������ ��Ƽ����Ʈ�� ó���ȴ�.	
*/
class CSoundManager
{
private:
	/*
		FMOD::System : fmod���� �����ϴ� ���� �ý��� Ŭ�����̴�.
		�̰��� �̿��Ͽ� ������ �ε� �� ����� �� ���̴�.
	*/
	FMOD::System* m_system;
	// ��� ä�� �׷��� �ֻ���� ������ ä�� �׷��̴�. 	
	FMOD::ChannelGroup* m_masterGroup;
	// ��� ���带 �����ϱ� ���� map�̴�.
	std::unordered_map<std::string, CSharedPtr<class CSound>>	m_mapSound;
	// ������ ä�� �׷��� ������ ��� ä�� �׷��� �����ϱ� ���� map�̴�. 
	// ä�� �׷��� �翬�� ������ ������ �� �ִ�.
	std::unordered_map<std::string, FMOD::ChannelGroup*>	m_mapChannelGroup;
public:
	bool Init();
	void Update();
public:

public:
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
private:
	CSoundManager();
	~CSoundManager();

	friend class CResourceManager;
};

