#include "MainHUD.h"
#include "Button.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../GameManager.h"
#include "../Scene/MainScene.h"
#include "../Scene/SceneManager.h"
#include "../GameObject/Player.h"
#include "../Input.h"
#include "ProgressBar.h"
#include "ImageWidget.h"
#include "Text.h"
#include "Number.h"
bool CMainHUD::Init()
{
	if (!CWidgetWindow::Init())
		return false;

	/*m_scene->GetSceneResource()->LoadSound("UI", "ButtonHovered", false,
		"1Up.wav");
	m_scene->GetSceneResource()->LoadSound("UI", "ButtonClick", false,
		"Stun.wav");*/

	// 위젯 윈도우 설정
	SetSize(800.f, 600.f);
	SetPos(0.f, 0.f);

	// 메인프레임
	m_mainFrame = CreateWidget<CImageWidget>("MainFrame");
	m_mainFrame->SetTexture("MainFrame", TEXT("Maple/UI/StatusBar/Base/BaseUI.bmp"));
	m_mainFrame->SetColorKey(255, 0, 255);
	m_mainFrame->SetSize(800.f, 600.f);

	// hp바
	m_HPBar = CreateWidget<CProgressBar>("HPBar");
	m_HPBar->SetTexture(EProgressBar_Texture_Type::Bar, "HPBar", TEXT("Maple/UI/StatusBar/Gauge/HPBar.bmp"));
	m_HPBar->SetColorKey(EProgressBar_Texture_Type::Bar, 255, 0, 255);
	m_HPBar->SetSize(108, 17);
	m_HPBar->SetPos(220.f, 582.f);
	m_HPBar->SetBarDir(EProgressBar_Dir::LeftToRight);

	// mp바 
	m_MPBar = CreateWidget<CProgressBar>("MPBar");
	m_MPBar->SetTexture(EProgressBar_Texture_Type::Bar, "MPBar", TEXT("Maple/UI/StatusBar/Gauge/MPBar.bmp"));
	m_MPBar->SetColorKey(EProgressBar_Texture_Type::Bar, 255, 0, 255);
	m_MPBar->SetSize(108, 17);
	m_MPBar->SetPos(328.f, 582.f);
	m_MPBar->SetBarDir(EProgressBar_Dir::LeftToRight);

	// exp바
	m_EXPBar = CreateWidget<CProgressBar>("EXPBar");
	m_EXPBar->SetTexture(EProgressBar_Texture_Type::Bar, "EXPBar", TEXT("Maple/UI/StatusBar/Gauge/EXPBar.bmp"));
	m_EXPBar->SetColorKey(EProgressBar_Texture_Type::Bar, 255, 0, 255);
	m_EXPBar->SetSize(117, 17);
	m_EXPBar->SetPos(441.f, 582.f);
	m_EXPBar->SetBarDir(EProgressBar_Dir::LeftToRight);
	m_EXPBar->SetValue(0.f);

	// FPS 출력 위젯 생성
	m_FPSText = CreateWidget<CText>("Text");
	// 위치, 크기, 색상 등 설정
	m_FPSText->SetText(TEXT("FPS"));
	m_FPSText->SetPos(600.f, 30.f);
	m_FPSText->SetTextColor(255, 0, 0);
	m_FPSText->EnableShadow(true);
	m_FPSText->SetShadowOffset(2.f, 2.f);


	// hp, mp, exp, level 숫자 위젯 추가
	m_HPNumber = CreateWidget<CNumber>("HP");
	m_HPMaxNumber = CreateWidget<CNumber>("HPMax");
	m_MPNumber = CreateWidget<CNumber>("MP");
	m_MPMaxNumber = CreateWidget<CNumber>("MPMax");
	m_EXPNumber = CreateWidget<CNumber>("EXP");
	m_EXPRatioNumber = CreateWidget<CNumber>("EXPRatio");
	CImageWidget* slash1 = CreateWidget<CImageWidget>("Slash1");
	CImageWidget* slash2 = CreateWidget<CImageWidget>("Slash2");
	CImageWidget* LBracket1 = CreateWidget<CImageWidget>("LBracket1");
	CImageWidget* LBracket2 = CreateWidget<CImageWidget>("LBracket2");
	CImageWidget* LBracket3 = CreateWidget<CImageWidget>("LBracket3");
	CImageWidget* RBracket1 = CreateWidget<CImageWidget>("RBracket1");
	CImageWidget* RBracket2 = CreateWidget<CImageWidget>("RBracket2");
	CImageWidget* RBracket3 = CreateWidget<CImageWidget>("RBracket3");
	CImageWidget* percent = CreateWidget<CImageWidget>("Percent");

	LBracket1->SetTexture("LBracket", TEXT("Maple/UI/StatusBar/Number/number.Lbracket.bmp"));
	LBracket1->SetSize(2.f, 9.f);
	LBracket1->SetPos(241.f, 570.f);
	LBracket1->SetColorKey(255, 0, 255);

	slash1->SetTexture("Slash", TEXT("Maple/UI/StatusBar/Number/number.slash.bmp"));
	slash1->SetSize(7.f, 7.f);
	slash1->SetPos(275.f, 571.f);
	slash1->SetColorKey(255, 0, 255);

	RBracket1->SetTexture("RBracket", TEXT("Maple/UI/StatusBar/Number/number.Rbracket.bmp"));
	RBracket1->SetSize(2.f, 9.f);
	RBracket1->SetPos(315.f, 570.f);
	RBracket1->SetColorKey(255, 0, 255);


	LBracket2->SetTexture("LBracket", TEXT("Maple/UI/StatusBar/Number/number.Lbracket.bmp"));
	LBracket2->SetSize(2.f, 9.f);
	LBracket2->SetPos(351.f, 570.f);
	LBracket2->SetColorKey(255, 0, 255);

	slash2->SetTexture("Slash", TEXT("Maple/UI/StatusBar/Number/number.slash.bmp"));
	slash2->SetSize(7.f, 7.f);
	slash2->SetPos(385.f, 571.f);
	slash2->SetColorKey(255, 0, 255);

	RBracket2->SetTexture("RBracket", TEXT("Maple/UI/StatusBar/Number/number.Rbracket.bmp"));
	RBracket2->SetSize(2.f, 9.f);
	RBracket2->SetPos(425.f, 570.f);
	RBracket2->SetColorKey(255, 0, 255);


	LBracket3->SetTexture("LBracket", TEXT("Maple/UI/StatusBar/Number/number.Lbracket.bmp"));
	LBracket3->SetSize(2.f, 9.f);
	LBracket3->SetPos(524.f, 570.f);
	LBracket3->SetColorKey(255, 0, 255);

	percent->SetTexture("Percent", TEXT("Maple/UI/StatusBar/Number/number.percent.bmp"));
	percent->SetSize(7.f, 7.f);
	percent->SetPos(541.f, 571.f);
	percent->SetColorKey(255, 0, 255);

	RBracket3->SetTexture("RBracket", TEXT("Maple/UI/StatusBar/Number/number.Rbracket.bmp"));
	RBracket3->SetSize(2.f, 9.f);
	RBracket3->SetPos(550.f, 570.f);
	RBracket3->SetColorKey(255, 0, 255);


	// 프레임 이미지인 숫자를 받아오기 위한 벡터
	std::vector<std::wstring>	vecFileName;

	for (int i = 0; i <= 9; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
		wsprintf(FileName, TEXT("Maple/UI/StatusBar/Number/number.%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	m_HPNumber->SetTexture("HP", vecFileName);
	m_HPMaxNumber->SetTexture("HPMax", vecFileName);
	m_MPNumber->SetTexture("MP", vecFileName);
	m_MPMaxNumber->SetTexture("MPMax", vecFileName);
	m_EXPNumber->SetTexture("EXP", vecFileName);
	m_EXPRatioNumber->SetTexture("EXPRatio", vecFileName);

	// 위치, 크기, 컬러키 설정
	m_HPNumber->SetColorKey(255, 0, 255);
	m_HPMaxNumber->SetColorKey(255, 0, 255);
	m_MPNumber-> SetColorKey(255, 0, 255);
	m_MPMaxNumber->SetColorKey(255, 0, 255);
	m_EXPNumber->SetColorKey(255, 0, 255);
	m_EXPRatioNumber->SetColorKey(255, 0, 255);

	m_HPNumber->SetSize(5.f, 7.f);
	m_HPNumber->SetPos(244.f, 571.f);
	m_HPMaxNumber->SetSize(5.f, 7.f);
	m_HPMaxNumber->SetPos(284.f, 571.f);

	m_MPNumber->SetSize(5.f, 7.f);
	m_MPNumber->SetPos(354.f, 571.f);
	m_MPMaxNumber->SetSize(5.f, 7.f);
	m_MPMaxNumber->SetPos(393.f, 571.f);

	m_EXPNumber->SetSize(5.f, 7.f);
	m_EXPNumber->SetPos(469.f, 571.f);
	m_EXPRatioNumber->SetSize(5.f, 7.f);
	m_EXPRatioNumber->SetPos(530.f, 571.f);
	

	vecFileName.clear();
	for (int i = 0; i <= 9; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
		wsprintf(FileName, TEXT("Maple/UI/StatusBar/Level/LevelNo.%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	m_levelNumber = CreateWidget<CNumber>("Level");

	m_levelNumber->SetTexture("Level", vecFileName);
	m_levelNumber->SetColorKey(255, 0, 255);
	m_levelNumber->SetSize(12.f, 13.f);
	m_levelNumber->SetPos(44.f, 576.f);


	// 퀵슬롯 스킬1 아이콘	
	m_skill1 = CreateWidget<CImageWidget>("SkillQuick1");
	m_skill1->SetTexture("SkillQuick1_Disabled", TEXT("Maple/UI/StatusBar/QuickSlot/PowerStrike_Disabled.bmp"));
	m_skill1->SetColorKey(255, 0, 255);
	m_skill1->SetSize(32.f, 32.f);
	m_skill1->SetPos(657.f, 527.f);

	m_skill2 = CreateWidget<CImageWidget>("SkillQuick2");
	m_skill2->SetTexture("SkillQuick2_Disabled", TEXT("Maple/UI/StatusBar/QuickSlot/SlashBlast_Disabled.bmp"));
	m_skill2->SetColorKey(255, 0, 255);
	m_skill2->SetSize(32.f, 32.f);
	m_skill2->SetPos(693.f, 527.f);

	m_skill3 = CreateWidget<CImageWidget>("SkillQuick3");
	m_skill3->SetTexture("SkillQuick3_Disabled", TEXT("Maple/UI/StatusBar/QuickSlot/Judgement_Disabled.bmp"));
	m_skill3->SetColorKey(255, 0, 255);
	m_skill3->SetSize(32.f, 32.f);
	m_skill3->SetPos(728.f, 527.f);

	m_skill4 = CreateWidget<CImageWidget>("SkillQuick4");
	m_skill4->SetTexture("SkillQuick4_Disabled", TEXT("Maple/UI/StatusBar/QuickSlot/Justice_Disabled.bmp"));
	m_skill4->SetColorKey(255, 0, 255);
	m_skill4->SetSize(32.f, 32.f);
	m_skill4->SetPos(763.f, 527.f);


	// 퀵슬롯 아이템 개수
	vecFileName.clear();

	for (int i = 0; i <= 9; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
		wsprintf(FileName, TEXT("Maple/UI/StatusBar/QuickSlot/ItemNo/ItemNo.%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	m_HPPotionCnt = CreateWidget<CNumber>("HPPotionCnt");
	m_MPPotionCnt = CreateWidget<CNumber>("MPPotionCnt");
	m_itemCnt = CreateWidget<CNumber>("ItemCnt");

	m_HPPotionCnt->SetTexture("HPPotionCnt", vecFileName);
	m_MPPotionCnt->SetTexture("MPPotionCnt", vecFileName);
	m_itemCnt->SetTexture("ItemCnt", vecFileName);

	// 위치, 크기, 컬러키 설정
	m_HPPotionCnt->SetColorKey(255, 0, 255);
	m_MPPotionCnt->SetColorKey(255, 0, 255);
	m_itemCnt->SetColorKey(255, 0, 255);

	m_HPPotionCnt->SetSize(8.f, 11.f);
	m_MPPotionCnt->SetSize(8.f, 11.f);
	m_itemCnt->SetSize(8.f, 11.f);

	m_HPPotionCnt->SetPos(694.f, 580.f);
	m_MPPotionCnt->SetPos(729.f, 580.f);
	m_itemCnt->SetPos(764.f, 580.f);


	return true;
}

void CMainHUD::Update(float _deltaTime)
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


	// hp, mp, exp 설정
	m_HPNumber->SetNumber(m_scene->GetPlayer()->GetHP());
	m_HPMaxNumber->SetNumber(m_scene->GetPlayer()->GetHPMax());
	m_MPNumber->SetNumber(m_scene->GetPlayer()->GetMP());
	m_MPMaxNumber->SetNumber(m_scene->GetPlayer()->GetMPMax());
	m_EXPNumber->SetNumber(m_scene->GetPlayer()->GetEXP());
	m_EXPRatioNumber->SetNumber((m_scene->GetPlayer()->GetEXP() / m_scene->GetPlayer()->GetEXPMax())*100);

	// 퀵슬롯 아이템 개수 설정
	m_HPPotionCnt->SetNumber(m_scene->GetPlayer()->GetHPPotionCnt());
	m_MPPotionCnt->SetNumber(m_scene->GetPlayer()->GetMPPotionCnt());
	m_itemCnt->SetNumber(m_scene->GetPlayer()->GetItemCnt());


	// 레벨 설정
	m_levelNumber->SetNumber(m_scene->GetPlayer()->GetLevel());

	// hp바 조절
	if (m_HPbarAdjust)
	{
		m_HPadjustTime += _deltaTime;

		if (m_HPadjustTime >= 0.8f)
		{
			m_HPbarAdjust = false;
			m_HPadjustTime = 0.f;
			
		}
		else
		{
			// 체력 ui 조정
			m_HPBar->SetValue(m_prevHP - (m_prevHP-m_HP)* (m_HPadjustTime * 1.25f));

		}
	}

	// MP바 조절
	if (m_MPbarAdjust)
	{
		m_MPadjustTime += _deltaTime;

		if (m_MPadjustTime >= 0.8f)
		{
			m_MPbarAdjust = false;
			m_MPadjustTime = 0.f;
		}
		else
		{
			// 마나 ui 조정
			m_MPBar->SetValue(m_prevMP - (m_prevMP - m_MP) * (m_MPadjustTime * 1.25f));

		}
	}

	//// EXP바 조절
	//if (m_EXPbarAdjust)
	//{
	//	m_EXPadjustTime += _deltaTime;

	//	if (m_EXPadjustTime >= 0.8f)
	//	{
	//		m_EXPbarAdjust = false;
	//		m_EXPadjustTime = 0.f;

	//	}
	//	else
	//	{
	//		// 경험치 ui 조정
	//		m_EXPBar->SetValue((m_prevEXP - (m_prevEXP - m_EXP) * m_EXPadjustTime));

	//	}
	//}

	// EXP바 조절
	if (m_EXPbarAdjust)
	{
		m_EXPadjustTime += _deltaTime;

		if (m_EXPadjustTime >= 0.8f)
		{
			m_EXPbarAdjust = false;
			m_EXPadjustTime = 0.f;

		}
		else
		{
			// 경험치 ui 조정
			m_EXPBar->SetValue((m_prevEXP - (m_prevEXP - m_EXP) * (m_EXPadjustTime*1.25f)));

		}
	}

	// 퀵슬럿 스킬아이콘
	switch (m_scene->GetPlayer()->GetPowerStrikeState())
	{
	case ESkillState::Disabled:
		m_skill1->SetTexture("SkillQuick1_Disabled", TEXT("Maple/UI/StatusBar/QuickSlot/PowerStrike_Disabled.bmp"));
		break;
	case ESkillState::Normal:
		m_skill1->SetTexture("SkillQuick1_Normal", TEXT("Maple/UI/StatusBar/QuickSlot/PowerStrike_Normal.bmp"));
		break;
	case ESkillState::Used:
		m_skill1->SetTexture("SkillQuick1_Used", TEXT("Maple/UI/StatusBar/QuickSlot/PowerStrike_Used.bmp"));
		break;
	}
	m_skill1->SetColorKey(255, 0, 255);
	m_skill1->SetSize(32.f, 32.f);
	m_skill1->SetPos(657.f, 527.f);


	switch (m_scene->GetPlayer()->GetSlashBlastState())
	{
	case ESkillState::Disabled:
		m_skill2->SetTexture("SkillQuick2_Disabled", TEXT("Maple/UI/StatusBar/QuickSlot/SlashBlast_Disabled.bmp"));
		break;
	case ESkillState::Normal:
		m_skill2->SetTexture("SkillQuick2_Normal", TEXT("Maple/UI/StatusBar/QuickSlot/SlashBlast_Normal.bmp"));
		break;
	case ESkillState::Used:
		m_skill2->SetTexture("SkillQuick2_Used", TEXT("Maple/UI/StatusBar/QuickSlot/SlashBlast_Used.bmp"));
		break;
	}

	m_skill2->SetColorKey(255, 0, 255);
	m_skill2->SetSize(32.f, 32.f);
	m_skill2->SetPos(693.f, 527.f);

	switch (m_scene->GetPlayer()->GetJudgementState())
	{
	case ESkillState::Disabled:
		m_skill3->SetTexture("SkillQuick3_Disabled", TEXT("Maple/UI/StatusBar/QuickSlot/Judgement_Disabled.bmp"));
		break;
	case ESkillState::Normal:
		m_skill3->SetTexture("SkillQuick3_Normal", TEXT("Maple/UI/StatusBar/QuickSlot/Judgement_Normal.bmp"));
		break;
	case ESkillState::Used:
		m_skill3->SetTexture("SkillQuick3_Used", TEXT("Maple/UI/StatusBar/QuickSlot/Judgement_Used.bmp"));
		break;
	}

	m_skill3->SetColorKey(255, 0, 255);
	m_skill3->SetSize(32.f, 32.f);
	m_skill3->SetPos(728.f, 527.f);

	switch (m_scene->GetPlayer()->GetJusticeState())
	{
	case ESkillState::Disabled:
		m_skill4->SetTexture("SkillQuick4_Disabled", TEXT("Maple/UI/StatusBar/QuickSlot/Justice_Disabled.bmp"));
		break;
	case ESkillState::Normal:
		m_skill4->SetTexture("SkillQuick4_Normal", TEXT("Maple/UI/StatusBar/QuickSlot/Justice_Normal.bmp"));
		break;
	case ESkillState::Used:
		m_skill4->SetTexture("SkillQuick4_Used", TEXT("Maple/UI/StatusBar/QuickSlot/Justice_Used.bmp"));
		break;
	}

	m_skill4->SetColorKey(255, 0, 255);
	m_skill4->SetSize(32.f, 32.f);
	m_skill4->SetPos(763.f, 527.f);
}

void CMainHUD::SetHP(float _HP, float _prev)
{
	m_HP = _HP;
	m_prevHP = _prev;

	m_HPbarAdjust = true;
}

void CMainHUD::SetHP2(float _HP)
{
	m_HPBar->SetValue(_HP);
}

void CMainHUD::SetMP(float _MP, float _prev)
{
	m_MP = _MP;
	m_prevMP = _prev;

	m_MPbarAdjust = true;
}

void CMainHUD::SetMP2(float _MP)
{
	m_MPBar->SetValue(_MP);
}

void CMainHUD::SetEXP2(float _EXP)
{
	m_EXPBar->SetValue(_EXP);
}

void CMainHUD::SetEXP(float _EXP, float _prev)
{
	m_EXP = _EXP;
	m_prevEXP = _prev;

	m_EXPbarAdjust = true;
}



CMainHUD::CMainHUD()
{

}

CMainHUD::~CMainHUD()
{
}
