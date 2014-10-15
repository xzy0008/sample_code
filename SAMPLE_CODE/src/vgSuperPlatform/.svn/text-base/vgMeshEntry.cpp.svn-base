#include <vgStableHeaders.h>
#include "vgMeshEntry.h"
#include <vgMesh/vgmMeshManager.h>
#include <vgKernel/vgkSelectManager.h>
#include <vgEditTreeCtrlEx.h>
#include "vgUIController.h"

#include <vgDatabase/vgdDatabaseManager.h>
#include <vgDatabase/vgdProfileManager.h>

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


	vgUIController::GetInstance()->RemoveAllPages();

	vgPropertiesViewBar* pageViewBar = vgUIController::GetInstance()->GetPropertiesViewBar();

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

	param.label = "显示";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_BOOL;
	param.connectedPtr = &_visible;
	param.comment = "";
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

	// ===========================================================================
	vgPropertyPage* propPage = vgUIController::GetInstance()->GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

	//propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
	propPage->ConnectNode(this, &s_ParamArray);

	pageViewBar->AddTab("自动属性", propPage);

	// 调用父类生成Database属性的Tab页
	vgDatabaseEntry::AddSingleTabPage();

	vgUIController::GetInstance()->SetCurrentSelectedNode(this);
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
		
		float sdx = pos.x + vgCore::vgCoordinate::getSingleton().GetSceneCood().x - m_posX;
		float sdy = pos.y + vgCore::vgCoordinate::getSingleton().GetSceneCood().y - m_posY;
		float sdz = pos.z + vgCore::vgCoordinate::getSingleton().GetSceneCood().z - m_posZ;

		m_posX = pos.x + vgCore::vgCoordinate::getSingleton().GetSceneCood().x;
		m_posY = pos.y + vgCore::vgCoordinate::getSingleton().GetSceneCood().y;
		m_posZ = pos.z + vgCore::vgCoordinate::getSingleton().GetSceneCood().z;

		TRACE("AXIS child: %.3f, %.3f, %.3f \n", m_posX, m_posY, m_posZ);

		//TRACE("New Camera Position %.2f %.2f %.2f \n", posPtr->x, posPtr->y, posPtr->z);
		// 实现Group Changed
		if (s_group_list.size() > 0 && this == vgUIController::GetInstance()->GetCurrentSelectedNode())
		{
			
			OnGroupChanged( sdx,  sdy,  sdz);
			//return ;
		}
		else if (this == vgUIController::GetInstance()->GetCurrentSelectedNode())
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
		vgUIController::GetInstance()->SelectNode(this);

		return ;
	}

	if (eventId == vgKernel::VG_OBS_ADDSELECTION)
	{
		vgUIController::GetInstance()->AddSelection(this);

		return ;
	}

	if (eventId == vgKernel::VG_OBS_GROUPUPDATE)
	{
		vgUIController::GetInstance()->RemoveAllPages();
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

	vgUIController::GetInstance()->RemoveAllPages();

	vgPropertiesViewBar* pageViewBar = vgUIController::GetInstance()->GetPropertiesViewBar();
	
	vgKernel::SelectManager::getSingleton().updateBox();
	vgKernel::Vec3 axPos =  vgKernel::SelectManager::getSingleton().getSelectedCenter();
	
	TRACE("asix position %f %f %f \n", axPos.x, axPos.y, axPos.z);
	s_group_item_name = "";

	for (int i=0; i<s_group_list.size(); i++)
	{
		s_group_item_name += s_group_list[i]->GetName(); 
		s_group_item_name += " ";
	}

	s_group_posX = axPos.x + vgCore::vgCoordinate::getSingleton().GetSceneCood().x;
	s_group_posY = axPos.y + vgCore::vgCoordinate::getSingleton().GetSceneCood().y;
	s_group_posZ = axPos.z + vgCore::vgCoordinate::getSingleton().GetSceneCood().z;
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
	pageViewBar->AddTab("Group属性", propPage);

	vgUIController::GetInstance()->SetCurrentSelectedNode(this);
}

void vgMeshEntry::OnGroupChanged(float sdx, float sdy, float sdz)
{
	if (this != vgUIController::GetInstance()->GetCurrentSelectedNode())
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
 	vgUIController::GetInstance()->GetWorkSpaceBar()->SetItemText(hTreeItem, 
 		GetName() );
 
 	Vector3 aa = vgCore::vgCoordinate::getSingleton().GetSceneCood();
 
 	// undo redo ==============================================
 	Vector3 offset = Vector3( m_posX, m_posY, m_posZ)
 		- this->getRender()->getBoundingBox().getCenter() - vgCore::vgCoordinate::getSingleton().GetSceneCood();
 	
 	vgKernel::SelectManager::getSingleton().setsumtrans\
 		(vgKernel::Vec3(offset.x,offset.y,offset.z));
 
 	// ========================================================
 	this->getRender()->moveTo(m_posX - aa.x, m_posY - aa.y, m_posZ - aa.z);
 
 	vgKernel::SelectManager::getSingleton().updateBox();


 
 	vgMesh::MeshItem* pMeshItem = dynamic_cast<vgMesh::MeshItem*>(this->getRender());
 
 	ASSERT(pMeshItem != NULL);

	pMeshItem->setVisible( _visible );

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
 
 	const float& dx = s_group_posX - axpos.x - vgCore::vgCoordinate::getSingleton().GetSceneCood().x;
 	const float& dy = s_group_posY - axpos.y - vgCore::vgCoordinate::getSingleton().GetSceneCood().y;
 	const float& dz = s_group_posZ - axpos.z - vgCore::vgCoordinate::getSingleton().GetSceneCood().z;
 
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

vgMeshEntry::vgMeshEntry( vgMesh::MeshItem* meshitem ) : vgDatabaseEntry( VG_ENTRY_MESH , meshitem )
{
	assert( meshitem != NULL );

	vgKernel::Vec3 pos = meshitem->getPosition();

	_visible = meshitem->getVisible();

	m_posX = pos.x + vgCore::vgCoordinate::getSingleton().GetSceneCood().x;
	m_posY = pos.y + vgCore::vgCoordinate::getSingleton().GetSceneCood().y;
	m_posZ = pos.z + vgCore::vgCoordinate::getSingleton().GetSceneCood().z;

	m_posZMinus = -m_posZ;

	squareDistNear = meshitem->getSquareDistNear();
	squareDistFar = meshitem->getSquareDistFar();

	char buffer[32];

	sprintf_s(buffer, 32, "%d", meshitem->getNumOfTriangles());

	strNumberOfTran = buffer;

	vgCore::vgCoordinate::getSingleton().registerObserver(this);

	_isLodMesh = meshitem->getLodMeshFlag();

	//颜色编辑	
	vgKernel::ColorVal val;
	val.setAsRGBQUAD( *meshitem->getRgbaQuadRef()->getRGBQUAD());
	_colorRef = val.getAsColorRef();
	m_fColorRatio = meshitem->getRgbaQuadRef()->alpha / 255.0f;
}