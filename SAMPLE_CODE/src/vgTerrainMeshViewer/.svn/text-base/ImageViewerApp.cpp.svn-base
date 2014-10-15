/****************************************************************************
ImageViewerApp.cpp : Implementation file for the CImageViewerApp class
written by PJ Arends
pja@telus.net

For updates check http://www.codeproject.com/tools/imageviewer.asp

-----------------------------------------------------------------------------
This code is provided as is, with no warranty as to it's suitability or usefulness
in any application in which it may be used.

This code may be used in any way you desire. This file may be redistributed by any
means as long as it is not sold for profit, and providing that this notice and the
author's name are included. Any modifications not made by the original author should
be clearly marked as such to remove any confusion between the original version and
any other versions.

If any bugs are found and fixed, a note to the author explaining the problem and
fix would be nice.
-----------------------------------------------------------------------------
****************************************************************************/

#include <vgStableHeaders.h>
#include "ImageViewerApp.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "ImageViewerDoc.h"
#include "ImageViewerView.h"
#include "MyDocManager.h"
#include "IVDialog.h"
#include "MaxMemDialog.h"

#include "XHyperLink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageViewerApp

BEGIN_MESSAGE_MAP(CImageViewerApp, CWinApp)
    ON_COMMAND(ID_APP_ABOUT, &CImageViewerApp::OnAppAbout)
    // Standard file based document commands
    ON_COMMAND(ID_FILE_OPEN, &CImageViewerApp::OnFileOpen)
    ON_COMMAND(ID_FILE_PAUSE, &CImageViewerApp::OnFilePause)
    ON_UPDATE_COMMAND_UI(ID_FILE_PAUSE, &CImageViewerApp::OnUpdateFilePause)
    ON_COMMAND(ID_SETUP_MEMORY, &CImageViewerApp::OnSetupMemory)
END_MESSAGE_MAP()


// CImageViewerApp construction

CImageViewerApp::CImageViewerApp()
: MemoryEvent(TRUE, TRUE)
, PausedEvent(TRUE, TRUE)
, ModalDialogEvent(TRUE, TRUE)
, RecieverThread(NULL)
, MaximumMemoryUsage(1000000)       // approx 1GB
{
}


// The one and only CImageViewerApp object

CImageViewerApp theApp;

// CImageViewerApp initialization

BOOL CImageViewerApp::InitInstance()
{
    // Parse command line for standard shell commands, DDE, file open
    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);

    // Allow only one instance of this program at a time
    CreateMutex(NULL, FALSE, _T("{04482A69-54D7-4156-9846-D42A4F09F373}"));
    DWORD LastError = GetLastError();
    if (ERROR_ALREADY_EXISTS == LastError || ERROR_ACCESS_DENIED == LastError)
    {
        // Another instance running? Find it's main window
        HWND hOther = NULL;
        EnumWindows(Searcher, (LPARAM)&hOther);
        if (NULL != hOther)
        {
            // found, tell it which file to open
            if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileOpen)
            {
                COPYDATASTRUCT cds = {0};
                cds.dwData = 0x1FEB1965;
                cds.lpData = (LPVOID)(LPCTSTR)cmdInfo.m_strFileName;
                cds.cbData = (cmdInfo.m_strFileName.GetLength() + 1) * sizeof(TCHAR);

                SendMessageTimeout(hOther,
                                   WM_COPYDATA,
                                   (WPARAM)NULL,
                                   (LPARAM)&cds,
                                   SMTO_ABORTIFHUNG | SMTO_BLOCK,
                                   200,
                                   NULL);
            }
        }
        return FALSE;
    }

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

    SetRegistryKey(_T("PJ Arends"));

    // Change the profile name, by default it uses the AFX_IDS_APP_TITLE string
    free((void*)m_pszProfileName);
    m_pszProfileName = _tcsdup(_T("VRGIS Terrain Mesh Viewer"));

    LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)

    // Register the application's document templates.  Document templates
    //  serve as the connection between documents, frame windows and views
    CMultiDocTemplate* pDocTemplate;
    pDocTemplate = new CMultiDocTemplate(IDR_IMAGEVIEWERTYPE,
        RUNTIME_CLASS(CImageViewerDoc),
        RUNTIME_CLASS(CChildFrame), // custom MDI child frame
        RUNTIME_CLASS(CImageViewerView));
    if (!pDocTemplate)
        return FALSE;

    // use my own derived CDocManager class
    m_pDocManager = dynamic_cast<CDocManager *>(new CMyDocManager);
    AddDocTemplate(pDocTemplate);

    // create main MDI Frame window
    CMainFrame* pMainFrame = new CMainFrame;
    if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
    {
        delete pMainFrame;
        return FALSE;
    }
    m_pMainWnd = pMainFrame;

    if (ERROR_SUCCESS != GetObjectArray(_T("Settings"), _T("Maximum Memory Usage"), &MaximumMemoryUsage))
    {
        MaximumMemoryUsage = 1000000;
    }

    // call DragAcceptFiles only if there's a suffix
    //  In an MDI app, this should occur immediately after setting m_pMainWnd
    // Enable drag/drop open
    m_pMainWnd->DragAcceptFiles();

    // Enable DDE Execute open
    // EnableShellOpen();
    // RegisterShellFileTypes(TRUE);

    // Dispatch commands specified on the command line.  Will return FALSE if
    // app was launched with /RegServer, /Register, /Unregserver or /Unregister.

    // do not create an empty document
    // save the opening of a document file until after main frame window is fully shown
    if (cmdInfo.m_nShellCommand != CCommandLineInfo::FileNew &&
        cmdInfo.m_nShellCommand != CCommandLineInfo::FileOpen)
    {
        if (!ProcessShellCommand(cmdInfo))
            return FALSE;
    }

    // start the image reciever thread
    RecieverThread = dynamic_cast<CRecieverThread *>(AfxBeginThread(RUNTIME_CLASS(CRecieverThread)));
    ASSERT (NULL != RecieverThread);
    if (NULL == RecieverThread)
    {
        delete pMainFrame;
        return FALSE;
    }

    // The main window has been initialized, so show and update it
    pMainFrame->ShowWindow(m_nCmdShow);
    pMainFrame->UpdateWindow();

    // main frame window is up and running, now we can open any files on the command line
    if (CCommandLineInfo::FileOpen == cmdInfo.m_nShellCommand)
    {
        ModalDialogEvent.ResetEvent();
        ProcessShellCommand(cmdInfo);
        ModalDialogEvent.SetEvent();
    }

    return TRUE;
}



// CAboutDlg dialog used for App About

class CAboutDlg : public CIVDialog
{
public:
    CAboutDlg();

// Dialog Data
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    DECLARE_MESSAGE_MAP()
    CXHyperLink m_HyperLink;
};

CAboutDlg::CAboutDlg() : CIVDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CIVDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_LINK, m_HyperLink);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CIVDialog)
END_MESSAGE_MAP()


// App command to run the dialog
void CImageViewerApp::OnAppAbout()
{
    //CAboutDlg aboutDlg;
    //aboutDlg.DoModal();
}

// CImageViewerApp message handlers


int CImageViewerApp::ExitInstance()
{
    // Tell the image reciever thread to quit
    if (RecieverThread && RecieverThread->m_hThread)
    {
        RecieverThread->Quit();
        WaitForSingleObject(RecieverThread->m_hThread,
#ifdef _DEBUG
                            INFINITE);
#else
                            1000);
#endif
    }
    return CWinApp::ExitInstance();
}

BOOL CALLBACK CImageViewerApp::Searcher(HWND hWnd, LPARAM lp)
{
    // check if the window handle 'hWnd' is the window we are looking for
    DWORD Result = 0;
    LRESULT Ok = ::SendMessageTimeout(hWnd, 
                                      RWM_ARE_YOU_ME,
                                      0, 0, 
                                      SMTO_BLOCK | SMTO_ABORTIFHUNG,
                                      200,
                                      &Result);
    
    // SendMessageTimeout encountered an error, keep looking
    if (0 == Ok)
    {
        LRESULT Error = GetLastError();
        if (0 == Error)
        {
            TRACE(_T("CImageViewerApp::Searcher - SendMessageTimeout() timed out. HWND: 0x%08X\n"), hWnd);
        }
        else
        {
            TRACE(_T("CImageViewerApp::Searcher - SendMessageTimeout() encounter error: 0x%08X.  HWND: 0x%08X\n"), Error, hWnd);
        }

        return TRUE;
    }

    // Found it!
    if (RWM_ARE_YOU_ME == Result)
    {
        *(HWND*)lp = hWnd;
        return FALSE;
    }

    // Not found, try again
    return TRUE;
}

BOOL CImageViewerApp::IsIdleMessage(MSG* pMsg)
{
    // stop mouse movements and timers from kicking in
    // the OnIdle() handler
    if (pMsg->message == WM_TIMER ||
        pMsg->message == WM_NCMOUSEMOVE ||
        pMsg->message == WM_MOUSEMOVE)
    {
        return FALSE;
    }

    return CWinApp::IsIdleMessage(pMsg);
}

void CImageViewerApp::OnFileOpen()
{
    ModalDialogEvent.ResetEvent();
    CWinApp::OnFileOpen();
    ModalDialogEvent.SetEvent();
}

void CImageViewerApp::OnFilePause()
{
    if (WAIT_OBJECT_0 != WaitForSingleObject(PausedEvent, 0))
    {
        PausedEvent.SetEvent();
        m_pMainWnd->PostMessage(WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE, 0);
    }
    else
    {
        PausedEvent.ResetEvent();
        m_pMainWnd->PostMessage(WM_SETMESSAGESTRING, IDS_PAUSEDMESSAGE, 0);
    }
}

void CImageViewerApp::OnUpdateFilePause(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(WAIT_OBJECT_0 != WaitForSingleObject(PausedEvent, 0));
}

void CImageViewerApp::OnSetupMemory()
{
    CMaximumMemoryDialog dlg;
    if (IDOK == dlg.DoModal())
    {
        WriteObjectArray(_T("Settings"), _T("Maximum Memory Usage"), &MaximumMemoryUsage);
    }
}
