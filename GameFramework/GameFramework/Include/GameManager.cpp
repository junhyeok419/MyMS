#include "GameManager.h"
#include "resource.h"   // 아이콘 등을 사용하기 위해
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
        _CrtSetDbgFlag : 디버그 모드로 실행 시 메모리 릭이 발생할 경우
        '번호'를 남겨준다.

        _CrtSetBreakAlloc : 위에서 나온 '번호'를 인자로 전달하고 
        실행하면 메모리 릭이 발생한 코드를 알려준다.
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

    // 브러쉬를 제거한다.
    for (int i = 0; i < (int)EBrushType::Max; ++i)
    {
        DeleteObject(m_brush[i]);
    }

    // 펜을 제거한다.
    for (int i = 0; i < (int)EBrushType::Max; ++i)
    {
        DeleteObject(m_pen[i]);
    }

    // 프로그램 종료 시, 첫 인자의 윈도우에 해당하는 DC를 제거한다.
    ReleaseDC(m_hWnd, m_hDC);   
}

bool CGameManager::Init(HINSTANCE _hInst)
{
	m_hInst = _hInst;

    m_rs.Width = 800;
    m_rs.Height = 600;

	// 윈도우클래스 구조체를 만들어주고 등록한다. (->MyRegisterClass)
	Register();

    // 윈도우 창을 생성하고 보여준다. (->InitInstance)
    Create();

    // 패스 매니저를 생성하고 초기화한다
    if (!CPathManager::GetInst()->Init())
    {
        return false;
    }

    // 리소스 매니저를 생성하고 초기화한다.
    if (!CResourceManager::GetInst()->Init())
    {
        return false;
    }

    // 충돌 매니저를 생성하고 초기화한다.
    if (!CCollisionManager::GetInst()->Init())
        return false;

    // 입력 매니저를 생성하고 초기화한다.
    if (!CInput::GetInst()->Init(m_hWnd))
    {
        return false;
    }

    // 씬 매니저를 생성하고 초기화한다.
    if (!CSceneManager::GetInst()->Init())
    {
        return false;
    }

    // 고해상도 타이머를 생성하고 초기화한다.
    m_timer = new CTimer;
    m_timer->Init();

    /* 
        GetDC : 인자의 윈도우에 그리기 위한 DC를 얻어온다.
        DC는 윈도우 프로그램에서 출력하기 위해 꼭 필요한 핸들이다. (그리기 도구)
        이 함수로 DC를 얻어오면 나중에 ReleaseDC를 이용해 소멸시켜야 한다.
    */ 
    m_hDC = GetDC(m_hWnd);

    m_frameLimitTime = 1 / 60.f;

    /*
        <더블 버퍼링을 이용한 문제 해결>

        현재 렌더링의 문제점
        1. 오브젝트 1개를 그릴때마다 계속 갱신이 되므로, 물체가 깜빡인다.
        2. 주표면을 지우지 않으므로 잔상이 남는다.
        -> 더블 버퍼링을 이용하여 해결한다.

        더블 버퍼링 과정
        1. 주표면 크기만한 메모리DC를 하나 더 만든다(백버퍼 생성). 
           당연히 백퍼버용 백비트맵을 만들어 구성한 뒤 메모리DC에 지정해줘야 한다.
        2. 백버퍼에 하얀색 사각형을 덮은 뒤, 주표면에 들어갈 오브젝트를 모두 그린다.
        3. 렌더링 과정의 마지막에 한 번만, 백버퍼에 그린 오브젝트를 주표면에 모두 그린다.
        
        이제 주표면은 매 프레임마다 1번만 갱신되므로 깜빡이가 없어지고,
        백버퍼에 하얀 사각형으로 덮으므로 잔상도 남지 않게된다. 
        (하얀 사각형으로 덮는 이유는 아직 게임 맵이 없어서 그렇다. 그 전까지 임시 조치이다.)
    */

    /*
		CreateCompatibleDC : 화면 DC를 넣고 메모리 DC를 얻는다.
		게임매니저의 화면 DC를 얻어다 사용한다.
	*/
    m_hBackDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());

    // 비트맵을 로딩한다. 윈도우창과 동일한 크기로 한다.
    m_hBackBmp = CreateCompatibleBitmap(m_hDC, m_rs.Width, m_rs.Height);

    /*
        읽어온 비트맵을 메모리 DC에 지정한다.

        SelectObject는 기존에 DC가 가지고 있던 도구를 반환하는데,
        그것을 m_hPrevBmp에 저장해 뒀다가 소멸자에서 다시 DC에 넣어준 뒤
        (원래대로 돌려준 뒤) 삭제한다.
        이것은 정해진 일련의 과정이다.
    */
    m_hBackPrevBmp = (HBITMAP)SelectObject(m_hBackDC, m_hBackBmp);
    
    m_timeScale = 1.f;  // 기본값.

    // 몇 가지 브러쉬를 만들어 놓는다.
    m_brush[(int)EBrushType::Red] = CreateSolidBrush(RGB(255, 0, 0));
    m_brush[(int)EBrushType::Green] = CreateSolidBrush(RGB(0, 255, 0));
    m_brush[(int)EBrushType::Black] = CreateSolidBrush(RGB(0, 0, 0));
    m_brush[(int)EBrushType::Blue] = CreateSolidBrush(RGB(0, 0, 255));
    m_brush[(int)EBrushType::Yellow] = CreateSolidBrush(RGB(255, 255, 0));

    // 펜을 만들어 놓는다. (스타일 : 솔리드(실선), 두께 : 2픽셀)
    m_pen[(int)EBrushType::Red] = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    m_pen[(int)EBrushType::Green] = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
    m_pen[(int)EBrushType::Black] = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    m_pen[(int)EBrushType::Blue] = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
    m_pen[(int)EBrushType::Yellow] = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));
    
    return true;
}

int CGameManager::Run()
{
    // (이벤트 발생 시)운영체제가 만들어 준 메시지를 얻어오기 위한 구조체이다.
    MSG msg;

    while (m_loop)
    {
        /*
            PeekMessage : 이 함수도 메시지 큐에서 메시지를 꺼내오는 함수이다.
            단, 이 함수는 메시지 큐가 비어있을 경우 GetMessage와 다르게 false를
            반환하여 바로 빠져나오게 된다.
            -> 데드 타임의 활용이 가능하다
        */
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            /*
                 TranslateMessage : 메시지 큐에서 꺼내온 메시지가 문자 키에 대한 메시지인지,
                 f1이나 방향키같은 키인지를 판단한다.

                 f1이나 방향키를 누르면 WM_KEYDOWN으로 메시지 인식이 되고,
                 문자 키를 누르면 WM_KEYDOWN에 추가로 WM_CHAR 메시지를 만들어 메시지 큐에 넣는다.
                 즉, 이 함수가 없으면 문자 키에 대한 메시지가 발생하지 않는다.
            */
            TranslateMessage(&msg);

            /*
                DispatchMessage : 메시지 큐에서 꺼내온 메시지를 '메시지 처리 함수'에 보내준다.
                현재 설정된 함수인 WndProc 함수로 보내준다.
            */
            DispatchMessage(&msg);
        }
        else
        {
            // 메시지가 없을 때 게임 로직을 실행한다.
            Logic();
        }
    }

    return (int)msg.wParam;
}

void CGameManager::Exit()
{
    // 윈도우 창을 닫는다. 
    // 메시지가 반환되어 프로그램이 종료된다.
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
    실제 게임 로직이 실행되는 부분.게임을 크게 4단계로 나눈다.
    각 단계에 델타 타임을 인자로 전달한다.
*/ 
void CGameManager::Logic()
{
    // 타이머를 매번 갱신하여, 델타 타임과 fps를 구한다.
    m_timer->Update();

    // 갱신한 델타 타임을 받아와 각 단계의 인자로 전달할 것이다.
    // 배속율을 곱해 각 단계에서도 적용될 수 있도록 한다.
    float deltaTime = m_timer->GetDeltaTime() * m_timeScale;

    // 델타 타임 멤버 변수를 갱신한다.
    m_deltaTime = deltaTime;

    Input(deltaTime);

    // 씬이 중간에 교체될 경우, Logic의 처음부터 다시 동작시킨다.
    if (Update(deltaTime))
        return;

    // 씬이 중간에 교체될 경우, Logic의 처음부터 다시 동작시킨다.
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
       이제 오브젝트를 이곳에서 직접 업데이트하지 않고,
       씬 매니저를 통해 오브젝트를 업데이트한다.
    */ 
    return CSceneManager::GetInst()->Update(_deltaTime);

    
    /*m_player->Update(_deltaTime);*/
}

bool CGameManager::PostUpdate(float _deltaTime)
{
    // 마우스 업데이트 처리를 위해. (씬매니저나 리소스매니저에서 처리하지 못하므로)
    CInput::GetInst()->PostUpdate(_deltaTime);

    return CSceneManager::GetInst()->PostUpdate(_deltaTime);
}

void CGameManager::Collision(float _deltaTime)
{
}

void CGameManager::Render(float _deltaTime)
{
    /*
        주표면의 해상도와 동일한 크기의 흰 사각형을 백버퍼에 만든다. 
        (화면을 지워내는 효과)

        좌상단이 -1, 우하단이 +1인 이유는 사각형의 테두리에 생기는 검은색 선을
        안보이게 하기 위함이다.
    */
    // Rectangle(m_hBackDC, -1, -1, m_rs.Width + 1, m_rs.Height + 1);

    // '백버퍼에만' 오브젝트를 렌더링한다.
    CSceneManager::GetInst()->Render(m_hBackDC, _deltaTime);
    
    // 모든 오브젝트가 그려진 뒤 마지막으로 마우스를 그린다.
    CInput::GetInst()->Render(m_hBackDC, _deltaTime);
    
    /*
        위에서 백버퍼에 모든 오브젝트가 출력되었다.
        마지막으로 백버퍼를 통으로, 주표면 버퍼에 그려낸다.

        BitBlt : 이미지를 원하는 DC에 출력해준다.
        1. 이미지를 출력해줄 DC (주표면)
        2. 출력해줄 DC에서의 x좌표
        3. 출력해줄 DC에서의 y좌표
        4. 그려낼 이미지의 가로크기
        5. 그려낼 이미지의 세로크기
        6. 이미지를 출력할 DC (백버퍼)
        7. 출력할 DC에서의 시작 x좌표
        8. 출력할 DC에서의 시작 y좌표
        9. 그리는 방법 지정 (SRCCOPY : 고속 복사)
    */
    BitBlt(m_hDC, 0, 0, m_rs.Width, m_rs.Height, m_hBackDC, 0, 0, SRCCOPY);

    /*m_player->Render(m_hDC, _deltaTime);*/

    ////////////////////////////// 기초1 //////////////////////////////////

    ///*
    //    TextOutA : 멀티바이트 문자열(char형 문자열)을 출력하는 함수이다.
    //    TextOutW : 유니코드 문자열(wchar_t형 문자열)을 출력하는 함수이다.
    //    TextOut : 현재 프로젝트의 설정이 멀티바이트인지 유니코드인지에 따라 위의 두 함수중 하나가 결정된다.
    //*/
    //TextOut(m_hDC, 50, 50, TEXT("텍스트1"), lstrlen(TEXT("텍스트1")));
    //TextOut(m_hDC, 50, 100, TEXT("텍스트2"), lstrlen(TEXT("텍스트2")));
    //
    //
    ///*
    //    도형 그리기
    //    Rectangle : 사각형을 그린다. (좌상단 좌표, 우하단 좌표)
    //    Ellipse : 원을 그린다. (동일)
    //*/
    //Rectangle(m_hDC, 50, 150, 150, 250);
    //Ellipse(m_hDC, 50, 300, 150, 400);

    ///*
    //    픽셀 찍기 : 
    //    픽셀을 20개 찍어 직선처럼 보이게 한다. (좌표, 색상)
    //*/ 
    //for (int i = 0; i < 20; ++i)
    //{
    //    SetPixel(m_hDC, 200+i, 100, RGB(255, 0, 0));
    //}

    ///*
    //    직선 그리기
    //    MoveToEx : 시작점을 지정한다.
    //    LineTo : 마지막에 지정된 점으로부터 현재 점을 연결하는 선을 그린다.
    //*/
    //MoveToEx(m_hDC, 200, 300, nullptr);
    //LineTo(m_hDC, 300, 500);
    //LineTo(m_hDC, 200, 600);

    ///*
    //    도형의 충돌 연습하기 : 
    //    도형의 좌상단과 우하단의 y좌표를 1씩 증감시키면서
    //    윈도우의 클라이언트 영역의 끝에 도달 했을 때
    //    부호를 바꾸고 다시 1씩 증감시키면 반대로 이동하게 된다.
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
    //    델타 타임과 그것을 이용해 현재까지 지난 시간을 출력한다.

    //    sprintf_s : 멀티바이트 문자열을 만든다.
    //    - 유니코드 문자열은 문자열의 실수부 처리가 잘 안되므로, 
    //      멀티바이트로 만든다.
    //*/
    //// 델타 타임을 문자열로 만들고 출력한다.
    //char dtText[64] = {};
    //sprintf_s(dtText, "DeltaTime : %.5f", _deltaTime);
    //TextOutA(m_hDC, 600, 50, dtText, strlen(dtText));

    //// 델타 타임을 누적시켜 현재까지 지난 시간을 구한다.
    //static float currentTime = 0.f;
    //currentTime += _deltaTime;

    //// 지난 시간을 문자열로 만들고 출력한다.
    //char timeText[64] = {};
    //sprintf_s(timeText, "pastTime : %.5f", currentTime);
    //TextOutA(m_hDC, 600, 100, timeText, strlen(timeText));

    ///*
    //    델타 타임을 출력에 활용해본다.

    //    원하는 동작에 델타 타임을 곱함으로써, 
    //    그 동작을 총 1초에 걸쳐서 할 수 있다.

    //    델타 타임에 어떤 값(x)을 곱하건 1초가 지나면 x가 나오게 된다.
    //    따라서 프레임이 들쭉날쭉해도, 어떤 동작이 한 번 완전히 수행되는 속도를 
    //    모든 컴퓨터에서 일정하게 유지할 수 있다. 
    //*/
    //static float top = 100.f;
    //static float bottom = 200.f;

    //// 초당 400 픽셀만큼 움직이도록 한다.  
    //top += 400.f * _deltaTime;
    //bottom += 400.f * _deltaTime;

    //Rectangle(m_hDC, 800, top, 900, bottom);

    ///////////////////////////////////////////////////////////////////////

}

void CGameManager::Register()
{
    // 레지스터에 등록할, '윈도우 클래스' 구조체를 만들어준다.
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    // 여기부터 윈도우의 형태를 설정한다.

    // (창 조절 등으로)윈도우의 가로 또는 세로가 바뀌게 될 경우, 다시 그려주도록 한다.
    wcex.style = CS_HREDRAW | CS_VREDRAW;

    // 메시지 큐에서 꺼낸 메시지를 인자로 전달할 때 호출할 함수(defalt : WndProc)의 주소를 등록한다.
    wcex.lpfnWndProc = WndProc;

    // 무시한다.
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;

    // hinstance(이 프로그램의 식별번호)를 등록한다.
    wcex.hInstance = m_hInst;

    // 실행파일에 사용할 아이콘을 결정한다.
    wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));

    // 마우스 커서의 모양을 결정한다.
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);

    // 무시한다.
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    // 상단 메뉴의 사용 여부를 결정한다.
    wcex.lpszMenuName = nullptr; // MAKEINTRESOURCEW(IDC_WINAPIBASE);

    // 등록할 '윈도우 클래스'의 이름을 유니코드 문자열로 만들어 지정한다.
    // 윈도우 클래스의 이름에는 한글을 넣으면 안 된다.
    // TEXT 매크로 : 프로젝트 설정이 유니코드인지 멀티바이트인지에 따라 그에 맞는 문자열로 변환시킨다.
    wcex.lpszClassName = TEXT("GameFramework");

    // 윈도우창 좌상단에 표시할 작은 아이콘을 등록한다.
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    // 설정한 윈도우의 형태를 최종 등록한다.
    RegisterClassExW(&wcex);
}

bool CGameManager::Create()
{
    /*
       CreateWindowW : 윈도우 창 생성, 인자는 총 11개이다.
       1. 윈도우 클래스의 이름
       2. 타이틀 바에 표시할 이름
       3. 윈도우 창을 어떻게 생성할지를 지정하는 옵션 (WS_OVERLAPPEDWINDOW : 기본 옵션)
          - OVERLAPPED  : 겹쳐지는 윈도우
          - CAPTION     : 타이틀바에 이름 표시함
          - SYSMENU     : 좌상단 아이콘을 눌렀을 때 메뉴 나오게 함
          - THICKFRAME  : 가장자리를 잡고 크기 조정 가능
          - MINIMIZEBOX : 최소화 버튼
          - MAXIMIZEBOX : 최대화 버튼
          - POPUP       : (경고 메시지처럼) 튀어나오는 윈도우
       4,5. 윈도우 창이 생성될 좌상단 위치의 x,y좌표를 픽셀단위로 지정한다.
       6,7. 윈도우 창의 가로, 세로의 크기를 픽셀단위로 지정한다.
       8. 부모윈도우가 있다면 부모윈도우의 핸들을 지정하고, 없다면 nullptr로 지정한다.
       9. 메뉴가 있다면 메뉴 핸들을 지정하고, 없다면 nullptr로 지정한다.
       10. 프로그램의 인스턴스를 지정하여 이 인스턴스에 속한 윈도우 창을 만들도록 한다.
       11. 무시한다.
  */
    m_hWnd = CreateWindowW(TEXT("GameFramework"), TEXT("GameFramework"), WS_OVERLAPPEDWINDOW,
        50, 50, 0, 0, nullptr, nullptr, m_hInst, nullptr);

    if (!m_hWnd)
    {
        return false;
    }

    /*
        CreateWindowW 함수를 이용해 윈도우 크기를 1280X720으로 잡아도, 이것은 전체 윈도우의 크기이지
        '클라이언트 영역'의 크기가 아니다.
        따라서 클라이언트 영역의 크기를 1280X720으로 하고 싶다면, 전체 윈도우 크기는 더 커야한다.

        이때, AdjustWindowRect 함수를 이용해 실제로 필요한 윈도우 크기를 얻어오고,
        MoveWindow 함수를 이용해 얻어온 크기로 윈도우의 크기를 변경해준다
    */
    // RECT : 사각형을 표현하기 위해 지원하는 구조체. left, top, right, bottom 값으로 이루어져 있다.
    // RECT rc = { 0, 0, 1280, 720 };
    // 초기화한 해상도 멤버로 만들어준다.
    RECT rc = { 0, 0, m_rs.Width, m_rs.Height };

    // 위 rc에서 지정한 크기만큼 클라이언트 영역의 크기로 잡기 위해서, 실제 필요한 윈도우 크기를 얻어온다.
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    // 위에서 얻어온 크기로 윈도우 창의 크기를 변경한다. (2,3:시작점, 4,5:가로세로 크기)
    MoveWindow(m_hWnd, 50, 50, rc.right - rc.left, rc.bottom - rc.top, TRUE);

    // ShowWindow : 윈도우 창을 보이도록 설정한다.
    // 1번인자의 윈도우를 보여줄지 말지를 2번인자에 따라 결정한다.
    ShowWindow(m_hWnd, SW_SHOW); // SW_HIDE

    // UpdataWindow : 해당 윈도우의 클라이언트 영역을 갱신한다.
    // 제대로 갱신하였다면 0이 아닌 값을, 실패했다면 0을 반환한다.
    UpdateWindow(m_hWnd);

    return true;
}

LRESULT CGameManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // 메시지에 따라 분기를 달리하여 처리한다.
    switch (message)
    {
    // x버튼을 누르면 WM_DESTROY메시지가 생성되고, m_loop를 조작하여 메시지 루프를 빠져나간다.
    case WM_DESTROY:
        m_loop = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
