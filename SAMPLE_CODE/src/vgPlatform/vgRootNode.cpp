#include <vgStableHeaders.h>
#include "vgRootNode.h"
#include "vgUIController.h"

vgRootNode::vgRootNode(string nameID):vgBasedNode(nameID)
{
//	m_pRootTab = new vgRootTabPage;
}

vgRootNode::~vgRootNode(void)
{
//	delete m_pRootTab;
}

void vgRootNode::AddNodeTabs()
{
	vgUIController::GetInstance()->RemoveAllPages();

	vgPropertiesViewBar* pageViewBar = vgUIController::GetInstance()->GetPropertiesViewBar();
	
	m_pRootTab = dynamic_cast<vgRootTabPage*> (vgUIController::GetInstance()->GetTabPage(TAB_ROOT_TAB));
	m_pRootTab->ConnectNode(this);
	m_pRootTab->Create(IDD_ROOTVIEW, pageViewBar->GetTabControl());
	pageViewBar->AddTab(m_pRootTab->GetTitle(), m_pRootTab);
}