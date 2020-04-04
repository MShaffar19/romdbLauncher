#include "wlistview.h"

WListView::~WListView()
{
	if (Handle)
	{
		RemoveWindowSubclass(Handle, WListView::SubclassProc, 0);
		DestroyWindow(Handle);
	}
}

BOOL WListView::Create(DWORD style, DWORD exStyle, int x, int y, int width, int height, HWND hWndParent, UINT hMenu)
{
	Handle =
		CreateWindowExW(0, WC_LISTVIEW, NULL, style, x, y, width, height, hWndParent, (HMENU)hMenu, Instance, NULL);
	if (Handle)
	{
		SetExtendedStyle(exStyle);
		SetWindowSubclass(Handle, WListView::SubclassProc, 0, (DWORD_PTR)this);
		return TRUE;
	}
	return FALSE;
}

LRESULT CALLBACK WListView::SubclassProc(
	HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	WListView* control = (WListView*)dwRefData;

	control->currentMsg.hwnd = hWnd;
	control->currentMsg.message = uMsg;
	control->currentMsg.wParam = wParam;
	control->currentMsg.lParam = lParam;

	switch (uMsg)
	{
	case WM_CONTEXTMENU:
		return control->OnContextMenu(LOWORD(lParam), HIWORD(lParam), (HWND)wParam);
	case WM_KEYDOWN:
		return control->OnKeyDown((int)wParam, (int)lParam);
	case WM_KEYUP:
		return control->OnKeyUp((int)wParam, (int)lParam);
	case WM_CREATE:
		return control->OnCreate();
	case WM_PAINT:
		return control->OnPaint();
	case WM_HSCROLL:
		return control->OnHScroll(
			(DWORD)GetWindowLongPtrW((HWND)lParam, GWL_ID), (int)LOWORD(wParam), int HIWORD(wParam), (HWND)lParam);
	case WM_VSCROLL:
		return control->OnVScroll(
			(DWORD)GetWindowLongPtrW((HWND)lParam, GWL_ID), (int)LOWORD(wParam), int HIWORD(wParam), (HWND)lParam);
	case WM_COMMAND:
		return control->OnCommand(HIWORD(wParam), LOWORD(wParam), (HWND)lParam);
	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		return control->OnMouseDown(wParam, LOWORD(lParam), HIWORD(lParam));
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		return control->OnMouseUp(wParam, LOWORD(lParam), HIWORD(lParam));
	case WM_LBUTTONDBLCLK:
	case WM_MBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
		return control->OnDblClick(wParam, LOWORD(lParam), HIWORD(lParam));
	case WM_MOUSEMOVE:
		return control->OnMouseMove(wParam, LOWORD(lParam), HIWORD(lParam));
	case WM_MOUSEWHEEL:
		return control->OnMouseWheel(wParam, LOWORD(lParam), HIWORD(lParam));
	case WM_SIZE:
		return control->OnSize(wParam, LOWORD(lParam), HIWORD(lParam));
	case WM_SIZING:
		return control->OnSizing(wParam, (LPRECT)lParam);
	case WM_MOVE:
		return control->OnMove(LOWORD(lParam), HIWORD(lParam));
	case WM_DESTROY: {
		return control->OnDestroy();
	default:
		break;
	}
	}
	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

LRESULT WListView::OnDblClick(DWORD fwKeys, int X, int Y)
{
	UNREFERENCED_PARAMETER(fwKeys);
	UNREFERENCED_PARAMETER(X);
	UNREFERENCED_PARAMETER(Y);
	return DefProc();
}

LRESULT WListView::OnMouseDown(DWORD fwKeys, int X, int Y)
{
	UNREFERENCED_PARAMETER(fwKeys);
	UNREFERENCED_PARAMETER(X);
	UNREFERENCED_PARAMETER(Y);
	return DefProc();
}

LRESULT WListView::OnMouseUp(DWORD fwKeys, int X, int Y)
{
	UNREFERENCED_PARAMETER(fwKeys);
	UNREFERENCED_PARAMETER(X);
	UNREFERENCED_PARAMETER(Y);
	return DefProc();
}

LRESULT WListView::OnMouseMove(DWORD fwKeys, int X, int Y)
{
	UNREFERENCED_PARAMETER(fwKeys);
	UNREFERENCED_PARAMETER(X);
	UNREFERENCED_PARAMETER(Y);
	return DefProc();
}

LRESULT WListView::OnMouseWheel(DWORD fwKeys, int X, int Y)
{
	UNREFERENCED_PARAMETER(fwKeys);
	UNREFERENCED_PARAMETER(X);
	UNREFERENCED_PARAMETER(Y);
	return DefProc();
}

LRESULT WListView::OnCreate() { return DefProc(); }

LRESULT WListView::OnPaint() { return DefProc(); }

LRESULT WListView::OnHScroll(DWORD ScrollbarID, int nScrollCode, int nPos, HWND scHandle)
{
	UNREFERENCED_PARAMETER(ScrollbarID);
	UNREFERENCED_PARAMETER(nScrollCode);
	UNREFERENCED_PARAMETER(nPos);
	UNREFERENCED_PARAMETER(scHandle);
	return DefProc();
}

LRESULT WListView::OnVScroll(DWORD ScrollbarID, int nScrollCode, int nPos, HWND scHandle)
{
	UNREFERENCED_PARAMETER(ScrollbarID);
	UNREFERENCED_PARAMETER(nScrollCode);
	UNREFERENCED_PARAMETER(nPos);
	UNREFERENCED_PARAMETER(scHandle);
	return DefProc();
}

LRESULT WListView::OnContextMenu(int X, int Y, HWND Handle)
{
	UNREFERENCED_PARAMETER(X);
	UNREFERENCED_PARAMETER(Y);
	UNREFERENCED_PARAMETER(Handle);
	return DefProc();
}

LRESULT WListView::OnSize(UINT nType, int cx, int cy)
{
	UNREFERENCED_PARAMETER(nType);
	UNREFERENCED_PARAMETER(cx);
	UNREFERENCED_PARAMETER(cy);
	return DefProc();
}

LRESULT WListView::OnSizing(UINT edge, LPRECT screenCoords)
{
	UNREFERENCED_PARAMETER(edge);
	UNREFERENCED_PARAMETER(screenCoords);
	return DefProc();
}

LRESULT WListView::OnMove(int cx, int cy)
{
	UNREFERENCED_PARAMETER(cx);
	UNREFERENCED_PARAMETER(cy);
	return DefProc();
}

LRESULT WListView::OnDestroy() { return DefProc(); }

LRESULT WListView::OnCommand(int wNotifyCode, int ControlID, HWND hWndControl)
{
	UNREFERENCED_PARAMETER(wNotifyCode);
	UNREFERENCED_PARAMETER(ControlID);
	UNREFERENCED_PARAMETER(hWndControl);
	return DefProc();
}

LRESULT WListView::OnKeyDown(int VirtKey, int KeyData)
{
	UNREFERENCED_PARAMETER(VirtKey);
	UNREFERENCED_PARAMETER(KeyData);
	return DefProc();
}

LRESULT WListView::OnKeyUp(int VirtKey, int KeyData)
{
	UNREFERENCED_PARAMETER(VirtKey);
	UNREFERENCED_PARAMETER(KeyData);
	return DefProc();
}

LRESULT WListView::DefProc()
{
	return DefSubclassProc(currentMsg.hwnd, currentMsg.message, currentMsg.wParam, currentMsg.lParam);
}

COLORREF WListView::GetBkColor() const { return ListView_GetBkColor(Handle); }

BOOL WListView::SetBkColor(COLORREF cr) { return ListView_SetBkColor(Handle, cr); }

UINT WListView::GetCallbackMask() const { return ListView_GetCallbackMask(Handle); }

BOOL WListView::SetCallbackMask(UINT nMask) { return ListView_SetCallbackMask(Handle, nMask); }

HWND WListView::GetHeader() const { return ListView_GetHeader(Handle); }

HIMAGELIST WListView::GetImageList(int nImageList) const { return ListView_GetImageList(Handle, nImageList); }

HIMAGELIST WListView::SetImageList(HIMAGELIST hImageList, int nImageList)
{
	return ListView_SetImageList(Handle, hImageList, nImageList);
}

BOOL WListView::GetItem(LPLVITEM pItem) const { return ListView_GetItem(Handle, pItem); }

BOOL WListView::SetItem(const LPLVITEM pItem) { return ListView_SetItem(Handle, pItem); }

int WListView::GetItemCount() const { return ListView_GetItemCount(Handle); }

void WListView::GetItemText(int nItem, int nSubItem, LPTSTR lpszText, int nLen) const
{
	ListView_GetItemText(Handle, nItem, nSubItem, lpszText, nLen);
}

void WListView::SetItemText(int nItem, int nSubItem, LPTSTR lpszText)
{
	ListView_SetItemText(Handle, nItem, nSubItem, lpszText);
}

HWND WListView::GetToolTips() const { return ListView_GetToolTips(Handle); }

HWND WListView::SetToolTips(HWND hTip) { return ListView_SetToolTips(Handle, hTip); }

int WListView::InsertItem(const LVITEM* pItem) { return ListView_InsertItem(Handle, pItem); }

BOOL WListView::DeleteItem(int nItem) { return ListView_DeleteItem(Handle, nItem); }

BOOL WListView::DeleteAllItems() { return ListView_DeleteAllItems(Handle); }

int WListView::GetNextItem(int nItem, int nFlags) const { return ListView_GetNextItem(Handle, nItem, nFlags); }

int WListView::FindItem(int nStart, LVFINDINFO* pFindInfo) const
{
	return ListView_FindItem(Handle, nStart, pFindInfo);
}

int WListView::HitTest(LPLVHITTESTINFO pHitTestInfo) const { return ListView_HitTest(Handle, pHitTestInfo); }

void WListView::SetItemPosition(int nItem, POINT pt) { ListView_SetItemPosition32(Handle, nItem, pt.x, pt.y); }

BOOL WListView::GetItemPosition(int nItem, LPPOINT lpPoint) const
{
	return ListView_GetItemPosition(Handle, nItem, lpPoint);
}

int WListView::GetStringWidth(LPCTSTR lpsz) const { return ListView_GetStringWidth(Handle, lpsz); }

BOOL WListView::EnsureVisible(int nItem, BOOL bPartialOK) { return ListView_EnsureVisible(Handle, nItem, bPartialOK); }

BOOL WListView::Scroll(SIZE size) { return ListView_Scroll(Handle, size.cx, size.cy); }

BOOL WListView::RedrawItems(int nFirst, int nLast) { return ListView_RedrawItems(Handle, nFirst, nLast); }

BOOL WListView::Arrange(UINT nCode) { return ListView_Arrange(Handle, nCode); }

HWND WListView::EditLabel(int nItem) { return ListView_EditLabel(Handle, nItem); }

HWND WListView::GetEditControl() const { return ListView_GetEditControl(Handle); }

BOOL WListView::GetColumn(int nCol, LVCOLUMN* pColumn) const { return ListView_GetColumn(Handle, nCol, pColumn); }

BOOL WListView::SetColumn(int nCol, const LPLVCOLUMN pColumn) { return ListView_SetColumn(Handle, nCol, pColumn); }

int WListView::InsertColumn(int nCol, const LPLVCOLUMN pColumn) { return ListView_InsertColumn(Handle, nCol, pColumn); }

BOOL WListView::DeleteColumn(int nCol) { return ListView_DeleteColumn(Handle, nCol); }

int WListView::GetColumnWidth(int nCol) const { return ListView_GetColumnWidth(Handle, nCol); }

BOOL WListView::SetColumnWidth(int nCol, int cx) { return ListView_SetColumnWidth(Handle, nCol, cx); }

BOOL WListView::GetViewRect(LPRECT lpRect) const { return ListView_GetViewRect(Handle, lpRect); }

COLORREF WListView::GetInsertMarkColor() const { return ListView_GetInsertMarkColor(Handle); }

BOOL WListView::SetInsertMarkColor(COLORREF cr) { return ListView_SetInsertMarkColor(Handle, cr); }

COLORREF WListView::GetOutlineColor() const { return ListView_GetOutlineColor(Handle); }

BOOL WListView::SetOutlineColor(COLORREF cr) { return ListView_SetOutlineColor(Handle, cr); }

COLORREF WListView::GetTextColor() const { return ListView_GetTextColor(Handle); }

BOOL WListView::SetTextColor(COLORREF cr) { return ListView_SetTextColor(Handle, cr); }

COLORREF WListView::GetTextBkColor() const { return ListView_GetTextBkColor(Handle); }

BOOL WListView::SetTextBkColor(COLORREF cr) { return ListView_SetTextBkColor(Handle, cr); }

int WListView::GetTopIndex() const { return ListView_GetTopIndex(Handle); }

int WListView::GetCountPerPage() const { return ListView_GetCountPerPage(Handle); }

BOOL WListView::GetOrigin(LPPOINT lpPoint) const { return ListView_GetOrigin(Handle, lpPoint); }

BOOL WListView::Update(int nItem) { return ListView_Update(Handle, nItem); }

UINT WListView::GetItemRect(int nItem, LPRECT lpRect, UINT nCode) const
{
	return ListView_GetItemRect(Handle, nItem, lpRect, nCode);
}

void WListView::SetItemState(int nItem, UINT nState, UINT nMask)
{
	ListView_SetItemState(Handle, nItem, nState, nMask);
}

UINT WListView::GetItemState(int nItem, UINT nMask) const { return ListView_GetItemState(Handle, nItem, nMask); }

void WListView::SetItemCount(int nItems) { ListView_SetItemCount(Handle, nItems); }

BOOL WListView::SortItems(PFNLVCOMPARE pfnCompare, DWORD_PTR dwData)
{
	return ListView_SortItems(Handle, pfnCompare, dwData);
}

BOOL WListView::SortItemsEx(PFNLVCOMPARE pfnCompare, DWORD_PTR dwData)
{
	return ListView_SortItemsEx(Handle, pfnCompare, dwData);
}

UINT WListView::GetSelectedCount() const { return ListView_GetSelectedCount(Handle); }

BOOL WListView::GetItemSpacing(BOOL fSmall, int* pnHorzSpacing, int* pnVertSpacing) const
{
	DWORD dwSpacing = ListView_GetItemSpacing(Handle, fSmall);
	*pnHorzSpacing = (int)LOWORD(dwSpacing);
	*pnVertSpacing = (int)HIWORD(dwSpacing);
	return TRUE;
}

DWORD WListView::SetExtendedStyle(DWORD dwNewStyle) { return ListView_SetExtendedListViewStyle(Handle, dwNewStyle); }

HCURSOR WListView::SetHotCursor(HCURSOR hc) { return ListView_SetHotCursor(Handle, hc); }

int WListView::SetHotItem(int iIndex) { return ListView_SetHotItem(Handle, iIndex); }

void WListView::SetWorkAreas(int nWorkAreas, LPRECT lpRect) { ListView_SetWorkAreas(Handle, nWorkAreas, lpRect); }

int WListView::SubItemHitTest(LPLVHITTESTINFO pInfo) { return ListView_SubItemHitTest(Handle, pInfo); }

int WListView::SubItemHitTestEx(LPLVHITTESTINFO pInfo) { return ListView_SubItemHitTestEx(Handle, pInfo); }

HCURSOR WListView::GetHotCursor() const { return ListView_GetHotCursor(Handle); }

int WListView::GetHotItem() const { return ListView_GetHotItem(Handle); }

DWORD WListView::GetExtendedStyle() const { return ListView_GetExtendedListViewStyle(Handle); }

DWORD WListView::ApproximateViewRect(SIZE sz, int iCount) const
{
	return ListView_ApproximateViewRect(Handle, sz.cx, sz.cy, iCount);
}

BOOL WListView::GetBkImage(LPLVBKIMAGE plvbkImage) const { return ListView_GetBkImage(Handle, plvbkImage); }

DWORD WListView::GetHoverTime() const { return ListView_GetHoverTime(Handle); }

void WListView::GetWorkAreas(int nWorkAreas, LPRECT prc) const { ListView_GetWorkAreas(Handle, nWorkAreas, prc); }

BOOL WListView::SetBkImage(LPLVBKIMAGE plvbkImage) { return ListView_SetBkImage(Handle, plvbkImage); }

DWORD WListView::SetHoverTime(DWORD dwHoverTime) { return ListView_SetHoverTime(Handle, dwHoverTime); }

UINT WListView::GetNumberOfWorkAreas() const
{
	UINT nWorkAreas;
	ListView_GetNumberOfWorkAreas(Handle, &nWorkAreas);
	return nWorkAreas;
}

int WListView::SetSelectionMark(int iIndex) { return ListView_SetSelectionMark(Handle, iIndex); }

int WListView::GetSelectionMark() const { return ListView_GetSelectionMark(Handle); }

BOOL WListView::HasVerticalScrollbar() const
{
	SCROLLBARINFO sbi;
	sbi.cbSize = sizeof(SCROLLBARINFO);
	if (GetScrollBarInfo(Handle, OBJID_VSCROLL, &sbi))
	{
		if (sbi.rgstate[0] == 0)
			return TRUE;
	}
	return FALSE;
}

int WListView::GetVerticalScrollbarWidth() const { return GetSystemMetrics(SM_CXVSCROLL); }
