
/////////////////////////////////////////////////////////////////////////////


// EditTreeCtrlEx.cpp : implementation file
//

#include <vgStableHeaders.h>
#include "vgEditTreeCtrlEx.h"
#include "vgUIController.h"
#include <algorithm>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma warning(4:4503)		// decorated name length exceeded

enum ECmdHandler {
	ID_RENAME = 1,
	ID_DELETE,
	ID_ADD_SIBLING,
	ID_ADD_CHILD,
	ID_ADD_ROOT,
	ID_SORT_LEVEL,
	ID_SORT_LEVELANDBELOW,

	ID_MAX_CMD
};

enum EExCmds {
	ID_SELECT_ALL = 34555,
	ID_SELECT_NONE,

	ID_EX_MAX
};

//---------------------------------------------------------------------------
// helper class for tracking

void CEditTreeTracker::SetupTracker(CEditTreeCtrlEx * pTree, CPoint & pt) {
	//m_pEditTree = pTree;
	//ASSERT(m_pEditTree != 0);
	//// Before we start tracking, we store all selected
	//// items. If the user interupts the tracking, we have to
	//// restore them...
	//list<HTREEITEM> listSel;
	//for(HTREEITEM hItem = pTree->GetFirstSelectedItem(); hItem != 0; hItem = pTree->GetNextSelectedItem(hItem)) {
	//	listSel.push_back(hItem);
	//	pTree->SetItemState(hItem, UINT(~TVIS_SELECTED), UINT(TVIS_SELECTED));
	//}

	//if(!TrackRubberBand(pTree, pt)) {
	//	// Deselect all items selected by the tracker
	//	pTree->ClearSelection();

	//	// Restore previously selected items
	//	for(list<HTREEITEM>::iterator it = listSel.begin(); it != listSel.end(); ++it)
	//		pTree->SetItemState(*it, UINT(TVIS_SELECTED), UINT(TVIS_SELECTED));

	//	// if the user canceled the tracking, it might happen, that the
	//	// rubber band leaves artefacts on the display :-\ 
	//	pTree->Invalidate();
	//}
	//m_pEditTree = 0;
}


void CEditTreeTracker::OnChangedRect(const CRect & rcOld) {
	//ASSERT(m_pEditTree != 0);

	//CRect rc(rcOld);
	//rc.NormalizeRect();

	//CRect rcClient;
	//m_pEditTree->GetClientRect(rcClient);

	//m_pEditTree->SetRedraw(false);

	//bool bFirstItem = true;

	//// Walk the visible items
	//for(HTREEITEM hItem = m_pEditTree->GetFirstVisibleItem(); hItem != 0; hItem = m_pEditTree->GetNextVisibleItem(hItem)) {
	//	CRect rcItem;
	//	m_pEditTree->GetItemRect(hItem, rcItem, true);

	//	if(rcClient.PtInRect(rcItem.TopLeft()) || rcClient.PtInRect(rcItem.BottomRight())) {
	//		// The item is actually (partially) visible in the client area
	//		if(rc.PtInRect(rcItem.TopLeft()) || rc.PtInRect(rcItem.BottomRight())) {
	//			// We have to move the focus to the first item of the
	//			// selction. If we don't do it, the default implementation
	//			// of the CTreeCtrl class will automatically select the
	//			// focused item as soon as we start dragging the selection...
	//			if(bFirstItem) {
	//				m_pEditTree->SelectItem(hItem);
	//				bFirstItem = false;
	//			}
	//			// the item is at least partially inside the tracker's rectangle
	//			m_pEditTree->SetItemState(hItem, UINT(TVIS_SELECTED), UINT(TVIS_SELECTED));
	//		} else {
	//			// The item lies outside the tracker's rectangle
	//			m_pEditTree->SetItemState(hItem, UINT(~TVIS_SELECTED), UINT(TVIS_SELECTED));
	//		}
	//		m_pEditTree->InvalidateRect(rcItem);
	//	}
	//}

	//rc.DeflateRect(1,1);
	//m_pEditTree->InvalidateRect(rc);
	//m_pEditTree->SetRedraw();
}

//---------------------------------------------------------------------------
// CEditTreeCtrlEx

CEditTreeCtrlEx::CEditTreeCtrlEx()
	: m_bOldItemSelected(false)
	, m_bMultiSel(true)
	, m_bOnDrag(false)
{
	// Extend the keymapper with our own methods:

	// Ctrl+A selects all items
	m_Keymap['A'][true][false] = method(&CEditTreeCtrlEx::DoSelectAll);
	m_selectedList.clear();
	m_dragList.clear();
}


CEditTreeCtrlEx::~CEditTreeCtrlEx()
{
	
}


void CEditTreeCtrlEx::ListAddSelectedItem(HTREEITEM hItem)
{
	if (find(m_selectedList.begin(), m_selectedList.end(), hItem) == m_selectedList.end())
	{
		SetItemState(hItem, UINT(TVIS_SELECTED), UINT(TVIS_SELECTED));
		m_selectedList.push_back(hItem);

		TRACE("选择 %s \n", GetItemText(hItem));
	}
}

void CEditTreeCtrlEx::ListRemoveSelectedItem(HTREEITEM hItem)
{
	SetItemState(hItem, UINT(~TVIS_SELECTED), UINT(TVIS_SELECTED));
	m_selectedList.remove(hItem);

	TRACE("取消选择  %s \n", GetItemText(hItem));
}

HTREEITEM CEditTreeCtrlEx::ListGetNextSelectedItem(HTREEITEM hItem)
{
	list<HTREEITEM>::iterator iter = find(m_selectedList.begin(), m_selectedList.end(), hItem);

	if (iter != m_selectedList.end())
	{
		iter ++;
		if (iter != m_selectedList.end())
		{
			return *iter;
		}
	}

	return 0;
}

HTREEITEM CEditTreeCtrlEx::ListGetPrevSelectedItem(HTREEITEM hItem)
{
	list<HTREEITEM>::iterator iter = find(m_selectedList.begin(), m_selectedList.end(), hItem);

	if (iter != m_selectedList.end() && iter != m_selectedList.begin())
	{
		iter --;
		
		return *iter;
	}

	return 0;
}

HTREEITEM CEditTreeCtrlEx::ListGetFirstSelectedItem()
{
	if (! m_selectedList.empty())
		return *m_selectedList.begin();
	return 0;
}

int CEditTreeCtrlEx::ListGetSelectedCount()
{
	return m_selectedList.size();
}

void CEditTreeCtrlEx::ListClearSelection()
{
	while (! m_selectedList.empty())
	{
		SetItemState(m_selectedList.front(), UINT(~TVIS_SELECTED), UINT(TVIS_SELECTED));
		m_selectedList.pop_front();
	}

	TRACE("移除所有选择 \n");
}

int CEditTreeCtrlEx::GetSelectedCount() {
	//int nResult = 0 ;
	//for(HTREEITEM hItem = GetRootItem(); hItem != 0; hItem = GetNextVisibleItem(hItem))
	//	if(GetItemState(hItem, UINT(TVIS_SELECTED)) & TVIS_SELECTED)
	//		++nResult;
	//return nResult;

	//return ListGetSelectedCount();

	return m_dragList.size();
}


HTREEITEM CEditTreeCtrlEx::GetFirstSelectedItem() {
	//for(HTREEITEM hItem = GetRootItem(); hItem; hItem = GetNextVisibleItem(hItem))
	//	if(GetItemState(hItem, UINT(TVIS_SELECTED)) & TVIS_SELECTED)
	//		return hItem;
	//return 0;

	//return ListGetFirstSelectedItem();
	

	if (!m_dragList.empty())
	{
		return m_dragList.front();
	}
	
	return 0;
}


HTREEITEM CEditTreeCtrlEx::GetNextSelectedItem(HTREEITEM hItem) {
	//if(hItem)
	//	for(hItem = GetNextVisibleItem(hItem); hItem; hItem = GetNextVisibleItem(hItem))
	//		if(GetItemState(hItem, UINT(TVIS_SELECTED)) & TVIS_SELECTED)
	//			return hItem;
	//return 0;
	// return ListGetNextSelectedItem(hItem);

	list<HTREEITEM>::iterator iter = find(m_dragList.begin(), m_dragList.end(), hItem);

	if (iter != m_dragList.end())
	{
		iter ++;
		if (iter != m_dragList.end())
		{
			return *iter;
		}
	}

	return 0;
}


HTREEITEM CEditTreeCtrlEx::GetPrevSelectedItem(HTREEITEM hItem) {
	//if(hItem)
	//	for(hItem = GetPrevVisibleItem(hItem); hItem; hItem = GetPrevVisibleItem(hItem))
	//		if(GetItemState(hItem, UINT(TVIS_SELECTED)) & TVIS_SELECTED)
	//			return hItem;
	//return 0;

	//return ListGetPrevSelectedItem(hItem);

	list<HTREEITEM>::iterator iter = find(m_dragList.begin(), m_dragList.end(), hItem);

	if (iter != m_dragList.end() && iter != m_dragList.begin())
	{
		iter --;

		return *iter;
	}

	return 0;
}


void CEditTreeCtrlEx::ClearSelection(HTREEITEM hExcept, HTREEITEM hItem) {
	//if(!hItem)
	//	hItem = GetRootItem();
	//while(hItem) {
	//	if(hItem != hExcept)
	//		SetItemState(hItem, UINT(~TVIS_SELECTED), UINT(TVIS_SELECTED));

	//	if(ItemHasChildren(hItem))
	//		ClearSelection(hExcept, GetChildItem(hItem));
	//	hItem = GetNextSiblingItem(hItem);
	//}
	
	//ListClearSelection();

	m_dragList.clear();
	// 有待测试
	ListClearSelection();
	TRACE("清空DragList....");
}


void CEditTreeCtrlEx::SelectAll() {
	for(HTREEITEM hItem = GetRootItem(); hItem != 0; hItem = GetNextVisibleItem(hItem))
		SetItemState(hItem, UINT(TVIS_SELECTED), UINT(TVIS_SELECTED));
}


void CEditTreeCtrlEx::DeselectItem(HTREEITEM hItem) {
	if(hItem)
		SetItemState(hItem, UINT(~TVIS_SELECTED), UINT(TVIS_SELECTED));
}


void CEditTreeCtrlEx::InvalidateSelectedItems() {
	for(HTREEITEM hItem = GetFirstSelectedItem(); hItem != 0; hItem = GetNextSelectedItem(hItem)) {
		CRect rc;
		if(GetItemRect(hItem, rc, true))
			InvalidateRect(rc);
	}
}


void CEditTreeCtrlEx::SelectItems(HTREEITEM hFrom, HTREEITEM hTo) {
	HTREEITEM hItem = GetRootItem();
	bool bSelect = false;
	while(hItem) {
		if(hItem == hFrom || hItem == hTo)
			bSelect = !bSelect;
		if(bSelect || hItem == hFrom || hItem == hTo)
			SetItemState(hItem, UINT(TVIS_SELECTED), UINT(TVIS_SELECTED));

		hItem = GetNextVisibleItem(hItem);
	}
}


void CEditTreeCtrlEx::GetSelectedItemsWithoutDescendents(list<HTREEITEM> & listSel) {
	for(HTREEITEM hItem = GetFirstSelectedItem(); hItem != 0; hItem = GetNextSelectedItem(hItem)) {
		bool bChild = false;
		for(list<HTREEITEM>::iterator it = listSel.begin(); it != listSel.end(); ++it)
			if(IsAncestor(*it, hItem)) {
				bChild = true;
				break;
			}
		if(!bChild)
			listSel.push_back(hItem);
	}
}


void CEditTreeCtrlEx::DeselectTree(HTREEITEM hItem) {
	while(hItem) {
		SetItemState(hItem, UINT(~TVIS_SELECTED), UINT(TVIS_SELECTED));
		if(ItemHasChildren(hItem))
			DeselectTree(GetChildItem(hItem));
		hItem = GetNextSiblingItem(hItem);
	}
}


bool CEditTreeCtrlEx::DoSelectAll(HTREEITEM) {
	SelectAll();
	return true;
}


CImageList * CEditTreeCtrlEx::CreateDragImageEx() {
	CImageList	*pResultImageList = 0;

	int nNumSelected = GetSelectedCount();

	if(nNumSelected >= 1) {
		HTREEITEM hItem = 0;
		CString strItemText;
		CRect rcItem;
		int nMaxWidth = 0;

		CDC * pDragImageCalcDC = GetDC();
		if(pDragImageCalcDC == NULL)
			return 0;

		CImageList * pImageList = GetImageList(TVSIL_NORMAL);
		if(!pImageList)
			// even a normal CTreeCtrl can't create a drag image without an imagelist set... :-\ 
			return 0;
		int cx,cy;
		ImageList_GetIconSize(*pImageList, &cx, &cy);

		// Calculate the maximum width of the bounding rectangle
		for(hItem = GetFirstSelectedItem(); hItem; hItem = GetNextSelectedItem(hItem)) {
			// Get the item's height and width one by one
			strItemText = GetItemText(hItem);
			rcItem.SetRectEmpty();
			pDragImageCalcDC->DrawText(strItemText, rcItem, DT_CALCRECT);
			if(nMaxWidth < ( rcItem.Width()+cx))
				nMaxWidth = rcItem.Width()+cx;
		}

		// Get the first item's height and width
		hItem = GetFirstSelectedItem();
		strItemText = GetItemText(hItem);
		rcItem.SetRectEmpty();
		pDragImageCalcDC->DrawText(strItemText, rcItem, DT_CALCRECT);
		ReleaseDC(pDragImageCalcDC);

		// Initialize textRect for the first item
		CRect rcText;  // Holds text area of image
		rcText.SetRect(1, 1, nMaxWidth, rcItem.Height());

		// Find the bounding rectangle of the bitmap
		CRect rcBounding; // Holds rectangle bounding area for bitmap
		rcBounding.SetRect(0,0, nMaxWidth+2, (rcItem.Height()+2)*nNumSelected);

		// Create bitmap		
		CDC MemoryDC; // Memory Device Context used to draw the drag image
		CClientDC DraggedNodeDC(this); // To draw drag image
		if(!MemoryDC.CreateCompatibleDC(&DraggedNodeDC))
			return 0;
		CBitmap DraggedNodeBmp; // Instance used for holding  dragged bitmap
		if(!DraggedNodeBmp.CreateCompatibleBitmap(&DraggedNodeDC, rcBounding.Width(), rcBounding.Height()))
			return 0;

		CBitmap * pBitmapOldMemDCBitmap = MemoryDC.SelectObject(&DraggedNodeBmp);
		CFont * pFontOld = MemoryDC.SelectObject(GetFont());

		CBrush brush(RGB(255,255,255));
		MemoryDC.FillRect(&rcBounding,&brush);
		MemoryDC.SetBkColor(RGB(255,255,255));
		MemoryDC.SetBkMode(TRANSPARENT);
		MemoryDC.SetTextColor(RGB(0,0,0));

		// Search through array list
		for(hItem = GetFirstSelectedItem(); hItem; hItem = GetNextSelectedItem(hItem)) {
			int nImg, nSelImg;
			GetItemImage(hItem,nImg,nSelImg);
			HICON hIcon = pImageList->ExtractIcon(nImg);
			int nLeft = rcText.left;
			rcText.left += 3;
			::DrawIconEx(MemoryDC.m_hDC, rcText.left, rcText.top, hIcon, 16, 16, 0, 0, DI_NORMAL);
			rcText.left += cx;
			MemoryDC.DrawText(GetItemText(hItem), rcText, DT_LEFT| DT_SINGLELINE|DT_NOPREFIX);
			rcText.left = nLeft;
			rcText.OffsetRect(0, rcItem.Height()+2);
			DestroyIcon(hIcon);
		}
		MemoryDC.SelectObject(pFontOld);
		MemoryDC.SelectObject(pBitmapOldMemDCBitmap);
		MemoryDC.DeleteDC();

		// Create imagelist
		pResultImageList = new CImageList;
		pResultImageList->Create(rcBounding.Width(), rcBounding.Height(), ILC_COLOR | ILC_MASK, 0, 1);
		pResultImageList->Add(&DraggedNodeBmp, RGB(255, 255,255)); 
	} else if(nNumSelected == 1)
		pResultImageList = CreateDragImage(GetFirstSelectedItem());

	return pResultImageList;
}

//---------------------------------------------------------------------------
// Dragging overrides

bool CEditTreeCtrlEx::CanDropItem(HTREEITEM hDrag, HTREEITEM hDrop, EDropHint) {
	// We have to take care about more than one dragged item
	for(HTREEITEM hItem = GetFirstSelectedItem(); hItem != 0; hItem = GetNextSelectedItem(hItem))
		if(IsAncestor(hItem, hDrop))
			return false;
	return true;
}


void CEditTreeCtrlEx::DragMoveItem(HTREEITEM, HTREEITEM hDrop, EDropHint hint, bool bCopy) {
	list<HTREEITEM> listSel;
	GetSelectedItemsWithoutDescendents(listSel);

	//SetRedraw(false);

	for(list<HTREEITEM>::iterator it = listSel.begin(); it != listSel.end(); ++it)
		CEditTreeCtrl::DragMoveItem(*it, hDrop, hint, bCopy);

	InvalidateSelectedItems();
}


void CEditTreeCtrlEx::DragStart() {

	TRACE("拖拽列表数据： \n");
	m_dragList.clear();

	list<HTREEITEM>::iterator iter = m_selectedList.begin();

	while (iter != m_selectedList.end())
	{
		TRACE("\n %s \n", GetItemText(*iter));
		m_dragList.push_back(*iter);
		iter ++;
	}

	InvalidateSelectedItems();
	
	CEditTreeCtrl::DragStart();

	iter = m_dragList.begin();

	while (iter != m_dragList.end())
	{
		//TRACE("\n %s \n", GetItemText(*iter));
		SetItemState(*iter, UINT(TVIS_SELECTED), UINT(TVIS_SELECTED));
		iter ++;
	}

	InvalidateSelectedItems();
	// UpdateWindow();
}

void CEditTreeCtrlEx::DragEnd()
{
	m_bOnDrag = true;

	if (m_dragList.empty())
	{
		TRACE("We fixed it ! \n");
		m_dragList.push_back(m_pDragData->GetDragItem());
	}

	list<HTREEITEM>::iterator iter = m_dragList.begin();

	while (iter != m_dragList.end())
	{
		TRACE("\n拖拽 %s 完成\n", GetItemText(*iter));
	
		iter ++;
	}

	EDropHint eHint;
	HTREEITEM hDrop = GetDropTarget(eHint);

	TRACE1("Drag to %s \n" , GetItemText(hDrop));

	CEditTreeCtrl::DragEnd();

	m_dragList.clear();

	ListClearSelection();
	
	m_bOnDrag = false;
	vgUIController::GetInstance()->RemoveAllPages();
	TRACE("拖拽结束 \n");
}

void CEditTreeCtrlEx::DragStop() {
	CEditTreeCtrl::DragStop();
	InvalidateSelectedItems();
	UpdateWindow();

	m_dragList.clear();
	ListClearSelection();
}


CDragData * CEditTreeCtrlEx::CreateDragData(HTREEITEM hDragItem, bool bRightDrag) {
	return new CDragDataEx(*this, hDragItem, bRightDrag);
}


//---------------------------------------------------------------------------
// other overrides

bool CEditTreeCtrlEx::CanEditLabel(HTREEITEM hItem) {
	// Don't edit label if multiple items are selected
	return GetSelectedCount() <= 1;
}


bool CEditTreeCtrlEx::CanInsertItem(HTREEITEM hItem) {
	// Don't edit label if multiple items are selected
	return GetSelectedCount() <= 1;
}


bool CEditTreeCtrlEx::DoDeleteItem(HTREEITEM) {
	list<HTREEITEM> listSel;
	GetSelectedItemsWithoutDescendents(listSel);

	for(list<HTREEITEM>::iterator it = listSel.begin(); it != listSel.end(); ++it)
	{
		TRACE("Menu effect %s \n", GetItemText(*it));
		if(!CEditTreeCtrl::DoDeleteItem(*it))
			return false;
		
	}
	
	return true;
}


void CEditTreeCtrlEx::ExtendContextMenu(CMenu & menu) {
	if(IsMultiSelectEnabled()) {
		if(menu.GetMenuItemCount())
			VERIFY(menu.AppendMenu(MF_SEPARATOR));
		VERIFY(menu.AppendMenu(MF_STRING, ID_SELECT_ALL, _T("Select All")));
		VERIFY(menu.AppendMenu(MF_STRING, ID_SELECT_NONE, _T("Select None")));
	}
	// InvalidateSelectedItems();

	list <HTREEITEM>::iterator iter = m_selectedList.begin();

	while (iter != m_selectedList.end())
	{
		TRACE("Menu Selected Item --- %s \n\n", GetItemText(*iter));
		iter ++;
	}
	// TRACE("Error Here \n");
}


//---------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CEditTreeCtrlEx, CEditTreeCtrl)
	//{{AFX_MSG_MAP(CEditTreeCtrlEx)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_NOTIFY_REFLECT(TVN_SELCHANGING, OnSelchanging)
	ON_NOTIFY_REFLECT(NM_KILLFOCUS, OnKillfocus)
	ON_NOTIFY_REFLECT(NM_SETFOCUS, OnSetfocus)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemexpanded)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(ID_SELECT_ALL, ID_EX_MAX-1, OnExCmd)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
#if _MFC_VER >= 0x0420
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomTreeDraw)
#endif
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditTreeCtrlEx message handlers

void CEditTreeCtrlEx::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{

	list <HTREEITEM>::iterator iter = m_selectedList.begin();

	while (iter != m_selectedList.end())
	{
		TRACE("Selected Item --- %s \n\n", GetItemText(*iter));
		SetItemState(*iter, UINT(~TVIS_SELECTED), UINT(TVIS_SELECTED));
		SetItemState(*iter, UINT(TVIS_SELECTED), UINT(TVIS_SELECTED));
		iter ++;
	}
	InvalidateSelectedItems();


	CPoint point;
	GetCursorPos(&point);


	CPoint pt(point);
	ScreenToClient(&pt);
	//ScreenToClient(&point);

	UINT flags;
	HTREEITEM hItem = HitTest(pt, &flags);
	bool bOnItem = (flags & TVHT_ONITEM) != 0;

	CMenu add;
	VERIFY(add.CreatePopupMenu());
	if(bOnItem) {
		if(CanInsertItem(GetParentItem(hItem)))
			VERIFY(add.AppendMenu(MF_STRING, ID_ADD_SIBLING, _T("New Sibling\tINS")));
		if(CanInsertItem(hItem))
			VERIFY(add.AppendMenu(MF_STRING, ID_ADD_CHILD, _T("New Child Item\tCtrl+INS")));
	}
	if(CanInsertItem(0))
		VERIFY(add.AppendMenu(MF_STRING, ID_ADD_ROOT, _T("New Root Item\tShift+INS")));

	CMenu sort;
	VERIFY(sort.CreatePopupMenu());
	VERIFY(sort.AppendMenu(MF_STRING, ID_SORT_LEVEL, _T("Current Level\tCtrl+S")));
	VERIFY(sort.AppendMenu(MF_STRING, ID_SORT_LEVELANDBELOW, _T("Current Level And Below\tCtrl+Shift+S")));

	CMenu menu;
	VERIFY(menu.CreatePopupMenu());
	if(bOnItem) {
		if(CanEditLabel(hItem))
			VERIFY(menu.AppendMenu(MF_STRING, ID_RENAME, _T("Rename\tF2")));
		if(CanDeleteItem(hItem))
			VERIFY(menu.AppendMenu(MF_STRING, ID_DELETE, _T("Delete\tDEL")));
	}
	if(add.GetMenuItemCount() > 0)
		VERIFY(menu.AppendMenu(MF_POPUP, UINT(add.GetSafeHmenu()), _T("Add")));
	if(bOnItem) {
		if(menu.GetMenuItemCount() > 0)
			VERIFY(menu.AppendMenu(MF_SEPARATOR));
		VERIFY(menu.AppendMenu(MF_POPUP, UINT(sort.GetSafeHmenu()), _T("Sort")));
	}

	ExtendContextMenu(menu);

	// maybe the menu is empty...
	if(menu.GetMenuItemCount() > 0)
		menu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);

}

void CEditTreeCtrlEx::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// DisplayContextMenu(point);

}

void CEditTreeCtrlEx::OnExCmd(UINT id) {
	switch(id) {
		case ID_SELECT_ALL:
			DoSelectAll(0);
			break;

		case ID_SELECT_NONE:
			ClearSelection(0);
			break;

		default:
			// New command?
			ASSERT(false);
			break;
	}
}


void CEditTreeCtrlEx::OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult) 
{
	* pResult = 0 ;

	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	HTREEITEM hNew = pNMTreeView->itemNew.hItem;

	if(IsMultiSelectEnabled()) {
		TRACE0(_T("OnSelchanging()\n"));

		HTREEITEM hOld = pNMTreeView->itemOld.hItem;
		UINT & action = pNMTreeView->action;

		bool bCtrl = (::GetKeyState(VK_CONTROL) & 0x8000) != 0;
		bool bShift = (::GetKeyState(VK_SHIFT) & 0x8000) != 0;
		m_bOldItemSelected = hOld && (GetItemState(hOld, UINT(TVIS_SELECTED)) & TVIS_SELECTED);

		if((action == TVC_BYMOUSE && bCtrl) ) {
			// Ctrl+Mouse - if the item was selected before, deselect it
			if(pNMTreeView->itemNew.state & TVIS_SELECTED) {
				SetItemState(hNew, UINT(~TVIS_SELECTED), UINT(TVIS_SELECTED));
				
				// zsc
				// ListAddSelectedItem(hNew);
				ListRemoveSelectedItem(hNew);

				UpdateWindow() ;
				*pResult = 1 ;	// abort change of selection !
			} else if(!(pNMTreeView->itemOld.state & TVIS_SELECTED))
				// The old item is not selected, so make sure OnSelchanged()
				// will not "re-select" it !
				m_bOldItemSelected = false;
		} else if(action == TVC_BYKEYBOARD && bShift) {
			if(pNMTreeView->itemNew.state & TVIS_SELECTED)
				// misuse of the m_bOldItemSelected data member :-)
				// this marks wether the list of selected items expands or
				// collapses (i.e. the user presses shift on one item and
				// then moves first up a few items and then down or vice
				// versa while holding the shift key)
				m_bOldItemSelected = false;
		} else if(action == TVC_UNKNOWN) {
			// Software generated change of selection.
			// The CTreeCtrl implements a strange behavior when beginning
			// a drag operation by clicking an a different item than the
			// default and not releasing the mouse button before starting to drag:
			// First the 'begin drag' operation occurs. The selected item is
			// the old item, so the "CreateDragImage() method returns the image of the
			// old item. Then occur the 'selection changed' events :-\ 
			// We try to correct this behavior here...
			if(m_pDragData) {
				// Yep - that's it. The 'begin drag' event was already fired while the
				// old item was still selected...
				// If the 'new' item still has no selected state, then we have to
				// deselect all the other selected items.
				if(!(pNMTreeView->itemNew.state & TVIS_SELECTED)) {
					if(!bCtrl) {
						ClearSelection(hNew);

						ListClearSelection();
						
						ListAddSelectedItem(hNew);
						m_bOldItemSelected = false;
					}
					// The new item still has not the selected state set.
					// Creating a new drag image might fail if we don't
					// set it now.
					SetItemState(hNew, UINT(TVIS_SELECTED), UINT(TVIS_SELECTED));
					ListAddSelectedItem(hNew);
					
					// The drag image must be changed, too
					m_pDragData->ReleaseDragImage();
					m_pDragData->CreateDragImage();
				}
			}
		}
	} else {
		// single selection only
		ClearSelection(hNew);
		CEditTreeCtrl::OnSelchanging(pNMHDR, pResult);
	}
}


void CEditTreeCtrlEx::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;

	if(IsMultiSelectEnabled()) {
		TRACE0(_T("OnSelchanged()\n"));

		NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

		HTREEITEM hNew = pNMTreeView->itemNew.hItem;
		HTREEITEM hOld = pNMTreeView->itemOld.hItem;
		UINT & action = pNMTreeView->action;

		bool bCtrl = (::GetKeyState(VK_CONTROL) & 0x8000) != 0;
		bool bShift = (::GetKeyState(VK_SHIFT) & 0x8000) != 0;
		
		if (! bCtrl)
		{
			ListClearSelection();
			SetItemState(hNew, UINT(TVIS_SELECTED), UINT(TVIS_SELECTED));
			ListAddSelectedItem(hNew);
		} else {

			ListAddSelectedItem(hNew);
		}

		// make sure the old selection will not disappear if
		// o CTRL or SHIFT is down (mouse)
		// o SHIFT is down (keyboard)

		if((bCtrl && action == TVC_BYMOUSE) || (bShift && action == TVC_BYKEYBOARD)) {
			// Keep selection at old item
			if(hOld && m_bOldItemSelected)
			{
				SetItemState(hOld, UINT(TVIS_SELECTED), UINT(TVIS_SELECTED));

				// zsc

				ListAddSelectedItem(hOld);
			}

		} else if(bShift && action == TVC_BYMOUSE) {
			// select all items between the old and new item inclusive.
			//SelectItems(hOld, hNew);
		} else if(pNMTreeView->action != TVC_UNKNOWN) {
			// NOTE: TVC_UNKNOWN is set, if the programmer changes
			// the selection (no user action). We remove all
			// selctions only in the case of a user action!
			// remove all selections made earlier ...
			//ClearSelection(/* except */ hNew);
		
			//ListRemoveSelectedItem(hNew);

		} else if(pNMTreeView->action == TVC_UNKNOWN && m_bOldItemSelected && hOld){
			
			// Item changed programmatically. Keep old selection
			SetItemState(hOld, UINT(TVIS_SELECTED), UINT(TVIS_SELECTED));
			ListAddSelectedItem(hOld);
		}
	}


	if (m_dragList.size() > 1 || m_selectedList.size() > 1)
		return ;
	
	if (m_bOnDrag)
		return ;

	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	HTREEITEM hSelected = pNMTreeView->itemNew.hItem;

	// TODO: 在此添加控件通知处理程序代码
	// *pResult = 0;
	// ::MessageBox(NULL, "Selected changed", "Info", MB_OK);
	
	vgBasedNode* pNode = (vgBasedNode*)GetItemData(hSelected);

	ASSERT(pNode);

	vgUIController::GetInstance()->SetCurrentSelectedNode(pNode);

	TRACE("设置当前选择节点 \n");

	// 通知vgUIController更新Tab页面
	pNode->AddNodeTabs();

	//vgCore::QuadtreeSceneManager::getSingleton().m_pNodeSelectd = pNode;

	// ::SendMessage(this->GetParent()->m_hWnd,TVN_SELCHANGED,(WPARAM)pNMHDR, (LPARAM)pResult);
}



void CEditTreeCtrlEx::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;

	if(IsMultiSelectEnabled()) {
		CPoint point;
		GetCursorPos(&point);
		ScreenToClient(&point);

		bool bCtrl = (::GetKeyState(VK_CONTROL) & 0x8000) != 0;
		bool bShift = (::GetKeyState(VK_SHIFT) & 0x8000) != 0;
		
		UINT uFlags ;
		HTREEITEM hNew = HitTest( point, &uFlags ) ;
		HTREEITEM hCur = GetSelectedItem() ;

		// Always keep in mind:
		// If the currently clicked item already has the focus (hNew == hCur)
		// then no TVN_SELCHANG* reflection message will be generated. These
		// special cases will be handled here !
		 
		if(bCtrl) {
			if(hNew == hCur && (uFlags & TVHT_ONITEMLABEL)) {
				// CTRL+LeftClick twice on the same item toggles selection.
				if(GetItemState(hCur, UINT(TVIS_SELECTED)) & TVIS_SELECTED)
				{
					SetItemState(hCur, UINT(~TVIS_SELECTED), UINT(TVIS_SELECTED));
					ListRemoveSelectedItem(hCur);
				}
				else
				{
					SetItemState(hCur, UINT(TVIS_SELECTED), UINT(TVIS_SELECTED));
					ListAddSelectedItem(hCur);
				}
				UpdateWindow();
				return;
			}
		} else if(!bCtrl && !bShift && hNew == hCur && (uFlags & TVHT_ONITEMLABEL) && GetSelectedCount() > 1) {
			// special case: if there is more than one item selected and
			// the user clicks at the item that has the focus (hNew == hCur)
			// then nothing happens (i.e. no reflection message will
			// be generated !). So we have to handle this ourself to get
			// the right behaviour (current item keeps selected and all other
			// selections will be removed):
			
			//ClearSelection(hCur);
			ListClearSelection();
			ListAddSelectedItem(hCur);

			UpdateWindow();
			*pResult = 1;
			return;
		}
	}
}


void CEditTreeCtrlEx::OnKillfocus(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(GetSelectedCount() > 1)
		// Ensure the multiple selected items are drawn correctly when loosing
		// the focus
		InvalidateSelectedItems();
	*pResult = 0;
}


void CEditTreeCtrlEx::OnSetfocus(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(GetSelectedCount() > 1)
		// Ensure the multiple selected items are drawn correctly when getting
		// the focus
		InvalidateSelectedItems();
	*pResult = 0;
}


void CEditTreeCtrlEx::OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	*pResult = 0;

	if(pNMTreeView->action == TVE_COLLAPSE) {
		// make sure there are no selected items in collapsed trees
		// otherwise the user might be confused by the behavior of
		// the tree control.
		HTREEITEM hItem = pNMTreeView->itemNew.hItem;
		ASSERT(hItem != 0);
		DeselectTree(GetChildItem(hItem));
	}
}


void CEditTreeCtrlEx::OnLButtonDown(UINT nFlags, CPoint point) 
{
	UINT flags;
	HTREEITEM hItem = HitTest(point, &flags);

	if (m_selectedList.empty() && hItem)
	{
		ListAddSelectedItem(hItem);
	}

	if(IsMultiSelectEnabled() && ((flags & TVHT_ONITEMRIGHT) || (flags & TVHT_NOWHERE))) {
		m_Tracker.SetupTracker(this, point);
	} else
		CEditTreeCtrl::OnLButtonDown(nFlags, point);
}


BOOL CEditTreeCtrlEx::OnEraseBkgnd(CDC* pDC) 
{
	if(m_Tracker.IsTracking())
		return true;	// otherwise the tree control will scratch the rubber band...
	return CEditTreeCtrl::OnEraseBkgnd(pDC);
}


#if _MFC_VER >= 0x0420
void CEditTreeCtrlEx::OnCustomTreeDraw(NMHDR * pNMHDR, LRESULT * pResult) {
	*pResult = CDRF_DODEFAULT;

	if(m_pDragData) {
		// Have to take care on the visual effects when dragging multiple items
		// The normal behavior of a tree control would be to hide the selection.
		// With multiple selection this would be too much confusing...
		LPNMTVCUSTOMDRAW pCDRW = (LPNMTVCUSTOMDRAW) pNMHDR;
		switch( pCDRW->nmcd.dwDrawStage ) {
			case CDDS_PREPAINT:
				*pResult = CDRF_NOTIFYITEMDRAW ;	// ask for item notifications
				break ;
			case CDDS_ITEMPREPAINT:
				{
					HTREEITEM hCur = (HTREEITEM) pCDRW->nmcd.dwItemSpec;
					HTREEITEM hDrop = GetDropHilightItem();
					if(hDrop && hCur != hDrop) {
						for(HTREEITEM hItem = GetFirstSelectedItem(); hItem != 0; hItem = GetNextSelectedItem(hItem))
							if(hItem == hCur) {
								// mark selected items with a different background color
								pCDRW->clrTextBk = ::GetSysColor(COLOR_BTNFACE);
								return;
							}
						}
				}
				break;
			default:
				break;
		}
	}
}
#endif // _MFC_VER
