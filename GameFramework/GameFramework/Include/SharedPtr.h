#pragma once

/*
	공유 포인터(SharedPointer) :
	  - 레퍼런스 클래스를 관리하는 템플릿이다.

	  - 스마트 포인터로 사용하기 원하는 클래스타입을 이 템플릿의 인자로 전달한다.
		공유 포인터로 객체를 가리키게 한다.

	  - 공유 포인터가 가리키는 객체는 레퍼런스 클래스를 상속함으로써,
		공유 포인터로 해당 객체의 레퍼런스 카운트를 조작한다.
*/
template <typename T>
class CSharedPtr
{
private:
	T* m_ptr;	// 템플릿 인자로 전달된 클래스의 포인터 타입을 의미한다.

public:
	void operator=(const CSharedPtr<T>& _ptr)
	{
		/*
			기존에 참조하던 객체가 있을경우, 
			연결이 끊어지므로 기존 객체의 레퍼런스 카운트를 1 감소
		*/ 
		if (m_ptr)
			m_ptr->Release();

		m_ptr = _ptr.m_ptr;

		// 새로운 객체를 참조하므로, 해당 객체의 레퍼런스 카운트 1 증가
		if (m_ptr)
			m_ptr->AddRef();
	}

	void operator=(T* _ptr)
	{
		if (m_ptr)
			m_ptr->Release();

		m_ptr = _ptr;

		if (m_ptr)
			m_ptr->AddRef();
	}

	bool operator==(const CSharedPtr<T>& _ptr) const
	{
		return m_ptr == _ptr.m_ptr;
	}

	bool operator==(T* _ptr) const
	{
		return m_ptr == _ptr;
	}

	bool operator!=(const CSharedPtr<T>& _ptr) const
	{
		return m_ptr != _ptr.m_ptr;
	}

	bool operator!=(T* _ptr) const
	{
		return m_ptr != _ptr;
	}

	/*
		형변환 연산자 오버로딩 :
		SharedPtr 타입의 객체가 T*로 형변환 되어야 할 때 호출
	*/
	operator T*() const
	{
		return m_ptr;
	}

	T* operator->() const
	{
		return m_ptr;
	}

	T* operator*() const
	{
		return m_ptr;
	}

	T* Get() const
	{
		return m_ptr;
	}

	CSharedPtr()
		: m_ptr(nullptr)
	{}

	CSharedPtr(const CSharedPtr<T>& _ptr)
	{
		m_ptr = _ptr.m_ptr;

		/*
			_ptr이 가리키던 객체를 m_ptr도 가리키게 되었으므로, 
			m_ptr이 가리키는 객체의 레퍼런스 카운트를 1 증가시킨다.
		*/
		if (m_ptr)
			m_ptr->AddRef();
	}

	CSharedPtr(T* _ptr)
	{
		m_ptr = _ptr;

		if (m_ptr)
			m_ptr->AddRef();
	}

	~CSharedPtr()
	{
		/*
			m_ptr이 더이상 해당 객체를 가리키지 않게되므로,
			m_ptr이 가리키는 객체의 레퍼런스 카운트를 1 감소시킨다.
		*/
		if (m_ptr)
			m_ptr->Release();
	}
};

