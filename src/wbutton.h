#pragma once

#include "wcontrol.h"

class WButton : public WControl
{
public:
	~WButton();
	BOOL Create(LPCWSTR text, int x, int y, int width, int height, HWND hWndParent, UINT hMenu);
	BOOL Create(
		LPCWSTR text, DWORD style, DWORD exStyle, int x, int y, int width, int height, HWND hWndParent, UINT hMenu);

	BOOL SetText(LPCWSTR text);
};
