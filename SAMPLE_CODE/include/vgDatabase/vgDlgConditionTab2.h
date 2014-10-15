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
#include <vgDatabase/vgResultGridControl.h>

class  VGD_EXPORT DBConditionTab2: public CDialog
{
// Construction
public:
	DBConditionTab2(CWnd* pParent = NULL);   // standard constructor
	~DBConditionTab2();

	bool InitResultGrid(String connectString, String id, String pwd, CString sqlString);

// Dialog Data
	//{{AFX_DATA(DlgDBOpenning)
	enum { IDD = IDD_DB_CDTAB2 };
	CString	m_cstrFilePath;
	//}}AFX_DATA

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
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
	
	void AdjustLayout();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CWnd* m_pParent;

	ResultGridControl m_resultGrid;
	CString OutputDir;

	CBCGPColorButton	m_ColorPicker;
	COLORREF			m_curColor;

	CSpinButtonCtrl     m_spinAlpha;
	int				    m_editAlpha;


public:
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedDbtab2Back();
	afx_msg void OnBnClickedPrint();
	afx_msg void OnBnClickedButton1();
	bool DeleteDirectory(const char* DirName );

	afx_msg void OnColorPicker();
	afx_msg void OnHilightDisplay();

	afx_msg void OnSpinAlpha();

};

