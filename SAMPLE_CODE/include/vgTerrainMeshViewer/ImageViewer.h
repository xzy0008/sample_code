/***************************************************************************
ImageViewer.h : header file for the Image Viewer tool
written by PJ Arends
pja@telus.net

For updates check http://www.codeproject.com/tools/imageviewer.asp

Version 2.3

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

-----------------------------------------------------------------------------

Credits
=======

The ShowImageList portion was originally written by Jörgen Sigvardsson <jorgen@profitab.com>

The ShowRegion portion was originally written by Waldermort <waldermort@hotmail.com>

The ShowGraphic portion was originally written by Morpheus Ftp <morftp@hotmail.com>
    and is based on the TRACE macro written by Paul Mclachlan which is found at
    http://www.codeproject.com/debug/location_trace.asp

-----------------------------------------------------------------------------

            Instructions on using the Image Viewer utility
            ==============================================

The Image Viewer utility is used to show the contents of memory device contexts
and in memory bitmaps while you are stepping through some drawing code.

To use the image viewer utility, make sure the ImageViewer.dll file is in your
executable path, the ImageViewer.exe program is running, the ImageViewer.lib
file is in your library include path, and then simply include this file
in any file you want to use it in. This utility only works in debug builds
and you turn the tool on by #defining the 'ACTIVATE_VIEWER' macro.

  ie.
     #define ACTIVATE_VIEWER
     #include <ImageViewer.h>


This file defines the following macros :

  ShowBitmap  (HBITMAP Bitmap)
  ShowBitmap2 (HBITMAP Bitmap, LPCTSTR Text)

      Bitmap [in] - A HBITMAP or a CBitmap object
      Text   [in] - A descriptive text that is accessible from the viewer

      Displays the contents of an in-memory bitmap


  ShowDC  (HDC DC)
  ShowDC2 (HDC DC, LPCTSTR Text)

      DC   [in] - A HDC or a CDC object
      Text [in] - A descriptive text that is accessible from the viewer

      Displays the contents of a memory device context


  ShowGDIPlusBitmap  (Gdiplus::Image Bitmap)
  ShowGDIPlusBitmap2 (Gdiplus::Image Bitmap, LPCTSTR Text)

      Bitmap [in] - A Gdiplus Image
      Text   [in] - A descriptive text that is accessible from the viewer

      Displays the contents of an in memory GDI+ Image


  ShowIcon  (HICON Icon)
  ShowIcon2 (HICON Icon, LPCTSTR Text)

      Icon [in] - A HICON object
      Text [in] - A descriptive text that is accessible from the viewer

      Displays the contents of a HICON handle


  ShowImageList  (HIMAGELIST List, int Index, UINT Flags)
  ShowImageList2 (HIMAGELIST List, int Index, UINT Flags, LPCTSTR Text)

      List  [in] - A HIMAGELIST or a CImageList object
      Index [in] - Index of image in list to show, -1 for all
      Flags [in] - The ILD_* flag that specifies how to display the image
      Text  [in] - A descriptive text that is accessible from the viewer

      Displays the contents of an in-memory image list


  ShowFont  (HFONT Font)
  ShowFont2 (HFONT Font, LPCTSTR Text)
  ShowFont3 (LPCTSTR Sample, HFONT Font, LPCTSTR Text)

      Font   [in] - A HFONT or a CFont object
      Text   [in] - A descriptive text that is accessible from the viewer
      Sample [in] - The text that is drawn on the final image


  ShowRegion  (HRGN Region)
  ShowRegion2 (HRGN Region, LPCTSTR Text)
  ShowRegion3 (HRGN Region, HBITMAP Bitmap, LPCTSTR Text)
  ShowRegion4 (HRGN Region, HDC DC, LPCTSTR Text)

      Region [in] - A HRGN or a CRgn object
      Text   [in] - A descriptive text that is accessible from the viewer
      Bitmap [in] - The background bitmap to draw the region onto
      DC     [in] - The memory device context to draw the region onto

      Displays the shape of a HRGN object. If a bitmap or memory device context
      is supplied the region is shown by inverting the colours of the area covered
      by the region, otherwise the region is shown in black on a white background.


  ShowGraphic (HBITMAP Bitmap, LPCTSTR Text, ...)
  ShowGraphic (HDC DC, LPCTSTR Text, ...)
  ShowGraphic (HICON Icon, LPCTSTR Text, ...)
  ShowGraphic (HFONT Font, LPCTSTR Text, ...)
  ShowGraphic (LPCTSTR Sample, HFONT Font, LPCTSTR Text, ...)
  ShowGraphic (HIMAGELIST List, int Index, UINT Flags, Text, ...)
  ShowGraphic (Gdiplus::Image &GdiplusImage, LPCTSTR Text, ...)
  ShowGraphic (HRGN Region, LPCTSTR Text, ...)
  ShowGraphic (HRGN Region, HBITMAP BkGndBitmap, LPCTSTR Text, ...)
  ShowGraphic (HRGN Region, HDC BkGndDC, LPCTSTR Text, ...)

      Bitmap        [in] - A HBITMAP or a CBitmap object
      DC            [in] - A HDC or a CDC object
      Icon          [in] - A HICON object
      Font          [in] - A HFONT or CFont object
      Sample        [in] - Sample text used to display the font
      List          [in] - A HIMAGELIST or a CImageList object
      Index         [in] - Index of image in list to show, -1 for all
      Flags         [in] - The ILD_* flag that specifies how to display the image
      GdiplusImage  [in] - A Gdiplus Image
      Region        [in] - A HRGN or a CRgn object
      BkGndBitmap   [in] - The background bitmap to draw the region onto
      BkGndDC       [in] - The memory device context to draw the region onto
      Text  (opt)   [in] - A descriptive text that conforms to printf() style formatting
      ...   (opt)   [in] - Addition parameters for formatting the descriptive text

      The ShowGraphic function is only available if using Visual Studio 7.0 (2002) or
      later. The main advantage of using ShowGraphic over using the other older Show*
      macros is that the optional descriptive text can be formatted using printf() style
      formatting specifiers, much the same way as the MFC TRACE() function. The
      ShowGraphic function is otherwise functionally identical to the other Show*
      macros that have the same parameters.


If the ACTIVATE_VIEWER and _DEBUG macros are not defined, the Show* macros
are ignored, The ImageViewer.lib file is not linked, and the ImageViewer.dll
file is not loaded.

If the Image Viewer tool is active, the VIEWER_ACTIVE macro will be defined,
so you can control extra code around the Show* macros by checking for the
VIEWER_ACTIVE macro.

  ie.
     #ifdef VIEWER_ACTIVE

     // Some code that requires the image viewer tool

     #endif // VIEWER_ACTIVE

****************************************************************************/

#ifndef PJA_IMAGE_VIEWER_UTILITY_HEADER_FILE_INCLUDED
#   define PJA_IMAGE_VIEWER_UTILITY_HEADER_FILE_INCLUDED

#   if _MSC_VER > 1000
#       pragma once
#   endif // _MSC_VER > 1000

#   undef VIEWER_ACTIVE

#   if defined _DEBUG && defined ACTIVATE_VIEWER
#       define VIEWER_ACTIVE 1
#   endif // defined _DEBUG && defined ACTIVATE_VIEWER

#   ifdef VIEWER_ACTIVE
//#       pragma comment(lib, "ImageViewer.lib")

#       ifdef __cplusplus
            extern "C" {
#       endif // __cplusplus

        // Do not call these functions directly in your code, doing so
        // will cause linker and/or run time errors if the Image Viewer
        // tool is turned off. Use the Show* macros instead.
        __declspec(dllimport) HBITMAP GetBGBitmap(UINT, UINT);

#       ifdef _UNICODE
            __declspec(dllimport) LRESULT BitmapViewW(HBITMAP, LPCWSTR, UINT, LPCWSTR, LPCWSTR);
            __declspec(dllimport) LRESULT IconViewW(HICON, LPCWSTR, UINT, LPCWSTR, LPCWSTR);
            __declspec(dllimport) LRESULT RegionViewW(HRGN, HBITMAP, LPCWSTR, UINT, LPCWSTR, LPCWSTR);
            __declspec(dllimport) LRESULT FontViewW(HFONT, LPCWSTR, LPCWSTR, UINT, LPCWSTR, LPCWSTR);
#           define BitmapView BitmapViewW
#           define IconView IconViewW
#           define RegionView RegionViewW
#           define FontView FontViewW
#       else // _UNICODE
            __declspec(dllimport) LRESULT BitmapViewA(HBITMAP, LPCSTR, UINT, LPCSTR, LPCSTR);
            __declspec(dllimport) LRESULT IconViewA(HICON, LPCSTR, UINT, LPCSTR, LPCSTR);
            __declspec(dllimport) LRESULT RegionViewA(HRGN, HBITMAP, LPCSTR, UINT, LPCSTR, LPCSTR);
            __declspec(dllimport) LRESULT FontViewA(HFONT, LPCSTR, LPCSTR, UINT, LPCSTR, LPCSTR);
#           define BitmapView BitmapViewA
#           define IconView IconViewA
#           define RegionView RegionViewA
#           define FontView FontViewA
#       endif // _UNICODE

#       ifdef _INC_COMMCTRL
#           ifdef _UNICODE
                __declspec(dllimport) LRESULT ImageListViewW(HIMAGELIST, int, UINT, LPCWSTR, UINT, LPCWSTR, LPCWSTR);
#               define ImageListView ImageListViewW
#           else // _UNICODE
                __declspec(dllimport) LRESULT ImageListViewA(HIMAGELIST, int, UINT, LPCSTR, UINT, LPCSTR, LPCSTR);
#               define ImageListView ImageListViewA
#           endif // _UNICODE
#       endif // _INC_COMMCTRL

#       ifdef __cplusplus
            }
#       endif // __cplusplus

#       if _MSC_VER < 1300                  // The __FUNCTION__ macro is only valid in VC7.0 and above
#           define FUNC NULL
#       else // _MSC_VER < 1300
#           define FUNC _T(__FUNCTION__)
#       endif // _MSC_VER < 1300

#       define ShowBitmap(Bitmap)        BitmapView((Bitmap), _T(__FILE__), __LINE__, FUNC, NULL)
#       define ShowBitmap2(Bitmap, Text) BitmapView((Bitmap), _T(__FILE__), __LINE__, FUNC, (Text))

#       define ShowDC(DC)        BitmapView((HBITMAP)GetCurrentObject((DC), OBJ_BITMAP), _T(__FILE__), __LINE__, FUNC, NULL)
#       define ShowDC2(DC, Text) BitmapView((HBITMAP)GetCurrentObject((DC), OBJ_BITMAP), _T(__FILE__), __LINE__, FUNC, (Text))

#       define ShowIcon(Icon)        IconView ((Icon), _T(__FILE__), __LINE__, FUNC, NULL)
#       define ShowIcon2(Icon, Text) IconView ((Icon), _T(__FILE__), __LINE__, FUNC, (Text))

#       define ShowCursor(Cursor)        IconView ((Cursor), _T(__FILE__), __LINE__, FUNC, NULL)
#       define ShowCursor2(Cursor, Text) IconView ((Cursor), _T(__FILE__), __LINE__, FUNC, (Text))

#       define ShowFont(Font)                FontView ((Font), NULL, _T(__FILE__), __LINE__, FUNC, NULL)
#       define ShowFont2(Font, Text)         FontView ((Font), NULL, _T(__FILE__), __LINE__, FUNC, Text)
#       define ShowFont3(Sample, Font, Text) FontView ((Font), Sample, _T(__FILE__), __LINE__, FUNC, Text)

#       define ShowRegion(Region)                RegionView((Region), NULL, _T(__FILE__), __LINE__, FUNC, NULL)
#       define ShowRegion2(Region, Text)         RegionView((Region), NULL, _T(__FILE__), __LINE__, FUNC, (Text))
#       define ShowRegion3(Region, Bitmap, Text) RegionView((Region), (Bitmap), _T(__FILE__), __LINE__, FUNC, (Text))
#       define ShowRegion4(Region, DC, Text)     RegionView((Region), (HBITMAP)GetCurrentObject((DC), OBJ_BITMAP), _T(__FILE__), __LINE__, FUNC, (Text))

#       ifdef _INC_COMMCTRL   // defined in CommCtrl.h; header needed for HIMAGELIST
#           define ShowImageList(List, Index, Flags)        ImageListView((List), (Index), (Flags), _T(__FILE__), __LINE__, FUNC, NULL)
#           define ShowImageList2(List, Index, Flags, Text) ImageListView((List), (Index), (Flags), _T(__FILE__), __LINE__, FUNC, (Text))
#       else // _INC_COMMCTRL
#           define ShowImageList(List, Index, Flags)
#           define ShowImageList2(List, Index, Flags, Text)
#       endif // _INC_COMMCTRL

#       ifdef _GDIPLUS_H   // defined in GdiPlus.h, header needed for the Gdiplus namespace

            // Use an inline static class member function to avoid LNK2005 errors.
            // This is placed here and not in the dll so users of the dll do not
            // have to have GDI+ installed on their machines.
            //
            // This code assumes that the calling code has properly initialized
            // the GDI+ library by calling GdiplusStartup()

            namespace pja_ImageViewer
            {
                class GDIPlus
                {
                public:
                    static LRESULT ImageView (Gdiplus::Image &Image, LPCTSTR File, UINT Line, LPCTSTR Function, LPCTSTR Text)
                    {
                        LRESULT ret = ERROR_INVALID_PARAMETER;

                        UINT Width = Image.GetWidth();
                        UINT Height = Image.GetHeight();

                        HDC DC = CreateCompatibleDC(NULL);
                        HBITMAP hBitmap = GetBGBitmap(Width, Height);
                        HGDIOBJ hGDIObj = SelectObject(DC, hBitmap);
                        {
                            // seperate scope for Graphics object
                            Gdiplus::Graphics Graphics(DC);
                            if (Gdiplus::Ok == Graphics.DrawImage(&Image, 0, 0, Width, Height))
                            {
                                ret = BitmapView(hBitmap, File, Line, Function, Text);
                            }
                        }
                        SelectObject(DC, hGDIObj);
                        DeleteObject(hBitmap);
                        DeleteDC(DC);

                        return ret;
                    }
                }; // class GDIPlus
            } // namespace pja_ImageViewer

#           define ShowGDIPlusBitmap(Image)        pja_ImageViewer::GDIPlus::ImageView((Image), _T(__FILE__), __LINE__, FUNC, NULL)
#           define ShowGDIPlusBitmap2(Image, Text) pja_ImageViewer::GDIPlus::ImageView((Image), _T(__FILE__), __LINE__, FUNC, (Text))
#       else
#           define ShowGDIPlusBitmap(Image)
#           define ShowGDIPlusBitmap2(Image, Text)
#       endif // _GDIPLUS_H


        // The following pja_ImageViewer namespace and it's contained classes and
        // functions are used as helpers for the ShowGraphic macro.
        // The ShowGraphic macro is only available in VC 7.0 and above.

#       if _MSC_VER >= 1300

#           include <stdio.h>
#           include <stdarg.h>

            namespace pja_ImageViewer
            {
                class CFormatText
                {
                private:
                    LPTSTR Text;

                public:
                    CFormatText(LPCTSTR Format, va_list ArgList)
                        : Text(NULL)
                    {
                        if (NULL != Format)
                        {
                            int BufferSize = _vsctprintf(Format, ArgList) + 1;
                            Text = new TCHAR[BufferSize];
#                           if _MSC_VER >= 1400
                                _vstprintf_s(Text, BufferSize, Format, ArgList);
#                           else
                                _vstprintf(Text, Format, ArgList);
#                           endif
                        }
                    }

                    ~CFormatText()
                    {
                        delete[] Text;
                    }

                    operator LPCTSTR()
                    {
                        return Text;
                    }
                }; // class CFormatText

                class CShowGraphic
                {
                private:
                    LPCTSTR m_File;
                    UINT    m_Line;
                    LPCTSTR m_Function;

                public:
                    CShowGraphic(LPCTSTR File, UINT Line, LPCTSTR Function)
                    : m_File(File), m_Line(Line), m_Function(Function)
                    {
                    }

                    LRESULT operator()(HBITMAP hBitmap, LPCTSTR Format = NULL, ...)
                    {
                        va_list ArgList;
                        va_start(ArgList, Format);
                        return BitmapView(hBitmap, m_File, m_Line, m_Function, CFormatText(Format, ArgList));
                    }

                    LRESULT operator()(HDC hDC, LPCTSTR Format = NULL, ...)
                    {
                        va_list ArgList;
                        va_start(ArgList, Format);
                        return BitmapView(reinterpret_cast<HBITMAP>(GetCurrentObject(hDC, OBJ_BITMAP)), m_File, m_Line, m_Function, CFormatText(Format, ArgList));
                    }

                    // HICON and HCURSOR are polymorphic so this function serves both (see windef.h)
                    LRESULT operator()(HICON hIcon, LPCTSTR Format = NULL, ...)
                    {
                        va_list ArgList;
                        va_start(ArgList, Format);
                        return IconView(hIcon, m_File, m_Line, m_Function, CFormatText(Format, ArgList));
                    }

                    LRESULT operator()(HFONT hFont, LPCTSTR Format = NULL, ...)
                    {
                        va_list ArgList;
                        va_start(ArgList, Format);
                        return FontView(hFont, NULL, m_File, m_Line, m_Function, CFormatText(Format, ArgList));
                    }

                    // Place the sample text first in the parameter list to avoid ambiguity errors
                    LRESULT operator()(LPCTSTR Sample, HFONT hFont, LPCTSTR Format = NULL, ...)
                    {
                        va_list ArgList;
                        va_start(ArgList, Format);
                        return FontView(hFont, Sample, m_File, m_Line, m_Function, CFormatText(Format, ArgList));
                    }

                    LRESULT operator()(HRGN hRgn, LPCTSTR Format = NULL, ...)
                    {
                        va_list ArgList;
                        va_start(ArgList, Format);
                        return RegionView(hRgn, NULL, m_File, m_Line, m_Function, CFormatText(Format, ArgList));
                    }

                    LRESULT operator()(HRGN hRgn, HBITMAP hBitmap, LPCTSTR Format = NULL, ...)
                    {
                        va_list ArgList;
                        va_start(ArgList, Format);
                        return RegionView(hRgn, hBitmap, m_File, m_Line, m_Function, CFormatText(Format, ArgList));
                    }

                    LRESULT operator()(HRGN hRgn, HDC hDC, LPCTSTR Format = NULL, ...)
                    {
                        va_list ArgList;
                        va_start(ArgList, Format);
                        return RegionView(hRgn, reinterpret_cast<HBITMAP>(GetCurrentObject(hDC, OBJ_BITMAP)), m_File, m_Line, m_Function, CFormatText(Format, ArgList));
                    }

#                   ifdef _INC_COMMCTRL // defined in CommCtrl.h; header needed for HIMAGELIST
                        LRESULT operator()(HIMAGELIST hImageList, int iImg, UINT nCustomFlags, LPCTSTR Format = NULL, ...)
                        {
                            va_list ArgList;
                            va_start(ArgList, Format);
                            return ImageListView(hImageList, iImg, nCustomFlags, m_File, m_Line, m_Function, CFormatText(Format, ArgList));
                        }
#                   endif // _INC_COMMCTRL

#                   ifdef _GDIPLUS_H // defined in GdiPlus.h, header needed for the Gdiplus namespace
                        LRESULT operator()(Gdiplus::Image &Image, LPCTSTR Format = NULL, ...)
                        {
                            va_list ArgList;
                            va_start(ArgList, Format);
                            return GDIPlus::ImageView(Image, m_File, m_Line, m_Function, CFormatText(Format, ArgList));
                        }
#                   endif // _GDIPLUS_H                     
                }; // class CShowGraphic
            } // namespace pja_ImageViewer

#           define ShowGraphic pja_ImageViewer::CShowGraphic(_T(__FILE__), __LINE__, _T(__FUNCTION__))
#       endif // _MSC_VER >= 1300

#   else // VIEWER_ACTIVE
#       define ShowBitmap(Bitmap)                       (LRESULT)(0)
#       define ShowDC(DC)                               (LRESULT)(0)
#       define ShowIcon(Icon)                           (LRESULT)(0)
#       define ShowCursor(Cursor)                       (LRESULT)(0)
#       define ShowFont(Font)                           (LRESULT)(0)
#       define ShowImageList(List, Index, Flags)        (LRESULT)(0)
#       define ShowRegion(Region)                       (LRESULT)(0)
#       define ShowGDIPlusBitmap(Image)                 (LRESULT)(0)

#       define ShowBitmap2(Bitmap, Text)                (LRESULT)(0)
#       define ShowDC2(DC, Text)                        (LRESULT)(0)
#       define ShowIcon2(Icon, Text)                    (LRESULT)(0)
#       define ShowCursor2(Cursor, Text)                (LRESULT)(0)
#       define ShowFont2(Font, Text)                    (LRESULT)(0)
#       define ShowImageList2(List, Index, Flags, Text) (LRESULT)(0)
#       define ShowRegion2(Region, Text)                (LRESULT)(0)
#       define ShowGDIPlusBitmap2(Image, Text)          (LRESULT)(0)

#       define ShowFont3(Sample, Font, Text)            (LRESULT)(0)
#       define ShowRegion3(Region, Bitmap, Text)        (LRESULT)(0)

#       define ShowRegion4(Region, DC, Text)            (LRESULT)(0)

#       if _MSC_VER >= 1300             // VC 7.0 and above
#           define ShowGraphic __noop
#       endif // _MSC_VER >= 1300
#   endif // VIEWER_ACTIVE

#endif // PJA_IMAGE_VIEWER_UTILITY_HEADER_FILE_INCLUDED
