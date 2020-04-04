#pragma once

#include "wcontrol.h"

class WTextBox : public WControl
{
private:
	MSG currentMsg{};

	static LRESULT CALLBACK SubclassProc(
		HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

protected:
	virtual LRESULT OnKeyDown(int VirtKey, int KeyData);

	LRESULT DefProc();

public:
	~WTextBox();
	BOOL Create(LPCWSTR text, int x, int y, int width, int height, HWND hWndParent, UINT hMenu);
	BOOL Create(
		LPCWSTR text, DWORD style, DWORD exStyle, int x, int y, int width, int height, HWND hWndParent, UINT hMenu);
};
