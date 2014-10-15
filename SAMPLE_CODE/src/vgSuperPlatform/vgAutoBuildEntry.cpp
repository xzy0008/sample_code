
#include <vgStableHeaders.h>
#include "vgAutoBuildEntry.h"
#include <vgKernel/vgkSelectManager.h>
#include <vgVector/vgAutoBuildNode.h>

#include "vgUIController.h"



namespace vgCore{

	//	PropertiesParam vgObjectEntry::s_ParamArray[s_NumOfParam];


	void vgAutoBuildEntry::OnSinglePropertyChanged(string paramName)
	{

		vgDatabaseEntry::OnSinglePropertyChanged(paramName);

		vgVector::AutoBuildNode *pObject = ( vgVector::AutoBuildNode*) m_Renderer;


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
		Vector3 offset = Vector3( m_posX, m_posY, m_posZ)
			- pObject->getPosition() - vgCore::vgCoordinate::getSingleton().GetSceneCood();
		pObject->translate( offset.x, offset.y, offset.z );
		// 更新TREEITEM
		vgUIController::GetInstance()->GetWorkSpaceBar()->SetItemText(hTreeItem, m_Renderer->getName());
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

			vgVector::AutoBuildNode *pObject = ( vgVector::AutoBuildNode*) m_Renderer;

			Vector3 pos = pObject->getPosition();


			m_posX = pos.x + vgCore::vgCoordinate::getSingleton().GetSceneCood().x;
			m_posY = pos.y + vgCore::vgCoordinate::getSingleton().GetSceneCood().y;
			m_posZ = pos.z + vgCore::vgCoordinate::getSingleton().GetSceneCood().z;

			////TRACE("New Camera Position %.2f %.2f %.2f \n", posPtr->x, posPtr->y, posPtr->z);
			if (this == vgUIController::GetInstance()->GetCurrentSelectedNode())
			{
				s_ParamArray[1].pProp->SetValue(m_posX);
				s_ParamArray[2].pProp->SetValue(m_posY);
				m_posZMinus = - m_posZ;
				s_ParamArray[3].pProp->SetValue(m_posZMinus/*m_posZ*/);
			}
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

		TRACE("%d POS in OnChange : %f, %f, %f \n", this, m_posX, m_posY, m_posZ);

	}

	void vgAutoBuildEntry::AddSingleTabPage()
	{
		TRACE("1: %d POS in AddSingleTabPage : %f, %f, %f \n", this, m_posX, m_posY, m_posZ);

		getData();

		vgUIController::GetInstance()->RemoveAllPages();

		vgPropertiesViewBar* pageViewBar = vgUIController::GetInstance()->GetPropertiesViewBar();

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

		vector<vgDatabase::QueryProfile> profiles = vgDatabase::ProfileManager::getSingleton().GetProfile();

		for (INT i=0; i<profiles.size(); i++)
		{
			if (profiles[i].GetName() != m_profileName)
			{
				param.label = profiles[i].GetName();
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

		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_OPTION_END;
		s_ParamArray.push_back(param);

		vgPropertyPage* propPage = vgUIController::GetInstance()->GetPropPage();
		propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

		propPage->ConnectNode(this, &s_ParamArray);
		pageViewBar->AddTab("AUTO Build", propPage);

		vgDatabaseEntry::AddSingleTabPage();

		TRACE("%d POS in AddSingleTabPage : %f, %f, %f \n", this, m_posX, m_posY, m_posZ);
	}

	void vgAutoBuildEntry::AddGroupTabPage()
	{

		vgUIController::GetInstance()->RemoveAllPages();

		vgPropertiesViewBar* pageViewBar = vgUIController::GetInstance()->GetPropertiesViewBar();

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

		vector<vgDatabase::QueryProfile> profiles = vgDatabase::ProfileManager::getSingleton().GetProfile();

		for (int i=0; i<profiles.size(); i++)
		{
			param.label = profiles[i].GetName();
			param.typeId = PROP_ITEM_DATA;
			param.dataType = PROP_DATA_OPTION_ITEM;
			s_GroupParamArray.push_back(param);
		}

		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_OPTION_END;
		s_GroupParamArray.push_back(param);


		vgPropertyPage* propPage = vgUIController::GetInstance()->GetPropPage();
		propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());
		propPage->ConnectNode(this, &s_GroupParamArray);

		//propPage->ConnectNode(this, s_GroupParamArray, s_NumOfGroupParam);
		pageViewBar->AddTab("MOD Group", propPage);

		vgUIController::GetInstance()->SetCurrentSelectedNode(this);
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
		vgVector::AutoBuildNode *pObject = ( vgVector::AutoBuildNode*) m_Renderer;

		Vector3 pos = pObject->getPosition();

		m_posX = pos.x + vgCore::vgCoordinate::getSingleton().GetSceneCood().x;
		m_posY = pos.y + vgCore::vgCoordinate::getSingleton().GetSceneCood().y;
		m_posZ = pos.z + vgCore::vgCoordinate::getSingleton().GetSceneCood().z;
		m_posZMinus = - m_posZ;
	}

	vgAutoBuildEntry::vgAutoBuildEntry( vgVector::AutoBuildNode* pObject /*= NULL*/ ) : vgDatabaseEntry( VG_ENTRY_MODOBJECT , pObject )
	{
		assert( pObject != NULL );

		Vector3 pos = pObject->getPosition();

		TRACE("%d Auto Build Node pos: %f, %f, %f \n", this, pos.x, pos.y, pos.z);

		m_posX = pos.x + vgCore::vgCoordinate::getSingleton().GetSceneCood().x;
		m_posY = pos.y + vgCore::vgCoordinate::getSingleton().GetSceneCood().y;
		m_posZ = pos.z + vgCore::vgCoordinate::getSingleton().GetSceneCood().z;
		m_posZMinus = - m_posZ;

		m_size = pObject->getSize();

		vgCore::vgCoordinate::getSingleton().registerObserver(this);

		TRACE("POS in Constructor : %f, %f, %f \n", m_posX, m_posY, m_posZ);
	}
}//namespace vgCore