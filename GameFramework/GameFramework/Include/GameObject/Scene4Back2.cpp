#include "Scene4Back2.h"

bool CScene4Back2::Init()
{
	SetPos(0.f, 0.f);
	SetSize(1532.f, 940.f);	// 이미지의 사이즈
	SetPivot(0.f, 0.f);

	

	SetTexture("Scene4Back2", TEXT("Maple/Map/Scene4Back2.bmp"));

	SetColorKey(255, 0, 255);
	return true;
}

void CScene4Back2::Update(float _deltaTime)
{
	CGameObject::Update(_deltaTime);
}

void CScene4Back2::Render(HDC _hDC, float _deltaTime)
{
	CGameObject::Render(_hDC, _deltaTime);
}

CScene4Back2::CScene4Back2()
{
	SetTypeID<CScene4Back2>();
	m_renderLayer = ERenderLayer::Back2;
}

CScene4Back2::CScene4Back2(const CScene4Back2& _obj)
	:CGameObject(_obj)
{
}

CScene4Back2::~CScene4Back2()
{
}


