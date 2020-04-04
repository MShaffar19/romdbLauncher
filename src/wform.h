#pragma once

#include "wcontrol.h"

#define TRAY_ICON_CALLBACKMESSAGE WM_USER + 0x7FFF

class WForm : public WControl
{
private:
	MSG currentMsg{};

public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

protected:
	static WForm* frmInstance;

	virtual BOOL OnMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, DWORD& dwReturn);

	virtual LRESULT OnCreate();
	virtual LRESULT OnMouseMove(DWORD fwKeys, int X, int Y);
	virtual LRESULT OnMouseWheel(DWORD fwKeys, int X, int Y);
	virtual LRESULT OnMouseDown(DWORD fwKeys, int X, int Y);
	virtual LRESULT OnMouseUp(DWORD fwKeys, int X, int Y);
	virtual LRESULT OnKeyDown(int VirtKey, int KeyData);
	virtual LRESULT OnKeyUp(int VirtKey, int KeyData);
	virtual LRESULT OnDeviceChange(UINT Event, DWORD Data);
	virtual LRESULT OnActivate();
	virtual LRESULT OnDeactivate();
	virtual LRESULT OnTrayIconNotify(DWORD Message, UINT iconID);
	virtual LRESULT OnDblClick(DWORD fwKeys, int X, int Y);
	virtual LRESULT OnDestroy();
	virtual LRESULT OnCommand(int wNotifyCode, int ControlID, HWND hWndControl);
	virtual LRESULT OnButtonClick(int ButtonID, void* Sender);
	virtual LRESULT OnPaint();
	virtual LRESULT OnTimer(UINT idTimer);
	virtual LRESULT OnHScroll(DWORD ScrollbarID, int nScrollCode, int nPos, HWND scHandle);
	virtual LRESULT OnVScroll(DWORD ScrollbarID, int nScrollCode, int nPos, HWND scHandle);
	virtual LRESULT OnContextMenu(int X, int Y, HWND Handle);
	virtual LRESULT OnDropFiles(HDROP hDropInfo);
	virtual LRESULT OnSize(UINT nType, int cx, int cy);
	virtual LRESULT OnSizing(UINT edge, LPRECT screenCoords);
	virtual LRESULT OnMove(int cx, int cy);
	virtual LRESULT OnClose();

	virtual void OnFade(BOOL bMax);

	LRESULT DefProc();

	WForm();
	~WForm();

public:
	bool Create(LPCWSTR lpszClassName, DWORD dwExStyle, LPCWSTR lpWindowName, DWORD dwStyle, int x, int y, int width,
		int height, HWND hParent = HWND_DESKTOP);

	BOOL SetTimer(UINT idTimer, UINT uTimeout);
	BOOL KillTimer(UINT idTimer);

	void MinimizeToTray(UINT uID, HICON hIcon, LPCWSTR lpszTip);
	void RestoreFromTray(UINT uID);

	BOOL TaskBarAddIcon(UINT uID, HICON hIcon, LPCWSTR lpszTip);
	BOOL TaskBarDeleteIcon(UINT uID);

	void ForceVisibleDisplay();
};
