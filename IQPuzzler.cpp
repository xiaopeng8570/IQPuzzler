// IQPuzzler.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "IQPuzzler.h"
#include "PzSolveThread.h"
#include "PzPieceGroup.h"
#include "PzPiece.h"
#include "PzBoard.h"
#include "PzBoardSquare.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

PzSolveThread gSolveThread;
PzPieceGroup gPieceGroup;

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_IQPUZZLER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_IQPUZZLER));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



void InitPieceGroup()
{
    PzPiece pp;
    pp.Reset();
    pp.SetName("blue");
    pp.SetPoints({ 0, 0, 1, 0, 2, 0, 0, 1 });
    gPieceGroup.AddPiece(pp);

    pp.Reset();
    pp.SetName("red");
    pp.SetPoints({ 0, 0, 1, 0, 2, 0, 3, 0, 0, 1 });
    gPieceGroup.AddPiece(pp);

    pp.Reset();
    pp.SetName("pink");
    pp.SetPoints({ 0, 0, 1, 0, 1, 1, 2, 1, 3, 1 });
    gPieceGroup.AddPiece(pp);

    pp.Reset();
    pp.SetName("green");
    pp.SetPoints({ 0, 0, 1, 0, 2, 0, 0, 1, 2, 1 });
    gPieceGroup.AddPiece(pp);

    pp.Reset();
    pp.SetName("yellow");
    pp.SetPoints({ 0, 0, 1, 0, 2, 0, 3, 0, 1, 1 });
    gPieceGroup.AddPiece(pp);

    pp.Reset();
    pp.SetName("skyblue");
    pp.SetPoints({ 0, 0, 1, 0, 2, 0, 0, 1, 0, 2 });
    gPieceGroup.AddPiece(pp);

    pp.Reset();
    pp.SetName("deepgreen");
    pp.SetPoints({ 0, 0, 1, 0, 2, 0, 1, 1 });
    gPieceGroup.AddPiece(pp);

    pp.Reset();
    pp.SetName("purple");
    pp.SetPoints({ 0, 0, 0, 1, 1, 1, 1, 2, 2, 2 });
    gPieceGroup.AddPiece(pp);

    pp.Reset();
    pp.SetName("coffee");
    pp.SetPoints({ 0, 0, 1, 0, 1, 1, 2, 1 });
    gPieceGroup.AddPiece(pp);

    pp.Reset();
    pp.SetName("cyan");
    pp.SetPoints({ 0, 0, 1, 0, 2, 0, 0, 1, 1, 1 });
    gPieceGroup.AddPiece(pp);

    pp.Reset();
    pp.SetName("orange");
    pp.SetPoints({ 0, 0, 0, 1, 1, 1, 2, 1, 1, 2 });
    gPieceGroup.AddPiece(pp);

    pp.Reset();
    pp.SetName("lightblue");
    pp.SetPoints({ 0, 0, 1, 0, 0, 1 });
    gPieceGroup.AddPiece(pp);
}

//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_IQPUZZLER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_IQPUZZLER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   InitPieceGroup();

   PzBoard* pBoard = new PzBoardSquare();
   if (false) {
       pBoard->AddPiece({ 0,0, 0,1, 0,2, 1,2, 1,3 });
       pBoard->AddPiece({ 1,0, 1,1, 2,0 });
       pBoard->AddPiece({ 3,0, 4,0, 4,1, 5,1, 5,2 });
       pBoard->AddPiece({ 5,0, 6,0, 7,0, 8,0, 6,1 });
       pBoard->AddPiece({ 9,0, 10,0, 8,1, 9,1, 10,1 });
   }
   if (true) {
       pBoard->AddPiece({ 0,0, 0,1, 1,1, 2,1 });
       pBoard->AddPiece({ 2,2, 2,3, 3,3, 4,3, 5,3 });
   }

   gSolveThread.SetBoard(pBoard);
   gSolveThread.Solve();

   gPieceGroup.BeginEnum();

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   ::SetTimer(hWnd, 1, 500, NULL);

   return TRUE;
}

COLORREF GetPieceColor(const PzPiece& pc)
{
    std::string pname = pc.GetName();
    if (pname == "blue") {
        return RGB(0, 128, 255);
    }
    else if (pname == "red") {
        return RGB(255, 0, 0);
    }
    else if (pname == "pink") {
        return RGB(255, 128, 255);
    }
    else if (pname == "green") {
        return RGB(128, 255, 0);
    }
    else if (pname == "yellow") {
        return RGB(255, 255, 128);
    }
    else if (pname == "skyblue") {
        return RGB(128, 192, 255);
    }
    else if (pname == "deepgreen") {
        return RGB(0, 198, 50);
    }
    else if (pname == "purple") {
        return RGB(128, 0, 128);
    }
    else if (pname == "coffee") {
        return RGB(128, 64, 0);
    }
    else if (pname == "cyan") {
        return RGB(170, 231, 25);
    }
    else if (pname == "orange") {
        return RGB(255, 128, 0);
    }
    else if (pname == "lightblue") {
        return RGB(53, 202, 175);
    }
    return RGB(220, 220, 220);
}

void DoPaintPiece(HDC hdc, const PzPiece& pc) {
    COLORREF clr = GetPieceColor(pc);
    HBRUSH hBrush = CreateSolidBrush(clr);
    HGDIOBJ pOld = SelectObject(hdc, hBrush);

    auto ps = pc.GetPoints();
    for (auto p = ps.begin(); p != ps.end(); p++) {
        int px = p->x * 15 + 30;
        int py = p->y * 15 + 30;
        RoundRect(hdc, px, py, px + 10, py + 10, 5, 5);
    }
    SelectObject(hdc, pOld);
    DeleteObject(hBrush);
}

void DoPaintPoint(HDC hdc, const PzPoint& p) {

    SelectObject(hdc, CreatePen(PS_SOLID, 2, RGB(200, 200, 200)));
    int px = p.x * 15 + 30;
    int py = p.y * 15 + 30;
    Arc(hdc, px, py, px + 10, py + 10, px, py + 5, px + 10, py + 5);
    Arc(hdc, px, py, px + 10, py + 10, px + 10, py + 5, px, py + 5);
}

void DoPaintSquare(HDC hdc)
{
    PzBoardSquare *pBoard = reinterpret_cast<PzBoardSquare*>(gSolveThread.GetBoard());
    if (pBoard == nullptr) {
        return;
    }
    auto pcs = pBoard->GetPieces();
    for (auto pc = pcs.begin(); pc != pcs.end(); pc++) {
        DoPaintPiece(hdc, *pc);
    }
    auto pps = pBoard->GetPoints();
    for (auto p = pps.begin(); p != pps.end(); p++) {
        if (!pBoard->IsCover(*p) && !p->IsCover()) {
            DoPaintPoint(hdc, *p);
        }
    }
}

void DoPaint(HDC hdc)
{
    DoPaintSquare(hdc);

    return;

    //SelectObject(hdc, CreatePen(PS_SOLID, 2, RGB(255, 0, 0)));
    SelectObject(hdc, GetStockObject(GRAY_BRUSH));

    PzPointGroup pg = gPieceGroup.EnumGetPointGroup();
    if (!pg.IsError()) {
        std::vector<PzPoint> ps = pg.GetPoints();
        for (auto p = ps.begin(); p != ps.end(); p++) {
            MoveToEx(hdc, 10 + p->x * 15, 10 + p->y * 15, NULL);
            RoundRect(hdc, 10 + p->x * 15, 10 + p->y * 15,
                20 + p->x * 15, 20 + p->y * 15,
                5, 5);
        }
    }

    //LineTo(hdc, 100, 100);
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            DoPaint(hdc);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_TIMER:
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_LBUTTONUP:
        gPieceGroup.EnumPointGroup();
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
