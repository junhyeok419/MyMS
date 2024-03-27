#include "Effect.h"

bool CEffect::Init()
{
	/*
		����Ʈ�� �ִϸ��̼� ����̹Ƿ�
		�ִϸ��̼��� 1�� ������ �����Ѵ�.
	*/
	CreateAnimation();

	/*
		� ����Ʈ �ִϸ��̼��̵�, ������
		���� �Լ�(AnimationEnd)�� ȣ��� �� �ֵ��� �Ѵ�.
	*/
	SetCurrentAnimationEndFunction<CEffect>(this, &CEffect::AnimationEnd);

	return true;
}

void CEffect::Update(float _deltaTime)
{
	CGameObject::Update(_deltaTime);

	// ����Ʈ Ÿ�Կ� ���� �ٸ� ������Ʈ ó���� �ؾ��Ѵ�.

	/*
		����Ʈ Ÿ���� Duration(����)�� ��� �ð� üũ�� �Ͽ�,
		���� �ð��� �ʰ��� ��쿡 �����Ѵ�.
	*/
	if (m_effectType == EEffectType::Duration)
	{
		m_time += _deltaTime;

		if (m_time >= m_duration)
			SetActive(false);
	}
}

void CEffect::PostUpdate(float _deltaTime)
{
	CGameObject::PostUpdate(_deltaTime);
}

void CEffect::Render(HDC _hDC, float _deltaTime)
{
	CGameObject::Render(_hDC, _deltaTime);
}

EEffectType CEffect::GetEffectType() const
{
	return m_effectType;
}

void CEffect::SetEffectType(EEffectType _type)
{
	m_effectType = _type;
}

void CEffect::SetDuration(float _duration)
{
	m_duration = _duration;
}

void CEffect::AnimationEnd()
{
	// ����ƮŸ���� 'Once'�� ���, �ִϸ��̼� ���� �� ����Ʈ�� �����Ѵ�.
	if (m_effectType == EEffectType::Once)
		SetActive(false);
}

CEffect::CEffect()
	: m_effectType(EEffectType::Once)
	, m_duration(0.f)
	, m_time(0.f)
{
	m_renderLayer = ERenderLayer::Effect;
}

CEffect::CEffect(const CEffect& _obj)
	: CGameObject(_obj)
{
}

CEffect::~CEffect()
{
}
