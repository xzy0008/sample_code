#include <vgStableHeaders.h>
#include "vgRootEntry.h"
#include "vgUIController.h"

 


void vgRootEntry::AddNodeTabs()
{
	vgUIController::GetInstance()->RemoveAllPages();

	vgPropertiesViewBar* pageViewBar = vgUIController::GetInstance()->GetPropertiesViewBar();
	
	m_pRootTab = dynamic_cast<vgRootTabPage*> (vgUIController::GetInstance()->GetTabPage(TAB_ROOT_TAB));
	m_pRootTab->ConnectNode(this);
	m_pRootTab->Create(NIDD_ROOTVIEW, pageViewBar->GetTabControl());
	pageViewBar->AddTab(m_pRootTab->GetTitle(), m_pRootTab);

}

CMenu* vgRootEntry::GetContextMenu()
{
	CMenu *pMenu = new CMenu;

	if (	(m_name.find(".vgm") != -1)
		||(m_name.find(".VGM") != -1)
		||(m_name.find(".mod") != -1)
		||(m_name.find(".MOD") != -1)
		||(m_name.find(".kfm") != -1)
		||(m_name.find(".KFM") != -1)
		||(m_name.find(".vg") != -1)
		||(m_name.find(".VG") != -1)
		)
	{
		VERIFY(pMenu->CreatePopupMenu());
		VERIFY(pMenu->AppendMenu(MF_STRING, NID_ROOT_DELETE, _T("É¾³ý")));
		//VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_DELETE,_T("É¾³ý")));

		return pMenu; 
	}

	return NULL;
}