#pragma once
#include "Character.h"

/*
	������ ���� :
	�÷��̾ �������� �ʾƵ� �ν� ���� ���� ������
	�ڵ����� ���� �� ������

	�񼱰��� ���� :
	�÷��̾ ������ �� ���� �⺻ ���ϸ� ������
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

// �⺻ ����
enum class EBasicPattern
{
	MoveLeft,
	MoveRight,
	Stop,
	None
};

// ������ ����
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
	int m_dir;			// �̵� ����
	float m_fireTime;	// ���� �ֱ�
	int m_fireCount;	// ���� Ƚ��(3Ÿ ī��Ʈ��)
	/*
		vecSequenceKey : ������ �迭.
		Ű��Ʈ�� ������, ���� ������ ������ ������ ���̴�.
	*/
	std::vector<std::string>	m_vecSequenceKey[2];
	// std::vector <CSharedPtr<class CCollider>> m_monsterCollider;  // ���� �浹ü ����
	bool m_attack;		// ���������� �ƴ���. �������̸� �ǰݸ��, �˹� �� ��� ����ϸ� �ȵǹǷ�
	bool m_die;			// �׾����� �ƴ���. �߰����� ��� ��ȯ�� ���ϱ� ���� ����
	bool m_hit;			// �¾Ƽ� �������� �ƴ���. �߰����� ��� ��ȯ�� ���ϱ� ���� ����
	float m_hitTime;    // �� �ð����� �˹�ɰ��� 0.4��
	int m_hitDir;	    // �¾Ƽ� �����Ǿ��� ��� ����
	EBasicPattern m_basicPattern; // �⺻ ���� �� � ����������.
	ECombatPattern m_combatPattern; // ���� ���� �� � ����������.
	float m_moveTime;    // �̵� �ð�(���� �����Ǹ� �̵� �����Ű�� ����)
	bool m_alert;		// �÷��̾�� ��ġ������
	MonsterAbility m_ability;
	CGameObject* m_target;  // �ν� ������ ���� Ÿ��(�÷��̾�)
	/*
		�浹ü�� �ƴ� ���� �浹ü�� �̸��� �Ἥ ����� ������,
		�浹ü�� ����Ʈ���� erase�� ������ ������ �����Ǳ� �����̴�.
		������ �̸��� �������� ������ �����Ƿ� �̸��� �޾ƿ� ����Ʈ�� �����.

		�̰��� �ν� ������ ���۰� ���ῡ�� ����� ���̴�.
	*/
	std::list<std::string> m_targetNameList;  // �ν� ������ ���� Ÿ��(�÷��̾�) �浹ü�� �̸�
	bool m_flag;	    // ���� �̵��� ��ȯ��
	/*
		�÷��̾��� ���� �浹ü�� ������ �ν� ������ �Ѳ�����
		������ �� �� �������� �� �ϳ��� ���������� ������ �ν���
		Ǯ�������� ���� �����ϱ� ���� �ν� ī��Ʈ�� ����.
	*/
	std::vector<CSharedPtr<class CCollider>> m_vecAttackCollider; // ���� �浹ü
	bool m_attackCheck; // ���� �� �÷��̾��� 1�� �浹ü���� �����ϵ��� ]

	std::vector<CSharedPtr<class CWidgetComponent>> m_damageWidget;  // ���� �������� ǥ���ϴ� ����
	int widgetCnt;	// �� ���� �ε��� �Ǵ�
	float m_widgetLifeTime;

public:
	virtual bool Init();
	virtual void Update(float _deltaTime);
	virtual void PostUpdate(float _deltaTime);
	virtual void Render(HDC _hDC, float _deltaTime);
	virtual float InflictDamage(float _damage, int _dir = 1);		// �������� �Դ� �Լ�
public:
	virtual bool GetFlag() const;
	virtual void SetFlag(bool _flag);
private:
	virtual	void CollisionBegin(CCollider* _src, CCollider* _dest);	// �浹 ���� �� ȣ��� �Լ�
	virtual void CollisionEnd(CCollider* _src, CCollider* _dest);   // �浹 ���� �� ȣ��� �Լ�
	virtual void CollisionMouseBegin(CCollider* _src, const Vector2& _mousePos); // ���콺 ����
	virtual void CollisionMouseEnd(CCollider* _src, const Vector2& _mousePos);   // ���콺 ����
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

	friend class CScene;	// �� ������ �� ������ �Ѱܹޱ� ����
};

