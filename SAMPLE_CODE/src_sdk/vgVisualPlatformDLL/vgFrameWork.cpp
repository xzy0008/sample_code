// vgFrameWork.cpp : Defines the class behaviors for the application.
//

#include <vgStableHeaders.h>
#include "vgFrameWork.h"
#include "MainFrm.h"

#include "vgFrameWorkDoc.h"
#include "vgFrameWorkView.h"

#include "vgUIController/CGFILTYP.H"	//	CGCFileTypeAccess

#include <vgGlobal/vggSystemFacade.h>
#include <vgGlobal/vggSceneFileUtility.h>

#include <vgKernel/vgkPluginLoaderOnString.h>



#include <vgConf/vgcoExeConfigRegProxy.h>
#include <vgConf/vgcoExeConfig.h>
#include <vgConf/vgcoProjectConfig.h>
#include <vgConf/vgcoProjectConfigRegProxy.h>

#include <vgDeprecatedMFCDLL/AutoLoadDialog.h>
#include "vgAutoLoadThread.h"

#include <vgKernel/vgkPluginManager.h>
#include "vgChannel/vgcDefinition.h"

#define VGDLL_EXECONF		"ExeDllConfig"
#define VGDLL_EXECONF_TITLE "ExeDllTitle"
#define VGDLL_EXECONF_NAMES	"ExeDllNames"
#define VGDLL_EXECONF_ENABLEPACKAGE	"ExeDllEnablePackage"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CvgFrameWorkApp

BEGIN_MESSAGE_MAP(CvgFrameWorkApp, CWinApp)
//	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CvgFrameWorkApp construction

CvgFrameWorkApp::CvgFrameWorkApp() :
	CBCGPWorkspace (TRUE /* m_bResourceSmartUpdate */)
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	//std::locale::global(std::locale("chs"));

	m_hinstBCGCBRes = NULL;

	_enablePackage = true;
}


// The one and only CvgFrameWorkApp object

CvgFrameWorkApp theApp;


// CvgFrameWorkApp initialization

BOOL CvgFrameWorkApp::InitInstance()
{

#if VGK_LANG_CHS
	m_hinstBCGCBRes = LoadLibrary (_T("vgUserInterfaceResCHS.dll"));    // *** - language
	BCGCBProSetResourceHandle (m_hinstBCGCBRes);
#endif

	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	//_CrtSetBreakAlloc(5866); 
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(NIDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("VRGIS"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)

	SetRegistryBase (_T("Settings")); 

	// 清除注册表信息,release时去掉
	this->CleanState(); 
	// Initialize all Managers for usage. They are automatically constructed
	// if not yet present
	// InitContextMenuManager();
	InitKeyboardManager();

	// TODO: Remove this if you don't want extended tooltips:
	InitTooltipManager();

	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;

	theApp.GetTooltipManager ()->SetTooltipParams (
		BCGP_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS (CBCGPToolTipCtrl),
		&params);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		NIDR_MAINFRAME,
		RUNTIME_CLASS(CvgFrameWorkDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CvgFrameWorkView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	//----------progress position------------------//
	CUILoadThread *thread = 
		(CUILoadThread*)AfxBeginThread(RUNTIME_CLASS(CUILoadThread));                //启动用户界面线程	
	Sleep(50);
	//---------------------------------------------//

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand


		
		//---写入注册表------------------------
		CGCFileTypeAccess TheFTA;

		TCHAR	szProgPath[MAX_PATH * 2];
		::GetModuleFileName(NULL, szProgPath, sizeof(szProgPath)/sizeof(TCHAR));

		CString csTempText;

		//TheFTA.SetExtension("fc");
		TheFTA.SetExtension("vg");

		// just pass file path in quotes on command line
		csTempText  = szProgPath;
		csTempText += " \"%1\"";
		TheFTA.SetShellOpenCommand(csTempText);
		TheFTA.SetDocumentShellOpenCommand(csTempText);

		//TheFTA.SetDocumentClassName("CGFileType.Document");
		TheFTA.SetDocumentClassName("vgFrameWork.Document");

		// use first icon in program
		csTempText  = szProgPath;
		csTempText += ",0";
		TheFTA.SetDocumentDefaultIcon(csTempText);

		//::MessageBox(NULL, csTempText, "Info ", MB_OK);

		TheFTA.RegSetAllInfo();

		// The one and only window has been initialized, so show and update it

#if 0//_DEBUG
		vgKernel::SystemUtility::showModelDialog( "progress position" );
#endif
		//----------progress position------------------//
		m_pMainWnd->ShowWindow(SW_HIDE);
		m_pMainWnd->SetForegroundWindow();
 		m_pMainWnd->UpdateWindow();
		//---------------------------------------------//

		String falseDLLs = vgKernel::PluginLoaderOnString::load();
		if ( !falseDLLs.empty() )
		{
#if VGK_LANG_CHS
			falseDLLs += "无法导入！";
			falseDLLs += "\n出错原因:可能是因为该DLL所依赖的底层DLL无法找到，请核查！";

#else
			falseDLLs += "load failed！";
#endif
			//AfxMessageBox( falseDLLs.c_str() );
			vgKernel::SystemUtility::showModelDialog( falseDLLs );
		}
		

#if 0//_DEBUG
		vgKernel::SystemUtility::showModelDialog( "finish to load dlls" );
#endif

		_enablePackage = vgKernel::PluginLoaderOnString::getEnablePack();

		CWnd* pWnd = AfxGetApp()->m_pMainWnd;
		assert( pWnd != NULL);
		pWnd->SetWindowText( vgKernel::PluginLoaderOnString::getAppTitle().c_str() );
		
		// 刷新界面
		RECT rect;
		AfxGetApp()->m_pMainWnd->GetWindowRect( &rect );
		InvalidateRect( NULL , &rect , TRUE );

		//-----自动加载VG文件----------------------------
		String iniDataPath = vgKernel::SystemUtility::getCurrentProcessPath() + "data.ini";
		std::ifstream iniDataFile;
		iniDataFile.open(iniDataPath.c_str());
		if (!iniDataFile.fail())
		{
			char aa[30];
			iniDataFile.getline(aa, 30, '\n');
			String autoLoadFilePath = vgKernel::SystemUtility::getCurrentProcessPath() + aa;
			iniDataFile.close();

#if 0//_DEBUG			
			vgKernel::SystemUtility::showModelDialog("read data.ini vg!");
#endif
			vgGlobal::SceneFileUtility::setUpdateTime(1);

			vgGlobal::SceneFileUtility::openScene(autoLoadFilePath);
		}

		// 加到InitInstance最后	
		bool bFullScreen = false;
		bool bStartChannel = false;
		bool bSoftBlend = false;
		int chanNum = -2;

		if( m_lpCmdLine && m_lpCmdLine[0] )
		{
			TRACE(".Command Line = \n");
			TRACE(".'");
			TRACE(m_lpCmdLine);
			TRACE("'\n");
			//AfxMessageBox(m_lpCmdLine, MB_OK);
			CString recvParam;
			String  strFilePath;

			for (int i=0;i<__argc;i++)
			{
				recvParam.Format("%s", __argv[i]);
				if (recvParam == "-fs")			//是否打开全屏
				{
					bFullScreen = true;
				}
				else if ( recvParam == "-fs\n")
				{
					bFullScreen = true;
				}
				else if (recvParam == "-sc")	//是否打开多通道
				{
					bStartChannel = true;
				}
				else if (recvParam == "-sc\n")
				{
					bStartChannel = true;
				}
				else if (recvParam == "-baa")	// 是否开启软融合(边缘融合和几何校正)
				{
					bSoftBlend = true;
				}
				else if (recvParam == "-baa\n")
				{
					bSoftBlend = true;
				}
				else if ( recvParam == "-0" || recvParam == "-0\n")
				{
					chanNum = 0;
				}
				else if ( recvParam == "-1" || recvParam == "-1\n")
				{
					chanNum = -1;
				}
				else if ( recvParam.Right(3) == "exe")	//第一个参数是可执行文件的完整路径
				{ 
					//AfxMessageBox(recvParam);
				}
				else if ( recvParam.Right(3) == ".vg")	//第二个参数应该输入vg文件的路径
				{
					strFilePath = recvParam.GetBuffer();
					
				}
				//AfxMessageBox(recvParam);

			}

			//			vgCore::MFCApplication::getSingleton().readFilePath = String(m_lpCmdLine);
			//AfxMessageBox("Hello World!2033");
			//String  strFilePath(m_lpCmdLine);
			//strFilePath.erase(strFilePath.length()-1, std::string::npos);
			//strFilePath.erase(0, 1);

			//String  strFilePath= "E:\\TEMP\\data\\VRGIS应用项目\\VRGIS_春晖乳业循环经济产业园虚拟展示系统8-21（已升级，适用于插件版平台）\\春晖乳业循环经济产业园虚拟展示系统8-21.vg";
#if 0//_DEBUG
			vgKernel::SystemUtility::showModelDialog("double clicked vg!");
#endif
			vgGlobal::SceneFileUtility::setUpdateTime(1);

			if ( !(strFilePath.empty()))
			{
				vgGlobal::SceneFileUtility::openScene( strFilePath );
			}
			
			if ( bFullScreen )
			{
				CMainFrame *m_pFrame =(CMainFrame *)(this->m_pMainWnd);
				m_pFrame->OnFullScreen();
			}

			if ( bStartChannel )
			{
				//AfxMessageBox("StartChannel!");
				using namespace vgKernel;
		 		Plugin* plg = PluginManager::getSingleton().getPluginRef( VGCHAN_DLL_NAME );
		 
		 		if ( plg == NULL )
		 		{
					AfxMessageBox("多通道动态库未加载!");
					//return TRUE;
		 		}

				VGK_DLL_DECLARE_CLASSFUNC( plg, ChannelManager, SetChannelFromFile, channel_func2 );
				VGK_DLL_DECLARE_CLASSFUNC( plg, ChannelManager, startChannel, channel_func );
				VGK_DLL_DECLARE_CLASSFUNC( plg, ChannelManager, setBlendAndAdjustEnable, chan_func_BlendAdj );
				VGK_DLL_DECLARE_CLASSFUNC( plg, ChannelManager, setEdgeBlendEnable, chan_func_EdgeBlend );

				if ( channel_func2 != NULL )
				{
					(*channel_func2)();
				}
				if ( channel_func(chanNum) != NULL)
				{
					(*channel_func)(chanNum);
				}
				//assert( channel_func(-1) != NULL);

				if ( bSoftBlend )	// 开启软融合为True
				{
					if ( chan_func_BlendAdj != NULL )
					{
						(*chan_func_BlendAdj)(true);	// 开启几何校正
					}
					if ( chan_func_EdgeBlend != NULL )
					{
						(*chan_func_EdgeBlend)(true);	// 开启边缘融合
					}
				}
			}
		}

	//----------progress position------------------//
	thread->PostThreadMessage(WM_DESTROY, 0, 0);

	WaitForSingleObject(thread->m_hThread ,3000);

	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->SetForegroundWindow(); 
	m_pMainWnd->UpdateWindow();
	//---------------------------------------------//

	return TRUE;
}

// CvgFrameWorkApp message handlers

int CvgFrameWorkApp::ExitInstance() 
{
	BCGCBProCleanUp();

#if VGK_LANG_CHS
	if ( m_hinstBCGCBRes != NULL )
	{	
		FreeLibrary (m_hinstBCGCBRes);
	}
#endif

	return CWinApp::ExitInstance();
}

// CAboutDlg dialog used for App About

//class CAboutDlg : public CDialog
//{
//public:
//	CAboutDlg();
//
//// Dialog Data
//	enum { IDD = NIDD_ABOUTBOX };
//	CBCGPURLLinkButton m_btnURL;
//
//protected:
//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
//
//// Implementation
//protected:
//	DECLARE_MESSAGE_MAP()
//};
//
//CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
//{
//}
//
//void CAboutDlg::DoDataExchange(CDataExchange* pDX)
//{
//	CDialog::DoDataExchange(pDX);
//	DDX_Control(pDX, NIDC_COMPANY_URL, m_btnURL);
//}
//
//BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//END_MESSAGE_MAP()

// App command to run the dialog
//void CvgFrameWorkApp::OnAppAbout()
//{
//	CAboutDlg aboutDlg;
//	aboutDlg.DoModal();
//}


// CvgFrameWorkApp message handlers


void CvgFrameWorkApp::PreLoadState ()
{

	GetContextMenuManager()->AddMenu (_T("My menu"), NIDR_CONTEXT_MENU);

	// TODO: add another context menus here
}

