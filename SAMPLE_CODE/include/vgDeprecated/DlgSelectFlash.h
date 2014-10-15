#pragma once

#include <Resource.h>
#include "vgKernel/vgkStringUtility.h"
#include "vgKernel/vgkSystemUtility.h"
// CDlgFindObject dialog

class VGDEP_EXPORT CDlgSelectFlash : public CDialog
{
	DECLARE_DYNAMIC(CDlgSelectFlash)

public:
	CDlgSelectFlash(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSelectFlash();

// Dialog Data
	enum { IDD = IDD_DIALOG_SELECTFLASH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_SearchName;
	CString m_filepath;
	String  m_userFlashPath;
	String  m_packFilePath;
public:
	afx_msg void OnBnClickedSelectFlash();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOK();

	String getUserInterfacePath(){ return m_userFlashPath;}
	String getPackFilePath(){ return m_packFilePath; }
	afx_msg void OnBnClickedButtonPackpath();
};
