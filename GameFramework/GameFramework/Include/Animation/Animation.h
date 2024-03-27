#pragma once
#include "AnimationInfo.h"

/*
	�ִϸ��̼� : '�ִϸ��̼� ����'�� ���� �� ���� �������μ�,
	�ʿ信 ���� ����� ��ȯ ���� �� �� �ִ�,
	���������� �ִϸ��̼��� �����ִ� Ŭ�����̴�.

	���� ������Ʈ�� �� �ִϸ��̼� ��ü�� ���� �ְ� �Ͽ�
	�ִϸ��̼��� ����ϵ��� �� ���̴�.
*/
class CAnimation
{
private:
	class CGameObject* m_owner;	// �� �ִϸ��̼��� ���� ������Ʈ
	class CScene* m_scene;		// �� �ִϸ��̼��� ���� ��
	/*
		�ϳ��� �ִϸ��̼� ������ �� �ϳ��� ����� �ǹǷ�,
		map���� �ִϸ��̼� ������ ���� �Ѵ�.
		���� ����� ����� ����س��� ���Ҷ����� ��ü�ؼ� ����ϱ� �����̴�.
		����� �ǽð����� �߰��ϴ� ���� �ƴϴ� map���� �����Ѵ�.
	*/
	std::unordered_map<std::string, class CAnimationInfo*> m_mapAnimation;
	class CAnimationInfo* m_currentAnimation;	// ���� �������� �ִϸ��̼� �ּ�. �� map�� ����� �ϳ�
	std::function<void()>	m_currentAnimationEndFunc;
public:
	// �ִϸ��̼� �������� �߰��Ѵ�.
	void AddAnimation(const std::string& _sequenceName, bool _loop = true,
		float _playTime = 1.f, float _playScale = 1.f, bool _reverse = false);
	void SetPlayTime(const std::string& _name, float _playTime);
	void SetPlayScale(const std::string& _name, float _playScale);
	void SetPlayLoop(const std::string& _name, bool _loop);
	void SetPlayReverse(const std::string& _name, bool _reverse);
	// ���� ���۵Ǵ� �ִϸ��̼� �ٲ���
	void SetCurrentAnimation(std::string& _name); 
	// ���� ������ ���� �ִϸ��̼��� �ʱ�ȭ�ϰ� �ٲ���
	void ChangeAnimation(const std::string& _name);
	// ���ڷ� ���� �ִϸ��̼ǰ� ���� ���۵Ǵ� �ִϸ��̼��� ���� ����
	bool CheckCurrentAnimation(const std::string& _name); 
	void Update(float _deltaTime);
private:
	CAnimationInfo* FindInfo(const std::string& _name);
public:
	// �����Լ�(������ �������� ȣ��Ǵ� �Լ�) �߰�
	template <typename T>
	void SetEndFunction(const std::string& _name, T* _obj, void(T::* _func)())
	{
		// Ű(_name)�� �ش��ϴ� �ִϸ��̼��� ã�´�.
		CAnimationInfo* info = FindInfo(_name);

		// ���ٸ� ����
		if (!info)
			return;

		// �����Ѵٸ� �ش� �ִϸ��̼��� �����Լ��� ����Ѵ�.
		info->SetEndFunction<T>(_obj, _func);
	}

	// ��Ƽ���� �߰�
	template <typename T>
	void AddNotify(const std::string& _name, int _frame, T* _obj, void(T::* _func)())
	{
		// Ű(_name)�� �ش��ϴ� �ִϸ��̼��� ã�´�.
		CAnimationInfo* info = FindInfo(_name);

		// ���ٸ� ����
		if (!info)
			return;

		// �����Ѵٸ� �ش� �ִϸ��̼��� _frame��° �����ӿ� ��Ƽ���̸� ����Ѵ�.
		info->AddNotify<T>(_frame, _obj, _func);
	}

	/*
		���� �ִϸ��̼�(currentAnimation)�� ���� �� ȣ���� �Լ��� �߰��Ѵ�.
		
		�ϳ��� �ִϸ��̼ǿ��� ���� ���(�ȱ�, ���� ���� ��)�� ����ִ�.
		�� ��ǵ��� ���ư��鼭 ���� �ִϸ��̼����� �����Ǵµ�,
		� ����� �����ǵ� ����ɶ����� ȣ������ �Լ��� ���� ���̴�.
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

