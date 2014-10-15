/****************************************************************************
MainFrm.cpp : Implementation file for the CMainFrame class
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
#include "ImageViewerView.h"

#include <set>

#define INPUTQUEUEREADERTIMER 0xFEB11965

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
    ON_WM_ACTIVATE()
    ON_WM_COPYDATA()
    ON_WM_CREATE()
    ON_WM_DESTROY()
    ON_WM_TIMER()

    ON_MESSAGE(WM_SETMESSAGESTRING, &CMainFrame::OnSetMessageString)
    ON_MESSAGE(WMU_DOCUMENTCLOSING, &CMainFrame::OnDocumentClosing)
    ON_MESSAGE(WMU_GETBGCOLOUR, &CMainFrame::OnGetBGColour)
    ON_MESSAGE(WMU_GETDISPLAYLOCK, &CMainFrame::OnGetDisplayLock)
    ON_MESSAGE(WMU_UPDATETOOLTIP, &CMainFrame::OnUpdateTooltip)
    ON_MESSAGE(WMU_SETPROPERTIES, &CMainFrame::OnSetProperties)
    ON_REGISTERED_MESSAGE(RWM_ARE_YOU_ME, &CMainFrame::OnAreYouMe)

    ON_COMMAND(ID_VIEW_BACKGROUND_COLOUR, &CMainFrame::OnViewBackgroundColour)

    ON_COMMAND(ID_VIEW_HEXADECIMAL_TOOLTIPS, &CMainFrame::OnViewHexadecimalTooltips)
    ON_UPDATE_COMMAND_UI(ID_VIEW_HEXADECIMAL_TOOLTIPS, &CMainFrame::OnUpdateViewHexadecimalTooltips)

    ON_COMMAND(ID_VIEW_DISPLAY_LOCK, &CMainFrame::OnViewDisplayLock)
    ON_UPDATE_COMMAND_UI(ID_VIEW_DISPLAY_LOCK, &CMainFrame::OnUpdateViewDisplayLock)

    ON_COMMAND(ID_VIEW_ON_TOP, &CMainFrame::OnViewOnTop)
    ON_UPDATE_COMMAND_UI(ID_VIEW_ON_TOP, &CMainFrame::OnUpdateViewOnTop)

    ON_COMMAND(ID_IMAGE_PROPERTIES, &CMainFrame::OnImageProperties)
    ON_UPDATE_COMMAND_UI(ID_IMAGE_PROPERTIES, &CMainFrame::OnUpdateImageProperties)

    ON_UPDATE_COMMAND_UI(ID_INDICATOR_MEM, &CMainFrame::OnUpdateIndicatorMem)

    ON_COMMAND(ID_FILE_CLOSEALL, &CMainFrame::OnFileCloseAll)
    ON_COMMAND(ID_FILE_CLOSEALLEXCEPTACTIVE, &CMainFrame::OnFileCloseAllExceptActive)
    ON_COMMAND(ID_FILE_CLOSEACTIVE, &CMainFrame::OnFileCloseActive)
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
: HexTooltip(false)
, DisplayLock(false)
{
    BackgroundColour = RGB(192, 192, 192);                                               // default colour
    theApp.GetObjectArray(_T("Settings"), _T("Background Colour"), &BackgroundColour);   // get saved colour, if any
    HexTooltip = theApp.GetProfileInt(_T("Settings"), _T("Hex Tooltips"), 0) != 0;
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
        | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
        !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
    {
        TRACE0("Failed to create toolbar\n");
        return -1;      // fail to create
    }

    if (!m_wndStatusBar.Create(this))
    {
        TRACE0("Failed to create status bar\n");
        return -1;      // fail to create
    }

    m_wndToolBar.LoadTrueColorToolBar(32, IDB_COLOURTOOLBAR, 0, IDB_GRAYTOOLBAR);

    if (theApp.GetProfileInt(_T("Settings"), _T("Always on Top"), 0) != 0)
    {
        SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }

    // move the main window to where it was the last time the app was run
    WINDOWPLACEMENT WindowPlacement = {0};
    if (ERROR_SUCCESS == theApp.GetObjectArray(_T("Settings"), _T("Main Window Placement"), &WindowPlacement))
    {
        // bug: Window looses restored settings when it was closed in minimized or maximized state
        // fix: http://support.microsoft.com/kb/171375/en-us
        // will cause window to flash at restored size before switching to either maximized or minimized size
        UINT ShowCommand = WindowPlacement.showCmd;
        if (ShowCommand == SW_SHOWMINIMIZED || ShowCommand == SW_SHOWMAXIMIZED)
        {
            WindowPlacement.showCmd = SW_RESTORE;
        }

        SetWindowPlacement(&WindowPlacement);

        if (ShowCommand == SW_SHOWMINIMIZED || ShowCommand == SW_SHOWMAXIMIZED)
        {
            PostMessage(WM_SYSCOMMAND, ShowCommand == SW_SHOWMINIMIZED ? SC_MINIMIZE : SC_MAXIMIZE, 0);
        }
    }

    // Create and setup the tooltip
    ColourTooltip.Create(this);
    ColourTooltip.SetHex(HexTooltip);

    // create the image properties dialog
    PropertiesDialog.Create(IDD_PROPERTIES, this);

    // start the image queue reader timer
    SetTimer(INPUTQUEUEREADERTIMER, USER_TIMER_MINIMUM, NULL);

#ifdef DEBUG
    CString Text;
    GetWindowText(Text);
    Text += _T(" - DEBUG");
    SetWindowText(Text);
#endif

    return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.style &= ~FWS_ADDTOTITLE;
    if( !CMDIFrameWnd::PreCreateWindow(cs) )
        return FALSE;
    return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
    CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
    CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers


void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
    if (INPUTQUEUEREADERTIMER == nIDEvent && !theApp.InputQueue.empty())
    {
        CSingleLock SingleLock(&theApp.QueueSection, FALSE);
        CImageData ImageData;
        int counter = 0;
        DWORD ID = 0;
        std::set<DWORD> UsedIDs;

        // process at most only 50 images at a time in order to keep the app responsive
        while (!theApp.InputQueue.empty() && ++counter < 50)
        {
            if (SingleLock.Lock())
            {
                // get the next image from the queue
                ImageData = theApp.InputQueue.front();
                theApp.InputQueue.pop();
                SingleLock.Unlock();
            }

            ID = ImageData.GetProcessID();
            if (ID != 0)
            {
                IDDocMap::iterator it = IDDocs.find(ID);
                if (it == IDDocs.end())
                {
                    // Create a document and view for this new process
                    POSITION pos = theApp.GetFirstDocTemplatePosition();
                    CDocTemplate *pTemplate = theApp.GetNextDocTemplate(pos);

                    // if the display lock is on we save the current child frame so we can reactivate it later
                    CFrameWnd *pActiveFrame = NULL;
                    if (DisplayLock)
                    {
                        pActiveFrame = GetActiveFrame();
                    }

                    CImageViewerDoc *pDoc = dynamic_cast<CImageViewerDoc *>(pTemplate->OpenDocumentFile(NULL));

                    if (DisplayLock && NULL != pActiveFrame)
                    {
                        pActiveFrame->ActivateFrame();
                    }

                    if (NULL == pDoc)
                    {
                        // OpenDocumentFile failed, skip this image and go on to the next one
                        continue;
                    }

                    IDDocs[ID] = pDoc;
                    pDoc->SetCaption(ID);
                    if (DisplayLock)
                    {
                        // short circuit loop to make sure the first image recieved is displayed
                        counter = 50;
                    }
                }

                IDDocs[ID]->AddImageData(ImageData);
                UsedIDs.insert(ID);
            }
        }

        if (!UsedIDs.empty())
        {
            for (std::set<DWORD>::iterator it = UsedIDs.begin(); it != UsedIDs.end(); ++it)
            {
                // update the views of the documents that got new images
                IDDocs[*it]->UpdateAllViews(NULL, 0xfeb1, NULL);
            }
            theApp.OnIdle(-1);  // force the toolbar to update
        }
    }
}

LRESULT CMainFrame::OnDocumentClosing(WPARAM ID, LPARAM)
{
    // When a document is closed, it sends a WMU_DOCUMENTCLOSING message
    // to the mainframe so the mainframe can remove the document ID from
    // its map of active documents. See CImageViewerDoc::OnCloseDocument()
    return IDDocs.erase(static_cast<DWORD>(ID));
}

void CMainFrame::OnViewBackgroundColour()
{
    theApp.ModalDialogEvent.ResetEvent();

    COLORREF CustomColours[16] = {0};
    UINT ColourCount = _countof(CustomColours);
    theApp.GetObjectArray(_T("Settings"), _T("Custom Colours"), CustomColours, &ColourCount);
    for (UINT i = ColourCount; i < _countof(CustomColours); ++i)
    {
        CustomColours[i] = GetSysColor(COLOR_WINDOW);
    }

    CHOOSECOLOR cc = {0};
    cc.lStructSize = sizeof(CHOOSECOLOR);
    cc.hwndOwner = m_hWnd;
    cc.rgbResult = BackgroundColour;
    cc.lpCustColors = CustomColours;
    cc.Flags = CC_ANYCOLOR | CC_RGBINIT | CC_SOLIDCOLOR;

    if (ChooseColor(&cc) != 0)
    {
        BackgroundColour = cc.rgbResult;
        theApp.WriteObjectArray(_T("Settings"), _T("Background Colour"), &BackgroundColour);
        theApp.WriteObjectArray(_T("Settings"), _T("Custom Colours"), CustomColours, _countof(CustomColours));
    }

    POSITION pos = theApp.GetFirstDocTemplatePosition();
    CDocTemplate *pDocTemplate = theApp.GetNextDocTemplate(pos);
    pos = pDocTemplate->GetFirstDocPosition();
    while (NULL != pos)
    {
        CDocument *pDoc = pDocTemplate->GetNextDoc(pos);
        pDoc->UpdateAllViews(NULL);
    }

    theApp.ModalDialogEvent.SetEvent();
}

void CMainFrame::OnViewHexadecimalTooltips()
{
    HexTooltip = !HexTooltip;
    ColourTooltip.SetHex(HexTooltip);
}

void CMainFrame::OnUpdateViewHexadecimalTooltips(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(HexTooltip ? BST_CHECKED : BST_UNCHECKED);
}

void CMainFrame::OnViewDisplayLock()
{
    DisplayLock = !DisplayLock;
}

void CMainFrame::OnUpdateViewDisplayLock(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(DisplayLock ? BST_CHECKED : BST_UNCHECKED);
}

LRESULT CMainFrame::OnGetBGColour(WPARAM, LPARAM)
{
    return static_cast<LRESULT>(BackgroundColour);
}

LRESULT CMainFrame::OnGetDisplayLock(WPARAM, LPARAM)
{
    return static_cast<LRESULT>(DisplayLock);
}

LRESULT CMainFrame::OnSetProperties(WPARAM wp, LPARAM lp)
{
    if (NULL != wp && NULL != lp && IsWindow(PropertiesDialog))
    {
        CMDIChildWnd *pFrame = reinterpret_cast<CMDIChildWnd *>(wp);
        if (MDIGetActive() == pFrame)
        {
            return PropertiesDialog.SendMessage(WMU_SETPROPERTIES, wp, lp);
        }
    }

    return 0;
}

void CMainFrame::OnDestroy()
{
    CMDIFrameWnd::OnDestroy();

    KillTimer(INPUTQUEUEREADERTIMER);

    WINDOWPLACEMENT WindowPlacement = {0};
    WindowPlacement.length = sizeof(WINDOWPLACEMENT);
    GetWindowPlacement(&WindowPlacement);
    theApp.WriteObjectArray(_T("Settings"), _T("Main Window Placement"), &WindowPlacement);
    theApp.WriteProfileInt(_T("Settings"), _T("Hex Tooltips"), HexTooltip);
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
    if (CMDIFrameWnd::OnCreateClient(lpcs, pContext))
    {
        // subclass the default MDIClient window with our own class
        MDIClient.SubclassWindow(m_hWndMDIClient);
        return TRUE;
    }

    return FALSE;
}

void CMainFrame::OnViewOnTop()
{
    bool OnTop = WS_EX_TOPMOST == (GetExStyle() & WS_EX_TOPMOST);
    theApp.WriteProfileInt(_T("Settings"), _T("Always on Top"), !OnTop);

    if (OnTop)
    {
        SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
    }
    else
    {
        SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
    }
}

void CMainFrame::OnUpdateViewOnTop(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(WS_EX_TOPMOST == (GetExStyle() & WS_EX_TOPMOST) ? BST_CHECKED : BST_UNCHECKED);
}

void CMainFrame::OnImageProperties()
{
    if (this != GetActiveFrame() && IsWindow(PropertiesDialog))
    {
        PropertiesDialog.ShowWindow(PropertiesDialog.IsWindowVisible() ? SW_HIDE : SW_SHOW);
        GetActiveFrame()->GetActiveView()->SetFocus();
    }
}

void CMainFrame::OnUpdateImageProperties(CCmdUI *pCmdUI)
{
    if (this == GetActiveFrame() || !IsWindow(PropertiesDialog))
    {
        pCmdUI->Enable(FALSE);
        pCmdUI->SetCheck(BST_UNCHECKED);

        if (IsWindow(PropertiesDialog) && PropertiesDialog.IsWindowVisible())
        {
            PropertiesDialog.ShowWindow(SW_HIDE);
        }
    }
    else
    {
        pCmdUI->Enable(TRUE);
        pCmdUI->SetCheck(PropertiesDialog.IsWindowVisible() ? BST_CHECKED : BST_UNCHECKED);
    }
}

void CMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
    CMDIFrameWnd::OnActivate(nState, pWndOther, bMinimized);

    if (IsWindow(ColourTooltip))
    {
        // the tooltip is active only when this app has the input focus
        ColourTooltip.Activate(nState != WA_INACTIVE);
    }
}

void CMainFrame::OnUpdateIndicatorMem(CCmdUI *pCmdUI)
{
    // Update the memory usage indicator on the status bar.
    // See CMainStatusBar::DrawItem()
    size_t mem = CImageData::GetMemUsage() / 1024;
    pCmdUI->SetText(reinterpret_cast<LPCTSTR>(&mem));
}

LRESULT CMainFrame::OnUpdateTooltip(WPARAM, LPARAM)
{
    ColourTooltip.Update();

    return 0;
}

// Single Instance message handlers.
//
// When the Image Viewer app starts it uses a mutex to ensure only one
// instance can run (see CImageViewerApp::OnInitInstance()). If another
// instance is running it sequentially sends out a RWM_ARE_YOU_ME message
// to all the top level windows on the system looking for the other
// instance. The first one that returns with RWM_ARE_YOU_ME is assumed
// to be the existing instance. The existing instance can then activate itself.
// If the new instance was suppose to open a file, it will send a
// WM_COPYDATA message to the existing instance with the file name so
// that the existing instance can open it instead.

LRESULT CMainFrame::OnAreYouMe(WPARAM, LPARAM)
{
    if (IsIconic())
    {
        ShowWindow(SW_RESTORE);
    }

    SetForegroundWindow();

    return RWM_ARE_YOU_ME;
}

BOOL CMainFrame::OnCopyData(CWnd* /*pWnd*/, COPYDATASTRUCT* pCopyDataStruct)
{
    BOOL ret = FALSE;

    if (pCopyDataStruct->dwData == 0x1FEB1965 &&
        pCopyDataStruct->lpData != NULL)
    {
        // only open the file if a file operation is not already in progress
        if (WAIT_OBJECT_0 == WaitForSingleObject(theApp.ModalDialogEvent, 0))
        {
            CString File = (LPCTSTR)pCopyDataStruct->lpData;

            theApp.ModalDialogEvent.ResetEvent();
            if (NULL != AfxGetApp()->OpenDocumentFile(File))
            {
                ret = TRUE;
            }
            theApp.ModalDialogEvent.SetEvent();
        }
    }

    return ret;
}

LRESULT CMainFrame::OnSetMessageString(WPARAM wp, LPARAM lp)
{
    if (wp == AFX_IDS_IDLEMESSAGE || wp == IDS_PAUSEDMESSAGE)
    {
        if (WAIT_OBJECT_0 != WaitForSingleObject(theApp.MemoryEvent, 0))
        {
            wp = IDS_OUTOFMEMORY;
        }
        else if (WAIT_OBJECT_0 != WaitForSingleObject(theApp.PausedEvent, 0))
        {
            wp = IDS_PAUSEDMESSAGE;
        }
    }

    return CMDIFrameWnd::OnSetMessageString(wp, lp);
}

BOOL CALLBACK CloseChildFrames(HWND hWnd, LPARAM lp)
{
    CWnd *pWnd = CWnd::FromHandle(hWnd);
    CWnd *pActive = reinterpret_cast<CWnd*>(lp);

    if (pWnd->IsKindOf(RUNTIME_CLASS(CMDIChildWnd)) && pWnd != pActive)
    {
        pWnd->PostMessage(WM_CLOSE, 0, 0);
    }

    return TRUE;
}

void CMainFrame::OnFileCloseAll()
{
    EnumChildWindows(*this, &CloseChildFrames, NULL);
}

void CMainFrame::OnFileCloseAllExceptActive()
{
    EnumChildWindows(*this, &CloseChildFrames, reinterpret_cast<LPARAM>(MDIGetActive()));
}

void CMainFrame::OnFileCloseActive()
{
    MDIGetActive()->PostMessage(WM_CLOSE, 0, 0);
}
