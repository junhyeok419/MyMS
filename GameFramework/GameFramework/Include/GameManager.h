#pragma once

#include "GameInfo.h"
#include "SingletonMacro.h"

// ������ â ���� �� ��ü ������ �����ϴ� Ŭ����
class CGameManager
{
	DECLARE_SINGLE(CGameManager)
private:
	// ���α׷��� �������� �ڵ��� ���´�.
	HINSTANCE m_hInst;
	HWND m_hWnd;
	HDC m_hDC;

	// ���� ���۸��� ���� �������̴�. : Init->Render Ȯ��
	HDC m_hBackDC;
	HBITMAP m_hBackBmp;
	HBITMAP m_hBackPrevBmp;

	// Ÿ�̸Ӹ� ������ ���� �����̴�.
	class CTimer* m_timer;
	/*
		�� ������ WndProc static ��� �Լ����� �� ������ �̿���
		�����찡 ����� �� false�� ������ֱ� ����
		static���� �����Ͽ���.
	*/
	static bool m_loop;
	float m_frameLimitTime;
	float m_deltaTime;

	// �������� �ػ��̴�.
	Resolution m_rs;

	/*
		������Ʈ ������ ����� �ٸ��� �ؾ� �Ѵٸ�,
		���� ������Ʈ�� scale�� �����ϸ� �ǰ�,
		��ü�� ����� �����ؾ� �Ѵٸ� �� ������ �����ϰ� 
		�� �ܰ迡 �����ϴ� ��ŸŸ�ӿ� �����ָ� �ȴ�.
	*/
	float m_timeScale;	// �۷ι� ��� ����
	HBRUSH m_brush[(int)EBrushType::Max];	// �ڽ� �浹ü ��� ���
	HPEN   m_pen[(int)EBrushType::Max]; // �� �浹ü ��� ���
public:
	bool Init(HINSTANCE _hInst);
	int Run();
	// ���α׷� ����
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
		� �����̵� ���� �����ϰ� �����ϱ� ����, ������ ũ�� 4���� �ܰ�� ������.
		1. Input : ������� �Է��� �޴� �ܰ� (���콺, Ű����..)
		2. Update : �Է¹��� ������ ���� �����͸� ������Ʈ�ϴ� �ܰ�
		3. Collision : ������Ʈ�� �����͸� ���� �浹 ó�� �ܰ� (����ü �浹 ��)
		4. Render : (��µǾ�� �ϴ� ��ü�� ���� �Ǵ��ϰ�) ȭ�鿡 ����ؾ� �ϴ� ��ü���� ����ϴ� �ܰ�
	*/
	/*
		�� �Լ����� ��ŸŸ���� ���ڷ� �޾�, ��ǻ�� ���(������)�� ���ֹ��� �ʰ�
		�� ���۵��� ó���� �� �ִ�.
		
		��ŸŸ���� �̿��� �� ��ǻ���� �����ӿ� ���� ����Ƚ���� �����Ͽ� ���� ����� ���� �� �ִ�.
	*/
	void Input(float _deltaTime);
	bool Update(float _deltaTime);
	bool PostUpdate(float _deltaTime);
	void Collision(float _deltaTime);
	void Render(float _deltaTime);

	void Register();
	bool Create();

	// static ����Լ��� �����Լ�ó�� �Լ��������� ����� �����ϴ�.
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

