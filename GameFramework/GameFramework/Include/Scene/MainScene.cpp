#include "MainScene.h"
#include "../GameObject/Player.h"
#include "../GameObject/Monster.h"
#include "../GameObject/Scene4Back2.h"
#include "../GameObject/Scene4Back1.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../Input.h"
#include "../UI/MainHUD.h"
#include "../UI/CharacterHUD.h"
#include "../GameObject/Ballog.h"
#include "../GameObject/TauroMasis.h"
#include "../GameObject/TauroSpear.h"
#include "../GameObject/WildCargo.h"
#include "../GameObject/Ground.h"
#include "../GameObject/Wall.h"
#include "../GameObject/Ladder.h"
#include "../GameObject/Portal.h"
#include "../Scene/SceneManager.h"
#include "../Scene/SceneCollision.h"
bool CMainScene::Init()
{
	// 필요한 애니메이션 시퀀스를 생성하고 추가한다.
	CreateAnimationSequence_Effect();
	CreateAnimationSequence();
	CreateAnimationSequence1();
	CreateAnimationSequence2();
	CreateAnimationSequence3();
	CreateAnimationSequence4();
	CreateAnimationSequence5();
	CreateAnimationSequence6();

	// 채널 그룹을 BGM으로 하는 사운드 이름 MainBGM을 루프로 로드한다. 파일 명은 MainBgm.mp3 이다.
	// GetSceneResource()->LoadSound("BGM", "MainBGM", true, "MainBgm.mp3");
	// GetSceneResource()->LoadSound("Effect", "TeemoSmile", false, "TeemoSmile.mp3");
	// GetSceneResource()->LoadSound("Effect", "Gabung", false, "Demasia.mp3");
	GetSceneResource()->LoadSound("BGM", "Scene2BGM", true, "Maple/Back/CaveOfHontale.mp3");

	GetSceneResource()->LoadSound("Effect", "Use", false, "Maple/Player/Use.mp3");
	GetSceneResource()->LoadSound("Effect", "Gain", false, "Maple/Player/Item/PickUpItem.mp3");
	GetSceneResource()->LoadSound("Effect", "Portal", false, "Maple/Portal/Portal.mp3");
	GetSceneResource()->LoadSound("Effect", "LevelUp", false, "Maple/Player/LevelUp/LevelUp.mp3");

	GetSceneResource()->LoadSound("Effect", "AttackVoice1", false, "Maple/Player/Skill/Base/Voice1.mp3");
	GetSceneResource()->LoadSound("Effect", "AttackVoice2", false, "Maple/Player/Skill/Base/Voice2.mp3");
	GetSceneResource()->LoadSound("Effect", "AttackVoice3", false, "Maple/Player/Skill/Base/Voice3.mp3");
	GetSceneResource()->LoadSound("Effect", "AttackVoice4", false, "Maple/Player/Skill/Base/Voice4.mp3");

	GetSceneResource()->LoadSound("Effect", "JudgementVoice1", false, "Maple/Player/Skill/Judgement/Voice1.mp3");
	GetSceneResource()->LoadSound("Effect", "JudgementVoice2", false, "Maple/Player/Skill/Judgement/Voice2.mp3");
	GetSceneResource()->LoadSound("Effect", "JudgementVoice3", false, "Maple/Player/Skill/Judgement/Voice3.mp3");
	GetSceneResource()->LoadSound("Effect", "JudgementVoice4", false, "Maple/Player/Skill/Judgement/Voice4.mp3");

	GetSceneResource()->LoadSound("Effect", "Jump", false, "Maple/Player/Jump/Jump.mp3");
	GetSceneResource()->LoadSound("Effect", "Attack", false, "Maple/Player/Attack/Attack.mp3");
	GetSceneResource()->LoadSound("Effect", "PowerStrikeUse", false, "Maple/Player/Skill/PowerStrike/Use.mp3");
	GetSceneResource()->LoadSound("Effect", "PowerStrikeHit", false, "Maple/Player/Skill/PowerStrike/Hit.mp3");
	GetSceneResource()->LoadSound("Effect", "SlashBlastUse", false, "Maple/Player/Skill/SlashBlast/Use.mp3");
	GetSceneResource()->LoadSound("Effect", "SlashBlastHit", false, "Maple/Player/Skill/SlashBlast/Hit.mp3");
	GetSceneResource()->LoadSound("Effect", "JudgementUse", false, "Maple/Player/Skill/Judgement/Use.mp3");
	GetSceneResource()->LoadSound("Effect", "JudgementHit", false, "Maple/Player/Skill/Judgement/Hit.mp3");
	GetSceneResource()->LoadSound("Effect", "JusticeUse1", false, "Maple/Player/Skill/Justice/Use1.mp3");
	GetSceneResource()->LoadSound("Effect", "JusticeUse2", false, "Maple/Player/Skill/Justice/Use2.mp3");

	GetSceneResource()->LoadSound("Effect", "BallogDamage", false, "Maple/Monster/Ballog/Damage.mp3");
	GetSceneResource()->LoadSound("Effect", "BallogDie", false, "Maple/Monster/Ballog/Die.mp3");
	GetSceneResource()->LoadSound("Effect", "BallogSkill1Use", false, "Maple/Monster/Ballog/Attack1.mp3");
	GetSceneResource()->LoadSound("Effect", "BallogSkill1Hit", false, "Maple/Monster/Ballog/CharDam1.mp3");
	GetSceneResource()->LoadSound("Effect", "BallogSkill2Use", false, "Maple/Monster/Ballog/Attack2.mp3");
	GetSceneResource()->LoadSound("Effect", "BallogSkill2Hit", false, "Maple/Monster/Ballog/CharDam2.mp3");
	GetSceneResource()->LoadSound("Effect", "BallogSkill3Use", false, "Maple/Monster/Ballog/Attack3.mp3");
	GetSceneResource()->LoadSound("Effect", "BallogSkill3Hit", false, "Maple/Monster/Ballog/CharDam3.mp3");

	GetSceneResource()->LoadSound("Effect", "TauroMasisDie", false, "Maple/Monster/TauroMasis/Die.mp3");
	GetSceneResource()->LoadSound("Effect", "TauroMasisDamage", false, "Maple/Monster/TauroMasis/Damage.mp3");
	GetSceneResource()->LoadSound("Effect", "TauroMasisSkill1", false, "Maple/Monster/TauroMasis/Attack1.mp3");

	GetSceneResource()->LoadSound("Effect", "TauroSpearDie", false, "Maple/Monster/TauroSpear/Die.mp3");
	GetSceneResource()->LoadSound("Effect", "TauroSpearDamage", false, "Maple/Monster/TauroSpear/Damage.mp3");
	GetSceneResource()->LoadSound("Effect", "TauroSpearSkill1", false, "Maple/Monster/TauroSpear/Attack1.mp3");
	GetSceneResource()->LoadSound("Effect", "TauroSpearSkill2", false, "Maple/Monster/TauroSpear/Attack2.mp3");
	GetSceneResource()->LoadSound("Effect", "TauroSpearSkill1Hit", false, "Maple/Monster/TauroSpear/CharDam1.mp3");
	GetSceneResource()->LoadSound("Effect", "TauroSpearSkill2Hit", false, "Maple/Monster/TauroSpear/CharDam2.mp3");

	GetSceneResource()->LoadSound("Effect", "WildCargoDie", false, "Maple/Monster/WildCargo/Die.mp3");
	GetSceneResource()->LoadSound("Effect", "WildCargoDamage", false, "Maple/Monster/WildCargo/Damage.mp3");


	// 이름이 MainBGM인 사운드를 재생한다.
	// GetSceneResource()->SoundPlay("MainBGM");

	// 마스터 볼륨 조절
	GetSceneResource()->SetVolume(70);

	// 채널별 볼륨 조절
	GetSceneResource()->SetVolume("Effect", 40);
	GetSceneResource()->SetVolume("BGM", 50);

	// 카메라 구성요소를 초기화한다.
	GetCamera()->SetResolution(800.f, 600.f);	// 카메라 영역 크기
	GetCamera()->SetWorldResolution(1532.f, 940.f);  // 전체 크기
	GetCamera()->SetTargetPivot(0.5f, 0.5f);  // 타겟 피봇 (오브젝트의 카메라 영역 상 위치 비율)

    /*
        오브젝트중 배경을 가장 먼저 생성해야 다른 오브젝트들이
        그 위에 덮여 그려질 수 있다.
    */
    // 메인씬에 오브젝트(배경)을 추가한다.
	CScene4Back1* back1 = CreateObject<CScene4Back1>("Scene4Back1");
    CreateObject<CScene4Back2>("Scene4Back2");


	// 메인씬에 바닥 선을 추가한다.
	CGround* ground = CreateObject<CGround>("Ground1");
	ground->SetInfo(Vector2(1.f, 739.f), Vector2(1529.f, 739.f));
	ground->SetType(ELineType::Ground);

	ground = CreateObject<CGround>("Ground2");
	ground->SetInfo(Vector2(1.f, 260.f), Vector2(195.f, 260.f));
	ground->SetType(ELineType::Ground);

	ground = CreateObject<CGround>("Ground3");
	ground->SetInfo(Vector2(1.f, 441.f), Vector2(181.f, 441.f));
	ground->SetType(ELineType::Ground);

	ground = CreateObject<CGround>("Ground4");
	ground->SetInfo(Vector2(142.f, 288.f), Vector2(300.f, 288.f));
	ground->SetType(ELineType::Ground);

	ground = CreateObject<CGround>("Ground5");
	ground->SetInfo(Vector2(306.f, 254.f), Vector2(454.f, 254.f));
	ground->SetType(ELineType::Ground);

	ground = CreateObject<CGround>("Ground6");
	ground->SetInfo(Vector2(413.f, 393.f), Vector2(585.f, 393.f));
	ground->SetType(ELineType::Ground);

	ground = CreateObject<CGround>("Ground7");
	ground->SetInfo(Vector2(913.f, 445.f), Vector2(1208.f, 445.f));
	ground->SetType(ELineType::Ground);


	// 벽 선을 추가한다.
	CWall* wall = CreateObject<CWall>("Wall1");
	wall->SetInfo(Vector2(1.f, 1.f), Vector2(1.f, 738.f));
	wall->SetType(ELineType::Wall);

	wall = CreateObject<CWall>("Wall2");
	wall->SetInfo(Vector2(1532.f, 1.f), Vector2(1532.f, 933.f));
	wall->SetType(ELineType::Wall);


	// 밧줄과 사다리를 추가한다.
	CLadder* ladder = CreateObject<CLadder>("Ladder1");
	ladder->SetInfo(Vector2(194.f, 287.f), Vector2(194.f, 499.f));
	ladder->SetType(ELineType::Ladder);

	ladder = CreateObject<CLadder>("Ladder2");
	ladder->SetInfo(Vector2(105.f, 439.f), Vector2(105.f, 665.f));
	ladder->SetType(ELineType::Ladder);

	ladder = CreateObject<CLadder>("Ladder3");
	ladder->SetInfo(Vector2(1079.f, 445.f), Vector2(1079.f, 662.f));
	ladder->SetType(ELineType::Ladder);

	// 씬에 위젯 윈도우를 추가한다.
	CreateWidgetWindow<CMainHUD>("MainHUD");
	
	// 메인씬에 오브젝트(플레이어)를 추가한다.
	CPlayer* player;

	player = CreateObject<CPlayer>("Player");

	Vector2 pos = CPlayer::m_spawnPos;
	player->SetPos(pos.x, pos.y);
	player->SetFallStartY(pos.y);

	// 메인씬에 플레이어 정보를 등록한다.
	SetPlayer(player);

	// 카메라의 타겟으로 '플레이어'를 지정한다.
	GetCamera()->SetTarget(m_player);



 //   // 씬에 오브젝트(플레이어)를 추가한다.
 //   CPlayer* player =  CreateObject<CPlayer>("Player");

 //   // 씬에 플레이어 정보를 등록한다.
 //   SetPlayer(player);

	//// 카메라의 타겟으로 '플레이어'를 지정한다.
	//GetCamera()->SetTarget(player);




    // 메인씬에 오브젝트(몬스터)를 추가한다. 카메라 변환을 위해 반환값을 가져다 사용한다. 
    // m_monster = CreateObject<CMonster>("Monster");



	// 메인씬에 발록을 추가한다.
	CMonster* Ballog = CreateObject<CBallog>("Ballog0");

	// 발록의 위치를 설정한다.
	Ballog->SetPos(100, 739);
	// 메인씬에 발록을 등록한다.
	m_monsterList.push_back(Ballog);
	Ballog->SetFallStartY(700.f);


	Ballog = CreateObject<CBallog>("Ballog1");
	Ballog->SetPos(1400, 300);
	m_monsterList.push_back(Ballog);
	Ballog->SetFallStartY(700.f);
\

	/*Ballog = CreateObject<CBallog>("Ballog3");
	Ballog->SetPos(650, 300);
	m_monsterList.push_back(Ballog);

	Ballog = CreateObject<CBallog>("Ballog4");
	Ballog->SetPos(600, 300);
	m_monsterList.push_back(Ballog);

	Ballog = CreateObject<CBallog>("Ballog5");
	Ballog->SetPos(550, 300);
	m_monsterList.push_back(Ballog);

	Ballog = CreateObject<CBallog>("Ballog6");
	Ballog->SetPos(500, 300);
	m_monsterList.push_back(Ballog);

	Ballog = CreateObject<CBallog>("Ballog7");
	Ballog->SetPos(450, 300);
	m_monsterList.push_back(Ballog);

	Ballog = CreateObject<CBallog>("Ballog8");
	Ballog->SetPos(400, 300);
	m_monsterList.push_back(Ballog);


	Ballog = CreateObject<CBallog>("Ballog9");
	Ballog->SetPos(600, 800);
	m_monsterList.push_back(Ballog);

	Ballog = CreateObject<CBallog>("Ballog10");
	Ballog->SetPos(700, 800);
	m_monsterList.push_back(Ballog);

	Ballog = CreateObject<CBallog>("Ballog11");
	Ballog->SetPos(800, 800);
	m_monsterList.push_back(Ballog);

	Ballog = CreateObject<CBallog>("Ballog12");
	Ballog->SetPos(900, 800);
	m_monsterList.push_back(Ballog);

	Ballog = CreateObject<CBallog>("Ballog13");
	Ballog->SetPos(1000, 800);
	m_monsterList.push_back(Ballog);

	Ballog = CreateObject<CBallog>("Ballog14");
	Ballog->SetPos(1100, 800);
	m_monsterList.push_back(Ballog);

	Ballog = CreateObject<CBallog>("Ballog15");
	Ballog->SetPos(1200, 800);
	m_monsterList.push_back(Ballog);*/

	//TauroMasis = CreateObject<CTauroMasis>("TauroMasis1");
	//TauroMasis->SetPos(1043, 500);
	//m_monsterList.push_back(TauroMasis);

	//TauroMasis = CreateObject<CTauroMasis>("TauroMasis2");
	//TauroMasis->SetPos(1043, 500);
	//m_monsterList.push_back(TauroMasis);

	//TauroMasis = CreateObject<CTauroMasis>("TauroMasis3");
	//TauroMasis->SetPos(1043, 500);
	//m_monsterList.push_back(TauroMasis);

	//// 메인씬에 타우로스피어를 추가한다.
	//CMonster* TauroSpear = CreateObject<CTauroSpear>("TauroSpear1");
	//TauroSpear->SetPos(100, 500);
	//// 메인씬에 타우로스피어를 등록한다.
	//m_monsterList.push_back(TauroSpear);
	//TauroSpear->SetFallStartY(700.f);

	//TauroSpear = CreateObject<CTauroSpear>("TauroSpear2");
	//TauroSpear->SetPos(200, 500);
	//// 메인씬에 타우로스피어를 등록한다.
	//m_monsterList.push_back(TauroSpear);
	//TauroSpear->SetFallStartY(700.f);

	//TauroSpear = CreateObject<CTauroSpear>("TauroSpear3");
	//TauroSpear->SetPos(300, 500);
	//// 메인씬에 타우로스피어를 등록한다.
	//m_monsterList.push_back(TauroSpear);
	//TauroSpear->SetFallStartY(700.f);

	//TauroSpear = CreateObject<CTauroSpear>("TauroSpear4");
	//TauroSpear->SetPos(400, 500);
	//// 메인씬에 타우로스피어를 등록한다.
	//m_monsterList.push_back(TauroSpear);
	//TauroSpear->SetFallStartY(700.f);

	//TauroSpear = CreateObject<CTauroSpear>("TauroSpear5");
	//TauroSpear->SetPos(800, 500);
	//// 메인씬에 타우로스피어를 등록한다.
	//m_monsterList.push_back(TauroSpear);
	//TauroSpear->SetFallStartY(700.f);

	//TauroSpear = CreateObject<CTauroSpear>("TauroSpear6");
	//TauroSpear->SetPos(900, 500);
	//// 메인씬에 타우로스피어를 등록한다.
	//m_monsterList.push_back(TauroSpear);
	//TauroSpear->SetFallStartY(700.f);

	//TauroSpear = CreateObject<CTauroSpear>("TauroSpear7");
	//TauroSpear->SetPos(1000, 500);
	//// 메인씬에 타우로스피어를 등록한다.
	//m_monsterList.push_back(TauroSpear);
	//TauroSpear->SetFallStartY(700.f);

	//TauroSpear = CreateObject<CTauroSpear>("TauroSpear8");
	//TauroSpear->SetPos(1100, 500);
	//// 메인씬에 타우로스피어를 등록한다.
	//m_monsterList.push_back(TauroSpear);
	//TauroSpear->SetFallStartY(700.f);

	//TauroSpear = CreateObject<CTauroSpear>("TauroSpear2");
	//TauroSpear->SetPos(943, 500);
	//m_monsterList.push_back(TauroSpear);

	//TauroSpear = CreateObject<CTauroSpear>("TauroSpear3");
	//TauroSpear->SetPos(943, 500);
	//m_monsterList.push_back(TauroSpear);


	// Scene3로 가는 포탈을 추가한다.
	CPortal* scene4Portal3 = CreateObject<CPortal>("Portal_Scene4ToScene3");
	scene4Portal3->SetPos(60.f, 255.f);

	// Scene1로 가는 포탈을 추가한다.
	CPortal* scene4Portal1 = CreateObject<CPortal>("Portal_Scene4ToScene1");
	scene4Portal1->SetPos(1470.f, 735.f);

	/*
		메인 씬 전용 키를 추가한다.
		F1 키를 누르면 Cam1Key 함수가 호출되어 타겟이 플레이어로 바뀔 것이고,
		F2 키를 누르면 Cam2Key 함수가 호출되어 타겟이 몬스터로 바뀔 것이다.
	*/
	/*CInput::GetInst()->AddBindFunction<CMainScene>("Cam1",
		EInputType::DOWN, this, &CMainScene::Cam1Key);
	CInput::GetInst()->AddBindFunction<CMainScene>("Cam2",
		EInputType::DOWN, this, &CMainScene::Cam2Key);*/

	// 씬에 위젯 윈도우를 추가한다.
	// CreateWidgetWindow<CCharacterHUD>("CharacterHUD");


    return true;
}

void CMainScene::CreateAnimationSequence_Effect()
{
	// 플레이어 왼쪽->오른쪽 히트 이펙트 
	std::vector<std::wstring>	vecFileName_LhitEffect;

	for (int i = 0; i < 3; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Skill/HitEffect/Base/LeftToRight/%d.bmp"), i);

		vecFileName_LhitEffect.push_back(fileName);
	}

	// 있는 애니메이션인지 판단한다.
	if (!GetSceneResource()->FindAnimation("LeftHitEffect"))
	{
		GetSceneResource()->CreateAnimationSequence("LeftHitEffect",
			"LeftHitEffect", vecFileName_LhitEffect, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("LeftHitEffect", 0.f, 0.f,
			36.f, 59.f);
		GetSceneResource()->AddAnimationFrame("LeftHitEffect", 0.f, 0.f,
			48.f, 77.f);
		GetSceneResource()->AddAnimationFrame("LeftHitEffect", 0.f, 0.f,
			24.f, 47.f);

		GetSceneResource()->AddAnimationFramePivot("LeftHitEffect", 0.277f, 0.98f);
		GetSceneResource()->AddAnimationFramePivot("LeftHitEffect", 0.23f, 0.987f);
		GetSceneResource()->AddAnimationFramePivot("LeftHitEffect", 0.f, 0.978f);

		GetSceneResource()->SetColorKey("LeftHitEffect", 255, 0, 255);
	}



	// 플레이어 오른쪽->왼쪽 히트 이펙트 
	std::vector<std::wstring>	vecFileName_hitEffect;

	for (int i = 0; i < 3; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Skill/HitEffect/Base/RightToLeft/%d.bmp"), i);

		vecFileName_hitEffect.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("RightHitEffect"))
	{
		GetSceneResource()->CreateAnimationSequence("RightHitEffect",
			"RightHitEffect", vecFileName_hitEffect, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("RightHitEffect", 0.f, 0.f,
			36.f, 59.f);
		GetSceneResource()->AddAnimationFrame("RightHitEffect", 0.f, 0.f,
			48.f, 77.f);
		GetSceneResource()->AddAnimationFrame("RightHitEffect", 0.f, 0.f,
			24.f, 47.f);

		GetSceneResource()->AddAnimationFramePivot("RightHitEffect", 0.723f, 0.98f);
		GetSceneResource()->AddAnimationFramePivot("RightHitEffect", 0.77f, 0.987f);
		GetSceneResource()->AddAnimationFramePivot("RightHitEffect", 1.f, 0.978f);

		GetSceneResource()->SetColorKey("RightHitEffect", 255, 0, 255);
	}



	// 플레이어 왼쪽->오른쪽 공격 이펙트 1
	std::vector<std::wstring> vecFileName;

	for (int i = 0; i < 4; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Skill/AttackEffect/Base/Left/swing1_%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("LeftAttackEffect1"))
	{
		GetSceneResource()->CreateAnimationSequence("LeftAttackEffect1",
			"LeftAttackEffect1", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("LeftAttackEffect1", 0.f, 0.f,
			166.f, 119.f);
		GetSceneResource()->AddAnimationFrame("LeftAttackEffect1", 0.f, 0.f,
			166.f, 119.f);
		GetSceneResource()->AddAnimationFrame("LeftAttackEffect1", 0.f, 0.f,
			166.f, 119.f);
		GetSceneResource()->AddAnimationFrame("LeftAttackEffect1", 0.f, 0.f,
			166.f, 119.f);


		GetSceneResource()->AddAnimationFramePivot("LeftAttackEffect1", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("LeftAttackEffect1", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("LeftAttackEffect1", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("LeftAttackEffect1", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("LeftAttackEffect1", 255, 0, 255);
	}



	// 플레이어 왼쪽->오른쪽 공격 이펙트 2
	vecFileName.clear();

	for (int i = 0; i < 4; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Skill/AttackEffect/Base/Left/swing2_%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("LeftAttackEffect2"))
	{
		GetSceneResource()->CreateAnimationSequence("LeftAttackEffect2",
			"LeftAttackEffect2", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("LeftAttackEffect2", 0.f, 0.f,
			141.f, 100.f);
		GetSceneResource()->AddAnimationFrame("LeftAttackEffect2", 0.f, 0.f,
			141.f, 100.f);
		GetSceneResource()->AddAnimationFrame("LeftAttackEffect2", 0.f, 0.f,
			141.f, 100.f);
		GetSceneResource()->AddAnimationFrame("LeftAttackEffect2", 0.f, 0.f,
			141.f, 100.f);

		GetSceneResource()->AddAnimationFramePivot("LeftAttackEffect2", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("LeftAttackEffect2", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("LeftAttackEffect2", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("LeftAttackEffect2", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("LeftAttackEffect2", 255, 0, 255);
	}



	// 플레이어 왼쪽->오른쪽 공격 이펙트 3
	vecFileName.clear();

	for (int i = 0; i < 4; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Skill/AttackEffect/Base/Left/swing3_%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("LeftAttackEffect3"))
	{
		GetSceneResource()->CreateAnimationSequence("LeftAttackEffect3",
			"LeftAttackEffect3", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("LeftAttackEffect3", 0.f, 0.f,
			164.f, 121.f);
		GetSceneResource()->AddAnimationFrame("LeftAttackEffect3", 0.f, 0.f,
			164.f, 121.f);
		GetSceneResource()->AddAnimationFrame("LeftAttackEffect3", 0.f, 0.f,
			164.f, 121.f);
		GetSceneResource()->AddAnimationFrame("LeftAttackEffect3", 0.f, 0.f,
			164.f, 121.f);

		GetSceneResource()->AddAnimationFramePivot("LeftAttackEffect3", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("LeftAttackEffect3", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("LeftAttackEffect3", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("LeftAttackEffect3", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("LeftAttackEffect3", 255, 0, 255);
	}



	// 플레이어 왼쪽->오른쪽 공격 이펙트 4
	vecFileName.clear();

	for (int i = 0; i < 5; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Skill/AttackEffect/Base/Left/stab_%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("LeftAttackEffect4"))
	{
		GetSceneResource()->CreateAnimationSequence("LeftAttackEffect4",
			"LeftAttackEffect4", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("LeftAttackEffect4", 0.f, 0.f,
			120.f, 100.f);
		GetSceneResource()->AddAnimationFrame("LeftAttackEffect4", 0.f, 0.f,
			120.f, 100.f);
		GetSceneResource()->AddAnimationFrame("LeftAttackEffect4", 0.f, 0.f,
			120.f, 100.f);
		GetSceneResource()->AddAnimationFrame("LeftAttackEffect4", 0.f, 0.f,
			120.f, 100.f);
		GetSceneResource()->AddAnimationFrame("LeftAttackEffect4", 0.f, 0.f,
			120.f, 100.f);

		GetSceneResource()->AddAnimationFramePivot("LeftAttackEffect4", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("LeftAttackEffect4", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("LeftAttackEffect4", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("LeftAttackEffect4", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("LeftAttackEffect4", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("LeftAttackEffect4", 255, 0, 255);
	}



	// 플레이어 오른쪽->왼쪽 공격 이펙트 1
	vecFileName.clear();

	for (int i = 0; i < 4; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Skill/AttackEffect/Base/Right/swing1_%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("RightAttackEffect1"))
	{
		GetSceneResource()->CreateAnimationSequence("RightAttackEffect1",
			"RightAttackEffect1", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("RightAttackEffect1", 0.f, 0.f,
			166.f, 119.f);
		GetSceneResource()->AddAnimationFrame("RightAttackEffect1", 0.f, 0.f,
			166.f, 119.f);
		GetSceneResource()->AddAnimationFrame("RightAttackEffect1", 0.f, 0.f,
			166.f, 119.f);
		GetSceneResource()->AddAnimationFrame("RightAttackEffect1", 0.f, 0.f,
			166.f, 119.f);

		GetSceneResource()->AddAnimationFramePivot("RightAttackEffect1", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("RightAttackEffect1", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("RightAttackEffect1", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("RightAttackEffect1", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("RightAttackEffect1", 255, 0, 255);
	}



	// 플레이어 오른쪽->왼쪽 공격 이펙트 2
	vecFileName.clear();

	for (int i = 0; i < 4; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Skill/AttackEffect/Base/Right/swing2_%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("RightAttackEffect2"))
	{
		GetSceneResource()->CreateAnimationSequence("RightAttackEffect2",
			"RightAttackEffect2", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("RightAttackEffect2", 0.f, 0.f,
			141.f, 100.f);
		GetSceneResource()->AddAnimationFrame("RightAttackEffect2", 0.f, 0.f,
			141.f, 100.f);
		GetSceneResource()->AddAnimationFrame("RightAttackEffect2", 0.f, 0.f,
			141.f, 100.f);
		GetSceneResource()->AddAnimationFrame("RightAttackEffect2", 0.f, 0.f,
			141.f, 100.f);

		GetSceneResource()->AddAnimationFramePivot("RightAttackEffect2", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("RightAttackEffect2", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("RightAttackEffect2", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("RightAttackEffect2", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("RightAttackEffect2", 255, 0, 255);
	}



	// 플레이어 오른쪽->왼쪽 공격 이펙트 3
	vecFileName.clear();

	for (int i = 0; i < 4; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Skill/AttackEffect/Base/Right/swing3_%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("RightAttackEffect3"))
	{
		GetSceneResource()->CreateAnimationSequence("RightAttackEffect3",
			"RightAttackEffect3", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("RightAttackEffect3", 0.f, 0.f,
			164.f, 121.f);
		GetSceneResource()->AddAnimationFrame("RightAttackEffect3", 0.f, 0.f,
			164.f, 121.f);
		GetSceneResource()->AddAnimationFrame("RightAttackEffect3", 0.f, 0.f,
			164.f, 121.f);
		GetSceneResource()->AddAnimationFrame("RightAttackEffect3", 0.f, 0.f,
			164.f, 121.f);

		GetSceneResource()->AddAnimationFramePivot("RightAttackEffect3", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("RightAttackEffect3", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("RightAttackEffect3", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("RightAttackEffect3", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("RightAttackEffect3", 255, 0, 255);
	}



	// 플레이어 오른쪽->왼쪽 공격 이펙트 4
	vecFileName.clear();

	for (int i = 0; i < 5; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Skill/AttackEffect/Base/Right/stab_%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("RightAttackEffect4"))
	{
		GetSceneResource()->CreateAnimationSequence("RightAttackEffect4",
			"RightAttackEffect4", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("RightAttackEffect4", 0.f, 0.f,
			120.f, 100.f);
		GetSceneResource()->AddAnimationFrame("RightAttackEffect4", 0.f, 0.f,
			120.f, 100.f);
		GetSceneResource()->AddAnimationFrame("RightAttackEffect4", 0.f, 0.f,
			120.f, 100.f);
		GetSceneResource()->AddAnimationFrame("RightAttackEffect4", 0.f, 0.f,
			120.f, 100.f);
		GetSceneResource()->AddAnimationFrame("RightAttackEffect4", 0.f, 0.f,
			120.f, 100.f);

		GetSceneResource()->AddAnimationFramePivot("RightAttackEffect4", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("RightAttackEffect4", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("RightAttackEffect4", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("RightAttackEffect4", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("RightAttackEffect4", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("RightAttackEffect4", 255, 0, 255);
	}



	// 파워스트라이크 발동 이펙트
	vecFileName.clear();

	for (int i = 0; i < 8; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Skill/AttackEffect/PowerStrike/11001002.effect.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PowerStrikeEffect"))
	{
		GetSceneResource()->CreateAnimationSequence("PowerStrikeEffect",
			"PowerStrikeEffect", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("PowerStrikeEffect", 0.f, 0.f,
			228.f, 215.f);
		GetSceneResource()->AddAnimationFrame("PowerStrikeEffect", 0.f, 0.f,
			223.f, 207.f);
		GetSceneResource()->AddAnimationFrame("PowerStrikeEffect", 0.f, 0.f,
			212.f, 196.f);
		GetSceneResource()->AddAnimationFrame("PowerStrikeEffect", 0.f, 0.f,
			197.f, 177.f);
		GetSceneResource()->AddAnimationFrame("PowerStrikeEffect", 0.f, 0.f,
			144.f, 113.f);
		GetSceneResource()->AddAnimationFrame("PowerStrikeEffect", 0.f, 0.f,
			78.f, 64.f);
		GetSceneResource()->AddAnimationFrame("PowerStrikeEffect", 0.f, 0.f,
			68.f, 59.f);
		GetSceneResource()->AddAnimationFrame("PowerStrikeEffect", 0.f, 0.f,
			64.f, 51.f);

		GetSceneResource()->AddAnimationFramePivot("PowerStrikeEffect", 0.5f, 0.47f);
		GetSceneResource()->AddAnimationFramePivot("PowerStrikeEffect", 0.5f, 0.47f);
		GetSceneResource()->AddAnimationFramePivot("PowerStrikeEffect", 0.51f, 0.47f);
		GetSceneResource()->AddAnimationFramePivot("PowerStrikeEffect", 0.52f, 0.47f);
		GetSceneResource()->AddAnimationFramePivot("PowerStrikeEffect", 0.65f, 0.45f);
		GetSceneResource()->AddAnimationFramePivot("PowerStrikeEffect", 0.58f, 0.51f);
		GetSceneResource()->AddAnimationFramePivot("PowerStrikeEffect", 0.5f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("PowerStrikeEffect", 0.5f, 0.5f);

		GetSceneResource()->SetColorKey("PowerStrikeEffect", 255, 0, 255);
	}



	// 파워스트라이크 히트 이펙트
	vecFileName.clear();

	for (int i = 0; i < 5; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Skill/HitEffect/PowerStrike/11001002.Hit.1.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PowerStrikeHit"))
	{
		GetSceneResource()->CreateAnimationSequence("PowerStrikeHit",
			"PowerStrikeHit", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("PowerStrikeHit", 0.f, 0.f,
			55.f, 73.f);
		GetSceneResource()->AddAnimationFrame("PowerStrikeHit", 0.f, 0.f,
			110.f, 146.f);
		GetSceneResource()->AddAnimationFrame("PowerStrikeHit", 0.f, 0.f,
			120.f, 155.f);
		GetSceneResource()->AddAnimationFrame("PowerStrikeHit", 0.f, 0.f,
			126.f, 154.f);
		GetSceneResource()->AddAnimationFrame("PowerStrikeHit", 0.f, 0.f,
			122.f, 146.f);

		GetSceneResource()->AddAnimationFramePivot("PowerStrikeHit", 0.5f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("PowerStrikeHit", 0.5f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("PowerStrikeHit", 0.5f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("PowerStrikeHit", 0.5f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("PowerStrikeHit", 0.5f, 0.5f);

		GetSceneResource()->SetColorKey("PowerStrikeHit", 255, 0, 255);
	}



	// 슬래시블러스트 발동 이펙트
	vecFileName.clear();

	for (int i = 0; i < 5; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Skill/AttackEffect/SlashBlast/11001003.effect.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("SlashBlastEffect"))
	{
		GetSceneResource()->CreateAnimationSequence("SlashBlastEffect",
			"SlashBlastEffect", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("SlashBlastEffect", 0.f, 0.f,
			92.f, 80.f);
		GetSceneResource()->AddAnimationFrame("SlashBlastEffect", 0.f, 0.f,
			92.f, 79.f);
		GetSceneResource()->AddAnimationFrame("SlashBlastEffect", 0.f, 0.f,
			80.f, 69.f);
		GetSceneResource()->AddAnimationFrame("SlashBlastEffect", 0.f, 0.f,
			54.f, 49.f);
		GetSceneResource()->AddAnimationFrame("SlashBlastEffect", 0.f, 0.f,
			35.f, 32.f);

		GetSceneResource()->AddAnimationFramePivot("SlashBlastEffect", 0.5f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("SlashBlastEffect", 0.5f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("SlashBlastEffect", 0.5f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("SlashBlastEffect", 0.5f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("SlashBlastEffect", 0.5f, 0.5f);

		GetSceneResource()->SetColorKey("SlashBlastEffect", 255, 0, 255);
	}



	// 슬래시블러스트 히트 이펙트
	vecFileName.clear();

	for (int i = 0; i < 4; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Skill/HitEffect/SlashBlast/11001003.hit.1.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("SlashBlastHit"))
	{
		GetSceneResource()->CreateAnimationSequence("SlashBlastHit",
			"SlashBlastHit", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("SlashBlastHit", 0.f, 0.f,
			101.f, 93.f);
		GetSceneResource()->AddAnimationFrame("SlashBlastHit", 0.f, 0.f,
			125.f, 90.f);
		GetSceneResource()->AddAnimationFrame("SlashBlastHit", 0.f, 0.f,
			120.f, 86.f);
		GetSceneResource()->AddAnimationFrame("SlashBlastHit", 0.f, 0.f,
			88.f, 56.f);

		GetSceneResource()->AddAnimationFramePivot("SlashBlastHit", 0.53f, 0.69f);
		GetSceneResource()->AddAnimationFramePivot("SlashBlastHit", 0.46f, 0.82f);
		GetSceneResource()->AddAnimationFramePivot("SlashBlastHit", 0.46f, 0.82f);
		GetSceneResource()->AddAnimationFramePivot("SlashBlastHit", 0.36f, 0.96f);

		GetSceneResource()->SetColorKey("SlashBlastHit", 255, 0, 255);
	}


	// 오른쪽 저지먼트 발동 이펙트
	vecFileName.clear();
	for (int i = 1; i <= 4; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Player/Right/Judgement/e%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PlayerRightJudgementEffect"))
	{
		GetSceneResource()->CreateAnimationSequence("PlayerRightJudgementEffect",
			"PlayerRightJudgementEffect", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("PlayerRightJudgementEffect", 0.f, 0.f,
			752.f, 428.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJudgementEffect", 0.f, 0.f,
			740.f, 440.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJudgementEffect", 0.f, 0.f,
			740.f, 440.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJudgementEffect", 0.f, 0.f,
			752.f, 428.f);

		GetSceneResource()->AddAnimationFramePivot("PlayerRightJudgementEffect", 0.5f, 0.53f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJudgementEffect", 0.5f, 0.53f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJudgementEffect", 0.5f, 0.53f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJudgementEffect", 0.5f, 0.53f);

		GetSceneResource()->SetColorKey("PlayerRightJudgementEffect", 255, 0, 255);
	}
	


	// 저지먼트 히트 이펙트
	vecFileName.clear();
	for (int i = 0; i < 4; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Skill/HitEffect/Judgement/%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("JudgementHit"))
	{
		GetSceneResource()->CreateAnimationSequence("JudgementHit",
			"JudgementHit", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("JudgementHit", 0.f, 0.f,
			159.f, 99.f);
		GetSceneResource()->AddAnimationFrame("JudgementHit", 0.f, 0.f,
			144.f, 108.f);
		GetSceneResource()->AddAnimationFrame("JudgementHit", 0.f, 0.f,
			132.f, 101.f);
		GetSceneResource()->AddAnimationFrame("JudgementHit", 0.f, 0.f,
			87.f, 17.f);

		GetSceneResource()->AddAnimationFramePivot("JudgementHit", 0.5f, 0.6f);
		GetSceneResource()->AddAnimationFramePivot("JudgementHit", 0.6f, 0.61f);
		GetSceneResource()->AddAnimationFramePivot("JudgementHit", 0.55f, 0.57f);
		GetSceneResource()->AddAnimationFramePivot("JudgementHit", 0.5f, 0.52f);

		GetSceneResource()->SetColorKey("JudgementHit", 255, 0, 255);
	}
	

	// 오른쪽 저스티스 이펙트
	vecFileName.clear();
	for (int i = 1; i <= 15; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Player/Right/Justice/e%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PlayerRightJusticeEffect"))
	{
		GetSceneResource()->CreateAnimationSequence("PlayerRightJusticeEffect",
			"PlayerRightJusticeEffect", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("PlayerRightJusticeEffect", 0.f, 0.f,
			740.f, 440.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJusticeEffect", 0.f, 0.f,
			752.f, 428.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJusticeEffect", 0.f, 0.f,
			760.f, 420.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJusticeEffect", 0.f, 0.f,
			752.f, 380.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJusticeEffect", 0.f, 0.f,
			752.f, 380.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJusticeEffect", 0.f, 0.f,
			752.f, 380.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJusticeEffect", 0.f, 0.f,
			752.f, 380.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJusticeEffect", 0.f, 0.f,
			752.f, 380.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJusticeEffect", 0.f, 0.f,
			752.f, 380.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJusticeEffect", 0.f, 0.f,
			752.f, 428.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJusticeEffect", 0.f, 0.f,
			760.f, 420.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJusticeEffect", 0.f, 0.f,
			752.f, 380.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJusticeEffect", 0.f, 0.f,
			752.f, 380.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJusticeEffect", 0.f, 0.f,
			752.f, 380.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJusticeEffect", 0.f, 0.f,
			752.f, 380.f);

		GetSceneResource()->AddAnimationFramePivot("PlayerRightJusticeEffect", 0.56f, 0.64f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJusticeEffect", 0.56f, 0.64f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJusticeEffect", 0.56f, 0.64f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJusticeEffect", 0.56f, 0.64f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJusticeEffect", 0.56f, 0.64f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJusticeEffect", 0.56f, 0.64f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJusticeEffect", 0.56f, 0.64f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJusticeEffect", 0.56f, 0.64f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJusticeEffect", 0.56f, 0.64f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJusticeEffect", 0.58f, 0.50f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJusticeEffect", 0.58f, 0.50f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJusticeEffect", 0.58f, 0.50f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJusticeEffect", 0.58f, 0.50f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJusticeEffect", 0.58f, 0.50f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJusticeEffect", 0.58f, 0.50f);

		GetSceneResource()->SetColorKey("PlayerRightJusticeEffect", 255, 0, 255);
	}
	


	// 왼쪽 저스티스 이펙트
	vecFileName.clear();
	for (int i = 1; i <= 15; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Player/Left/Justice/e%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PlayerLeftJusticeEffect"))
	{
		GetSceneResource()->CreateAnimationSequence("PlayerLeftJusticeEffect",
			"PlayerLeftJusticeEffect", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("PlayerLeftJusticeEffect", 0.f, 0.f,
			740.f, 440.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJusticeEffect", 0.f, 0.f,
			752.f, 428.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJusticeEffect", 0.f, 0.f,
			760.f, 420.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJusticeEffect", 0.f, 0.f,
			752.f, 380.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJusticeEffect", 0.f, 0.f,
			752.f, 380.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJusticeEffect", 0.f, 0.f,
			752.f, 380.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJusticeEffect", 0.f, 0.f,
			752.f, 380.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJusticeEffect", 0.f, 0.f,
			752.f, 380.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJusticeEffect", 0.f, 0.f,
			752.f, 380.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJusticeEffect", 0.f, 0.f,
			752.f, 428.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJusticeEffect", 0.f, 0.f,
			760.f, 420.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJusticeEffect", 0.f, 0.f,
			752.f, 380.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJusticeEffect", 0.f, 0.f,
			752.f, 380.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJusticeEffect", 0.f, 0.f,
			752.f, 380.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJusticeEffect", 0.f, 0.f,
			752.f, 380.f);

		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJusticeEffect", 0.44f, 0.64f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJusticeEffect", 0.44f, 0.64f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJusticeEffect", 0.44f, 0.64f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJusticeEffect", 0.44f, 0.64f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJusticeEffect", 0.44f, 0.64f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJusticeEffect", 0.44f, 0.64f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJusticeEffect", 0.44f, 0.64f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJusticeEffect", 0.44f, 0.64f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJusticeEffect", 0.44f, 0.64f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJusticeEffect", 0.42f, 0.50f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJusticeEffect", 0.42f, 0.50f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJusticeEffect", 0.42f, 0.50f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJusticeEffect", 0.42f, 0.50f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJusticeEffect", 0.42f, 0.50f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJusticeEffect", 0.42f, 0.50f);

		GetSceneResource()->SetColorKey("PlayerLeftJusticeEffect", 255, 0, 255);
	}
	


	// 레벨업 이펙트
	vecFileName.clear();
	for (int i = 8; i <= 20; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/UI/LevelUp/LevelUp2.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("LevelUp"))
	{
		GetSceneResource()->CreateAnimationSequence("LevelUp",
			"LevelUp", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("LevelUp", 0.f, 0.f,
			246.f, 316.f);
		GetSceneResource()->AddAnimationFrame("LevelUp", 0.f, 0.f,
			296.f, 328.f);
		GetSceneResource()->AddAnimationFrame("LevelUp", 0.f, 0.f,
			296.f, 170.f);
		GetSceneResource()->AddAnimationFrame("LevelUp", 0.f, 0.f,
			296.f, 170.f);
		GetSceneResource()->AddAnimationFrame("LevelUp", 0.f, 0.f,
			178.f, 173.f);
		GetSceneResource()->AddAnimationFrame("LevelUp", 0.f, 0.f,
			178.f, 187.f);
		GetSceneResource()->AddAnimationFrame("LevelUp", 0.f, 0.f,
			178.f, 177.f);
		GetSceneResource()->AddAnimationFrame("LevelUp", 0.f, 0.f,
			178.f, 184.f);
		GetSceneResource()->AddAnimationFrame("LevelUp", 0.f, 0.f,
			178.f, 180.f);
		GetSceneResource()->AddAnimationFrame("LevelUp", 0.f, 0.f,
			178.f, 146.f);
		GetSceneResource()->AddAnimationFrame("LevelUp", 0.f, 0.f,
			178.f, 152.f);
		GetSceneResource()->AddAnimationFrame("LevelUp", 0.f, 0.f,
			163.f, 108.f);
		GetSceneResource()->AddAnimationFrame("LevelUp", 0.f, 0.f,
			161.f, 105.f);

		GetSceneResource()->AddAnimationFramePivot("LevelUp", 0.5f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("LevelUp", 0.5f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("LevelUp", 0.5f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("LevelUp", 0.5f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("LevelUp", 0.47f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("LevelUp", 0.47f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("LevelUp", 0.47f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("LevelUp", 0.47f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("LevelUp", 0.47f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("LevelUp", 0.47f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("LevelUp", 0.47f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("LevelUp", 0.47f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("LevelUp", 0.47f, 0.5f);

		GetSceneResource()->SetColorKey("LevelUp", 255, 0, 255);
	}
	
}

void CMainScene::CreateAnimationSequence()
{
	// 플레이어 오른쪽 멈춤

	/*
		우리가 가진 마우스 이미지는 sprite 타입의 이미지가 아닌
		여러 장으로 이루어진 frame 이미지이기 때문에, 텍스쳐 파일
		이름에 대한 벡터를 wstring으로 한다. (LoadTexture를 그렇게 만들었음)
	*/
	std::vector<std::wstring>	vecFileName;

	/*
		반복을 통해 정지상태를 표현하는 4개의 텍스쳐 파일에 대한
		FileName이 만들어 질 것이다.
	*/
	for (int i = 0; i < 4; ++i)
	{
		// 빈 파일네임 문자열을 만든다.
		TCHAR	fileName[MAX_PATH] = {};

		// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
		// 그렇게 만들어진 문자열은 FileName에 들어오게 된다.
		wsprintf(fileName, TEXT("Maple/Player/Right/stand_%d.bmp"), i);

		// 만들어진 파일 이름을 벡터에 추가한다
		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PlayerRightStand"))
	{
		// vecFileName을 인자로 전달하며 4개의 텍스쳐를 모두 등록한다. 
			// (텍스쳐 클래스의 vecImageInfo에 4번 등록하게 될 것임)
		GetSceneResource()->CreateAnimationSequence("PlayerRightStand",
			"PlayerRightStand", vecFileName, TEXTURE_PATH);

		// stand_0.bmp ~ stand_3.bmp 의 애니메이션 프레임데이터를 등록한다.
		for (int i = 0; i < 4; ++i)
		{
			GetSceneResource()->AddAnimationFrame("PlayerRightStand", 0.f, 0.f,
				57.f, 75.f);
		}

		// stand_0.bmp ~ stand_3.bmp 의 피봇을 등록한다.
		GetSceneResource()->AddAnimationFramePivot("PlayerRightStand", 0.45f, 0.93f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightStand", 0.47f, 0.93f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightStand", 0.49f, 0.93f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightStand", 0.47f, 0.93f);

		// stand_0.bmp ~ stand_3.bmp 의 컬러키를 등록한다.
		GetSceneResource()->SetColorKey("PlayerRightStand", 255, 0, 255);
	}



	// 플레이어 오른쪽 걷기

	vecFileName.clear();

	for (int i = 0; i < 4; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Player/Right/walk_%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PlayerRightWalk"))
	{
		GetSceneResource()->CreateAnimationSequence("PlayerRightWalk",
			"PlayerRightWalk", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("PlayerRightWalk", 0.f, 0.f,
			88.f, 71.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightWalk", 0.f, 0.f,
			90.f, 70.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightWalk", 0.f, 0.f,
			85.f, 71.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightWalk", 0.f, 0.f,
			81.f, 73.f);

		GetSceneResource()->AddAnimationFramePivot("PlayerRightWalk", 0.27f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightWalk", 0.23f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightWalk", 0.247f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightWalk", 0.27f, 0.945f);

		GetSceneResource()->SetColorKey("PlayerRightWalk", 255, 0, 255);
	}



	// 플레이어 오른쪽 기본공격1
	vecFileName.clear();
	for (int i = 0; i < 6; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Player/Right/swing1_%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PlayerRightAttack1"))
	{
		GetSceneResource()->CreateAnimationSequence("PlayerRightAttack1",
			"PlayerRightAttack1", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("PlayerRightAttack1", 0.f, 0.f,
			108.f, 71.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightAttack1", 0.f, 0.f,
			108.f, 71.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightAttack1", 0.f, 0.f,
			55.f, 100.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightAttack1", 0.f, 0.f,
			110.f, 80.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightAttack1", 0.f, 0.f,
			110.f, 80.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightAttack1", 0.f, 0.f,
			110.f, 80.f);

		GetSceneResource()->AddAnimationFramePivot("PlayerRightAttack1", 0.70f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightAttack1", 0.70f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightAttack1", 0.25f, 0.99f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightAttack1", 0.07f, 0.787f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightAttack1", 0.07f, 0.787f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightAttack1", 0.07f, 0.787f);

		GetSceneResource()->SetColorKey("PlayerRightAttack1", 255, 0, 255);

	}



	// 플레이어 오른쪽 기본공격2

	vecFileName.clear();

	for (int i = 0; i < 6; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Player/Right/swing2_%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PlayerRightAttack2"))
	{
		GetSceneResource()->CreateAnimationSequence("PlayerRightAttack2",
			"PlayerRightAttack2", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("PlayerRightAttack2", 0.f, 0.f,
			94.f, 69.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightAttack2", 0.f, 0.f,
			94.f, 69.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightAttack2", 0.f, 0.f,
			59.f, 98.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightAttack2", 0.f, 0.f,
			90.f, 76.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightAttack2", 0.f, 0.f,
			90.f, 76.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightAttack2", 0.f, 0.f,
			90.f, 76.f);

		GetSceneResource()->AddAnimationFramePivot("PlayerRightAttack2", 0.68f, 0.985f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightAttack2", 0.68f, 0.985f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightAttack2", 0.18f, 0.99f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightAttack2", 0.1f, 0.815f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightAttack2", 0.1f, 0.815f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightAttack2", 0.1f, 0.815f);

		GetSceneResource()->SetColorKey("PlayerRightAttack2", 255, 0, 255);
	}
	

	// 플레이어 오른쪽 기본공격3
	
	vecFileName.clear();

	for (int i = 0; i < 6; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Player/Right/swing3_%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PlayerRightAttack3"))
	{
		GetSceneResource()->CreateAnimationSequence("PlayerRightAttack3",
			"PlayerRightAttack3", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("PlayerRightAttack3", 0.f, 0.f,
			112.f, 69.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightAttack3", 0.f, 0.f,
			112.f, 69.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightAttack3", 0.f, 0.f,
			110.f, 73.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightAttack3", 0.f, 0.f,
			75.f, 97.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightAttack3", 0.f, 0.f,
			75.f, 97.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightAttack3", 0.f, 0.f,
			75.f, 97.f);

		GetSceneResource()->AddAnimationFramePivot("PlayerRightAttack3", 0.627f, 0.985f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightAttack3", 0.627f, 0.985f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightAttack3", 0.52f, 0.85f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightAttack3", 0.1f, 0.99f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightAttack3", 0.1f, 0.99f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightAttack3", 0.1f, 0.99f);

		GetSceneResource()->SetColorKey("PlayerRightAttack3", 255, 0, 255);
	}
	


	// 플레이어 오른쪽 기본공격4
	
	vecFileName.clear();

	for (int i = 0; i < 6; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Player/Right/stab_%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PlayerRightAttack4"))
	{
		GetSceneResource()->CreateAnimationSequence("PlayerRightAttack4",
			"PlayerRightAttack4", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("PlayerRightAttack4", 0.f, 0.f,
			85.f, 68.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightAttack4", 0.f, 0.f,
			86.f, 71.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightAttack4", 0.f, 0.f,
			86.f, 71.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightAttack4", 0.f, 0.f,
			122.f, 65.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightAttack4", 0.f, 0.f,
			122.f, 65.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightAttack4", 0.f, 0.f,
			122.f, 65.f);

		GetSceneResource()->AddAnimationFramePivot("PlayerRightAttack4", 0.27f, 0.985f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightAttack4", 0.24f, 0.985f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightAttack4", 0.24f, 0.985f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightAttack4", 0.03f, 0.985f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightAttack4", 0.03f, 0.985f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightAttack4", 0.03f, 0.985f);

		GetSceneResource()->SetColorKey("PlayerRightAttack4", 255, 0, 255);
	}
	


	// 플레이어 오른쪽 경계상태
	vecFileName.clear();

	for (int i = 0; i < 4; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Player/Right/alert_%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PlayerRightAlert"))
	{
		GetSceneResource()->CreateAnimationSequence("PlayerRightAlert",
			"PlayerRightAlert", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("PlayerRightAlert", 0.f, 0.f,
			96.f, 68.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightAlert", 0.f, 0.f,
			95.f, 69.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightAlert", 0.f, 0.f,
			96.f, 70.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightAlert", 0.f, 0.f,
			95.f, 69.f);

		GetSceneResource()->AddAnimationFramePivot("PlayerRightAlert", 0.22f, 0.985f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightAlert", 0.2f, 0.985f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightAlert", 0.2f, 0.985f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightAlert", 0.2f, 0.985f);

		GetSceneResource()->SetColorKey("PlayerRightAlert", 255, 0, 255);
	}
	


	// 플레이어 왼쪽 멈춤
	vecFileName.clear();

	for (int i = 0; i < 4; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Player/Left/stand_%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PlayerLeftStand"))
	{
		GetSceneResource()->CreateAnimationSequence("PlayerLeftStand",
			"PlayerLeftStand", vecFileName, TEXTURE_PATH);

		for (int i = 0; i < 3; ++i)
		{
			GetSceneResource()->AddAnimationFrame("PlayerLeftStand", 0.f, 0.f,
				57.f, 75.f);
		}

		GetSceneResource()->AddAnimationFramePivot("PlayerLeftStand", 0.55f, 0.93f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftStand", 0.53f, 0.93f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftStand", 0.51f, 0.93f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftStand", 0.53f, 0.93f);

		GetSceneResource()->SetColorKey("PlayerLeftStand", 255, 0, 255);
	}

	


	// 플레이어 왼쪽 걷기
	vecFileName.clear();

	for (int i = 0; i < 4; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Player/Left/walk_%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PlayerLeftWalk"))
	{
		GetSceneResource()->CreateAnimationSequence("PlayerLeftWalk",
			"PlayerLeftWalk", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("PlayerLeftWalk", 0.f, 0.f,
			88.f, 71.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftWalk", 0.f, 0.f,
			90.f, 70.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftWalk", 0.f, 0.f,
			85.f, 71.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftWalk", 0.f, 0.f,
			81.f, 73.f);

		GetSceneResource()->AddAnimationFramePivot("PlayerLeftWalk", 0.73f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftWalk", 0.77f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftWalk", 0.753f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftWalk", 0.73f, 0.945f);

		GetSceneResource()->SetColorKey("PlayerLeftWalk", 255, 0, 255);
	}

	
	// 플레이어 왼쪽 기본공격1
	std::vector<std::wstring>	vecFileName5;

	for (int i = 0; i < 6; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Player/Left/swing1_%d.bmp"), i);

		vecFileName5.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PlayerLeftAttack1"))
	{
		GetSceneResource()->CreateAnimationSequence("PlayerLeftAttack1",
			"PlayerLeftAttack1", vecFileName5, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("PlayerLeftAttack1", 0.f, 0.f,
			108.f, 71.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftAttack1", 0.f, 0.f,
			108.f, 71.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftAttack1", 0.f, 0.f,
			55.f, 100.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftAttack1", 0.f, 0.f,
			110.f, 80.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftAttack1", 0.f, 0.f,
			110.f, 80.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftAttack1", 0.f, 0.f,
			110.f, 80.f);

		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAttack1", 0.3, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAttack1", 0.3, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAttack1", 0.75f, 0.99f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAttack1", 0.93f, 0.787f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAttack1", 0.93f, 0.787f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAttack1", 0.93f, 0.787f);

		GetSceneResource()->SetColorKey("PlayerLeftAttack1", 255, 0, 255);
	}

	


	// 플레이어 왼쪽 기본공격2
	std::vector<std::wstring>	vecFileName_swingL2;

	for (int i = 0; i < 6; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Player/Left/swing2_%d.bmp"), i);

		vecFileName_swingL2.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PlayerLeftAttack2"))
	{
		GetSceneResource()->CreateAnimationSequence("PlayerLeftAttack2",
			"PlayerLeftAttack2", vecFileName_swingL2, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("PlayerLeftAttack2", 0.f, 0.f,
			94.f, 69.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftAttack2", 0.f, 0.f,
			94.f, 69.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftAttack2", 0.f, 0.f,
			59.f, 98.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftAttack2", 0.f, 0.f,
			90.f, 76.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftAttack2", 0.f, 0.f,
			90.f, 76.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftAttack2", 0.f, 0.f,
			90.f, 76.f);

		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAttack2", 0.28f, 0.985f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAttack2", 0.28f, 0.985f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAttack2", 0.78f, 0.99f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAttack2", 0.87f, 0.815f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAttack2", 0.87f, 0.815f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAttack2", 0.87f, 0.815f);

		GetSceneResource()->SetColorKey("PlayerLeftAttack2", 255, 0, 255);
	}
	
	

	// 플레이어 왼쪽 기본공격3
	std::vector<std::wstring>	vecFileName_Lswing3;

	for (int i = 0; i < 6; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Player/Left/swing3_%d.bmp"), i);

		vecFileName_Lswing3.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PlayerLeftAttack3"))
	{
		GetSceneResource()->CreateAnimationSequence("PlayerLeftAttack3",
			"PlayerLeftAttack3", vecFileName_Lswing3, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("PlayerLeftAttack3", 0.f, 0.f,
			112.f, 69.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftAttack3", 0.f, 0.f,
			112.f, 69.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftAttack3", 0.f, 0.f,
			110.f, 73.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftAttack3", 0.f, 0.f,
			75.f, 97.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftAttack3", 0.f, 0.f,
			75.f, 97.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftAttack3", 0.f, 0.f,
			75.f, 97.f);

		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAttack3", 0.373f, 0.985f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAttack3", 0.373f, 0.985f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAttack3", 0.48f, 0.85f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAttack3", 0.9f, 0.99f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAttack3", 0.9f, 0.99f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAttack3", 0.9f, 0.99f);

		GetSceneResource()->SetColorKey("PlayerLeftAttack3", 255, 0, 255);
	}


	// 플레이어 왼쪽 기본공격4
	std::vector<std::wstring>	vecFileName_Lstab;

	for (int i = 0; i < 6; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Player/Left/stab_%d.bmp"), i);

		vecFileName_Lstab.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PlayerLeftAttack4"))
	{
		GetSceneResource()->CreateAnimationSequence("PlayerLeftAttack4",
			"PlayerLeftAttack4", vecFileName_Lstab, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("PlayerLeftAttack4", 0.f, 0.f,
			85.f, 68.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftAttack4", 0.f, 0.f,
			86.f, 71.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftAttack4", 0.f, 0.f,
			86.f, 71.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftAttack4", 0.f, 0.f,
			122.f, 65.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftAttack4", 0.f, 0.f,
			122.f, 65.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftAttack4", 0.f, 0.f,
			122.f, 65.f);

		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAttack4", 0.73f, 0.985f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAttack4", 0.76f, 0.985f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAttack4", 0.76f, 0.985f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAttack4", 0.97f, 0.985f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAttack4", 0.97f, 0.985f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAttack4", 0.97f, 0.985f);

		GetSceneResource()->SetColorKey("PlayerLeftAttack4", 255, 0, 255);
	}

	


	// 플레이어 오른쪽 경계상태
	std::vector<std::wstring>	vecFileName_Lalert;

	for (int i = 0; i < 4; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Player/Left/alert_%d.bmp"), i);

		vecFileName_Lalert.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PlayerLeftAlert"))
	{
		GetSceneResource()->CreateAnimationSequence("PlayerLeftAlert",
			"PlayerLeftAlert", vecFileName_Lalert, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("PlayerLeftAlert", 0.f, 0.f,
			96.f, 68.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftAlert", 0.f, 0.f,
			95.f, 69.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftAlert", 0.f, 0.f,
			96.f, 70.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftAlert", 0.f, 0.f,
			95.f, 69.f);

		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAlert", 0.78f, 0.985f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAlert", 0.8f, 0.985f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAlert", 0.8f, 0.985f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftAlert", 0.8f, 0.985f);

		GetSceneResource()->SetColorKey("PlayerLeftAlert", 255, 0, 255);
	}
	
	//GetSceneResource()->CreateAnimationSequence("SlashBlastHit",
	//	"SlashBlastHit", vecFileName, TEXTURE_PATH);

	//GetSceneResource()->AddAnimationFrame("SlashBlastHit", 0.f, 0.f,
	//	101.f, 93.f);
	//GetSceneResource()->AddAnimationFrame("SlashBlastHit", 0.f, 0.f,
	//	125.f, 90.f);
	//GetSceneResource()->AddAnimationFrame("SlashBlastHit", 0.f, 0.f,
	//	120.f, 86.f);
	//GetSceneResource()->AddAnimationFrame("SlashBlastHit", 0.f, 0.f,
	//	88.f, 56.f);
	//
	//GetSceneResource()->AddAnimationFramePivot("SlashBlastHit", 0.53f, 0.69f);
	//GetSceneResource()->AddAnimationFramePivot("SlashBlastHit", 0.46f, 0.82f);
	//GetSceneResource()->AddAnimationFramePivot("SlashBlastHit", 0.46f, 0.82f);
	//GetSceneResource()->AddAnimationFramePivot("SlashBlastHit", 0.36f, 0.96f);
	//
	//GetSceneResource()->SetColorKey("SlashBlastHit", 255, 0, 255);


	//// 씬리소스를 통해 애니메이션 시퀀스를 생성한다.
	//// Right/astand.bmp : 오른쪽 정지상태 애니메이션
	//GetSceneResource()->CreateAnimationSequence("PlayerRightIdle",
	//	"PlayerRightIdle", TEXT("Player/Right/astand.bmp"), TEXTURE_PATH);

	//// astand.bmp을 6조각으로 나눈 프레임 이미지의 좌표정보를 추가한다.
	//for (int i = 0; i < 6; ++i)
	//{
	//	GetSceneResource()->AddAnimationFrame("PlayerRightIdle", 82.f * i, 0.f,
	//		82.f, 73.f);
	//}

	//// astand.bmp의 컬러키를 지정한다.
	//GetSceneResource()->SetColorKey("PlayerRightIdle", 255, 0, 255);


	//// 씬리소스를 통해 애니메이션 시퀀스를 생성한다.
	//// Right/awalk.bmp : 오른쪽 걷기 애니메이션
	//GetSceneResource()->CreateAnimationSequence("PlayerRightWalk",
	//	"PlayerRightWalk", TEXT("Player/Right/awalk.bmp"), TEXTURE_PATH);

	//// awalk.bmp을 4조각으로 나눈 프레임 이미지의 좌표정보를 추가한다.
	//for (int i = 0; i < 4; ++i)
	//{
	//	GetSceneResource()->AddAnimationFrame("PlayerRightWalk", 85.f * i, 0.f,
	//		85.f, 75.f);
	//}

	//// awalk.bmp의 컬러키를 지정한다.
	//GetSceneResource()->SetColorKey("PlayerRightWalk", 255, 0, 255);


	//// 씬리소스를 통해 애니메이션 시퀀스를 생성한다.
	//// Right/aswing.bmp : 오른쪽 공격 애니메이션
	//GetSceneResource()->CreateAnimationSequence("PlayerRightAttack",
	//	"PlayerRightAttack", TEXT("Player/Right/aswing.bmp"), TEXTURE_PATH);

	//// aswing.bmp을 3조각으로 나눈 프레임 이미지의 좌표정보를 추가한다.
	//for (int i = 0; i < 3; ++i)
	//{
	//	GetSceneResource()->AddAnimationFrame("PlayerRightAttack", 176.f * i, 0.f,
	//		176.f, 89.f);
	//}

	//// aswing.bmp의 컬러키를 지정한다.
	//GetSceneResource()->SetColorKey("PlayerRightAttack", 255, 0, 255);

	//// 씬리소스를 통해 애니메이션 시퀀스를 생성한다.
	//// Left/astand_left.bmp : 왼쪽 정지상태 애니메이션
	//GetSceneResource()->CreateAnimationSequence("PlayerLeftIdle",
	//	"PlayerLeftIdle", TEXT("Player/Left/astand_left.bmp"), TEXTURE_PATH);

	//// astand_left.bmp을 6조각으로 나눈 프레임 이미지의 좌표정보를 추가한다.
	//for (int i = 0; i < 6; ++i)
	//{
	//	GetSceneResource()->AddAnimationFrame("PlayerLeftIdle", 82.f * i, 0.f,
	//		82.f, 73.f);
	//}

	//// astand_left.bmp의 컬러키를 지정한다.
	//GetSceneResource()->SetColorKey("PlayerLeftIdle", 255, 0, 255);


	//// 씬리소스를 통해 애니메이션 시퀀스를 생성한다.
	//// Left/awalk_left.bmp : 왼쪽 걷기 애니메이션
	//GetSceneResource()->CreateAnimationSequence("PlayerLeftWalk",
	//	"PlayerLeftWalk", TEXT("Player/Left/awalk_left.bmp"), TEXTURE_PATH);

	//// awalk_left.bmp을 4조각으로 나눈 프레임 이미지의 좌표정보를 추가한다.
	//for (int i = 0; i < 4; ++i)
	//{
	//	GetSceneResource()->AddAnimationFrame("PlayerLeftWalk", 85.f * i, 0.f,
	//		85.f, 75.f);

	//}

	//// awalk_left.bmp의 컬러키를 지정한다.
	//GetSceneResource()->SetColorKey("PlayerLeftWalk", 255, 0, 255);


	//// 씬리소스를 통해 애니메이션 시퀀스를 생성한다.
	//// Left/aswing_left.bmp : 왼쪽 공격 애니메이션
	//GetSceneResource()->CreateAnimationSequence("PlayerLeftAttack",
	//	"PlayerLeftAttack", TEXT("Player/Left/aswing_left.bmp"), TEXTURE_PATH);

	//// aswing_left.bmp을 3조각으로 나눈 프레임 이미지의 좌표정보를 추가한다.
	//for (int i = 0; i < 3; ++i)
	//{
	//	GetSceneResource()->AddAnimationFrame("PlayerLeftAttack", 176.f * i, 0.f,
	//		176.f, 89.f);
	//}

	//// aswing_left.bmp의 컬러키를 지정한다.
	//GetSceneResource()->SetColorKey("PlayerLeftAttack", 255, 0, 255);
	//

	//// 씬리소스를 통해 애니메이션 시퀀스를 생성한다.
	//// Hit.bmp : 왼쪽 히트 이펙트 애니메이션
	//GetSceneResource()->CreateAnimationSequence("LeftHitEffect",
	//	"LeftHitEffect", TEXT("Hit.bmp"), TEXTURE_PATH);

	//// Hit.bmp을 6조각으로 나눈 프레임 이미지의 좌표정보를 추가한다.
	//for (int i = 0; i < 6; ++i)
	//{
	//	GetSceneResource()->AddAnimationFrame("LeftHitEffect", 178.f * i, 0.f,
	//		178.f, 164.f);
	//}

	//// Hit.bmp의 컬러키를 지정한다.
	//GetSceneResource()->SetColorKey("LeftHitEffect", 255, 0, 255);

}

void CMainScene::CreateAnimationSequence1()
{
	std::vector<std::wstring>	vecFileName;

	// 왼쪽 점프 이펙트
	vecFileName.clear();
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Player/Left/jump.bmp"));

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PlayerLeftJump"))
	{
		GetSceneResource()->CreateAnimationSequence("PlayerLeftJump",
			"PlayerLeftJump", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("PlayerLeftJump", 0.f, 0.f,
			67.f, 90.f);

		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJump", 0.41f, 1.f);

		GetSceneResource()->SetColorKey("PlayerLeftJump", 255, 0, 255);
	}



	// 오른쪽 점프 이펙트
	vecFileName.clear();
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Player/Right/jump.bmp"));

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PlayerRightJump"))
	{
		GetSceneResource()->CreateAnimationSequence("PlayerRightJump",
			"PlayerRightJump", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("PlayerRightJump", 0.f, 0.f,
			67.f, 90.f);

		GetSceneResource()->AddAnimationFramePivot("PlayerRightJump", 0.59f, 1.f);

		GetSceneResource()->SetColorKey("PlayerRightJump", 255, 0, 255);
	}



	// 로프 타기
	vecFileName.clear();
	for (int i = 0; i < 2; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Player/rope.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PlayerRope"))
	{
		GetSceneResource()->CreateAnimationSequence("PlayerRope",
			"PlayerRope", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("PlayerRope", 0.f, 0.f,
			57.f, 80.f);
		GetSceneResource()->AddAnimationFrame("PlayerRope", 0.f, 0.f,
			57.f, 81.f);

		GetSceneResource()->AddAnimationFramePivot("PlayerRope", 0.5f, 0.83f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRope", 0.5f, 0.83f);

		GetSceneResource()->SetColorKey("PlayerRope", 255, 0, 255);
	}



	// 로프 정지
	vecFileName.clear();

	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Player/rope.0.bmp"));

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PlayerRopeStand"))
	{
		GetSceneResource()->CreateAnimationSequence("PlayerRopeStand",
			"PlayerRopeStand", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("PlayerRopeStand", 0.f, 0.f,
			57.f, 80.f);

		GetSceneResource()->AddAnimationFramePivot("PlayerRopeStand", 0.5f, 0.83f);


		GetSceneResource()->SetColorKey("PlayerRopeStand", 255, 0, 255);
	}



	// 줄 타기
	vecFileName.clear();
	for (int i = 0; i < 2; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Player/ladder.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PlayerLadder"))
	{
		GetSceneResource()->CreateAnimationSequence("PlayerLadder",
			"PlayerLadder", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("PlayerLadder", 0.f, 0.f,
			57.f, 77.f);
		GetSceneResource()->AddAnimationFrame("PlayerLadder", 0.f, 0.f,
			57.f, 77.f);

		GetSceneResource()->AddAnimationFramePivot("PlayerLadder", 0.5f, 0.87f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLadder", 0.5f, 0.87f);

		GetSceneResource()->SetColorKey("PlayerLadder", 255, 0, 255);
	}



	// 줄 정지
	vecFileName.clear();

	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Player/ladder.0.bmp"));

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PlayerLadderStand"))
	{
		GetSceneResource()->CreateAnimationSequence("PlayerLadderStand",
			"PlayerLadderStand", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("PlayerLadderStand", 0.f, 0.f,
			57.f, 77.f);

		GetSceneResource()->AddAnimationFramePivot("PlayerLadderStand", 0.5f, 0.87f);

		GetSceneResource()->SetColorKey("PlayerLadderStand", 255, 0, 255);
	}



	// 오른쪽 저지먼트 모션
	vecFileName.clear();
	for (int i = 1; i <= 4; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Player/Right/Judgement/%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PlayerRightJudgement"))
	{
		GetSceneResource()->CreateAnimationSequence("PlayerRightJudgement",
			"PlayerRightJudgement", vecFileName, TEXTURE_PATH);

		/*GetSceneResource()->AddAnimationFrame("PlayerRightJudgement", 0.f, 0.f,
			110.f, 73.f);*/
		GetSceneResource()->AddAnimationFrame("PlayerRightJudgement", 0.f, 0.f,
			122.f, 64.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJudgement", 0.f, 0.f,
			60.f, 99.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJudgement", 0.f, 0.f,
			75.f, 97.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJudgement", 0.f, 0.f,
			122.f, 64.f);

		GetSceneResource()->AddAnimationFramePivot("PlayerRightJudgement", 0.85f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJudgement", 0.61f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJudgement", 0.26f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJudgement", 0.13f, 1.f);

		GetSceneResource()->SetColorKey("PlayerRightJudgement", 255, 0, 255);
	}


	// 오른쪽 저스티스 동작
	vecFileName.clear();
	for (int i = 1; i <= 15; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Player/Right/Justice/%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PlayerRightJustice"))
	{
		GetSceneResource()->CreateAnimationSequence("PlayerRightJustice",
			"PlayerRightJustice", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("PlayerRightJustice", 0.f, 0.f,
			110.f, 80.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJustice", 0.f, 0.f,
			55.f, 100.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJustice", 0.f, 0.f,
			65.f, 109.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJustice", 0.f, 0.f,
			65.f, 109.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJustice", 0.f, 0.f,
			65.f, 109.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJustice", 0.f, 0.f,
			65.f, 109.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJustice", 0.f, 0.f,
			65.f, 109.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJustice", 0.f, 0.f,
			65.f, 109.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJustice", 0.f, 0.f,
			65.f, 109.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJustice", 0.f, 0.f,
			110.f, 73.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJustice", 0.f, 0.f,
			110.f, 73.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJustice", 0.f, 0.f,
			110.f, 73.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJustice", 0.f, 0.f,
			110.f, 73.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJustice", 0.f, 0.f,
			110.f, 73.f);
		GetSceneResource()->AddAnimationFrame("PlayerRightJustice", 0.f, 0.f,
			110.f, 73.f);

		GetSceneResource()->AddAnimationFramePivot("PlayerRightJustice", 0.18f, 0.8f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJustice", 0.38f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJustice", 0.44f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJustice", 0.44f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJustice", 0.44f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJustice", 0.44f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJustice", 0.44f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJustice", 0.44f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJustice", 0.44f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJustice", 0.645f, 0.84f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJustice", 0.645f, 0.84f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJustice", 0.645f, 0.84f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJustice", 0.645f, 0.84f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJustice", 0.645f, 0.84f);
		GetSceneResource()->AddAnimationFramePivot("PlayerRightJustice", 0.645f, 0.84f);

		GetSceneResource()->SetColorKey("PlayerRightJustice", 255, 0, 255);
	}



	// 왼쪽 저스티스 동작
	vecFileName.clear();
	for (int i = 1; i <= 15; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Player/Left/Justice/%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("PlayerLeftJustice"))
	{
		GetSceneResource()->CreateAnimationSequence("PlayerLeftJustice",
			"PlayerLeftJustice", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("PlayerLeftJustice", 0.f, 0.f,
			110.f, 80.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJustice", 0.f, 0.f,
			55.f, 100.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJustice", 0.f, 0.f,
			65.f, 109.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJustice", 0.f, 0.f,
			65.f, 109.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJustice", 0.f, 0.f,
			65.f, 109.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJustice", 0.f, 0.f,
			65.f, 109.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJustice", 0.f, 0.f,
			65.f, 109.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJustice", 0.f, 0.f,
			65.f, 109.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJustice", 0.f, 0.f,
			65.f, 109.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJustice", 0.f, 0.f,
			110.f, 73.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJustice", 0.f, 0.f,
			110.f, 73.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJustice", 0.f, 0.f,
			110.f, 73.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJustice", 0.f, 0.f,
			110.f, 73.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJustice", 0.f, 0.f,
			110.f, 73.f);
		GetSceneResource()->AddAnimationFrame("PlayerLeftJustice", 0.f, 0.f,
			110.f, 73.f);

		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJustice", 0.82f, 0.8f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJustice", 0.62f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJustice", 0.56f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJustice", 0.56f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJustice", 0.56f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJustice", 0.56f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJustice", 0.56f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJustice", 0.56f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJustice", 0.56f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJustice", 0.355f, 0.84f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJustice", 0.355f, 0.84f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJustice", 0.355f, 0.84f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJustice", 0.355f, 0.84f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJustice", 0.355f, 0.84f);
		GetSceneResource()->AddAnimationFramePivot("PlayerLeftJustice", 0.355f, 0.84f);

		GetSceneResource()->SetColorKey("PlayerLeftJustice", 255, 0, 255);
	}
}

void CMainScene::CreateAnimationSequence2()
{
	// 발록 왼쪽 정지상태 
	std::vector<std::wstring> vecFileName;

	for (int i = 0; i < 2; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Left/stand.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogLeftStand"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogLeftStand",
			"BallogLeftStand", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogLeftStand", 0.f, 0.f,
			160.f, 156.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftStand", 0.f, 0.f,
			160.f, 156.f);

		GetSceneResource()->AddAnimationFramePivot("BallogLeftStand", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftStand", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("BallogLeftStand", 255, 0, 255);
	}
	


	// 발록 왼쪽 사망 
	vecFileName.clear();

	for (int i = 0; i < 5; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Left/Die/die1.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogLeftDie"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogLeftDie",
			"BallogLeftDie", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogLeftDie", 0.f, 0.f,
			153.f, 158.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftDie", 0.f, 0.f,
			224.f, 158.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftDie", 0.f, 0.f,
			240.f, 120.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftDie", 0.f, 0.f,
			240.f, 120.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftDie", 0.f, 0.f,
			240.f, 120.f);

		GetSceneResource()->AddAnimationFramePivot("BallogLeftDie", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftDie", 0.5f, 0.987f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftDie", 0.55f, 0.841f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftDie", 0.55f, 0.841f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftDie", 0.55f, 0.841f);

		GetSceneResource()->SetColorKey("BallogLeftDie", 255, 0, 255);
	}
	


	// 발록 왼쪽 피격
	vecFileName.clear();

	TCHAR	fileName[MAX_PATH] = {};

	wsprintf(fileName, TEXT("Maple/Monster/Ballog/Left/Hit/hit1.0.bmp"));

	vecFileName.push_back(fileName);

	if (!GetSceneResource()->FindAnimation("BallogLeftHit"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogLeftHit",
			"BallogLeftHit", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogLeftHit", 0.f, 0.f,
			172.f, 160.f);

		GetSceneResource()->AddAnimationFramePivot("BallogLeftHit", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("BallogLeftHit", 255, 0, 255);
	}

	


	// 발록 왼쪽 걷기
	vecFileName.clear();

	for (int i = 0; i < 5; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Left/move.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogLeftWalk"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogLeftWalk",
			"BallogLeftWalk", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogLeftWalk", 0.f, 0.f,
			171.f, 162.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftWalk", 0.f, 0.f,
			158.f, 156.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftWalk", 0.f, 0.f,
			177.f, 166.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftWalk", 0.f, 0.f,
			169.f, 158.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftWalk", 0.f, 0.f,
			177.f, 170.f);

		GetSceneResource()->AddAnimationFramePivot("BallogLeftWalk", 0.43f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftWalk", 0.44f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftWalk", 0.39f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftWalk", 0.46f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftWalk", 0.4f, 1.f);

		GetSceneResource()->SetColorKey("BallogLeftWalk", 255, 0, 255);
	}
	


	// 발록 오른쪽 정지상태 
	vecFileName.clear();

	for (int i = 0; i < 2; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Right/stand.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogRightStand"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogRightStand",
			"BallogRightStand", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogRightStand", 0.f, 0.f,
			160.f, 156.f);
		GetSceneResource()->AddAnimationFrame("BallogRightStand", 0.f, 0.f,
			160.f, 156.f);

		GetSceneResource()->AddAnimationFramePivot("BallogRightStand", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightStand", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("BallogRightStand", 255, 0, 255);
	}
	


	// 발록 오른쪽 사망 
	vecFileName.clear();

	for (int i = 0; i < 5; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Right/Die/die1.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogRightDie"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogRightDie",
			"BallogRightDie", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogRightDie", 0.f, 0.f,
			153.f, 158.f);
		GetSceneResource()->AddAnimationFrame("BallogRightDie", 0.f, 0.f,
			224.f, 158.f);
		GetSceneResource()->AddAnimationFrame("BallogRightDie", 0.f, 0.f,
			240.f, 120.f);
		GetSceneResource()->AddAnimationFrame("BallogRightDie", 0.f, 0.f,
			240.f, 120.f);
		GetSceneResource()->AddAnimationFrame("BallogRightDie", 0.f, 0.f,
			240.f, 120.f);

		GetSceneResource()->AddAnimationFramePivot("BallogRightDie", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightDie", 0.5f, 0.987f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightDie", 0.45f, 0.841f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightDie", 0.45f, 0.841f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightDie", 0.45f, 0.841f);

		GetSceneResource()->SetColorKey("BallogRightDie", 255, 0, 255);
	}
	

	// 발록 오른쪽 피격
	vecFileName.clear();

	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Right/Hit/hit1.0.bmp"));

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogRightHit"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogRightHit",
			"BallogRightHit", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogRightHit", 0.f, 0.f,
			172.f, 160.f);

		GetSceneResource()->AddAnimationFramePivot("BallogRightHit", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("BallogRightHit", 255, 0, 255);
	}
	

	// 발록 오른쪽 걷기
	vecFileName.clear();

	for (int i = 0; i < 5; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Right/move.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogRightWalk"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogRightWalk",
			"BallogRightWalk", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogRightWalk", 0.f, 0.f,
			171.f, 162.f);
		GetSceneResource()->AddAnimationFrame("BallogRightWalk", 0.f, 0.f,
			158.f, 156.f);
		GetSceneResource()->AddAnimationFrame("BallogRightWalk", 0.f, 0.f,
			177.f, 166.f);
		GetSceneResource()->AddAnimationFrame("BallogRightWalk", 0.f, 0.f,
			169.f, 158.f);
		GetSceneResource()->AddAnimationFrame("BallogRightWalk", 0.f, 0.f,
			177.f, 170.f);

		GetSceneResource()->AddAnimationFramePivot("BallogRightWalk", 0.57f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightWalk", 0.56f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightWalk", 0.61f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightWalk", 0.54f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightWalk", 0.6f, 1.f);

		GetSceneResource()->SetColorKey("BallogRightWalk", 255, 0, 255);
	}
	


	// 발록 왼쪽 스킬3(손톱) 
	vecFileName.clear();

	for (int i = 0; i < 10; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Left/Attack3/attack3.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogLeftAttack3"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogLeftAttack3",
			"BallogLeftAttack3", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogLeftAttack3", 0.f, 0.f,
			176.f, 160.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack3", 0.f, 0.f,
			192.f, 161.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack3", 0.f, 0.f,
			191.f, 171.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack3", 0.f, 0.f,
			191.f, 171.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack3", 0.f, 0.f,
			191.f, 171.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack3", 0.f, 0.f,
			202.f, 159.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack3", 0.f, 0.f,
			202.f, 159.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack3", 0.f, 0.f,
			202.f, 159.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack3", 0.f, 0.f,
			202.f, 159.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack3", 0.f, 0.f,
			202.f, 159.f);


		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack3", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack3", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack3", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack3", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack3", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack3", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack3", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack3", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack3", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack3", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("BallogLeftAttack3", 255, 0, 255);
	}
	


	// 발록 왼쪽 스킬3 발동 이펙트 
	vecFileName.clear();

	for (int i = 0; i < 4; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Left/Attack3/attack3.effect.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogLeftAttack3Effect"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogLeftAttack3Effect",
			"BallogLeftAttack3Effect", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogLeftAttack3Effect", 0.f, 0.f,
			243.f, 112.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack3Effect", 0.f, 0.f,
			243.f, 112.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack3Effect", 0.f, 0.f,
			243.f, 111.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack3Effect", 0.f, 0.f,
			240.f, 110.f);

		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack3Effect", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack3Effect", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack3Effect", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack3Effect", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("BallogLeftAttack3Effect", 255, 0, 255);
	}

	
	// 발록 왼쪽 스킬3 히트 이펙트 
	vecFileName.clear();

	for (int i = 0; i < 5; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Left/Attack3/attack3.info.hit.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogLeftAttack3Hit"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogLeftAttack3Hit",
			"BallogLeftAttack3Hit", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogLeftAttack3Hit", 0.f, 0.f,
			78.f, 72.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack3Hit", 0.f, 0.f,
			77.f, 78.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack3Hit", 0.f, 0.f,
			83.f, 94.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack3Hit", 0.f, 0.f,
			77.f, 78.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack3Hit", 0.f, 0.f,
			77.f, 78.f);

		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack3Hit", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack3Hit", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack3Hit", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack3Hit", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack3Hit", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("BallogLeftAttack3Hit", 255, 0, 255);
	}
	


	// 발록 왼쪽 스킬1(메테오) 
	vecFileName.clear();

	for (int i = 0; i < 18; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Left/Attack1/attack1.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogLeftAttack1"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogLeftAttack1",
			"BallogLeftAttack1", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1", 0.f, 0.f,
			176.f, 160.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1", 0.f, 0.f,
			160.f, 156.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1", 0.f, 0.f,
			160.f, 156.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1", 0.f, 0.f,
			246.f, 193.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1", 0.f, 0.f,
			243.f, 193.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1", 0.f, 0.f,
			243.f, 193.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1", 0.f, 0.f,
			243.f, 193.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1", 0.f, 0.f,
			243.f, 193.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1", 0.f, 0.f,
			243.f, 193.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1", 0.f, 0.f,
			503.f, 179.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1", 0.f, 0.f,
			503.f, 179.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1", 0.f, 0.f,
			503.f, 179.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1", 0.f, 0.f,
			503.f, 179.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1", 0.f, 0.f,
			503.f, 179.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1", 0.f, 0.f,
			503.f, 179.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1", 0.f, 0.f,
			503.f, 179.f);
		/*GetSceneResource()->AddAnimationFrame("BallogLeftAttack1", 0.f, 0.f,
			246.f, 193.f);*/
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1", 0.f, 0.f,
			160.f, 156.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1", 0.f, 0.f,
			160.f, 156.f);

		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1", 0.43f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1", 0.48f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1", 0.48f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1", 0.31f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1", 0.30f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1", 0.30f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1", 0.30f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1", 0.30f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1", 0.30f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1", 0.39f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1", 0.39f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1", 0.39f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1", 0.39f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1", 0.39f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1", 0.39f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1", 0.39f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1", 0.3f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1", 0.47f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1", 0.47f, 1.f);

		GetSceneResource()->SetColorKey("BallogLeftAttack1", 255, 0, 255);
	}
	


	// 발록 왼쪽 스킬1 발동 이펙트 
	vecFileName.clear();

	for (int i = 0; i < 8; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Left/Attack1/attack1.info.effect.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogLeftAttack1Effect"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogLeftAttack1Effect",
			"BallogLeftAttack1Effect", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1Effect", 0.f, 0.f,
			25.f, 28.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1Effect", 0.f, 0.f,
			25.f, 30.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1Effect", 0.f, 0.f,
			104.f, 100.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1Effect", 0.f, 0.f,
			106.f, 102.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1Effect", 0.f, 0.f,
			114.f, 111.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1Effect", 0.f, 0.f,
			114.f, 111.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1Effect", 0.f, 0.f,
			114.f, 111.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1Effect", 0.f, 0.f,
			114.f, 111.f);

		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1Effect", 0.48f, 0.2f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1Effect", 0.48f, 0.2f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1Effect", 0.48f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1Effect", 0.48f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1Effect", 0.48f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1Effect", 0.48f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1Effect", 0.48f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1Effect", 0.48f, 0.5f);

		GetSceneResource()->SetColorKey("BallogLeftAttack1Effect", 255, 0, 255);
	}
	


	// 발록 왼쪽 스킬1 히트 이펙트 
	vecFileName.clear();

	for (int i = 0; i < 13; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Left/Attack1/attack1.info.hit.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogLeftAttack1Hit"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogLeftAttack1Hit",
			"BallogLeftAttack1Hit", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1Hit", 0.f, 0.f,
			113.f, 114.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1Hit", 0.f, 0.f,
			141.f, 126.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1Hit", 0.f, 0.f,
			141.f, 126.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1Hit", 0.f, 0.f,
			140.f, 13.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1Hit", 0.f, 0.f,
			140.f, 133.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1Hit", 0.f, 0.f,
			131.f, 131.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1Hit", 0.f, 0.f,
			131.f, 131.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1Hit", 0.f, 0.f,
			59.f, 123.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1Hit", 0.f, 0.f,
			59.f, 123.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1Hit", 0.f, 0.f,
			57.f, 123.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1Hit", 0.f, 0.f,
			57.f, 123.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1Hit", 0.f, 0.f,
			44.f, 121.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack1Hit", 0.f, 0.f,
			44.f, 121.f);

		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1Hit", -1.f, 2.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1Hit", 0.2f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1Hit", 0.2f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1Hit", 0.22f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1Hit", 0.22f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1Hit", 0.22f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1Hit", 0.22f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1Hit", 0.6f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1Hit", 0.6f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1Hit", 0.6f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1Hit", 0.6f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1Hit", 0.6f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack1Hit", 0.6f, 1.f);

		GetSceneResource()->SetColorKey("BallogLeftAttack1Hit", 255, 0, 255);
	}
	


	// 발록 왼쪽 스킬2(파이어볼) 
	vecFileName.clear();

	for (int i = 0; i < 10; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Left/Attack2/attack2.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogLeftAttack2"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogLeftAttack2",
			"BallogLeftAttack2", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogLeftAttack2", 0.f, 0.f,
			201.f, 159.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack2", 0.f, 0.f,
			201.f, 159.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack2", 0.f, 0.f,
			201.f, 159.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack2", 0.f, 0.f,
			201.f, 159.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack2", 0.f, 0.f,
			192.f, 161.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack2", 0.f, 0.f,
			191.f, 171.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack2", 0.f, 0.f,
			191.f, 171.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack2", 0.f, 0.f,
			191.f, 171.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack2", 0.f, 0.f,
			191.f, 171.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack2", 0.f, 0.f,
			193.f, 171.f);

		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack2", 0.47f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack2", 0.47f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack2", 0.47f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack2", 0.47f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack2", 0.47f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack2", 0.45f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack2", 0.45f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack2", 0.45f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack2", 0.45f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack2", 0.49f, 1.f);

		GetSceneResource()->SetColorKey("BallogLeftAttack2", 255, 0, 255);
	}
	


	// 발록 왼쪽 스킬2 발동 이펙트 
	vecFileName.clear();

	for (int i = 0; i < 4; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Left/Attack2/attack2.info.effect.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogLeftAttack2Effect"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogLeftAttack2Effect",
			"BallogLeftAttack2Effect", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogLeftAttack2Effect", 0.f, 0.f,
			158.f, 89.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack2Effect", 0.f, 0.f,
			87.f, 108.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack2Effect", 0.f, 0.f,
			96.f, 115.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack2Effect", 0.f, 0.f,
			99.f, 122.f);

		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack2Effect", 0.24f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack2Effect", 0.5f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack2Effect", 0.5f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack2Effect", 0.5f, 0.5f);

		GetSceneResource()->SetColorKey("BallogLeftAttack2Effect", 255, 0, 255);
	}
	


	// 발록 왼쪽 스킬2 히트 이펙트 
	vecFileName.clear();

	for (int i = 0; i < 4; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Left/Attack2/attack2.info.hit.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogLeftAttack2Hit"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogLeftAttack2Hit",
			"BallogLeftAttack2Hit", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogLeftAttack2Hit", 0.f, 0.f,
			100.f, 113.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack2Hit", 0.f, 0.f,
			100.f, 104.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack2Hit", 0.f, 0.f,
			103.f, 114.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftAttack2Hit", 0.f, 0.f,
			106.f, 90.f);

		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack2Hit", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack2Hit", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack2Hit", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftAttack2Hit", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("BallogLeftAttack2Hit", 255, 0, 255);
	}
	


	// 발록 오른쪽 스킬3(손톱) 
	vecFileName.clear();

	for (int i = 0; i < 10; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Right/Attack3/attack3.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogRightAttack3"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogRightAttack3",
			"BallogRightAttack3", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogRightAttack3", 0.f, 0.f,
			176.f, 160.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack3", 0.f, 0.f,
			192.f, 161.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack3", 0.f, 0.f,
			191.f, 171.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack3", 0.f, 0.f,
			191.f, 171.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack3", 0.f, 0.f,
			191.f, 171.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack3", 0.f, 0.f,
			202.f, 159.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack3", 0.f, 0.f,
			202.f, 159.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack3", 0.f, 0.f,
			202.f, 159.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack3", 0.f, 0.f,
			202.f, 159.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack3", 0.f, 0.f,
			202.f, 159.f);


		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack3", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack3", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack3", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack3", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack3", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack3", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack3", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack3", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack3", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack3", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("BallogRightAttack3", 255, 0, 255);
	}
	


	// 발록 오른쪽 스킬3 발동 이펙트 
	vecFileName.clear();

	for (int i = 0; i < 4; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Right/Attack3/attack3.effect.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogRightAttack3Effect"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogRightAttack3Effect",
			"BallogRightAttack3Effect", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogRightAttack3Effect", 0.f, 0.f,
			243.f, 112.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack3Effect", 0.f, 0.f,
			243.f, 112.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack3Effect", 0.f, 0.f,
			243.f, 111.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack3Effect", 0.f, 0.f,
			240.f, 110.f);

		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack3Effect", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack3Effect", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack3Effect", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack3Effect", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("BallogRightAttack3Effect", 255, 0, 255);
	}
	


	// 발록 오른쪽 스킬3 히트 이펙트 
	vecFileName.clear();

	for (int i = 0; i < 5; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Right/Attack3/attack3.info.hit.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogRightAttack3Hit"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogRightAttack3Hit",
			"BallogRightAttack3Hit", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogRightAttack3Hit", 0.f, 0.f,
			78.f, 72.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack3Hit", 0.f, 0.f,
			77.f, 78.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack3Hit", 0.f, 0.f,
			83.f, 94.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack3Hit", 0.f, 0.f,
			77.f, 78.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack3Hit", 0.f, 0.f,
			77.f, 78.f);

		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack3Hit", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack3Hit", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack3Hit", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack3Hit", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack3Hit", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("BallogRightAttack3Hit", 255, 0, 255);
	}
	


	// 발록 오른쪽 스킬1(메테오) 
	vecFileName.clear();

	for (int i = 0; i < 18; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Right/Attack1/attack1.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogRightAttack1"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogRightAttack1",
			"BallogRightAttack1", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogRightAttack1", 0.f, 0.f,
			176.f, 160.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1", 0.f, 0.f,
			160.f, 156.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1", 0.f, 0.f,
			160.f, 156.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1", 0.f, 0.f,
			246.f, 193.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1", 0.f, 0.f,
			243.f, 193.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1", 0.f, 0.f,
			243.f, 193.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1", 0.f, 0.f,
			243.f, 193.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1", 0.f, 0.f,
			243.f, 193.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1", 0.f, 0.f,
			243.f, 193.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1", 0.f, 0.f,
			503.f, 179.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1", 0.f, 0.f,
			503.f, 179.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1", 0.f, 0.f,
			503.f, 179.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1", 0.f, 0.f,
			503.f, 179.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1", 0.f, 0.f,
			503.f, 179.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1", 0.f, 0.f,
			503.f, 179.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1", 0.f, 0.f,
			503.f, 179.f);
		/*GetSceneResource()->AddAnimationFrame("BallogRightAttack1", 0.f, 0.f,
			246.f, 193.f);*/
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1", 0.f, 0.f,
			160.f, 156.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1", 0.f, 0.f,
			160.f, 156.f);


		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1", 0.57f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1", 0.52f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1", 0.52f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1", 0.69f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1", 0.70f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1", 0.70f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1", 0.70f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1", 0.70f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1", 0.70f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1", 0.61f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1", 0.61f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1", 0.61f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1", 0.61f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1", 0.61f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1", 0.61f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1", 0.61f, 1.f);
		// GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1", 0.7f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1", 0.53f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1", 0.53f, 1.f);

		GetSceneResource()->SetColorKey("BallogRightAttack1", 255, 0, 255);
	}
	


	// 발록 오른쪽 스킬1 발동 이펙트 
	vecFileName.clear();

	for (int i = 0; i < 8; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Right/Attack1/attack1.info.effect.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogRightAttack1Effect"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogRightAttack1Effect",
			"BallogRightAttack1Effect", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogRightAttack1Effect", 0.f, 0.f,
			25.f, 28.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1Effect", 0.f, 0.f,
			25.f, 30.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1Effect", 0.f, 0.f,
			104.f, 100.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1Effect", 0.f, 0.f,
			106.f, 102.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1Effect", 0.f, 0.f,
			114.f, 111.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1Effect", 0.f, 0.f,
			114.f, 111.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1Effect", 0.f, 0.f,
			114.f, 111.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1Effect", 0.f, 0.f,
			114.f, 111.f);

		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1Effect", 0.52f, 0.2f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1Effect", 0.52f, 0.2f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1Effect", 0.52f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1Effect", 0.52f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1Effect", 0.52f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1Effect", 0.52f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1Effect", 0.52f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1Effect", 0.52f, 0.5f);

		GetSceneResource()->SetColorKey("BallogRightAttack1Effect", 255, 0, 255);
	}
	


	// 발록 오른쪽 스킬1 히트 이펙트 
	vecFileName.clear();

	for (int i = 0; i < 13; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Right/Attack1/attack1.info.hit.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogRightAttack1Hit"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogRightAttack1Hit",
			"BallogRightAttack1Hit", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogRightAttack1Hit", 0.f, 0.f,
			113.f, 114.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1Hit", 0.f, 0.f,
			141.f, 126.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1Hit", 0.f, 0.f,
			141.f, 126.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1Hit", 0.f, 0.f,
			140.f, 13.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1Hit", 0.f, 0.f,
			140.f, 133.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1Hit", 0.f, 0.f,
			131.f, 131.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1Hit", 0.f, 0.f,
			131.f, 131.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1Hit", 0.f, 0.f,
			59.f, 123.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1Hit", 0.f, 0.f,
			59.f, 123.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1Hit", 0.f, 0.f,
			57.f, 123.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1Hit", 0.f, 0.f,
			57.f, 123.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1Hit", 0.f, 0.f,
			44.f, 121.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack1Hit", 0.f, 0.f,
			44.f, 121.f);

		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1Hit", 2.f, 2.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1Hit", 0.8f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1Hit", 0.8f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1Hit", 0.78f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1Hit", 0.78f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1Hit", 0.78f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1Hit", 0.78f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1Hit", 0.4f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1Hit", 0.4f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1Hit", 0.4f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1Hit", 0.4f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1Hit", 0.4f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack1Hit", 0.4f, 1.f);

		GetSceneResource()->SetColorKey("BallogRightAttack1Hit", 255, 0, 255);
	}
	


	// 발록 오른쪽 스킬2(파이어볼) 
	vecFileName.clear();

	for (int i = 0; i < 10; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Right/Attack2/attack2.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogRightAttack2"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogRightAttack2",
			"BallogRightAttack2", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogRightAttack2", 0.f, 0.f,
			201.f, 159.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack2", 0.f, 0.f,
			201.f, 159.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack2", 0.f, 0.f,
			201.f, 159.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack2", 0.f, 0.f,
			201.f, 159.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack2", 0.f, 0.f,
			192.f, 161.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack2", 0.f, 0.f,
			191.f, 171.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack2", 0.f, 0.f,
			191.f, 171.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack2", 0.f, 0.f,
			191.f, 171.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack2", 0.f, 0.f,
			191.f, 171.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack2", 0.f, 0.f,
			193.f, 171.f);

		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack2", 0.53f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack2", 0.53f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack2", 0.53f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack2", 0.53f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack2", 0.53f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack2", 0.55f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack2", 0.55f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack2", 0.55f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack2", 0.55f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack2", 0.51f, 1.f);

		GetSceneResource()->SetColorKey("BallogRightAttack2", 255, 0, 255);
	}
	


	// 발록 오른쪽 스킬2 발동 이펙트 
	vecFileName.clear();

	for (int i = 0; i < 4; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Right/Attack2/attack2.info.effect.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogRightAttack2Effect"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogRightAttack2Effect",
			"BallogRightAttack2Effect", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogRightAttack2Effect", 0.f, 0.f,
			158.f, 89.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack2Effect", 0.f, 0.f,
			87.f, 108.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack2Effect", 0.f, 0.f,
			96.f, 115.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack2Effect", 0.f, 0.f,
			99.f, 122.f);

		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack2Effect", 0.76f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack2Effect", 0.5f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack2Effect", 0.5f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack2Effect", 0.5f, 0.5f);

		GetSceneResource()->SetColorKey("BallogRightAttack2Effect", 255, 0, 255);
	}
	


	// 발록 오른쪽 스킬2 히트 이펙트 
	vecFileName.clear();

	for (int i = 0; i < 4; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Right/Attack2/attack2.info.hit.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogRightAttack2Hit"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogRightAttack2Hit",
			"BallogRightAttack2Hit", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogRightAttack2Hit", 0.f, 0.f,
			100.f, 113.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack2Hit", 0.f, 0.f,
			100.f, 104.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack2Hit", 0.f, 0.f,
			103.f, 114.f);
		GetSceneResource()->AddAnimationFrame("BallogRightAttack2Hit", 0.f, 0.f,
			106.f, 90.f);

		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack2Hit", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack2Hit", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack2Hit", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightAttack2Hit", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("BallogRightAttack2Hit", 255, 0, 255);
	}
	


	// 발록 왼쪽 파이어볼
	vecFileName.clear();

	for (int i = 0; i < 3; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Left/Attack2/attack2.info.ball.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogLeftFireBall"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogLeftFireBall",
			"BallogLeftFireBall", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogLeftFireBall", 0.f, 0.f,
			61.f, 32.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftFireBall", 0.f, 0.f,
			68.f, 33.f);
		GetSceneResource()->AddAnimationFrame("BallogLeftFireBall", 0.f, 0.f,
			59.f, 31.f);

		GetSceneResource()->AddAnimationFramePivot("BallogLeftFireBall", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftFireBall", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogLeftFireBall", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("BallogLeftFireBall", 255, 0, 255);
	}
	


	// 발록 오른쪽 파이어볼
	vecFileName.clear();

	for (int i = 0; i < 3; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/Ballog/Right/Attack2/attack2.info.ball.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("BallogRightFireBall"))
	{
		GetSceneResource()->CreateAnimationSequence("BallogRightFireBall",
			"BallogRightFireBall", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("BallogRightFireBall", 0.f, 0.f,
			61.f, 32.f);
		GetSceneResource()->AddAnimationFrame("BallogRightFireBall", 0.f, 0.f,
			68.f, 33.f);
		GetSceneResource()->AddAnimationFrame("BallogRightFireBall", 0.f, 0.f,
			59.f, 31.f);

		GetSceneResource()->AddAnimationFramePivot("BallogRightFireBall", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightFireBall", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("BallogRightFireBall", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("BallogRightFireBall", 255, 0, 255);
	}
	
}

void CMainScene::CreateAnimationSequence3()
{
	// 타우로마시스 왼쪽 정지상태 
	std::vector<std::wstring> vecFileName;

	for (int i = 0; i < 8; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/TauroMasis/Left/stand.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("TauroMasisLeftStand"))
	{
		GetSceneResource()->CreateAnimationSequence("TauroMasisLeftStand",
			"TauroMasisLeftStand", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("TauroMasisLeftStand", 0.f, 0.f,
			162.f, 120.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftStand", 0.f, 0.f,
			162.f, 120.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftStand", 0.f, 0.f,
			162.f, 120.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftStand", 0.f, 0.f,
			162.f, 120.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftStand", 0.f, 0.f,
			162.f, 120.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftStand", 0.f, 0.f,
			162.f, 120.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftStand", 0.f, 0.f,
			162.f, 120.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftStand", 0.f, 0.f,
			162.f, 120.f);

		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftStand", 0.7f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftStand", 0.7f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftStand", 0.7f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftStand", 0.7f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftStand", 0.7f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftStand", 0.7f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftStand", 0.7f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftStand", 0.7f, 1.f);

		GetSceneResource()->SetColorKey("TauroMasisLeftStand", 255, 0, 255);

	}
	

	// 타우로마시스 오른쪽 정지상태 
	vecFileName.clear();

	for (int i = 0; i < 8; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/TauroMasis/Right/stand.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("TauroMasisRightStand"))
	{
		GetSceneResource()->CreateAnimationSequence("TauroMasisRightStand",
			"TauroMasisRightStand", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("TauroMasisRightStand", 0.f, 0.f,
			162.f, 120.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightStand", 0.f, 0.f,
			162.f, 120.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightStand", 0.f, 0.f,
			162.f, 120.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightStand", 0.f, 0.f,
			162.f, 120.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightStand", 0.f, 0.f,
			162.f, 120.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightStand", 0.f, 0.f,
			162.f, 120.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightStand", 0.f, 0.f,
			162.f, 120.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightStand", 0.f, 0.f,
			162.f, 120.f);

		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightStand", 0.3f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightStand", 0.3f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightStand", 0.3f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightStand", 0.3f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightStand", 0.3f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightStand", 0.3f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightStand", 0.3f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightStand", 0.3f, 1.f);

		GetSceneResource()->SetColorKey("TauroMasisRightStand", 255, 0, 255);
	}
	


	// 타우로마시스 왼쪽 이동 
	vecFileName.clear();

	for (int i = 0; i < 6; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/TauroMasis/Left/move.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("TauroMasisLeftMove"))
	{
		GetSceneResource()->CreateAnimationSequence("TauroMasisLeftMove",
			"TauroMasisLeftMove", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("TauroMasisLeftMove", 0.f, 0.f,
			170.f, 115.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftMove", 0.f, 0.f,
			170.f, 112.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftMove", 0.f, 0.f,
			193.f, 115.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftMove", 0.f, 0.f,
			170.f, 116.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftMove", 0.f, 0.f,
			170.f, 112.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftMove", 0.f, 0.f,
			175.f, 115.f);

		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftMove", 0.6f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftMove", 0.6f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftMove", 0.6f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftMove", 0.6f, 0.96f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftMove", 0.6f, 0.98f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftMove", 0.6f, 1.f);

		GetSceneResource()->SetColorKey("TauroMasisLeftMove", 255, 0, 255);

	}
	


	// 타우로마시스 오른쪽 이동 
	vecFileName.clear();

	for (int i = 0; i < 6; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/TauroMasis/Right/move.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("TauroMasisRightMove"))
	{
		GetSceneResource()->CreateAnimationSequence("TauroMasisRightMove",
			"TauroMasisRightMove", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("TauroMasisRightMove", 0.f, 0.f,
			170.f, 115.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightMove", 0.f, 0.f,
			170.f, 112.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightMove", 0.f, 0.f,
			193.f, 115.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightMove", 0.f, 0.f,
			170.f, 116.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightMove", 0.f, 0.f,
			170.f, 112.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightMove", 0.f, 0.f,
			175.f, 115.f);

		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightMove", 0.4f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightMove", 0.4f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightMove", 0.4f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightMove", 0.4f, 0.96f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightMove", 0.4f, 0.98f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightMove", 0.4f, 1.f);

		GetSceneResource()->SetColorKey("TauroMasisRightMove", 255, 0, 255);
	}
	


	// 타우로마시스 왼쪽 피격
	vecFileName.clear();

	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/TauroMasis/Left/Hit/hit1.%d.bmp"),0);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("TauroMasisLeftHit"))
	{
		GetSceneResource()->CreateAnimationSequence("TauroMasisLeftHit",
			"TauroMasisLeftHit", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("TauroMasisLeftHit", 0.f, 0.f,
			172.f, 122.f);

		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftHit", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("TauroMasisLeftHit", 255, 0, 255);
	}
	


	// 타우로마시스 오른쪽 피격
	vecFileName.clear();

	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/TauroMasis/Right/Hit/hit1.%d.bmp"),0);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("TauroMasisRightHit"))
	{
		GetSceneResource()->CreateAnimationSequence("TauroMasisRightHit",
			"TauroMasisRightHit", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("TauroMasisRightHit", 0.f, 0.f,
			172.f, 122.f);

		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightHit", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("TauroMasisRightHit", 255, 0, 255);
	}
	


	// 타우로마시스 왼쪽 사망
	vecFileName.clear();

	for (int i = 0; i < 10; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/TauroMasis/Left/Die/die1.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("TauroMasisLeftDie"))
	{
		GetSceneResource()->CreateAnimationSequence("TauroMasisLeftDie",
			"TauroMasisLeftDie", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("TauroMasisLeftDie", 0.f, 0.f,
			162.f, 128.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftDie", 0.f, 0.f,
			172.f, 119.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftDie", 0.f, 0.f,
			172.f, 117.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftDie", 0.f, 0.f,
			179.f, 119.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftDie", 0.f, 0.f,
			179.f, 111.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftDie", 0.f, 0.f,
			189.f, 52.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftDie", 0.f, 0.f,
			189.f, 52.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftDie", 0.f, 0.f,
			189.f, 52.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftDie", 0.f, 0.f,
			189.f, 52.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftDie", 0.f, 0.f,
			189.f, 52.f);

		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftDie", 0.39f, 0.96f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftDie", 0.39f, 0.97f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftDie", 0.39f, 0.97f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftDie", 0.44f, 0.97f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftDie", 0.41f, 0.98f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftDie", 0.46f, 0.76f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftDie", 0.46f, 0.76f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftDie", 0.46f, 0.76f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftDie", 0.46f, 0.76f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftDie", 0.46f, 0.76f);

		GetSceneResource()->SetColorKey("TauroMasisLeftDie", 255, 0, 255);
	}



	// 타우로마시스 오른쪽 사망
	vecFileName.clear();

	for (int i = 0; i < 10; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/TauroMasis/Right/Die/die1.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("TauroMasisRightDie"))
	{
		GetSceneResource()->CreateAnimationSequence("TauroMasisRightDie",
			"TauroMasisRightDie", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("TauroMasisRightDie", 0.f, 0.f,
			162.f, 128.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightDie", 0.f, 0.f,
			172.f, 119.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightDie", 0.f, 0.f,
			172.f, 117.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightDie", 0.f, 0.f,
			179.f, 119.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightDie", 0.f, 0.f,
			179.f, 111.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightDie", 0.f, 0.f,
			189.f, 52.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightDie", 0.f, 0.f,
			189.f, 52.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightDie", 0.f, 0.f,
			189.f, 52.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightDie", 0.f, 0.f,
			189.f, 52.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightDie", 0.f, 0.f,
			189.f, 52.f);

		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightDie", 0.61f, 0.96f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightDie", 0.61f, 0.97f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightDie", 0.61f, 0.97f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightDie", 0.56f, 0.97f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightDie", 0.59f, 0.98f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightDie", 0.54f, 0.76f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightDie", 0.54f, 0.76f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightDie", 0.54f, 0.76f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightDie", 0.54f, 0.76f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightDie", 0.54f, 0.76f);

		GetSceneResource()->SetColorKey("TauroMasisRightDie", 255, 0, 255);
	}
	

	// 타우로마시스 왼쪽 공격1
	vecFileName.clear();

	for (int i = 1; i <= 6; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/TauroMasis/Left/Attack1/attack1.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("TauroMasisLeftAttack"))
	{
		GetSceneResource()->CreateAnimationSequence("TauroMasisLeftAttack",
			"TauroMasisLeftAttack", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("TauroMasisLeftAttack", 0.f, 0.f,
			165.f, 158.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftAttack", 0.f, 0.f,
			156.f, 235.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftAttack", 0.f, 0.f,
			140.f, 233.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftAttack", 0.f, 0.f,
			140.f, 220.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftAttack", 0.f, 0.f,
			143.f, 162.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftAttack", 0.f, 0.f,
			140.f, 158.f);

		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftAttack", 0.53f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftAttack", 0.57f, 0.93f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftAttack", 0.63f, 0.92f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftAttack", 0.63f, 0.93f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftAttack", 0.61f, 0.97f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftAttack", 0.63f, 1.f);

		GetSceneResource()->SetColorKey("TauroMasisLeftAttack", 255, 0, 255);
	}
	


	// 타우로마시스 오른쪽 공격1
	vecFileName.clear();

	for (int i = 1; i <= 6; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/TauroMasis/Right/Attack1/attack1.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("TauroMasisRightAttack"))
	{
		GetSceneResource()->CreateAnimationSequence("TauroMasisRightAttack",
			"TauroMasisRightAttack", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("TauroMasisRightAttack", 0.f, 0.f,
			165.f, 158.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightAttack", 0.f, 0.f,
			156.f, 235.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightAttack", 0.f, 0.f,
			140.f, 233.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightAttack", 0.f, 0.f,
			140.f, 220.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightAttack", 0.f, 0.f,
			143.f, 162.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightAttack", 0.f, 0.f,
			140.f, 158.f);

		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightAttack", 0.47f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightAttack", 0.43f, 0.93f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightAttack", 0.37f, 0.92f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightAttack", 0.37f, 0.93f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightAttack", 0.39f, 0.97f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightAttack", 0.37f, 1.f);

		GetSceneResource()->SetColorKey("TauroMasisRightAttack", 255, 0, 255);
	}
	


	// 타우로마시스 왼쪽 공격1 히트 이펙트
	vecFileName.clear();

	for (int i = 0; i < 3; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/TauroMasis/Left/Attack1/attack1.info.hit.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("TauroMasisLeftAttackHit"))
	{
		GetSceneResource()->CreateAnimationSequence("TauroMasisLeftAttackHit",
			"TauroMasisLeftAttackHit", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("TauroMasisLeftAttackHit", 0.f, 0.f,
			63.f, 235.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftAttackHit", 0.f, 0.f,
			60.f, 233.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisLeftAttackHit", 0.f, 0.f,
			39.f, 220.f);

		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftAttackHit", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftAttackHit", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisLeftAttackHit", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("TauroMasisLeftAttackHit", 255, 0, 255);
	}
	


	// 타우로마시스 오른쪽 공격1 히트 이펙트
	vecFileName.clear();

	for (int i = 0; i < 3; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/TauroMasis/Right/Attack1/attack1.info.hit.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("TauroMasisRightAttackHit"))
	{
		GetSceneResource()->CreateAnimationSequence("TauroMasisRightAttackHit",
			"TauroMasisRightAttackHit", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("TauroMasisRightAttackHit", 0.f, 0.f,
			63.f, 235.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightAttackHit", 0.f, 0.f,
			60.f, 233.f);
		GetSceneResource()->AddAnimationFrame("TauroMasisRightAttackHit", 0.f, 0.f,
			39.f, 220.f);

		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightAttackHit", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightAttackHit", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroMasisRightAttackHit", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("TauroMasisRightAttackHit", 255, 0, 255);
	}
	
}

void CMainScene::CreateAnimationSequence4()
{
	// 타우로스피어 왼쪽 정지상태 
	std::vector<std::wstring> vecFileName;

	for (int i = 0; i < 8; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/TauroSpear/Left/stand.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("TauroSpearLeftStand"))
	{
		GetSceneResource()->CreateAnimationSequence("TauroSpearLeftStand",
			"TauroSpearLeftStand", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("TauroSpearLeftStand", 0.f, 0.f,
			186.f, 122.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftStand", 0.f, 0.f,
			186.f, 122.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftStand", 0.f, 0.f,
			186.f, 122.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftStand", 0.f, 0.f,
			186.f, 122.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftStand", 0.f, 0.f,
			186.f, 122.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftStand", 0.f, 0.f,
			186.f, 122.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftStand", 0.f, 0.f,
			186.f, 122.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftStand", 0.f, 0.f,
			186.f, 122.f);

		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftStand", 0.74f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftStand", 0.74f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftStand", 0.74f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftStand", 0.74f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftStand", 0.74f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftStand", 0.74f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftStand", 0.74f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftStand", 0.74f, 1.f);

		GetSceneResource()->SetColorKey("TauroSpearLeftStand", 255, 0, 255);
	}
	


	// 타우로스피어 오른쪽 정지상태 
	vecFileName.clear();

	for (int i = 0; i < 8; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/TauroSpear/Right/stand.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("TauroSpearRightStand"))
	{
		GetSceneResource()->CreateAnimationSequence("TauroSpearRightStand",
			"TauroSpearRightStand", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("TauroSpearRightStand", 0.f, 0.f,
			186.f, 122.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightStand", 0.f, 0.f,
			186.f, 122.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightStand", 0.f, 0.f,
			186.f, 122.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightStand", 0.f, 0.f,
			186.f, 122.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightStand", 0.f, 0.f,
			186.f, 122.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightStand", 0.f, 0.f,
			186.f, 122.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightStand", 0.f, 0.f,
			186.f, 122.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightStand", 0.f, 0.f,
			186.f, 122.f);

		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightStand", 0.26f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightStand", 0.26f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightStand", 0.26f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightStand", 0.26f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightStand", 0.26f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightStand", 0.26f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightStand", 0.26f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightStand", 0.26f, 1.f);

		GetSceneResource()->SetColorKey("TauroSpearRightStand", 255, 0, 255);
	}
	


	// 타우로스피어 왼쪽 이동 
	vecFileName.clear();

	for (int i = 0; i < 6; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/TauroSpear/Left/move.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("TauroSpearLeftMove"))
	{
		GetSceneResource()->CreateAnimationSequence("TauroSpearLeftMove",
			"TauroSpearLeftMove", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("TauroSpearLeftMove", 0.f, 0.f,
			188.f, 124.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftMove", 0.f, 0.f,
			188.f, 121.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftMove", 0.f, 0.f,
			211.f, 124.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftMove", 0.f, 0.f,
			188.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftMove", 0.f, 0.f,
			188.f, 121.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftMove", 0.f, 0.f,
			211.f, 124.f);

		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftMove", 0.64f, 0.98f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftMove", 0.64f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftMove", 0.62f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftMove", 0.66f, 0.98f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftMove", 0.65f, 0.98f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftMove", 0.62f, 1.f);

		GetSceneResource()->SetColorKey("TauroSpearLeftMove", 255, 0, 255);
	}
	


	// 타우로스피어 오른쪽 이동 
	vecFileName.clear();

	for (int i = 0; i < 6; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/TauroSpear/Right/move.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("TauroSpearRightMove"))
	{
		GetSceneResource()->CreateAnimationSequence("TauroSpearRightMove",
			"TauroSpearRightMove", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("TauroSpearRightMove", 0.f, 0.f,
			188.f, 124.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightMove", 0.f, 0.f,
			188.f, 121.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightMove", 0.f, 0.f,
			211.f, 124.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightMove", 0.f, 0.f,
			188.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightMove", 0.f, 0.f,
			188.f, 121.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightMove", 0.f, 0.f,
			211.f, 124.f);

		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightMove", 0.36f, 0.98f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightMove", 0.36f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightMove", 0.38f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightMove", 0.34f, 0.98f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightMove", 0.35f, 0.98f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightMove", 0.38f, 1.f);

		GetSceneResource()->SetColorKey("TauroSpearRightMove", 255, 0, 255);
	}
	


	// 타우로스피어 왼쪽 피격
	vecFileName.clear();

	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/TauroSpear/Left/Hit/hit1.%d.bmp"), 0);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("TauroSpearLeftHit"))
	{
		GetSceneResource()->CreateAnimationSequence("TauroSpearLeftHit",
			"TauroSpearLeftHit", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("TauroSpearLeftHit", 0.f, 0.f,
			186.f, 116.f);

		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftHit", 0.62f, 1.f);

		GetSceneResource()->SetColorKey("TauroSpearLeftHit", 255, 0, 255);
	}
	


	// 타우로스피어 오른쪽 피격
	vecFileName.clear();

	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/TauroSpear/Right/Hit/hit1.%d.bmp"), 0);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("TauroSpearRightHit"))
	{
		GetSceneResource()->CreateAnimationSequence("TauroSpearRightHit",
			"TauroSpearRightHit", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("TauroSpearRightHit", 0.f, 0.f,
			186.f, 116.f);

		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightHit", 0.38f, 1.f);

		GetSceneResource()->SetColorKey("TauroSpearRightHit", 255, 0, 255);
	}
	


	// 타우로스피어 왼쪽 사망
	vecFileName.clear();

	for (int i = 0; i < 10; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/TauroSpear/Left/Die/die1.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("TauroSpearLeftDie"))
	{
		GetSceneResource()->CreateAnimationSequence("TauroSpearLeftDie",
			"TauroSpearLeftDie", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("TauroSpearLeftDie", 0.f, 0.f,
			186.f, 126.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftDie", 0.f, 0.f,
			186.f, 115.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftDie", 0.f, 0.f,
			186.f, 113.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftDie", 0.f, 0.f,
			189.f, 115.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftDie", 0.f, 0.f,
			189.f, 115.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftDie", 0.f, 0.f,
			201.f, 52.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftDie", 0.f, 0.f,
			201.f, 52.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftDie", 0.f, 0.f,
			201.f, 52.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftDie", 0.f, 0.f,
			201.f, 52.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftDie", 0.f, 0.f,
			201.f, 52.f);

		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftDie", 0.7f, 0.96f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftDie", 0.7f, 0.97f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftDie", 0.7f, 0.97f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftDie", 0.7f, 0.97f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftDie", 0.7f, 0.98f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftDie", 0.7f, 0.76f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftDie", 0.7f, 0.76f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftDie", 0.7f, 0.76f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftDie", 0.7f, 0.76f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftDie", 0.7f, 0.76f);

		GetSceneResource()->SetColorKey("TauroSpearLeftDie", 255, 0, 255);
	}
	


	// 타우로스피어 오른쪽 사망
	vecFileName.clear();

	for (int i = 0; i < 10; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/TauroSpear/Right/Die/die1.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("TauroSpearRightDie"))
	{
		GetSceneResource()->CreateAnimationSequence("TauroSpearRightDie",
			"TauroSpearRightDie", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("TauroSpearRightDie", 0.f, 0.f,
			186.f, 126.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightDie", 0.f, 0.f,
			186.f, 115.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightDie", 0.f, 0.f,
			186.f, 113.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightDie", 0.f, 0.f,
			189.f, 115.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightDie", 0.f, 0.f,
			189.f, 115.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightDie", 0.f, 0.f,
			201.f, 52.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightDie", 0.f, 0.f,
			201.f, 52.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightDie", 0.f, 0.f,
			201.f, 52.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightDie", 0.f, 0.f,
			201.f, 52.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightDie", 0.f, 0.f,
			201.f, 52.f);

		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightDie", 0.3f, 0.96f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightDie", 0.3f, 0.97f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightDie", 0.3f, 0.97f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightDie", 0.3f, 0.97f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightDie", 0.3f, 0.98f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightDie", 0.3f, 0.76f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightDie", 0.3f, 0.76f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightDie", 0.3f, 0.76f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightDie", 0.3f, 0.76f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightDie", 0.3f, 0.76f);

		GetSceneResource()->SetColorKey("TauroSpearRightDie", 255, 0, 255);
	}
	

	// 타우로스피어 왼쪽 공격1
	vecFileName.clear();

	for (int i = 0; i < 7; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/TauroSpear/Left/Attack1/attack1.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("TauroSpearLeftAttack1"))
	{
		GetSceneResource()->CreateAnimationSequence("TauroSpearLeftAttack1",
			"TauroSpearLeftAttack1", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("TauroSpearLeftAttack1", 0.f, 0.f,
			186.f, 161.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftAttack1", 0.f, 0.f,
			186.f, 161.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftAttack1", 0.f, 0.f,
			135.f, 229.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftAttack1", 0.f, 0.f,
			299.f, 246.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftAttack1", 0.f, 0.f,
			273.f, 228.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftAttack1", 0.f, 0.f,
			263.f, 104.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftAttack1", 0.f, 0.f,
			263.f, 104.f);

		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftAttack1", 0.28f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftAttack1", 0.28f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftAttack1", 0.25f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftAttack1", 0.7f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftAttack1", 0.73f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftAttack1", 0.73f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftAttack1", 0.73f, 1.f);

		GetSceneResource()->SetColorKey("TauroSpearLeftAttack1", 255, 0, 255);
	}
	


	// 타우로스피어 오른쪽 공격1
	vecFileName.clear();

	for (int i = 0; i < 7; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/TauroSpear/Right/Attack1/attack1.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("TauroSpearRightAttack1"))
	{
		GetSceneResource()->CreateAnimationSequence("TauroSpearRightAttack1",
			"TauroSpearRightAttack1", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("TauroSpearRightAttack1", 0.f, 0.f,
			186.f, 161.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightAttack1", 0.f, 0.f,
			186.f, 161.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightAttack1", 0.f, 0.f,
			135.f, 229.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightAttack1", 0.f, 0.f,
			299.f, 246.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightAttack1", 0.f, 0.f,
			273.f, 228.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightAttack1", 0.f, 0.f,
			263.f, 104.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightAttack1", 0.f, 0.f,
			263.f, 104.f);

		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightAttack1", 0.72f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightAttack1", 0.72f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightAttack1", 0.75f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightAttack1", 0.3f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightAttack1", 0.27f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightAttack1", 0.27f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightAttack1", 0.27f, 1.f);

		GetSceneResource()->SetColorKey("TauroSpearRightAttack1", 255, 0, 255);
	}
	


	// 타우로스피어 왼쪽 공격2
	vecFileName.clear();

	for (int i = 0; i < 17; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/TauroSpear/Left/Attack2/attack2.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("TauroSpearLeftAttack2"))
	{
		GetSceneResource()->CreateAnimationSequence("TauroSpearLeftAttack2",
			"TauroSpearLeftAttack2", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("TauroSpearLeftAttack2", 0.f, 0.f,
			189.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftAttack2", 0.f, 0.f,
			189.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftAttack2", 0.f, 0.f,
			189.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftAttack2", 0.f, 0.f,
			189.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftAttack2", 0.f, 0.f,
			323.f, 104.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftAttack2", 0.f, 0.f,
			309.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftAttack2", 0.f, 0.f,
			309.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftAttack2", 0.f, 0.f,
			304.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftAttack2", 0.f, 0.f,
			314.f, 104.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftAttack2", 0.f, 0.f,
			309.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftAttack2", 0.f, 0.f,
			309.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftAttack2", 0.f, 0.f,
			307.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftAttack2", 0.f, 0.f,
			328.f, 104.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftAttack2", 0.f, 0.f,
			313.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftAttack2", 0.f, 0.f,
			307.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftAttack2", 0.f, 0.f,
			307.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearLeftAttack2", 0.f, 0.f,
			307.f, 125.f);

		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftAttack2", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftAttack2", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftAttack2", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftAttack2", 0.48f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftAttack2", 0.78f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftAttack2", 0.69f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftAttack2", 0.69f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftAttack2", 0.67f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftAttack2", 0.77f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftAttack2", 0.69f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftAttack2", 0.69f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftAttack2", 0.66f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftAttack2", 0.78f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftAttack2", 0.69f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftAttack2", 0.68f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftAttack2", 0.68f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearLeftAttack2", 0.68f, 1.f);

		GetSceneResource()->SetColorKey("TauroSpearLeftAttack2", 255, 0, 255);
	}
	


	// 타우로스피어 오른쪽 공격2
	vecFileName.clear();

	for (int i = 0; i < 17; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/TauroSpear/Right/Attack2/attack2.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("TauroSpearRightAttack2"))
	{
		GetSceneResource()->CreateAnimationSequence("TauroSpearRightAttack2",
			"TauroSpearRightAttack2", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("TauroSpearRightAttack2", 0.f, 0.f,
			189.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightAttack2", 0.f, 0.f,
			189.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightAttack2", 0.f, 0.f,
			189.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightAttack2", 0.f, 0.f,
			189.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightAttack2", 0.f, 0.f,
			323.f, 104.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightAttack2", 0.f, 0.f,
			309.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightAttack2", 0.f, 0.f,
			309.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightAttack2", 0.f, 0.f,
			304.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightAttack2", 0.f, 0.f,
			314.f, 104.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightAttack2", 0.f, 0.f,
			309.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightAttack2", 0.f, 0.f,
			309.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightAttack2", 0.f, 0.f,
			307.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightAttack2", 0.f, 0.f,
			328.f, 104.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightAttack2", 0.f, 0.f,
			313.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightAttack2", 0.f, 0.f,
			307.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightAttack2", 0.f, 0.f,
			307.f, 125.f);
		GetSceneResource()->AddAnimationFrame("TauroSpearRightAttack2", 0.f, 0.f,
			307.f, 125.f);

		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightAttack2", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightAttack2", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightAttack2", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightAttack2", 0.52f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightAttack2", 0.22f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightAttack2", 0.31f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightAttack2", 0.31f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightAttack2", 0.33f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightAttack2", 0.23f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightAttack2", 0.31f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightAttack2", 0.31f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightAttack2", 0.34f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightAttack2", 0.22f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightAttack2", 0.31f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightAttack2", 0.32f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightAttack2", 0.32f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("TauroSpearRightAttack2", 0.32f, 1.f);

		GetSceneResource()->SetColorKey("TauroSpearRightAttack2", 255, 0, 255);
	}
	
}

void CMainScene::CreateAnimationSequence5()
{
	// 와일드카고 왼쪽 정지상태 
	std::vector<std::wstring> vecFileName;

	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/WildCargo/Left/stand.%d.bmp"), 0);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("WildCargoLeftStand"))
	{
		GetSceneResource()->CreateAnimationSequence("WildCargoLeftStand",
			"WildCargoLeftStand", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("WildCargoLeftStand", 0.f, 0.f,
			159.f, 91.f);

		GetSceneResource()->AddAnimationFramePivot("WildCargoLeftStand", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("WildCargoLeftStand", 255, 0, 255);
	}
	


	// 와일드카고 오른쪽 정지상태 
	vecFileName.clear();

	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/WildCargo/Right/stand.%d.bmp"), 0);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("WildCargoRightStand"))
	{
		GetSceneResource()->CreateAnimationSequence("WildCargoRightStand",
			"WildCargoRightStand", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("WildCargoRightStand", 0.f, 0.f,
			159.f, 91.f);

		GetSceneResource()->AddAnimationFramePivot("WildCargoRightStand", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("WildCargoRightStand", 255, 0, 255);
	}
	


	// 와일드카고 왼쪽 이동 
	vecFileName.clear();

	for (int i = 0; i < 5; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/WildCargo/Left/move.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("WildCargoLeftMove"))
	{
		GetSceneResource()->CreateAnimationSequence("WildCargoLeftMove",
			"WildCargoLeftMove", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("WildCargoLeftMove", 0.f, 0.f,
			166.f, 91.f);
		GetSceneResource()->AddAnimationFrame("WildCargoLeftMove", 0.f, 0.f,
			156.f, 91.f);
		GetSceneResource()->AddAnimationFrame("WildCargoLeftMove", 0.f, 0.f,
			147.f, 97.f);
		GetSceneResource()->AddAnimationFrame("WildCargoLeftMove", 0.f, 0.f,
			139.f, 94.f);
		GetSceneResource()->AddAnimationFrame("WildCargoLeftMove", 0.f, 0.f,
			151.f, 94.f);

		GetSceneResource()->AddAnimationFramePivot("WildCargoLeftMove", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("WildCargoLeftMove", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("WildCargoLeftMove", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("WildCargoLeftMove", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("WildCargoLeftMove", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("WildCargoLeftMove", 255, 0, 255);
	}
	


	// 와일드카고 오른쪽 이동 
	vecFileName.clear();

	for (int i = 0; i < 5; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/WildCargo/Right/move.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("WildCargoRightMove"))
	{
		GetSceneResource()->CreateAnimationSequence("WildCargoRightMove",
			"WildCargoRightMove", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("WildCargoRightMove", 0.f, 0.f,
			166.f, 91.f);
		GetSceneResource()->AddAnimationFrame("WildCargoRightMove", 0.f, 0.f,
			156.f, 91.f);
		GetSceneResource()->AddAnimationFrame("WildCargoRightMove", 0.f, 0.f,
			147.f, 97.f);
		GetSceneResource()->AddAnimationFrame("WildCargoRightMove", 0.f, 0.f,
			139.f, 94.f);
		GetSceneResource()->AddAnimationFrame("WildCargoRightMove", 0.f, 0.f,
			151.f, 94.f);

		GetSceneResource()->AddAnimationFramePivot("WildCargoRightMove", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("WildCargoRightMove", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("WildCargoRightMove", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("WildCargoRightMove", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("WildCargoRightMove", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("WildCargoRightMove", 255, 0, 255);
	}
	


	// 와일드카고 왼쪽 히트
	vecFileName.clear();
	{
		TCHAR	fileName[MAX_PATH] = {};
	
		wsprintf(fileName, TEXT("Maple/Monster/WildCargo/Left/Hit/hit1.%d.bmp"), 0);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("WildCargoLeftHit"))
	{
		GetSceneResource()->CreateAnimationSequence("WildCargoLeftHit",
			"WildCargoLeftHit", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("WildCargoLeftHit", 0.f, 0.f,
			116.f, 101.f);

		GetSceneResource()->AddAnimationFramePivot("WildCargoLeftHit", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("WildCargoLeftHit", 255, 0, 255);
	}
	


	// 와일드카고 오른쪽 히트
	vecFileName.clear();

	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/WildCargo/Right/Hit/hit1.%d.bmp"), 0);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("WildCargoRightHit"))
	{
		GetSceneResource()->CreateAnimationSequence("WildCargoRightHit",
			"WildCargoRightHit", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("WildCargoRightHit", 0.f, 0.f,
			116.f, 101.f);

		GetSceneResource()->AddAnimationFramePivot("WildCargoRightHit", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("WildCargoRightHit", 255, 0, 255);

	}
	

	// 와일드카고 왼쪽 사망
	vecFileName.clear();

	for (int i = 0; i < 5; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/WildCargo/Left/Die/die1.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("WildCargoLeftDie"))
	{
		GetSceneResource()->CreateAnimationSequence("WildCargoLeftDie",
			"WildCargoLeftDie", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("WildCargoLeftDie", 0.f, 0.f,
			162.f, 82.f);
		GetSceneResource()->AddAnimationFrame("WildCargoLeftDie", 0.f, 0.f,
			162.f, 82.f);
		GetSceneResource()->AddAnimationFrame("WildCargoLeftDie", 0.f, 0.f,
			162.f, 82.f);
		GetSceneResource()->AddAnimationFrame("WildCargoLeftDie", 0.f, 0.f,
			166.f, 86.f);
		GetSceneResource()->AddAnimationFrame("WildCargoLeftDie", 0.f, 0.f,
			166.f, 86.f);

		GetSceneResource()->AddAnimationFramePivot("WildCargoLeftDie", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("WildCargoLeftDie", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("WildCargoLeftDie", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("WildCargoLeftDie", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("WildCargoLeftDie", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("WildCargoLeftDie", 255, 0, 255);
	}
	


	// 와일드카고 오른쪽 사망
	vecFileName.clear();

	for (int i = 0; i < 5; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Monster/WildCargo/Right/Die/die1.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("WildCargoRightDie"))
	{
		GetSceneResource()->CreateAnimationSequence("WildCargoRightDie",
			"WildCargoRightDie", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("WildCargoRightDie", 0.f, 0.f,
			162.f, 82.f);
		GetSceneResource()->AddAnimationFrame("WildCargoRightDie", 0.f, 0.f,
			162.f, 82.f);
		GetSceneResource()->AddAnimationFrame("WildCargoRightDie", 0.f, 0.f,
			162.f, 82.f);
		GetSceneResource()->AddAnimationFrame("WildCargoRightDie", 0.f, 0.f,
			166.f, 86.f);
		GetSceneResource()->AddAnimationFrame("WildCargoRightDie", 0.f, 0.f,
			166.f, 86.f);

		GetSceneResource()->AddAnimationFramePivot("WildCargoRightDie", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("WildCargoRightDie", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("WildCargoRightDie", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("WildCargoRightDie", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("WildCargoRightDie", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("WildCargoRightDie", 255, 0, 255);
	}

}

void CMainScene::CreateAnimationSequence6()
{
	// 포탈
	std::vector<std::wstring> vecFileName;

	for (int i = 0; i < 14; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Portal/portal.game.pv.4.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("Portal"))
	{
		GetSceneResource()->CreateAnimationSequence("Portal",
			"Portal", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("Portal", 0.f, 0.f,
			127.f, 178.f);
		GetSceneResource()->AddAnimationFrame("Portal", 0.f, 0.f,
			129.f, 175.f);
		GetSceneResource()->AddAnimationFrame("Portal", 0.f, 0.f,
			128.f, 172.f);
		GetSceneResource()->AddAnimationFrame("Portal", 0.f, 0.f,
			122.f, 174.f);
		GetSceneResource()->AddAnimationFrame("Portal", 0.f, 0.f,
			120.f, 170.f);
		GetSceneResource()->AddAnimationFrame("Portal", 0.f, 0.f,
			120.f, 172.f);
		GetSceneResource()->AddAnimationFrame("Portal", 0.f, 0.f,
			124.f, 174.f);
		GetSceneResource()->AddAnimationFrame("Portal", 0.f, 0.f,
			127.f, 178.f);
		GetSceneResource()->AddAnimationFrame("Portal", 0.f, 0.f,
			129.f, 175.f);
		GetSceneResource()->AddAnimationFrame("Portal", 0.f, 0.f,
			128.f, 172.f);
		GetSceneResource()->AddAnimationFrame("Portal", 0.f, 0.f,
			122.f, 174.f);
		GetSceneResource()->AddAnimationFrame("Portal", 0.f, 0.f,
			120.f, 170.f);
		GetSceneResource()->AddAnimationFrame("Portal", 0.f, 0.f,
			120.f, 172.f);
		GetSceneResource()->AddAnimationFrame("Portal", 0.f, 0.f,
			124.f, 174.f);

		GetSceneResource()->AddAnimationFramePivot("Portal", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("Portal", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("Portal", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("Portal", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("Portal", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("Portal", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("Portal", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("Portal", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("Portal", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("Portal", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("Portal", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("Portal", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("Portal", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("Portal", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("Portal", 255, 0, 255);
	}
	

	// 무영 정지
	vecFileName.clear();

	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Npc/Muyeong/stand.%d.bmp"), 0);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("MuyeongStand"))
	{
		GetSceneResource()->CreateAnimationSequence("MuyeongStand",
			"MuyeongStand", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("MuyeongStand", 0.f, 0.f,
			82.f, 83.f);

		GetSceneResource()->AddAnimationFramePivot("MuyeongStand", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("MuyeongStand", 255, 0, 255);
	}


	// 무영 우울
	vecFileName.clear();

	for (int i = 0; i < 5; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Npc/Muyeong/gloomy.%d.bmp"), 0);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("MuyeongGloomy"))
	{
		GetSceneResource()->CreateAnimationSequence("MuyeongGloomy",
			"MuyeongGloomy", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("MuyeongGloomy", 0.f, 0.f,
			82.f, 83.f);
		GetSceneResource()->AddAnimationFrame("MuyeongGloomy", 0.f, 0.f,
			82.f, 83.f);
		GetSceneResource()->AddAnimationFrame("MuyeongGloomy", 0.f, 0.f,
			83.f, 82.f);
		GetSceneResource()->AddAnimationFrame("MuyeongGloomy", 0.f, 0.f,
			83.f, 82.f);
		GetSceneResource()->AddAnimationFrame("MuyeongGloomy", 0.f, 0.f,
			83.f, 82.f);

		GetSceneResource()->AddAnimationFramePivot("MuyeongGloomy", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("MuyeongGloomy", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("MuyeongGloomy", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("MuyeongGloomy", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("MuyeongGloomy", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("MuyeongGloomy", 255, 0, 255);
	}


	// 무영 대화
	vecFileName.clear();

	for (int i = 0; i < 4; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Npc/Muyeong/say.%d.bmp"), 0);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("MuyeongSay"))
	{
		GetSceneResource()->CreateAnimationSequence("MuyeongSay",
			"MuyeongSay", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("MuyeongSay", 0.f, 0.f,
			82.f, 83.f);
		GetSceneResource()->AddAnimationFrame("MuyeongSay", 0.f, 0.f,
			82.f, 83.f);
		GetSceneResource()->AddAnimationFrame("MuyeongSay", 0.f, 0.f,
			82.f, 83.f);
		GetSceneResource()->AddAnimationFrame("MuyeongSay", 0.f, 0.f,
			82.f, 83.f);

		GetSceneResource()->AddAnimationFramePivot("MuyeongSay", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("MuyeongSay", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("MuyeongSay", 0.5f, 1.f);
		GetSceneResource()->AddAnimationFramePivot("MuyeongSay", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("MuyeongSay", 255, 0, 255);
	}


	// 포장마차 정지
	vecFileName.clear();

	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Npc/Store/stand.%d.bmp"), 0);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("StoreStand"))
	{
		GetSceneResource()->CreateAnimationSequence("StoreStand",
			"StoreStand", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("StoreStand", 0.f, 0.f,
			157.f, 123.f);

		GetSceneResource()->AddAnimationFramePivot("StoreStand", 0.5f, 1.f);

		GetSceneResource()->SetColorKey("StoreStand", 255, 0, 255);
	}


	// 아이템
	vecFileName.clear();

	for (int i = 0; i < 6; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};

		wsprintf(fileName, TEXT("Maple/Object/Item/item.%d.bmp"), i);

		vecFileName.push_back(fileName);
	}

	if (!GetSceneResource()->FindAnimation("Item"))
	{
		GetSceneResource()->CreateAnimationSequence("Item",
			"Item", vecFileName, TEXTURE_PATH);

		GetSceneResource()->AddAnimationFrame("Item", 0.f, 0.f,
			34.f, 35.f);
		GetSceneResource()->AddAnimationFrame("Item", 0.f, 0.f,
			34.f, 35.f);
		GetSceneResource()->AddAnimationFrame("Item", 0.f, 0.f,
			34.f, 35.f);
		GetSceneResource()->AddAnimationFrame("Item", 0.f, 0.f,
			34.f, 35.f);
		GetSceneResource()->AddAnimationFrame("Item", 0.f, 0.f,
			34.f, 35.f);
		GetSceneResource()->AddAnimationFrame("Item", 0.f, 0.f,
			34.f, 35.f);

		GetSceneResource()->AddAnimationFramePivot("Item", 0.5f, 0.5f);
		GetSceneResource()->AddAnimationFramePivot("Item", 0.5f, 0.6f);
		GetSceneResource()->AddAnimationFramePivot("Item", 0.5f, 0.7f);
		GetSceneResource()->AddAnimationFramePivot("Item", 0.5f, 0.8f);
		GetSceneResource()->AddAnimationFramePivot("Item", 0.5f, 0.7f);
		GetSceneResource()->AddAnimationFramePivot("Item", 0.5f, 0.6f);

		GetSceneResource()->SetColorKey("Item", 255, 0, 255);
	}
}

void CMainScene::Cam1Key()
{
	// 카메라의 타겟을 플레이어로 바꾼다.
	GetCamera()->SetTarget(m_player);
}

void CMainScene::Cam2Key()
{
	// 카메라의 타겟을 몬스터로 바꾼다.
	// GetCamera()->SetTarget(m_monster);  // 카메라 전환 시범 코드
}

CMainScene::CMainScene()
{
}

CMainScene::~CMainScene()
{
}
