#include "mainForm.h"
#include "file.h"
#include "Resource.h"
#include <ShlObj.h>
#include "utils.h"

using namespace std::literals;

#define TIMER_PROCESS 501

INT_PTR CALLBACK MainForm::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

bool MainForm::Create(LPCWSTR lpszClassName, LPCWSTR lpWindowName)
{
	config.load();
	return WForm::Create(lpszClassName, 0, lpWindowName, WS_OVERLAPPEDWINDOW, config.positionX, config.positionY,
		config.sizeX, config.sizeY);
}

LRESULT MainForm::OnCreate()
{
	DWORD style = WS_BORDER | WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT | SS_NOTIFY | ES_AUTOHSCROLL;
	searchBox.Create(utils::str2wstr(config.currentSearch).c_str(), style, 0, 0, 0, 100, 20, Handle, ID_SEARCHBOX);

	style = WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT | BS_DEFPUSHBUTTON;
	searchBtn.Create(L"Search", style, 0, 100, 0, 80, 20, Handle, ID_SEARCHBTN);

	style = WS_CHILD | WS_VISIBLE | WS_TABSTOP | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_NOCOLUMNHEADER | LVS_SINGLESEL;
	DWORD exStyle = LVS_EX_FULLROWSELECT | LVS_EX_COLUMNOVERFLOW | LVS_EX_DOUBLEBUFFER | LVS_EX_BORDERSELECT;
	searchResultsLv.Create(style, exStyle, 0, 20, 100, 100, Handle, ID_SEARCHRESULTS);

	LVCOLUMNW lvc = {};
	lvc.mask = LVCF_TEXT | LVCF_FMT;
	lvc.fmt = LVCFMT_CENTER;
	searchResultsLv.InsertColumn(0, &lvc);
	lvc.fmt = LVCFMT_LEFT;
	searchResultsLv.InsertColumn(1, &lvc);
	lvc.fmt = LVCFMT_CENTER;
	searchResultsLv.InsertColumn(2, &lvc);
	lvc.fmt = LVCFMT_RIGHT;
	searchResultsLv.InsertColumn(3, &lvc);

	hMenu = GetMenu(Handle);

	ForceVisibleDisplay();
	LoadRomdbs();
	UpdateSystemsMenu();
	return 0;
}

LRESULT MainForm::OnCommand(int wNotifyCode, int ControlID, HWND hWndControl)
{
	// Parse the menu selections:
	switch (ControlID)
	{
	case IDM_OPENCONFIGURATIONFILE:
		ShellExecuteW(0, 0, config.configPath.wstring().c_str(), 0, 0, SW_SHOW);
		break;
	case IDM_RELOADCONFIGURATION:
		ReloadConfig();
		break;
	case IDM_ABOUT:
		DialogBoxW(Instance, MAKEINTRESOURCE(IDD_ABOUTBOX), Handle, About);
		break;
	case IDM_EXIT:
		DestroyWindow(Handle);
		break;
	case IDM_DELETEFILEONCLOSE: {
		config.deleteFileOnClose = !config.deleteFileOnClose;
		CheckMenuItem(hMenu, IDM_DELETEFILEONCLOSE, config.deleteFileOnClose ? MF_CHECKED : MF_UNCHECKED);
		break;
	}
	case IDM_INCLUDEMEDIAINSEARCH: {
		config.includeMedia = !config.includeMedia;
		CheckMenuItem(hMenu, IDM_INCLUDEMEDIAINSEARCH, config.includeMedia ? MF_CHECKED : MF_UNCHECKED);
		break;
	}
	case IDM_ALLSYSTEMS: {
		config.allSystems = !config.allSystems;
		CheckMenuItem(hMenu, IDM_ALLSYSTEMS, config.allSystems ? MF_CHECKED : MF_UNCHECKED);
		break;
	}
	case ID_OPENROM:
		OpenFile((int)((size_t)hWndControl));
		break;
	case IDOK: {
		if (searchResultsLv.Handle == GetFocus())
		{
			int idx = searchResultsLv.GetHotItem();
			if (idx != -1)
				OpenFile(idx);
			break;
		}
	}
	case ID_SEARCHROM:
	case ID_SEARCHBTN:
		SearchMedia(utils::wstr2str(searchBox.GetText()));
		break;
	default: {
		if (ControlID >= 3000 && ControlID < 3100)
		{
			size_t idx = ControlID - 3000;
			if (idx < config.systems.size())
			{
				config.systems[idx].active = !config.systems[idx].active;
				CheckMenuItem(hMenu, ControlID, config.systems[idx].active ? MF_CHECKED : MF_UNCHECKED);
			}
			break;
		}
		return DefProc();
	}
	}
	return 0;
}

LRESULT MainForm::OnDestroy()
{
	RECT rc;
	GetPos(&rc);
	config.positionX = rc.left;
	config.positionY = rc.top;
	config.sizeX = rc.right - rc.left;
	config.sizeY = rc.bottom - rc.top;
	config.currentSearch = utils::wstr2str(searchBox.GetText());
	config.save();
	PostQuitMessage(0);
	return 0;
}

LRESULT MainForm::OnPaint()
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(Handle, &ps);
	FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW));
	EndPaint(Handle, &ps);
	return 0;
}

LRESULT MainForm::OnKeyDown(int VirtKey, int KeyData)
{
	switch (VirtKey)
	{
	case VK_RETURN:
		break;
	default:
		break;
	}
	return 0;
}

LRESULT MainForm::OnTimer(UINT idTimer)
{
	switch (idTimer)
	{
	case TIMER_PROCESS: {
		if (emuProcInfo.hProcess && WaitForSingleObject(emuProcInfo.hProcess, 0) == 0)
		{
			CloseHandle(emuProcInfo.hProcess);
			CloseHandle(emuProcInfo.hThread);
			emuStartInfo = {};
			emuProcInfo = {};
			KillTimer(TIMER_PROCESS);
			RestoreFromTray(1);
			trayText.clear();
			if (config.deleteFileOnClose)
			{
				DeleteFileW(currentFilePath.c_str());
				currentFilePath.clear();
			}
		}
		break;
	}
	default:
		break;
	}
	return 0;
}

LRESULT MainForm::OnSize(UINT nType, int cx, int cy)
{
	if (nType == SIZE_MINIMIZED)
	{
		if (emuProcInfo.hProcess)
			MinimizeToTray(1, LoadIconW(Instance, MAKEINTRESOURCE(IDI_SMALL)), trayText.c_str());
	}
	else
	{
		searchBox.SetPos(0, 0, cx - 80, 20);
		searchBtn.SetPos(cx - 80, 0, 80, 20);
		searchResultsLv.SetPos(0, 20, cx, cy - 20);
		ResizeListView(cx);
	}
	return TRUE;
}

void MainForm::ResizeListView(int cx)
{
	if (!cx)
	{
		RECT rc;
		searchResultsLv.GetPos(&rc);
		cx = rc.right - rc.left;
	}
	searchResultsLv.SetColumnWidth(0, LVSCW_AUTOSIZE);
	searchResultsLv.SetColumnWidth(2, LVSCW_AUTOSIZE);
	searchResultsLv.SetColumnWidth(3, 0);
	int colWidth = cx - searchResultsLv.GetColumnWidth(0) - searchResultsLv.GetColumnWidth(2);
	if (searchResultsLv.HasVerticalScrollbar())
		colWidth -= GetSystemMetrics(SM_CXVSCROLL);
	searchResultsLv.SetColumnWidth(1, colWidth);
}

LRESULT MainForm::OnSizing(UINT edge, LPRECT screenCoords)
{
	auto width = screenCoords->right - screenCoords->left;
	auto height = screenCoords->bottom - screenCoords->top;
	if (width < 320)
		screenCoords->right = screenCoords->left + 320;
	if (height < 240)
		screenCoords->bottom = screenCoords->top + 240;
	return TRUE;
}

LRESULT MainForm::OnTrayIconNotify(DWORD Message, UINT iconID)
{
	switch (Message)
	{
	case WM_LBUTTONDOWN:
		RestoreFromTray(iconID);
		break;
	default:
		break;
	}
	return 0;
}

void MainForm::UpdateSystemsMenu()
{
	CheckMenuItem(hMenu, IDM_DELETEFILEONCLOSE, config.deleteFileOnClose ? MF_CHECKED : MF_UNCHECKED);
	CheckMenuItem(hMenu, IDM_INCLUDEMEDIAINSEARCH, config.includeMedia ? MF_CHECKED : MF_UNCHECKED);
	CheckMenuItem(hMenu, IDM_ALLSYSTEMS, config.allSystems ? MF_CHECKED : MF_UNCHECKED);

	auto hSystemsMenu = GetSubMenu(hMenu, 2);
	while (DeleteMenu(hSystemsMenu, 2, MF_BYPOSITION)) {}

	for (const auto& system : systems)
	{
		auto sysPtr = config.getSystem(system.first);
		if (!sysPtr)
			continue;
		sysPtr->available = true;
		auto menuTitle = utils::str2wstr(system.second) + L" (" + utils::str2wstr(system.first) + L")";
		AppendMenuW(hSystemsMenu, 0, sysPtr->index + 3000, menuTitle.c_str());
		CheckMenuItem(hMenu, sysPtr->index + 3000, sysPtr->active ? MF_CHECKED : MF_UNCHECKED);
	}
}

void MainForm::AddListViewItem(
	int idx, const std::wstring& col1, const std::wstring& col2, const std::wstring& col3, const std::wstring& col4)
{
	LVITEMW lvi = {};
	lvi.mask = LVIF_TEXT;
	lvi.iItem = idx;

	lvi.iSubItem = 0;
	lvi.pszText = (WCHAR*)col1.c_str();
	lvi.cchTextMax = col1.size();
	searchResultsLv.InsertItem(&lvi);

	lvi.iSubItem = 1;
	lvi.pszText = (WCHAR*)col2.c_str();
	lvi.cchTextMax = col2.size();
	searchResultsLv.SetItem(&lvi);

	lvi.iSubItem = 2;
	lvi.pszText = (WCHAR*)col3.c_str();
	lvi.cchTextMax = col3.size();
	searchResultsLv.SetItem(&lvi);

	lvi.iSubItem = 3;
	lvi.pszText = (WCHAR*)col4.c_str();
	lvi.cchTextMax = col4.size();
	searchResultsLv.SetItem(&lvi);
}

void MainForm::ReloadConfig()
{
	config.load();
	searchResults.clear();
	searchResultsLv.DeleteAllItems();
	LoadRomdbs();
	UpdateSystemsMenu();
}

void MainForm::LoadRomdbs()
{
	romdbs.clear();
	systems.clear();
	for (const auto& romdbFile : config.romdbFiles)
	{
		Romdb db;
		if (db.open(romdbFile))
		{
			db.getSystems(systems);
			romdbs.push_back(std::move(db));
		}
	}
}

void MainForm::SearchMedia(const std::string& search)
{
	searchResults.clear();
	for (size_t i = 0; i < romdbs.size(); i++)
	{
		romdbs[i].searchMedia("%" + utils::replaceString(search, " "sv, "%"sv) + "%", i, false, searchResults);
	}
	UpdateSearchResultsLv(config.includeMedia);
}

void MainForm::UpdateSearchResultsLv(bool includeMedia)
{
	searchResultsLv.DeleteAllItems();
	int lvIdx = 0;
	int itemIdx = 1;
	for (size_t i = 0; i < searchResults.size(); i++)
	{
		const auto& sr = searchResults[i];

		if (!config.allSystems && !config.isSystemActive(sr.system.code))
			continue;

		for (size_t j = 0; j < sr.mediaFiles.size(); j++)
		{
			const auto& mf = sr.mediaFiles[j];
			if (includeMedia)
			{
				auto mediaTitle = utils::str2wstr(mf.media.name) + L" (" + utils::str2wstr(sr.system.name) + L")";
				AddListViewItem(lvIdx++, std::to_wstring(itemIdx++), mediaTitle, L"media", {});
			}
			for (size_t k = 0; k < mf.files.size(); k++)
			{
				const auto& f = mf.files[k];
				std::wstring col1 = includeMedia ? L"" : std::to_wstring(itemIdx++);
				auto romId = std::to_wstring(i) + L"," + std::to_wstring(j) + L"," + std::to_wstring(k);
				AddListViewItem(lvIdx++, col1, utils::str2wstr(f.name), L"file", romId);
			}
		}
	}
	ResizeListView(0);
}

void MainForm::OpenFile(int lvItemIdx)
{
	WCHAR lpszText[32];
	searchResultsLv.GetItemText(lvItemIdx, 3, lpszText, 32);
	if (lpszText[0] == 0)
		return;
	auto strIds1 = utils::splitStringIn2(utils::wstr2str(lpszText), ',');
	auto strIds2 = utils::splitStringIn2(strIds1.second, ',');
	auto srId = (int)std::strtol(strIds1.first.c_str(), nullptr, 10);
	auto mediaId = (int)std::strtol(strIds2.first.c_str(), nullptr, 10);
	auto fileId = (int)std::strtol(strIds2.second.c_str(), nullptr, 10);
	RunRom(srId, mediaId, fileId);
}

void MainForm::RunRom(int srId, int mediaId, int fileId)
{
	if (emuProcInfo.hProcess)
	{
		MessageBoxW(Handle, L"Another file is open.", 0, MB_ICONWARNING);
		return;
	}
	if (srId >= 0 && (size_t)srId < searchResults.size())
	{
		const auto& smf = searchResults[srId];
		if (mediaId >= 0 && (size_t)mediaId < smf.mediaFiles.size())
		{
			const auto& mediaFiles = searchResults[srId].mediaFiles[mediaId];
			if (fileId >= 0 && (size_t)fileId < mediaFiles.files.size())
			{
				const auto& file = mediaFiles.files[fileId];

				auto system = config.getSystem(searchResults[srId].system.code);
				if (!system)
					return;

				auto emuPath = std::filesystem::path(system->emulator);
				if (!std::filesystem::exists(emuPath) || std::filesystem::is_directory(emuPath))
					return;

				auto romPath = std::filesystem::path(system->romPath);
				if (!std::filesystem::exists(romPath) || !std::filesystem::is_directory(romPath))
					return;

				{
					auto fileBytes = romdbs[smf.index].getFile(file.id);
					romPath /= utils::str2wstr(file.name);
					currentFilePath = romPath.wstring();
					file::writeBytes(currentFilePath, fileBytes.data(), fileBytes.size());
				}

				auto argsStr = utils::str2wstr(system->args);
				auto filePathArg = L"\"" + currentFilePath + L"\"";
				if (argsStr.find(L"%file%") != std::wstring::npos)
					argsStr = utils::replaceString(argsStr, L"%file%"sv, std::wstring_view(filePathArg));
				else
					argsStr = argsStr + L" " + filePathArg;

				argsStr = L"\"" + emuPath.wstring() + L"\" " + argsStr;

				emuStartInfo = { sizeof(emuStartInfo) };
				emuProcInfo = {};
				if (CreateProcessW(emuPath.wstring().c_str(), (WCHAR*)argsStr.c_str(), 0, 0, TRUE, 0, 0, 0,
						&emuStartInfo, &emuProcInfo))
				{
					SetTimer(TIMER_PROCESS, 100);
					trayText = L"Running " + utils::str2wstr(file.name);
					MinimizeToTray(1, LoadIconW(Instance, MAKEINTRESOURCE(IDI_SMALL)), trayText.c_str());
				}
			}
		}
	}
}
