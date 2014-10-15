// TifDoc.cpp : 实现文件
//

//#include "stdafx.h"
#include <vgStableHeaders.h>
#include "TifDoc.h"


// TifDoc

IMPLEMENT_DYNCREATE(TifDoc, CDocument)

TifDoc::TifDoc()
{
}

BOOL TifDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

TifDoc::~TifDoc()
{
}


BEGIN_MESSAGE_MAP(TifDoc, CDocument)
END_MESSAGE_MAP()


// TifDoc 诊断

#ifdef _DEBUG
void TifDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void TifDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// TifDoc 序列化

void TifDoc::Serialize(CArchive& ar)
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


// TifDoc 命令
