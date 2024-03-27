#pragma once
#include "../../Ref.h"
class CSound :
    public CRef
{
private:
    FMOD::System* m_system;       // ���� �ý���
    FMOD::Sound* m_sound;         // ����
    FMOD::ChannelGroup* m_group;  // ä���� ���� �׷� 
    FMOD::Channel* m_channel;     // ���� ä�� (���带 �����Ű�� ��ȯ�Ǿ� ä����)
    bool        m_play;           // ���� ���� ��� ����
    bool        m_loop;           // ���� ����
    bool        m_pause;          // �Ͻ����� ����
public:
    bool LoadSound(FMOD::System* _system, FMOD::ChannelGroup* _group, bool _loop,
        const char* _fileName, const std::string& _pathName = SOUND_PATH);
    // ���
    void Play();
    // ����
    void Stop();
    // �Ͻ�����
    void Pause();
    // �簳
    void Resume();
public:
    bool GetPlay()   const;
    bool GetLoop()   const;
private:
    CSound();
    ~CSound();

    friend class CSoundManager;
};

