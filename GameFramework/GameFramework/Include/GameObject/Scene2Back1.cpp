#include "Scene2Back1.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
bool CScene2Back1::Init()
{
	SetPos(0.f, 0.f);
	SetSize(2052.f, 1044.f);	// �̹����� ������
	SetPivot(0.f, 0.f);

	// ī�޶��� Ÿ������ '�÷��̾�'�� �����Ѵ�.

	SetTexture("Scene2Back1", TEXT("Maple/Map/Scene2Back1.bmp"));

	return true;
}

void CScene2Back1::Update(float _deltaTime)
{
	CGameObject::Update(_deltaTime);
}

void CScene2Back1::Render(HDC _hDC, float _deltaTime)
{

	CGameObject::Render(_hDC, _deltaTime);
}

CScene2Back1::CScene2Back1()
{
	SetTypeID<CScene2Back1>();
	m_renderLayer = ERenderLayer::Back1;
}

CScene2Back1::CScene2Back1(const CScene2Back1& _obj)
	: CGameObject(_obj)
{
}

CScene2Back1::~CScene2Back1()
{
}
