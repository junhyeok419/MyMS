#pragma once
#include "GameObject.h"

/*
	이펙트를 나타내는 클래스이다.
	이펙트는 크게, 타격 이펙트처럼 1회만 재생되고 제거되거나
	오오라 처럼 일정 시간동안 반복재생하여 남아있는 이펙트로
	분류할 수 있다.

	이펙트는 애니메이션을 갖는 오브젝트이다.
*/
class CEffect :
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

