// Framework.cpp : �w�q���ε{�����i�J�I�C
//

#include "Framework.h"
#include "Game.h"
#include "Config.h"
#include "Direct2D.h"
#include <Windowsx.h>

#define MAX_LOADSTRING 100
namespace {
	// �����ܼ�: 
	HINSTANCE hInst;                                // �ثe�������
	WCHAR szTitle[MAX_LOADSTRING];                  // ���D�C��r
	WCHAR szWindowClass[MAX_LOADSTRING];            // �D�������O�W��
}
// �o�ӵ{���X�Ҳդ��ҥ]�t���禡���V�e�ŧi: 
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

	// TODO: �b���m�J�{���X�C
	/**********************************************************************
	*                                                                     *
	*                                                                     *
	*                                                                     *
	*                                                                     *
	***********************************************************************/
	//Game::Instance()->Test();
	//Game::Instance()->Test();
	//Game::Instance()->Test();

	// ��l�ƥ���r��
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_FRAMEWORK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// �������ε{����l�]�w: 
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
//  �禡: MyRegisterClass()
//
//  �γ~: ���U�������O�C
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
//   �禡: InitInstance(HINSTANCE, int)
//
//   �γ~: �x�s������鱱��N�X�åB�إߥD����
//
//   ����: 
//
//        �b�o�Ө禡���A�ڭ̷|�N������鱱��N�X�x�s�b�����ܼƤ��A
//        �åB�إߩM��ܥD�{�������C
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // �N������鱱��N�X�x�s�b�����ܼƤ�

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
//  �禡: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �γ~:     �B�z�D�������T���C
//
//  WM_COMMAND  - �B�z���ε{���\���
//  WM_PAINT    - ø�s�D����
//  WM_DESTROY  - ��ܵ����T���M���^
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
		// ��R�\���������: 
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
		//Game�n��Direct�MAudio(�٨S��)������A�]�����J�O�L�̰����A�ҥH�]�|�s�L������A�YDirect�MAudio��release�A����Game�hcall�N�|error
		KillTimer(hWnd, 1);
		Game::Instance()->Release();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// [����] ������T���B�z�`���C
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

//�����D������A���న�W��Initial�ҥH��timer delay�AwicFactory�|�ؤ��_�ӡA����A���]
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