#include "searchResultsLv.h"
#include "Resource.h"

LRESULT SearchResultsLv::OnDblClick(DWORD fwKeys, int X, int Y)
{
	LVHITTESTINFO hti = {};
	hti.pt.x = X;
	hti.pt.y = Y;
	int idx = HitTest(&hti);
	if (idx != -1)
	{
		SendMessageW(GetParent(Handle), WM_COMMAND, ID_OPENROM, idx);
	}
	return 0;
}
