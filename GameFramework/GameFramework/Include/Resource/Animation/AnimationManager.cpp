#include "AnimationManager.h"
#include "AnimationSequence.h"

bool CAnimationManager::Init()
{
    return true;
}

bool CAnimationManager::CreateAnimationSequence(const std::string& _name, CTexture* _texture)
{
    // ���� Ű(_name)�� �ش��ϴ� �ִϸ��̼� �������� ã�´�.
    CAnimationSequence* sequence = FindAnimation(_name);
    
    // �ִٸ� ���� �ʿ䰡 �����Ƿ� �����Ѵ�.
    if (sequence)
        return true;

    // �ִϸ��̼� �������� �����Ѵ�.
    sequence = new CAnimationSequence;

    // �ִϸ��̼� �������� ���۷��� Ŭ������ name�� ����Ѵ�.
    sequence->SetName(_name);

    // �ִϸ��̼� �������� �ؽ��ĸ� ����Ѵ�.
    sequence->m_texture = _texture;

    // �ִϸ��̼� �������� map�� �߰��Ѵ�.
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
    // Ű(_name)�� �ش��ϴ� �ִϸ��̼� �������� �ʿ��� ã�´�.
    auto iter = m_mapSequence.find(_name);

    // ���ٸ� �����Ѵ�.
    if (iter == m_mapSequence.end())
        return nullptr;

    // �ִٸ� ���� ��ȯ�Ѵ�.
    return iter->second;
}

void CAnimationManager::ReleaseAnimation(const std::string& _name)
{
    auto iter = m_mapSequence.find(_name);

    if (iter == m_mapSequence.end())
        return;

    // �ش� map�� �����ϰ� ���� ��쿡�� �����. �ؽ��Ŀ��� ����� �� �־���.
    if (iter->second->GetRefCount() == 1)
        m_mapSequence.erase(iter);
}

CAnimationManager::CAnimationManager()
{
}


CAnimationManager::~CAnimationManager()
{
}
