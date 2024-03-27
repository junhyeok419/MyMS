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

	m_moveSpeed = 150.f;  //150 �⺻��

	/*m_gunAngle = 0.f;
	m_gunLength = 70.f;*/
	
	//// �⺻ �ɷ�ġ ����
	//PlayerAbility::HP = 2000;  
	//PlayerAbility::HPMax = 2000; //�⺻ 2000
	//PlayerAbility::MP = 10000;
	//PlayerAbility::MPMax = 10000;  // �⺻ 1000
	//PlayerAbility::EXP = 0.f;
	//PlayerAbility::EXPMax = EXPTable[0];
	//PlayerAbility::DamageMin = 200;  // 200
	//PlayerAbility::DamageMax = 400; // 400
	//PlayerAbility::Level = 1;

	/*
		���� ���ӸŴ����� �ƴ� ������Ʈ ������ Init����
		�ʱ�ȭ �ϵ��� �Ѵ�.
	*/
 	SetPos(500.f, 0.f);
	SetSize(85.f, 75.f);
	SetPivot(0.5f, 1.f);	// �Ǻ��� �� �� ���߾����� �����.

	//m_satelAngle[0] = 0.f;
	//m_satelAngle[1] = 120.f;
	//m_satelAngle[2] = 240.f;

	//m_satelLength = 100.f;
	//m_satelLengthMin = 100.f;
	//m_satelLengthMax = 200.f;

	//m_satelRotationSpeed = 60.f;

	//m_satelSkillOn = false;
	//m_satelSkillTime = 0.f;
	//m_satelSkillDir = 1.f;	// 'Ȯ��' ����

	/*
		��ų�� ���� ��ٿ� ���� ���
		1��° ��ų(����̵�)�� 5��,
		2��° ��ų(����)�� 10���� ��ٿ��� ����
	*/
	SkillCoolDownInfo info = {};
	
	info.coolDown = 5.f;
	m_vecCoolDown.push_back(info);

	info.coolDown = 10.f;
	m_vecCoolDown.push_back(info);

	//// ���� ��ü 3���� �����Ѵ�.
	//for (int i = 0; i < 3; ++i)
	//{	
	//	// ���� ��ü�� �����Ѵ�.
	//	m_satellite[i] = m_scene->CreateObject<CSatellite>("Satellite");

	//	// ������ ��ġ�� �÷��̾ �������� ��´�.
	//	Vector2 pos;
	//	pos.x = m_pos.x + cosf(DegreeToRadian(m_satelAngle[i])) * m_satelLength;
	//	pos.y = m_pos.y + sinf(DegreeToRadian(m_satelAngle[i])) * m_satelLength;
	//	m_satellite[i]->SetPos(pos);
	//}

	// �� ������Ʈ�� �ִϸ��̼��� �����Ѵ�.
	CreateAnimation();

	// �ִϸ��̼��� �߰��Ѵ�. 
	AddAnimation("PlayerRightStand",true, 2.f);   // ������ ��������
	AddAnimation("PlayerRightWalk");	// ������ �̵�
	AddAnimation("PlayerRightAttack1", false, 0.7f);  // ������ ����1 (���� 1ȸ�� 0.9��)
	AddAnimation("PlayerRightAttack2", false, 0.7f);  // ������ ����2 
	AddAnimation("PlayerRightAttack3", false, 0.7f);  // ������ ����3 
	AddAnimation("PlayerRightAttack4", false, 0.7f);  // ������ ����4
	AddAnimation("PlayerRightAlert", true, 2.f);   // ������ ������
	AddAnimation("PlayerRightJump", false, 1.f);   // ������ ����
	AddAnimation("PlayerRightJudgement", true, 0.3f);   // ������Ʈ ���
	AddAnimation("PlayerRightJustice", false, 0.8f);   // ������ ����Ƽ�� ���

	AddAnimation("PlayerRope", true, 0.7f);   // ����Ÿ��
	AddAnimation("PlayerRopeStand", false);   // ��������
	AddAnimation("PlayerLadder", true, 0.7f);   // ��ٸ�Ÿ��
	AddAnimation("PlayerLadderStand", false);   // ��ٸ�����

	AddAnimation("PlayerLeftStand", true, 2.f);		// ���� ��������
	AddAnimation("PlayerLeftWalk");		// ���� �̵�
	AddAnimation("PlayerLeftAttack1", false, 0.7f);	 // ���� ����1
	AddAnimation("PlayerLeftAttack2", false, 0.7f);	 // ���� ����2
	AddAnimation("PlayerLeftAttack3", false, 0.7f);	 // ���� ����3
	AddAnimation("PlayerLeftAttack4", false, 0.7f);	 // ���� ����4
	AddAnimation("PlayerLeftAlert", true, 2.f);   // ���� ������
	AddAnimation("PlayerLeftJump", false, 1.f);   // ���� ����
	AddAnimation("PlayerLeftJustice", false, 0.8f);   // ���� ����Ƽ�� ���

	// AttackEnd�� ���� �Լ��� �����Ͽ� ������ �������� �����ϰ� �Ѵ�.
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


	// 1 �����ӿ� Attack�� ��Ƽ���̷� �����Ͽ� ����ġ�� �����ӿ� ���� ������ ������ �Ѵ�.
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

	// Ű��Ʈ�� �����ʰ� �������� ������ �����Ѵ�.
	m_vecSequenceKey[0].push_back("PlayerRightStand");
	m_vecSequenceKey[0].push_back("PlayerRightWalk");
	// [2] ~ [5] �⺻ ���ݸ��
	m_vecSequenceKey[0].push_back("PlayerRightAttack1");
	m_vecSequenceKey[0].push_back("PlayerRightAttack2");
	m_vecSequenceKey[0].push_back("PlayerRightAttack3");
	m_vecSequenceKey[0].push_back("PlayerRightAttack4");
	// [6] �����
	m_vecSequenceKey[0].push_back("PlayerRightAlert");
	// [7] �������
	m_vecSequenceKey[0].push_back("PlayerRightJump");

	m_vecSequenceKey[1].push_back("PlayerLeftStand");
	m_vecSequenceKey[1].push_back("PlayerLeftWalk");
	m_vecSequenceKey[1].push_back("PlayerLeftAttack1");
	m_vecSequenceKey[1].push_back("PlayerLeftAttack2");
	m_vecSequenceKey[1].push_back("PlayerLeftAttack3");
	m_vecSequenceKey[1].push_back("PlayerLeftAttack4");
	m_vecSequenceKey[1].push_back("PlayerLeftAlert");
	m_vecSequenceKey[1].push_back("PlayerLeftJump");

	m_playerDir = 1;	// �⺻ ������ ���� ����.

	m_attack = false;   // ������ �ƴ� ����
	m_alert = false;	// �⺻ ���� ����
	/*
		�浹ü�� �߰��ϴ� �κ��̴�.
		�÷��̾��� �Ӹ��� ������ ������ �浹ü�� ���� ���̴�.
		 
		* ũ�� �� offset�� ������ '�˾�'�� �̿��ϸ�
		�̹����� �ȼ� ���� ��ǥ�� �� �� �־� ���ϴ�. 
	*/
	// Head ��� �̸��� �ڽ� �浹ü�� �����.
	CColliderBox* box = AddCollider<CColliderBox>("Head");

	box->SetExtent(50.f, 42.f);  // ���μ��� ũ��
	box->SetOffset(3.f, -50.f);	 // owner(�÷��̾� �߹� pos)�κ��� �󸶳� ������ ���� ��
	box->SetCollisionProfile("Player");  // �浹 �������� ���� : Player 

	// Head�� �浹 �� ȣ���� �Լ� ���
	box->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::CollisionBegin);
	box->SetCollisionEndFunction<CPlayer>(this, &CPlayer::CollisionEnd);

	// ���Ϳ� �߰��Ѵ�
	m_playerCollider.push_back(box);


	// Body ��� �̸��� �ڽ� �浹ü�� �����.
	box = AddCollider<CColliderBox>("Body");
	box->SetExtent(36.f, 31.f);
	box->SetOffset(3.f, -13.5f);
	box->SetCollisionProfile("Player");

	// body�� �浹 �� ȣ���� �Լ� ���
	box->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::CollisionBegin);
	box->SetCollisionEndFunction<CPlayer>(this, &CPlayer::CollisionEnd);
	
	// ���Ϳ� �߰��Ѵ�
	m_playerCollider.push_back(box);

	/*
		���ε�Ű�� �Լ��� ����Ѵ�. �Ʒ��� ���, 
		1. ����� �Լ��� ȣ��Ǵ� ���ε�Ű�� �̸��� "MoveFront"�̴�.
		2. InputType�� PUSH�� ��� ȣ��Ǵ� �Լ��̴�.
		3. ���� CPlayer ��ü�� �ּ��̴�.
		4. MoveFront �Լ��� �ּ��̴�.

		���ݰ� ��ų�� ���, InputType�� DOWN���� ����Ͽ�
		�������� �߻���� �ʰ� �ٲ۴�.
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

	

	//// hp�� ���� ������Ʈ ����
	//m_HPBar = CreateWidgetComponent<CProgressBar>("HPBar");

	//// �ؽ��� �� ũ��, ��ġ ����
	//m_HPBar->GetWidget<CProgressBar>()->SetTexture(EProgressBar_Texture_Type::Bar,
	//	"HPBar", TEXT("CharacterHPBar.bmp"));
	//m_HPBar->GetWidget<CProgressBar>()->SetSize(50.f, 10.f);
	//m_HPBar->SetPos(-25.f, -90.f);

	
	// �̸�ǥ ����
	m_nameBarFrame = CreateWidgetComponent<CImageWidget>("NameBarPlayer");
	m_nameBarFrame->GetWidget<CImageWidget>()->SetTexture("NameBarPlayer", TEXT("Maple/UI/Basic/Name/NameBar_Player.bmp"));
	m_nameBarFrame->GetWidget<CImageWidget>()->SetColorKey(255, 0, 255);
	m_nameBarFrame->GetWidget<CImageWidget>()->SetSize(56.f, 15.f);
	m_nameBarFrame->SetPos(-25.f, 0.f);

	// �̷��� �÷��̾ �����ɶ����� ���� ��������ߵ�!!!
	m_scene->FindWidget<CMainHUD>("MainHUD")
		->SetHP2(CPlayer::m_ability.HP / CPlayer::m_ability.HPMax);

	m_scene->FindWidget<CMainHUD>("MainHUD")
		->SetMP2(CPlayer::m_ability.MP / CPlayer::m_ability.MPMax);

	m_scene->FindWidget<CMainHUD>("MainHUD")
		->SetEXP2(CPlayer::m_ability.EXP / CPlayer::m_ability.EXPMax);

	// �߷� ���� on
	SetPhysicsSimulate(true);
	// ���� �ӵ� ���� 30
	SetJumpVelocity(35.f);


	return true;
}

void CPlayer::Update(float _deltaTime)
{
	CCharacter::Update(_deltaTime);


	// SetJumpVelocity(50.f);
	m_objDir = m_playerDir;

	// �� �����¿��� ������ ������ 1�ʸ��� �ִ�ü���� 1% ȸ���Ѵ�
	if (!m_alert)
	{
		m_healTime += _deltaTime;

		if (m_healTime > 1.5f)
		{
			if (PlayerAbility::HPMax > (PlayerAbility::HP + PlayerAbility::HPMax * 0.01f))
			{
				// �ѹ� ȸ���ϸ� �ٽ� ����
				m_healTime = 0.f;

					PlayerAbility::HP += PlayerAbility::HPMax * 0.01f;

					// ���� ������ ���س��´�.
					float prevHP = PlayerAbility::HP / (float)PlayerAbility::HPMax;

					// ü�� ui ����
					m_scene->FindWidget<CMainHUD>("MainHUD")
					->SetHP(PlayerAbility::HP / (float)PlayerAbility::HPMax, prevHP);


				// ȸ�� ���� �Ӹ����� ����
				std::vector<std::wstring> vecFileName;
				for (int i = 0; i <= 9; ++i)
				{
					TCHAR	FileName[MAX_PATH] = {};
					// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
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
		// �����̸� ó������ �ٽ� 1�� ī��Ʈ
		else if (m_move.x > 0.f)
		{
			m_healTime = 0.f;
		}
	}

	
	// �ͼ��� ������ 1��
	if (m_judgementDelay > 0.f)
	{
		m_judgementDelay -= _deltaTime;
	}

	// ��ٸ��� �ӵ� ������
	if (m_ladder)
	{
		m_moveSpeed = 75.f;
		// ���Ƶξ��� upŰ Ȱ��ȭ
		SetEnableUpKey(true);
	}
	else
		m_moveSpeed = 150.f; // 150

	// ������Ʈ ���� �Ͻ��� �ӵ� ����
	if (m_useSkill == ESkill::Judgement)
		m_moveSpeed = 250.f;

	// ��ų ���� ����Ʈ ��ġ�� ����ֱ� ����
	if (m_useSkill == ESkill::PowerStrike)
	{
		m_effect->SetPos(m_pos + Vector2(10.f * m_playerDir, -35.f));
	}
	else if(m_effect)
		m_effect->SetPos(m_pos);
	


	// �� ������ ���� = ��ų�� ����
	size_t size = m_vecCoolDown.size();

	_deltaTime *= m_timeScale;

	for (size_t i = 0; i < size; ++i)
	{
		// ���� ��ų�� ��ٿ��� �����ִٸ�
		if (m_vecCoolDown[i].coolDownEnable)
		{
			// �������� �ð���ŭ �����Ѵ�.
			m_vecCoolDown[i].coolDown -= _deltaTime;

			// ��ٿ��� 0�� �����ߴٸ�, ��ٿ� '����'���� �ٲ۴�.
			if (m_vecCoolDown[i].coolDown <= 0.f)
				m_vecCoolDown[i].coolDownEnable = false;
		}
	}

	

	// ������ ���ӽð��� üũ�Ѵ�. �ð��� ������ false�� �ٲ� �� ���̴�. 
	if (m_alert)
	{
		// ȸ���ð��� �پ���� �ʵ���
		m_healTime = 0.f;

		m_alertTime -= _deltaTime;

		if (m_alertTime <= 0.f)
		{
			m_alert = false;
		}
	}

	// �������� ���ӽð��� üũ�Ѵ�. 
	if (m_grace)
	{
		m_graceTime -= _deltaTime;

		if (m_graceTime <= 0.f)
		{
			/*
				�̷��� �÷��̾� �浹ü�� ����->��������� ������
				���Ϳ� �浹�� �����ϰ� �־ ü���� �ѹ��ۿ� ������ �ʴ´�.
			*/
			ResetPlayerCollider();
			m_grace = false;
			m_scene->SetGrace(false);
		}
	}

	//// ���� ��ġ�� �Ź� ������Ʈ�Ѵ�. 
	//m_gunPos.x = m_pos.x + cosf(DegreeToRadian(m_gunAngle)) * m_gunLength;
	//m_gunPos.y = m_pos.y + sinf(DegreeToRadian(m_gunAngle)) * m_gunLength;

	//// ������ Ȱ��ȭ ������ ���
	//if (m_satelSkillOn)
	//{
	//	// ������ �˵��� dir�� ���� ���� �����ų� ������.
	//	m_satelLength += m_satelSkillDir * 
	//		(m_satelLengthMax - m_satelLengthMin) / 2.f * _deltaTime;

	//	// ������ �˵��� �ִ� ������ �����ϰų� ������ ������ �ִ�� �������ش�.
	//	if (m_satelLength >= m_satelLengthMax)
	//		m_satelLength = m_satelLengthMax;

	//	// ������ �˵��� �ּ� ������ �����ϰų� ������ ������ �ּҷ� �������ְ�
	//	else if (m_satelLength <= m_satelLengthMin)
	//	{
	//		// ������ ��Ȱ��ȭ ���·� �ٲٸ�, ȸ���ӵ��� �⺻������ �����Ѵ�. 
	//		m_satelRotationSpeed = 60.f;
	//		m_satelLength = m_satelLengthMin;
	//		m_satelSkillOn = false;
	//	}

	//	m_satelSkillTime += _deltaTime;

	//	// ������ ���ӽð��� 5�ʰ� ������ (���ӽð��� ����ϸ�)
	//	if (m_satelSkillTime >= 5.f)
	//	{
	//		// ������ �˵��� '���' ���·� �ٲ۴�.
	//		m_satelSkillDir = -1.f;
	//	}
	//}

	//// ������ ��ġ�� �Ź� ������Ʈ�Ѵ�.
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
		�̰��� ���⿡�� ������ �ִ� ������,
		���� �浹ü�� �ʹ� ���� ���� �ð����� �����ϴ� ��찡
		����� ������ ������ ������ �ֱ� �����̴�.

		* �ϴ� �浹ü�� ���̵��� �ּ��ɾ����
	*/
	if (m_attackCollider)
	{
		if (m_attackCollider->GetActive())
			m_attackCollider->SetActive(false);
	}


	// �÷��̾ ������ ������ ���
	if (m_playerDir == 1)
	{
		// �̵����� 0�̶�� ���� ���������� �̵��� ����ٴ� ���̴�.
		if (m_move.x < 0.f)
			m_playerDir = -1;
	}
	// �÷��̾ ������ ������ ���
	else
	{
		// �̵����� 0�̶�� ���� ���������� �̵��� ����ٴ� ���̴�.
		if (m_move.x > 0.f)
			m_playerDir = 1;
	}

	int	AnimDirIndex = 0;

	if (m_playerDir == -1)
		AnimDirIndex = 1;

	//if (m_move.x != 0.f || m_move.y != 0.f)
	//{
	//	// �̵��� �� ��� �������̴��� ������ ����Ѵ�.
	//	m_attack = false;
	//	ChangeAnimation(m_vecSequenceKey[AnimDirIndex][1]);
	//}
	
		
	if (m_ladder)
	{
		if (m_move.y != 0.f)
		{
			// �̵� ������� ��ȯ
			ChangeAnimation("PlayerLadder");
		}
		else
			ChangeAnimation("PlayerLadderStand");

		return;
	}

	if (m_jump && !m_attack)
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][7]);
	// �̵����� 0�� �ƴ� ��� = �����̰� ���� ��� and �������� �ƴҰ�쿡��(�̵��߿� ������ ��������)
	else if ((m_move.x != 0.f || m_move.y != 0.f) && !m_attack)
	{
		// �̵� ������� ��ȯ
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][1]);
	}
	// �������� �ƴϰ� �����°� �ƴϸ� ����������� ��ȯ
	else if (!m_attack && !m_alert)
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][0]);
	// �������� �ƴϰ� �����¸� ��������� ��ȯ
	else if (!m_attack && m_alert)
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][6]);
	
	// �÷��̾� ��ġ ����
	if (m_ladder)
	{
		SetPos(m_LadderCollider->GetLineInfo().Point1.x, m_pos.y);
	}
}

void CPlayer::Render(HDC _hDC, float _deltaTime)
{
	// �ǰ� �� �������� ǥ���ϱ� ����
	
	// ���������ϰ��
	if (m_grace)
	{
		// 0.00001�ʵ��� �׸��� �ʴ´�.
		if (m_graceRender < 0.00001f)
		{
			m_graceRender += _deltaTime;
			return;
		}
	}

	// �ѹ� �׸���
	CCharacter::Render(_hDC, _deltaTime);
	
	// �ٽ� �ð� �ʱ�ȭ
	m_graceRender = 0.f;


	/* 
		�÷��̾ ������ ��(��)�� �׸���.
		���� �� ������Ʈ���� �÷��̾� ��ġ(pos)�� Ű �Է¿� ���� 
		��ȭ�� ��ġ�� ���ŵǹǷ�, �� ��ġ(gunPos)�� ���� �׷����� �ȴ�.
	*/ 
	
	/*
		ī�޶� ���� �� ���� ���� ��ġ�� ī�޶� ��ġ�� ���� �������
		��ġ�� �ٲ�Ƿ� �Ʒ��� ���� ����Ѵ�.
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

	
	// ���� ������ ���س��´�.
	float prevHP = m_ability.HP / (float)m_ability.HPMax;

	// ���� ü�� ����
	if (0 > m_ability.HP - _damage)
		m_ability.HP = 0;
	else
	{
		m_ability.HP -= _damage;
	}
	

	// ü�� ui ����
	m_scene->FindWidget<CMainHUD>("MainHUD")
		->SetHP(m_ability.HP / (float)m_ability.HPMax , prevHP);

	//// �̰� ĳ���Ϳ� �پ��ִ� ����������Ʈ ü�¹ٸ� �����ϴ� ��
	//m_HPBar->GetWidget<CProgressBar>()->SetValue(m_ability.HP / (float)m_ability.HPMax);

	// ���� �������°� �ƴ� ��� �������·� ��ȯ �� 1.2���� �����ð� �ο�
	if (!m_grace)
	{
		m_grace = true;
		m_scene->SetGrace(true);
		m_graceTime = 1.2f;
	}

	// ������ ��ȯ �� 7�� ����
	m_alert = true;
	m_alertTime = 7.f;

	// ���� ������ ��ŭ �Ӹ� ���� ������ ����.

	std::vector<std::wstring> vecFileName;
	for (int i = 0; i <= 9; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		// %d�� i�� ���� ���ԵǾ� ���ڿ��� ��������� �ȴ�.
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
	// ���� ������ ���س��´�.
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
	// npc�ϰ��
	if (m_interactiveNpc)
	{
		m_interactiveNpc->OpenUIWindow();
		return;
	}
	
	// ��Ż�ϰ��
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
	���ε�Ű�� ����� �Լ��鿡�� ��ŸŸ���� ����ϱ� ����
	��ŸŸ���� ���ӸŴ����� ��������� �߰��� ��ũ�η� ����Ѵ�.
*/
void CPlayer::MoveFront()
{
	//// ���� ���⿡ ���� �̵� ������ ���Ѵ�.
	//Vector2 dir;
	//dir.x = cosf(DegreeToRadian(m_gunAngle));
	//dir.y = sinf(DegreeToRadian(m_gunAngle));

	//// �̵� ���⿡ ���� �ʴ� 400��ŭ �̵��Ѵ�.
	//m_pos += dir * 400.f * DELTA_TIME * m_timeScale;

	//// �ִϸ��̼��� ��ü�Ѵ�.
	//ChangeAnimation("PlayerRightWalk");

	if (m_attack)
		return;

	if (m_enableUpKey)
	{
		ChangeAnimation("PlayerLadder");
		MoveDir(Vector2(0.f, -1.f));	// �ش� �������� �̵���Ų��. (��)
		SetGround(false);
		SetPhysicsSimulate(false);
		m_ladder = true;
	}
}

void CPlayer::MoveBack()
{
	//// ���� ���⿡ ���� �̵� ������ ���Ѵ�.
	//Vector2 dir;
	//dir.x = cosf(DegreeToRadian(m_gunAngle));
	//dir.y = sinf(DegreeToRadian(m_gunAngle));

	//// �̵� ���⿡ ���� �ʴ� 400��ŭ �ݴ�� �̵��Ѵ�.
	//m_pos -= dir * 400.f * DELTA_TIME * m_timeScale;

	//// �ִϸ��̼��� ��ü�Ѵ�.
	//ChangeAnimation("PlayerRightWalk");

	if (m_attack)
		return;

	if (m_enableDownKey)
	{
		ChangeAnimation("PlayerLadder");
		MoveDir(Vector2(0.f, 1.f));	// �ش� �������� �̵���Ų��. (��)
		SetGround(false);
		SetPhysicsSimulate(false);
		m_ladder = true;
	}
}

void CPlayer::GunRotation()	// �̵����� �ٲ����
{
	// ��ٸ�Ÿ�� ���߿� �¿� �̵� �Ұ�
	if (m_ladder)
		return;

	// �����߿� �̵� �Ұ����ϰ� �Ѵ�. ��, �����߿��� ���ܷ��Ͽ� ���������� �ڿ������� �ǵ��� �Ѵ�.
	// ������Ʈ�� �̵��ϸ鼭 ����� �����ϴ�.
	if (m_attack && !m_jump && (m_useSkill != ESkill::Judgement))
		return;

	//// ���� �ʴ� 180�� ��ŭ �ð�������� ȸ���Ѵ�.
	//m_gunAngle += 180.f * DELTA_TIME * m_timeScale;

	MoveDir(Vector2(1.f, 0.f));	// �ش� �������� �̵���Ų��. (��)
}

void CPlayer::GunRotationInv() // �̵����� �ٲ����
{
	// ��ٸ�Ÿ�� ���߿� �¿� �̵� �Ұ�
	if (m_ladder)
		return;

	// �����߿� �̵� �Ұ����ϰ� �Ѵ�. ��, �����߿��� ���ܷ��Ͽ� ���������� �ڿ������� �ǵ��� �Ѵ�.
	// ������Ʈ�� �̵��ϸ鼭 ����� �����ϴ�.
	if (m_attack && !m_jump && (m_useSkill != ESkill::Judgement))
		return;

	//// ���� �ʴ� 180�� ��ŭ �� �ð�������� ȸ���Ѵ�.
	//m_gunAngle -= 180.f * DELTA_TIME * m_timeScale;

	MoveDir(Vector2(-1.f, 0.f)); // �ش� �������� �̵���Ų��. (��)
}

void CPlayer::Fire()
{
	// ��ٸ�Ÿ�� ���߿� ���� �Ұ�
	if (m_ladder)
		return;

	// �̹� �������̶�� ����
	if (m_attack)
		return;

	m_useSkill = ESkill::Attack;

	// ���������� �ٲ�
	m_attack = true;

	// �������� ���� �����·� �ٲ��, 6�ʰ� �ٽ� ���ŵȴ�.
	m_alert = true;
	m_alertTime = 7.f;

	int	AnimDirIndex = 0;

	// �÷��̾��� ������ �����̶��
	if (m_playerDir == -1)
		// Ű��Ʈ ������ '���� ����'�� �ε�����
		AnimDirIndex = 1;

	int randomAttack = (rand()%4)+2;  // 2 ~ 5

	// �ش� ���� ��Ʈ�� �ִϸ��̼� ��ü. ���� 4���� �� �ϳ��� �������� �� 
	ChangeAnimation(m_vecSequenceKey[AnimDirIndex][randomAttack]);

	// ���� ���� ���
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
	// ��ٿ��� �������� ��� �ٷ� �����Ѵ�.
	if (m_vecCoolDown[0].coolDownEnable)
		return;

	// ��ų Ű�� ������ ���ÿ� ��ٿ��� '����'���·�, 5�ʷ� ������ش�.
	m_vecCoolDown[0].coolDownEnable = true;
	m_vecCoolDown[0].coolDown = 5.f;

	//// ����̵��� �����Ѵ�.
	//CTornado* bullet = m_scene->CreateObject<CTornado>("Tornado");

	//// ����̵��� �߻������ ���� ���⿡ �����ش�.
	//bullet->SetAngle(m_gunAngle);

	//// ����̵��� ù ��ġ�� ���� ��ġ�� �����Ѵ�.
	//bullet->SetPos(m_gunPos);
}

void CPlayer::Skill2()
{
	// ��ٿ��� �������� ��� �ٷ� �����Ѵ�.
	if (m_vecCoolDown[1].coolDownEnable)
		return;

	// �ƴ϶��, ��ų ������� ���� ��ٿ��� '����'���·�, 10�ʷ� ������ش�.
	m_vecCoolDown[1].coolDownEnable = true;
	m_vecCoolDown[1].coolDown = 10.f;

	//// ������ Ȱ��ȭ ��Ų��.
	//m_satelSkillOn = true;

	//// �� �� �⺻������ �ٲ��ش�. ���ӽð��� ��� 0���� �ٽ� �����ȴ�.
	//m_satelRotationSpeed = 180.f;
	//m_satelSkillTime = 0.f;
	//m_satelSkillDir = 1.f;
}

void CPlayer::JumpKey()
{
	// ��ٸ� Ÿ���� ������ Ż�� �����ϰ� �ϱ�
	

	if (m_ladder)
	{
		
		m_physicsSimulate = true;
		m_fallStartY = m_pos.y;
		m_fallTime = 0.f;

		m_ladder = false;
	}

	// ���� �� �����Ұ�, ������Ʈ�� ����
	if (m_attack && m_useSkill != ESkill::Judgement)
		return;
	else if (m_jump)
		return;

	m_scene->GetSceneResource()->SoundPlay("Jump");

	Jump();
}

void CPlayer::PowerStrike()
{
	// ��ٸ�Ÿ�� ���߿� ���� �Ұ�
	if (m_ladder)
		return;

	// �̹� �������̶�� ����
	if (m_attack)
		return;

	// mp�� �����ص� ����
	if (m_ability.MP < 30)
	{
		return;
	}

	// ���� ������ ���س��´�.
	float prevMP = m_ability.MP / (float)m_ability.MPMax;

	// ���� MP ����
	m_ability.MP -= 30;

	// MP UI ����
	m_scene->FindWidget<CMainHUD>("MainHUD")
		->SetMP(m_ability.MP / (float)m_ability.MPMax, prevMP);


	m_powerStrikeState = ESkillState::Used;

	m_useSkill = ESkill::PowerStrike;

	// ��� ����
	m_scene->GetSceneResource()->SoundPlay("PowerStrikeUse");

	m_effect = m_scene->CreateObject<CEffect>("PowerStrikeEffect");
	m_effect->SetPos(m_pos + Vector2(10.f * m_playerDir, -35.f));
	m_effect->AddAnimation("PowerStrikeEffect", false, 0.35f);

	/*CEffect* effect = m_scene->CreateObject<CEffect>("SlashBlastEffect");
	effect->SetPos(m_pos + Vector2(7.f * m_playerDir, -32.f));
	effect->AddAnimation("SlashBlastEffect", false, 0.35f);*/

	// ���������� �ٲ�
	m_attack = true;

	// �������� ���� �����·� �ٲ��, 6�ʰ� �ٽ� ���ŵȴ�.
	m_alert = true;
	m_alertTime = 7.f;

	int	AnimDirIndex = 0;

	// �÷��̾��� ������ �����̶��
	if (m_playerDir == -1)
		// Ű��Ʈ ������ '���� ����'�� �ε�����
		AnimDirIndex = 1;

	int randomAttack = (rand() % 4) + 2;  // 2 ~ 5

	// �ش� ���� ��Ʈ�� �ִϸ��̼� ��ü. ���� 4���� �� �ϳ��� �������� �� 
	ChangeAnimation(m_vecSequenceKey[AnimDirIndex][randomAttack]);

	// ���� ���� ���
	m_attackPattern = randomAttack - 1;
}

void CPlayer::SlashBlast()
{
	// ��ٸ�Ÿ�� ���߿� ���� �Ұ�
	if (m_ladder)
		return;

	// �̹� �������̶�� ����
	if (m_attack)
		return;

	// mp�� �����ص� ����
	if (m_ability.MP < 50)
	{
		return;
	}

	// ���� ������ ���س��´�.
	float prevMP = m_ability.MP / (float)m_ability.MPMax;

	// ���� MP ����
	m_ability.MP -= 50;

	// MP UI ����
	m_scene->FindWidget<CMainHUD>("MainHUD")
		->SetMP(m_ability.MP / (float)m_ability.MPMax, prevMP);

	m_slashBlastState = ESkillState::Used;

	m_useSkill = ESkill::SlashBlast;

	// ��� ����
	m_scene->GetSceneResource()->SoundPlay("SlashBlastUse");

	CEffect* effect = m_scene->CreateObject<CEffect>("SlashBlastEffect");
	effect->SetPos(m_pos + Vector2(7.f * m_playerDir, -32.f));
	effect->AddAnimation("SlashBlastEffect", false, 0.3f);

	// ���������� �ٲ�
	m_attack = true;

	// �������� ���� �����·� �ٲ��, 6�ʰ� �ٽ� ���ŵȴ�.
	m_alert = true;
	m_alertTime = 7.f;

	int	AnimDirIndex = 0;

	// �÷��̾��� ������ �����̶��
	if (m_playerDir == -1)
		// Ű��Ʈ ������ '���� ����'�� �ε�����
		AnimDirIndex = 1;

	int randomAttack = (rand() % 4) + 2;  // 2 ~ 5

	// �ش� ���� ��Ʈ�� �ִϸ��̼� ��ü. ���� 4���� �� �ϳ��� �������� �� 
	ChangeAnimation(m_vecSequenceKey[AnimDirIndex][randomAttack]);

	// ���� ���� ���
	m_attackPattern = randomAttack - 1;
}

void CPlayer::Judgement()
{
	// ��ٸ�Ÿ�� ���߿� ���� �Ұ�
	if (m_ladder)
		return;
	
	// ���������̶�� ����
	if (m_judgementDelay > 0.1f)
		return;

	// �̹� �������̶�� ����
	if (m_attack)
		return;

	

	// mp�� �����ص� ����
	if (m_ability.MP < 30)
	{
		return;
	}


	m_judgementState = ESkillState::Used;

	m_useSkill = ESkill::Judgement;


	ChangeAnimation("PlayerRightJudgement");

	// ���������� �ٲ�
	m_attack = true;

	// �������� ���� �����·� �ٲ��, 6�ʰ� �ٽ� ���ŵȴ�.
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
	// ��ٸ�Ÿ�� ���߿� ���� �Ұ�
	if (m_ladder)
		return;

	// �̹� �������̶�� ����
	if (m_attack)
		return;

	// mp�� �����ص� ����
	if (m_ability.MP < 200)
	{
		return;
	}

	// ���� ������ ���س��´�.
	float prevMP = m_ability.MP / (float)m_ability.MPMax;

	// ���� MP ����
	m_ability.MP -= 200;

	// MP UI ����
	m_scene->FindWidget<CMainHUD>("MainHUD")
		->SetMP(m_ability.MP / (float)m_ability.MPMax, prevMP);

	m_justiceState = ESkillState::Used;

	m_useSkill = ESkill::Justice;

	// �����ϸ鼭 ����ߴٸ� �������� ���������� ����
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
	

	// ���������� �ٲ�
	m_attack = true;

	// �������� ���� �����·� �ٲ��, 6�ʰ� �ٽ� ���ŵȴ�.
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

		// ���� ������ ���س��´�.
		float prevHP = PlayerAbility::HP / (float)PlayerAbility::HPMax;

		// ���� ü�� ����
		PlayerAbility::HP += 1000;
		if (PlayerAbility::HP > PlayerAbility::HPMax)
			PlayerAbility::HP = PlayerAbility::HPMax;
			

		// ü�� ui ����
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

		// ���� ������ ���س��´�.
		float prevMP = PlayerAbility::MP / (float)PlayerAbility::MPMax;

		// ���� ü�� ����
		PlayerAbility::MP += 1000;
		if (PlayerAbility::MP > PlayerAbility::MPMax)
			PlayerAbility::MP = PlayerAbility::MPMax;


		// ü�� ui ����
		m_scene->FindWidget<CMainHUD>("MainHUD")
			->SetMP(PlayerAbility::MP / (float)PlayerAbility::MPMax, prevMP);

		--PlayerAbility::MPPotionCnt;

	}
}



void CPlayer::AttackEnd()
{
	// ������ �������Ƿ� ���ݻ��¸� false�� �ٲ۴�
	
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

		// ��ų ������ 1�� �߰�
		m_judgementDelay = 1.f;
	}

	m_useSkill = ESkill::None;
	
	// ������ false�ϰ�� �⺻ ���·� �ٲ�� �� ���̴�.
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
		�浹ü�� ����� ���� �浹�� üũ�� �� (SceneCollision�� Collision�Լ�)
		�̹Ƿ�, ������ �浹ü�� �����Ѵٰ� �ؼ� ������ �浹 ��Ͽ� ���� �浹ü��
		�������� �ʴ´�.

		���� DeleteCollisionList�� �̿��� �����ش�.

		����** : ���� ���� ���ְ� ClearCollisionList��...
	*/
		m_attackCollider->ClearCollisionList();
	}
	
	m_mapMonsterCollider.clear();

}

void CPlayer::Attack()
{
	// ��Ƽ���̷� ���� ����ġ�� Ÿ�ֿ̹� ȣ��ȴ�.
	
	if (m_useSkill == ESkill::Judgement)
	{
		// mp�� �����ص� ����
		if (m_ability.MP < 30)
		{
			AttackEnd();
		}

		// ���� ������ ���س��´�.
		float prevMP = m_ability.MP / (float)m_ability.MPMax;

		// ���� MP ����
		m_ability.MP -= 30;

		// MP UI ����
		m_scene->FindWidget<CMainHUD>("MainHUD")
			->SetMP(m_ability.MP / (float)m_ability.MPMax, prevMP);



		m_scene->GetSceneResource()->SoundPlay("JudgementUse");

		// ������Ʈ�� ���⼭ �浹ü�� �����ؼ� Ÿ�� ���� ������� �ʰ� �Ѵ�.

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
		// �� �ֵθ��� ���� ���
		m_scene->GetSceneResource()->SoundPlay("Attack");
	}

	// ��Ҹ� �������� Ȯ��
	int random = (rand() % 2) + 1;  // 1 ~ 2

	// ����� ���Ͽ� ���� �ٸ� ���� ����Ʈ ����
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

		//// ���� �浹ü�� ������.
		//m_attackCollider = AddCollider<CColliderBox>("PlayerAttack");
		//m_attackCollider->SetExtent(85.f, 80.f);
		//m_attackCollider->SetOffset(m_playerDir * 65.f, -35.f);
		//m_attackCollider->SetCollisionProfile("PlayerAttack");

		//m_attackCollider->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::CollisionBeginAttack);
		//m_attackCollider->SetCollisionEndFunction<CPlayer>(this, &CPlayer::CollisionEndAttack);
	}
	else if (m_useSkill == ESkill::Judgement)
	{
		// �Ź� ����Ʈ�� ����Ѵ�
		m_effect = m_scene->CreateObject<CEffect>("PlayerRightJudgementEffect");
		m_effect->SetPos(m_pos);
		m_effect->AddAnimation("PlayerRightJudgementEffect", false, 0.3);

		// ���� �浹ü�� ������.
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

		// 1Ÿ ���� ���� 
		m_scene->GetSceneResource()->SoundPlay("JusticeUse1");

		// ���� �浹ü�� ������.
		m_attackCollider = AddCollider<CColliderBox>("PlayerAttack");
		m_attackCollider->SetExtent(300.f, 400.f);
		m_attackCollider->SetOffset(m_playerDir * 85.f, -30.f);
		m_attackCollider->SetCollisionProfile("PlayerAttack");

		m_attackCollider->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::CollisionBeginAttack);
		m_attackCollider->SetCollisionEndFunction<CPlayer>(this, &CPlayer::CollisionEndAttack);
	}
	else 
	{
		// ���� �浹ü�� ������.
		m_attackCollider = AddCollider<CColliderBox>("PlayerAttack");
		m_attackCollider->SetExtent(85.f, 80.f);
		m_attackCollider->SetOffset(m_playerDir * 65.f, -35.f);
		m_attackCollider->SetCollisionProfile("PlayerAttack");

		m_attackCollider->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::CollisionBeginAttack);
		m_attackCollider->SetCollisionEndFunction<CPlayer>(this, &CPlayer::CollisionEndAttack);
	}

	//// ��Ƽ���̷� ������ �����ӿ� ȣ��ǵ��� �Ѵ�.
	//// Ư�� �����ӿ� �� �Լ��� ȣ������ν� �Ҹ��� �����ȴ�.
	//CBullet* bullet = m_scene->CreateObject<CBullet>("Bullet");

	//bullet->SetAngle(m_gunAngle);

	//bullet->SetPos(m_gunPos);
	//
	//// �÷��̾ �߻��ϴ� �Ҹ��� �������� �����Ѵ�.
	//bullet->SetDamage(30.f);

	//// �Ҹ��� �浹ü �� �浹 ���������� �����Ѵ�.
	//CCollider* bulletCol = bullet->FindCollider("Body");
	//bulletCol->SetCollisionProfile("PlayerAttack");
}

void CPlayer::Attack2()
{
	// 1Ÿ�� �浹ü�� �����ش�.
	if (m_attackCollider)
	{
		if (m_attackCollider->GetActive())
			m_attackCollider->SetActive(false);
	}

	if(m_useSkill == ESkill::Justice)
	{
		m_justiceState = ESkillState::Normal;

		m_attackCnt = 2;

		// 2Ÿ ���� ���� 
		m_scene->GetSceneResource()->SoundPlay("JusticeUse2");

		// ���� �浹ü�� ������.
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
	// �÷��̾� �浹ü�� �浹�Ǹ� ȣ���
	
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

	// ���� �浹ü�� '����' �浹ü��� �����Ѵ�.
	if (_dest->GetName() == "Ground")
	{
		// ������Ʈ���� �÷��̾��� ��ġ�� �����ϱ� ���� ���� �޾ƿ�
		m_LadderCollider = _dest;

		// ��ų ��� ������ �̵��ӵ� �ٲ���� ���� ����� ����
		m_jumpVelocity = 35.f;

		return;
	}

	// ���� ���� ���¶�� �����Ѵ�.
	if (m_grace)
		return;

	// ���� �浹ü�� '�ν�' �浹ü��� �����Ѵ�.
	if (_dest->GetName() == "Cognition")
		return;

	// ���� �浹ü�� '����' �浹ü��� 
	else if (_dest->GetProfile()->Channel == ECollisionChannel::Monster)
	{
		// �� �Լ��� ȣ���� �� �Ǵ��� Ȯ���ϱ� ���� ����
		// m_scene->GetSceneResource()->SoundPlay("Gabung");

		//// ü�� ui ����
		//m_scene->FindWidget<CCharacterHUD>("CharacterHUD")
		//	->SetHP(m_ability.HP / (float)m_ability.HPMax);

		//// ���� �������°� �ƴ� ��� �������·� ��ȯ �� 1.5���� �����ð� �ο�
		//if (!m_grace)
		//{
		//	m_grace = true;
		//	m_graceTime =2.0f;
		//}

		//// ������ ��ȯ �� 7�� ����
		//m_alert = true;
		//m_alertTime = 7.f;

		//// �̰� ĳ���Ϳ� �پ��ִ� ����������Ʈ ü�¹ٸ� �����ϴ� ��
		//m_HPBar->GetWidget<CProgressBar>()->SetValue(m_ability.HP / (float)m_ability.HPMax);
	
	}
}

void CPlayer::CollisionBeginAttack(CCollider* _src, CCollider* _dest)
{
	// �浹���ڸ��� �����ؼ� �߰����� �浹�� ����
	// ������Ʈ�� ���⼭ �����ϸ� �ȵ�
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

	// ��¥���� �̰��Ϸ��� �󸶳�..
	if (m_useSkill == ESkill::SlashBlast)
	{
		if (m_mapMonsterCollider.size() < 6)
		{
			// �̹� �浹���� ���Ϳ� �浹�̶�� �����Ѵ�.
			auto	iter = m_mapMonsterCollider.find(_dest->GetOwner()->GetName());

			if (iter != m_mapMonsterCollider.end())
				return;

			// ���� �浹ü ������ �߰��Ѵ�.
			m_mapMonsterCollider.insert(std::make_pair(_dest->GetOwner()->GetName(), _dest));
		}
		// Ÿ���� 6������ �Ѿ�� �����Ѵ�.
		else
			return;
	}
	else
	{
		// ���� �浹ü ������ �߰��Ѵ�.
		m_mapMonsterCollider.insert(std::make_pair(_dest->GetOwner()->GetName(), _dest));


		// ù��°(���� ���� �浹��) ���͸� ����
		// ������Ʈ, ����Ƽ���� ����
		if ((m_mapMonsterCollider.begin()->second != _dest) && (m_useSkill != ESkill::Judgement) && (m_useSkill != ESkill::Justice))
			return;
	}
	

	if (m_useSkill == ESkill::Attack)
	{
		// ���⿡ ���� �ٸ� ��Ʈ ����Ʈ ����
		if (m_playerDir == 1)
		{
			// �浹�� ���ÿ� ��Ʈ ����Ʈ�� �����Ѵ�. Once�̹Ƿ� 1�� ��� �� ������ ���̴�.
			CEffect_2* effect = m_scene->CreateObject<CEffect_2>("LeftHitEffect");

			// ����Ʈ�� ��ġ�� ��Ʈ ����Ʈ(�浹 ���� �߰�)�� �� ���̴�.
			// �� �浹ü�� �ݹ� ������� ������ ��Ʈ ����Ʈ�� _dest �浹ü�� ������ �Ѵ�.
			effect->SetPos(_dest->GetHitPoint()+Vector2(m_playerDir * 15.f, 5.f));

			// �ִϸ��̼� �߰� (�ִϸ��̼� �̸�, ��������, �÷���Ÿ��)
			effect->AddAnimation("LeftHitEffect", false, 0.3f);
		}
		else
		{
			CEffect_2* effect = m_scene->CreateObject<CEffect_2>("RightHitEffect");

			effect->SetPos(_dest->GetHitPoint() + Vector2(m_playerDir * 15.f, 5.f));

			effect->AddAnimation("RightHitEffect", false, 0.3f);
		}

		/*
			 Damage ó��
			 �÷��̾� ���� ���� �浹ü(_src)�� ���� _dest �浹ü�� ���� ������Ʈ����
			 �������� �������� �Լ��� ȣ��
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
		
		// �������� �浹ü ������ ����
		CColliderBox* collider;
		collider = AddCollider<CColliderBox>("PlayerAttack");
		collider->SetExtent(85.f, 80.f);	
		
		// �����̰͵���¥...
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
		// 1Ÿ�ϰ��
		if (m_attackCnt == 1)
		{
			// ���� ���߿� ����.
			_dest->GetOwner()->Jump();
			_dest->GetOwner()->SetJumpVelocity(50);
		}
		// 2Ÿ�ϰ��
		else if (m_attackCnt == 2)
		{
			// ���� ũ�� �˹��Ų��.
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
		�浹ü�� ����� ���� �浹�� üũ�� �� (SceneCollision�� Collision�Լ�)
		�̹Ƿ�, ������ �浹ü�� �����Ѵٰ� �ؼ� ������ �浹 ��Ͽ� ���� �浹ü��
		�������� �ʴ´�.

		���� ClearCollisionList�� �̿��� �����ش�.
	*/
	m_playerCollider[0]->ClearCollisionList();
	m_playerCollider[1]->ClearCollisionList();

	m_playerCollider.clear();

	CColliderBox* box = AddCollider<CColliderBox>("Head");

	box->SetExtent(50.f, 42.f);  // ���μ��� ũ��
	box->SetOffset(3.f, -50.f);	 // ����(�÷��̾� �߹� pos)�κ��� �󸶳� ������ ���� ��
	box->SetCollisionProfile("Player");  // �浹 �������� ���� : Player 

	// Head�� �浹 �� ȣ���� �Լ� ���
	box->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::CollisionBegin);
	box->SetCollisionEndFunction<CPlayer>(this, &CPlayer::CollisionEnd);

	// ���Ϳ� �߰��Ѵ�
	m_playerCollider.push_back(box);


	// Body ��� (���۷���)�̸��� �ڽ� �浹ü�� �����.
	box = AddCollider<CColliderBox>("Body");

	box->SetExtent(36.f, 31.f);
	box->SetOffset(3.f, -13.5f);
	box->SetCollisionProfile("Player");

	// body�� �浹 �� ȣ���� �Լ� ���
	box->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::CollisionBegin);
	box->SetCollisionEndFunction<CPlayer>(this, &CPlayer::CollisionEnd);

	// ���Ϳ� �߰��Ѵ�
	m_playerCollider.push_back(box);
}

bool CPlayer::SortX(const CSharedPtr<class CCollider>& _src, const CSharedPtr<class CCollider>& _dest)
{
	float	srcX = _src->GetOwner()->GetPos().x;
	float	destX = _dest->GetOwner()->GetPos().x;

	// �÷��̾ �������� ���� ���� ���, ���ʹ� x��ǥ�� ���� ������ ����
	if (true)
	{
		return srcX < destX;
	}
	// �÷��̾ ������ ���� ���� ���, ���ʹ� x��ǥ�� ū ������ ����
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
	// ��ü ���� �� Ÿ�� ���̵�(���۷��� Ŭ������ ���)�� �ʱ�ȭ
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
