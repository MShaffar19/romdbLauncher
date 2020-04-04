#pragma once

#include "wcontrol.h"

class WListView : public WControl
{
private:
	MSG currentMsg{};

	static LRESULT CALLBACK SubclassProc(
		HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

protected:
	virtual LRESULT OnCreate();
	virtual LRESULT OnMouseMove(DWORD fwKeys, int X, int Y);
	virtual LRESULT OnMouseWheel(DWORD fwKeys, int X, int Y);
	virtual LRESULT OnMouseDown(DWORD fwKeys, int X, int Y);
	virtual LRESULT OnMouseUp(DWORD fwKeys, int X, int Y);
	virtual LRESULT OnKeyDown(int VirtKey, int KeyData);
	virtual LRESULT OnKeyUp(int VirtKey, int KeyData);
	virtual LRESULT OnDblClick(DWORD fwKeys, int X, int Y);
	virtual LRESULT OnDestroy();
	virtual LRESULT OnCommand(int wNotifyCode, int ControlID, HWND hWndControl);
	virtual LRESULT OnPaint();
	virtual LRESULT OnHScroll(DWORD ScrollbarID, int nScrollCode, int nPos, HWND scHandle);
	virtual LRESULT OnVScroll(DWORD ScrollbarID, int nScrollCode, int nPos, HWND scHandle);
	virtual LRESULT OnContextMenu(int X, int Y, HWND Handle);
	virtual LRESULT OnSize(UINT nType, int cx, int cy);
	virtual LRESULT OnSizing(UINT edge, LPRECT screenCoords);
	virtual LRESULT OnMove(int cx, int cy);

	LRESULT DefProc();

public:
	~WListView();

	BOOL Create(DWORD style, DWORD exStyle, int x, int y, int width, int height, HWND hWndParent, UINT hMenu);

	COLORREF GetBkColor() const;
	BOOL SetBkColor(COLORREF cr);
	UINT GetCallbackMask() const;
	BOOL SetCallbackMask(UINT nMask);
	HWND GetHeader() const;
	HIMAGELIST GetImageList(int nImageList) const;
	HIMAGELIST SetImageList(HIMAGELIST hImageList, int nImageList);
	BOOL GetItem(LPLVITEM pItem) const;
	BOOL SetItem(const LPLVITEM pItem);
	int GetItemCount() const;
	void GetItemText(int nItem, int nSubItem, LPTSTR lpszText, int nLen) const;
	void SetItemText(int nItem, int nSubItem, LPTSTR lpszText);
	HWND GetToolTips() const;
	HWND SetToolTips(HWND hTip);
	int InsertItem(const LVITEM* pItem);
	BOOL DeleteItem(int nItem);
	BOOL DeleteAllItems();
	int GetNextItem(int nItem, int nFlags) const;
	int FindItem(int nStart, LVFINDINFO* pFindInfo) const;
	int HitTest(LPLVHITTESTINFO pHitTestInfo) const;
	void SetItemPosition(int nItem, POINT pt);
	BOOL GetItemPosition(int nItem, LPPOINT lpPoint) const;
	int GetStringWidth(LPCTSTR lpsz) const;
	BOOL EnsureVisible(int nItem, BOOL bPartialOK);
	BOOL Scroll(SIZE size);
	BOOL RedrawItems(int nFirst, int nLast);
	BOOL Arrange(UINT nCode);
	HWND EditLabel(int nItem);
	HWND GetEditControl() const;
	BOOL GetColumn(int nCol, LVCOLUMN* pColumn) const;
	BOOL SetColumn(int nCol, const LPLVCOLUMN pColumn);
	int InsertColumn(int nCol, const LPLVCOLUMN pColumn);
	BOOL DeleteColumn(int nCol);
	int GetColumnWidth(int nCol) const;
	BOOL SetColumnWidth(int nCol, int cx);
	BOOL GetViewRect(LPRECT lpRect) const;
	COLORREF GetInsertMarkColor() const;
	BOOL SetInsertMarkColor(COLORREF cr);
	COLORREF GetOutlineColor() const;
	BOOL SetOutlineColor(COLORREF cr);
	COLORREF GetTextColor() const;
	BOOL SetTextColor(COLORREF cr);
	COLORREF GetTextBkColor() const;
	BOOL SetTextBkColor(COLORREF cr);
	int GetTopIndex() const;
	int GetCountPerPage() const;
	BOOL GetOrigin(LPPOINT lpPoint) const;
	BOOL Update(int nItem);
	UINT GetItemRect(int nItem, LPRECT lpRect, UINT nCode) const;
	void SetItemState(int nItem, UINT nState, UINT nMask);
	UINT GetItemState(int nItem, UINT nMask) const;
	void SetItemCount(int nItems);
	BOOL SortItems(PFNLVCOMPARE pfnCompare, DWORD_PTR dwData);
	BOOL SortItemsEx(PFNLVCOMPARE pfnCompare, DWORD_PTR dwData);
	UINT GetSelectedCount() const;
	BOOL GetItemSpacing(BOOL fSmall, int* pnHorzSpacing, int* pnVertSpacing) const;
	DWORD SetExtendedStyle(DWORD dwNewStyle);
	HCURSOR SetHotCursor(HCURSOR hc);
	int SetHotItem(int iIndex);
	void SetWorkAreas(int nWorkAreas, LPRECT lpRect);
	int SubItemHitTest(LPLVHITTESTINFO pInfo);
	int SubItemHitTestEx(LPLVHITTESTINFO pInfo);
	HCURSOR GetHotCursor() const;
	int GetHotItem() const;
	DWORD GetExtendedStyle() const;
	DWORD ApproximateViewRect(SIZE sz, int iCount) const;
	BOOL GetBkImage(LPLVBKIMAGE plvbkImage) const;
	DWORD GetHoverTime() const;
	void GetWorkAreas(int nWorkAreas, LPRECT prc) const;
	BOOL SetBkImage(LPLVBKIMAGE plvbkImage);
	DWORD SetHoverTime(DWORD dwHoverTime);
	UINT GetNumberOfWorkAreas() const;
	int SetSelectionMark(int iIndex);
	int GetSelectionMark() const;
	BOOL HasVerticalScrollbar() const;
	int GetVerticalScrollbarWidth() const;
};
