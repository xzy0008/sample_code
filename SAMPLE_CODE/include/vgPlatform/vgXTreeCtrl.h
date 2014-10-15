// XTreeCtrl.h : header file
#if !defined(AFX_XTREECTRL_H__3EF12526_EF66_4FD9_A572_59476441D79A__INCLUDED_)
#define AFX_XTREECTRL_H__3EF12526_EF66_4FD9_A572_59476441D79A__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VG_MSG_TREEDRAG WM_USER + 1

#include "vgBasedNode.h"

class vgXTreeCtrl : public CTreeCtrl
{
	// Construction
public:
	vgXTreeCtrl();
	// Attributes
public:
	// Operations
public:
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXTreeCtrl)
	//}}AFX_VIRTUAL
	// Implementation
public:
	virtual ~vgXTreeCtrl();
	// Generated message map functions
protected:
    UINT m_TimerTicks; //处理滚动的定时器所经过的时间
    UINT_PTR m_nScrollTimerID; //处理滚动的定时器
    CPoint m_HoverPoint; //鼠标位置
    UINT_PTR m_nHoverTimerID; //鼠标敏感定时器
    DWORD m_dwDragStart; //按下鼠标左键那一刻的时间
    BOOL m_bDragging; //标识是否正在拖动过程中
    CImageList* m_pDragImage; //拖动时显示的图象列表
    HTREEITEM m_hItemDragS; //被拖动的标签
    HTREEITEM m_hItemDragD; //接受拖动的标签

	//{{AFX_MSG(CXTreeCtrl)
    afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    HTREEITEM CopyBranch(HTREEITEM htiBranch,HTREEITEM htiNewParent,HTREEITEM htiAfter);
    HTREEITEM CopyItem(HTREEITEM hItem,HTREEITEM htiNewParent,HTREEITEM htiAfter);
};
#endif
