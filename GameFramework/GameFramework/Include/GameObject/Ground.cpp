#include "Ground.h"


bool CGround::Init()
{
	// ���� ��ġ, ũ��, �Ǻ� ����
	SetPos(900.f, 100.f); 
	SetSize(160.f, 156.f);
	SetPivot(0.5f, 0.5f);  

	CColliderLine* line = AddCollider<CColliderLine>("Ground");

	line->SetCollisionProfile("Ground");  // �浹 �������� ���� : Ground

	// Head�� �浹 �� ȣ���� �Լ� ���
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
	// ������ ����� ���
	
	// ��ü�� �ν��ϵ���
	if (_dest->GetName() == "Head")
		return;


	// ������Ʈ�� ����� �´��� ���·�
	_dest->GetOwner()->SetGround(true);

	if (m_ladder)
	{
		// ��ٸ� ����
		_dest->GetOwner()->SetLadder(false);
		
	}

	// ������Ʈ�� ������ �ƴ� ���·�
	_dest->GetOwner()->SetJump(false);
	
	
	// ������ �ð�, ������ ��ġ �� �ʱ�ȭ
	_dest->GetOwner()->SetFallTime(0.f);
	_dest->GetOwner()->SetFallStartY(_dest->GetOwner()->GetPos().y);
}

void CGround::CollisionEnd(CCollider* _src, CCollider* _dest)
{
	// ��ü�� �ν��ϵ���
	if (_dest->GetName() == "Head")
		return;

	// ������ �������� ���, ����� �´��� ���� ���·�
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
