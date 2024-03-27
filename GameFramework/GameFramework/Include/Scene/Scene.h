#pragma once

#include "../GameInfo.h"
#include "../UI/WidgetWindow.h"
#include "../UI/WidgetComponent.h"

// 모든 씬이 상속하는 최상위 부모 클래스
class CScene
{
protected:
	/*
		각 씬이 여러 오브젝트를 관리할 수 있게 하는 리스트를 만든다.
		-> 스마트 포인터를 이용한다.
	*/ 
	std::list<CSharedPtr<class CGameObject>> m_objList[(int)ERenderLayer::Max];
	/*
		오브젝트에 속한 위젯 컴포넌트(이름,hp바 등)는 
		오브젝트에 속할지라도 모든 오브젝트보다 나중에 그려지는것이 대부분이다.
		따라서 오브젝트-위젯컴포넌트-위젯윈도우 순으로 그려지게 하기 위해
		씬을 이용할 것이기 때문에 이 변수를 렌더링용으로 추가한다.

		즉 업데이트는 오브젝트 내부에서 하고, 렌더링만 씬에서 직접한다.
	*/
	std::list<CSharedPtr<CWidgetComponent>>	m_widgetComponentList;
	/*
		플레이어와 몬스터는 여러 다른 오브젝트의 대상이 될 수 있으므로,
		씬이 따로 멤버로 갖게 한다.
	*/
	CSharedPtr<class CGameObject> m_player;
	std::list<CSharedPtr<class CGameObject>> m_monsterList;

	/*
		씬에서 위젯을 관리할 수 있도록
		씬의 위젯들을 벡터로 들고있는다.
	*/
	// 정보가 안지워지도록 static으로
	std::vector<CSharedPtr<CWidgetWindow>>	m_vecWidgetWindow;
private:
	// '씬이 관리하는 리소스의 모임'인 씬리소스를 갖고있는다. 생성자에서 바로 동적할당 한다.
	class CSceneResource* m_resource;
	// 씬마다 존재하는 카메라이다.
	class CCamera* m_camera;
	// '씬이 관리하는 충돌체의 모임'인 씬컬리젼을 갖고있는다. 생성자에서 바로 동적할당 한다.
	class CSceneCollision* m_collision;
	bool m_playerGrace;		// 플레이어 무적상태를 씬이 알게해서 몬스터가 알게함
public:
	bool Init();
	void Update(float _deltaTime);
	virtual void PostUpdate(float _deltaTime);
	void Render(HDC _hDC, float _deltaTime);
public:
public:
	void SetGrace(bool _grace);
	bool GetGrace();
	class CSceneCollision* GetCollision() const;
	void SetEffect(class CGameObject* _effect);
	void SetPlayer(class CGameObject* _player);
	class CCamera* GetCamera() const;
	class CGameObject* GetPlayer() const;
	class CSceneResource* GetSceneResource() const;
	void AddWidgetComponent(CWidgetComponent* _widget);
public:
	/*
		씬에 원하는 오브젝트를 추가한다.
		각 오브젝트가 상속하는 레퍼런스 클래스의 멤버 
		_name의 기본 인자는 GameObject로 만든다.
	*/
	template <typename T>
	T* CreateObject(const std::string& _name = "GameObject")
	{
		// 객체 생성
		T* obj = new T;

		// 레퍼런스 클래스에 이름 등록
		obj->SetName(_name);

		// 오브젝트에 씬 정보 전달 (이걸 위해 오브젝트에서 friend선언 필요)
		obj->m_scene = this;

		// 오브젝트 초기화
		if (!obj->Init())
		{
			SAFE_DELETE(obj);
			return nullptr; 
		}

		//// 몬스터 오브젝트 일 경우 전용 리스트에 추가
		//if (_name = "Monster")
		//{
		//	m_monsterList[(int)obj->GetRenderLayer()].push_back((CGameObject*)obj);
		//}
		//else
		// 오브젝트를 리스트에 추가
			m_objList[(int)obj->GetRenderLayer()].push_back((CGameObject*)obj);
		
		return obj;
	}


	/*
		씬에 원하는 위젯을 추가한다.
		각 위젯이 상속하는 ref 클래스의 멤버
		_name의 기본 인자는 Window로 만든다.
	*/
	template <typename T>
	T* CreateWidgetWindow(const std::string& _name = "Window")
	{
		// 객체 생성
		T* window = new T;

		// 레퍼런스 클래스에 이름 등록
		window->SetName(_name);

		// 위젯에 자신이 속한 씬 정보 전달
		window->m_scene = this;

		// 위젯 초기화
		if (!window->Init())
		{
			SAFE_DELETE(window);
			return nullptr;
		}

		// 씬의 위젯 벡터에 추가
		m_vecWidgetWindow.push_back(window);

		return (T*)window;
	}

	template <typename T>
	T* FindWidgetWindow(const std::string& Name)
	{
		size_t	Size = m_vecWidgetWindow.size();

		for (size_t i = 0; i < Size; ++i)
		{
			if (m_vecWidgetWindow[i]->GetName() == Name)
				return (T*)m_vecWidgetWindow[i].Get();
		}

		return nullptr;
	}

	/*
		특정 이름의 위젯을 찾아준다.
	*/
	template <typename T>
	T* FindWidget(const std::string& _name)
	{
		size_t	size = m_vecWidgetWindow.size();

		for (size_t i = 0; i < size; ++i)
		{
			if (m_vecWidgetWindow[i]->GetName() == _name)
				return (T*)m_vecWidgetWindow[i].Get();
		}

		return nullptr;
	}
private:
	/*
		y소팅 : 2d게임을 만들 때는 y소팅으로 오브젝트를 정렬한다.
		y축 기준으로 아래쪽에 위치한 오브젝트가 위에 있는 오브젝트를
		덮도록 정렬하는 것이다.

		(오브젝트가 y축 기준 아래쪽에 있는지 위에 있는지는 발밑 기준의
		y값을 이용한다. 정렬의 대상은 씬의 오브젝트 리스트이다.)

		그러나 배경같은 경우에는 관계없이 가장 먼저 출력되어야 하는데,
		이때문에 레이어 개념을 추가한다. (flag.h)
	*/
	static bool SortY(const CSharedPtr<class CGameObject>& _src, 
		const CSharedPtr<class CGameObject>& _dest);

	static bool SortX_Up(const CSharedPtr<class CGameObject>& _src,
		const CSharedPtr<class CGameObject>& _dest);
	static bool SortX_Down(const CSharedPtr<class CGameObject>& _src,
		const CSharedPtr<class CGameObject>& _dest);
	/*
		
	*/
	static bool SortYWidgetComponent(const CSharedPtr<class CWidgetComponent>& _src,
		const CSharedPtr<class CWidgetComponent>& _dest);

	/*
		위젯 정렬 : 
		* SceneCollision::SortWidget : 충돌 체크를 위한 정렬
		위젯 충돌 체크는 zOrder가 큰 순서로 체크해야 하므로
		zOrder가 큰 순으로 내림차순 정렬하여 벡터에 넣을 것이다.

		* Scene::SortWidget : 렌더링을 위한 정렬
		단, zOrder가 큰 위젯이 가장 마지막에 그려지므로,
		그릴 때는 zOrder가 작은 순서부터 오름차순으로 그려야 한다.
	*/
	static bool SortWidget(const CSharedPtr<CWidgetWindow>& _src, 
		const CSharedPtr<CWidgetWindow>& _dest);
	/*
		객체를 외부에서 생성하지 못하게 막아놓기 위해
		생성자를 protected로 선언하였다.
		오직 씬 매니저를 통해서만 씬을 생성/소멸시킬 수 있게 한다.
	*/
protected:
	CScene();
	virtual ~CScene();

	friend class CSceneManager;
};

