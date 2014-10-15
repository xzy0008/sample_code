#pragma once


/////////////////////////////////////////////////////////////////////////////
// CScriptConsoleDlg dialog
#include <resource.h>
#include "ResizableDialog.h"
#include "SplitterControl.h"
#include "afxwin.h"

#include "CmdFrame.h"


#include <string>

#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))


class CScriptConsoleDlg : public CResizableDialog
{
	// Construction
public:
	CScriptConsoleDlg(CWnd* pParent = NULL);	// standard constructor

	// Dialog Data
	//{{AFX_DATA(CScriptConsoleDlg)
	enum { IDD = IDD_SCRIPT_CONSOLE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptConsoleDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL


	CStatic	m_wndMenuBarLocation;
	CBCGPMenuBar m_wndMenuBar;

	CCmdFrame*			m_pMenuFrame;

	//////////////////////////////////////////////////////////////////////////

	CSplitterControl m_wndSplitter1;
	void DoResize2(int delta);

	//////////////////////////////////////////////////////////////////////////

	// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CScriptConsoleDlg)
	virtual BOOL OnInitDialog();

	void addAnchorToItems();
	void createSplitter();

	void setSplitterRange();


	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeScriptEdit();
	afx_msg void OnBnClickedScriptExecuate();
protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	CEdit _outputCtrl;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CStatic _splitterStatic;
	CEdit _scriptEditCtrl;
	CEdit _scriptTipsCtrl;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CString _scriptContent;
	CString _scriptOutput;

	void dumpToOutput( const std::string& msg,
		const bool& addlinesep = true  , const bool& add_decoration = false );

	void clearOutput();

	void setScriptTips( const std::string& tips );
	CString _scriptTips;
	afx_msg void OnScriptExit();
	afx_msg void OnScriptSave();
	afx_msg void OnImportPy();
	afx_msg void OnScriptAbout();
	afx_msg void OnDestroy();
	afx_msg void OnClear();
};
