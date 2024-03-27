#include "Scene4Back1.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
bool CScene4Back1::Init()
{
	SetPos(0.f, 0.f);
	SetSize(1532.f, 940.f);	// 이미지의 사이즈
	SetPivot(0.f, 0.f);

	// 카메라의 타겟으로 '플레이어'를 지정한다.

	SetTexture("Scene4Back1", TEXT("Maple/Map/Scene4Back1.bmp"));
	
	return true;
}

void CScene4Back1::Update(float _deltaTime)
{
	CGameObject::Update(_deltaTime);
}

void CScene4Back1::Render(HDC _hDC, float _deltaTime)
{
	
	CGameObject::Render(_hDC, _deltaTime);
}

CScene4Back1::CScene4Back1()
{
	SetTypeID<CScene4Back1>();
	m_renderLayer = ERenderLayer::Back1;
}

CScene4Back1::CScene4Back1(const CScene4Back1& _obj)
	: CGameObject(_obj)
{
}

CScene4Back1::~CScene4Back1()
{
}
