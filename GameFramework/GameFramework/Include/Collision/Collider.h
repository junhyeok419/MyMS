#pragma once
#include "../Ref.h"

/*
	�浹ü�� ��Ÿ���� CCollider Ŭ�����̴�.
	���� ��� �뵵�̹Ƿ� �߻�Ŭ������ �����.

	�浹ü�� ���� ������ ������ �־�� �ϱ� ������ 
	�浹ü�� ��ġ, �浹 �������� ���� ������ ���´�.

	�浹ü�� ������ �� �ְ� ���� ���̹Ƿ� ���۷��� Ŭ������ ����ϸ�
	�翬�� ������Ʈ�� �޾��� ���̹Ƿ� CGameObject�� friend�� �����Ѵ�. 
*/
class CCollider
	: public CRef
{
protected:
	// Data
	class CScene* m_scene;				// �浹ü�� ���� ��
	class CGameObject* m_owner;			// �浹ü�� ���� ������Ʈ
	EColliderType     m_colliderType;	// �浹ü�� Ÿ��(�� or �ڽ�)
	/*
		������Ʈ�� �浹ü�� 2���� �̻� ������ ���� ���� �ִ�.
		�Ӹ��� ������ �浹ü�� ����ȭ �ϰų�, ���⸦ �ֵѷ��� ��
		�ָ� �������ִ� �浹ü�� ���� ���� �ִ�.
		���� �浹ü�� �󸶸�ŭ ������ �������� ���� ������ �ʿ��ϴ�. 

		���� ������Ʈ(����)�� �̰��� ���� ��ġ�� �߽�����, �浹ü�� ���� ���̴�. 
	*/
	Vector2            m_offset;		// owner�κ��� �浹ü�� �󸶸�ŭ ������ ������
	CollisionProfile*  m_profile;		// �浹 ��������
	Vector2			   m_hitPoint;		// �浹ü�� ��ġ�� ������ �߾� ��ǥ

	/*
		���콺 �浹���� �������� y������ �ϱ� ���� �浹ü�� ��ġ�̴�.
		�� ������ �� �浹ü�� PostUpdate ����
		������ �浹ü�� ���� ���� y��ǥ�� ���õȴ�.
	*/
	float              m_bottom;		

	/*
		�Ʒ��� �Լ� �����Ϳ��� CCollider* 2���� �޴� ������ 
		���� �浹�� �� ��ü�� ���ڷ� �Ѱ��ֱ� ���ؼ��̴�.
	*/
	std::function<void(CCollider*, CCollider*)> m_collisionBegin; // �浹�� ó�� �������� �� ȣ���� �Լ�
	std::function<void(CCollider*, CCollider*)> m_collisionEnd;	  // �浹 �� �������� �� ȣ���� �Լ�
	
	// ���콺 �浹�� ���, ���콺 Ŀ���� ���̹Ƿ� Vector2�� �����Ѵ�.
	std::function<void(CCollider*, const Vector2&)> m_mouseCollisionBegin;
	std::function<void(CCollider*, const Vector2&)> m_mouseCollisionEnd;

	/*
		m_collisionBegin �� ȣ�� ������, '��ü���� ù �浹'�� ��ǥ�� ��ġ��
		�������� �Ǵ��ϱ� ����.

		�׷��� �� ���� �������� �������� ��ü�� ���� �浹���̶�� �ٰŰ� �ʿ��ϱ� ������
		'���� �����ӿ� �浹�Ǿ��� �浹ü'�� ��� �� �ʿ䰡 �ִ�.
		
		��, ��ü�� �浹�Ǿ��µ� ����Ʈ�� ����ִ�. -> ��� �� �浹�� ��
		��ü�� �浹�Ǿ��µ� ����Ʈ�� ������� �ʴ�. -> �������� ���ݵ� �浹���� ��
		��ü�� �浹���� �ʾҴµ� ����Ʈ�� ������� �ʴ�. -> �浹 �� ��� ���� ������ ��
		�̷� ������ �� �Լ�(Begin, End)�� ȣ�� ������ ���� �Ǵ��� �����ϴ�.

		����Ʈ�� ������ �߰������� ����� �Ͼ�� ����
	*/
	std::list<CSharedPtr<CCollider>>    m_collisionList;  // �� �浹ü�� ���� �����ӿ��� �浹�� �浹ü ���
	/*
		���콺�� �浹ü�� �ƴ� ���̴�. ���� �浹 ��� ����Ʈ�� ���� ���� ���̴�.	
		
		���� ���콺 �浹�� ���� �浹�� �Ͼ���� �ȵǴ� �� �翬�Ͽ�
		��� ��ü�� �ʿ���� ������, bool Ÿ�� ������ �̿��� �浹ü�� ���콺��
		�浹�� �Ǿ����� �ȵǾ������� �Ǵ��� ���̴�.

		���콺 �浹�� �켱������ ui -> �ٸ� ���� ��ü�� ������
		���� ���̴�.
	*/
	bool m_mouseCollision;
public:
	// Logic
	virtual bool Init();
	virtual void Update(float _deltaTime);
	virtual void PostUpdate(float _deltaTime);
	virtual void Render(HDC hDC, float _deltaTime);
	virtual bool Collision(CCollider* _dest);		    // ���� �浹ü�� �޴´�.
	virtual bool CollisionMouse(const Vector2& _mouse);  // ���콺 Ŀ���� ��ǥ�� �޴´�.
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
	void SetCollisionProfile(const std::string& _name); // �浹 �������� ����� set
	void AddCollisionList(CCollider* _collider);		// ����Ʈ�� �浹ü �߰�
	bool CheckCollisionList(CCollider* _collider);		// ����Ʈ�� Ư�� �浹ü�� �����ϴ��� �Ǵ�
	void DeleteCollisionList(CCollider* _collider);		// ����Ʈ���� Ư�� �浹ü ���� 
	void ClearCollisionList();							// ����Ʈ �� ����
public:
	// CallBack
	void CallCollisionBegin(CCollider* _dest);			// �浹 ���ۿ� ���� �Լ��� ȣ������
	void CallCollisionEnd(CCollider* _dest);			// �浹 ���ῡ ���� �Լ��� ȣ������
	void CallMouseCollisionBegin(const Vector2& _mousePos);	// ���콺 �浹 ����
	void CallMouseCollisionEnd(const Vector2& _mousePos);   // ���콺 �浹 ����
public:
	// Template
	// �浹�� ������ �� ȣ���� �Լ��� �߰��Ѵ�.
	template <typename T>
	void SetCollisionBeginFunction(T* _obj, void(T::* _func)(CCollider*, CCollider*))
	{
		// placeholders : �����ϴ� �� ���ڸ� �����Ͽ� ���ʴ�� �ѱ��. 
		m_collisionBegin = std::bind(_func, _obj, std::placeholders::_1, std::placeholders::_2);
	}
	// �浹�� ����� �� ȣ���� �Լ��� �߰��Ѵ�.
	template <typename T>
	void SetCollisionEndFunction(T* _obj, void(T::* _func)(CCollider*, CCollider*))
	{
		m_collisionEnd = std::bind(_func, _obj, std::placeholders::_1, std::placeholders::_2);
	}
	// ���콺 �������� �߰��Ѵ�.
	template <typename T>
	void SetMouseCollisionBeginFunction(T* _obj, void(T::* _func)(CCollider*, const Vector2&))
	{
		m_mouseCollisionBegin = std::bind(_func, _obj, std::placeholders::_1, std::placeholders::_2);
	}
	// ���콺 �������� �߰��Ѵ�.
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

