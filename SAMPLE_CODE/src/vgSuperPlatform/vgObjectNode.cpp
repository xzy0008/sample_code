#include <vgStableHeaders.h>
#include "vgObjectNode.h"
#include "vgUIController.h"



#if 0
vgObjectNode::vgObjectNode(String nameID)
:vgBaseEntry( vgKernel::UniqueIDFactory::getUniqueID() , nameID)
{
//	m_pPropPage = new vgObjectPropPage(this);

	m_posX = 0.f;
	m_posY = 0.f;
	m_posZ = 0.f;

	m_near = 0l;
	m_far  = 0l;

	m_rotX = 0.f;
	m_rotY = 0.f;
	m_rotZ = 0.f;

	m_scaleX = 0l;
	m_scaley = 0l;
	m_scaleZ = 0l;

	m_visable = TRUE;
}

vgObjectNode::~vgObjectNode(void)
{
//	delete m_pPropPage;
}

void vgObjectNode::AddNodeTabs()
{
	vgUIController::GetInstance()->RemoveAllPages();

	vgPropertiesViewBar* pageViewBar = vgUIController::GetInstance()->GetPropertiesViewBar();
	
	m_pPropPage = dynamic_cast<vgObjectPropPage*> (vgUIController::GetInstance()->GetTabPage(TAB_OBJECT_PROP));
	m_pPropPage->ConnectNode(this);
	m_pPropPage->Create(NIDD_PROP, pageViewBar->GetTabControl());
	pageViewBar->AddTab(" Ù–‘", m_pPropPage);
	
	return ;
}


#endif