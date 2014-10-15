#include <vgStableHeaders.h>
#include "vgViewCamEntry.h"
#include <vgCam/vgcaViewCam.h>
#include <vgKernel/vgkSelectManager.h>

#include "vgUIController.h"
PropertiesParam vgViewCamEntry::s_ParamArray[s_NumOfParam];



 void vgViewCamEntry::AddNodeTabs()
 {
 	vgUIController::GetInstance()->RemoveAllPages();
 
 	vgPropertiesViewBar* pageViewBar = vgUIController::GetInstance()->GetPropertiesViewBar();
 
#if VGK_LANG_CHS
 	s_ParamArray[0].label = "坐标值设置";
 	s_ParamArray[0].typeId = PROP_ITEM_GROUP;
 	s_ParamArray[0].dataType = PROP_DATA_NONE;
 	s_ParamArray[0].connectedPtr = NULL;
 	s_ParamArray[0].comment = "设置相机的坐标";
 

	vgCam::ViewCam *pViewCam = ( vgCam::ViewCam*) m_Renderer;
 	s_ParamArray[1].label = "X 坐标";
 	s_ParamArray[1].typeId = PROP_ITEM_DATA;
 	s_ParamArray[1].dataType = PROP_DATA_FLOAT;
 	s_ParamArray[1].connectedPtr = &m_posX;
 	s_ParamArray[1].comment = "设置X坐标";
 
 
 	s_ParamArray[2].label = "Y 坐标";
 	s_ParamArray[2].typeId = PROP_ITEM_DATA;
 	s_ParamArray[2].dataType = PROP_DATA_FLOAT;
 	s_ParamArray[2].connectedPtr = &m_posY;
 	s_ParamArray[2].comment = "设置Y坐标";
 
 	s_ParamArray[3].label = "Z 坐标";
 	s_ParamArray[3].typeId = PROP_ITEM_DATA;
 	s_ParamArray[3].dataType = PROP_DATA_FLOAT;
 	s_ParamArray[3].connectedPtr = &m_posZMinus/*m_posZ*/;
 	s_ParamArray[3].comment = "设置Z坐标";
 
 	s_ParamArray[4].label = "其他设置";
 	s_ParamArray[4].typeId = PROP_ITEM_GROUP;
 	s_ParamArray[4].dataType = PROP_DATA_NONE;
 	s_ParamArray[4].connectedPtr = NULL;
 	s_ParamArray[4].comment = string();
 
 	s_ParamArray[5].label = "物体名称";
 	s_ParamArray[5].typeId = PROP_ITEM_DATA;
 	s_ParamArray[5].dataType = PROP_DATA_STR;
 	s_ParamArray[5].connectedPtr = m_Renderer->getNamePtr();
 	s_ParamArray[5].comment = "物体的名称";
 
 	vgPropertyPage* propPage = vgUIController::GetInstance()->GetPropPage();
 	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());
 
 	propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
 	pageViewBar->AddTab("自动属性", propPage);

#else

	s_ParamArray[0].label = "Coord";
	s_ParamArray[0].typeId = PROP_ITEM_GROUP;
	s_ParamArray[0].dataType = PROP_DATA_NONE;
	s_ParamArray[0].connectedPtr = NULL;
	s_ParamArray[0].comment = "";


	vgCam::ViewCam *pViewCam = ( vgCam::ViewCam*) m_Renderer;
	s_ParamArray[1].label = "X";
	s_ParamArray[1].typeId = PROP_ITEM_DATA;
	s_ParamArray[1].dataType = PROP_DATA_FLOAT;
	s_ParamArray[1].connectedPtr = &m_posX;
	s_ParamArray[1].comment = "";


	s_ParamArray[2].label = "Y";
	s_ParamArray[2].typeId = PROP_ITEM_DATA;
	s_ParamArray[2].dataType = PROP_DATA_FLOAT;
	s_ParamArray[2].connectedPtr = &m_posY;
	s_ParamArray[2].comment = "";

	s_ParamArray[3].label = "Z";
	s_ParamArray[3].typeId = PROP_ITEM_DATA;
	s_ParamArray[3].dataType = PROP_DATA_FLOAT;
	s_ParamArray[3].connectedPtr = &m_posZMinus/*m_posZ*/;
	s_ParamArray[3].comment = "";

	s_ParamArray[4].label = "Others";
	s_ParamArray[4].typeId = PROP_ITEM_GROUP;
	s_ParamArray[4].dataType = PROP_DATA_NONE;
	s_ParamArray[4].connectedPtr = NULL;
	s_ParamArray[4].comment = string();

	s_ParamArray[5].label = "Name";
	s_ParamArray[5].typeId = PROP_ITEM_DATA;
	s_ParamArray[5].dataType = PROP_DATA_STR;
	s_ParamArray[5].connectedPtr = m_Renderer->getNamePtr();
	s_ParamArray[5].comment = "";

	vgPropertyPage* propPage = vgUIController::GetInstance()->GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

	propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
	pageViewBar->AddTab("Auto Prop", propPage);
#endif

//	vgKernel::SelectManager::getSingleton().SetSelection(m_meshId);

}

void vgViewCamEntry::OnPropertyChanged(string paramName)
{
	// 更新TREEITEM
	vgUIController::GetInstance()->GetWorkSpaceBar()->SetItemText(hTreeItem, 
		GetName() );
 	vgCam::ViewCam *pViewCam = ( vgCam::ViewCam*) m_Renderer;
 
 	assert(pViewCam != NULL);

	m_posZ=-m_posZMinus;
 
 	pViewCam->setPosition(vgKernel::Vec3(
		m_posX-vgCore::vgCoordinate::getSingleton().GetSceneCood().x,
		m_posY-vgCore::vgCoordinate::getSingleton().GetSceneCood().y,
		m_posZ-vgCore::vgCoordinate::getSingleton().GetSceneCood().z
		));
 	pViewCam->getBoundingBox();
	vgKernel::SelectManager::getSingleton().updateBox();

}

void vgViewCamEntry::onChanged(int eventId, void* param)
{
	if (eventId == vgKernel::VG_OBS_PROPCHANGED)
	{
		vgCam::ViewCam *pViewCam = ( vgCam::ViewCam*) m_Renderer;

		assert(pViewCam != NULL);

		vgKernel::Vec3 pos = pViewCam->getPosition();

		m_posX = pos.x + vgCore::vgCoordinate::getSingleton().GetSceneCood().x;
		m_posY = pos.y + vgCore::vgCoordinate::getSingleton().GetSceneCood().y;
		m_posZ = pos.z + vgCore::vgCoordinate::getSingleton().GetSceneCood().z;

		////TRACE("New Camera Position %.2f %.2f %.2f \n", posPtr->x, posPtr->y, posPtr->z);
		if (this == vgUIController::GetInstance()->GetCurrentSelectedNode())
		{
			s_ParamArray[1].pProp->SetValue(m_posX);
			s_ParamArray[2].pProp->SetValue(m_posY);
			m_posZMinus = -m_posZ;
			s_ParamArray[3].pProp->SetValue(m_posZMinus/*m_posZ*/);
		}

		return ;
	}	

	if (eventId == vgKernel::VG_OBS_SELECTCHAGNED)
	{
		vgUIController::GetInstance()->SelectNode(this);
	}


	if (eventId == vgKernel::VG_OBS_ADDSELECTION)
	{
		vgUIController::GetInstance()->AddSelection(this);

		return ;
	}
}

CMenu* vgViewCamEntry::GetContextMenu()
{
	CMenu *menu = new CMenu;

	VERIFY(menu->CreatePopupMenu());

#if VGK_LANG_CHS
	VERIFY(menu->AppendMenu(MF_STRING, NID_VIEW_SWITCH2/*NID_MESH_GOTO*/, _T("切换至")));
	VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_DELETE,_T("删除")));
#else
	VERIFY(menu->AppendMenu(MF_STRING, NID_VIEW_SWITCH2/*NID_MESH_GOTO*/, _T("Turn to")));
	VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_DELETE,_T("delete")));
#endif

	return menu;
}