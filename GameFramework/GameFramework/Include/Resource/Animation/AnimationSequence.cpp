#include "AnimationSequence.h"

Vector2 CAnimationSequence::GetFramePivot(int _index) const
{
    return m_vecFramePivot[_index];
}

bool CAnimationSequence::IsFramePivot() const
{
    return !m_vecFramePivot.empty();
}

CTexture* CAnimationSequence::GetTexture() const
{
    return m_texture;
}

ETextureType CAnimationSequence::GetTextureType() const
{
    return m_texture->GetTextureType();
}

const AnimationFrameData& CAnimationSequence::GetFrame(int _index) const
{
    return m_vecFrame[_index];
}

int CAnimationSequence::GetFrameCount() const
{
    return (int)m_vecFrame.size();
}

void CAnimationSequence::AddFrame(const Vector2& _start, const Vector2& _end)
{
    // 빈 프레임 정보를 만든다.
    AnimationFrameData data = {};

    // 시작점과 끝점을 등록한다.
    data.Start = _start;
    data.End = _end;

    // 벡터에 추가한다.
    m_vecFrame.push_back(data);
}

void CAnimationSequence::AddFrame(float _posX, float _posY, float _sizeX, float _sizeY)
{
    // 빈 프레임 정보를 만든다.
    AnimationFrameData data = {};

    // 시작점과 끝점을 등록한다.
    // 우하단 좌표를 구하기 위해 현위치 + 사이즈가 필요하다.
    data.Start = Vector2(_posX, _posY);
    data.End = Vector2(_posX + _sizeX, _posY + _sizeY);

    // 벡터에 추가한다.
    m_vecFrame.push_back(data);
}

void CAnimationSequence::AddFramePivot(const Vector2& _pivot)
{
    m_vecFramePivot.push_back(_pivot);
}

void CAnimationSequence::AddFramePivot(float _pivotX, float _pivotY)
{
    Vector2 data = {};
    data.x = _pivotX;
    data.y = _pivotY;

    m_vecFramePivot.push_back(data);
}

CAnimationSequence::CAnimationSequence()
{
}

CAnimationSequence::~CAnimationSequence()
{
}
