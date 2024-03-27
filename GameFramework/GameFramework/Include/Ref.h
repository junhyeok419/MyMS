#pragma once
#include "GameInfo.h"
/*
	댕글링 포인터(포인터가 이미 해제된 메모리의 주소를 갖는 문제)를
	쉽게 해결하기 위해 '스마트 포인터'를 만든다.

	1. 레퍼런스 클래스 : 
		- 레퍼런스 카운트를 이용해, 메모리 공간을 바로 삭제하지 않고
		카운트를 1씩 감소시켜 카운트가 0이 될때 삭제하게 만든다.

		- 그 외, 런타임 도중 클래스가 어떤 타입인지를 알아낼 수 있는
		  기능도 가지고 있다.

	2. 공유 포인터(SharedPointer) : 
		- 레퍼런스 클래스를 관리하는 템플릿이다.

		- 스마트 포인터로 사용하기 원하는 클래스타입을 이 템플릿의 인자로 전달한다.
		  공유 포인터로 클래스를 가리키게 한다.

	    - 공유 포인터가 가리키는 클래스는 레퍼런스 클래스를 상속함으로써,
		  공유 포인터로 해당 클래스의 레퍼런스 카운트를 조작한다.
*/
class CRef
{
protected:
	int m_refCount;		// 레퍼런스 카운트

	std::string m_name;		// 이름 (첫 초기화 시 정하는) 
	std::string m_typeName; // 클래스 이름
	size_t m_typeID;		// 클래스 고유코드

	bool m_enable;			// 활성(1) / 비활성(0) 
	bool m_active;			// 살아있는지 죽었는지 확인
public:
	void AddRef();		// 카운트 추가
	int Release();		// 카운트 감소, 카운트를 반환

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
			typeid(T).name() : T타입의 이름을 문자열로 얻어온다.
			T가 int면 "int"를, CRef면 "class CRef"로 얻어온다.

			typeid(T).hash_code() : T타입의 고유한 번호를 얻어온다.
			모든 타입은 고유한 번호를 가지고 있다.
		*/
		m_typeName = typeid(T).name();
		m_typeID = typeid(T).hash_code();
	}

	template <typename T>
	bool CheckTypeID() const
	{
		// '현재 타입'과 '템플릿 인자로 들어온 타입'이 같은지 판단
		return m_typeID == typeid(T).hash_code();
	}

	CRef();
	CRef(const CRef& _ref);
	virtual ~CRef();
};
