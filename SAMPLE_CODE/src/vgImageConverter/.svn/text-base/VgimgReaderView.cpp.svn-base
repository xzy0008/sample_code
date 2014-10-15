// VgimgReaderView.cpp : CVgimgReaderView 类的实现
//

#include <vgStableHeaders.h>
#include "VgimgReader.h"

#include "VgimgReaderDoc.h"
#include "VgimgReaderView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVgimgReaderView

IMPLEMENT_DYNCREATE(CVgimgReaderView, CListView)

BEGIN_MESSAGE_MAP(CVgimgReaderView, CListView)
	ON_WM_STYLECHANGED()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_COMMAND(ID_RIGHTVIEW_REFRESH, &CVgimgReaderView::OnLeftviewRefresh)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CVgimgReaderView::OnNMRclick)
	ON_COMMAND(ID_VIEW_LARGEICON, &CVgimgReaderView::OnViewLargeicon)
	ON_COMMAND(ID_VIEW_SMALLICON, &CVgimgReaderView::OnViewSmallicon)
	ON_COMMAND(ID_VIEW_LIST, &CVgimgReaderView::OnViewList)
	ON_COMMAND(ID_VIEW_DETAILS, &CVgimgReaderView::OnViewDetails)
END_MESSAGE_MAP()

// CVgimgReaderView 构造/析构

#define NUM_COLUMNS 6
//#define NUM_ITEMS   7

static _TCHAR *_gszColumnLabel[NUM_COLUMNS] =
{
	_T("basename"), _T("path"), _T("filename"), _T("compressedSize"),
	_T("uncompressedSize"), _T("Type")
};

static int _gnColumnFmt[NUM_COLUMNS] =
{
	LVCFMT_LEFT, LVCFMT_LEFT, LVCFMT_LEFT, LVCFMT_LEFT,
	LVCFMT_LEFT,  LVCFMT_CENTER
};

static int _gnColumnWidth[NUM_COLUMNS] =
{
	150, 150, 150, 150, 100, 150
};

//static _TCHAR *_gszItem[NUM_ITEMS][NUM_COLUMNS] =
//{
//	_T("Yellow"),  _T("255"), _T("255"), _T("0"),   _T("40"),  _T("240"), _T("120"), _T("Neutral"),
//	_T("Red"),     _T("255"), _T("0"),   _T("0"),   _T("0"),   _T("240"), _T("120"), _T("Warm"),
//	_T("Green"),   _T("0"),   _T("255"), _T("0"),   _T("80"),  _T("240"), _T("120"), _T("Cool"),
//	_T("Magenta"), _T("255"), _T("0"),   _T("255"), _T("200"), _T("240"), _T("120"), _T("Warm"),
//	_T("Cyan"),    _T("0"),   _T("255"), _T("255"), _T("120"), _T("240"), _T("120"), _T("Cool"),
//	_T("Blue"),    _T("0"),   _T("0"),   _T("255"), _T("160"), _T("240"), _T("120"), _T("Cool"),
//	_T("Gray"),    _T("192"), _T("192"), _T("192"), _T("160"), _T("0"),   _T("181"), _T("Neutral")
//};


CVgimgReaderView::CVgimgReaderView()
{
	// TODO: 在此处添加构造代码

	//m_CurrentArchiveFile = "G:\\win_zip4.zip";

}

CVgimgReaderView::~CVgimgReaderView()
{
}

BOOL CVgimgReaderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CListView::PreCreateWindow(cs);
}

void CVgimgReaderView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
	// TODO: 调用 GetListCtrl() 直接访问 ListView 的列表控件，
	//  从而可以用项填充 ListView。

	CListCtrl& ListCtrl = GetListCtrl();


	this->updateAll();

	//pView->m_bRunning=false;
	//pView->m_bTerminate=false;

	//_endthreadex( 0 );



	// set image lists

	//m_LargeImageList.Create(IDB_LARGEICONS, 32, 1, RGB(255, 255, 255));
	//m_SmallImageList.Create(IDB_SMALLICONS, 16, 1, RGB(255, 255, 255));
	//m_StateImageList.Create(IDB_STATEICONS, 16, 1, RGB(255, 0, 0));

	//m_LargeImageList.SetOverlayImage(100, 1);
	//m_SmallImageList.SetOverlayImage(100, 1);

	//ListCtrl.SetImageList(&m_LargeImageList, LVSIL_NORMAL);
	//ListCtrl.SetImageList(&m_SmallImageList, LVSIL_SMALL);
	//ListCtrl.SetImageList(&m_StateImageList, LVSIL_STATE);




	/*

	try
	{
		// insert items

		LV_ITEM lvi;

		for ( size_t i = 0 ; i < pfileinfolist->size() ; ++ i )
		{
			lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
			lvi.iItem = i;
			lvi.iSubItem = 0;
			lvi.pszText = (char *)fileinfoVec[i].filename.c_str();
			lvi.iImage = 0;
			lvi.stateMask = LVIS_STATEIMAGEMASK;
			lvi.state = INDEXTOSTATEIMAGEMASK(1);

			ListCtrl.InsertItem(&lvi);
		}

		// set item text for additional columns

		for( size_t i = 0 ; i < pfileinfolist->size() ; ++ i )
		{
			//for( int j = 1; j<NUM_COLUMNS; ++j )
			//{
				//ListCtrl.SetItemText(i,j,_gszItem[i][j]);
			//}


			ListCtrl.SetItemText( i , 1 , (char *)fileinfoVec[i].path.c_str() );
			ListCtrl.SetItemText( i , 2 , (char *)fileinfoVec[i].basename.c_str() );

			String compress_size =
				vgtest::ConvertUtil::textCast<size_t>( 
				fileinfoVec[i].compressedSize );
			ListCtrl.SetItemText( i , 3 , (char *)compress_size.c_str() );

			String uncompress_size =
				vgtest::ConvertUtil::textCast<size_t>( 
				fileinfoVec[i].uncompressedSize );
			ListCtrl.SetItemText( i , 4 , (char *)uncompress_size.c_str() );


		}

		//for(i = 0; i < NUM_ITEMS; i++)
		//{
		//	lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
		//	lvi.iItem = i;
		//	lvi.iSubItem = 0;
		//	lvi.pszText = _gszItem[i][0];
		//	lvi.iImage = i;
		//	lvi.stateMask = LVIS_STATEIMAGEMASK;
		//	lvi.state = INDEXTOSTATEIMAGEMASK(1);

		//	ListCtrl.InsertItem(&lvi);
		//}

	}
	catch (vgTestSystem::Exception &e)
	{
		::MessageBox( NULL , e.getFullDescription().c_str() , "ERROR" , MB_OK );
	}




	VG_TRACE( m_ImageListThumb.GetImageCount() );


	// set item text for additional columns

	//for(i = 0; i<NUM_ITEMS; i++)
	//{
	//	for(j = 1; j<NUM_COLUMNS; j++)
	//	{
	//		ListCtrl.SetItemText(i,j,_gszItem[i][j]);
	//	}
	//}

	*/
}


// CVgimgReaderView 诊断

#ifdef _DEBUG
void CVgimgReaderView::AssertValid() const
{
	CListView::AssertValid();
}

void CVgimgReaderView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CVgimgReaderDoc* CVgimgReaderView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVgimgReaderDoc)));
	return (CVgimgReaderDoc*)m_pDocument;
}
#endif //_DEBUG


// CVgimgReaderView 消息处理程序
void CVgimgReaderView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: 添加代码以响应用户对窗口视图样式的更改	
	CListView::OnStyleChanged(nStyleType,lpStyleStruct);	

}

void CVgimgReaderView::OnSize(UINT nType, int cx, int cy)
{
	CListView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	GetListCtrl().Arrange(LVA_ALIGNTOP);
}

bool CVgimgReaderView::updateAll(void)
{

	assert(0);
#if 0
	// insert columns
	CListCtrl& ListCtrl = GetListCtrl();
	ListCtrl.DeleteAllItems();


	CImageList* pImgList=&m_ImageListThumb;

	// reset our image list
	for(int i=0; i<pImgList->GetImageCount(); i++)
	{
		pImgList->Remove(i);	
	}



	//vgTestSystem::ZipArchive ziparch( m_CurrentArchiveFile , "zip");

	vgtest::ArchivePtr parch =
		vgtest::ArchiveFactory::createFromName( m_CurrentArchiveFile );

	if ( parch.isNull() )
	{
		return false;
	}
	

	parch->load();

	vgtest::FileInfoListPtr pfileinfolist = parch->listFileInfo();
	assert( !pfileinfolist.isNull() );

	std::vector<vgTestSystem::FileInfo>& fileinfoVec = *pfileinfolist;


	pImgList->SetImageCount( fileinfoVec.size() );

#define MAX_PATH          260


	TCHAR path[MAX_PATH];
	vgtest::FileInfoList::iterator iter;

	// Set redraw to FALSE to avoid flickering during adding new items
	ListCtrl.SetRedraw(FALSE);
	int nIndex=0;

	for(iter= fileinfoVec.begin(); 
		iter!= fileinfoVec.end() /*&& pView->m_bTerminate!=true*/; 
		iter++, nIndex++)
	{
		ListCtrl.InsertItem(nIndex, (char*)iter->basename.c_str(), nIndex);
	}

	ListCtrl.SetRedraw(TRUE);
	ListCtrl.Invalidate();

	// Create Brushes for Border and BackGround
	HBRUSH hBrushBorder=::CreateSolidBrush(RGB(192, 192, 192));
	HBRUSH hBrushBk=::CreateSolidBrush(RGB(255, 255, 255));

	// Border Size
	RECT rcBorder;
	rcBorder.left=rcBorder.top=0;
	rcBorder.right=THUMBNAIL_WIDTH;
	rcBorder.bottom=THUMBNAIL_HEIGHT;

	const float fRatio=(float)THUMBNAIL_HEIGHT/THUMBNAIL_WIDTH;

	int XDest, YDest, nDestWidth, nDestHeight;
	nIndex=0;
	for(iter= fileinfoVec.begin(); 
		iter!= fileinfoVec.end(); 
		iter++, nIndex++)
	{
		// 查看扩展名。若为非图像文件格式，则跳过。
		String basename = iter->basename;

		vgtest::ImageFormat format = vgtest::ImageUtility::findImageFormat( basename );

		if ( format == vgtest::IMAGE_FORMAT_UNKNOWN )
		{
			continue;
		}

		vgtest::NormalImagePtr pimg = 
			vgtest::ImageFactory::createNormalImagePtr();

		assert( !pimg.isNull() );

		bool load_result = pimg->loadFromFileInfo( 
			parch->getFileInfo( iter->basename ) );

		assert( !pimg.isNull() );

		if( load_result == false)
		{
			CBitmap bitmap;
			bitmap.CreateBitmap( THUMBNAIL_WIDTH , THUMBNAIL_HEIGHT ,
				3 , 32 , NULL );
			bool res = bitmap.LoadBitmap( IDB_BITMAP1 );
			
			assert( res == true );


			//bitmap.Attach(bm);
			pImgList->Replace(nIndex, &bitmap, NULL);

			ListCtrl.RedrawItems(nIndex, nIndex);

			ListCtrl.SetRedraw(TRUE);
			ListCtrl.Invalidate();

			continue;
		}

		// Calculate Rect to fit to canvas
		const float fImgRatio=(float)pimg->getHeight()/pimg->getWidth();
		if(fImgRatio > fRatio)
		{
			nDestWidth=THUMBNAIL_HEIGHT/fImgRatio;
			XDest=(THUMBNAIL_WIDTH-nDestWidth)/2;
			YDest=0;
			nDestHeight=THUMBNAIL_HEIGHT;
		}
		else
		{
			XDest=0;
			nDestWidth=THUMBNAIL_WIDTH;
			nDestHeight=THUMBNAIL_WIDTH*fImgRatio;
			YDest=(THUMBNAIL_HEIGHT-nDestHeight)/2;
		}

		CClientDC cdc( this );
		HDC hDC=::CreateCompatibleDC(cdc.m_hDC);
		HBITMAP bm = CreateCompatibleBitmap(cdc.m_hDC, THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT);
		HBITMAP pOldBitmapImage = (HBITMAP)SelectObject(hDC,bm);
		// Draw Background
		::FillRect(hDC, &rcBorder, hBrushBk);

		vgtest::CximagePtr pcximg = pimg->getCximagePtr();
		assert( !pcximg.isNull() );

		// Draw Image
		pcximg->Stretch(hDC, XDest, YDest, nDestWidth, nDestHeight);

		// Draw Border
		::FrameRect(hDC, &rcBorder, hBrushBorder);

		SelectObject(hDC, pOldBitmapImage);

		// Attach to Bitmap and Replace image in CImageList
		CBitmap bitmap;
		bitmap.Attach(bm);
		pImgList->Replace(nIndex, &bitmap, NULL);

		// Redraw only a current item for removing flickering and fast speed.
		ListCtrl.RedrawItems(nIndex, nIndex);

		// Release used DC and Object
		DeleteDC(hDC);
		DeleteObject(bm);
	}
	DeleteObject(hBrushBorder);
	DeleteObject(hBrushBk);


	try
	{
		//// insert items

		//LV_ITEM lvi;

		//for ( size_t i = 0 ; i < pfileinfolist->size() ; ++ i )
		//{
		//	lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
		//	lvi.iItem = i;
		//	lvi.iSubItem = 0;
		//	lvi.pszText = (char *)fileinfoVec[i].filename.c_str();
		//	lvi.iImage = 0;
		//	lvi.stateMask = LVIS_STATEIMAGEMASK;
		//	lvi.state = INDEXTOSTATEIMAGEMASK(1);

		//	ListCtrl.InsertItem(&lvi);
		//}

		// set item text for additional columns

		for( size_t i = 0 ; i < pfileinfolist->size() ; ++ i )
		{
			ListCtrl.SetItemText( i , 1 , (char *)fileinfoVec[i].path.c_str() );
			ListCtrl.SetItemText( i , 2 , (char *)fileinfoVec[i].filename.c_str() );

			String compress_size =
				vgtest::ConvertUtil::textCast<size_t>( 
				fileinfoVec[i].compressedSize );
			ListCtrl.SetItemText( i , 3 , (char *)compress_size.c_str() );

			String uncompress_size =
				vgtest::ConvertUtil::textCast<size_t>( 
				fileinfoVec[i].uncompressedSize );
			ListCtrl.SetItemText( i , 4 , (char *)uncompress_size.c_str() );

			ListCtrl.SetItemText( i , 5 , (char*)parch->getType().c_str() );
		}
	}
	catch (vgTestSystem::Exception &e)
	{
		::MessageBox( NULL , e.getFullDescription().c_str() , "ERROR" , MB_OK );
	}

	ListCtrl.Invalidate();

	parch->unload();


#endif

	return true;
}

int CVgimgReaderView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here


	// Initialize Imaget List and Attach it to ListCtrl
	m_ImageListThumb.Create(THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT, ILC_COLOR32, 0, 1);
	GetListCtrl().SetImageList(&m_ImageListThumb, LVSIL_NORMAL);

	// Set the background color to white.
	m_ImageListThumb.SetBkColor(RGB(255, 255, 255));
	ASSERT(m_ImageListThumb.GetBkColor() == RGB(255, 255, 255));

	// set image lists

	m_LargeImageList.Create(IDB_LARGEICONS, 32, 1, RGB(255, 255, 255));
	m_SmallImageList.Create(IDB_SMALLICONS, 16, 1, RGB(255, 255, 255));
	m_StateImageList.Create(IDB_STATEICONS, 16, 1, RGB(255, 0, 0));

	m_LargeImageList.SetOverlayImage(100, 1);
	m_SmallImageList.SetOverlayImage(100, 1);

	//GetListCtrl().SetImageList(&m_LargeImageList, LVSIL_NORMAL);
	GetListCtrl().SetImageList(&m_SmallImageList, LVSIL_SMALL);
	GetListCtrl().SetImageList(&m_StateImageList, LVSIL_STATE);


	m_BackgroundMenu.LoadMenu(IDR_RIGHTVIEW_BACK_MENU);   

	int i, j;
	LV_COLUMN lvc;

	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	for(i = 0; i<NUM_COLUMNS; i++)
	{
		lvc.iSubItem = i;
		lvc.pszText = _gszColumnLabel[i];
		lvc.cx = _gnColumnWidth[i];
		lvc.fmt = _gnColumnFmt[i];
		GetListCtrl().InsertColumn(i,&lvc);
	}



	return 0;
}

void CVgimgReaderView::OnLeftviewRefresh()
{
	// TODO: Add your command handler code here
	//MessageBox("fff");
	this->updateAll();
}

void CVgimgReaderView::OnNMRclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	CMenu*   pMenu = m_BackgroundMenu.GetSubMenu(0);
	CPoint   pos;   
	GetCursorPos(&pos);//   获取鼠标位置   
	SetForegroundWindow(); 
	pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,  
		pos.x,   pos.y,   this,   NULL);   

}

void CVgimgReaderView::OnViewLargeicon()
{
	// TODO: Add your command handler code here
	( (CMainFrame*)AfxGetMainWnd() )->OnViewStyle( ID_VIEW_LARGEICON );
}

void CVgimgReaderView::OnViewSmallicon()
{
	// TODO: Add your command handler code here
	( (CMainFrame*)AfxGetMainWnd() )->OnViewStyle( ID_VIEW_SMALLICON );
}

void CVgimgReaderView::OnViewList()
{
	// TODO: Add your command handler code here
	( (CMainFrame*)AfxGetMainWnd() )->OnViewStyle( ID_VIEW_LIST );
}

void CVgimgReaderView::OnViewDetails()
{
	// TODO: Add your command handler code here
	( (CMainFrame*)AfxGetMainWnd() )->OnViewStyle( ID_VIEW_DETAILS );
}
