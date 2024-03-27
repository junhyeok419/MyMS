#pragma once
#include "GameObject.h"

/*
	����Ʈ�� ��Ÿ���� Ŭ�����̴�.
	����Ʈ�� ũ��, Ÿ�� ����Ʈó�� 1ȸ�� ����ǰ� ���ŵǰų�
	������ ó�� ���� �ð����� �ݺ�����Ͽ� �����ִ� ����Ʈ��
	�з��� �� �ִ�.

	����Ʈ�� �ִϸ��̼��� ���� ������Ʈ�̴�.
*/
class CEffect :
    public CGameObject
{
private:
	EEffectType 	m_effectType;	// ����Ʈ Ÿ��
	float			m_duration;		// ����Ʈ ���ӽð�
	float			m_time;			// �ð� üũ ����(������)
public:
	virtual bool Init();
	virtual void Update(float _deltaTime);
	virtual void PostUpdate(float _deltaTime);
	virtual void Render(HDC _hDC, float _deltaTime);
public:
	EEffectType GetEffectType() const;
	void SetEffectType(EEffectType _type);
	void SetDuration(float _duration);
private:
	void AnimationEnd();
protected:
	CEffect();
	CEffect(const CEffect& _obj);
	virtual ~CEffect();
	
	friend class CScene;
};

