// WizardSheetDlg.h : header file
//

#pragma once
#include <vgCellGridCtrl.h>
#include "afxwin.h"

// CWizardSheetDlg dialog
class CWizardSheetDlg : public CBCGPDialog
{
// Construction
public:
	CWizardSheetDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_WIZARDSHEET_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:

	CStatic m_wndGridLocation;

	CCellTypesGridCtrl	m_wndGrid;
	afx_msg void OnDestroy();
private:
	CComboBox m_versionCombo;
public:
	afx_msg void OnCbnSelchangeCombo1();
	CEdit m_versionInfoEdit;
	afx_msg void OnBnClickedSelfile();
private:
	CString m_filePath;
public:
	afx_msg void OnBnClickedGenerate();
	afx_msg void OnBnClickedEdit();
};
