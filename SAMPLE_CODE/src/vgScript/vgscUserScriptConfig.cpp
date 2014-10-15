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
// MyPropertySheet.cpp : implementation file
//

#include <vgStableHeaders.h>

#include "resource.h"

#include <BCGCBPro.h>
#include <BCGPDrawManager.h>
#include "vgScript/vgscUserScriptConfig.h"
#include <vgKernel/vgkWarning.h>
#include <vgScript/vgscScriptManager.h>


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// UserScriptConfig

IMPLEMENT_DYNAMIC(UserScriptConfig, CBCGPPropertySheet)

UserScriptConfig::UserScriptConfig( vgKernel::StringVector input_scripts , 
								   CWnd* pParentWnd )
#if VGK_LANG_CHS
	 : CBCGPPropertySheet( "用户脚本配置" , pParentWnd ),
#else
	 : CBCGPPropertySheet( "User Config" , pParentWnd ),

#endif
	 m_Page1( input_scripts )
{
	SetLook ( CBCGPPropertySheet::PropSheetLook_OneNoteTabs );
	GetTab ().EnableAutoColor();

	AddPage(&m_Page1);
}

UserScriptConfig::~UserScriptConfig()
{
}


BEGIN_MESSAGE_MAP(UserScriptConfig, CBCGPPropertySheet)
	//{{AFX_MSG_MAP(UserScriptConfig)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// UserScriptConfig message handlers


void UserScriptConfig::OnDrawPageHeader (CDC* pDC, int nPage, CRect rectHeader)
{
	rectHeader.top += 2;
	rectHeader.right -= 2;
	rectHeader.bottom -= 2;

	if (IsVisualManagerStyle ())
	{
		pDC->FillRect (rectHeader, &globalData.brBarFace);
		pDC->Draw3dRect (rectHeader, globalData.clrBarShadow, globalData.clrBarShadow);
		pDC->SetTextColor (globalData.clrBarText);
	}
	else
	{
		pDC->FillRect (rectHeader, &globalData.brBtnFace);
		pDC->Draw3dRect (rectHeader, globalData.clrBtnShadow, globalData.clrBtnShadow);
		pDC->SetTextColor (globalData.clrBtnText);
	}

	CBCGPDrawManager dm (*pDC);
	dm.DrawShadow (rectHeader, 2);	

	CString strText;
	strText.Format (_T("Page %d description..."), nPage + 1);

	CRect rectText = rectHeader;
	rectText.DeflateRect (10, 0);

	CFont* pOldFont = pDC->SelectObject (&globalData.fontBold);
	pDC->SetBkMode (TRANSPARENT);

	pDC->DrawText (strText, rectText, DT_SINGLELINE | DT_VCENTER);

	pDC->SelectObject (pOldFont);
}


BOOL UserScriptConfig::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类

	if(wParam==IDOK || wParam == IDCANCEL ) 
	{
		if ( m_Page1.isStringChanged() )
		{
			std::ostringstream o;

#if VGK_LANG_CHS
			o << "用户定义脚本已被修改, 是否保存?";
#else
			o << "Save the changes?";
#endif

			int ret = VGK_WARN( vgKernel::Warning::WARN_INTERNAL_WARNING , 
				vgKernel::Warning::BUTTON_YES_NO_CANCEL , 
				o.str(),
				"UserScriptConfig::OnCommand");

			if ( ret == vgKernel::Warning::RETURN_YES )
			{
				vgKernel::StringVector userstr = m_Page1.getScripts();

				vgKernel::StringVector::iterator iter = userstr.begin();
				vgKernel::StringVector::iterator iter_end = userstr.end();

				for ( ; iter != iter_end ; ++ iter )
				{
					vgKernel::StringUtility::replace( *iter , "\r" , "" );
				}

				vgScript::ScriptManager::getSingleton().setUserDefinedScripts( 
					userstr );
			}
			else if ( ret == vgKernel::Warning::RETURN_CANCEL )
			{
				return TRUE;
			}
		}
	}

	return CBCGPPropertySheet::OnCommand(wParam, lParam);
}
