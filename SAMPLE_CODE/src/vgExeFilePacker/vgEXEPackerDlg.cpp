// vgTemplateSettingDlgDlg.cpp : 实现文件
//

#include "vgStableHeaders.h"
#include "vgEXEPacker.h"
#include "vgEXEPackerDlg.h"


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


// CvgTemplateSettingDlgDlg 对话框




CvgEXEPackerDlg::CvgEXEPackerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CvgEXEPackerDlg::IDD, pParent)
	, m_strDirIn(_T(""))
	, m_strDirOut(_T(""))
	, m_strDirExecute(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CvgEXEPackerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strDirIn);
	DDX_Text(pDX, IDC_EDIT2, m_strDirOut);
	DDX_Text(pDX, IDC_EDIT3, m_strDirExecute);
}

BEGIN_MESSAGE_MAP(CvgEXEPackerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CvgEXEPackerDlg::OnBnClickedButton1Executing)
	ON_BN_CLICKED(IDC_BUTTON2, &CvgEXEPackerDlg::OnBnClickedButton2OpenPathIn)
	ON_BN_CLICKED(IDC_BUTTON3, &CvgEXEPackerDlg::OnBnClickedButton3OpenPathOut)
	ON_BN_CLICKED(IDC_BUTTON4, &CvgEXEPackerDlg::OnBnClickedButtonEXE)
END_MESSAGE_MAP()


// CvgTemplateSettingDlgDlg 消息处理程序

BOOL CvgEXEPackerDlg::OnInitDialog()
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

void CvgEXEPackerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CvgEXEPackerDlg::OnPaint()
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

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CvgEXEPackerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CvgEXEPackerDlg::OnBnClickedButton1Executing()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	if (m_strDirIn==""||m_strDirOut=="" )
	{
		::MessageBox(NULL,"参数不能为空","",MB_OK | MB_TOPMOST );
		return;
	}

	String src_file_path = m_strDirIn;

	String des_file_path = m_strDirOut;
	
	String execute_file_path = m_strDirExecute;

	String ExeFileName = vgKernel::StringUtility::getFilenameFromAbsolutePath(des_file_path);

	String ExeFileNameWithoutExt =  vgKernel::StringUtility::getFilenameWithoutExtension(ExeFileName); 

	String ExeFileFolderPath = vgKernel::StringUtility::getPathFromAbsoluteFilename(des_file_path);

	char tempSystemPath[MAX_PATH]; 
	GetTempPath(MAX_PATH,tempSystemPath);

	String currentDirectory = tempSystemPath;

	String vgFileFolderName = vgKernel::StringUtility::getFilenameFromAbsolutePath(src_file_path);

	String currentProcessName = vgKernel::SystemUtility::getCurrentProcessName();

	String processDirectory = vgKernel::SystemUtility::getCurrentProcessPath();

	// 定位并新建打包目录
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// 2、新建临时目录并保存源文件夹
	String::size_type found = src_file_path.find_last_of( "\\/" );
	String srcFolder = src_file_path.substr( 0 , found );
	String tempfolderName = vgKernel::StringUtility::getFilenameFromAbsolutePath(srcFolder);
	String tempFolder = currentDirectory + tempfolderName;
	
	vgKernel::SystemUtility::createDirectory(tempFolder);
	vgKernel::SystemUtility::copyDirectory(tempFolder,srcFolder);

	// 保存文件夹
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// 3、在临时目录新建并保存打包配置文件（sescript、data.ini等）

	FILE* iniFile;
	String fileName = processDirectory + "sescript" ;
	String strLine;
	if( !_tfopen_s( &iniFile, fileName.c_str() , _T("wt") ) )
	{
		strLine =  "Silent=1" ;
		_ftprintf( iniFile,  _T("%s%c")  , strLine.c_str(), '\n' );
		strLine =  "Overwrite=1" ;
		_ftprintf( iniFile,  _T("%s%c")  , strLine.c_str(), '\n' );
		strLine =  "TempMode" ;
		_ftprintf( iniFile,  _T("%s%c")  , strLine.c_str(), '\n' );
		strLine = "Setup=" + tempfolderName + "\\" + vgKernel::StringUtility::getFilenameFromAbsolutePath(execute_file_path);
		_ftprintf( iniFile,  _T("%s")  , strLine.c_str() );
		fclose( iniFile );
	}
	else
	{
		fclose( iniFile );
	}

	// 新建并保存打包配置文件（sescript、data.ini等）
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// 4、复制其它文件（路径动画、背景音效、数据库文件、打包必需文件等）至临时目录
	String srcDirPath = execute_file_path;
	String desDirPath = tempFolder + "\\" + vgKernel::StringUtility::getFilenameFromAbsolutePath(execute_file_path);
	vgKernel::SystemUtility::copyFile(srcDirPath,desDirPath);

	// 复制其它文件（路径动画、背景音效、数据库文件、打包必需文件等）
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// 5、打包临时目录开始...

	String sourceDir = processDirectory + "Default.SFX";
	String destinDir = currentDirectory + "Default.SFX";
	vgKernel::SystemUtility::copyFile(sourceDir, destinDir);

	sourceDir = processDirectory + "VRGIS.ico";
	destinDir = currentDirectory + "VRGIS.ico";
	vgKernel::SystemUtility::copyFile(sourceDir, destinDir);

	sourceDir = processDirectory + "sescript";
	destinDir = currentDirectory + "sescript";
	vgKernel::SystemUtility::copyFile(sourceDir, destinDir);

	String zipParameter = String("a -m0 -inul -idp -sfxDefault.SFX -ibck -iiconVRGIS.ico -zsescript ")
		+ ExeFileNameWithoutExt + " "
		+ tempfolderName;
	
	CFile fp;
	String dllFileName = processDirectory + "mfcm80chs.dll";
	if (!fp.Open( dllFileName.c_str()  , CFile::modeRead))
	{
		::MessageBox(NULL,"没有找到打包软件，失败！","",MB_OK | MB_TOPMOST );
		fp.Close();
		return;
	}
	fp.Close();

	String zipFileName = processDirectory + "vgZip.exe";
	vgKernel::SystemUtility::moveFile( dllFileName, zipFileName );

	if (!fp.Open( zipFileName.c_str()  , CFile::modeRead))
	{
		::MessageBox(NULL,"没有找到打包软件，失败！","",MB_OK | MB_TOPMOST );
		fp.Close();
		return;
	}
	fp.Close();

	SHELLEXECUTEINFO ShExecInfo = {0};
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = zipFileName.c_str();             
	ShExecInfo.lpParameters = zipParameter.c_str();     
	ShExecInfo.lpDirectory = currentDirectory.c_str();
	ShExecInfo.nShow = SW_SHOWNORMAL;
	ShExecInfo.hInstApp = NULL;       
	ShellExecuteEx(&ShExecInfo);

	long waitStatus = WaitForSingleObject(ShExecInfo.hProcess,INFINITE);

	if ( waitStatus )
	{
		::MessageBox(NULL,"打包失败！","",MB_OK | MB_TOPMOST );
		vgKernel::SystemUtility::moveFile( zipFileName, dllFileName );

		String filename = currentDirectory + "Default.SFX";
		vgKernel::SystemUtility::removeFile(filename,false);
		filename = currentDirectory + "VRGIS.ico";
		vgKernel::SystemUtility::removeFile(filename,false);
		filename = currentDirectory + "sescript";
		vgKernel::SystemUtility::removeFile(filename,false);

		return;
	}

	vgKernel::SystemUtility::moveFile( zipFileName, dllFileName );

	// 打包结束
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// 6、拷贝exe包至目的目录，删除临时目录 及 exe包

	String srcFileName = currentDirectory + ExeFileName;

	String desFileName = ExeFileFolderPath + ExeFileName;

	vgKernel::SystemUtility::copyFile( srcFileName, desFileName );

	vgKernel::SystemUtility::removeFile( srcFileName, false );

	vgKernel::SystemUtility::removeDirectory( tempFolder );

	String filename = currentDirectory + "Default.SFX";
	vgKernel::SystemUtility::removeFile(filename,false);
	filename = currentDirectory + "VRGIS.ico";
	vgKernel::SystemUtility::removeFile(filename,false);
	filename = currentDirectory + "sescript";
	vgKernel::SystemUtility::removeFile(filename,false);

	//拷贝exe包至目的目录，删除临时目录 及 exe包
	//////////////////////////////////////////////////////////////////////////

	::MessageBox(
		AfxGetApp()->m_pMainWnd->m_hWnd ,"打包结束！","提示",MB_OK | MB_TOPMOST );


	return;

}

void CvgEXEPackerDlg::OnBnClickedButton2OpenPathIn()
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

void CvgEXEPackerDlg::OnBnClickedButton3OpenPathOut()
{
	// TODO: 在此添加控件通知处理程序代码

	vgKernel::StringVector	fileExt;
	fileExt.push_back("exe");

	String	filePath = vgKernel::SystemUtility::
		getFileSaveByDialog(fileExt);

	if (filePath.empty())
	{
		return;
	}

// 	filePath = vgKernel::StringUtility::
// 		getPathFromAbsoluteFilename(filePath);

	m_strDirOut = filePath.c_str();

	UpdateData(FALSE);

}

void CvgEXEPackerDlg::OnBnClickedButtonEXE()
{
	// TODO: 在此添加控件通知处理程序代码
	vgKernel::StringVector	fileExt;
	fileExt.push_back("exe");

	String	filePath = vgKernel::SystemUtility::
		getFileSaveByDialog(fileExt);

	if (filePath.empty())
	{
		return;
	}

	// 	filePath = vgKernel::StringUtility::
	// 		getPathFromAbsoluteFilename(filePath);

	m_strDirExecute = filePath.c_str();

	UpdateData(FALSE);

}
