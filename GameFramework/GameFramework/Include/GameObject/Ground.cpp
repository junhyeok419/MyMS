#include "Ground.h"


bool CGround::Init()
{
	// 몬스터 위치, 크기, 피봇 설정
	SetPos(900.f, 100.f); 
	SetSize(160.f, 156.f);
	SetPivot(0.5f, 0.5f);  

	CColliderLine* line = AddCollider<CColliderLine>("Ground");

	line->SetCollisionProfile("Ground");  // 충돌 프로파일 설정 : Ground

	// Head와 충돌 시 호출할 함수 등록
	line->SetCollisionBeginFunction<CGround>(this, &CGround::CollisionBegin);
	line->SetCollisionEndFunction<CGround>(this, &CGround::CollisionEnd);

	line->SetOffset(0, 0);

	m_line = line;

	return true;
}

void CGround::Update(float _deltaTime)
{
	CGameObject::Update(_deltaTime);
}

void CGround::PostUpdate(float _deltaTime)
{
	CGameObject::PostUpdate(_deltaTime);
}

void CGround::Render(HDC _hDC, float _deltaTime)
{
	CGameObject::Render(_hDC, _deltaTime);
}

void CGround::SetType(ELineType _type)
{
	m_line->SetType(_type);
}

ELineType CGround::GetType() const
{
	return m_line->GetType();
}

void CGround::CollisionBegin(CCollider* _src, CCollider* _dest)
{
	// 지형에 닿았을 경우
	
	// 하체만 인식하도록
	if (_dest->GetName() == "Head")
		return;


	// 오브젝트를 지면과 맞닿은 상태로
	_dest->GetOwner()->SetGround(true);

	if (m_ladder)
	{
		// 사다리 해제
		_dest->GetOwner()->SetLadder(false);
		
	}

	// 오브젝트를 점프가 아닌 상태로
	_dest->GetOwner()->SetJump(false);
	
	
	// 떨어진 시간, 떨어진 위치 등 초기화
	_dest->GetOwner()->SetFallTime(0.f);
	_dest->GetOwner()->SetFallStartY(_dest->GetOwner()->GetPos().y);
}

void CGround::CollisionEnd(CCollider* _src, CCollider* _dest)
{
	// 하체만 인식하도록
	if (_dest->GetName() == "Head")
		return;

	// 지형과 떨어졌을 경우, 지면과 맞닿지 않은 상태로
	_dest->GetOwner()->SetGround(false);
}

void CGround::SetInfo(const Vector2& _pos1, const Vector2& _pos2)
{
	m_line->SetInfo(_pos1, _pos2);
}

CGround::CGround()
{
	SetTypeID<CGround>();
	m_renderLayer = ERenderLayer::Ground;
}

CGround::CGround(const CGround& obj)
{
}

CGround::~CGround()
{
}
