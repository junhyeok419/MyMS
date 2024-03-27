#include "GameInfo.h"

// 라디안을 각도로 변환해 반환
float RadianToDegree(float _radian)
{
	return _radian / PI * 180.f;
}

// 각도를 라디안으로 변환해 반환
float DegreeToRadian(float _degree)
{
	return _degree / 180.f * PI;
}
