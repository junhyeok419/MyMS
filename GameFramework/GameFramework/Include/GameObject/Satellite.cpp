#include "Satellite.h"

bool CSatellite::Init()
{
    // 위성 위치(어차피 발사주체에서 조정 받음), 크기, 피봇 설정
    SetPos(900.f, 100.f);
    SetSize(30.f, 30.f);
    SetPivot(0.5f, 0.5f);
    return true;
}

void CSatellite::Update(float _deltaTime)
{
}

void CSatellite::Render(HDC _hDC, float _deltaTime)
{
    // 위성이 그려질 좌상단 좌표를 구한다.
    Vector2 renderLT;
    renderLT = m_pos - m_pivot * m_size;

    // 위성을 그린다.
   /* Ellipse(_hDC, (int)renderLT.x, (int)renderLT.y,
        (int)(renderLT.x + m_size.x), (int)(renderLT.y + m_size.y));*/
}

CSatellite::CSatellite()
{
    // 객체 생성 시 타입 아이디(레퍼런스 클래스의 멤버)를 초기화
    SetTypeID<CSatellite>();
}

CSatellite::CSatellite(const CSatellite& _obj)
    : CGameObject(_obj)
{
}

CSatellite::~CSatellite()
{
}
