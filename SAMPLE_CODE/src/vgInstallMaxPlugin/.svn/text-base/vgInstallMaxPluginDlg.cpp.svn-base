// vgTemplateSettingDlgDlg.cpp : 实现文件
//

#include "vgStableHeaders.h"
#include "vgInstallMaxPlugin.h"
#include "vgInstallMaxPluginDlg.h"


#include "vgPatchUtility.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//标识拷贝文件部分占进度条的百分比
const int percentRate = 8;   /* 80% */

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


// CvgInstallPatchWizardDlg 对话框




CvgInstallPatchWizardDlg::CvgInstallPatchWizardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CvgInstallPatchWizardDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	_desDirs.empty();
	_numOfFiles = 0;
	_numOfDirs = 0;
	_progressPos = 0;
}

void CvgInstallPatchWizardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_progressCtrl);
}

BEGIN_MESSAGE_MAP(CvgInstallPatchWizardDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_INSTALL, &CvgInstallPatchWizardDlg::OnBnClickedInstall)
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CvgInstallPatchWizardDlg 消息处理程序

BOOL CvgInstallPatchWizardDlg::OnInitDialog()
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
	CStatic* pStatic = ((CStatic*)GetDlgItem(IDC_STATIC_TEXT));
	pStatic->SetWindowText( "欢迎使用 Max 9.0 Plugin For VRGIS 安装程序!" );
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CvgInstallPatchWizardDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CvgInstallPatchWizardDlg::OnPaint()
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
		//对话框在桌面中央最前端显示
		CRect rect;
		GetWindowRect( &rect );
		SetWindowPos(&(AfxGetApp()->m_pMainWnd->wndTopMost), rect.left, rect.top, 
			rect.Width(), rect.Height(), SWP_SHOWWINDOW );

		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CvgInstallPatchWizardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CvgInstallPatchWizardDlg::OnBnClickedInstall()
{
	CStatic* pStatic = ((CStatic*)GetDlgItem( IDC_STATIC_TEXT ));
	pStatic->SetWindowText( "正在搜索安装目录..." );


	//从注册表获取安装目录
	if ( !this->getDesPathFormRegedit() )
	{
 		return;
	}

	GroupNodeItemPtr pRootNode;
	pRootNode = _nodeManger.getVersionByVersionName( String("all") );
	assert( pRootNode != NULL );

	String srcDir = _nodeManger.getPathIn();

	assert( srcDir != "" );

	pStatic->SetWindowText( "正在生成更新信息..." );

	//生成树状目录
	this->getDirectorySystemIn( pRootNode, srcDir );

	//////////////////////////////////////////////////////////////////////////
	//设置进度条范围
	assert( _numOfDirs != 0 );
	m_progressCtrl.SetRange( 0, _numOfFiles*10*_numOfDirs );

	_progressPos = _numOfFiles * ( 10 - percentRate ) * _numOfDirs;
	m_progressCtrl.SetPos( _progressPos );
	//////////////////////////////////////////////////////////////////////////

	//循环拷贝文件
	vector<String>::iterator itr = _desDirs.begin();
	vector<String>::iterator itr_end = _desDirs.end();

	for ( ; itr != itr_end; itr++ )
	{
		String desDir = *itr;
		this->copyPatchFiles( pRootNode, desDir );
	}
	

	pStatic->SetWindowText( "安装完成，请按“确定”按纽关闭安装程序!" );
	CButton* pButton = ((CButton*)GetDlgItem( IDC_INSTALL ));
	pButton->EnableWindow( FALSE );

}

//----------------------------------------------------------------
bool CvgInstallPatchWizardDlg::getDesPathFormRegedit()
{
	//从注册表中获取安装目录
	bool result = false;

	HKEY      hRootKey;       
	LPCTSTR   data_Set = "software\\Autodesk\\3dsmax\\9.0\\";

	//打开注册表项,检查是否安装了Max 9.0程序
	long  ret0 = ( ::RegOpenKeyEx( HKEY_LOCAL_MACHINE, data_Set, 0, KEY_READ, &hRootKey ) );    
	if( ret0 != ERROR_SUCCESS )   
	{
		string msg = "错误:无法打开有关的hRootKey!请检查您是否已经安装了Max 9.0程序！";
		::MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd, msg.c_str(), 
			"错误", MB_OK|MB_ICONASTERISK );     
		return false;
	}     

	DWORD   dwIndex = 0;
	CString strKeyName;
	DWORD   dwNameSize = 256;

	//遍历9.0文件夹下的所有目录项
	LONG lRet = RegEnumKeyEx( hRootKey, dwIndex, strKeyName.GetBuffer(dwNameSize ), 
		&dwNameSize, 0, NULL, NULL, NULL );

	while( ERROR_SUCCESS == lRet )
	{
		if ( strKeyName.Find( "MAX-1" ) != -1 )
		{
			LPBYTE   path_Get = new BYTE[256];    
			DWORD    type = REG_SZ;
			DWORD    cbData = 256;  

			CString keyName;
			keyName.Append( "software\\Autodesk\\3dsmax\\9.0\\" );
			keyName.Append( strKeyName.GetBuffer( dwNameSize ) );
			keyName.Append( "\\" );

			LPCTSTR   data_Set2 = keyName.GetBuffer( sizeof(keyName) );

			//打开目的注册表项
			HKEY hSubKey;
			long  ret0 = ( ::RegOpenKeyEx( HKEY_LOCAL_MACHINE, data_Set2, 0, KEY_READ, &hSubKey ) );     
			if( ret0 != ERROR_SUCCESS )   
			{
				string msg = "错误:无法打开有关的hSubKey!请检查您是否已经安装了Max 9.0程序！";
				::MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd, msg.c_str(), 
					"错误", MB_OK|MB_ICONASTERISK );     
			}     

			//根据Installdir键值查询安装目录
			long ret1 = ::RegQueryValueEx( hSubKey, "Installdir", NULL, &type, path_Get, &cbData );  
			if ( ret1 == ERROR_SUCCESS )
			{
				result = true;
				
				//处理目标路径
				CString exeAbsPath = (CString)path_Get;
				String desPath = vgUtility::PatchUtility::getPathFromAbsoluteFilename( (String)exeAbsPath );
				desPath += "\plugins\\";

				_desDirs.push_back( desPath );  //向数组中添加目标路径

				delete[] path_Get;
				path_Get = NULL;
			}

			_numOfDirs ++;

			::RegCloseKey( hSubKey );  //关闭子项

		}
		dwIndex++;
		dwNameSize = 256;
		lRet = RegEnumKeyEx( hRootKey, dwIndex, strKeyName.GetBuffer(dwNameSize ), 
			&dwNameSize, 0, NULL, NULL, NULL );
	}

	::RegCloseKey( hRootKey );     //程序结束前要关闭已经打开的RootKey

	if ( result == false )
	{
		string msg = "错误:无法查询有关注册表信息!请检查您是否已经安装了Max 9.0程序！";
		::MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd, msg.c_str(), 
			"错误", MB_OK | MB_ICONASTERISK );  
		return false;     
	}  


	return result;
}
//----------------------------------------------------------------
int CvgInstallPatchWizardDlg::getDirectorySystemIn( GroupNodeItemPtr pGroupNode, String filePath,
												 int* nCountFile/* = NULL*/, int* nCountDir/*NULL*/  )
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

	HANDLE hFind = FindFirstFile( szFind, &wfd ); 

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
			_numOfFiles ++;  //文件个数累加
			pTempParentNode->appendSubItem( String(wfd.cFileName) );
		} 
	} while (FindNextFile(hFind, &wfd)); 

	FindClose(hFind); // 关闭查找句柄 

	return true;
}

//----------------------------------------------------------------
bool CvgInstallPatchWizardDlg::copyPatchFiles( GroupNodeItemPtr pGroupNode, String dir )
{
	String dirParent = dir;

	GroupNodeItemVec*	pSubItems = pGroupNode->getSubItems();
	GroupNodeItemVec::iterator itr = pSubItems->begin();
	for ( ; itr != pSubItems->end(); itr ++)
	{
		if (  itr->isLeafItem() )
		{
			String fileSrc = itr->getParentNode()->getPath();
			fileSrc += itr->getName();

			String fileDes = dirParent + itr->getName();

			//输出正在更新的文件信息
			CStatic* pStatic = ((CStatic*)GetDlgItem( IDC_STATIC_TEXT ));
			String msg = "正在更新文件 " + itr->getName(); 
			pStatic->SetWindowText( msg.c_str() );

			//拷贝文件
			vgUtility::PatchUtility::copyFile(fileSrc, fileDes);

			//设置进度条
			_progressPos += percentRate;
			m_progressCtrl.SetPos( _progressPos );
		}
		else 
		{
			String dirTemp = dirParent + itr->getName() + '\\';
			vgUtility::PatchUtility::createDirectory( dirTemp );
			copyPatchFiles(&(*itr), dirTemp );//递归调用 
		}
	}

	return true;
}
