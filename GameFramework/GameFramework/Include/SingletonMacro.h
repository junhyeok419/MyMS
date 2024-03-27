#pragma once

#define DECLARE_SINGLE(TYPE)\
private:\
	static TYPE* m_inst;\
public:\
	static TYPE* GetInst()\
	{\
		if (!m_inst)\
			m_inst = new TYPE;\
		return m_inst;\
	}\
	static void DestroyInst()\
	{\
		if(m_inst)\
		{\
			delete m_inst;\
			m_inst = nullptr;\
		}\
	}\
private:\
	TYPE();\
	~TYPE();

#define DEFINITION_SINGLE(TYPE) TYPE* TYPE::m_inst = nullptr;