#pragma once
#include "../GameInfo.h"
/*
	씬별로 충돌체를 관리하기 위한 클래스이다.

	충돌체도 리소스와 마찬가지로 다음 씬으로 넘어갈 때
	사용하지 않는 충돌체는 지워야하기 때문에 씬별로 관리할
	필요가 있다.
	또한 씬의 중간에 충돌체가 생길 수도 있고, 그외에도 
	충돌체에 대한 경우의 수가 다양하기 때문이다.
*/
class CSceneCollision
{
private:
	std::vector<class CCollider*> m_vecCollider;  // 충돌체 벡터
	std::vector<class CWidgetWindow*>	m_vecWidgetWindow; // 위젯 벡터
	class CCollider* m_mouseCollision;			  // 마우스와 충돌한 충돌체
	class CWidget* m_mouseCollisionWidget;		  // 마우스와 충돌한 위젯		
public:
	void AddCollider(class CCollider* _collider); // 벡터에 충돌체 추가
	void AddWidgetWindow(class CWidgetWindow* _window); // 벡터에 위젯 윈도우 추가 
	void Collision(float _deltaTime);			  // 충돌 체크
	void CollisionMouse(float _deltaTime);		  // 마우스 충돌 체크
private:
	// 충돌체의 내림차순 y소팅을 위한 함수
	static bool SortY(class CCollider* _src, class CCollider* _dest);
	/*
		위젯 정렬 :
		* SceneCollision::SortWidget : 충돌 체크를 위한 정렬
		위젯 충돌 체크는 zOrder가 큰 순서로 체크해야 하므로
		zOrder가 큰 순으로 내림차순 정렬하여 벡터에 넣을 것이다.

		* Scene::SortWidget : 렌더링을 위한 정렬
		단, zOrder가 큰 위젯이 가장 마지막에 그려지므로,
		그릴 때는 zOrder가 작은 순서부터 오름차순으로 그려야 한다.
	*/
	static bool SortWidget(class CWidgetWindow* _src, class CWidgetWindow* _dest);
private:
	CSceneCollision();
	~CSceneCollision();

	friend class CScene;
};

