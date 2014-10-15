#include <vgStableHeaders.h>

#include <vgEntry/vgMeshEntry.h>

#include <vgEntry/vgRootEntry.h>
#include <vgMesh/vgmMeshManager.h>
#include <vgKernel/vgkSelectManager.h>
#include <vgUIController/vgEditTreeCtrlEx.h>
#include <vgUIController/vgUIController.h>

#include <vgKernel/vgkPluginManager.h>
#include <vgDatabase/vgdDefinition.h>



// ==============================================================================
float vgMeshEntry::s_group_posX = 0.f;
float vgMeshEntry::s_group_posY = 0.f;
float vgMeshEntry::s_group_posZ = 0.f;
float vgMeshEntry::s_group_posZMinus = 0.f;



float vgMeshEntry::s_group_squareDistFar = 0.f;
float vgMeshEntry::s_group_squareDistNear = 0.f;

bool vgMeshEntry::s_isLodMesh  =  true;

string vgMeshEntry::s_group_item_name;

bool vgMeshEntry::s_group_onEdit = false;


// ==============================================================================

void vgMeshEntry::AddSingleTabPage()
{
	//颜色编辑
	vgMesh::MeshItem *pMesh = ( vgMesh::MeshItem*) m_Renderer;

	vgKernel::ColorVal val;
	val.setAsRGBQUAD( *pMesh->getRgbaQuadRef()->getRGBQUAD());
	_colorRef = val.getAsColorRef();
	m_fColorRatio = pMesh->getRgbaQuadRef()->alpha / 255.0f;


	vgUI::UIController::getSingleton().RemoveAllPages();

	vgPropertiesViewBar* pageViewBar = vgUI::UIController::getSingleton().GetPropertiesViewBar();

	s_ParamArray.clear();
	PropertiesParam param;

	param.label = "VGM物体坐标值设置";
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

	m_posZMinus = - m_posZ;
	param.label = "Z 坐标";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &m_posZMinus;
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

	param.label = "物体材质设置";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = string();
	s_ParamArray.push_back(param);

	param.label = "物体颜色";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_COLOR;
	param.connectedPtr = &_colorRef;
	param.comment = "设值物体默认颜色";
	s_ParamArray.push_back(param);

	param.label = "混合比例";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &m_fColorRatio;
	param.comment = "调整纹理颜色相混合比例";
	s_ParamArray.push_back(param);

	param.label = "Lod";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = "Lod参数设置";
	s_ParamArray.push_back(param);

	param.label = "SquareFar";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &squareDistFar;
	param.comment = "SquareDistFar";
	s_ParamArray.push_back(param);

	param.label = "SquareDistNear";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &squareDistNear;
	param.comment = "SquareDistNear";
	s_ParamArray.push_back(param);

	param.label = "面数";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_CONST_STR;
	param.connectedPtr = &strNumberOfTran;
	param.comment = "物体面数";
	s_ParamArray.push_back(param);

	param.label = "自动LOD标记";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_BOOL;
	param.connectedPtr = &_isLodMesh;
	param.comment = "自动LOD标记";
	s_ParamArray.push_back(param);

	param.label = "数据库";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = "数据库参数设置";
	s_ParamArray.push_back(param);

	// 数据库profile配置 ========================================================
	param.label = "数据库配置";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_OPTION_START;
	param.connectedPtr = &m_profileName;
	s_ParamArray.push_back(param);

	using namespace vgKernel;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGD_DLL_NAME );


	if ( plg != NULL )
	{
		VGK_DLL_DECLARE_CLASSFUNC( plg, ProfileManager, GetProfileListSize, func_profilelistsize );
		VGK_DLL_DECLARE_CLASSFUNC( plg, ProfileManager, GetProfileNameByIndex, func_profilename );

		int profilesize = (*func_profilelistsize)();

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

	// ===========================================================================
	vgPropertyPage* propPage = vgUI::UIController::getSingleton().GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

	//propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
	propPage->ConnectNode(this, &s_ParamArray);

	pageViewBar->AddTab("自动属性", propPage);

	// 调用父类生成Database属性的Tab页
	vgDatabaseEntry::AddSingleTabPage();

	vgUI::UIController::getSingleton().SetCurrentSelectedNode(this);
	//vgKernel::SelectManager::getSingleton().SetSelection(m_meshId);
}

void vgMeshEntry::onChanged(int eventId, void* param)
{
	// 	vgCam::CamManager* cam = vgMesh::MeshManager::getSingleton().getCurrentCamera();
	// 
	// 
	// 	vgKernel::Vec3* posPtr222 = vgMesh::MeshManager::getSingleton().getCurrentCamera()->getCurrentPositionPtr();
	// 	vgKernel::Vec3* posPtr = cam->getCurrentPositionPtr();
	//

	//ASSERT(eventId == vgKernel::VG_OBS_PROPCHANGED);
	
	if (eventId == vgKernel::VG_OBS_PROPCHANGED)
	{
		if (s_group_onEdit)
			return ;

		vgMesh::MeshItem *pMesh = ( vgMesh::MeshItem*) m_Renderer;

		assert(pMesh != NULL);

		vgKernel::Vec3 pos = pMesh->getPosition();
		
		float sdx = pos.x + vgKernel::CoordSystem::getSingleton().getProjectionCoord().x - m_posX;
		float sdy = pos.y + vgKernel::CoordSystem::getSingleton().getProjectionCoord().y - m_posY;
		float sdz = pos.z + vgKernel::CoordSystem::getSingleton().getProjectionCoord().z - m_posZ;

		m_posX = pos.x + vgKernel::CoordSystem::getSingleton().getProjectionCoord().x;
		m_posY = pos.y + vgKernel::CoordSystem::getSingleton().getProjectionCoord().y;
		m_posZ = pos.z + vgKernel::CoordSystem::getSingleton().getProjectionCoord().z;

		TRACE("AXIS child: %.3f, %.3f, %.3f \n", m_posX, m_posY, m_posZ);

		//TRACE("New Camera Position %.2f %.2f %.2f \n", posPtr->x, posPtr->y, posPtr->z);
		// 实现Group Changed
		if (s_group_list.size() > 0 && this == vgUI::UIController::getSingleton().GetCurrentSelectedNode())
		{
			
			OnGroupChanged( sdx,  sdy,  sdz);
			//return ;
		}
		else if (this == vgUI::UIController::getSingleton().GetCurrentSelectedNode())
		{
			s_ParamArray[1].pProp->SetValue(m_posX);
			s_ParamArray[2].pProp->SetValue(m_posY);
			m_posZMinus = - m_posZ;
			s_ParamArray[3].pProp->SetValue(m_posZMinus);
		}

		return ;
	}	

	if (eventId == vgKernel::VG_OBS_SELECTCHAGNED)
	{
		vgUI::UIController::getSingleton().SelectNode(this);

		return ;
	}

	if (eventId == vgKernel::VG_OBS_ADDSELECTION)
	{
		vgUI::UIController::getSingleton().AddSelection(this);

		return ;
	}

	if (eventId == vgKernel::VG_OBS_GROUPUPDATE)
	{
		vgUI::UIController::getSingleton().RemoveAllPages();
		AddNodeTabs();
	}
}

CMenu* vgMeshEntry::GetContextMenu()
{
	CMenu *menu = new CMenu;

#if VGK_LANG_CHS
	VERIFY(menu->CreatePopupMenu());
	VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_GOTO, _T("转到")));
	VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_DELETE,_T("删除")));
	VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_SHOWPROP, _T("隐藏/显示属性栏")));
#else
	VERIFY(menu->CreatePopupMenu());
	VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_GOTO, _T("Turn to")));
	VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_DELETE,_T("Delete")));
	VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_SHOWPROP, _T("Hide/show properties")));

#endif

	return menu;
}

void vgMeshEntry::AddGroupTabPage()
{
	// AfxMessageBox("Add Group Tabpage here !");

	vgUI::UIController::getSingleton().RemoveAllPages();

	vgPropertiesViewBar* pageViewBar = vgUI::UIController::getSingleton().GetPropertiesViewBar();
	
	vgKernel::SelectManager::getSingleton().updateBox();
	vgKernel::Vec3 axPos =  vgKernel::SelectManager::getSingleton().getSelectedCenter();
	
	TRACE("asix position %f %f %f \n", axPos.x, axPos.y, axPos.z);
	s_group_item_name = "";

	for (int i=0; i<s_group_list.size(); i++)
	{
		s_group_item_name += s_group_list[i]->GetName(); 
		s_group_item_name += " ";
	}

	s_group_posX = axPos.x + vgKernel::CoordSystem::getSingleton().getProjectionCoord().x;
	s_group_posY = axPos.y + vgKernel::CoordSystem::getSingleton().getProjectionCoord().y;
	s_group_posZ = axPos.z + vgKernel::CoordSystem::getSingleton().getProjectionCoord().z;
	s_group_posZMinus = -s_group_posZ;



	s_group_squareDistFar = squareDistFar;
	s_group_squareDistNear = squareDistNear;

	s_GroupParamArray.clear();
	PropertiesParam param;

	param.label = "Group VGM坐标中点设置";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = "设置Group中点的坐标";
	s_GroupParamArray.push_back(param);

	param.label = "X 坐标";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &s_group_posX;
	param.comment = "设置X坐标";
	s_GroupParamArray.push_back(param);


	param.label = "Y 坐标";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &s_group_posY;
	param.comment = "设置Y坐标";
	s_GroupParamArray.push_back(param);

	param.label = "Z 坐标";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &s_group_posZMinus;
	param.comment = "设置Z坐标";
	s_GroupParamArray.push_back(param);

	param.label = "其他设置";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = string();
	s_GroupParamArray.push_back(param);

	param.label = "物体名称";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_CONST_STR;
	param.connectedPtr = &s_group_item_name;
	param.comment = "物体的名称";
	s_GroupParamArray.push_back(param);

	param.label = "物体材质设置";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = "物体材质设置";
	s_GroupParamArray.push_back(param);

	param.label = "物体颜色";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_COLOR;
	param.connectedPtr = &_colorRef;
	param.comment = "设值物体默认颜色";
	s_GroupParamArray.push_back(param);

	param.label = "混合比例";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &m_fColorRatio;
	param.comment = "调整纹理颜色相混合比例";
	s_GroupParamArray.push_back(param);

	param.label = "Lod";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = "Lod参数设置";
	s_GroupParamArray.push_back(param);

	param.label = "SquareDistFar";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &s_group_squareDistFar;
	param.comment = "SquareDistFar";
	s_GroupParamArray.push_back(param);

	param.label = "SquareDistNear";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &s_group_squareDistNear;
	param.comment = "SquareDistNear";
	s_GroupParamArray.push_back(param);

	param.label = "自动lod标志";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_BOOL;
	param.connectedPtr = &s_isLodMesh;
	param.comment = "自动lod标志";
	s_GroupParamArray.push_back(param);


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
	pageViewBar->AddTab("Group属性", propPage);

	vgUI::UIController::getSingleton().SetCurrentSelectedNode(this);
}

void vgMeshEntry::OnGroupChanged(float sdx, float sdy, float sdz)
{
	if (this != vgUI::UIController::getSingleton().GetCurrentSelectedNode())
		return;

	if (s_group_onEdit)
		return ;

	// 不精确的结果，改用直接计算的方法 
	//vgKernel::Vec3 axPos =  vgKernel::SelectManager::getSingleton().getSelectedCenter(true);
	//s_group_posX = axPos.x;
	//s_group_posY = axPos.y;
	//s_group_posZ = axPos.z;

	//s_GroupParamArray[1].pProp->SetValue(s_group_posX);
	//s_GroupParamArray[2].pProp->SetValue(s_group_posY);
	//s_GroupParamArray[3].pProp->SetValue(s_group_posZ);

	// 有可能和当前的坐标轴坐标不一致 但是正确的计算结果 下次渲染时坐标轴将重算
	s_group_posX += sdx;
	s_group_posY += sdy;
	s_group_posZ += sdz;

	s_GroupParamArray[1].pProp->SetValue(s_group_posX);
	s_GroupParamArray[2].pProp->SetValue(s_group_posY);
	s_group_posZMinus = - s_group_posZ;
	s_GroupParamArray[3].pProp->SetValue(s_group_posZMinus);

	// TRACE("AXIS : %.3f, %.3f, %.3f \n", s_group_posX, s_group_posY, s_group_posZ);

	//	s_group_lastPosX = s_group_posX;
	//	s_group_lastPosY = s_group_posY;
	//	s_group_lastPosZ = s_group_posZ;
}

void vgMeshEntry::OnSinglePropertyChanged(string paramName)
{
	vgDatabaseEntry::OnSinglePropertyChanged(paramName);

	m_posZ = -m_posZMinus;

 	// 更新TREEITEM
 	vgUI::UIController::getSingleton().GetWorkSpaceBar()->SetItemText(hTreeItem, 
 		GetName() );
 
 	vgKernel::Vec3 aa = vgKernel::CoordSystem::getSingleton().getProjectionCoord();
 
 	// undo redo ==============================================
 	vgKernel::Vec3 offset = vgKernel::Vec3( m_posX, m_posY, m_posZ)
 		- this->getRender()->getBoundingBox().getCenter() - vgKernel::CoordSystem::getSingleton().getProjectionCoord();
 	
 	vgKernel::SelectManager::getSingleton().setsumtrans\
 		(offset);
 
 	// ========================================================
 	this->getRender()->moveTo(m_posX - aa.x, m_posY - aa.y, m_posZ - aa.z);
 
 	vgKernel::SelectManager::getSingleton().updateBox();


 
 	vgMesh::MeshItem* pMeshItem = dynamic_cast<vgMesh::MeshItem*>(this->getRender());
 
 	ASSERT(pMeshItem != NULL);

 	pMeshItem->setSquareDistFar(squareDistFar);
 
 	pMeshItem->setSquareDistNear(squareDistNear);
 
 	pMeshItem->setLodMeshFlag( _isLodMesh );

	// 颜色编辑========================================================

	vgKernel::ColorVal colorval;
	colorval.setAsColorRef( _colorRef );
	vgKernel::RgbaQuad color;
	color = colorval.getAsRGBQUAD();  
	pMeshItem->setColorableValue( color ); 

	pMeshItem->getRgbaQuadRef()->alpha = m_fColorRatio * 255;

}

void vgMeshEntry::OnGroupPropertyChanged(string paramName)
{
	
 	vgMesh::MeshItem* pMeshItem;
 	vgMeshEntry *pMeshEntry;
 
	vgDatabaseEntry::OnGroupPropertyChanged(paramName);

 	if (paramName == "SquareDistFar")
 	{
 		for (int i=0; i<s_group_list.size(); i++)
 		{
 			pMeshEntry = ((vgMeshEntry*)s_group_list[i]);
 			pMeshItem = (vgMesh::MeshItem*)(pMeshEntry->getRender());
 
 			//pMeshItem->setSquareDistNear(s_group_squareDistNear);
 			pMeshItem->setSquareDistFar(s_group_squareDistFar);
 
 			pMeshEntry->squareDistFar = s_group_squareDistFar;
 		}
 
 		return ;
 	}
 	else if (paramName == "SquareDistNear")
 	{
 		for (int i=0; i<s_group_list.size(); i++)
 		{
 			pMeshEntry = ((vgMeshEntry*)s_group_list[i]);
 			pMeshItem = (vgMesh::MeshItem*)(pMeshEntry->getRender());
 
 			pMeshItem->setSquareDistNear(s_group_squareDistNear);
 			//pMeshItem->setSquareDistFar(s_group_squareDistFar);
 
 			pMeshEntry->squareDistNear = s_group_squareDistNear;
 		}
 
 		return ;
 	}
 	else if (paramName == "自动lod标志")
 	{
 		for (int i=0; i<s_group_list.size(); i++)
 		{
 			pMeshEntry = ((vgMeshEntry*)s_group_list[i]);
 			pMeshItem = (vgMesh::MeshItem*)(pMeshEntry->getRender());
 
 			pMeshItem->setLodMeshFlag(s_isLodMesh);
 
 			pMeshEntry->_isLodMesh = s_isLodMesh;
 		}
 
 		return ;
 	}	
	else if (paramName == "物体颜色")
	{
		for (int i=0; i<s_group_list.size(); i++)
		{
			pMeshEntry = ((vgMeshEntry*)s_group_list[i]);
			pMeshItem = (vgMesh::MeshItem*)(pMeshEntry->getRender());

			vgKernel::ColorVal colorval;
			colorval.setAsColorRef( _colorRef );
			vgKernel::RgbaQuad color;
			color = colorval.getAsRGBQUAD();  
			pMeshItem->setColorableValue( color ); 

			pMeshItem->getRgbaQuadRef()->alpha = m_fColorRatio * 255;

		}
	}
	else if (paramName == "混合比例")
	{
		for (int i=0; i<s_group_list.size(); i++)
		{
			pMeshEntry = ((vgMeshEntry*)s_group_list[i]);
			pMeshItem = (vgMesh::MeshItem*)(pMeshEntry->getRender());

			vgKernel::ColorVal colorval;
			colorval.setAsColorRef( _colorRef );
			vgKernel::RgbaQuad color;
			color = colorval.getAsRGBQUAD();  
			pMeshItem->setColorableValue( color ); 

			pMeshItem->getRgbaQuadRef()->alpha = m_fColorRatio * 255;

		}
	}
 	else if (paramName == "数据库配置")
 	{
		return ;
 	}
 
 
	s_group_posZ = -s_group_posZMinus;

 	s_group_onEdit = true;
 
 	//const float& dx = s_group_posX - s_group_lastPosX;
 	//const float& dy = s_group_posY - s_group_lastPosY;
 	//const float& dz = s_group_posZ - s_group_lastPosZ;
 
 	vgKernel::Vec3 axpos = vgKernel::SelectManager::getSingleton().getSelectedCenter(true); 
 
 	const float& dx = s_group_posX - axpos.x - vgKernel::CoordSystem::getSingleton().getProjectionCoord().x;
 	const float& dy = s_group_posY - axpos.y - vgKernel::CoordSystem::getSingleton().getProjectionCoord().y;
 	const float& dz = s_group_posZ - axpos.z - vgKernel::CoordSystem::getSingleton().getProjectionCoord().z;
 
 	vgKernel::SelectManager::getSingleton().translateGroup(dx, dy, dz);
 
 	for (int i=0; i<s_group_list.size(); i++)
 	{
 		((vgMeshEntry*)s_group_list[i])->m_posX = ((vgMeshEntry*)s_group_list[i])->m_posX + dx;
 		((vgMeshEntry*)s_group_list[i])->m_posY = ((vgMeshEntry*)s_group_list[i])->m_posY + dy;
 		((vgMeshEntry*)s_group_list[i])->m_posZ = ((vgMeshEntry*)s_group_list[i])->m_posZ + dz;
 	}
 

 	axpos = vgKernel::SelectManager::getSingleton().getSelectedCenter(true); 
 	
 	if (abs(axpos.x - s_group_posX) > 1e-3 || abs(axpos.y - s_group_posY) > 1e-3 || abs(axpos.z - s_group_posZ) > 1e-3)
 	{
 		//char outBuffer[128];
 
 		//sprintf_s(outBuffer, 128, "检测到坐标误差 x: %f y:%f z:%f 请检查", axpos.x - s_group_posX, axpos.y - s_group_posY, axpos.z - s_group_posZ);
 		//AfxMessageBox(outBuffer);
 		TRACE(" %.3f %.3f %.3f -  %.3f %.3f %.3f ", s_group_posX, s_group_posY, s_group_posZ, axpos.x, axpos.y, axpos.z);
 	}
 
 	s_group_onEdit = false;
}
