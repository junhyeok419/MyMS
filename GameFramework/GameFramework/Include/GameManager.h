#pragma once

#include "GameInfo.h"
#include "SingletonMacro.h"

// 윈도우 창 생성 및 전체 게임을 관리하는 클래스
class CGameManager
{
	DECLARE_SINGLE(CGameManager)
private:
	// 프로그램과 윈도우의 핸들을 갖는다.
	HINSTANCE m_hInst;
	HWND m_hWnd;
	HDC m_hDC;

	// 더블 버퍼링을 위한 변수들이다. : Init->Render 확인
	HDC m_hBackDC;
	HBITMAP m_hBackBmp;
	HBITMAP m_hBackPrevBmp;

	// 타이머를 얻어오기 위한 변수이다.
	class CTimer* m_timer;
	/*
		이 변수는 WndProc static 멤버 함수에서 이 변수를 이용해
		윈도우가 종료될 때 false로 만들어주기 위해
		static으로 선언하였다.
	*/
	static bool m_loop;
	float m_frameLimitTime;
	float m_deltaTime;

	// 윈도우의 해상도이다.
	Resolution m_rs;

	/*
		오브젝트 마다의 배속을 다르게 해야 한다면,
		게임 오브젝트의 scale을 설정하면 되고,
		전체의 배속을 설정해야 한다면 이 변수를 설정하고 
		각 단계에 전달하는 델타타임에 곱해주면 된다.
	*/
	float m_timeScale;	// 글로벌 재생 배율
	HBRUSH m_brush[(int)EBrushType::Max];	// 박스 충돌체 등에서 사용
	HPEN   m_pen[(int)EBrushType::Max]; // 원 충돌체 등에서 사용
public:
	bool Init(HINSTANCE _hInst);
	int Run();
	// 프로그램 종료
	void Exit();
	HBRUSH GetBrush(EBrushType _type) const;
	HPEN GetPen(EBrushType _type) const;
	float GetDeltaTime() const;
	HDC GetWindowDC() const;
	HWND GetWindowHandle() const;
	HINSTANCE GetWindowInstance() const;
	float GetTimeScale() const;
	float GetFPS()	const;
	void SetTimeScale(float _scale);
private:
	void Logic();
	/*
		어떤 게임이든 적용 가능하게 설계하기 위해, 게임을 크게 4가지 단계로 나눈다.
		1. Input : 사용자의 입력을 받는 단계 (마우스, 키보드..)
		2. Update : 입력받은 내용을 토대로 데이터를 업데이트하는 단계
		3. Collision : 업데이트된 데이터를 토대로 충돌 처리 단계 (투사체 충돌 등)
		4. Render : (출력되어야 하는 물체를 먼저 판단하고) 화면에 출력해야 하는 물체들을 출력하는 단계
	*/
	/*
		이 함수들은 델타타임을 인자로 받아, 컴퓨터 사양(프레임)에 구애받지 않고
		각 동작들을 처리할 수 있다.
		
		델타타임을 이용해 각 컴퓨터의 프레임에 따라 동작횟수를 조절하여 같은 결과를 보일 수 있다.
	*/
	void Input(float _deltaTime);
	bool Update(float _deltaTime);
	bool PostUpdate(float _deltaTime);
	void Collision(float _deltaTime);
	void Render(float _deltaTime);

	void Register();
	bool Create();

	// static 멤버함수는 전역함수처럼 함수포인터의 사용이 가능하다.
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

