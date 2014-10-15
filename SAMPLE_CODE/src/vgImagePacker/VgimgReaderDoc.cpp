// VgimgReaderDoc.cpp : CVgimgReaderDoc 类的实现
//

#include <vgStableHeaders.h>
#include "VgimgReader.h"

#include "VgimgReaderDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVgimgReaderDoc

IMPLEMENT_DYNCREATE(CVgimgReaderDoc, CDocument)

BEGIN_MESSAGE_MAP(CVgimgReaderDoc, CDocument)
END_MESSAGE_MAP()


// CVgimgReaderDoc 构造/析构

CVgimgReaderDoc::CVgimgReaderDoc()
{
	// TODO: 在此添加一次性构造代码

}

CVgimgReaderDoc::~CVgimgReaderDoc()
{
}

BOOL CVgimgReaderDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CVgimgReaderDoc 序列化

void CVgimgReaderDoc::Serialize(CArchive& ar)
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


// CVgimgReaderDoc 诊断

#ifdef _DEBUG
void CVgimgReaderDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVgimgReaderDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CVgimgReaderDoc 命令
