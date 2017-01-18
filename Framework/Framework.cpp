// Framework.cpp : 定義應用程式的進入點。
//

#include "Framework.h"
#include "Game.h"
#include "Config.h"
#include "Direct2D.h"
#include <Windowsx.h>

#define MAX_LOADSTRING 100
namespace {
	// 全域變數: 
	HINSTANCE hInst;                                // 目前執行個體
	WCHAR szTitle[MAX_LOADSTRING];                  // 標題列文字
	WCHAR szWindowClass[MAX_LOADSTRING];            // 主視窗類別名稱
}
// 這個程式碼模組中所包含之函式的向前宣告: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void CALLBACK DelayTimer(HWND, UINT, UINT, DWORD);
void CALLBACK FixedUpdated(HWND, UINT, UINT, DWORD);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 在此置入程式碼。
	/**********************************************************************
	*                                                                     *
	*                                                                     *
	*                                                                     *
	*                                                                     *
	***********************************************************************/
	//Game::Instance()->Test();
	//Game::Instance()->Test();
	//Game::Instance()->Test();

	// 初始化全域字串
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_FRAMEWORK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 執行應用程式初始設定: 
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FRAMEWORK));

	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  函式: MyRegisterClass()
//
//  用途: 註冊視窗類別。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FRAMEWORK));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_FRAMEWORK);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   函式: InitInstance(HINSTANCE, int)
//
//   用途: 儲存執行個體控制代碼並且建立主視窗
//
//   註解: 
//
//        在這個函式中，我們會將執行個體控制代碼儲存在全域變數中，
//        並且建立和顯示主程式視窗。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 將執行個體控制代碼儲存在全域變數中

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, nullptr, nullptr, hInstance, nullptr);
	if (!hWnd)
	{
		return FALSE;
	}

	//SetWindowPos(hWnd, HWND_TOP, 0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, SWP_NOMOVE);


	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  函式: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  用途:     處理主視窗的訊息。
//
//  WM_COMMAND  - 處理應用程式功能表
//  WM_PAINT    - 繪製主視窗
//  WM_DESTROY  - 顯示結束訊息然後返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		Game::Instance()->KeyDown((unsigned int)wParam);
		//wchar_t buffer[256];
		//wsprintf(buffer, L"%d", i);
		//MessageBox(hWnd, buffer, buffer, MB_OK);
		break;
	case WM_KEYUP:
		Game::Instance()->KeyUp((unsigned int)wParam);
		//MessageBox(nullptr, (LPCWSTR)lParam, (LPCWSTR)lParam, MB_OK);
		break;
	case WM_MOUSEMOVE:
		Game::Instance()->SetMousePosition(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	case WM_RBUTTONDOWN:
		Game::Instance()->RightMouseDown();
		//MessageBox(nullptr, L"WM_RBUTTONDOWN", L"WM_RBUTTONDOWN", MB_OK);
		break;
	case WM_RBUTTONUP:
		Game::Instance()->RightMouseUp();
		//MessageBox(nullptr, (LPCWSTR)lParam, (LPCWSTR)lParam, MB_OK);
		break;
	case WM_LBUTTONDOWN:
		Game::Instance()->LeftMouseDown();
		//MessageBox(nullptr, (LPCWSTR)lParam, (LPCWSTR)lParam, MB_OK);
		break;
	case WM_LBUTTONUP:
		Game::Instance()->LeftMouseUp();
		//MessageBox(nullptr, (LPCWSTR)lParam, (LPCWSTR)lParam, MB_OK);
		break;
	case WM_MBUTTONDOWN:
		Game::Instance()->MiddleMouseDown();
		break;
	case WM_MBUTTONUP:
		Game::Instance()->MiddleMouseUp();
		break;
	case WM_CREATE:
		Direct2D::Instance()->CreateDirect2dDevice(hWnd);
		SetTimer(hWnd, 0, 16, DelayTimer);
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 剖析功能表選取項目: 
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
		ValidateRect(hWnd, nullptr);
		break;
	case WM_ERASEBKGND:
		break;
	case WM_DESTROY:
		//Game要比Direct和Audio(還沒做)早釋放，因為載入是他們做的，所以也會叫他們釋放，若Direct和Audio先release，那麼Game去call就會error
		KillTimer(hWnd, 1);
		Game::Instance()->Release();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// [關於] 方塊的訊息處理常式。
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

//不知道為什麼，不能馬上最Initial所以用timer delay，wicFactory會建不起來，之後再找原因
void CALLBACK DelayTimer(HWND hWnd, UINT message, UINT timerID, DWORD time)
{
	KillTimer(hWnd, 0);
	Game::Instance()->Initial();
	SetTimer(nullptr, 1, 16, FixedUpdated);
}

void CALLBACK FixedUpdated(HWND hWnd, UINT message, UINT timerID, DWORD time)
{
	//MessageBeep(-1);
	Game::Instance()->FixedUpdate();
}