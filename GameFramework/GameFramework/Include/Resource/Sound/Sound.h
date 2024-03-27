#pragma once
#include "../../Ref.h"
class CSound :
    public CRef
{
private:
    FMOD::System* m_system;       // 메인 시스템
    FMOD::Sound* m_sound;         // 사운드
    FMOD::ChannelGroup* m_group;  // 채널이 속한 그룹 
    FMOD::Channel* m_channel;     // 사운드 채널 (사운드를 재생시키면 반환되어 채워짐)
    bool        m_play;           // 현재 사운드 재생 여부
    bool        m_loop;           // 루프 여부
    bool        m_pause;          // 일시정지 여부
public:
    bool LoadSound(FMOD::System* _system, FMOD::ChannelGroup* _group, bool _loop,
        const char* _fileName, const std::string& _pathName = SOUND_PATH);
    // 재생
    void Play();
    // 중지
    void Stop();
    // 일시정지
    void Pause();
    // 재개
    void Resume();
public:
    bool GetPlay()   const;
    bool GetLoop()   const;
private:
    CSound();
    ~CSound();

    friend class CSoundManager;
};

