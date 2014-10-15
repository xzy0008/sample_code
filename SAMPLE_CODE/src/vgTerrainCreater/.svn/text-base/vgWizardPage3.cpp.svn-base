// G:\#NewWorkingFolders\vrgis_2.0_terrain\RealityFramework_BCG8\src\vgTerrainCreater\vgWizardPage3.cpp : implementation file
//

#include <vgStableHeaders.h>
#include "WizardSheet.h"
#include "vgWizardPropertySheet.h"
#include "vgWizardPage3.h"

#include <vgTerritory/vgtDemAreaBag.h>
#include <vgTerritory/vgTerrainHugeImageProcessor.h>
#include <vgKernel/vgkTrace.h>

// WizardPage3 dialog

IMPLEMENT_DYNAMIC(WizardPage3, CPropertyPage)

WizardPage3::WizardPage3()
	: CPropertyPage(WizardPage3::IDD)
	, _selectedFolder(_T(""))
	, _selectOuputFolder(_T(""))
	, _scaleDemToImgID(0)
	, _terrainName(_T(""))
	, _terrainNComboxID(0)
{
	m_psp.dwFlags |= PSP_DEFAULT|PSP_USEHEADERTITLE|PSP_USEHEADERSUBTITLE;

	m_psp.pszHeaderTitle = _T("第2步");
	m_psp.pszHeaderSubTitle = _T("输入参数");

	_scaleDemToImg = 1;


	_terrainN = 8;


}

WizardPage3::~WizardPage3()
{
}

void WizardPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SELECT_FOLDER, _selectedFolder);
	DDX_Text(pDX, IDC_TERRAIN_NAME, _terrainName);
	DDX_Text(pDX, IDC_SELECT_OUTPUT_FOLDER, _selectOuputFolder);
	DDX_CBIndex(pDX, IDC_COMBO_SCALE_DEM_TO_IMG, _scaleDemToImgID);
	DDX_CBIndex(pDX, IDC_COMBO_TERRAIN_N, _terrainNComboxID);
	DDX_Control(pDX, IDC_COMBO_SCALE_DEM_TO_IMG, _btnScaleDemToImg);
}


BEGIN_MESSAGE_MAP(WizardPage3, CPropertyPage)
	ON_BN_CLICKED(IDC_BTN_SELECT_FOLDER, &WizardPage3::OnBnClickedBtnSelectFolder)
	ON_BN_CLICKED(IDC_BTN_SELECT_OUTPUT_FOLDER, &WizardPage3::OnBnClickedBtnSelectOutputFolder)
//	ON_CBN_SELCHANGE(IDC_COMBO_SCALE_DEM_TO_IMG, &WizardPage3::OnCbnSelchangeComboScaleDemToImg)
ON_EN_CHANGE(IDC_TERRAIN_NAME, &WizardPage3::OnEnChangeTerrainName)
ON_CBN_SELCHANGE(IDC_COMBO_SCALE_DEM_TO_IMG, &WizardPage3::OnCbnSelchangeComboScaleDemToImg)
ON_CBN_SELCHANGE(IDC_COMBO_TERRAIN_N, &WizardPage3::OnCbnSelchangeComboTerrainN)
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

	WizardPropertySheet* psheet = (WizardPropertySheet*)GetParent();         
	psheet->SetWizardButtons(PSWIZB_NEXT);   


	assert( psheet->_demBag != NULL);
	
	long scale = psheet->_demBag->getScaleOfDemToImg();

	switch( scale )
	{
	case 1:
		_scaleDemToImgID = 0;
		UpdateData( FALSE );
		break;
	case 2:
		_scaleDemToImgID = 1;
		UpdateData( FALSE );
		break;
	case 8:
		_scaleDemToImgID = 2;
		UpdateData( FALSE );
	}

	checkAndSetNextBtn();

	return CPropertyPage::OnSetActive();
}

void WizardPage3::OnBnClickedBtnSelectFolder()
{
	if (theApp.GetShellManager ()->BrowseForFolder (
		_selectedFolder, this, _selectedFolder))
	{
		UpdateData (FALSE);
	}

	checkAndSetNextBtn();
}

void WizardPage3::OnBnClickedBtnSelectOutputFolder()
{
	if (theApp.GetShellManager ()->BrowseForFolder (
		_selectOuputFolder, this, _selectOuputFolder))
	{
		UpdateData (FALSE);
	}

	checkAndSetNextBtn();
}

//void WizardPage3::OnCbnSelchangeComboScaleDemToImg()
//{
//	UpdateData ();
//
//	switch( _scaleDemToImgID )
//	{
//	case 0:
//		_scaleDemToImg = 1;
//		break;
//	case 1:
//		_scaleDemToImg = 2;
//		break;
//	case 2:
//		_scaleDemToImg = 8;
//		break;
//	}
//}

BOOL WizardPage3::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}



LRESULT WizardPage3::OnWizardNext()
{
	// TODO: Add your specialized code here and/or call the base class

	UpdateData();

	WizardPropertySheet* psheet = (WizardPropertySheet*)GetParent();  



	switch( _scaleDemToImgID )
	{
	case 0:
		_scaleDemToImg = 1;
		break;
	case 1:
		_scaleDemToImg = 2;
		break;
	case 2:
		_scaleDemToImg = 8;
		break;
	}


	switch( _terrainNComboxID )
	{
	case 0:
		_terrainN = 8;
		break;
	case 1:
		_terrainN = 7;
		break;
	}


	return CPropertyPage::OnWizardNext();
}

LRESULT WizardPage3::OnWizardBack()
{
	// TODO: Add your specialized code here and/or call the base class

	WizardPropertySheet*   psheet   =  
		(WizardPropertySheet*)   GetParent();         
	assert( psheet->_demBag != NULL);


	delete psheet->_demBag;
	psheet->_demBag = NULL;


	return CPropertyPage::OnWizardBack();
}

void WizardPage3::checkAndSetNextBtn()
{

	if ( _selectOuputFolder != "" && 
		 _selectedFolder != "" &&
		 _terrainName != "" )
	{
		WizardPropertySheet* psheet = (WizardPropertySheet*)GetParent();         
		psheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);   

	}
	else
	{
		WizardPropertySheet* psheet = (WizardPropertySheet*)GetParent();         
		psheet->SetWizardButtons(PSWIZB_BACK);   
	}




}


//void CMyProgressDlg::OnDrawHeader( CDC* pDC, CRect rect )
//{
//	ASSERT_VALID (pDC);
//	//ASSERT_VALID (m_pHeader);
//
//	//m_pHeader->DrawEx (pDC, rect, 0);
//
//	CString strText;
//	strText.Format (_T("正在处理文件 \'%s\'"), m_strCurrFile);
//
//	CRect rectText = rect;
//	rectText.DeflateRect (10, 0);
//
//	pDC->SetBkMode (TRANSPARENT);
//	pDC->SetTextColor (RGB (255, 255, 255));
//
//	CFont* pOldFont = (CFont*) pDC->SelectStockObject (DEFAULT_GUI_FONT);
//
//	pDC->DrawText (strText, rectText, DT_SINGLELINE | DT_VCENTER);
//
//	pDC->SelectObject (pOldFont);
//}
void WizardPage3::OnEnChangeTerrainName()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	UpdateData();

	checkAndSetNextBtn();
	// TODO:  Add your control notification handler code here
}

void WizardPage3::OnCbnSelchangeComboScaleDemToImg()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE );
}

void WizardPage3::OnCbnSelchangeComboTerrainN()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE );
}
