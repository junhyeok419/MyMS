#include "CharacterHUD.h"
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

bool CCharacterHUD::Init()
{
	if (!CWidgetWindow::Init())
		return false;

	/*m_scene->GetSceneResource()->LoadSound("UI", "ButtonHovered", false,
		"1Up.wav");
	m_scene->GetSceneResource()->LoadSound("UI", "ButtonClick", false,
		"Stun.wav");*/

	// 위젯 윈도우 설정
	SetSize(210.f, 110.f);
	SetPos(50.f, 50.f);

	// 바 프레임 설정
	m_HPBarFrame = CreateWidget<CImageWidget>("HPBarFrame");
	m_HPBarFrame->SetTexture("BarFrame", TEXT("BarBack.bmp"));
	m_HPBarFrame->SetColorKey(255, 0, 255);
	m_HPBarFrame->SetSize(220.f, 50.f);

	// 바 설정
	m_HPBar = CreateWidget<CProgressBar>("HPBar");
	m_HPBar->SetTexture(EProgressBar_Texture_Type::Bar, "HPBar", TEXT("BarDefault.bmp"));
	m_HPBar->SetSize(200.f, 30.f);
	m_HPBar->SetPos(10.f, 10.f);
	m_HPBar->SetBarDir(EProgressBar_Dir::LeftToRight);

	// FPS 출력 위젯 생성
	m_FPSText = CreateWidget<CText>("Text");

	// 위치, 크기, 색상 등 설정
	m_FPSText->SetText(TEXT("FPS"));
	m_FPSText->SetPos(900.f, 50.f);
	m_FPSText->SetTextColor(255, 0, 0);
	m_FPSText->EnableShadow(true);
	m_FPSText->SetShadowOffset(2.f, 2.f);

	return true;
}

void CCharacterHUD::Update(float _deltaTime)
{
	CWidgetWindow::Update(_deltaTime);

	// FPS를 받아와서
	float FPS = CGameManager::GetInst()->GetFPS();

	// 문자열 구성을 하고 Text에 담아준다.
	char	Text[256] = {};
	sprintf_s(Text, "FPS : %.5f", FPS);

	// Text를 유니코드 문자열로 변환하여
	TCHAR	Unicode[256] = {};
	int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);

	// 변환된 문자열을 최종적으로 위젯에 등록한다.
	m_FPSText->SetText(Unicode);
}

void CCharacterHUD::SetHP(float _HP)
{
	m_HPBar->SetValue(_HP);
}

CCharacterHUD::CCharacterHUD()
{
}

CCharacterHUD::~CCharacterHUD()
{
}
