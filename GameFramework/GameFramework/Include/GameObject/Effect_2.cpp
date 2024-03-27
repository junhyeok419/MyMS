#include "Effect_2.h"

bool CEffect_2::Init()
{
	/*
		이펙트도 애니메이션 기반이므로
		애니메이션을 1개 무조건 생성한다.
	*/
	CreateAnimation();

	/*
		어떤 이펙트 애니메이션이든, 끝나면
		같은 함수(AnimationEnd)가 호출될 수 있도록 한다.
	*/
	SetCurrentAnimationEndFunction<CEffect_2>(this, &CEffect_2::AnimationEnd);

	return true;
}

void CEffect_2::Update(float _deltaTime)
{
	CGameObject::Update(_deltaTime);

	// 이펙트 타입에 따라서 다른 업데이트 처리를 해야한다.

	/*
		이펙트 타입이 Duration(지속)일 경우 시간 체크를 하여,
		지속 시간을 초과할 경우에 제거한다.
	*/
	if (m_effectType == EEffectType::Duration)
	{
		m_time += _deltaTime;

		if (m_time >= m_duration)
			SetActive(false);
	}
}

void CEffect_2::PostUpdate(float _deltaTime)
{
	CGameObject::PostUpdate(_deltaTime);
}

void CEffect_2::Render(HDC _hDC, float _deltaTime)
{
	CGameObject::Render(_hDC, _deltaTime);
}

EEffectType CEffect_2::GetEffectType() const
{
	return m_effectType;
}

void CEffect_2::SetDuration(float _duration)
{
	m_duration = _duration;
}

void CEffect_2::AnimationEnd()
{
	// 이펙트타입이 'Once'일 경우, 애니메이션 종료 시 이펙트를 제거한다.
	if (m_effectType == EEffectType::Once)
		SetActive(false);
}

CEffect_2::CEffect_2()
	: m_effectType(EEffectType::Once)
	, m_duration(0.f)
	, m_time(0.f)
{
	m_renderLayer = ERenderLayer::Effect2;
}

CEffect_2::CEffect_2(const CEffect_2& _obj)
	: CGameObject(_obj)
{
}

CEffect_2::~CEffect_2()
{
}
