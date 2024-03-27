#include "Scene1Back1.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
bool CScene1Back1::Init()
{
	SetPos(0.f, 0.f);
	SetSize(1945.f, 1035.f);	// �̹����� ������
	SetPivot(0.f, 0.f);

	// ī�޶��� Ÿ������ '�÷��̾�'�� �����Ѵ�.

	SetTexture("Scene1Back1", TEXT("Maple/Map/Scene1Back1.bmp"));

	return true;
}

void CScene1Back1::Update(float _deltaTime)
{
	CGameObject::Update(_deltaTime);
}

void CScene1Back1::Render(HDC _hDC, float _deltaTime)
{

	CGameObject::Render(_hDC, _deltaTime);
}

CScene1Back1::CScene1Back1()
{
	SetTypeID<CScene1Back1>();
	m_renderLayer = ERenderLayer::Back1;
}

CScene1Back1::CScene1Back1(const CScene1Back1& _obj)
	: CGameObject(_obj)
{
}

CScene1Back1::~CScene1Back1()
{
}
