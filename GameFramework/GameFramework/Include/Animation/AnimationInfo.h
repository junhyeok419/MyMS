#pragma once

#include "../GameInfo.h"

/*
	��Ƽ���� : ���� ���, Ȱ��� ���� �ִϸ��̼��� �����Ѵٰ� �ؼ�
	�ٷ� ������ ������ ���� �ƴ϶�, ������ ���� �����ӿ� ������ ������ ��
	�����̰� �ִ�. 
	���� �ִϸ��̼��� ���ϴ� Ư�� �����ӿ� ȣ��� �Լ��� ����Ͽ� 
	����� �� �ֵ��� ���� ���̰� �̰��� ��Ƽ���̴�.

	�ȱ� ����� ���� ���� �ݴ� �����Ӹ��� ������ ���� ����Ʈ�� ������
	�Լ��� ��Ͻ�Ű�� ��, �� �� �׷����� ������ ���� �� �ִ�.
*/
struct AnimationNotify
{
	int Frame;	// �Լ��� �� ��° �����ӿ� ����� ������
	/*
		Call ���� ���� ���� : Ư�� �����ӿ� ��Ƽ���� �Լ��� ����
		�Ǿ��� ���, ���� �ִϸ��̼� ������ ����(�ش� ����� ����
		������ ����)���� ��Ƽ���� �Լ��� �������� �ʱ� ����
		Call�� true�� ����� �����Ѵ�.

		���� �̷��� ������ ������, 3�����ӿ��� �����ϴ� �Լ���
		�ִٰ� �� ��, �������� �������� �ð����� �Լ��� �����ϴ�
		�ð��� �����ٸ� ����̰� ȣ�� �� ������ �ִ�.
	*/
	bool Call;	// ���� ��� �����߿� �Լ��� ȣ�� �Ǿ�����
	std::function<void()> Function;	 // ȣ���� �Լ�

	AnimationNotify()
		: Frame(0)
		, Call(false)
	{}
};

/*
	�ִϸ��̼� ���� : '�ִϸ��̼� ������'�� '1��' ������ �����鼭,
	�ش� ����� �� ���ʿ� ���ļ� �� �� �������, ����� �ݺ� �������
	���� �����صδ� Ŭ�����̴�. (��� �ϳ��� ���� ����)
*/
class CAnimationInfo
{
private:
	CSharedPtr<class CAnimationSequence> m_sequence; // ��� �ִϸ��̼� �������� 1�� ���´�.
	int m_frame;	// �ִϸ��̼��� ���۵Ǵ� ������ 
	/*
		time�� '�ִϸ��̼��� �������� ���������ֱ� ���� �ð���'�̴�.
		���� ���, 3������ ¥�� �ִϸ��̼��� 1�� �����ϴµ��� 1�ʰ� �ɷȴٸ�,
		1������ �� 0.333...�ʰ� �ɷȴٴ� ���ε�,
		�� 0.333...�ʰ� ���������� �Ǵ��ϴ� ���̴�. 
	*/
	float m_time;		
	float m_frameTime;	// �� �������� �����ϱ� ���� �ð�. ���⿡ ������ ���� 0.333...�ʰ� ���´�.
	float m_playTime;	// ����� 1�� �����ϱ� ���� �ð�. �̰��� 1�ʶ�� ����� 1�� �����ϴµ��� 1�ʰ� �ɸ���.
	float m_playScale;  // ����ӵ� ����
	bool  m_loop;		// �ݺ���� ����
	bool  m_reverse;	// ����� ����
	std::function<void()> m_endFunction; // �ִϸ��̼��� ���� ������ ȣ���� �Լ� ���
	std::vector<AnimationNotify*> m_vecNotify; // �� �ִϸ��̼��� ��Ƽ����. �翬�� ������ ����� �� �ֵ��� ���ͷ�
public:
	template <typename T>
	void SetEndFunction(T* _obj, void(T::* _func)())
	{
		/*
			std::bind : �Լ� ���
			����Լ��� ����� ��, �Լ��ּҿ� ��ü�ּҸ�
			��� �����ؾ� �Ѵ�.
		*/
		m_endFunction = std::bind(_func, _obj);
	}
	template <typename T>
	void AddNotify(int _frame, T* _obj, void(T::* _func)())
	{
		// ��Ƽ���� ����
		AnimationNotify* notify = new AnimationNotify;

		// �����Ӱ� �Լ� ���
		notify->Frame = _frame;
		notify->Function = std::bind(_func, _obj);

		// ���Ϳ� �߰�
		m_vecNotify.push_back(notify);
	}
private:
	CAnimationInfo();
	~CAnimationInfo();

	friend class CAnimation;
	friend class CGameObject;
};

