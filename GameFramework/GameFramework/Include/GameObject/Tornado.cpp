#include "Tornado.h"

bool CTornado::Init()
{
	m_moveSpeed = 400.f;
	m_distance = 600.f;
	m_angle = 180.f;
	m_rotationAngle = 0.f;
	m_range = 100.f;

	// 토네이도 위치(어차피 발사주체에서 조정 받음), 크기, 피봇 설정
	SetPos(900.f, 100.f);
	SetSize(50.f, 50.f);
	SetPivot(0.5f, 0.5f);

	return true;
}

void CTornado::Update(float _deltaTime)
{
	/*
		cos 0, 90, 180, 270    ->  cos세타 1, 0, -1, 0  (이후 반복)
		sin 0, 90, 180, 270    ->  sin세타 0, 1, 0, -1  (이후 반복)

		cos와 sin의 각도에 해당하는 세타를 x,y좌표로하여 서로 대응시키면,
		원의 둘레의 4점이 나온다.
		즉, 불릿의 방향 좌표에 cos세타를 x좌표로, sin세타를 y좌표로 사용한다.

		불릿이 발사되는 좌표(-> m_pos.x + m_moveSpeed * _deltaTime) 에
		각도(-> cosf(DegreeToRadian(m_angle)) )를 곱하여, 각도에 따라
		다른 방향으로 발사되게 만들 것이다.

		'각도'는 발사주체 객체에서 매번 갱신 받는다.

		cosf : 라디안값을 인자로 con세타를 구한다.
		sinf : 라디안값을 인자로 sin세타를 구한다.
	*/

	// 가상 선 상에서의 점의 위치를 갱신한다.
	m_linePos.x = m_linePos.x + cosf(DegreeToRadian(m_angle)) * m_moveSpeed * _deltaTime;
	m_linePos.y = m_linePos.y + sinf(DegreeToRadian(m_angle)) * m_moveSpeed * _deltaTime;

	/*
		1440의 의미 :
		cos세타와 sin세타를 대응시킨 좌표는 0~270도 범위에서 반복되기 때문에
		1440 / 270 = 6, 발사 1번당 6번 회전시키겠다는 의미이고,
		
	*/
	m_rotationAngle += 1440.f * _deltaTime;

	// 위에서 구한 점의 위치를 기준으로, 토네이도의 위치를 갱신한다.
	m_pos.x = m_linePos.x + cosf(DegreeToRadian(m_rotationAngle)) * m_range;
	m_pos.y = m_linePos.y + sinf(DegreeToRadian(m_rotationAngle)) * m_range;


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

void CTornado::Render(HDC _hDC, float _deltaTime)
{
	// 토네이도가 그려질 좌상단 좌표를 구한다.
	Vector2 renderLT;
	renderLT = m_pos - m_pivot * m_size;

	// 토네이도를 그린다.
	Ellipse(_hDC, (int)renderLT.x, (int)renderLT.y,
		(int)(renderLT.x + m_size.x), (int)(renderLT.y + m_size.y));
}

void CTornado::SetPos(float _x, float _y)
{
	CGameObject::SetPos(_x, _y);
	// 가상의 선 상에서의 점의 위치를 조정한다.
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
	// 객체 생성 시 타입 아이디(레퍼런스 클래스의 멤버)를 초기화
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
