#pragma once
#include "Collider.h"

/*
    원(Circle)형 충돌체를 나타내는 클래스이다.
    
    원 충돌체는 2가지의 데이터(중점, 반지름)로 구성된다.
    두 충돌체 a와 b사이의 거리를 구하고, 이 거리가 두 충돌체의
    반지름의 합보다 같거나 작으면 충돌, 크면 충돌이 아님을 알 수 있다.

    ** 원 충돌체는 히트 포인트(Hit Point)를 정확히 구하지 않을 것이다.
       박스와 다르게 과정이 번거롭고, 정확한 위치가 굳이 필요 없기 때문이다.
       (극도의 정확성이 필요 없는 게임 기준)
       그래서 히트 포인트는 두 원 충돌체의 중점 사이의 거리의 1/2의 좌표로
       구할 것이다.

    ** 원 충돌체의 중점은 충돌체가 속한 오브젝트(Owner)의 pos에 OffSet을 
       더한 값 그대로이다. 
       반지름만 처음에 정해준다.
*/
class CColliderCircle :
    public CCollider
{
protected:
    CircleInfo m_info;  // 중점과 반지름 정보
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void PostUpdate(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
    virtual bool Collision(CCollider* _dest);
    virtual bool CollisionMouse(const Vector2& _mouse); // 마우스 커서의 좌표를 받아 충돌 처리를 한다.
public:
    CircleInfo GetInfo() const;
    void SetRadius(float _radius); 
protected:
    CColliderCircle();
    CColliderCircle(const CColliderCircle& _collider);
    virtual ~CColliderCircle();

    friend class CGameObject;
};

