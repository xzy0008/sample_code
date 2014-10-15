#pragma once
#include "afxcmn.h"

#include "resource.h"


// WizardPage2 dialog

class WizardPage2 : public CPropertyPage
{
	DECLARE_DYNAMIC(WizardPage2)

public:
	WizardPage2();
	virtual ~WizardPage2();


// Dialog Data
	enum { IDD = IDD_WIZARDPAGE2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();

	int m_CurrentFileID;

	virtual BOOL OnKillActive();
	virtual LRESULT OnWizardNext();
};
