#pragma once
#include <shlwapi.h>

class TrayIconManagment {
public:
	TrayIconManagment(HWND hwnd);
	~TrayIconManagment();
	NOTIFYICONDATA nid;

private:
	const LPSTR sTip;
};

