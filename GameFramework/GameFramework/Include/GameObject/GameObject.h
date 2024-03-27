#pragma once

/* 
   ���� ������, GameObject ������ �̸� ���� ��
   GameObject/GameObject.h
   GameObject/GameObject.cpp �� �����Ѵ�.
*/

// ../ : ���� ������ �����ϴ� ����� �����Ѵٴ� �ǹ��̴�.

#include "../Ref.h"
#include "../Animation/Animation.h"
#include "../UI/WidgetComponent.h"
/*
	CGameObject : ������ �����ϴ� ������Ʈ���� �ֻ��� �θ��̴�.
	������Ʈ ���� �ϳ��� ĳ���ʹ� ������Ʈ�� ����ϰ�,
	ĳ���� ���� �ϳ��� �÷��̾�� ĳ���ʹ� ����ϴ� ������ �����.
*/
class CGameObject
	: public CRef
{
protected:
	// ������Ʈ�� ��µ� ���̾��̴�. (������Ʈ�� ���� ���̾�)
	ERenderLayer m_renderLayer;
	// ������Ʈ�� ����ϴ� �ؽ����̴�.
	CSharedPtr<class CTexture> m_texture;
	// ������Ʈ�� �ִϸ��̼��̴�.
	CAnimation* m_animation;
	// ������Ʈ�� ��� �����̴�.
	float m_timeScale;
	// ������Ʈ�� �̵� �ӵ��̴�. �̰��� �̿��� ���� ������ Move �Լ��� ���� ���̴�.
	float m_moveSpeed; 
	// ������Ʈ�� �̵����̴�. 
	Vector2 m_prevPos;
	Vector2 m_move;
	// ��� ������Ʈ�� �ڽ��� ������ ��ġ, ũ��, �Ǻ��� �����Ƿ� �ֻ��� �θ� �д�.
	/*
		�Ǻ�(pivot) :
		��ü�� �������� pos�� ��ü ������ �����ϴ� ��ġ��
		0 ~ 1 ������ ������ ��Ÿ�� ��.

		pivot�� (0.5, 0.5)�̸� pos�� ��ü�� �߽ɿ� ��ġ�ϵ��� ��ü�� �׷�����.
		pivot�� (0, 0)�̸� pos�� ��ü�� �»�ܿ� ��ġ�ϵ��� ��ü�� �׷�����.
		pivot�� (1, 1)�̸� pos�� ��ü�� ���ϴܿ� ��ġ�ϵ��� ��ü�� �׷�����.
	*/
	Vector2 m_pos;
	Vector2 m_size;
	Vector2 m_pivot;
	/*int m_dir;*/

	// ������Ʈ���� ���� �˰� �����ν� �ٸ� ��ü�� ������ �� �ִ�.(���� -> �Ҹ�)
	class CScene* m_scene;

	// ������Ʈ�� ���� �浹ü ����Ʈ�̴�.
	std::list<CSharedPtr<class CCollider>>	m_colliderList;
	// ������Ʈ�� ���� ���� ������Ʈ ����Ʈ�̴�.
    std::list<CSharedPtr<CWidgetComponent>>	m_widgetComponentList;

	/*
		������Ʈ�� �߷��� �������� ������ �����ϴ� �����̴�.
		�� ������ ���� on/off �ϸ鼭,
		��� ������Ʈ���� �������� �߷��� ������ �� �ְ� �Ѵ�.

		���� ��� �������� ���� ���� ���, �÷��̾ ����� ��
		�߷��� on�ؼ� ���ʶ߸��� ��� ���� �ִ�.
	*/
	bool m_physicsSimulate;
	bool		m_ground;	     // ���� ��� �ִ� �������� �ƴ��� 
	float		m_fallTime;		 // ������ �ð� (���ӵ��� �����)
	float		m_gravityAccel;  // ������ �ð��� 10�� ���� 
	float		m_fallStartY;    // �������� ������ y��ǥ
	bool		m_jump;			 // ���������� �ƴ���
	float		m_jumpVelocity;  // ���� �ӵ�(V)

	int m_objDir;
	bool m_enableUpKey;	// ���� ����Ű ��� ������ ��������
	bool m_enableUpKey_Portal;
	bool m_enableDownKey;	// ���� ����Ű ��� ������ ��������
	bool m_ladder;				// ��ٸ��� Ÿ���ִ� ��������
public:
	// �ڽĿ��� ������ ������ ���� �Լ��� �����Ѵ�.
	virtual bool Init();
	virtual void Update(float _deltaTime);
	/*
		PostUpdate : ���� ���, ���Ϳ��� ������Ʈ�� �� ��
		(���� ������Ʈ)������Ʈ ȣ���� ����, �� ���� Move�� ȣ���ϹǷ�,
		�̵��� ����� 1������ �и��� �ȴ�. 
		�׷��� ������Ʈ �Ŀ� ���������� ������Ʈ�� �ѹ� �� ó�����ִ� 
		PostUpdate�� �����.

		PostUpdate�� ���� �̵����� ���� ������ ó���� ���ָ� �ȴ�.
	*/
	virtual void PostUpdate(float _deltaTime);
	virtual void Render(HDC _hDC, float _deltaTime);
	// �������� �Դ� �Լ�
	virtual float InflictDamage(float _damage, int _dir = 1);
	class CCollider* FindCollider(const std::string& _name);
	virtual enum class ESkillState GetPowerStrikeState();
	virtual ESkillState GetSlashBlastState() ;
	virtual ESkillState GetJudgementState();
	virtual ESkillState GetJusticeState();
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
	virtual ESkill GetUseSkill() const;
	virtual bool GetFlag() const;
	int GetDir() const;
	bool GetGround() const;
	bool GetJump() const;
	ERenderLayer GetRenderLayer() const;
	float GetTimeScale() const;
	const Vector2& GetPos() const;
	const Vector2& GetSize() const;
	const Vector2& GetPivot() const;
	bool GetLadder() const;
	virtual void SetPortalEnable(std::string _portalName);
	void SetMoveSpeed(float _speed);
	virtual void SetFlag(bool _flag);
	void SetLadder(bool _ladder);
	void SetEnableUpKey_Portal(bool _enable);
	void SetEnableUpKey(bool _enable);
	void SetEnableDownKey(bool _enable);
	void SetFallTime(float _time);
	void SetFallStartY(float _y);
	void SetGround(bool _ground);
	void SetJump(bool _jump);
	void SetRenderLayer(ERenderLayer _layer);
	void SetPhysicsSimulate(bool _physics);
	void SetGravityAccel(float _accel);
	void SetJumpVelocity(float _jumpVelocity);
	void SetTimeScale(float _scale);
	void SetPos(const Vector2& _pos);
	void SetPos(float _x, float _y);
	void SetSize(const Vector2& _size);
	void SetSize(float _x, float _y);
	void SetPivot(const Vector2& _pivot);
	void SetPivot(float _x, float _y);

	virtual void OpenUIWindow();

	// sprite Ÿ���� �ؽ��� ����
	void SetTexture(const std::string& _name);	// �̸�����
	void SetTexture(class CTexture* _texture);	// �ؽ��� ��ü��
	void SetTexture(const std::string& _name, const TCHAR* _fileName,
		const std::string& _pathName = TEXTURE_PATH);	// �̸�, �����̸�, ��η�
	void SetTextureFullPath(const std::string& _name, const TCHAR* _fullPath);	// �̸�, �����Ѱ�η�

#ifdef UNICODE	// frame Ÿ���� �ؽ��� ���� (�����ڵ� ȯ��)
	
	void SetTexture(const std::string& _name, const std::vector<std::wstring>& _vecFileName,
		const std::string& _pathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& _name, const std::vector<std::wstring>& _vecFullPath);

#else	// frame Ÿ���� �ؽ��� ���� (��Ƽ����Ʈ ȯ��)

	void SetTexture(const std::string& _name, const std::vector<std::string>& _vecFileName,
		const std::string& _pathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& _name, const std::vector<std::string>& _vecFullPath);

#endif // UNICODE
	/*
		�̷��� ���� �Լ��� �����ҽ�, ���ҽ��Ŵ���, ���ӿ�����Ʈ��
		�Ȱ��� �����ϴ� ������ �ʿ��� ������ �ٷ� �� �� 
		�ֵ��� �ϱ� �����̴�.
	*/
	// �ؽ����� �̹���(�ε����� �ش��ϴ�)�� �÷�Ű�� �����Ѵ�.
	bool SetColorKey(unsigned char _r, unsigned char _g, unsigned char _b, int _index = 0);
	// �ؽ����� ��� �̹����� �÷�Ű�� �����Ѵ�.
	bool SetColorKeyAll(unsigned char _r, unsigned char _g, unsigned char _b);

public:
	void CreateAnimation();
	void AddAnimation(const std::string& _sequenceName, bool _loop = true,
		float _playTime = 1.f, float _playScale = 1.f,
		bool reverse = false);
	void SetPlayTime(const std::string& _name, float _playTime);
	void SetPlayScale(const std::string& _name, float _playScale);
	void SetPlayLoop(const std::string& _name, bool _loop);
	void SetPlayReverse(const std::string& _name, bool _reverse);
	void SetCurrentAnimation(std::string& _name);
	virtual void AddEXP(float _exp);
	virtual void AddMoney(int _money);
	void ChangeAnimation(const std::string& _name);
	bool CheckCurrentAnimation(const std::string& _name);

public:
	// Ư�� �������� �̵���Ų��.
	void MoveDir(const Vector2& _dir);
	// xy�� ���뷮��ŭ �̵���Ų��. 
	void Move(const Vector2& _moveValue);
	// Ư�� ������ �̵���Ų��.
	void Move(float _angle);
	void Jump();

	template <typename T>
	void SetEndFunction(const std::string& _name, T* _obj, void(T::* _func)())
	{
		if (m_animation)
			m_animation->SetEndFunction<T>(_name, _obj, _func);
	}

	template <typename T>
	void AddNotify(const std::string& _name, int _frame, T* _obj, void(T::* _func)())
	{
		if (m_animation)
			m_animation->AddNotify<T>(_name, _frame, _obj, _func);
	}

	/*
		���� �ִϸ��̼�(currentAnimation)�� ���� �� ȣ���� �Լ��� �߰��Ѵ�.

		�ϳ��� �ִϸ��̼ǿ��� ���� ���(�ȱ�, ���� ���� ��)�� ����ִ�.
		�� ��ǵ��� ���ư��鼭 ���� �ִϸ��̼����� �����Ǵµ�,
		� ����� �����ǵ� ����ɶ����� ȣ������ �Լ��� ���� ���̴�.
	*/
	template <typename T>
	void SetCurrentAnimationEndFunction(T* _obj, void(T::* _func)())
	{
		if (m_animation)
			m_animation->SetCurrentAnimationEndFunction<T>(_obj, _func);
	}

	// �浹ü�� ���� ����(�ڽ�, �� ��)�� ������ �� �����Ƿ�, ������ ���ø�����
	template <typename T>
	T* AddCollider(const std::string& _name)
	{
		// �浹ü ���� �� �ʱ�ȭ
		T* collider = new T;

		collider->SetName(_name);
		collider->m_owner = this;
		collider->m_scene = m_scene;

		if (!collider->Init())
		{
			SAFE_DELETE(collider);
			return nullptr;
		}

		m_colliderList.push_back(collider);

		return collider;
	}

	// �̸����� ������ ã�´�.
	CWidgetComponent* FindWidgetComponent(const std::string& _name)
	{
		auto	iter = m_widgetComponentList.begin();
		auto	iterEnd = m_widgetComponentList.end();

		for (; iter != iterEnd; ++iter)
		{
			if ((*iter)->GetName() == _name)
				return *iter;
		}

		return nullptr;
	}

	// �̸��� �ش��ϴ� ������ �����.
	template <typename T>
	CWidgetComponent* CreateWidgetComponent(const std::string& _name)
	{
		CWidgetComponent* widget = FindWidgetComponent(_name);

		if (widget)
			return widget;

		widget = new CWidgetComponent;

		widget->m_owner = this;
		widget->m_scene = m_scene;
		widget->SetName(_name);

		if (!widget->Init())
		{
			SAFE_DELETE(widget);
			return nullptr;
		}

		widget->CreateWidget<T>(_name);

		m_widgetComponentList.push_back(widget);

		return widget;
	}

protected:
	CGameObject();
	CGameObject(const CGameObject& _obj);
	virtual ~CGameObject();

	friend class CScene;	// �� �������� �� ������ �Ѱܹޱ� ����
	friend class CInput;    // ��ǲ Ŭ�������� ���콺 ������Ʈ�� �����ϱ� ����
};

