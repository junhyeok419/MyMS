#pragma once

#include "GameInfo.h"

/*
	������� ���ػ� Ÿ�̸Ӹ� �����Ѵ�.
	��Ÿ Ÿ��(�����Ӱ� ������ ������ �ð� = 1������ �� �ɸ��� �ð�)�� ���ϰ��� �� ��,
	�� ���ػ� Ÿ�̸��� ���� ���ͼ� ���� �� �ִ�.
*/
class CTimer
{
private:
	/*
		LARGE_INTEGER�� ������ �̷���� 
		8����Ʈ ����ü�̴�.
	*/
	LARGE_INTEGER m_second;			// Ÿ�̸Ӱ� 1�ʵ��� ī���� ������ ��
	LARGE_INTEGER m_time;			// ������� Ÿ�̸Ӱ� ī���� �� ��

	float	      m_deltaTime;		// ��Ÿ Ÿ��
	float		  m_fps;			// �ʴ� ������
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

