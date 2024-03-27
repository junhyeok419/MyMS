#include "ColliderCircle.h"
#include "../GameObject/GameObject.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "CollisionManager.h"
#include "ColliderBox.h"	// 원 대 박스 충돌 처리를 위해

bool CColliderCircle::Init()
{
	if (!CCollider::Init())
		return false;

	return true;
}

void CColliderCircle::Update(float _deltaTime)
{
	CCollider::Update(_deltaTime);
}

void CColliderCircle::PostUpdate(float _deltaTime)
{
	CCollider::PostUpdate(_deltaTime);

	/*
	   충돌체의 중점을 계속 업데이트 해준다. 
	
	   원 충돌체의 중점은 충돌체가 속한 오브젝트(Owner)의 pos OffSet을 
       더한 값이다. 
	*/
	Vector2	pos = m_owner->GetPos();
	m_info.Center = pos + m_offset;

	// 마우스 충돌 체크를 위한 bottom을 세팅 (원 충돌체)
	m_bottom = m_info.Center.y + m_info.Radius;
}

void CColliderCircle::Render(HDC _hDC, float _deltaTime)
{
	/*
		원 충돌체의 원은 LineTo를 이용한 선으로 그릴 것이다.
		ellipse는 내부가 채워져 있는 원이기 때문에,
		LineTo로 그려지는 것은 HPEN을 이용해 색상을 변경한다.

		** 먼저 MoveToEx를 이용해 중점에서 0도 각도로 반지름 만큼
		   떨어진 곳에 위치를 잡는다. 
		   이후 반복문으로 일정한 각도만큼 이동하면서 계속 선을 그린다.
		   사실은 원 충돌체는 원이 아니라 '다각형'인 것이다.
	*/
#ifdef _DEBUG

	// 초록색 펜 색상을 얻어온다.
	HPEN	Pen = CGameManager::GetInst()->GetPen(EBrushType::Green);

	// 충돌중이라면 빨간색 펜 색상을 얻어온다.
	if (!m_collisionList.empty() || m_mouseCollision) // 마우스 충돌의 경우에도 빨간색으로 바꿔준다.
		Pen = CGameManager::GetInst()->GetPen(EBrushType::Red);

	// 이전에 들어있던 기본 색상을 받아놓고, 초록(빨강)색으로 바꾼다.
	HPEN	PrevPen = (HPEN)SelectObject(_hDC, Pen);

	// 카메라를 얻어와 충돌체의 상대적인 실 위치를 구한다.
	CCamera* Camera = m_scene->GetCamera();

	Vector2	Pos = m_info.Center - Camera->GetPos();

	// 원 충돌체가 그려질 첫 좌표를 잡는다. 0도이므로 y좌표는 중점 그대로 사용한다.
	MoveToEx(_hDC, (long)(Pos.x + m_info.Radius), (long)Pos.y, nullptr);

	// 반복을 통해 12도씩 증가시키면서 선을 그린다.
	for (int i = 12; i <= 360; i += 12)
	{
		Vector2	Target;
		Target.x = Pos.x + cosf(DegreeToRadian((float)i)) * m_info.Radius;
		Target.y = Pos.y + sinf(DegreeToRadian((float)i)) * m_info.Radius;

		LineTo(_hDC, (long)Target.x, (long)Target.y);
	}

	// 사용이 끝났으면 원래 펜으로 돌려주어야 한다.
	SelectObject(_hDC, PrevPen);

#endif // _DEBUG
}

bool CColliderCircle::Collision(CCollider* _dest)
{
	switch (_dest->GetColliderType())
	{
		// Circle to Box 
	case EColliderType::Box:
		return CCollisionManager::GetInst()->CollisionBoxToCircle(m_hitPoint, (CColliderBox*)_dest, this);
		break;
		// Circle to Circle
	case EColliderType::Circle:
		return CCollisionManager::GetInst()->CollisionCircleToCircle(m_hitPoint, this, (CColliderCircle*)_dest);
	}
	return false;
}

bool CColliderCircle::CollisionMouse(const Vector2& _mouse)
{
	// 충돌 관리자의 '점 대 원 충돌' 체크 함수를 호출
	return CCollisionManager::GetInst()->
		CollisionPointToCircle(m_hitPoint, _mouse, m_info);
}

CircleInfo CColliderCircle::GetInfo() const
{
	return m_info;
}

void CColliderCircle::SetRadius(float _radius)
{
	m_info.Radius = _radius;
}

CColliderCircle::CColliderCircle()
{
	// 레퍼런스 클래스에 이름 등록
	SetTypeID<CColliderCircle>();

	// 충돌체 타입 : 원
	m_colliderType = EColliderType::Circle;

	// 반지름 초기화
	m_info.Radius = 30.f;
}

CColliderCircle::CColliderCircle(const CColliderCircle& _collider)
	: CCollider(_collider)
	, m_info(_collider.m_info)
{

}

CColliderCircle::~CColliderCircle()
{
}
