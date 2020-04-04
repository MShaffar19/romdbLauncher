#include "wapp.h"
#include "wcontrol.h"

WApp::WApp() { Instance = (HINSTANCE)GetModuleHandleW(NULL); }

WApp::WApp(HINSTANCE hInstance, LPTSTR lpszCmdLine, int nCmdShow)
{
	WControl::Instance = hInstance;
	Instance = hInstance;
	CmdLine = lpszCmdLine;
	CmdShow = nCmdShow;
}

int WApp::Run()
{
	MSG msg;
	while (GetMessageW(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return (int)msg.wParam;
}

int WApp::Run(HACCEL hAccelTable)
{
	MSG msg;
	while (GetMessageW(&msg, nullptr, 0, 0))
	{
		if (!TranslateAcceleratorW(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}
	return (int)msg.wParam;
}

int WApp::Run(HACCEL hAccelTable, HWND hDialog)
{
	MSG msg;
	while (GetMessageW(&msg, nullptr, 0, 0))
	{
		if (!TranslateAcceleratorW(hDialog, hAccelTable, &msg) && !IsDialogMessageW(hDialog, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}
	return (int)msg.wParam;
}

void WApp::Terminate() { PostQuitMessage(0); }
