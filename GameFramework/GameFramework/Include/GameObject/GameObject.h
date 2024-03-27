#pragma once

/* 
   파일 생성시, GameObject 폴더를 미리 만든 뒤
   GameObject/GameObject.h
   GameObject/GameObject.cpp 로 생성한다.
*/

// ../ : 이전 폴더에 존재하는 헤더를 포함한다는 의미이다.

#include "../Ref.h"
#include "../Animation/Animation.h"
#include "../UI/WidgetComponent.h"
/*
	CGameObject : 게임의 존재하는 오브젝트들의 최상위 부모이다.
	오브젝트 중의 하나인 캐릭터는 오브젝트를 상속하고,
	캐릭터 중의 하나인 플레이어는 캐릭터는 상속하는 식으로 만든다.
*/
class CGameObject
	: public CRef
{
protected:
	// 오브젝트가 출력될 레이어이다. (오브젝트가 속한 레이어)
	ERenderLayer m_renderLayer;
	// 오브젝트를 출력하는 텍스쳐이다.
	CSharedPtr<class CTexture> m_texture;
	// 오브젝트의 애니메이션이다.
	CAnimation* m_animation;
	// 오브젝트의 배속 비율이다.
	float m_timeScale;
	// 오브젝트의 이동 속도이다. 이것을 이용해 여러 형태의 Move 함수를 만들 것이다.
	float m_moveSpeed; 
	// 오브젝트의 이동량이다. 
	Vector2 m_prevPos;
	Vector2 m_move;
	// 모든 오브젝트는 자신이 존재할 위치, 크기, 피봇을 갖으므로 최상위 부모에 둔다.
	/*
		피봇(pivot) :
		물체의 기준점인 pos가 물체 내에서 존재하는 위치를
		0 ~ 1 사이의 비율로 나타낸 값.

		pivot이 (0.5, 0.5)이면 pos가 물체의 중심에 위치하도록 물체가 그려진다.
		pivot이 (0, 0)이면 pos가 물체의 좌상단에 위치하도록 물체가 그려진다.
		pivot이 (1, 1)이면 pos가 물체의 우하단에 위치하도록 물체가 그려진다.
	*/
	Vector2 m_pos;
	Vector2 m_size;
	Vector2 m_pivot;
	/*int m_dir;*/

	// 오브젝트에서 씬을 알게 함으로써 다른 객체를 생성할 수 있다.(몬스터 -> 불릿)
	class CScene* m_scene;

	// 오브젝트에 속한 충돌체 리스트이다.
	std::list<CSharedPtr<class CCollider>>	m_colliderList;
	// 오브젝트에 속한 위젯 컴포넌트 리스트이다.
    std::list<CSharedPtr<CWidgetComponent>>	m_widgetComponentList;

	/*
		오브젝트에 중력을 적용할지 말지를 결정하는 변수이다.
		이 변수를 통해 on/off 하면서,
		모든 오브젝트들이 언제든지 중력을 적용할 수 있게 한다.

		예를 들어 무너지는 발판 같은 경우, 플레이어가 닿았을 때
		중력을 on해서 무너뜨리는 방법 등이 있다.
	*/
	bool m_physicsSimulate;
	bool		m_ground;	     // 땅을 밟고 있는 상태인지 아닌지 
	float		m_fallTime;		 // 떨어진 시간 (가속도를 대신함)
	float		m_gravityAccel;  // 떨어진 시간에 10배 해줌 
	float		m_fallStartY;    // 떨어지기 시작한 y좌표
	bool		m_jump;			 // 점프중인지 아닌지
	float		m_jumpVelocity;  // 점프 속도(V)

	int m_objDir;
	bool m_enableUpKey;	// 위쪽 방향키 사용 가능한 상태인지
	bool m_enableUpKey_Portal;
	bool m_enableDownKey;	// 위쪽 방향키 사용 가능한 상태인지
	bool m_ladder;				// 사다리를 타고있는 상태인지
public:
	// 자식에서 구현할 내용을 가상 함수로 정의한다.
	virtual bool Init();
	virtual void Update(float _deltaTime);
	/*
		PostUpdate : 예를 들어, 몬스터에서 업데이트를 할 때
		(게임 오브젝트)업데이트 호출이 먼저, 그 다음 Move를 호출하므로,
		이동량 계산이 1프레임 밀리게 된다. 
		그래서 업데이트 후에 마지막으로 업데이트를 한번 더 처리해주는 
		PostUpdate를 만든다.

		PostUpdate를 통해 이동량이 계산된 다음에 처리를 해주면 된다.
	*/
	virtual void PostUpdate(float _deltaTime);
	virtual void Render(HDC _hDC, float _deltaTime);
	// 데미지를 입는 함수
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

	// sprite 타입의 텍스쳐 세팅
	void SetTexture(const std::string& _name);	// 이름으로
	void SetTexture(class CTexture* _texture);	// 텍스쳐 자체로
	void SetTexture(const std::string& _name, const TCHAR* _fileName,
		const std::string& _pathName = TEXTURE_PATH);	// 이름, 파일이름, 경로로
	void SetTextureFullPath(const std::string& _name, const TCHAR* _fullPath);	// 이름, 완전한경로로

#ifdef UNICODE	// frame 타입의 텍스쳐 세팅 (유니코드 환경)
	
	void SetTexture(const std::string& _name, const std::vector<std::wstring>& _vecFileName,
		const std::string& _pathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& _name, const std::vector<std::wstring>& _vecFullPath);

#else	// frame 타입의 텍스쳐 세팅 (멀티바이트 환경)

	void SetTexture(const std::string& _name, const std::vector<std::string>& _vecFileName,
		const std::string& _pathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& _name, const std::vector<std::string>& _vecFullPath);

#endif // UNICODE
	/*
		이렇게 같은 함수를 씬리소스, 리소스매니저, 게임오브젝트에
		똑같이 정의하는 이유는 필요한 곳에서 바로 쓸 수 
		있도록 하기 위함이다.
	*/
	// 텍스쳐의 이미지(인덱스에 해당하는)의 컬러키를 지정한다.
	bool SetColorKey(unsigned char _r, unsigned char _g, unsigned char _b, int _index = 0);
	// 텍스쳐의 모든 이미지의 컬러키를 지정한다.
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
	// 특정 방향으로 이동시킨다.
	void MoveDir(const Vector2& _dir);
	// xy의 절대량만큼 이동시킨다. 
	void Move(const Vector2& _moveValue);
	// 특정 각도로 이동시킨다.
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
		현재 애니메이션(currentAnimation)이 끝날 때 호출할 함수를 추가한다.

		하나의 애니메이션에는 여러 모션(걷기, 공격 정지 등)이 들어있다.
		이 모션들이 돌아가면서 현재 애니메이션으로 지정되는데,
		어떤 모션이 지정되든 종료될때마다 호출해줄 함수를 만들 것이다.
	*/
	template <typename T>
	void SetCurrentAnimationEndFunction(T* _obj, void(T::* _func)())
	{
		if (m_animation)
			m_animation->SetCurrentAnimationEndFunction<T>(_obj, _func);
	}

	// 충돌체는 여러 형태(박스, 원 등)로 존재할 수 있으므로, 생성은 템플릿으로
	template <typename T>
	T* AddCollider(const std::string& _name)
	{
		// 충돌체 생성 및 초기화
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

	// 이름으로 위젯을 찾는다.
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

	// 이름에 해당하는 위젯을 만든다.
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

	friend class CScene;	// 씬 변수에다 씬 정보를 넘겨받기 위해
	friend class CInput;    // 인풋 클래스에서 마우스 오브젝트를 생성하기 위해
};

