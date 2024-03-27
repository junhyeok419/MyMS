#pragma once

// ���� ���а��� ���̺귯�� ���
#include <cmath>

const float PI = 3.14159f;

// �Ǽ��� �̷���� x,y��ǥ�� ������ Vector2�� ���� 
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
		�ſ��߿�!! ���� ���ϱ� :
		1. �غ��� ���̸� �˸� ��Ÿ��� ������ ���� ������ ���� �� �ִ�.
		2. ������ �˰� �Ǿ����Ƿ� cos��Ÿ�� ���� �� �ִ� ( �غ� / ���� )
		3. ���� cos��Ÿ�� arccos(�ڻ����� ��)�� ���ϸ�, ����(��Ÿ)�� ���´�.
	*/
	float Angle(const Vector2& v)	const
	{
		// �غ�
		float width = v.x - x;

		// ����
		float height = v.y - y;

		// ���� (sqrtf : ��Ʈ)
		float c = sqrtf(width * width + height * height);

		// cos ��Ÿ ( a / c )
		float angle = width / c;

		/*
			���� cos ��Ÿ�� arccos�� ���ϸ�, ���� ����(��Ÿ)�� �����µ�,
			�� ������ PI�� ������ 180.f�� ���� �������� ��ȯ�Ѵ�.

			���� �Լ��� ���� ������ ���ڸ� �ޱ� �����̴�.
		*/
		angle = acosf(angle) / PI * 180.f;

		// ����� �� �Ʒ��� ���� ���??
		if (v.y < y)
			angle = 360.f - angle;

		return angle;
	}

	// ��Ÿ��� ������ �̿��� ���� ������ �Ÿ��� ���Ѵ�.
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