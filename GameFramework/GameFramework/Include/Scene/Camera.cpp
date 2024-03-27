#include "Camera.h"
#include "../Input.h"

void CCamera::Update(float _deltaTime)
{
	// 타겟이 존재할 경우
	if (m_target)
	{
		// 타겟이 죽은 상태면 nullptr로 만들어준다.
		if (!m_target->GetActive())
			m_target = nullptr;
		// 타겟이 살아있다면 
		else
			/*
				전체 월드 중 카메라 영역의 위치(카메라 영역 좌상단)를 잡아준다.
				아래 식에 따라 처음엔 0,0이 카메라 위치(좌상단)가 될 것이다.
			*/
			m_pos = m_target->GetPos() 
			- m_targetPivot * m_resolution + m_targetOffset;
	}

	// 아래는 카메라가 월드(전체 해상도)를 벗어나지 못하도록 하는 부분이다.
	
	// 카메라가 (전체 해상도의)왼쪽 최대 범위를 벗어나면 맞춰준다. 
	if (m_pos.x < 0.f)
		m_pos.x = 0.f;
	// 카메라가 오른쪽 최대 범위를 벗어나면 맞춰준다. 
	else if (m_pos.x + m_resolution.x > m_worldResolution.x)
		m_pos.x = m_worldResolution.x - m_resolution.x;

	// 카메라가 위쪽 최대 범위를 벗어나면 맞춰준다. 
	if (m_pos.y < 0.f)
		m_pos.y = 0.f;
	// 카메라가 아래쪽 최대 범위를 벗어나면 맞춰준다. 
	else if (m_pos.y + m_resolution.y > m_worldResolution.y)
		m_pos.y = m_worldResolution.y - m_resolution.y;

	// 구한 카메라 위치를 전달해 마우스 커서의 월드상 위치를 구한다.
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

