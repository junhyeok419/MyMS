#include "GameManager.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    srand(time(nullptr));

    // ��ü ������ �ʱ�ȭ�Ѵ�. �����ϸ� �����Ų��.
    if (!CGameManager::GetInst()->Init(hInstance))
    {
        CGameManager::DestroyInst();
        return 0;
    }

    int returnValue = CGameManager::GetInst()->Run();

    // ������ ����� �� ��� �޸𸮸� �������ش�.
    CGameManager::DestroyInst();

    // ������ ��� ����Ǿ����� �������ֱ� ���� ��ȯ�ϴ� ���̴�.
    return returnValue;
}