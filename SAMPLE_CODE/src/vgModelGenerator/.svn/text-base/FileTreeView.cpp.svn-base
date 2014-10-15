// FileTreeView.cpp : implementation file
//

#include <vgStableHeaders.h>
//#include "SystemTree.h"
#include "FileTreeView.h"

#include "FileTreeDlg.h"
#include <direct.h>




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileTreeView

IMPLEMENT_DYNCREATE(CFileTreeView, CView)

CFileTreeView::CFileTreeView()
{
	//CFileTreeDlg dlg;

	//dlg.DoModal();
}

CFileTreeView::~CFileTreeView()
{
}


BEGIN_MESSAGE_MAP(CFileTreeView, CView)
	//{{AFX_MSG_MAP(CFileTreeView)
	ON_NOTIFY(TVN_ITEMEXPANDING, ID_FILETREE, OnItemexpanding)
	//ON_NOTIFY(NM_DBLCLK, ID_FILETREE, OnDblclk)
	ON_WM_SIZE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileTreeView drawing

void CFileTreeView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CFileTreeView diagnostics

#ifdef _DEBUG
void CFileTreeView::AssertValid() const
{
	CView::AssertValid();
}

void CFileTreeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFileTreeView message handlers

void CFileTreeView::InitRootDirectory()
{
	HTREEITEM		hItem,hti;
	CStringArray	arDriverName;
	CString			strDriverName;
	CString			str;
	UINT			nDriverType;

	if (m_tree.GetImageList(TVSIL_NORMAL) == NULL)
		m_tree.SetImageList(&m_ImageList,TVSIL_NORMAL);

	hItem = m_tree.InsertItem(_T("我的电脑"),0,0,TVI_ROOT,TVI_LAST);

	char szDriverName[500];
	char szDriverLabel[500];
	memset(szDriverName,0,sizeof(szDriverName));
	memset(szDriverLabel,0,sizeof(szDriverLabel));
	DWORD nLength = GetLogicalDriveStrings(sizeof(szDriverName),szDriverName);
	
	int i;

	for ( i=0; i<(int)nLength; i++)
	{
		if (szDriverName[i] != '\0')
			strDriverName += szDriverName[i];
		else
		{
			strDriverName = strDriverName.Left(strDriverName.GetLength() - 1);
			arDriverName.Add(strDriverName);
			strDriverName = "";
		}
	}


	char *szCurDir = NULL;
	for (i=0; i<arDriverName.GetSize(); i++)
	{
		nDriverType = GetDriveType((LPCTSTR)arDriverName.GetAt(i));
		GetVolumeInformation((LPCTSTR)(arDriverName.GetAt(i) + "\\"),szDriverLabel,\
			sizeof(szDriverLabel),NULL,NULL,0,NULL,0);
		hti = m_tree.InsertItem((CString)szDriverLabel + "(" + arDriverName.GetAt(i) + ")",\
			nDriverType,nDriverType,hItem,TVI_LAST);

		DisplayButton(hti);
		memset(szDriverLabel,0,sizeof(szDriverLabel));
	}

	hti = m_tree.GetRootItem();
	m_tree.SelectItem(hti);
	m_tree.Expand(hti,TVE_EXPAND);
}

void CFileTreeView::DisplayButton(HTREEITEM hti)
{
	TVITEM tvi;
	tvi.mask = TVIF_CHILDREN;
	tvi.hItem = hti;
	tvi.cChildren = 1;

	m_tree.SetItem(&tvi);
}

CString CFileTreeView::GetFileExName(TCHAR cFileName[MAX_PATH])
{
	CString strFileName,strFileExName;

	strFileName = (CString)cFileName;
	strFileExName.Empty();
	for (int i=strFileName.GetLength()-1; i>=0; i--)
	{
		if (strFileName.GetAt(i) != '.')
			strFileExName = strFileName.GetAt(i) + strFileExName;
		else
			return strFileExName;
	}
	return strFileExName;
}

BOOL CFileTreeView::GetSubSiblingItem(HTREEITEM hItem, char *szCurDir)
{
	BOOL bHaveChild = FALSE;
	CString strEx;
	HANDLE hFind;
	HTREEITEM hti;
	WIN32_FIND_DATA wfd;

	if (_chdir(szCurDir) != 0) return bHaveChild;
	hFind = FindFirstFile(_T("*.*"),&wfd);
	if(hFind == INVALID_HANDLE_VALUE) return bHaveChild;

	if ((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
		!(wfd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
	{
		if( wfd.cFileName[0] != '.' )
		{
			bHaveChild = TRUE;
			hti = m_tree.InsertItem(wfd.cFileName,6,6,hItem,TVI_FIRST);
			m_tree.SetItemData(hti,DIR);
			DisplayButton(hti);
			_chdir(".."); // 查找完毕之后, 返回上一级目录
		} 
	} 
	else
	{ 
		strEx = GetFileExName(wfd.cFileName);
		strEx.MakeUpper();
		if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
		{
			if (strEx == "RTF")
			{
				hti = m_tree.InsertItem(wfd.cFileName,8,8,hItem,TVI_LAST);
				m_tree.SetItemData(hti,FILE);
				bHaveChild = TRUE;
			}
			else if (strEx == "TXT" || strEx == "LOG" || strEx == "INI" || strEx == "HTM" ||
					 strEx == "HTML"|| strEx == "CPP" || strEx == "H"   || strEx == "JAVA"||
					 strEx == "C"   || strEx == "CSS" || strEx == "DIC" || strEx == "INF")
			{
				hti = m_tree.InsertItem(wfd.cFileName,7,7,hItem,TVI_LAST);
				m_tree.SetItemData(hti,FILE);
				bHaveChild = TRUE;
			}
		}
	} 

	while(FindNextFile(hFind, &wfd)) 
	{ 
		if ((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && 
			!(wfd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
		{ 
			if(wfd.cFileName[0] != '.') 
			{ 
				bHaveChild = TRUE;
				hti = m_tree.InsertItem(wfd.cFileName,6,6,hItem,TVI_FIRST);
				m_tree.SetItemData(hti,DIR);
				DisplayButton(hti);
				_chdir(".."); // 查找完毕之后, 返回上一级目录 
			} 
		} 
		else 
		{ 
			strEx = GetFileExName(wfd.cFileName);
			strEx.MakeUpper();
			if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
			{
				if (strEx == "RTF")
				{
					hti = m_tree.InsertItem(wfd.cFileName,8,8,hItem,TVI_LAST);
					m_tree.SetItemData(hti,FILE);
					bHaveChild = TRUE;
				}
				else if (strEx == "TXT" || strEx == "LOG" || strEx == "INI" || strEx == "HTM" ||
						 strEx == "HTML"|| strEx == "CPP" || strEx == "H"   || strEx == "JAVA"||
						 strEx == "C"   || strEx == "CSS" || strEx == "DIC" || strEx == "INF")
				{
					hti = m_tree.InsertItem(wfd.cFileName,7,7,hItem,TVI_LAST);
					m_tree.SetItemData(hti,FILE);
					bHaveChild = TRUE;
				}
			}
		} 
	} 
	FindClose(hFind);
	return bHaveChild;}

BOOL CFileTreeView::HaveSubDirOrFile(char *szCurDir)
{
	BOOL bHaveChild = FALSE;
	HANDLE hFind;
	WIN32_FIND_DATA wfd;
	CString strEx;

	if (_chdir(szCurDir) != 0) return bHaveChild;
	hFind = FindFirstFile(_T("*.*"),&wfd);
	if(hFind == INVALID_HANDLE_VALUE) return bHaveChild;

	if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
	{ 
		if( wfd.cFileName[0] != '.' ) 
		{
			bHaveChild = TRUE;
			_chdir(".."); // 查找完毕之后, 返回上一级目录 
			FindClose(hFind);
			return bHaveChild;
		} 
	} 
	else
	{ 
		strEx = GetFileExName(wfd.cFileName);
		strEx.MakeUpper();
		if (strEx == "TXT" || strEx == "LOG" || strEx == "INI" || strEx == "HTM" ||
		    strEx == "HTML"|| strEx == "CPP" || strEx == "H"   || strEx == "JAVA"||
		    strEx == "C"   || strEx == "CSS" || strEx == "DIC" || strEx == "INF" ||
			strEx == "RTF")
		{
			bHaveChild = TRUE;
			FindClose(hFind);
			return bHaveChild;
		}
	} 

	while(FindNextFile(hFind, &wfd)) 
	{ 
		if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
		{ 
			if(wfd.cFileName[0] != '.') 
			{ 
				bHaveChild = TRUE;
				_chdir("..");
				FindClose(hFind);
				return bHaveChild;
			} 
		} 
		else 
		{ 
			strEx = GetFileExName(wfd.cFileName);
			strEx.MakeUpper();
			if (strEx == "TXT" || strEx == "LOG" || strEx == "INI" || strEx == "HTM" ||
				strEx == "HTML"|| strEx == "CPP" || strEx == "H"   || strEx == "JAVA"||
				strEx == "C"   || strEx == "CSS" || strEx == "DIC" || strEx == "INF" ||
				strEx == "RTF")
			{
				bHaveChild = TRUE;
				FindClose(hFind);
				return bHaveChild;
			}
		}
	} 
	FindClose(hFind);
	return bHaveChild;
}

void CFileTreeView::HideButton(HTREEITEM hti)
{
	TVITEM tvi;
	tvi.mask = TVIF_CHILDREN;
	tvi.hItem = hti;
	tvi.cChildren = 0;

	m_tree.SetItem(&tvi);
}

void CFileTreeView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{

	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CFileTreeView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HTREEITEM hti,hParent;
	CTreeCtrl &tree = m_tree;
	CString strPath,str1,str2;

	hti = tree.GetSelectedItem();
	if (tree.GetItemData(hti) == FILE)
	{
		strPath = tree.GetItemText(hti);
		hParent = tree.GetParentItem(hti);
		while (hParent != tree.GetRootItem())
		{
			strPath = tree.GetItemText(hParent) + "\\" + strPath;
			hParent = tree.GetParentItem(hParent);
		}
		strPath += "\\";
		str1 = strPath.Mid(strPath.Find(":") - 2 + 1,2);
		str2 = strPath.Right(strPath.GetLength() - strPath.Find(":") - 2);
		strPath = str1 + str2;
		strPath = strPath.Left(strPath.GetLength() - 1);
		m_strOpenFile = strPath;

		/////////////////////////////////////////////////////////////////////
		//临时打开文件
//		CMDIChildWnd *pMainFrame = ((CMainFrame*)GetParentFrame())->MDIGetActive();
//		CWnd *pWnd = ((CRichFrame*)pMainFrame)->m_wndSplitter.GetPane(0,0);
//		CRichSyntaxView *pRich = (CRichSyntaxView*)pWnd;
//		pRich->SetFileName(strPath);
//		pRich->OnOpen();
		/////////////////////////////////////////////////////////////////////
	}

	*pResult = 0;
}

////////////////////////////////////////////////////////////////////////
//当需要展开节点时，将该节点下的内容加入
////////////////////////////////////////////////////////////////////////
void CFileTreeView::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	CTreeCtrl &tree = m_tree;
	HTREEITEM hti = pNMTreeView->itemNew.hItem;
	
	if (hti != tree.GetRootItem())
	{
		//清空儿子
		HTREEITEM hChild = tree.GetChildItem(hti);
		while (hChild)
		{
			tree.DeleteItem(hChild);
			hChild = tree.GetChildItem(hti);
		}

		char *szCurDir;
		HTREEITEM hParent;
		CString strPath,str1,str2;

		strPath = tree.GetItemText(hti);
		hParent = tree.GetParentItem(hti);
		while (hParent != tree.GetRootItem())
		{
			strPath = tree.GetItemText(hParent) + "\\" + strPath;
			hParent = tree.GetParentItem(hParent);
		}
		strPath += "\\";
		str1 = strPath.Mid(strPath.Find(":") - 2 + 1,2);
		str2 = strPath.Right(strPath.GetLength() - strPath.Find(":") - 2);
		strPath = str1 + str2;

		szCurDir = (LPSTR)(LPCSTR)strPath;
		if (!GetSubSiblingItem(hti,szCurDir))
			HideButton(hti);
	}

	*pResult = 0;
}

void CFileTreeView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if (m_tree)
		m_tree.MoveWindow(0,0,cx,cy,TRUE);
}

int CFileTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_tree)
		m_tree.Create(WS_CHILD|WS_VISIBLE|TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS,CRect(0,0,0,0),this,ID_FILETREE);

	if (!m_ImageList)
		m_ImageList.Create(IDB_FILE,16,16,RGB(0,255,0));

	InitRootDirectory();

	return 0;
}

void CFileTreeView::OnFiletreeRefresh()
{
	InitRootDirectory();
}
