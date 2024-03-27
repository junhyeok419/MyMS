#include "SceneFinalBack2.h"

bool CSceneFinalBack2::Init()
{
	SetPos(0.f, 0.f);
	SetSize(1200.f, 762.f);	// 이미지의 사이즈
	SetPivot(0.f, 0.f);



	SetTexture("SceneFinalBack2", TEXT("Maple/Map/SceneFinalBack2.bmp"));

	SetColorKey(255, 0, 255);
	return true;
}

void CSceneFinalBack2::Update(float _deltaTime)
{
	CGameObject::Update(_deltaTime);
}

void CSceneFinalBack2::Render(HDC _hDC, float _deltaTime)
{
	CGameObject::Render(_hDC, _deltaTime);
}

CSceneFinalBack2::CSceneFinalBack2()
{
	SetTypeID<CSceneFinalBack2>();
	m_renderLayer = ERenderLayer::Back2;
}

CSceneFinalBack2::CSceneFinalBack2(const CSceneFinalBack2& _obj)
	:CGameObject(_obj)
{
}

CSceneFinalBack2::~CSceneFinalBack2()
{
}


