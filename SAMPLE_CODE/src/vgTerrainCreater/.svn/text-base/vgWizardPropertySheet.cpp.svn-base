// vgWizardPropertySheet.cpp : implementation file
//

#include <vgStableHeaders.h>
#include "WizardSheet.h"
#include "vgWizardPropertySheet.h"


// WizardPropertySheet

IMPLEMENT_DYNAMIC(WizardPropertySheet, CPropertySheet)

WizardPropertySheet::WizardPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CBCGPPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	SetWizardMode();

	_listItemCtrl = &_page2._importList;

	AddPage(&_page1);
	AddPage(&_page2);
	AddPage(&_page3);
	AddPage(&_page4);
	AddPage(&_page5);

	m_psh.dwFlags |= PSH_WIZARD97|PSH_WATERMARK|PSH_HEADER|PSH_NOAPPLYNOW;
	m_psh.dwFlags &= ~PSH_HASHELP ;
	m_psh.pszbmWatermark = MAKEINTRESOURCE(IDB_WATERMARK);
	m_psh.pszbmHeader = MAKEINTRESOURCE(IDB_BANNER_ICON);
	// Next line is very important
	m_psh.hInstance = AfxGetInstanceHandle(); 

	_demBag = NULL;
}

WizardPropertySheet::WizardPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CBCGPPropertySheet(pszCaption, pParentWnd, iSelectPage)
{

	SetWizardMode();


	_listItemCtrl = &_page2._importList;

	AddPage(&_page1);
	AddPage(&_page2);
	AddPage(&_page3);
	AddPage(&_page4);
	AddPage(&_page5);

	m_psh.dwFlags |= PSH_WIZARD97|PSH_WATERMARK|PSH_HEADER|PSH_NOAPPLYNOW;
	m_psh.dwFlags &= ~PSH_HASHELP ;
	m_psh.pszbmWatermark = MAKEINTRESOURCE(IDB_WATERMARK);
	m_psh.pszbmHeader = MAKEINTRESOURCE(IDB_BANNER_ICON);
	// Next line is very important
	m_psh.hInstance = AfxGetInstanceHandle(); 



	HICON m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);   
	m_psh.dwFlags|=PSP_USEHICON;   
	m_psh.hIcon=m_hIcon ;

	_demBag = NULL;


}

WizardPropertySheet::~WizardPropertySheet()
{
}


BEGIN_MESSAGE_MAP(WizardPropertySheet, CBCGPPropertySheet)
END_MESSAGE_MAP()


// WizardPropertySheet message handlers

BOOL WizardPropertySheet::OnInitDialog()
{
	BOOL bResult = CBCGPPropertySheet::OnInitDialog();


	return bResult;
}
