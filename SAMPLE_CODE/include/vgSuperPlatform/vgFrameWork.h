// vgFrameWork.h : main header file for the vgFrameWork application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CvgFrameWorkApp:
// See vgFrameWork.cpp for the implementation of this class
//

class CvgFrameWorkApp : public CWinApp,
							public CBCGPWorkspace
{
public:
	CvgFrameWorkApp();

	// Override from CBCGPWorkspace
	virtual void PreLoadState ();


private:

	HINSTANCE    m_hinstBCGCBRes;

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
//	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CvgFrameWorkApp theApp;