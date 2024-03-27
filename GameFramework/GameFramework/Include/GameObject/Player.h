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
	static int ItemCnt;	// 갖고있는 아이템 개수
};

struct SkillCoolDownInfo
{
	float	coolDown;			// 쿨다운 시간
	bool	coolDownEnable;		// 쿨다운 남아있는지 (false : 없음, true : 있음)
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
	//float m_gunAngle;	// 총의 각도
	//float m_gunLength;	// 총의 길이
	//Vector2 m_gunPos;	// 총의 위치
	//float m_satelAngle[3];		// 위성 3개의 각도
	//float m_satelLength;		// 위성 궤도 범위 (현재)
	//float m_satelLengthMin;		// 위성 궤도 범위 (최소)
	//float m_satelLengthMax;		// 위성 궤도 범위 (최대)
	//float m_satelRotationSpeed;	// 위성 회전 속도
	//float m_satelSkillDir;		// 위성 궤도의 확대/축소 여부
	//bool m_satelSkillOn;		// 위성 활성화 여부
	//float m_satelSkillTime;		// 위성 지속 시간
	//class CSatellite* m_satellite[3];	// 위성 객체

	std::vector<SkillCoolDownInfo> m_vecCoolDown;	// 스킬별 쿨다운 정보
	int m_playerDir;			// 좌우 애니메이션 출력을 위한 플레이어의 방향
	/*
		vecSequenceKey : 벡터의 배열.
		키세트를 오른쪽, 왼쪽 등으로 나누어 구성할 것이다.
	*/
	std::vector<std::string>	m_vecSequenceKey[2];
	bool m_attack;				// 현재 공격중인지
	bool m_alert;				// 현재 경계상태인지
	float m_alertTime;			// 6초를 세고 경계상태를 해제시킴
	bool m_grace;				// 현재 무적상태인지
	float m_graceTime;			// 1.5초를 세고 무적상태를 해제시킴
	int m_attackPattern;		// 공격 1~4중 어느 것을 사용중인지
	float m_graceRender;		// 무적시간중 렌더링 안하는시간 세기
	static PlayerAbility m_ability;	// 능력치
	std::vector <CSharedPtr<class CColliderBox>> m_playerCollider;  // 플레이어 충돌체
	CSharedPtr<class CColliderBox> m_attackCollider;		// 공격 충돌체 (단일 공격기)
	std::vector<CSharedPtr<class CColliderBox>> m_vecAttackCollider;		// 공격 충돌체 (슬래시 블러스트)
	std::unordered_map<std::string, CSharedPtr<class CCollider>> m_mapMonsterCollider;	// 공격 충돌체와 충돌한 몬스터 충돌체들(타겟 수 체크용)
	CSharedPtr<class CCollider> m_LadderCollider;	// 현재 충돌중인 사다리
	ESkill m_useSkill;			// 현재 사용중인 스킬
	CSharedPtr<class CEffect> m_effect;	// 현재 적용중인 이펙트 (저지먼트의 위치를 잡아주기 위함)
	//CSharedPtr<class CWidgetComponent>	m_HPBar;	// 체력 바 

	CSharedPtr<class CWidgetComponent>	m_nameBarFrame;  // 이름 프레임
	int m_attackCnt;	// 현재 스킬 몇 타 인지

	static float EXPTable[19];

	ESkillState m_powerStrikeState;
	ESkillState m_slashBlastState;
	ESkillState m_judgementState;
	float m_judgementDelay;			// 스킬 딜레이 (바로 재사용 방지)
	ESkillState m_justiceState;

	std::string m_portalEnable;	// 현재 접촉중인 포탈 이름

	std::vector<CSharedPtr<class CWidgetComponent>> m_damageWidget; // 머리위데미지위젯
	int widgetCnt; // 위 위젯 셈

	CSharedPtr<class CWidgetComponent> m_healWidget; // 머리위힐위젯

	

	static Vector2 m_spawnPos; // 포탈 타고 스폰 위치 정함 (스태틱?

	float m_healTime;	 // 경계상태가 아니면 5초마다 최대체력, 마나의 3% 회복

	std::list<CSharedPtr<class CItem>> m_gainableItemList;  // 접촉한 아이템들
	std::list<CSharedPtr<class CHPPotion>> m_gainableHPPotionList;  // 접촉한 아이템들
	std::list<CSharedPtr<class CMPPotion>> m_gainableMPPotionList;  // 접촉한 아이템들
	
	CSharedPtr<class CGameObject> m_interactiveNpc; // 접촉한 npc
public:
	virtual bool Init();
	virtual void Update(float _deltaTime);
	virtual void PostUpdate(float _deltaTime);
	virtual void Render(HDC _hDC, float _deltaTime);
	virtual float InflictDamage(float _damage, int _dir = 1);		// 데미지를 입기 위한 함수
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
	// 아래는 바인드키에 등록할 함수들이다.
	void Portal();
	void MoveFront();		// 앞으로 이동
	void MoveBack();		// 뒤로 이동	
	void GunRotation();		// 총 회전(시계방향)
	void GunRotationInv();	// 총 회전(반 시계방향)
	void Fire();			// 기본공격
	void Gain();			// 줍기
	void Skill1();			// 스킬 1
	void Skill2();			// 스킬 2
	void JumpKey();			// 점프
	void PowerStrike();		// 파워스트라이크 - 단일공격
	void SlashBlast();		// 슬래시블러스트 - 다수공격
	void Judgement();		// 믹서기
	void Justice();		// 올려베기
	void HPPotion();
	void MPPotion();
private:
	void AttackEnd();
	void Attack();
	void Attack2();
private:
	void CollisionBegin(CCollider* _src, CCollider* _dest);	// 충돌 시작 시 호출될 함수
	void CollisionBeginAttack(CCollider* _src, CCollider* _dest);
	void CollisionEnd(CCollider* _src, CCollider* _dest);   // 충돌 종료 시 호출될 함수
	void CollisionEndAttack(CCollider* _src, CCollider* _dest);
	void ResetPlayerCollider();
private:
	static bool SortX(const CSharedPtr<class CCollider>& _src,
		const CSharedPtr<class CCollider>& _dest);
protected:
	CPlayer();
	CPlayer(const CPlayer& _obj);
	virtual ~CPlayer();

	friend class CScene;	// 씬 변수에 씬 정보를 넘겨받기 위해
};

