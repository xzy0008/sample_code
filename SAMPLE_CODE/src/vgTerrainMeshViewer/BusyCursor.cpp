/****************************************************************************
BusyCursor.cpp : Implementation file for the CBusyCursor class
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
#include "BusyCursor.h"

// The c'tor starts the wait cursor and sets the
// status bar text to the supplied text
// The d'tor clears the wait cursor and sets the
// status bar text to the app's default idle message

CBusyCursor::CBusyCursor(LPCTSTR StatusText /*= NULL*/)
{
    AfxGetApp()->BeginWaitCursor();
    if (NULL != StatusText)
    {
        AfxGetMainWnd()->SendMessage(WM_SETMESSAGESTRING, 0, reinterpret_cast<LPARAM>(StatusText));
    }
}

CBusyCursor::CBusyCursor(UINT StatusText)
{
    AfxGetApp()->BeginWaitCursor();
    AfxGetMainWnd()->SendMessage(WM_SETMESSAGESTRING, StatusText, 0);
}

CBusyCursor::~CBusyCursor(void)
{
    AfxGetApp()->EndWaitCursor();
    AfxGetMainWnd()->SendMessage(WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE, 0);
}
