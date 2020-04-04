#include "wtextbox.h"

WTextBox::~WTextBox()
{
	if (Handle)
	{
		RemoveWindowSubclass(Handle, WTextBox::SubclassProc, 0);
		DestroyWindow(Handle);
	}
}

BOOL WTextBox::Create(LPCWSTR text, int x, int y, int width, int height, HWND hWndParent, UINT hMenu)
{
	DWORD style = WS_BORDER | WS_CHILD | WS_VISIBLE | ES_LEFT | SS_NOTIFY;
	return Create(text, style, 0, x, y, width, height, hWndParent, hMenu);
}

BOOL WTextBox::Create(
	LPCWSTR text, DWORD style, DWORD exStyle, int x, int y, int width, int height, HWND hWndParent, UINT hMenu)
{
	Handle =
		CreateWindowExW(exStyle, WC_EDIT, text, style, x, y, width, height, hWndParent, (HMENU)hMenu, Instance, NULL);
	if (Handle)
	{
		SetWindowSubclass(Handle, WTextBox::SubclassProc, 0, (DWORD_PTR)this);
		return TRUE;
	}
	return FALSE;
}

LRESULT CALLBACK WTextBox::SubclassProc(
	HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	WTextBox* control = (WTextBox*)dwRefData;

	control->currentMsg.hwnd = hWnd;
	control->currentMsg.message = uMsg;
	control->currentMsg.wParam = wParam;
	control->currentMsg.lParam = lParam;

	switch (uMsg)
	{
	case WM_KEYDOWN:
		return control->OnKeyDown((int)wParam, (int)lParam);
	default:
		break;
	}
	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

LRESULT WTextBox::OnKeyDown(int VirtKey, int KeyData)
{
	UNREFERENCED_PARAMETER(VirtKey);
	UNREFERENCED_PARAMETER(KeyData);
	return DefProc();
}

LRESULT WTextBox::DefProc()
{
	return DefSubclassProc(currentMsg.hwnd, currentMsg.message, currentMsg.wParam, currentMsg.lParam);
}
