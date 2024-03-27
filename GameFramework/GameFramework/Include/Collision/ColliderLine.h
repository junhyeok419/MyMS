#pragma once
#include "../GameInfo.h"
#include "Collider.h"

// 선 타입
enum class ELineType
{
    Ground,  // 땅
    Wall,    // 벽
    Ladder,  // 사다리(밧줄)
};

/*
    선(Line)형 충돌체를 나타내는 클래스이다.
*/
class CColliderLine :
    public CCollider
{
protected:
    // Data
    float   m_length;    // 길이
    LineInfo m_info;     // 두 개의 점 좌표
    ELineType m_type;    // 타입
public:
    // Logic
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void PostUpdate(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
    virtual bool Collision(CCollider* _dest);     // 상대방 충돌체의 모양별로 충돌 처리를 한다.
   // virtual bool CollisionMouse(const Vector2& _mouse); // 마우스 커서의 좌표를 받아 충돌 처리를 한다.
public:
    // Access
    virtual const LineInfo& GetLineInfo() const;
    ELineType GetType() const;
    LineInfo GetInfo() const;
    void SetType(ELineType _type);
    void SetInfo(const Vector2& _pos1, const Vector2& _pos2);
    virtual void SetLength(float _length);  // 길이를 지정
    virtual const float& GetLength() const;
protected:
    // Constructor, destructor
    CColliderLine();
    CColliderLine(const CColliderLine& _collider);
    virtual ~CColliderLine();

    friend class CGameObject;
};

