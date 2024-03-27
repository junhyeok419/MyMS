#pragma once
#include "AnimationInfo.h"

/*
	애니메이션 : '애니메이션 인포'를 여러 개 갖고 있음으로서,
	필요에 따라 모션의 전환 등을 할 수 있는,
	실질적으로 애니메이션을 돌려주는 클래스이다.

	게임 오브젝트가 이 애니메이션 객체를 갖고 있게 하여
	애니메이션을 재생하도록 할 것이다.
*/
class CAnimation
{
private:
	class CGameObject* m_owner;	// 이 애니메이션이 속한 오브젝트
	class CScene* m_scene;		// 이 애니메이션이 속한 씬
	/*
		하나의 애니메이션 인포는 곧 하나의 모션이 되므로,
		map으로 애니메이션 인포를 갖게 한다.
		여러 모션을 멤버로 등록해놓고 원할때마다 교체해서 사용하기 위함이다.
		모션은 실시간으로 추가하는 것이 아니니 map으로 저장한다.
	*/
	std::unordered_map<std::string, class CAnimationInfo*> m_mapAnimation;
	class CAnimationInfo* m_currentAnimation;	// 현재 적용중인 애니메이션 주소. 위 map의 요소중 하나
	std::function<void()>	m_currentAnimationEndFunc;
public:
	// 애니메이션 시퀀스를 추가한다.
	void AddAnimation(const std::string& _sequenceName, bool _loop = true,
		float _playTime = 1.f, float _playScale = 1.f, bool _reverse = false);
	void SetPlayTime(const std::string& _name, float _playTime);
	void SetPlayScale(const std::string& _name, float _playScale);
	void SetPlayLoop(const std::string& _name, bool _loop);
	void SetPlayReverse(const std::string& _name, bool _reverse);
	// 현재 동작되는 애니메이션 바꿔줌
	void SetCurrentAnimation(std::string& _name); 
	// 위와 같지만 기존 애니메이션을 초기화하고 바꿔줌
	void ChangeAnimation(const std::string& _name);
	// 인자로 넣은 애니메이션과 현재 동작되는 애니메이션의 동일 여부
	bool CheckCurrentAnimation(const std::string& _name); 
	void Update(float _deltaTime);
private:
	CAnimationInfo* FindInfo(const std::string& _name);
public:
	// 엔드함수(프레임 마지막에 호출되는 함수) 추가
	template <typename T>
	void SetEndFunction(const std::string& _name, T* _obj, void(T::* _func)())
	{
		// 키(_name)에 해당하는 애니메이션을 찾는다.
		CAnimationInfo* info = FindInfo(_name);

		// 없다면 리턴
		if (!info)
			return;

		// 존재한다면 해당 애니메이션의 엔드함수를 등록한다.
		info->SetEndFunction<T>(_obj, _func);
	}

	// 노티파이 추가
	template <typename T>
	void AddNotify(const std::string& _name, int _frame, T* _obj, void(T::* _func)())
	{
		// 키(_name)에 해당하는 애니메이션을 찾는다.
		CAnimationInfo* info = FindInfo(_name);

		// 없다면 리턴
		if (!info)
			return;

		// 존재한다면 해당 애니메이션의 _frame번째 프레임에 노티파이를 등록한다.
		info->AddNotify<T>(_frame, _obj, _func);
	}

	/*
		현재 애니메이션(currentAnimation)이 끝날 때 호출할 함수를 추가한다.
		
		하나의 애니메이션에는 여러 모션(걷기, 공격 정지 등)이 들어있다.
		이 모션들이 돌아가면서 현재 애니메이션으로 지정되는데,
		어떤 모션이 지정되든 종료될때마다 호출해줄 함수를 만들 것이다.
	*/
	template <typename T>
	void SetCurrentAnimationEndFunction(T* _obj, void(T::* _func)())
	{
		m_currentAnimationEndFunc = std::bind(_func, _obj);
	}
private:
	CAnimation();
	~CAnimation();

	friend class CGameObject;
};

