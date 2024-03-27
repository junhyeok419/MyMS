#include "ColliderBox.h"
#include "../GameObject/GameObject.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "CollisionManager.h"
#include "ColliderCircle.h" // 박스 대 원 충돌 처리를 위해
#include "ColliderLine.h"

bool CColliderBox::Init()
{
	if (!CCollider::Init())
		return false;

	return true;
}

void CColliderBox::Update(float _deltaTime)
{
	CCollider::Update(_deltaTime);
}

void CColliderBox::PostUpdate(float _deltaTime)
{
	CCollider::PostUpdate(_deltaTime);

	/*
		충돌체가 속한 오브젝트(owner)의 위치에 offset 만큼
		더한 위치가 박스 충돌체의 중심이다. 
		그렇게 나온 중심에 박스 사이즈의 절반만큼 +-해주면
		박스의 leftTop, rightBottom 을 구할 수 있다.
	*/
	Vector2	pos = m_owner->GetPos();
	Vector2	size(m_width, m_height);

	m_info.Lt = pos + m_offset - size / 2.f;
	m_info.Rb = pos + m_offset + size / 2.f;

	// 마우스 충돌 체크를 위한 bottom을 세팅 (사각형 충돌체)
	m_bottom = m_info.Rb.y;
}

void CColliderBox::Render(HDC _hDC, float _deltaTime)
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
	HBRUSH	brush = CGameManager::GetInst()->GetBrush(EBrushType::Green);

	/*
		'충돌 목록 리스트'가 비어있지 않다는 것은 현재 충돌중이라는 것이다.
		충돌중일 경우엔 빨간색 브러쉬를 얻어와 그릴 것이다.
	*/
	if (!m_collisionList.empty() || m_mouseCollision)  // 마우스 충돌의 경우에도 빨간색으로 바꿔준다.
		brush = CGameManager::GetInst()->GetBrush(EBrushType::Red);

	/*
		충돌체의 위치도 마찬가지로, 카메라 위치에 따른 
		상대적인 실제 충돌체의 위치를 구한다.
	*/
	CCamera* camera = m_scene->GetCamera();

	RECT	renderRC;

	renderRC.left = (long)(m_info.Lt.x - camera->GetPos().x);
	renderRC.top = (long)(m_info.Lt.y - camera->GetPos().y);
	renderRC.right = (long)(m_info.Rb.x - camera->GetPos().x);
	renderRC.bottom = (long)(m_info.Rb.y - camera->GetPos().y);

	// 2번째 인자의 도형을 3번째 인자의 브러쉬 색상으로 그린다.
	FrameRect(_hDC, &renderRC, brush);

#endif // _DEBUG
}

bool CColliderBox::Collision(CCollider* _dest)
{
	// 상대방 충돌체(_dest)의 모양에 따라 다르게 충돌 처리를 한다.
	switch (_dest->GetColliderType())
	{
		// Box to Box
	case EColliderType::Box:
		return CCollisionManager::GetInst()->
			CollisionBoxToBox(m_hitPoint, this, (CColliderBox*)_dest);
		// Box to Circle
	case EColliderType::Circle:
		return CCollisionManager::GetInst()->CollisionBoxToCircle(m_hitPoint, this, (CColliderCircle*)_dest);
	case EColliderType::Line:
		return CCollisionManager::GetInst()->CollisionBoxToLine(m_hitPoint, this, (CColliderLine*)_dest);
	}

	return false;
}

bool CColliderBox::CollisionMouse(const Vector2& _mouse)
{
	// 충돌 관리자의 '점 대 사각형 충돌' 체크 함수를 호출
	return CCollisionManager::GetInst()->
		CollisionPointToBox(m_hitPoint, _mouse, m_info);
}

BoxInfo CColliderBox::GetInfo() const
{
	return m_info;
}

void CColliderBox::SetInfo(const Vector2& _lt, const Vector2& _rb)
{
	m_info.Lt = _lt;
	m_info.Rb = _rb;
}

const BoxInfo& CColliderBox::GetBoxInfo() const
{
	return m_info;
}

void CColliderBox::SetExtent(float _width, float _height)
{
	m_width = _width;
	m_height = _height;
}

void CColliderBox::SetExtent(const Vector2& _size)
{
	m_width = _size.x;
	m_height = _size.y;
}

const Vector2& CColliderBox::GetExtent() const
{
	return Vector2(m_width, m_height);
}

CColliderBox::CColliderBox()
	: m_width(100.f)
	, m_height(100.f)
{
	// 첫 초기화시 레퍼런스 클래스에 이름를 등록한다.
	SetTypeID<CColliderBox>();

	// 충돌 타입을 '박스'로 설정한다.
	m_colliderType = EColliderType::Box;
}

CColliderBox::CColliderBox(const CColliderBox& _collider)
	: CCollider(_collider)
	 ,m_width(_collider.m_width)
	 ,m_height(_collider.m_height)
	 ,m_info(_collider.m_info)
{
}

CColliderBox::~CColliderBox()
{
}
