#include "SceneManager.h"
#include "MainScene.h"
#include "StartScene.h"
#include "../Input.h"
DEFINITION_SINGLE(CSceneManager)

bool CSceneManager::Init()
{
    // �� ����. ���� ���� ����
    CreateScene<CStartScene>();

    // �� ����
    // CreateScene<CMainScene>();

    return true;
}

bool CSceneManager::Update(float _deltaTime)
{
    m_scene->Update(_deltaTime);

    /*
        ChangeScene ������ nextScene�� ���� ������ ���� ��ȯ�ϹǷ�
        true�� ��ȯ�ȴٸ� �� ��ȯ�� �ǹ��Ѵ�.

         �׷� ���, ���� �Ŵ������� return�Ͽ� ������ �ٽ� �����Ѵ�.
    */
    return ChangeScene();
}

bool CSceneManager::PostUpdate(float _deltaTime)
{
    m_scene->PostUpdate(_deltaTime);

    /*
        ChangeScene ������ nextScene�� ���� ������ ���� ��ȯ�ϹǷ�
        true�� ��ȯ�ȴٸ� �� ��ȯ�� �ǹ��Ѵ�.

         �׷� ���, ���� �Ŵ������� return�Ͽ� ������ �ٽ� �����Ѵ�.
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
    // ���� �� ������ �ִٸ�
    if (m_nextScene)
    {
        // ���� ����� �����Ѵ�.
        SAFE_DELETE(m_scene);

        CInput::GetInst()->ClearCallback(m_scene);

        // ���� �ٲ��ش�.
        m_scene = m_nextScene;

        // ���� �� ������ '����'���� ����
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