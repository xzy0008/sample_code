// CutSurfDoc.cpp : 实现文件
//

#include "vgStableHeaders.h"
#include "vgTerritory/CutSurfDoc.h"

// CutSurfDoc

IMPLEMENT_DYNCREATE(CutSurfDoc, CDocument)

CutSurfDoc::CutSurfDoc()
{
}

BOOL CutSurfDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CutSurfDoc::~CutSurfDoc()
{
}


BEGIN_MESSAGE_MAP(CutSurfDoc, CDocument)
END_MESSAGE_MAP()


// CutSurfDoc 诊断

#ifdef _DEBUG
void CutSurfDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CutSurfDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CutSurfDoc 序列化

void CutSurfDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}
#endif


// CutSurfDoc 命令
