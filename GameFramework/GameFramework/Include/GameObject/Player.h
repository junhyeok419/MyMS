#pragma once
#include "../GameInfo.h"
#include "Character.h"


struct PlayerAbility
{
	static int Level;
	static float HP;
	static float HPMax;
	static float MP;
	static float MPMax;
	static float EXP;
	static float EXPMax;
	static float DamageMin;
	static float DamageMax;
	static int Money;

	static int HPPotionCnt;
	static int MPPotionCnt;
	static int ItemCnt;	// �����ִ� ������ ����
};

struct SkillCoolDownInfo
{
	float	coolDown;			// ��ٿ� �ð�
	bool	coolDownEnable;		// ��ٿ� �����ִ��� (false : ����, true : ����)
};

enum class ESkillState
{
	Normal,
	Used,
	Disabled
};


class CPlayer 
	: public CCharacter
{
public:
	//float m_gunAngle;	// ���� ����
	//float m_gunLength;	// ���� ����
	//Vector2 m_gunPos;	// ���� ��ġ
	//float m_satelAngle[3];		// ���� 3���� ����
	//float m_satelLength;		// ���� �˵� ���� (����)
	//float m_satelLengthMin;		// ���� �˵� ���� (�ּ�)
	//float m_satelLengthMax;		// ���� �˵� ���� (�ִ�)
	//float m_satelRotationSpeed;	// ���� ȸ�� �ӵ�
	//float m_satelSkillDir;		// ���� �˵��� Ȯ��/��� ����
	//bool m_satelSkillOn;		// ���� Ȱ��ȭ ����
	//float m_satelSkillTime;		// ���� ���� �ð�
	//class CSatellite* m_satellite[3];	// ���� ��ü

	std::vector<SkillCoolDownInfo> m_vecCoolDown;	// ��ų�� ��ٿ� ����
	int m_playerDir;			// �¿� �ִϸ��̼� ����� ���� �÷��̾��� ����
	/*
		vecSequenceKey : ������ �迭.
		Ű��Ʈ�� ������, ���� ������ ������ ������ ���̴�.
	*/
	std::vector<std::string>	m_vecSequenceKey[2];
	bool m_attack;				// ���� ����������
	bool m_alert;				// ���� ����������
	float m_alertTime;			// 6�ʸ� ���� �����¸� ������Ŵ
	bool m_grace;				// ���� ������������
	float m_graceTime;			// 1.5�ʸ� ���� �������¸� ������Ŵ
	int m_attackPattern;		// ���� 1~4�� ��� ���� ���������
	float m_graceRender;		// �����ð��� ������ ���ϴ½ð� ����
	static PlayerAbility m_ability;	// �ɷ�ġ
	std::vector <CSharedPtr<class CColliderBox>> m_playerCollider;  // �÷��̾� �浹ü
	CSharedPtr<class CColliderBox> m_attackCollider;		// ���� �浹ü (���� ���ݱ�)
	std::vector<CSharedPtr<class CColliderBox>> m_vecAttackCollider;		// ���� �浹ü (������ ����Ʈ)
	std::unordered_map<std::string, CSharedPtr<class CCollider>> m_mapMonsterCollider;	// ���� �浹ü�� �浹�� ���� �浹ü��(Ÿ�� �� üũ��)
	CSharedPtr<class CCollider> m_LadderCollider;	// ���� �浹���� ��ٸ�
	ESkill m_useSkill;			// ���� ������� ��ų
	CSharedPtr<class CEffect> m_effect;	// ���� �������� ����Ʈ (������Ʈ�� ��ġ�� ����ֱ� ����)
	//CSharedPtr<class CWidgetComponent>	m_HPBar;	// ü�� �� 

	CSharedPtr<class CWidgetComponent>	m_nameBarFrame;  // �̸� ������
	int m_attackCnt;	// ���� ��ų �� Ÿ ����

	static float EXPTable[19];

	ESkillState m_powerStrikeState;
	ESkillState m_slashBlastState;
	ESkillState m_judgementState;
	float m_judgementDelay;			// ��ų ������ (�ٷ� ���� ����)
	ESkillState m_justiceState;

	std::string m_portalEnable;	// ���� �������� ��Ż �̸�

	std::vector<CSharedPtr<class CWidgetComponent>> m_damageWidget; // �Ӹ�������������
	int widgetCnt; // �� ���� ��

	CSharedPtr<class CWidgetComponent> m_healWidget; // �Ӹ���������

	

	static Vector2 m_spawnPos; // ��Ż Ÿ�� ���� ��ġ ���� (����ƽ?

	float m_healTime;	 // �����°� �ƴϸ� 5�ʸ��� �ִ�ü��, ������ 3% ȸ��

	std::list<CSharedPtr<class CItem>> m_gainableItemList;  // ������ �����۵�
	std::list<CSharedPtr<class CHPPotion>> m_gainableHPPotionList;  // ������ �����۵�
	std::list<CSharedPtr<class CMPPotion>> m_gainableMPPotionList;  // ������ �����۵�
	
	CSharedPtr<class CGameObject> m_interactiveNpc; // ������ npc
public:
	virtual bool Init();
	virtual void Update(float _deltaTime);
	virtual void PostUpdate(float _deltaTime);
	virtual void Render(HDC _hDC, float _deltaTime);
	virtual float InflictDamage(float _damage, int _dir = 1);		// �������� �Ա� ���� �Լ�
public:
	bool GetDir();
	virtual ESkill GetUseSkill() const;
	virtual float GetHP() const;
	virtual float GetHPMax() const;
	virtual float GetMP() const;
	virtual float GetMPMax() const;
	virtual float GetEXP() const;
	virtual float GetEXPMax() const;
	virtual float GetLevel() const;
	virtual int GetHPPotionCnt() const;
	virtual int GetMPPotionCnt() const;
	virtual int GetItemCnt() const;
	virtual ESkillState GetPowerStrikeState();
	virtual ESkillState GetSlashBlastState();
	virtual ESkillState GetJudgementState();
	virtual ESkillState GetJusticeState();
	virtual void SetPortalEnable(std::string _portalName);
	virtual void AddEXP(float _exp);
	virtual void AddMoney(int _money);
	void LevelUp();
private:
	// �Ʒ��� ���ε�Ű�� ����� �Լ����̴�.
	void Portal();
	void MoveFront();		// ������ �̵�
	void MoveBack();		// �ڷ� �̵�	
	void GunRotation();		// �� ȸ��(�ð����)
	void GunRotationInv();	// �� ȸ��(�� �ð����)
	void Fire();			// �⺻����
	void Gain();			// �ݱ�
	void Skill1();			// ��ų 1
	void Skill2();			// ��ų 2
	void JumpKey();			// ����
	void PowerStrike();		// �Ŀ���Ʈ����ũ - ���ϰ���
	void SlashBlast();		// �����ú���Ʈ - �ټ�����
	void Judgement();		// �ͼ���
	void Justice();		// �÷�����
	void HPPotion();
	void MPPotion();
private:
	void AttackEnd();
	void Attack();
	void Attack2();
private:
	void CollisionBegin(CCollider* _src, CCollider* _dest);	// �浹 ���� �� ȣ��� �Լ�
	void CollisionBeginAttack(CCollider* _src, CCollider* _dest);
	void CollisionEnd(CCollider* _src, CCollider* _dest);   // �浹 ���� �� ȣ��� �Լ�
	void CollisionEndAttack(CCollider* _src, CCollider* _dest);
	void ResetPlayerCollider();
private:
	static bool SortX(const CSharedPtr<class CCollider>& _src,
		const CSharedPtr<class CCollider>& _dest);
protected:
	CPlayer();
	CPlayer(const CPlayer& _obj);
	virtual ~CPlayer();

	friend class CScene;	// �� ������ �� ������ �Ѱܹޱ� ����
};

