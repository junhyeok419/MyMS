#include "SceneFinalBack1.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
bool CSceneFinalBack1::Init()
{
	SetPos(0.f, 0.f);
	SetSize(1200.f, 762.f);	// 이미지의 사이즈
	SetPivot(0.f, 0.f);

	// 카메라의 타겟으로 '플레이어'를 지정한다.

	SetTexture("SceneFinalBack1", TEXT("Maple/Map/SceneFinalBack1.bmp"));

	return true;
}

void CSceneFinalBack1::Update(float _deltaTime)
{
	CGameObject::Update(_deltaTime);
}

void CSceneFinalBack1::Render(HDC _hDC, float _deltaTime)
{

	CGameObject::Render(_hDC, _deltaTime);
}

CSceneFinalBack1::CSceneFinalBack1()
{
	SetTypeID<CSceneFinalBack1>();
	m_renderLayer = ERenderLayer::Back1;
}

CSceneFinalBack1::CSceneFinalBack1(const CSceneFinalBack1& _obj)
	: CGameObject(_obj)
{
}

CSceneFinalBack1::~CSceneFinalBack1()
{
}
