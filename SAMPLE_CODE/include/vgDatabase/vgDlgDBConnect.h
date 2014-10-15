// #if !defined(AFX_DBOPENNINGDLG_H__D70AF99E_A2D0_4716_94B6_560C09529EFF__INCLUDED_)
// #define AFX_DBOPENNINGDLG_H__D70AF99E_A2D0_4716_94B6_560C09529EFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBOpenningDlg.h : header file
//
#include <vgDatabase/vgdDefinition.h>

#ifdef VGD_DLL
#include <vgDatabaseDLL/vgDatabaseResource.h>
#else
#include <vgLibraryResource.h>
#endif

 
//#include <FileOpenedDlg.h>
/////////////////////////////////////////////////////////////////////////////
// DlgDBOpenning dialog

class  VGD_EXPORT DBConnectDlg : public CDialog
{
// Construction
public:
	DBConnectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgDBOpenning)
	enum { IDD = IDD_DB_CONNECT };
	CString	m_cstrFilePath;
	//}}AFX_DATA
//	CFileOpenedDlg	*dbtablesel;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgDBOpenning)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgDBOpenning)
	afx_msg void OnBtnFilepath();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	bool saveToConfigFile();
	bool deleteConfigFile();

private:
	CString m_databaseName;
	CString m_databaseSource;
	CString m_userName;
	CString m_pwd;

	String m_profilePath;

	int m_remPwd;
public:
	afx_msg void OnBnClickedBtnDatabasefile();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

// #endif // !defined(AFX_DBOPENNINGDLG_H__D70AF99E_A2D0_4716_94B6_560C09529EFF__INCLUDED_)
