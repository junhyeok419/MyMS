#pragma once
#include "GameObject.h"

/*
    �Ϲ� �Ҹ��� �ƴ�, ȸ���ϸ� �߻�Ǵ� '����̵�'��ų�� ���� ���̴�.
    �Ҹ��� ������ �ִ� ����� 3���� ������ �߰��ȴ�(ȸ������, ȸ���ݰ�, ����)
    
    Ư�� ������ ���� �����, �� ���� �������� ���� �ݰ��� ȸ���ϴ� �߻�ü��
    �����ϱ� ���� linePos ��� ������ �ʿ��ϴ�.
*/
class CTornado :
    public CGameObject
{
private:
    float m_moveSpeed;  // �߻�ӵ�
    float m_angle;      // (�߻�)���� ����
    float m_distance;   // (������ ����)��Ÿ� 
    float m_rotationAngle; // (�߻�ü��) ȸ�� ����
    float m_range;          // ȸ�� �ݰ�
    Vector2 m_linePos;      // ������ �� �󿡼��� �� 
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

