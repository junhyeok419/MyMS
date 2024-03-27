#pragma once
#include "GameObject.h"

/*
    일반 불릿이 아닌, 회전하며 발사되는 '토네이도'스킬을 만들 것이다.
    불릿이 가지고 있던 멤버에 3개의 변수가 추가된다(회전각도, 회전반경, 가상선)
    
    특히 가상의 선을 만들고, 그 선을 기준으로 일정 반경의 회전하는 발사체를
    구현하기 위해 linePos 멤버 변수가 필요하다.
*/
class CTornado :
    public CGameObject
{
private:
    float m_moveSpeed;  // 발사속도
    float m_angle;      // (발사)방향 각도
    float m_distance;   // (삭제를 위한)사거리 
    float m_rotationAngle; // (발사체의) 회전 각도
    float m_range;          // 회전 반경
    Vector2 m_linePos;      // 가상의 선 상에서의 점 
public:
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
    virtual void SetPos(float _x, float _y);
    virtual void SetPos(const Vector2& _pos);
    void SetAngle(float _angle);
    void SetDistance(float _distance);
   
protected:
    CTornado();
    CTornado(const CTornado& _obj);
    friend class CScene;
};

