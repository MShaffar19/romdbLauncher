#pragma once

#include "framework.h"

class WApp
{
private:
	WApp(const WApp& rhs) = delete;
	WApp& operator=(const WApp& rhs) = delete;

public:
	HINSTANCE Instance = nullptr; // instance of module
	LPTSTR CmdLine = nullptr;	  // command line
	int CmdShow = 0;

	WApp();
	WApp(HINSTANCE hInstance, LPTSTR lpszCmdLine, int nCmdShow);

	// run message loop
	int Run();
	int Run(HACCEL hAccelTable);
	int Run(HACCEL hAccelTable, HWND hDialog);

	// terminate message loop
	void Terminate();
};
