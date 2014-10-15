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
// MMStyleExampleDoc.cpp : implementation of the CMMStyleExampleDoc class
//

#include <vgStableHeaders.h>
#include "windowsx.h"
#include "MMStyleExample.h"
#include "MMStyleExampleDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMMStyleExampleDoc

IMPLEMENT_DYNCREATE(CMMStyleExampleDoc, CDocument)

BEGIN_MESSAGE_MAP(CMMStyleExampleDoc, CDocument)
	//{{AFX_MSG_MAP(CMMStyleExampleDoc)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_OPEN, &CMMStyleExampleDoc::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMStyleExampleDoc construction/destruction

CMMStyleExampleDoc::CMMStyleExampleDoc()
{
	// TODO: add one-time construction code here

}

CMMStyleExampleDoc::~CMMStyleExampleDoc()
{
}

BOOL CMMStyleExampleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMMStyleExampleDoc serialization

void CMMStyleExampleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMMStyleExampleDoc diagnostics

#ifdef _DEBUG
void CMMStyleExampleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMMStyleExampleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


void CMMStyleExampleDoc::OnFileOpen()
{
	

	

	//char szFilters[]=
	//	"(*.vgi)|*.vgi|All Files (*.*)|*.*||";

	//CFileDialog dlg (TRUE, "vgi", "*.vgi",
	//	OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);

	//if( dlg.DoModal ()==IDOK )
	//{
	//	this->m_DecalMapPath = dlg.GetPathName();



	//}


}
