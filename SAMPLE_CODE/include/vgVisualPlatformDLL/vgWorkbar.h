#pragma once

#include <vgUIController/vgUIController.h>

#include <string>

using std::string;


class vgWorkbar :  public CBCGPDockingControlBar ,public vgWorkSpaceBar
{
public:

	virtual void ShowControlBar(BOOL bShow, BOOL bDelay, BOOL bActivate/* = TRUE*/)
	{
		CBCGPDockingControlBar::ShowControlBar(bShow, bDelay, bActivate);
	}

	virtual BOOL IsVisible()
	{	
		return CBCGPDockingControlBar::IsVisible();
	}

protected:
 	//{{AFX_MSG(CWorkSpaceBar)
 	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
 	afx_msg void OnSize(UINT nType, int cx, int cy);
 	afx_msg void OnPaint();
 	//}}AFX_MSG
 
 	afx_msg void OnContextMenu(CWnd* pWnd, CPoint pos);
 
 	afx_msg LRESULT OnTreeDrag(WPARAM h1,LPARAM h2); 
 
 	DECLARE_MESSAGE_MAP()
};

