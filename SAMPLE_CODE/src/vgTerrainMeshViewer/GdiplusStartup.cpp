/****************************************************************************
GdiplusStartup.cpp : Implementation file for the CGdiplusStartup class
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

// See: http://msdn2.microsoft.com/en-us/library/001tckck(VS.80).aspx

#include <vgStableHeaders.h>
#include "GdiplusStartup.h"

CGdiplusStartup::CGdiplusStartup()
{
#if !defined NO_GDIPLUS
    Gdiplus::GdiplusStartupInput gdipsi;
    gdipsi.SuppressBackgroundThread = TRUE;
    Gdiplus::GdiplusStartup(&Token, &gdipsi, &StartupOutput);
    StartupOutput.NotificationHook(&HookToken);
#endif
}

CGdiplusStartup::~CGdiplusStartup()
{
#if !defined NO_GDIPLUS
    StartupOutput.NotificationUnhook(HookToken);
    Gdiplus::GdiplusShutdown(Token);
#endif
}


int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
    int ret = -1;           // assume failure

#if !defined NO_GDIPLUS

    UINT  num = 0;          // number of image encoders
    UINT  size = 0;         // size of the image encoder array in bytes

    Gdiplus::GetImageEncodersSize(&num, &size);

    if (size != 0)
    {
        try
        {
            Gdiplus::ImageCodecInfo* pImageCodecInfo = reinterpret_cast<Gdiplus::ImageCodecInfo*>(new BYTE[size]);
            if (NULL != pImageCodecInfo)
            {
                Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

                for(UINT j = 0; j < num; ++j)
                {
                    if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
                    {
                        *pClsid = pImageCodecInfo[j].Clsid;
                        ret = j;  // Success
                    }    
                }
                delete[] pImageCodecInfo;
            }
        }
        catch (CMemoryException *me)
        {
            me->Delete();
        }
    }

#endif

    return ret;
}

