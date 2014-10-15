#include <vgStableHeaders.h>
#include <vgTrigger/vgTriggerEntry.h>
#include <vgUIController/vgUIController.h>
#include <vgKernel/vgkSelectManager.h>
#include <vgUIController/vgPropertyPage.h>
#include <vgKernel/vgkVec3.h>

//vgTriggerEntry::vgTriggerEntry(vgTrigger::Trigger* pTrigger) : vgGroupBasedEntry(pTrigger )
//{
//	m_pTrigger = pTrigger;
//	getData();
//}
//
//void vgTriggerEntry::getData()
//{
//	vgTrigger::Trigger *pTrigger = dynamic_cast<vgTrigger::Trigger*>(m_pTrigger);
//
//	if (pTrigger != NULL)
//	{
//		vgKernel::Vec3 pos = pTrigger->getPosition();
//
//	    m_posX = pos.x + vgKernel::CoordSystem::getSingleton().getProjectionCoord().x;
//		m_posY = pos.y + vgKernel::CoordSystem::getSingleton().getProjectionCoord().y;
//		m_posZ = pos.z + vgKernel::CoordSystem::getSingleton().getProjectionCoord().z;
//		m_posZMinus = - m_posZ;
//
//		m_triggerName = pTrigger->getName();
//		m_enableTrigger = pTrigger->getTriggerEnable();
//		m_innerVisible = pTrigger->getInnerVisible();
//	}
//}

void vgTriggerEntry::AddSingleTabPage()
{
	TRACE("1: %d POS in AddSingleTabPage : %f, %f, %f \n", this, m_posX, m_posY, m_posZ);

	getData();
	
	vgUI::UIController::getSingleton().RemoveAllPages();

	vgPropertiesViewBar* pageViewBar = vgUI::UIController::getSingleton().GetPropertiesViewBar();

	s_ParamArray.clear();
	PropertiesParam param;

	param.label = "坐标值设置";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = "设置物体的坐标";
	s_ParamArray.push_back(param);

	param.label = "X 坐标";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &m_posX;
	param.comment = "设置X坐标";
	s_ParamArray.push_back(param);

	param.label = "Y 坐标";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &m_posY;
	param.comment = "设置Y坐标";
	s_ParamArray.push_back(param);

	param.label = "Z 坐标";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &m_posZMinus/*m_posZ*/;
	param.comment = "设置Z坐标";
	s_ParamArray.push_back(param);

	param.label = "其他设置";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = string();
	s_ParamArray.push_back(param);

	param.label = "触发器名称";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_STR;
	param.connectedPtr = m_Renderer->getNamePtr();
	param.comment = "触发器名称";
	s_ParamArray.push_back(param);

	param.label = "开启触发";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_BOOL;
	param.connectedPtr = &m_enableTrigger;
	param.comment = "触发器是否处于可触发状态";
	s_ParamArray.push_back(param);

	param.label = "内部实体渲染";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_BOOL;
	param.connectedPtr = &m_innerVisible;
	param.comment = "触发器内部的实体是否渲染可见";
	s_ParamArray.push_back(param);

	vgPropertyPage* propPage = vgUI::UIController::getSingleton().GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

	propPage->ConnectNode(this, &s_ParamArray);
	pageViewBar->AddTab("触发器", propPage);

	// vgGroupBasedEntry::AddSingleTabPage();

	TRACE("%d POS in AddSingleTabPage : %f, %f, %f \n", this, m_posX, m_posY, m_posZ);
}

void vgTriggerEntry::OnSinglePropertyChanged(string paramName)
{
	/*	vgGroupBasedEntry::OnSinglePropertyChanged(paramName);*/

	vgTrigger::Trigger *pTrigger = ( vgTrigger::Trigger*) m_Renderer;


	if (paramName == "内部实体渲染" || paramName == "开启触发")
	{

		pTrigger->setTriggerEnable(m_enableTrigger);
		pTrigger->setInnerVisible(m_innerVisible);

		return ;
	}

	m_posZ = - m_posZMinus;
	vgKernel::Vec3 offset = vgKernel::Vec3( m_posX, m_posY, m_posZ)
		- pTrigger->getPosition() - vgKernel::CoordSystem::getSingleton().getProjectionCoord();
	
	pTrigger->translate( offset.x, offset.y, offset.z );

	// 更新TREEITEM
	vgUI::UIController::getSingleton().GetWorkSpaceBar()->SetItemText(hTreeItem, m_Renderer->getName());
	pTrigger->setName( (TCHAR*)m_Renderer->getName().c_str() );

	vgKernel::SelectManager::getSingleton().updateBox();
}


void vgTriggerEntry::onChanged(int eventId, void *param)
{

	if (eventId == vgKernel::VG_OBS_PROPCHANGED)
	{
		if (s_group_list.size() > 0)
		{
			return ;
		}

		vgTrigger::Trigger *pObject = ( vgTrigger::Trigger* ) m_Renderer;

		vgKernel::Vec3 pos = pObject->getPosition();

		m_posX = pos.x + vgKernel::CoordSystem::getSingleton().getProjectionCoord().x;
		m_posY = pos.y + vgKernel::CoordSystem::getSingleton().getProjectionCoord().y;
		m_posZ = pos.z + vgKernel::CoordSystem::getSingleton().getProjectionCoord().z;

		////TRACE("New Camera Position %.2f %.2f %.2f \n", posPtr->x, posPtr->y, posPtr->z);
		if (this == vgUI::UIController::getSingleton().GetCurrentSelectedNode())
		{
			s_ParamArray[1].pProp->SetValue(m_posX);
			s_ParamArray[2].pProp->SetValue(m_posY);
			m_posZMinus = - m_posZ;
			s_ParamArray[3].pProp->SetValue(m_posZMinus/*m_posZ*/);

			s_ParamArray[6].pProp->SetValue(m_enableTrigger);
			s_ParamArray[7].pProp->SetValue(m_innerVisible);
		}
	}

	if (eventId == vgKernel::VG_OBS_SELECTCHAGNED)
	{
		vgUI::UIController::getSingleton().SelectNode(this);
	}

	if (eventId == vgKernel::VG_OBS_ADDSELECTION)
	{
		vgUI::UIController::getSingleton().AddSelection(this);

		return ;
	}

	TRACE("%d POS in OnChange : %f, %f, %f \n", this, m_posX, m_posY, m_posZ);
}