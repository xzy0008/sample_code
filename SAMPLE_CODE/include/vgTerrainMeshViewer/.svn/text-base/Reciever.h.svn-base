/****************************************************************************
Reciever.h : Header file for the CRecieverThread and CRecieverWindow classes
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

#pragma once

// CRecieverThread

class CRecieverThread : public CWinThread
{
    DECLARE_DYNCREATE(CRecieverThread)

protected:
    CRecieverThread();           // protected constructor used by dynamic creation
    virtual ~CRecieverThread();

public:
    void Quit();
    virtual BOOL InitInstance();
    virtual int ExitInstance();

protected:
    DECLARE_MESSAGE_MAP()
};

// CRecieverWindow

class CRecieverWindow : public CWnd
{
    DECLARE_DYNAMIC(CRecieverWindow)

public:
    CRecieverWindow();
    virtual ~CRecieverWindow();
    virtual BOOL Create();

protected:
    virtual void PostNcDestroy();

protected:
    afx_msg LRESULT OnLookingForViewerApp(WPARAM wp, LPARAM lp);
    afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
    DECLARE_MESSAGE_MAP()
};


