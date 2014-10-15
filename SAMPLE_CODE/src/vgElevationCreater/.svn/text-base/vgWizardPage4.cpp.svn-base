// G:\#NewWorkingFolders\vrgis_2.0_terrain\RealityFramework_BCG8\src\vgTerrainCreater\vgWizardPage4.cpp : implementation file
//

#include <vgStableHeaders.h>
#include "vgWizardPage3.h"
#include "vgWizardPage4.h"
#include "vgWizardPropertySheet.h"
#include <vgTerritory/vgTerrainHugeImageProcessor.h>
#include <vgImage/vgiFileWriterDdsToVgi.h>
#include <vgKernel/vgkSystemUtility.h>
#include <vgTerritory/vgtFileWriterVgtrToVtr.h>
#include <vgTerritory/vgtGeoDemManager.h>

#include "WizardSheet.h"

// WizardPage4 dialog

IMPLEMENT_DYNAMIC(WizardPage4, CPropertyPage)

WizardPage4::WizardPage4()
	: CPropertyPage(WizardPage4::IDD)
	, _genMesh( TRUE )
{
	m_psp.dwFlags |= PSP_DEFAULT|PSP_USEHEADERTITLE|PSP_USEHEADERSUBTITLE;

	m_psp.pszHeaderTitle = _T("第3步");
	m_psp.pszHeaderSubTitle = _T("处理数据");



	m_nTotalTasks = 0;


	m_nPos			= 0;
	m_curTaskID		= 0;
	m_sTaskList.RemoveAll();
	m_pTaskDlg = NULL;
}

WizardPage4::~WizardPage4()
{
	if ( m_pTaskDlg != NULL )
	{
		delete m_pTaskDlg;
		m_pTaskDlg = NULL;
	}
}

void WizardPage4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_GEN_MESH, _genMesh);
	DDX_Check(pDX, IDC_CHECK_GEN_TEX, _genImage);
	DDX_Check(pDX, IDC_CHECK_DELETE_TEMP_FILES, _deleteTempFiles);
	DDX_Check(pDX, IDC_CHECK_GEN_TEX_USE_MESH, _genTexUseMesh);

	DDX_Control(pDX, IDC_PROCESS_START, _startBtn);
}


BEGIN_MESSAGE_MAP(WizardPage4, CPropertyPage)
	ON_BN_CLICKED(IDC_PROCESS_START, &WizardPage4::OnBnClickedProcessStart)
END_MESSAGE_MAP()


// WizardPage4 message handlers

BOOL WizardPage4::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here

	_genMesh = TRUE;
	_genImage = TRUE;
	_deleteTempFiles = TRUE;
	_genTexUseMesh = FALSE;


	UpdateData( FALSE );

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL WizardPage4::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class

	WizardPropertySheet* psheet = (WizardPropertySheet*)GetParent();         

	WizardPage3* page3 = ( WizardPage3* )(psheet->GetPage( 2 ));



	//if ( psheet->_demBag->getScaleOfDemToImg() != page3->_scaleDemToImg )
	//{
	//	_startBtn.EnableWindow(TRUE);
	//	psheet->SetWizardButtons(PSWIZB_BACK);  
	//}
	//else
	//{
	//	_startBtn.EnableWindow(FALSE);
	//	psheet->SetWizardButtons(PSWIZB_NEXT);  
	//}

	return CPropertyPage::OnSetActive();
}

void WizardPage4::OnBnClickedProcessStart()
{

	vgTerritory::GeoDemManager::getSingleton().clearProcessObservers();
	vgTerritory::GeoDemManager::getSingleton().registerProcessObs( this );
	
	WizardPropertySheet* psheet = (WizardPropertySheet*)GetParent();      

	WizardPage3* page3 = ( WizardPage3* )(psheet->GetPage( 2 ));

	_startBtn.EnableWindow(FALSE);

	
	UpdateData( TRUE );

	//------------------------------------------
	// 进度条设置
	//------------------------------------------
	m_nPos			= 0;
	m_curTaskID		= 0;
	m_sTaskList.RemoveAll();

	const int StepId_1 = 0;
	const int StepId_2 = 1;
	const int StepId_3 = 2;
	const int StepId_4 = 3;
	const int StepId_5 = 4;
	const int StepId_6 = 5;
	const int StepId_7 = 6;


	m_sTaskList.Add(_T("Step 1: 保存高程数据到二进制文件."));
	m_sTaskList.Add(_T("Step 2: 切割高程数据, 生成vtr文件."));
	m_sTaskList.Add(_T("Step 3: 通过高度图生成影像文件."));
	m_sTaskList.Add(_T("Step 4: 将高度图影像切割, 创建金字塔."));
	m_sTaskList.Add(_T("Step 5: 预处理影像文件, 做适当的切割, 分块处理."));
	m_sTaskList.Add(_T("Step 6: 操作影像文件, 生成vgi文件."));
	m_sTaskList.Add(_T("Step 7: 删除临时文件."));

	m_nTotalTasks	= m_sTaskList.GetSize();

	if ( m_pTaskDlg != NULL )
	{
		delete m_pTaskDlg;
		m_pTaskDlg = NULL;
	}

	assert( m_pTaskDlg == NULL );
	m_pTaskDlg = new CTaskProgressDialog();
	m_pTaskDlg->SetTasks(m_sTaskList);
	m_pTaskDlg->Create();

	m_pTaskDlg->ShowWindow(SW_SHOW);

	m_pTaskDlg->enableCanelButton( false );
	m_pTaskDlg->SetWindowText("正在处理中, 请稍候...");



	//////////////////////////////////////////////////////////////////////////
	//------------------------------------------
	// 写GeoManager的部分
	//------------------------------------------
	//------------------------------------------
	// 获得参数
	//------------------------------------------
	long N = page3->_terrainN;

	long imgsize = (long)pow( 2.0f, page3->_terrainN ) * page3->_scaleDemToImg;
	assert( imgsize > 0 );

	String terrain_name = page3->_terrainName.GetBuffer(0);

	float cellsize = page3->_adjustCellsize;

	String aimfileprefix = page3->_selectOuputFolder.GetBuffer(0);
	aimfileprefix += "\\";
	aimfileprefix += page3->_terrainName.GetBuffer(0);


	String outputpath = page3->_selectOuputFolder.GetBuffer(0);
	String tempPath = page3->_selectedFolder.GetBuffer(0);
	long celltexsize  =page3->_scaleDemToImg;


	// 更新全局信息
	vgTerritory::GeoDemManager::getSingleton().clearOverviews();

	vgTerritory::GeoDemManager::getSingleton().updateGeoDemsSecond();


	uchar color[4];

	color[0] = 127;
	color[1] = 153;
	color[2] = 204;
	color[3] = 255;

	vgKernel::SystemUtility::createDirectory( tempPath );
	vgKernel::SystemUtility::createDirectory( outputpath );

	vgTerritory::GeoDemManager::getSingleton().setGlobalData( 
		terrain_name , tempPath , outputpath,  N , cellsize , celltexsize, 
		_deleteTempFiles , _genTexUseMesh ,color );


	if ( _genMesh )
	{
		m_curTaskID = StepId_1;
		vgTerritory::GeoDemManager::getSingleton().saveDemToImages();

		
		m_curTaskID = StepId_2;
		vgTerritory::GeoDemManager::getSingleton().saveVgtrLayers();
	}

	if ( _genTexUseMesh )
	{
		m_curTaskID = StepId_3;
		vgTerritory::GeoDemManager::getSingleton().saveToDebugImages();
		m_curTaskID = StepId_4;
		vgTerritory::GeoDemManager::getSingleton().saveDebugLayers();
	}
	else if ( _genImage )
	{
		m_curTaskID = StepId_5;
		vgTerritory::GeoDemManager::getSingleton().saveOrthoToImages();
		m_curTaskID = StepId_6;
		vgTerritory::GeoDemManager::getSingleton().saveImageLayers();
	}

	m_curTaskID = StepId_7;
	m_pTaskDlg->SetCurTask( m_curTaskID );
	if ( _deleteTempFiles )
	{
		vgTerritory::GeoDemManager::getSingleton().clearTempData();
	}

	m_pTaskDlg->setPosToMax();

	//////////////////////////////////////////////////////////////////////////
	// 处理显示
	//------------------------------------------
	Sleep(500);

	if ( m_pTaskDlg != NULL )
	{
		delete m_pTaskDlg;
		m_pTaskDlg = NULL;
	}

	psheet->SetWizardButtons(PSWIZB_NEXT);   



	UpdateData( FALSE );


	//------------------------------------------
	// 下一页
	//------------------------------------------

	psheet->SetActivePage( 4 );

}



void WizardPage4::onStart( const String& text , const int& range_lower , 
						  const int& range_upper )
{
	//vgThreads::ScopedLock locker( _taskDlgSect );
 
	if ( m_pTaskDlg == NULL )
	{
		return;
	}

	assert( m_pTaskDlg != NULL );

	m_pTaskDlg->SetCurTask( m_curTaskID );
	m_pTaskDlg->SetRange( range_lower , range_upper  );

	m_pTaskDlg->SetStatus( text.c_str() );
}

void WizardPage4::onNotify( const String& msg , const int& process_pos )
{

	//CWizardSheetApp* app = (CWizardSheetApp*)AfxGetApp();
	//
	//WizardPage4* page4 = ( WizardPage4* )(app->_sheet->GetPage( 3 ));


	//->GetMainWnd()->get

	//vgThreads::ScopedLock locker( _taskDlgSect );

	m_pTaskDlg->SetPos( process_pos );
	m_pTaskDlg->SetStatus( msg.c_str() );
}

void WizardPage4::onFinish( const String& msg )
{
	//vgThreads::ScopedLock locker( _taskDlgSect );

	int lower = 0;
	int upper = 0;

	m_pTaskDlg->setPosToMax();
	m_pTaskDlg->SetStatus( msg.c_str() );

}