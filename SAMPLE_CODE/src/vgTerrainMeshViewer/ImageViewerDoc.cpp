/****************************************************************************
ImageViewerDoc.cpp : Implementation file for the CImageViewerDoc class
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

#include "ImageViewerDoc.h"
#include "pja_format.h"
#include "pja_dc.h"
#include "pja_bitmap.h"

#include "ProgressDialog.h"
#include "BusyCursor.h"

#include <vgImage/vgiCximageWrapper.h>
#include <vgTerritory/vgVgtrFile.h>


#define ACTIVATE_VIEWER
#include <ImageViewer.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageViewerDoc

IMPLEMENT_DYNCREATE(CImageViewerDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageViewerDoc, CDocument)
    ON_COMMAND(ID_FILE_SAVE_AS, &CImageViewerDoc::OnFileSaveAs)
    ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, &CImageViewerDoc::OnUpdateFileSaveAs)
END_MESSAGE_MAP()


// CImageViewerDoc construction/destruction

CImageViewerDoc::CImageViewerDoc()
: ProcessID(0)
, IsImageFile(false)
{
    // TODO: add one-time construction code here
}

CImageViewerDoc::~CImageViewerDoc()
{
}

BOOL CImageViewerDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: add reinitialization code here
    // (SDI documents will reuse this document)

    return TRUE;
}

// CImageViewerDoc diagnostics

#ifdef _DEBUG
void CImageViewerDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CImageViewerDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageViewerDoc commands

void CImageViewerDoc::AddImageData(const CImageData &ImageData)
{
    Images.push_back(ImageData);
}

size_t CImageViewerDoc::GetImageDataCount() const
{
    return Images.size();
}

CImageData *CImageViewerDoc::GetImageData(size_t Index)
{
    CImageData *pointer = NULL;
    if (Index < Images.size())
    {
        pointer = &Images[Index];
    }
    return pointer;
}

void CImageViewerDoc::DeleteImageData(size_t First, size_t Last /* = 0 */)
{
    if (First >= Images.size())
    {
        return;
    }

    if (0 == Last)
    {
        ImageDataVector::iterator it = Images.begin() + First;
        Images.erase(it);
    }
    else
    {
        CBusyCursor Busy(IDS_WAITDELETE);

        if (Last >= Images.size())
        {
            Last = Images.size() - 1;
        }

        ASSERT (First <= Last);

        size_t End = Last + 1;
        do
        {
            // by erasing only 500 images at a time the memory usage
            // indicator on the status bar can be animated
            size_t Start = End > 500 ? End - 500 : 0;
            if (Start < First)
            {
                Start = First;
            }

            ImageDataVector::iterator it1 = Images.begin() + Start;
            ImageDataVector::iterator it2 = Images.begin() + End;
            Images.erase(it1, it2);

            // update the status bar
            theApp.OnIdle(-1);

            End = End > 500 ? End - 500 : 0;
        } while (End > First);
    }

    if (CImageData::GetMemUsage() < theApp.MaximumMemoryUsage * 1024)
    {
        theApp.MemoryEvent.SetEvent();
        theApp.m_pMainWnd->PostMessage(WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE, 0);
    }

    CDeletedImageData Data;
    Data.StartRange = First;
    Data.EndRange = 0 == Last ? First : Last;
    Data.CountLeft = GetImageDataCount();
    UpdateAllViews(NULL, 0, &Data);
}

void CImageViewerDoc::OnCloseDocument()
{
    if (ProcessID != 0)
    {
        VERIFY (AfxGetMainWnd()->SendMessage(WMU_DOCUMENTCLOSING,
                                             ProcessID,
                                             0));
    }

    CDocument::OnCloseDocument();
}

void CImageViewerDoc::SetCaption(DWORD ID)
{
    // assign a title to this new document and view
    std::tstring Title;
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ID);
    if (NULL != hProcess)
    {
        Title = GetModuleBaseName(hProcess, NULL);
    }

    pja::CFormat cf;
    Caption = cf.MakeMessage(NULL, IDS_TITLE, 2, cf.TS(ID), Title);
    ProcessID = ID;
}

std::tstring CImageViewerDoc::GetModuleBaseName(HANDLE hProcess, HMODULE hModule) const
{
    std::tstring Name;
    DWORD Size = 0;
    DWORD Used = 0;
    LPTSTR Buffer = NULL;

    try
    {
        do {
            Size += 32;
            Buffer = new TCHAR[Size];
            if (NULL != Buffer)
            {
                Used = ::GetModuleBaseName(hProcess, hModule, Buffer, Size);
                Name = Buffer;
                delete[] Buffer;
            }
        } while (Used > Size - 1);
    }

    catch (CMemoryException *me)
    {
        theApp.m_pMainWnd->PostMessage(WM_SETMESSAGESTRING, IDS_OUTOFMEMORY, 0);
        theApp.MemoryEvent.ResetEvent();
        me->ReportError();
        me->Delete();
        Name = _T("");
    }

    return Name;
}

void CImageViewerDoc::Serialize(CArchive& ar)
{
    BYTE ID[] = "Image Viewer";
    volatile bool Stop = false;
    CProgressDialog Dlg;

    if (ar.IsStoring())
    {    // storing code
        ar.Write(ID, sizeof(ID));

        UINT count = Images.size();
        ar << count;

        CString Format;
        Format.LoadString(IDS_SAVINGIMAGE);

        Dlg.Create(AfxGetMainWnd(), ar.GetFile()->GetFileName(), Format, count, &Stop);

        for (UINT x = 0; x < count && !Stop; ++x)
        {
            CImageData *pData = GetImageData(x);
            if (pData)
            {
                pData->SaveData(ar);
            }
            else
            {
                Stop = true;
            }
            Dlg.Stepit();
        }
    }
    else
    {    // loading code
        Caption = ar.GetFile()->GetFileName();
        UINT count = 1;

        BYTE TempID[13] = {0};
        if (13 != ar.Read(TempID, 13) || memcmp(TempID, ID, 13) != 0)
        {
            // not an Image Viewer Data (*.ivd) file
            if (LoadImageFile(ar.GetFile()->GetFilePath()))
            {
                // loaded an image file
                return;
            }

            AfxThrowArchiveException(CArchiveException::badIndex); // Unexpected file format
        }

        ar >> count;

        ULONGLONG FileSize = ar.GetFile()->GetLength();
        if (FileSize + count * sizeof(CImageData) + CImageData::GetMemUsage() > theApp.MaximumMemoryUsage * 1024)
        {
            Stop = true;
        }
        else
        {
            CString Format;
            Format.LoadString(IDS_LOADINGIMAGE);

            Dlg.Create(AfxGetMainWnd(), ar.GetFile()->GetFileName(), Format, count, &Stop);

            Images.reserve(count);

            CImageData ImageData;
            for (UINT x = 0; x < count && !Stop; ++x)
            {
                if (ImageData.ReadData(ar))
                {
                    Images.push_back(ImageData);
                }
                else
                {
                    Stop = true;
                }
                Dlg.Stepit();
            }
        }
    }

    if (Stop)
    {
        // Throwing an exception here causes CDocument::OnSaveDocument()
        // to return FALSE which then causes CDocument::DoSave() to
        // delete the partially written file.
        //
        // Throwing an exception here causes CDocument::OnOpenDocument()
        // to remove the partially loaded contents and return FALSE
        // which then causes CMultiDocTemplate::OnOpenDocumentFile()
        // to close the frame window holding the new document view.
        AfxThrowArchiveException(CArchiveException::none);
    }
}

void CImageViewerDoc::DeleteContents()
{
    if (!Images.empty())
    {
        while (GetQueueStatus(QS_PAINT))
        {
            // if the user has closed a view window this allows
            // the main window to totally redraw itself before
            // we start a potentially lengthy delete operation
            theApp.PumpMessage();
        }

        CBusyCursor Wait(IDS_WAITDELETE);
        while (Images.size() > 500)
        {
            // by erasing only 500 images at a time the memory usage
            // indicator on the status bar can be animated
            Images.erase(Images.begin(), Images.begin() + 500);
            theApp.OnIdle(-1);
        }
        Images.clear();
        theApp.OnIdle(-1);
        if (CImageData::GetMemUsage() < theApp.MaximumMemoryUsage * 1024)
        {
            theApp.m_pMainWnd->PostMessage(WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE, 0);
            theApp.MemoryEvent.SetEvent();
        }
    }
}

void CImageViewerDoc::OnFileSaveAs()
{
    theApp.ModalDialogEvent.ResetEvent();
    CDocument::OnFileSaveAs();
    theApp.ModalDialogEvent.SetEvent();
}

void CImageViewerDoc::OnUpdateFileSaveAs(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(!IsImageFile);
}

bool CImageViewerDoc::LoadImageFile(CString FilePath)
{

	vgKernel::StreamReaderPtr stream = 
		vgKernel::StreamReaderFactory::createFromFile( FilePath.GetBuffer(0) );

	vgTerritory::VgtrFilePtr vgtr( new vgTerritory::VgtrFile );

	bool readok = vgtr->readFromStream( stream );
	if ( readok == false )
	{
		return false;
	}


	LoadLodImageFile( vgtr , VGLOD_CLEAR );

	return true;


    bool ret = false;

#if !defined NO_GDIPLUS
    //Gdiplus::Bitmap Image(static_cast<LPCWSTR>(CT2W(FilePath)));

	//////////////////////////////////////////////////////////////////////////

	vgKernel::StreamReaderPtr pstream = 
		vgKernel::StreamReaderFactory::createFromFile( FilePath.GetBuffer(0) );

	vgTerritory::VgtrFilePtr pvgtr( new vgTerritory::VgtrFile );

	bool read_ok = pvgtr->readFromStream( pstream );
	if ( read_ok == false )
	{
		return false;
	}

	vgTerritory::VgtrHeaderPtr header = pvgtr->_headerPtr;
	float* data = pvgtr->_dataLod[VGLOD_CLEAR];

	//------------------------------------------
	// 申请图像的内存并赋值
	//------------------------------------------
	uchar* imgdata = new uchar[ header->xNum * header->zNum * 3 ];
	uchar tmp;
	for ( int i = 0 ; i < header->xNum * header->zNum ; ++ i )
	{
		tmp = data[i] * 255;
		imgdata[ 3 * i ] = tmp;
		imgdata[ 3 * i + 1 ] = tmp;
		imgdata[ 3 * i + 2 ] = tmp;
	}



	Gdiplus::Bitmap Image( header->xNum , header->zNum , 
		3 * header->xNum , PixelFormat24bppRGB , (BYTE*)imgdata );

	//////////////////////////////////////////////////////////////////////////

    if (Gdiplus::Ok == Image.GetLastStatus())
    {
        GUID DimensionID;
        Image.GetFrameDimensionsList(&DimensionID, 1);
        UINT Frames = Image.GetFrameCount(&DimensionID);

        CBrush Background(static_cast<COLORREF>(AfxGetMainWnd()->SendMessage(WMU_GETBGCOLOUR, 0, 0)));

        for (UINT CurrentFrame = 0; CurrentFrame < Frames; ++CurrentFrame)
        {
            if (Gdiplus::Ok == Image.SelectActiveFrame(&DimensionID, CurrentFrame))
            {
                CRect Size(0, 0, Image.GetWidth(), Image.GetHeight());
                pja::CBitmap Bitmap(NULL, Size.right, Size.bottom);
                if (NULL == Bitmap)
                {
                    // Unable to create a memory bitmap
                    AfxThrowResourceException();
                }

                pja::CCompatibleDC dc;
                SelectObject(dc, Bitmap);
                FillRect(dc, &Size, Background);

                Gdiplus::Graphics Graphics(dc);
                if (Gdiplus::Ok == Graphics.DrawImage(&Image, 0, 0, Size.right, Size.bottom))
                {
                    Gdiplus::PixelFormat PixelFormat = Image.GetPixelFormat();
                    WORD Bits = 0;
                    switch (PixelFormat)
                    {
                    case PixelFormat1bppIndexed :
                        Bits = 1;
                        break;
                    case PixelFormat4bppIndexed :
                        Bits = 4;
                        break;
                    case PixelFormat8bppIndexed :
                        Bits = 8;
                        break;
                    case PixelFormat16bppARGB1555 :
                    case PixelFormat16bppGrayScale :
                    case PixelFormat16bppRGB555 :
                    case PixelFormat16bppRGB565 :
                        Bits = 16;
                        break;
                    case PixelFormat24bppRGB :
                        Bits = 24;
                        break;
                    case PixelFormat32bppARGB :
                    case PixelFormat32bppPARGB :
                    case PixelFormat32bppRGB :
                        Bits = 32;
                        break;
                    case PixelFormat48bppRGB :
                        Bits = 48;
                        break;
                    case PixelFormat64bppARGB :
                    case PixelFormat64bppPARGB :
                        Bits = 64;
                    }

                    CImageData ImageData(Bitmap, Bits);
                    Images.push_back(ImageData);
                    IsImageFile = true;
                    ret = true;
                }
            }
        }
    }
#endif
    
    return ret;
}

bool CImageViewerDoc::LoadLodImageFile( const vgTerritory::VgtrFilePtr vgtr ,
									   const long& lod )
{
	bool ret = false;

#if !defined NO_GDIPLUS
	//Gdiplus::Bitmap Image(static_cast<LPCWSTR>(CT2W(FilePath)));

	//////////////////////////////////////////////////////////////////////////

	vgTerritory::VgtrHeaderPtr header = vgtr->_headerPtr;

	float* data = vgtr->_dataLod[ lod ];

	//------------------------------------------
	// 申请图像的内存并赋值
	//------------------------------------------
	long ttt = pow( 2.0f , 2 - lod );

	long w = header->xNum / ttt;
	long h = header->zNum / ttt;

	uchar* imgdata = new uchar[ w * h * 3 ];
	uchar tmp;
	for ( int i = 0 ; i < w * h ; ++ i )
	{
		tmp = data[i] * 255;
		imgdata[ 3 * i ] = tmp;
		imgdata[ 3 * i + 1 ] = tmp;
		imgdata[ 3 * i + 2 ] = tmp;
	}



	Gdiplus::Bitmap Image( w , h, 
		3 *w , PixelFormat24bppRGB , (BYTE*)imgdata );

	//////////////////////////////////////////////////////////////////////////

	if (Gdiplus::Ok == Image.GetLastStatus())
	{
		GUID DimensionID;
		Image.GetFrameDimensionsList(&DimensionID, 1);
		UINT Frames = Image.GetFrameCount(&DimensionID);

		CBrush Background(static_cast<COLORREF>(AfxGetMainWnd()->SendMessage(WMU_GETBGCOLOUR, 0, 0)));

		for (UINT CurrentFrame = 0; CurrentFrame < Frames; ++CurrentFrame)
		{
			if (Gdiplus::Ok == Image.SelectActiveFrame(&DimensionID, CurrentFrame))
			{
				CRect Size(0, 0, Image.GetWidth(), Image.GetHeight());
				pja::CBitmap Bitmap(NULL, Size.right, Size.bottom);
				if (NULL == Bitmap)
				{
					// Unable to create a memory bitmap
					AfxThrowResourceException();
				}

				pja::CCompatibleDC dc;
				SelectObject(dc, Bitmap);
				FillRect(dc, &Size, Background);

				Gdiplus::Graphics Graphics(dc);
				if (Gdiplus::Ok == Graphics.DrawImage(&Image, 0, 0, Size.right, Size.bottom))
				{
					Gdiplus::PixelFormat PixelFormat = Image.GetPixelFormat();
					WORD Bits = 0;
					switch (PixelFormat)
					{
					case PixelFormat1bppIndexed :
						Bits = 1;
						break;
					case PixelFormat4bppIndexed :
						Bits = 4;
						break;
					case PixelFormat8bppIndexed :
						Bits = 8;
						break;
					case PixelFormat16bppARGB1555 :
					case PixelFormat16bppGrayScale :
					case PixelFormat16bppRGB555 :
					case PixelFormat16bppRGB565 :
						Bits = 16;
						break;
					case PixelFormat24bppRGB :
						Bits = 24;
						break;
					case PixelFormat32bppARGB :
					case PixelFormat32bppPARGB :
					case PixelFormat32bppRGB :
						Bits = 32;
						break;
					case PixelFormat48bppRGB :
						Bits = 48;
						break;
					case PixelFormat64bppARGB :
					case PixelFormat64bppPARGB :
						Bits = 64;
					}

					CImageData ImageData(Bitmap, Bits);
					Images.push_back(ImageData);
					IsImageFile = true;
					ret = true;
				}
			}
		}
	}
#endif

	return ret;
}