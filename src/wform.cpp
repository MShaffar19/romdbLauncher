#include "wform.h"

WForm* WForm::frmInstance = NULL;

WForm::WForm() { frmInstance = this; }

WForm::~WForm()
{
	if (Handle)
		DestroyWindow(Handle);
	RemoveClassPointer();
}

bool WForm::Create(LPCWSTR lpszClassName, DWORD dwExStyle, LPCWSTR lpWindowName, DWORD dwStyle, int x, int y, int width,
	int height, HWND hParent)
{
	frmInstance = this;
	Handle = CreateWindowExW(
		dwExStyle, lpszClassName, lpWindowName, dwStyle, x, y, width, height, hParent, NULL, Instance, NULL);
	return Handle != nullptr;
}

LRESULT CALLBACK WForm::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	WForm* form = (WForm*)GetClassPointer(hWnd);
	if (form == nullptr)
	{
		form = frmInstance;
	}

	form->currentMsg.hwnd = hWnd;
	form->currentMsg.message = msg;
	form->currentMsg.wParam = wParam;
	form->currentMsg.lParam = lParam;

	DWORD ret;
	if (form->OnMessage(hWnd, msg, wParam, lParam, ret) == TRUE)
		return ret;

	switch (msg)
	{
	case WM_CONTEXTMENU:
		return form->OnContextMenu(LOWORD(lParam), HIWORD(lParam), (HWND)wParam);
	case WM_DEVICECHANGE:
		return form->OnDeviceChange((UINT)wParam, lParam);
	case WM_KEYDOWN:
		return form->OnKeyDown((int)wParam, (int)lParam);
	case WM_KEYUP:
		return form->OnKeyUp((int)wParam, (int)lParam);
	case WM_CANCELMODE: {
		ReleaseCapture();
		return 0;
	}
	case TRAY_ICON_CALLBACKMESSAGE:
		return form->OnTrayIconNotify(lParam, wParam);
	case WM_TIMER:
		return form->OnTimer(wParam);
	case WM_SETFOCUS:
		return form->OnActivate();
	case WM_KILLFOCUS:
		return form->OnDeactivate();
	case WM_CREATE: {
		form->Handle = hWnd;
		auto ret = form->OnCreate();
		if (ret >= 0)
		{
			form->SetClassPointer(hWnd, (HANDLE)form);
		}
		return ret;
	}
	case WM_PAINT:
		return form->OnPaint();
	case WM_ERASEBKGND:
		return (LRESULT)1; // Say we handled it.
	case WM_HSCROLL:
		return form->OnHScroll(
			(DWORD)GetWindowLongPtrW((HWND)lParam, GWL_ID), (int)LOWORD(wParam), int HIWORD(wParam), (HWND)lParam);
	case WM_VSCROLL:
		return form->OnVScroll(
			(DWORD)GetWindowLongPtrW((HWND)lParam, GWL_ID), (int)LOWORD(wParam), int HIWORD(wParam), (HWND)lParam);
	case WM_COMMAND:
		return form->OnCommand(HIWORD(wParam), LOWORD(wParam), (HWND)lParam);
	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		return form->OnMouseDown(wParam, LOWORD(lParam), HIWORD(lParam));
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
		return form->OnMouseUp(wParam, LOWORD(lParam), HIWORD(lParam));
	case WM_RBUTTONUP: {
		DefWindowProc(hWnd, msg, wParam, lParam);
		return form->OnMouseUp(wParam, LOWORD(lParam), HIWORD(lParam));
	}
	case WM_LBUTTONDBLCLK:
	case WM_MBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
		return form->OnDblClick(wParam, LOWORD(lParam), HIWORD(lParam));
	case WM_NCMOUSEMOVE:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	case WM_MOUSEMOVE:
		return form->OnMouseMove(wParam, LOWORD(lParam), HIWORD(lParam));
	case WM_MOUSEWHEEL:
		return form->OnMouseWheel(wParam, LOWORD(lParam), HIWORD(lParam));
	case WM_DROPFILES:
		return form->OnDropFiles((HDROP)wParam);
	case WM_SIZE:
		return form->OnSize(wParam, LOWORD(lParam), HIWORD(lParam));
	case WM_SIZING:
		return form->OnSizing(wParam, (LPRECT)lParam);
	case WM_MOVE:
		return form->OnMove(LOWORD(lParam), HIWORD(lParam));
	case WM_CLOSE:
		return form->OnClose();
	case WM_DESTROY: {
		form->RemoveClassPointer();
		return form->OnDestroy();
	}
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}

LRESULT WForm::OnDblClick(DWORD fwKeys, int X, int Y)
{
	UNREFERENCED_PARAMETER(fwKeys);
	UNREFERENCED_PARAMETER(X);
	UNREFERENCED_PARAMETER(Y);
	return DefProc();
}

LRESULT WForm::OnMouseDown(DWORD fwKeys, int X, int Y)
{
	UNREFERENCED_PARAMETER(fwKeys);
	UNREFERENCED_PARAMETER(X);
	UNREFERENCED_PARAMETER(Y);
	return DefProc();
}

LRESULT WForm::OnMouseUp(DWORD fwKeys, int X, int Y)
{
	UNREFERENCED_PARAMETER(fwKeys);
	UNREFERENCED_PARAMETER(X);
	UNREFERENCED_PARAMETER(Y);
	return DefProc();
}

LRESULT WForm::OnMouseMove(DWORD fwKeys, int X, int Y)
{
	UNREFERENCED_PARAMETER(fwKeys);
	UNREFERENCED_PARAMETER(X);
	UNREFERENCED_PARAMETER(Y);
	return DefProc();
}

LRESULT WForm::OnMouseWheel(DWORD fwKeys, int X, int Y)
{
	UNREFERENCED_PARAMETER(fwKeys);
	UNREFERENCED_PARAMETER(X);
	UNREFERENCED_PARAMETER(Y);
	return DefProc();
}

LRESULT WForm::OnDropFiles(HDROP hDropInfo)
{
	UNREFERENCED_PARAMETER(hDropInfo);
	return DefProc();
}

LRESULT WForm::OnCreate() { return DefProc(); }

LRESULT WForm::OnPaint() { return DefProc(); }

LRESULT WForm::OnHScroll(DWORD ScrollbarID, int nScrollCode, int nPos, HWND scHandle)
{
	UNREFERENCED_PARAMETER(ScrollbarID);
	UNREFERENCED_PARAMETER(nScrollCode);
	UNREFERENCED_PARAMETER(nPos);
	UNREFERENCED_PARAMETER(scHandle);
	return DefProc();
}

LRESULT WForm::OnVScroll(DWORD ScrollbarID, int nScrollCode, int nPos, HWND scHandle)
{
	UNREFERENCED_PARAMETER(ScrollbarID);
	UNREFERENCED_PARAMETER(nScrollCode);
	UNREFERENCED_PARAMETER(nPos);
	UNREFERENCED_PARAMETER(scHandle);
	return DefProc();
}

LRESULT WForm::OnButtonClick(int ButtonID, void* Sender)
{
	UNREFERENCED_PARAMETER(ButtonID);
	UNREFERENCED_PARAMETER(Sender);
	return DefProc();
}

LRESULT WForm::OnSize(UINT nType, int cx, int cy)
{
	UNREFERENCED_PARAMETER(nType);
	UNREFERENCED_PARAMETER(cx);
	UNREFERENCED_PARAMETER(cy);
	return DefProc();
}

LRESULT WForm::OnSizing(UINT edge, LPRECT screenCoords)
{
	UNREFERENCED_PARAMETER(edge);
	UNREFERENCED_PARAMETER(screenCoords);
	return DefProc();
}

LRESULT WForm::OnMove(int cx, int cy)
{
	UNREFERENCED_PARAMETER(cx);
	UNREFERENCED_PARAMETER(cy);
	return DefProc();
}

LRESULT WForm::OnClose() { return DefProc(); }

LRESULT WForm::OnDestroy() { return DefProc(); }

LRESULT WForm::OnTrayIconNotify(DWORD Message, UINT iconID)
{
	UNREFERENCED_PARAMETER(Message);
	UNREFERENCED_PARAMETER(iconID);
	return DefProc();
}

LRESULT WForm::OnTimer(UINT idTimer)
{
	UNREFERENCED_PARAMETER(idTimer);
	return DefProc();
}

BOOL WForm::SetTimer(UINT idTimer, UINT uTimeout) { return ::SetTimer(Handle, idTimer, uTimeout, (TIMERPROC)NULL); }

BOOL WForm::KillTimer(UINT idTimer) { return ::KillTimer(Handle, idTimer); }

LRESULT WForm::OnCommand(int wNotifyCode, int ControlID, HWND hWndControl)
{
	UNREFERENCED_PARAMETER(wNotifyCode);
	UNREFERENCED_PARAMETER(ControlID);
	UNREFERENCED_PARAMETER(hWndControl);
	return DefProc();
}

LRESULT WForm::OnActivate() { return DefProc(); }

LRESULT WForm::OnDeactivate() { return DefProc(); }

LRESULT WForm::OnKeyDown(int VirtKey, int KeyData)
{
	UNREFERENCED_PARAMETER(VirtKey);
	UNREFERENCED_PARAMETER(KeyData);
	return DefProc();
}

LRESULT WForm::OnKeyUp(int VirtKey, int KeyData)
{
	UNREFERENCED_PARAMETER(VirtKey);
	UNREFERENCED_PARAMETER(KeyData);
	return DefProc();
}

LRESULT WForm::OnDeviceChange(UINT Event, DWORD Data)
{
	UNREFERENCED_PARAMETER(Event);
	UNREFERENCED_PARAMETER(Data);
	return DefProc();
}

LRESULT WForm::DefProc()
{
	return DefWindowProcW(currentMsg.hwnd, currentMsg.message, currentMsg.wParam, currentMsg.lParam);
}

void WForm::OnFade(BOOL bMax) { UNREFERENCED_PARAMETER(bMax); }

void WForm::MinimizeToTray(UINT uID, HICON hIcon, LPCWSTR lpszTip)
{
	NOTIFYICONDATAW tnid = {};
	tnid.cbSize = sizeof(NOTIFYICONDATA);
	tnid.hWnd = Handle;
	tnid.uID = uID;
	tnid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	tnid.uCallbackMessage = TRAY_ICON_CALLBACKMESSAGE;
	tnid.hIcon = hIcon;
	if (lpszTip)
		StringCbCopyW(tnid.szTip, sizeof(tnid.szTip), lpszTip);
	Shell_NotifyIconW(NIM_ADD, &tnid);
	Show(FALSE);
}

void WForm::RestoreFromTray(UINT uID)
{
	NOTIFYICONDATAW tnid = {};
	tnid.cbSize = sizeof(NOTIFYICONDATA);
	tnid.hWnd = Handle;
	tnid.uID = uID;
	Shell_NotifyIconW(NIM_DELETE, &tnid);
	Show(TRUE);
}

BOOL WForm::TaskBarAddIcon(UINT uID, HICON hIcon, LPCWSTR lpszTip)
{
	NOTIFYICONDATAW tnid = {};
	tnid.cbSize = sizeof(NOTIFYICONDATAW);
	tnid.hWnd = Handle;
	tnid.uID = uID;
	tnid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	tnid.uCallbackMessage = TRAY_ICON_CALLBACKMESSAGE;
	tnid.hIcon = hIcon;
	if (lpszTip)
		StringCbCopyW(tnid.szTip, sizeof(tnid.szTip), lpszTip);
	return Shell_NotifyIconW(NIM_ADD, &tnid);
}

BOOL WForm::TaskBarDeleteIcon(UINT uID)
{
	NOTIFYICONDATAW tnid = {};
	tnid.cbSize = sizeof(NOTIFYICONDATAW);
	tnid.hWnd = Handle;
	tnid.uID = uID;
	return Shell_NotifyIconW(NIM_DELETE, &tnid);
}

LRESULT WForm::OnContextMenu(int X, int Y, HWND Handle)
{
	UNREFERENCED_PARAMETER(X);
	UNREFERENCED_PARAMETER(Y);
	UNREFERENCED_PARAMETER(Handle);
	return DefProc();
}

BOOL WForm::OnMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, DWORD& dwReturn)
{
	UNREFERENCED_PARAMETER(hwnd);
	UNREFERENCED_PARAMETER(msg);
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
	UNREFERENCED_PARAMETER(dwReturn);
	return FALSE;
}

void WForm::ForceVisibleDisplay()
{
	RECT rect;
	GetWindowRect(Handle, &rect);

	// check if the specified window-rectangle is visible on any display
	if (NULL == MonitorFromRect(&rect, MONITOR_DEFAULTTONULL))
	{
		HMONITOR hMonitor;
		MONITORINFO mi = { sizeof(mi) };

		// find the nearest display to the rectangle
		hMonitor = MonitorFromRect(&rect, MONITOR_DEFAULTTONEAREST);

		GetMonitorInfoW(hMonitor, &mi);

		// center window rectangle
		rect.left = mi.rcWork.left + ((mi.rcWork.right - mi.rcWork.left) - (rect.right - rect.left)) / 2;
		rect.top = mi.rcWork.top + ((mi.rcWork.bottom - mi.rcWork.top) - (rect.bottom - rect.top)) / 2;
		rect.right = 0;
		rect.bottom = 0;

		SetWindowPos(0, rect, SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);
	}
}
