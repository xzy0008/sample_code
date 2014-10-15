// vgWizardPage1.cpp : implementation file
//

#include <vgStableHeaders.h>
#include "WizardSheet.h"
#include "vgWizardPage1.h"


// WizardPage1 dialog

IMPLEMENT_DYNAMIC(WizardPage1, CBCGPPropertyPage)

WizardPage1::WizardPage1()
	: CBCGPPropertyPage(WizardPage1::IDD)
{
	m_psp.dwFlags |= PSP_DEFAULT|PSP_HIDEHEADER;
	


}

WizardPage1::~WizardPage1()
{
}

void WizardPage1::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WizardPage1, CBCGPPropertyPage)
END_MESSAGE_MAP()


// WizardPage1 message handlers

BOOL WizardPage1::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
	CPropertySheet*   psheet   =   (CPropertySheet*)   GetParent();         
	psheet->SetWizardButtons(PSWIZB_NEXT);   


	return CBCGPPropertyPage::OnSetActive();
}
