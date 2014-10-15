#pragma once



#include "resource.h"
// WizardPage5 dialog

class WizardPage5 : public CPropertyPage
{
	DECLARE_DYNAMIC(WizardPage5)

public:
	WizardPage5();
	virtual ~WizardPage5();

// Dialog Data
	enum { IDD = IDD_WIZARDPAGE5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
};
