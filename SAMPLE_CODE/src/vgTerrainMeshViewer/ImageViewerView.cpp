/****************************************************************************
ImageViewerView.cpp : Implementation file for the CImageViewerView class
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
#include "ImageViewerView.h"
#include "MainFrm.h"
#include "WindowScroller.h"
#include "SelectImageDialog.h"
#include "DeleteImageDialog.h"
#include "BitmapInfoHeader.h"

#include "pja_bitmap.h"
#include "pja_dc.h"
#include "pja_format.h"

#include <math.h>

//#define ACTIVATE_VIEWER
#include <ImageViewer.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// When the user presses the left mouse button down and
// then moves the mouse cursor to an edge of the view the
// view will scroll. These defines are for that scrolling.
#define AUTOSCROLLTIMERID       0xFEB11965              // Timer ID
#define AUTOSCROLLTIMERSPEED    USER_TIMER_MINIMUM      // Timer and scrolling speed
#define AUTOSCROLLBORDER        4                       // pixels from edge within which scrolling is active

// Mouse gesture IDs
#define GESTUREUP               0x01
#define GESTUREDOWN             0x02
#define GESTURELEFT             0x03
#define GESTURERIGHT            0x04

// CImageViewerView

IMPLEMENT_DYNCREATE(CImageViewerView, CScrollView)

BEGIN_MESSAGE_MAP(CImageViewerView, CScrollView)
    ON_WM_ERASEBKGND()
    ON_WM_HSCROLL()
    ON_WM_KEYDOWN()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_MOUSEWHEEL()
    ON_WM_SETFOCUS()
    ON_WM_SIZE()
    ON_WM_TIMER()
    ON_WM_VSCROLL()

    ON_MESSAGE(WMU_GETPOINTDATA, &CImageViewerView::OnGetPointData)
    ON_REGISTERED_MESSAGE(WMU_MOUSEGESTURE, &CImageViewerView::OnMouseGesture)

    ON_COMMAND(ID_IMAGE_FIRST, &CImageViewerView::OnImageFirst)
    ON_UPDATE_COMMAND_UI(ID_IMAGE_FIRST, &CImageViewerView::OnUpdateImageFirst)

    ON_COMMAND(ID_IMAGE_PREVIOUS, &CImageViewerView::OnImagePrevious)
    ON_UPDATE_COMMAND_UI(ID_IMAGE_PREVIOUS, &CImageViewerView::OnUpdateImagePrevious)

    ON_COMMAND(ID_IMAGE_SELECT, &CImageViewerView::OnImageSelect)
    ON_UPDATE_COMMAND_UI(ID_IMAGE_SELECT, &CImageViewerView::OnUpdateImageSelect)

    ON_COMMAND(ID_IMAGE_NEXT, &CImageViewerView::OnImageNext)
    ON_UPDATE_COMMAND_UI(ID_IMAGE_NEXT, &CImageViewerView::OnUpdateImageNext)

    ON_COMMAND(ID_IMAGE_LAST, &CImageViewerView::OnImageLast)
    ON_UPDATE_COMMAND_UI(ID_IMAGE_LAST, &CImageViewerView::OnUpdateImageLast)

    ON_COMMAND(ID_ZOOM_ZOOMIN, &CImageViewerView::OnZoomZoomIn)
    ON_UPDATE_COMMAND_UI(ID_ZOOM_ZOOMIN, &CImageViewerView::OnUpdateZoomZoomIn)

    ON_COMMAND(ID_ZOOM_ZOOMOUT, &CImageViewerView::OnZoomZoomOut)
    ON_UPDATE_COMMAND_UI(ID_ZOOM_ZOOMOUT, &CImageViewerView::OnUpdateZoomZoomOut)

    ON_COMMAND(ID_ZOOM_GRID, &CImageViewerView::OnZoomGrid)
    ON_UPDATE_COMMAND_UI(ID_ZOOM_GRID, &CImageViewerView::OnUpdateZoomGrid)

    ON_COMMAND(ID_IMAGE_DELETE, &CImageViewerView::OnImageDelete)
    ON_UPDATE_COMMAND_UI(ID_IMAGE_DELETE, &CImageViewerView::OnUpdateImageDelete)

    ON_COMMAND(ID_VIEW_CENTER_MOUSE, &CImageViewerView::OnViewCenterMouse)
    ON_UPDATE_COMMAND_UI(ID_VIEW_CENTER_MOUSE, &CImageViewerView::OnUpdateViewCenterMouse)

#if !defined NO_GDIPLUS
    ON_COMMAND(ID_IMAGE_SAVE, &CImageViewerView::OnImageSave)
    ON_UPDATE_COMMAND_UI(ID_IMAGE_SAVE, &CImageViewerView::OnUpdateImageSave)
#endif // #if !defined NO_GDIPLUS

END_MESSAGE_MAP()

// supported zoom ratios in percentage. feel free to add or remove from this list.
// As of version 2.3 any zoom ratios over 100% have to be multiples of 100. The new
// drawing code is kind of screwy at other zoom ratios as I have problems synchronizing
// the grid lines and pixel borders.
const LONG ZoomRatios[] = { 1, 5, 10, 25, 50, 75, 100, 200, 300, 400, 500, 700, 1000, 1200, 1500, 2000, 3500, 5000 };

// CImageViewerView construction/destruction

CImageViewerView::CImageViewerView()
: CurrentImage(0xffffffff)  // ensure an invalid value
, CurrentZoomRatio(6)       // 100%
, ViewGrid(false)
, AutoScrollTimer(false)
, LButtonDown(false)
, ZoomedBitmapRect(0, 0, 0, 0)
{
#ifdef _DEBUG
    // check the values in the ZoomRatios array
    // must be >0 and in ascending order
    // any magnification must be a multiple of 100
    size_t CountOfZoomRatios = _countof(ZoomRatios);
    ASSERT(CountOfZoomRatios > 0);
    ASSERT(CurrentZoomRatio >= 0);
    ASSERT(CurrentZoomRatio < CountOfZoomRatios);
    ASSERT(100 == ZoomRatios[CurrentZoomRatio]);

    for (size_t counter = 0; counter < CountOfZoomRatios; ++counter)
    {
        ASSERT(ZoomRatios[counter] > 0);

        if (counter > 0)
        {
            ASSERT(ZoomRatios[counter] > ZoomRatios[counter - 1]);
        }
        
        if (ZoomRatios[counter] > 100)
        {
            ASSERT(0 == ZoomRatios[counter] % 100);
        }
    }
#endif
}

CImageViewerView::~CImageViewerView()
{
}

BOOL CImageViewerView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return CScrollView::PreCreateWindow(cs);
}

// CImageViewerView drawing

void CImageViewerView::OnDraw(CDC* pDC)
{
    CRect ClipBox;
    if (ZoomedBitmapRect.IsRectEmpty())
    {
        GetClientRect(ClipBox);
    }
    else
    {
        pDC->GetClipBox(ClipBox);
    }

    if (ClipBox.IsRectEmpty())
    {
        return;
    }

    // Create a NULL pen and pattern brush for drawing the grid lines
    CPen Pen(PS_NULL, 1, RGB(0, 0, 0));
    CBitmap GridBitmap;
    GridBitmap.LoadBitmap(IDB_GRIDBRUSH);
    CBrush Brush(&GridBitmap);

    // create a double buffer dc and bitmap the size of the clipbox
    // The dc must be created after any GDI objects that are selected into it
    pja::CBitmap DoubleBufferBitmap(*pDC, ClipBox.Width(), ClipBox.Height());
    pja::CCompatibleDC DoubleBufferDC(*pDC);

    // Select the GDI objects into the double buffer DC
    // These are cleaned up automatically in the CCompatibleDC's d'tor
    SelectObject(DoubleBufferDC, DoubleBufferBitmap);
    SelectObject(DoubleBufferDC, Pen);
    SelectObject(DoubleBufferDC, Brush);


    // fill the double buffer dc with the background colour
    COLORREF BackGround = static_cast<COLORREF>(AfxGetMainWnd()->SendMessage(WMU_GETBGCOLOUR, 0, 0));
    CBrush BackgroundBrush(BackGround);
    FillRect(DoubleBufferDC, CRect(0, 0, ClipBox.Width(), ClipBox.Height()), BackgroundBrush);

    if (ZoomedBitmapRect.IsRectEmpty())
    {
        // no bitmap, display error text
        CString ErrorText;
        ErrorText.LoadString(IDS_NOIMAGE);
        BackGround = (GetRValue(BackGround) * 299 + GetGValue(BackGround) * 587 + GetBValue(BackGround) * 114) > 105000 ? RGB(0, 0, 0) : RGB(255, 255, 255);
        SetTextColor(DoubleBufferDC, BackGround);
        SetBkMode(DoubleBufferDC, TRANSPARENT);
        DrawText(DoubleBufferDC, ErrorText, -1, ClipBox, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
    else
    {
        bool ShowGrid = ViewGrid && ZoomRatios[CurrentZoomRatio] > 199;
        bool ShowOutline = ViewGrid && ZoomRatios[CurrentZoomRatio] < 200;

        // do the clip box and bitmap area intersect?
        CRect IntersectRect = ZoomedBitmapRect & ClipBox;
        if (!IntersectRect.IsRectEmpty())
        {
            // yes they do, calculate what area of the bitmap needs to be drawn, and where in the clipbox to draw it
            int to_x = ClipBox.left > ZoomedBitmapRect.left ? 0 : ZoomedBitmapRect.left - ClipBox.left;
            int to_y = ClipBox.top > ZoomedBitmapRect.top ? 0 : ZoomedBitmapRect.top - ClipBox.top;

            CRect FromRect(GetPixelFromPoint(IntersectRect.TopLeft()), GetPixelFromPoint(IntersectRect.BottomRight()));
            // so we do not clip the right and bottom sides
            FromRect.InflateRect(0, 0, 1, 1);

            if (ZoomRatios[CurrentZoomRatio] > 100)
            {
                // ensure placement of the left and top pixels
                // TODO: This is where I have problems with zoom ratios that are not
                // multiples of 100. Depending on what the ratio is and which pixel falls
                // on the left side of the clipbox I can not coordinate this clipped area
                // and the grid lines with the StretchBlt() drawing of the original full
                // image. I can end up being out by a single pixel, plus or minus.
                if (0 == to_x)
                {
                    to_x = ZoomedBitmapRect.left - ClipBox.left + FromRect.left * ZoomRatios[CurrentZoomRatio] / 100;
                }

                if (0 == to_y)
                {
                    to_y = ZoomedBitmapRect.top - ClipBox.top + FromRect.top * ZoomRatios[CurrentZoomRatio] / 100;
                }
            }

            int to_w = FromRect.Width() * ZoomRatios[CurrentZoomRatio] / 100;
            int to_h = FromRect.Height() * ZoomRatios[CurrentZoomRatio] / 100;

            pja::CCompatibleDC CurrentBitmapDC;
            SelectObject(CurrentBitmapDC, CurrentBitmap);

            SetStretchBltMode(DoubleBufferDC, ZoomRatios[CurrentZoomRatio] < 100 ? HALFTONE : COLORONCOLOR);

            StretchBlt(DoubleBufferDC,
                       to_x, to_y, to_w, to_h,
                       CurrentBitmapDC,
                       FromRect.left, FromRect.top, FromRect.Width(), FromRect.Height(),
                       SRCCOPY);

            if (ShowGrid)
            {
                // Draw the grid lines
                SetStretchBltMode(DoubleBufferDC, HALFTONE); // see MSDN for SetBrushOrgEx()
                SetBrushOrgEx(DoubleBufferDC, ClipBox.left % 8, ClipBox.top % 8, NULL);

                // vertical
                CRect rc;
                rc.top = IntersectRect.top - ClipBox.top;
                rc.bottom = rc.top + IntersectRect.Height();
                if (IntersectRect.bottom <= ZoomedBitmapRect.bottom)
                {
                    ++rc.bottom;
                }

                for (int x = to_x * 100; x < (to_x + to_w) * 100; x += ZoomRatios[CurrentZoomRatio])
                {
                    rc.left = x / 100 - 1;
                    rc.right = rc.left + 2;
                    Rectangle(DoubleBufferDC, rc.left, rc.top, rc.right, rc.bottom);
                }

                // horizontal
                rc.left = IntersectRect.left - ClipBox.left;
                rc.right = rc.left + IntersectRect.Width();
                if (IntersectRect.right <= ZoomedBitmapRect.right)
                {
                    ++rc.right;
                }

                for (int y = to_y * 100; y < (to_y + to_h) * 100; y += ZoomRatios[CurrentZoomRatio])
                {
                    rc.top = y / 100 - 1;
                    rc.bottom = rc.top + 2;
                    Rectangle(DoubleBufferDC, rc.left, rc.top, rc.right, rc.bottom);
                }
            }
        }

        if (ShowGrid || ShowOutline)
        {
            // draw the outline
            SetStretchBltMode(DoubleBufferDC, HALFTONE); // see MSDN for SetBrushOrgEx()
            SetBrushOrgEx(DoubleBufferDC, ClipBox.left % 8, ClipBox.top % 8, NULL);

            // The outline is drawn around the outside of the image, not over top of it.
            // With the grid the first left and top lines are also drawn outside the image, but
            // the last right and bottom grid lines are drawn on the image.
            CRect OutlineRect(ZoomedBitmapRect);
            OutlineRect.InflateRect(1, 1, 1, 1);
            IntersectRect = OutlineRect & ClipBox;
            if (!IntersectRect.IsRectEmpty())
            {
                CRect rc;
                rc.top = IntersectRect.top - ClipBox.top;
                rc.bottom = rc.top + IntersectRect.Height();
                if (ShowOutline)
                {
                    ++rc.bottom;
                }

                if (ClipBox.left <= ZoomedBitmapRect.left && ClipBox.right >= ZoomedBitmapRect.left)
                {
                    // Draw the left grid line
                    rc.right = ZoomedBitmapRect.left - ClipBox.left + 1;
                    rc.left = rc.right - 2;
                    Rectangle(DoubleBufferDC, rc.left, rc.top, rc.right, rc.bottom);
                }   

                if (ShowOutline && ClipBox.left <= ZoomedBitmapRect.right && ClipBox.right >= ZoomedBitmapRect.right)
                {
                    // Draw the right grid line
                    rc.right = ZoomedBitmapRect.right - ClipBox.left + 2;
                    rc.left = rc.right - 2;
                    Rectangle(DoubleBufferDC, rc.left, rc.top, rc.right, rc.bottom);
                }

                rc.left = IntersectRect.left - ClipBox.left;
                rc.right = rc.left + IntersectRect.Width();
                if (ShowOutline)
                {
                    ++rc.right;
                }

                if (ClipBox.top <= ZoomedBitmapRect.top && ClipBox.bottom >= ZoomedBitmapRect.top)
                {
                    // Draw the top grid line
                    rc.bottom = ZoomedBitmapRect.top - ClipBox.top + 1;
                    rc.top = rc.bottom - 2;
                    Rectangle(DoubleBufferDC, rc.left, rc.top, rc.right, rc.bottom);
                }

                if (ShowOutline && ClipBox.top <= ZoomedBitmapRect.bottom && ClipBox.bottom >= ZoomedBitmapRect.bottom)
                {
                    // Draw the bottom grid line
                    rc.bottom = ZoomedBitmapRect.bottom - ClipBox.top + 2;
                    rc.top = rc.bottom - 2;
                    Rectangle(DoubleBufferDC, rc.left, rc.top, rc.right, rc.bottom);
                }
            }
        }
    }

    //ShowGraphic(DoubleBufferDC);

    // now copy the double buffer dc to the screen
    BitBlt(*pDC,
           ClipBox.left, ClipBox.top, ClipBox.Width(), ClipBox.Height(),
           DoubleBufferDC,
           0, 0,
           SRCCOPY);
}

BOOL CImageViewerView::OnEraseBkgnd(CDC*)
{
    return TRUE;
}

void CImageViewerView::OnInitialUpdate()
{
    SetScrollSizes(MM_TEXT, CSize(0, 0));

    MouseGesture.Attach(*this, 20);
    CMouseGesture::Motion Up[] = {CMouseGesture::RightButton, CMouseGesture::Up};
    CMouseGesture::Motion Down[] = {CMouseGesture::RightButton, CMouseGesture::Down};
    CMouseGesture::Motion Left[] = {CMouseGesture::RightButton, CMouseGesture::Left};
    CMouseGesture::Motion Right[] = {CMouseGesture::RightButton, CMouseGesture::Right};

    MouseGesture.AddGesture(GESTUREUP, Up, _countof(Up));
    MouseGesture.AddGesture(GESTUREDOWN, Down, _countof(Down));
    MouseGesture.AddGesture(GESTURELEFT, Left, _countof(Left));
    MouseGesture.AddGesture(GESTURERIGHT, Right, _countof(Right));

    OnUpdate(NULL, 0xfeb1, NULL);
}


// CImageViewerView diagnostics

#ifdef _DEBUG
void CImageViewerView::AssertValid() const
{
    CScrollView::AssertValid();
}

void CImageViewerView::Dump(CDumpContext& dc) const
{
    CScrollView::Dump(dc);
}

CImageViewerDoc* CImageViewerView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageViewerDoc)));
    return (CImageViewerDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageViewerView message handlers

bool CImageViewerView::SetCurrentImage(size_t nImage, bool PassLock)
{
    CImageViewerDoc *pDoc = GetDocument();

    // First make sure nImage is in range
    if (NULL != pDoc && nImage < pDoc->GetImageDataCount())
    {
        // Is the display locked? Can we get past it?
        if (PassLock || !AfxGetMainWnd()->SendMessage(WMU_GETDISPLAYLOCK, 0, 0))
        {
            // clean up the old bitmap
            CurrentBitmap.DeleteObject();
            ZoomedBitmapRect.SetRectEmpty();
            CurrentImage = nImage;
            GetParent()->SendMessage(WMU_SETMESSAGETEXT, 0, 0);

            // and get the data for the new one
            CImageData *pData = pDoc->GetImageData(CurrentImage);
            if (NULL != pData)
            {
                CurrentBitmap = pja::CBitmap(pData->GetBitmap());
                CSize Size;
                Size.cx = CurrentBitmap.Width() * ZoomRatios[CurrentZoomRatio] / 100;
                Size.cy = CurrentBitmap.Height() * ZoomRatios[CurrentZoomRatio] / 100;

                long LineSize = ZoomRatios[CurrentZoomRatio] / 100;
                if (LineSize < 1)
                    LineSize = 1;

                SetScrollSizes(MM_TEXT, Size, sizeDefault, CSize(LineSize, LineSize));

                // center the bitmap on the view if the bitmap is smaller than the view
                ZoomedBitmapRect.SetRect(0, 0, Size.cx, Size.cy);
                CalcBitmapRect();

                GetParent()->SendMessage(WMU_SETMESSAGETEXT,
                                         0,
                                         reinterpret_cast<LPARAM>(pDoc->GetImageData(CurrentImage)));
                AfxGetMainWnd()->SendMessage(WMU_UPDATETOOLTIP,
                                             reinterpret_cast<WPARAM>(this), 0);
                AfxGetMainWnd()->SendMessage(WMU_SETPROPERTIES,
                                             reinterpret_cast<WPARAM>(GetParent()),
                                             reinterpret_cast<LPARAM>(pDoc->GetImageData(CurrentImage)));
            }
        }
    }

    // force the view window to refresh
    Invalidate();
    SetCaption();
    return true;
}

void CImageViewerView::SetCaption()
{
    // set the view's caption bar text
    CImageViewerDoc *pDoc = GetDocument();
    pja::CFormat cf;
    GetParent()->SetWindowText(cf.MakeMessage(NULL,
                                              IDS_CAPTION,
                                              4,
                                              pDoc->GetCaption(),
                                              cf.TS(CurrentImage + 1),
                                              cf.TS(pDoc->GetImageDataCount()),
                                              cf.TS(ZoomRatios[CurrentZoomRatio])).c_str());
}

void CImageViewerView::OnImageFirst()
{
    bool locked = AfxGetMainWnd()->SendMessage(WMU_GETDISPLAYLOCK, 0, 0) != 0;
    if (!locked)
    {
        AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_VIEW_DISPLAY_LOCK, 0);
        AfxGetApp()->OnIdle(-1);
    }
    SetCurrentImage(0, true);
}

void CImageViewerView::OnUpdateImageFirst(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(CurrentImage != 0);
}

void CImageViewerView::OnImagePrevious()
{
    bool locked = AfxGetMainWnd()->SendMessage(WMU_GETDISPLAYLOCK, 0, 0) != 0;
    if (!locked)
    {
        AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_VIEW_DISPLAY_LOCK, 0);
        AfxGetApp()->OnIdle(-1);
    }
    SetCurrentImage(CurrentImage - 1, true);
}

void CImageViewerView::OnUpdateImagePrevious(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(CurrentImage != 0);
}

void CImageViewerView::OnImageSelect()
{
    CImageViewerDoc *pDoc = GetDocument();
    if (pDoc)
    {
        bool locked = AfxGetMainWnd()->SendMessage(WMU_GETDISPLAYLOCK, 0, 0) != 0;
        if (!locked)
        {
            AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_VIEW_DISPLAY_LOCK, 0);
            AfxGetApp()->OnIdle(-1);
        }
        CSelectImageDialog Dlg(this);
        Dlg.m_Image = (UINT)CurrentImage + 1;
        Dlg.m_MaxImage = (UINT)pDoc->GetImageDataCount();
        if (Dlg.DoModal() == IDOK)
        {
            SetCurrentImage(Dlg.m_Image - 1, true);
        }
        else if (!locked)
        {
            AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_VIEW_DISPLAY_LOCK, 0);
        }
    }
}

void CImageViewerView::OnUpdateImageSelect(CCmdUI *pCmdUI)
{
    bool Enable = false;
    CImageViewerDoc *pDoc = GetDocument();
    if (pDoc)
    {
        Enable = pDoc->GetImageDataCount() > 1;
    }

    pCmdUI->Enable(Enable);
}

void CImageViewerView::OnImageNext()
{
    bool locked = AfxGetMainWnd()->SendMessage(WMU_GETDISPLAYLOCK, 0, 0) != 0;
    if (!locked)
    {
        AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_VIEW_DISPLAY_LOCK, 0);
        AfxGetApp()->OnIdle(-1);
    }

    SetCurrentImage(CurrentImage + 1, true);
}

void CImageViewerView::OnUpdateImageNext(CCmdUI *pCmdUI)
{
    bool Enable = false;
    CImageViewerDoc *pDoc = GetDocument();
    if (pDoc)
    {
        Enable = pDoc->GetImageDataCount() > CurrentImage + 1;
    }

    pCmdUI->Enable(Enable);
}

void CImageViewerView::OnImageLast()
{
    bool locked = AfxGetMainWnd()->SendMessage(WMU_GETDISPLAYLOCK, 0, 0) != 0;
    if (!locked)
    {
        AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_VIEW_DISPLAY_LOCK, 0);
        AfxGetApp()->OnIdle(-1);
    }
    CImageViewerDoc *pDoc = GetDocument();
    if (pDoc)
    {
        SetCurrentImage(pDoc->GetImageDataCount() - 1, true);
    }
}

void CImageViewerView::OnUpdateImageLast(CCmdUI *pCmdUI)
{
    bool Enable = false;
    CImageViewerDoc *pDoc = GetDocument();
    if (pDoc)
    {
        Enable = pDoc->GetImageDataCount() > CurrentImage + 1;
    }

    pCmdUI->Enable(Enable);
}

void CImageViewerView::OnZoomZoomIn()
{
    if (CurrentZoomRatio < _countof(ZoomRatios) - 1)
    {
        SetRedraw(FALSE);
        CPoint Cursor;
        GetCursorPos(&Cursor);
        CPoint Pixel(-1, -1);
        if (GetVisibleRect().PtInRect(Cursor))
        {
            ScreenToClient(&Cursor);
            Pixel = GetPixelFromPoint(Cursor, false);
        }

        ++CurrentZoomRatio;
        SetCurrentImage(CurrentImage, true);

        MovePixelToPoint(Pixel, Cursor);
        SetRedraw(TRUE);
        RedrawWindow();
    }
}

void CImageViewerView::OnUpdateZoomZoomIn(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(CurrentZoomRatio < _countof(ZoomRatios) - 1);
}

void CImageViewerView::OnZoomZoomOut()
{
    if (CurrentZoomRatio > 0)
    {
        SetRedraw(FALSE);
        CPoint Cursor;
        GetCursorPos(&Cursor);
        CPoint Pixel(-1, -1);
        if (GetVisibleRect().PtInRect(Cursor))
        {
            ScreenToClient(&Cursor);
            Pixel = GetPixelFromPoint(Cursor, false);
        }

        --CurrentZoomRatio;
        SetCurrentImage(CurrentImage, true);

        MovePixelToPoint(Pixel, Cursor);
        SetRedraw(TRUE);
        RedrawWindow();
    }
}

void CImageViewerView::OnUpdateZoomZoomOut(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(CurrentZoomRatio > 0);
}

// When zooming in or out this keeps the same image pixel centered under the mouse cursor
void CImageViewerView::MovePixelToPoint(CPoint Pixel, CPoint Client)
{
    // Pixel - The pixel that you want at the supplied point
    // Client - The point, in the view's client coords, where you want the supplied pixel
    if (PtInRect(CurrentBitmap.Rect(), Pixel))
    {
        CPoint CurrentPosition = GetDeviceScrollPosition();
        CPoint CurrentPixel = GetPixelFromPoint(Client, false);
        CurrentPosition.x += (Pixel.x - CurrentPixel.x) * ZoomRatios[CurrentZoomRatio] / 100;
        if (ZoomRatios[CurrentZoomRatio] > 200)
        {
            long left = Pixel.x * ZoomRatios[CurrentZoomRatio] / 100 - CurrentPosition.x;
            long diff = Client.x - left;
            CurrentPosition.x -= diff;
            CurrentPosition.x += ZoomRatios[CurrentZoomRatio] / 200;
        }

        CurrentPosition.y += (Pixel.y - CurrentPixel.y) * ZoomRatios[CurrentZoomRatio] / 100;
        if (ZoomRatios[CurrentZoomRatio] > 200)
        {
            long top = Pixel.y * ZoomRatios[CurrentZoomRatio] / 100 - CurrentPosition.y;
            long diff = Client.y - top;
            CurrentPosition.y -= diff;
            CurrentPosition.y += ZoomRatios[CurrentZoomRatio] / 200;
        }

        long MaxHorz = 0;
        if (GetStyle() & WS_HSCROLL)
        {
            MaxHorz = GetScrollLimit(SB_HORZ);
        }

        long MaxVert = 0;
        if (GetStyle() & WS_VSCROLL)
        {
            MaxVert = GetScrollLimit(SB_VERT);
        }

        if (CurrentPosition.x < 0)
        {
            CurrentPosition.x = 0;
        }
        if (CurrentPosition.x > MaxHorz)
        {
            CurrentPosition.x = MaxHorz;
        }
        if (CurrentPosition.y < 0)
        {
            CurrentPosition.y = 0;
        }
        if (CurrentPosition.y > MaxVert)
        {
            CurrentPosition.y = MaxVert;
        }

        ScrollToPosition(CurrentPosition);
        AfxGetMainWnd()->SendMessage(WMU_UPDATETOOLTIP, (WPARAM)this, 0);
    }
}

void CImageViewerView::OnZoomGrid()
{
    ViewGrid = !ViewGrid;
    SetCurrentImage(CurrentImage, true);
}

void CImageViewerView::OnUpdateZoomGrid(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(ViewGrid ? BST_CHECKED : BST_UNCHECKED);
}

void CImageViewerView::OnMButtonDown(UINT, CPoint point)
{
    try
    {
        new pja::CWindowScroller(this, point);
    }

    catch (CMemoryException *me)
    {
        theApp.MemoryEvent.ResetEvent();
        me->ReportError();
        me->Delete();
    }
}

// Handler for the WMU_GETPOINTDATA message sent by the tooltip
LRESULT CImageViewerView::OnGetPointData(WPARAM, LPARAM lp)
{
    if (!ZoomedBitmapRect.IsRectEmpty())
    {
        CTooltipWindow::PointData *PointData = reinterpret_cast<CTooltipWindow::PointData *>(lp);

        ScreenToClient(&PointData->Point);

        CRect ClientRect;
        GetClientRect(ClientRect);
        if (ClientRect.PtInRect(PointData->Point))
        {
            PointData->Point += GetDeviceScrollPosition();
            if (ZoomRatios[CurrentZoomRatio] > 99 && ZoomedBitmapRect.PtInRect(PointData->Point))
            {
                PointData->Point = GetPixelFromPoint(PointData->Point);
                PointData->Colour = GetPixelColour(PointData->Point);

                if (CLR_NONE != PointData->Colour)
                {
                    // if we are dealing with just a region or one that that has negative coordinates
                    // then adjust the tooltip's reported coordinates to reflect the region
                    CImageData *pImageData = GetDocument()->GetImageData(CurrentImage);
                    CBitmapInfoHeader BitmapInfoHeader(pImageData->GetBitmapInfoHeader());
                    CRect RegionRect(pImageData->GetRegionRect());

                    if (RegionRect.left < 0 || RegionRect.Width() == BitmapInfoHeader.biWidth)
                    {
                        PointData->Point.x += RegionRect.left;
                    }

                    if (RegionRect.top < 0 || RegionRect.Height() == BitmapInfoHeader.biHeight)
                    {
                        PointData->Point.y += RegionRect.top;
                    }
                }
                return 1;
            }
        }
    }

    return 0;
}

// returns the colour of the pixel at the supplied point in the image
COLORREF CImageViewerView::GetPixelColour(CPoint &pt) const
{
    COLORREF ret = CLR_NONE;

    if (pt.x >= 0 && pt.x < CurrentBitmap.Width() && pt.y >= 0 && pt.y < CurrentBitmap.Height())
    {
        pja::CCompatibleDC DC;
        SelectObject(DC, CurrentBitmap);
        ret = GetPixel(DC, pt.x, pt.y);
    }

    return ret;
}

// returns a CPoint that contains the pixel coords that is located
// at the supplied client coords
CPoint CImageViewerView::GetPixelFromPoint(CPoint Point, bool AdjustedForScrolling /* = true */)
{
    CPoint pt;

    if (!AdjustedForScrolling)
    {
        Point += GetDeviceScrollPosition();
    }

    pt.x = (Point.x - ZoomedBitmapRect.left) * 100 / ZoomRatios[CurrentZoomRatio];
    pt.y = (Point.y - ZoomedBitmapRect.top) * 100 / ZoomRatios[CurrentZoomRatio];

    return pt;
}

void CImageViewerView::OnImageDelete()
{
    bool locked = AfxGetMainWnd()->SendMessage(WMU_GETDISPLAYLOCK, 0, 0) != 0;
    if (!locked)
    {
        // temporarily lock the display
        AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_VIEW_DISPLAY_LOCK, 0);
        AfxGetApp()->OnIdle(-1);
    }

    CImageViewerDoc *pDoc = GetDocument();

    CDeleteImageDialog Dlg(this);
    Dlg.To = pDoc->GetImageDataCount() - 1;

    if (Dlg.DoModal() == IDOK)
    {
        while(GetQueueStatus(QS_PAINT))
        {
            // allow main window to redraw to fully remove the dialog
            // before starting a potentially lengthy delete operation
            theApp.PumpMessage();
        }

        switch (Dlg.Selection)
        {
        case 0: // Current image
            pDoc->DeleteImageData(CurrentImage);
            break;

        case 1: // All except current image
            if (0 != CurrentImage)
            {
                pDoc->DeleteImageData(0, CurrentImage - 1);
            }

            pDoc->DeleteImageData(CurrentImage + 1, pDoc->GetImageDataCount());
            break;

        case 2: // All images
            pDoc->DeleteImageData(0, pDoc->GetImageDataCount());
            break;

        case 3: // range of images
            {

                UINT From = min(Dlg.From, Dlg.To);
                UINT To = max(Dlg.From, Dlg.To);
                pDoc->DeleteImageData(From - 1, To - 1);
            }
            break;

        default: // invalid value
            ASSERT(0);
        }
    }

    if (!locked)
    {
        // remove the temporary lock
        AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_VIEW_DISPLAY_LOCK, 0);
    }
}

void CImageViewerView::OnUpdateImageDelete(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(GetDocument()->GetImageDataCount() > 0);
}

void CImageViewerView::OnSetFocus(CWnd* pOldWnd)
{
    CScrollView::OnSetFocus(pOldWnd);

    AfxGetMainWnd()->SendMessage(WMU_SETPROPERTIES,
                                 reinterpret_cast<WPARAM>(GetParent()),
                                 reinterpret_cast<LPARAM>(GetDocument()->GetImageData(CurrentImage)));
}

bool CImageViewerView::MoveCursor(int x, int y)
{
    if (0 == x && 0 == y)
        return false;

    CRect VisibleRect = GetVisibleRect();
    CPoint CursorPos;
    GetCursorPos(&CursorPos);
    if (!VisibleRect.PtInRect(CursorPos))
        return false;

    if (ZoomRatios[CurrentZoomRatio] > 100)
    {
        // convert client coords to pixel coords, advance pixel, convert pixel coords back to client coords
        ScreenToClient(&CursorPos);
        CursorPos += GetDeviceScrollPosition();
        double xpos = floor((CursorPos.x - ZoomedBitmapRect.left) * 100.0 / ZoomRatios[CurrentZoomRatio]) + x;
        CursorPos.x = long(ZoomedBitmapRect.left + ceil(xpos * ZoomRatios[CurrentZoomRatio] / 100.0));
        double ypos = floor((CursorPos.y - ZoomedBitmapRect.top) * 100.0 / ZoomRatios[CurrentZoomRatio]) + y;
        CursorPos.y = long(ZoomedBitmapRect.top + ceil(ypos * ZoomRatios[CurrentZoomRatio] / 100.0));
        CursorPos -= GetDeviceScrollPosition();
        ClientToScreen(&CursorPos);
    }
    else
    {
        CursorPos += CPoint(x, y);
    }

    int bottomrightoffset = (ViewGrid && ZoomRatios[CurrentZoomRatio] > 199) ? 2 : 1;

    if (CursorPos.x > VisibleRect.right - bottomrightoffset)
        CursorPos.x = VisibleRect.right - bottomrightoffset;
    if (CursorPos.x < VisibleRect.left)
        CursorPos.x = VisibleRect.left;

    if (CursorPos.y > VisibleRect.bottom - bottomrightoffset)
        CursorPos.y = VisibleRect.bottom - bottomrightoffset;
    if (CursorPos.y < VisibleRect.top)
        CursorPos.y = VisibleRect.top;

    return CenterCursorOnPixel(CursorPos);
}

bool CImageViewerView::CenterCursorOnPixel(CPoint CursorPos)
{
    CPoint ImagePoint(CursorPos);
    ScreenToClient(&ImagePoint);
    ImagePoint += GetDeviceScrollPosition();
    if (ZoomRatios[CurrentZoomRatio] >= 200)
    {
        // center the mouse cursor on the image pixel
        double pixels = ZoomRatios[CurrentZoomRatio] / 100.0;
        long xpos = long((ImagePoint.x - ZoomedBitmapRect.left) / pixels);
        ImagePoint.x = ZoomedBitmapRect.left + long(xpos * pixels) + long(pixels / 2);
        long ypos = long((ImagePoint.y - ZoomedBitmapRect.top) / pixels);
        ImagePoint.y = ZoomedBitmapRect.top + long(ypos * pixels) + long(pixels / 2);
        ImagePoint -= GetDeviceScrollPosition();
        ClientToScreen(&ImagePoint);
        CursorPos = ImagePoint;
    }

    if (GetVisibleRect().PtInRect(CursorPos))
    {
        SetCursorPos(CursorPos.x, CursorPos.y);
        return true;
    }
    return false;
}

void CImageViewerView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if (IsCTRLpressed())
    {
        if (IsSHIFTpressed() || (nChar != VK_HOME && nChar != VK_END))
        {
            return CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
        }
    }

    UINT Message = IsSHIFTpressed() ? WM_HSCROLL : WM_VSCROLL;
    CPoint CursorPos;
    GetCursorPos(&CursorPos);

    switch (nChar)
    {
    case VK_UP:
        if (IsSCROLLLOCKToggled() ||
            IsSHIFTpressed() ||
            GetScrollPos(SB_VERT) <= 0)
        {
            MoveCursor(0, -1);
        }
        else
        {
            SendMessage(WM_VSCROLL, SB_LINEUP, 0);
            CenterCursorOnPixel(CursorPos);
        }
        break;

    case VK_DOWN:
        if (IsSCROLLLOCKToggled() ||
            IsSHIFTpressed() ||
            GetScrollPos(SB_VERT) >= GetScrollLimit(SB_VERT) ||
            !(GetStyle() & WS_VSCROLL))
        {
            MoveCursor(0, 1);
        }
        else
        {
            SendMessage(WM_VSCROLL, SB_LINEDOWN, 0);
            CenterCursorOnPixel(CursorPos);
        }
        break;

    case VK_LEFT:
        if (IsSCROLLLOCKToggled() ||
            IsSHIFTpressed() ||
            GetScrollPos(SB_HORZ) <= 0)
        {
            MoveCursor(-1, 0);
        }
        else
        {
            SendMessage(WM_HSCROLL, SB_LINELEFT, 0);
            CenterCursorOnPixel(CursorPos);
        }
        break;

    case VK_RIGHT:
        if (IsSCROLLLOCKToggled() ||
            IsSHIFTpressed() ||
            GetScrollPos(SB_HORZ) >= GetScrollLimit(SB_HORZ) ||
            !(GetStyle() & WS_HSCROLL))
        {
            MoveCursor(1, 0);
        }
        else
        {
            SendMessage(WM_HSCROLL, SB_LINERIGHT, 0);
            CenterCursorOnPixel(CursorPos);
        }
        break;

    case VK_NEXT:
        SendMessage(Message, SB_PAGEDOWN, 0);
            CenterCursorOnPixel(CursorPos);
        break;

    case VK_PRIOR:
        SendMessage(Message, SB_PAGEUP, 0);
        CenterCursorOnPixel(CursorPos);
        break;

    case VK_HOME:
        if (IsCTRLpressed())
        {
            SendMessage(WM_HSCROLL, SB_LEFT, 0);
            SendMessage(WM_VSCROLL, SB_TOP, 0);
        }
        else
        {
            SendMessage(Message, SB_TOP, 0);
        }
        CenterCursorOnPixel(CursorPos);
        break;

    case VK_END:
        if (IsCTRLpressed())
        {
            SendMessage(WM_HSCROLL, SB_RIGHT, 0);
            SendMessage(WM_VSCROLL, SB_BOTTOM, 0);
        }
        else
        {
            SendMessage(Message, SB_BOTTOM, 0);
        }
        CenterCursorOnPixel(CursorPos);
        break;

    case VK_ESCAPE:
        {
            CMainFrame *pMainFrame = dynamic_cast<CMainFrame *>(AfxGetMainWnd());
            if (NULL != pMainFrame && pMainFrame->PropertiesDialog.IsWindowVisible())
            {
                pMainFrame->PostMessage(WM_COMMAND, MAKEWPARAM(ID_IMAGE_PROPERTIES, 1), NULL);
            }
        }
        break;

    case VK_TAB:
        {
            CMainFrame *pMainFrame = dynamic_cast<CMainFrame *>(AfxGetMainWnd());
            if (NULL != pMainFrame && pMainFrame->PropertiesDialog.IsWindowVisible())
            {
                pMainFrame->PropertiesDialog.SetFocus();
            }
        }
        break;

    default:
        CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
    }
}

void CImageViewerView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
    CDeletedImageData *pData = dynamic_cast<CDeletedImageData *>(pHint);
    if (pData)
    {
        if (pData->CountLeft == 0)
        {
            GetParent()->PostMessage(WM_CLOSE);
            return;
        }

        size_t Temp = CurrentImage;
        if (CurrentImage >= pData->StartRange && CurrentImage <= pData->EndRange)
        {
            // current image in deleted range, set to first image after deleted range
            Temp = pData->StartRange;
        }
        else if (CurrentImage > pData->EndRange)
        {
            // deleted range below this image, keep on same image
            Temp -= pData->EndRange - pData->StartRange + 1;
        }

        if (Temp >= pData->CountLeft)
        {
            // went past the last image, stay on the last image
            Temp = pData->CountLeft - 1;
        }

//        TRACE(_T("CurrentImage %d, Deleted %d to %d, CountLeft %d, Temp %d\n"),
//              CurrentImage, pData->StartRange, pData->EndRange, pData->CountLeft, Temp);

        SetCurrentImage(Temp, true);
    }
    else if (lHint == 0xfeb1)
    {
        CImageViewerDoc *pDoc = GetDocument();
        SetCurrentImage(pDoc->GetImageDataCount() - 1, CurrentImage == 0xffffffff);
    }
    else
    {
        CScrollView::OnUpdate(pSender, lHint, pHint);
    }
}

BOOL CImageViewerView::OnMouseWheel(UINT nFlags, short zDelta, CPoint /*pt*/)
{
    // Wheel = vertical scroll
    // Shift + wheel = horizontal scroll
    // Control + wheel = zoom
    static int Cumulative = 0;
    static UINT LastFlag = nFlags;

    if (nFlags != LastFlag)
    {
        Cumulative = 0;
        LastFlag = nFlags;
    }

    Cumulative += zDelta;

    if (nFlags & MK_CONTROL)
    {
        if (abs(Cumulative) >= WHEEL_DELTA)
        {
            if (Cumulative < 0)
            {
                OnZoomZoomIn();
            }
            else
            {
                OnZoomZoomOut();
            }
            Cumulative = 0;
        }
    }
    else
    {
        UINT LinesPerDelta = 3;
        SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &LinesPerDelta, 0);
        int LineDelta = WHEEL_DELTA / LinesPerDelta;
        if (abs(Cumulative) >= LineDelta)
        {
            UINT Message = nFlags & MK_SHIFT ? WM_HSCROLL : WM_VSCROLL;
            WPARAM Direction = Cumulative < 0 ? SB_LINERIGHT : SB_LINELEFT;
            for (int x = 0; x < abs(Cumulative / LineDelta); x++)
            {
                PostMessage(Message, Direction, 0);
            }
            Cumulative = 0;
        }
    }

    return TRUE;
}

void CImageViewerView::OnMouseMove(UINT nFlags, CPoint point)
{
    CRect ClientRect;
    GetClientRect(ClientRect);

    if (LButtonDown &&
        (point.x < AUTOSCROLLBORDER ||
         point.y < AUTOSCROLLBORDER ||
         ClientRect.right - point.x < AUTOSCROLLBORDER ||
         ClientRect.bottom - point.y < AUTOSCROLLBORDER
        )
       )
    {
        SetTimer(AUTOSCROLLTIMERID, AUTOSCROLLTIMERSPEED, NULL);
        AutoScrollTimer = true;
    }
    else if (AutoScrollTimer)
    {
        AutoScrollTimer = false;
    }

    CScrollView::OnMouseMove(nFlags, point);
}

void CImageViewerView::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == AUTOSCROLLTIMERID)
    {
        if (!AutoScrollTimer)
        {
            KillTimer(AUTOSCROLLTIMERID);
            return;
        }

        CPoint pt;
        GetCursorPos(&pt);
        ScreenToClient(&pt);

        CRect ClientRect;
        GetClientRect(&ClientRect);

        if (!ClientRect.PtInRect(pt))
        {
            // should never get here, cursor has been clipped in OnLButtonDown
            KillTimer(AUTOSCROLLTIMERID);
            AutoScrollTimer = false;
        }
        else
        {
            int pixels = ZoomRatios[CurrentZoomRatio] / 100;
            if (pixels < 1)
                pixels = 1;

            CPoint ScrollPos(GetScrollPos(SB_HORZ), GetScrollPos(SB_VERT));
            CPoint NewPos = ScrollPos;

            if (GetStyle() & WS_HSCROLL)
            {
                if (pt.x < AUTOSCROLLBORDER)
                    NewPos.x -= pixels;

                if (ClientRect.right - pt.x < AUTOSCROLLBORDER)
                    NewPos.x += pixels;

                int xMax = GetScrollLimit(SB_HORZ);
                if (NewPos.x < 0)
                    NewPos.x = 0;
                else if (NewPos.x > xMax)
                    NewPos.x = xMax;
            }

            if (GetStyle() & WS_VSCROLL)
            {
                if (pt.y < AUTOSCROLLBORDER)
                    NewPos.y -= pixels;

                if (ClientRect.bottom - pt.y < AUTOSCROLLBORDER)
                    NewPos.y += pixels;

                int yMax = GetScrollLimit(SB_VERT);

                if (NewPos.y < 0)
                    NewPos.y = 0;
                else if (NewPos.y > yMax)
                    NewPos.y = yMax;
            }

            if (NewPos != ScrollPos)
            {
                SetScrollPos(SB_HORZ, NewPos.x);
                SetScrollPos(SB_VERT, NewPos.y);
                ScrollWindow(ScrollPos.x - NewPos.x, ScrollPos.y - NewPos.y);
            }
        }

        return;
    }

    CScrollView::OnTimer(nIDEvent);
}

void CImageViewerView::OnLButtonDown(UINT nFlags, CPoint point)
{
    CRect rc;
    GetClientRect(rc);
    rc.DeflateRect(AUTOSCROLLBORDER, AUTOSCROLLBORDER);
    if (rc.PtInRect(point))
    {
        SetCapture();
        LButtonDown = true;
        ClipCursor(GetVisibleRect());
    }

    CScrollView::OnLButtonDown(nFlags, point);
}

void CImageViewerView::OnLButtonUp(UINT nFlags, CPoint point)
{
    if (LButtonDown)
    {
        ReleaseCapture();
        LButtonDown = false;
        AutoScrollTimer = false;
        ClipCursor(NULL);
    }

    CScrollView::OnLButtonUp(nFlags, point);
}

CRect CImageViewerView::GetVisibleRect(void) const
{
    // returns the part of the client area of the view window that
    // is visible within the MDIClient area, in screen coordinates
    CRect VisibleRect;
    VisibleRect.SetRectEmpty();

    CMainFrame *pMainFrame = dynamic_cast<CMainFrame *>(AfxGetMainWnd());
    if (pMainFrame)
    {
        CWnd *pMDIClient = CWnd::FromHandle(pMainFrame->m_hWndMDIClient);
        if (pMDIClient)
        {
            CRect MDIClientRect;
            pMDIClient->GetClientRect(MDIClientRect);
            pMDIClient->ClientToScreen(MDIClientRect);

            CRect ViewClientRect;
            GetClientRect(ViewClientRect);
            ClientToScreen(ViewClientRect);

            VisibleRect = ViewClientRect & MDIClientRect;
        }
    }

    return VisibleRect;
}

void CImageViewerView::OnViewCenterMouse()
{
    CRect rc = GetVisibleRect();
    if (!rc.IsRectEmpty())
    {
        CPoint pt = rc.CenterPoint();
        CenterCursorOnPixel(pt);
    }
}

void CImageViewerView::OnUpdateViewCenterMouse(CCmdUI *pCmdUI)
{
    CRect rc = GetVisibleRect();
    pCmdUI->Enable(!rc.IsRectNull());
}

#if !defined NO_GDIPLUS

void CImageViewerView::OnImageSave()
{
    bool locked = AfxGetMainWnd()->SendMessage(WMU_GETDISPLAYLOCK, 0, 0) != 0;
    if (!locked)
    {
        // temporarily lock the display
        AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_VIEW_DISPLAY_LOCK, 0);
        AfxGetApp()->OnIdle(-1);
    }

    // Save the image
    Gdiplus::Bitmap GDIplusBitmap(CurrentBitmap, NULL);

    CString Filter;
    Filter.LoadString(IDS_SAVEFILTER);

    CString Title;
    Title.LoadString(IDS_SAVEIMAGEAS);

    CFileDialog Dlg(FALSE,
        _T(".png"),
        _T("Untitled"),
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ENABLESIZING,
        Filter,
        this);
    Dlg.m_ofn.lpstrTitle = Title;

    theApp.ModalDialogEvent.ResetEvent();
    if (IDOK == Dlg.DoModal())
    {
        CString Path = Dlg.GetPathName();
        CString Extension = Dlg.GetFileExt().MakeLower();
        CString Encoder = _T("image/");
        if (Extension == _T("tif") || Extension == _T("tiff"))
        {
            Encoder += _T("tiff");
        }
        else if (Extension == _T("jpg") || Extension == _T("jpeg"))
        {
            Encoder += _T("jpeg");
        }
        else if (Extension == _T("dib") || Extension == _T("bmp"))
        {
            Encoder += _T("bmp");
        }
        else if (Extension == _T("png"))
        {
            Encoder += _T("png");
        }
        else if (Extension == _T("gif"))
        {
            Encoder += _T("gif");
        }
        else
        {
            switch(Dlg.m_pOFN->nFilterIndex)
            {
            case 0:
            case 1:
                Path += _T(".png");
                Encoder += _T("png");
                break;
            case 2:
                Path += _T(".bmp");
                Encoder += _T("bmp");
                break;
            case 3:
                Path += _T(".tif");
                Encoder += _T("tiff");
                break;
            case 4:
                Path += _T(".gif");
                Encoder += _T("gif");
                break;
            case 5:
                Path += _T(".jpg");
                Encoder += _T("jpeg");
                break;
            }
        }

        CLSID Clsid;
        Gdiplus::Status Status = Gdiplus::UnknownImageFormat;
        if (-1 != GetEncoderClsid(CT2CW(Encoder), &Clsid))
        {
            Status = GDIplusBitmap.Save(CT2CW(Path), &Clsid, NULL);
        }
        if (Status != Gdiplus::Ok)
        {
            AfxMessageBox(CString(_T("An error happened. Unable to save file:\n\n")) + Path);
        }
    }
    theApp.ModalDialogEvent.SetEvent();

    if (!locked)
    {
        // remove the temporary lock
        AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_VIEW_DISPLAY_LOCK, 0);
    }
}

void CImageViewerView::OnUpdateImageSave(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(NULL != CurrentBitmap);
}

#endif // #if !defined NO_GDIPLUS


void CImageViewerView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    if ((GetStyle() & WS_HSCROLL) != WS_HSCROLL)
    {
        return;
    }

    int pos = GetScrollPos(SB_HORZ);
    int max = GetScrollLimit(SB_HORZ);
    int newpos = pos;

    switch(nSBCode)
    {
    case SB_LINERIGHT:
        if (pos < max)
        {
            if (ZoomRatios[CurrentZoomRatio] < 100)
            {
                newpos = pos + 1;
            }
            else
            {
                double d = (double)pos / ((double)ZoomRatios[CurrentZoomRatio] / 100.0);
                d = 1.0 + floor(d - floor(d) > 0.5 ? d + 1.0 : d);
                newpos = (int)(((double)ZoomRatios[CurrentZoomRatio] / 100.0) * d);
            }

            if (newpos > max)
            {
                newpos = max;
            }
        }
        break;

    case SB_LINELEFT:
        if (pos > 0)
        {
            if (ZoomRatios[CurrentZoomRatio] < 100)
            {
                newpos = pos - 1;
            }
            else
            {
                double d = (double)pos / ((double)ZoomRatios[CurrentZoomRatio] / 100.0);
                d = -1.0 + floor(d - floor(d) > 0.5 ? d + 1.0 : d);
                newpos = (int)(((double)ZoomRatios[CurrentZoomRatio] / 100.0) * d);
            }

            if (newpos < 0)
            {
                newpos = 0;
            }
        }
        break;

    case SB_THUMBTRACK:
    case SB_THUMBPOSITION:
        {
            SCROLLINFO ScrollInfo = {0};
            GetScrollInfo(SB_HORZ, &ScrollInfo, SIF_TRACKPOS);
            newpos = ScrollInfo.nTrackPos;
        }
        break;

    default:
        CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
        return;
    }

    if (pos != newpos)
    {
        SetScrollPos(SB_HORZ, newpos);
        ScrollWindow(pos - newpos, 0);
        AfxGetMainWnd()->SendMessage(WMU_UPDATETOOLTIP, (WPARAM)this, 0);
    }
}

void CImageViewerView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    if ((GetStyle() & WS_VSCROLL) != WS_VSCROLL)
    {
        return;
    }

    int pos = GetScrollPos(SB_VERT);
    int max = GetScrollLimit(SB_VERT);
    int newpos = pos;

    switch(nSBCode)
    {
    case SB_LINEDOWN:
        if (pos < max)
        {
            if (ZoomRatios[CurrentZoomRatio] < 100)
            {
                newpos = pos + 1;
            }
            else
            {
                double d = (double)pos / ((double)ZoomRatios[CurrentZoomRatio] / 100.0);
                d = 1.0 + floor(d - floor(d) < 0.5 ? d : d + 1.0);
                newpos = (int)(((double)ZoomRatios[CurrentZoomRatio] / 100.0) * d);
            }

            if (newpos > max)
            {
                newpos = max;
            }
        }
        break;

    case SB_LINEUP:
        if (pos > 0)
        {
            if (ZoomRatios[CurrentZoomRatio] < 100)
            {
                newpos = pos - 1;
            }
            else
            {
                double d = (double)pos / ((double)ZoomRatios[CurrentZoomRatio] / 100.0);
                d = -1.0 + floor(d - floor(d) < 0.5 ? d : d + 1.0);
                newpos = (int)(((double)ZoomRatios[CurrentZoomRatio] / 100.0) * d);
            }
            
            if (newpos < 0)
            {
                newpos = 0;
            }
        }
        break;

    case SB_THUMBTRACK:
    case SB_THUMBPOSITION:
        {
            SCROLLINFO ScrollInfo = {0};
            GetScrollInfo(SB_VERT, &ScrollInfo, SIF_TRACKPOS);
            newpos = ScrollInfo.nTrackPos;
        }
        break;

    default:
        CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
        return;
    }

    if (pos != newpos)
    {
        SetScrollPos(SB_VERT, newpos);
        ScrollWindow(0, pos - newpos);
        AfxGetMainWnd()->SendMessage(WMU_UPDATETOOLTIP, (WPARAM)this, 0);
    }
}

void CImageViewerView::CalcBitmapRect()
{
    if (!ZoomedBitmapRect.IsRectEmpty())
    {
        CRect ClientRect;
        GetClientRect(ClientRect);

        // Set the top left corner to 0, 0
        ZoomedBitmapRect.OffsetRect(-ZoomedBitmapRect.left, -ZoomedBitmapRect.top);

        // Center the zoomed image on the view
        int top = ZoomedBitmapRect.Height() < ClientRect.Height() ? ClientRect.CenterPoint().y - ZoomedBitmapRect.Height() / 2 : 0;
        int left = ZoomedBitmapRect.Width() < ClientRect.Width() ? ClientRect.CenterPoint().x - ZoomedBitmapRect.Width() / 2 : 0;
        ZoomedBitmapRect.OffsetRect(left, top);
    }
}

void CImageViewerView::OnSize(UINT nType, int cx, int cy)
{
    CScrollView::OnSize(nType, cx, cy);

    CalcBitmapRect();
}

LRESULT CImageViewerView::OnMouseGesture(WPARAM wp, LPARAM /* lp */)
{
    switch (wp)
    {
    case GESTUREUP:
        OnImageFirst();
        break;

    case GESTUREDOWN:
        OnImageLast();
        break;

    case GESTURELEFT:
        OnImagePrevious();
        break;

    case GESTURERIGHT:
        OnImageNext();
        break;

    default:
        TRACE(_T("Unhandled mouse gesture: ID = %d\n"), wp);
        ASSERT(0);
    }

    return 0;
}

