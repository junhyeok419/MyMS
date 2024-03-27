#pragma once

// 각종 수학관련 라이브러리 헤더
#include <cmath>

const float PI = 3.14159f;

// 실수로 이루어진 x,y좌표의 집합인 Vector2의 정의 
struct Vector2
{
	float x;
	float y;

	void operator = (const Vector2& v)
	{
		x = v.x;
		y = v.y;
	}

	void operator = (float f)
	{
		x = f;
		y = f;
	}

	bool operator == (const Vector2& v)	const
	{
		return x == v.x && y == v.y;
	}

	bool operator != (const Vector2& v)	const
	{
		return x != v.x || y != v.y;
	}

	// +
	Vector2 operator + (const Vector2& v)	const
	{
		Vector2	result;

		result.x = x + v.x;
		result.y = y + v.y;

		return result;
	}

	Vector2 operator + (float f)	const
	{
		Vector2	result;

		result.x = x + f;
		result.y = y + f;

		return result;
	}

	Vector2 operator + (int i)	const
	{
		Vector2	result;

		result.x = x + (float)i;
		result.y = y + (float)i;

		return result;
	}

	// +=
	void operator += (const Vector2& v)
	{
		x += v.x;
		y += v.y;
	}

	void operator += (float f)
	{
		x += f;
		y += f;
	}

	void operator += (int i)
	{
		x += (float)i;
		y += (float)i;
	}

	// -
	Vector2 operator - (const Vector2& v)	const
	{
		Vector2	result;

		result.x = x - v.x;
		result.y = y - v.y;

		return result;
	}

	Vector2 operator - (float f)	const
	{
		Vector2	result;

		result.x = x - f;
		result.y = y - f;

		return result;
	}

	Vector2 operator - (int i)	const
	{
		Vector2	result;

		result.x = x - (float)i;
		result.y = y - (float)i;

		return result;
	}

	// -=
	void operator -= (const Vector2& v)
	{
		x -= v.x;
		y -= v.y;
	}

	void operator -= (float f)
	{
		x -= f;
		y -= f;
	}

	void operator -= (int i)
	{
		x -= (float)i;
		y -= (float)i;
	}

	// *
	Vector2 operator * (const Vector2& v)	const
	{
		Vector2	result;

		result.x = x * v.x;
		result.y = y * v.y;

		return result;
	}

	Vector2 operator * (float f)	const
	{
		Vector2	result;

		result.x = x * f;
		result.y = y * f;

		return result;
	}

	Vector2 operator * (int i)	const
	{
		Vector2	result;

		result.x = x * (float)i;
		result.y = y * (float)i;

		return result;
	}

	// *=
	void operator *= (const Vector2& v)
	{
		x *= v.x;
		y *= v.y;
	}

	void operator *= (float f)
	{
		x *= f;
		y *= f;
	}

	void operator *= (int i)
	{
		x *= (float)i;
		y *= (float)i;
	}

	// /
	Vector2 operator / (const Vector2& v)	const
	{
		Vector2	result;

		result.x = x / v.x;
		result.y = y / v.y;

		return result;
	}

	Vector2 operator / (float f)	const
	{
		Vector2	result;

		result.x = x / f;
		result.y = y / f;

		return result;
	}

	Vector2 operator / (int i)	const
	{
		Vector2	result;

		result.x = x / (float)i;
		result.y = y / (float)i;

		return result;
	}

	// /=
	void operator /= (const Vector2& v)
	{
		x /= v.x;
		y /= v.y;
	}

	void operator /= (float f)
	{
		x /= f;
		y /= f;
	}

	void operator /= (int i)
	{
		x /= (float)i;
		y /= (float)i;
	}

	/*
		매우중요!! 각도 구하기 :
		1. 밑변과 높이를 알면 피타고라스 정리에 의해 빗변을 구할 수 있다.
		2. 빗변을 알게 되었으므로 cos세타를 구할 수 있다 ( 밑변 / 빗변 )
		3. 구한 cos세타의 arccos(코사인의 역)을 구하면, 각도(세타)가 나온다.
	*/
	float Angle(const Vector2& v)	const
	{
		// 밑변
		float width = v.x - x;

		// 높이
		float height = v.y - y;

		// 빗변 (sqrtf : 루트)
		float c = sqrtf(width * width + height * height);

		// cos 세타 ( a / c )
		float angle = width / c;

		/*
			구한 cos 세타의 arccos를 구하면, 최종 각도(세타)가 나오는데,
			그 각도를 PI로 나누고 180.f를 곱해 라디안으로 변환한다.

			관련 함수가 라디안 단위로 인자를 받기 때문이다.
		*/
		angle = acosf(angle) / PI * 180.f;

		// 대상이 더 아래에 있을 경우??
		if (v.y < y)
			angle = 360.f - angle;

		return angle;
	}

	// 피타고라스 정리를 이용해 두점 사이의 거리를 구한다.
	float Distance(const Vector2& v)	const
	{
		float Width = x - v.x;
		float Height = y - v.y;

		return sqrtf(Width * Width + Height * Height);
	}

	Vector2() :
		x(0.f),
		y(0.f)
	{
	}

	Vector2(float _x, float _y) :
		x(_x),
		y(_y)
	{
	}

	Vector2(const Vector2& v) :
		x(v.x),
		y(v.y)
	{
	}
};