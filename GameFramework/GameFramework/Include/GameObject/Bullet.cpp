#include "Bullet.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderCircle.h"
#include "Effect.h"

bool CBullet::Init()
{
	m_moveSpeed = 700.f;
	m_distance = 300.f;
	m_angle = 180.f;

	// 불릿 위치(어차피 발사주체에서 조정 받음), 크기, 피봇 설정
	SetPos(900.f, 100.f);
	SetSize(50.f, 50.f);
	SetPivot(0.5f, 0.5f);

	//// 불릿에 박스충돌체를 생성한다.
	//CColliderBox* Box = AddCollider<CColliderBox>("Body");

	//Box->SetExtent(100.f, 100.f);

	//Box->SetCollisionBeginFunction<CBullet>(this, &CBullet::CollisionBegin);
	//Box->SetCollisionEndFunction<CBullet>(this, &CBullet::CollisionEnd);
	
	// 불릿의 충돌체를 원 충돌체로 한다.
	CColliderCircle* circle = AddCollider<CColliderCircle>("Body");

	circle->SetRadius(25.f);

	// 지금 세팅 필요 없다? 아마 아직 원대 사각형 충돌을 못햇으므로
	// Circle->SetCollisionProfile("MonsterAttack"); 

	circle->SetCollisionBeginFunction<CBullet>(this, &CBullet::CollisionBegin);
	circle->SetCollisionEndFunction<CBullet>(this, &CBullet::CollisionEnd);
	return true;
}

void CBullet::Update(float _deltaTime)
{
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

	CGameObject::Update(_deltaTime);

	Move(m_angle); // 원하는 각도로 속도만큼 이동시킨다.

	// distance(최대 사거리)에서 이동 거리를 감소키다가
	m_distance -= m_moveSpeed * _deltaTime;

	/*
		최대 거리에 도달하면 불릿을 죽인다. (화면에 남는게 보여도 지워진게 맞다)

		단순히 총알을 비활성화 할 때는 enable로 on/off한다.
		그렇게 하면 Update와 Render를 중단시킬 수 있다.
	*/
	if (m_distance <= 0.f)
		SetActive(false);
		
}

void CBullet::PostUpdate(float _deltaTime)
{
	CGameObject::PostUpdate(_deltaTime);
}

void CBullet::Render(HDC _hDC, float _deltaTime)
{
	CGameObject::Render(_hDC, _deltaTime);

	// 불릿이 그려질 좌상단 좌표를 구한다.
	Vector2 renderLT;
	renderLT = m_pos - m_pivot * m_size - m_scene->GetCamera()->GetPos();

	// 불릿을 그린다.
	Ellipse(_hDC, (int)renderLT.x, (int)renderLT.y,
		(int)(renderLT.x + m_size.x), (int)(renderLT.y + m_size.y));
}

void CBullet::SetDamage(float _damage)
{
	m_damage = _damage;
}

void CBullet::SetAngle(float _angle)
{
	m_angle = _angle;
}

void CBullet::SetDistance(float _distance)
{
	m_distance = _distance;
}

void CBullet::CollisionBegin(CCollider* _src, CCollider* _dest)
{
	// 불릿이 오브젝트와 충돌하는 순간, 바로 삭제시킨다.
	SetActive(false);

	//// 동시에 히트 이펙트를 생성한다. Once이므로 바로 삭제될 것이다.
	//CEffect* effect = m_scene->CreateObject<CEffect>("HitEffect");

	//// 이펙트의 위치는 히트 포인트(충돌 영역 중간)로 할 것이다.
	//effect->SetPivot(0.5f, 0.5f);
	//effect->SetPos(_src->GetHitPoint());
	//
	//// 애니메이션 추가 (애니메이션 이름, 루프여부, 플레이타임)
	//effect->AddAnimation("LeftHitEffect", false, 0.3f);

	/*
	   Damage 처리
	   불릿 충돌체(_src)에 의해 _dest 충돌체가 속한 오브젝트에게 
	   데미지를 입히도록 함수를 호출 

	   플레이어와 몬스터에서 설정한 불릿의 데미지에 따라
	   누가 발사했는지에 따라 입는 데미지가 달라질 것이다.
	*/
	_dest->GetOwner()->InflictDamage(m_damage);
}

void CBullet::CollisionEnd(CCollider* _src, CCollider* _dest)
{
}

CBullet::CBullet()
	: m_damage(0.f)
{
	// 객체 생성 시 타입 아이디(레퍼런스 클래스의 멤버)를 초기화
	SetTypeID<CBullet>();
}

CBullet::CBullet(const CBullet& _obj)
	: CGameObject(_obj)
	, m_angle(_obj.m_angle)
	, m_distance(_obj.m_distance)
{
}

CBullet::~CBullet()
{
}
