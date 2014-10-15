#pragma once

#include "resource.h"

#include "afxwin.h"

// WizardPage4 dialog

class WizardPage4 : public CPropertyPage
{
	DECLARE_DYNAMIC(WizardPage4)

public:
	WizardPage4();
	virtual ~WizardPage4();

// Dialog Data
	enum { IDD = IDD_WIZARDPAGE4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();
	virtual BOOL OnSetActive();
};
