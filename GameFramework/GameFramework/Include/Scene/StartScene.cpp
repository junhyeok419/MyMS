#include "StartScene.h"
#include "../GameObject/Player.h"
#include "../GameObject/Monster.h"
#include "../GameObject/BackObj.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../Input.h"
#include "../UI/StartWindow.h"

bool CStartScene::Init()
{
	// ��ŸƮ ���� ���� ������ ũ�Ⱑ ���� �ʿ� �����Ƿ� ���� ��´�.
	GetCamera()->SetResolution(800.f, 600.f);
	GetCamera()->SetWorldResolution(800.f, 600.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	// '��ŸƮ ���� ������'�� �����Ѵ�.
	CreateWidgetWindow<CStartWindow>("StartWindow");

	return true;
}

CStartScene::CStartScene()
{
	
}

CStartScene::~CStartScene()
{
}
