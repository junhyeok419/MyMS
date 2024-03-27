#include "GameManager.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    srand(time(nullptr));

    // 전체 게임을 초기화한다. 실패하면 종료시킨다.
    if (!CGameManager::GetInst()->Init(hInstance))
    {
        CGameManager::DestroyInst();
        return 0;
    }

    int returnValue = CGameManager::GetInst()->Run();

    // 게임이 종료될 때 모든 메모리를 정리해준다.
    CGameManager::DestroyInst();

    // 게임이 어떻게 종료되었는지 전달해주기 위해 반환하는 값이다.
    return returnValue;
}