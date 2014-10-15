// SaveVgimgDlg.cpp : implementation file
//

#include <vgStableHeaders.h>
#include "VgimgReader.h"
#include "SaveVgimgDlg.h"
#include "SaveVgimg_ImportFileDlg.h"
#include "SaveVgimg_ConfigSelectedDlg.h"


#include <vgKernel/vgkStringUtility.h>
#include <vgDtxCreater/vgiFileWriterDtx.h>
#include <vgTex/vgDtxDeclaration.h>	

// CSaveVgimgDlg dialog

IMPLEMENT_DYNAMIC(CSaveVgimgDlg, CDialog)

CSaveVgimgDlg::CSaveVgimgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveVgimgDlg::IDD, pParent)
	, m_AimFilePath(_T(""))
	, m_dxt_select(0)
	, m_vgimg_filename(_T(""))
// 	, _lod0_factor(0.1)
// 	, _lod1_factor(0.35)
{
	m_CurrentFileID = 0;

	m_timelength = 50;

	m_ratio = 1;
}

CSaveVgimgDlg::~CSaveVgimgDlg()
{
}

void CSaveVgimgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_wndList);
	DDX_Text(pDX, IDC_SAVEVGIMG_AIMFILE_PATH, m_AimFilePath);
	//DDX_Text(pDX, IDC_EDIT1, m_vgimg_filename);
	//DDX_Radio(pDX, IDC_RADIO1, m_dxt_select);
	DDX_Text(pDX, IDC_EDIT1, m_timelength);
// 	DDV_MinMaxFloat(pDX, _lod0_factor, 0.f, 1.f);
	DDX_Text(pDX, IDC_EDIT2, m_ratio);
// 	DDV_MinMaxFloat(pDX, _lod1_factor, 0.f, 1.f);
	DDX_Control(pDX, IDC_PROGRESS_BAR, _processBar);
}


BEGIN_MESSAGE_MAP(CSaveVgimgDlg, CDialog)
ON_BN_CLICKED(IDC_IMPORT_FILES, &CSaveVgimgDlg::OnBnClickedImportFiles)
	ON_BN_CLICKED(IDC_BUTTON2, &CSaveVgimgDlg::OnBnClickedButton2)
//	ON_BN_CLICKED(IDC_SAVEVGIMG_SAVEFILELIST, &CSaveVgimgDlg::OnBnClickedSavevgimgSavefilelist)
//	ON_BN_CLICKED(IDC_BUTTON4, &CSaveVgimgDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_SAVEVGIMG_SELECTEDALL, &CSaveVgimgDlg::OnBnClickedSavevgimgSelectedall)
	ON_BN_CLICKED(IDC_SAVEVGIMG_CANCELSELECTED, &CSaveVgimgDlg::OnBnClickedSavevgimgCancelselected)
	ON_BN_CLICKED(IDC_SAVEVGIMG_INVERTSELECTED, &CSaveVgimgDlg::OnBnClickedSavevgimgInvertselected)
	ON_BN_CLICKED(IDC_SAVEVGIMG_DELETESELECTED, &CSaveVgimgDlg::OnBnClickedSavevgimgDeleteselected)
	ON_BN_CLICKED(IDC_SAVEVGIMG_AIMFILE_OPEN, &CSaveVgimgDlg::OnBnClickedSavevgimgAimfileOpen)
//	ON_BN_CLICKED(IDC_SAVEVGIMG_IMPORTFILELIST, &CSaveVgimgDlg::OnBnClickedSavevgimgImportfilelist)
//	ON_BN_CLICKED(IDC_SAVEVGIMG_CONFIGSELECTED, &CSaveVgimgDlg::OnBnClickedSavevgimgConfigselected)
//	ON_BN_CLICKED(ID_SAVEVGIMG_ONOK, &CSaveVgimgDlg::OnBnClickedSavevgimgOnok)
	ON_BN_CLICKED(IDC_DDS_SAVe, &CSaveVgimgDlg::OnBnClickedDdsSave)
//	ON_BN_CLICKED(IDC_SAVEDDS_AND_VGIMG, &CSaveVgimgDlg::OnBnClickedSaveddsAndVgimg)
//	ON_BN_CLICKED(IDC_SAVE_VGIMG, &CSaveVgimgDlg::OnBnClickedSaveVgimg)
ON_WM_SIZE()
ON_WM_PAINT()
ON_BN_CLICKED(IDC_MOVE_TOP, &CSaveVgimgDlg::OnBnClickedMoveTop)
ON_BN_CLICKED(IDC_MOVE_BOTTOM, &CSaveVgimgDlg::OnBnClickedMoveBottom)
ON_BN_CLICKED(IDC_MOVE_UP, &CSaveVgimgDlg::OnBnClickedMoveUp)
ON_BN_CLICKED(IDC_MOVE_DOWN, &CSaveVgimgDlg::OnBnClickedMoveDown)
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

	StringPairListPtr pResult( new StringPairList() );
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
	}



	//for (int i = 100; i < 110; i++)
	//{
	//	const int IDX = m_wndList.InsertItem(9, _T(""));
	//	m_wndList.SetItemText(IDX, 0, i );
	//	m_wndList.SetItemText(IDX, 1, rand() % 3000);
	//	m_wndList.SetItemText(IDX, 2, "ffff");
	//	m_wndList.SetItemText(IDX, 3, (rand() % 51) + 50);

	//	//for (int j = 0; j < 2; j++)
	//	//	m_wndList.SetItemImage(IDX, j, rand() % 5); // subitem images
	//}

	m_wndList.SortItems( 0 , true );

	m_wndList.UpdateData();

	UpdateData(true);


}

BOOL CSaveVgimgDlg::OnInitDialog()
{
	std::locale::global(std::locale("CHS"));

	CDialog::OnInitDialog();



	//////////////////////////////////////////////////////////////////////////


	m_wndList.SetColumnHeader(_T("序号, 40;源文件名, 100;源文件路径, 250"));



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



	//------------------------------------------
	// 设置OpenGLWindow
	//------------------------------------------
	/***************/
	/* ADDED CODE: */
	/***************/
	CRect rect/*(0,200,300,300)*/;

	//rect.top = 1;
	//rect.bottom = 1;
	//rect.left = 1;
	//rect.right = 1;
	// Get size and position of the template textfield we created before in the dialog editor
// 	GetDlgItem(IDC_SMALL_OPENGL)->GetWindowRect(rect);

	// Convert screen coordinates to client coordinates
	ScreenToClient(rect);



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
	//MessageBox( vgCore::ConvertUtil::textCast<int>(selected).c_str() );
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
		"dynamic texture (*.dtx)|*.dtx|All Files (*.*)|*.*||";

	CFileDialog fileDlg (false, "dtx", NULL,
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);



	if( fileDlg.DoModal ()==IDOK )
	{
		CString pathName = fileDlg.GetPathName();

		CString fileName = fileDlg.GetFileTitle ();

		SetWindowText(fileName);

		SetDlgItemText( IDC_SAVEVGIMG_AIMFILE_PATH , pathName );
	}


	/*
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
	*/
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


	if ( m_AimFilePath == "" )
	{
		MessageBox( "请输入目标文件路径!");
		return;
	}

	int   nCount   =   m_wndList.GetItemCount();   
	if ( nCount == 0 )
	{
		return;
	}

	vgKernel::StringVectorPtr pResult( new vgKernel::StringVector );
	pResult->reserve( nCount );

	FrameVectorPtr pframes( new FrameVector );
	pframes->reserve( nCount );


	int i;
	for( i = 0 ; i != nCount ; ++ i )   
	{   
		TCHAR szBuffer[1024];
		DWORD cchBuf(1024);
		LVITEM lvi_2;
		lvi_2.iItem = i;
		lvi_2.iSubItem = 2;
		lvi_2.mask = LVIF_TEXT;
		lvi_2.pszText = szBuffer;
		lvi_2.cchTextMax = cchBuf;
		m_wndList.GetItem(&lvi_2);

		String src_2( lvi_2.pszText );
		pResult->push_back( src_2 );

		LVITEM lvi_1;
		lvi_1.iItem = i;
		lvi_1.iSubItem = 1;
		lvi_1.mask = LVIF_TEXT;
		lvi_1.pszText = szBuffer;
		lvi_1.cchTextMax = cchBuf;
		m_wndList.GetItem(&lvi_1);

		SingleFrame sframe;
		String src_1(lvi_1.pszText);
		memset(sframe.filename, 0, DTX_FILENAME_LENGTH);
		strcpy(sframe.filename, src_1.c_str());
		sframe.frameId = i;
		sframe.timelength = m_timelength;

		pframes->push_back(sframe);

	} 

	String aim_path( m_AimFilePath.GetBuffer(0) );

	FileWriterDtx vgDTXwriter;

	vgDTXwriter.registerProcessObs( (this) );

	bool writeok = vgDTXwriter.writeToDtxFile(
		pResult, pframes, aim_path, m_ratio );
	
	if ( writeok == false )
	{
		MessageBox("出错, 请检查DDS文件.");
	}
	//else
	//{
	//	MessageBox("制作成功!");
	//}


	this->OnOK();

	return;

}


void CSaveVgimgDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	

}

void CSaveVgimgDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
}

String CSaveVgimgDlg::getBasenameFromFilepath( const String& filepath )
{
	String basename , path ;
	vgKernel::StringUtility::splitFilename( filepath , basename , path );
	return basename;
}

void CSaveVgimgDlg::onStart( const String& text , const int& range_lower , const int& range_upper )
{
	_processBar.SetRange32( range_lower , range_upper );
}

void CSaveVgimgDlg::onNotify( const String& msg , const int& process_pos )
{
	_processBar.SetPos( process_pos );
}

void CSaveVgimgDlg::onFinish( const String& msg )
{
	int lower = 0;
	int upper = 0;
	_processBar.GetRange( lower , upper );
	_processBar.SetPos( upper );
}
void CSaveVgimgDlg::OnBnClickedMoveTop()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_wndList.GetSelectedCount()!=1)
		return;
	CString S[4];
	UINT i=m_wndList.GetSelectionMark();
	if(i==0)
		return;
	S[0]=m_wndList.GetItemText(0,1);
	S[1]=m_wndList.GetItemText(0,2);
	S[2]=m_wndList.GetItemText(i,1);
	S[3]=m_wndList.GetItemText(i,2);
	m_wndList.SetItemText(0,1,S[2]);
	m_wndList.SetItemText(0,2,S[3]);
	m_wndList.SetItemState(0,LVIS_SELECTED,LVIS_SELECTED);
	m_wndList.SetItemText(i,1,S[0]);
	m_wndList.SetItemText(i,2,S[1]);
	m_wndList.SetItemState(i,0,LVIS_SELECTED);

	m_wndList.SetSelectionMark(0);
}

void CSaveVgimgDlg::OnBnClickedMoveBottom()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_wndList.GetSelectedCount()!=1)
		return;
	CString S[4];
	UINT i=m_wndList.GetSelectionMark();
	if(i==(m_wndList.GetItemCount()-1))
		return;
	S[0]=m_wndList.GetItemText(m_wndList.GetItemCount()-1,1);
	S[1]=m_wndList.GetItemText(m_wndList.GetItemCount()-1,2);
	S[2]=m_wndList.GetItemText(i,1);
	S[3]=m_wndList.GetItemText(i,2);
	m_wndList.SetItemText(m_wndList.GetItemCount()-1,1,S[2]);
	m_wndList.SetItemText(m_wndList.GetItemCount()-1,2,S[3]);
	m_wndList.SetItemState(m_wndList.GetItemCount()-1,LVIS_SELECTED,LVIS_SELECTED);
	m_wndList.SetItemText(i,1,S[0]);
	m_wndList.SetItemText(i,2,S[1]);
	m_wndList.SetItemState(i,0,LVIS_SELECTED);

	m_wndList.SetSelectionMark(m_wndList.GetItemCount()-1);

}

void CSaveVgimgDlg::OnBnClickedMoveUp()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_wndList.GetSelectedCount()!=1)
		return;
	CString S[4];
	UINT i=m_wndList.GetSelectionMark();
	if(i==0)
		return;
	S[0]=m_wndList.GetItemText(i-1,1);
	S[1]=m_wndList.GetItemText(i-1,2);
	S[2]=m_wndList.GetItemText(i,1);
	S[3]=m_wndList.GetItemText(i,2);
	m_wndList.SetItemText(i-1,1,S[2]);
	m_wndList.SetItemText(i-1,2,S[3]);
	m_wndList.SetItemState(i-1,LVIS_SELECTED,LVIS_SELECTED);
	m_wndList.SetItemText(i,1,S[0]);
	m_wndList.SetItemText(i,2,S[1]);
	m_wndList.SetItemState(i,0,LVIS_SELECTED);

	m_wndList.SetSelectionMark(i-1);
}

void CSaveVgimgDlg::OnBnClickedMoveDown()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_wndList.GetSelectedCount()!=1)
		return;
	CString S[4];
	UINT i=m_wndList.GetSelectionMark();
	if(i==(m_wndList.GetItemCount()-1))
		return;
	S[0]=m_wndList.GetItemText(i+1,1);
	S[1]=m_wndList.GetItemText(i+1,2);
	S[2]=m_wndList.GetItemText(i,1);
	S[3]=m_wndList.GetItemText(i,2);
	m_wndList.SetItemText(i+1,1,S[2]);
	m_wndList.SetItemText(i+1,2,S[3]);
	m_wndList.SetItemState(i+1,LVIS_SELECTED,LVIS_SELECTED);
	m_wndList.SetItemText(i,1,S[0]);
	m_wndList.SetItemText(i,2,S[1]);
	m_wndList.SetItemState(i,0,LVIS_SELECTED);

	m_wndList.SetSelectionMark(i+1);

}
