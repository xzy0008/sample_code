// PropertiesViewBar.h: interface for the CPropertiesViewBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROPERTIESVIEWBAR_H__91E4A4A8_1AD0_450E_841C_409767044A55__INCLUDED_)
#define AFX_PROPERTIESVIEWBAR_H__91E4A4A8_1AD0_450E_841C_409767044A55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

using std::string;


/**
* vgPropertiesViewBar 在vgUIController的控制下管理属性视图
*
* @see		   vgUIController	   
*
* @author      ZSC
* @version     VRGIS FrameWork RC
* @since       VRGIS 1.0
*/
class vgPropertiesViewBar : public CBCGPDockingControlBar  
{
// Construction
public:
	vgPropertiesViewBar();

	virtual ~vgPropertiesViewBar();

	void AdjustLayout ();

	CBCGPTabWnd* GetTabControl();

	void AddTab(string name, CWnd *wnd);

	void RemoveAllTab();
	
// Attributes
public:

protected:
	
	int m_tabCnt;

	CBCGPTabWnd		m_wndTab;

public:

// Attributes
protected:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertiesViewBar)
	//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CPropertiesViewBar)
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_PROPERTIESVIEWBAR_H__91E4A4A8_1AD0_450E_841C_409767044A55__INCLUDED_)
