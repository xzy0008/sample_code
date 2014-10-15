// vgWizardPage2.cpp : implementation file
//

#include <vgStableHeaders.h>
#include "WizardSheet.h"
#include "vgWizardPage2.h"
#include "vgWizardPropertySheet.h"


// WizardPage2 dialog

IMPLEMENT_DYNAMIC(WizardPage2, CPropertyPage)

WizardPage2::WizardPage2()
	: CPropertyPage(WizardPage2::IDD)
{
	m_psp.dwFlags |= PSP_DEFAULT|PSP_USEHEADERTITLE|PSP_USEHEADERSUBTITLE;

	m_psp.pszHeaderTitle = _T("第1步");
	m_psp.pszHeaderSubTitle = _T("导入高度图数据");
}

WizardPage2::~WizardPage2()
{

}

void WizardPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WizardPage2, CPropertyPage)

END_MESSAGE_MAP()


// WizardPage2 message handlers

BOOL WizardPage2::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
	CPropertySheet*   psheet   =   (CPropertySheet*)   GetParent();         
	psheet->SetWizardButtons(PSWIZB_NEXT );   

	return CPropertyPage::OnSetActive();
}

BOOL WizardPage2::OnKillActive()
{
	// TODO: Add your specialized code here and/or call the base class

	return CPropertyPage::OnKillActive();
}

LRESULT WizardPage2::OnWizardNext()
{
	// TODO: Add your specialized code here and/or call the base class

	return CPropertyPage::OnWizardNext();
}




