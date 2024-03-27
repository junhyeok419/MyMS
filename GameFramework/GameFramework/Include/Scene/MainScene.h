#pragma once

#include "Scene.h"

// ���� ��
class CMainScene :
    public CScene
{
private:
    // CSharedPtr<class CMonster> m_monster; ī�޶� ��ȯ �ù� �ڵ�
public:
    bool Init();
private:
    void CreateAnimationSequence_Effect(); // ����Ʈ
    void CreateAnimationSequence();  // �÷��̾�1
    void CreateAnimationSequence1();  // �÷��̾�2
    void CreateAnimationSequence2(); // �ִϾ�߷�
    void CreateAnimationSequence3(); // Ÿ��θ��ý�
    void CreateAnimationSequence4(); // Ÿ��ν��Ǿ�
    void CreateAnimationSequence5(); // ���ϵ�ī��
    void CreateAnimationSequence6(); // ��Ÿ������Ʈ
    void Cam1Key();
    void Cam2Key();
protected:
    CMainScene();
    virtual ~CMainScene();

    friend class CSceneManager;
};

