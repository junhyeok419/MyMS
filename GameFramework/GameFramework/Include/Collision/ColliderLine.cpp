#include "ColliderLine.h"
#include "../GameObject/GameObject.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "CollisionManager.h"
#include "ColliderCircle.h" // 선 대 원 충돌 처리를 위해
#include "ColliderBox.h" // 선 대 박스 충돌 처리를 위해

bool CColliderLine::Init()
{
	if (!CCollider::Init())
		return false;

	return true;
}

void CColliderLine::Update(float _deltaTime)
{
	CCollider::Update(_deltaTime);
}

void CColliderLine::PostUpdate(float _deltaTime)
{
	CCollider::PostUpdate(_deltaTime);
}

void CColliderLine::Render(HDC _hDC, float _deltaTime)
{
	/*
		디버그 모드일 경우에만 충돌체를 눈에 보이게 할 것이다.
		ifdef _DEBUG : 디버그 모드일 때만 실행된다.
		ifdef NDEBUG : 릴리즈 모드일 때만 실행된다.
	*/

	/*
		박스 충돌체의 사각형은  프레임렉트 (가운데가 비어있는,
		선으로만 이루어진) 방식으로 그릴 것이다.

		프레임렉트 방식은 Hbrush 라는 것을 이용해 선을 어떤 색으로 할 지
		결정한다.
	*/
	
#ifdef _DEBUG

	// 기본으로, 게임매니저에서 초록색 브러쉬를 얻어와 그릴 것이다..
	HPEN pen = CGameManager::GetInst()->GetPen(EBrushType::Green);
	
	/*
		'충돌 목록 리스트'가 비어있지 않다는 것은 현재 충돌중이라는 것이다.
		충돌중일 경우엔 빨간색 브러쉬를 얻어와 그릴 것이다.
	*/
	if (!m_collisionList.empty() || m_mouseCollision)  // 마우스 충돌의 경우에도 빨간색으로 바꿔준다.
 		pen = CGameManager::GetInst()->GetPen(EBrushType::Red);

	// 이전에 들어있던 기본 색상을 받아놓고, 초록(빨강)색으로 바꾼다.
	HPEN	PrevPen = (HPEN)SelectObject(_hDC, pen);

	// 상대적인 위치로 그려야 한다. (이거 안하면 따라다님)
	CCamera* camera = m_scene->GetCamera();

	//RECT	renderRC;

	//renderRC.left = (long)(m_info.Point1.x - camera->GetPos().x);
	//renderRC.top = (long)(m_info.Point1.y - camera->GetPos().y);
	//renderRC.right = (long)(m_info.Point2.x - camera->GetPos().x);
	//renderRC.bottom = (long)(m_info.Point2.y - camera->GetPos().y);

	//// 2번째 인자의 도형을 3번째 인자의 브러쉬 색상으로 그린다.
	//FrameRect(_hDC, &renderRC, brush);

	// 색상 안바뀌어서 이거로 하면 안될듯
	MoveToEx(_hDC, m_info.Point1.x - camera->GetPos().x, m_info.Point1.y - camera->GetPos().y, nullptr);
	LineTo(_hDC, m_info.Point2.x - camera->GetPos().x, m_info.Point2.y - camera->GetPos().y);

	SelectObject(_hDC, PrevPen);

#endif // _DEBUG
}

bool CColliderLine::Collision(CCollider* _dest)
{
	// 상대방 충돌체(_dest)의 모양에 따라 다르게 충돌 처리를 한다.
	switch (_dest->GetColliderType())
	{
	case EColliderType::Box:
		return CCollisionManager::GetInst()->
			CollisionBoxToLine(m_hitPoint, (CColliderBox*)_dest, this);
		// Line to Line
	/*case EColliderType::Line:
		return CCollisionManager::GetInst()->
			CollisionLineToLine(m_hitPoint, this, (CColliderLine*)_dest);*/
		// Line to Circle
	/*case EColliderType::Circle:
		return CCollisionManager::GetInst()->CollisionLineToCircle(m_hitPoint, this, (CColliderCircle*)_dest);*/
	}

	return false;
}

//bool CColliderLine::CollisionMouse(const Vector2& _mouse)
//{
//	// 충돌 관리자의 '점 대 사각형 충돌' 체크 함수를 호출
//	/*return CCollisionManager::GetInst()->
//		CollisionPointToLine(m_hitPoint, _mouse, m_info);*/
//}

const LineInfo& CColliderLine::GetLineInfo() const
{
	return m_info;
}

ELineType CColliderLine::GetType() const
{
	return m_type;
}

LineInfo CColliderLine::GetInfo() const
{
	return m_info;
}

void CColliderLine::SetType(ELineType _type)
{
	m_type = _type;
}

void CColliderLine::SetInfo(const Vector2& _pos1, const Vector2& _pos2)
{
	m_info.Point1 = _pos1;
	m_info.Point2 = _pos2;
}

void CColliderLine::SetLength(float _length)
{
	m_length = _length;
}

const float& CColliderLine::GetLength() const
{
	return m_length;
}

CColliderLine::CColliderLine()
	: m_length(0.f)
{
	// 첫 초기화시 레퍼런스 클래스에 이름를 등록한다.
	SetTypeID<CColliderLine>();

	// 충돌 타입을 '박스'로 설정한다.
	m_colliderType = EColliderType::Line;
}

CColliderLine::CColliderLine(const CColliderLine& _collider)
	: CCollider(_collider)
	, m_length(_collider.m_length)
	, m_info(_collider.m_info)
{
}

CColliderLine::~CColliderLine()
{
}
