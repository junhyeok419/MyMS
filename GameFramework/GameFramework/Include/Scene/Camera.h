#pragma once
#include "../GameObject/GameObject.h"
/*
	ī�޶� : ��ũ��(ĳ���� �̵� �� ȭ���� �̵��ϴ� ��)�� �����ϰ� �ϱ� �����̴�.
	ī�޶�� ������ �ϳ��� ��ġ�� ���̸�, 
	��ü �ػ� ���ο��� ī�޶�� Ÿ������ ������ ������Ʈ�� �������� ���� �κ�(������ �ػ�)
	���� ������ ���̴�.

	�� ������� ���� ���̴� �� ī�޶� �����ִ� ��ŭ(=������â�� �ػ�)�� ȭ���̴�.


	*** 
		�̷��� ���� ī�޶�, �ػ� + ��ü�ػ󵵸� �����ص� �˾Ƽ� ó���ȴ�.
		�Ǻ��� ���ϴ� ��� ����. ���� ���, �Ǻ��� (0.2, 0.5)�� ������ ȭ����
		20% �������� ��ũ�Ѹ��� �� ���̴�.
	***
*/
class CCamera
{
	friend class CScene;

private:	
	Vector2 m_pos;						// ���� ī�޶��� ��ġ (������â �ػ��� �»��)
	Vector2 m_resolution;				// ī�޶� ���� (������ â�� �ػ󵵿� ����)
	Vector2 m_worldResolution;			// ��ü ���� �ػ�
	CSharedPtr<CGameObject> m_target;	// ī�޶��� Ÿ�� ������Ʈ. ī�޶� ���� ���̴�.
	Vector2 m_targetOffset;				// Ÿ�����κ��� ī�޶� �󸶳� ���������� ������. �⺻ 0
	/*
		Ÿ�� ������Ʈ�� �Ǻ��̴�.
		�ػ�(m_resolution)�� 1280x720 �̶��,
		Ÿ�� �Ǻ��� 1280x720 �������� Ÿ���� ��ġ�� ���� �����̴�.

		Ÿ���� ȭ���� ����� ���� �Ѿư� ������, �ٸ��ʿ� ġ��ġ�� ����
		�̵��� ������ ���� �����Ѵ�.

		�� ���� 0.5, 0.5��� Ÿ���� ���� �߰��� �Ѿ�� ���� ī�޶� ���󰣴�.
	*/
	Vector2 m_targetPivot;				// Ÿ���� ȭ�鿡�� ��ũ�Ѹ� �� ���� ����		
public:
	void Update(float _deltaTime);
public:
	Vector2 GetPos() const;
	Vector2 GetResolution() const;
	Vector2 GetWorldResolution() const;
	CGameObject* GetTarget() const;
	Vector2 GetTargetOffset() const;
	Vector2 GetTargetPivot() const;
	void SetPos(const Vector2& _pos);
	void SetPos(float _x, float _y);
	void SetResolution(const Vector2& _resolution);
	void SetResolution(float _x, float _y);
	void SetWorldResolution(const Vector2& _worldResolution);
	void SetWorldResolution(float _x, float _y);
	void SetTargetOffset(const Vector2& _targetOffset);
	void SetTargetOffset(float _x, float _y);
	void SetTargetPivot(const Vector2& _targetPivot);
	void SetTargetPivot(float _x, float _y);
	void SetTarget(CGameObject* _target);
private:
	CCamera();
	~CCamera();
};

