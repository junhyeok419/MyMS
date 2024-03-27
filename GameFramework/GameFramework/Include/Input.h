#pragma once

#include "GameInfo.h"
#include "SingletonMacro.h"
#include "Scene/Scene.h"

/*
	입력 관리자 : 지금까지는 각 오브젝트 클래스 자체에 
	(키)입력 코드를 작성했지만, 이제는 입력 관리자에서 
	입력에 관한 것들을 처리하도록 한다.

	다른 프레임워크를 만들 때에도 이 시스템은 복사해서 쓰는걸 추천한다.
*/

enum class EInputType
{
	DOWN,
	PUSH,
	UP,
	MAX
};

// 각각의 키 하나에 대한 상태를 나타낸다.
struct KeyState
{
	/*
		우리가 알고있는 키 개수가 200개가 넘지 않는 것처럼,
		GetAsyncKeyState의 인자로 들어갈 수 있는 개수도 200개가 안된다.
		즉 0~255사이의 값(unsigend char)로 처리가 가능하다.
	*/
	unsigned char key;	
	bool down;	// 누르기 시작할 때
	bool push;	// 누르고 있을 때
	bool up;	// 누르고 있던 키가 올라올 때

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
	// func에 함수를 등록한다.
	std::function<void()> func;

	class CScene* scene;

	BindFunction()
		: obj(nullptr)
		, scene(nullptr)

	{}
};

// 실제 묶여진(바인딩 된) 키에 대한 정의를 나타낸다.
struct BindKey
{
	KeyState* key;		// 어떤 키인지
	std::string name;	// 키에 붙여진 이름(점프, 왼쪽 이동 등)
	
	bool ctrl;			// 해당 조합 키가 같이 사용되는지
	bool alt;
	bool shift;

	/*
		키를 눌렀을 때 사용할 함수를 등록한다.
		여러 함수의 등록을 가능케 하기 위해 벡터의 배열로 선언한다.

		예를 들어 a키의 각 상태(down, push, up)마다 여러 함수를 
		등록할 수 있도록 하기 위함이다.
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
	// 등록된 각각의 키의 목록 <키(고유번호), 값>
	std::unordered_map<unsigned char, KeyState*> m_mapKeyState;
	// 실제 묶여진 키에 대한 정의 목록 <키(고유번호), 값>
	std::unordered_map<std::string, BindKey*> m_mapBindKey;
	// 해당 조합키가 눌렸는지 체크하기 위한 변수들(ctrl, alt, shift)
	bool m_ctrl;
	bool m_alt;
	bool m_shift;

	/*
		마우스 충돌 등의 기능을 위해 필요하다.

		마우스 위치는 2가지로 만들 것이다.
		1. 화면상에서의 위치 (ui를 위한 용도)
		2. 카메라가 적용된 전체 월드상에서의 위치 
	*/
	Vector2	m_mousePos;			// 윈도우 창에서의 커서 위치
	Vector2	m_mouseWorldPos;	// 전체 월드공간에서의 커서 위치
	Vector2	m_mouseMove;		// 매 프레임마다 마우스의 이동량
	/*
		마우스 충돌은 마우스 커서가 점이기 때문에 
		Vector2로 판단이 가능하지만, 
		마우스와 상호작용하면 안되는 오브젝트들도 존재할 수 있기
		때문에, 마우스의 충돌 프로파일도 만들어 줄 것이다.

		만약 마우스와 충돌되기 싫은 물체는 충돌 매니저에서
		마우스와의 상호작용을	Ignore로 설정해주면 된다.
	*/
	CollisionProfile* m_mouseProfile;

	/*
		마우스 왼쪽 버튼은 자주 사용되므로
		기본적으로 상태를 추가시켜서 실시간으로
		체크할 것이다.
	*/
	bool m_mouseLDown;
	bool m_mouseLPush;
	bool m_mouseLUp;
	/*
		이미지 위젯은 애니메이션 기능을 구현하지 않았기 때문에,
		마우스는 오브젝트로 만들 것이다. (애니메이션 사용을 위해)
		어차피 출력만 제일 나중에 하면 상관이 없다.
	*/
	CSharedPtr<class CGameObject> m_mouseObj;
	// 마우스 커서를 보이게 할지 말지 여부
	bool	m_showCursor;

	HWND	m_hWnd;

public:
	bool Init(HWND _hWnd);	// 마우스 커서 계산을 위해 게임매니저에서 윈도우 핸들을 받아온다.
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
	// 카메라 위치를 통해 마우스 커서의 월드상 위치를 계산한다.
	void ComputeWorldMousePos(const Vector2& cameraPos);
	// 키를 바인딩하여 등록한다.
	bool AddBindKey(const std::string& _name, unsigned char _key);
private:
	// 어떤 마우스 버튼이 눌렸는지 체크 및 업데이트한다.
	void UpdateMouse(float _deltaTime);
	// 어떤 키가 눌렸는지 체크 및 업데이트한다.
	void UpdateKeyState(float _deltaTime);
	// 어떤 바인드키가 눌렸는지 체크 및 업데이트한다.
	void UpdateBindKey(float _deltaTime);
	
	// 원하는 바인드키에 조합키 사용 여부를 정한다.
	void SetKeyCtrl(const std::string& _name, bool _ctrl = true);
	void SetKeyAlt(const std::string& _name, bool _alt = true);
	void SetKeyShift(const std::string& _name, bool _shift = true);

	// m_mapKeyState 내부에 인자로 들어온 키가 있는지 찾는다.
	KeyState* FindKeyState(unsigned char _key);
	// m_mapKeyState 내부에 인자로 들어온 이름을 가진 키가 있는지 찾는다.
	BindKey* FindBindKey(const std::string& _name);
public:
	/*
		씬의 전환함에 따라 플레이어를 새로 생성하거나 할 때, 
		씬에서 등록한 키에 대한 콜백 함수를 몽땅 지워주는 함수.

		플레이어를 계속 남겨두면 상관 없지만,
		씬에 따라 플레이어를 새로 생성한다던가 하면 꼭 필요하다.
	*/
	void ClearCallback();
	void ClearCallback(class CScene* scene);
public:
	/*
		바인드키에 키를 눌렀을 때 사용할 함수를 추가한다.
		1. 바인드키의 이름
		2. EInputType 정보(어느 입력 시점에 사용할 함수인지)
		3. 등록할 함수의 객체 주소
		4. 등록할 함수의 주소

		어떤 클래스의 멤버함수 등록될지 모르므로 템플릿으로 만든다.
	*/
	template <typename T> 
	void AddBindFunction(const std::string& _keyName,
		EInputType _type, T* _object, void (T:: *_func)(), class CScene* _scene)
	{
		// 이름에 해당하는 바인드키를 찾는다.
		BindKey* key = FindBindKey(_keyName);

		if (!key)
			return;

		/*
			바인드키를 눌렀을 때 사용할 함수를 등록하기 위해,
			BindFunction 객체를 생성한다.
		*/
		BindFunction* function = new BindFunction;

		// 등록할 멤버함수의 객체 주소를 전달한다.
		function->obj = _object;

		/*
			std::bind : 함수 등록
			멤버함수를 등록할 때, 함수주소와 객체주소를 
			모두 전달해야 한다.
		*/
		function->func = std::bind(_func, _object);
		function->scene = _scene;

		// 바인드키에 완성된 BindFunction 객체를 추가한다.
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

