#include "wbutton.h"

WButton::~WButton()
{
	if (Handle)
		DestroyWindow(Handle);
}

BOOL WButton::Create(LPCWSTR text, int x, int y, int width, int height, HWND hWndParent, UINT hMenu)
{
	DWORD style = WS_BORDER | WS_CHILD | WS_VISIBLE | ES_LEFT | SS_NOTIFY;
	return Create(text, style, 0, x, y, width, height, hWndParent, hMenu);
}

BOOL WButton::Create(
	LPCWSTR text, DWORD style, DWORD exStyle, int x, int y, int width, int height, HWND hWndParent, UINT hMenu)
{
	Handle =
		CreateWindowExW(exStyle, WC_BUTTON, text, style, x, y, width, height, hWndParent, (HMENU)hMenu, Instance, NULL);
	if (Handle)
		return TRUE;
	return FALSE;
}

BOOL WButton::SetText(LPCWSTR text) { return SetWindowTextW(Handle, text); }
