#pragma once
#include "../GameInfo.h"
#include "../SingletonMacro.h"

/*
	�浹 �Ŵ��� : �浹 �� �������ϵ��� �����Ѵ�. 
*/

class CCollisionManager
{
	DECLARE_SINGLE(CCollisionManager)
private:
	std::unordered_map<std::string, CollisionProfile*>	m_mapProfile;	// �浹 �������ϵ��� �����ϴ� map

public:
	bool Init();
	/*
		�浹 ���������� �����Ѵ�.
		���������� �̸�, � ä���� ����� ����, Ȱ��ȭ ����, �⺻ ��ȣ�ۿ� ���¸� �����Ѵ�.
	*/
	bool CreateProfile(const std::string& _name, ECollisionChannel _channel, bool _enable,
		ECollisionInteraction _baseInteraction = ECollisionInteraction::Collision);
	/*
		������ �浹 ���������� �����Ѵ�.
		������ ���������� �̸���, � ä��(_channel)�� ����ϴ� �������ϰ� 
		��� ��ȣ�ۿ�(_interaction)�� ���� �����Ѵ�.
	*/
	bool SetCollisionInteraction(const std::string& _name, ECollisionChannel _channel,
		ECollisionInteraction _interaction);
	// Ű(_name)�� �ش��ϴ� ���������� ã�´�.
	CollisionProfile* FindProfile(const std::string& _name);
	
public:
	// �浹 �����̴�.
	bool CollisionBoxToBox(Vector2& _hitPoint, class CColliderBox* _src, class CColliderBox* _dest);
	bool CollisionCircleToCircle(Vector2& _hitPoint, class CColliderCircle* _src, class CColliderCircle* _dest);
	bool CollisionBoxToCircle(Vector2& _hitPoint, class CColliderBox* _src, class CColliderCircle* _dest);
	bool CollisionPointToBox(Vector2& _hitPoint, const Vector2& _src, class CColliderBox* _dest);
	bool CollisionPointToCircle(Vector2& _hitPoint, const Vector2& _src, class CColliderCircle* _dest);
	bool CollisionBoxToLine(Vector2& _hitPoint, class CColliderBox* _src, class CColliderLine* _dest);
public:
	bool CollisionBoxToBox(Vector2& _hitPoint, const BoxInfo& _src, const BoxInfo& _dest);
	bool CollisionCircleToCircle(Vector2& _hitPoint, const CircleInfo& _src, const CircleInfo& _dest);
	bool CollisionBoxToCircle(Vector2& _hitPoint, const BoxInfo& _src, const CircleInfo& _dest);
	bool CollisionPointToBox(Vector2& _hitPoint, const Vector2& _src, const BoxInfo& _dest);
	bool CollisionPointToCircle(Vector2& _hitPoint, const Vector2& _src, const CircleInfo& _dest);
	bool CollisionBoxToLine(Vector2& _hitPoint, const BoxInfo& _src, const CColliderLine* _dest);
};

