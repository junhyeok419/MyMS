#include "CollisionManager.h"
#include "ColliderBox.h"
#include "ColliderCircle.h"
#include "ColliderLine.h"

DEFINITION_SINGLE(CCollisionManager)

bool CCollisionManager::Init()
{
	// 충돌 프로파일을 생성한다.

	/*
		이름은 Default, 
		사용하는  충돌 채널은 Default, 
		활성화 여부는 true, 
		기본 상호작용 상태는 Ignore으로 세팅한다. 아무것도 안넣으면 기본 Collision
	*/
	CreateProfile("Default", ECollisionChannel::Default, false, ECollisionInteraction::Ignore);
	CreateProfile("Player", ECollisionChannel::Player, true, ECollisionInteraction::Ignore);
	CreateProfile("Monster", ECollisionChannel::Monster, true, ECollisionInteraction::Ignore);
	CreateProfile("PlayerAttack", ECollisionChannel::PlayerAttack, true, ECollisionInteraction::Ignore);
	CreateProfile("MonsterAttack", ECollisionChannel::MonsterAttack, true, ECollisionInteraction::Ignore);
	CreateProfile("Cognition", ECollisionChannel::Cognition, true, ECollisionInteraction::Ignore);
	CreateProfile("Ground", ECollisionChannel::Ground, true, ECollisionInteraction::Collision);
	CreateProfile("Item", ECollisionChannel::Item, true, ECollisionInteraction::Collision);
	CreateProfile("Mouse", ECollisionChannel::Mouse, true, ECollisionInteraction::Collision); // 기본 Collision으로.
	CreateProfile("Npc", ECollisionChannel::Npc, true, ECollisionInteraction::Collision);
																							  
	/*
		'Player 라는 이름을 가진 프로파일' 을 대상으로
		'Default 채널을 사용하는 프로파일' 과의 
		상호작용 상태를 'Collision'으로 한다. 라는 의미이다.
	*/
	SetCollisionInteraction("Player", ECollisionChannel::Default, ECollisionInteraction::Ignore);
	SetCollisionInteraction("Player", ECollisionChannel::MonsterAttack, ECollisionInteraction::Collision);
	SetCollisionInteraction("Player", ECollisionChannel::Cognition, ECollisionInteraction::Collision);
	SetCollisionInteraction("Player", ECollisionChannel::Ground, ECollisionInteraction::Collision);
	SetCollisionInteraction("Player", ECollisionChannel::Monster, ECollisionInteraction::Collision);	
	SetCollisionInteraction("Player", ECollisionChannel::Mouse, ECollisionInteraction::Collision);
	SetCollisionInteraction("Player", ECollisionChannel::Item, ECollisionInteraction::Collision);
	SetCollisionInteraction("Player", ECollisionChannel::Npc, ECollisionInteraction::Collision);

	SetCollisionInteraction("Monster", ECollisionChannel::Default, ECollisionInteraction::Ignore);
	SetCollisionInteraction("Monster", ECollisionChannel::PlayerAttack, ECollisionInteraction::Collision);
	SetCollisionInteraction("Monster", ECollisionChannel::Ground, ECollisionInteraction::Collision);
	SetCollisionInteraction("Monster", ECollisionChannel::Player, ECollisionInteraction::Collision);
	SetCollisionInteraction("Monster", ECollisionChannel::Mouse, ECollisionInteraction::Collision);

	SetCollisionInteraction("PlayerAttack", ECollisionChannel::Default, ECollisionInteraction::Collision);

	SetCollisionInteraction("Ground", ECollisionChannel::Player, ECollisionInteraction::Collision);

	SetCollisionInteraction("Npc", ECollisionChannel::Mouse, ECollisionInteraction::Collision);
	SetCollisionInteraction("Mouse", ECollisionChannel::Npc, ECollisionInteraction::Collision);

	/*
		'PlayerAttack 라는 이름을 가진 프로파일' 을 대상으로
		'Monster 채널을 사용하는 프로파일' 과의 
		상호작용 상태를 'Collision'으로 한다. 라는 의미이다.

		앞서 Monster라는 이름을 가진 프로파일과 PlayerAttack채널을 
		사용하는 프로파일과의 상호작용을 Collision으로 변경하였으므로,
		이 둘(PlayerAttack, Monster)은 충돌 체크를 할 것이다. 
	*/
	SetCollisionInteraction("PlayerAttack", ECollisionChannel::Monster, ECollisionInteraction::Collision);

	SetCollisionInteraction("MonsterAttack", ECollisionChannel::Default, ECollisionInteraction::Collision);
	SetCollisionInteraction("MonsterAttack", ECollisionChannel::Player, ECollisionInteraction::Collision);
	
	SetCollisionInteraction("Cognition", ECollisionChannel::Player, ECollisionInteraction::Collision);
	
	return true;
}

bool CCollisionManager::CreateProfile(const std::string& _name, ECollisionChannel _channel, bool _enable, ECollisionInteraction _baseInteraction)
{
	// 생성하려는 이름에 해당하는 프로파일이 있다면 리턴한다.
	CollisionProfile* profile = FindProfile(_name);

	if (profile)
		return false;

	// 빈 프로파일을 생성한다.
	profile = new CollisionProfile;
	
	// 인자로 들어온 정보를 세팅한다.
	profile->Name = _name;
	profile->Channel = _channel;
	profile->Enable = _enable;
	// 상호작용을 위한 벡터를 최대 채널 개수만큼 push_back 한다.
	// (중요) 이 벡터의 i번째 인덱스에 해당하는 상호작용이 곧 i번 채널과의 상호작용이다. 
	profile->VecCollisionInteraction.resize((size_t)ECollisionChannel::Max);

	// 상호작용을 위한 벡터를 '기본 상호작용'으로 세팅한다.
	for (int i = 0; i < (int)ECollisionChannel::Max; ++i)
	{
		profile->VecCollisionInteraction[i] = _baseInteraction;
	}

	// 완성된 프로파일을 map에 추가한다.
	m_mapProfile.insert(std::make_pair(_name, profile));

	return true;
}

bool CCollisionManager::SetCollisionInteraction(const std::string& _name, ECollisionChannel _channel, ECollisionInteraction _interaction)
{
	// 바꾸고 싶은 이름의 프로파일이 없으면 리턴한다.
	CollisionProfile* profile = FindProfile(_name);

	if (!profile)
		return false;
	
	// 프로파일의 원하는 채널(_channel)과의 상호작용 상태를 _interaction으로 바꾼다.
	profile->VecCollisionInteraction[(int)_channel] = _interaction;

	return true;
}

CollisionProfile* CCollisionManager::FindProfile(const std::string& _name)
{
	auto	iter = m_mapProfile.find(_name);

	if (iter == m_mapProfile.end())
		return nullptr;

	return iter->second;
}

bool CCollisionManager::CollisionBoxToBox(Vector2& _hitPoint, CColliderBox* _src, CColliderBox* _dest)
{
	/*
		hitPoint(겹치는 영역의 중앙 좌표),
		충돌체 1의 좌상단 및 우하단 좌표,
		충돌체 2의 좌상단 및 우하단 좌표를 전달해
		박스 투 박스 충돌을 체크한다.
	*/
	if (CollisionBoxToBox(_hitPoint, _src->GetInfo(), _dest->GetInfo()))
	{
		// 위 함수에서 구한 히트 포인트를 dest 충돌체에도 적용시켜준다.
		_dest->m_hitPoint = _hitPoint;
		return true;
	}
		
	return false;
}

bool CCollisionManager::CollisionCircleToCircle(Vector2& _hitPoint, CColliderCircle* _src, CColliderCircle* _dest)
{
	/*
		hitPoint(겹치는 영역의 중앙 좌표),
		충돌체 1의 중점 및 반지름,
		충돌체 2의 중점 및 반지름 정보를 전달해
		원 대 원 충돌을 체크한다.
	*/
	if (CollisionCircleToCircle(_hitPoint, _src->GetInfo(), _dest->GetInfo()))
	{
		// 위 함수에서 구한 히트 포인트를 dest 충돌체에도 적용시켜준다.
		_dest->m_hitPoint = _hitPoint;
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionBoxToCircle(Vector2& HitPoint, CColliderBox* Src, CColliderCircle* Dest)
{
	if (CollisionBoxToCircle(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		// 위 함수에서 구한 히트 포인트를 dest 충돌체에도 적용시켜준다.
		Dest->m_hitPoint = HitPoint;
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionPointToBox(Vector2& _hitPoint, 
	const Vector2& _src, CColliderBox* _dest)
{
	// 마우스는 하나의 '점'이므로, Vector2로 전달한다.
	if (CollisionPointToBox(_hitPoint, _src, _dest->GetInfo()))
	{
		_dest->m_hitPoint = _hitPoint;
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionPointToCircle(Vector2& _hitPoint, 
	const Vector2& _src, CColliderCircle* _dest)
{
	// 마우스는 하나의 '점'이므로, Vector2로 전달한다.
	if (CollisionPointToCircle(_hitPoint, _src, _dest->GetInfo()))
	{
		_dest->m_hitPoint = _hitPoint;
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionBoxToLine(Vector2& _hitPoint, 
	CColliderBox* _src, CColliderLine* _dest)
{
	/*
		hitPoint(겹치는 영역의 중앙 좌표),
		박스 충돌체의 좌상단 및 우하단 좌표,
		선 충돌체의 양 끝점 좌표를 전달해
		박스 투 라인 충돌을 체크한다.
	*/
	if (CollisionBoxToLine(_hitPoint, _src->GetInfo(), _dest))
	{
		// 위 함수에서 구한 히트 포인트를 dest 충돌체에도 적용시켜준다.
		_dest->m_hitPoint = _hitPoint;
		return true;
	}

	return false;
}



bool CCollisionManager::CollisionBoxToBox(Vector2& _hitPoint, const BoxInfo& _src, const BoxInfo& _dest)
{
	// 실제 충돌체크는 여기서 한다.

	// 좌표상으로 충돌이 아닌 4가지 경우를 먼저 골라낸다.
	if (_src.Lt.x > _dest.Rb.x)
		return false;

	else if (_src.Lt.y > _dest.Rb.y)
		return false;

	else if (_src.Rb.x < _dest.Lt.x)
		return false;

	else if (_src.Rb.y < _dest.Lt.y)
		return false;

	// 충돌 교집합 부분의 lt, rb 좌표를 구한다.
	float left = _src.Lt.x > _dest.Lt.x ? _src.Lt.x : _dest.Lt.x;
	float top = _src.Lt.y > _dest.Lt.y ? _src.Lt.y : _dest.Lt.y;
	float right = _src.Rb.x < _dest.Rb.x ? _src.Rb.x : _dest.Rb.x;
	float bottom = _src.Rb.y < _dest.Rb.y ? _src.Rb.y : _dest.Rb.y;

	// 히트포인트를 구한다. x끼리 y끼리 각각 더한 값에 2를나눠야 
	// 중앙 좌표가 나올 것이다.
	_hitPoint.x = (left + right) / 2.f;
	_hitPoint.y = (top + bottom) / 2.f;

	return true;
}

bool CCollisionManager::CollisionCircleToCircle(Vector2& _hitPoint, const CircleInfo& _src, const CircleInfo& _dest)
{
	// 두 충돌체의 중점 사이의 거리를 구한다.
	float Dist = _src.Center.Distance(_dest.Center);

	// 두 충돌체의 중점 사이의 거리가 반지름의 합보다 작거나 같은지 따진다. 
	bool result = Dist <= _src.Radius + _dest.Radius;

	// 히트 포인트를 구해준다. 단순하게 두 충돌체의 중점의 1/2 지점으로 구한다.
	_hitPoint = (_src.Center + _dest.Center) / 2.f;

	// result가 true라면 충돌, false라면 충돌이 아니다.
	return result;
}

bool CCollisionManager::CollisionBoxToCircle(Vector2& _hitPoint, const BoxInfo& _src, const CircleInfo& _dest)
{
	/*
		원 대 사각형 충돌 : 
		- 사각형의 4면을 원의 반지름만큼 '가상으로' 확장한다.
		  그러면 '네 귀퉁이'와 '상하좌우'에 총 8개 영역이 생긴다.
		  
		  사각형 충돌체 원본을 '사각형 A', 
		  확장된 사각형을 '사각형 B'라고 하자.
		
		- 반대로 원은 반지름만큼 축소한다. 따라서 원은 원의 중심이 된다.

		- 이 원의 중심이 사각형 B의 내부에 들어가는지 판단해야 한다.
		  단, 네 귀퉁이의 사각형은 반지름 길이가 아닌, 
		  반지름의 약 1.4배 이므로 별도의 처리를 해 줄 것이다.

		결론은, 
		1. 사각형 B의 상하좌우의 영역에 원의 중심이 존재한다면 '충돌'이다.
		2. 사각형 B의 네 귀퉁이의 영역에 원의 중심이 존재한다면,
		   별도의 충돌 처리가 필요하다.
	*/

	// 먼저 원의 중점이 사각형 A의 '상하' 또는 '좌우' 범위에 존재하는지 판단한다.
	if ((_src.Lt.x <= _dest.Center.x && _dest.Center.x <= _src.Rb.x) ||
		(_src.Lt.y <= _dest.Center.y && _dest.Center.y <= _src.Rb.y))
	{
		// 사각형을 원의 반지름만큼 확장한다.
		BoxInfo	RC = _src;
		RC.Lt.x -= _dest.Radius;
		RC.Lt.y -= _dest.Radius;
		RC.Rb.x += _dest.Radius;
		RC.Rb.y += _dest.Radius;

		/*
			확장된 사각형(사각형 B) 안에 원의 중점이 들어온다면 
			충돌된 것이므로, 충돌이 아닌 경우를 먼저 판단해준다.
		*/
		if (RC.Lt.x > _dest.Center.x)
			return false;

		else if (RC.Lt.y > _dest.Center.y)
			return false;

		else if (RC.Rb.x < _dest.Center.x)
			return false;

		else if (RC.Rb.y < _dest.Center.y)
			return false;

		// 여기까지 왔으면 충돌이다. 히트 포인트를 구해준다.
		/*
			원 대 사각형 충돌의 히트 포인트 : 
			- 원 충돌체를 내접원으로 갖는 가상의 '사각형 C'를 그린다.
			- 사각형 A와 사각형 C가 교차되면서 만들어지는 충돌 영역의
			  중점을 히트 포인트로 한다. (즉, 이것도 정확한 지점은 아니다.)
		*/
		
		// 가상의 '사각형 C' 
		BoxInfo	CircleBox;
		CircleBox.Lt = _dest.Center - _dest.Radius;
		CircleBox.Rb = _dest.Center + _dest.Radius;

		// 사각형 A와 사각형 C의 충돌 영역
		float left = _src.Lt.x > CircleBox.Lt.x ? _src.Lt.x : CircleBox.Lt.x;
		float top = _src.Lt.y > CircleBox.Lt.y ? _src.Lt.y : CircleBox.Lt.y;
		float right = _src.Rb.x < CircleBox.Rb.x ? _src.Rb.x : CircleBox.Rb.x;
		float bottom = _src.Rb.y < CircleBox.Rb.y ? _src.Rb.y : CircleBox.Rb.y;

		// 히트 포인트
		_hitPoint.x = (left + right) / 2.f;
		_hitPoint.y = (top + bottom) / 2.f;

		return true;
	}

	/*
		이곳까지 왔다면, 원의 중점이 사각형 B의 네 귀퉁이(대각선 영역)에
		들어오는 경우중에서 충돌인지 아닌지 판단해야 한다.

		- 사각형 A의 네 꼭짓점이 원 충돌체 안에 들어오면 충돌이다.

		- 꼭짓점과 원 중점과의 거리가 원의 반지름보다 작거나 같으면 
		  들어온 것이다.
	*/

	// 사각형 A의 4개의 꼭짓점을 나타내는 Vector2 배열을 만든다.
	Vector2	Pos[4] =
	{
		_src.Lt,
		Vector2(_src.Rb.x, _src.Lt.y),
		Vector2(_src.Lt.x, _src.Rb.y),
		_src.Rb
	};

	// 4개의 꼭짓점중 하나라도 원 안에 들어오는지 판단한다.
	for (int i = 0; i < 4; ++i)
	{
		// 꼭짓점과 원 중점과의 거리를 구한다.
		float dist = _dest.Center.Distance(Pos[i]);

		// 반지름보다 작거나 같은지 확인한다.
		if (dist <= _dest.Radius)
		{
			// true일 경우 충돌이므로, 위와 같이 히트 포인트를 구해준다.
			
			// 가상의 '사각형 C' 
			BoxInfo	CircleBox;
			CircleBox.Lt = _dest.Center - _dest.Radius;
			CircleBox.Rb = _dest.Center + _dest.Radius;

			// 사각형 A와 사각형 C의 충돌 영역
			float left = _src.Lt.x > CircleBox.Lt.x ? _src.Lt.x : CircleBox.Lt.x;
			float top = _src.Lt.y > CircleBox.Lt.y ? _src.Lt.y : CircleBox.Lt.y;
			float right = _src.Rb.x < CircleBox.Rb.x ? _src.Rb.x : CircleBox.Rb.x;
			float bottom = _src.Rb.y < CircleBox.Rb.y ? _src.Rb.y : CircleBox.Rb.y;

			// 히트 포인트
			_hitPoint.x = (left + right) / 2.f;
			_hitPoint.y = (top + bottom) / 2.f;

			return true;
		}
	}

	// 충돌이 아닐 경우 여기서 리턴
	return false;
}

bool CCollisionManager::CollisionPointToBox(Vector2& _hitPoint, const Vector2& _src, const BoxInfo& _dest)
{
	/*
		점 대 사각형 충돌 : 단순히 점이 사각형 내 좌표에
		들어와 있으면 된다.
		따라서 아닌 경우를 먼저 걸러주면 충돌이 체크된다.

		위에서 했던 것의 일부다. 매우 간단하다.
	*/
	if (_dest.Lt.x > _src.x)
		return false;

	else if (_dest.Lt.y > _src.y)
		return false;

	else if (_dest.Rb.x < _src.x)
		return false;

	else if (_dest.Rb.y < _src.y)
		return false;

	// 히트 포인트는 점의 위치와 같다.
	_hitPoint = _src;

	return true;
}

bool CCollisionManager::CollisionPointToCircle(Vector2& _hitPoint, const Vector2& _src, const CircleInfo& _dest)
{
	/*
		점 대 원 충돌 : 점과 원의 중심 사이 거리를 구하고,
		이 거리가 원의 반지름 보다 작거나 같으면 충돌이다.

		위에서 했던 것의 일부다. 매우 간단하다.
	*/
	float dist = _dest.Center.Distance(_src);

	if (dist <= _dest.Radius)
	{
		// 히트 포인트는 점의 위치와 같다.
		_hitPoint = _src;

		return true;
	}

	return false;
}

bool CCollisionManager::CollisionBoxToLine(Vector2& _hitPoint, const BoxInfo& _src, const CColliderLine* _dest)
{
	/*
		사각형 대 선 충돌 : 사각형의 네 꼭짓점의 좌표에 대해 직선과의 거리를 구한다.

		직선의 양 끝점이 (a,b) (c,d)라고 할 때, 직선의 방정식은 아래와 같다.

		(d-b)*x + (a-c)*y + (b*c-a*d) = 0

		따라서 점 p(x,y)와 위 직선 사이의 거리를 공식을 이용해 풀면,

		distance = (d-b)*x + (a-c)*y + (b*c - a*d) / sqrt(pow((d-b), 2) + pow((a-c), 2)) 이다.


		이렇게 4개의 값을 얻어내고, 이 값들이 '모두 양수'이거나 '모두 음수'라면 직선과 사각형은 충돌이고,
		그렇지 않다면 충돌이 아니다
	*/

	float a = _dest->GetInfo().Point1.x;
	float b = _dest->GetInfo().Point1.y;
	float c = _dest->GetInfo().Point2.x;
	float d = _dest->GetInfo().Point2.y;

	float x1 = _src.Lt.x;
	float y1 = _src.Lt.y;

	float x2 = _src.Rb.x;
	float y2 = _src.Lt.y;

	float x3 = _src.Lt.x;
	float y3 = _src.Rb.y;

	float x4 = _src.Rb.x;
	float y4 = _src.Rb.y;

	/*
		sqrt() : 제곱근을 구하는 함수 
		pow() : 거듭제곱을 해주는 함수 
	*/

	float distance1 = ((d - b) * x1 + (a - c) * y1 + (b * c - a * d)) / (sqrt(pow((d - b), 2) + pow((a - c), 2)));
	float distance2 = ((d - b) * x2 + (a - c) * y2 + (b * c - a * d)) / (sqrt(pow((d - b), 2) + pow((a - c), 2)));
	float distance3 = ((d - b) * x3 + (a - c) * y3 + (b * c - a * d)) / (sqrt(pow((d - b), 2) + pow((a - c), 2)));
	float distance4 = ((d - b) * x4 + (a - c) * y4 + (b * c - a * d)) / (sqrt(pow((d - b), 2) + pow((a - c), 2)));

	// 전부 양수이거나 전부 음수가 아니면 충돌이 아니다.
	if (distance1 > 0 && distance2 > 0 && distance3 > 0 && distance4 > 0)
		return false;
	else if (distance1 < 0 && distance2 < 0 && distance3 < 0 && distance4 < 0)
		return false;

	// 땅일 경우
	if (_dest->GetType() == ELineType::Ground)
	{
		// 박스의 x좌표가 선분의 x좌표를 벗어났을 경우도 충돌이 아닌 것으로 한다.
		// 위는 '직선'의 충돌이기 때문에 이것이 없으면 플레이어가 지형을 벗어나도 낙하하지 않는다.
		if (x4 <= a || x3 >= c)
		{
			return false;
		}

		// y값에 대한 예외처리
		if (y3 > b+3)
		{
			return false;
		}
	}
	// 벽일 경우
	else if (_dest->GetType() == ELineType::Wall)
	{
		// y값에 대한 예외처리
		if (36.f && y3 < b + 1)
		{
			return false;
		}
   
	    // 세로 직선이기 때문에, 직선의 어떤 x좌표든 상관없다
		if (x3 > a || x4 < a)
		{
			return false;
		}

		
	}
	// 사다리(줄)일 경우
	else if (_dest->GetType() == ELineType::Ladder)
	{
		if (x4 < a || x3 > c)
		{
			return false;
		}
		if (y3 < b || y1 > d)
		{
			return false;
		}

		// 가운데로 위치가 잡히도록 정확히 내부에 들어와야 함을 판단한다.
		// 사각형의 한가운데 x좌표가 직선의 x좌표 += 1픽셀 안에 들어오게끔 한다.

		// 사각형의 가운데 x좌표
		float boxMiddleX = (x2 + x1) / 2;

		if (boxMiddleX < a-1.f || boxMiddleX > a + 1.f)
		{
			return false;
		}
	}

	// 여기까지 오면 충돌이다
	return true;
}

CCollisionManager::CCollisionManager()
{}

CCollisionManager::~CCollisionManager()
{
	// 프로파일을 모두 삭제한다.
	auto	iter = m_mapProfile.begin();
	auto	iterEnd = m_mapProfile.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}