
#include <vgStableHeaders.h>
#include "vgplan/vgBlockEntry.h"
#include <vgKernel/vgkSelectManager.h>
#include <vgUIController/vgPropertyPage.h>
#include <vgUIController/vgUIController.h>
#include <vgKernel/vgkVec3.h>

vgBlockEntry::vgBlockEntry(  vgPlan::vgPlanbox* pObject ) : vgGroupBasedEntry( pObject )
{
	assert( pObject != NULL );

	vgKernel::Vec3 pos = pObject->getPosition();
	
	// TRACE("%d Auto Build Node pos: %f, %f, %f \n", this, pos.x, pos.y, pos.z);

	m_posX = pos.x + vgKernel::CoordSystem::getSingleton().getProjectionCoord().x;
	m_posY = pos.y + vgKernel::CoordSystem::getSingleton().getProjectionCoord().y;
	m_posZ = pos.z + vgKernel::CoordSystem::getSingleton().getProjectionCoord().z;
	m_posZMinus = - m_posZ;

	// m_size = pObject->getSize();
	m_layer = pObject->getLayerNum();
	m_length = pObject->getLength();
	m_width = pObject->getWidth();
	m_heightPerLayer = pObject->getHeightPerLayer();
	m_angle = pObject->getAngle();

	vgKernel::CoordSystem::getSingleton().registerObserver(this);

	// TRACE("POS in Constructor : %f, %f, %f \n", m_posX, m_posY, m_posZ);

}

void vgBlockEntry::OnSinglePropertyChanged(string paramName)
{
/*	vgGroupBasedEntry::OnSinglePropertyChanged(paramName);*/

	vgPlan::vgPlanbox *pObject = ( vgPlan::vgPlanbox*) m_Renderer;

	if (paramName == "体块长")
	{
		pObject->setLength(m_length);
		pObject->attachToTerrain();

		return ;
	}

	if (paramName == "体块宽")
	{
		pObject->setWidth(m_width);
		pObject->attachToTerrain();

		return ;
	}

	if (paramName == "单层高度")
	{
		pObject->setHeightPerLayer(m_heightPerLayer);
		pObject->attachToTerrain();

		return ;
	}

	if (paramName == "体块层数")
	{
		pObject->setLayerNum(m_layer);
		pObject->attachToTerrain();

		return ;
	}

	if (paramName == "旋转角度")
	{
		pObject->setAngle(m_angle);

		return;
	}

	m_posZ = - m_posZMinus;
	vgKernel::Vec3 offset = vgKernel::Vec3( m_posX, m_posY, m_posZ)
		- pObject->getPosition() - vgKernel::CoordSystem::getSingleton().getProjectionCoord();
	pObject->translate( offset.x, offset.y, offset.z );

	// 更新TREEITEM
	// vgUI::vgUIController::GetInstance()->GetWorkSpaceBar()->SetItemText(hTreeItem, m_Renderer->getName());
	// pObject->setName( (TCHAR*)m_Renderer->getName().c_str() );

	vgKernel::SelectManager::getSingleton().updateBox();

}

void vgBlockEntry::onChanged(int eventId, void *param)
{

	if (eventId == vgKernel::VG_OBS_PROPCHANGED)
	{
		if (s_group_list.size() > 0)
		{
			return ;
		}

		vgPlan::vgPlanbox *pObject = ( vgPlan::vgPlanbox* ) m_Renderer;

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

void vgBlockEntry::AddSingleTabPage()
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

	param.label = "物体名称";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_STR;
	param.connectedPtr = m_Renderer->getNamePtr();
	param.comment = "物体的名称";
	s_ParamArray.push_back(param);

	param.label = "体块长";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &m_length;
	param.comment = "设置体块长度(东西方向长度)";
	s_ParamArray.push_back(param);

	param.label = "体块宽";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &m_width;
	param.comment = "设置体块宽度(南北方向长度)";
	s_ParamArray.push_back(param);

	param.label = "体块层数";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_INT;
	param.connectedPtr = &m_layer;
	param.comment = "设置体块层数";
	s_ParamArray.push_back(param);

	param.label = "单层高度";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &m_heightPerLayer;
	param.comment = "设置体块单层高度";
	s_ParamArray.push_back(param);

	param.label = "旋转角度";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &m_angle;
	param.comment = "设置体块旋转角度";
	s_ParamArray.push_back(param);

	vgPropertyPage* propPage = vgUI::UIController::getSingleton().GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

	propPage->ConnectNode(this, &s_ParamArray);
	pageViewBar->AddTab("AUTO Build", propPage);

	// vgGroupBasedEntry::AddSingleTabPage();

	TRACE("%d POS in AddSingleTabPage : %f, %f, %f \n", this, m_posX, m_posY, m_posZ);
	TRACE("PROP in AddSingleTabPage : %f, %f, %f \n", this, m_length, m_width, m_layer);
}

void vgBlockEntry::AddGroupTabPage()
{

}

void vgBlockEntry::OnGroupPropertyChanged(string paramName)
{
	//vgGroupBasedEntry::OnGroupPropertyChanged(paramName);
}


CMenu* vgBlockEntry::GetContextMenu()
{
	CMenu *menu = new CMenu;

	VERIFY(menu->CreatePopupMenu());
	//VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_GOTO, _T("转到")));
	//VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_DELETE,_T("删除")));

	return menu;
}

void vgBlockEntry::getData()
{
	vgPlan::vgPlanbox *pObject = ( vgPlan::vgPlanbox * ) m_Renderer;

	vgKernel::Vec3 pos = pObject->getPosition();

	m_posX = pos.x + vgKernel::CoordSystem::getSingleton().getProjectionCoord().x;
	m_posY = pos.y + vgKernel::CoordSystem::getSingleton().getProjectionCoord().y;
	m_posZ = pos.z + vgKernel::CoordSystem::getSingleton().getProjectionCoord().z;
	m_posZMinus = - m_posZ;
}