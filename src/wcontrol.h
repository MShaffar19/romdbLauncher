#pragma once

#include "framework.h"
#include <string>

class WControl
{
private:
	static WCHAR ClassPointer[];

protected:
	static void* GetClassPointer(HWND hWnd);

	void SetClassPointer();
	BOOL SetClassPointer(HWND hWnd, HANDLE handle);
	void RemoveClassPointer();

	WControl() = default;
	~WControl() = default;
	WControl(const WControl& rhs) = delete;
	WControl& operator=(const WControl& rhs) = delete;

public:
	static HINSTANCE Instance;
	HWND Handle{};

	void SetFocus();

	void SetPos(int x, int y, int width, int height, BOOL bRepaint = TRUE);
	void ResizeTo(int width, int height, BOOL bRepaint = TRUE);
	void MoveTo(int x, int y);
	void SetPos(RECT* rcPos, BOOL bRepaint = TRUE);
	void Enable(BOOL bEnable = TRUE);
	void Show(BOOL fShow);
	BOOL ShowWindow(int nCmdShow);
	BOOL Update();
	void Close();
	void Destroy();
	void Minimize();
	void Redraw();

	DWORD SendCommand(HWND hWnd, WORD NotificationCode, WORD Identifier, HWND hWndControl = NULL);

	DWORD SetRedraw(BOOL fRedraw = TRUE);

	BOOL GetPos(RECT* rcPos);
	BOOL GetClientPos(RECT* rcPos);

	std::wstring GetText();
	BOOL SetText(LPCWSTR text);

	BOOL SetWindowPos(HWND hWndInsertAfter, RECT& rcPos, UINT uFlags);
	BOOL SetWindowPos(HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags);
	void AlwaysOnTop(BOOL bOnTop = TRUE);

	BOOL MoveWindow(int x, int y, int width, int height, BOOL bRepaint);

	BOOL MoveWindow(RECT* rcPos, BOOL bRepaint);

	BOOL IsVisible();
	BOOL IsMinimized();

	BOOL _ModifyStyle(int nStyleOffset, DWORD dwRemove, DWORD dwAdd, UINT nFlags);
	BOOL ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);
	BOOL ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);

	void BringToForeground(BOOL fShow);
};
