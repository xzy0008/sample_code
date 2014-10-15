// vgWizardPage2.cpp : implementation file
//

#include <vgStableHeaders.h>
#include "WizardSheet.h"
#include "vgWizardPage2.h"
#include "vgWizardPropertySheet.h"

#include <vgTerritory/vgtGeoDemManager.h>




// WizardPage2 dialog

IMPLEMENT_DYNAMIC(WizardPage2, CPropertyPage)

WizardPage2::WizardPage2()
	: CPropertyPage(WizardPage2::IDD)
	, _progressMsg(_T("点击下一步开始预读dem并生成预览..."))
	, _genMeshOverview( FALSE )
	, _genTexOverview( FALSE )
{
	m_psp.dwFlags |= PSP_DEFAULT|PSP_USEHEADERTITLE|PSP_USEHEADERSUBTITLE;

	m_psp.pszHeaderTitle = _T("第1步");
	m_psp.pszHeaderSubTitle = _T("导入高度图数据");

	m_CurrentFileID = 0;


	m_pTaskDlg = NULL;
}

WizardPage2::~WizardPage2()
{
	if ( m_pTaskDlg != NULL )
	{
		delete m_pTaskDlg;
		m_pTaskDlg = NULL;
	}
}

void WizardPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMPORT_LIST, _importList);
	DDX_Control(pDX, IDC_IMPORT_LIST2, _importList2);

	DDX_Check(pDX, IDC_CHECK_GEN_MESH_OVERVIEW, _genMeshOverview);
	DDX_Check(pDX, IDC_CHECK_GEN_TEX_OVERVIEW, _genTexOverview);

}


BEGIN_MESSAGE_MAP(WizardPage2, CPropertyPage)
ON_BN_CLICKED(IDC_IMPORT, &WizardPage2::OnBnClickedImport)
	ON_BN_CLICKED(IDC_IMPORT_IMG, &WizardPage2::OnBnClickedImportImg)
	ON_BN_CLICKED(IDC_CLEAR_ALL, &WizardPage2::OnBnClickedClearAll)
	ON_BN_CLICKED(IDC_IMPORT2, &WizardPage2::OnBnClickedImport2)
	ON_BN_CLICKED(IDC_CLEAR_ALL2, &WizardPage2::OnBnClickedClearAll2)
END_MESSAGE_MAP()


// WizardPage2 message handlers

BOOL WizardPage2::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
	CPropertySheet*   psheet   =   (CPropertySheet*)   GetParent();         
	psheet->SetWizardButtons(PSWIZB_NEXT );   


	vgTerritory::GeoDemManager::getSingleton().clearData();

	vgTerritory::GeoDemManager::getSingleton().registerProcessObs( this );

	return CPropertyPage::OnSetActive();
}


void WizardPage2::OnBnClickedImport()
{
	CString DefExt;

	DefExt.Format("%s","dem (*.dem)|*.dem|Geotiff (*.tif;*.tiff)|*.tif;*.tiff|(*.img)|*.img|(*.*)|*.*|");

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
	_importList2.initialise();

	

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

	//////////////////////////////////////////////////////////////////////////

	WizardPropertySheet*   psheet   =  
		(WizardPropertySheet*)  GetParent();         
	////assert( psheet->_demBag == NULL );

	vgKernel::StringVectorPtr pdems = 
		psheet->_listItemCtrl->getDemFileNameVector();

	vgKernel::StringVectorPtr pimgs = 
		psheet->_listItemCtrl2->getDemFileNameVector();

	assert( pdems.isNull() == false );


	//------------------------------------------
	// 设置overview标记 
	//------------------------------------------
	UpdateData( TRUE );
	vgTerritory::GeoDemManager::getSingleton().setOverviewFlag( 
		_genMeshOverview , _genTexOverview );


	m_nPos			= 0;
	m_currentTaskID		= 0;
	m_sTaskList.RemoveAll();
	m_sTaskList.Add(_T("Step 1: 预读取高程数据并生成预览图."));
	m_sTaskList.Add(_T("Step 2: 读取影像数据并生成预览图."));
	m_nTotalTasks	= m_sTaskList.GetSize();


	assert( m_pTaskDlg == NULL );
	m_pTaskDlg = new CTaskProgressDialog();
	m_pTaskDlg->SetTasks(m_sTaskList);
	m_pTaskDlg->Create();

	m_pTaskDlg->ShowWindow(SW_SHOW);

	m_pTaskDlg->enableCanelButton( false );
	m_pTaskDlg->SetWindowText("正在生成预览图, 请稍候...");



	//------------------------------------------
	// 开始添加文件
	//------------------------------------------
	m_currentTaskID = 0;

	if( vgTerritory::GeoDemManager::getSingleton().addGeoDemAndCheckValid( pdems ) 
		== false )
	{
		return FALSE;
	}

	m_currentTaskID = 1;

	if ( pimgs.isNull() == false)
	{
		if ( pimgs->empty() == false )
		{
			bool addok = vgTerritory::GeoDemManager::getSingleton().addGeoImages( pimgs );

			if ( addok == false )
			{
				return FALSE;
			}
		}
	}

	if ( m_pTaskDlg != NULL )
	{
		delete m_pTaskDlg;
		m_pTaskDlg = NULL;
	}

	vgTerritory::GeoDemManager::getSingleton().clearProcessObservers();

	return CPropertyPage::OnWizardNext();
}

void WizardPage2::onStart( const String& text , const int& range_lower , const int& range_upper )
{
	m_pTaskDlg->SetCurTask( m_currentTaskID );
	m_pTaskDlg->SetRange( range_lower , range_upper  );
	m_pTaskDlg->SetStatus(text.c_str() );
}

void WizardPage2::onFinish( const String& msg )
{
	m_pTaskDlg->setPosToMax();
}

void WizardPage2::onNotify( const String& msg , const int& process_pos )
{
	//_progressOverview.SetPos( process_pos );

	_progressMsg = "正在处理:" ;
	_progressMsg += msg.c_str();
	_progressMsg += "... ";

	//_progressOverview.SetWindowText( _progressMsg );

	//_progressOverview.RedrawWindow();

	//UpdateData( FALSE );	

	m_pTaskDlg->SetCurTask( m_currentTaskID );
	m_pTaskDlg->SetPos( process_pos );
	m_pTaskDlg->SetStatus( _progressMsg );

}

void WizardPage2::OnBnClickedImport2()
{
	CString DefExt;

	DefExt.Format("%s","tif文件(*.tif)|*.tif|(*.sid)|*.sid|(*.*)|*.*|");

	CFileDialog dlgmodelFile(true,"tif",
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
	dlgmodelFile.m_ofn.lpstrTitle="image文件导入";

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
		_importList2.updateDems( strVec );
	}

}

void WizardPage2::OnBnClickedClearAll2()
{
	_importList2.clearAll();
}



