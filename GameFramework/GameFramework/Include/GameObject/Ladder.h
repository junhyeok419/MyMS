#pragma once
#include "GameObject.h"
#include "../Collision/ColliderLine.h"
class CLadder :
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
	LineInfo GetLineInfo() const;
private:
	virtual	void CollisionBegin(CCollider* _src, CCollider* _dest);	// �浹 ���� �� ȣ��� �Լ�
	virtual void CollisionEnd(CCollider* _src, CCollider* _dest);   // �浹 ���� �� ȣ��� �Լ�
public:
	void SetInfo(const Vector2& _pos1, const Vector2& _pos2);
protected:
	CLadder();
	CLadder(const CLadder& obj);
	virtual ~CLadder();

	friend class CScene;	// �� ������ �� ������ �Ѱܹޱ� ����
};

