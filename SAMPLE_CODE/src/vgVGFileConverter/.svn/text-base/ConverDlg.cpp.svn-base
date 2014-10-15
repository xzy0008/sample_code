// WizardSheetDlg.cpp : implementation file
//

#include <vgStableHeaders.h>
#include <vgConf/XMLProfile.h>
#include "convertapp.h"
#include "convertdlg.h"

#include "vgMod/vgFileWriterVG.h"
#include "vgMod/vgFileReaderMOD.h"
#include "vgGlobal/vggSceneFileUtility.h"

#include "vgCam/vgcaCamManager.h"
#include "vgSound/vgSoundManager.h"

#include "vgKernel/vgkOpenGLSupport.h"
//#include <vgRoot.h>
#include <vgSound/vgSoundManager.h>
#include <vgMod/vgNodeManager.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWizardSheetDlg dialog

CWizardSheetDlg::CWizardSheetDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CWizardSheetDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


CWizardSheetDlg::~CWizardSheetDlg()
{
	releaseGLContext();
}

void CWizardSheetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWizardSheetDlg, CBCGPDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_INFILE, &CWizardSheetDlg::OnBnClickedInfile)
	ON_BN_CLICKED(IDC_OUTFILE, &CWizardSheetDlg::OnBnClickedOutfile)
	ON_BN_CLICKED(ID_GENERATE, &CWizardSheetDlg::OnBnClickedGenerate)
END_MESSAGE_MAP()

//vgCore::Root *p_root = new vgCore::Root("win_log.log"); 

// CWizardSheetDlg message handlers

BOOL CWizardSheetDlg::OnInitDialog()
{

	CDialog::OnInitDialog();
	
	CWaitCursor wait;

	UpdateData ();
	theApp.WriteInt (_T("Image"), true);

	theApp.WriteInt (_T("PushButtonsDefaultLook"), false);

	CBCGPButton::m_bDontSkin = false;
	RedrawWindow (NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN);

	SetBackgroundImage (true ? IDB_BITMAP4 : 0);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here


	UpdateData(FALSE);

	
	initializeEnvironment();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWizardSheetDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWizardSheetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CWizardSheetDlg::OnBnClickedInfile()
{
	// TODO: 在此添加控件通知处理程序代码
	char szFilters[]=
		"(*.vg)|*.vg|All Files (*.*)|*.*||";

	CFileDialog dlg (TRUE, "vg", "*.vg",
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);

	if (dlg.DoModal())
	{
		m_inFile = dlg.GetPathName();

		SetDlgItemText(IDC_INFILE_EDIT, m_inFile.c_str());

		UpdateData(FALSE);
	}
}

void CWizardSheetDlg::OnBnClickedOutfile()
{
	// TODO: 在此添加控件通知处理程序代码
	char szFilters[]=
		"(*.vg)|*.vg|All Files (*.*)|*.*||";

	CFileDialog dlg (FALSE, "vg", "*.vg",
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);

	if (dlg.DoModal())
	{
		m_outFile = dlg.GetPathName();
		
		SetDlgItemText(IDC_OUTFILE_EDIT, m_outFile.c_str());
		UpdateData(FALSE);
	}
}

void CWizardSheetDlg::OnBnClickedGenerate()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( m_inFile.empty() || m_outFile.empty() )
	{
		AfxMessageBox("请设置输入输出路径！");
	}

	copyAllFilesDefault();

	vgGlobal::SceneFileUtility::setUpdateTime(0);

	vgGlobal::SceneFileUtility::openSceneDirectly( m_inFile );

	vgGlobal::SceneFileUtility::setUpdateTime(1);

	vgGlobal::SceneFileUtility::saveSceneDirectly( m_folderpathOut );

	AfxMessageBox("转换完成！");

	m_inFile = "";

	m_outFile = "";

	SetDlgItemText(IDC_INFILE_EDIT, m_inFile.c_str());
	SetDlgItemText(IDC_OUTFILE_EDIT, m_outFile.c_str());

	UpdateData(FALSE);

	resetManager();
}

void CWizardSheetDlg::copyAllFilesDefault()
{
	string prefix = 
		vgKernel::StringUtility::getFilenameWithoutExtFromAbsPath( m_outFile );


	string folderpath = 
		vgKernel::StringUtility::getPathFromAbsoluteFilename( m_outFile );

	string dirpath = "VRGIS_" + prefix; 
	m_folderpathOut = folderpath + dirpath;
	BOOL createok = vgKernel::SystemUtility::createDirectory(m_folderpathOut);

	if ( createok == FALSE )
	{
		return ;
	}

	string folderpathIn = 
		vgKernel::StringUtility::getPathFromAbsoluteFilename( m_inFile );

	vgKernel::SystemUtility::copyDirectory(m_folderpathOut, folderpathIn);

	string filename = 
		vgKernel::StringUtility::getFilenameFromAbsolutePath( m_inFile );

	m_folderpathOut += "\\";
	m_folderpathOut += filename;

}

void CWizardSheetDlg::initializeEnvironment()
{
	initGLContext();

	vgCam::CamManager::getSingleton();
	vgSound::SoundManager::getSingleton();

	if ( vgCore::MovingManager::getSingletonPtr() == 0)
	{
		m_pMovingMgr = new vgCore::MovingManager();
		assert( m_pMovingMgr != NULL );

		m_pMovingMgr->initialise();

	}

	if ( vgCore::TextureManager::getSingletonPtr() == 0)
	{
		m_pTextureMgr = new vgCore::TextureManager();
		assert( m_pTextureMgr != NULL );

	}

	if( vgCore::ArchiveManager::getSingletonPtr() == 0 )
	{
		m_pArchiveManger = new vgCore::ArchiveManager( true );
	}

	if( vgCore::GpuManager::getSingletonPtr() == 0 )
	{
		m_pGpuManager = new vgCore::GpuManager;
		assert( m_pGpuManager!= NULL );
		m_pGpuManager->initialise();
	}

	vgKernel::OpenGLSupport::initialiseOpenGLExtension();
}

bool CWizardSheetDlg::initGLContext(void)
{
	GLuint PixelFormat;	

	static PIXELFORMATDESCRIPTOR pfd = { 
		sizeof(PIXELFORMATDESCRIPTOR),    // pfd结构的大小 
		1,                                // 版本号 
		PFD_DRAW_TO_WINDOW |              // 支持在窗口中绘图 
		PFD_SUPPORT_OPENGL |              // 支持 OpenGL 
		PFD_DOUBLEBUFFER,                 // 双缓存模式 
		PFD_TYPE_RGBA,                    // RGBA 颜色模式 
		24,                               // 24 位颜色深度 
		0, 0, 0, 0, 0, 0,                 // 忽略颜色位 
		1,                                // 没有非透明度缓存 
		0,                                // 忽略移位位 
		0,                                // 无累加缓存 
		0, 0, 0, 0,                       // 忽略累加位 
		32,                               // 32 位深度缓存     
		8,                                // 无模板缓存 //改动阴影
		0,                                // 无辅助缓存 
		PFD_MAIN_PLANE,                   // 主层 
		0,                                // 保留 
		0, 0, 0                           // 忽略层,可见性和损毁掩模 
	};

	HWND hWND = this->GetSafeHwnd();
	HDC hDC = ::GetDC(hWND);
	m_pDC = new CClientDC(this);
	// 选择合适的Device Context像素点格式
	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))		// Did Windows Find A Matching Pixel Format?
	{							
		::MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}


	// 设置新的Device Context像素点格式
	if(!SetPixelFormat(hDC,PixelFormat,&pfd))			// Are We Able To Set The Pixel Format?
	{
		::MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}
	// 根据当前的Device Context得到rending context
	if (!(this->m_hGLContext=wglCreateContext(hDC)))	// Are We Able To Get A Rendering Context?
	{
		//KillGLWindow();								// Reset The Display
		::MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}
	// 设置当前Device context 的rendering context
	if(!wglMakeCurrent(hDC,this->m_hGLContext))			// Try To Activate The Rendering Context
	{
		//KillGLWindow();								// Reset The Display
		::MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.5f,0.6f,0.8f,1.0f);					// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations


	return true;
}


bool CWizardSheetDlg::resetManager()
{
	vgSound::SoundManager::getSingleton().unloadData();
	vgMod::NodeManager::getSingleton().uninitBeforeOpenGLDestroy();

	return true;
}

void CWizardSheetDlg::releaseGLContext(void)
{
	if (this->m_hGLContext)										// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))							// Are We Able To Release The DC And RC Contexts?
		{
			::MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(this->m_hGLContext))				// Are We Able To Delete The RC?
		{
			::MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		this->m_hGLContext=NULL;								// Set RC To NULL
	}

	if (m_pDC)
		delete m_pDC;
}