//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2008 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// MMStyleExampleView.cpp : implementation of the CMMStyleExampleView class
//

#include <vgStableHeaders.h>
#include "MMStyleExample.h"

#include "MMStyleExampleDoc.h"
#include "MMStyleExampleView.h"

#include <vgImage/vgiFileReaderVgi.h>

#include <vgKernel/vgkSystemUtility.h>
#include <vgTerritory/vgtFileReaderVtr.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const UINT idPlay = 1;

/////////////////////////////////////////////////////////////////////////////
// CMMStyleExampleView

IMPLEMENT_DYNCREATE(CMMStyleExampleView, CListView)

BEGIN_MESSAGE_MAP(CMMStyleExampleView, CListView)
	//{{AFX_MSG_MAP(CMMStyleExampleView)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_NOTIFY_REFLECT(LVN_BEGINDRAG, OnBegindrag)
	ON_COMMAND(IDC_SELECT_ALL__, OnSelectAll)
	ON_COMMAND(IDC_INVERT_SELECTION__, OnInvertSelection)
	ON_COMMAND(IDC_REMOVE_FROM_LIST__, OnRemoveFromList)
	ON_COMMAND(IDC_CLEAR_LIST__, OnClearList)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_OPEN, &CMMStyleExampleView::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMStyleExampleView construction/destruction

CMMStyleExampleView::CMMStyleExampleView() : m_bUseDnDHelper(false),
m_piDropHelper(NULL)
{
	// Create an instance of the shell DnD helper object.

	if ( SUCCEEDED( CoCreateInstance ( CLSID_DragDropHelper, NULL, 
		CLSCTX_INPROC_SERVER,
		IID_IDropTargetHelper, 
		(void**) &m_piDropHelper ) ))
	{
		m_bUseDnDHelper = true;
	}

	vgiBriefs = NULL;

	vtrBriefs = NULL;
}

CMMStyleExampleView::~CMMStyleExampleView()
{
	if ( NULL != m_piDropHelper )
		m_piDropHelper->Release();
}

BOOL CMMStyleExampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMMStyleExampleView drawing

void CMMStyleExampleView::OnDraw(CDC* pDC)
{
	CMMStyleExampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CMMStyleExampleView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	CListCtrl& list = GetListCtrl();

	// Register our view as a drop target.

	m_droptarget.Register ( this );

	// Get a handle to the system small icon image list, and set that as the
	// image list for our list control

	SHFILEINFO rInfo;
	HIMAGELIST hImglist;

	hImglist = (HIMAGELIST) SHGetFileInfo ( _T(""), 0, &rInfo, sizeof(SHFILEINFO), 
		SHGFI_ICON | SHGFI_SMALLICON | 
		SHGFI_SYSICONINDEX );

	m_imglist.Attach ( hImglist );

	// Make sure the list control has the share image list style, so it won't
	// destroy the system image list when the dialog closes.

	list.ModifyStyle ( LVS_TYPEMASK, 
		LVS_REPORT | LVS_NOSORTHEADER | LVS_SHAREIMAGELISTS );

	list.SetImageList ( &m_imglist, LVSIL_SMALL );

	// Enable tooltips for items that aren't completely visible.

	list.SetExtendedStyle ( LVS_EX_INFOTIP );

	// Set up the list control columns.

	list.InsertColumn ( 0, _T("Filename"), LVCFMT_LEFT, 0, 0 );
	list.InsertColumn ( 1, _T("Type"), LVCFMT_LEFT, 0, 1 );
	list.InsertColumn ( 2, _T("Size"), LVCFMT_LEFT, 0, 2 );

	list.SetColumnWidth ( 0, LVSCW_AUTOSIZE_USEHEADER );
	list.SetColumnWidth ( 1, LVSCW_AUTOSIZE_USEHEADER );
	list.SetColumnWidth ( 2, LVSCW_AUTOSIZE_USEHEADER );
}

/////////////////////////////////////////////////////////////////////////////
// CMMStyleExampleView diagnostics

#ifdef _DEBUG
void CMMStyleExampleView::AssertValid() const
{
	CListView::AssertValid();
}

void CMMStyleExampleView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CMMStyleExampleDoc* CMMStyleExampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMMStyleExampleDoc)));
	return (CMMStyleExampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMMStyleExampleView message handlers

void CMMStyleExampleView::OnDestroy() 
{
	// Detach our CImageList from the system image list.

	if ( NULL != m_imglist.GetSafeHandle() )
		m_imglist.Detach();

	CListView::OnDestroy();
}

void CMMStyleExampleView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CPoint ptCursorPos;
	CMenu  menu;

	// We'll show the menu at the current cursor position.

	GetCursorPos ( &ptCursorPos );

	VERIFY ( menu.LoadMenu ( IDR_LIST_CONTEXTMENU__ ));
	ASSERT ( NULL != menu.GetSubMenu(0) );  // check that there's a popup menu at index 0.

	// Show the menu!

	menu.GetSubMenu(0)->TrackPopupMenu ( TPM_RIGHTBUTTON, ptCursorPos.x,
		ptCursorPos.y, this );

	*pResult = 0;   // return value ignored
}

void CMMStyleExampleView::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMLISTVIEW*    pNMLV = (NMLISTVIEW*) pNMHDR;
	CListCtrl&     list = GetListCtrl();
	COleDataSource datasrc;
	HGLOBAL        hgDrop;
	DROPFILES*     pDrop;
	CStringList    lsDraggedFiles;
	POSITION       pos;
	int            nSelItem;
	CString        sFile;
	UINT           uBuffSize = 0;
	TCHAR*         pszBuff;
	FORMATETC      etc = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };

	*pResult = 0;   // return value ignored

	// For every selected item in the list, put the filename into lsDraggedFiles.

	vgKernel::StringVectorPtr draglist( new vgKernel::StringVector );


	pos = list.GetFirstSelectedItemPosition();

	while ( NULL != pos )
	{
		nSelItem = list.GetNextSelectedItem ( pos );
		sFile = list.GetItemText ( nSelItem, 0 );

		//lsDraggedFiles.AddTail ( sFile );

		draglist->push_back( sFile.GetBuffer(0) );

		// Calculate the # of chars required to hold this string.

		//uBuffSize += lstrlen ( sFile ) + 1;
	}


 

	String temppath = vgKernel::SystemUtility::getSystemTempPath();

	vgKernel::StringVector _tempFiles;

	assert( (vgiBriefs != NULL && vtrBriefs == NULL) ||
		(vgiBriefs == NULL && vtrBriefs != NULL) );

	if ( vgiBriefs != NULL )
	{
		//------------------------------------------
		// 然后开始拷贝到temppath
		//------------------------------------------
		vgKernel::StringVector::iterator iter  = draglist->begin();
		vgKernel::StringVector::iterator iter_end = draglist->end();

		for ( ; iter != iter_end ; ++ iter )
		{
			String curfile = *iter;

			vgImage::VgiBriefPtr brief;
			// 查找这个brief
			vgImage::VgiBriefPtrVec::iterator bi = vgiBriefs->begin();
			vgImage::VgiBriefPtrVec::iterator bi_end = vgiBriefs->end();

			for ( ; bi != bi_end ; ++ bi )
			{
				if ( String((*bi)->_fileName) == curfile )
				{
					brief = *bi;
					break;
				}
			}

			assert( brief.isNull() == false );

			assert( _vgiFilename.empty() == false );
			vgKernel::StreamReaderPtr pstream = 
				vgKernel::StreamReaderFactory::createFromFile( _vgiFilename );

			assert( pstream.isNull() == false );
			char* buf = new char[ brief->_metaFileSize ];

			pstream->seek( brief->_metaFileOffset );

			long readnum = pstream->read( buf , brief->_metaFileSize );
			assert( readnum == brief->_metaFileSize  );

			String dst = temppath + "\\" + brief->_fileName;

			vgKernel::StreamWriterPtr pwriter = 
				vgKernel::StreamWriterFactory::createFromFile( dst );

			assert( pwriter.isNull() == false );

			pwriter->write( buf  , brief->_metaFileSize );

			delete[] buf;

			_tempFiles.push_back( dst );
		}
	}
	else
	{
		//------------------------------------------
		// 这个时候是vtr的格式
		//------------------------------------------

		vgKernel::StringVector::iterator iter  = draglist->begin();
		vgKernel::StringVector::iterator iter_end = draglist->end();

		for ( ; iter != iter_end ; ++ iter )
		{
			String curfile = *iter;

			vgTerritory::VtrBriefPtr brief;
			// 查找这个brief
			vgTerritory::VtrBriefPtrVec::iterator bi = vtrBriefs->begin();
			vgTerritory::VtrBriefPtrVec::iterator bi_end = vtrBriefs->end();

			for ( ; bi != bi_end ; ++ bi )
			{
				if ( String((*bi)->_fileName) == curfile )
				{
					brief = *bi;
					break;
				}
			}

			assert( brief.isNull() == false );

			assert( _vtrFilename.empty() == false );
			vgKernel::StreamReaderPtr pstream = 
				vgKernel::StreamReaderFactory::createFromFile( _vtrFilename );

			assert( pstream.isNull() == false );
			char* buf = new char[ brief->_metaFileSize ];

			pstream->seek( brief->_metaFileOffset );

			long readnum = pstream->read( buf , brief->_metaFileSize );
			assert( readnum == brief->_metaFileSize  );

			String dst = temppath + "\\" + brief->_fileName;

			vgKernel::StreamWriterPtr pwriter = 
				vgKernel::StreamWriterFactory::createFromFile( dst );

			assert( pwriter.isNull() == false );

			pwriter->write( buf  , brief->_metaFileSize );

			delete[] buf;

			_tempFiles.push_back( dst );

		}
	}



	//------------------------------------------
	// 添加到drag buffer
	//------------------------------------------

	{
		vgKernel::StringVector::iterator iter  = _tempFiles.begin();
		vgKernel::StringVector::iterator iter_end = _tempFiles.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			sFile = iter->c_str();

			lsDraggedFiles.AddTail ( sFile );


			// Calculate the # of chars required to hold this string.

			uBuffSize += lstrlen ( sFile ) + 1;
		}
	}



	// Add 1 extra for the final null char, and the size of the DROPFILES struct.

	uBuffSize = sizeof(DROPFILES) + sizeof(TCHAR) * (uBuffSize + 1);

	// Allocate memory from the heap for the DROPFILES struct.

	hgDrop = GlobalAlloc ( GHND | GMEM_SHARE, uBuffSize );

	if ( NULL == hgDrop )
		return;

	pDrop = (DROPFILES*) GlobalLock ( hgDrop );

	if ( NULL == pDrop )
	{
		GlobalFree ( hgDrop );
		return;
	}

	// Fill in the DROPFILES struct.

	pDrop->pFiles = sizeof(DROPFILES);

#ifdef _UNICODE
	// If we're compiling for Unicode, set the Unicode flag in the struct to
	// indicate it contains Unicode strings.

	pDrop->fWide = TRUE;
#endif

	// Copy all the filenames into memory after the end of the DROPFILES struct.

	pos = lsDraggedFiles.GetHeadPosition();
	pszBuff = (TCHAR*) (LPBYTE(pDrop) + sizeof(DROPFILES));

	while ( NULL != pos )
	{
		lstrcpy ( pszBuff, (LPCTSTR) lsDraggedFiles.GetNext ( pos ) );
		pszBuff = 1 + _tcschr ( pszBuff, '\0' );
	}

	GlobalUnlock ( hgDrop );

	// Put the data in the data source.

	datasrc.CacheGlobalData ( CF_HDROP, hgDrop, &etc );

	// Add in our own custom data, so we know that the drag originated from our 
	// window.  OnDragEnter() checks for this custom format, and
	// doesn't allow the drop if it's present.  This is how we prevent the user
	// from dragging and then dropping in our own window.
	// The data will just be a dummy bool.
	HGLOBAL hgBool;

	hgBool = GlobalAlloc ( GHND | GMEM_SHARE, sizeof(bool) );

	if ( NULL == hgBool )
	{
		GlobalFree ( hgDrop );
		return;
	}

	// Put the data in the data source.

	etc.cfFormat = g_uCustomClipbrdFormat;

	datasrc.CacheGlobalData ( g_uCustomClipbrdFormat, hgBool, &etc );


	// Start the drag 'n' drop!

	DROPEFFECT dwEffect = datasrc.DoDragDrop ( DROPEFFECT_COPY | DROPEFFECT_MOVE );

	// If the DnD completed OK, we remove all of the dragged items from our
	// list.

	switch ( dwEffect )
	{
	case DROPEFFECT_COPY:
	case DROPEFFECT_MOVE:
		{
			// The files were copied or moved.
			// Note: Don't call GlobalFree() because the data will be freed by the drop target.

			//for ( nSelItem = list.GetNextItem ( -1, LVNI_SELECTED );
			//	nSelItem != -1;
			//	nSelItem = list.GetNextItem ( nSelItem, LVNI_SELECTED ) )
			//{
			//	list.DeleteItem ( nSelItem );
			//	nSelItem--;
			//}

			//// Resize the list columns.

			//list.SetColumnWidth ( 0, LVSCW_AUTOSIZE_USEHEADER );
			//list.SetColumnWidth ( 1, LVSCW_AUTOSIZE_USEHEADER );
			//list.SetColumnWidth ( 2, LVSCW_AUTOSIZE_USEHEADER );
		}
		break;

	case DROPEFFECT_NONE:
		{
			// This needs special handling, because on NT, DROPEFFECT_NONE
			// is returned for move operations, instead of DROPEFFECT_MOVE.
			// See Q182219 for the details.
			// So if we're on NT, we check each selected item, and if the
			// file no longer exists, it was moved successfully and we can
			// remove it from the list.

			if ( g_bNT )
			{
				bool bDeletedAnything = false;

				//for ( nSelItem = list.GetNextItem ( -1, LVNI_SELECTED );
				//	nSelItem != -1;
				//	nSelItem = list.GetNextItem ( nSelItem, LVNI_SELECTED ) )
				//{
				//	CString sFilename = list.GetItemText ( nSelItem, 0 );

				//	if ( 0xFFFFFFFF == GetFileAttributes ( sFile ) &&
				//		GetLastError() == ERROR_FILE_NOT_FOUND )
				//	{
				//		// We couldn't read the file's attributes, and GetLastError()
				//		// says the file doesn't exist, so remove the corresponding 
				//		// item from the list.

				//		list.DeleteItem ( nSelItem );

				//		nSelItem--;
				//		bDeletedAnything = true;
				//	}
				//}

				// Resize the list columns if we deleted any items.

				if ( bDeletedAnything )
				{
					list.SetColumnWidth ( 0, LVSCW_AUTOSIZE_USEHEADER );
					list.SetColumnWidth ( 1, LVSCW_AUTOSIZE_USEHEADER );
					list.SetColumnWidth ( 2, LVSCW_AUTOSIZE_USEHEADER );

					// Note: Don't call GlobalFree() because the data belongs to 
					// the caller.
				}
				else
				{
					// The DnD operation wasn't accepted, or was canceled, so we 
					// should call GlobalFree() to clean up.

					GlobalFree ( hgDrop );
					GlobalFree ( hgBool );
				}
			}   // end if (NT)
			else
			{
				// We're on 9x, and a return of DROPEFFECT_NONE always means
				// that the DnD operation was aborted.  We need to free the
				// allocated memory.

				GlobalFree ( hgDrop );
				GlobalFree ( hgBool );
			}
		}
		break;  // end case DROPEFFECT_NONE
	}   // end switch



}


/////////////////////////////////////////////////////////////////////////////
// CMMStyleExampleView drag 'n' drop handlers

DROPEFFECT CMMStyleExampleView::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	DROPEFFECT dwEffect = DROPEFFECT_NONE;

	// Check for our own custom clipboard format in the data object.  If it's
	// present, then the DnD was initiated from our own window, and we won't
	// accept the drop.
	// If it's not present, then we check for CF_HDROP data in the data object.

	if ( NULL == pDataObject->GetGlobalData ( g_uCustomClipbrdFormat ))
	{
		// Look for CF_HDROP data in the data object, and accept the drop if
		// it's there.

		if ( NULL != pDataObject->GetGlobalData ( CF_HDROP ) )
			dwEffect = DROPEFFECT_COPY;
	}

	// Call the DnD helper.

	if ( m_bUseDnDHelper )
	{
		// The DnD helper needs an IDataObject interface, so get one from
		// the COleDataObject.  Note that the FALSE param means that
		// GetIDataObject will not AddRef() the returned interface, so 
		// we do not Release() it.

		IDataObject* piDataObj = pDataObject->GetIDataObject ( FALSE ); 

		m_piDropHelper->DragEnter ( GetSafeHwnd(), piDataObj, 
			&point, dwEffect );
	}

	return dwEffect;
}

DROPEFFECT CMMStyleExampleView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	DROPEFFECT dwEffect = DROPEFFECT_NONE;

	// Check for our own custom clipboard format in the data object.  If it's
	// present, then the DnD was initiated from our own window, and we won't
	// accept the drop.
	// If it's not present, then we check for CF_HDROP data in the data object.

	if ( NULL == pDataObject->GetGlobalData ( g_uCustomClipbrdFormat ))
	{
		// Look for CF_HDROP data in the data object, and accept the drop if
		// it's there.

		if ( NULL != pDataObject->GetGlobalData ( CF_HDROP ) )
			dwEffect = DROPEFFECT_COPY;
	}

	// Call the DnD helper.

	if ( m_bUseDnDHelper )
	{
		m_piDropHelper->DragOver ( &point, dwEffect );
	}

	return dwEffect;
}

BOOL CMMStyleExampleView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
{
	BOOL bRet;

	// Read the CF_HDROP data and put the files in the main window's list.

	bRet = ReadHdropData ( pDataObject );

	// Call the DnD helper.

	if ( m_bUseDnDHelper )
	{
		// The DnD helper needs an IDataObject interface, so get one from
		// the COleDataObject.  Note that the FALSE param means that
		// GetIDataObject will not AddRef() the returned interface, so 
		// we do not Release() it.

		IDataObject* piDataObj = pDataObject->GetIDataObject ( FALSE ); 

		m_piDropHelper->Drop ( piDataObj, &point, dropEffect );
	}

	return bRet;
}

void CMMStyleExampleView::OnDragLeave() 
{
	if ( m_bUseDnDHelper )
	{
		m_piDropHelper->DragLeave();
	}
}

// ReadHdropData() reads CF_HDROP data from the passed-in data object, and 
// puts all dropped files/folders into the main window's list control.
BOOL CMMStyleExampleView::ReadHdropData ( COleDataObject* pDataObject )
{
	HGLOBAL     hg;
	HDROP       hdrop;
	UINT        uNumFiles;
	TCHAR       szNextFile [MAX_PATH];
	SHFILEINFO  rFileInfo;
	LVFINDINFO  rlvFind = { LVFI_STRING, szNextFile };
	LVITEM      rItem;
	CListCtrl&  list = GetListCtrl();
	int         nIndex = list.GetItemCount();
	HANDLE      hFind;
	WIN32_FIND_DATA rFind;
	TCHAR       szFileLen [64];

	// Get the HDROP data from the data object.

	hg = pDataObject->GetGlobalData ( CF_HDROP );

	if ( NULL == hg )
	{
		return FALSE;
	}

	hdrop = (HDROP) GlobalLock ( hg );

	if ( NULL == hdrop )
	{
		GlobalUnlock ( hg );
		return FALSE;
	}

	// Get the # of files being dropped.

	uNumFiles = DragQueryFile ( hdrop, -1, NULL, 0 );


	if ( uNumFiles != 1 )
	{
		MessageBox("请拖拽一个vgi或者vtr文件" , "提示" );
		return FALSE;
	}

	String vgifile;

	for ( UINT uFile = 0; uFile < uNumFiles; uFile++ )
	{
		// Get the next filename from the HDROP info.

		if ( DragQueryFile ( hdrop, uFile, szNextFile, MAX_PATH ) > 0 )
		{
			// If the filename is already in the list, skip it.

			if ( -1 != list.FindItem ( &rlvFind, -1 ))
				continue;

			// Get the index of the file's icon in the system image list and
			// it's type description.

			SHGetFileInfo ( szNextFile, 0, &rFileInfo, sizeof(rFileInfo),
				SHGFI_SYSICONINDEX | SHGFI_ATTRIBUTES |
				SHGFI_TYPENAME );

			// Set up an LVITEM for the file we're about to insert.

			vgifile = szNextFile;

#if 0
			ZeroMemory ( &rItem, sizeof(LVITEM) );

			rItem.mask    = LVIF_IMAGE | LVIF_TEXT;
			rItem.iItem   = nIndex;
			rItem.pszText = szNextFile;
			rItem.iImage  = rFileInfo.iIcon;

			// If the file has the hidden attribute set, its attributes in
			// the SHFILEINFO struct will include SFGAO_GHOSTED.  We'll mark
			// the item as "cut" in our list to give it the same ghosted look.

			if ( rFileInfo.dwAttributes & SFGAO_GHOSTED )
			{
				rItem.mask |= LVIF_STATE;
				rItem.state = rItem.stateMask = LVIS_CUT;
			}

			// Insert it into the list!

			list.InsertItem ( &rItem );

			// Set column #1 to the file's type description.

			list.SetItemText ( nIndex, 1, rFileInfo.szTypeName );

			// Get the file size, and put that in column #2.

			hFind = FindFirstFile ( szNextFile, &rFind );

			if ( INVALID_HANDLE_VALUE != hFind )
			{
				StrFormatByteSize ( rFind.nFileSizeLow, szFileLen, 64 );
				FindClose ( hFind );
			}

			list.SetItemText ( nIndex, 2, szFileLen );

			nIndex++;

#endif
		}
	}

	if ( vgKernel::StringUtility::getFileExtension( vgifile ) == "vgi" )
	{
		openVgi(vgifile, list, nIndex);
	}
	else if ( vgKernel::StringUtility::getFileExtension( vgifile ) == "vtr"  )
	{
		opengVtr( vgifile , list, nIndex );
	}
	else
	{
		MessageBox("请拖拽一个vgi或者vtr文件",  "提示" );
		return FALSE;
	}


	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CMMStyleExampleView command handlers

void CMMStyleExampleView::OnSelectAll() 
{
	CListCtrl& list = GetListCtrl();
	int        nIndex, nMaxIndex = list.GetItemCount() - 1;

	for ( nIndex = 0; nIndex <= nMaxIndex; nIndex++ )
	{
		list.SetItemState ( nIndex, LVIS_SELECTED, LVIS_SELECTED );
	}
}

void CMMStyleExampleView::OnInvertSelection() 
{
	CListCtrl& list = GetListCtrl();
	int        nIndex;
	int        nMaxIndex = list.GetItemCount() - 1;
	UINT       uItemState;

	for ( nIndex = 0; nIndex <= nMaxIndex; nIndex++ )
	{
		uItemState = list.GetItemState ( nIndex, LVIS_SELECTED );

		list.SetItemState ( nIndex, uItemState ^ LVIS_SELECTED, 
			LVIS_SELECTED );
	}
}

void CMMStyleExampleView::OnRemoveFromList() 
{
	CListCtrl& list = GetListCtrl();
	int        nSelItem;

	for ( nSelItem = list.GetNextItem ( -1, LVNI_SELECTED );
		nSelItem != -1;
		nSelItem = list.GetNextItem ( nSelItem, LVNI_SELECTED ) )
	{
		list.DeleteItem ( nSelItem );
		nSelItem--;
	}
}

void CMMStyleExampleView::OnClearList() 
{
	GetListCtrl().DeleteAllItems();
}

void CMMStyleExampleView::openVgi( String vgifile, CListCtrl &list, int nIndex )
{
	//------------------------------------------
	// 开始插入文件
	//------------------------------------------

	assert( vgiBriefs == NULL );

	vgImage::VgiHeader header;

	vgiBriefs= vgImage::FileReaderVgi::readFromFile(
		vgifile , header );

	assert( vgiBriefs != NULL );

	list.DeleteAllItems();

	_vgiFilename = vgifile;

	vgImage::VgiBriefPtrVec::iterator iter  = vgiBriefs->begin();
	vgImage::VgiBriefPtrVec::iterator iter_end  = vgiBriefs->end();

	for ( ; iter != iter_end ; ++ iter )
	{
		vgImage::VgiBrief* curbrief = (*iter).getPointer();

		int _nIndex = list.GetItemCount();

		LVITEM      rItem;
		ZeroMemory ( &rItem, sizeof(LVITEM) );

		rItem.mask    = LVIF_TEXT;
		rItem.iItem   = _nIndex;
		rItem.pszText = curbrief->_fileName;


		// Insert it into the list!
		list.InsertItem ( &rItem );

		// Set column #1 to the file's type description.
		list.SetItemText ( _nIndex, 1, "dds" );

		std::ostringstream o;
		o << curbrief->_metaFileSize;


		list.SetItemText ( _nIndex, 2, o.str().c_str() );

	}


	// Resize columns so all text is visible.

	list.SetColumnWidth ( 0, LVSCW_AUTOSIZE_USEHEADER );
	list.SetColumnWidth ( 1, LVSCW_AUTOSIZE_USEHEADER );
	list.SetColumnWidth ( 2, LVSCW_AUTOSIZE_USEHEADER );

	list.EnsureVisible ( list.GetItemCount() - 1, FALSE );


}
void CMMStyleExampleView::OnFileOpen()
{
	char szFilters[]=
		"(*.vgi)|*.vgi|All Files (*.*)|*.*||";

	CFileDialog dlg (TRUE, "vgi", "*.vgi",
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);

	if( dlg.DoModal ()==IDOK )
	{
		String abspath = dlg.GetPathName();

		clearAllData();

		openVgi( abspath , GetListCtrl() , GetListCtrl().GetItemCount() );

	}
}

void CMMStyleExampleView::clearAllData()
{
	GetListCtrl().DeleteAllItems();

	if ( vgiBriefs != NULL )
	{
		delete vgiBriefs;
		vgiBriefs = NULL;
	}

	_vgiFilename = "";
}

void CMMStyleExampleView::opengVtr( String vtrfile, CListCtrl &list, int nIndex )
{
	//------------------------------------------
	// 开始插入文件
	//------------------------------------------

	assert( vtrBriefs == NULL );

	vtrBriefs= vgTerritory::FileReaderVtr::readFromFile(
		vtrfile );

	assert( vtrBriefs != NULL );


	_vtrFilename = vtrfile;

	vgTerritory::VtrBriefPtrVec::iterator iter  = vtrBriefs->begin();
	vgTerritory::VtrBriefPtrVec::iterator iter_end  = vtrBriefs->end();

	list.DeleteAllItems();

	for ( ; iter != iter_end ; ++ iter )
	{
		vgTerritory::VtrBrief* curbrief = (*iter).getPointer();

		int _nIndex = list.GetItemCount();

		LVITEM      rItem;
		ZeroMemory ( &rItem, sizeof(LVITEM) );

		rItem.mask    = LVIF_TEXT;
		rItem.iItem   = _nIndex;
		rItem.pszText = curbrief->_fileName;


		// Insert it into the list!
		list.InsertItem ( &rItem );

		// Set column #1 to the file's type description.
		list.SetItemText ( _nIndex, 1, "vgtr" );

		std::ostringstream o;
		o << curbrief->_metaFileSize;


		list.SetItemText ( _nIndex, 2, o.str().c_str() );

	}


	// Resize columns so all text is visible.

	list.SetColumnWidth ( 0, LVSCW_AUTOSIZE_USEHEADER );
	list.SetColumnWidth ( 1, LVSCW_AUTOSIZE_USEHEADER );
	list.SetColumnWidth ( 2, LVSCW_AUTOSIZE_USEHEADER );

	list.EnsureVisible ( list.GetItemCount() - 1, FALSE );

}