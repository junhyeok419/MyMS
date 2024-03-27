#pragma once

/*
	이 헤더파일은 게임에서 공통으로 사용되는 내용들을 
	include 하여 사용할 목적으로 만들었다.
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
	(전역or멤버함수의)함수포인터를 등록해놓고 
	사용할수있도록 하는 기능을 제공 (CInput 연관)
*/
#include <functional> 
/*
	마우스 충돌에서 std::sort등의 함수를 사용하기 위함
*/
#include <algorithm>
#include <ctime>
#include <cmath>

#include "Vector2.h"
#include "SharedPtr.h"
#include "Flag.h"
#include "fmod.hpp"		// 사운드 사용을 위한 fmod 헤더 포함

#define	GRAVITY	9.8f

/*
	이미지를 사용하려면 라이브러리 링크를 걸어야 한다.
	라이브러리 파일은 lib, dll의 두 가지 형식으로 존재한다.
	
	lib 형식 라이브러리 링크를 거는 방법은 2가지가 있다.
	1. 프로젝트 속성 -> 링커 -> 입력 -> 추가 종속성 -> lib파일 링크 걸기
	2. 코드에서 직접 작성 : #pragma comment ~~ 
	   (컴파일 이전 단계에서 전처리기를 통해 라이브러리 링크 걸기)

	msimg32.lib는 기본적으로 제공되는 파일이다.
*/
#pragma comment(lib, "msimg32.lib")

/*
	사운드를 사용하기 위한 라이브러리 링크이다.
	- fmod 라이브러리를 Bin폴더에 넣는다.
	- 관련 헤더파일을 include폴더에 넣는다.
	- 링크를 건다.
*/
#pragma comment(lib, "../Bin/fmod64_vc.lib")

#define ROOT_PATH    "RootPath"
#define TEXTURE_PATH "TexturePath"
#define	SOUND_PATH	 "SoundPath"
#define	FONT_PATH	 "FontPath"


#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; } 
#define SAFE_DELETE_ARRAY(p) if(p) { delete[] p; p = nullptr; } 
#define SAFE_RELEASE(p)	if(p) { p->Release(); p=nullptr; }

float RadianToDegree(float _radian);	// 라디안을 각도로 변환해 반환
float DegreeToRadian(float _degree);	// 각도를 라디안으로 변환해 반환

/*
	게임매니저를 상속한 클래스들이 어디에서든 델타타임을
	사용할 수 있도록, 게임매니저에 델타타임을 멤버변수로 두고
	이 매크로를 만들었다.
*/
#define DELTA_TIME CGameManager::GetInst()->GetDeltaTime()

// 해상도를 표현하는 구조체이다.
struct Resolution
{
	int Width;
	int Height;
};

/*
	sprite 이미지의 어디부터 어디까지 가져올지에 대한 좌표이다.
	가져온 이미지를 하나의 'frame'이미지로 보게 된다.
*/
struct AnimationFrameData
{
	Vector2 Start;
	Vector2 End;
};

/*
	충돌체(collider)에 대한 정보를 담고있는 '충돌 프로파일'이다.
	프로파일의 멤버 중 채널과 채널간의 상호작용 상태를 통해 
	충돌을 체크할지 말지를 결정하는 역할을 한다.
*/
struct CollisionProfile
{
	std::string							Name;
	ECollisionChannel					Channel;	// 이 프로파일이 사용하는 채널
	bool								Enable;		// 활성화 여부
	std::vector<ECollisionInteraction>	VecCollisionInteraction;	// 다른 채널과의 충돌 상호작용 

	CollisionProfile() :
		Enable(true)
	{
	}
};

/*
	박스(Box)타입 충돌체(Collider)에 대한 좌표 정보이다.
	박스 충돌체 클래스의 멤버로 들어올 것이다
*/
struct BoxInfo
{
	Vector2 Lt;
	Vector2 Rb;
};

/*
	원(Circle)타입 충돌체(Collider)의 위치에 대한 정보이다.
	박스와 다르게 중점과 반지름이 필요하다.

	원 충돌체 클래스의 멤버로 들어올 것이다
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