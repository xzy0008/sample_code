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

// WizardPage4 dialog

IMPLEMENT_DYNAMIC(WizardPage4, CPropertyPage)

WizardPage4::WizardPage4()
	: CPropertyPage(WizardPage4::IDD)
	, _processMsg(_T(""))
	, _showMsgResize(_T("未完成"))
	, _showMsgCut(_T("未完成"))
	, _showMsgVgtr(_T("未完成"))
	, _showMsgClean(_T("未完成"))
{
	m_psp.dwFlags |= PSP_DEFAULT|PSP_USEHEADERTITLE|PSP_USEHEADERSUBTITLE;

	m_psp.pszHeaderTitle = _T("第3步");
	m_psp.pszHeaderSubTitle = _T("处理数据");

	_currentProcessBar = NULL;

	_currentMsg = NULL;
}

WizardPage4::~WizardPage4()
{
}

void WizardPage4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX ,IDC_PROCESS_MESSAGE,_processMsg );
	DDX_Text(pDX ,IDC__PROCESS_MSG_RESIZE ,_showMsgResize );
	DDX_Text(pDX ,IDC__PROCESS_MSG_CUT ,_showMsgCut );
	DDX_Text(pDX ,IDC__PROCESS_MSG_VGTR ,_showMsgVgtr );
	DDX_Text(pDX ,IDC__PROCESS_MSG_CLEAN ,_showMsgClean );

	DDX_Control(pDX, IDC_PROGRESS_IMG_RESIZE, _processBarOfResizing);
	DDX_Control(pDX, IDC_PROGRESS_IMG_CUT, _processBarOfCutting);
	DDX_Control(pDX, IDC_PROGRESS_VGTR, _processBarOfVgtr);
	DDX_Control(pDX, IDC_PROGRESS_CLEAN, _processBarOfClean);

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
	WizardPropertySheet* psheet = (WizardPropertySheet*)GetParent();      

	WizardPage3* page3 = ( WizardPage3* )(psheet->GetPage( 2 ));

	_startBtn.EnableWindow(FALSE);


	psheet->_demBag->registerProcessObs( this );

	//------------------------------------------
	// 获得参数
	//------------------------------------------
	long N = page3->_terrainN;

	long imgsize = (long)pow( 2.0f, page3->_terrainN ) * page3->_scaleDemToImg;
	assert( imgsize > 0 );

	String terrain_name = page3->_terrainName.GetBuffer(0);


	String aimfileprefix = page3->_selectOuputFolder.GetBuffer(0);
	aimfileprefix += "\\";
	aimfileprefix += page3->_terrainName.GetBuffer(0);


	String saveVgtrPath = page3->_selectOuputFolder.GetBuffer(0);
	saveVgtrPath += "\\";

	String saveVgiPath = page3->_selectOuputFolder.GetBuffer(0);
	saveVgiPath += "\\";
	saveVgiPath += page3->_terrainName + ".vgi";

	String saveVtrPath = page3->_selectOuputFolder.GetBuffer(0);
	saveVtrPath += "\\";
	saveVtrPath += page3->_terrainName + ".vtr";

	String tempPath = page3->_selectedFolder.GetBuffer(0);

	StringVectorPtr outddsnames( new StringVector );


	//------------------------------------------
	// 1.首先开始对图像进行resize操作
	//------------------------------------------
	_currentProcessBar = &_processBarOfResizing;
	_currentMsg = &_showMsgResize;
	assert( psheet->_demBag != NULL );

	if ( psheet->_demBag->getScaleOfDemToImg() != page3->_scaleDemToImg )
	{
		//------------------------------------------
		// 这个时候需要重新resize一下
		//------------------------------------------
		bool resizeres = 
			psheet->_demBag->resizeImages( page3->_scaleDemToImg , tempPath);

		if ( resizeres == false )
		{
			MessageBox("操作影像数据时产生错误." ,"error");
			return;
		}
	}
	else
	{
		onFinish("操作完成");
	}

	_showMsgResize = "已完成";
	UpdateData( FALSE );
	//------------------------------------------
	// 2.开始对图像进行切割操作
	//------------------------------------------
	_currentProcessBar = &_processBarOfCutting;
	_currentMsg = &_showMsgCut;

	// 计算层级
	long width = psheet->_demBag->getDemWidth();
	assert( width != 0 );
	assert( width % 2 == 0 );

	assert( width % (int)pow( 2.0, N )  == 0 );

	float tmpnum =  log( (float) (width / (int)pow( 2.0, N )  ) );

	long layernum = (int)( tmpnum / log( 2.0f ) );

	for ( int i = 0 ; i < layernum ; ++ i )
	{
		std::ostringstream o;
		o << aimfileprefix << "_level" << i;

		vgTerritory::HugeImagesProcessor imgprocessor;
		vgTerritory::HugeImageBlockInfoVectorPtr vgtrinfovec;

		imgprocessor.registerProcessObs( this );

		try 
		{
			imgprocessor.initialiseFileBlocks( psheet->_demBag->getFileBlockVec() );

			imgprocessor.initialiseParameters( o.str() , 
				imgsize , imgsize ,"bmp","dds",false,true,false,true
				,false,"",false,"",
				false, //是否写上调试信息
				vgKernel::ImagePos::ZERO ,0, -1);

			//imgprocessor.makeProcessing();
			imgprocessor.makeProcessingAndSaving();

			vgtrinfovec = imgprocessor.getHugeImageBlockInfos();

			//------------------------------------------
			// resize到一半的长宽. 最后一次不需要
			//------------------------------------------
			if ( i != layernum - 1)
			{
				psheet->_demBag->resizeImageForLod( tempPath );
			}

			//------------------------------------------
			// 插入到output队列,便于删除
			//------------------------------------------
			vgTerritory::HugeImageBlockInfoVector::iterator iter = vgtrinfovec->begin();
			vgTerritory::HugeImageBlockInfoVector::iterator iter_end = vgtrinfovec->end();

			vgKernel::StringVectorPtr ddsnames( new vgKernel::StringVector );

			for ( ; iter != iter_end ; ++ iter )
			{
				if ( vgKernel::SystemUtility::checkFileExist( iter->m_BlockFileName) )
				{
					outddsnames->push_back( iter->m_BlockFileName );
				}
			}
		}
		catch ( vgKernel::Exception *e ) 
		{
			::MessageBox( NULL , e->getFullDescription().c_str() , "error!" , MB_OK );
			return;
		}
		catch (...)
		{
			assert(0);
			return;
		}
	}

	_showMsgCut = "已完成";
	UpdateData( FALSE );
	//------------------------------------------
	// 3.最后生成vgtr
	//------------------------------------------
	_currentProcessBar = &_processBarOfVgtr;
	_currentMsg = &_showMsgVgtr;

	bool savevtrok = psheet->_demBag->saveToVtr( outddsnames , 
		terrain_name , 
		saveVgtrPath , N );
	assert( savevtrok == true );
	if ( savevtrok == false )
	{
		MessageBox("保存vgtr时出现错误","error");
		return;
	}
    

	_showMsgVgtr = "已完成";
	UpdateData( FALSE );
	//------------------------------------------
	// 4.清理操作.包括生成vgi和删除临时文件 
	//------------------------------------------
	_currentProcessBar = &_processBarOfClean;
	_currentMsg = &_showMsgClean;

	// 生成vgi
	assert( outddsnames.isNull() == false );


	vgImage::FileWriterDdsToVgi vgiwriter;

	vgiwriter.registerProcessObs( this );

	bool writeok = vgiwriter.writeToVgiFileFromDdsNames(
		outddsnames , saveVgiPath );

	if ( writeok == false )
	{
		MessageBox("出错, 请检查DDS文件.");
		return;
	}

	// 清理操作
	// 清除中间的文件
	psheet->_demBag->clearTempFiles();

	// 清除dds文件
	{
		StringVector::iterator iter = outddsnames->begin();
		StringVector::iterator iter_end = outddsnames->end();
		for ( ; iter != iter_end ; ++ iter )
		{
			vgKernel::SystemUtility::removeFile( *iter );
		}
	}


	_showMsgClean = "已完成";
	UpdateData( FALSE );

	//------------------------------------------
	// 处理显示
	//------------------------------------------
	_processMsg = "已完成,单击下一步查看报告.";
	psheet->SetWizardButtons(PSWIZB_NEXT);   

	UpdateData( FALSE );
}

void WizardPage4::onStart( const String& text , const int& range_lower , const int& range_upper )
{
	_currentProcessBar->SetRange32( range_lower , range_upper );

	_processMsg = text.c_str();

	UpdateData( FALSE );
	Invalidate();
}

void WizardPage4::onNotify( const String& msg , const int& process_pos )
{
	_currentProcessBar->SetPos( process_pos );

	_processMsg = msg.c_str();

	UpdateData( FALSE );	
	Invalidate();
}

void WizardPage4::onFinish( const String& msg )
{
	int lower = 0;
	int upper = 0;


	_processMsg = msg.c_str();

	_currentProcessBar->GetRange( lower , upper );
	_currentProcessBar->SetPos( upper );

	//*_currentMsg = "已完成";
	UpdateData( FALSE );
	Invalidate();

}