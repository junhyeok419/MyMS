#include "Scene2Back2.h"

bool CScene2Back2::Init()
{
	SetPos(0.f, 0.f);
	SetSize(2052.f, 1044.f);	// 이미지의 사이즈
	SetPivot(0.f, 0.f);



	SetTexture("Scene2Back2", TEXT("Maple/Map/Scene2Back2.bmp"));

	SetColorKey(255, 0, 255);
	return true;
}

void CScene2Back2::Update(float _deltaTime)
{
	CGameObject::Update(_deltaTime);
}

void CScene2Back2::Render(HDC _hDC, float _deltaTime)
{
	CGameObject::Render(_hDC, _deltaTime);
}

CScene2Back2::CScene2Back2()
{
	SetTypeID<CScene2Back2>();
	m_renderLayer = ERenderLayer::Back2;
}

CScene2Back2::CScene2Back2(const CScene2Back2& _obj)
	:CGameObject(_obj)
{
}

CScene2Back2::~CScene2Back2()
{
}


