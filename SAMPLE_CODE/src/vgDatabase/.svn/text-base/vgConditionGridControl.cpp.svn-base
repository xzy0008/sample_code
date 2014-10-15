#include <vgStableHeaders.h>
#include <vgDatabase/vgConditionGridControl.h>



BEGIN_MESSAGE_MAP(ConditionGridControl, CBCGPGridCtrl)
	ON_WM_CONTEXTMENU()

	ON_COMMAND(ID_DBC_POP_DELETE, OnMenuDelete)

END_MESSAGE_MAP()


void ConditionGridControl::OnContextMenu(CWnd* pWnd, CPoint pos)
{
	// AfxMessageBox("On Context menu");

	CMenu popMenu;

	popMenu.LoadMenu(IDR_DBC_POP);
	popMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pos.x, pos.y, this);
}

void ConditionGridControl::OnMenuDelete()
{
	for (int nIndex =0;nIndex < GetRowCount();nIndex++)
	{
		if (IsRowSelected(nIndex))
		{
			RemoveRow(nIndex);

			return ;
		}
	}
}