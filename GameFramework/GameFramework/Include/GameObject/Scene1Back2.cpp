#include "Scene1Back2.h"

bool CScene1Back2::Init()
{
	SetPos(0.f, 0.f);
	SetSize(1049.f, 1035.f);	// 이미지의 사이즈
	SetPivot(0.f, 0.f);



	SetTexture("Scene1Back2", TEXT("Maple/Map/Scene1Back2.bmp"));

	SetColorKey(255, 0, 255);
	return true;
}

void CScene1Back2::Update(float _deltaTime)
{
	CGameObject::Update(_deltaTime);
}

void CScene1Back2::Render(HDC _hDC, float _deltaTime)
{
	CGameObject::Render(_hDC, _deltaTime);
}

CScene1Back2::CScene1Back2()
{
	SetTypeID<CScene1Back2>();
	m_renderLayer = ERenderLayer::Back2;
}

CScene1Back2::CScene1Back2(const CScene1Back2& _obj)
	:CGameObject(_obj)
{
}

CScene1Back2::~CScene1Back2()
{
}


