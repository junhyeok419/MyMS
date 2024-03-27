#pragma once

#include "../GameInfo.h"
#include "../UI/WidgetWindow.h"
#include "../UI/WidgetComponent.h"

// ��� ���� ����ϴ� �ֻ��� �θ� Ŭ����
class CScene
{
protected:
	/*
		�� ���� ���� ������Ʈ�� ������ �� �ְ� �ϴ� ����Ʈ�� �����.
		-> ����Ʈ �����͸� �̿��Ѵ�.
	*/ 
	std::list<CSharedPtr<class CGameObject>> m_objList[(int)ERenderLayer::Max];
	/*
		������Ʈ�� ���� ���� ������Ʈ(�̸�,hp�� ��)�� 
		������Ʈ�� �������� ��� ������Ʈ���� ���߿� �׷����°��� ��κ��̴�.
		���� ������Ʈ-����������Ʈ-���������� ������ �׷����� �ϱ� ����
		���� �̿��� ���̱� ������ �� ������ ������������ �߰��Ѵ�.

		�� ������Ʈ�� ������Ʈ ���ο��� �ϰ�, �������� ������ �����Ѵ�.
	*/
	std::list<CSharedPtr<CWidgetComponent>>	m_widgetComponentList;
	/*
		�÷��̾�� ���ʹ� ���� �ٸ� ������Ʈ�� ����� �� �� �����Ƿ�,
		���� ���� ����� ���� �Ѵ�.
	*/
	CSharedPtr<class CGameObject> m_player;
	std::list<CSharedPtr<class CGameObject>> m_monsterList;

	/*
		������ ������ ������ �� �ֵ���
		���� �������� ���ͷ� ����ִ´�.
	*/
	// ������ ������������ static����
	std::vector<CSharedPtr<CWidgetWindow>>	m_vecWidgetWindow;
private:
	// '���� �����ϴ� ���ҽ��� ����'�� �����ҽ��� �����ִ´�. �����ڿ��� �ٷ� �����Ҵ� �Ѵ�.
	class CSceneResource* m_resource;
	// ������ �����ϴ� ī�޶��̴�.
	class CCamera* m_camera;
	// '���� �����ϴ� �浹ü�� ����'�� ���ø����� �����ִ´�. �����ڿ��� �ٷ� �����Ҵ� �Ѵ�.
	class CSceneCollision* m_collision;
	bool m_playerGrace;		// �÷��̾� �������¸� ���� �˰��ؼ� ���Ͱ� �˰���
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
		���� ���ϴ� ������Ʈ�� �߰��Ѵ�.
		�� ������Ʈ�� ����ϴ� ���۷��� Ŭ������ ��� 
		_name�� �⺻ ���ڴ� GameObject�� �����.
	*/
	template <typename T>
	T* CreateObject(const std::string& _name = "GameObject")
	{
		// ��ü ����
		T* obj = new T;

		// ���۷��� Ŭ������ �̸� ���
		obj->SetName(_name);

		// ������Ʈ�� �� ���� ���� (�̰� ���� ������Ʈ���� friend���� �ʿ�)
		obj->m_scene = this;

		// ������Ʈ �ʱ�ȭ
		if (!obj->Init())
		{
			SAFE_DELETE(obj);
			return nullptr; 
		}

		//// ���� ������Ʈ �� ��� ���� ����Ʈ�� �߰�
		//if (_name = "Monster")
		//{
		//	m_monsterList[(int)obj->GetRenderLayer()].push_back((CGameObject*)obj);
		//}
		//else
		// ������Ʈ�� ����Ʈ�� �߰�
			m_objList[(int)obj->GetRenderLayer()].push_back((CGameObject*)obj);
		
		return obj;
	}


	/*
		���� ���ϴ� ������ �߰��Ѵ�.
		�� ������ ����ϴ� ref Ŭ������ ���
		_name�� �⺻ ���ڴ� Window�� �����.
	*/
	template <typename T>
	T* CreateWidgetWindow(const std::string& _name = "Window")
	{
		// ��ü ����
		T* window = new T;

		// ���۷��� Ŭ������ �̸� ���
		window->SetName(_name);

		// ������ �ڽ��� ���� �� ���� ����
		window->m_scene = this;

		// ���� �ʱ�ȭ
		if (!window->Init())
		{
			SAFE_DELETE(window);
			return nullptr;
		}

		// ���� ���� ���Ϳ� �߰�
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
		Ư�� �̸��� ������ ã���ش�.
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
		y���� : 2d������ ���� ���� y�������� ������Ʈ�� �����Ѵ�.
		y�� �������� �Ʒ��ʿ� ��ġ�� ������Ʈ�� ���� �ִ� ������Ʈ��
		������ �����ϴ� ���̴�.

		(������Ʈ�� y�� ���� �Ʒ��ʿ� �ִ��� ���� �ִ����� �߹� ������
		y���� �̿��Ѵ�. ������ ����� ���� ������Ʈ ����Ʈ�̴�.)

		�׷��� ��氰�� ��쿡�� ������� ���� ���� ��µǾ�� �ϴµ�,
		�̶����� ���̾� ������ �߰��Ѵ�. (flag.h)
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
		���� ���� : 
		* SceneCollision::SortWidget : �浹 üũ�� ���� ����
		���� �浹 üũ�� zOrder�� ū ������ üũ�ؾ� �ϹǷ�
		zOrder�� ū ������ �������� �����Ͽ� ���Ϳ� ���� ���̴�.

		* Scene::SortWidget : �������� ���� ����
		��, zOrder�� ū ������ ���� �������� �׷����Ƿ�,
		�׸� ���� zOrder�� ���� �������� ������������ �׷��� �Ѵ�.
	*/
	static bool SortWidget(const CSharedPtr<CWidgetWindow>& _src, 
		const CSharedPtr<CWidgetWindow>& _dest);
	/*
		��ü�� �ܺο��� �������� ���ϰ� ���Ƴ��� ����
		�����ڸ� protected�� �����Ͽ���.
		���� �� �Ŵ����� ���ؼ��� ���� ����/�Ҹ��ų �� �ְ� �Ѵ�.
	*/
protected:
	CScene();
	virtual ~CScene();

	friend class CSceneManager;
};

