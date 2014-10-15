#pragma once

#include <vgUIController/vgUIController.h>

#include <string>

using std::string;


class vgPropBar :  public CBCGPDockingControlBar ,public vgPropertiesViewBar
{

 public:
 	vgPropBar();
 
 	virtual ~vgPropBar();
 
	void AdjustLayout ();

  	CBCGPTabWnd* GetTabControl();
  
  	void AddTab(string name, CWnd *wnd);
  
  	void RemoveAllTab();
 
 	virtual void ShowControlBar(BOOL bShow, BOOL bDelay, BOOL bActivate/* = TRUE*/)
 	{
 		CBCGPDockingControlBar::ShowControlBar(bShow, bDelay, bActivate);
 	}
 
 	virtual BOOL IsVisible()
 	{
 		return CBCGPDockingControlBar::IsVisible();
 	}

 protected:
 
 	int m_tabCnt;
 
 	CBCGPTabWnd		m_wndTab;

 protected:

  	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

