#pragma once

#include "../GameInfo.h"
#include "../SingletonMacro.h"

/*
	������ ���� ���ο��� ������Ʈ�� �����Ѵ�.
	���� ������Ʈ�� ���� ���ӵǹǷ�, ���� �Ҹ�Ǹ�
	�ش� ���� ���ӵ� ��� ������Ʈ�� �Ҹ��ų ���̴�.
*/

// ���� �����ϴ� Ŭ����
class CSceneManager
{
	DECLARE_SINGLE(CSceneManager)
private:
	class CScene* m_scene;	   // ���� ��
	class CScene* m_nextScene; // ���� ���� ���� ����

public:
	bool Init();
	/*
		Update�� ��ȯŸ���� bool�� ������, 
		���� ��ü ���θ� �Ǵ��ϱ� �����̴�.

		Update������ ���ÿ� ���� ���� ��ü�Ǿ��ٸ�,
		Collision�̳� Render�� �ƴ� 
		ó������ �ٽ� �����ؾ� �ϱ� �����̴�.
	*/
	bool Update(float _deltaTime);
	bool PostUpdate(float _deltaTime);
	void Render(HDC _hDC, float _deltaTime);
	class CScene* GetScene() const;

private:
	bool ChangeScene();
public:
	/*
		������ ���ϴ� � Ÿ���� ���� �߰��� �� �ְ� �ϱ� ����,
		���� �߰��ϴ� �Լ��� ���ø����� �����Ѵ�.
	*/
	template <typename T>
	bool CreateScene()
	{
		// �� ����
		T* scene = new T;
		
		// �� �ʱ�ȭ �� �ʱ�ȭ�� ������ ���
		if (!scene->Init())
		{
			SAFE_DELETE(scene);
			return false;
		}

		// ���� ���� ���� ��쿡 �߰�
		if (!m_scene)
			m_scene = (CScene*)scene;
		// ���� ���� �ִٸ� ���� �� ������ �߰�
		else
			m_nextScene = (CScene*)scene;
		
		return true;
	}
};