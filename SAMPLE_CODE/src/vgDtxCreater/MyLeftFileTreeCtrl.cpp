// CMyLeftFileTreeCtrl.cpp : implementation file
//

#include <vgStableHeaders.h>
#include "VgimgReader.h"
#include "MainFrm.h"
#include "MyLeftFileTreeCtrl.h"
#include "VgimgReaderView.h"


// CMyLeftFileTreeCtrl

IMPLEMENT_DYNAMIC(CMyLeftFileTreeCtrl, CFileTreeCtrl)

CMyLeftFileTreeCtrl::CMyLeftFileTreeCtrl()
{

}

CMyLeftFileTreeCtrl::~CMyLeftFileTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyLeftFileTreeCtrl, CFileTreeCtrl)
	//ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CMyLeftFileTreeCtrl::OnTvnSelchanged)
END_MESSAGE_MAP()



// CMyLeftFileTreeCtrl message handlers




bool CMyLeftFileTreeCtrl::MatchExtension( CString file )
{
	CString strTemp = file.Right(4);
	if (!strTemp.CollateNoCase(".zip")) 
	{
		return TRUE;
	}

	CString strTemp2 = file.Right(6);
	if (!strTemp2.CollateNoCase(".vgimg")) 
	{
		return TRUE;
	}

	return FALSE;
}