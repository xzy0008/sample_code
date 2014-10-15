/****************************************************************************
MouseGesture.h: interface for the CMouseGesture class.
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
****************************************************************************/

#if !defined(AFX_MOUSEGESTURES_H__8E80AD8B_6FB6_4FF0_99EC_8666996E639E__INCLUDED_)
#define AFX_MOUSEGESTURES_H__8E80AD8B_6FB6_4FF0_99EC_8666996E639E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning (disable: 4786)

#ifndef _VECTOR_
#   pragma message("To avoid this message, put vector in your PCH (usually stdafx.h)")
#   include <vector>
#endif

#ifndef _MAP_
#   pragma message("To avoid this message, put map in your PCH (usually stdafx.h)")
#   include <map>
#endif

#ifndef _ALGORITHM_
#   pragma message("To avoid this message, put algorithm in your PCH (usually stdafx.h)")
#   include <algorithm>
#endif

//////////////////////////////////////////////////////////////////////
// MOUSE_GESTURE_MESSAGE_STRING
//
// Pass this string to RegisterWindowMessage() to get the ID of
// the registered message that CMouseGesture posts to your window
// when a mouse gesture is made and recognized
//////////////////////////////////////////////////////////////////////

#define MOUSE_GESTURE_MESSAGE_STRING _T("MGMS-{5E11C944-1412-4b52-8C86-DB293CB4BE93}")

//////////////////////////////////////////////////////////////////////
// Registered message sent to the window that initiated the gesture
// when a gesture is recognized
//   WPARAM: The ID of the recognized gesture
//   LPARAM: A CMouseGesture* pointer to the CGesture object that sent the message
//////////////////////////////////////////////////////////////////////

const UINT WMU_MOUSEGESTURE = RegisterWindowMessage(MOUSE_GESTURE_MESSAGE_STRING);

class CMouseGesture  
{
public:
    enum Motion { None         = 0x0000,

                  // These are the possible directions
                  Up           = 0x0001,
                  Down         = 0x0002,
                  Left         = 0x0003,
                  Right        = 0x0004,

                  // These are for the shift and control keys
                  Shift        = 0x0005,
                  Control      = 0x0006,

                  // These are bit flags for the mouse buttons
                  LeftButton   = 0x0100,
                  MiddleButton = 0x0200,
                  RightButton  = 0x0400
                };

    typedef std::vector<Motion> Gesture;

    CMouseGesture();
    virtual ~CMouseGesture();

    bool Attach(HWND hWnd, UINT Distance = 25);
    void Detach();
    int AddGesture(UINT nID, const Motion *Motions, size_t count);
    int AddGesture(UINT nID, const Gesture &rGesture);
    bool RemoveGesture (UINT nID);

protected:
    virtual CMouseGesture* OnButtonDown(MOUSEHOOKSTRUCT *pMHS);
    virtual CMouseGesture* OnMouseMove (MOUSEHOOKSTRUCT *pMHS);
    virtual CMouseGesture* OnButtonUp  (MOUSEHOOKSTRUCT *pMHS);

private:
    static LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wp, LPARAM lp);
    static CMouseGesture *GetGesturePointer(HWND hWnd, POINT pt);

    CMouseGesture* MouseMessage(WPARAM wp, LPARAM lp);
    void KillGesture();
    UINT GetGestureIdFromMap(const Gesture &gesture);

    typedef std::map<HWND, CMouseGesture *> _WndMap;
    static _WndMap WindowMap;       // Maps HWNDs to CMouseGesture
    static CMouseGesture* Current;  // The CMouseGesture currently reading the mouse movements
    static HHOOK MainHook;

    DWORD m_ButtonFlag;             // Bitmask for which mouse button can start a mouse gesture
    Motion m_ButtonDown;            // The mouse button that started the gesture
    HWND m_hWnd;                    // The window attached to this CMouseGesture object
    bool m_bCaptured;               // Is mouse captured
    bool m_bShift;                  // Is Shift key down
    bool m_bControl;                // Is Control key down
    UINT m_nDistance;               // Minimum distance mouse has to move to register a motion
    RECT   m_BoundingSquare;        // Boundary that mouse has to cross to register a motion
    Motion m_LastDirection;         // The last motion registered
    Gesture m_CurrentGesture;       // The gesture

    typedef std::map<UINT, Gesture> GestureMap;
    GestureMap m_GestureMap;        // The gesture patterns. Maps ID numbers to gestures
};

#endif // !defined(AFX_MOUSEGESTURES_H__8E80AD8B_6FB6_4FF0_99EC_8666996E639E__INCLUDED_)
