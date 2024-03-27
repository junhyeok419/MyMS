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

	// �Ҹ� ��ġ(������ �߻���ü���� ���� ����), ũ��, �Ǻ� ����
	SetPos(900.f, 100.f);
	SetSize(50.f, 50.f);
	SetPivot(0.5f, 0.5f);

	//// �Ҹ��� �ڽ��浹ü�� �����Ѵ�.
	//CColliderBox* Box = AddCollider<CColliderBox>("Body");

	//Box->SetExtent(100.f, 100.f);

	//Box->SetCollisionBeginFunction<CBullet>(this, &CBullet::CollisionBegin);
	//Box->SetCollisionEndFunction<CBullet>(this, &CBullet::CollisionEnd);
	
	// �Ҹ��� �浹ü�� �� �浹ü�� �Ѵ�.
	CColliderCircle* circle = AddCollider<CColliderCircle>("Body");

	circle->SetRadius(25.f);

	// ���� ���� �ʿ� ����? �Ƹ� ���� ���� �簢�� �浹�� �������Ƿ�
	// Circle->SetCollisionProfile("MonsterAttack"); 

	circle->SetCollisionBeginFunction<CBullet>(this, &CBullet::CollisionBegin);
	circle->SetCollisionEndFunction<CBullet>(this, &CBullet::CollisionEnd);
	return true;
}

void CBullet::Update(float _deltaTime)
{
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

	CGameObject::Update(_deltaTime);

	Move(m_angle); // ���ϴ� ������ �ӵ���ŭ �̵���Ų��.

	// distance(�ִ� ��Ÿ�)���� �̵� �Ÿ��� ����Ű�ٰ�
	m_distance -= m_moveSpeed * _deltaTime;

	/*
		�ִ� �Ÿ��� �����ϸ� �Ҹ��� ���δ�. (ȭ�鿡 ���°� ������ �������� �´�)

		�ܼ��� �Ѿ��� ��Ȱ��ȭ �� ���� enable�� on/off�Ѵ�.
		�׷��� �ϸ� Update�� Render�� �ߴܽ�ų �� �ִ�.
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

	// �Ҹ��� �׷��� �»�� ��ǥ�� ���Ѵ�.
	Vector2 renderLT;
	renderLT = m_pos - m_pivot * m_size - m_scene->GetCamera()->GetPos();

	// �Ҹ��� �׸���.
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
	// �Ҹ��� ������Ʈ�� �浹�ϴ� ����, �ٷ� ������Ų��.
	SetActive(false);

	//// ���ÿ� ��Ʈ ����Ʈ�� �����Ѵ�. Once�̹Ƿ� �ٷ� ������ ���̴�.
	//CEffect* effect = m_scene->CreateObject<CEffect>("HitEffect");

	//// ����Ʈ�� ��ġ�� ��Ʈ ����Ʈ(�浹 ���� �߰�)�� �� ���̴�.
	//effect->SetPivot(0.5f, 0.5f);
	//effect->SetPos(_src->GetHitPoint());
	//
	//// �ִϸ��̼� �߰� (�ִϸ��̼� �̸�, ��������, �÷���Ÿ��)
	//effect->AddAnimation("LeftHitEffect", false, 0.3f);

	/*
	   Damage ó��
	   �Ҹ� �浹ü(_src)�� ���� _dest �浹ü�� ���� ������Ʈ���� 
	   �������� �������� �Լ��� ȣ�� 

	   �÷��̾�� ���Ϳ��� ������ �Ҹ��� �������� ����
	   ���� �߻��ߴ����� ���� �Դ� �������� �޶��� ���̴�.
	*/
	_dest->GetOwner()->InflictDamage(m_damage);
}

void CBullet::CollisionEnd(CCollider* _src, CCollider* _dest)
{
}

CBullet::CBullet()
	: m_damage(0.f)
{
	// ��ü ���� �� Ÿ�� ���̵�(���۷��� Ŭ������ ���)�� �ʱ�ȭ
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
