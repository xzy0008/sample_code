// G:\#NewWorkingFolders\vrgis_2.0_terrain\RealityFramework_BCG8\src\vgTerrainCreater\vgWizardPage3.cpp : implementation file
//

#include <vgStableHeaders.h>
#include "WizardSheet.h"
#include "vgWizardPropertySheet.h"
#include "vgWizardPage3.h"

// WizardPage3 dialog

IMPLEMENT_DYNAMIC(WizardPage3, CPropertyPage)

WizardPage3::WizardPage3()
	: CPropertyPage(WizardPage3::IDD)
{
	m_psp.dwFlags |= PSP_DEFAULT|PSP_USEHEADERTITLE|PSP_USEHEADERSUBTITLE;

	m_psp.pszHeaderTitle = _T("第2步");
	m_psp.pszHeaderSubTitle = _T("输入参数");

}

WizardPage3::~WizardPage3()
{
}

void WizardPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WizardPage3, CPropertyPage)

END_MESSAGE_MAP()


// WizardPage3 message handlers

BOOL WizardPage3::OnKillActive()
{
	// TODO: Add your specialized code here and/or call the base class

	return CPropertyPage::OnKillActive();
}

BOOL WizardPage3::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class



	return CPropertyPage::OnSetActive();
}


BOOL WizardPage3::OnInitDialog()
{
	CPropertyPage::OnInitDialog();


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}



LRESULT WizardPage3::OnWizardNext()
{
	// TODO: Add your specialized code here and/or call the base class

	return CPropertyPage::OnWizardNext();
}

LRESULT WizardPage3::OnWizardBack()
{
	// TODO: Add your specialized code here and/or call the base class

	CPropertySheet*   psheet   =   (CPropertySheet*)   GetParent();         
	psheet->SetWizardButtons(PSWIZB_NEXT);   

	return CPropertyPage::OnWizardBack();
}
