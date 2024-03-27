#pragma once
#include "../Ref.h"

/*
	충돌체를 나타내는 CCollider 클래스이다.
	오직 상속 용도이므로 추상클래스로 만든다.

	충돌체에 대한 정보를 가지고 있어야 하기 때문에 
	충돌체의 위치, 충돌 프로파일 등의 정보를 갖는다.

	충돌체는 공유할 수 있게 만들 것이므로 레퍼런스 클래스를 상속하며
	당연히 오브젝트에 달아줄 것이므로 CGameObject를 friend로 지정한다. 
*/
class CCollider
	: public CRef
{
protected:
	// Data
	class CScene* m_scene;				// 충돌체가 속한 씬
	class CGameObject* m_owner;			// 충돌체가 속한 오브젝트
	EColliderType     m_colliderType;	// 충돌체의 타입(원 or 박스)
	/*
		오브젝트는 충돌체를 2가지 이상 가지고 있을 수도 있다.
		머리와 몸통의 충돌체를 세분화 하거나, 무기를 휘둘렀을 때
		멀리 떨어져있는 충돌체를 만들 수도 있다.
		따라서 충돌체가 얼마만큼 떨어져 있을지에 대한 변수가 필요하다. 

		또한 오브젝트(오너)에 이것을 더한 위치를 중심으로, 충돌체를 만들 것이다. 
	*/
	Vector2            m_offset;		// owner로부터 충돌체가 얼마만큼 떨어져 있을지
	CollisionProfile*  m_profile;		// 충돌 프로파일
	Vector2			   m_hitPoint;		// 충돌체가 겹치는 영역의 중앙 좌표

	/*
		마우스 충돌에서 내림차순 y소팅을 하기 위한 충돌체의 위치이다.
		이 변수는 각 충돌체의 PostUpdate 에서
		무조건 충돌체의 가장 높은 y좌표가 세팅된다.
	*/
	float              m_bottom;		

	/*
		아래의 함수 포인터에서 CCollider* 2개를 받는 이유는 
		서로 충돌된 두 물체를 인자로 넘겨주기 위해서이다.
	*/
	std::function<void(CCollider*, CCollider*)> m_collisionBegin; // 충돌을 처음 시작했을 때 호출할 함수
	std::function<void(CCollider*, CCollider*)> m_collisionEnd;	  // 충돌 후 떨어졌을 때 호출할 함수
	
	// 마우스 충돌의 경우, 마우스 커서는 점이므로 Vector2로 전달한다.
	std::function<void(CCollider*, const Vector2&)> m_mouseCollisionBegin;
	std::function<void(CCollider*, const Vector2&)> m_mouseCollisionEnd;

	/*
		m_collisionBegin 의 호출 조건인, '물체간의 첫 충돌'은 좌표가 겹치는
		시점으로 판단하기 쉽다.

		그러나 그 이후 겹쳐지는 시점부터 물체가 서로 충돌중이라는 근거가 필요하기 때문에
		'이전 프레임에 충돌되었던 충돌체'를 담아 둘 필요가 있다.
		
		즉, 물체가 충돌되었는데 리스트가 비어있다. -> 방금 막 충돌된 것
		물체가 충돌되었는데 리스트가 비어있지 않다. -> 이전에도 지금도 충돌중인 것
		물체가 충돌되지 않았는데 리스트가 비어있지 않다. -> 충돌 후 방금 서로 떨어진 것
		이런 식으로 위 함수(Begin, End)의 호출 시점에 대한 판단이 가능하다.

		리스트인 이유는 추가삭제가 빈번히 일어나기 때문
	*/
	std::list<CSharedPtr<CCollider>>    m_collisionList;  // 이 충돌체와 이전 프레임에서 충돌한 충돌체 목록
	/*
		마우스는 충돌체가 아닌 점이다. 따라서 충돌 목록 리스트에 넣지 않을 것이다.	
		
		또한 마우스 충돌은 동시 충돌이 일어나서는 안되는 게 당연하여
		목록 자체가 필요없기 때문에, bool 타입 변수를 이용해 충돌체가 마우스와
		충돌이 되었는지 안되었는지만 판단할 것이다.

		마우스 충돌의 우선순위는 ui -> 다른 월드 물체들 순으로
		만들 것이다.
	*/
	bool m_mouseCollision;
public:
	// Logic
	virtual bool Init();
	virtual void Update(float _deltaTime);
	virtual void PostUpdate(float _deltaTime);
	virtual void Render(HDC hDC, float _deltaTime);
	virtual bool Collision(CCollider* _dest);		    // 상대방 충돌체를 받는다.
	virtual bool CollisionMouse(const Vector2& _mouse);  // 마우스 커서의 좌표를 받는다.
public:
	// Access
	virtual void SetExtent(float _width, float _height);
	virtual void SetExtent(const Vector2& _size);
	virtual void SetLength(const float _length);
	void SetMouseCollision(bool _collision);
	void SetOffset(const Vector2& _offset);
	void SetOffset(float _x, float _y);
	const Vector2& GetOffset() const; 
	bool GetMouseCollision() const;
	float GetBottom()   const;
	virtual const Vector2& GetExtent() const;
	virtual const LineInfo& GetLineInfo() const;
	virtual const BoxInfo& GetBoxInfo() const;
	virtual const float& GetLength() const;
	const Vector2& GetHitPoint()  const;
	class CGameObject* GetOwner() const;
	class CScene* GetScene() const;
	EColliderType GetColliderType() const;
	const CollisionProfile* GetProfile() const;
public:
	// Collision profile & List
	void SetCollisionProfile(const std::string& _name); // 충돌 프로파일 멤버를 set
	void AddCollisionList(CCollider* _collider);		// 리스트에 충돌체 추가
	bool CheckCollisionList(CCollider* _collider);		// 리스트에 특정 충돌체가 존재하는지 판단
	void DeleteCollisionList(CCollider* _collider);		// 리스트에서 특정 충돌체 삭제 
	void ClearCollisionList();							// 리스트 다 지움
public:
	// CallBack
	void CallCollisionBegin(CCollider* _dest);			// 충돌 시작에 따른 함수를 호출해줌
	void CallCollisionEnd(CCollider* _dest);			// 충돌 종료에 따른 함수를 호출해줌
	void CallMouseCollisionBegin(const Vector2& _mousePos);	// 마우스 충돌 전용
	void CallMouseCollisionEnd(const Vector2& _mousePos);   // 마우스 충돌 전용
public:
	// Template
	// 충돌을 시작할 때 호출할 함수를 추가한다.
	template <typename T>
	void SetCollisionBeginFunction(T* _obj, void(T::* _func)(CCollider*, CCollider*))
	{
		// placeholders : 전달하는 두 인자를 고정하여 차례대로 넘긴다. 
		m_collisionBegin = std::bind(_func, _obj, std::placeholders::_1, std::placeholders::_2);
	}
	// 충돌이 종료될 때 호출할 함수를 추가한다.
	template <typename T>
	void SetCollisionEndFunction(T* _obj, void(T::* _func)(CCollider*, CCollider*))
	{
		m_collisionEnd = std::bind(_func, _obj, std::placeholders::_1, std::placeholders::_2);
	}
	// 마우스 전용으로 추가한다.
	template <typename T>
	void SetMouseCollisionBeginFunction(T* _obj, void(T::* _func)(CCollider*, const Vector2&))
	{
		m_mouseCollisionBegin = std::bind(_func, _obj, std::placeholders::_1, std::placeholders::_2);
	}
	// 마우스 전용으로 추가한다.
	template <typename T>
	void SetMouseCollisionEndFunction(T* _obj, void(T::* _func)(CCollider*, const Vector2&))
	{
		m_mouseCollisionEnd = std::bind(_func, _obj, std::placeholders::_1, std::placeholders::_2);
	}
protected:
	// Constructor, destructor
	CCollider();
	CCollider(const CCollider& _collider);
	virtual ~CCollider() = 0;

	friend class CGameObject;
	friend class CCollisionManager;
};

