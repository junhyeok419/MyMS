#include "FireBall.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderCircle.h"
#include "Effect.h"
#include "Effect_2.h"

bool CFireBall::Init()
{
	m_moveSpeed = 200.f;
	m_angle = 180.f;
	m_distance = 600.f;

	// 불릿 위치(어차피 발사주체에서 조정 받음), 크기, 피봇 설정
	SetPos(900.f, 100.f);
	SetSize(50.f, 50.f);
	SetPivot(0.5f, 0.5f);

	// 이 오브젝트의 애니메이션을 생성한다.
	CreateAnimation();

	AddAnimation("BallogLeftFireBall", true, 0.2f);   // 왼쪽 방향 파이어볼
	AddAnimation("BallogRightFireBall", true, 0.2f);   // 오른쪽 방향 파이어볼


	// 불릿의 충돌체를 원 충돌체로 한다.
	CColliderCircle* circle = AddCollider<CColliderCircle>("FireBall");

	circle->SetRadius(15.f);
	circle->SetOffset(16.f, -17.f);

	return true;
}

void CFireBall::Update(float _deltaTime)
{
	CGameObject::Update(_deltaTime);

	


	///*
	//	cos 0, 90, 180, 270    ->  cos세타 1, 0, -1, 0  (이후 반복)
	//	sin 0, 90, 180, 270    ->  sin세타 0, 1, 0, -1  (이후 반복)

	//	cos와 sin의 각도에 해당하는 세타를 x,y좌표로하여 서로 대응시키면,
	//	원의 둘레의 4점이 나온다.
	//	즉, 불릿의 방향 좌표에 cos세타를 x좌표로, sin세타를 y좌표로 사용한다.

	//	불릿이 발사되는 좌표(-> m_pos.x + m_moveSpeed * _deltaTime) 에 
	//	각도(-> cosf(DegreeToRadian(m_angle)) )를 곱하여, 각도에 따라 
	//	다른 방향으로 발사되게 만들 것이다.
	//	
	//	'각도'는 발사주체 객체에서 매번 갱신 받는다.

	//	cosf : 라디안값을 인자로 con세타를 구한다.
	//	sinf : 라디안값을 인자로 sin세타를 구한다.
	//*/
	//m_pos.x = m_pos.x + cosf(DegreeToRadian(m_angle)) * m_moveSpeed * _deltaTime;
	//m_pos.y = m_pos.y + sinf(DegreeToRadian(m_angle)) * m_moveSpeed * _deltaTime;


	// distance(최대 사거리)에서 이동 거리를 감소키다가 
	//m_distance -= m_moveSpeed * _deltaTime;

	///*
	//	최대 거리에 도달하면 불릿을 죽인다. (화면에 남는게 보여도 지워진게 맞다)

	//	단순히 총알을 비활성화 할 때는 enable로 on/off한다.
	//	그렇게 하면 Update와 Render를 중단시킬 수 있다.
	//*/

	Move(m_angle); // 원하는 각도로 속도만큼 이동시킨다.

	// distance(최대 사거리)에서 이동 거리를 감소시키다가
	m_distance -= m_moveSpeed * _deltaTime;
	/*
		최대 거리에 도달하면 불릿을 죽인다. (화면에 남는게 보여도 지워진게 맞다)

		단순히 총알을 비활성화 할 때는 enable로 on/off한다.
		그렇게 하면 Update와 Render를 중단시킬 수 있다.
	*/
	if (m_distance <= 0.f)
	{
		SetActive(false);
	}

}

void CFireBall::PostUpdate(float _deltaTime)
{
	CGameObject::PostUpdate(_deltaTime);
}

void CFireBall::Render(HDC _hDC, float _deltaTime)
{
	CGameObject::Render(_hDC, _deltaTime);
}

void CFireBall::SetDamage(float _damage)
{
	m_damage = _damage;
}

void CFireBall::SetAngle(float _angle)
{
	m_angle = _angle;
}

void CFireBall::SetDistance(float _distance)
{
	m_distance = _distance;
}

void CFireBall::CollisionBegin(CCollider* _src, CCollider* _dest)
{
	
}

void CFireBall::CollisionEnd(CCollider* _src, CCollider* _dest)
{
}

CFireBall::CFireBall()
	: m_damage(0.f)
{
	// 객체 생성 시 타입 아이디(레퍼런스 클래스의 멤버)를 초기화
	SetTypeID<CFireBall>();
	m_renderLayer = ERenderLayer::Effect;
}

CFireBall::CFireBall(const CFireBall& _obj)
	: CBallog(_obj)
	, m_angle(_obj.m_angle)
	, m_distance(_obj.m_distance)
{
}

CFireBall::~CFireBall()
{
}
