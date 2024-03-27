#include "Ladder.h"
#include "../Scene/Scene.h"
#include "../GameObject/Player.h"
bool CLadder::Init()
{
	CColliderLine* line = AddCollider<CColliderLine>("Ladder");

	line->SetCollisionProfile("Ground");  // 충돌 프로파일 설정 : Ground

	// Head와 충돌 시 호출할 함수 등록
	line->SetCollisionBeginFunction<CLadder>(this, &CLadder::CollisionBegin);
	line->SetCollisionEndFunction<CLadder>(this, &CLadder::CollisionEnd);

	line->SetOffset(0, 0);

	m_line = line;

	return true;
}

void CLadder::Update(float _deltaTime)
{
	CGameObject::Update(_deltaTime);
}

void CLadder::PostUpdate(float _deltaTime)
{
	CGameObject::PostUpdate(_deltaTime);
}

void CLadder::Render(HDC _hDC, float _deltaTime)
{
	CGameObject::Render(_hDC, _deltaTime);
}

void CLadder::SetType(ELineType _type)
{
	m_line->SetType(_type);
}

ELineType CLadder::GetType() const
{
	return m_line->GetType();
}

LineInfo CLadder::GetLineInfo() const
{
	return m_line->GetInfo();
}

void CLadder::CollisionBegin(CCollider* _src, CCollider* _dest)
{
	// 플레이어를 상호작용 가능 상태로 만들어서, 방향키 입력을 활성화한다

	// 위에서 아래로 내려오는 밧줄이라면 위방향키를 꾹 누를때 문제때문에 
	// 밧줄 위쪽 y좌표가 플레이어 충돌체 bottom과 같다면 위 방향키를 비활성화해야한다. 
	
	_dest->GetOwner()->SetEnableDownKey(true);

	
	if (_src->GetLineInfo().Point1.y+3.f >= _dest->GetBottom())
	{
		_dest->GetOwner()->SetEnableUpKey(false);
		return;
	}
	else
		_dest->GetOwner()->SetEnableUpKey(true);
}

void CLadder::CollisionEnd(CCollider* _src, CCollider* _dest)
{
	// 밧줄에 스치기만해도 실행되는걸 막기 위해 실제 탔을 경우에만 실행되도록 
	if (!_dest->GetOwner()->GetLadder())
	{
		// 스쳐지나갔다면 '상호작용 불가능 상태'로 되돌린다.
		_dest->GetOwner()->SetEnableUpKey(false);
		_dest->GetOwner()->SetEnableDownKey(false);
		return;
	}

	// 점프로 밧줄을 탔을 경우도 있으니 먼저 점프를 해제해주어야 한다.
	_dest->GetOwner()->SetJump(false);

	// 밧줄 y좌표의 1/2지점을 구한다
	float middle = (_src->GetLineInfo().Point1.y +_src->GetLineInfo().Point2.y) / 2;

	// 밧줄 y좌표의 1 / 2지점보다 플레이어가 위에 있다면 위로 올라갔다는 뜻이다.
	if (_dest->GetOwner()->GetPos().y < middle)
	{
		// 위로 올라갔을 때는 Body가 밧줄에서 벗어나야 완전히 올라간 것이다.
		// 따라서 우선 dest가 Head일 경우 리턴한다.
		if (_dest->GetName() == "Head")
			return;
	}

	// 밧줄 y좌표의 1 / 2지점보다 플레이어가 아래에 있다면 아래로 내려갔다는 뜻이다.
	if (_dest->GetOwner()->GetPos().y > middle)
	{
		// 아래로 내려갔을 때는 Head가 밧줄에서 벗어나야 완전히 내려간 것이다.
		// 따라서 우선 dest가 Body일 경우 리턴한다.
		if (_dest->GetName() == "Body")
			return;
	}

	// 사다리 상태를 해제하여 원래 모션으로 돌아가게 한다.
	_dest->GetOwner()->SetLadder(false);
	
	// '상호작용 불가능 상태'로 되돌린다.
	_dest->GetOwner()->SetEnableUpKey(false);
	_dest->GetOwner()->SetEnableDownKey(false);

	// 물리 적용을 다시 시작하여 지면에 떨어지거나 올라갈 수 있도록 한다.
	_dest->GetOwner()->SetPhysicsSimulate(true);

	// 물리가 재적용된 만큼 현재 위치로 다시 초기화하여 이상한 점프를 하지 않도록 한다.
	_dest->GetOwner()->SetFallTime(0.f);
	_dest->GetOwner()->SetFallStartY(_dest->GetOwner()->GetPos().y);


}

void CLadder::SetInfo(const Vector2& _pos1, const Vector2& _pos2)
{
	m_line->SetInfo(_pos1, _pos2);
}

CLadder::CLadder()
{
	SetTypeID<CLadder>();
	m_renderLayer = ERenderLayer::Ground;
}

CLadder::CLadder(const CLadder& obj)
{
}

CLadder::~CLadder()
{
}
