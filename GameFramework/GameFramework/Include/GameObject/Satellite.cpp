#include "Satellite.h"

bool CSatellite::Init()
{
    // ���� ��ġ(������ �߻���ü���� ���� ����), ũ��, �Ǻ� ����
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
    // ������ �׷��� �»�� ��ǥ�� ���Ѵ�.
    Vector2 renderLT;
    renderLT = m_pos - m_pivot * m_size;

    // ������ �׸���.
   /* Ellipse(_hDC, (int)renderLT.x, (int)renderLT.y,
        (int)(renderLT.x + m_size.x), (int)(renderLT.y + m_size.y));*/
}

CSatellite::CSatellite()
{
    // ��ü ���� �� Ÿ�� ���̵�(���۷��� Ŭ������ ���)�� �ʱ�ȭ
    SetTypeID<CSatellite>();
}

CSatellite::CSatellite(const CSatellite& _obj)
    : CGameObject(_obj)
{
}

CSatellite::~CSatellite()
{
}
