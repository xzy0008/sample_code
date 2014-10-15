// vgFrameWork.cpp : Defines the class behaviors for the application.
//

#include <vgStableHeaders.h>
#include "vgFrameWork.h"
#include "MainFrm.h"

#include "vgFrameWorkDoc.h"
#include "vgFrameWorkView.h"

#include "CGFILTYP.H"	//	CGCFileTypeAccess
#include <vgMFCApplication.h>
#include <vgGlobal/vggSystemFacade.h>


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
	SetRegistryKey(_T("BCGP AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)

	SetRegistryBase (_T("Settings")); 

	// 清除注册表信息,release时去掉
	this->CleanState(); 
	// Initialize all Managers for usage. They are automatically constructed
	// if not yet present
	InitContextMenuManager();
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



	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand

	// 加到InitInstance最后	
		if( m_lpCmdLine && m_lpCmdLine[0] ){
			TRACE(".Command Line = \n");
			TRACE(".'");
			TRACE(m_lpCmdLine);
			TRACE("'\n");
			//AfxMessageBox(m_lpCmdLine, MB_OK);

			vgCore::MFCApplication::getSingleton().readFilePath = String(m_lpCmdLine);
			//AfxMessageBox("Hello World!2033");
			String  strFilePath(m_lpCmdLine);
			strFilePath.erase(strFilePath.length()-1, std::string::npos);
			strFilePath.erase(0, 1);

			vgGlobal::SystemFacade::openSceneFile( strFilePath );
			//((CvgFrameWorkView*)m_pMainWnd)->OnSceneRead(strFilePath);
		}

		

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
		m_pMainWnd->ShowWindow(SW_SHOW);
		m_pMainWnd->UpdateWindow();




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

