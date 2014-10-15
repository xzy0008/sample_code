#include <vgStableHeaders.h>
#include <vgEntry/vgRootEntry.h>
#include <vgUIController/vgUIController.h>

 


void vgRootEntry::AddNodeTabs()
{
	vgUI::UIController::getSingleton().RemoveAllPages();

	vgPropertiesViewBar* pageViewBar = vgUI::UIController::getSingleton().GetPropertiesViewBar();
	
	m_pRootTab = dynamic_cast<vgRootTabPage*> (vgUI::UIController::getSingleton().GetTabPage(TAB_ROOT_TAB));
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