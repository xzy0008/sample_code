#pragma  once

#include "Resource.h"
//#include "vgOpenGLControl.h"
#include <map>

class   VGDEP_EXPORT  CAboutDlg : public CDialog  
{
public:
	CAboutDlg();  

	// Dialog Data
	enum { IDD = NIDD_ABOUTBOX2 };
	CBCGPURLLinkButton m_btnURL;

//	vgCore::OpenGLControl openglcontrol;
	CBitmap m_bmpBackground;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CString m_component;
	CString str; 
	std::map<CString,CString> component_comment;
	std::map<CString,CString>::const_iterator iter;
	afx_msg void OnLbnSelchangeComponent();
	CString m_comment;
	afx_msg void OnEnChangeComment();
	afx_msg void OnBnClickedButton1();
};
