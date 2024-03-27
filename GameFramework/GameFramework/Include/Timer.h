#pragma once

#include "GameInfo.h"

/*
	윈도우는 고해상도 타이머를 제공한다.
	델타 타임(프레임과 프레임 사이의 시간 = 1프레임 당 걸리는 시간)을 구하고자 할 때,
	이 고해상도 타이머의 값을 얻어와서 구할 수 있다.
*/
class CTimer
{
private:
	/*
		LARGE_INTEGER은 정수로 이루어진 
		8바이트 공용체이다.
	*/
	LARGE_INTEGER m_second;			// 타이머가 1초동안 카운팅 가능한 값
	LARGE_INTEGER m_time;			// 현재까지 타이머가 카운팅 한 값

	float	      m_deltaTime;		// 델타 타임
	float		  m_fps;			// 초당 프레임
	float		  m_fpsTime;		
	float         m_tick;
public:
	void Init();
	void Update();
	float GetDeltaTime() const;
	float GetFPS() const;
	CTimer();
	~CTimer();
};

