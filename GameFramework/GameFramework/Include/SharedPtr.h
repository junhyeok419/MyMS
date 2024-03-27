#pragma once

/*
	���� ������(SharedPointer) :
	  - ���۷��� Ŭ������ �����ϴ� ���ø��̴�.

	  - ����Ʈ �����ͷ� ����ϱ� ���ϴ� Ŭ����Ÿ���� �� ���ø��� ���ڷ� �����Ѵ�.
		���� �����ͷ� ��ü�� ����Ű�� �Ѵ�.

	  - ���� �����Ͱ� ����Ű�� ��ü�� ���۷��� Ŭ������ ��������ν�,
		���� �����ͷ� �ش� ��ü�� ���۷��� ī��Ʈ�� �����Ѵ�.
*/
template <typename T>
class CSharedPtr
{
private:
	T* m_ptr;	// ���ø� ���ڷ� ���޵� Ŭ������ ������ Ÿ���� �ǹ��Ѵ�.

public:
	void operator=(const CSharedPtr<T>& _ptr)
	{
		/*
			������ �����ϴ� ��ü�� �������, 
			������ �������Ƿ� ���� ��ü�� ���۷��� ī��Ʈ�� 1 ����
		*/ 
		if (m_ptr)
			m_ptr->Release();

		m_ptr = _ptr.m_ptr;

		// ���ο� ��ü�� �����ϹǷ�, �ش� ��ü�� ���۷��� ī��Ʈ 1 ����
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
		����ȯ ������ �����ε� :
		SharedPtr Ÿ���� ��ü�� T*�� ����ȯ �Ǿ�� �� �� ȣ��
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
			_ptr�� ����Ű�� ��ü�� m_ptr�� ����Ű�� �Ǿ����Ƿ�, 
			m_ptr�� ����Ű�� ��ü�� ���۷��� ī��Ʈ�� 1 ������Ų��.
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
			m_ptr�� ���̻� �ش� ��ü�� ����Ű�� �ʰԵǹǷ�,
			m_ptr�� ����Ű�� ��ü�� ���۷��� ī��Ʈ�� 1 ���ҽ�Ų��.
		*/
		if (m_ptr)
			m_ptr->Release();
	}
};

