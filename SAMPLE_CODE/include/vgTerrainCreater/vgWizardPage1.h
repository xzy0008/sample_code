#pragma once

#include "resource.h"
// WizardPage1 dialog

class WizardPage1 : public CBCGPPropertyPage
{
	DECLARE_DYNAMIC(WizardPage1)

public:
	WizardPage1();
	virtual ~WizardPage1();



// Dialog Data
	enum { IDD = IDD_WIZARDPAGE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
};
