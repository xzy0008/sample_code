#pragma once

#include "resource.h"
#include "filetreectrl.h"


// CFileTreeDlg dialog

class CFileTreeDlg : public CDialog
{
	DECLARE_DYNAMIC(CFileTreeDlg)

public:
	CFileTreeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFileTreeDlg();

// Dialog Data
	enum { IDD = IDD_FILETREEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CFileTreeCtrl m_FileTree;
	virtual BOOL OnInitDialog();
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
};
