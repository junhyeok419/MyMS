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
		같은 키(_sequenceName)의 애니메이션 시퀀스가 
		이 애니메이션 map에 존재한다면 리턴한다.
	*/
	if (FindInfo(_sequenceName))
		return;

	// 빈 애니메이션 시퀀스를 생성한다.
	CAnimationSequence* sequence = nullptr;

	// 현재 애니메이션 시퀀스가 속한 씬이 존재할 경우
	if (m_scene)
	{	
		// 씬리소스에서 애니메이션을 얻어온다.
		sequence = m_scene->GetSceneResource()->FindAnimation(_sequenceName);
	}
	// 속한 씬이 없을 경우
	else
	{	
		// 리소스매니저를 통해 애니메이션을 얻어온다.
		sequence = CResourceManager::GetInst()->FindAnimation(_sequenceName);
	}

	if (!sequence)
		return;

	// 빈 애니메이션 인포를 만들어 애니메이션 시퀀스에 대한 정보를 채운다.
	CAnimationInfo* info = new CAnimationInfo;

	info->m_sequence = sequence;	// 맨 위에서 만든 애니메이션 시퀀스를 등록
	info->m_loop = _loop;
	info->m_playTime = _playTime;
	info->m_playScale = _playScale;
	info->m_reverse = _reverse;
	info->m_frameTime = info->m_playTime / sequence->GetFrameCount();

	// 처음 추가되는 애니메이션일 경우 현재 재생 애니메이션으로 기본 지정해준다.
	if (m_mapAnimation.empty())
		m_currentAnimation = info;

	
	// 애니메이션을 map에 추가한다.
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
	// 키(_name)를 이용해 map에서 애니메이션 시퀀스를 찾는다.
	CAnimationInfo* info = FindInfo(_name);

	if (!info)
		return;

	// map에서 찾은 애니메이션으로 현 애니메이션 시퀀스를 지정한다.
	m_currentAnimation = info;

	// 애니메이션 시퀀스가 기본 0프레임에 동작하게 하고, 시간도 0으로 되돌린다.
	m_currentAnimation->m_frame = 0;
	m_currentAnimation->m_time = 0.f;


	// 현 애니메이션 시퀀스의 노티파이 개수 확인하고 모두 false상태로 초기화
	size_t	size = m_currentAnimation->m_vecNotify.size();

	for (size_t i = 0; i < size; ++i)
	{
		m_currentAnimation->m_vecNotify[i]->Call = false;
	}
}

/*
	SetCurrentAnimation은 map에서 하나의 애니메이션 시퀀스를 골라 
	현 애니메이션을 교체하는 것이고

	ChangeAnimation은 그것에 더해 이전 시퀀스까지 초기화 해주므로, 
	도중에 교체하는 느낌이 강하다.
*/
void CAnimation::ChangeAnimation(const std::string& _name)
{
	if (_name == "PlayerRightJudgement")
	{
		int a = 0;
	}
	// 현 시퀀스와 교체할 시퀀스가 같다면 리턴
	if (m_currentAnimation->m_sequence->GetName() == _name)
		return;

	// 키(_name)를 이용해 애니메이션 시퀀스를 찾는다.
	CAnimationInfo* info = FindInfo(_name);

	if (!info)
		return;

	// map에서 찾은 애니메이션으로 현 애니메이션 시퀀스를 지정한다.
	m_currentAnimation->m_frame = 0;
	m_currentAnimation->m_time = 0.f;

	// 전 애니메이션 시퀀스의 노티파이 개수 확인하고 모두 false상태로 초기화
	size_t	size = m_currentAnimation->m_vecNotify.size();

	for (size_t i = 0; i < size; ++i)
	{
		m_currentAnimation->m_vecNotify[i]->Call = false;
	}

	// 교체한다.
	m_currentAnimation = info;

	m_currentAnimation->m_frame = 0;
	m_currentAnimation->m_time = 0.f;

	// 현 애니메이션 시퀀스의 노티파이 개수 확인하고 모두 false상태로 초기화
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
	// 하나의 애니메이션을 돌리면서 지난 시간을 누적시킨다.
	m_currentAnimation->m_time += _deltaTime * m_currentAnimation->m_playScale;

	bool animationEnd = false;

	// 진행된 시간이 1프레임당 흘러야 할 시간을 지났다면 프레임을 증가시킨다.
	if (m_currentAnimation->m_time >= m_currentAnimation->m_frameTime)
	{
		// 1프레임당 흘러야 할 시간을 빼서 다시 계산하게 만들어준다.
		m_currentAnimation->m_time -= m_currentAnimation->m_frameTime;

		// 역재생 상태라면
		if (m_currentAnimation->m_reverse)
		{
			// 애니메이션 시퀀스의 프레임을 1 감소시킨다. (감소가 곧 다음 프레임)
			--m_currentAnimation->m_frame;

			// 애니메이션의 마지막 프레임에 도달했다면
			if (m_currentAnimation->m_frame < 0)
				// 애니메이션 종료 상태로 인식시킨다.
				animationEnd = true;
		}
		// 일반 재생 상태라면
		else
		{
			// 애니메이션 시퀀스의 프레임을 1 증가시킨다. (증가가 곧 다음 프레임)
			++m_currentAnimation->m_frame;

			// 애니메이션의 마지막 프레임에 도달했다면
			if (m_currentAnimation->m_frame == m_currentAnimation->m_sequence->GetFrameCount())
				// 애니메이션 종료 상태로 인식시킨다.
				animationEnd = true;
		}
	}

	size_t	Size = m_currentAnimation->m_vecNotify.size();

	// 각 프레임의 노티파이를 호출하는 부분이다. 
	for (size_t i = 0; i < Size; ++i)
	{
		// 현재 프레임의 노티파이가 호출이 안되었고 해당 프레임에 도달했다면 호출한다.
		if (!m_currentAnimation->m_vecNotify[i]->Call &&
			m_currentAnimation->m_vecNotify[i]->Frame == m_currentAnimation->m_frame)
		{
			// 현재 프레임의 노티파이를 '호출했음' 상태로 바꿔준다.
			m_currentAnimation->m_vecNotify[i]->Call = true;
			// 현재 프레임의 노티파이를 호출한다.
			m_currentAnimation->m_vecNotify[i]->Function();
		}
	}

	// 하나의 애니메이션이 종료되었다면
	if (animationEnd)
	{
		// 어떤 모션이든 종료될때마다 호출하는 urrentAnimationEndFunc를 먼저 호출한다.
		if (m_currentAnimationEndFunc)
			m_currentAnimationEndFunc();

		// 애니메이션이 '루프'이고
		if (m_currentAnimation->m_loop)
		{
			// 역재생 이라면 
			if (m_currentAnimation->m_reverse)
				// 첫번째 프레임으로 되돌려준다. 
				m_currentAnimation->m_frame = m_currentAnimation->m_sequence->GetFrameCount() - 1;
			// 역재생이 아니라면
			else
				// 첫번째 프레임(0 프레임)으로 되돌려준다.
				m_currentAnimation->m_frame = 0;
		}

		// '루프'가 아니고
		else
		{
			// 역재생 이라면
			if (m_currentAnimation->m_reverse)
				// 마지막 프레임(0 프레임)으로 다시 고정한다.
				m_currentAnimation->m_frame = 0;
			// 역재생이 아니라면
			else
				// 마지막 프레임으로 다시 고정한다.
				m_currentAnimation->m_frame = m_currentAnimation->m_sequence->GetFrameCount() - 1;
		}

		// 엔드 함수를 호출한다.
		if (m_currentAnimation->m_endFunction)
			m_currentAnimation->m_endFunction();

		// 노티파이의 Call 변수를 모두 false로 하여, 다음 모션에서 다시 실행될 수 있도록 한다. 
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