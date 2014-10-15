// VgFrame.h : main header file for the VgFrame application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CVgFrameApp:
// See VgFrame.cpp for the implementation of this class
//

class CVgFrameApp : public CWinApp,
							public CBCGPWorkspace
{
public:
	CVgFrameApp();
	~CVgFrameApp();

	// Override from CBCGPWorkspace
	virtual void PreLoadState ();

	// leven add
	BOOL	m_bHiColorIcons;

#ifdef CHINESE_VERSION
	HINSTANCE    m_hinstBCGCBRes;
#endif

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CVgFrameApp theApp;