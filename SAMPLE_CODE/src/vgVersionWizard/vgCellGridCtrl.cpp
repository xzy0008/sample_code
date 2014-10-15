//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2008 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// CellTypesGridCtrl.cpp : implementation file
//

#include "vgStableHeaders.h"
#include "vgCellGridCtrl.h"
#include "vgLibDependence.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define idProgressAnim	100

inline int Rand (int nMax)
{
	if (nMax <= 0)
	{
		return 0;
	}

	int nRes = rand () % nMax;
	return min (nRes, nMax - 1);
}

#define COLORS_NUM	7

LPCTSTR colors [COLORS_NUM] =
{
	_T("Red"),
	_T("Orange"),
	_T("Yellow"),
	_T("Green"),
	_T("Blue"),
	_T("Indigo"),
	_T("Violet"),
};

/////////////////////////////////////////////////////////////////////////////
// CCellTypesGridCtrl

CCellTypesGridCtrl::CCellTypesGridCtrl()
{
	m_pProgressItem = NULL;
	m_bProgressIsOn = FALSE;
}

CCellTypesGridCtrl::~CCellTypesGridCtrl()
{
}


BEGIN_MESSAGE_MAP(CCellTypesGridCtrl, CBCGPGridCtrl)
	//{{AFX_MSG_MAP(CCellTypesGridCtrl)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCellTypesGridCtrl message handlers

int CCellTypesGridCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPGridCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	srand ((unsigned) time (NULL));

	SetWholeRowSel (FALSE);
	EnableMarkSortedColumn (FALSE);
	EnableHeader (FALSE, 0);

//  	InsertColumn (0, _T("A"), 30);
//  	InsertColumn (1, _T("B"), 80);
//  	InsertColumn (2, _T("C"), 120);
//  	InsertColumn (3, _T("D"), 50);
//  	InsertColumn (4, _T("E"), 80);
//  	InsertColumn (5, _T("F"), 120);
//  
//  	AddEmptyRow();
//  
//  	CBCGPGridRow* pRow = CreateNewRow ();
//  	ASSERT_VALID (pRow);
//  
//  	//-------------
//  	// Simple text:
//  	//-------------
//  	pRow->GetItem (1)->SetValue (_T("Text:"));
//  	pRow->ReplaceItem (2, new CBCGPGridItem (_T("Hello, world!")));
//  
//  	//-------------
//  	// Masked text:
//  	//-------------
//  	pRow->GetItem (4)->SetValue (_T("Masked Edit:"));
//  	pRow->ReplaceItem (5, new CBCGPGridItem (_T("(123) 123-12-12"),
//  		0, _T(" ddd  ddd dd dd"),
//  		_T("(___) ___-__-__")));
//  		
//  	AddRow (pRow, FALSE);
//  
//  	AddEmptyRow ();
//  	pRow = CreateNewRow ();
//  
//  	
//  	AddRow (pRow, FALSE);
//  
//  	AddEmptyRow();
//  	pRow = CreateNewRow ();
//  
//  
//  	AddRow (pRow, FALSE);
//  
//  	AddEmptyRow();
//  	pRow = CreateNewRow ();
//  
//  	//----------
//  	// Checkbox:
//  	//----------
//  	pRow->GetItem (4)->SetValue (_T("CheckBox:"));
//  	pRow->ReplaceItem (5, new CBCGPGridCheckItem (FALSE));
//  	
//  	AddRow (pRow, FALSE);
//  
//  	AddEmptyRow();
//  	pRow = CreateNewRow ();


	return 0;
}

void CCellTypesGridCtrl::OnDestroy() 
{
	SaveState (_T("CellTypesGrid"));
	CBCGPGridCtrl::OnDestroy();
}

CBCGPGridRow* CCellTypesGridCtrl::CreateNewRow ()
{
	CBCGPGridRow* pRow = CreateRow (GetColumnCount ());

	for (int i = 0; i < GetColumnCount ();i++)
	{
		pRow->GetItem (i)->AllowEdit (FALSE);
	}

	return pRow;
}

void CCellTypesGridCtrl::AddEmptyRow ()
{
	AddRow (CreateNewRow (), FALSE);
}
// 
// void CCellTypesGridCtrl::OnAnimateProgress()
// {
// 	CBCGPGridRow *pRow = this->GetRow(9);
// 	_variant_t re = pRow->GetItem(5)->GetValue();
// 	if (re.vt == VT_BOOL)
// 	{
// 		bool val = re.boolVal;
// 		if (val)
// 		{
// 			AfxMessageBox("True");
// 		}
// 		else
// 		{
// 			AfxMessageBox("False");
// 		}
// 	}
// 
// 	if (m_bProgressIsOn)
// 	{
// 		KillTimer (idProgressAnim);
// 		m_bProgressIsOn = FALSE;
// 	}
// 	else
// 	{
// 		SetTimer (idProgressAnim, 50, NULL);
// 		m_bProgressIsOn = TRUE;
// 	}
// }

void CCellTypesGridCtrl::OnTimer(UINT_PTR nIDEvent) 
{

}

void CCellTypesGridCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	vector<VARIANT_BOOL> lastVal;

   	for (int i=0; i<this->GetRowCount(); i++)
   	{
   		_variant_t val = this->GetRow(i)->GetItem(0)->GetValue();
   		
		lastVal.push_back(val.boolVal);
		
   	}

	CBCGPGridCtrl::OnLButtonUp(nFlags, point);

 	for (int i=0; i<this->GetRowCount(); i++)
 	{
 		_variant_t val = this->GetRow(i)->GetItem(0)->GetValue();
 
 		if (lastVal[i] != val.boolVal)
 		{
 			_variant_t sval = this->GetRow(i)->GetItem(1)->GetValue();
 
 			string dllName = _com_util::ConvertBSTRToString(sval.bstrVal);
 
 			if(val.boolVal)
 			{
 				TRACE("Check %s\n", dllName.c_str());
 
 				vgCheckLibItem(dllName, *this);
 			}
 			else
 			{
 				TRACE("UNCheck %s\n", dllName.c_str());
 
 				vgUnCheckLibItem(dllName, *this);
 			}
 		}
 	}
}
