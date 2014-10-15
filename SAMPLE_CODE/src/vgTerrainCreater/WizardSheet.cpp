// WizardSheet.cpp : Defines the class behaviors for the application.
//

#include <vgStableHeaders.h>
#include "WizardSheet.h"
#include "WizardSheetDlg.h"

#include "vgWizardPropertySheet.h"

#include <vgTerritory/vgtDemArea.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWizardSheetApp

BEGIN_MESSAGE_MAP(CWizardSheetApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CWizardSheetApp construction

CWizardSheetApp::CWizardSheetApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CWizardSheetApp object

CWizardSheetApp theApp;


// CWizardSheetApp initialization

BOOL CWizardSheetApp::InitInstance()
{

	//////////////////////////////////////////////////////////////////////////

	//------------------------------------------
	// 测试
	//------------------------------------------
#if 0

	using namespace vgTerritory;

	DemArea area( "D:\\terrain_data\\67-00.dem" , "D:\\terrain_data\\67-00.bmp");


	bool ddd = area.readFileAndCheckValid();

	assert( ddd == true );


#endif

	//////////////////////////////////////////////////////////////////////////


	//CWinApp::InitInstance();
	AfxEnableControlContainer();

#if _MSC_VER < 1400
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif


	InitCommonControls();
	InitContextMenuManager ();
	InitShellManager ();


	CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPWinXPVisualManager));
	CBCGPButton::EnableWinXPTheme ();


	WizardPropertySheet wiz("地形生成向导");
	wiz.DoModal();

	BCGCBProCleanUp ();

	return FALSE;


	//// Standard initialization
	//// If you are not using these features and wish to reduce the size
	//// of your final executable, you should remove from the following
	//// the specific initialization routines you do not need
	//// Change the registry key under which our settings are stored
	//// TODO: You should modify this string to be something appropriate
	//// such as the name of your company or organization
	////SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	//CWizardSheetDlg dlg;
	//m_pMainWnd = &dlg;
	//INT_PTR nResponse = dlg.DoModal();
	//if (nResponse == IDOK)
	//{
	//	// TODO: Place code here to handle when the dialog is
	//	//  dismissed with OK
	//}
	//else if (nResponse == IDCANCEL)
	//{
	//	// TODO: Place code here to handle when the dialog is
	//	//  dismissed with Cancel
	//}

	//// Since the dialog has been closed, return FALSE so that we exit the
	////  application, rather than start the application's message pump.
	//return FALSE;
}
