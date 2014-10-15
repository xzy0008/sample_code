// G:\#NewWorkingFolders\vrgis_2.0_terrain\RealityFramework_BCG10_jicheng\src\vgTerrainCreater\vgWizardPage5.cpp : implementation file
//

#include <vgStableHeaders.h>
#include "vgWizardPage5.h"
#include "vgWizardPropertySheet.h"


// WizardPage5 dialog

IMPLEMENT_DYNAMIC(WizardPage5, CPropertyPage)

WizardPage5::WizardPage5()
	: CPropertyPage(WizardPage5::IDD)
{
	m_psp.dwFlags |= PSP_DEFAULT|PSP_USEHEADERTITLE|PSP_USEHEADERSUBTITLE;

	m_psp.pszHeaderTitle = _T("第4步");
	m_psp.pszHeaderSubTitle = _T("生成报告");
}

WizardPage5::~WizardPage5()
{
}

void WizardPage5::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WizardPage5, CPropertyPage)
END_MESSAGE_MAP()


// WizardPage5 message handlers

BOOL WizardPage5::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
	WizardPropertySheet* psheet = (WizardPropertySheet*)GetParent();    

	psheet->SetWizardButtons(PSWIZB_FINISH);  


	return CPropertyPage::OnSetActive();
}
