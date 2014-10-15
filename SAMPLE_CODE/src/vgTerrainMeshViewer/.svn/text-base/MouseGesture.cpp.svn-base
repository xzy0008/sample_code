/****************************************************************************
MouseGesture.cpp: implementation of the CMouseGesture class.
written by PJ Arends
pja@telus.net

Copyright (c) 2005

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

Revision History:
    June 2005 - initial release on The CodeProject - http://www.codeproject.com

****************************************************************************/

#include <vgStableHeaders.h>
#include "MouseGesture.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// DEBUG only stuff
//////////////////////////////////////////////////////////////////////

#ifdef _DEBUG

//////////////////////////////////////////////////////////////////////
// Uncomment the #define _SHOW_GESTURE line to draw mouse points and
// bounding squares on screen when the gesture is being made. 
//////////////////////////////////////////////////////////////////////

//#   define _SHOW_GESTURE  // this line controls visual feedback

#   ifdef _SHOW_GESTURE

        void SHOW_BOUNDING_SQUARE (MOUSEHOOKSTRUCT *pMHS,
                                   RECT rc)
        {
            HWND hWnd = WindowFromPoint(pMHS->pt);
            MapWindowPoints(NULL, hWnd, (POINT *)&rc, 2);
            HDC hdc = GetDC(hWnd);
            DrawFocusRect(hdc, &rc);
            ReleaseDC(hWnd, hdc);
        }

#   else // _SHOW_GESTURE
#       define SHOW_BOUNDING_SQUARE(pMHS, rc)
#   endif // _SHOW_GESTURE
#else // _DEBUG
#   define SHOW_BOUNDING_SQUARE(pMHS, rc)
#endif // _DEBUG

//////////////////////////////////////////////////////////////////////
// handy functions borrowed from Chris Maunder's CGridCtrl class
//////////////////////////////////////////////////////////////////////

#define IsSHIFTpressed() ( (GetKeyState(VK_SHIFT) & (1 << (sizeof(SHORT)*8-1))) != 0   )
#define IsCTRLpressed()  ( (GetKeyState(VK_CONTROL) & (1 << (sizeof(SHORT)*8-1))) != 0 )

//////////////////////////////////////////////////////////////////////
// Static private member variables
//////////////////////////////////////////////////////////////////////

CMouseGesture::_WndMap CMouseGesture::WindowMap;
CMouseGesture* CMouseGesture::Current = NULL;
HHOOK CMouseGesture::MainHook = NULL;

//////////////////////////////////////////////////////////////////////
// Static functions
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// GetGesturePointer
//    static private member function
//
// Gets a pointer to the CMouseGesture object that will handle mouse
// gestures for the given window.
//////////////////////////////////////////////////////////////////////

CMouseGesture* CMouseGesture::GetGesturePointer(HWND hWnd,
                                                POINT pt)
{
    if (!IsWindow(hWnd))
    {
        return NULL;
    }

    _WndMap::iterator it = WindowMap.find(hWnd);
    if (it == WindowMap.end())
    {
        // hWnd not found, move up the parent chain
        return GetGesturePointer(GetParent(hWnd), pt);
    }

    // ensure given point is in the client area of the window
    RECT rc;
    GetClientRect(hWnd, &rc);
    MapWindowPoints(hWnd, NULL, (POINT *)&rc, 2);
    if (!PtInRect(&rc, pt))
    {
        return NULL;
    }

    // ensure the CMouseGesture object has gestures to recognize
    CMouseGesture *pGestures = (CMouseGesture *)((*it).second);
    if (pGestures->m_GestureMap.empty())
    {
        return NULL;
    }

    return pGestures;
}

//////////////////////////////////////////////////////////////////////
// MouseHookProc
//    static private member function
//////////////////////////////////////////////////////////////////////

LRESULT CMouseGesture::MouseHookProc(int nCode,
                                     WPARAM wp,
                                     LPARAM lp)
{
    MOUSEHOOKSTRUCT *pMHS = (MOUSEHOOKSTRUCT *)lp;
    
    if (wp == WM_LBUTTONDOWN ||
        wp == WM_MBUTTONDOWN ||
        wp == WM_RBUTTONDOWN)
    {
        if (Current != NULL)
        {
            Current->KillGesture();
        }

        Current = GetGesturePointer(pMHS->hwnd, pMHS->pt);
    }

    // mouse wheel messages are ignored
    if (wp != WM_MOUSEWHEEL && Current != NULL)
    {
        Current = Current->MouseMessage(wp, lp);
    }

    return CallNextHookEx(MainHook, nCode, wp, lp);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMouseGesture::CMouseGesture() :
m_hWnd(NULL),
m_bCaptured(false),
m_bShift(false),
m_bControl(false),
m_ButtonFlag(0),
m_ButtonDown(None),
m_CurrentGesture(NULL),
m_nDistance(0),
m_LastDirection(None)
{
}

CMouseGesture::~CMouseGesture()
{
    Detach();
}

//////////////////////////////////////////////////////////////////////
// Initialization functions
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Attach
//    public member function
//
// Sets up the CMouseGesture object for use
//
// Parameters:
//    hWnd     - The window that uses the gestures
//    Distance - The minimum distance, in pixels, that the mouse must
//               travel in order for a motion to be recognized
//
// Returns:
//    true if successful
//    false if not successful
//////////////////////////////////////////////////////////////////////

bool CMouseGesture::Attach(HWND hWnd,
                           UINT Distance /* = 25 */)
{
    _ASSERT (Distance > 9);
    _ASSERT (::IsWindow(hWnd));

    if (Distance < 10 || !IsWindow(hWnd))
    {
        return false;
    }

    if (m_hWnd != NULL)
    {
        // This CMouseGesture is already attached to a window
        // call Detach() before calling Attach()
        _ASSERT (false);
        return false;
    }

    _WndMap::iterator it = WindowMap.find(hWnd);
    if (it != WindowMap.end())
    {
        // This window already has a CMouseGesture object associated with it
        _ASSERT (false);
        return false;
    }

    if (WindowMap.insert(std::make_pair(hWnd, this)).second != true)
    {
        // failed to add this window to the WindowMap
        _ASSERT (false);
        return false;
    }

    if (MainHook == NULL)
    {
        DWORD ThreadID = GetWindowThreadProcessId(hWnd, NULL);
        MainHook = SetWindowsHookEx(WH_MOUSE, MouseHookProc, NULL, ThreadID);
        if (MainHook == NULL)
        {
            // failed to create the hook
            WindowMap.erase(hWnd);
            _ASSERT (false);
            return false;
        }
    }

    m_hWnd = hWnd;
    m_nDistance = Distance;

    return true;
}

//////////////////////////////////////////////////////////////////////
// AddGesture
//    public member functions
//
// Adds mouse movement patterns for the CMouseGesture object to recognize
//
// Parameters:
//    ID       - An identifier number for the pattern
//    Motions  - A pointer to an array of Motions
//    count    - The number of Motions in the array
//    rGesture - A Gesture vector containing the Motions
//
// Returns:
//    -2 : gesture already present
//    -1 : a gesture with given ID already present
//    0  : error in the supplied gesture or invalid ID
//    >0 : number of gestures
//////////////////////////////////////////////////////////////////////

int CMouseGesture::AddGesture(UINT ID,
                              const Motion *Motions,
                              size_t count)
{
    _ASSERT (Motions != NULL);
    _ASSERT (count > 1);

    if (Motions == NULL || count < 2)
    {
        return 0;
    }

    Gesture gesture;
    for (size_t i = 0; i < count; ++i)
    {
        gesture.push_back(Motions[i]);
    }

    return AddGesture(ID, gesture);
}

int CMouseGesture::AddGesture(UINT ID,
                              const Gesture &rGesture)
{
    _ASSERT (ID > 0);
    _ASSERT (rGesture.size() > 1);

    if (rGesture.size() < 2 || ID < 1)
    {
        return 0;
    }

    // Make sure the supplied gesture is valid
    if (rGesture[0] != LeftButton &&
        rGesture[0] != MiddleButton &&
        rGesture[0] != RightButton)
    {
        // The first element must be the mouse button
        _ASSERT (false);
        return 0;
    }

    Motion last = None;
    for (Gesture::const_iterator it = rGesture.begin(); it != rGesture.end(); ++it)
    {
        if (*it == LeftButton ||
            *it == MiddleButton ||
            *it == RightButton)
        {
            if (it != rGesture.begin())
            {
                // mouse button can only be first
                _ASSERT(false);
                return 0;
            }
            continue;
        }

        if (*it == Shift)
        {
            if (rGesture.size() < 3)
            {
                // Gesture must be more than just Shift
                _ASSERT (false);
                return 0;
            }

            if (it != rGesture.begin() + 1)
            {
                // Shift must be in second spot
                _ASSERT (false);
                return 0;
            }
            continue;
        }

        if (*it == Control)
        {
            if (rGesture.size() < 3)
            {
                // Gesture must be more than just Control
                _ASSERT (false);
                return 0;
            }

            if (it != rGesture.begin() + 1 &&
                it != rGesture.begin() + 2)
            {
                // Control must be either second or third
                _ASSERT (false);
                return 0;
            }

            if (it == rGesture.begin() + 2 &&
                (rGesture[1] != Shift || rGesture.size() < 4))
            {
                // if control is third, shift must be second, and there must be more motions
                _ASSERT (false);
                return 0;
            }
            continue;
        }

        if (*it == last ||
            *it < Up ||
            *it > Right)
        {
            // The motion has to be Up, Down, Left, or Right
            // The same motion can not immediately repeat
            _ASSERT (false);
            return 0;
        }
        last = *it;
    }

    // make sure the supplied ID is unique
    if (m_GestureMap.find(ID) != m_GestureMap.end())
    {
        _ASSERT(false);
        return -1;
    }

    // make sure the supplied gesture is unique
    if (GetGestureIdFromMap(rGesture) != 0)
    {
        _ASSERT(false);
        return -2;
    }

    m_ButtonFlag |= rGesture[0];
    m_GestureMap.insert(std::make_pair(ID, rGesture));

    return m_GestureMap.size();
}

//////////////////////////////////////////////////////////////////////
// Deinitialize functions
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// RemoveGesture
//    public member function
//
// Removes the gesture pattern
//
// Parameters:
//    nID - The ID of the pattern to remove
//
// Returns
//   true : the pattern was found and removed
//   false : the pattern was not found
//////////////////////////////////////////////////////////////////////

bool CMouseGesture::RemoveGesture(UINT nID)
{
    bool ret = m_GestureMap.erase(nID) == 1;

    if (ret)
    {
        // reset the m_ButtonFlag in case a mouse button is eliminated
        m_ButtonFlag = 0;
        for (GestureMap::const_iterator it = m_GestureMap.begin(); it != m_GestureMap.end(); ++it)
        {
            m_ButtonFlag |= (*it).second[0];
        }
    }

    return ret;
}

//////////////////////////////////////////////////////////////////////
// Detach
//    public member function
//
// Detaches this CMouseGesture object from the window
//////////////////////////////////////////////////////////////////////

#pragma warning(push)
#pragma warning(disable: 4189)  // 'erased' : local variable is initialized but not referenced
void CMouseGesture::Detach()
{
    if (m_hWnd != NULL)
    {
        int erased = WindowMap.erase(m_hWnd);
        _ASSERT (erased == 1);
        m_hWnd = NULL;
    }

    if (WindowMap.size() == 0 && MainHook != NULL)
    {
        UnhookWindowsHookEx(MainHook);
        MainHook = NULL;
    }
}
#pragma warning(pop)

//////////////////////////////////////////////////////////////////////
// Mouse message handler functions
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// MouseMessage
//    private member function
//
// Called by the MouseHookProc to handle the mouse messages
//
// Returns:
//    the this pointer if handling a gesture
//    NULL if not
//////////////////////////////////////////////////////////////////////

CMouseGesture* CMouseGesture::MouseMessage(WPARAM wp, LPARAM lp)
{
    CMouseGesture *ret = NULL;
    DWORD Message = (DWORD)wp;
    MOUSEHOOKSTRUCT *pMHS = (MOUSEHOOKSTRUCT *)lp;

    switch (Message)
    {
    case WM_LBUTTONDOWN:
        if (m_ButtonFlag & LeftButton)
        {
            m_CurrentGesture.clear();
            m_CurrentGesture.push_back(LeftButton);
            m_ButtonDown = LeftButton;
            ret = OnButtonDown(pMHS);
        }
        break;

    case WM_MBUTTONDOWN:
        if (m_ButtonFlag & MiddleButton)
        {
            m_CurrentGesture.clear();
            m_CurrentGesture.push_back(MiddleButton);
            m_ButtonDown = MiddleButton;
            ret = OnButtonDown(pMHS);
        }
        break;

    case WM_RBUTTONDOWN:
        if (m_ButtonFlag & RightButton)
        {
            m_CurrentGesture.clear();
            m_CurrentGesture.push_back(RightButton);
            m_ButtonDown = RightButton;
            ret = OnButtonDown(pMHS);
        }
        break;

    case WM_LBUTTONUP:
        if (m_ButtonDown == LeftButton)
        {
            ret = OnButtonUp(pMHS);
        }
        break;

    case WM_MBUTTONUP:
        if (m_ButtonDown == MiddleButton)
        {
            ret = OnButtonUp(pMHS);
        }
        break;

    case WM_RBUTTONUP:
        if (m_ButtonDown == RightButton)
        {
            ret = OnButtonUp(pMHS);
        }
        break;

    case WM_MOUSEMOVE:
    case WM_NCMOUSEMOVE:
        if (m_ButtonDown != None)
        {
            ret = OnMouseMove(pMHS);
        }
    }

    if (ret == NULL)
    {
        KillGesture();
    }

    return ret;
}

//////////////////////////////////////////////////////////////////////
// OnButtonDown
//    protected virtual member function
//
// Handles the start of a gesture
//////////////////////////////////////////////////////////////////////

CMouseGesture* CMouseGesture::OnButtonDown(MOUSEHOOKSTRUCT *pMHS)
{
    m_BoundingSquare.left = pMHS->pt.x - m_nDistance;
    m_BoundingSquare.top = pMHS->pt.y - m_nDistance;
    m_BoundingSquare.right = pMHS->pt.x + m_nDistance;
    m_BoundingSquare.bottom = pMHS->pt.y + m_nDistance;

    SHOW_BOUNDING_SQUARE (pMHS, m_BoundingSquare);

    m_LastDirection = None;

    if (IsSHIFTpressed())
    {
        m_bShift = true;
        m_CurrentGesture.push_back(Shift);
    }

    if (IsCTRLpressed())
    {
        m_bControl = true;
        m_CurrentGesture.push_back(Control);
    }

    return this;
}

//////////////////////////////////////////////////////////////////////
// OnMouseMove
//    protected virtual member function
//
// Handles the building of the gesture
//////////////////////////////////////////////////////////////////////

CMouseGesture* CMouseGesture::OnMouseMove(MOUSEHOOKSTRUCT *pMHS)
{
#ifdef _SHOW_GESTURE
    {
        POINT pt;
        pt.x = pMHS->pt.x;
        pt.y = pMHS->pt.y;
        HWND hWnd = WindowFromPoint(pt);
        ScreenToClient(hWnd, &pt);
        HDC hdc = GetDC(hWnd);
        SetPixel(hdc, pt.x, pt.y, RGB(255, 0, 0));
        ReleaseDC(hWnd, hdc);
    }
#endif

    // make sure the SHIFT and CTRL keys are in
    // the same state as when the gesture started
    if (m_bShift != IsSHIFTpressed() ||
        m_bControl != IsCTRLpressed())
    {
        return NULL;
    }

    // looking for next direction mouse is taking
    if (PtInRect(&m_BoundingSquare, pMHS->pt))
    {
        // not yet able to determine
        return this;
    }

    Motion Direction = None;
    if ((pMHS->pt.x >= m_BoundingSquare.right) &&
        (pMHS->pt.y >= m_BoundingSquare.top) &&
        (pMHS->pt.y <= m_BoundingSquare.bottom))
    {
        Direction = Right;
    }
    else if ((pMHS->pt.x <= m_BoundingSquare.left) &&
             (pMHS->pt.y >= m_BoundingSquare.top) &&
             (pMHS->pt.y <= m_BoundingSquare.bottom))
    {
        Direction = Left;
    }
    else if ((pMHS->pt.y >= m_BoundingSquare.bottom) &&
             (pMHS->pt.x >= m_BoundingSquare.left) &&
             (pMHS->pt.x <= m_BoundingSquare.right))
    {
        Direction = Down;
    }
    else if ((pMHS->pt.y <= m_BoundingSquare.top) &&
             (pMHS->pt.x >= m_BoundingSquare.left) &&
             (pMHS->pt.x <= m_BoundingSquare.right))
    {
        Direction = Up;
    }

    if (Direction == None)
    {
        // Unable to calculate the direction, probably went
        // diagonally off a corner of the bounding square
        return NULL;
    }

    SHOW_BOUNDING_SQUARE (pMHS, m_BoundingSquare);

    // move the bounding square to follow the mouse
    if (m_LastDirection == Direction)
    {
        switch (Direction)
        {
        case Left:
        case Right:
            m_BoundingSquare.left = pMHS->pt.x - m_nDistance;
            m_BoundingSquare.right = pMHS->pt.x + m_nDistance;
            break;
        case Up:
        case Down:
            m_BoundingSquare.top = pMHS->pt.y - m_nDistance;
            m_BoundingSquare.bottom = pMHS->pt.y + m_nDistance;
        }
    }
    else // m_LastDirection != Direction
    {
        m_BoundingSquare.left = pMHS->pt.x - m_nDistance;
        m_BoundingSquare.right = pMHS->pt.x + m_nDistance;
        m_BoundingSquare.top = pMHS->pt.y - m_nDistance;
        m_BoundingSquare.bottom = pMHS->pt.y + m_nDistance;

        // direction changed, save the new direction
        m_CurrentGesture.push_back(Direction);
        m_LastDirection = Direction;
    }

    SHOW_BOUNDING_SQUARE (pMHS, m_BoundingSquare);

    if (GetCapture() == NULL)
    {
        // capture the mouse so we can continue recieving messages
        // if the mouse leaves the window
        SetCapture(m_hWnd);
        m_bCaptured = true;
    }

    return this;
}

//////////////////////////////////////////////////////////////////////
// OnButtonUp
//    protected virtual member function
//
// Handles the end of the mouse gesture
//////////////////////////////////////////////////////////////////////

CMouseGesture* CMouseGesture::OnButtonUp(MOUSEHOOKSTRUCT *pMHS)
{
    UNREFERENCED_PARAMETER(pMHS);

    // make sure the SHIFT and CTRL keys are in
    // the same state as when the gesture started
    if (m_bShift != IsSHIFTpressed() ||
        m_bControl != IsCTRLpressed())
    {
        return NULL;
    }


#ifdef _DEBUG
    OutputDebugString (_T("\nDumping gesture:\n"));

    for (Gesture::iterator it = m_CurrentGesture.begin(); it != m_CurrentGesture.end(); ++it)
    {
        switch (*it)
        {
        case Up:
            OutputDebugString (_T("Up, "));
            break;
        case Down:
            OutputDebugString (_T("Down, "));
            break;
        case Left:
            OutputDebugString (_T("Left, "));
            break;
        case Right:
            OutputDebugString (_T("Right, "));
            break;
        case LeftButton:
            OutputDebugString (_T("Left Button, "));
            break;
        case MiddleButton:
            OutputDebugString (_T("Middle Button, "));
            break;
        case RightButton:
            OutputDebugString (_T("Right Button, "));
            break;
        case Shift:
            OutputDebugString (_T("Shift, "));
            break;
        case Control:
            OutputDebugString (_T("Control, "));
            break;
        default:
            OutputDebugString (_T("Invalid Gesture"));
        }
    }
    OutputDebugString (_T("\n\n"));
#endif

    UINT GestureID = GetGestureIdFromMap(m_CurrentGesture);

    if (GestureID > 0 && IsWindow(m_hWnd))
    {
        PostMessage(m_hWnd, WMU_MOUSEGESTURE, (WPARAM)GestureID, (LPARAM)this);
    }

    return NULL;
}

//////////////////////////////////////////////////////////////////////
// Helper functions
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// GetGestureIdFromMap
//    private member function
//
// Finds the gesture in the map of recognized patterns
//
// Returns:
//    The ID of the pattern found
//    0 if not found
//////////////////////////////////////////////////////////////////////

UINT CMouseGesture::GetGestureIdFromMap(const Gesture &gesture)
{
    UINT ret = 0;

    for (GestureMap::const_iterator it = m_GestureMap.begin(); it != m_GestureMap.end(); ++it)
    {
        if ((*it).second == gesture)
        {
            ret = (*it).first;
            break;
        }
    }

    return ret;
}

//////////////////////////////////////////////////////////////////////
// KillGesture
//    private member function
//
// Cleans up when a gesture ends or is abandoned
//////////////////////////////////////////////////////////////////////

void CMouseGesture::KillGesture()
{
#ifdef _SHOW_GESTURE
    // remove any drawing done
    RedrawWindow(m_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
#endif
    OutputDebugString (_T("Gesture Ended\n"));

    if (m_bCaptured && GetCapture() == m_hWnd)
    {
        ReleaseCapture();
    }

    m_ButtonDown = None;
    m_bShift = false;
    m_bControl = false;
    m_CurrentGesture.clear();
    m_bCaptured = false;
}

//////////////////////////////////////////////////////////////////////
// End
//////////////////////////////////////////////////////////////////////
