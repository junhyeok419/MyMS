#include "Ladder.h"
#include "../Scene/Scene.h"
#include "../GameObject/Player.h"
bool CLadder::Init()
{
	CColliderLine* line = AddCollider<CColliderLine>("Ladder");

	line->SetCollisionProfile("Ground");  // �浹 �������� ���� : Ground

	// Head�� �浹 �� ȣ���� �Լ� ���
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
	// �÷��̾ ��ȣ�ۿ� ���� ���·� ����, ����Ű �Է��� Ȱ��ȭ�Ѵ�

	// ������ �Ʒ��� �������� �����̶�� ������Ű�� �� ������ ���������� 
	// ���� ���� y��ǥ�� �÷��̾� �浹ü bottom�� ���ٸ� �� ����Ű�� ��Ȱ��ȭ�ؾ��Ѵ�. 
	
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
	// ���ٿ� ��ġ�⸸�ص� ����Ǵ°� ���� ���� ���� ���� ��쿡�� ����ǵ��� 
	if (!_dest->GetOwner()->GetLadder())
	{
		// �����������ٸ� '��ȣ�ۿ� �Ұ��� ����'�� �ǵ�����.
		_dest->GetOwner()->SetEnableUpKey(false);
		_dest->GetOwner()->SetEnableDownKey(false);
		return;
	}

	// ������ ������ ���� ��쵵 ������ ���� ������ �������־�� �Ѵ�.
	_dest->GetOwner()->SetJump(false);

	// ���� y��ǥ�� 1/2������ ���Ѵ�
	float middle = (_src->GetLineInfo().Point1.y +_src->GetLineInfo().Point2.y) / 2;

	// ���� y��ǥ�� 1 / 2�������� �÷��̾ ���� �ִٸ� ���� �ö󰬴ٴ� ���̴�.
	if (_dest->GetOwner()->GetPos().y < middle)
	{
		// ���� �ö��� ���� Body�� ���ٿ��� ����� ������ �ö� ���̴�.
		// ���� �켱 dest�� Head�� ��� �����Ѵ�.
		if (_dest->GetName() == "Head")
			return;
	}

	// ���� y��ǥ�� 1 / 2�������� �÷��̾ �Ʒ��� �ִٸ� �Ʒ��� �������ٴ� ���̴�.
	if (_dest->GetOwner()->GetPos().y > middle)
	{
		// �Ʒ��� �������� ���� Head�� ���ٿ��� ����� ������ ������ ���̴�.
		// ���� �켱 dest�� Body�� ��� �����Ѵ�.
		if (_dest->GetName() == "Body")
			return;
	}

	// ��ٸ� ���¸� �����Ͽ� ���� ������� ���ư��� �Ѵ�.
	_dest->GetOwner()->SetLadder(false);
	
	// '��ȣ�ۿ� �Ұ��� ����'�� �ǵ�����.
	_dest->GetOwner()->SetEnableUpKey(false);
	_dest->GetOwner()->SetEnableDownKey(false);

	// ���� ������ �ٽ� �����Ͽ� ���鿡 �������ų� �ö� �� �ֵ��� �Ѵ�.
	_dest->GetOwner()->SetPhysicsSimulate(true);

	// ������ ������� ��ŭ ���� ��ġ�� �ٽ� �ʱ�ȭ�Ͽ� �̻��� ������ ���� �ʵ��� �Ѵ�.
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
