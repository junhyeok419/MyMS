#include "GameManager.h"
#include "resource.h"   // ������ ���� ����ϱ� ����
#include "Timer.h"
#include "GameObject/Player.h"
#include "Scene/SceneManager.h"
#include "Input.h"
#include "Resource/ResourceManager.h"
#include "PathManager.h"
#include "Collision/CollisionManager.h"

DEFINITION_SINGLE(CGameManager)
bool CGameManager::m_loop = true;

CGameManager::CGameManager()
{
    /*
        _CrtSetDbgFlag : ����� ���� ���� �� �޸� ���� �߻��� ���
        '��ȣ'�� �����ش�.

        _CrtSetBreakAlloc : ������ ���� '��ȣ'�� ���ڷ� �����ϰ� 
        �����ϸ� �޸� ���� �߻��� �ڵ带 �˷��ش�.
    */
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(921);
}

CGameManager::~CGameManager()
{
    CPathManager::DestroyInst();

    CSceneManager::DestroyInst();

    CCollisionManager::DestroyInst();

    CInput::DestroyInst();

    CResourceManager::DestroyInst();

    SAFE_DELETE(m_timer);

    SelectObject(m_hBackDC, m_hBackPrevBmp);
    DeleteObject(m_hBackBmp);
    DeleteDC(m_hBackDC);

    // �귯���� �����Ѵ�.
    for (int i = 0; i < (int)EBrushType::Max; ++i)
    {
        DeleteObject(m_brush[i]);
    }

    // ���� �����Ѵ�.
    for (int i = 0; i < (int)EBrushType::Max; ++i)
    {
        DeleteObject(m_pen[i]);
    }

    // ���α׷� ���� ��, ù ������ �����쿡 �ش��ϴ� DC�� �����Ѵ�.
    ReleaseDC(m_hWnd, m_hDC);   
}

bool CGameManager::Init(HINSTANCE _hInst)
{
	m_hInst = _hInst;

    m_rs.Width = 800;
    m_rs.Height = 600;

	// ������Ŭ���� ����ü�� ������ְ� ����Ѵ�. (->MyRegisterClass)
	Register();

    // ������ â�� �����ϰ� �����ش�. (->InitInstance)
    Create();

    // �н� �Ŵ����� �����ϰ� �ʱ�ȭ�Ѵ�
    if (!CPathManager::GetInst()->Init())
    {
        return false;
    }

    // ���ҽ� �Ŵ����� �����ϰ� �ʱ�ȭ�Ѵ�.
    if (!CResourceManager::GetInst()->Init())
    {
        return false;
    }

    // �浹 �Ŵ����� �����ϰ� �ʱ�ȭ�Ѵ�.
    if (!CCollisionManager::GetInst()->Init())
        return false;

    // �Է� �Ŵ����� �����ϰ� �ʱ�ȭ�Ѵ�.
    if (!CInput::GetInst()->Init(m_hWnd))
    {
        return false;
    }

    // �� �Ŵ����� �����ϰ� �ʱ�ȭ�Ѵ�.
    if (!CSceneManager::GetInst()->Init())
    {
        return false;
    }

    // ���ػ� Ÿ�̸Ӹ� �����ϰ� �ʱ�ȭ�Ѵ�.
    m_timer = new CTimer;
    m_timer->Init();

    /* 
        GetDC : ������ �����쿡 �׸��� ���� DC�� ���´�.
        DC�� ������ ���α׷����� ����ϱ� ���� �� �ʿ��� �ڵ��̴�. (�׸��� ����)
        �� �Լ��� DC�� ������ ���߿� ReleaseDC�� �̿��� �Ҹ���Ѿ� �Ѵ�.
    */ 
    m_hDC = GetDC(m_hWnd);

    m_frameLimitTime = 1 / 60.f;

    /*
        <���� ���۸��� �̿��� ���� �ذ�>

        ���� �������� ������
        1. ������Ʈ 1���� �׸������� ��� ������ �ǹǷ�, ��ü�� �����δ�.
        2. ��ǥ���� ������ �����Ƿ� �ܻ��� ���´�.
        -> ���� ���۸��� �̿��Ͽ� �ذ��Ѵ�.

        ���� ���۸� ����
        1. ��ǥ�� ũ�⸸�� �޸�DC�� �ϳ� �� �����(����� ����). 
           �翬�� ���۹��� ���Ʈ���� ����� ������ �� �޸�DC�� ��������� �Ѵ�.
        2. ����ۿ� �Ͼ�� �簢���� ���� ��, ��ǥ�鿡 �� ������Ʈ�� ��� �׸���.
        3. ������ ������ �������� �� ����, ����ۿ� �׸� ������Ʈ�� ��ǥ�鿡 ��� �׸���.
        
        ���� ��ǥ���� �� �����Ӹ��� 1���� ���ŵǹǷ� �����̰� ��������,
        ����ۿ� �Ͼ� �簢������ �����Ƿ� �ܻ� ���� �ʰԵȴ�. 
        (�Ͼ� �簢������ ���� ������ ���� ���� ���� ��� �׷���. �� ������ �ӽ� ��ġ�̴�.)
    */

    /*
		CreateCompatibleDC : ȭ�� DC�� �ְ� �޸� DC�� ��´�.
		���ӸŴ����� ȭ�� DC�� ���� ����Ѵ�.
	*/
    m_hBackDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());

    // ��Ʈ���� �ε��Ѵ�. ������â�� ������ ũ��� �Ѵ�.
    m_hBackBmp = CreateCompatibleBitmap(m_hDC, m_rs.Width, m_rs.Height);

    /*
        �о�� ��Ʈ���� �޸� DC�� �����Ѵ�.

        SelectObject�� ������ DC�� ������ �ִ� ������ ��ȯ�ϴµ�,
        �װ��� m_hPrevBmp�� ������ �״ٰ� �Ҹ��ڿ��� �ٽ� DC�� �־��� ��
        (������� ������ ��) �����Ѵ�.
        �̰��� ������ �Ϸ��� �����̴�.
    */
    m_hBackPrevBmp = (HBITMAP)SelectObject(m_hBackDC, m_hBackBmp);
    
    m_timeScale = 1.f;  // �⺻��.

    // �� ���� �귯���� ����� ���´�.
    m_brush[(int)EBrushType::Red] = CreateSolidBrush(RGB(255, 0, 0));
    m_brush[(int)EBrushType::Green] = CreateSolidBrush(RGB(0, 255, 0));
    m_brush[(int)EBrushType::Black] = CreateSolidBrush(RGB(0, 0, 0));
    m_brush[(int)EBrushType::Blue] = CreateSolidBrush(RGB(0, 0, 255));
    m_brush[(int)EBrushType::Yellow] = CreateSolidBrush(RGB(255, 255, 0));

    // ���� ����� ���´�. (��Ÿ�� : �ָ���(�Ǽ�), �β� : 2�ȼ�)
    m_pen[(int)EBrushType::Red] = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    m_pen[(int)EBrushType::Green] = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
    m_pen[(int)EBrushType::Black] = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    m_pen[(int)EBrushType::Blue] = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
    m_pen[(int)EBrushType::Yellow] = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));
    
    return true;
}

int CGameManager::Run()
{
    // (�̺�Ʈ �߻� ��)�ü���� ����� �� �޽����� ������ ���� ����ü�̴�.
    MSG msg;

    while (m_loop)
    {
        /*
            PeekMessage : �� �Լ��� �޽��� ť���� �޽����� �������� �Լ��̴�.
            ��, �� �Լ��� �޽��� ť�� ������� ��� GetMessage�� �ٸ��� false��
            ��ȯ�Ͽ� �ٷ� ���������� �ȴ�.
            -> ���� Ÿ���� Ȱ���� �����ϴ�
        */
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            /*
                 TranslateMessage : �޽��� ť���� ������ �޽����� ���� Ű�� ���� �޽�������,
                 f1�̳� ����Ű���� Ű������ �Ǵ��Ѵ�.

                 f1�̳� ����Ű�� ������ WM_KEYDOWN���� �޽��� �ν��� �ǰ�,
                 ���� Ű�� ������ WM_KEYDOWN�� �߰��� WM_CHAR �޽����� ����� �޽��� ť�� �ִ´�.
                 ��, �� �Լ��� ������ ���� Ű�� ���� �޽����� �߻����� �ʴ´�.
            */
            TranslateMessage(&msg);

            /*
                DispatchMessage : �޽��� ť���� ������ �޽����� '�޽��� ó�� �Լ�'�� �����ش�.
                ���� ������ �Լ��� WndProc �Լ��� �����ش�.
            */
            DispatchMessage(&msg);
        }
        else
        {
            // �޽����� ���� �� ���� ������ �����Ѵ�.
            Logic();
        }
    }

    return (int)msg.wParam;
}

void CGameManager::Exit()
{
    // ������ â�� �ݴ´�. 
    // �޽����� ��ȯ�Ǿ� ���α׷��� ����ȴ�.
    DestroyWindow(m_hWnd);
}

HBRUSH CGameManager::GetBrush(EBrushType _type) const
{
    return m_brush[(int)_type];
}

HPEN CGameManager::GetPen(EBrushType _type) const
{
    return m_pen[(int)_type];
}

float CGameManager::GetDeltaTime() const
{
    return m_deltaTime;
}

HDC CGameManager::GetWindowDC() const
{
    return m_hDC;
}

HWND CGameManager::GetWindowHandle() const
{
    return m_hWnd;
}

HINSTANCE CGameManager::GetWindowInstance() const
{
    return m_hInst;
}

float CGameManager::GetTimeScale() const
{
    return m_timeScale;
}

float CGameManager::GetFPS() const
{
    return m_timer->GetFPS();
}

void CGameManager::SetTimeScale(float _scale)
{
    m_timeScale = _scale;
}

/*
    ���� ���� ������ ����Ǵ� �κ�.������ ũ�� 4�ܰ�� ������.
    �� �ܰ迡 ��Ÿ Ÿ���� ���ڷ� �����Ѵ�.
*/ 
void CGameManager::Logic()
{
    // Ÿ�̸Ӹ� �Ź� �����Ͽ�, ��Ÿ Ÿ�Ӱ� fps�� ���Ѵ�.
    m_timer->Update();

    // ������ ��Ÿ Ÿ���� �޾ƿ� �� �ܰ��� ���ڷ� ������ ���̴�.
    // ������� ���� �� �ܰ迡���� ����� �� �ֵ��� �Ѵ�.
    float deltaTime = m_timer->GetDeltaTime() * m_timeScale;

    // ��Ÿ Ÿ�� ��� ������ �����Ѵ�.
    m_deltaTime = deltaTime;

    Input(deltaTime);

    // ���� �߰��� ��ü�� ���, Logic�� ó������ �ٽ� ���۽�Ų��.
    if (Update(deltaTime))
        return;

    // ���� �߰��� ��ü�� ���, Logic�� ó������ �ٽ� ���۽�Ų��.
    if (PostUpdate(deltaTime))
        return;

    Collision(deltaTime);

    Render(deltaTime);
}

void CGameManager::Input(float _deltaTime)
{
    CInput::GetInst()->Update(_deltaTime);
}

bool CGameManager::Update(float _deltaTime)
{
    CResourceManager::GetInst()->Update();
    /*
       ���� ������Ʈ�� �̰����� ���� ������Ʈ���� �ʰ�,
       �� �Ŵ����� ���� ������Ʈ�� ������Ʈ�Ѵ�.
    */ 
    return CSceneManager::GetInst()->Update(_deltaTime);

    
    /*m_player->Update(_deltaTime);*/
}

bool CGameManager::PostUpdate(float _deltaTime)
{
    // ���콺 ������Ʈ ó���� ����. (���Ŵ����� ���ҽ��Ŵ������� ó������ ���ϹǷ�)
    CInput::GetInst()->PostUpdate(_deltaTime);

    return CSceneManager::GetInst()->PostUpdate(_deltaTime);
}

void CGameManager::Collision(float _deltaTime)
{
}

void CGameManager::Render(float _deltaTime)
{
    /*
        ��ǥ���� �ػ󵵿� ������ ũ���� �� �簢���� ����ۿ� �����. 
        (ȭ���� �������� ȿ��)

        �»���� -1, ���ϴ��� +1�� ������ �簢���� �׵θ��� ����� ������ ����
        �Ⱥ��̰� �ϱ� �����̴�.
    */
    // Rectangle(m_hBackDC, -1, -1, m_rs.Width + 1, m_rs.Height + 1);

    // '����ۿ���' ������Ʈ�� �������Ѵ�.
    CSceneManager::GetInst()->Render(m_hBackDC, _deltaTime);
    
    // ��� ������Ʈ�� �׷��� �� ���������� ���콺�� �׸���.
    CInput::GetInst()->Render(m_hBackDC, _deltaTime);
    
    /*
        ������ ����ۿ� ��� ������Ʈ�� ��µǾ���.
        ���������� ����۸� ������, ��ǥ�� ���ۿ� �׷�����.

        BitBlt : �̹����� ���ϴ� DC�� ������ش�.
        1. �̹����� ������� DC (��ǥ��)
        2. ������� DC������ x��ǥ
        3. ������� DC������ y��ǥ
        4. �׷��� �̹����� ����ũ��
        5. �׷��� �̹����� ����ũ��
        6. �̹����� ����� DC (�����)
        7. ����� DC������ ���� x��ǥ
        8. ����� DC������ ���� y��ǥ
        9. �׸��� ��� ���� (SRCCOPY : ��� ����)
    */
    BitBlt(m_hDC, 0, 0, m_rs.Width, m_rs.Height, m_hBackDC, 0, 0, SRCCOPY);

    /*m_player->Render(m_hDC, _deltaTime);*/

    ////////////////////////////// ����1 //////////////////////////////////

    ///*
    //    TextOutA : ��Ƽ����Ʈ ���ڿ�(char�� ���ڿ�)�� ����ϴ� �Լ��̴�.
    //    TextOutW : �����ڵ� ���ڿ�(wchar_t�� ���ڿ�)�� ����ϴ� �Լ��̴�.
    //    TextOut : ���� ������Ʈ�� ������ ��Ƽ����Ʈ���� �����ڵ������� ���� ���� �� �Լ��� �ϳ��� �����ȴ�.
    //*/
    //TextOut(m_hDC, 50, 50, TEXT("�ؽ�Ʈ1"), lstrlen(TEXT("�ؽ�Ʈ1")));
    //TextOut(m_hDC, 50, 100, TEXT("�ؽ�Ʈ2"), lstrlen(TEXT("�ؽ�Ʈ2")));
    //
    //
    ///*
    //    ���� �׸���
    //    Rectangle : �簢���� �׸���. (�»�� ��ǥ, ���ϴ� ��ǥ)
    //    Ellipse : ���� �׸���. (����)
    //*/
    //Rectangle(m_hDC, 50, 150, 150, 250);
    //Ellipse(m_hDC, 50, 300, 150, 400);

    ///*
    //    �ȼ� ��� : 
    //    �ȼ��� 20�� ��� ����ó�� ���̰� �Ѵ�. (��ǥ, ����)
    //*/ 
    //for (int i = 0; i < 20; ++i)
    //{
    //    SetPixel(m_hDC, 200+i, 100, RGB(255, 0, 0));
    //}

    ///*
    //    ���� �׸���
    //    MoveToEx : �������� �����Ѵ�.
    //    LineTo : �������� ������ �����κ��� ���� ���� �����ϴ� ���� �׸���.
    //*/
    //MoveToEx(m_hDC, 200, 300, nullptr);
    //LineTo(m_hDC, 300, 500);
    //LineTo(m_hDC, 200, 600);

    ///*
    //    ������ �浹 �����ϱ� : 
    //    ������ �»�ܰ� ���ϴ��� y��ǥ�� 1�� ������Ű�鼭
    //    �������� Ŭ���̾�Ʈ ������ ���� ���� ���� ��
    //    ��ȣ�� �ٲٰ� �ٽ� 1�� ������Ű�� �ݴ�� �̵��ϰ� �ȴ�.
    //*/
    //m_testRC.top += m_dir;
    //m_testRC.bottom += m_dir;

    //if (m_testRC.bottom >= 720)
    //{
    //    m_dir = -1;
    //}
    //if (m_testRC.top <= 0)
    //{
    //    m_dir = 1;
    //}

    //Rectangle(m_hDC, m_testRC.left, m_testRC.top, m_testRC.right, m_testRC.bottom);

    ///*
    //    ��Ÿ Ÿ�Ӱ� �װ��� �̿��� ������� ���� �ð��� ����Ѵ�.

    //    sprintf_s : ��Ƽ����Ʈ ���ڿ��� �����.
    //    - �����ڵ� ���ڿ��� ���ڿ��� �Ǽ��� ó���� �� �ȵǹǷ�, 
    //      ��Ƽ����Ʈ�� �����.
    //*/
    //// ��Ÿ Ÿ���� ���ڿ��� ����� ����Ѵ�.
    //char dtText[64] = {};
    //sprintf_s(dtText, "DeltaTime : %.5f", _deltaTime);
    //TextOutA(m_hDC, 600, 50, dtText, strlen(dtText));

    //// ��Ÿ Ÿ���� �������� ������� ���� �ð��� ���Ѵ�.
    //static float currentTime = 0.f;
    //currentTime += _deltaTime;

    //// ���� �ð��� ���ڿ��� ����� ����Ѵ�.
    //char timeText[64] = {};
    //sprintf_s(timeText, "pastTime : %.5f", currentTime);
    //TextOutA(m_hDC, 600, 100, timeText, strlen(timeText));

    ///*
    //    ��Ÿ Ÿ���� ��¿� Ȱ���غ���.

    //    ���ϴ� ���ۿ� ��Ÿ Ÿ���� �������ν�, 
    //    �� ������ �� 1�ʿ� ���ļ� �� �� �ִ�.

    //    ��Ÿ Ÿ�ӿ� � ��(x)�� ���ϰ� 1�ʰ� ������ x�� ������ �ȴ�.
    //    ���� �������� ���߳����ص�, � ������ �� �� ������ ����Ǵ� �ӵ��� 
    //    ��� ��ǻ�Ϳ��� �����ϰ� ������ �� �ִ�. 
    //*/
    //static float top = 100.f;
    //static float bottom = 200.f;

    //// �ʴ� 400 �ȼ���ŭ �����̵��� �Ѵ�.  
    //top += 400.f * _deltaTime;
    //bottom += 400.f * _deltaTime;

    //Rectangle(m_hDC, 800, top, 900, bottom);

    ///////////////////////////////////////////////////////////////////////

}

void CGameManager::Register()
{
    // �������Ϳ� �����, '������ Ŭ����' ����ü�� ������ش�.
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    // ������� �������� ���¸� �����Ѵ�.

    // (â ���� ������)�������� ���� �Ǵ� ���ΰ� �ٲ�� �� ���, �ٽ� �׷��ֵ��� �Ѵ�.
    wcex.style = CS_HREDRAW | CS_VREDRAW;

    // �޽��� ť���� ���� �޽����� ���ڷ� ������ �� ȣ���� �Լ�(defalt : WndProc)�� �ּҸ� ����Ѵ�.
    wcex.lpfnWndProc = WndProc;

    // �����Ѵ�.
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;

    // hinstance(�� ���α׷��� �ĺ���ȣ)�� ����Ѵ�.
    wcex.hInstance = m_hInst;

    // �������Ͽ� ����� �������� �����Ѵ�.
    wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));

    // ���콺 Ŀ���� ����� �����Ѵ�.
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);

    // �����Ѵ�.
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    // ��� �޴��� ��� ���θ� �����Ѵ�.
    wcex.lpszMenuName = nullptr; // MAKEINTRESOURCEW(IDC_WINAPIBASE);

    // ����� '������ Ŭ����'�� �̸��� �����ڵ� ���ڿ��� ����� �����Ѵ�.
    // ������ Ŭ������ �̸����� �ѱ��� ������ �� �ȴ�.
    // TEXT ��ũ�� : ������Ʈ ������ �����ڵ����� ��Ƽ����Ʈ������ ���� �׿� �´� ���ڿ��� ��ȯ��Ų��.
    wcex.lpszClassName = TEXT("GameFramework");

    // ������â �»�ܿ� ǥ���� ���� �������� ����Ѵ�.
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    // ������ �������� ���¸� ���� ����Ѵ�.
    RegisterClassExW(&wcex);
}

bool CGameManager::Create()
{
    /*
       CreateWindowW : ������ â ����, ���ڴ� �� 11���̴�.
       1. ������ Ŭ������ �̸�
       2. Ÿ��Ʋ �ٿ� ǥ���� �̸�
       3. ������ â�� ��� ���������� �����ϴ� �ɼ� (WS_OVERLAPPEDWINDOW : �⺻ �ɼ�)
          - OVERLAPPED  : �������� ������
          - CAPTION     : Ÿ��Ʋ�ٿ� �̸� ǥ����
          - SYSMENU     : �»�� �������� ������ �� �޴� ������ ��
          - THICKFRAME  : �����ڸ��� ��� ũ�� ���� ����
          - MINIMIZEBOX : �ּ�ȭ ��ư
          - MAXIMIZEBOX : �ִ�ȭ ��ư
          - POPUP       : (��� �޽���ó��) Ƣ����� ������
       4,5. ������ â�� ������ �»�� ��ġ�� x,y��ǥ�� �ȼ������� �����Ѵ�.
       6,7. ������ â�� ����, ������ ũ�⸦ �ȼ������� �����Ѵ�.
       8. �θ������찡 �ִٸ� �θ��������� �ڵ��� �����ϰ�, ���ٸ� nullptr�� �����Ѵ�.
       9. �޴��� �ִٸ� �޴� �ڵ��� �����ϰ�, ���ٸ� nullptr�� �����Ѵ�.
       10. ���α׷��� �ν��Ͻ��� �����Ͽ� �� �ν��Ͻ��� ���� ������ â�� ���鵵�� �Ѵ�.
       11. �����Ѵ�.
  */
    m_hWnd = CreateWindowW(TEXT("GameFramework"), TEXT("GameFramework"), WS_OVERLAPPEDWINDOW,
        50, 50, 0, 0, nullptr, nullptr, m_hInst, nullptr);

    if (!m_hWnd)
    {
        return false;
    }

    /*
        CreateWindowW �Լ��� �̿��� ������ ũ�⸦ 1280X720���� ��Ƶ�, �̰��� ��ü �������� ũ������
        'Ŭ���̾�Ʈ ����'�� ũ�Ⱑ �ƴϴ�.
        ���� Ŭ���̾�Ʈ ������ ũ�⸦ 1280X720���� �ϰ� �ʹٸ�, ��ü ������ ũ��� �� Ŀ���Ѵ�.

        �̶�, AdjustWindowRect �Լ��� �̿��� ������ �ʿ��� ������ ũ�⸦ ������,
        MoveWindow �Լ��� �̿��� ���� ũ��� �������� ũ�⸦ �������ش�
    */
    // RECT : �簢���� ǥ���ϱ� ���� �����ϴ� ����ü. left, top, right, bottom ������ �̷���� �ִ�.
    // RECT rc = { 0, 0, 1280, 720 };
    // �ʱ�ȭ�� �ػ� ����� ������ش�.
    RECT rc = { 0, 0, m_rs.Width, m_rs.Height };

    // �� rc���� ������ ũ�⸸ŭ Ŭ���̾�Ʈ ������ ũ��� ��� ���ؼ�, ���� �ʿ��� ������ ũ�⸦ ���´�.
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    // ������ ���� ũ��� ������ â�� ũ�⸦ �����Ѵ�. (2,3:������, 4,5:���μ��� ũ��)
    MoveWindow(m_hWnd, 50, 50, rc.right - rc.left, rc.bottom - rc.top, TRUE);

    // ShowWindow : ������ â�� ���̵��� �����Ѵ�.
    // 1�������� �����츦 �������� ������ 2�����ڿ� ���� �����Ѵ�.
    ShowWindow(m_hWnd, SW_SHOW); // SW_HIDE

    // UpdataWindow : �ش� �������� Ŭ���̾�Ʈ ������ �����Ѵ�.
    // ����� �����Ͽ��ٸ� 0�� �ƴ� ����, �����ߴٸ� 0�� ��ȯ�Ѵ�.
    UpdateWindow(m_hWnd);

    return true;
}

LRESULT CGameManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // �޽����� ���� �б⸦ �޸��Ͽ� ó���Ѵ�.
    switch (message)
    {
    // x��ư�� ������ WM_DESTROY�޽����� �����ǰ�, m_loop�� �����Ͽ� �޽��� ������ ����������.
    case WM_DESTROY:
        m_loop = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
