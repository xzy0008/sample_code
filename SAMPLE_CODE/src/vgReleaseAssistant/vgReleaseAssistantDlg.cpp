// vgReleaseAssistantDlg.cpp : 实现文件
//

#include "vgStableHeaders.h"
#include "vgReleaseAssistant.h"
#include "vgReleaseAssistantDlg.h"


#include <vgKernel/vgkSystemUtility.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgKernel/vgkStringVector.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CvgReleaseAssistantDlg 对话框




CvgReleaseAssistantDlg::CvgReleaseAssistantDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CvgReleaseAssistantDlg::IDD, pParent)
	, m_folderName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_strDirIn	= _versionsManager.getPathIn().c_str();

	m_strDirOut = _versionsManager.getPathOut().c_str();

	_oldTime = 0;

}

void CvgReleaseAssistantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strDirIn);
	DDX_Text(pDX, IDC_EDIT2, m_strDirOut);
	DDX_Text(pDX, IDC_EDIT_FOLDERNAME, m_folderName);
}

BEGIN_MESSAGE_MAP(CvgReleaseAssistantDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CvgReleaseAssistantDlg::OnBnClickedButton1Executing)
	ON_BN_CLICKED(IDC_BUTTON2, &CvgReleaseAssistantDlg::OnBnClickedButton2OpenPathIn)
	ON_BN_CLICKED(IDC_BUTTON3, &CvgReleaseAssistantDlg::OnBnClickedButton3OpenPathOut)
	ON_BN_CLICKED(IDC_CHECK_COMMON, &CvgReleaseAssistantDlg::OnBnClickedCheckCommon)
	ON_BN_CLICKED(IDC_CHECK_DEBUG, &CvgReleaseAssistantDlg::OnBnClickedCheckDebug)
	ON_BN_CLICKED(IDC_CHECK_RELEASE, &CvgReleaseAssistantDlg::OnBnClickedCheckRelease)
	ON_BN_CLICKED(IDC_BUTTON_ADDFLOLDER, &CvgReleaseAssistantDlg::OnBnClickedButtonAddflolder)
	ON_EN_CHANGE(IDC_EDIT_FOLDERNAME, &CvgReleaseAssistantDlg::OnEnChangeEditFoldername)
	ON_BN_CLICKED(IDC_BUTTON_REMOVEFLOLDER, &CvgReleaseAssistantDlg::OnBnClickedButtonRemoveflolder)
END_MESSAGE_MAP()


// CvgReleaseAssistantDlg 消息处理程序

BOOL CvgReleaseAssistantDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CvgReleaseAssistantDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}


//----------------------------------------------------------------
void CvgReleaseAssistantDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}



//----------------------------------------------------------------
HCURSOR CvgReleaseAssistantDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//----------------------------------------------------------------
void CvgReleaseAssistantDlg::OnBnClickedButton1Executing()
{
	_oldTime = GetTickCount();
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	if (m_strDirIn.IsEmpty() || m_strDirOut.IsEmpty())
	{
		AfxMessageBox("请输入参数！");
		return;
	}
	distrubuteFiles();

	return;

}


//----------------------------------------------------------------
void CvgReleaseAssistantDlg::OnBnClickedButton2OpenPathIn()
{
	// TODO: 在此添加控件通知处理程序代码

	vgKernel::StringVector	fileExt;
	fileExt.push_back("exe");

	vgKernel::StringVector	filePaths = vgKernel::SystemUtility::
		getFilesOpenByDialog(fileExt);

	if (filePaths.empty())
	{
		return;
	}

	String filePath = vgKernel::StringUtility::
		getPathFromAbsoluteFilename(filePaths[0].c_str());

	m_strDirIn = filePath.c_str();

	UpdateData(FALSE);
}


//----------------------------------------------------------------
void CvgReleaseAssistantDlg::OnBnClickedButton3OpenPathOut()
{
	// TODO: 在此添加控件通知处理程序代码
#if 0
	vgKernel::StringVector	fileExt;
	fileExt.push_back("exe");

	String	filePath = vgKernel::SystemUtility::
		getFileSaveByDialog(fileExt);

	if (filePath.empty())
	{
		return;
	}

	filePath = vgKernel::StringUtility::
		getPathFromAbsoluteFilename(filePath);

	m_strDirOut = filePath.c_str();
#endif
	CString selectPath = BrowseFolder( this->m_hWnd,"选择目录" ); 
	m_strDirOut = selectPath + '\\';

	assert( m_strDirOut != "" );

	UpdateData(FALSE);

}


//----------------------------------------------------------------
bool CvgReleaseAssistantDlg::distrubuteFiles()
{

	GroupNodeItemPtr	pRootNode;
	vgKernel::StringVector filters;

	
	// Step 1: 初始化目录结构
	pRootNode = _versionsManager.getVersionByVersionName( String("all") );
	getDirectorySystemIn( pRootNode,
		String(m_strDirIn) );
	
	pRootNode->getPath() = String(m_strDirIn);

	// Step 2: 过滤release和debug
	VersionMap* pVersions	= _versionsManager.getVersionsPtr();
	FiltersMap* pFilters	= _versionsManager.getFiltersPtr();
	VersionMapItr itrVer =  ++pVersions->begin();
	FiltersMapItr itrFil =  ++pFilters->begin();
	
	for ( ;
		itrVer != pVersions->end(), itrFil != pFilters->end();
		itrVer ++, itrFil ++)
	{
		filterVersion( &itrVer->second, itrFil->second);
	}


	// Step 3: 拷贝文件
	copyReleaseFiles();


	// Step 4: 转换结果提示
	outputResultMsg();

	pRootNode->deleteAllData();
	return true;

}


//----------------------------------------------------------------
int CvgReleaseAssistantDlg::getDirectorySystemIn( GroupNodeItemPtr pGroupNode, String filePath,
												 int* nCountFile/* = NULL*/, int* nCountDir/* = NULL*/  )
{
	int nCountLeaf(0), nCountBranch(0);

	using namespace vgGroup;
	
	GroupNodeItemPtr pTempParentNode = pGroupNode;

	TCHAR szFind[MAX_PATH]; 
	String src_path(filePath);
	String src_subpath;

	lstrcpy(szFind, src_path.c_str() ); 

	lstrcat(szFind, "\\"); 

	lstrcat(szFind, "*.*"); // 找所有文件 

	WIN32_FIND_DATA wfd; 

	HANDLE hFind = FindFirstFile(szFind, &wfd); 

	if (hFind == INVALID_HANDLE_VALUE) // 如果没有找到或查找失败 
		return false; 	
	do 
	{ 
		if (wfd.cFileName[0] == '.') 

			continue; // 过滤这两个目录 

		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
		{ 
			src_subpath = src_path + "\\" + wfd.cFileName;

			GroupNodeItem	subGroupNode( String(wfd.cFileName), pTempParentNode, 0, GROUP_NODE_BRANCH);

			getDirectorySystemIn( &subGroupNode, src_subpath, nCountFile, nCountDir );	

			pTempParentNode->appendSubItem( subGroupNode );

		} 
		else 
		{ 
			pTempParentNode->appendSubItem( String(wfd.cFileName) );			
		} 
	} while (FindNextFile(hFind, &wfd)); 

	FindClose(hFind); // 关闭查找句柄 

	return true;
}

//----------------------------------------------------------------
bool CvgReleaseAssistantDlg::filterVersion( GroupNodeItemPtr pGroupNode,
												vgKernel::StringVector filters)
{
	// pRootNodeIn 过滤到 pRootNodeOutD、pRootNodeOutR，即Debug和Release目录
	
	GroupNodeItemPtr	pRootNodeIn	= _versionsManager.getVersionByVersionName( String("all") );
	GroupNodeItemPtr	pRootNodeOut= pGroupNode;

	*pRootNodeOut = *pRootNodeIn;

	GroupNodeManager::filterVersion( pRootNodeOut, filters, _folderNameMap );

	return true;
}

//----------------------------------------------------------------
bool CvgReleaseAssistantDlg::copyReleaseFiles()
{

	VersionMap* pVersions	= _versionsManager.getVersionsPtr();
	VersionMapItr itrVer =  ++pVersions->begin();
	for ( ;
		itrVer != pVersions->end();
		itrVer ++)
	{
		String outDir = String(m_strDirOut) + itrVer->first + '\\';

		vgKernel::SystemUtility::createDirectory( outDir );

		copyReleaseFiles( &itrVer->second, outDir);
	}


	return true;
}

//----------------------------------------------------------------
bool CvgReleaseAssistantDlg::copyReleaseFiles( GroupNodeItemPtr pGroupNode, String dir )
{
	String dirParent = dir;

	GroupNodeItemVec*	pSubItems = pGroupNode->getSubItems();
	GroupNodeItemVec::iterator itr = pSubItems->begin();
	for ( ; itr != pSubItems->end(); itr ++)
	{
		//如果是分支，检测文件夹是否需要过滤,目前只检测bin 下的子文件夹
		if ( itr->getType() == GROUP_NODE_BRANCH && itr->getParentNode()->getParentNode() == NULL )
		{
			if ( !_versionsManager.checkIsNeedFilter( &(*itr), _folderNameMap ) )
			{
				String dirSrc = itr->getParentNode()->getPath();
				dirSrc += itr->getName();

				String dirDes = dirParent + itr->getName();
				vgKernel::SystemUtility::copyDirectory( dirDes, dirSrc );

				continue;
			}

		}

		if (  itr->isLeafItem() )
		{
			String fileSrc = itr->getParentNode()->getPath();
			fileSrc += itr->getName();

			String fileDes = dirParent + itr->getName();

			vgKernel::SystemUtility::copyFile(fileSrc, fileDes);
		}
		else //if( itr->hasSubItem() ) 
		{
			String dirTemp = dirParent + itr->getName() + '\\';
			vgKernel::SystemUtility::createDirectory( dirTemp );
			copyReleaseFiles(&(*itr), dirTemp );
		}
	}

	return true;
}

//----------------------------------------------------------------
void CvgReleaseAssistantDlg::outputResultMsg()
{
	DWORD elpseTime = GetTickCount() - _oldTime;
	CString str;
	str.Format( "%u", elpseTime );

	std::ostringstream ostr;
	ostr << "版本生成已完成，总共生成：";
	ostr << _versionsManager.getVersionsPtr()->size() - 1;
	ostr << "个版本！";
/*
	ostr << "\n";
	ostr << "耗时:";
	ostr << str;
	ostr << "毫秒";*/

	AfxMessageBox( ostr.str().c_str() );

	
	
	
}

//----------------------------------------------------------------
bool CvgReleaseAssistantDlg::AddVersionAndFilter( string versionName, 
												 vgKernel::StringVector filterString )
{
	//加入VersionMap
	VersionMap* pVersions = _versionsManager.getVersionsPtr();

	assert( pVersions != NULL );
	if ( !pVersions )
	{
		return false;
	}

	VersionMapItr itrVer =  pVersions->begin();
	pVersions->insert( VersionPair( versionName, itrVer->second ) );


	//加入FiltersMap
	FiltersMap* pFilters = _versionsManager.getFiltersPtr();

	assert( pFilters != NULL );
	if ( !pFilters )
	{
		return false;
	}

	pFilters->insert( FiltersPair( versionName,	filterString ) );

	return true;
}

//----------------------------------------------------------------
bool CvgReleaseAssistantDlg::RemoveVersionAndFilter( string versionName )
{
	//移除VersionMap
	VersionMap* pVersions = _versionsManager.getVersionsPtr();

	assert( pVersions != NULL );
	if ( !pVersions )
	{
		return false;
	}

	VersionMapItr itrVer = pVersions->find( versionName );
	if ( itrVer != pVersions->end() )
	{
		pVersions->erase( itrVer );
	}

	//移除FiltersMap
	FiltersMap* pFilters = _versionsManager.getFiltersPtr();

	assert( pFilters != NULL );
	if ( !pFilters )
	{
		return false;
	}

	FiltersMapItr itrFil = pFilters->find( versionName );
	if ( itrFil != pFilters->end() )
	{
		pFilters->erase( itrFil );
	}
	
	return true;
}

//----------------------------------------------------------------
void CvgReleaseAssistantDlg::OnBnClickedCheckCommon()
{
	// TODO: Add your control notification handler code here
	static bool bCheck = false;
	bCheck = !bCheck;

	if ( bCheck )
	{
		vgKernel::StringVector filterString;
		filterString.clear();
		filterString.push_back( "debug" );
		filterString.push_back( "release" );

		this->AddVersionAndFilter( "common", filterString );
	}
	else
	{
		this->RemoveVersionAndFilter( "common" );
	}
}

//----------------------------------------------------------------
void CvgReleaseAssistantDlg::OnBnClickedCheckDebug()
{
	// TODO: Add your control notification handler code here
	static bool bCheck = false;
	bCheck = !bCheck;

	if ( bCheck )
	{
		vgKernel::StringVector filterString;
		filterString.clear();
		filterString.push_back( "release" );

		this->AddVersionAndFilter( "debug", filterString );
	}
	else
	{
		this->RemoveVersionAndFilter( "debug" );
	}
}

//----------------------------------------------------------------
void CvgReleaseAssistantDlg::OnBnClickedCheckRelease()
{
	// TODO: Add your control notification handler code here
	static bool bCheck = false;
	bCheck = !bCheck;

	if ( bCheck )
	{
		vgKernel::StringVector filterString;
		filterString.clear();
		filterString.push_back( "debug" );

		this->AddVersionAndFilter( "release", filterString );
	}
	else
	{
		this->RemoveVersionAndFilter( "release" );
	}
}

//----------------------------------------------------------------
void CvgReleaseAssistantDlg::OnBnClickedButtonAddflolder()
{
	// TODO: Add your control notification handler code here
	if ( m_folderName == "" )
	{
		return;
	}

	//向列表框中加入数据
	CListBox* pListBox = ( ( CListBox* )GetDlgItem( IDC_LIST_SHOWFOLDER ) );
	pListBox->AddString( m_folderName );

	int index = pListBox->GetCount() - 1;

	_folderNameMap.insert( FolderNamePair( index, (String)m_folderName ) );

	//清空编辑框数据
	SetDlgItemText( IDC_EDIT_FOLDERNAME, "" );


}

//----------------------------------------------------------------
void CvgReleaseAssistantDlg::OnEnChangeEditFoldername()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData( true );
}

//----------------------------------------------------------------
void CvgReleaseAssistantDlg::OnBnClickedButtonRemoveflolder()
{
	// TODO: Add your control notification handler code here
	int index = ( ( CListBox* )GetDlgItem( IDC_LIST_SHOWFOLDER ) )->GetCurSel();
	if ( index < 0 )
	{
		return;
	}

	( ( CListBox* )GetDlgItem( IDC_LIST_SHOWFOLDER ) )->DeleteString( index );

	FolderNameMapItr iter = _folderNameMap.find( index );
	if ( iter != _folderNameMap.end() )
	{
		_folderNameMap.erase( iter );
	}

}

//----------------------------------------------------------------
CString CvgReleaseAssistantDlg::BrowseFolder( HWND hWnd, LPCTSTR lpTitle )
{

	char szPath[MAX_PATH]={0};
	BROWSEINFO m_bi;

	m_bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
	m_bi.hwndOwner = hWnd;
	m_bi.pidlRoot = NULL;
	m_bi.lpszTitle = lpTitle;
	m_bi.lpfn = NULL;
	m_bi.lParam = NULL;
	m_bi.pszDisplayName = szPath;

	LPITEMIDLIST pidl = ::SHBrowseForFolder( &m_bi );
	if ( pidl )
	{
		if( !::SHGetPathFromIDList ( pidl, szPath ) ) szPath[0]=0;

		IMalloc * pMalloc = NULL;
		if ( SUCCEEDED ( ::SHGetMalloc( &pMalloc ) ) ) // 取得IMalloc分配器接口
		{
			pMalloc->Free( pidl ); // 释放内存
			pMalloc->Release(); // 释放接口
		}
	}
	return szPath;
}