#pragma once
#include "../GameInfo.h"
/*
	������ �浹ü�� �����ϱ� ���� Ŭ�����̴�.

	�浹ü�� ���ҽ��� ���������� ���� ������ �Ѿ ��
	������� �ʴ� �浹ü�� �������ϱ� ������ ������ ������
	�ʿ䰡 �ִ�.
	���� ���� �߰��� �浹ü�� ���� ���� �ְ�, �׿ܿ��� 
	�浹ü�� ���� ����� ���� �پ��ϱ� �����̴�.
*/
class CSceneCollision
{
private:
	std::vector<class CCollider*> m_vecCollider;  // �浹ü ����
	std::vector<class CWidgetWindow*>	m_vecWidgetWindow; // ���� ����
	class CCollider* m_mouseCollision;			  // ���콺�� �浹�� �浹ü
	class CWidget* m_mouseCollisionWidget;		  // ���콺�� �浹�� ����		
public:
	void AddCollider(class CCollider* _collider); // ���Ϳ� �浹ü �߰�
	void AddWidgetWindow(class CWidgetWindow* _window); // ���Ϳ� ���� ������ �߰� 
	void Collision(float _deltaTime);			  // �浹 üũ
	void CollisionMouse(float _deltaTime);		  // ���콺 �浹 üũ
private:
	// �浹ü�� �������� y������ ���� �Լ�
	static bool SortY(class CCollider* _src, class CCollider* _dest);
	/*
		���� ���� :
		* SceneCollision::SortWidget : �浹 üũ�� ���� ����
		���� �浹 üũ�� zOrder�� ū ������ üũ�ؾ� �ϹǷ�
		zOrder�� ū ������ �������� �����Ͽ� ���Ϳ� ���� ���̴�.

		* Scene::SortWidget : �������� ���� ����
		��, zOrder�� ū ������ ���� �������� �׷����Ƿ�,
		�׸� ���� zOrder�� ���� �������� ������������ �׷��� �Ѵ�.
	*/
	static bool SortWidget(class CWidgetWindow* _src, class CWidgetWindow* _dest);
private:
	CSceneCollision();
	~CSceneCollision();

	friend class CScene;
};

