#include "mainForm.h"
#include "Resource.h"
#include "wapp.h"

#pragma comment(lib, "comctl32.lib")

#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define MAX_LOADSTRING 100

WCHAR szTitle[MAX_LOADSTRING];		 // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING]; // the main window class name

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	{
		INITCOMMONCONTROLSEX icce;
		icce.dwSize = sizeof(INITCOMMONCONTROLSEX);
		icce.dwICC = ICC_STANDARD_CLASSES;
		if (!InitCommonControlsEx(&icce))
			return FALSE;
	}

	WApp app(hInstance, lpCmdLine, nCmdShow);

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_ROMDBLAUNCHER, szWindowClass, MAX_LOADSTRING);
	{
		WNDCLASSEXW wcex = {};
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WForm::WndProc;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ROMDBLAUNCHER));
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_ROMDBLAUNCHER);
		wcex.lpszClassName = szWindowClass;
		wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
		if (!RegisterClassExW(&wcex))
			return FALSE;
	}

	MainForm form;
	if (!form.Create(szWindowClass, szTitle))
		return FALSE;
	form.ShowWindow(nCmdShow);
	form.Update();

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ROMDBLAUNCHER));
	return app.Run(hAccelTable, form.Handle);
}
