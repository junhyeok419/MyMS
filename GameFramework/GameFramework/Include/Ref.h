#pragma once
#include "GameInfo.h"
/*
	��۸� ������(�����Ͱ� �̹� ������ �޸��� �ּҸ� ���� ����)��
	���� �ذ��ϱ� ���� '����Ʈ ������'�� �����.

	1. ���۷��� Ŭ���� : 
		- ���۷��� ī��Ʈ�� �̿���, �޸� ������ �ٷ� �������� �ʰ�
		ī��Ʈ�� 1�� ���ҽ��� ī��Ʈ�� 0�� �ɶ� �����ϰ� �����.

		- �� ��, ��Ÿ�� ���� Ŭ������ � Ÿ�������� �˾Ƴ� �� �ִ�
		  ��ɵ� ������ �ִ�.

	2. ���� ������(SharedPointer) : 
		- ���۷��� Ŭ������ �����ϴ� ���ø��̴�.

		- ����Ʈ �����ͷ� ����ϱ� ���ϴ� Ŭ����Ÿ���� �� ���ø��� ���ڷ� �����Ѵ�.
		  ���� �����ͷ� Ŭ������ ����Ű�� �Ѵ�.

	    - ���� �����Ͱ� ����Ű�� Ŭ������ ���۷��� Ŭ������ ��������ν�,
		  ���� �����ͷ� �ش� Ŭ������ ���۷��� ī��Ʈ�� �����Ѵ�.
*/
class CRef
{
protected:
	int m_refCount;		// ���۷��� ī��Ʈ

	std::string m_name;		// �̸� (ù �ʱ�ȭ �� ���ϴ�) 
	std::string m_typeName; // Ŭ���� �̸�
	size_t m_typeID;		// Ŭ���� �����ڵ�

	bool m_enable;			// Ȱ��(1) / ��Ȱ��(0) 
	bool m_active;			// ����ִ��� �׾����� Ȯ��
public:
	void AddRef();		// ī��Ʈ �߰�
	int Release();		// ī��Ʈ ����, ī��Ʈ�� ��ȯ

	int GetRefCount() const;
	const std::string& GetName() const;
	const std::string& GetTypeName() const;
	size_t GetTypeID() const;
	bool GetEnable() const;
	bool GetActive() const;
	void SetName(const std::string& _name);
	void SetEnable(bool _enable);
	void SetActive(bool _active);

	template <typename T>
	void SetTypeID()
	{
		/*
			typeid(T).name() : TŸ���� �̸��� ���ڿ��� ���´�.
			T�� int�� "int"��, CRef�� "class CRef"�� ���´�.

			typeid(T).hash_code() : TŸ���� ������ ��ȣ�� ���´�.
			��� Ÿ���� ������ ��ȣ�� ������ �ִ�.
		*/
		m_typeName = typeid(T).name();
		m_typeID = typeid(T).hash_code();
	}

	template <typename T>
	bool CheckTypeID() const
	{
		// '���� Ÿ��'�� '���ø� ���ڷ� ���� Ÿ��'�� ������ �Ǵ�
		return m_typeID == typeid(T).hash_code();
	}

	CRef();
	CRef(const CRef& _ref);
	virtual ~CRef();
};
