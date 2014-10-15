// vgFrameWorkDoc.cpp : implementation of the CvgFrameWorkDoc class
//

#include <vgStableHeaders.h>
#include "vgFrameWork.h"

#include "vgFrameWorkDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CvgFrameWorkDoc

IMPLEMENT_DYNCREATE(CvgFrameWorkDoc, CDocument)

BEGIN_MESSAGE_MAP(CvgFrameWorkDoc, CDocument)
END_MESSAGE_MAP()


// CvgFrameWorkDoc construction/destruction

CvgFrameWorkDoc::CvgFrameWorkDoc()
{
	// TODO: add one-time construction code here

}

CvgFrameWorkDoc::~CvgFrameWorkDoc()
{
}

BOOL CvgFrameWorkDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CvgFrameWorkDoc serialization

void CvgFrameWorkDoc::Serialize(CArchive& ar)
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


// CvgFrameWorkDoc diagnostics

#ifdef _DEBUG
void CvgFrameWorkDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CvgFrameWorkDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CvgFrameWorkDoc commands
