#include "StartWindow.h"
#include "Button.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../GameManager.h"
#include "../Scene/MainScene.h"
#include "../Scene/Scene1.h"
#include "../Scene/Scene2.h"
#include "../Scene/Scene3.h"
#include "../Scene/SceneFinal.h"
#include "../Scene/SceneManager.h"
#include "../Input.h"
#include "ImageWidget.h"
#include "Text.h"
#include "Number.h"

bool CStartWindow::Init()
{
	if (!CWidgetWindow::Init())
		return false;

	m_scene->GetSceneResource()->LoadSound("BGM", "StartSceneBGM", true, "Maple/Back/DeepCave.mp3");

	// ��ư�� Ŀ���� �ö��� �� ����� ���带 �ε��Ѵ�.
	// ������ ä�� �׷��� UI, �̸��� ButtonHovered, ������ false�� �Ѵ�.
	m_scene->GetSceneResource()->LoadSound("UI", "ButtonHovered", false,
		"Maple/BtMouseOver.mp3");
	// ��ư�� Ŭ������ �� ����� ���带 �ε��Ѵ�.
	m_scene->GetSceneResource()->LoadSound("UI", "ButtonClick", false,
		"Maple/ScrollUp.mp3");

	m_scene->GetSceneResource()->SetVolume("UI", 100.f);

	m_scene->GetSceneResource()->SoundPlay("StartSceneBGM");

	// ��ŸƮ ���� �������� ũ��. ��ŸƮ ���� ���� ũ��� �� ���̴�.
	SetSize(1280.f, 720.f);

	// ��� ������ �����Ѵ�.
	CImageWidget* back = CreateWidget<CImageWidget>("Back");

	back->SetTexture("StartBack", TEXT("Maple/Start/start.bmp"));

	back->SetSize(800.f, 600.f);

	
	// ��ư ��ü�� �����Ѵ�.
	CButton* startButton = CreateWidget<CButton>("StartButton");

	// ��ư �ؽ��ĸ� �����Ѵ�.
	startButton->SetTexture("StartButton", TEXT("Maple/Start/startButton.bmp"));

	// ��ư ���¿� ���� �ؽ����� ������ ��ǥ�� �ִ´�.
	startButton->SetButtonStateData(EButtonState::Normal, Vector2(0.f, 0.f), Vector2(200.f, 100.f));
	startButton->SetButtonStateData(EButtonState::MouseHovered, Vector2(0.f, 0.f), Vector2(200.f, 100.f));
	startButton->SetButtonStateData(EButtonState::Click, Vector2(200.f, 0.f), Vector2(400.f, 100.f));
	startButton->SetButtonStateData(EButtonState::Disable, Vector2(600.f, 0.f), Vector2(800.f, 100.f));
	
	// ��ư ���¿� ���� ����� ���带 ã�� �ִ´�.
	startButton->SetSound(EButtonSoundState::MouseHovered, "Hovered");
	startButton->SetSound(EButtonSoundState::Click, "Click");
	
	// ��ư�� ��ġ�� �����Ѵ�.
	startButton->SetPos(300.f, 330.f);
	startButton->SetZOrder(1);
	startButton->SetColorKeyAll(255, 0, 255);

	// ��ŸƮ ��ư�� ���� �ݹ��Լ� ���
	startButton->SetCallback<CStartWindow>(EButtonSoundState::Click,
		this, &CStartWindow::StartButtonCallback);


	CButton* endButton = CreateWidget<CButton>("ExitButton");

	endButton->SetTexture("ExitButton", TEXT("Maple/Start/exitButton.bmp"));

	endButton->SetButtonStateData(EButtonState::Normal, Vector2(0.f, 0.f), Vector2(200.f, 100.f));
	endButton->SetButtonStateData(EButtonState::MouseHovered, Vector2(0.f, 0.f), Vector2(200.f, 100.f));
	endButton->SetButtonStateData(EButtonState::Click, Vector2(200.f, 0.f), Vector2(400.f, 100.f));
	endButton->SetButtonStateData(EButtonState::Disable, Vector2(600.f, 0.f), Vector2(800.f, 100.f));
	
	endButton->SetSound(EButtonSoundState::MouseHovered, "Hovered");
	endButton->SetSound(EButtonSoundState::Click, "Click");
	
	endButton->SetPos(300.f, 450.f);
	endButton->SetZOrder(1);
	endButton->SetColorKeyAll(255, 0, 255);

	// ���� ��ư�� ���� �ݹ��Լ� ���
	endButton->SetCallback<CStartWindow>(EButtonSoundState::Click,
		this, &CStartWindow::EndButtonCallback);


	//// �ؽ�Ʈ ���� �߰�
	//m_text = CreateWidget<CText>("Text");

	//// �ؽ�Ʈ ������ �ؽ�Ʈ ���
	//m_text->SetText(TEXT("�ؽ�Ʈ ���!!"));

	//// ����
	//m_text->SetPos(200.f, 50.f);
	//m_text->SetTextColor(255, 0, 0);
	//m_text->EnableShadow(true);
	//m_text->SetShadowOffset(5.f, 5.f);

	//// ���ʸ��� �ؽ�Ʈ �߰�
	//m_textTime = 0.f;
	//memset(m_addText, 0, sizeof(TCHAR) * 32);
	//lstrcpy(m_addText, TEXT("�濰��"));
	//m_addCount = 0;

	
	// �Ʒ��� �ð� ����� ���� �ڵ��̴�.

	//// ���� ������ �̹��� ����(�ݷ�)�� �߰��Ѵ�.
	//m_hour = CreateWidget<CNumber>("Hour");
	//CImageWidget* Colon = CreateWidget<CImageWidget>("Colon");
	//m_minute = CreateWidget<CNumber>("Minute");
	//m_second = CreateWidget<CNumber>("Second");

	//Colon->SetTexture("Colon", TEXT("Number/Colon.bmp"));
	//Colon->SetSize(29.f, 48.f);
	//Colon->SetPos(558.f, 100.f);
	//Colon->SetColorKey(255, 255, 255);


	//// ������ �̹����� �޾ƿ��� ���� ����
	//std::vector<std::wstring>	vecFileName;

	//for (int i = 0; i <= 9; ++i)
	//{
	//	TCHAR	FileName[MAX_PATH] = {};
	//	// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
	//	wsprintf(FileName, TEXT("Number/%d.bmp"), i);
	//	vecFileName.push_back(FileName);
	//}

	//m_hour->SetTexture("Number", vecFileName);
	//m_minute->SetTexture("Number", vecFileName);
	//m_second->SetTexture("Number", vecFileName);

	//// ��ġ, ũ��, �÷�Ű ����
	//m_hour->SetColorKey(255, 255, 255);
	//m_minute->SetColorKey(255, 255, 255);
	//m_second->SetColorKey(255, 255, 255);

	//m_hour->SetSize(29.f, 48.f);
	//m_hour->SetPos(500.f, 100.f);

	//m_minute->SetSize(29.f, 48.f);
	//m_minute->SetPos(587.f, 100.f);

	//m_second->SetSize(29.f, 48.f);
	//m_second->SetPos(655.f, 100.f);

	//// FPS ��� ���� ����
	//m_FPSText = CreateWidget<CText>("Text");

	//// ��ġ, ũ��, ���� �� ����
	//m_FPSText->SetText(TEXT("FPS"));
	//m_FPSText->SetPos(900.f, 50.f);
	//m_FPSText->SetTextColor(255, 0, 0);
	//m_FPSText->EnableShadow(true);
	//m_FPSText->SetShadowOffset(2.f, 2.f);

	return true;
}

void CStartWindow::Update(float _deltaTime)
{
	CWidgetWindow::Update(_deltaTime);

	/*
		GetLocalTime���� �ý��� �ð��� �޾ƿ�
		Time ������ �����Ѵ�.
	*/
	//SYSTEMTIME Time;
	//GetLocalTime(&Time);

	//// �޾ƿ� �ð����� ���ڸ� �ʱ�ȭ�Ѵ�.
	//m_hour->SetNumber(Time.wHour);
	//m_minute->SetNumber(Time.wMinute);
	//m_second->SetNumber(Time.wSecond);

	// �Ʒ��� �ѱ��ھ� ������ �ϴ� �ڵ� 
	// '�ؽ�Ʈ�� �߰��� ����'�� '�߰��� �ؽ�Ʈ ���ڿ� ����'���� �۴ٸ� 
	//if (m_addCount < lstrlen(m_addText))
	//{
	//	// �ؽ�Ʈ�� �߰��Ǵ� �ð��� ������Ű��
	//	m_textTime += _deltaTime;

	//	// �װ� 1�ʰ� �Ǹ�
	//	if (m_textTime >= 1.f)
	//	{
	//		// 0�ʷ� �ʱ�ȭ��Ų��
	//		m_textTime -= 1.f;

	//		// 1���ڸ� �߰��Ѵ�.
	//		m_text->AddText(m_addText[m_addCount]);

	//		// '�ؽ�Ʈ�� �߰��� ����'�� ������Ų��.
	//		++m_addCount;
	//	}
	//}

	//// FPS�� �޾ƿͼ�
	//float FPS = CGameManager::GetInst()->GetFPS();

	//// ���ڿ� ������ �ϰ� Text�� ����ش�.
	//char	Text[256] = {};
	//sprintf_s(Text, "FPS : %.5f", FPS);

	//// Text�� �����ڵ� ���ڿ��� ��ȯ�Ͽ�
	//TCHAR	Unicode[256] = {};
	//int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	//MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);

	//// ��ȯ�� ���ڿ��� ���������� ������ ����Ѵ�.
	//m_FPSText->SetText(Unicode);
}

void CStartWindow::StartButtonCallback()
{
	// �� ���� ���� ���ε� Ű�� �ݹ� �Լ��� �����.
	CInput::GetInst()->ClearCallback();

	// ���� ���� �����Ѵ�.
	// CSceneManager::GetInst()->CreateScene<CMainScene>();

	// ��1�� �����Ѵ�.
	 CSceneManager::GetInst()->CreateScene<CScene1>();

	// CSceneManager::GetInst()->CreateScene<CScene3>();

	// CSceneManager::GetInst()->CreateScene<CSceneFinal>();
}

void CStartWindow::EndButtonCallback()
{
	// ������ â�� �ݾ� ���α׷��� �����Ѵ�.
	CGameManager::GetInst()->Exit();
}

CStartWindow::CStartWindow()
{
}

CStartWindow::~CStartWindow()
{
}
