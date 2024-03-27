#include "Character.h"

bool CCharacter::Init()
{
	return true;
}

void CCharacter::Update(float _deltaTime)
{
	CGameObject::Update(_deltaTime);
}

void CCharacter::PostUpdate(float _deltaTime)
{
	CGameObject::PostUpdate(_deltaTime);
}

void CCharacter::Render(HDC _hDC, float _deltaTime)
{
	CGameObject::Render(_hDC, _deltaTime);
}

float CCharacter::InflictDamage(float _damage, int _dir)
{
	return CGameObject::InflictDamage(_damage);
}

CCharacter::CCharacter()
{
	SetTypeID<CCharacter>();
}

CCharacter::CCharacter(const CCharacter& Obj) :
	CGameObject(Obj)
{
}

CCharacter::~CCharacter()
{
}
