// FrameWork.cpp : Defines the class behaviors for the application.
//

#include <vgStableHeaders.h>
#include "FrameWork.h"

#include "MainFrm.h"
#include "FrameWorkDoc.h"
#include "FrameWorkView.h"
#include <vgSplash.h>
#include <SkinPlusPlus.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFrameWorkApp

BEGIN_MESSAGE_MAP(CFrameWorkApp, CWinApp)
	//{{AFX_MSG_MAP(CFrameWorkApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrameWorkApp construction

CFrameWorkApp::CFrameWorkApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	//setlocale( LC_ALL, "CHS" );

	std::locale::global(std::locale("CHS"));

}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFrameWorkApp object

CFrameWorkApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CFrameWorkApp initialization

BOOL CFrameWorkApp::InitInstance()
{



	CSaveVgimgDlg dlg;
	dlg.DoModal();


	return true;



	// CG: The following block was added by the Splash Screen component.
\
	{
\
		CCommandLineInfo cmdInfo;
\
		ParseCommandLine(cmdInfo);
\

\
		CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);
\
	}
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

#if VG_EXPLORER_AUTO_LOAD
	//void GetPath(TCHAR*   pPath)   
	//{   
		TCHAR   szBuf[200];   

		GetModuleFileName(NULL,szBuf,sizeof(szBuf));     

		TCHAR*   p   =   szBuf;   
		while(_tcschr(p,'\\'))     
		{   
			p   =   _tcschr(p,'\\');   
			p++;   
		}   
		*p   =   '\0';   

	//	_tcscpy(pPath,szBuf);   
	//}

	string ddd = szBuf;

	ddd.erase( ddd.find_last_of("\\/") , std::string::npos );


	ddd += "\\SoftCrystal.ssk";

	InitializeSkin(const_cast<char*>(ddd.c_str()));

	//InitializeSkin("SoftCrystal.ssk");

#endif
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CFrameWorkDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CFrameWorkView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// The one and only window has been initialized, so show and update it.
#if !VG_EXPLORER_AUTO_LOAD
	m_pMainWnd->ShowWindow(SW_MAXIMIZE);//(SW_SHOW);
#endif
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About



CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CFrameWorkApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CFrameWorkApp message handlers


BOOL CFrameWorkApp::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following lines were added by the Splash Screen component.
	if (CSplashWnd::PreTranslateAppMessage(pMsg))
		return TRUE;

	return CWinApp::PreTranslateMessage(pMsg);
}
