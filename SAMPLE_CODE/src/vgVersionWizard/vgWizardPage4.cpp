// G:\#NewWorkingFolders\vrgis_2.0_terrain\RealityFramework_BCG8\src\vgTerrainCreater\vgWizardPage4.cpp : implementation file
//

#include <vgStableHeaders.h>
#include "vgWizardPage3.h"
#include "vgWizardPage4.h"
#include "vgWizardPropertySheet.h"
#include "WizardSheet.h"

// WizardPage4 dialog

IMPLEMENT_DYNAMIC(WizardPage4, CPropertyPage)

WizardPage4::WizardPage4()
	: CPropertyPage(WizardPage4::IDD)
{
	m_psp.dwFlags |= PSP_DEFAULT|PSP_USEHEADERTITLE|PSP_USEHEADERSUBTITLE;

	m_psp.pszHeaderTitle = _T("第3步");
	m_psp.pszHeaderSubTitle = _T("处理数据");

}

WizardPage4::~WizardPage4()
{

}

void WizardPage4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(WizardPage4, CPropertyPage)

END_MESSAGE_MAP()


// WizardPage4 message handlers

BOOL WizardPage4::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL WizardPage4::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
	CPropertySheet*   psheet   =   (CPropertySheet*)   GetParent();         
	psheet->SetWizardButtons(PSWIZB_NEXT);   

	return CPropertyPage::OnSetActive();
}

