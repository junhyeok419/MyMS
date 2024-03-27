#pragma once
#include "GameObject.h"
#include "../Collision/ColliderLine.h"
class CWall :
	public CGameObject
{
private:
	CColliderLine* m_line;
public:
	virtual bool Init();
	virtual void Update(float _deltaTime);
	virtual void PostUpdate(float _deltaTime);
	virtual void Render(HDC _hDC, float _deltaTime);
public:
	void SetType(ELineType _type);
	ELineType GetType() const;
private:
	virtual	void CollisionBegin(CCollider* _src, CCollider* _dest);	// 충돌 시작 시 호출될 함수
	virtual void CollisionEnd(CCollider* _src, CCollider* _dest);   // 충돌 종료 시 호출될 함수
public:
	void SetInfo(const Vector2& _pos1, const Vector2& _pos2);
protected:
	CWall();
	CWall(const CWall& obj);
	virtual ~CWall();

	friend class CScene;	// 씬 변수에 씬 정보를 넘겨받기 위해
};

