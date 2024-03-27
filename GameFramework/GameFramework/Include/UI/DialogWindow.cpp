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

    // ���� ������ ����
	SetSize(520.f, 202.f);
	SetPos(150.f, 200.f);

	// ���ιڽ�
	m_mainBox = CreateWidget<CImageWidget>("MainBox");
	m_mainBox->SetTexture("MainBox", TEXT("Maple/Npc/Muyeong/dialog1.bmp"));
	m_mainBox->SetColorKey(255, 0, 255);
	m_mainBox->SetSize(520.f, 202.f);


	// ��ư ��ü�� �����Ѵ�.
	CButton* startButton = CreateWidget<CButton>("StartButton");

	// ��ư �ؽ��ĸ� �����Ѵ�.
	startButton->SetTexture("StartButton", TEXT("Maple/Npc/ExitButton.bmp"));

	//// ��ư ���¿� ���� �ؽ����� ������ ��ǥ�� �ִ´�.
	//startButton->SetButtonStateData(EButtonState::Normal, Vector2(0.f, 0.f), Vector2(200.f, 100.f));
	//startButton->SetButtonStateData(EButtonState::MouseHovered, Vector2(0.f, 0.f), Vector2(200.f, 100.f));
	//startButton->SetButtonStateData(EButtonState::Click, Vector2(200.f, 0.f), Vector2(400.f, 100.f));
	//startButton->SetButtonStateData(EButtonState::Disable, Vector2(600.f, 0.f), Vector2(800.f, 100.f));

	// ��ư ���¿� ���� ����� ���带 ã�� �ִ´�.
	startButton->SetSound(EButtonSoundState::MouseHovered, "Hovered");
	startButton->SetSound(EButtonSoundState::Click, "Click");

	// ��ư�� ��ġ�� �����Ѵ�.
	startButton->SetPos(150.f, 200.f);
	startButton->SetZOrder(1);
	startButton->SetColorKeyAll(255, 0, 255);

	// ��ŸƮ ��ư�� ���� �ݹ��Լ� ���
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
