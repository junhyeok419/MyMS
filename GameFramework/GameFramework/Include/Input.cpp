#include "Input.h"
#include "Collision/CollisionManager.h"
#include "Resource/ResourceManager.h"
#include "GameObject/GameObject.h"
#include "Collision/ColliderBox.h"

DEFINITION_SINGLE(CInput)

bool CInput::Init(HWND _hWnd)
{
	// ������ �ڵ��� �޾ƿ´�.
	m_hWnd = _hWnd;

	// ���ε�Ű�� ����Ѵ�.
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


	// Skill2�� ���� Ű ctrl�� �߰��Ѵ�. 
	SetKeyCtrl("Skill2");

	// ī�޶� ��ȯ�� ���� ���ε�Ű�� ����Ѵ�. 
	AddBindKey("Cam1", VK_F1);
	AddBindKey("Cam2", VK_F2);

	m_ctrl = false;
	m_alt = false;
	m_shift = false;

	// ���콺�� �浹 ���������� �޾ƿ� �����Ѵ�.
	// �̰��� ���� ���� �Ŵ������� �浹�� ���� Init�Ѵ�.
	m_mouseProfile = CCollisionManager::GetInst()->FindProfile("Mouse");

	// �Ʒ��� ���콺 Ŀ���� �ؽ��� ������ ���� ��
	/*
		�츮�� ���� ���콺 �̹����� sprite Ÿ���� �̹����� �ƴ�
		���� ������ �̷���� frame �̹����̱� ������, �ؽ��� ����
		�̸��� ���� ���͸� wstring���� �Ѵ�. (LoadTexture�� �׷��� �������)
	*/
	std::vector<std::wstring>	vecFileName;

	/*
		�ݺ��� ���� ���콺 Ŀ���� ǥ���ϴ� 11���� �ؽ��� ���Ͽ� ���� 
		FileName�� ����� �� ���̴�. 
	*/

	{
		// �� ���ϳ��� ���ڿ��� �����.
		TCHAR	FileName[MAX_PATH] = {};

		// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
		// �׷��� ������� ���ڿ��� FileName�� ������ �ȴ�.
		wsprintf(FileName, TEXT("Maple/UI/Basic/Cursor/Basic.img.Cursor.0.0.bmp"));

		// ������� ���� �̸��� ���Ϳ� �߰��Ѵ�
		vecFileName.push_back(FileName);
	}

	// vecFileName�� ���ڷ� �����ϸ� 11���� �ؽ��ĸ� ��� ����Ѵ�. 
	// (�ؽ��� Ŭ������ vecImageInfo�� 11�� ����ϰ� �� ����)
	CResourceManager::GetInst()->CreateAnimationSequence("MouseDefault",
		"MouseDefault", vecFileName, TEXTURE_PATH);

	// Mouse/0.bmp ~ Mouse/10.bmp �� �ִϸ��̼� �����ӵ����͸� ����Ѵ�.
	// ���ξ����� �÷��̾� ����Ҷ��� ���غ���.
	
		CResourceManager::GetInst()->AddAnimationFrame("MouseDefault", 0.f, 0.f,
			24.f, 28.f);


	// Mouse/0.bmp ~ Mouse/10.bmp �� �÷�Ű�� ����Ѵ�.
	CResourceManager::GetInst()->SetColorKey("MouseDefault", 255, 0, 255);

	

	vecFileName.clear();
	{
		// �� ���ϳ��� ���ڿ��� �����.
		TCHAR	FileName[MAX_PATH] = {};

		// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
		// �׷��� ������� ���ڿ��� FileName�� ������ �ȴ�.
		wsprintf(FileName, TEXT("Maple/UI/Basic/Cursor/Basic.img.Cursor.1.0.bmp"));

		// ������� ���� �̸��� ���Ϳ� �߰��Ѵ�
		vecFileName.push_back(FileName);
	}

	// vecFileName�� ���ڷ� �����ϸ� 11���� �ؽ��ĸ� ��� ����Ѵ�. 
	// (�ؽ��� Ŭ������ vecImageInfo�� 11�� ����ϰ� �� ����)
	CResourceManager::GetInst()->CreateAnimationSequence("MouseHovered",
		"MouseHovered", vecFileName, TEXTURE_PATH);

	// Mouse/0.bmp ~ Mouse/10.bmp �� �ִϸ��̼� �����ӵ����͸� ����Ѵ�.
	// ���ξ����� �÷��̾� ����Ҷ��� ���غ���.
	
		CResourceManager::GetInst()->AddAnimationFrame("MouseHovered", 0.f, 0.f,
			29.f, 30.f);
	

	// Mouse/0.bmp ~ Mouse/10.bmp �� �÷�Ű�� ����Ѵ�.
	CResourceManager::GetInst()->SetColorKey("MouseHovered", 255, 0, 255);


	vecFileName.clear();
	{
		// �� ���ϳ��� ���ڿ��� �����.
		TCHAR	FileName[MAX_PATH] = {};

		// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
		// �׷��� ������� ���ڿ��� FileName�� ������ �ȴ�.
		wsprintf(FileName, TEXT("Maple/UI/Basic/Cursor/Basic.img.Cursor.1.1.bmp"));

		// ������� ���� �̸��� ���Ϳ� �߰��Ѵ�
		vecFileName.push_back(FileName);
	}

	// vecFileName�� ���ڷ� �����ϸ� 11���� �ؽ��ĸ� ��� ����Ѵ�. 
	// (�ؽ��� Ŭ������ vecImageInfo�� 11�� ����ϰ� �� ����)
	CResourceManager::GetInst()->CreateAnimationSequence("MouseClicked",
		"MouseClicked", vecFileName, TEXTURE_PATH);

	// Mouse/0.bmp ~ Mouse/10.bmp �� �ִϸ��̼� �����ӵ����͸� ����Ѵ�.
	// ���ξ����� �÷��̾� ����Ҷ��� ���غ���.
	
		CResourceManager::GetInst()->AddAnimationFrame("MouseClicked", 0.f, 0.f,
			30.f, 28.f);
	

	// Mouse/0.bmp ~ Mouse/10.bmp �� �÷�Ű�� ����Ѵ�.
	CResourceManager::GetInst()->SetColorKey("MouseClicked", 255, 0, 255);
	
	//std::vector<std::wstring>	vecFileName;

	//for (int i = 0; i <= 10; ++i)
	//{
	//	TCHAR	FileName[MAX_PATH] = {};
	//	// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
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


	// ���콺 Ŀ���� ��Ÿ�� ������Ʈ�� �����Ѵ�.
	m_mouseObj = new CGameObject;
	

	// ���۷��� �̸��� ����Ѵ�.
	m_mouseObj->SetName("Mouse");

	m_mouseObj->Init();

	m_mouseObj->SetSize(24.f, 28.f);

	m_mouseObj->CreateAnimation();

	// ������ ���� �ؽ��� �ִϸ��̼��� mouseObj�� �ִϸ��̼����� �߰��Ѵ�.
	m_mouseObj->AddAnimation("MouseDefault", true);
	m_mouseObj->AddAnimation("MouseHovered", true);
	m_mouseObj->AddAnimation("MouseClicked", true);
	

	/*
		ShowCursor : ���ڿ� ���� �⺻ ���콺Ŀ���� ������ ���� �����Ѵ�.
		FALSE -> �Ⱥ���
		TRUE -> ����

		�� �Լ��� ī������ �ϱ� ������, Ƚ���� ���缭 ����ؾ� �Ѵ�.
		���� FALSE�� 2�� ȣ���ϰ� �ٽ� ���̰� �ϰ� ���� ��,
		TRUE�� 1���� �ƴ� �Ȱ��� 2�� ȣ���ؾ� �Ѵ�.
	*/
	ShowCursor(FALSE);
	m_showCursor = false;

	return true;
}

void CInput::Update(float _deltaTime)
{
	m_mouseObj->ChangeAnimation("MouseDefault");

	// �Ʒ��� ����� �Է�(���콺, Ű����)�� ���¸� �ڵ����� ������Ʈ
	
	// � ���콺 ��ư�� ���ȴ��� üũ �� ������Ʈ�Ѵ�.
	UpdateMouse(_deltaTime);

	// � Ű�� ���ȴ��� üũ �� ������Ʈ�Ѵ�.
	UpdateKeyState(_deltaTime);

	// � ���ε�Ű�� ���ȴ��� üũ �� ������Ʈ�Ѵ�.
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
	// �� ���콺 Ŀ�� ��ġ�� ī�޶� ��ġ��ŭ ���ϸ� 
	// ���콺 Ŀ���� ��ü ����� ��ġ�� ���´�.
	m_mouseWorldPos = m_mousePos + cameraPos;
}

bool CInput::AddBindKey(const std::string& _name, unsigned char _key)
{
	// ����� ���ϴ� �̸��� ���� �̸��� ���� BindKey�� ��ϵǾ� ���� ���, ����
	if (FindBindKey(_name))
		return false;

	BindKey* newKey = new BindKey;

	// ����� ���ϴ� key�� ���� key�� �̹� KeyState�� ��ϵǾ� �ִ��� ã�´�.
	KeyState* state = FindKeyState(_key);

	// ����� �ȵǾ� ���� ��� ���� KeyState�� ����� ����Ѵ�.
	if (!state)
	{
		state = new KeyState;
		state->key = _key;

		// key�� state�� map�� <Ű(������ȣ), ��>���� ���
		m_mapKeyState.insert(std::make_pair(_key, state));
	}

	/*
		���ϴ� Ű�� �̹� ����� �Ǿ� ���� ��� 
		KeyState�� �����ٰ� ����Ѵ�.

		BindKey�� ����Ű��� �ϸ�, ���� Ű�� ���� ��쵵 
		���� �� �ֱ� �����̴�.
	*/
	newKey->key = state;
	newKey->name = _name;

	// name�� newKey�� map�� <Ű(������ȣ), ��>���� ���
	m_mapBindKey.insert(std::make_pair(_name, newKey));

	return true;
}

void CInput::UpdateMouse(float _deltaTime)
{

	// ���콺 ��ġ�� �޾ƿ��� ���� POINT����ü�� �����Ѵ�.
	POINT	ptMouse;

	/*
		��ǥ��
		- ��ũ�� ��ǥ�� : ����ȭ�� ��ü�� �������� ��ǥ�� ����.
		  �� ����ȭ�� �»���� (0,0)�� ��.

		- Ŭ���̾�Ʈ ��ǥ�� : ������â�� �������� ��ǥ�� ����.
		  ������â �»���� (0,0)�� ��.

		GetCursorPos : ��ũ�� ��ǥ�� �������� Ŀ�� ��ġ �޾ƿ�
		ScreenToClient : 1��° ������ ������ �������� 2��° ������
		��ǥ�� Ŭ���̾�Ʈ ��ǥ�� ����
	*/

	// ���콺 Ŀ���� ��ġ�� ��ũ�� ��ǥ�� �޾ƿ´�.
	GetCursorPos(&ptMouse);

	// ��ũ�� ��ǥ�� ������ ��ǥ�� �����Ѵ�.
	ScreenToClient(m_hWnd, &ptMouse);

	// ���콺�� �̵����� ����Ѵ�. (�� ��ġ - ���� ��ġ)
	m_mouseMove.x = (float)ptMouse.x - m_mousePos.x;
	m_mouseMove.y = (float)ptMouse.y - m_mousePos.y;

	// ���콺 ��ġ�� ������Ʈ�Ѵ�.
	m_mousePos.x = (float)ptMouse.x;
	m_mousePos.y = (float)ptMouse.y;

	/*
		ShowCursor�� �⺻ ���콺 Ŀ���� ����������,
		Ŭ���̾�Ʈ ���� �� �޴� �ٿ��� 
		�ƹ��� Ŀ���� ������ �ʴ� ������ �߻��Ѵ�.

		���� Ŭ���̾�Ʈ ������ �簢�� ������ ����
		�� ������ ����� �ٽ� �⺻ ���콺 Ŀ���� ���̰� �� ���̴�.
	*/

	// Ŭ���̾�Ʈ ������ �簢�� ������ �޾ƿ´�.
	RECT	rc = {};
	GetClientRect(m_hWnd, &rc);

	// ���콺 Ŀ���� Ŭ���̾�Ʈ ���� ���ο� �ִٸ�
	if (rc.left <= ptMouse.x && ptMouse.x <= rc.right &&
		rc.top <= ptMouse.y && ptMouse.y <= rc.bottom)
	{
		// �⺻ ���콺 Ŀ�� off
		if (m_showCursor)
		{
			m_showCursor = false;
			ShowCursor(FALSE);
		}
	}
	// ������(�޴� ��) �����ٸ�
	else
	{
		// �⺻ ���콺 Ŀ�� on
		if (!m_showCursor)
		{
			m_showCursor = true;
			ShowCursor(TRUE);
		}
	}

	// ���콺 ���� ��ư�� ���ȴٸ�
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		// down, push�� �Ѵ� false��� ���� �� ���ȴٴ� ���̹Ƿ�
		if (!m_mouseLDown && !m_mouseLPush)
		{
			// down, push�� true�� ����
			m_mouseLDown = true;
			m_mouseLPush = true;
		}
		// down, push�� �� �� �ϳ��� true��� �̹� �����ִٴ� ���̹Ƿ�
		// (��� push�� true�ų� �� �� true�� �����) 
		else
			// down�� false�� ����
			m_mouseLDown = false;
	}
	// ���콺�� �ȴ��ȴµ� push�� true���, ������ �ôٴ� ���̹Ƿ� 
	else if (m_mouseLPush)
	{
		// down, push�� false��
		m_mouseLDown = false;
		m_mouseLPush = false;
		// up�� true��
		m_mouseLUp = true;
	}
	// ���콺�� �ȴ����µ� m_mouseLUp�� true���, ���� 1������ �̻� �����ٴ� ���̹Ƿ�
	else if (m_mouseLUp)
		// up�� false��, (��� ������ false����)
		m_mouseLUp = false;

	// ���콺 Ŀ�� ������Ʈ�� ��ġ ����
	m_mouseObj->SetPos(m_mouseWorldPos.x, m_mouseWorldPos.y);

	// ���콺 Ŀ�� ������Ʈ�� ������Ʈ ó��
	m_mouseObj->Update(_deltaTime);

	
}

void CInput::UpdateKeyState(float _deltaTime)
{
	// ���� ����Ű�� ���ȴ��� Ȯ���Ѵ�.
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
	
	// ��������, ���� Ű�� ���ȴ��� Ȯ���Ѵ�.
	for (; iter != iterEnd; ++iter)
	{
		bool keyPush = false;

		// Ű�� ���ȴ��� Ȯ��
		if (GetAsyncKeyState(iter->second->key) & 0x8000)
		{
			keyPush = true;
		}

		// Ű�� ������ ���
		if (keyPush)
		{
			/*
				down, push�� ��� false ���, �� Ű�� ���� ���� ���̴�.
				���� down, push�� true�� �����Ѵ�.
			*/
			if (!iter->second->down && !iter->second->push)
			{
				iter->second->down = true;
				iter->second->push = true;
			}
			/*
				down, push�߿� �� �� �ϳ��� true ���,
				down�� false�� �Ǿ�� �Ѵ�.
			*/
			else
				iter->second->down = false;
		}
		// Ű�� ������ �ʾ��� ���
		/*

			Ű�� �� �������µ� push�� true�� ���¶��,
			�� Ű�� ������ �ִٰ� ��� �� ���̴�.
			���� up�� true��, �������� false�� �����Ѵ�.
		*/
		else if (iter->second->push)
		{
			iter->second->up = true;
			iter->second->push = false;
			iter->second->down = false;
		}
		/*
			Ű�� �� �������µ� up�� true�� ���¶��,
			�� Ű�� ���� �� �� ���� ���̴�.
			���� ��� false�� �����Ѵ�. (down, push�� ������ false�� �����)
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
			���ε�Ű �߿��� ������(���°� DOWN��) Ű�� ã�´�. 
			���� Ű + ���� Ű ���ΰ� ��� ���ƾ� ������ Ű��� �� �� �ִ�.
		*/
		if (iter->second->key->down &&
			iter->second->ctrl == m_ctrl &&
			iter->second->alt == m_alt &&
			iter->second->shift == m_shift)
		{
			size_t size = iter->second->vecFunction[(int)EInputType::DOWN].size();
			
			for (size_t i = 0; i < size; ++i)
			{
				// �ش� ���ε�Ű�� ����� �Լ��� ��� ȣ���Ѵ�. 
				iter->second->vecFunction[(int)EInputType::DOWN][i]->func();
			}
		}

		// ���ε�Ű �߿��� ���°� PUSH�� Ű�� ã�´�.
		if (iter->second->key->push &&
			iter->second->ctrl == m_ctrl &&
			iter->second->alt == m_alt &&
			iter->second->shift == m_shift)
		{
			size_t size = iter->second->vecFunction[(int)EInputType::PUSH].size();

			for (size_t i = 0; i < size; ++i)
			{
				// �ش� ���ε�Ű�� ����� �Լ��� ��� ȣ���Ѵ�. 
				iter->second->vecFunction[(int)EInputType::PUSH][i]->func();
			}
		}

		// ���ε�Ű �߿��� ���°� UP�� Ű�� ã�´�.
		if (iter->second->key->up &&
			iter->second->ctrl == m_ctrl &&
			iter->second->alt == m_alt &&
			iter->second->shift == m_shift)
		{
			size_t size = iter->second->vecFunction[(int)EInputType::UP].size();

			for (size_t i = 0; i < size; ++i)
			{
				// �ش� ���ε�Ű�� ����� �Լ��� ��� ȣ���Ѵ�. 
				iter->second->vecFunction[(int)EInputType::UP][i]->func();
			}
		}
	}

}

void CInput::SetKeyCtrl(const std::string& _name, bool _ctrl)
{
	// �ش� ���ε�Ű�� ã�Ƽ�
	BindKey* key = FindBindKey(_name);

	if (!key)
		return;

	// ctrl�� ���� ����ϵ��� �����Ѵ�.
	key->ctrl = _ctrl;
}

void CInput::SetKeyAlt(const std::string& _name, bool _alt)
{
	// �ش� ���ε�Ű�� ã�Ƽ�
	BindKey* key = FindBindKey(_name);

	if (!key)
		return;

	// alt�� ���� ����ϵ��� �����Ѵ�.
	key->alt = _alt;
}

void CInput::SetKeyShift(const std::string& _name, bool _shift)
{
	// �ش� ���ε�Ű�� ã�Ƽ�
	BindKey* key = FindBindKey(_name);

	if (!key)
		return;

	// shift�� ���� ����ϵ��� �����Ѵ�.
	key->shift = _shift;
}

KeyState* CInput::FindKeyState(unsigned char _key)
{
	std::unordered_map<unsigned char, KeyState*>::iterator iter = m_mapKeyState.find(_key);

	// ��ã���� ���(���� ���ͷ����� ��ȯ)
	if (iter == m_mapKeyState.end())
	{
		return nullptr;
	}

	/*
		ã���� ���, value(���⼱ KeyState*) ��ȯ
		iter -> first : key
		iter -> second : value
	*/
	return iter->second;
}

BindKey* CInput::FindBindKey(const std::string& _name)
{
	std::unordered_map<std::string, BindKey*>::iterator iter = m_mapBindKey.find(_name);

	// ��ã���� ���(���� ���ͷ����� ��ȯ)
	if (iter == m_mapBindKey.end())
	{
		return nullptr;
	}

	/*
		ã���� ���, value(���⼱ BindKey*) ��ȯ
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
				��� ���ε� Ű�� ��ϵ� �ݹ��Լ��� (���� �迭) 
				���� ���� ���̴�.
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
	// �Ҹ��ڿ����� ����ߴ� Ű���� ��� ���Ž�Ų��.
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
