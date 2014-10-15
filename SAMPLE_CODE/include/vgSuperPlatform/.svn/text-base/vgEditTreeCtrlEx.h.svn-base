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
#include "vgBaseEntry.h"


#include "vgRootEntry.h"
using namespace std;

enum ExTreeCmdHandler {
	NID_MESH_GOTO = 1,

	NID_MESH_DELETE,

	NID_MESH_SHOWPROP,
	
	NID_ROOT_DELETE,

	NID_VIEW_SWITCH2,
	
	NID_CITYPLAN_DELETE,	

	NID_CITYPLAN_CONVERT_ACTUALITY,//2008.10.21

	NID_CITYPLAN_CONVERT_BLUEPRINT1,

	NID_CITYPLAN_CONVERT_BLUEPRINT2,

	NID_CITYPLAN_CONVERT_BLUEPRINT3,

	NID_MESH_MAX_CMD

	
};

class CEditTreeCtrlEx;

//---------------------------------------------------------------------------
// helper class for tracking

class CEditTreeTracker : public CRectTracker {
	CEditTreeCtrlEx *		m_pEditTree;

	public:
		CEditTreeTracker()
			: m_pEditTree(0)
		{}

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

		int					m_shiftFlag;

		//list <vgBasedNode*>		m_nodeList;
	// Construction
	public:
		CEditTreeCtrlEx();

	// Attributes

public:

	// 提供的外部接口，不影响SelectedManager
	void		SetSelection(HTREEITEM hItem);

	void		AddSelection(HTREEITEM hItem);

	void		RemoveAllSeletions();
	// Invalidate all parts of the client area, where selected items occur.
	void		InvalidateSelectedItems();

	void		ClearSelection(HTREEITEM Except = 0) { ClearSelection(Except, 0); }

	void		DeleteSelectedNode(); 

	const list<HTREEITEM>& GetSelectedList()
	{
		return m_selectedList;
	}

public:
		// GetSelectedCount() returns the number of currently selected items.
	int			GetSelectedCount();
//	void		AddSelectedItem(HTREEITEM hItem);

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

		// We have multiple items selected, thus we might have a different drag image.
		// As with CTreeCtrl::CreateDragImage() the list returned was created on
		// the heap and should delete'd if it is not longer needed.
		CImageList * CEditTreeCtrlEx::CreateDragImageEx();
		 
protected:

	virtual bool	DoGotoMesh(HTREEITEM);
	virtual bool	DoDeleteMesh(HTREEITEM);
	virtual bool    DoDeleteRoot(HTREEITEM);
	virtual bool    DoShowHideProp(HTREEITEM);
	//virtual bool    DoDeletePlanItem( HTREEITEM )/*2008.10.21 */;
	//virtual bool DoConvertPlanActuality(HTREEITEM );

	//  [11/4/2008 zhu]
	virtual bool    DoVCRPlay( HTREEITEM );
	virtual bool    DoVCRStop( HTREEITEM );
	virtual bool    DoVCRGoon( HTREEITEM );
	virtual bool    DoVCRShow( HTREEITEM );

	//virtual bool DoConvertPlanBlueprint1(HTREEITEM);
	//virtual bool DoConvertPlanBlueprint2(HTREEITEM);
	//virtual bool DoConvertPlanBlueprint3(HTREEITEM);
	virtual bool	DoSwichToViewCam(HTREEITEM);

private:
	HTREEITEM	GetFirstSelectedItem() ;
	HTREEITEM	GetNextSelectedItem(HTREEITEM hItem) ;
	HTREEITEM	GetPrevSelectedItem(HTREEITEM hItem) ;

	// 通知SeletedManager 供内部使用
	void ListAddSelectedItem(HTREEITEM hItem, bool mergeMeshBox = true);
	void ListRemoveSelectedItem(HTREEITEM hItem);
	HTREEITEM ListGetFirstSelectedItem();
	HTREEITEM ListGetNextSelectedItem(HTREEITEM hItem);
	HTREEITEM ListGetPrevSelectedItem(HTREEITEM hItem);
	int ListGetSelectedCount();
	void ListClearSelection();
	// Operations


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
	// virtual bool	DoSelectAll(HTREEITEM);

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
		bool		m_bOnDel;

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
		afx_msg void OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );

		afx_msg void	OnContextCmd2(UINT uID);

		afx_msg void	OnExCmd(UINT id);

#if _MFC_VER >= 0x0420
		// take care on visual effects when dragging multiple items
		afx_msg void OnCustomTreeDraw(NMHDR * pNMHDR, LRESULT * pResult);
#endif

		DECLARE_MESSAGE_MAP()

		void UpdateMeshManagerSelection();

		typedef bool (CEditTreeCtrlEx::*method2)(HTREEITEM);

		typedef std::map<UINT, method2>			cmdmap_t2;

		cmdmap_t2	m_Commandmap2;
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
//2008.10.21

class  vgSubEntry : public vgRootEntry
{
public:

	vgSubEntry(string name)
	{
		m_name = name;
	}

	int GetUnSelectedImage() { return 2; }

	int GetSelectedImage() { return 1; }
protected:
private:
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITTREECTRLEX_H__A2215620_F871_408A_9519_D5A6317EBA5C__INCLUDED_)
