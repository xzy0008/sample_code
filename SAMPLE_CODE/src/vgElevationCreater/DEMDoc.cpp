// DEMDoc.cpp : 实现文件
//

//#include "stdafx.h"
#include <vgStableHeaders.h>
#include "DEMDoc.h"


// DEMDoc

IMPLEMENT_DYNCREATE(DEMDoc, CDocument)

DEMDoc::DEMDoc()
{
}

BOOL DEMDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

DEMDoc::~DEMDoc()
{
}


BEGIN_MESSAGE_MAP(DEMDoc, CDocument)
END_MESSAGE_MAP()


// DEMDoc 诊断

#ifdef _DEBUG
void DEMDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void DEMDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// DEMDoc 序列化

void DEMDoc::Serialize(CArchive& ar)
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


// DEMDoc 命令
