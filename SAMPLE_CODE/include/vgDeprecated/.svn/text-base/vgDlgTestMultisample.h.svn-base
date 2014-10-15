

#pragma once


#include <vgCore/vgPrerequisites.h>

#include "resource.h"
#include <vgOpenGLControl.h>





class  VGDEP_EXPORT DlgTestMultisample : public CDialog
{

	DECLARE_DYNAMIC(DlgTestMultisample)

public:
	DlgTestMultisample(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgTestMultisample();

	vgCore::OpenGLControl m_oglWindow;

	bool *_parbMultisampleSupported;
	int *_parbMultisampleFormat;

// Dialog Data
	enum { IDD = IDD_TEST_MULTISAMPLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
/////////////////////////////////////////////////////////////

private:
	std::map<CString,CString> User_Password;
	CString Name;
	CString Password;
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedButton1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
