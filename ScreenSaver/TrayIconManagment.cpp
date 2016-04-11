#include "TrayIconManagment.h"


TrayIconManagment::TrayIconManagment(HWND hwnd) : sTip("The Game Of Life Screensaver"), WTXT_SETTINGS("Settings"), WTXT_QUIT("Quit"){
	this->hwnd = hwnd;
	show();
}


TrayIconManagment::~TrayIconManagment() {
}

void TrayIconManagment::show(void) {
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = hwnd;
	nid.uID = ID_TRAY1;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = CMSG_TRAY1;
	nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//.hIcon = (HICON)LoadImage( NULL, TEXT("green_man.ico"), IMAGE_ICON, 0, 0, LR_LOADFROMFILE  ) ;
	lstrcpy(nid.szTip, sTip);

	BOOL r;
	r = Shell_NotifyIcon(NIM_ADD, &nid);
	//if (!r) {
	//	MessageBox(hwnd, "No niestety, z ikonki nici...", "£eeee...", MB_ICONEXCLAMATION);
	//}
}

void TrayIconManagment::remove(void) {
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = hwnd;
	nid.uID = ID_TRAY1;
	nid.uFlags = 0;

	Shell_NotifyIcon(NIM_DELETE, &nid);
}

void TrayIconManagment::createMenu(void) {
	MENUITEMINFO separatorBtn = { 0 };
	separatorBtn.cbSize = sizeof(MENUITEMINFO);
	separatorBtn.fMask = MIIM_FTYPE;
	separatorBtn.fType = MFT_SEPARATOR;

	HMENU hMenu = CreatePopupMenu();

	if (hMenu) {
		InsertMenu(hMenu, -1, MF_BYPOSITION, MENU_SETTINGS, WTXT_SETTINGS);
		InsertMenuItem(hMenu, -1, FALSE, &separatorBtn);
		InsertMenu(hMenu, -1, MF_BYPOSITION, MENU_QUIT, WTXT_QUIT);
		SetMenuDefaultItem(hMenu, MENU_SETTINGS, FALSE);

		POINT pt;
		GetCursorPos(&pt);
		SetForegroundWindow(hwnd);
		TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hwnd, NULL);
		PostMessage(hwnd, WM_NULL, 0, 0);
		DestroyMenu(hMenu);
	}
}

