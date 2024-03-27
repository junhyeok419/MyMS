#include "SceneManager.h"
#include "MainScene.h"
#include "StartScene.h"
#include "../Input.h"
DEFINITION_SINGLE(CSceneManager)

bool CSceneManager::Init()
{
    // 씬 생성. 가장 먼저 시작
    CreateScene<CStartScene>();

    // 씬 생성
    // CreateScene<CMainScene>();

    return true;
}

bool CSceneManager::Update(float _deltaTime)
{
    m_scene->Update(_deltaTime);

    /*
        ChangeScene 에서는 nextScene이 있을 때에만 씬을 전환하므로
        true가 반환된다면 씬 전환을 의미한다.

         그럴 경우, 게임 매니저에서 return하여 로직을 다시 실행한다.
    */
    return ChangeScene();
}

bool CSceneManager::PostUpdate(float _deltaTime)
{
    m_scene->PostUpdate(_deltaTime);

    /*
        ChangeScene 에서는 nextScene이 있을 때에만 씬을 전환하므로
        true가 반환된다면 씬 전환을 의미한다.

         그럴 경우, 게임 매니저에서 return하여 로직을 다시 실행한다.
    */
    return ChangeScene();
}

void CSceneManager::Render(HDC _hDC, float _deltaTime)
{
    m_scene->Render(_hDC, _deltaTime);
}

CScene* CSceneManager::GetScene() const
{
    return m_scene;
}


bool CSceneManager::ChangeScene()
{
    // 다음 씬 정보가 있다면
    if (m_nextScene)
    {
        // 기존 장면을 제거한다.
        SAFE_DELETE(m_scene);

        CInput::GetInst()->ClearCallback(m_scene);

        // 씬을 바꿔준다.
        m_scene = m_nextScene;

        // 다음 씬 정보를 '없음'으로 변경
        m_nextScene = nullptr;

        return true;
    }

    return false;
}

CSceneManager::CSceneManager()
    : m_scene(nullptr)
    , m_nextScene(nullptr)
{}

CSceneManager::~CSceneManager()
{
    SAFE_DELETE(m_nextScene);
    SAFE_DELETE(m_scene);
}