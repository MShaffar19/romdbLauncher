#include "wcontrol.h"

WCHAR WControl::ClassPointer[] = L"W_CLASS_POINTER";
HINSTANCE WControl::Instance{};

BOOL WControl::SetClassPointer(HWND hWnd, HANDLE handle) { return SetPropW(hWnd, ClassPointer, handle); }

void WControl::AlwaysOnTop(BOOL bOnTop)
{
	if (bOnTop)
		SetWindowPos(HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	else
		SetWindowPos(HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
}

void* WControl::GetClassPointer(HWND hWnd) { return GetProp(hWnd, ClassPointer); }

void WControl::SetPos(int x, int y, int width, int height, BOOL bRepaint)
{
	::MoveWindow(Handle, x, y, width, height, bRepaint);
}

void WControl::SetPos(RECT* rcPos, BOOL bRepaint)
{
	::MoveWindow(Handle, rcPos->left, rcPos->top, rcPos->right, rcPos->bottom, bRepaint);
}

void WControl::Enable(BOOL bEnable) { EnableWindow(Handle, bEnable); }

void WControl::Show(BOOL fShow) { ShowWindow(fShow ? SW_SHOW : SW_HIDE); }

BOOL WControl::ShowWindow(int nCmdShow) { return ::ShowWindow(Handle, nCmdShow); }

BOOL WControl::Update() { return ::UpdateWindow(Handle); }

void WControl::ResizeTo(int width, int height, BOOL bRepaint)
{
	::SetWindowPos(Handle, NULL, 0, 0, width, height, SWP_NOZORDER | SWP_NOMOVE);
	if (bRepaint)
		InvalidateRect(Handle, NULL, FALSE);
}

void WControl::Close() { SendMessage(Handle, WM_CLOSE, 0, 0); }

void WControl::Destroy() { DestroyWindow(Handle); }

void WControl::SetClassPointer() { SetPropW(Handle, ClassPointer, (HANDLE)this); }

void WControl::RemoveClassPointer() { RemovePropW(Handle, ClassPointer); }

void WControl::MoveTo(int x, int y)
{
	::SetWindowPos(Handle, NULL, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
}

void WControl::Minimize() { ShowWindow(SW_MINIMIZE); }

BOOL WControl::IsVisible() { return IsWindowVisible(Handle); }

BOOL WControl::IsMinimized() { return IsIconic(Handle); }

BOOL WControl::GetPos(RECT* rcPos) { return GetWindowRect(Handle, rcPos); }

BOOL WControl::GetClientPos(RECT* rcPos) { return GetClientRect(Handle, rcPos); }

std::wstring WControl::GetText()
{
	std::wstring str;
	auto length = GetWindowTextLengthW(Handle);
	str.reserve(length + 1);
	str.resize(length);
	GetWindowTextW(Handle, const_cast<WCHAR*>(str.c_str()), length + 1);
	return str;
}

BOOL WControl::SetText(LPCWSTR text) { return SetWindowTextW(Handle, text); }

BOOL WControl::SetWindowPos(HWND hWndInsertAfter, RECT& rcPos, UINT uFlags)
{
	return ::SetWindowPos(Handle, hWndInsertAfter, rcPos.left, rcPos.top, rcPos.right, rcPos.bottom, uFlags);
}

BOOL WControl::SetWindowPos(HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags)
{
	return ::SetWindowPos(Handle, hWndInsertAfter, x, y, cx, cy, uFlags);
}

BOOL WControl::MoveWindow(int x, int y, int width, int height, BOOL bRepaint)
{
	return ::MoveWindow(Handle, x, y, width, height, bRepaint);
}

BOOL WControl::MoveWindow(RECT* rcPos, BOOL bRepaint)
{
	return ::MoveWindow(Handle, rcPos->left, rcPos->top, rcPos->right, rcPos->bottom, bRepaint);
}

void WControl::Redraw() { InvalidateRect(Handle, NULL, TRUE); }

void WControl::SetFocus() { ::SetFocus(Handle); }

DWORD WControl::SendCommand(HWND hWnd, WORD NotificationCode, WORD Identifier, HWND hWndControl)
{
	return ::SendMessage(hWnd, WM_COMMAND, MAKEWPARAM(Identifier, NotificationCode), (LPARAM)hWndControl);
}

DWORD WControl::SetRedraw(BOOL fRedraw) { return ::SendMessage(Handle, WM_SETREDRAW, (WPARAM)fRedraw, 0); }

BOOL WControl::_ModifyStyle(int nStyleOffset, DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{
	DWORD dwStyle = ::GetWindowLongW(Handle, nStyleOffset);
	DWORD dwNewStyle = (dwStyle & ~dwRemove) | dwAdd;
	if (dwStyle == dwNewStyle)
		return FALSE;

	::SetWindowLongW(Handle, nStyleOffset, dwNewStyle);
	if (nFlags != 0)
	{
		::SetWindowPos(Handle, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | nFlags);
	}
	return TRUE;
}

BOOL WControl::ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{
	return _ModifyStyle(GWL_STYLE, dwRemove, dwAdd, nFlags);
}

BOOL WControl::ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{
	return _ModifyStyle(GWL_EXSTYLE, dwRemove, dwAdd, nFlags);
}

void WControl::BringToForeground(BOOL fShow)
{
	HWND hForeground = GetForegroundWindow();
	DWORD piForeground;
	DWORD tForeground = GetWindowThreadProcessId(hForeground, &piForeground);
	DWORD piMe;
	DWORD tMe = GetWindowThreadProcessId(Handle, &piMe);

	if (tForeground == tMe)
	{
		SetForegroundWindow(Handle);
	}
	else
	{
		AttachThreadInput(tMe, tForeground, TRUE);
		SetForegroundWindow(Handle);
		AttachThreadInput(tMe, tForeground, FALSE);
	}

	if (!fShow)
		return;

	if (IsIconic(Handle))
	{
		ShowWindow(SW_RESTORE);
	}
	else
	{
		ShowWindow(SW_SHOW);
	}
}
