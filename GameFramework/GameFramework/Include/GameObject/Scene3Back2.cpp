#include "Scene3Back2.h"

bool CScene3Back2::Init()
{
	SetPos(0.f, 0.f);
	SetSize(2144.f, 999.f);	// 이미지의 사이즈
	SetPivot(0.f, 0.f);



	SetTexture("Scene3Back2", TEXT("Maple/Map/Scene3Back2.bmp"));

	SetColorKey(255, 0, 255);
	return true;
}

void CScene3Back2::Update(float _deltaTime)
{
	CGameObject::Update(_deltaTime);
}

void CScene3Back2::Render(HDC _hDC, float _deltaTime)
{
	CGameObject::Render(_hDC, _deltaTime);
}

CScene3Back2::CScene3Back2()
{
	SetTypeID<CScene3Back2>();
	m_renderLayer = ERenderLayer::Back2;
}

CScene3Back2::CScene3Back2(const CScene3Back2& _obj)
	:CGameObject(_obj)
{
}

CScene3Back2::~CScene3Back2()
{
}


