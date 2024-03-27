#include <ctime>
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "Player.h"
#include "Bullet.h"
#include "Tornado.h"
#include "Satellite.h"
#include "../Input.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Scene/SceneResource.h"
#include "Effect.h"
#include "Effect_2.h"
#include "../UI/MainHUD.h"
#include "../UI/CharacterHUD.h"
#include "../UI/WidgetComponent.h"
#include "../UI/Text.h"
#include "../UI/ImageWidget.h"
#include "../UI/ProgressBar.h"
#include "../Collision/ColliderLine.h"
#include "../Scene/SceneManager.h"
#include "../Scene/MainScene.h"
#include "../Scene/Scene1.h"
#include "../Scene/SceneCollision.h"
#include "../UI/Number.h"
#include "../Scene/Scene2.h"
#include "../Scene/Scene3.h"
#include "Item.h"
#include "HPPotion.h"
#include "MPPotion.h"
#include "Npc.h"

Vector2 CPlayer::m_spawnPos = { 400.f, 100.f };

float CPlayer::EXPTable[19] = { 500,800,	1100,1400,1900,2400,2900,3400,
		3900,4600,5300,6000,6700,7400,8400,9400,10400,11400,15000 };

int PlayerAbility::Level = 1;
float PlayerAbility::HP = 2000;
float PlayerAbility::HPMax = 4000;
float PlayerAbility::MP = 2000;
float PlayerAbility::MPMax = 2000;
float PlayerAbility::EXP = 0.f;
float PlayerAbility::EXPMax = CPlayer::EXPTable[0];
float PlayerAbility::DamageMin = 200;
float PlayerAbility::DamageMax = 200;
int PlayerAbility::Money = 0;
int PlayerAbility::ItemCnt = 50;
int PlayerAbility::HPPotionCnt = 30;
int PlayerAbility::MPPotionCnt = 30;

bool CPlayer::Init()
{
	CGameObject::Init();

	m_moveSpeed = 150.f;  //150 기본값

	/*m_gunAngle = 0.f;
	m_gunLength = 70.f;*/
	
	//// 기본 능력치 설정
	//PlayerAbility::HP = 2000;  
	//PlayerAbility::HPMax = 2000; //기본 2000
	//PlayerAbility::MP = 10000;
	//PlayerAbility::MPMax = 10000;  // 기본 1000
	//PlayerAbility::EXP = 0.f;
	//PlayerAbility::EXPMax = EXPTable[0];
	//PlayerAbility::DamageMin = 200;  // 200
	//PlayerAbility::DamageMax = 400; // 400
	//PlayerAbility::Level = 1;

	/*
		이제 게임매니저가 아닌 오브젝트 각자의 Init에서
		초기화 하도록 한다.
	*/
 	SetPos(500.f, 0.f);
	SetSize(85.f, 75.f);
	SetPivot(0.5f, 1.f);	// 피봇을 발 밑 정중앙으로 맞춘다.

	//m_satelAngle[0] = 0.f;
	//m_satelAngle[1] = 120.f;
	//m_satelAngle[2] = 240.f;

	//m_satelLength = 100.f;
	//m_satelLengthMin = 100.f;
	//m_satelLengthMax = 200.f;

	//m_satelRotationSpeed = 60.f;

	//m_satelSkillOn = false;
	//m_satelSkillTime = 0.f;
	//m_satelSkillDir = 1.f;	// '확대' 상태

	/*
		스킬에 대한 쿨다운 정보 등록
		1번째 스킬(토네이도)은 5초,
		2번째 스킬(위성)은 10초의 쿨다운을 설정
	*/
	SkillCoolDownInfo info = {};
	
	info.coolDown = 5.f;
	m_vecCoolDown.push_back(info);

	info.coolDown = 10.f;
	m_vecCoolDown.push_back(info);

	//// 위성 객체 3개를 생성한다.
	//for (int i = 0; i < 3; ++i)
	//{	
	//	// 위성 객체를 생성한다.
	//	m_satellite[i] = m_scene->CreateObject<CSatellite>("Satellite");

	//	// 위성의 위치를 플레이어를 기준으로 잡는다.
	//	Vector2 pos;
	//	pos.x = m_pos.x + cosf(DegreeToRadian(m_satelAngle[i])) * m_satelLength;
	//	pos.y = m_pos.y + sinf(DegreeToRadian(m_satelAngle[i])) * m_satelLength;
	//	m_satellite[i]->SetPos(pos);
	//}

	// 이 오브젝트의 애니메이션을 생성한다.
	CreateAnimation();

	// 애니메이션을 추가한다. 
	AddAnimation("PlayerRightStand",true, 2.f);   // 오른쪽 정지상태
	AddAnimation("PlayerRightWalk");	// 오른쪽 이동
	AddAnimation("PlayerRightAttack1", false, 0.7f);  // 오른쪽 공격1 (공격 1회에 0.9초)
	AddAnimation("PlayerRightAttack2", false, 0.7f);  // 오른쪽 공격2 
	AddAnimation("PlayerRightAttack3", false, 0.7f);  // 오른쪽 공격3 
	AddAnimation("PlayerRightAttack4", false, 0.7f);  // 오른쪽 공격4
	AddAnimation("PlayerRightAlert", true, 2.f);   // 오른쪽 경계상태
	AddAnimation("PlayerRightJump", false, 1.f);   // 오른쪽 점프
	AddAnimation("PlayerRightJudgement", true, 0.3f);   // 저지먼트 모션
	AddAnimation("PlayerRightJustice", false, 0.8f);   // 오른쪽 저스티스 모션

	AddAnimation("PlayerRope", true, 0.7f);   // 로프타기
	AddAnimation("PlayerRopeStand", false);   // 로프정지
	AddAnimation("PlayerLadder", true, 0.7f);   // 사다리타기
	AddAnimation("PlayerLadderStand", false);   // 사다리정지

	AddAnimation("PlayerLeftStand", true, 2.f);		// 왼쪽 정지상태
	AddAnimation("PlayerLeftWalk");		// 왼쪽 이동
	AddAnimation("PlayerLeftAttack1", false, 0.7f);	 // 왼쪽 공격1
	AddAnimation("PlayerLeftAttack2", false, 0.7f);	 // 왼쪽 공격2
	AddAnimation("PlayerLeftAttack3", false, 0.7f);	 // 왼쪽 공격3
	AddAnimation("PlayerLeftAttack4", false, 0.7f);	 // 왼쪽 공격4
	AddAnimation("PlayerLeftAlert", true, 2.f);   // 왼쪽 경계상태
	AddAnimation("PlayerLeftJump", false, 1.f);   // 왼쪽 점프
	AddAnimation("PlayerLeftJustice", false, 0.8f);   // 왼쪽 저스티스 모션

	// AttackEnd을 엔드 함수로 세팅하여 공격이 끝났음을 인지하게 한다.
	SetEndFunction<CPlayer>("PlayerRightAttack1", this, &CPlayer::AttackEnd);
	SetEndFunction<CPlayer>("PlayerRightAttack2", this, &CPlayer::AttackEnd);
	SetEndFunction<CPlayer>("PlayerRightAttack3", this, &CPlayer::AttackEnd);
	SetEndFunction<CPlayer>("PlayerRightAttack4", this, &CPlayer::AttackEnd);
	SetEndFunction<CPlayer>("PlayerLeftAttack1", this, &CPlayer::AttackEnd);
	SetEndFunction<CPlayer>("PlayerLeftAttack2", this, &CPlayer::AttackEnd);
	SetEndFunction<CPlayer>("PlayerLeftAttack3", this, &CPlayer::AttackEnd);
	SetEndFunction<CPlayer>("PlayerLeftAttack4", this, &CPlayer::AttackEnd);
	SetEndFunction<CPlayer>("PlayerRightJustice", this, &CPlayer::AttackEnd);
	SetEndFunction<CPlayer>("PlayerLeftJustice", this, &CPlayer::AttackEnd);


	// 1 프레임에 Attack을 노티파이로 세팅하여 내려치는 프레임에 공격 판정이 들어가도록 한다.
	AddNotify<CPlayer>("PlayerRightAttack1", 3, this, &CPlayer::Attack);
	AddNotify<CPlayer>("PlayerRightAttack2", 3, this, &CPlayer::Attack);
	AddNotify<CPlayer>("PlayerRightAttack3", 3, this, &CPlayer::Attack);
	AddNotify<CPlayer>("PlayerRightAttack4", 3, this, &CPlayer::Attack);
	AddNotify<CPlayer>("PlayerLeftAttack1", 3, this, &CPlayer::Attack);
	AddNotify<CPlayer>("PlayerLeftAttack2", 3, this, &CPlayer::Attack);
	AddNotify<CPlayer>("PlayerLeftAttack3", 3, this, &CPlayer::Attack);
	AddNotify<CPlayer>("PlayerLeftAttack4", 3, this, &CPlayer::Attack);
	AddNotify<CPlayer>("PlayerRightJudgement", 1, this, &CPlayer::Attack);
	AddNotify<CPlayer>("PlayerRightJustice", 1, this, &CPlayer::Attack);
	AddNotify<CPlayer>("PlayerLeftJustice", 1, this, &CPlayer::Attack);
	AddNotify<CPlayer>("PlayerRightJustice", 9, this, &CPlayer::Attack2);
	AddNotify<CPlayer>("PlayerLeftJustice", 9, this, &CPlayer::Attack2);

	// 키세트를 오른쪽과 왼쪽으로 나누어 세팅한다.
	m_vecSequenceKey[0].push_back("PlayerRightStand");
	m_vecSequenceKey[0].push_back("PlayerRightWalk");
	// [2] ~ [5] 기본 공격모션
	m_vecSequenceKey[0].push_back("PlayerRightAttack1");
	m_vecSequenceKey[0].push_back("PlayerRightAttack2");
	m_vecSequenceKey[0].push_back("PlayerRightAttack3");
	m_vecSequenceKey[0].push_back("PlayerRightAttack4");
	// [6] 경계모션
	m_vecSequenceKey[0].push_back("PlayerRightAlert");
	// [7] 점프모션
	m_vecSequenceKey[0].push_back("PlayerRightJump");

	m_vecSequenceKey[1].push_back("PlayerLeftStand");
	m_vecSequenceKey[1].push_back("PlayerLeftWalk");
	m_vecSequenceKey[1].push_back("PlayerLeftAttack1");
	m_vecSequenceKey[1].push_back("PlayerLeftAttack2");
	m_vecSequenceKey[1].push_back("PlayerLeftAttack3");
	m_vecSequenceKey[1].push_back("PlayerLeftAttack4");
	m_vecSequenceKey[1].push_back("PlayerLeftAlert");
	m_vecSequenceKey[1].push_back("PlayerLeftJump");

	m_playerDir = 1;	// 기본 오른쪽 보고 있음.

	m_attack = false;   // 공격이 아닌 상태
	m_alert = false;	// 기본 비경계 상태
	/*
		충돌체를 추가하는 부분이다.
		플레이어의 머리와 몸통을 나누어 충돌체를 만들 것이다.
		 
		* 크기 및 offset의 조정은 '알씨'를 이용하면
		이미지의 픽셀 단위 좌표를 볼 수 있어 편하다. 
	*/
	// Head 라는 이름의 박스 충돌체를 만든다.
	CColliderBox* box = AddCollider<CColliderBox>("Head");

	box->SetExtent(50.f, 42.f);  // 가로세로 크기
	box->SetOffset(3.f, -50.f);	 // owner(플레이어 발밑 pos)로부터 얼마나 떨어져 있을 지
	box->SetCollisionProfile("Player");  // 충돌 프로파일 설정 : Player 

	// Head와 충돌 시 호출할 함수 등록
	box->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::CollisionBegin);
	box->SetCollisionEndFunction<CPlayer>(this, &CPlayer::CollisionEnd);

	// 벡터에 추가한다
	m_playerCollider.push_back(box);


	// Body 라는 이름의 박스 충돌체를 만든다.
	box = AddCollider<CColliderBox>("Body");
	box->SetExtent(36.f, 31.f);
	box->SetOffset(3.f, -13.5f);
	box->SetCollisionProfile("Player");

	// body와 충돌 시 호출할 함수 등록
	box->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::CollisionBegin);
	box->SetCollisionEndFunction<CPlayer>(this, &CPlayer::CollisionEnd);
	
	// 벡터에 추가한다
	m_playerCollider.push_back(box);

	/*
		바인드키에 함수를 등록한다. 아래의 경우, 
		1. 등록할 함수가 호출되는 바인드키의 이름은 "MoveFront"이다.
		2. InputType이 PUSH일 경우 호출되는 함수이다.
		3. 현재 CPlayer 객체의 주소이다.
		4. MoveFront 함수의 주소이다.

		공격과 스킬의 경우, InputType을 DOWN으로 등록하여
		연속으로 발사되지 않게 바꾼다.
	*/

	CInput::GetInst()->AddBindFunction<CPlayer>
		("Portal", EInputType::DOWN, this, &CPlayer::Portal, m_scene);

	CInput::GetInst()->AddBindFunction<CPlayer>
		("MoveFront", EInputType::PUSH, this, &CPlayer::MoveFront, m_scene);

	CInput::GetInst()->AddBindFunction<CPlayer>
		("MoveBack", EInputType::PUSH, this, &CPlayer::MoveBack, m_scene);

	CInput::GetInst()->AddBindFunction<CPlayer>
		("GunRotation", EInputType::PUSH, this, &CPlayer::GunRotation, m_scene);

	CInput::GetInst()->AddBindFunction<CPlayer>
		("GunRotationInv", EInputType::PUSH, this, &CPlayer::GunRotationInv, m_scene);

	CInput::GetInst()->AddBindFunction<CPlayer>
		("Fire", EInputType::DOWN, this, &CPlayer::Fire, m_scene);

	CInput::GetInst()->AddBindFunction<CPlayer>
		("Gain", EInputType::DOWN, this, &CPlayer::Gain, m_scene);

	CInput::GetInst()->AddBindFunction<CPlayer>
		("PowerStrike", EInputType::DOWN, this, &CPlayer::PowerStrike, m_scene);

	CInput::GetInst()->AddBindFunction<CPlayer>
		("SlashBlast", EInputType::DOWN, this, &CPlayer::SlashBlast, m_scene);

	CInput::GetInst()->AddBindFunction<CPlayer>
		("Judgement", EInputType::DOWN, this, &CPlayer::Judgement, m_scene);

	CInput::GetInst()->AddBindFunction<CPlayer>
		("Judgement", EInputType::UP, this, &CPlayer::AttackEnd, m_scene);

	CInput::GetInst()->AddBindFunction<CPlayer>
		("Justice", EInputType::DOWN, this, &CPlayer::Justice, m_scene);

	CInput::GetInst()->AddBindFunction<CPlayer>
		("HPPotion", EInputType::DOWN, this, &CPlayer::HPPotion, m_scene);

	CInput::GetInst()->AddBindFunction<CPlayer>
		("MPPotion", EInputType::DOWN, this, &CPlayer::MPPotion, m_scene);

	CInput::GetInst()->AddBindFunction<CPlayer>
		("Skill1", EInputType::DOWN, this, &CPlayer::Skill1, m_scene);

	CInput::GetInst()->AddBindFunction<CPlayer>
		("Skill2", EInputType::DOWN, this, &CPlayer::Skill2, m_scene);

	CInput::GetInst()->AddBindFunction<CPlayer>
		("Jump",EInputType::DOWN, this, &CPlayer::JumpKey, m_scene);

	

	//// hp바 위젯 컴포넌트 생성
	//m_HPBar = CreateWidgetComponent<CProgressBar>("HPBar");

	//// 텍스쳐 및 크기, 위치 설정
	//m_HPBar->GetWidget<CProgressBar>()->SetTexture(EProgressBar_Texture_Type::Bar,
	//	"HPBar", TEXT("CharacterHPBar.bmp"));
	//m_HPBar->GetWidget<CProgressBar>()->SetSize(50.f, 10.f);
	//m_HPBar->SetPos(-25.f, -90.f);

	
	// 이름표 설정
	m_nameBarFrame = CreateWidgetComponent<CImageWidget>("NameBarPlayer");
	m_nameBarFrame->GetWidget<CImageWidget>()->SetTexture("NameBarPlayer", TEXT("Maple/UI/Basic/Name/NameBar_Player.bmp"));
	m_nameBarFrame->GetWidget<CImageWidget>()->SetColorKey(255, 0, 255);
	m_nameBarFrame->GetWidget<CImageWidget>()->SetSize(56.f, 15.f);
	m_nameBarFrame->SetPos(-25.f, 0.f);

	// 이렇게 플레이어가 생성될때마다 값을 갱신해줘야됨!!!
	m_scene->FindWidget<CMainHUD>("MainHUD")
		->SetHP2(CPlayer::m_ability.HP / CPlayer::m_ability.HPMax);

	m_scene->FindWidget<CMainHUD>("MainHUD")
		->SetMP2(CPlayer::m_ability.MP / CPlayer::m_ability.MPMax);

	m_scene->FindWidget<CMainHUD>("MainHUD")
		->SetEXP2(CPlayer::m_ability.EXP / CPlayer::m_ability.EXPMax);

	// 중력 적용 on
	SetPhysicsSimulate(true);
	// 점프 속도 지정 30
	SetJumpVelocity(35.f);


	return true;
}

void CPlayer::Update(float _deltaTime)
{
	CCharacter::Update(_deltaTime);


	// SetJumpVelocity(50.f);
	m_objDir = m_playerDir;

	// 비 경계상태에서 가만히 있으면 1초마다 최대체력의 1% 회복한다
	if (!m_alert)
	{
		m_healTime += _deltaTime;

		if (m_healTime > 1.5f)
		{
			if (PlayerAbility::HPMax > (PlayerAbility::HP + PlayerAbility::HPMax * 0.01f))
			{
				// 한번 회복하면 다시 세기
				m_healTime = 0.f;

					PlayerAbility::HP += PlayerAbility::HPMax * 0.01f;

					// 이전 비율을 구해놓는다.
					float prevHP = PlayerAbility::HP / (float)PlayerAbility::HPMax;

					// 체력 ui 조정
					m_scene->FindWidget<CMainHUD>("MainHUD")
					->SetHP(PlayerAbility::HP / (float)PlayerAbility::HPMax, prevHP);


				// 회복 위젯 머리위에 띄우기
				std::vector<std::wstring> vecFileName;
				for (int i = 0; i <= 9; ++i)
				{
					TCHAR	FileName[MAX_PATH] = {};
					// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
					wsprintf(FileName, TEXT("Maple/UI/Damage/NoBlue0.%d.bmp"), i);
					vecFileName.push_back(FileName);
				}
				m_healWidget = CreateWidgetComponent<CNumber>("DamageNo");
				m_healWidget->GetWidget<CNumber>()->SetTexture("PlayerHealNo", vecFileName);
				m_healWidget->GetWidget<CNumber>()->SetColorKey(255, 0, 255);
				m_healWidget->GetWidget<CNumber>()->SetSize(31.f, 33.f);
				m_healWidget->SetPos(-30.f, -100.f);
				m_healWidget->GetWidget<CNumber>()->SetNumber((int)PlayerAbility::HPMax * 0.01f);
			}
		}
		// 움직이면 처음부터 다시 1초 카운트
		else if (m_move.x > 0.f)
		{
			m_healTime = 0.f;
		}
	}

	
	// 믹서기 딜레이 1초
	if (m_judgementDelay > 0.f)
	{
		m_judgementDelay -= _deltaTime;
	}

	// 사다리는 속도 느리게
	if (m_ladder)
	{
		m_moveSpeed = 75.f;
		// 막아두었던 up키 활성화
		SetEnableUpKey(true);
	}
	else
		m_moveSpeed = 150.f; // 150

	// 저지먼트 사용시 일시적 속도 증가
	if (m_useSkill == ESkill::Judgement)
		m_moveSpeed = 250.f;

	// 스킬 사용시 이펙트 위치를 잡아주기 위함
	if (m_useSkill == ESkill::PowerStrike)
	{
		m_effect->SetPos(m_pos + Vector2(10.f * m_playerDir, -35.f));
	}
	else if(m_effect)
		m_effect->SetPos(m_pos);
	


	// 이 벡터의 길이 = 스킬의 개수
	size_t size = m_vecCoolDown.size();

	_deltaTime *= m_timeScale;

	for (size_t i = 0; i < size; ++i)
	{
		// 현재 스킬에 쿨다운이 남아있다면
		if (m_vecCoolDown[i].coolDownEnable)
		{
			// 지나가는 시간만큼 차감한다.
			m_vecCoolDown[i].coolDown -= _deltaTime;

			// 쿨다운이 0에 도달했다면, 쿨다운 '없음'으로 바꾼다.
			if (m_vecCoolDown[i].coolDown <= 0.f)
				m_vecCoolDown[i].coolDownEnable = false;
		}
	}

	

	// 경계상태 지속시간을 체크한다. 시간이 지나면 false로 바꿔 줄 것이다. 
	if (m_alert)
	{
		// 회복시간이 줄어들지 않도록
		m_healTime = 0.f;

		m_alertTime -= _deltaTime;

		if (m_alertTime <= 0.f)
		{
			m_alert = false;
		}
	}

	// 무적상태 지속시간을 체크한다. 
	if (m_grace)
	{
		m_graceTime -= _deltaTime;

		if (m_graceTime <= 0.f)
		{
			/*
				이렇게 플레이어 충돌체를 삭제->재생성하지 않으면
				몬스터와 충돌을 유지하고 있어도 체력이 한번밖에 깎이지 않는다.
			*/
			ResetPlayerCollider();
			m_grace = false;
			m_scene->SetGrace(false);
		}
	}

	//// 총의 위치를 매번 업데이트한다. 
	//m_gunPos.x = m_pos.x + cosf(DegreeToRadian(m_gunAngle)) * m_gunLength;
	//m_gunPos.y = m_pos.y + sinf(DegreeToRadian(m_gunAngle)) * m_gunLength;

	//// 위성이 활성화 상태일 경우
	//if (m_satelSkillOn)
	//{
	//	// 위성의 궤도를 dir에 따라 점점 넓히거나 좁힌다.
	//	m_satelLength += m_satelSkillDir * 
	//		(m_satelLengthMax - m_satelLengthMin) / 2.f * _deltaTime;

	//	// 위성의 궤도가 최대 범위에 도달하거나 넘으면 범위를 최대로 조정해준다.
	//	if (m_satelLength >= m_satelLengthMax)
	//		m_satelLength = m_satelLengthMax;

	//	// 위성의 궤도가 최소 범위에 도달하거나 넘으면 범위를 최소로 조정해주고
	//	else if (m_satelLength <= m_satelLengthMin)
	//	{
	//		// 위성을 비활성화 상태로 바꾸며, 회전속도를 기본값으로 조정한다. 
	//		m_satelRotationSpeed = 60.f;
	//		m_satelLength = m_satelLengthMin;
	//		m_satelSkillOn = false;
	//	}

	//	m_satelSkillTime += _deltaTime;

	//	// 위성의 지속시간이 5초가 넘으면 (지속시간이 경과하면)
	//	if (m_satelSkillTime >= 5.f)
	//	{
	//		// 위성의 궤도를 '축소' 상태로 바꾼다.
	//		m_satelSkillDir = -1.f;
	//	}
	//}

	//// 위성의 위치를 매번 업데이트한다.
	//for (int i = 0; i < 3; ++i)
	//{
	//	m_satelAngle[i] += m_satelRotationSpeed * _deltaTime;

	//	Vector2 pos;
	//	pos.x = m_pos.x + cosf(DegreeToRadian(m_satelAngle[i])) * m_satelLength;
	//	pos.y = m_pos.y + sinf(DegreeToRadian(m_satelAngle[i])) * m_satelLength;

	//	m_satellite[i]->SetPos(pos);
	//}


}

void CPlayer::PostUpdate(float _deltaTime)
{
	CCharacter::PostUpdate(_deltaTime);

	

	/*
		이것을 여기에서 삭제해 주는 이유는,
		공격 충돌체가 너무 오래 남아 시간차로 공격하는 경우가
		생기기 때문에 빠르게 삭제해 주기 위함이다.

		* 일단 충돌체가 보이도록 주석걸어놓음
	*/
	if (m_attackCollider)
	{
		if (m_attackCollider->GetActive())
			m_attackCollider->SetActive(false);
	}


	// 플레이어가 오른쪽 방향일 경우
	if (m_playerDir == 1)
	{
		// 이동량이 0이라는 것은 오른쪽으로 이동중 멈췄다는 것이다.
		if (m_move.x < 0.f)
			m_playerDir = -1;
	}
	// 플레이어가 오른쪽 방향일 경우
	else
	{
		// 이동량이 0이라는 것은 오른쪽으로 이동중 멈췄다는 것이다.
		if (m_move.x > 0.f)
			m_playerDir = 1;
	}

	int	AnimDirIndex = 0;

	if (m_playerDir == -1)
		AnimDirIndex = 1;

	//if (m_move.x != 0.f || m_move.y != 0.f)
	//{
	//	// 이동을 할 경우 공격중이더라도 공격을 취소한다.
	//	m_attack = false;
	//	ChangeAnimation(m_vecSequenceKey[AnimDirIndex][1]);
	//}
	
		
	if (m_ladder)
	{
		if (m_move.y != 0.f)
		{
			// 이동 모션으로 전환
			ChangeAnimation("PlayerLadder");
		}
		else
			ChangeAnimation("PlayerLadderStand");

		return;
	}

	if (m_jump && !m_attack)
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][7]);
	// 이동량이 0이 아닐 경우 = 움직이고 있을 경우 and 공격중이 아닐경우에만(이동중에 공격이 가능해짐)
	else if ((m_move.x != 0.f || m_move.y != 0.f) && !m_attack)
	{
		// 이동 모션으로 전환
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][1]);
	}
	// 공격중이 아니고 경계상태가 아니면 정지모션으로 전환
	else if (!m_attack && !m_alert)
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][0]);
	// 공격중이 아니고 경계상태면 경계모션으로 전환
	else if (!m_attack && m_alert)
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][6]);
	
	// 플레이어 위치 보정
	if (m_ladder)
	{
		SetPos(m_LadderCollider->GetLineInfo().Point1.x, m_pos.y);
	}
}

void CPlayer::Render(HDC _hDC, float _deltaTime)
{
	// 피격 시 깜빡임을 표현하기 위함
	
	// 무적상태일경우
	if (m_grace)
	{
		// 0.00001초동안 그리지 않는다.
		if (m_graceRender < 0.00001f)
		{
			m_graceRender += _deltaTime;
			return;
		}
	}

	// 한번 그리면
	CCharacter::Render(_hDC, _deltaTime);
	
	// 다시 시간 초기화
	m_graceRender = 0.f;


	/* 
		플레이어에 부착될 총(선)을 그린다.
		총은 매 업데이트마다 플레이어 위치(pos)와 키 입력에 따른 
		변화된 위치가 갱신되므로, 그 위치(gunPos)에 맞춰 그려지게 된다.
	*/ 
	
	/*
		카메라를 만든 후 부터 총의 위치는 카메라 위치에 따른 상대적인
		위치로 바뀌므로 아래와 같이 계산한다.
	*/
	/*Vector2 pos = m_pos - m_scene->GetCamera()->GetPos();
	Vector2 gunPos = m_gunPos - m_scene->GetCamera()->GetPos();

	MoveToEx(_hDC, (int)pos.x, (int)pos.y, nullptr);
	LineTo(_hDC, (int)gunPos.x, (int)gunPos.y);*/

}

float CPlayer:: InflictDamage(float _damage, int _dir)
{
	if (m_grace)
		return 0.f;

	
	// 이전 비율을 구해놓는다.
	float prevHP = m_ability.HP / (float)m_ability.HPMax;

	// 실제 체력 조정
	if (0 > m_ability.HP - _damage)
		m_ability.HP = 0;
	else
	{
		m_ability.HP -= _damage;
	}
	

	// 체력 ui 조정
	m_scene->FindWidget<CMainHUD>("MainHUD")
		->SetHP(m_ability.HP / (float)m_ability.HPMax , prevHP);

	//// 이건 캐릭터에 붙어있는 위젯컴포넌트 체력바를 조정하는 것
	//m_HPBar->GetWidget<CProgressBar>()->SetValue(m_ability.HP / (float)m_ability.HPMax);

	// 현재 무적상태가 아닐 경우 무적상태로 전환 및 1.2초의 무적시간 부여
	if (!m_grace)
	{
		m_grace = true;
		m_scene->SetGrace(true);
		m_graceTime = 1.2f;
	}

	// 경계상태 전환 및 7초 갱신
	m_alert = true;
	m_alertTime = 7.f;

	// 받은 데미지 만큼 머리 위에 위젯을 띄운다.

	std::vector<std::wstring> vecFileName;
	for (int i = 0; i <= 9; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
		wsprintf(FileName, TEXT("Maple/UI/Damage/NoViolet0.%d.bmp"), i);
		vecFileName.push_back(FileName);
	}

	++widgetCnt;

	m_damageWidget.push_back(CreateWidgetComponent<CNumber>("DamageNo"));
	m_damageWidget[widgetCnt - 1]->GetWidget<CNumber>()->SetTexture("PlayerDamageNo", vecFileName);
	m_damageWidget[widgetCnt - 1]->GetWidget<CNumber>()->SetColorKey(255, 0, 255);
	m_damageWidget[widgetCnt - 1]->GetWidget<CNumber>()->SetSize(31.f, 33.f);

	m_damageWidget[widgetCnt - 1]->SetPos(-50.f, -100.f);

	m_damageWidget[widgetCnt - 1]->GetWidget<CNumber>()->SetNumber(_damage);

	return m_ability.HP;
}


bool CPlayer::GetDir()
{
	return m_playerDir;
}

ESkill CPlayer::GetUseSkill() const
{
	return m_useSkill;
}

float CPlayer::GetHP() const
{
	return m_ability.HP;
}

float CPlayer::GetHPMax() const
{
	return m_ability.HPMax;
}

float CPlayer::GetMP() const
{
	return m_ability.MP;
}

float CPlayer::GetMPMax() const
{
	return m_ability.MPMax;
}

float CPlayer::GetEXP() const
{
	return m_ability.EXP;
}

float CPlayer::GetEXPMax() const
{
	return m_ability.EXPMax;
}

float CPlayer::GetLevel() const
{
	return m_ability.Level;
}

int CPlayer::GetHPPotionCnt() const
{
	return PlayerAbility::HPPotionCnt;
}

int CPlayer::GetMPPotionCnt() const
{
	return PlayerAbility::MPPotionCnt;
}

int CPlayer::GetItemCnt() const
{
	return PlayerAbility::ItemCnt;
}

ESkillState CPlayer::GetPowerStrikeState()
{
	return m_powerStrikeState;
}

ESkillState CPlayer::GetSlashBlastState()
{
	return m_slashBlastState;
}

ESkillState CPlayer::GetJudgementState()
{
	return m_judgementState;
}

ESkillState CPlayer::GetJusticeState()
{
	return m_justiceState;
}

void CPlayer::SetPortalEnable(std::string _portalName)
{
	m_portalEnable = _portalName;
}

void CPlayer::AddEXP(float _exp)
{
	// 이전 비율을 구해놓는다.
	float prevEXP = m_ability.EXP /  m_ability.EXPMax;

	m_ability.EXP += _exp;

	if (m_ability.EXP >= m_ability.EXPMax)
	{
		m_scene->GetSceneResource()->SoundPlay("LevelUp");
		LevelUp();
	}
	else
		m_scene->FindWidget<CMainHUD>("MainHUD")
			->SetEXP(m_ability.EXP / m_ability.EXPMax, prevEXP);

	
}

void CPlayer::AddMoney(int _money)
{
	m_ability.Money += _money;
}

void CPlayer::LevelUp()
{
	++m_ability.Level;

	CEffect* effect = m_scene->CreateObject<CEffect>("LevelUp");
	effect->SetPos(m_pos+Vector2(0.f,-60.f));
	effect->AddAnimation("LevelUp", false, 1.0f);

	float prevEXP = 1.f;
	m_ability.EXP = m_ability.EXP - m_ability.EXPMax;
	m_ability.EXPMax = EXPTable[m_ability.Level - 1];
	m_scene->FindWidget<CMainHUD>("MainHUD")
		->SetEXP(m_ability.EXP / m_ability.EXPMax, prevEXP);

	m_ability.HPMax +=150;
	float prevHP = m_ability.HP / m_ability.HPMax;
	m_ability.HP = m_ability.HPMax;
	m_scene->FindWidget<CMainHUD>("MainHUD")
		->SetHP(m_ability.HP / m_ability.HPMax, prevHP);

	m_ability.MPMax += 80;
	float prevMP = m_ability.MP / m_ability.MPMax;
	m_ability.MP = m_ability.MPMax;
	m_scene->FindWidget<CMainHUD>("MainHUD")
		->SetMP(m_ability.MP /m_ability.MPMax, prevMP);

	m_ability.DamageMax += 30;
	m_ability.DamageMin += 15;


}

void CPlayer::Portal()
{
	// npc일경우
	if (m_interactiveNpc)
	{
		m_interactiveNpc->OpenUIWindow();
		return;
	}
	
	// 포탈일경우
	if (m_enableUpKey_Portal && !m_portalEnable.empty() && !m_ladder)
	{
		if (m_portalEnable == "Portal_Scene1ToScene2")
		{
			CInput::GetInst()->ClearCallback();
			m_spawnPos = { 100.f, 475.f };
			CSceneManager::GetInst()->CreateScene<CScene2>();
		}
		else if (m_portalEnable == "Portal_Scene2ToScene1")
		{
			CInput::GetInst()->ClearCallback();
			m_spawnPos = { 800.f, 205.f };
			CSceneManager::GetInst()->CreateScene<CScene1>();
		}
		else if (m_portalEnable == "Portal_Scene2ToScene3")
		{
			CInput::GetInst()->ClearCallback();
			m_spawnPos = { 70.f, 475.f };
			CSceneManager::GetInst()->CreateScene<CScene3>();

		}
		else if (m_portalEnable == "Portal_Scene3ToScene2")
		{
			CInput::GetInst()->ClearCallback();
			m_spawnPos = { 1960.f, 760.f };
			CSceneManager::GetInst()->CreateScene<CScene2>();
		}
		else if (m_portalEnable == "Portal_Scene3ToScene4")
		{
			CInput::GetInst()->ClearCallback();
			m_spawnPos = { 60.f, 250.f };
			CSceneManager::GetInst()->CreateScene<CMainScene>();
		}
		else if (m_portalEnable == "Portal_Scene4ToScene3")
		{
			CInput::GetInst()->ClearCallback();
			m_spawnPos = { 1960.f, 793.f };
			CSceneManager::GetInst()->CreateScene<CScene3>();
		}
		else if (m_portalEnable == "Portal_Scene4ToScene1")
		{
			CInput::GetInst()->ClearCallback();
			m_spawnPos = { 800.f, 205.f };
			CSceneManager::GetInst()->CreateScene<CScene1>();
		}

 		m_scene->GetSceneResource()->SoundPlay("Portal");

		m_portalEnable.clear();

		return;
	}
}

/*
	바인드키에 등록할 함수들에서 델타타임을 사용하기 위해
	델타타임을 게임매니저의 멤버변수로 추가해 매크로로 사용한다.
*/
void CPlayer::MoveFront()
{
	//// 총의 방향에 맞춰 이동 방향을 구한다.
	//Vector2 dir;
	//dir.x = cosf(DegreeToRadian(m_gunAngle));
	//dir.y = sinf(DegreeToRadian(m_gunAngle));

	//// 이동 방향에 맞춰 초당 400만큼 이동한다.
	//m_pos += dir * 400.f * DELTA_TIME * m_timeScale;

	//// 애니메이션을 교체한다.
	//ChangeAnimation("PlayerRightWalk");

	if (m_attack)
		return;

	if (m_enableUpKey)
	{
		ChangeAnimation("PlayerLadder");
		MoveDir(Vector2(0.f, -1.f));	// 해당 방향으로 이동시킨다. (상)
		SetGround(false);
		SetPhysicsSimulate(false);
		m_ladder = true;
	}
}

void CPlayer::MoveBack()
{
	//// 총의 방향에 맞춰 이동 방향을 구한다.
	//Vector2 dir;
	//dir.x = cosf(DegreeToRadian(m_gunAngle));
	//dir.y = sinf(DegreeToRadian(m_gunAngle));

	//// 이동 방향에 맞춰 초당 400만큼 반대로 이동한다.
	//m_pos -= dir * 400.f * DELTA_TIME * m_timeScale;

	//// 애니메이션을 교체한다.
	//ChangeAnimation("PlayerRightWalk");

	if (m_attack)
		return;

	if (m_enableDownKey)
	{
		ChangeAnimation("PlayerLadder");
		MoveDir(Vector2(0.f, 1.f));	// 해당 방향으로 이동시킨다. (하)
		SetGround(false);
		SetPhysicsSimulate(false);
		m_ladder = true;
	}
}

void CPlayer::GunRotation()	// 이동으로 바뀌었음
{
	// 사다리타는 도중에 좌우 이동 불가
	if (m_ladder)
		return;

	// 공격중에 이동 불가능하게 한다. 단, 점프중에는 예외로하여 점프공격이 자연스럽게 되도록 한다.
	// 저지먼트는 이동하면서 사용이 가능하다.
	if (m_attack && !m_jump && (m_useSkill != ESkill::Judgement))
		return;

	//// 총을 초당 180도 만큼 시계방향으로 회전한다.
	//m_gunAngle += 180.f * DELTA_TIME * m_timeScale;

	MoveDir(Vector2(1.f, 0.f));	// 해당 방향으로 이동시킨다. (우)
}

void CPlayer::GunRotationInv() // 이동으로 바뀌었음
{
	// 사다리타는 도중에 좌우 이동 불가
	if (m_ladder)
		return;

	// 공격중에 이동 불가능하게 한다. 단, 점프중에는 예외로하여 점프공격이 자연스럽게 되도록 한다.
	// 저지먼트는 이동하면서 사용이 가능하다.
	if (m_attack && !m_jump && (m_useSkill != ESkill::Judgement))
		return;

	//// 총을 초당 180도 만큼 반 시계방향으로 회전한다.
	//m_gunAngle -= 180.f * DELTA_TIME * m_timeScale;

	MoveDir(Vector2(-1.f, 0.f)); // 해당 방향으로 이동시킨다. (좌)
}

void CPlayer::Fire()
{
	// 사다리타는 도중에 공격 불가
	if (m_ladder)
		return;

	// 이미 공격중이라면 리턴
	if (m_attack)
		return;

	m_useSkill = ESkill::Attack;

	// 공격중으로 바꿈
	m_attack = true;

	// 공격으로 인해 경계상태로 바뀌며, 6초가 다시 갱신된다.
	m_alert = true;
	m_alertTime = 7.f;

	int	AnimDirIndex = 0;

	// 플레이어의 방향이 왼쪽이라면
	if (m_playerDir == -1)
		// 키세트 벡터의 '왼쪽 방향'의 인덱스로
		AnimDirIndex = 1;

	int randomAttack = (rand()%4)+2;  // 2 ~ 5

	// 해당 방향 세트로 애니메이션 교체. 공격 4가지 중 하나를 랜덤으로 함 
	ChangeAnimation(m_vecSequenceKey[AnimDirIndex][randomAttack]);

	// 패턴 정보 등록
	m_attackPattern = randomAttack-1;
}

void CPlayer::Gain()
{
	if (!m_gainableItemList.empty())
	{
		m_scene->GetSceneResource()->SoundPlay("Gain");

		PlayerAbility::ItemCnt += (int)m_gainableItemList.size();

		auto iter = m_gainableItemList.begin();
		auto iterEnd = m_gainableItemList.end();

		for (; iter != iterEnd;)
		{
			(*iter)->SetActive(false);
			++iter;


		}
		m_gainableItemList.clear();

		return;
	}
	if (!m_gainableHPPotionList.empty())
	{
		m_scene->GetSceneResource()->SoundPlay("Gain");

		PlayerAbility::HPPotionCnt += (int)m_gainableHPPotionList.size();

		auto iter = m_gainableHPPotionList.begin();
		auto iterEnd = m_gainableHPPotionList.end();

		for (; iter != iterEnd;)
		{
			(*iter)->SetActive(false);
			++iter;


		}
		m_gainableHPPotionList.clear();

		return;
	}
	if (!m_gainableMPPotionList.empty())
	{
		m_scene->GetSceneResource()->SoundPlay("Gain");

		PlayerAbility::MPPotionCnt += (int)m_gainableMPPotionList.size();

		auto iter = m_gainableMPPotionList.begin();
		auto iterEnd = m_gainableMPPotionList.end();

		for (; iter != iterEnd;)
		{
			(*iter)->SetActive(false);
			++iter;


		}
		m_gainableMPPotionList.clear();

		return;
	}
	else
		return;
}

void CPlayer::Skill1()
{
	// 쿨다운이 남아있을 경우 바로 리턴한다.
	if (m_vecCoolDown[0].coolDownEnable)
		return;

	// 스킬 키를 누르는 동시에 쿨다운을 '있음'상태로, 5초로 만들어준다.
	m_vecCoolDown[0].coolDownEnable = true;
	m_vecCoolDown[0].coolDown = 5.f;

	//// 토네이도를 생성한다.
	//CTornado* bullet = m_scene->CreateObject<CTornado>("Tornado");

	//// 토네이도의 발사방향을 총의 방향에 맞춰준다.
	//bullet->SetAngle(m_gunAngle);

	//// 토네이도의 첫 위치를 총의 위치로 조정한다.
	//bullet->SetPos(m_gunPos);
}

void CPlayer::Skill2()
{
	// 쿨다운이 남아있을 경우 바로 리턴한다.
	if (m_vecCoolDown[1].coolDownEnable)
		return;

	// 아니라면, 스킬 사용으로 인해 쿨다운을 '있음'상태로, 10초로 만들어준다.
	m_vecCoolDown[1].coolDownEnable = true;
	m_vecCoolDown[1].coolDown = 10.f;

	//// 위성을 활성화 시킨다.
	//m_satelSkillOn = true;

	//// 이 외 기본값으로 바꿔준다. 지속시간의 경우 0부터 다시 누적된다.
	//m_satelRotationSpeed = 180.f;
	//m_satelSkillTime = 0.f;
	//m_satelSkillDir = 1.f;
}

void CPlayer::JumpKey()
{
	// 사다리 타는중 점프로 탈출 가능하게 하기
	

	if (m_ladder)
	{
		
		m_physicsSimulate = true;
		m_fallStartY = m_pos.y;
		m_fallTime = 0.f;

		m_ladder = false;
	}

	// 공격 중 점프불가, 저지먼트는 가능
	if (m_attack && m_useSkill != ESkill::Judgement)
		return;
	else if (m_jump)
		return;

	m_scene->GetSceneResource()->SoundPlay("Jump");

	Jump();
}

void CPlayer::PowerStrike()
{
	// 사다리타는 도중에 공격 불가
	if (m_ladder)
		return;

	// 이미 공격중이라면 리턴
	if (m_attack)
		return;

	// mp가 부족해도 리턴
	if (m_ability.MP < 30)
	{
		return;
	}

	// 이전 비율을 구해놓는다.
	float prevMP = m_ability.MP / (float)m_ability.MPMax;

	// 실제 MP 조정
	m_ability.MP -= 30;

	// MP UI 조정
	m_scene->FindWidget<CMainHUD>("MainHUD")
		->SetMP(m_ability.MP / (float)m_ability.MPMax, prevMP);


	m_powerStrikeState = ESkillState::Used;

	m_useSkill = ESkill::PowerStrike;

	// 사용 사운드
	m_scene->GetSceneResource()->SoundPlay("PowerStrikeUse");

	m_effect = m_scene->CreateObject<CEffect>("PowerStrikeEffect");
	m_effect->SetPos(m_pos + Vector2(10.f * m_playerDir, -35.f));
	m_effect->AddAnimation("PowerStrikeEffect", false, 0.35f);

	/*CEffect* effect = m_scene->CreateObject<CEffect>("SlashBlastEffect");
	effect->SetPos(m_pos + Vector2(7.f * m_playerDir, -32.f));
	effect->AddAnimation("SlashBlastEffect", false, 0.35f);*/

	// 공격중으로 바꿈
	m_attack = true;

	// 공격으로 인해 경계상태로 바뀌며, 6초가 다시 갱신된다.
	m_alert = true;
	m_alertTime = 7.f;

	int	AnimDirIndex = 0;

	// 플레이어의 방향이 왼쪽이라면
	if (m_playerDir == -1)
		// 키세트 벡터의 '왼쪽 방향'의 인덱스로
		AnimDirIndex = 1;

	int randomAttack = (rand() % 4) + 2;  // 2 ~ 5

	// 해당 방향 세트로 애니메이션 교체. 공격 4가지 중 하나를 랜덤으로 함 
	ChangeAnimation(m_vecSequenceKey[AnimDirIndex][randomAttack]);

	// 패턴 정보 등록
	m_attackPattern = randomAttack - 1;
}

void CPlayer::SlashBlast()
{
	// 사다리타는 도중에 공격 불가
	if (m_ladder)
		return;

	// 이미 공격중이라면 리턴
	if (m_attack)
		return;

	// mp가 부족해도 리턴
	if (m_ability.MP < 50)
	{
		return;
	}

	// 이전 비율을 구해놓는다.
	float prevMP = m_ability.MP / (float)m_ability.MPMax;

	// 실제 MP 조정
	m_ability.MP -= 50;

	// MP UI 조정
	m_scene->FindWidget<CMainHUD>("MainHUD")
		->SetMP(m_ability.MP / (float)m_ability.MPMax, prevMP);

	m_slashBlastState = ESkillState::Used;

	m_useSkill = ESkill::SlashBlast;

	// 사용 사운드
	m_scene->GetSceneResource()->SoundPlay("SlashBlastUse");

	CEffect* effect = m_scene->CreateObject<CEffect>("SlashBlastEffect");
	effect->SetPos(m_pos + Vector2(7.f * m_playerDir, -32.f));
	effect->AddAnimation("SlashBlastEffect", false, 0.3f);

	// 공격중으로 바꿈
	m_attack = true;

	// 공격으로 인해 경계상태로 바뀌며, 6초가 다시 갱신된다.
	m_alert = true;
	m_alertTime = 7.f;

	int	AnimDirIndex = 0;

	// 플레이어의 방향이 왼쪽이라면
	if (m_playerDir == -1)
		// 키세트 벡터의 '왼쪽 방향'의 인덱스로
		AnimDirIndex = 1;

	int randomAttack = (rand() % 4) + 2;  // 2 ~ 5

	// 해당 방향 세트로 애니메이션 교체. 공격 4가지 중 하나를 랜덤으로 함 
	ChangeAnimation(m_vecSequenceKey[AnimDirIndex][randomAttack]);

	// 패턴 정보 등록
	m_attackPattern = randomAttack - 1;
}

void CPlayer::Judgement()
{
	// 사다리타는 도중에 공격 불가
	if (m_ladder)
		return;
	
	// 딜레이중이라면 리턴
	if (m_judgementDelay > 0.1f)
		return;

	// 이미 공격중이라면 리턴
	if (m_attack)
		return;

	

	// mp가 부족해도 리턴
	if (m_ability.MP < 30)
	{
		return;
	}


	m_judgementState = ESkillState::Used;

	m_useSkill = ESkill::Judgement;


	ChangeAnimation("PlayerRightJudgement");

	// 공격중으로 바꿈
	m_attack = true;

	// 공격으로 인해 경계상태로 바뀌며, 6초가 다시 갱신된다.
	m_alert = true;
	m_alertTime = 7.f;

	m_attackPattern = 0;

	int random = (rand() % 4) + 1;  // 1 ~ 4
	if (random == 1)
	{
		m_scene->GetSceneResource()->SoundPlay("JudgementVoice1");
	}
	else if (random == 2)
		m_scene->GetSceneResource()->SoundPlay("JudgementVoice2");
	else if (random == 3)
		m_scene->GetSceneResource()->SoundPlay("JudgementVoice3");
	else if (random == 4)
		m_scene->GetSceneResource()->SoundPlay("JudgementVoice4");
}

void CPlayer::Justice()
{
	// 사다리타는 도중에 공격 불가
	if (m_ladder)
		return;

	// 이미 공격중이라면 리턴
	if (m_attack)
		return;

	// mp가 부족해도 리턴
	if (m_ability.MP < 200)
	{
		return;
	}

	// 이전 비율을 구해놓는다.
	float prevMP = m_ability.MP / (float)m_ability.MPMax;

	// 실제 MP 조정
	m_ability.MP -= 200;

	// MP UI 조정
	m_scene->FindWidget<CMainHUD>("MainHUD")
		->SetMP(m_ability.MP / (float)m_ability.MPMax, prevMP);

	m_justiceState = ESkillState::Used;

	m_useSkill = ESkill::Justice;

	// 점프하면서 사용했다면 점프력을 순간적으로 높임
	if (m_jump)
	{
		m_jumpVelocity = 55.f;
	}

	if (m_playerDir == 1)
	{
		ChangeAnimation("PlayerRightJustice");
		m_effect = m_scene->CreateObject<CEffect>("PlayerRightJusticeEffect");
		m_effect->SetPos(m_pos + Vector2(7.f * m_playerDir, -32.f));
		m_effect->AddAnimation("PlayerRightJusticeEffect", false, 0.8f);
	}
	else
	{
		ChangeAnimation("PlayerLeftJustice");
		m_effect = m_scene->CreateObject<CEffect>("PlayerLeftJusticeEffect");
		m_effect->SetPos(m_pos + Vector2(7.f * m_playerDir, -32.f));
		m_effect->AddAnimation("PlayerLeftJusticeEffect", false, 0.8f);
	}
	

	// 공격중으로 바꿈
	m_attack = true;

	// 공격으로 인해 경계상태로 바뀌며, 6초가 다시 갱신된다.
	m_alert = true;
	m_alertTime = 7.f;

	m_attackPattern = 0;
}

void CPlayer::HPPotion()
{
	if (PlayerAbility::HPPotionCnt < 1)
		return;
	else
	{
		m_scene->GetSceneResource()->SoundPlay("Use");

		// 이전 비율을 구해놓는다.
		float prevHP = PlayerAbility::HP / (float)PlayerAbility::HPMax;

		// 실제 체력 조정
		PlayerAbility::HP += 1000;
		if (PlayerAbility::HP > PlayerAbility::HPMax)
			PlayerAbility::HP = PlayerAbility::HPMax;
			

		// 체력 ui 조정
		m_scene->FindWidget<CMainHUD>("MainHUD")
			->SetHP(PlayerAbility::HP / (float)PlayerAbility::HPMax, prevHP);

		--PlayerAbility::HPPotionCnt;
	}
}

void CPlayer::MPPotion()
{
	if (PlayerAbility::MPPotionCnt < 1)
		return;
	else
	{
		m_scene->GetSceneResource()->SoundPlay("Use");

		// 이전 비율을 구해놓는다.
		float prevMP = PlayerAbility::MP / (float)PlayerAbility::MPMax;

		// 실제 체력 조정
		PlayerAbility::MP += 1000;
		if (PlayerAbility::MP > PlayerAbility::MPMax)
			PlayerAbility::MP = PlayerAbility::MPMax;


		// 체력 ui 조정
		m_scene->FindWidget<CMainHUD>("MainHUD")
			->SetMP(PlayerAbility::MP / (float)PlayerAbility::MPMax, prevMP);

		--PlayerAbility::MPPotionCnt;

	}
}



void CPlayer::AttackEnd()
{
	// 공격이 끝났으므로 공격상태를 false로 바꾼다
	
	if (m_useSkill == ESkill::PowerStrike)
	{
		m_powerStrikeState = ESkillState::Normal;
	}
	else if (m_useSkill == ESkill::SlashBlast)
	{
		m_slashBlastState = ESkillState::Normal;
	}
	else if (m_useSkill == ESkill::Judgement)
	{
		m_judgementState = ESkillState::Normal;

		// 스킬 딜레이 1초 추가
		m_judgementDelay = 1.f;
	}

	m_useSkill = ESkill::None;
	
	// 어택이 false일경우 기본 상태로 바뀌게 할 것이다.
	m_attack = false;

	if (m_useSkill == ESkill::Justice)
	{
		m_attackCnt = 0;
	}
	

	size_t size = m_vecAttackCollider.size();

	for (int i = 0; i < size; ++i)
	{
		m_vecAttackCollider[i]->SetActive(false);
		m_vecAttackCollider[i]->ClearCollisionList();
	}
	m_vecAttackCollider.clear();

	if (m_attackCollider)
	{
		if (m_attackCollider->GetActive())
			m_attackCollider->SetActive(false);

		/*
		충돌체를 지우는 것은 충돌을 체크할 때 (SceneCollision의 Collision함수)
		이므로, 위에서 충돌체를 제거한다고 해서 몬스터의 충돌 목록에 공격 충돌체가
		지워지지 않는다.

		따라서 DeleteCollisionList을 이용해 지워준다.

		수정** : 몬스터 벡터 없애고 ClearCollisionList로...
	*/
		m_attackCollider->ClearCollisionList();
	}
	
	m_mapMonsterCollider.clear();

}

void CPlayer::Attack()
{
	// 노티파이로 검을 내려치는 타이밍에 호출된다.
	
	if (m_useSkill == ESkill::Judgement)
	{
		// mp가 부족해도 리턴
		if (m_ability.MP < 30)
		{
			AttackEnd();
		}

		// 이전 비율을 구해놓는다.
		float prevMP = m_ability.MP / (float)m_ability.MPMax;

		// 실제 MP 조정
		m_ability.MP -= 30;

		// MP UI 조정
		m_scene->FindWidget<CMainHUD>("MainHUD")
			->SetMP(m_ability.MP / (float)m_ability.MPMax, prevMP);



		m_scene->GetSceneResource()->SoundPlay("JudgementUse");

		// 저지먼트는 여기서 충돌체를 삭제해서 타겟 수에 영향받지 않게 한다.

		if (m_attackCollider)
		{
			if (m_attackCollider->GetActive())
				m_attackCollider->SetActive(false);

			m_attackCollider->ClearCollisionList();
		}

		m_mapMonsterCollider.clear();
	}
	else
	{
		// 검 휘두르는 사운드 재생
		m_scene->GetSceneResource()->SoundPlay("Attack");
	}

	// 목소리 낼지말지 확률
	int random = (rand() % 2) + 1;  // 1 ~ 2

	// 방향과 패턴에 따라 다른 공격 이펙트 생성
	if (m_playerDir == 1)
		switch (m_attackPattern)
		{
		case 1:
		{
			if(random == 1)
				m_scene->GetSceneResource()->SoundPlay("AttackVoice1");
			CEffect* effect = m_scene->CreateObject<CEffect>("LeftAttackEffect1");
			effect->SetPos(m_pos + Vector2(45.f, 9.f));
			effect->AddAnimation("LeftAttackEffect1", false, 0.12f);
			break;
		}
		case 2:
		{
			if (random == 1)
				m_scene->GetSceneResource()->SoundPlay("AttackVoice2");
			CEffect* effect = m_scene->CreateObject<CEffect>("LeftAttackEffect2");
			effect->SetPos(m_pos + Vector2(60.f, 17.f));
			effect->AddAnimation("LeftAttackEffect2", false, 0.12f);
			break;
		}
		case 3:
		{
			if (random == 1)
				m_scene->GetSceneResource()->SoundPlay("AttackVoice3");
			CEffect* effect = m_scene->CreateObject<CEffect>("LeftAttackEffect3");
			effect->SetPos(m_pos + Vector2(55.f, 25.f));
			effect->AddAnimation("LeftAttackEffect3", false, 0.12f);
			break;
		}
		case 4:
		{
			if (random == 1)
				m_scene->GetSceneResource()->SoundPlay("AttackVoice4");
			CEffect* effect = m_scene->CreateObject<CEffect>("LeftAttackEffect4");
			effect->SetPos(m_pos + Vector2(80.f, 25.f));
			effect->AddAnimation("LeftAttackEffect4", false, 0.12f);
			break;
		}
		}
	else
	{
		switch (m_attackPattern)
		{
		case 1:
		{
			if (random == 1)
				m_scene->GetSceneResource()->SoundPlay("AttackVoice1");
			CEffect* effect = m_scene->CreateObject<CEffect>("RightAttackEffect1");
			effect->SetPos(m_pos + Vector2(-45.f, 9.f));
			effect->AddAnimation("RightAttackEffect1", false, 0.12f);
			break;
		}
		case 2:
		{
			if (random == 1)
				m_scene->GetSceneResource()->SoundPlay("AttackVoice2");
			CEffect* effect = m_scene->CreateObject<CEffect>("RightAttackEffect2");
			effect->SetPos(m_pos + Vector2(-60.f, 17.f));
			effect->AddAnimation("RightAttackEffect2", false, 0.12f);
			break;
		}
		case 3:
		{
			if (random == 1)
				m_scene->GetSceneResource()->SoundPlay("AttackVoice3");
			CEffect* effect = m_scene->CreateObject<CEffect>("RightAttackEffect3");
			effect->SetPos(m_pos + Vector2(-55.f, 25.f));
			effect->AddAnimation("RightAttackEffect3", false, 0.12f);
			break;
		}
		case 4:
		{
			if (random == 1)
				m_scene->GetSceneResource()->SoundPlay("AttackVoice4");
			CEffect* effect = m_scene->CreateObject<CEffect>("RightAttackEffect4");
			effect->SetPos(m_pos + Vector2(-80.f, 25.f));
			effect->AddAnimation("RightAttackEffect4", false, 0.12f);
			break;
		}
		}
	}
	
	if (m_useSkill == ESkill::SlashBlast)
	{
		CColliderBox* collider;
		collider = AddCollider<CColliderBox>("PlayerAttack");
		collider->SetExtent(85.f, 80.f);
		collider->SetOffset(m_playerDir * 65.f, -35.f);
		collider->SetCollisionProfile("PlayerAttack");

		collider->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::CollisionBeginAttack);
		collider->SetCollisionEndFunction<CPlayer>(this, &CPlayer::CollisionEndAttack);
		
		m_vecAttackCollider.push_back(collider);

		//// 공격 충돌체를 만들어낸다.
		//m_attackCollider = AddCollider<CColliderBox>("PlayerAttack");
		//m_attackCollider->SetExtent(85.f, 80.f);
		//m_attackCollider->SetOffset(m_playerDir * 65.f, -35.f);
		//m_attackCollider->SetCollisionProfile("PlayerAttack");

		//m_attackCollider->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::CollisionBeginAttack);
		//m_attackCollider->SetCollisionEndFunction<CPlayer>(this, &CPlayer::CollisionEndAttack);
	}
	else if (m_useSkill == ESkill::Judgement)
	{
		// 매번 이펙트를 출력한다
		m_effect = m_scene->CreateObject<CEffect>("PlayerRightJudgementEffect");
		m_effect->SetPos(m_pos);
		m_effect->AddAnimation("PlayerRightJudgementEffect", false, 0.3);

		// 공격 충돌체를 만들어낸다.
		m_attackCollider = AddCollider<CColliderBox>("PlayerAttack");
		m_attackCollider->SetExtent(500.f, 150.f);
		m_attackCollider->SetOffset(0, -35.f);
		m_attackCollider->SetCollisionProfile("PlayerAttack");

		m_attackCollider->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::CollisionBeginAttack);
		m_attackCollider->SetCollisionEndFunction<CPlayer>(this, &CPlayer::CollisionEndAttack);
	}
	else if (m_useSkill == ESkill::Justice)
	{
		m_attackCnt = 1;

		// 1타 공격 사운드 
		m_scene->GetSceneResource()->SoundPlay("JusticeUse1");

		// 공격 충돌체를 만들어낸다.
		m_attackCollider = AddCollider<CColliderBox>("PlayerAttack");
		m_attackCollider->SetExtent(300.f, 400.f);
		m_attackCollider->SetOffset(m_playerDir * 85.f, -30.f);
		m_attackCollider->SetCollisionProfile("PlayerAttack");

		m_attackCollider->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::CollisionBeginAttack);
		m_attackCollider->SetCollisionEndFunction<CPlayer>(this, &CPlayer::CollisionEndAttack);
	}
	else 
	{
		// 공격 충돌체를 만들어낸다.
		m_attackCollider = AddCollider<CColliderBox>("PlayerAttack");
		m_attackCollider->SetExtent(85.f, 80.f);
		m_attackCollider->SetOffset(m_playerDir * 65.f, -35.f);
		m_attackCollider->SetCollisionProfile("PlayerAttack");

		m_attackCollider->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::CollisionBeginAttack);
		m_attackCollider->SetCollisionEndFunction<CPlayer>(this, &CPlayer::CollisionEndAttack);
	}

	//// 노티파이로 지정된 프레임에 호출되도록 한다.
	//// 특정 프레임에 이 함수가 호출됨으로써 불릿이 생성된다.
	//CBullet* bullet = m_scene->CreateObject<CBullet>("Bullet");

	//bullet->SetAngle(m_gunAngle);

	//bullet->SetPos(m_gunPos);
	//
	//// 플레이어가 발사하는 불릿의 데미지를 설정한다.
	//bullet->SetDamage(30.f);

	//// 불릿의 충돌체 및 충돌 프로파일을 설정한다.
	//CCollider* bulletCol = bullet->FindCollider("Body");
	//bulletCol->SetCollisionProfile("PlayerAttack");
}

void CPlayer::Attack2()
{
	// 1타의 충돌체를 지워준다.
	if (m_attackCollider)
	{
		if (m_attackCollider->GetActive())
			m_attackCollider->SetActive(false);
	}

	if(m_useSkill == ESkill::Justice)
	{
		m_justiceState = ESkillState::Normal;

		m_attackCnt = 2;

		// 2타 공격 사운드 
		m_scene->GetSceneResource()->SoundPlay("JusticeUse2");

		// 공격 충돌체를 만들어낸다.
		m_attackCollider = AddCollider<CColliderBox>("PlayerAttack");
		m_attackCollider->SetExtent(300.f, 400.f);
		m_attackCollider->SetOffset(m_playerDir * 85.f, -30.f);
		m_attackCollider->SetCollisionProfile("PlayerAttack");

		m_attackCollider->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::CollisionBeginAttack);
		m_attackCollider->SetCollisionEndFunction<CPlayer>(this, &CPlayer::CollisionEndAttack);
	}
}

void CPlayer::CollisionBegin(CCollider* _src, CCollider* _dest)
{
	// 플레이어 충돌체가 충돌되면 호출됨
	
	if (_dest->GetName() == "Npc")
	{
		m_interactiveNpc = _dest->GetOwner();

		return;
	}


	if (_dest->GetName() == "Item")
	{
		m_gainableItemList.push_back((CItem*)_dest->GetOwner());

		return;
	}
	if (_dest->GetName() == "HPPotion")
	{
		m_gainableHPPotionList.push_back((CHPPotion*)_dest->GetOwner());

		return;
	}
	if (_dest->GetName() == "MPPotion")
	{
		m_gainableMPPotionList.push_back((CMPPotion*)_dest->GetOwner());

		return;
	}

	// 상대방 충돌체가 '지형' 충돌체라면 리턴한다.
	if (_dest->GetName() == "Ground")
	{
		// 업데이트에서 플레이어의 위치를 보정하기 위해 지형 받아옴
		m_LadderCollider = _dest;

		// 스킬 사용 등으로 이동속도 바뀌었을 때를 대비해 복구
		m_jumpVelocity = 35.f;

		return;
	}

	// 현재 무적 상태라면 리턴한다.
	if (m_grace)
		return;

	// 상대방 충돌체가 '인식' 충돌체라면 리턴한다.
	if (_dest->GetName() == "Cognition")
		return;

	// 상대방 충돌체가 '몬스터' 충돌체라면 
	else if (_dest->GetProfile()->Channel == ECollisionChannel::Monster)
	{
		// 이 함수가 호출이 잘 되는지 확인하기 위한 음성
		// m_scene->GetSceneResource()->SoundPlay("Gabung");

		//// 체력 ui 조정
		//m_scene->FindWidget<CCharacterHUD>("CharacterHUD")
		//	->SetHP(m_ability.HP / (float)m_ability.HPMax);

		//// 현재 무적상태가 아닐 경우 무적상태로 전환 및 1.5초의 무적시간 부여
		//if (!m_grace)
		//{
		//	m_grace = true;
		//	m_graceTime =2.0f;
		//}

		//// 경계상태 전환 및 7초 갱신
		//m_alert = true;
		//m_alertTime = 7.f;

		//// 이건 캐릭터에 붙어있는 위젯컴포넌트 체력바를 조정하는 것
		//m_HPBar->GetWidget<CProgressBar>()->SetValue(m_ability.HP / (float)m_ability.HPMax);
	
	}
}

void CPlayer::CollisionBeginAttack(CCollider* _src, CCollider* _dest)
{
	// 충돌하자마자 삭제해서 추가적인 충돌을 방지
	// 저지먼트는 여기서 삭제하면 안됨
	if (m_useSkill != ESkill::Judgement)
	{
		size_t size = m_vecAttackCollider.size();

		for (int i = 0; i < size; ++i)
		{
			m_vecAttackCollider[i]->SetActive(false);
		}

		if (m_attackCollider)
			m_attackCollider->SetActive(false);
	}

	// 진짜씨빨 이거하려고 얼마나..
	if (m_useSkill == ESkill::SlashBlast)
	{
		if (m_mapMonsterCollider.size() < 6)
		{
			// 이미 충돌중인 몬스터와 충돌이라면 리턴한다.
			auto	iter = m_mapMonsterCollider.find(_dest->GetOwner()->GetName());

			if (iter != m_mapMonsterCollider.end())
				return;

			// 몬스터 충돌체 정보를 추가한다.
			m_mapMonsterCollider.insert(std::make_pair(_dest->GetOwner()->GetName(), _dest));
		}
		// 타겟이 6마리를 넘어가도 리턴한다.
		else
			return;
	}
	else
	{
		// 몬스터 충돌체 정보를 추가한다.
		m_mapMonsterCollider.insert(std::make_pair(_dest->GetOwner()->GetName(), _dest));


		// 첫번째(가장 먼저 충돌한) 몬스터만 공격
		// 저지먼트, 저스티스는 예외
		if ((m_mapMonsterCollider.begin()->second != _dest) && (m_useSkill != ESkill::Judgement) && (m_useSkill != ESkill::Justice))
			return;
	}
	

	if (m_useSkill == ESkill::Attack)
	{
		// 방향에 따라 다른 히트 이펙트 생성
		if (m_playerDir == 1)
		{
			// 충돌과 동시에 히트 이펙트를 생성한다. Once이므로 1번 재생 후 삭제될 것이다.
			CEffect_2* effect = m_scene->CreateObject<CEffect_2>("LeftHitEffect");

			// 이펙트의 위치는 히트 포인트(충돌 영역 중간)로 할 것이다.
			// 이 충돌체는 금방 사라지기 때문에 히트 포인트는 _dest 충돌체의 것으로 한다.
			effect->SetPos(_dest->GetHitPoint()+Vector2(m_playerDir * 15.f, 5.f));

			// 애니메이션 추가 (애니메이션 이름, 루프여부, 플레이타임)
			effect->AddAnimation("LeftHitEffect", false, 0.3f);
		}
		else
		{
			CEffect_2* effect = m_scene->CreateObject<CEffect_2>("RightHitEffect");

			effect->SetPos(_dest->GetHitPoint() + Vector2(m_playerDir * 15.f, 5.f));

			effect->AddAnimation("RightHitEffect", false, 0.3f);
		}

		/*
			 Damage 처리
			 플레이어 근접 공격 충돌체(_src)에 의해 _dest 충돌체가 속한 오브젝트에게
			 데미지를 입히도록 함수를 호출
		*/
		_dest->GetOwner()->InflictDamage(m_ability.DamageMax, m_playerDir);
	}
	else if (m_useSkill == ESkill::PowerStrike)
	{
		if(_dest->GetName() != "Machine")
			m_scene->GetSceneResource()->SoundPlay("PowerStrikeHit");

		CEffect_2* effect1 = m_scene->CreateObject<CEffect_2>("PowerStrikeHit");
		effect1->SetPos(_dest->GetHitPoint() + Vector2(m_playerDir * 20.f, -10.f));
		effect1->AddAnimation("PowerStrikeHit", false, 0.2f);

		_dest->GetOwner()->InflictDamage(m_ability.DamageMax * 3, m_playerDir);
	}
	else if (m_useSkill == ESkill::SlashBlast)
	{
		if (_dest->GetName() != "Machine")
			m_scene->GetSceneResource()->SoundPlay("SlashBlastHit");

		int random = (rand() % 3) + 1;

		CEffect_2* effect1 = m_scene->CreateObject<CEffect_2>("SlashBlastHit");
		effect1->SetPos(_dest->GetHitPoint()+Vector2(m_playerDir*30.f,1.f*random*20-20));
		effect1->AddAnimation("SlashBlastHit", false, 0.3f);
		
		// 연쇄적인 충돌체 생성을 위해
		CColliderBox* collider;
		collider = AddCollider<CColliderBox>("PlayerAttack");
		collider->SetExtent(85.f, 80.f);	
		
		// 씨발이것도진짜...
		if(m_playerDir == 1)
			collider->SetOffset((_dest->GetHitPoint().x+_dest->GetExtent().x)-m_pos.x-60.f, -35.f); 
		else
			collider->SetOffset(_dest->GetHitPoint().x - m_pos.x - 50.f, -35.f);
		
		/*collider->SetOffset(m_playerDir * (65.f + 70 * m_mapMonsterCollider.size()), -35.f);*/
		collider->SetCollisionProfile("PlayerAttack");

		collider->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::CollisionBeginAttack);
		collider->SetCollisionEndFunction<CPlayer>(this, &CPlayer::CollisionEndAttack);

		m_vecAttackCollider.push_back(collider);

		
		_dest->GetOwner()->InflictDamage(m_ability.DamageMax, m_playerDir);
	}
	else if (m_useSkill == ESkill::Judgement)
	{
		if (_dest->GetName() != "Machine")
			m_scene->GetSceneResource()->SoundPlay("JudgementHit");

		CEffect_2* effect1 = m_scene->CreateObject<CEffect_2>("JudgementHit");
		effect1->SetPos(_dest->GetHitPoint() + Vector2(m_playerDir * 20.f, -10.f));
		effect1->AddAnimation("JudgementHit", false, 0.2f);

		_dest->GetOwner()->InflictDamage(m_ability.DamageMax*0.5, m_playerDir);
	}
	else if (m_useSkill == ESkill::Justice)
	{
		// 1타일경우
		if (m_attackCnt == 1)
		{
			// 적을 공중에 띄운다.
			_dest->GetOwner()->Jump();
			_dest->GetOwner()->SetJumpVelocity(50);
		}
		// 2타일경우
		else if (m_attackCnt == 2)
		{
			// 적을 크게 넉백시킨다.
			m_scene->GetSceneResource()->SoundPlay("PowerStrikeHit");
			_dest->GetOwner()->SetMoveSpeed(500.f);
		}

		CEffect_2* effect1 = m_scene->CreateObject<CEffect_2>("JudgementHit");
		effect1->SetPos(_dest->GetHitPoint() + Vector2(m_playerDir * 20.f, -10.f));
		effect1->AddAnimation("JudgementHit", false, 0.2f);

		_dest->GetOwner()->InflictDamage(m_ability.DamageMax*1.5, m_playerDir);
	}
}

void CPlayer::CollisionEnd(CCollider* _src, CCollider* _dest)
{
	if (_dest->GetName() == "Npc")
		m_interactiveNpc = nullptr;

	if (_dest->GetName() == "Item")
	{
		auto iter = m_gainableItemList.begin();
		auto iterEnd = m_gainableItemList.end();

		for (; iter != iterEnd;)
		{
			if (_dest->GetOwner()->GetName() == iter->Get()->GetName())
			{
	            iter = m_gainableItemList.erase(iter);
				iterEnd = m_gainableItemList.end();
		 		continue;
			}
			++iter;
		}
		return;
	} 

	if (_dest->GetName() == "Item")
	{
		auto iter = m_gainableItemList.begin();
		auto iterEnd = m_gainableItemList.end();

		for (; iter != iterEnd;)
		{
			if (_dest->GetOwner()->GetName() == iter->Get()->GetName())
			{
				iter = m_gainableItemList.erase(iter);
				iterEnd = m_gainableItemList.end();
				continue;
			}
			++iter;
		}
		return;
	}

	if (_dest->GetName() == "HPPotion")
	{
		auto iter = m_gainableHPPotionList.begin();
		auto iterEnd = m_gainableHPPotionList.end();

		for (; iter != iterEnd;)
		{
			if (_dest->GetOwner()->GetName() == iter->Get()->GetName())
			{
	            iter = m_gainableHPPotionList.erase(iter);
				iterEnd = m_gainableHPPotionList.end();
		 		continue;
			}
			++iter;
		}
		return;
	} 

	if (_dest->GetName() == "MPPotion")
	{
		auto iter = m_gainableMPPotionList.begin();
		auto iterEnd = m_gainableMPPotionList.end();

		for (; iter != iterEnd;)
		{
			if (_dest->GetOwner()->GetName() == iter->Get()->GetName())
			{
				iter = m_gainableMPPotionList.erase(iter);
				iterEnd = m_gainableMPPotionList.end();
				continue;
			}
			++iter;
		}
		return;
	}

	if (_dest->GetName() == "Portal")
	{
		m_portalEnable.clear();
	}
}

void CPlayer::CollisionEndAttack(CCollider* _src, CCollider* _dest)
{
	if(m_useSkill != ESkill::Judgement)
		m_useSkill = ESkill::None;
}

void CPlayer::ResetPlayerCollider()
{
	m_playerCollider[0]->SetActive(false);
	m_playerCollider[1]->SetActive(false);

	/*
		충돌체를 지우는 것은 충돌을 체크할 때 (SceneCollision의 Collision함수)
		이므로, 위에서 충돌체를 제거한다고 해서 몬스터의 충돌 목록에 공격 충돌체가
		지워지지 않는다.

		따라서 ClearCollisionList을 이용해 지워준다.
	*/
	m_playerCollider[0]->ClearCollisionList();
	m_playerCollider[1]->ClearCollisionList();

	m_playerCollider.clear();

	CColliderBox* box = AddCollider<CColliderBox>("Head");

	box->SetExtent(50.f, 42.f);  // 가로세로 크기
	box->SetOffset(3.f, -50.f);	 // 오너(플레이어 발밑 pos)로부터 얼마나 떨어져 있을 지
	box->SetCollisionProfile("Player");  // 충돌 프로파일 설정 : Player 

	// Head와 충돌 시 호출할 함수 등록
	box->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::CollisionBegin);
	box->SetCollisionEndFunction<CPlayer>(this, &CPlayer::CollisionEnd);

	// 벡터에 추가한다
	m_playerCollider.push_back(box);


	// Body 라는 (레퍼런스)이름의 박스 충돌체를 만든다.
	box = AddCollider<CColliderBox>("Body");

	box->SetExtent(36.f, 31.f);
	box->SetOffset(3.f, -13.5f);
	box->SetCollisionProfile("Player");

	// body와 충돌 시 호출할 함수 등록
	box->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::CollisionBegin);
	box->SetCollisionEndFunction<CPlayer>(this, &CPlayer::CollisionEnd);

	// 벡터에 추가한다
	m_playerCollider.push_back(box);
}

bool CPlayer::SortX(const CSharedPtr<class CCollider>& _src, const CSharedPtr<class CCollider>& _dest)
{
	float	srcX = _src->GetOwner()->GetPos().x;
	float	destX = _dest->GetOwner()->GetPos().x;

	// 플레이어가 오른쪽을 보고 있을 경우, 몬스터는 x좌표가 작은 순으로 정렬
	if (true)
	{
		return srcX < destX;
	}
	// 플레이어가 왼쪽을 보고 있을 경우, 몬스터는 x좌표가 큰 순으로 정렬
	else 
	{
		return srcX > destX;
	}
}

CPlayer::CPlayer()
	: /*m_gunAngle(0.f)
	, m_gunLength(0.0)
	, m_gunPos()
	,*/
	m_attackCollider(nullptr)
	, m_grace(false)
	, m_useSkill(ESkill::None)
{
	// 객체 생성 시 타입 아이디(레퍼런스 클래스의 멤버)를 초기화
	SetTypeID<CPlayer>();

	m_renderLayer = ERenderLayer::Player;

	m_powerStrikeState = ESkillState::Normal;
	m_slashBlastState = ESkillState::Normal;
	m_judgementState = ESkillState::Normal;
	m_justiceState = ESkillState::Normal;

	widgetCnt = 0;
}

CPlayer::CPlayer(const CPlayer& _obj)
	: CCharacter(_obj)
{
}

CPlayer::~CPlayer()
{
	CInput::GetInst()->DeleteBindFunction<CPlayer>("Portal", EInputType::DOWN, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer>("MoveFront", EInputType::PUSH, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer>("MoveBack", EInputType::PUSH, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer>("GunRotation", EInputType::PUSH, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer>("GunRotationInv", EInputType::PUSH, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer>("Fire", EInputType::DOWN, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer>("Skill1", EInputType::DOWN, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer>("Skill2", EInputType::DOWN, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer>("Jump", EInputType::DOWN, this);

	CInput::GetInst()->DeleteBindFunction<CPlayer>("PowerStrike", EInputType::DOWN,this);
	CInput::GetInst()->DeleteBindFunction<CPlayer>("SlashBlast", EInputType::DOWN, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer>("Judgement", EInputType::DOWN, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer>("Judgement", EInputType::UP, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer>("Justice", EInputType::DOWN, this);
	CInput::GetInst()->DeleteBindFunction<CPlayer>("Inventory", EInputType::DOWN, this);
}
