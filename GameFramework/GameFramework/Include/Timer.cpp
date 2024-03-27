#include "Timer.h"

void CTimer::Init()
{
	// 타이머가 1초가 흘렀을 때의 값(타이머가 1초동안 카운팅 가능한 값)을 얻어온다.
	QueryPerformanceFrequency(&m_second);

	// 지금까지 카운팅한 타이머의 값을 얻어온다.
	QueryPerformanceCounter(&m_time);
}

void CTimer::Update()
{
	// 지금까지 카운팅한 타이머의 값을 얻어온다.
	// 즉, m_time은 '이전 update까지 카운팅한 타이머값'이 된다.
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	// 델타 타임을 구한다.
	// (지금까지 카운팅한 타이머값 - 이전 update까지 카운팅한 타이머값) / 초당 타이머값
	m_deltaTime = (time.QuadPart - m_time.QuadPart) / (float)m_second.QuadPart;

	// 이전 타이머값을 현재 타이머값으로 교체한다. (다음 계산을 위해)
	m_time = time;

	// 아래부터는 fps(초당 프레임)를 구한다.
	m_fpsTime += m_deltaTime;	// 델타타임을 누적시킨다.
	++m_tick;					// 1 프레임(1 update)씩 누적시킨다.

	if (m_tick == 60)			
	{
		/*
			만약 m_fpsTime에 누적된 환산 값이 0.2초라면,
			60프레임당 걸리는 시간이 0.2초라는 뜻이므로,
			fps는 300임을 알 수 있다.

			따라서 fps = tick / fpsTime이다.
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
	: m_second{}	// 공용체, 구조체를 0으로 초기화 할 때 이렇게 함 (배열처럼)
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
