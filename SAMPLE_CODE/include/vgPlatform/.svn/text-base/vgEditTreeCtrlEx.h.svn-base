#if !defined(AFX_EDITTREECTRLEX_H__A2215620_F871_408A_9519_D5A6317EBA5C__INCLUDED_)

/////////////////////////////////////////////////////////////////////////////


#define AFX_EDITTREECTRLEX_H__A2215620_F871_408A_9519_D5A6317EBA5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditTreeCtrlEx.h : header file
//

#include "vgEditTreeCtrl.h"
#include <list>
#include "vgBasedNode.h"
using namespace std;

class CEditTreeCtrlEx;

//---------------------------------------------------------------------------
// helper class for tracking

class CEditTreeTracker : public CRectTracker {
	CEditTreeCtrlEx *		m_pEditTree;

	public:
		CEditTreeTracker()
			: m_pEditTree(0)
		{
		}

	// Attribtes
	public:
		bool	IsTracking() const { return m_pEditTree != 0; }

	// Operations
	public:
		void	SetupTracker(CEditTreeCtrlEx * pTree, CPoint & pt);

	// Overridables
	protected:
		void	OnChangedRect(const CRect & rc);
};

//---------------------------------------------------------------------------
// CEditTreeCtrlEx window

class CEditTreeCtrlEx : public CEditTreeCtrl
{
	protected:
		bool				m_bOldItemSelected;
		CEditTreeTracker	m_Tracker;
		bool				m_bMultiSel;
		
		bool				m_bOnDrag;
		list <HTREEITEM>	m_selectedList;
		list <HTREEITEM>	m_dragList;

		//list <vgBasedNode*>		m_nodeList;
	// Construction
	public:
		CEditTreeCtrlEx();

		//HTREEITEM AddNode(HTREEITEM parent, vgBasedNode* node);
		//HTREEITEM AddNode(vgBasedNode* node);
		//HTREEITEM AddNode(vgBasedNode* parentNode, vgBasedNode* node);

	// Attributes
	public:
		// GetSelectedCount() returns the number of currently selected items.
		int			GetSelectedCount();

		// Note that multi-select is enabled by default.
		// If multi-select is disabled, the user is unable to select more than one
		// item. Programmatically you can select more than one item regardless
		// of this setting! For instance SelectAll() will select all visible items
		// even if multi-select is off.
		// SelectItem(HTREEITEM) behaves different if multi-select is on or off.
		// If multi-select is on, every call to SelectItem() will add the given
		// item to the list of selected items. If multi-selelct is off, SelectItem()
		// behaves as in a normal CTreeCtrl.
		void		EnableMultiSelect(bool bEnable = true) { m_bMultiSel = bEnable; }
		bool		IsMultiSelectEnabled() const { return m_bMultiSel; }

		// The Get<First|Next|Prev>SelectedItem() functions search for items
		// that have the SELECTED state set. NOTE that only expanded nodes
		// will be searched (i.e. only selected items that "might be visible"
		// will be returned by this functions). Use the return-code for
		// further searches. A return of 0 (NULL) indicates the end of the
		// list.
		//		for(HTREEITEM hItem = GetFirstSelectedItem() ;
		//			hItem != 0 ;
		//			hItem = GetNextSelectedItem(hItem)) {
		//			// ...			
		//			// whatever you want to do with "hItem"
		//			// ...
		//		}
		// This sample code can be used to iterate through all selected items.
		HTREEITEM	GetFirstSelectedItem() ;
		HTREEITEM	GetNextSelectedItem(HTREEITEM hItem) ;
		HTREEITEM	GetPrevSelectedItem(HTREEITEM hItem) ;

		// We have multiple items selected, thus we might have a different drag image.
		// As with CTreeCtrl::CreateDragImage() the list returned was created on
		// the heap and should delete'd if it is not longer needed.
		CImageList * CEditTreeCtrlEx::CreateDragImageEx();
		
private:

	void ListAddSelectedItem(HTREEITEM hItem);
	void ListRemoveSelectedItem(HTREEITEM hItem);
	HTREEITEM ListGetFirstSelectedItem();
	HTREEITEM ListGetNextSelectedItem(HTREEITEM hItem);
	HTREEITEM ListGetPrevSelectedItem(HTREEITEM hItem);
	int ListGetSelectedCount();
	void ListClearSelection();
	// Operations
	public:
		// SelectItems() selects all (visible) items between the two
		// given items (inclusive). There is no need to determine, wether
		// <From> occures above <To> or vice versa.
		void		SelectItems(HTREEITEM From, HTREEITEM To);

		// Invalidate all parts of the client area, where selected items occur.
		void		InvalidateSelectedItems();

		// ClearSelection() removes all selections except the one given
		// as argument (usally the one that has the focus) -> the following
		// call to this function might be a good idea:
		//		ClearSelection(GetSelectedItem());
		//
		// if <Except> is equal to zero, then ALL selections will be
		// removed.
		void		ClearSelection(HTREEITEM Except = 0) { ClearSelection(Except, 0); }

		// Select all items.
		void		SelectAll();

		// Deselect a specific item.
		// The focus does not change to the given item!
		void		DeselectItem(HTREEITEM hItem);


	// Overrides from CEditTreeCtrl
	protected:
		// Dragging multiple items needs a bit more attention...
		virtual bool	CanDropItem(HTREEITEM hDrag, HTREEITEM hDrop, EDropHint hint);
		virtual void	DragMoveItem(HTREEITEM hDrag, HTREEITEM hDrop, EDropHint hint, bool bCopy);
		virtual void	DragStart();
		virtual void	DragEnd();
		virtual void	DragStop();

		virtual CDragData *	CreateDragData(HTREEITEM hDragItem, bool bRightDrag);

		// other overrides to take care on multiple selections
		virtual bool	CanEditLabel(HTREEITEM hItem);		// <- in derived classes call this first
		virtual bool	CanInsertItem(HTREEITEM hParent);	// <- in derived classes call this first
		virtual bool	DoDeleteItem(HTREEITEM);
		virtual void	ExtendContextMenu(CMenu & menu);

	// Keyboard map extension
	protected:
		virtual bool	DoSelectAll(HTREEITEM);

	// Operations
	public:

	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CEditTreeCtrlEx)
		//}}AFX_VIRTUAL

	// Implementation
	public:
		virtual ~CEditTreeCtrlEx();

	protected:
		void		ClearSelection(HTREEITEM Except, HTREEITEM Start);
		void		DeselectTree(HTREEITEM hItem);
		void		GetSelectedItemsWithoutDescendents(std::list<HTREEITEM> & result);

		// Generated message map functions
		//{{AFX_MSG(CEditTreeCtrlEx)
		afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnKillfocus(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnSetfocus(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);
		afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
		afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
		//}}AFX_MSG

		afx_msg void	OnExCmd(UINT id);

#if _MFC_VER >= 0x0420
		// take care on visual effects when dragging multiple items
		afx_msg void OnCustomTreeDraw(NMHDR * pNMHDR, LRESULT * pResult);
#endif

		DECLARE_MESSAGE_MAP()
};


//---------------------------------------------------------------------------
// helper class CDragDataEx


class CDragDataEx : public CDragData {
	public:
		CDragDataEx(CEditTreeCtrl & tree, HTREEITEM hItem, bool bRightDrag)
			: CDragData(tree, hItem, bRightDrag)
		{
		}

		// We only need to call a different method to create the
		// drag-image...
		virtual void	CreateDragImage() {
							// make sure you don't create multiple images!
							ASSERT(m_pDragImg == 0);
							m_pDragImg = ((CEditTreeCtrlEx&)m_Owner).CreateDragImageEx();
							if(m_pDragImg) {
								CPoint pt;
								::GetCursorPos(&pt);
								m_Owner.ScreenToClient(&pt);
								m_pDragImg->DragShowNolock(TRUE);  // lock updates and show drag image
								m_pDragImg->SetDragCursorImage(0,CPoint(0,0));  // define the hot spot for the new cursor image
								m_pDragImg->BeginDrag(0,CPoint(0,0));
								m_pDragImg->DragEnter(&m_Owner,pt);
								m_pDragImg->DragMove(pt);
							}
						}
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITTREECTRLEX_H__A2215620_F871_408A_9519_D5A6317EBA5C__INCLUDED_)
