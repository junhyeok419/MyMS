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
	// 스타트 씬은 월드 영역의 크기가 따로 필요 없으므로 같게 잡는다.
	GetCamera()->SetResolution(800.f, 600.f);
	GetCamera()->SetWorldResolution(800.f, 600.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	// '스타트 위젯 윈도우'를 생성한다.
	CreateWidgetWindow<CStartWindow>("StartWindow");

	return true;
}

CStartScene::CStartScene()
{
	
}

CStartScene::~CStartScene()
{
}
