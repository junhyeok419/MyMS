#pragma once
#include "Scene.h"
class CScene3 :
    public CScene
{
private:


public:
    bool Init();
private:
    void CreateAnimationSequence_Effect();  // ����Ʈ
    void CreateAnimationSequence();  // �÷��̾�1
    void CreateAnimationSequence1();  // �÷��̾�2
    void CreateAnimationSequence2(); // �ִϾ�߷�
    void CreateAnimationSequence3(); // Ÿ��θ��ý�
    void CreateAnimationSequence4(); // Ÿ��ν��Ǿ�
    void CreateAnimationSequence5(); // ���ϵ�ī��
    void CreateAnimationSequence6(); // ��Ÿ������Ʈ
protected:
    CScene3();
    virtual ~CScene3();

    friend class CSceneManager;
};

