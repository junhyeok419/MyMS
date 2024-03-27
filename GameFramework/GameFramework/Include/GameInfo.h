#pragma once

/*
	�� ��������� ���ӿ��� �������� ���Ǵ� ������� 
	include �Ͽ� ����� �������� �������.
*/
#include <Windows.h>
#include <list>
#include <vector>
#include <stack>
#include <unordered_map>
#include <crtdbg.h>
#include <typeinfo>
#include <string>
/*
	(����or����Լ���)�Լ������͸� ����س��� 
	����Ҽ��ֵ��� �ϴ� ����� ���� (CInput ����)
*/
#include <functional> 
/*
	���콺 �浹���� std::sort���� �Լ��� ����ϱ� ����
*/
#include <algorithm>
#include <ctime>
#include <cmath>

#include "Vector2.h"
#include "SharedPtr.h"
#include "Flag.h"
#include "fmod.hpp"		// ���� ����� ���� fmod ��� ����

#define	GRAVITY	9.8f

/*
	�̹����� ����Ϸ��� ���̺귯�� ��ũ�� �ɾ�� �Ѵ�.
	���̺귯�� ������ lib, dll�� �� ���� �������� �����Ѵ�.
	
	lib ���� ���̺귯�� ��ũ�� �Ŵ� ����� 2������ �ִ�.
	1. ������Ʈ �Ӽ� -> ��Ŀ -> �Է� -> �߰� ���Ӽ� -> lib���� ��ũ �ɱ�
	2. �ڵ忡�� ���� �ۼ� : #pragma comment ~~ 
	   (������ ���� �ܰ迡�� ��ó���⸦ ���� ���̺귯�� ��ũ �ɱ�)

	msimg32.lib�� �⺻������ �����Ǵ� �����̴�.
*/
#pragma comment(lib, "msimg32.lib")

/*
	���带 ����ϱ� ���� ���̺귯�� ��ũ�̴�.
	- fmod ���̺귯���� Bin������ �ִ´�.
	- ���� ��������� include������ �ִ´�.
	- ��ũ�� �Ǵ�.
*/
#pragma comment(lib, "../Bin/fmod64_vc.lib")

#define ROOT_PATH    "RootPath"
#define TEXTURE_PATH "TexturePath"
#define	SOUND_PATH	 "SoundPath"
#define	FONT_PATH	 "FontPath"


#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; } 
#define SAFE_DELETE_ARRAY(p) if(p) { delete[] p; p = nullptr; } 
#define SAFE_RELEASE(p)	if(p) { p->Release(); p=nullptr; }

float RadianToDegree(float _radian);	// ������ ������ ��ȯ�� ��ȯ
float DegreeToRadian(float _degree);	// ������ �������� ��ȯ�� ��ȯ

/*
	���ӸŴ����� ����� Ŭ�������� ��𿡼��� ��ŸŸ����
	����� �� �ֵ���, ���ӸŴ����� ��ŸŸ���� ��������� �ΰ�
	�� ��ũ�θ� �������.
*/
#define DELTA_TIME CGameManager::GetInst()->GetDeltaTime()

// �ػ󵵸� ǥ���ϴ� ����ü�̴�.
struct Resolution
{
	int Width;
	int Height;
};

/*
	sprite �̹����� ������ ������ ���������� ���� ��ǥ�̴�.
	������ �̹����� �ϳ��� 'frame'�̹����� ���� �ȴ�.
*/
struct AnimationFrameData
{
	Vector2 Start;
	Vector2 End;
};

/*
	�浹ü(collider)�� ���� ������ ����ִ� '�浹 ��������'�̴�.
	���������� ��� �� ä�ΰ� ä�ΰ��� ��ȣ�ۿ� ���¸� ���� 
	�浹�� üũ���� ������ �����ϴ� ������ �Ѵ�.
*/
struct CollisionProfile
{
	std::string							Name;
	ECollisionChannel					Channel;	// �� ���������� ����ϴ� ä��
	bool								Enable;		// Ȱ��ȭ ����
	std::vector<ECollisionInteraction>	VecCollisionInteraction;	// �ٸ� ä�ΰ��� �浹 ��ȣ�ۿ� 

	CollisionProfile() :
		Enable(true)
	{
	}
};

/*
	�ڽ�(Box)Ÿ�� �浹ü(Collider)�� ���� ��ǥ �����̴�.
	�ڽ� �浹ü Ŭ������ ����� ���� ���̴�
*/
struct BoxInfo
{
	Vector2 Lt;
	Vector2 Rb;
};

/*
	��(Circle)Ÿ�� �浹ü(Collider)�� ��ġ�� ���� �����̴�.
	�ڽ��� �ٸ��� ������ �������� �ʿ��ϴ�.

	�� �浹ü Ŭ������ ����� ���� ���̴�
*/
struct CircleInfo
{
	Vector2	Center;
	float	Radius;
};


struct LineInfo
{
	Vector2	Point1;
	Vector2	Point2;
};