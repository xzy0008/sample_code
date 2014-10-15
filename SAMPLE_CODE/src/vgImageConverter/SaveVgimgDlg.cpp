// SaveVgimgDlg.cpp : implementation file
//

#include <vgStableHeaders.h>
#include "VgimgReader.h"
#include "SaveVgimgDlg.h"
#include "SaveVgimg_ImportFileDlg.h"
#include "SaveVgimg_ConfigSelectedDlg.h"

#include <vgImage/vgiBatchProcessor.h>




// CSaveVgimgDlg dialog

IMPLEMENT_DYNAMIC(CSaveVgimgDlg, CDialog)

CSaveVgimgDlg::CSaveVgimgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveVgimgDlg::IDD, pParent)
	, m_AimFilePath(_T(""))
	, m_dxt_select(0)
	, _imgScaleRatio(1.0f)
	, m_bAddNameSuffix(TRUE)
	, m_bTga2Dtx3(TRUE)
{
	m_CurrentFileID = 0;
}

CSaveVgimgDlg::~CSaveVgimgDlg()
{
}

void CSaveVgimgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_wndList);
	DDX_Text(pDX, IDC_SAVEVGIMG_AIMFILE_PATH, m_AimFilePath);
	DDX_Radio(pDX, IDC_RADIO1_DXT, m_dxt_select);
	DDX_Text(pDX, IDC_IMAGE_SCALE_RATIO, _imgScaleRatio);
	DDX_Check(pDX, IDC_CHECK1, m_bAddNameSuffix);
	DDX_Check(pDX, IDC_CHECK2, m_bTga2Dtx3);
}


BEGIN_MESSAGE_MAP(CSaveVgimgDlg, CDialog)
ON_BN_CLICKED(IDC_IMPORT_FILES, &CSaveVgimgDlg::OnBnClickedImportFiles)
	ON_BN_CLICKED(IDC_BUTTON2, &CSaveVgimgDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_SAVEVGIMG_SAVEFILELIST, &CSaveVgimgDlg::OnBnClickedSavevgimgSavefilelist)
	ON_BN_CLICKED(IDC_BUTTON4, &CSaveVgimgDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_SAVEVGIMG_SELECTEDALL, &CSaveVgimgDlg::OnBnClickedSavevgimgSelectedall)
	ON_BN_CLICKED(IDC_SAVEVGIMG_CANCELSELECTED, &CSaveVgimgDlg::OnBnClickedSavevgimgCancelselected)
	ON_BN_CLICKED(IDC_SAVEVGIMG_INVERTSELECTED, &CSaveVgimgDlg::OnBnClickedSavevgimgInvertselected)
	ON_BN_CLICKED(IDC_SAVEVGIMG_DELETESELECTED, &CSaveVgimgDlg::OnBnClickedSavevgimgDeleteselected)
	ON_BN_CLICKED(IDC_SAVEVGIMG_AIMFILE_OPEN, &CSaveVgimgDlg::OnBnClickedSavevgimgAimfileOpen)
	ON_BN_CLICKED(IDC_SAVEVGIMG_IMPORTFILELIST, &CSaveVgimgDlg::OnBnClickedSavevgimgImportfilelist)
	ON_BN_CLICKED(IDC_SAVEVGIMG_CONFIGSELECTED, &CSaveVgimgDlg::OnBnClickedSavevgimgConfigselected)
	ON_BN_CLICKED(IDC_DDS_SAVe, &CSaveVgimgDlg::OnBnClickedDdsSave)
END_MESSAGE_MAP()


// CSaveVgimgDlg message handlers

void CSaveVgimgDlg::OnBnClickedImportFiles()
{

	// TODO: Add your control notification handler code here
	CSaveVgimg_ImportFileDlg dlg;
	dlg.DoModal();

	StringVectorPtr files = dlg.getSelectedFilesVector();

	if ( files.isNull() )
	{
		return;
	}

	StringVector::iterator iter = files->begin();
	StringVector::iterator iter_end = files->end();

	
	vgKernel::StringPairVectorPtr pResult( new vgKernel::StringPairVector );
	pResult->reserve( files->size() );

	for ( ; iter != iter_end ; ++ iter )
	{
		assert( *iter != "" );
		
		pResult->push_back( std::make_pair( *iter , *iter ) );

		const int IDX = m_wndList.InsertItem(0, _T(""));
		m_wndList.SetItemText(IDX, 0, m_CurrentFileID++ );

		String basename = getBasenameFromFilepath( *iter );
		m_wndList.SetItemText(IDX, 1, basename.c_str() );
		m_wndList.SetItemText(IDX, 2, iter->c_str() );

		StringUtility::toLowerCase( basename );

		String ddsfilename = 
			basename.substr( 0 , basename.find_last_of(".") ) + ".dds";

		m_wndList.SetItemText(IDX, 3, ddsfilename.c_str() );
	}


	m_wndList.SortItems( 0 , true );

	m_wndList.UpdateData();

	UpdateData(true);


}

BOOL CSaveVgimgDlg::OnInitDialog()
{
	std::locale::global(std::locale("CHS"));

	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	m_wndList.SetColumnHeader(_T("序号, 40;源文件名, 100;源文件路径, 250; 目标文件名, 80"));

	//for (int i = 0; i < 10; i++)
	//{
	//	const int IDX = m_wndList.InsertItem(0, _T(""));
	//	m_wndList.SetItemText(IDX, 0, i );
	//	m_wndList.SetItemText(IDX, 1, rand() % 3000);
	//	m_wndList.SetItemText(IDX, 2, "ffff");
	//	m_wndList.SetItemText(IDX, 3, (rand() % 51) + 50);

	//	m_CurrentFileID ++;
	//	//for (int j = 0; j < 2; j++)
	//	//	m_wndList.SetItemImage(IDX, j, rand() % 5); // subitem images
	//}

	//m_wndList.SetImageList(IDB_BITMAP1);
	//m_wndList.SetHeaderImageList(IDB_BITMAP2);
	//m_wndList.SetHeaderImage(0, 0);
	//m_wndList.SetHeaderImage(1, 2, FALSE);
	//m_wndList.SetHeaderImage(2, 1);
	m_wndList.SetGridLines(TRUE); // SHow grid lines
	//m_wndList.SetCheckboxeStyle(RC_CHKBOX_NORMAL); // Enable checkboxes
	m_wndList.SetEditable(TRUE); // Allow sub-text edit
	m_wndList.SortItems(0, TRUE); // sort the 1st column, ascending

	m_bSortable = m_wndList.IsSortable();
	UpdateData(FALSE);

	//GetDlgItem(IDC_ALLOWSORT)->EnableWindow(m_wndList.HasColumnHeader());

	// now play some colorful stuff

	// Set the 3rd column background color to yellow, text color to blue
	//m_wndList.SetItemTextColor(-1, 2, RGB(0, 0, 0));
	//m_wndList.SetItemBkColor(-1, 2, RGB(255, 255, 0));



	//for (int n = 0; n < m_wndList.GetItemCount(); n++)
	//{
	//	const int SCORE = _ttoi(m_wndList.GetItemText(n, 2)); // student score

	//	if (SCORE < 60)
	//	{
	//		m_wndList.SetItemBkColor(n, -1, ::GetSysColor(COLOR_INFOBK));
	//		m_wndList.SetItemTextColor(n, -1, RGB(255, 0, 0));

	//		m_wndList.SetItemBkColor(n, 2, RGB(255, 0, 0));
	//		m_wndList.SetItemTextColor(n, 2, RGB(255, 255, 255));
	//	}
	//	else if (SCORE > 90)
	//	{
	//		m_wndList.SetItemBkColor(n, -1, RGB(160, 255, 192));
	//		m_wndList.SetItemTextColor(n, -1, RGB(0, 0, 255));

	//		m_wndList.SetItemTextColor(n, 2, RGB(255, 255, 255));
	//		m_wndList.SetItemBkColor(n, 2, RGB(0, 160, 0));
	//	}
	//}	



	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSaveVgimgDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	//m_wndList.RemoveAllGroups();
	m_wndList.DeleteAllItems();
}

void CSaveVgimgDlg::OnBnClickedSavevgimgSavefilelist()
{
	// TODO: Add your control notification handler code here

	char szFilters[]=
		"images list Files (*.vgilt)|*.vgilt|All Files (*.*)|*.*||";

	CFileDialog fileDlg (false, "vgilt", "*.vgilt",
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);

	if( fileDlg.DoModal ()==IDOK )
	{
		String pathName = fileDlg.GetPathName();

		CString fileName = fileDlg.GetFileTitle ();

		SetWindowText(fileName);

		// 保存文件列表
		{
			int count = m_wndList.GetItemCount();
			
			for ( int i =  0 ; i < count ; ++i )
			{

			}
		}

	}

}

void CSaveVgimgDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	//bool selected = m_wndList.IsItemSelected( 0 );
	int selected = m_wndList.GetSelectedItemCount();

	//m_wndList.SelectItem( 3 , true );

	//m_wndList.SelectAllItems();
	m_wndList.UnSelectAllItems();
	//MessageBox( ConvertUtil::textCast<int>(selected).c_str() );
}

void CSaveVgimgDlg::OnBnClickedSavevgimgSelectedall()
{
	// TODO: Add your control notification handler code here
	m_wndList.SelectAllItems();
}

void CSaveVgimgDlg::OnBnClickedSavevgimgCancelselected()
{
	// TODO: Add your control notification handler code here
	m_wndList.UnSelectAllItems();
}

void CSaveVgimgDlg::OnBnClickedSavevgimgInvertselected()
{
	// TODO: Add your control notification handler code here
	m_wndList.InvertSelect();
}

void CSaveVgimgDlg::OnBnClickedSavevgimgDeleteselected()
{
	// TODO: Add your control notification handler code here
	m_wndList.DeleteAllSelectedItems();
}

void CSaveVgimgDlg::OnBnClickedSavevgimgAimfileOpen()
{
	// TODO: Add your control notification handler code here
	char szFilters[]=
		"";

	//CFileDialog fileDlg (true, "vgimg", "*.vgimg",
	//	OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);
	/*

	CFileDialog fileDlg (false, "", "",
		NULL, NULL, this);

	if( fileDlg.DoModal ()==IDOK )
	{
		CString pathName = fileDlg.GetPathName();

		CString fileName = fileDlg.GetFileTitle ();

		SetWindowText(fileName);

		SetDlgItemText( IDC_SAVEVGIMG_AIMFILE_PATH , pathName );
	}

	*/

	CString   strFilePath;   
	TCHAR   pszBuffer[_MAX_PATH];   
	BROWSEINFO   bi;   LPITEMIDLIST   pidl;   
	bi.hwndOwner   =   NULL;   
	bi.pidlRoot   =   NULL;   
	bi.pszDisplayName   =   pszBuffer;   
	bi.lpszTitle   =   _T("选择目标文件路径");   
	bi.ulFlags   =   BIF_RETURNFSANCESTORS   |   BIF_RETURNONLYFSDIRS;   
	bi.lpfn   =   NULL;   
	bi.lParam   =   0;   
	if((pidl   =   SHBrowseForFolder(&bi))   !=   NULL)   
	{   
		if(SHGetPathFromIDList(pidl,   pszBuffer))   
		{   
			CString   strTemp(pszBuffer);       strFilePath   =   strTemp;   
			if   (strFilePath.GetLength()   <=   1)     
			{   
			}   
			else   if   (strFilePath.Right(1)   !=   _T("\\"))     
				strFilePath   +=   _T("\\");   
		}   

		
	}   
	

	SetDlgItemText( IDC_SAVEVGIMG_AIMFILE_PATH , strFilePath );

}

void CSaveVgimgDlg::OnBnClickedSavevgimgImportfilelist()
{
	// TODO: Add your control notification handler code here

	char szFilters[]=
		"images list Files (*.vgilt)|*.vgilt|All Files (*.*)|*.*||";

	CFileDialog fileDlg (TRUE, "vgilt", "*.vgilt",
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);

	if( fileDlg.DoModal ()==IDOK )
	{
		String pathName = fileDlg.GetPathName();

		CString fileName = fileDlg.GetFileTitle ();

		SetWindowText(fileName);

		// 保存文件列表
		{
			int count = m_wndList.GetItemCount();

			for ( int i =  0 ; i < count ; ++i )
			{

			}
		}

	}


}

void CSaveVgimgDlg::OnBnClickedSavevgimgConfigselected()
{
	// TODO: Add your control notification handler code here

	CSaveVgimg_ConfigSelectedDlg dlg;
	dlg.DoModal();

}

///newadding...begin
int getNearestPowerOfTwoNumber( const int& inputNum )
{
	if ( inputNum == 0 || inputNum < 0 )
	{
		assert(0);
		return 0 ;
	}

	int left = inputNum;

	int aim = 1;

	do 
	{
		left /= 2;

		aim *= 2;

	} while( left != 0);


	int s = aim/2;

	int b = aim;

	return ( (b - inputNum) >= ( inputNum - s) ) ? s : b;


}

///newadding...end


void CSaveVgimgDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnOK();
}

void CSaveVgimgDlg::OnBnClickedDdsSave()
{
	// TODO: Add your control notification handler code here

	UpdateData();

	if ( _imgScaleRatio < 0.0f || _imgScaleRatio > 1.0f )
	{
		MessageBox("缩放参数输入不正确!请输入0.0到1.0之间的数.");
		return;
	}

	saveDDSImplement();


	return;

}

void CSaveVgimgDlg::saveDDSImplement()
{

	StringVectorPtr src_imgs( new StringVector );
	StringVectorPtr src_imgsTga( new StringVector );


	GLenum ddsformat;


	switch( m_dxt_select )
	{
	case 0: 
		ddsformat = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case 1: 
		ddsformat = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case 2: 
		ddsformat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		::MessageBox(NULL, "select error!" , "error" , MB_OK );
		return;
	}



	int   nCount   =   m_wndList.GetItemCount();   
	if ( nCount == 0 )
	{
		return;
	}

	//----------------------------------------------------------------
	typedef std::map<String,String> StringMap;

	StringVector errFiles;
	StringMap* strmap = new StringMap;
	StringMap* strmapTga = new StringMap;

	int i;
	for( i = 0 ; i != nCount ; ++ i )   
	{   
		TCHAR szBuffer[1024];
		DWORD cchBuf(1024);
		LVITEM lvi;
		lvi.iItem = i;
		lvi.iSubItem = 2;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = szBuffer;
		lvi.cchTextMax = cchBuf;
		m_wndList.GetItem(&lvi);

		String src( lvi.pszText );

		String metaname = 
			StringUtility::getFilenameWithoutExtFromAbsPath( src );

		if ( metaname.empty() == true )
		{
			continue;
		}

		if ( getFlagAddNameSuffix() )
		{
			metaname += "_";
			metaname += StringUtility::getFileExtension( src );
		}

		std::pair<StringMap::iterator, bool> insertres;
		if( StringUtility::getFileExtension( src ) == "tga" )
		{
			insertres = strmapTga->insert( std::make_pair( metaname , src ) );
		}
		else
		{
			insertres = strmap->insert( std::make_pair( metaname , src ) );
		}
		
		if ( insertres.second == false )
		{
			if ( StringUtility::getFileExtension( src ) == "tga" )
			{
				String old = insertres.first->second;
				insertres.first->second = src;
				errFiles.push_back( old );
			}
			else
			{
				errFiles.push_back( src );
			}
		}
	} 

	if ( m_AimFilePath == "" )
	{
		if( IDYES == MessageBox( "未设置目标文件路径, 默认存放在第一个源文件夹下.", "", MB_YESNO) )
		{
			assert( strmap->empty() == false );
			String src = strmap->begin()->second;
			String path = StringUtility::getPathFromAbsoluteFilename( src );
			m_AimFilePath = path.c_str();
			assert( m_AimFilePath != "" );
		}	
		else
		{
			delete strmap;
			return;
		}
	}

	//------------------------------------------
	// 检查重名的文件名
	//------------------------------------------
	{
		StringMap::iterator iter  = strmap->begin();
		StringMap::iterator iter_end = strmap->end();

		for ( ; iter != iter_end ; ++ iter )
		{
			src_imgs->push_back( iter->second );
		}

		delete strmap;
	}
	{
		StringMap::iterator iter  = strmapTga->begin();
		StringMap::iterator iter_end = strmapTga->end();

		for ( ; iter != iter_end ; ++ iter )
		{
			src_imgsTga->push_back( iter->second );
		}

		delete strmapTga;
	}
	//------------------------------------------
	//  同名文件提示
	//------------------------------------------
	{
		if ( errFiles.empty() == false )
		{
			std::ostringstream o;
			StringVector::iterator iter  = errFiles.begin();
			StringVector::iterator iter_end = errFiles.end();

			o << "下列文件:\n";
			for ( ; iter != iter_end ; ++ iter )
			{
				o << *iter << "\n" ;
			}

			o << "存在同名, 这些文件将被忽略.";

			MessageBox( o.str().c_str() );
		}
	}
 

	String aim_path( m_AimFilePath.GetBuffer(0) );

	float resizeRatio = _imgScaleRatio;

	using namespace vgImage;


	//------------------------------------------
	// 进度条
	//------------------------------------------


	m_nPos			= 0;
	m_currentTaskID		= 0;
	m_sTaskList.RemoveAll();
	m_sTaskList.Add(_T("开始生成顺序生成dds..."));
	m_nTotalTasks	= m_sTaskList.GetSize();

	m_pTaskDlg = NULL;

	assert( m_pTaskDlg == NULL );
	m_pTaskDlg = new CTaskProgressDialog();
	m_pTaskDlg->SetTasks(m_sTaskList);
	m_pTaskDlg->Create();

	m_pTaskDlg->ShowWindow(SW_SHOW);

	m_pTaskDlg->enableCanelButton( false );
	m_pTaskDlg->SetWindowText("请稍候...");
	m_currentTaskID = 0;


	//------------------------------------------
	// 核心处理函数
	//------------------------------------------
	ProcessNotifier notifier;
	notifier.registerProcessObs( this );

	StringVectorPtr Ret( new StringVector );

	Ret = BatchProcessor::process( src_imgs , aim_path , "dds" , 
		ddsformat , &notifier , false , resizeRatio , getFlagAddNameSuffix()/*true*/ );

	GLenum ddsformatTga = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
	Ret = BatchProcessor::process( src_imgsTga , aim_path , "dds" , 
		ddsformatTga , &notifier , false , resizeRatio , getFlagAddNameSuffix()/*true*/ );



	if ( m_pTaskDlg != NULL )
	{
		delete m_pTaskDlg;
		m_pTaskDlg = NULL;
	}

	if (Ret != StringVectorPtr())
	{
		std::ostringstream o;
		o << "文件制作完成, 存放路径:" << aim_path /*<<",共"<< size << "个文件"*/;

		MessageBox( o.str().c_str() );
	}


	this->OnOK();

}


String CSaveVgimgDlg::getBasenameFromFilepath( const String& filepath )
{
	String basename , path ;

	vgKernel::StringUtility::splitFilename( filepath , basename , path  );
	return basename;
}

void CSaveVgimgDlg::onStart( const String& text , const int& range_lower , const int& range_upper )
{
	m_pTaskDlg->SetCurTask( m_currentTaskID );
	m_pTaskDlg->SetRange( range_lower , range_upper  );
	m_pTaskDlg->SetStatus(text.c_str() );
}

void CSaveVgimgDlg::onNotify( const String& msg , const int& process_pos )
{



	//_progressOverview.SetWindowText( _progressMsg );

	//_progressOverview.RedrawWindow();

	//UpdateData( FALSE );	

	m_pTaskDlg->SetCurTask( m_currentTaskID );
	m_pTaskDlg->SetPos( process_pos );
	m_pTaskDlg->SetStatus( msg.c_str() );
}

void CSaveVgimgDlg::onFinish( const String& msg )
{
m_pTaskDlg->setPosToMax();
}
bool CSaveVgimgDlg::getFlagAddNameSuffix()
{
	return m_bAddNameSuffix;
}