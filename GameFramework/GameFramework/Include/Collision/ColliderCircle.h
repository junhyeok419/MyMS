#pragma once
#include "Collider.h"

/*
    ��(Circle)�� �浹ü�� ��Ÿ���� Ŭ�����̴�.
    
    �� �浹ü�� 2������ ������(����, ������)�� �����ȴ�.
    �� �浹ü a�� b������ �Ÿ��� ���ϰ�, �� �Ÿ��� �� �浹ü��
    �������� �պ��� ���ų� ������ �浹, ũ�� �浹�� �ƴ��� �� �� �ִ�.

    ** �� �浹ü�� ��Ʈ ����Ʈ(Hit Point)�� ��Ȯ�� ������ ���� ���̴�.
       �ڽ��� �ٸ��� ������ ���ŷӰ�, ��Ȯ�� ��ġ�� ���� �ʿ� ���� �����̴�.
       (�ص��� ��Ȯ���� �ʿ� ���� ���� ����)
       �׷��� ��Ʈ ����Ʈ�� �� �� �浹ü�� ���� ������ �Ÿ��� 1/2�� ��ǥ��
       ���� ���̴�.

    ** �� �浹ü�� ������ �浹ü�� ���� ������Ʈ(Owner)�� pos�� OffSet�� 
       ���� �� �״���̴�. 
       �������� ó���� �����ش�.
*/
class CColliderCircle :
    public CCollider
{
protected:
    CircleInfo m_info;  // ������ ������ ����
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void PostUpdate(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
    virtual bool Collision(CCollider* _dest);
    virtual bool CollisionMouse(const Vector2& _mouse); // ���콺 Ŀ���� ��ǥ�� �޾� �浹 ó���� �Ѵ�.
public:
    CircleInfo GetInfo() const;
    void SetRadius(float _radius); 
protected:
    CColliderCircle();
    CColliderCircle(const CColliderCircle& _collider);
    virtual ~CColliderCircle();

    friend class CGameObject;
};

