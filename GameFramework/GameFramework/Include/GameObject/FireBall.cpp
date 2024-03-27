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

	// �Ҹ� ��ġ(������ �߻���ü���� ���� ����), ũ��, �Ǻ� ����
	SetPos(900.f, 100.f);
	SetSize(50.f, 50.f);
	SetPivot(0.5f, 0.5f);

	// �� ������Ʈ�� �ִϸ��̼��� �����Ѵ�.
	CreateAnimation();

	AddAnimation("BallogLeftFireBall", true, 0.2f);   // ���� ���� ���̾
	AddAnimation("BallogRightFireBall", true, 0.2f);   // ������ ���� ���̾


	// �Ҹ��� �浹ü�� �� �浹ü�� �Ѵ�.
	CColliderCircle* circle = AddCollider<CColliderCircle>("FireBall");

	circle->SetRadius(15.f);
	circle->SetOffset(16.f, -17.f);

	return true;
}

void CFireBall::Update(float _deltaTime)
{
	CGameObject::Update(_deltaTime);

	


	///*
	//	cos 0, 90, 180, 270    ->  cos��Ÿ 1, 0, -1, 0  (���� �ݺ�)
	//	sin 0, 90, 180, 270    ->  sin��Ÿ 0, 1, 0, -1  (���� �ݺ�)

	//	cos�� sin�� ������ �ش��ϴ� ��Ÿ�� x,y��ǥ���Ͽ� ���� ������Ű��,
	//	���� �ѷ��� 4���� ���´�.
	//	��, �Ҹ��� ���� ��ǥ�� cos��Ÿ�� x��ǥ��, sin��Ÿ�� y��ǥ�� ����Ѵ�.

	//	�Ҹ��� �߻�Ǵ� ��ǥ(-> m_pos.x + m_moveSpeed * _deltaTime) �� 
	//	����(-> cosf(DegreeToRadian(m_angle)) )�� ���Ͽ�, ������ ���� 
	//	�ٸ� �������� �߻�ǰ� ���� ���̴�.
	//	
	//	'����'�� �߻���ü ��ü���� �Ź� ���� �޴´�.

	//	cosf : ���Ȱ��� ���ڷ� con��Ÿ�� ���Ѵ�.
	//	sinf : ���Ȱ��� ���ڷ� sin��Ÿ�� ���Ѵ�.
	//*/
	//m_pos.x = m_pos.x + cosf(DegreeToRadian(m_angle)) * m_moveSpeed * _deltaTime;
	//m_pos.y = m_pos.y + sinf(DegreeToRadian(m_angle)) * m_moveSpeed * _deltaTime;


	// distance(�ִ� ��Ÿ�)���� �̵� �Ÿ��� ����Ű�ٰ� 
	//m_distance -= m_moveSpeed * _deltaTime;

	///*
	//	�ִ� �Ÿ��� �����ϸ� �Ҹ��� ���δ�. (ȭ�鿡 ���°� ������ �������� �´�)

	//	�ܼ��� �Ѿ��� ��Ȱ��ȭ �� ���� enable�� on/off�Ѵ�.
	//	�׷��� �ϸ� Update�� Render�� �ߴܽ�ų �� �ִ�.
	//*/

	Move(m_angle); // ���ϴ� ������ �ӵ���ŭ �̵���Ų��.

	// distance(�ִ� ��Ÿ�)���� �̵� �Ÿ��� ���ҽ�Ű�ٰ�
	m_distance -= m_moveSpeed * _deltaTime;
	/*
		�ִ� �Ÿ��� �����ϸ� �Ҹ��� ���δ�. (ȭ�鿡 ���°� ������ �������� �´�)

		�ܼ��� �Ѿ��� ��Ȱ��ȭ �� ���� enable�� on/off�Ѵ�.
		�׷��� �ϸ� Update�� Render�� �ߴܽ�ų �� �ִ�.
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
	// ��ü ���� �� Ÿ�� ���̵�(���۷��� Ŭ������ ���)�� �ʱ�ȭ
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
