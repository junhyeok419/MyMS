#pragma once
#include "GameObject.h"
class CEffect_2 :
    public CGameObject
{
private:
	EEffectType 	m_effectType;	// 이펙트 타입
	float			m_duration;		// 이펙트 지속시간
	float			m_time;			// 시간 체크 변수(축적용)
public:
	virtual bool Init();
	virtual void Update(float _deltaTime);
	virtual void PostUpdate(float _deltaTime);
	virtual void Render(HDC _hDC, float _deltaTime);
public:
	EEffectType GetEffectType() const;
	void SetDuration(float _duration);
private:
	void AnimationEnd();
protected:
	CEffect_2();
	CEffect_2(const CEffect_2& _obj);
	virtual ~CEffect_2();

	friend class CScene;
};

