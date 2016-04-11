#pragma once
#include <shlwapi.h>

#define ID_TRAY1		601
#define CMSG_TRAY1		0x8001
#define MENU_SETTINGS	101
#define MENU_QUIT		102
#define IDM_BOLD		12 

class TrayIconManagment {
public:
	TrayIconManagment(HWND hwnd);
	~TrayIconManagment();
	void show(void);
	void remove(void);
	void createMenu(void);


private:
	const LPSTR sTip;
	const LPSTR WTXT_SETTINGS;
	const LPSTR WTXT_QUIT;
	HWND hwnd;
	NOTIFYICONDATA nid;
};

