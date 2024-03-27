#include "Scene3Back1.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
bool CScene3Back1::Init()
{
	SetPos(0.f, 0.f);
	SetSize(2144.f, 999.f);	// �̹����� ������
	SetPivot(0.f, 0.f);

	// ī�޶��� Ÿ������ '�÷��̾�'�� �����Ѵ�.

	SetTexture("Scene3Back1", TEXT("Maple/Map/Scene3Back1.bmp"));

	return true;
}

void CScene3Back1::Update(float _deltaTime)
{
	CGameObject::Update(_deltaTime);
}

void CScene3Back1::Render(HDC _hDC, float _deltaTime)
{

	CGameObject::Render(_hDC, _deltaTime);
}

CScene3Back1::CScene3Back1()
{
	SetTypeID<CScene3Back1>();
	m_renderLayer = ERenderLayer::Back1;
}

CScene3Back1::CScene3Back1(const CScene3Back1& _obj)
	: CGameObject(_obj)
{
}

CScene3Back1::~CScene3Back1()
{
}
