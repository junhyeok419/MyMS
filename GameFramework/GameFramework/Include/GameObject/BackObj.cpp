#include "BackObj.h"

bool CBackObj::Init()
{
	SetPos(0.f, 0.f);
	SetSize(1049.f, 1035.f);	// 이미지의 사이즈
	SetPivot(0.f, 0.f);

	SetTexture("Map1", TEXT("Maple/Map/map_1.bmp"));
	return true;
}

void CBackObj::Update(float _deltaTime)
{
	CGameObject::Update(_deltaTime);
}

void CBackObj::Render(HDC _hDC, float _deltaTime)
{
	CGameObject::Render(_hDC, _deltaTime);
}

CBackObj::CBackObj()
{
	SetTypeID<CBackObj>();
	m_renderLayer = ERenderLayer::Back1;
}

CBackObj::CBackObj(const CBackObj& _obj)
	:CGameObject(_obj)
{
}

CBackObj::~CBackObj()
{
}
