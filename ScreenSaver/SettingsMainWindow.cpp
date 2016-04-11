
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <sstream>
#include "TrayIconManagment.h"

#define BTN_PLUS  100
#define BTN_EQUAL 101

// Global variables

const int WINDOW_INIT_WIDTH = 400;
const int WINDOW_INIT_HEIGHT = 400;
TrayIconManagment *tray;

// The main window class name.
static TCHAR szWindowClass[] = _T("win32app");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("The Game Of Life Screensaver - Settings");

HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void makeButtons(HWND hwnd);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	hInst = hInstance;
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		WINDOW_INIT_WIDTH, WINDOW_INIT_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	tray = new TrayIconManagment(hWnd);

	if (!hWnd) {
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	// The parameters to ShowWindow explained:
	// hWnd: the value returned from CreateWindow
	// nCmdShow: the fourth parameter from WinMain
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, World!");
	LRESULT tmp;
	switch (message) {
	case WM_CLOSE:
		ShowWindow(hWnd, SW_HIDE);
		return DefWindowProc(hWnd, message, wParam, lParam); // TODO temporary
		break;
	case WM_CREATE:
		makeButtons(hWnd);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps); {
			TextOut(hdc,
				50, 50,
				greeting, _tcslen(greeting));
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		tray->remove();
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch (HIWORD(wParam)) {
		case BN_CLICKED:
			// see which button was clicked
			if (LOWORD(wParam) == BTN_PLUS) {
				MessageBox(hWnd, _T("hPlus was clicked"), "OK", MB_OK);
			}
			break;
		}
		break;
	case CMSG_TRAY1:
		if (wParam == ID_TRAY1) {
			if (lParam == WM_LBUTTONDOWN) {
				if (IsWindowVisible(hWnd)) {
					ShowWindow(hWnd, SW_HIDE);
					
				}
				else {
					ShowWindow(hWnd, SW_RESTORE);
				}
			}
			else if (lParam == WM_RBUTTONDOWN) {
				tray->createMenu();
			}
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}

void makeButtons(HWND hwnd) {
	CreateWindowEx(0, _T("BUTTON"), _T("+"), WS_CHILD | WS_VISIBLE, 130, 240, 35, 30, hwnd, (HMENU)BTN_PLUS, GetModuleHandle(NULL), NULL);
	CreateWindowEx(0, _T("BUTTON"), _T("="), WS_CHILD | WS_VISIBLE, 170, 205, 65, 65, hwnd, (HMENU)BTN_EQUAL, GetModuleHandle(NULL), NULL);
}