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
// CmdFrame.cpp : implementation file
//

#include <vgStableHeaders.h>

#include "vgScript/CmdFrame.h"

#include <BCGPDialog.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCmdFrame

CCmdFrame::CCmdFrame(CBCGPDialog* pDlg) :
	m_pDlg (pDlg)
{
}

CCmdFrame::~CCmdFrame()
{
}


BEGIN_MESSAGE_MAP(CCmdFrame, CBCGPFrameWnd)
	//{{AFX_MSG_MAP(CCmdFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCmdFrame message handlers

BOOL CCmdFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	ASSERT_VALID (m_pDlg);
	return m_pDlg->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

class CMyFrameImpl : public CBCGPFrameImpl
{
	CMyFrameImpl() : CBCGPFrameImpl (NULL) {}

	friend class CCmdFrame;
};

void CCmdFrame::SetMenuBar (CBCGPMenuBar* pMenuBar)
{
	((CMyFrameImpl&)m_Impl).m_pMenuBar = pMenuBar;
}
