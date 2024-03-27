#include "Timer.h"

void CTimer::Init()
{
	// Ÿ�̸Ӱ� 1�ʰ� �귶�� ���� ��(Ÿ�̸Ӱ� 1�ʵ��� ī���� ������ ��)�� ���´�.
	QueryPerformanceFrequency(&m_second);

	// ���ݱ��� ī������ Ÿ�̸��� ���� ���´�.
	QueryPerformanceCounter(&m_time);
}

void CTimer::Update()
{
	// ���ݱ��� ī������ Ÿ�̸��� ���� ���´�.
	// ��, m_time�� '���� update���� ī������ Ÿ�̸Ӱ�'�� �ȴ�.
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	// ��Ÿ Ÿ���� ���Ѵ�.
	// (���ݱ��� ī������ Ÿ�̸Ӱ� - ���� update���� ī������ Ÿ�̸Ӱ�) / �ʴ� Ÿ�̸Ӱ�
	m_deltaTime = (time.QuadPart - m_time.QuadPart) / (float)m_second.QuadPart;

	// ���� Ÿ�̸Ӱ��� ���� Ÿ�̸Ӱ����� ��ü�Ѵ�. (���� ����� ����)
	m_time = time;

	// �Ʒ����ʹ� fps(�ʴ� ������)�� ���Ѵ�.
	m_fpsTime += m_deltaTime;	// ��ŸŸ���� ������Ų��.
	++m_tick;					// 1 ������(1 update)�� ������Ų��.

	if (m_tick == 60)			
	{
		/*
			���� m_fpsTime�� ������ ȯ�� ���� 0.2�ʶ��,
			60�����Ӵ� �ɸ��� �ð��� 0.2�ʶ�� ���̹Ƿ�,
			fps�� 300���� �� �� �ִ�.

			���� fps = tick / fpsTime�̴�.
		*/
		m_fps = m_tick / m_fpsTime;

		m_fpsTime = 0.f;
		m_tick = 0;
	}
}

float CTimer::GetDeltaTime() const
{
	return m_deltaTime;
}

float CTimer::GetFPS() const
{
	return m_fps;
}

CTimer::CTimer()
	: m_second{}	// ����ü, ����ü�� 0���� �ʱ�ȭ �� �� �̷��� �� (�迭ó��)
	, m_time{}	
	, m_deltaTime(0.f)
	, m_fps(0.f)
	, m_fpsTime(0.f)
	, m_tick(0)
{
}

CTimer::~CTimer()
{
}
