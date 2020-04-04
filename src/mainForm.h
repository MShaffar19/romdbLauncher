#pragma once

#include "config.h"
#include "romdb.h"
#include "searchResultsLv.h"
#include <vector>
#include "wbutton.h"
#include "wform.h"
#include "wtextbox.h"

class MainForm : public WForm
{
private:
	Config config;
	std::vector<Romdb> romdbs;
	std::vector<std::pair<std::string, std::string>> systems;
	std::vector<SystemMediaFiles> searchResults;

	HMENU hMenu{};
	WTextBox searchBox;
	WButton searchBtn;
	SearchResultsLv searchResultsLv;

	STARTUPINFO emuStartInfo{};
	PROCESS_INFORMATION emuProcInfo{};

	std::wstring currentFilePath;
	std::wstring trayText;

	static INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

	void UpdateSystemsMenu();
	void ResizeListView(int cx);
	void AddListViewItem(int idx, const std::wstring& col1, const std::wstring& col2, const std::wstring& col3,
		const std::wstring& col4);

	void ReloadConfig();
	void LoadRomdbs();
	void SearchMedia(const std::string& search);
	void UpdateSearchResultsLv(bool includeMedia);
	void OpenFile(int lvItemIdx);
	void RunRom(int srId, int mediaId, int fileId);

protected:
	LRESULT OnCreate() override;
	LRESULT OnCommand(int wNotifyCode, int ControlID, HWND hWndControl) override;
	LRESULT OnDestroy() override;
	LRESULT OnPaint() override;
	LRESULT OnKeyDown(int VirtKey, int KeyData) override;
	LRESULT OnTimer(UINT idTimer) override;
	LRESULT OnSize(UINT nType, int cx, int cy) override;
	LRESULT OnSizing(UINT edge, LPRECT screenCoords) override;
	LRESULT OnTrayIconNotify(DWORD Message, UINT iconID) override;

public:
	bool Create(LPCWSTR lpszClassName, LPCWSTR lpWindowName);
};
