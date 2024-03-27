#pragma once

#include "GameInfo.h"
#include "SingletonMacro.h"
#include "Scene/Scene.h"

/*
	�Է� ������ : ���ݱ����� �� ������Ʈ Ŭ���� ��ü�� 
	(Ű)�Է� �ڵ带 �ۼ�������, ������ �Է� �����ڿ��� 
	�Է¿� ���� �͵��� ó���ϵ��� �Ѵ�.

	�ٸ� �����ӿ�ũ�� ���� ������ �� �ý����� �����ؼ� ���°� ��õ�Ѵ�.
*/

enum class EInputType
{
	DOWN,
	PUSH,
	UP,
	MAX
};

// ������ Ű �ϳ��� ���� ���¸� ��Ÿ����.
struct KeyState
{
	/*
		�츮�� �˰��ִ� Ű ������ 200���� ���� �ʴ� ��ó��,
		GetAsyncKeyState�� ���ڷ� �� �� �ִ� ������ 200���� �ȵȴ�.
		�� 0~255������ ��(unsigend char)�� ó���� �����ϴ�.
	*/
	unsigned char key;	
	bool down;	// ������ ������ ��
	bool push;	// ������ ���� ��
	bool up;	// ������ �ִ� Ű�� �ö�� ��

	KeyState()
		: key(0)
		, down(false)
		, push(false)
		, up(false)
	{}
};

struct BindFunction
{
	void* obj;
	// func�� �Լ��� ����Ѵ�.
	std::function<void()> func;

	class CScene* scene;

	BindFunction()
		: obj(nullptr)
		, scene(nullptr)

	{}
};

// ���� ������(���ε� ��) Ű�� ���� ���Ǹ� ��Ÿ����.
struct BindKey
{
	KeyState* key;		// � Ű����
	std::string name;	// Ű�� �ٿ��� �̸�(����, ���� �̵� ��)
	
	bool ctrl;			// �ش� ���� Ű�� ���� ���Ǵ���
	bool alt;
	bool shift;

	/*
		Ű�� ������ �� ����� �Լ��� ����Ѵ�.
		���� �Լ��� ����� ������ �ϱ� ���� ������ �迭�� �����Ѵ�.

		���� ��� aŰ�� �� ����(down, push, up)���� ���� �Լ��� 
		����� �� �ֵ��� �ϱ� �����̴�.
	*/
	std::vector<BindFunction*> vecFunction[(int)EInputType::MAX];

	BindKey()
		: key(nullptr)
		, ctrl(false)
		, alt(false)
		, shift(false)
	{}
};

class CInput
{
	DECLARE_SINGLE(CInput)
private:
	// ��ϵ� ������ Ű�� ��� <Ű(������ȣ), ��>
	std::unordered_map<unsigned char, KeyState*> m_mapKeyState;
	// ���� ������ Ű�� ���� ���� ��� <Ű(������ȣ), ��>
	std::unordered_map<std::string, BindKey*> m_mapBindKey;
	// �ش� ����Ű�� ���ȴ��� üũ�ϱ� ���� ������(ctrl, alt, shift)
	bool m_ctrl;
	bool m_alt;
	bool m_shift;

	/*
		���콺 �浹 ���� ����� ���� �ʿ��ϴ�.

		���콺 ��ġ�� 2������ ���� ���̴�.
		1. ȭ��󿡼��� ��ġ (ui�� ���� �뵵)
		2. ī�޶� ����� ��ü ����󿡼��� ��ġ 
	*/
	Vector2	m_mousePos;			// ������ â������ Ŀ�� ��ġ
	Vector2	m_mouseWorldPos;	// ��ü ������������� Ŀ�� ��ġ
	Vector2	m_mouseMove;		// �� �����Ӹ��� ���콺�� �̵���
	/*
		���콺 �浹�� ���콺 Ŀ���� ���̱� ������ 
		Vector2�� �Ǵ��� ����������, 
		���콺�� ��ȣ�ۿ��ϸ� �ȵǴ� ������Ʈ�鵵 ������ �� �ֱ�
		������, ���콺�� �浹 �������ϵ� ����� �� ���̴�.

		���� ���콺�� �浹�Ǳ� ���� ��ü�� �浹 �Ŵ�������
		���콺���� ��ȣ�ۿ���	Ignore�� �������ָ� �ȴ�.
	*/
	CollisionProfile* m_mouseProfile;

	/*
		���콺 ���� ��ư�� ���� ���ǹǷ�
		�⺻������ ���¸� �߰����Ѽ� �ǽð�����
		üũ�� ���̴�.
	*/
	bool m_mouseLDown;
	bool m_mouseLPush;
	bool m_mouseLUp;
	/*
		�̹��� ������ �ִϸ��̼� ����� �������� �ʾұ� ������,
		���콺�� ������Ʈ�� ���� ���̴�. (�ִϸ��̼� ����� ����)
		������ ��¸� ���� ���߿� �ϸ� ����� ����.
	*/
	CSharedPtr<class CGameObject> m_mouseObj;
	// ���콺 Ŀ���� ���̰� ���� ���� ����
	bool	m_showCursor;

	HWND	m_hWnd;

public:
	bool Init(HWND _hWnd);	// ���콺 Ŀ�� ����� ���� ���ӸŴ������� ������ �ڵ��� �޾ƿ´�.
	void Update(float _deltaTime);
	void PostUpdate(float _deltaTime);
	void Render(HDC _hDC, float _deltaTime);
public:
	CSharedPtr<class CGameObject> GetMouseObj() const;
	bool GetMouseLDown() const;
	bool GetMouseLPush() const;
	bool GetMouseLUp()	const;
	const Vector2& GetMousePos();
	const Vector2& GetMouseWorldPos() const;
	const Vector2& GetMouseMove() const;
	CollisionProfile* GetMouseProfile()	const;
	// ī�޶� ��ġ�� ���� ���콺 Ŀ���� ����� ��ġ�� ����Ѵ�.
	void ComputeWorldMousePos(const Vector2& cameraPos);
	// Ű�� ���ε��Ͽ� ����Ѵ�.
	bool AddBindKey(const std::string& _name, unsigned char _key);
private:
	// � ���콺 ��ư�� ���ȴ��� üũ �� ������Ʈ�Ѵ�.
	void UpdateMouse(float _deltaTime);
	// � Ű�� ���ȴ��� üũ �� ������Ʈ�Ѵ�.
	void UpdateKeyState(float _deltaTime);
	// � ���ε�Ű�� ���ȴ��� üũ �� ������Ʈ�Ѵ�.
	void UpdateBindKey(float _deltaTime);
	
	// ���ϴ� ���ε�Ű�� ����Ű ��� ���θ� ���Ѵ�.
	void SetKeyCtrl(const std::string& _name, bool _ctrl = true);
	void SetKeyAlt(const std::string& _name, bool _alt = true);
	void SetKeyShift(const std::string& _name, bool _shift = true);

	// m_mapKeyState ���ο� ���ڷ� ���� Ű�� �ִ��� ã�´�.
	KeyState* FindKeyState(unsigned char _key);
	// m_mapKeyState ���ο� ���ڷ� ���� �̸��� ���� Ű�� �ִ��� ã�´�.
	BindKey* FindBindKey(const std::string& _name);
public:
	/*
		���� ��ȯ�Կ� ���� �÷��̾ ���� �����ϰų� �� ��, 
		������ ����� Ű�� ���� �ݹ� �Լ��� ���� �����ִ� �Լ�.

		�÷��̾ ��� ���ܵθ� ��� ������,
		���� ���� �÷��̾ ���� �����Ѵٴ��� �ϸ� �� �ʿ��ϴ�.
	*/
	void ClearCallback();
	void ClearCallback(class CScene* scene);
public:
	/*
		���ε�Ű�� Ű�� ������ �� ����� �Լ��� �߰��Ѵ�.
		1. ���ε�Ű�� �̸�
		2. EInputType ����(��� �Է� ������ ����� �Լ�����)
		3. ����� �Լ��� ��ü �ּ�
		4. ����� �Լ��� �ּ�

		� Ŭ������ ����Լ� ��ϵ��� �𸣹Ƿ� ���ø����� �����.
	*/
	template <typename T> 
	void AddBindFunction(const std::string& _keyName,
		EInputType _type, T* _object, void (T:: *_func)(), class CScene* _scene)
	{
		// �̸��� �ش��ϴ� ���ε�Ű�� ã�´�.
		BindKey* key = FindBindKey(_keyName);

		if (!key)
			return;

		/*
			���ε�Ű�� ������ �� ����� �Լ��� ����ϱ� ����,
			BindFunction ��ü�� �����Ѵ�.
		*/
		BindFunction* function = new BindFunction;

		// ����� ����Լ��� ��ü �ּҸ� �����Ѵ�.
		function->obj = _object;

		/*
			std::bind : �Լ� ���
			����Լ��� ����� ��, �Լ��ּҿ� ��ü�ּҸ� 
			��� �����ؾ� �Ѵ�.
		*/
		function->func = std::bind(_func, _object);
		function->scene = _scene;

		// ���ε�Ű�� �ϼ��� BindFunction ��ü�� �߰��Ѵ�.
		key->vecFunction[(int)_type].push_back(function);
	}

	template <typename T>
	bool DeleteBindFunction(const std::string& Name, EInputType Type, T* Obj)
	{
		BindKey* Key = FindBindKey(Name);

		if (!Key)
			return false;

		auto	iter = Key->vecFunction[(int)Type].begin();
		auto	iterEnd = Key->vecFunction[(int)Type].end();

		for (; iter != iterEnd;)
		{
			if ((*iter)->obj == Obj)
			{
				SAFE_DELETE((*iter));
				iter = Key->vecFunction[(int)Type].erase(iter);
				iterEnd = Key->vecFunction[(int)Type].end();
				continue;
			}

			++iter;
		}

		return true;
	}

};

