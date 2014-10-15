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
#include <vgDatabase/vgConditionGridControl.h>

class  VGD_EXPORT DBConditionTab1: public CDialog
{
// Construction
public:
	DBConditionTab1(CWnd* pParent = NULL);   // standard constructor
	~DBConditionTab1();
// Dialog Data
	//{{AFX_DATA(DlgDBOpenning)
	enum { IDD = IDD_DB_CDTAB1 };
	CString	m_cstrFilePath;
	//}}AFX_DATA

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void AdjustLayout();

	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgDBOpenning)

	virtual void OnOK();
	virtual void OnCancel();
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();

	virtual void OnSize(UINT nType, int cx, int cy);

	void OnCommitButtonClick();

	CWnd* m_pParent;
	//CBCGPGridCtrl m_wndGrid;
	ConditionGridControl QueryConditionView;
//	CBCGPPropertySheet *m_propertySheet;

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	

	//CListCtrl QueryConditionView;
	CComboBox Profile_Name;
	CComboBox Feild_Name;
	CComboBox LogicalSymbol;
	CComboBox QueryCondition;
	CEdit QueryConditionEdit;

private:

public:
	afx_msg void OnBnClickedDbcAddcon();
	afx_msg void OnCbnSelchangeCombo2();
};

