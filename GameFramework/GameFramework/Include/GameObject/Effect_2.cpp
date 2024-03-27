#include "Effect_2.h"

bool CEffect_2::Init()
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
	SetCurrentAnimationEndFunction<CEffect_2>(this, &CEffect_2::AnimationEnd);

	return true;
}

void CEffect_2::Update(float _deltaTime)
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
	// ����ƮŸ���� 'Once'�� ���, �ִϸ��̼� ���� �� ����Ʈ�� �����Ѵ�.
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
