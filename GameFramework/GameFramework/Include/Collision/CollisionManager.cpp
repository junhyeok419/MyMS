#include "CollisionManager.h"
#include "ColliderBox.h"
#include "ColliderCircle.h"
#include "ColliderLine.h"

DEFINITION_SINGLE(CCollisionManager)

bool CCollisionManager::Init()
{
	// �浹 ���������� �����Ѵ�.

	/*
		�̸��� Default, 
		����ϴ�  �浹 ä���� Default, 
		Ȱ��ȭ ���δ� true, 
		�⺻ ��ȣ�ۿ� ���´� Ignore���� �����Ѵ�. �ƹ��͵� �ȳ����� �⺻ Collision
	*/
	CreateProfile("Default", ECollisionChannel::Default, false, ECollisionInteraction::Ignore);
	CreateProfile("Player", ECollisionChannel::Player, true, ECollisionInteraction::Ignore);
	CreateProfile("Monster", ECollisionChannel::Monster, true, ECollisionInteraction::Ignore);
	CreateProfile("PlayerAttack", ECollisionChannel::PlayerAttack, true, ECollisionInteraction::Ignore);
	CreateProfile("MonsterAttack", ECollisionChannel::MonsterAttack, true, ECollisionInteraction::Ignore);
	CreateProfile("Cognition", ECollisionChannel::Cognition, true, ECollisionInteraction::Ignore);
	CreateProfile("Ground", ECollisionChannel::Ground, true, ECollisionInteraction::Collision);
	CreateProfile("Item", ECollisionChannel::Item, true, ECollisionInteraction::Collision);
	CreateProfile("Mouse", ECollisionChannel::Mouse, true, ECollisionInteraction::Collision); // �⺻ Collision����.
	CreateProfile("Npc", ECollisionChannel::Npc, true, ECollisionInteraction::Collision);
																							  
	/*
		'Player ��� �̸��� ���� ��������' �� �������
		'Default ä���� ����ϴ� ��������' ���� 
		��ȣ�ۿ� ���¸� 'Collision'���� �Ѵ�. ��� �ǹ��̴�.
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
		'PlayerAttack ��� �̸��� ���� ��������' �� �������
		'Monster ä���� ����ϴ� ��������' ���� 
		��ȣ�ۿ� ���¸� 'Collision'���� �Ѵ�. ��� �ǹ��̴�.

		�ռ� Monster��� �̸��� ���� �������ϰ� PlayerAttackä���� 
		����ϴ� �������ϰ��� ��ȣ�ۿ��� Collision���� �����Ͽ����Ƿ�,
		�� ��(PlayerAttack, Monster)�� �浹 üũ�� �� ���̴�. 
	*/
	SetCollisionInteraction("PlayerAttack", ECollisionChannel::Monster, ECollisionInteraction::Collision);

	SetCollisionInteraction("MonsterAttack", ECollisionChannel::Default, ECollisionInteraction::Collision);
	SetCollisionInteraction("MonsterAttack", ECollisionChannel::Player, ECollisionInteraction::Collision);
	
	SetCollisionInteraction("Cognition", ECollisionChannel::Player, ECollisionInteraction::Collision);
	
	return true;
}

bool CCollisionManager::CreateProfile(const std::string& _name, ECollisionChannel _channel, bool _enable, ECollisionInteraction _baseInteraction)
{
	// �����Ϸ��� �̸��� �ش��ϴ� ���������� �ִٸ� �����Ѵ�.
	CollisionProfile* profile = FindProfile(_name);

	if (profile)
		return false;

	// �� ���������� �����Ѵ�.
	profile = new CollisionProfile;
	
	// ���ڷ� ���� ������ �����Ѵ�.
	profile->Name = _name;
	profile->Channel = _channel;
	profile->Enable = _enable;
	// ��ȣ�ۿ��� ���� ���͸� �ִ� ä�� ������ŭ push_back �Ѵ�.
	// (�߿�) �� ������ i��° �ε����� �ش��ϴ� ��ȣ�ۿ��� �� i�� ä�ΰ��� ��ȣ�ۿ��̴�. 
	profile->VecCollisionInteraction.resize((size_t)ECollisionChannel::Max);

	// ��ȣ�ۿ��� ���� ���͸� '�⺻ ��ȣ�ۿ�'���� �����Ѵ�.
	for (int i = 0; i < (int)ECollisionChannel::Max; ++i)
	{
		profile->VecCollisionInteraction[i] = _baseInteraction;
	}

	// �ϼ��� ���������� map�� �߰��Ѵ�.
	m_mapProfile.insert(std::make_pair(_name, profile));

	return true;
}

bool CCollisionManager::SetCollisionInteraction(const std::string& _name, ECollisionChannel _channel, ECollisionInteraction _interaction)
{
	// �ٲٰ� ���� �̸��� ���������� ������ �����Ѵ�.
	CollisionProfile* profile = FindProfile(_name);

	if (!profile)
		return false;
	
	// ���������� ���ϴ� ä��(_channel)���� ��ȣ�ۿ� ���¸� _interaction���� �ٲ۴�.
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
		hitPoint(��ġ�� ������ �߾� ��ǥ),
		�浹ü 1�� �»�� �� ���ϴ� ��ǥ,
		�浹ü 2�� �»�� �� ���ϴ� ��ǥ�� ������
		�ڽ� �� �ڽ� �浹�� üũ�Ѵ�.
	*/
	if (CollisionBoxToBox(_hitPoint, _src->GetInfo(), _dest->GetInfo()))
	{
		// �� �Լ����� ���� ��Ʈ ����Ʈ�� dest �浹ü���� ��������ش�.
		_dest->m_hitPoint = _hitPoint;
		return true;
	}
		
	return false;
}

bool CCollisionManager::CollisionCircleToCircle(Vector2& _hitPoint, CColliderCircle* _src, CColliderCircle* _dest)
{
	/*
		hitPoint(��ġ�� ������ �߾� ��ǥ),
		�浹ü 1�� ���� �� ������,
		�浹ü 2�� ���� �� ������ ������ ������
		�� �� �� �浹�� üũ�Ѵ�.
	*/
	if (CollisionCircleToCircle(_hitPoint, _src->GetInfo(), _dest->GetInfo()))
	{
		// �� �Լ����� ���� ��Ʈ ����Ʈ�� dest �浹ü���� ��������ش�.
		_dest->m_hitPoint = _hitPoint;
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionBoxToCircle(Vector2& HitPoint, CColliderBox* Src, CColliderCircle* Dest)
{
	if (CollisionBoxToCircle(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		// �� �Լ����� ���� ��Ʈ ����Ʈ�� dest �浹ü���� ��������ش�.
		Dest->m_hitPoint = HitPoint;
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionPointToBox(Vector2& _hitPoint, 
	const Vector2& _src, CColliderBox* _dest)
{
	// ���콺�� �ϳ��� '��'�̹Ƿ�, Vector2�� �����Ѵ�.
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
	// ���콺�� �ϳ��� '��'�̹Ƿ�, Vector2�� �����Ѵ�.
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
		hitPoint(��ġ�� ������ �߾� ��ǥ),
		�ڽ� �浹ü�� �»�� �� ���ϴ� ��ǥ,
		�� �浹ü�� �� ���� ��ǥ�� ������
		�ڽ� �� ���� �浹�� üũ�Ѵ�.
	*/
	if (CollisionBoxToLine(_hitPoint, _src->GetInfo(), _dest))
	{
		// �� �Լ����� ���� ��Ʈ ����Ʈ�� dest �浹ü���� ��������ش�.
		_dest->m_hitPoint = _hitPoint;
		return true;
	}

	return false;
}



bool CCollisionManager::CollisionBoxToBox(Vector2& _hitPoint, const BoxInfo& _src, const BoxInfo& _dest)
{
	// ���� �浹üũ�� ���⼭ �Ѵ�.

	// ��ǥ������ �浹�� �ƴ� 4���� ��츦 ���� ��󳽴�.
	if (_src.Lt.x > _dest.Rb.x)
		return false;

	else if (_src.Lt.y > _dest.Rb.y)
		return false;

	else if (_src.Rb.x < _dest.Lt.x)
		return false;

	else if (_src.Rb.y < _dest.Lt.y)
		return false;

	// �浹 ������ �κ��� lt, rb ��ǥ�� ���Ѵ�.
	float left = _src.Lt.x > _dest.Lt.x ? _src.Lt.x : _dest.Lt.x;
	float top = _src.Lt.y > _dest.Lt.y ? _src.Lt.y : _dest.Lt.y;
	float right = _src.Rb.x < _dest.Rb.x ? _src.Rb.x : _dest.Rb.x;
	float bottom = _src.Rb.y < _dest.Rb.y ? _src.Rb.y : _dest.Rb.y;

	// ��Ʈ����Ʈ�� ���Ѵ�. x���� y���� ���� ���� ���� 2�������� 
	// �߾� ��ǥ�� ���� ���̴�.
	_hitPoint.x = (left + right) / 2.f;
	_hitPoint.y = (top + bottom) / 2.f;

	return true;
}

bool CCollisionManager::CollisionCircleToCircle(Vector2& _hitPoint, const CircleInfo& _src, const CircleInfo& _dest)
{
	// �� �浹ü�� ���� ������ �Ÿ��� ���Ѵ�.
	float Dist = _src.Center.Distance(_dest.Center);

	// �� �浹ü�� ���� ������ �Ÿ��� �������� �պ��� �۰ų� ������ ������. 
	bool result = Dist <= _src.Radius + _dest.Radius;

	// ��Ʈ ����Ʈ�� �����ش�. �ܼ��ϰ� �� �浹ü�� ������ 1/2 �������� ���Ѵ�.
	_hitPoint = (_src.Center + _dest.Center) / 2.f;

	// result�� true��� �浹, false��� �浹�� �ƴϴ�.
	return result;
}

bool CCollisionManager::CollisionBoxToCircle(Vector2& _hitPoint, const BoxInfo& _src, const CircleInfo& _dest)
{
	/*
		�� �� �簢�� �浹 : 
		- �簢���� 4���� ���� ��������ŭ '��������' Ȯ���Ѵ�.
		  �׷��� '�� ������'�� '�����¿�'�� �� 8�� ������ �����.
		  
		  �簢�� �浹ü ������ '�簢�� A', 
		  Ȯ��� �簢���� '�簢�� B'��� ����.
		
		- �ݴ�� ���� ��������ŭ ����Ѵ�. ���� ���� ���� �߽��� �ȴ�.

		- �� ���� �߽��� �簢�� B�� ���ο� ������ �Ǵ��ؾ� �Ѵ�.
		  ��, �� �������� �簢���� ������ ���̰� �ƴ�, 
		  �������� �� 1.4�� �̹Ƿ� ������ ó���� �� �� ���̴�.

		�����, 
		1. �簢�� B�� �����¿��� ������ ���� �߽��� �����Ѵٸ� '�浹'�̴�.
		2. �簢�� B�� �� �������� ������ ���� �߽��� �����Ѵٸ�,
		   ������ �浹 ó���� �ʿ��ϴ�.
	*/

	// ���� ���� ������ �簢�� A�� '����' �Ǵ� '�¿�' ������ �����ϴ��� �Ǵ��Ѵ�.
	if ((_src.Lt.x <= _dest.Center.x && _dest.Center.x <= _src.Rb.x) ||
		(_src.Lt.y <= _dest.Center.y && _dest.Center.y <= _src.Rb.y))
	{
		// �簢���� ���� ��������ŭ Ȯ���Ѵ�.
		BoxInfo	RC = _src;
		RC.Lt.x -= _dest.Radius;
		RC.Lt.y -= _dest.Radius;
		RC.Rb.x += _dest.Radius;
		RC.Rb.y += _dest.Radius;

		/*
			Ȯ��� �簢��(�簢�� B) �ȿ� ���� ������ ���´ٸ� 
			�浹�� ���̹Ƿ�, �浹�� �ƴ� ��츦 ���� �Ǵ����ش�.
		*/
		if (RC.Lt.x > _dest.Center.x)
			return false;

		else if (RC.Lt.y > _dest.Center.y)
			return false;

		else if (RC.Rb.x < _dest.Center.x)
			return false;

		else if (RC.Rb.y < _dest.Center.y)
			return false;

		// ������� ������ �浹�̴�. ��Ʈ ����Ʈ�� �����ش�.
		/*
			�� �� �簢�� �浹�� ��Ʈ ����Ʈ : 
			- �� �浹ü�� ���������� ���� ������ '�簢�� C'�� �׸���.
			- �簢�� A�� �簢�� C�� �����Ǹ鼭 ��������� �浹 ������
			  ������ ��Ʈ ����Ʈ�� �Ѵ�. (��, �̰͵� ��Ȯ�� ������ �ƴϴ�.)
		*/
		
		// ������ '�簢�� C' 
		BoxInfo	CircleBox;
		CircleBox.Lt = _dest.Center - _dest.Radius;
		CircleBox.Rb = _dest.Center + _dest.Radius;

		// �簢�� A�� �簢�� C�� �浹 ����
		float left = _src.Lt.x > CircleBox.Lt.x ? _src.Lt.x : CircleBox.Lt.x;
		float top = _src.Lt.y > CircleBox.Lt.y ? _src.Lt.y : CircleBox.Lt.y;
		float right = _src.Rb.x < CircleBox.Rb.x ? _src.Rb.x : CircleBox.Rb.x;
		float bottom = _src.Rb.y < CircleBox.Rb.y ? _src.Rb.y : CircleBox.Rb.y;

		// ��Ʈ ����Ʈ
		_hitPoint.x = (left + right) / 2.f;
		_hitPoint.y = (top + bottom) / 2.f;

		return true;
	}

	/*
		�̰����� �Դٸ�, ���� ������ �簢�� B�� �� ������(�밢�� ����)��
		������ ����߿��� �浹���� �ƴ��� �Ǵ��ؾ� �Ѵ�.

		- �簢�� A�� �� �������� �� �浹ü �ȿ� ������ �浹�̴�.

		- �������� �� �������� �Ÿ��� ���� ���������� �۰ų� ������ 
		  ���� ���̴�.
	*/

	// �簢�� A�� 4���� �������� ��Ÿ���� Vector2 �迭�� �����.
	Vector2	Pos[4] =
	{
		_src.Lt,
		Vector2(_src.Rb.x, _src.Lt.y),
		Vector2(_src.Lt.x, _src.Rb.y),
		_src.Rb
	};

	// 4���� �������� �ϳ��� �� �ȿ� �������� �Ǵ��Ѵ�.
	for (int i = 0; i < 4; ++i)
	{
		// �������� �� �������� �Ÿ��� ���Ѵ�.
		float dist = _dest.Center.Distance(Pos[i]);

		// ���������� �۰ų� ������ Ȯ���Ѵ�.
		if (dist <= _dest.Radius)
		{
			// true�� ��� �浹�̹Ƿ�, ���� ���� ��Ʈ ����Ʈ�� �����ش�.
			
			// ������ '�簢�� C' 
			BoxInfo	CircleBox;
			CircleBox.Lt = _dest.Center - _dest.Radius;
			CircleBox.Rb = _dest.Center + _dest.Radius;

			// �簢�� A�� �簢�� C�� �浹 ����
			float left = _src.Lt.x > CircleBox.Lt.x ? _src.Lt.x : CircleBox.Lt.x;
			float top = _src.Lt.y > CircleBox.Lt.y ? _src.Lt.y : CircleBox.Lt.y;
			float right = _src.Rb.x < CircleBox.Rb.x ? _src.Rb.x : CircleBox.Rb.x;
			float bottom = _src.Rb.y < CircleBox.Rb.y ? _src.Rb.y : CircleBox.Rb.y;

			// ��Ʈ ����Ʈ
			_hitPoint.x = (left + right) / 2.f;
			_hitPoint.y = (top + bottom) / 2.f;

			return true;
		}
	}

	// �浹�� �ƴ� ��� ���⼭ ����
	return false;
}

bool CCollisionManager::CollisionPointToBox(Vector2& _hitPoint, const Vector2& _src, const BoxInfo& _dest)
{
	/*
		�� �� �簢�� �浹 : �ܼ��� ���� �簢�� �� ��ǥ��
		���� ������ �ȴ�.
		���� �ƴ� ��츦 ���� �ɷ��ָ� �浹�� üũ�ȴ�.

		������ �ߴ� ���� �Ϻδ�. �ſ� �����ϴ�.
	*/
	if (_dest.Lt.x > _src.x)
		return false;

	else if (_dest.Lt.y > _src.y)
		return false;

	else if (_dest.Rb.x < _src.x)
		return false;

	else if (_dest.Rb.y < _src.y)
		return false;

	// ��Ʈ ����Ʈ�� ���� ��ġ�� ����.
	_hitPoint = _src;

	return true;
}

bool CCollisionManager::CollisionPointToCircle(Vector2& _hitPoint, const Vector2& _src, const CircleInfo& _dest)
{
	/*
		�� �� �� �浹 : ���� ���� �߽� ���� �Ÿ��� ���ϰ�,
		�� �Ÿ��� ���� ������ ���� �۰ų� ������ �浹�̴�.

		������ �ߴ� ���� �Ϻδ�. �ſ� �����ϴ�.
	*/
	float dist = _dest.Center.Distance(_src);

	if (dist <= _dest.Radius)
	{
		// ��Ʈ ����Ʈ�� ���� ��ġ�� ����.
		_hitPoint = _src;

		return true;
	}

	return false;
}

bool CCollisionManager::CollisionBoxToLine(Vector2& _hitPoint, const BoxInfo& _src, const CColliderLine* _dest)
{
	/*
		�簢�� �� �� �浹 : �簢���� �� �������� ��ǥ�� ���� �������� �Ÿ��� ���Ѵ�.

		������ �� ������ (a,b) (c,d)��� �� ��, ������ �������� �Ʒ��� ����.

		(d-b)*x + (a-c)*y + (b*c-a*d) = 0

		���� �� p(x,y)�� �� ���� ������ �Ÿ��� ������ �̿��� Ǯ��,

		distance = (d-b)*x + (a-c)*y + (b*c - a*d) / sqrt(pow((d-b), 2) + pow((a-c), 2)) �̴�.


		�̷��� 4���� ���� ����, �� ������ '��� ���'�̰ų� '��� ����'��� ������ �簢���� �浹�̰�,
		�׷��� �ʴٸ� �浹�� �ƴϴ�
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
		sqrt() : �������� ���ϴ� �Լ� 
		pow() : �ŵ������� ���ִ� �Լ� 
	*/

	float distance1 = ((d - b) * x1 + (a - c) * y1 + (b * c - a * d)) / (sqrt(pow((d - b), 2) + pow((a - c), 2)));
	float distance2 = ((d - b) * x2 + (a - c) * y2 + (b * c - a * d)) / (sqrt(pow((d - b), 2) + pow((a - c), 2)));
	float distance3 = ((d - b) * x3 + (a - c) * y3 + (b * c - a * d)) / (sqrt(pow((d - b), 2) + pow((a - c), 2)));
	float distance4 = ((d - b) * x4 + (a - c) * y4 + (b * c - a * d)) / (sqrt(pow((d - b), 2) + pow((a - c), 2)));

	// ���� ����̰ų� ���� ������ �ƴϸ� �浹�� �ƴϴ�.
	if (distance1 > 0 && distance2 > 0 && distance3 > 0 && distance4 > 0)
		return false;
	else if (distance1 < 0 && distance2 < 0 && distance3 < 0 && distance4 < 0)
		return false;

	// ���� ���
	if (_dest->GetType() == ELineType::Ground)
	{
		// �ڽ��� x��ǥ�� ������ x��ǥ�� ����� ��쵵 �浹�� �ƴ� ������ �Ѵ�.
		// ���� '����'�� �浹�̱� ������ �̰��� ������ �÷��̾ ������ ����� �������� �ʴ´�.
		if (x4 <= a || x3 >= c)
		{
			return false;
		}

		// y���� ���� ����ó��
		if (y3 > b+3)
		{
			return false;
		}
	}
	// ���� ���
	else if (_dest->GetType() == ELineType::Wall)
	{
		// y���� ���� ����ó��
		if (36.f && y3 < b + 1)
		{
			return false;
		}
   
	    // ���� �����̱� ������, ������ � x��ǥ�� �������
		if (x3 > a || x4 < a)
		{
			return false;
		}

		
	}
	// ��ٸ�(��)�� ���
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

		// ����� ��ġ�� �������� ��Ȯ�� ���ο� ���;� ���� �Ǵ��Ѵ�.
		// �簢���� �Ѱ�� x��ǥ�� ������ x��ǥ += 1�ȼ� �ȿ� �����Բ� �Ѵ�.

		// �簢���� ��� x��ǥ
		float boxMiddleX = (x2 + x1) / 2;

		if (boxMiddleX < a-1.f || boxMiddleX > a + 1.f)
		{
			return false;
		}
	}

	// ������� ���� �浹�̴�
	return true;
}

CCollisionManager::CCollisionManager()
{}

CCollisionManager::~CCollisionManager()
{
	// ���������� ��� �����Ѵ�.
	auto	iter = m_mapProfile.begin();
	auto	iterEnd = m_mapProfile.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}