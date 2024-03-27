#pragma once
#include "../GameInfo.h"
#include "../SingletonMacro.h"

/*
	충돌 매니저 : 충돌 및 프로파일들을 관리한다. 
*/

class CCollisionManager
{
	DECLARE_SINGLE(CCollisionManager)
private:
	std::unordered_map<std::string, CollisionProfile*>	m_mapProfile;	// 충돌 프로파일들을 관리하는 map

public:
	bool Init();
	/*
		충돌 프로파일을 생성한다.
		프로파일의 이름, 어떤 채널을 사용할 건지, 활성화 상태, 기본 상호작용 상태를 전달한다.
	*/
	bool CreateProfile(const std::string& _name, ECollisionChannel _channel, bool _enable,
		ECollisionInteraction _baseInteraction = ECollisionInteraction::Collision);
	/*
		생성된 충돌 프로파일을 세팅한다.
		세팅할 프로파일의 이름과, 어떤 채널(_channel)을 사용하는 프로파일과 
		어떠한 상호작용(_interaction)을 할지 결정한다.
	*/
	bool SetCollisionInteraction(const std::string& _name, ECollisionChannel _channel,
		ECollisionInteraction _interaction);
	// 키(_name)에 해당하는 프로파일을 찾는다.
	CollisionProfile* FindProfile(const std::string& _name);
	
public:
	// 충돌 로직이다.
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

