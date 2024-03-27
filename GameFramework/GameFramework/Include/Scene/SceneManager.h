#pragma once

#include "../GameInfo.h"
#include "../SingletonMacro.h"

/*
	각각의 씬은 내부에서 오브젝트를 관리한다.
	이제 오브젝트는 씬에 종속되므로, 씬이 소멸되면
	해당 씬에 종속된 모든 오브젝트를 소멸시킬 것이다.
*/

// 씬을 관리하는 클래스
class CSceneManager
{
	DECLARE_SINGLE(CSceneManager)
private:
	class CScene* m_scene;	   // 현재 씬
	class CScene* m_nextScene; // 다음 씬에 대한 정보

public:
	bool Init();
	/*
		Update의 반환타입이 bool인 이유는, 
		씬의 교체 여부를 판단하기 위함이다.

		Update내에서 선택에 의해 씬이 교체되었다면,
		Collision이나 Render가 아닌 
		처음부터 다시 진행해야 하기 때문이다.
	*/
	bool Update(float _deltaTime);
	bool PostUpdate(float _deltaTime);
	void Render(HDC _hDC, float _deltaTime);
	class CScene* GetScene() const;

private:
	bool ChangeScene();
public:
	/*
		앞으로 원하는 어떤 타입의 씬도 추가할 수 있게 하기 위해,
		씬을 추가하는 함수는 템플릿으로 정의한다.
	*/
	template <typename T>
	bool CreateScene()
	{
		// 씬 생성
		T* scene = new T;
		
		// 씬 초기화 및 초기화에 실패할 경우
		if (!scene->Init())
		{
			SAFE_DELETE(scene);
			return false;
		}

		// 현재 씬이 없을 경우에 추가
		if (!m_scene)
			m_scene = (CScene*)scene;
		// 현재 씬이 있다면 다음 씬 정보로 추가
		else
			m_nextScene = (CScene*)scene;
		
		return true;
	}
};