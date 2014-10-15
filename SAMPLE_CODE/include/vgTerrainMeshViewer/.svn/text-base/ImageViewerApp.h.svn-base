/****************************************************************************
ImageViewerApp.h : Header file for the CImageViewerApp class
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

#ifndef __AFXWIN_H__
#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

#include "Reciever.h"
#include "ImageData.h"
#include <queue>

#define WMU_DOCUMENTCLOSING         WM_APP + 0  // wp - Process ID               lp - unused
#define WMU_GETBGCOLOUR             WM_APP + 1  // wp - unused                   lp - unused
#define WMU_GETDISPLAYLOCK          WM_APP + 2  // wp - unused                   lp - unused
#define WMU_GETPOINTDATA            WM_APP + 3  // wp - CTooltipWindow pointer   lp - CTooltipWindow::PointData pointer
#define WMU_SETPROPERTIES           WM_APP + 4  // wp - CChildFrame pointer      lp - CImageData pointer
#define WMU_UPDATETOOLTIP           WM_APP + 5  // wp - CImageViewerView pointer lp - unused
#define WMU_SETMESSAGETEXT          WM_APP + 6  // wp - unused                   lp - CImageData pointer
#define WMU_UPDATECHILDSTATUSBAR    WM_APP + 7  // wp - active panes flag        lp - unused

#define IsSHIFTpressed() ((GetKeyState(VK_SHIFT) & (1 << (sizeof(SHORT) * 8 - 1))) != 0)
#define IsCTRLpressed() ((GetKeyState(VK_CONTROL) & (1 << (sizeof(SHORT) * 8 - 1))) != 0)
#define IsSCROLLLOCKToggled() ((GetKeyState(VK_SCROLL) & 1) != 0)

const UINT RWM_ARE_YOU_ME = RegisterWindowMessage(_T("ImageViewer_{D47B4656-B775-43dc-AE71-37A4DA3A425C}"));

typedef std::queue<CImageData> DataQueue;

// CImageViewerApp:
// See ImageViewerApp.cpp for the implementation of this class
//

class CImageViewerApp : public CWinApp
{
public:
    CImageViewerApp();

    CRecieverThread *RecieverThread;
    DataQueue InputQueue;

    CCriticalSection QueueSection;  // control thread access to InputQueue
    CEvent PausedEvent;             // used to stop the reciever thread from recieving data
    CEvent MemoryEvent;             // used to try to prevent 'Out of Memory' errors
    size_t MaximumMemoryUsage;      // maximum memory usage in KB

    // Because the Image Viewer application is limited to a single instance, and the way
    // I implemented opening files from the shell (new instance sends a WM_COPYDATA
    // message with the file name to open) it was possible for a file to be opened
    // while a modal dialog was active. When this happened, the modalness of the dialog
    // was broken, and the dialog was essentially orphaned. Using this event to control
    // the WM_COPYDATA message and modal dialogs is my workaround.
    CEvent ModalDialogEvent;

    CGdiplusStartup GdiplusStartup;

protected:
    static BOOL CALLBACK Searcher(HWND, LPARAM);

    // Overrides
public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();

protected:
    virtual BOOL IsIdleMessage(MSG* pMsg);

    // Implementation
    afx_msg void OnAppAbout();
    afx_msg void OnFileOpen();
    afx_msg void OnFilePause();
    afx_msg void OnUpdateFilePause(CCmdUI *pCmdUI);
    afx_msg void OnSetupMemory();
    DECLARE_MESSAGE_MAP()



    ////////////////////////////////////////////////////////////////////////////////////
    //                                                                                //
    //  WriteObjectArray() and ReadObjectArray()                                      //
    //                                                                                //
    //  Make these functions public members of your CWinApp derived class by copying  //
    //  them into the CWinApp class' header file                                      //
    //                                                                                //
    ////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////
    //
    //  WriteObjectArray - A template function to save an array of objects in the
    //  registry under "HKEY_CURRENT_USER\Software\<company name>\<app>\<Section>\<Entry>".
    //  Use CWinApp::SetRegistryKey() to setup the company name.
    //
    //  Parameters :
    //      Section [in] - The section name
    //      Entry   [in] - The entry name
    //      pObject [in] - A pointer to the object array
    //      Count   [in] - The number of objects in the array
    //
    //  Returns :
    //      If the function succeeds, the return value is ERROR_SUCCESS.
    //      If the function fails, the return value is a nonzero error code.
    //
    //  Note :
    //      This function does a bitwise copy of the object array into the registry.
    //      Do not use this function if your objects contain pointers to data.
    //
    ////////////////////////////////////////////////////////////////////////////////////

    public:

    template <typename T>
    long WriteObjectArray(LPCTSTR Section, LPCTSTR Entry, T *pObject, UINT Count = 1)
    {
        ASSERT(NULL != Section);
        ASSERT(NULL != Entry);
        ASSERT(NULL != pObject);
        ASSERT(0 != Count);

        if (NULL == Section || NULL == Entry || NULL == pObject || 0 == Count)
        {
            return ERROR_INVALID_PARAMETER;
        }

        // CWinApp::GetSectionKey() returns NULL on error, not a valid error
        // code, so I used ERROR_INVALID_HANDLE as the default failure code.
        long ErrorCode = ERROR_INVALID_HANDLE;
        HKEY hKey = GetSectionKey(Section);
        if (NULL != hKey)
        {
            ErrorCode = RegSetValueEx(hKey,
                                      Entry,
                                      NULL,
                                      REG_BINARY,
                                      reinterpret_cast<LPBYTE>(pObject),
                                      Count * sizeof(T));
            RegCloseKey(hKey);  // do not forget to close the HKEY!
        }

        return ErrorCode;
    };

    ////////////////////////////////////////////////////////////////////////////////////
    //
    //  GetObjectArray - A template function to read an array of objects from the
    //  registry that was saved using the WriteObjectArray function under
    //  "HKEY_CURRENT_USER\Software\<company name>\<app>\<Section>\<Entry>".
    //  Use CWinApp::SetRegistryKey() to setup the company name.
    //
    //  Parameters :
    //      Section  [in] - The section name
    //      Entry    [in] - The entry name
    //      pObject  [in] - A pointer to the object array that will take the data
    //      pCount   [in] - The number of objects that the array can hold
    //              [out] - The number of objects copied into the array, or if
    //                      ERROR_MORE_DATA is returned, the number of objects saved
    //                      in the registry.
    //
    //  Returns :
    //      If the function succeeds, the return value is ERROR_SUCCESS.
    //      If the array is too small to hold all the data, the return value is ERROR_MORE_DATA
    //      If the function fails, the return value is a nonzero error code.
    //
    //  Note :
    //      This function does a bitwise copy of the object array from the registry.
    //
    //      If pCount is NULL, only one object is read from the registry. If there is more
    //      than one object in the registry, the return value is ERROR_MORE_DATA
    //
    //      If the number of objects is less than or equal to pCount, pCount is set to the
    //      number of objects copied into the array and the return value is ERROR_SUCCESS
    //
    //      If the number of objects in the registry is more than pCount, then pCount objects
    //      are copied into the array, the return value is ERROR_MORE_DATA, and pCount is
    //      set to the number of objects saved in the registry.
    //
    ////////////////////////////////////////////////////////////////////////////////////

    template <typename T>
    long GetObjectArray(LPCTSTR Section, LPCTSTR Entry, T *pObject, UINT *pCount = NULL)
    {
        // validate parameters
        ASSERT(NULL != Section);
        ASSERT(NULL != Entry);
        ASSERT(NULL != pObject);
        ASSERT(NULL == pCount || *pCount != 0);

        if (NULL == Section || NULL == Entry || NULL == pObject || (NULL != pCount && 0 == *pCount))
        {
            if (NULL != pCount)
            {
                *pCount = 0;
            }

            return ERROR_INVALID_PARAMETER;
        }

        UINT Count = NULL != pCount ? *pCount : 1;  // how many?
        DWORD Size = 0;

        // CWinApp::GetSectionKey() returns NULL on error, not a valid error
        // code, so I used ERROR_INVALID_HANDLE as the default failure code.
        long ErrorCode = ERROR_INVALID_HANDLE;

        // Get the HKEY handle for the proper section (creates the section if not present)
        HKEY hKey = GetSectionKey(Section);
        if (NULL != hKey)
        {
            // Get the size of the data in the registry
            ErrorCode = RegQueryValueEx(hKey,
                                        Entry,
                                        NULL,
                                        NULL,
                                        NULL,
                                        &Size);
            if (ERROR_SUCCESS == ErrorCode)
            {
                // make sure there is data and it is the correct size
                if (0 != Size && 0 == Size % sizeof(T))
                {
                    T *Temp = pObject;

                    if (Size > Count * sizeof(T))
                    {
                        // more data than we have room for?
                        // allocate temporary storage so we can grab it all
                        try
                        {
                            Temp = new T[Size / sizeof(T)];
                        }
                        catch (CMemoryException *me)
                        {
                            theApp.m_pMainWnd->PostMessage(WM_SETMESSAGESTRING, IDS_OUTOFMEMORY, 0);
                            MemoryEvent.ResetEvent();
                            me->ReportError();
                            me->Delete();
                            return ERROR_NOT_ENOUGH_MEMORY;
                        }
                    }

                    ErrorCode = RegQueryValueEx(hKey,
                                                Entry,
                                                NULL,
                                                NULL,
                                                reinterpret_cast<LPBYTE>(Temp),
                                                &Size);
                    if (ERROR_SUCCESS == ErrorCode)
                    {
                        if (Temp != pObject)
                        {
                            // copy the requested amount of data into the pObject array
                            memcpy_s(pObject, Count * sizeof(T), Temp, Count * sizeof(T));
                            ErrorCode = ERROR_MORE_DATA;
                        }
                    }

                    if (Temp != pObject)
                    {
                        delete[] Temp;  // no memory leaks allowed!
                    }
                }
                else
                {
                    // no data or size mismatch
                    ErrorCode = ERROR_INVALID_DATA;
                    Size = 0;
                }
            }

            RegCloseKey(hKey);  // do not forget to close the HKEY!
        }

        if (pCount != NULL)
        {
            *pCount = Size / sizeof(T);
        }

        return ErrorCode;
    }

    ////////////////////////////////////////////////////////////////////////////////////
};

extern CImageViewerApp theApp;