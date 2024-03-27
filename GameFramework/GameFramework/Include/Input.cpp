#include "Input.h"
#include "Collision/CollisionManager.h"
#include "Resource/ResourceManager.h"
#include "GameObject/GameObject.h"
#include "Collision/ColliderBox.h"

DEFINITION_SINGLE(CInput)

bool CInput::Init(HWND _hWnd)
{
	// 윈도우 핸들을 받아온다.
	m_hWnd = _hWnd;

	// 바인드키를 등록한다.
	AddBindKey("GunRotation", VK_RIGHT);
	AddBindKey("GunRotationInv", VK_LEFT);
	AddBindKey("Portal", VK_UP);
	AddBindKey("MoveFront", VK_UP);
	AddBindKey("MoveBack", VK_DOWN);
	AddBindKey("Fire", 'A');
	AddBindKey("Gain", 'Z');
	AddBindKey("Jump", VK_SPACE);
	AddBindKey("PowerStrike", '1');
	AddBindKey("SlashBlast", '2');
	AddBindKey("Judgement", '3');
	AddBindKey("Justice", '4');
	AddBindKey("HPPotion", '5');
	AddBindKey("MPPotion", '6');
	AddBindKey("Skill1", '9');
	AddBindKey("Skill2", '0');


	// Skill2에 조합 키 ctrl을 추가한다. 
	SetKeyCtrl("Skill2");

	// 카메라 전환을 위한 바인드키를 등록한다. 
	AddBindKey("Cam1", VK_F1);
	AddBindKey("Cam2", VK_F2);

	m_ctrl = false;
	m_alt = false;
	m_shift = false;

	// 마우스의 충돌 프로파일을 받아와 세팅한다.
	// 이것을 위해 게임 매니저에서 충돌을 먼저 Init한다.
	m_mouseProfile = CCollisionManager::GetInst()->FindProfile("Mouse");

	// 아래는 마우스 커서의 텍스쳐 변경을 위한 것
	/*
		우리가 가진 마우스 이미지는 sprite 타입의 이미지가 아닌
		여러 장으로 이루어진 frame 이미지이기 때문에, 텍스쳐 파일
		이름에 대한 벡터를 wstring으로 한다. (LoadTexture를 그렇게 만들었음)
	*/
	std::vector<std::wstring>	vecFileName;

	/*
		반복을 통해 마우스 커서를 표현하는 11개의 텍스쳐 파일에 대한 
		FileName이 만들어 질 것이다. 
	*/

	{
		// 빈 파일네임 문자열을 만든다.
		TCHAR	FileName[MAX_PATH] = {};

		// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
		// 그렇게 만들어진 문자열은 FileName에 들어오게 된다.
		wsprintf(FileName, TEXT("Maple/UI/Basic/Cursor/Basic.img.Cursor.0.0.bmp"));

		// 만들어진 파일 이름을 벡터에 추가한다
		vecFileName.push_back(FileName);
	}

	// vecFileName을 인자로 전달하며 11개의 텍스쳐를 모두 등록한다. 
	// (텍스쳐 클래스의 vecImageInfo에 11번 등록하게 될 것임)
	CResourceManager::GetInst()->CreateAnimationSequence("MouseDefault",
		"MouseDefault", vecFileName, TEXTURE_PATH);

	// Mouse/0.bmp ~ Mouse/10.bmp 의 애니메이션 프레임데이터를 등록한다.
	// 메인씬에서 플레이어 등록할때랑 비교해보자.
	
		CResourceManager::GetInst()->AddAnimationFrame("MouseDefault", 0.f, 0.f,
			24.f, 28.f);


	// Mouse/0.bmp ~ Mouse/10.bmp 의 컬러키를 등록한다.
	CResourceManager::GetInst()->SetColorKey("MouseDefault", 255, 0, 255);

	

	vecFileName.clear();
	{
		// 빈 파일네임 문자열을 만든다.
		TCHAR	FileName[MAX_PATH] = {};

		// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
		// 그렇게 만들어진 문자열은 FileName에 들어오게 된다.
		wsprintf(FileName, TEXT("Maple/UI/Basic/Cursor/Basic.img.Cursor.1.0.bmp"));

		// 만들어진 파일 이름을 벡터에 추가한다
		vecFileName.push_back(FileName);
	}

	// vecFileName을 인자로 전달하며 11개의 텍스쳐를 모두 등록한다. 
	// (텍스쳐 클래스의 vecImageInfo에 11번 등록하게 될 것임)
	CResourceManager::GetInst()->CreateAnimationSequence("MouseHovered",
		"MouseHovered", vecFileName, TEXTURE_PATH);

	// Mouse/0.bmp ~ Mouse/10.bmp 의 애니메이션 프레임데이터를 등록한다.
	// 메인씬에서 플레이어 등록할때랑 비교해보자.
	
		CResourceManager::GetInst()->AddAnimationFrame("MouseHovered", 0.f, 0.f,
			29.f, 30.f);
	

	// Mouse/0.bmp ~ Mouse/10.bmp 의 컬러키를 등록한다.
	CResourceManager::GetInst()->SetColorKey("MouseHovered", 255, 0, 255);


	vecFileName.clear();
	{
		// 빈 파일네임 문자열을 만든다.
		TCHAR	FileName[MAX_PATH] = {};

		// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
		// 그렇게 만들어진 문자열은 FileName에 들어오게 된다.
		wsprintf(FileName, TEXT("Maple/UI/Basic/Cursor/Basic.img.Cursor.1.1.bmp"));

		// 만들어진 파일 이름을 벡터에 추가한다
		vecFileName.push_back(FileName);
	}

	// vecFileName을 인자로 전달하며 11개의 텍스쳐를 모두 등록한다. 
	// (텍스쳐 클래스의 vecImageInfo에 11번 등록하게 될 것임)
	CResourceManager::GetInst()->CreateAnimationSequence("MouseClicked",
		"MouseClicked", vecFileName, TEXTURE_PATH);

	// Mouse/0.bmp ~ Mouse/10.bmp 의 애니메이션 프레임데이터를 등록한다.
	// 메인씬에서 플레이어 등록할때랑 비교해보자.
	
		CResourceManager::GetInst()->AddAnimationFrame("MouseClicked", 0.f, 0.f,
			30.f, 28.f);
	

	// Mouse/0.bmp ~ Mouse/10.bmp 의 컬러키를 등록한다.
	CResourceManager::GetInst()->SetColorKey("MouseClicked", 255, 0, 255);
	
	//std::vector<std::wstring>	vecFileName;

	//for (int i = 0; i <= 10; ++i)
	//{
	//	TCHAR	FileName[MAX_PATH] = {};
	//	// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
	//	wsprintf(FileName, TEXT("Mouse/%d.bmp"), i);
	//	vecFileName.push_back(FileName);
	//}

	//CResourceManager::GetInst()->CreateAnimationSequence("MouseDefault",
	//	"MouseDefault", vecFileName, TEXTURE_PATH);

	//for (int i = 0; i < 11; ++i)
	//{
	//	CResourceManager::GetInst()->AddAnimationFrame("MouseDefault", 0.f, 0.f,
	//		32.f, 31.f);
	//}

	//CResourceManager::GetInst()->SetColorKey("MouseDefault", 255, 0, 255);


	// 마우스 커서를 나타낼 오브젝트를 생성한다.
	m_mouseObj = new CGameObject;
	

	// 레퍼런스 이름을 등록한다.
	m_mouseObj->SetName("Mouse");

	m_mouseObj->Init();

	m_mouseObj->SetSize(24.f, 28.f);

	m_mouseObj->CreateAnimation();

	// 위에서 만든 텍스쳐 애니메이션을 mouseObj의 애니메이션으로 추가한다.
	m_mouseObj->AddAnimation("MouseDefault", true);
	m_mouseObj->AddAnimation("MouseHovered", true);
	m_mouseObj->AddAnimation("MouseClicked", true);
	

	/*
		ShowCursor : 인자에 따라 기본 마우스커서를 보일지 말지 결정한다.
		FALSE -> 안보임
		TRUE -> 보임

		이 함수는 카운팅을 하기 때문에, 횟수를 맞춰서 사용해야 한다.
		가령 FALSE로 2번 호출하고 다시 보이게 하고 싶을 때,
		TRUE를 1번이 아닌 똑같이 2번 호출해야 한다.
	*/
	ShowCursor(FALSE);
	m_showCursor = false;

	return true;
}

void CInput::Update(float _deltaTime)
{
	m_mouseObj->ChangeAnimation("MouseDefault");

	// 아래는 등록한 입력(마우스, 키보드)의 상태를 자동으로 업데이트
	
	// 어떤 마우스 버튼이 눌렸는지 체크 및 업데이트한다.
	UpdateMouse(_deltaTime);

	// 어떤 키가 눌렸는지 체크 및 업데이트한다.
	UpdateKeyState(_deltaTime);

	// 어떤 바인드키가 눌렸는지 체크 및 업데이트한다.
	UpdateBindKey(_deltaTime);
}

void CInput::PostUpdate(float _deltaTime)
{
	m_mouseObj->PostUpdate(_deltaTime);
}

void CInput::Render(HDC _hDC, float _deltaTime)
{
	m_mouseObj->Render(_hDC, _deltaTime);
}

CSharedPtr<class CGameObject> CInput::GetMouseObj() const
{
	return m_mouseObj;
}

bool CInput::GetMouseLDown() const
{
	return m_mouseLDown;
}

bool CInput::GetMouseLPush() const
{
	return m_mouseLPush;
}

bool CInput::GetMouseLUp() const
{
	return m_mouseLUp;
}

const Vector2& CInput::GetMousePos()
{
	return m_mousePos;
}

const Vector2& CInput::GetMouseWorldPos() const
{
	return m_mouseWorldPos;
}

const Vector2& CInput::GetMouseMove() const
{
	return m_mouseMove;
}

CollisionProfile* CInput::GetMouseProfile() const
{
	return m_mouseProfile;
}

void CInput::ComputeWorldMousePos(const Vector2& cameraPos)
{
	// 현 마우스 커서 위치에 카메라 위치만큼 더하면 
	// 마우스 커서의 전체 월드상 위치가 나온다.
	m_mouseWorldPos = m_mousePos + cameraPos;
}

bool CInput::AddBindKey(const std::string& _name, unsigned char _key)
{
	// 등록을 원하는 이름과 같은 이름을 가진 BindKey가 등록되어 있을 경우, 리턴
	if (FindBindKey(_name))
		return false;

	BindKey* newKey = new BindKey;

	// 등록을 원하는 key와 같은 key로 이미 KeyState가 등록되어 있는지 찾는다.
	KeyState* state = FindKeyState(_key);

	// 등록이 안되어 있을 경우 새로 KeyState를 만들어 등록한다.
	if (!state)
	{
		state = new KeyState;
		state->key = _key;

		// key와 state를 map의 <키(고유번호), 값>으로 등록
		m_mapKeyState.insert(std::make_pair(_key, state));
	}

	/*
		원하는 키가 이미 등록이 되어 있을 경우 
		KeyState를 가져다가 사용한다.

		BindKey가 조합키라고 하면, 같은 키가 들어가는 경우도 
		있을 수 있기 때문이다.
	*/
	newKey->key = state;
	newKey->name = _name;

	// name와 newKey를 map의 <키(고유번호), 값>으로 등록
	m_mapBindKey.insert(std::make_pair(_name, newKey));

	return true;
}

void CInput::UpdateMouse(float _deltaTime)
{

	// 마우스 위치를 받아오기 위한 POINT구조체를 선언한다.
	POINT	ptMouse;

	/*
		좌표계
		- 스크린 좌표계 : 바탕화면 전체를 기준으로 좌표를 결정.
		  즉 바탕화면 좌상단이 (0,0)이 됨.

		- 클라이언트 좌표계 : 윈도우창을 기준으로 좌표를 결정.
		  윈도우창 좌상단이 (0,0)이 됨.

		GetCursorPos : 스크린 좌표계 기준으로 커서 위치 받아옴
		ScreenToClient : 1번째 인자의 윈도우 기준으로 2번째 인자의
		좌표를 클라이언트 좌표로 변경
	*/

	// 마우스 커서의 위치를 스크린 좌표로 받아온다.
	GetCursorPos(&ptMouse);

	// 스크린 좌표를 윈도우 좌표로 변경한다.
	ScreenToClient(m_hWnd, &ptMouse);

	// 마우스의 이동량을 계산한다. (현 위치 - 이전 위치)
	m_mouseMove.x = (float)ptMouse.x - m_mousePos.x;
	m_mouseMove.y = (float)ptMouse.y - m_mousePos.y;

	// 마우스 위치를 업데이트한다.
	m_mousePos.x = (float)ptMouse.x;
	m_mousePos.y = (float)ptMouse.y;

	/*
		ShowCursor로 기본 마우스 커서를 지워버리면,
		클라이언트 영역 밖 메뉴 바에서 
		아무런 커서가 보이지 않는 문제가 발생한다.

		따라서 클라이언트 영역의 사각형 정보를 구해
		그 영역을 벗어나면 다시 기본 마우스 커서를 보이게 할 것이다.
	*/

	// 클라이언트 영역의 사각형 정보를 받아온다.
	RECT	rc = {};
	GetClientRect(m_hWnd, &rc);

	// 마우스 커서가 클라이언트 영역 내부에 있다면
	if (rc.left <= ptMouse.x && ptMouse.x <= rc.right &&
		rc.top <= ptMouse.y && ptMouse.y <= rc.bottom)
	{
		// 기본 마우스 커서 off
		if (m_showCursor)
		{
			m_showCursor = false;
			ShowCursor(FALSE);
		}
	}
	// 밖으로(메뉴 바) 나간다면
	else
	{
		// 기본 마우스 커서 on
		if (!m_showCursor)
		{
			m_showCursor = true;
			ShowCursor(TRUE);
		}
	}

	// 마우스 왼쪽 버튼이 눌렸다면
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		// down, push가 둘다 false라면 이제 막 눌렸다는 뜻이므로
		if (!m_mouseLDown && !m_mouseLPush)
		{
			// down, push를 true로 변경
			m_mouseLDown = true;
			m_mouseLPush = true;
		}
		// down, push가 둘 중 하나라도 true라면 이미 눌려있다는 뜻이므로
		// (사실 push만 true거나 둘 다 true일 경우임) 
		else
			// down을 false로 변경
			m_mouseLDown = false;
	}
	// 마우스는 안눌렸는데 push가 true라면, 눌렀다 뗐다는 뜻이므로 
	else if (m_mouseLPush)
	{
		// down, push는 false로
		m_mouseLDown = false;
		m_mouseLPush = false;
		// up은 true로
		m_mouseLUp = true;
	}
	// 마우스는 안눌렀는데 m_mouseLUp은 true라면, 뗀지 1프레임 이상 지났다는 뜻이므로
	else if (m_mouseLUp)
		// up을 false로, (모든 변수가 false상태)
		m_mouseLUp = false;

	// 마우스 커서 오브젝트의 위치 갱신
	m_mouseObj->SetPos(m_mouseWorldPos.x, m_mouseWorldPos.y);

	// 마우스 커서 오브젝트의 업데이트 처리
	m_mouseObj->Update(_deltaTime);

	
}

void CInput::UpdateKeyState(float _deltaTime)
{
	// 먼저 조합키가 눌렸는지 확인한다.
	if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
		m_ctrl = true;
	else
		m_ctrl = false;

	if (GetAsyncKeyState(VK_MENU) & 0x8000)  // VK_MENU : alt
		m_alt = true;
	else
		m_alt = false;

	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		m_shift = true;
	else
		m_shift = false;

	std::unordered_map<unsigned char, KeyState*>::iterator iter = m_mapKeyState.begin();
	std::unordered_map<unsigned char, KeyState*>::iterator iterEnd = m_mapKeyState.end();
	
	// 다음으로, 메인 키가 눌렸는지 확인한다.
	for (; iter != iterEnd; ++iter)
	{
		bool keyPush = false;

		// 키가 눌렸는지 확인
		if (GetAsyncKeyState(iter->second->key) & 0x8000)
		{
			keyPush = true;
		}

		// 키가 눌렀을 경우
		if (keyPush)
		{
			/*
				down, push가 모두 false 라면, 이 키를 지금 누른 것이다.
				따라서 down, push를 true로 변경한다.
			*/
			if (!iter->second->down && !iter->second->push)
			{
				iter->second->down = true;
				iter->second->push = true;
			}
			/*
				down, push중에 둘 중 하나라도 true 라면,
				down은 false가 되어야 한다.
			*/
			else
				iter->second->down = false;
		}
		// 키를 누르지 않았을 경우
		/*

			키가 안 눌러졌는데 push가 true인 상태라면,
			이 키를 누르고 있다가 방금 뗀 것이다.
			따라서 up은 true로, 나머지는 false로 변경한다.
		*/
		else if (iter->second->push)
		{
			iter->second->up = true;
			iter->second->push = false;
			iter->second->down = false;
		}
		/*
			키가 안 눌러졌는데 up이 true인 상태라면,
			이 키를 뗀지 한 참 지난 것이다.
			따라서 모두 false로 변경한다. (down, push는 위에서 false로 변경됨)
		*/
		else if (iter->second->up)
			iter->second->up = false;
	}
}

void CInput::UpdateBindKey(float _deltaTime)
{
	std::unordered_map<std::string, BindKey*>::iterator iter = m_mapBindKey.begin();
	std::unordered_map<std::string, BindKey*>::iterator iterEnd = m_mapBindKey.end();

	for (; iter != iterEnd; ++iter)
	{
		/*
			바인드키 중에서 눌려진(상태가 DOWN인) 키를 찾는다. 
			메인 키 + 조합 키 여부가 모두 같아야 눌려진 키라고 할 수 있다.
		*/
		if (iter->second->key->down &&
			iter->second->ctrl == m_ctrl &&
			iter->second->alt == m_alt &&
			iter->second->shift == m_shift)
		{
			size_t size = iter->second->vecFunction[(int)EInputType::DOWN].size();
			
			for (size_t i = 0; i < size; ++i)
			{
				// 해당 바인드키에 등록한 함수를 모두 호출한다. 
				iter->second->vecFunction[(int)EInputType::DOWN][i]->func();
			}
		}

		// 바인드키 중에서 상태가 PUSH인 키를 찾는다.
		if (iter->second->key->push &&
			iter->second->ctrl == m_ctrl &&
			iter->second->alt == m_alt &&
			iter->second->shift == m_shift)
		{
			size_t size = iter->second->vecFunction[(int)EInputType::PUSH].size();

			for (size_t i = 0; i < size; ++i)
			{
				// 해당 바인드키에 등록한 함수를 모두 호출한다. 
				iter->second->vecFunction[(int)EInputType::PUSH][i]->func();
			}
		}

		// 바인드키 중에서 상태가 UP인 키를 찾는다.
		if (iter->second->key->up &&
			iter->second->ctrl == m_ctrl &&
			iter->second->alt == m_alt &&
			iter->second->shift == m_shift)
		{
			size_t size = iter->second->vecFunction[(int)EInputType::UP].size();

			for (size_t i = 0; i < size; ++i)
			{
				// 해당 바인드키에 등록한 함수를 모두 호출한다. 
				iter->second->vecFunction[(int)EInputType::UP][i]->func();
			}
		}
	}

}

void CInput::SetKeyCtrl(const std::string& _name, bool _ctrl)
{
	// 해당 바인드키를 찾아서
	BindKey* key = FindBindKey(_name);

	if (!key)
		return;

	// ctrl을 같이 사용하도록 변경한다.
	key->ctrl = _ctrl;
}

void CInput::SetKeyAlt(const std::string& _name, bool _alt)
{
	// 해당 바인드키를 찾아서
	BindKey* key = FindBindKey(_name);

	if (!key)
		return;

	// alt을 같이 사용하도록 변경한다.
	key->alt = _alt;
}

void CInput::SetKeyShift(const std::string& _name, bool _shift)
{
	// 해당 바인드키를 찾아서
	BindKey* key = FindBindKey(_name);

	if (!key)
		return;

	// shift을 같이 사용하도록 변경한다.
	key->shift = _shift;
}

KeyState* CInput::FindKeyState(unsigned char _key)
{
	std::unordered_map<unsigned char, KeyState*>::iterator iter = m_mapKeyState.find(_key);

	// 못찾았을 경우(엔드 이터레이터 반환)
	if (iter == m_mapKeyState.end())
	{
		return nullptr;
	}

	/*
		찾았을 경우, value(여기선 KeyState*) 반환
		iter -> first : key
		iter -> second : value
	*/
	return iter->second;
}

BindKey* CInput::FindBindKey(const std::string& _name)
{
	std::unordered_map<std::string, BindKey*>::iterator iter = m_mapBindKey.find(_name);

	// 못찾았을 경우(엔드 이터레이터 반환)
	if (iter == m_mapBindKey.end())
	{
		return nullptr;
	}

	/*
		찾았을 경우, value(여기선 BindKey*) 반환
		iter -> first : key
		iter -> second : value
	*/
	return iter->second;

}


void CInput::ClearCallback()
{
	auto	iter = m_mapBindKey.begin();
	auto	iterEnd = m_mapBindKey.end();

	for (; iter != iterEnd; ++iter)
	{
		for (int i = 0; i < (int)EInputType::MAX; ++i)
		{
			size_t	size = iter->second->vecFunction[i].size();

			/*
				모든 바인드 키에 등록된 콜백함수을 (벡터 배열) 
				몽땅 지울 것이다.
			*/
			for (size_t j = 0; j < size; ++j)
			{
				SAFE_DELETE(iter->second->vecFunction[i][j]);
			}
			iter->second->vecFunction[i].clear();
		}
	}
}

void CInput::ClearCallback(CScene* scene)
{
	auto	iter = m_mapBindKey.begin();
	auto	iterEnd = m_mapBindKey.end();

	for (; iter != iterEnd; ++iter)
	{
		for (int i = 0; i < (int)EInputType::MAX; ++i)
		{
			auto	iter1 = iter->second->vecFunction[i].begin();
			auto	iter1End = iter->second->vecFunction[i].end();

			for (; iter1 != iter1End;)
			{
				if ((*iter1)->scene == scene)
				{
					SAFE_DELETE((*iter1));
					iter1 = iter->second->vecFunction[i].erase(iter1);
					iter1End = iter->second->vecFunction[i].end();
					continue;
				}

				++iter1;
			}
		}
	}
}

CInput::CInput()
	: m_mouseLDown(false)
	, m_mouseLPush(false)
	, m_mouseLUp(false)
	, m_mouseObj(nullptr)
{}

CInput::~CInput()
{
	// 소멸자에서는 등록했던 키들을 모두 제거시킨다.
	{
		std::unordered_map<unsigned char, KeyState*>::iterator iter = m_mapKeyState.begin();
		std::unordered_map<unsigned char, KeyState*>::iterator iterEnd = m_mapKeyState.end();

		for (; iter != iterEnd; ++iter)
		{
			SAFE_DELETE(iter->second);
		}

		m_mapKeyState.clear();
	}

	{
		std::unordered_map<std::string, BindKey*>::iterator iter = m_mapBindKey.begin();
		std::unordered_map<std::string, BindKey*>::iterator iterEnd = m_mapBindKey.end();
		for (; iter != iterEnd; ++iter)
		{
			for (int i = 0; i < (int)EInputType::MAX; ++i)
			{
				size_t	Size = iter->second->vecFunction[i].size();

				for (size_t j = 0; j < Size; ++j)
				{
					SAFE_DELETE(iter->second->vecFunction[i][j]);
				}
			}

			SAFE_DELETE(iter->second);
		}

		m_mapBindKey.clear();
	}
}
