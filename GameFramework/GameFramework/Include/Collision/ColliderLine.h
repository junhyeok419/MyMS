#pragma once
#include "../GameInfo.h"
#include "Collider.h"

// �� Ÿ��
enum class ELineType
{
    Ground,  // ��
    Wall,    // ��
    Ladder,  // ��ٸ�(����)
};

/*
    ��(Line)�� �浹ü�� ��Ÿ���� Ŭ�����̴�.
*/
class CColliderLine :
    public CCollider
{
protected:
    // Data
    float   m_length;    // ����
    LineInfo m_info;     // �� ���� �� ��ǥ
    ELineType m_type;    // Ÿ��
public:
    // Logic
    virtual bool Init();
    virtual void Update(float _deltaTime);
    virtual void PostUpdate(float _deltaTime);
    virtual void Render(HDC _hDC, float _deltaTime);
    virtual bool Collision(CCollider* _dest);     // ���� �浹ü�� ��纰�� �浹 ó���� �Ѵ�.
   // virtual bool CollisionMouse(const Vector2& _mouse); // ���콺 Ŀ���� ��ǥ�� �޾� �浹 ó���� �Ѵ�.
public:
    // Access
    virtual const LineInfo& GetLineInfo() const;
    ELineType GetType() const;
    LineInfo GetInfo() const;
    void SetType(ELineType _type);
    void SetInfo(const Vector2& _pos1, const Vector2& _pos2);
    virtual void SetLength(float _length);  // ���̸� ����
    virtual const float& GetLength() const;
protected:
    // Constructor, destructor
    CColliderLine();
    CColliderLine(const CColliderLine& _collider);
    virtual ~CColliderLine();

    friend class CGameObject;
};

