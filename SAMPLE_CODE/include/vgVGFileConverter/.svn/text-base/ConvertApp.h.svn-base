// WizardSheet.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols



// CWizardSheetApp:
// See WizardSheet.cpp for the implementation of this class
//

class WizardPropertySheet;

class CWizardSheetApp : public CWinApp,
	public CBCGPWorkspace
{
public:
	CWizardSheetApp();

// Overrides
	public:
	virtual BOOL InitInstance();

	WizardPropertySheet* _sheet;

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CWizardSheetApp theApp;