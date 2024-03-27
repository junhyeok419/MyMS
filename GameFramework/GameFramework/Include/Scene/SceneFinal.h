#pragma once
#include "Scene.h"
class CSceneFinal :
    public CScene
{
private:


public:
    bool Init();
private:
    void CreateAnimationSequence_Effect();  // 이펙트
    void CreateAnimationSequence();  // 플레이어1
    void CreateAnimationSequence1();  // 플레이어2
    void CreateAnimationSequence2(); // 주니어발록
    void CreateAnimationSequence3(); // 타우로마시스
    void CreateAnimationSequence4(); // 타우로스피어
    void CreateAnimationSequence5(); // 와일드카고
    void CreateAnimationSequence6(); // 기타오브젝트
    void CreateAnimationBallogKing();  // 보스몹
protected:
    CSceneFinal();
    virtual ~CSceneFinal();

    friend class CSceneManager;
};

