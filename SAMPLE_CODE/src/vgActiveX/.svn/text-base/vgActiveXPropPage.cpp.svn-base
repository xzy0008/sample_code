// vgActiveXPropPage.cpp : Implementation of the CvgActiveXPropPage property page class.



#include <vgStableHeaders.h>

#include "vgActiveX.h"
#include "vgActiveXPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CvgActiveXPropPage, COlePropertyPage)



// Message map

BEGIN_MESSAGE_MAP(CvgActiveXPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CvgActiveXPropPage, "VGACTIVEX.vgActiveXPropPage.1",
	0xbe82b3e9, 0x544e, 0x4305, 0xac, 0x7, 0x2, 0xd3, 0x11, 0xd4, 0xae, 0x80)



// CvgActiveXPropPage::CvgActiveXPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CvgActiveXPropPage

BOOL CvgActiveXPropPage::CvgActiveXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_VGACTIVEX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CvgActiveXPropPage::CvgActiveXPropPage - Constructor

CvgActiveXPropPage::CvgActiveXPropPage() :
	COlePropertyPage(IDD, IDS_VGACTIVEX_PPG_CAPTION)
{
}



// CvgActiveXPropPage::DoDataExchange - Moves data between page and properties

void CvgActiveXPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CvgActiveXPropPage message handlers
