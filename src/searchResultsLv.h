#pragma once

#include "wlistview.h"

class SearchResultsLv : public WListView
{
protected:
	LRESULT OnDblClick(DWORD fwKeys, int X, int Y) override;
};
