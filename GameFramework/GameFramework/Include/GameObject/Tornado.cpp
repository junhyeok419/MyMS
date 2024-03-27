#include "Tornado.h"

bool CTornado::Init()
{
	m_moveSpeed = 400.f;
	m_distance = 600.f;
	m_angle = 180.f;
	m_rotationAngle = 0.f;
	m_range = 100.f;

	// ����̵� ��ġ(������ �߻���ü���� ���� ����), ũ��, �Ǻ� ����
	SetPos(900.f, 100.f);
	SetSize(50.f, 50.f);
	SetPivot(0.5f, 0.5f);

	return true;
}

void CTornado::Update(float _deltaTime)
{
	/*
		cos 0, 90, 180, 270    ->  cos��Ÿ 1, 0, -1, 0  (���� �ݺ�)
		sin 0, 90, 180, 270    ->  sin��Ÿ 0, 1, 0, -1  (���� �ݺ�)

		cos�� sin�� ������ �ش��ϴ� ��Ÿ�� x,y��ǥ���Ͽ� ���� ������Ű��,
		���� �ѷ��� 4���� ���´�.
		��, �Ҹ��� ���� ��ǥ�� cos��Ÿ�� x��ǥ��, sin��Ÿ�� y��ǥ�� ����Ѵ�.

		�Ҹ��� �߻�Ǵ� ��ǥ(-> m_pos.x + m_moveSpeed * _deltaTime) ��
		����(-> cosf(DegreeToRadian(m_angle)) )�� ���Ͽ�, ������ ����
		�ٸ� �������� �߻�ǰ� ���� ���̴�.

		'����'�� �߻���ü ��ü���� �Ź� ���� �޴´�.

		cosf : ���Ȱ��� ���ڷ� con��Ÿ�� ���Ѵ�.
		sinf : ���Ȱ��� ���ڷ� sin��Ÿ�� ���Ѵ�.
	*/

	// ���� �� �󿡼��� ���� ��ġ�� �����Ѵ�.
	m_linePos.x = m_linePos.x + cosf(DegreeToRadian(m_angle)) * m_moveSpeed * _deltaTime;
	m_linePos.y = m_linePos.y + sinf(DegreeToRadian(m_angle)) * m_moveSpeed * _deltaTime;

	/*
		1440�� �ǹ� :
		cos��Ÿ�� sin��Ÿ�� ������Ų ��ǥ�� 0~270�� �������� �ݺ��Ǳ� ������
		1440 / 270 = 6, �߻� 1���� 6�� ȸ����Ű�ڴٴ� �ǹ��̰�,
		
	*/
	m_rotationAngle += 1440.f * _deltaTime;

	// ������ ���� ���� ��ġ�� ��������, ����̵��� ��ġ�� �����Ѵ�.
	m_pos.x = m_linePos.x + cosf(DegreeToRadian(m_rotationAngle)) * m_range;
	m_pos.y = m_linePos.y + sinf(DegreeToRadian(m_rotationAngle)) * m_range;


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

void CTornado::Render(HDC _hDC, float _deltaTime)
{
	// ����̵��� �׷��� �»�� ��ǥ�� ���Ѵ�.
	Vector2 renderLT;
	renderLT = m_pos - m_pivot * m_size;

	// ����̵��� �׸���.
	Ellipse(_hDC, (int)renderLT.x, (int)renderLT.y,
		(int)(renderLT.x + m_size.x), (int)(renderLT.y + m_size.y));
}

void CTornado::SetPos(float _x, float _y)
{
	CGameObject::SetPos(_x, _y);
	// ������ �� �󿡼��� ���� ��ġ�� �����Ѵ�.
	m_linePos = m_pos;
}

void CTornado::SetPos(const Vector2& _pos)
{
	CGameObject::SetPos(_pos);
	m_linePos = m_pos;
}

void CTornado::SetAngle(float _angle)
{
	m_angle = _angle;
}

void CTornado::SetDistance(float _distance)
{
	m_distance = _distance;
}

CTornado::CTornado()
{
	// ��ü ���� �� Ÿ�� ���̵�(���۷��� Ŭ������ ���)�� �ʱ�ȭ
	SetTypeID<CTornado>();
}

CTornado::CTornado(const CTornado& _obj)
	: CGameObject(_obj)
	, m_moveSpeed(_obj.m_moveSpeed)
	, m_angle(_obj.m_angle)
	, m_distance(_obj.m_distance)
	, m_rotationAngle(_obj.m_rotationAngle)
	, m_range(_obj.m_range)
	, m_linePos(_obj.m_linePos)
{
}
