#include "TrayIconManagment.h"

#define ID_TRAY1   601
#define CMSG_TRAY1 0x8001


TrayIconManagment::TrayIconManagment(HWND hwnd) : sTip("Moja w³asna ikonka") {
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = hwnd;
	nid.uID = ID_TRAY1;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = CMSG_TRAY1;
	nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	lstrcpy(nid.szTip, sTip);

	BOOL r;
	r = Shell_NotifyIcon(NIM_ADD, &nid);
	if (!r) MessageBox(hwnd, "No niestety, z ikonki nici...", "£eeee...", MB_ICONEXCLAMATION);

	// DO OKIENKA
	//case WM_DESTROY:
	//{
	//	NOTIFYICONDATA nid;
	//	nid.cbSize = sizeof(NOTIFYICONDATA);
	//	nid.hWnd = hwnd;
	//	nid.uID = ID_TRAY1;
	//	nid.uFlags = 0;

	//	Shell_NotifyIcon(NIM_DELETE, &nid);

	//	PostQuitMessage(0);
	//}
	//break;
}


TrayIconManagment::~TrayIconManagment() {
}
