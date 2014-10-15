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
	m_psp.pszHeaderSubTitle = _T("导入高度图数据和影像数据");

	m_CurrentFileID = 0;
}

WizardPage2::~WizardPage2()
{
}

void WizardPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMPORT_LIST, _importList);
}


BEGIN_MESSAGE_MAP(WizardPage2, CPropertyPage)
	ON_BN_CLICKED(IDC_IMPORT, &WizardPage2::OnBnClickedImport)
	ON_BN_CLICKED(IDC_IMPORT_IMG, &WizardPage2::OnBnClickedImportImg)
	ON_BN_CLICKED(IDC_CLEAR_ALL, &WizardPage2::OnBnClickedClearAll)
END_MESSAGE_MAP()


// WizardPage2 message handlers

BOOL WizardPage2::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
	CPropertySheet*   psheet   =   (CPropertySheet*)   GetParent();         
	psheet->SetWizardButtons(PSWIZB_NEXT );   



	return CPropertyPage::OnSetActive();
}


void WizardPage2::OnBnClickedImport()
{
	CString DefExt;

	DefExt.Format("%s","dem文件(*.dem)|*.dem|");

	CFileDialog dlgmodelFile(true,"dem",
		NULL,OFN_HIDEREADONLY|
		OFN_CREATEPROMPT|
		OFN_NONETWORKBUTTON|
		OFN_ALLOWMULTISELECT|   
		OFN_FILEMUSTEXIST,
		DefExt);

	DWORD   MAXFILE = 0xFFFF;   
	dlgmodelFile.m_ofn.nMaxFile=MAXFILE; 

	char*  pc = new char[MAXFILE];   


	dlgmodelFile.m_ofn.lpstrFile = pc;   
	dlgmodelFile.m_ofn.lpstrFile[0] = NULL;   
	dlgmodelFile.m_ofn.lpstrTitle="dem文件导入";

	if( dlgmodelFile.DoModal() == IDOK )
	{
		POSITION posi;   
		vgKernel::StringVectorPtr strVec( new vgKernel::StringVector );

		posi = dlgmodelFile.GetStartPosition();   

		while( posi != NULL )
		{   
			strVec->push_back( dlgmodelFile.GetNextPathName(posi).GetBuffer(0));
		}   

		delete[] pc;

		//------------------------------------------
		// 开始导入
		//------------------------------------------
		_importList.updateDems( strVec );
	}
}

BOOL WizardPage2::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here


	_importList.initialise();

	UpdateData(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void WizardPage2::OnBnClickedImportImg()
{
	CString DefExt;

	DefExt.Format("%s","(*.bmp)|*.bmp|(*.tif)|*.tif|(*.*)|*.*|");

	CFileDialog dlgmodelFile(true,"影像文件",
		NULL,OFN_HIDEREADONLY|
		OFN_CREATEPROMPT|
		OFN_NONETWORKBUTTON|
		OFN_ALLOWMULTISELECT|   
		OFN_FILEMUSTEXIST,
		DefExt);

	DWORD   MAXFILE = 0xFFFF;   
	dlgmodelFile.m_ofn.nMaxFile=MAXFILE; 

	char*  pc = new char[MAXFILE];   


	dlgmodelFile.m_ofn.lpstrFile = pc;   
	dlgmodelFile.m_ofn.lpstrFile[0] = NULL;   
	dlgmodelFile.m_ofn.lpstrTitle="影像文件导入";

	if( dlgmodelFile.DoModal() == IDOK )
	{
		POSITION posi;   
		vgKernel::StringVectorPtr strVec( new vgKernel::StringVector );

		posi = dlgmodelFile.GetStartPosition();   

		while( posi != NULL )
		{   
			strVec->push_back( dlgmodelFile.GetNextPathName(posi).GetBuffer(0));
		}   

		delete[] pc;

		//------------------------------------------
		// 开始导入
		//------------------------------------------
		_importList.updateImage( strVec );
		
	}
}

void WizardPage2::OnBnClickedClearAll()
{
	_importList.clearAll();
}

BOOL WizardPage2::OnKillActive()
{
	// TODO: Add your specialized code here and/or call the base class

	if ( _importList.checkValid() == false )
	{
		return FALSE;
	}

	return CPropertyPage::OnKillActive();
}

LRESULT WizardPage2::OnWizardNext()
{
	// TODO: Add your specialized code here and/or call the base class

	if ( _importList.checkValid() == false )
	{
		MessageBox( "输入的列表不正确" , "提示" );
		return FALSE;
	}


	WizardPropertySheet*   psheet   =  
		(WizardPropertySheet*)  GetParent();         
	assert( psheet->_demBag == NULL );

	vgKernel::StringPairVector* list =  psheet->_listItemCtrl->getStringPairVec();

	assert( list != NULL );

	psheet->_demBag = new vgTerritory::DemAreaBag;

	vgTerritory::DemAreaBag& bag = *psheet->_demBag;

	if( bag.readFromFilePairs( *list ) == false )
	{
		delete list;
		return FALSE;
	}

	delete list;

	return CPropertyPage::OnWizardNext();
}
