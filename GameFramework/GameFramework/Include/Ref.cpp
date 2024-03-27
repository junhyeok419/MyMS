#include "Ref.h"

void CRef::AddRef()
{
	++m_refCount;
}

int CRef::Release()
{
	--m_refCount;

	// ���۷��� ī��Ʈ�� 0�� �Ǿ��� �� ��ü�� �Ҹ��Ų��.
	if (m_refCount <= 0)
	{
		delete this;
		return 0;
	}

	// ���� ���۷��� ī��Ʈ�� ��ȯ�Ѵ�.
	return m_refCount;
}

int CRef::GetRefCount() const
{
	return m_refCount;
}

const std::string& CRef::GetName() const
{
	return m_name;
}

const std::string& CRef::GetTypeName() const
{
	return m_typeName;
}

size_t CRef::GetTypeID() const
{
	return m_typeID;
}

bool CRef::GetEnable() const
{
	return m_enable;
}

bool CRef::GetActive() const
{
	return m_active;
}

void CRef::SetName(const std::string& _name)
{
	m_name = _name;
}

void CRef::SetEnable(bool _enable)
{
	m_enable = _enable;
}

void CRef::SetActive(bool _active)
{
	m_active = _active;
}

CRef::CRef()
	: m_refCount(0)
	, m_typeID(0)
	, m_enable(true)
	, m_active(true)
{
}

CRef::CRef(const CRef& _ref)
	: m_refCount(0)
	, m_typeName(_ref.m_typeName)
	, m_typeID(_ref.m_typeID)
	, m_enable(_ref.m_enable)
	, m_active(_ref.m_active)
{
}

CRef::~CRef()
{
}
