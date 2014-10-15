/****************************************************************************
ChildFrm.cpp : Implementation file for the CChildFrame.cpp class
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
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
ON_WM_CREATE()
ON_MESSAGE(WMU_SETMESSAGETEXT, &CChildFrame::OnSetMessageText)
ON_MESSAGE(WM_SETMESSAGESTRING, &CChildFrame::OnSetMessageString)
ON_MESSAGE(WMU_UPDATECHILDSTATUSBAR, &CChildFrame::OnUpdateChildStatusBar)
ON_MESSAGE(WM_THEMECHANGED, &CChildFrame::OnThemeChanged)

ON_COMMAND(ID_VIEW_INDICATORS_TEXT, &CChildFrame::OnViewIndicatorsText)
ON_UPDATE_COMMAND_UI(ID_VIEW_INDICATORS_TEXT, &CChildFrame::OnUpdateViewIndicatorsText)
ON_COMMAND(ID_VIEW_INDICATORS_TIME, &CChildFrame::OnViewIndicatorsTime)
ON_UPDATE_COMMAND_UI(ID_VIEW_INDICATORS_TIME, &CChildFrame::OnUpdateViewIndicatorsTime)
ON_COMMAND(ID_VIEW_INDICATORS_FILE, &CChildFrame::OnViewIndicatorsFile)
ON_UPDATE_COMMAND_UI(ID_VIEW_INDICATORS_FILE, &CChildFrame::OnUpdateViewIndicatorsFile)
ON_COMMAND(ID_VIEW_INDICATORS_LINE, &CChildFrame::OnViewIndicatorsLine)
ON_UPDATE_COMMAND_UI(ID_VIEW_INDICATORS_LINE, &CChildFrame::OnUpdateViewIndicatorsLine)
ON_COMMAND(ID_VIEW_INDICATORS_METHOD, &CChildFrame::OnViewIndicatorsMethod)
ON_UPDATE_COMMAND_UI(ID_VIEW_INDICATORS_METHOD, &CChildFrame::OnUpdateViewIndicatorsMethod)
ON_COMMAND(ID_VIEW_INDICATORS_SIZE, &CChildFrame::OnViewIndicatorsSize)
ON_UPDATE_COMMAND_UI(ID_VIEW_INDICATORS_SIZE, &CChildFrame::OnUpdateViewIndicatorsSize)
END_MESSAGE_MAP()


// CChildFrame construction/destruction

CChildFrame::CChildFrame()
: pCurrentImage(NULL)
{
    // TODO: add member initialization code here
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    // do not automagically add doc title to caption bar
    cs.style &= ~FWS_ADDTOTITLE;

    if( !CMDIChildWnd::PreCreateWindow(cs) )
        return FALSE;

    return TRUE;
}


// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
    CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
    CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

// CChildFrame message handlers

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // create the status bar
    m_StatusBar.Create(this, WS_CHILD | CBRS_BOTTOM, AFX_IDW_CONTROLBAR_LAST);
    OnUpdateChildStatusBar((WPARAM)(-1), 0);

    return 0;
}

LRESULT CChildFrame::OnSetMessageText(WPARAM, LPARAM lp)
{
    // Set the text in the child frame's status bar
    pCurrentImage = reinterpret_cast<CImageData *>(lp);
    m_StatusBar.UpdatePaneText(pCurrentImage);
    
    return 0;
}

LRESULT CChildFrame::OnSetMessageString(WPARAM wp, LPARAM lp)
{
    if (wp == AFX_IDS_IDLEMESSAGE)
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

    return CMDIChildWnd::OnSetMessageString(wp, lp);
}

LRESULT CChildFrame::OnThemeChanged(WPARAM, LPARAM)
{
    LRESULT ret = Default();
    OnUpdateChildStatusBar((WPARAM)(-1), 0);
    return ret;
}

LRESULT CChildFrame::OnUpdateChildStatusBar(WPARAM wp, LPARAM lp)
{
    LRESULT ret = m_StatusBar.OnUpdateStatusBar(wp, lp);
    ShowControlBar(&m_StatusBar, ret != CChildStatusBar::CSBP_NONE, FALSE);
    m_StatusBar.UpdatePaneText(pCurrentImage);
    return ret;
}

void CChildFrame::OnViewIndicatorsText()
{
    m_StatusBar.TogglePane(CChildStatusBar::CSBP_TEXT);
}

void CChildFrame::OnUpdateViewIndicatorsText(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck((m_StatusBar.GetPanes() & CChildStatusBar::CSBP_TEXT) != 0);
}

void CChildFrame::OnViewIndicatorsTime()
{
    m_StatusBar.TogglePane(CChildStatusBar::CSBP_TIME);
}

void CChildFrame::OnUpdateViewIndicatorsTime(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck((m_StatusBar.GetPanes() & CChildStatusBar::CSBP_TIME) != 0);
}

void CChildFrame::OnViewIndicatorsFile()
{
    m_StatusBar.TogglePane(CChildStatusBar::CSBP_FILE);
}

void CChildFrame::OnUpdateViewIndicatorsFile(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck((m_StatusBar.GetPanes() & CChildStatusBar::CSBP_FILE) != 0);
}

void CChildFrame::OnViewIndicatorsLine()
{
    m_StatusBar.TogglePane(CChildStatusBar::CSBP_LINE);
}

void CChildFrame::OnUpdateViewIndicatorsLine(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck((m_StatusBar.GetPanes() & CChildStatusBar::CSBP_LINE) != 0);
}

void CChildFrame::OnViewIndicatorsMethod()
{
    m_StatusBar.TogglePane(CChildStatusBar::CSBP_METHOD);
}

void CChildFrame::OnUpdateViewIndicatorsMethod(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck((m_StatusBar.GetPanes() & CChildStatusBar::CSBP_METHOD) != 0);
}

void CChildFrame::OnViewIndicatorsSize()
{
    m_StatusBar.TogglePane(CChildStatusBar::CSBP_SIZE);
}

void CChildFrame::OnUpdateViewIndicatorsSize(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck((m_StatusBar.GetPanes() & CChildStatusBar::CSBP_SIZE) != 0);
}
