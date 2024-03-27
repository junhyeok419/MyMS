#pragma once

#include "../GameInfo.h"

/*
	노티파이 : 예를 들어, 활쏘기 공격 애니메이션을 실행한다고 해서
	바로 공격이 나가는 것이 아니라, 시위를 놓는 프레임에 공격이 나가는 등
	딜레이가 있다. 
	따라서 애니메이션의 원하는 특정 프레임에 호출될 함수를 등록하여 
	사용할 수 있도록 만들 것이고 이것이 노티파이다.

	걷기 모션중 발이 땅에 닫는 프레임마다 먼지가 나는 이펙트나 사운드의
	함수를 등록시키는 등, 좀 더 그럴듯한 게임을 만들 수 있다.
*/
struct AnimationNotify
{
	int Frame;	// 함수를 몇 번째 프레임에 등록할 것인지
	/*
		Call 변수 존재 이유 : 특정 프레임에 노티파이 함수가 실행
		되었을 경우, 남은 애니메이션 프레임 동안(해당 모션이 전부
		끝날때 까지)같은 노티파이 함수를 실행하지 않기 위해
		Call을 true로 만들어 구분한다.

		만약 이러한 구분이 없으면, 3프레임에서 동작하는 함수가
		있다고 할 때, 프레임이 지나가는 시간보다 함수가 동작하는
		시간이 빠르다면 몇번이고 호출 될 여지가 있다.
	*/
	bool Call;	// 현재 모션 실행중에 함수가 호출 되었는지
	std::function<void()> Function;	 // 호출할 함수

	AnimationNotify()
		: Frame(0)
		, Call(false)
	{}
};

/*
	애니메이션 인포 : '애니메이션 시퀀스'를 '1개' 가지고 있으면서,
	해당 모션을 총 몇초에 걸쳐서 한 번 재생할지, 모션을 반복 재생할지
	등을 정의해두는 클래스이다. (모션 하나에 대한 정보)
*/
class CAnimationInfo
{
private:
	CSharedPtr<class CAnimationSequence> m_sequence; // 담당 애니메이션 시퀀스를 1개 갖는다.
	int m_frame;	// 애니메이션이 동작되는 프레임 
	/*
		time은 '애니메이션의 프레임을 증가시켜주기 위한 시간값'이다.
		예를 들어, 3프레임 짜리 애니메이션이 1번 동작하는데에 1초가 걸렸다면,
		1프레임 당 0.333...초가 걸렸다는 뜻인데,
		이 0.333...초가 지났는지를 판단하는 값이다. 
	*/
	float m_time;		
	float m_frameTime;	// 한 프레임이 증가하기 위한 시간. 여기에 위에서 말한 0.333...초가 들어온다.
	float m_playTime;	// 모션이 1번 동작하기 위한 시간. 이것이 1초라면 모션이 1번 동작하는데에 1초가 걸린다.
	float m_playScale;  // 재생속도 배율
	bool  m_loop;		// 반복재생 여부
	bool  m_reverse;	// 역재생 여부
	std::function<void()> m_endFunction; // 애니메이션이 끝날 때마다 호출할 함수 등록
	std::vector<AnimationNotify*> m_vecNotify; // 이 애니메이션의 노티파이. 당연히 여러개 등록할 수 있도록 벡터로
public:
	template <typename T>
	void SetEndFunction(T* _obj, void(T::* _func)())
	{
		/*
			std::bind : 함수 등록
			멤버함수를 등록할 때, 함수주소와 객체주소를
			모두 전달해야 한다.
		*/
		m_endFunction = std::bind(_func, _obj);
	}
	template <typename T>
	void AddNotify(int _frame, T* _obj, void(T::* _func)())
	{
		// 노티파이 생성
		AnimationNotify* notify = new AnimationNotify;

		// 프레임과 함수 등록
		notify->Frame = _frame;
		notify->Function = std::bind(_func, _obj);

		// 벡터에 추가
		m_vecNotify.push_back(notify);
	}
private:
	CAnimationInfo();
	~CAnimationInfo();

	friend class CAnimation;
	friend class CGameObject;
};

