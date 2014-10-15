
#include <vgStableHeaders.h>
#include "vgentry/vgSolidBuildEntry.h"
#include <vgKernel/vgkSelectManager.h>
#include <vgAutoBuild/vgSolidBuildNode.h>

#include <vgUIController/vgUIController.h>
#include <vgDatabase/vgdDefinition.h>
#include <vgKernel/vgkPluginManager.h>


namespace vgCore{

	vgSolidBuildEntry::vgSolidBuildEntry( vgAutoBuild::SolidBuildNode* pObject /*= NULL*/ ) 
		:vgDatabaseEntry( pObject )
	{
		assert( pObject != NULL );
		
		getData();

		vgKernel::CoordSystem::getSingleton().registerObserver(this);

	}


	void vgSolidBuildEntry::AddSingleTabPage()
	{
		getData();

		vgUI::UIController::getSingleton().RemoveAllPages();

		vgPropertiesViewBar* pageViewBar = vgUI::UIController::getSingleton().GetPropertiesViewBar();

		s_ParamArray.clear();
		PropertiesParam param;

#if VGK_LANG_CHS
		param.label = "MOD物体坐标值设置";
		param.typeId = PROP_ITEM_GROUP;
		param.dataType = PROP_DATA_NONE;
		param.connectedPtr = NULL;
		param.comment = "设置相机的坐标";
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

		param.label = "体块层数";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_INT;
		param.connectedPtr = &m_floor;
		param.comment = "设置体块层数";
		s_ParamArray.push_back(param);

		param.label = "体块单层高度";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_INT;
		param.connectedPtr = &m_heightPerFloor;
		param.comment = "设置体块单层高度";
		s_ParamArray.push_back(param);

		param.label = "物体颜色";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_COLOR;
		param.connectedPtr = &_colorRef;
		param.comment = "设置物体默认颜色";
		s_ParamArray.push_back(param);

		param.label = "混合比例";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_FLOAT;
		param.connectedPtr = &m_fColorRatio;
		param.comment = "调整纹理颜色相混合比例";
		s_ParamArray.push_back(param);
#else
		param.label = "MOD Coord";
		param.typeId = PROP_ITEM_GROUP;
		param.dataType = PROP_DATA_NONE;
		param.connectedPtr = NULL;
		param.comment = "";
		s_ParamArray.push_back(param);

		param.label = "X";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_FLOAT;
		param.connectedPtr = &m_posX;
		param.comment = "";
		s_ParamArray.push_back(param);

		param.label = "Y";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_FLOAT;
		param.connectedPtr = &m_posY;
		param.comment = "";
		s_ParamArray.push_back(param);

		param.label = "Z";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_FLOAT;
		param.connectedPtr = &m_posZMinus/*m_posZ*/;
		param.comment = "";
		s_ParamArray.push_back(param);

		param.label = "Others";
		param.typeId = PROP_ITEM_GROUP;
		param.dataType = PROP_DATA_NONE;
		param.connectedPtr = NULL;
		param.comment = string();
		s_ParamArray.push_back(param);

		param.label = "Name";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_STR;
		param.connectedPtr = m_Renderer->getNamePtr();
		param.comment = "";
		s_ParamArray.push_back(param);

		param.label = "FloorSum";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_INT;
		param.connectedPtr = &m_floor;
		param.comment = "";
		s_ParamArray.push_back(param);

		param.label = "HeightPerFloor";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_INT;
		param.connectedPtr = &m_heightPerFloor;
		param.comment = "";
		s_ParamArray.push_back(param);

		param.label = "Model Color";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_COLOR;
		param.connectedPtr = &_colorRef;
		param.comment = "set model color";
		s_ParamArray.push_back(param);

		param.label = "Texture-Color Blend Ratio";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_FLOAT;
		param.connectedPtr = &m_fColorRatio;
		param.comment = "Texture-Color Blend Ratio";
		s_ParamArray.push_back(param);

#endif

		vgPropertyPage* propPage = vgUI::UIController::getSingleton().GetPropPage();
		propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

		propPage->ConnectNode(this, &s_ParamArray);
		pageViewBar->AddTab("Auto Build", propPage);

	}


	void vgSolidBuildEntry::OnSinglePropertyChanged(string paramName)
	{
		vgAutoBuild::SolidBuildNode *pObject = ( vgAutoBuild::SolidBuildNode*) m_Renderer;

#if VGK_LANG_CHS
		if (paramName == "体块层数")
		{
			pObject->setFloor(m_floor);
		}

		if (paramName == "体块单层高度")
		{
			pObject->setHeightPerLayer(m_heightPerFloor);
		}

		if (paramName == "物体颜色")
		{
			vgKernel::ColorVal colorval;
			colorval.setAsColorRef( _colorRef );
			colorval.a = m_fColorRatio;
			pObject->setColor( colorval ); 
		}

		if (paramName == "混合比例")
		{
			vgKernel::ColorVal colorval;
			colorval.setAsColorRef( _colorRef );
			colorval.a = m_fColorRatio;
			pObject->setColor( colorval ); 
		}

#else
		if (paramName == "FloorSum")
		{
			pObject->setFloor(m_floor);
		}

		if (paramName == "HeightPerFloor")
		{
			pObject->setHeightPerLayer(m_heightPerFloor);
		}

		if (paramName == "Model Color")
		{
			vgKernel::ColorVal colorval;
			colorval.setAsColorRef( _colorRef );
			colorval.a = m_fColorRatio;
			pObject->setColor( colorval ); 
		}

		if (paramName == "Texture-Color Blend Ratio")
		{
			vgKernel::ColorVal colorval;
			colorval.setAsColorRef( _colorRef );
			colorval.a = m_fColorRatio;
			pObject->setColor( colorval ); 
		}

#endif

		m_posZ = - m_posZMinus;
		vgKernel::Vec3 offset = vgKernel::Vec3( m_posX, m_posY, m_posZ)
			- pObject->getPosition() - vgKernel::CoordSystem::getSingleton().getProjectionCoord();
		pObject->translate( offset.x, offset.y, offset.z );

		// 更新TREEITEM
		vgUI::UIController::getSingleton().GetWorkSpaceBar()->SetItemText(hTreeItem, m_Renderer->getName());
		pObject->setName( (TCHAR*)m_Renderer->getName().c_str() );

		vgKernel::SelectManager::getSingleton().updateBox();

	}


	void vgSolidBuildEntry::AddGroupTabPage()
	{
		vgUI::UIController::getSingleton().RemoveAllPages();

		getGroupData();

		vgPropertiesViewBar* pageViewBar = vgUI::UIController::getSingleton().GetPropertiesViewBar();

		s_GroupParamArray.clear();
		PropertiesParam param;


#if VGK_LANG_CHS
		// ==========================================================
		param.label = "体块属性";
		param.typeId = PROP_ITEM_GROUP;
		param.dataType = PROP_DATA_NONE;
		param.connectedPtr = NULL;
		param.comment = "数据库参数设置";
		s_GroupParamArray.push_back(param);

		param.label = "体块层数";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_INT;
		param.connectedPtr = &m_groupFloor;
		s_GroupParamArray.push_back(param);

		param.label = "体块单层高度";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_INT;
		param.connectedPtr = &m_groupHeightPerFloor;
		s_GroupParamArray.push_back(param);

		param.label = "物体颜色";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_COLOR;
		param.connectedPtr = &_groupColorRef;
		param.comment = "设值物体默认颜色";
		s_GroupParamArray.push_back(param);

		param.label = "混合比例";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_FLOAT;
		param.connectedPtr = &m_fGroupColorRatio;
		param.comment = "调整纹理颜色相混合比例";
		s_GroupParamArray.push_back(param);

#else
		// ==========================================================
		param.label = "AutoBuildProperty";
		param.typeId = PROP_ITEM_GROUP;
		param.dataType = PROP_DATA_NONE;
		param.connectedPtr = NULL;
		param.comment = "Param";
		s_GroupParamArray.push_back(param);

		param.label = "FloorSum";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_INT;
		param.connectedPtr = &m_groupFloor;
		s_GroupParamArray.push_back(param);

		param.label = "HeightPerFloor";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_INT;
		param.connectedPtr = &m_groupHeightPerFloor;
		s_GroupParamArray.push_back(param);

		param.label = "Model Color";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_COLOR;
		param.connectedPtr = &_groupColorRef;
		param.comment = "set model color";
		s_GroupParamArray.push_back(param);

		param.label = "Texture-Color Blend Ratio";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_FLOAT;
		param.connectedPtr = &m_fGroupColorRatio;
		param.comment = "Texture-Color Blend Ratio";
		s_GroupParamArray.push_back(param);
#endif


		vgPropertyPage* propPage = vgUI::UIController::getSingleton().GetPropPage();
		propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());
		propPage->ConnectNode(this, &s_GroupParamArray);

		pageViewBar->AddTab("Auto Group", propPage);

		vgUI::UIController::getSingleton().SetCurrentSelectedNode(this);
	}

	void vgSolidBuildEntry::OnGroupPropertyChanged(string paramName)
	{
		vgSolidBuildEntry* pSolidBuildEntry;
		vgAutoBuild::SolidBuildNode* pSolidBuildNode;

#if VGK_LANG_CHS
		if (paramName == "体块层数")
		{
			for (int i=0; i<s_group_list.size(); i++)
			{
				pSolidBuildEntry = ((vgSolidBuildEntry*)s_group_list[i]);
				pSolidBuildNode = (vgAutoBuild::SolidBuildNode*)(pSolidBuildEntry->getRender());

				pSolidBuildNode->setFloor(m_groupFloor);
			}
		}

		if (paramName == "体块单层高度")
		{
			for (int i=0; i<s_group_list.size(); i++)
			{
				pSolidBuildEntry = ((vgSolidBuildEntry*)s_group_list[i]);
				pSolidBuildNode = (vgAutoBuild::SolidBuildNode*)(pSolidBuildEntry->getRender());

				pSolidBuildNode->setHeightPerLayer(m_groupHeightPerFloor);
			}
		}

		if (paramName == "物体颜色")
		{
			for (int i=0; i<s_group_list.size(); i++)
			{
				pSolidBuildEntry = ((vgSolidBuildEntry*)s_group_list[i]);
				pSolidBuildNode = (vgAutoBuild::SolidBuildNode*)(pSolidBuildEntry->getRender());

				vgKernel::ColorVal colorval;
				colorval.setAsColorRef( _groupColorRef );
				colorval.a = m_fGroupColorRatio;
				pSolidBuildNode->setColor(colorval);
			}
		}

		if (paramName == "混合比例")
		{
			for (int i=0; i<s_group_list.size(); i++)
			{
				pSolidBuildEntry = ((vgSolidBuildEntry*)s_group_list[i]);
				pSolidBuildNode = (vgAutoBuild::SolidBuildNode*)(pSolidBuildEntry->getRender());

				vgKernel::ColorVal colorval;
				colorval.setAsColorRef( _groupColorRef );
				colorval.a = m_fGroupColorRatio;
				pSolidBuildNode->setColor(colorval);
			}
		}

#else
		if (paramName == "FloorSum")
		{
			for (int i=0; i<s_group_list.size(); i++)
			{
				pSolidBuildEntry = ((vgSolidBuildEntry*)s_group_list[i]);
				pSolidBuildNode = (vgAutoBuild::SolidBuildNode*)(pSolidBuildEntry->getRender());

				pSolidBuildNode->setFloor(m_groupFloor);
			}
		}

		if (paramName == "HeightPerFloor")
		{
			for (int i=0; i<s_group_list.size(); i++)
			{
				pSolidBuildEntry = ((vgSolidBuildEntry*)s_group_list[i]);
				pSolidBuildNode = (vgAutoBuild::SolidBuildNode*)(pSolidBuildEntry->getRender());

				pSolidBuildNode->setHeightPerLayer(m_groupHeightPerFloor);
			}
		}

		if (paramName == "Model Color")
		{
			for (int i=0; i<s_group_list.size(); i++)
			{
				pSolidBuildEntry = ((vgSolidBuildEntry*)s_group_list[i]);
				pSolidBuildNode = (vgAutoBuild::SolidBuildNode*)(pSolidBuildEntry->getRender());

				vgKernel::ColorVal colorval;
				colorval.setAsColorRef( _groupColorRef );
				colorval.a = m_fGroupColorRatio;
				pSolidBuildNode->setColor(colorval);
			}
		}

		if (paramName == "Texture-Color Blend Ratio")
		{
			for (int i=0; i<s_group_list.size(); i++)
			{
				pSolidBuildEntry = ((vgSolidBuildEntry*)s_group_list[i]);
				pSolidBuildNode = (vgAutoBuild::SolidBuildNode*)(pSolidBuildEntry->getRender());

				vgKernel::ColorVal colorval;
				colorval.setAsColorRef( _groupColorRef );
				colorval.a = m_fGroupColorRatio;
				pSolidBuildNode->setColor(colorval);
			}
		}
#endif

		return;
	}

	void vgSolidBuildEntry::onChanged(int eventId, void *param)
	{
		if (eventId == vgKernel::VG_OBS_PROPCHANGED)
		{
			if (s_group_list.size() > 0)
			{
				return ;
			}

			getData();

			if (this == vgUI::UIController::getSingleton().GetCurrentSelectedNode())
			{
				s_ParamArray[1].pProp->SetValue(m_posX);
				s_ParamArray[2].pProp->SetValue(m_posY);
				m_posZMinus = - m_posZ;
				s_ParamArray[3].pProp->SetValue(m_posZMinus/*m_posZ*/);

// 				s_ParamArray[6].pProp->SetValue(m_floor);
// 				s_ParamArray[7].pProp->SetValue(m_heightPerFloor);
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

	}

	CMenu* vgSolidBuildEntry::GetContextMenu()
	{
		CMenu *menu = new CMenu;

		VERIFY(menu->CreatePopupMenu());
 		VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_GOTO, _T("转到")));
 		VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_DELETE,_T("删除")));

		return menu;
	}

	void vgSolidBuildEntry::getData()
	{
		vgAutoBuild::SolidBuildNode *pObject = ( vgAutoBuild::SolidBuildNode*) m_Renderer;

		Vector3 pos = pObject->getPosition();

		m_posX = pos.x + vgKernel::CoordSystem::getSingleton().getProjectionCoord().x;
		m_posY = pos.y + vgKernel::CoordSystem::getSingleton().getProjectionCoord().y;
		m_posZ = pos.z + vgKernel::CoordSystem::getSingleton().getProjectionCoord().z;

		m_posZMinus = - m_posZ;

		m_floor = pObject->getFloor();
		m_heightPerFloor = pObject->getHeightPerLayer();

		_colorRef = pObject->getColor().getAsColorRef();
		m_fColorRatio = pObject->getColor().a;
	}

	void vgSolidBuildEntry::getGroupData()
	{
		vgSolidBuildEntry* pSolidBuildEntry;
		vgAutoBuild::SolidBuildNode* pSolidBuildNode;

		//暂时取组中第一个对象的属性作为组的显示属性
		pSolidBuildEntry = ((vgSolidBuildEntry*)s_group_list[0]);
		pSolidBuildNode = (vgAutoBuild::SolidBuildNode*)(pSolidBuildEntry->getRender());

        m_groupFloor = pSolidBuildNode->getFloor();
		m_groupHeightPerFloor = pSolidBuildNode->getHeightPerLayer();

		_groupColorRef = pSolidBuildNode->getColor().getAsColorRef();
		m_fGroupColorRatio = pSolidBuildNode->getColor().a;	
	}

}//namespace vgCore