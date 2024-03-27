#include "Wall.h"
#include "../Scene/Scene.h"
#include "../GameObject/Player.h"
bool CWall::Init()
{
	// 몬스터 위치, 크기, 피봇 설정
	SetPos(900.f, 100.f);
	SetSize(160.f, 156.f);
	SetPivot(0.5f, 0.5f);

	CColliderLine* line = AddCollider<CColliderLine>("Ground");

	line->SetCollisionProfile("Ground");  // 충돌 프로파일 설정 : Ground

	// Head와 충돌 시 호출할 함수 등록
	line->SetCollisionBeginFunction<CWall>(this, &CWall::CollisionBegin);
	line->SetCollisionEndFunction<CWall>(this, &CWall::CollisionEnd);

	line->SetOffset(0, 0);

	m_line = line;

	return true;
}

void CWall::Update(float _deltaTime)
{
	CGameObject::Update(_deltaTime);
}

void CWall::PostUpdate(float _deltaTime)
{
	CGameObject::PostUpdate(_deltaTime);
}

void CWall::Render(HDC _hDC, float _deltaTime)
{
	CGameObject::Render(_hDC, _deltaTime);
}

void CWall::SetType(ELineType _type)
{
	m_line->SetType(_type);
}

ELineType CWall::GetType() const
{
	return m_line->GetType();
}

void CWall::CollisionBegin(CCollider* _src, CCollider* _dest)
{
	// 벽에 닿았을 경우

	float curPosX = _dest->GetOwner()->GetPos().x;
	float curPosY = _dest->GetOwner()->GetPos().y;

	// 충돌시 x좌표를 계속 보정하여 통과하지 못하게 한다.
	if(_dest->GetOwner()->GetDir() == -1)
		_dest->GetOwner()->SetPos(curPosX + 5.f, curPosY);
	else
		_dest->GetOwner()->SetPos(curPosX - 5.f, curPosY);
}

void CWall::CollisionEnd(CCollider* _src, CCollider* _dest)
{
}

void CWall::SetInfo(const Vector2& _pos1, const Vector2& _pos2)
{
	m_line->SetInfo(_pos1, _pos2);
}

CWall::CWall()
{
	SetTypeID<CWall>();
	m_renderLayer = ERenderLayer::Ground;
}

CWall::CWall(const CWall& obj)
{
}

CWall::~CWall()
{
}
