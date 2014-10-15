/****************************************************************************
Reciever.cpp : Implementation file for the CRecieverThread and CRecieverWindow classes
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
#include "Reciever.h"
#include "ImageViewerApp.h"

// These same messages are also registered in the file IVDllWindow.cpp, part of the Viewer Library project

const UINT Looking_for_viewer_app = RegisterWindowMessage(_T("LOOKING_FOR_VIEWER_APP_{FD4EA0C0-ECFC-11d5-B625-ED551C514422}"));
const UINT Viewer_app_window = RegisterWindowMessage(_T("VIEWER_APP_WINDOW_{FD4EA0C0-ECFC-11d5-B625-ED551C514422}"));

// CRecieverThread

IMPLEMENT_DYNCREATE(CRecieverThread, CWinThread)

CRecieverThread::CRecieverThread()
{
}

CRecieverThread::~CRecieverThread()
{
}

BOOL CRecieverThread::InitInstance()
{
    CRecieverWindow *pWnd = new CRecieverWindow;

    if (pWnd->Create())
    {
        m_pMainWnd = pWnd;
        PostMessage(HWND_BROADCAST,
                    Viewer_app_window,
                    0xFEB11965,
                    reinterpret_cast<LPARAM>(m_pMainWnd->GetSafeHwnd()));
        return TRUE;
    }

    return FALSE;
}

int CRecieverThread::ExitInstance()
{
    PostMessage(HWND_BROADCAST,
                Viewer_app_window,
                0xFEB11965,
                NULL);

    return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CRecieverThread, CWinThread)
END_MESSAGE_MAP()


// CRecieverThread message handlers

void CRecieverThread::Quit()
{
    // closing the thread's main window will terminate the thread
    m_pMainWnd->PostMessage(WM_CLOSE);
}

// CRecieverWindow

IMPLEMENT_DYNAMIC(CRecieverWindow, CWnd)

CRecieverWindow::CRecieverWindow()
{
}

CRecieverWindow::~CRecieverWindow()
{
}


BEGIN_MESSAGE_MAP(CRecieverWindow, CWnd)
    ON_REGISTERED_MESSAGE(Looking_for_viewer_app, &CRecieverWindow::OnLookingForViewerApp)
    ON_WM_COPYDATA()
END_MESSAGE_MAP()

// CRecieverWindow message handlers

BOOL CRecieverWindow::Create()
{
    BOOL ret = CreateEx(0,
                        AfxRegisterWndClass(0),
                        _T("Image Viewer Hidden Reciever Window"),
                        WS_POPUP,
                        0, 0, 0, 0,
                        NULL,
                        0,
                        NULL);

    return ret;
}

LRESULT CRecieverWindow::OnLookingForViewerApp(WPARAM wp, LPARAM lp)
{
    UNREFERENCED_PARAMETER(lp);

    if (0xFEB11965 == wp)
    {
        return Looking_for_viewer_app;
    }

    return 0;
}

BOOL CRecieverWindow::OnCopyData(CWnd *, COPYDATASTRUCT *pCopyDataStruct)
{
    if (WAIT_OBJECT_0 != WaitForSingleObject(theApp.PausedEvent, 0))
    {
        TRACE(_T("Viewer Application - CRecieverWindow::OnCopyData: Viewer app is paused\n"));
        return ERROR_SHARING_PAUSED;
    }

    if (WAIT_OBJECT_0 != WaitForSingleObject(theApp.MemoryEvent, 0))
    {
        TRACE(_T("Viewer Application - CRecieverWindow::OnCopyData: Out of Memory!\n"));
        return ERROR_NOT_ENOUGH_MEMORY;
    }

    if (0xFEB11965 != pCopyDataStruct->dwData)
    {
        TRACE(_T("Viewer Application - CRecieverWindow::OnCopyData: dwData != 0xFEB11965\n"));
        return ERROR_INVALID_DATA;
    }

    if (pCopyDataStruct->cbData < sizeof(BITMAPINFO))
    {
        TRACE(_T("Viewer Application - CRecieverWindow::OnCopyData: cbData too small\n"));
        return ERROR_INVALID_DATA;
    }

    if (NULL == pCopyDataStruct->lpData)
    {
        TRACE(_T("Viewer Application - CRecieverWindow::OnCopyData: lpData is NULL\n"));
        return ERROR_INVALID_DATA;
    }

    CImageData DataBuffer;
    if (!DataBuffer.CopyData(pCopyDataStruct->cbData, reinterpret_cast<LPBYTE>(pCopyDataStruct->lpData)))
    {
        TRACE(_T("Viewer Application - CRecieverWindow::OnCopyData: Failed to copy the data\n"));
        return ERROR_FUNCTION_FAILED;
    }

    CSingleLock SingleLock(&theApp.QueueSection, TRUE);
    theApp.InputQueue.push(DataBuffer);

    return ERROR_SUCCESS;
}

void CRecieverWindow::PostNcDestroy()
{
    delete this;
}
