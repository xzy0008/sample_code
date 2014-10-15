// This file was created on March 21st 2001 by Robert Brault.
// I created this Class to be able change the Color of your Edit Box
// as well as your Edit Box Text. This is Derived from CEdit so you
// do not have all the overhead of a CRichEditCtrl.
//
// There are three functions available Currently:
// SetBkColor(COLORREF crColor)
// SetTextColor(COLORREF crColor)
// SetReadOnly(BOOL flag = TRUE)
//
// How To Use:
// Add three files to your project
// ColorEdit.cpp, ColorEdit.h and Color.h
// Color.h has (#define)'s for different colors (add any color you desire).
//
// Add #include "ColorEdit.h" to your Dialogs Header file.
// Declare an instance of CColorEdit for each edit box being modified.
// Ex. CColorEdit m_ebName;
//
// In your OnInitDialog() add a SubclassDlgItem for each CColorEdit member variable.
// Ex. m_ebName.SubclassDlgItem(IDC_EB_NAME, this);
// In this same function initialize your color for each box unless you want the default.


// ColorEdit.cpp : implementation file
//
#include "vgStableHeaders.h"
//#include "stdafx.h"
#include "vgColorEdit.h"
#include "vgColor.h"  // File Holding (#define)'s for COLORREF Values

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorEdit

CColorEdit::CColorEdit()
{
	m_crBkColor = ::GetSysColor(COLOR_3DFACE); // Initializing background color to the system face color.
	m_crTextColor = BLACK; // Initializing text color to black
	m_brBkgnd.CreateSolidBrush(m_crBkColor); // Creating the Brush Color For the Edit Box Background
	
// 	CFont font;
// 	VERIFY(font.CreateFont(
// 		12,                        // nHeight
// 		0,                         // nWidth
// 		0,                         // nEscapement
// 		0,                         // nOrientation
// 		FW_NORMAL,                 // nWeight
// 		FALSE,                     // bItalic
// 		FALSE,                     // bUnderline
// 		0,                         // cStrikeOut
// 		ANSI_CHARSET,              // nCharSet
// 		OUT_DEFAULT_PRECIS,        // nOutPrecision
// 		CLIP_DEFAULT_PRECIS,       // nClipPrecision
// 		DEFAULT_QUALITY,           // nQuality
// 		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
// 		"Arial"));                 // lpszFacename

// 	VERIFY(pFont->CreateFont(
// 		12,                        // nHeight
// 		0,                         // nWidth
// 		0,                         // nEscapement
// 		0,                         // nOrientation
// 		FW_NORMAL,                 // nWeight
// 		FALSE,                     // bItalic
// 		FALSE,                     // bUnderline
// 		0,                         // cStrikeOut
// 		ANSI_CHARSET,              // nCharSet
// 		OUT_DEFAULT_PRECIS,        // nOutPrecision
// 		CLIP_DEFAULT_PRECIS,       // nClipPrecision
// 		DEFAULT_QUALITY,           // nQuality
// 		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
// 		"Arial"));  
// 
// 	SetFont(pFont);
}

CColorEdit::~CColorEdit()
{
//	delete pFont;
}


BEGIN_MESSAGE_MAP(CColorEdit, CEdit)
	//{{AFX_MSG_MAP(CColorEdit)
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
	ON_WM_CREATE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorEdit message handlers

void CColorEdit::SetTextColor(COLORREF crColor)
{
	m_crTextColor = crColor; // Passing the value passed by the dialog to the member varaible for Text Color
	RedrawWindow();
}

void CColorEdit::SetBkColor(COLORREF crColor)
{
	m_crBkColor = crColor; // Passing the value passed by the dialog to the member varaible for Backgound Color
	m_brBkgnd.DeleteObject(); // Deleting any Previous Brush Colors if any existed.
	m_brBkgnd.CreateSolidBrush(crColor); // Creating the Brush Color For the Edit Box Background
	RedrawWindow();
}



HBRUSH CColorEdit::CtlColor(CDC* pDC, UINT nCtlColor)
{
	HBRUSH hbr;
	hbr = (HBRUSH)m_brBkgnd; // Passing a Handle to the Brush
	pDC->SetBkColor(m_crBkColor); // Setting the Color of the Text Background to the one passed by the Dialog
	pDC->SetTextColor(m_crTextColor); // Setting the Text Color to the one Passed by the Dialog

	if (nCtlColor)       // To get rid of compiler warning
      nCtlColor += 0;

	return hbr;
}

BOOL CColorEdit::SetReadOnly(BOOL flag)
{
   if (flag == TRUE)
      SetBkColor(m_crBkColor);
   else
      SetBkColor(WHITE);

   return CEdit::SetReadOnly(flag);
}

int CColorEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
 	VERIFY(font.CreateFont(
 		12,                        // nHeight
 		0,                         // nWidth
 		0,                         // nEscapement
 		0,                         // nOrientation
 		FW_NORMAL,                 // nWeight
 		FALSE,                     // bItalic
 		FALSE,                     // bUnderline
 		0,                         // cStrikeOut
 		ANSI_CHARSET,              // nCharSet
 		OUT_DEFAULT_PRECIS,        // nOutPrecision
 		CLIP_DEFAULT_PRECIS,       // nClipPrecision
 		DEFAULT_QUALITY,           // nQuality
 		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
 		"宋体"));  
 	SetFont(&font);

	return 0;
}
