#pragma once


#include "vgWizardPage1.h"
#include "vgWizardPage2.h"
#include "vgWizardPage3.h"
#include "vgWizardPage4.h"
#include "vgWizardPage5.h"



// WizardPropertySheet

class WizardPropertySheet : public CBCGPPropertySheet
{
	DECLARE_DYNAMIC(WizardPropertySheet)

public:
	WizardPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	WizardPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~WizardPropertySheet();

public:

	//vgTerritory::DemAreaBag* _demBag;

private:

	WizardPage1	_page1;
	WizardPage2	_page2;
	WizardPage3	_page3;
	WizardPage4  _page4;
	WizardPage5  _page5;

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};


