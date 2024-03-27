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

	// 버튼에 커서가 올라갔을 때 재생할 사운드를 로드한다.
	// 사운드의 채널 그룹은 UI, 이름은 ButtonHovered, 루프는 false로 한다.
	m_scene->GetSceneResource()->LoadSound("UI", "ButtonHovered", false,
		"Maple/BtMouseOver.mp3");
	// 버튼을 클릭했을 때 재생할 사운드를 로드한다.
	m_scene->GetSceneResource()->LoadSound("UI", "ButtonClick", false,
		"Maple/ScrollUp.mp3");

	m_scene->GetSceneResource()->SetVolume("UI", 100.f);

	m_scene->GetSceneResource()->SoundPlay("StartSceneBGM");

	// 스타트 위젯 윈도우의 크기. 스타트 씬과 같은 크기로 할 것이다.
	SetSize(1280.f, 720.f);

	// 배경 위젯을 생성한다.
	CImageWidget* back = CreateWidget<CImageWidget>("Back");

	back->SetTexture("StartBack", TEXT("Maple/Start/start.bmp"));

	back->SetSize(800.f, 600.f);

	
	// 버튼 객체를 생성한다.
	CButton* startButton = CreateWidget<CButton>("StartButton");

	// 버튼 텍스쳐를 설정한다.
	startButton->SetTexture("StartButton", TEXT("Maple/Start/startButton.bmp"));

	// 버튼 상태에 따른 텍스쳐의 프레임 좌표를 넣는다.
	startButton->SetButtonStateData(EButtonState::Normal, Vector2(0.f, 0.f), Vector2(200.f, 100.f));
	startButton->SetButtonStateData(EButtonState::MouseHovered, Vector2(0.f, 0.f), Vector2(200.f, 100.f));
	startButton->SetButtonStateData(EButtonState::Click, Vector2(200.f, 0.f), Vector2(400.f, 100.f));
	startButton->SetButtonStateData(EButtonState::Disable, Vector2(600.f, 0.f), Vector2(800.f, 100.f));
	
	// 버튼 상태에 따라 재생할 사운드를 찾아 넣는다.
	startButton->SetSound(EButtonSoundState::MouseHovered, "Hovered");
	startButton->SetSound(EButtonSoundState::Click, "Click");
	
	// 버튼의 위치를 조절한다.
	startButton->SetPos(300.f, 330.f);
	startButton->SetZOrder(1);
	startButton->SetColorKeyAll(255, 0, 255);

	// 스타트 버튼에 대한 콜백함수 등록
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

	// 엔드 버튼에 대한 콜백함수 등록
	endButton->SetCallback<CStartWindow>(EButtonSoundState::Click,
		this, &CStartWindow::EndButtonCallback);


	//// 텍스트 위젯 추가
	//m_text = CreateWidget<CText>("Text");

	//// 텍스트 위젯에 텍스트 출력
	//m_text->SetText(TEXT("텍스트 출력!!"));

	//// 설정
	//m_text->SetPos(200.f, 50.f);
	//m_text->SetTextColor(255, 0, 0);
	//m_text->EnableShadow(true);
	//m_text->SetShadowOffset(5.f, 5.f);

	//// 매초마다 텍스트 추가
	//m_textTime = 0.f;
	//memset(m_addText, 0, sizeof(TCHAR) * 32);
	//lstrcpy(m_addText, TEXT("흑염룡"));
	//m_addCount = 0;

	
	// 아래는 시간 출력을 위한 코드이다.

	//// 숫자 위젯과 이미지 위젯(콜론)을 추가한다.
	//m_hour = CreateWidget<CNumber>("Hour");
	//CImageWidget* Colon = CreateWidget<CImageWidget>("Colon");
	//m_minute = CreateWidget<CNumber>("Minute");
	//m_second = CreateWidget<CNumber>("Second");

	//Colon->SetTexture("Colon", TEXT("Number/Colon.bmp"));
	//Colon->SetSize(29.f, 48.f);
	//Colon->SetPos(558.f, 100.f);
	//Colon->SetColorKey(255, 255, 255);


	//// 프레임 이미지를 받아오기 위한 벡터
	//std::vector<std::wstring>	vecFileName;

	//for (int i = 0; i <= 9; ++i)
	//{
	//	TCHAR	FileName[MAX_PATH] = {};
	//	// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
	//	wsprintf(FileName, TEXT("Number/%d.bmp"), i);
	//	vecFileName.push_back(FileName);
	//}

	//m_hour->SetTexture("Number", vecFileName);
	//m_minute->SetTexture("Number", vecFileName);
	//m_second->SetTexture("Number", vecFileName);

	//// 위치, 크기, 컬러키 설정
	//m_hour->SetColorKey(255, 255, 255);
	//m_minute->SetColorKey(255, 255, 255);
	//m_second->SetColorKey(255, 255, 255);

	//m_hour->SetSize(29.f, 48.f);
	//m_hour->SetPos(500.f, 100.f);

	//m_minute->SetSize(29.f, 48.f);
	//m_minute->SetPos(587.f, 100.f);

	//m_second->SetSize(29.f, 48.f);
	//m_second->SetPos(655.f, 100.f);

	//// FPS 출력 위젯 생성
	//m_FPSText = CreateWidget<CText>("Text");

	//// 위치, 크기, 색상 등 설정
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
		GetLocalTime으로 시스템 시간을 받아와
		Time 변수에 저장한다.
	*/
	//SYSTEMTIME Time;
	//GetLocalTime(&Time);

	//// 받아온 시간으로 숫자를 초기화한다.
	//m_hour->SetNumber(Time.wHour);
	//m_minute->SetNumber(Time.wMinute);
	//m_second->SetNumber(Time.wSecond);

	// 아래는 한글자씩 나오게 하는 코드 
	// '텍스트가 추가된 개수'가 '추가할 텍스트 문자열 길이'보다 작다면 
	//if (m_addCount < lstrlen(m_addText))
	//{
	//	// 텍스트가 추가되는 시간값 증가시키고
	//	m_textTime += _deltaTime;

	//	// 그게 1초가 되면
	//	if (m_textTime >= 1.f)
	//	{
	//		// 0초로 초기화시킨뒤
	//		m_textTime -= 1.f;

	//		// 1글자를 추가한다.
	//		m_text->AddText(m_addText[m_addCount]);

	//		// '텍스트가 추가된 개수'를 증가시킨다.
	//		++m_addCount;
	//	}
	//}

	//// FPS를 받아와서
	//float FPS = CGameManager::GetInst()->GetFPS();

	//// 문자열 구성을 하고 Text에 담아준다.
	//char	Text[256] = {};
	//sprintf_s(Text, "FPS : %.5f", FPS);

	//// Text를 유니코드 문자열로 변환하여
	//TCHAR	Unicode[256] = {};
	//int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	//MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);

	//// 변환된 문자열을 최종적으로 위젯에 등록한다.
	//m_FPSText->SetText(Unicode);
}

void CStartWindow::StartButtonCallback()
{
	// 그 전에 현재 바인드 키에 콜백 함수를 지운다.
	CInput::GetInst()->ClearCallback();

	// 메인 씬을 생성한다.
	// CSceneManager::GetInst()->CreateScene<CMainScene>();

	// 씬1을 생성한다.
	 CSceneManager::GetInst()->CreateScene<CScene1>();

	// CSceneManager::GetInst()->CreateScene<CScene3>();

	// CSceneManager::GetInst()->CreateScene<CSceneFinal>();
}

void CStartWindow::EndButtonCallback()
{
	// 윈도우 창을 닫아 프로그램을 종료한다.
	CGameManager::GetInst()->Exit();
}

CStartWindow::CStartWindow()
{
}

CStartWindow::~CStartWindow()
{
}
