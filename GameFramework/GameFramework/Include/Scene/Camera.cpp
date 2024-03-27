#include "Camera.h"
#include "../Input.h"

void CCamera::Update(float _deltaTime)
{
	// Ÿ���� ������ ���
	if (m_target)
	{
		// Ÿ���� ���� ���¸� nullptr�� ������ش�.
		if (!m_target->GetActive())
			m_target = nullptr;
		// Ÿ���� ����ִٸ� 
		else
			/*
				��ü ���� �� ī�޶� ������ ��ġ(ī�޶� ���� �»��)�� ����ش�.
				�Ʒ� �Ŀ� ���� ó���� 0,0�� ī�޶� ��ġ(�»��)�� �� ���̴�.
			*/
			m_pos = m_target->GetPos() 
			- m_targetPivot * m_resolution + m_targetOffset;
	}

	// �Ʒ��� ī�޶� ����(��ü �ػ�)�� ����� ���ϵ��� �ϴ� �κ��̴�.
	
	// ī�޶� (��ü �ػ���)���� �ִ� ������ ����� �����ش�. 
	if (m_pos.x < 0.f)
		m_pos.x = 0.f;
	// ī�޶� ������ �ִ� ������ ����� �����ش�. 
	else if (m_pos.x + m_resolution.x > m_worldResolution.x)
		m_pos.x = m_worldResolution.x - m_resolution.x;

	// ī�޶� ���� �ִ� ������ ����� �����ش�. 
	if (m_pos.y < 0.f)
		m_pos.y = 0.f;
	// ī�޶� �Ʒ��� �ִ� ������ ����� �����ش�. 
	else if (m_pos.y + m_resolution.y > m_worldResolution.y)
		m_pos.y = m_worldResolution.y - m_resolution.y;

	// ���� ī�޶� ��ġ�� ������ ���콺 Ŀ���� ����� ��ġ�� ���Ѵ�.
	CInput::GetInst()->ComputeWorldMousePos(m_pos);
}

Vector2 CCamera::GetPos() const
{
	return m_pos;
}

Vector2 CCamera::GetResolution() const
{
	return m_resolution;
}

Vector2 CCamera::GetWorldResolution() const
{
	return m_worldResolution;
}

CGameObject* CCamera::GetTarget() const
{
	return m_target;
}

Vector2 CCamera::GetTargetOffset() const
{
	return m_targetOffset;
}

Vector2 CCamera::GetTargetPivot() const
{
	return m_targetPivot;
}

void CCamera::SetPos(const Vector2& _pos)
{
	m_pos = _pos;
}

void CCamera::SetPos(float _x, float _y)
{
	m_pos = Vector2(_x, _y);
}

void CCamera::SetResolution(const Vector2& _resolution)
{
	m_resolution = _resolution;
}

void CCamera::SetResolution(float _x, float _y)
{
	m_resolution = Vector2(_x, _y);
}

void CCamera::SetWorldResolution(const Vector2& _worldResolution)
{
	m_worldResolution = _worldResolution;
}

void CCamera::SetWorldResolution(float _x, float _y)
{
	m_worldResolution = Vector2(_x, _y);
}

void CCamera::SetTargetOffset(const Vector2& _targetOffset)
{
	m_targetOffset = _targetOffset;
}

void CCamera::SetTargetOffset(float _x, float _y)
{
	m_targetOffset = Vector2(_x, _y);
}

void CCamera::SetTargetPivot(const Vector2& _targetPivot)
{
	m_targetPivot = _targetPivot;
}

void CCamera::SetTargetPivot(float _x, float _y)
{
	m_targetPivot = Vector2(_x, _y);
}

void CCamera::SetTarget(CGameObject* _target)
{
	m_target = _target;
}

CCamera::CCamera()
{
}

CCamera::~CCamera()
{
}

