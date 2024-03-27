#pragma once
#include "../GameObject/GameObject.h"
/*
	카메라 : 스크롤(캐릭터 이동 시 화면이 이동하는 것)이 가능하게 하기 위함이다.
	카메라는 씬별로 하나씩 배치할 것이며, 
	전체 해상도 내부에서 카메라는 타겟으로 지정한 오브젝트를 기준으로 일정 부분(윈도우 해상도)
	만을 보여줄 것이다.

	즉 사용자의 눈에 보이는 건 카메라가 보여주는 만큼(=윈도우창의 해상도)의 화면이다.


	*** 
		이렇게 만든 카메라에, 해상도 + 전체해상도만 지정해도 알아서 처리된다.
		피봇만 원하는 대로 잡자. 예를 들어, 피봇을 (0.2, 0.5)로 잡으면 화면의
		20% 지점에서 스크롤링이 될 것이다.
	***
*/
class CCamera
{
	friend class CScene;

private:	
	Vector2 m_pos;						// 현재 카메라의 위치 (윈도우창 해상도의 좌상단)
	Vector2 m_resolution;				// 카메라 영역 (윈도우 창의 해상도와 같음)
	Vector2 m_worldResolution;			// 전체 월드 해상도
	CSharedPtr<CGameObject> m_target;	// 카메라의 타겟 오브젝트. 카메라가 따라갈 것이다.
	Vector2 m_targetOffset;				// 타겟으로부터 카메라가 얼마나 떨어져있을 것인지. 기본 0
	/*
		타겟 오브젝트의 피봇이다.
		해상도(m_resolution)가 1280x720 이라면,
		타겟 피봇은 1280x720 내에서의 타겟의 위치에 대한 비율이다.

		타겟을 화면의 가운데에 놓고 쫓아갈 것인지, 다른쪽에 치우치게 놓고
		이동할 것인지 등을 결정한다.

		이 값이 0.5, 0.5라면 타겟이 씬의 중간을 넘어가는 순간 카메라가 따라간다.
	*/
	Vector2 m_targetPivot;				// 타겟이 화면에서 스크롤링 될 때의 비율		
public:
	void Update(float _deltaTime);
public:
	Vector2 GetPos() const;
	Vector2 GetResolution() const;
	Vector2 GetWorldResolution() const;
	CGameObject* GetTarget() const;
	Vector2 GetTargetOffset() const;
	Vector2 GetTargetPivot() const;
	void SetPos(const Vector2& _pos);
	void SetPos(float _x, float _y);
	void SetResolution(const Vector2& _resolution);
	void SetResolution(float _x, float _y);
	void SetWorldResolution(const Vector2& _worldResolution);
	void SetWorldResolution(float _x, float _y);
	void SetTargetOffset(const Vector2& _targetOffset);
	void SetTargetOffset(float _x, float _y);
	void SetTargetPivot(const Vector2& _targetPivot);
	void SetTargetPivot(float _x, float _y);
	void SetTarget(CGameObject* _target);
private:
	CCamera();
	~CCamera();
};

