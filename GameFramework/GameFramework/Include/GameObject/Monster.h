#pragma once
#include "Character.h"

/*
	선공형 몬스터 :
	플레이어가 공격하지 않아도 인식 영역 내에 들어오면
	자동으로 추적 및 공격함

	비선공형 몬스터 :
	플레이어가 공격할 때 까지 기본 패턴만 실행함
*/
struct MonsterAbility
{
	int Level;
	float HP;
	float HPMax;
	float MP;
	float MPMax;
	float DamageMin;
	float DamageMax;
	float EXPDrop;
	float MoneyDrop;
};

// 기본 패턴
enum class EBasicPattern
{
	MoveLeft,
	MoveRight,
	Stop,
	None
};

// 전투중 패턴
enum class ECombatPattern
{
	MoveToTarget,
	Skill1,
	Skill2,
	Skill3,
	None
};

class CMonster :
    public CCharacter
{
protected:
	int m_dir;			// 이동 방향
	float m_fireTime;	// 공격 주기
	int m_fireCount;	// 공격 횟수(3타 카운트용)
	/*
		vecSequenceKey : 벡터의 배열.
		키세트를 오른쪽, 왼쪽 등으로 나누어 구성할 것이다.
	*/
	std::vector<std::string>	m_vecSequenceKey[2];
	// std::vector <CSharedPtr<class CCollider>> m_monsterCollider;  // 몬스터 충돌체 벡터
	bool m_attack;		// 공격중인지 아닌지. 공격중이면 피격모션, 넉백 등 모션 재생하면 안되므로
	bool m_die;			// 죽었는지 아닌지. 추가적인 모션 전환을 피하기 위한 변수
	bool m_hit;			// 맞아서 경직인지 아닌지. 추가적인 모션 전환을 피하기 위한 변수
	float m_hitTime;    // 이 시간동안 넉백될것임 0.4초
	int m_hitDir;	    // 맞아서 경직되었을 당시 방향
	EBasicPattern m_basicPattern; // 기본 패턴 중 어떤 패턴중인지.
	ECombatPattern m_combatPattern; // 전투 패턴 중 어떤 패턴중인지.
	float m_moveTime;    // 이동 시간(일정 누적되면 이동 종료시키기 위함)
	bool m_alert;		// 플레이어와 대치중인지
	MonsterAbility m_ability;
	CGameObject* m_target;  // 인식 영역에 들어온 타겟(플레이어)
	/*
		충돌체가 아닌 굳이 충돌체의 이름을 써서 만드는 이유는,
		충돌체는 리스트에서 erase해 버리면 원본이 삭제되기 때문이다.
		어차피 이름도 고유성을 가지고 있으므로 이름을 받아와 리스트를 만든다.

		이것은 인식 영역의 시작과 종료에서 사용할 것이다.
	*/
	std::list<std::string> m_targetNameList;  // 인식 영역에 들어온 타겟(플레이어) 충돌체의 이름
	bool m_flag;	    // 몬스터 이동의 반환점
	/*
		플레이어의 여러 충돌체가 몬스터의 인식 범위에 한꺼번에
		들어오고 난 뒤 빠져나갈 때 하나만 빠져나가도 몬스터의 인식이
		풀려버리는 것을 방지하기 위해 인식 카운트를 센다.
	*/
	std::vector<CSharedPtr<class CCollider>> m_vecAttackCollider; // 공격 충돌체
	bool m_attackCheck; // 공격 시 플레이어의 1개 충돌체에만 공격하도록 ]

	std::vector<CSharedPtr<class CWidgetComponent>> m_damageWidget;  // 받은 데미지를 표시하는 위젯
	int widgetCnt;	// 위 위젯 인덱스 판단
	float m_widgetLifeTime;

public:
	virtual bool Init();
	virtual void Update(float _deltaTime);
	virtual void PostUpdate(float _deltaTime);
	virtual void Render(HDC _hDC, float _deltaTime);
	virtual float InflictDamage(float _damage, int _dir = 1);		// 데미지를 입는 함수
public:
	virtual bool GetFlag() const;
	virtual void SetFlag(bool _flag);
private:
	virtual	void CollisionBegin(CCollider* _src, CCollider* _dest);	// 충돌 시작 시 호출될 함수
	virtual void CollisionEnd(CCollider* _src, CCollider* _dest);   // 충돌 종료 시 호출될 함수
	virtual void CollisionMouseBegin(CCollider* _src, const Vector2& _mousePos); // 마우스 전용
	virtual void CollisionMouseEnd(CCollider* _src, const Vector2& _mousePos);   // 마우스 전용
	virtual void CollisionCognitionBegin(CCollider* _src, CCollider* _dest);
	virtual void CollisionCognitionEnd(CCollider* _src, CCollider* _dest);
	virtual void CollisionBeginAttack(CCollider* _src, CCollider* _dest);
	virtual void CollisionEndAttack(CCollider* _src, CCollider* _dest);
private:
	virtual void Die();
	virtual void HitEnd();
private:
	virtual void MoveLeft();
	virtual void MoveRight();
protected:
	CMonster();
	CMonster(const CMonster& obj);
	virtual ~CMonster();

	friend class CScene;	// 씬 변수에 씬 정보를 넘겨받기 위해
};

