/****************************************************************************
MyDocManager.cpp : Implementation file for the CMyDocManager class
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
#include "MyDocManager.h"
#include "resource.h"
#include "FECFileDialog.h"

IMPLEMENT_DYNAMIC(CMyDocManager, CDocManager)

CMyDocManager::CMyDocManager(void)
{
}

CMyDocManager::~CMyDocManager(void)
{
}

BOOL CMyDocManager::DoPromptFileName(CString& fileName,
                                     UINT nIDSTitle,
                                     DWORD lFlags,
                                     BOOL bOpenFileDialog,
                                     CDocTemplate* pTemplate)
{
    // add the OFN_ENABLESIZING flag to the file dialog
    return CDocManager::DoPromptFileName(fileName,
                                         nIDSTitle,
                                         lFlags | OFN_ENABLESIZING,
                                         bOpenFileDialog,
                                         pTemplate);
}

void CMyDocManager::OnFileOpen()
{
    // add the OFN_ENABLESIZING and OFN_ALLOWMULTISELECT flags to the file dialog
    // add filters for multiple different image file types
    CString Filter;
    Filter.LoadString(IDS_OPENFILTER);
    CFECFileDialog Dlg(TRUE, _T(".ivd"), NULL, OFN_HIDEREADONLY | OFN_ENABLESIZING | OFN_ALLOWMULTISELECT, Filter, AfxGetMainWnd());
    if (IDOK == Dlg.DoModal())
    {
        POSITION Pos = Dlg.GetStartPosition();
        while (Pos)
        {
            AfxGetApp()->OpenDocumentFile(Dlg.GetNextPathName(Pos));
        }
    }
}
