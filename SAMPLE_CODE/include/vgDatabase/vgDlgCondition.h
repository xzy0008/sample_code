// #if !defined(AFX_DBOPENNINGDLG_H__D70AF99E_A2D0_4716_94B6_560C09529EFF__INCLUDED_)
// #define AFX_DBOPENNINGDLG_H__D70AF99E_A2D0_4716_94B6_560C09529EFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBOpenningDlg.h : header file
//

#include <afxole.h>
 
#include <vgDatabase/vgdDefinition.h>

#ifdef VGD_DLL
#include <vgDatabaseDLL/vgDatabaseResource.h>
#else
#include <vgLibraryResource.h>
#endif

#include <BCGPTabWnd.h>
#include <vgDatabase/vgDlgConditionTab1.h>
#include <vgDatabase/vgDlgConditionTab2.h>
#include <vgDatabase/vgDlgConditionTab3.h>

// #define  WM_DELETE_DLG_EXE WM_USER+100 
 const static UINT WM_DELETE_DLG   = ::RegisterWindowMessage( _T("WM_DELETE_DLG") );

class  VGD_EXPORT DBCondition : public CDialog
{
// Construction
public:
	DBCondition(CWnd* pParent = NULL);   // standard constructor
	~DBCondition();

	DBConditionTab2* GetResultTab()
	{
		return m_pConditionTab2;
	}
	
	DBConditionTab1* GetConditionTab()
	{
		return m_pConditionTab1;
	}

	DBConditionTab3* GetHtmlTab()
	{
		return m_pConditionTab3;
	}

	void SetActiveTab(int index)
	{
		m_wndTab.SetActiveTab(index);
	}


	void Quit()
	{
		OnCancel();
	}
// Dialog Data
	//{{AFX_DATA(DlgDBOpenning)
	enum { IDD = IDD_DB_CONDITION };
	CString	m_cstrFilePath;
	//}}AFX_DATA

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	void AdjustLayout();
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgDBOpenning)

	virtual void OnOK();
	virtual void OnCancel();
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();

	virtual void OnSize(UINT nType, int cx, int cy);
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CBCGPTabWnd		m_wndTab;
	DBConditionTab1 *m_pConditionTab1;
	DBConditionTab2 *m_pConditionTab2;
	DBConditionTab3 *m_pConditionTab3;


public:
	afx_msg void OnDestroy();
};

