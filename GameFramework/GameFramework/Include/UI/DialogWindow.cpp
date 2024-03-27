#include "DialogWindow.h"
#include "Button.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../GameManager.h"
#include "../Scene/MainScene.h"
#include "../Scene/SceneManager.h"
#include "../Input.h"
#include "ProgressBar.h"
#include "ImageWidget.h"
#include "Text.h"

bool CDialogWindow::Init()
{
	if (!CWidgetWindow::Init())
		return false;

	/*m_scene->GetSceneResource()->LoadSound("UI", "ButtonHovered", false,
		"1Up.wav");
	m_scene->GetSceneResource()->LoadSound("UI", "ButtonClick", false,
		"Stun.wav");*/

    // 위젯 윈도우 설정
	SetSize(520.f, 202.f);
	SetPos(150.f, 200.f);

	// 메인박스
	m_mainBox = CreateWidget<CImageWidget>("MainBox");
	m_mainBox->SetTexture("MainBox", TEXT("Maple/Npc/Muyeong/dialog1.bmp"));
	m_mainBox->SetColorKey(255, 0, 255);
	m_mainBox->SetSize(520.f, 202.f);


	// 버튼 객체를 생성한다.
	CButton* startButton = CreateWidget<CButton>("StartButton");

	// 버튼 텍스쳐를 설정한다.
	startButton->SetTexture("StartButton", TEXT("Maple/Npc/ExitButton.bmp"));

	//// 버튼 상태에 따른 텍스쳐의 프레임 좌표를 넣는다.
	//startButton->SetButtonStateData(EButtonState::Normal, Vector2(0.f, 0.f), Vector2(200.f, 100.f));
	//startButton->SetButtonStateData(EButtonState::MouseHovered, Vector2(0.f, 0.f), Vector2(200.f, 100.f));
	//startButton->SetButtonStateData(EButtonState::Click, Vector2(200.f, 0.f), Vector2(400.f, 100.f));
	//startButton->SetButtonStateData(EButtonState::Disable, Vector2(600.f, 0.f), Vector2(800.f, 100.f));

	// 버튼 상태에 따라 재생할 사운드를 찾아 넣는다.
	startButton->SetSound(EButtonSoundState::MouseHovered, "Hovered");
	startButton->SetSound(EButtonSoundState::Click, "Click");

	// 버튼의 위치를 조절한다.
	startButton->SetPos(150.f, 200.f);
	startButton->SetZOrder(1);
	startButton->SetColorKeyAll(255, 0, 255);

	// 스타트 버튼에 대한 콜백함수 등록
	startButton->SetCallback<CDialogWindow>(EButtonSoundState::Click,
		this, &CDialogWindow::StartButtonCallback);
	

	return true;
}

void CDialogWindow::Update(float _deltaTime)
{
	CWidgetWindow::Update(_deltaTime);

	
}



void CDialogWindow::StartButtonCallback()
{
	SetActive(false);
}

CDialogWindow::CDialogWindow()
{
}

CDialogWindow::~CDialogWindow()
{
}
