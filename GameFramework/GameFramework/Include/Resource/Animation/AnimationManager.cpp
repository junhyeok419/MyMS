#include "AnimationManager.h"
#include "AnimationSequence.h"

bool CAnimationManager::Init()
{
    return true;
}

bool CAnimationManager::CreateAnimationSequence(const std::string& _name, CTexture* _texture)
{
    // 먼저 키(_name)에 해당하는 애니메이션 시퀀스를 찾는다.
    CAnimationSequence* sequence = FindAnimation(_name);
    
    // 있다면 만들 필요가 없으므로 리턴한다.
    if (sequence)
        return true;

    // 애니메이션 시퀀스를 생성한다.
    sequence = new CAnimationSequence;

    // 애니메이션 시퀀스의 레퍼런스 클래스의 name을 등록한다.
    sequence->SetName(_name);

    // 애니메이션 시퀀스에 텍스쳐를 등록한다.
    sequence->m_texture = _texture;

    // 애니메이션 시퀀스를 map에 추가한다.
    m_mapSequence.insert(std::make_pair(_name, sequence));

    return true;
}

bool CAnimationManager::AddAnimationFrame(const std::string& _name, 
    const Vector2& _start, const Vector2& _end)
{
    CAnimationSequence* sequence = FindAnimation(_name);

    if (!sequence)
        return false;

    sequence->AddFrame(_start, _end);

    return true;
}

bool CAnimationManager::AddAnimationFrame(const std::string& _name, 
    float _posX, float _posY, float _sizeX, float _sizeY)
{
    CAnimationSequence* sequence = FindAnimation(_name);

    if (!sequence)
        return false;

    sequence->AddFrame(_posX, _posY, _sizeX, _sizeY);

    return true;
}

bool CAnimationManager::AddAnimationFramePivot(const std::string& _name, const Vector2& _pivot)
{
    CAnimationSequence* sequence = FindAnimation(_name);

    if (!sequence)
        return false;

    sequence->AddFramePivot(_pivot);

    return true;
}

bool CAnimationManager::AddAnimationFramePivot(const std::string& _name, float _pivotX, float _pivotY)
{
    CAnimationSequence* sequence = FindAnimation(_name);

    if (!sequence)
        return false;

    sequence->AddFramePivot(_pivotX, _pivotY);

    return true;
}

CAnimationSequence* CAnimationManager::FindAnimation(const std::string& _name)
{
    // 키(_name)에 해당하는 애니메이션 시퀀스를 맵에서 찾는다.
    auto iter = m_mapSequence.find(_name);

    // 없다면 리턴한다.
    if (iter == m_mapSequence.end())
        return nullptr;

    // 있다면 값을 반환한다.
    return iter->second;
}

void CAnimationManager::ReleaseAnimation(const std::string& _name)
{
    auto iter = m_mapSequence.find(_name);

    if (iter == m_mapSequence.end())
        return;

    // 해당 map만 참조하고 있을 경우에만 지운다. 텍스쳐에도 비슷한 거 있었음.
    if (iter->second->GetRefCount() == 1)
        m_mapSequence.erase(iter);
}

CAnimationManager::CAnimationManager()
{
}


CAnimationManager::~CAnimationManager()
{
}
