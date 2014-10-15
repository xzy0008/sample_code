// SaveVgimg_CFileTreeCtrl.cpp : implementation file
//

#include <vgStableHeaders.h>
#include "VgimgReader.h"
#include "SaveVgimg_CFileTreeCtrl.h"


// CSaveVgimg_CFileTreeCtrl

IMPLEMENT_DYNAMIC(CSaveVgimg_CFileTreeCtrl, CFileTreeCtrl)

CSaveVgimg_CFileTreeCtrl::CSaveVgimg_CFileTreeCtrl()
{

}

CSaveVgimg_CFileTreeCtrl::~CSaveVgimg_CFileTreeCtrl()
{
}

bool CSaveVgimg_CFileTreeCtrl::MatchExtension( CString file )
{
	CString strTemp = file.Right(4);
	if ( !strTemp.CollateNoCase(".") 
		|| !strTemp.CollateNoCase(".mod")
		/*|| !strTemp.CollateNoCase(".bmp")
		|| !strTemp.CollateNoCase(".tif")
		|| !strTemp.CollateNoCase(".jpg")
		|| !strTemp.CollateNoCase(".wmf")
		|| !strTemp.CollateNoCase(".dds")
		|| !strTemp.CollateNoCase(".tga")
		|| !strTemp.CollateNoCase(".png")
		|| !strTemp.CollateNoCase(".pnm")
		|| !strTemp.CollateNoCase(".pcx") */ ) 
	{
		return TRUE;
	}

	//strTemp = file.Right(5);
	//if ( !strTemp.CollateNoCase(".tiff") 
	//	|| !strTemp.CollateNoCase(".jpeg")	) 
	//{
	//	return TRUE;
	//}

	return FALSE;
}

BEGIN_MESSAGE_MAP(CSaveVgimg_CFileTreeCtrl, CFileTreeCtrl)
//	ON_NOTIFY_REFLECT(NM_RCLICK, &CSaveVgimg_CFileTreeCtrl::OnNMRclick)
END_MESSAGE_MAP()



// CSaveVgimg_CFileTreeCtrl message handlers



//void CSaveVgimg_CFileTreeCtrl::OnNMRclick(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// TODO: Add your control notification handler code here
//	*pResult = 0;
//
//	MessageBox("asfdsa");
//}
