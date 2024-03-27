#include "Animation.h"
#include "AnimationInfo.h"
#include "../Resource/Animation/AnimationSequence.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Resource/ResourceManager.h"

void CAnimation::AddAnimation(const std::string& _sequenceName, 
	bool _loop, float _playTime, float _playScale, bool _reverse)
{
	/*
		���� Ű(_sequenceName)�� �ִϸ��̼� �������� 
		�� �ִϸ��̼� map�� �����Ѵٸ� �����Ѵ�.
	*/
	if (FindInfo(_sequenceName))
		return;

	// �� �ִϸ��̼� �������� �����Ѵ�.
	CAnimationSequence* sequence = nullptr;

	// ���� �ִϸ��̼� �������� ���� ���� ������ ���
	if (m_scene)
	{	
		// �����ҽ����� �ִϸ��̼��� ���´�.
		sequence = m_scene->GetSceneResource()->FindAnimation(_sequenceName);
	}
	// ���� ���� ���� ���
	else
	{	
		// ���ҽ��Ŵ����� ���� �ִϸ��̼��� ���´�.
		sequence = CResourceManager::GetInst()->FindAnimation(_sequenceName);
	}

	if (!sequence)
		return;

	// �� �ִϸ��̼� ������ ����� �ִϸ��̼� �������� ���� ������ ä���.
	CAnimationInfo* info = new CAnimationInfo;

	info->m_sequence = sequence;	// �� ������ ���� �ִϸ��̼� �������� ���
	info->m_loop = _loop;
	info->m_playTime = _playTime;
	info->m_playScale = _playScale;
	info->m_reverse = _reverse;
	info->m_frameTime = info->m_playTime / sequence->GetFrameCount();

	// ó�� �߰��Ǵ� �ִϸ��̼��� ��� ���� ��� �ִϸ��̼����� �⺻ �������ش�.
	if (m_mapAnimation.empty())
		m_currentAnimation = info;

	
	// �ִϸ��̼��� map�� �߰��Ѵ�.
	m_mapAnimation.insert(std::make_pair(_sequenceName, info));
}

void CAnimation::SetPlayTime(const std::string& _name, float _playTime)
{
	CAnimationInfo* info = FindInfo(_name);

	if (!info)
		return;

	info->m_playTime = _playTime;
}

void CAnimation::SetPlayScale(const std::string& _name, float _playScale)
{
	CAnimationInfo* info = FindInfo(_name);

	if (!info)
		return;

	info->m_playScale = _playScale;
}

void CAnimation::SetPlayLoop(const std::string& _name, bool _loop)
{
	CAnimationInfo* info = FindInfo(_name);

	if (!info)
		return;

	info->m_loop = _loop;
}

void CAnimation::SetPlayReverse(const std::string& _name, bool _reverse)
{
	CAnimationInfo* info = FindInfo(_name);

	if (!info)
		return;

	info->m_reverse = _reverse;
}

void CAnimation::SetCurrentAnimation(std::string& _name)
{
	// Ű(_name)�� �̿��� map���� �ִϸ��̼� �������� ã�´�.
	CAnimationInfo* info = FindInfo(_name);

	if (!info)
		return;

	// map���� ã�� �ִϸ��̼����� �� �ִϸ��̼� �������� �����Ѵ�.
	m_currentAnimation = info;

	// �ִϸ��̼� �������� �⺻ 0�����ӿ� �����ϰ� �ϰ�, �ð��� 0���� �ǵ�����.
	m_currentAnimation->m_frame = 0;
	m_currentAnimation->m_time = 0.f;


	// �� �ִϸ��̼� �������� ��Ƽ���� ���� Ȯ���ϰ� ��� false���·� �ʱ�ȭ
	size_t	size = m_currentAnimation->m_vecNotify.size();

	for (size_t i = 0; i < size; ++i)
	{
		m_currentAnimation->m_vecNotify[i]->Call = false;
	}
}

/*
	SetCurrentAnimation�� map���� �ϳ��� �ִϸ��̼� �������� ��� 
	�� �ִϸ��̼��� ��ü�ϴ� ���̰�

	ChangeAnimation�� �װͿ� ���� ���� ���������� �ʱ�ȭ ���ֹǷ�, 
	���߿� ��ü�ϴ� ������ ���ϴ�.
*/
void CAnimation::ChangeAnimation(const std::string& _name)
{
	if (_name == "PlayerRightJudgement")
	{
		int a = 0;
	}
	// �� �������� ��ü�� �������� ���ٸ� ����
	if (m_currentAnimation->m_sequence->GetName() == _name)
		return;

	// Ű(_name)�� �̿��� �ִϸ��̼� �������� ã�´�.
	CAnimationInfo* info = FindInfo(_name);

	if (!info)
		return;

	// map���� ã�� �ִϸ��̼����� �� �ִϸ��̼� �������� �����Ѵ�.
	m_currentAnimation->m_frame = 0;
	m_currentAnimation->m_time = 0.f;

	// �� �ִϸ��̼� �������� ��Ƽ���� ���� Ȯ���ϰ� ��� false���·� �ʱ�ȭ
	size_t	size = m_currentAnimation->m_vecNotify.size();

	for (size_t i = 0; i < size; ++i)
	{
		m_currentAnimation->m_vecNotify[i]->Call = false;
	}

	// ��ü�Ѵ�.
	m_currentAnimation = info;

	m_currentAnimation->m_frame = 0;
	m_currentAnimation->m_time = 0.f;

	// �� �ִϸ��̼� �������� ��Ƽ���� ���� Ȯ���ϰ� ��� false���·� �ʱ�ȭ
	size = m_currentAnimation->m_vecNotify.size();

	for (size_t i = 0; i < size; ++i)
	{
		m_currentAnimation->m_vecNotify[i]->Call = false;
	}
}

bool CAnimation::CheckCurrentAnimation(const std::string& _name)
{
	return m_currentAnimation->m_sequence->GetName() == _name;
}

void CAnimation::Update(float _deltaTime)
{
	// �ϳ��� �ִϸ��̼��� �����鼭 ���� �ð��� ������Ų��.
	m_currentAnimation->m_time += _deltaTime * m_currentAnimation->m_playScale;

	bool animationEnd = false;

	// ����� �ð��� 1�����Ӵ� �귯�� �� �ð��� �����ٸ� �������� ������Ų��.
	if (m_currentAnimation->m_time >= m_currentAnimation->m_frameTime)
	{
		// 1�����Ӵ� �귯�� �� �ð��� ���� �ٽ� ����ϰ� ������ش�.
		m_currentAnimation->m_time -= m_currentAnimation->m_frameTime;

		// ����� ���¶��
		if (m_currentAnimation->m_reverse)
		{
			// �ִϸ��̼� �������� �������� 1 ���ҽ�Ų��. (���Ұ� �� ���� ������)
			--m_currentAnimation->m_frame;

			// �ִϸ��̼��� ������ �����ӿ� �����ߴٸ�
			if (m_currentAnimation->m_frame < 0)
				// �ִϸ��̼� ���� ���·� �νĽ�Ų��.
				animationEnd = true;
		}
		// �Ϲ� ��� ���¶��
		else
		{
			// �ִϸ��̼� �������� �������� 1 ������Ų��. (������ �� ���� ������)
			++m_currentAnimation->m_frame;

			// �ִϸ��̼��� ������ �����ӿ� �����ߴٸ�
			if (m_currentAnimation->m_frame == m_currentAnimation->m_sequence->GetFrameCount())
				// �ִϸ��̼� ���� ���·� �νĽ�Ų��.
				animationEnd = true;
		}
	}

	size_t	Size = m_currentAnimation->m_vecNotify.size();

	// �� �������� ��Ƽ���̸� ȣ���ϴ� �κ��̴�. 
	for (size_t i = 0; i < Size; ++i)
	{
		// ���� �������� ��Ƽ���̰� ȣ���� �ȵǾ��� �ش� �����ӿ� �����ߴٸ� ȣ���Ѵ�.
		if (!m_currentAnimation->m_vecNotify[i]->Call &&
			m_currentAnimation->m_vecNotify[i]->Frame == m_currentAnimation->m_frame)
		{
			// ���� �������� ��Ƽ���̸� 'ȣ������' ���·� �ٲ��ش�.
			m_currentAnimation->m_vecNotify[i]->Call = true;
			// ���� �������� ��Ƽ���̸� ȣ���Ѵ�.
			m_currentAnimation->m_vecNotify[i]->Function();
		}
	}

	// �ϳ��� �ִϸ��̼��� ����Ǿ��ٸ�
	if (animationEnd)
	{
		// � ����̵� ����ɶ����� ȣ���ϴ� urrentAnimationEndFunc�� ���� ȣ���Ѵ�.
		if (m_currentAnimationEndFunc)
			m_currentAnimationEndFunc();

		// �ִϸ��̼��� '����'�̰�
		if (m_currentAnimation->m_loop)
		{
			// ����� �̶�� 
			if (m_currentAnimation->m_reverse)
				// ù��° ���������� �ǵ����ش�. 
				m_currentAnimation->m_frame = m_currentAnimation->m_sequence->GetFrameCount() - 1;
			// ������� �ƴ϶��
			else
				// ù��° ������(0 ������)���� �ǵ����ش�.
				m_currentAnimation->m_frame = 0;
		}

		// '����'�� �ƴϰ�
		else
		{
			// ����� �̶��
			if (m_currentAnimation->m_reverse)
				// ������ ������(0 ������)���� �ٽ� �����Ѵ�.
				m_currentAnimation->m_frame = 0;
			// ������� �ƴ϶��
			else
				// ������ ���������� �ٽ� �����Ѵ�.
				m_currentAnimation->m_frame = m_currentAnimation->m_sequence->GetFrameCount() - 1;
		}

		// ���� �Լ��� ȣ���Ѵ�.
		if (m_currentAnimation->m_endFunction)
			m_currentAnimation->m_endFunction();

		// ��Ƽ������ Call ������ ��� false�� �Ͽ�, ���� ��ǿ��� �ٽ� ����� �� �ֵ��� �Ѵ�. 
		for (size_t i = 0; i < Size; ++i)
		{
			m_currentAnimation->m_vecNotify[i]->Call = false;
		}
	}
}

CAnimationInfo* CAnimation::FindInfo(const std::string& _name)
{
	auto	iter = m_mapAnimation.find(_name);

	if (iter == m_mapAnimation.end())
		return nullptr;

	return iter->second;
}

CAnimation::CAnimation()
	: m_owner(nullptr)
	, m_scene(nullptr)
	, m_currentAnimation(nullptr)
{
}

CAnimation::~CAnimation()
{
	auto iter = m_mapAnimation.begin();
	auto iterEnd = m_mapAnimation.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}