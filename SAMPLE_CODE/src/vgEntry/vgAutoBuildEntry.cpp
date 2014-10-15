
#include <vgStableHeaders.h>
#include "vgentry/vgAutoBuildEntry.h"
#include <vgKernel/vgkSelectManager.h>
#include <vgAutoBuild/vgAutoBuildNode.h>

#include <vgUIController/vgUIController.h>
#include <vgDatabase/vgdDefinition.h>
#include <vgKernel/vgkPluginManager.h>


namespace vgCore{

	//	PropertiesParam vgObjectEntry::s_ParamArray[s_NumOfParam];


	void vgAutoBuildEntry::OnSinglePropertyChanged(string paramName)
	{

		vgDatabaseEntry::OnSinglePropertyChanged(paramName);

		vgAutoBuild::AutoBuildNode *pObject = ( vgAutoBuild::AutoBuildNode*) m_Renderer;


#if VGK_LANG_CHS
		if (paramName == "自动建模高度")
		{
			pObject->setSize(m_size);
			
			return ;
		}
#else
		if (paramName == "Height")
		{
			pObject->setSize(m_size);

			return ;
		}
#endif

		//m_pCamera->setCurrentPosition(vgKernel::Vec3(m_eyePosX, m_eyePosY, m_eyePosZ));
		m_posZ = - m_posZMinus;
		vgKernel::Vec3 offset = vgKernel::Vec3( m_posX, m_posY, m_posZ)
			- pObject->getPosition() - vgKernel::CoordSystem::getSingleton().getProjectionCoord();
		pObject->translate( offset.x, offset.y, offset.z );
		// 更新TREEITEM
		vgUI::UIController::getSingleton().GetWorkSpaceBar()->SetItemText(hTreeItem, m_Renderer->getName());
		pObject->setName( (TCHAR*)m_Renderer->getName().c_str() );

		vgKernel::SelectManager::getSingleton().updateBox();

	}

	void vgAutoBuildEntry::onChanged(int eventId, void *param)
	{

		if (eventId == vgKernel::VG_OBS_PROPCHANGED)
		{
			if (s_group_list.size() > 0)
			{
				return ;
			}

			vgAutoBuild::AutoBuildNode *pObject = ( vgAutoBuild::AutoBuildNode*) m_Renderer;

			Vector3 pos = pObject->getPosition();


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

	void vgAutoBuildEntry::AddSingleTabPage()
	{
		TRACE("1: %d POS in AddSingleTabPage : %f, %f, %f \n", this, m_posX, m_posY, m_posZ);

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

		param.label = "自动建模高度";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_INT;
		param.connectedPtr = &m_size;
		param.comment = "设置物体自动增长的高度";
		s_ParamArray.push_back(param);

		// 数据库profile配置 ========================================================
		param.label = "数据库配置";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_OPTION_START;
		param.connectedPtr = &m_profileName;
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

		param.label = "Height";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_INT;
		param.connectedPtr = &m_size;
		param.comment = "";
		s_ParamArray.push_back(param);

		// 数据库profile配置 ========================================================
		param.label = "Database";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_OPTION_START;
		param.connectedPtr = &m_profileName;
		s_ParamArray.push_back(param);
#endif

		using namespace vgKernel;
		Plugin* plg = PluginManager::getSingleton().getPluginRef( VGD_DLL_NAME );

		if ( plg != NULL )
		{
			VGK_DLL_DECLARE_CLASSFUNC( plg, ProfileManager, GetProfileListSize, func_profilelistsize );
			VGK_DLL_DECLARE_CLASSFUNC( plg, ProfileManager, GetProfileNameByIndex, func_profilename );

			int profilesize = (*func_profilelistsize)();

			// 		vector<vgDatabase::QueryProfile> profiles = vgDatabase::ProfileManager::getSingleton().GetProfiles();

			for (INT i=0; i<profilesize; i++)
			{
				String profilename = (*func_profilename)(i);

				if (profilename != m_profileName)
				{
					param.label = profilename;
					param.typeId = PROP_ITEM_DATA;
					param.dataType = PROP_DATA_OPTION_ITEM;
					s_ParamArray.push_back(param);
				}
			}

			if (m_profileName != "")
			{
				param.label = "";
				param.typeId = PROP_ITEM_DATA;
				param.dataType = PROP_DATA_OPTION_ITEM;
				s_ParamArray.push_back(param);
			}

		}

		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_OPTION_END;
		s_ParamArray.push_back(param);

		vgPropertyPage* propPage = vgUI::UIController::getSingleton().GetPropPage();
		propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

		propPage->ConnectNode(this, &s_ParamArray);
		pageViewBar->AddTab("AUTO Build", propPage);

		vgDatabaseEntry::AddSingleTabPage();

		TRACE("%d POS in AddSingleTabPage : %f, %f, %f \n", this, m_posX, m_posY, m_posZ);
	}

	void vgAutoBuildEntry::AddGroupTabPage()
	{

		vgUI::UIController::getSingleton().RemoveAllPages();

		vgPropertiesViewBar* pageViewBar = vgUI::UIController::getSingleton().GetPropertiesViewBar();

		s_GroupParamArray.clear();
		PropertiesParam param;


#if VGK_LANG_CHS
		// Database ==========================================================
		param.label = "数据库";
		param.typeId = PROP_ITEM_GROUP;
		param.dataType = PROP_DATA_NONE;
		param.connectedPtr = NULL;
		param.comment = "数据库参数设置";
		s_GroupParamArray.push_back(param);

		s_groupProfileName = "";

		param.label = "数据库配置";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_OPTION_START;
		param.connectedPtr = &s_groupProfileName;
		s_GroupParamArray.push_back(param);
#else
		// Database ==========================================================
		param.label = "Database";
		param.typeId = PROP_ITEM_GROUP;
		param.dataType = PROP_DATA_NONE;
		param.connectedPtr = NULL;
		param.comment = "Param";
		s_GroupParamArray.push_back(param);

		s_groupProfileName = "";

		param.label = "Config";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_OPTION_START;
		param.connectedPtr = &s_groupProfileName;
		s_GroupParamArray.push_back(param);
#endif

		using namespace vgKernel;
		Plugin* plg = PluginManager::getSingleton().getPluginRef( VGD_DLL_NAME );

		if ( plg != NULL )
		{
			VGK_DLL_DECLARE_CLASSFUNC( plg, ProfileManager, GetProfileListSize, func_profilelistsize );
			VGK_DLL_DECLARE_CLASSFUNC( plg, ProfileManager, GetProfileNameByIndex, func_profilename );

			int profilesize = (*func_profilelistsize)();

			for (int i=0; i<profilesize; i++)
			{
				String profilename = (*func_profilename)(i);

				param.label = profilename;
				param.typeId = PROP_ITEM_DATA;
				param.dataType = PROP_DATA_OPTION_ITEM;
				s_GroupParamArray.push_back(param);
			}

		}

		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_OPTION_END;
		s_GroupParamArray.push_back(param);


		vgPropertyPage* propPage = vgUI::UIController::getSingleton().GetPropPage();
		propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());
		propPage->ConnectNode(this, &s_GroupParamArray);

		//propPage->ConnectNode(this, s_GroupParamArray, s_NumOfGroupParam);
		pageViewBar->AddTab("MOD Group", propPage);

		vgUI::UIController::getSingleton().SetCurrentSelectedNode(this);
	}

	void vgAutoBuildEntry::OnGroupPropertyChanged(string paramName)
	{
		vgDatabaseEntry::OnGroupPropertyChanged(paramName);
	}


	CMenu* vgAutoBuildEntry::GetContextMenu()
	{
		CMenu *menu = new CMenu;

		VERIFY(menu->CreatePopupMenu());
		//VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_GOTO, _T("转到")));
		//VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_DELETE,_T("删除")));

		return menu;
	}

	void vgAutoBuildEntry::getData()
	{
		vgAutoBuild::AutoBuildNode *pObject = ( vgAutoBuild::AutoBuildNode*) m_Renderer;

		Vector3 pos = pObject->getPosition();

		m_posX = pos.x + vgKernel::CoordSystem::getSingleton().getProjectionCoord().x;
		m_posY = pos.y + vgKernel::CoordSystem::getSingleton().getProjectionCoord().y;
		m_posZ = pos.z + vgKernel::CoordSystem::getSingleton().getProjectionCoord().z;
		m_posZMinus = - m_posZ;
	}

	vgAutoBuildEntry::vgAutoBuildEntry( 
		vgAutoBuild::AutoBuildNode* pObject /*= NULL*/ ) :
	vgDatabaseEntry( pObject )
	{
		assert( pObject != NULL );

		Vector3 pos = pObject->getPosition();

		TRACE("%d Auto Build Node pos: %f, %f, %f \n", this, pos.x, pos.y, pos.z);

		m_posX = pos.x + vgKernel::CoordSystem::getSingleton().getProjectionCoord().x;
		m_posY = pos.y + vgKernel::CoordSystem::getSingleton().getProjectionCoord().y;
		m_posZ = pos.z + vgKernel::CoordSystem::getSingleton().getProjectionCoord().z;
		m_posZMinus = - m_posZ;

		m_size = pObject->getSize();

		vgKernel::CoordSystem::getSingleton().registerObserver(this);

		TRACE("POS in Constructor : %f, %f, %f \n", m_posX, m_posY, m_posZ);
	}
}//namespace vgCore