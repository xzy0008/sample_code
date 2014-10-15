#include <vgStableHeaders.h>
#include <vgEntry/vgCamMgrEntry.h>

#include <vgUIController/vgPropertyPage.h>
#include <vgUIController/vgUIController.h>

#include <vgKernel/vgkVec3.h>
//#include <vgMesh/vgmMeshManager.h>


#include <vgCam/vgcaCamManager.h>



PropertiesParam vgCamMgrEntry::s_ParamArray[s_NumOfParam];

vgCamMgrEntry::vgCamMgrEntry() :
vgBaseEntry(  NULL )
{
	/*m_eyePosX = 0.f;
	m_eyePosY = 0.f;
	m_eyePosZ = 0.f;*/
	m_eyePosX = vgCam::CamManager::getSingleton().getCurrentPosition().x;
	m_eyePosY = vgCam::CamManager::getSingleton().getCurrentPosition().y;
	m_eyePosZ = vgCam::CamManager::getSingleton().getCurrentPosition().z;
	m_eyePosZMinus = - m_eyePosZ;
	m_tarPosX = 0.f;
	m_tarPoxY = 0.f;
	m_tarPoxZ = 0.f;

	m_upPosX = 0.f;
	m_upPosY = 1.f;
	m_upPoxZ = 0.f;

	m_hAngle = 0.f;
	m_vAngle = 0.f;

	m_speend	= vgCam::CamManager::getSingleton().getForwardVelocity();
	m_turningSpeed	= vgCam::CamManager::getSingleton().getTurningVelocity();
	m_pitchSpeed	= vgCam::CamManager::getSingleton().getPitchVelocity();
	m_turningDegree = vgCam::CamManager::getSingleton().getHeadingDegrees();
	m_pitchDegree	= vgCam::CamManager::getSingleton().getPitchDegrees();
	//m_speend = 0.f;
	//m_turningSpeed = 0.f;
	//m_pitchSpeed = 0.f;

	vgKernel::Vec3 eillipseVec = vgCam::CamManager::getSingleton().getEillipseVec();

	m_eillipX = eillipseVec.x;
	m_eillipY = eillipseVec.y;
	m_eillipZ = eillipseVec.z;

	vgCam::CamManager::getSingleton().registerObserver(this);

#if VGK_LANG_CHS
	m_sCaption = "当前相机";
#else
	m_sCaption = "Current Camera";
#endif

	vgKernel::CoordSystem::getSingleton().registerObserver(this);

	this->onChanged(vgKernel::VG_OBS_PROPCHANGED, NULL);
}
vgCamMgrEntry::~vgCamMgrEntry(void)
{
	vgCam::CamManager::getSingleton().unregisterObserver(this);

	vgKernel::CoordSystem::getSingleton().unregisterObserver(this);
}

void vgCamMgrEntry::OnPropertyChanged(string paramName)
{
	m_eyePosZ = -m_eyePosZMinus;
	vgKernel::Vec3 aa = vgKernel::CoordSystem::getSingleton().getProjectionCoord();

	vgCam::CamManager::getSingleton().setCurrentPosition(
		vgKernel::Vec3(m_eyePosX - aa.x, m_eyePosY - aa.y, m_eyePosZ - aa.z));

	vgCam::CamManager::getSingleton().setForwardVelocity(m_speend);
	vgCam::CamManager::getSingleton().setTurningVelocity(m_turningSpeed);
	vgCam::CamManager::getSingleton().setPitchVelocity(m_pitchSpeed);
	vgCam::CamManager::getSingleton().setHeadingDegrees(m_turningDegree);
	vgCam::CamManager::getSingleton().setPitchDegrees(m_pitchDegree);

	vgCam::CamManager::getSingleton().setUpAndDownMultiply( m_upAndDownMultiply );
	
	vgCam::CamManager::getSingleton().setEillipseVec(vgKernel::Vec3(m_eillipX, m_eillipY, m_eillipZ));

	// 更新TREEITEM
	vgUI::UIController::getSingleton().GetWorkSpaceBar()->SetItemText(hTreeItem, m_sCaption);
}

void vgCamMgrEntry::onChanged(int eventId, void *param)
{

	ASSERT (eventId == vgKernel::VG_OBS_PROPCHANGED);
// 	vgCam::CamManager* cam = vgMesh::MeshManager::getSingleton().getCurrentCamera();
// 
// 
// 	vgKernel::Vec3* posPtr222 = vgMesh::MeshManager::getSingleton().getCurrentCamera()->getCurrentPositionPtr();
// 	vgKernel::Vec3* posPtr = cam->getCurrentPositionPtr();
//
	getData();

	////TRACE("New Camera Position %.2f %.2f %.2f \n", posPtr->x, posPtr->y, posPtr->z);
	if (this == vgUI::UIController::getSingleton().GetCurrentSelectedNode())
	{
		s_ParamArray[3].pProp->SetValue(m_eyePosX);
		s_ParamArray[4].pProp->SetValue(m_eyePosY);
		m_eyePosZMinus = - m_eyePosZ;
		s_ParamArray[5].pProp->SetValue(m_eyePosZMinus/*m_eyePosZ*/);

		s_ParamArray[10].pProp->SetValue( m_speend );
		s_ParamArray[11].pProp->SetValue( m_turningSpeed );
		s_ParamArray[12].pProp->SetValue( m_pitchSpeed );
		s_ParamArray[13].pProp->SetValue( m_upAndDownMultiply );
		
		s_ParamArray[7].pProp->SetValue( m_turningDegree );
		s_ParamArray[8].pProp->SetValue( m_pitchDegree );	
	}
}

void vgCamMgrEntry::AddNodeTabs()
{
	getData();

	vgUI::UIController::getSingleton().RemoveAllPages();

	vgPropertiesViewBar* pageViewBar = vgUI::UIController::getSingleton().GetPropertiesViewBar();
	

#if VGK_LANG_CHS
	// 一般属性
	s_ParamArray[0].label = "一般属性";
	s_ParamArray[0].typeId = PROP_ITEM_GROUP;
	s_ParamArray[0].dataType = PROP_DATA_NONE;
	s_ParamArray[0].connectedPtr = NULL;
	s_ParamArray[0].comment = "设置相机的一般属性";

	s_ParamArray[1].label = "物体名称";
	s_ParamArray[1].typeId = PROP_ITEM_DATA;
	s_ParamArray[1].dataType = PROP_DATA_STR;
	s_ParamArray[1].connectedPtr = &m_sCaption;
	s_ParamArray[1].comment = "物体的名称";

	// 坐标值
	s_ParamArray[2].label = "位置设置";
	s_ParamArray[2].typeId = PROP_ITEM_GROUP;
	s_ParamArray[2].dataType = PROP_DATA_NONE;
	s_ParamArray[2].connectedPtr = NULL;
	s_ParamArray[2].comment = "设置相机的位置";

	s_ParamArray[3].label = "X 坐标";
	s_ParamArray[3].typeId = PROP_ITEM_DATA;
	s_ParamArray[3].dataType = PROP_DATA_FLOAT;
	s_ParamArray[3].connectedPtr = &m_eyePosX;
	s_ParamArray[3].comment = "设置X坐标";

	s_ParamArray[4].label = "Y 坐标";
	s_ParamArray[4].typeId = PROP_ITEM_DATA;
	s_ParamArray[4].dataType = PROP_DATA_FLOAT;
	s_ParamArray[4].connectedPtr = &m_eyePosY;
	s_ParamArray[4].comment = "设置Y坐标";

	s_ParamArray[5].label = "Z 坐标";
	s_ParamArray[5].typeId = PROP_ITEM_DATA;
	s_ParamArray[5].dataType = PROP_DATA_FLOAT;
	s_ParamArray[5].connectedPtr = &m_eyePosZMinus/*m_eyePosZ*/;
	s_ParamArray[5].comment = "设置Z坐标";

	// 角度
	s_ParamArray[6].label = "角度设置";
	s_ParamArray[6].typeId = PROP_ITEM_GROUP;
	s_ParamArray[6].dataType = PROP_DATA_NONE;
	s_ParamArray[6].connectedPtr = NULL;
	s_ParamArray[6].comment = string();

	s_ParamArray[7].label = "旋转角度";
	s_ParamArray[7].typeId = PROP_ITEM_DATA;
	s_ParamArray[7].dataType = PROP_DATA_FLOAT;
	s_ParamArray[7].connectedPtr = &m_turningDegree;
	s_ParamArray[7].comment = "设置旋转角度";

	s_ParamArray[8].label = "俯仰角度";
	s_ParamArray[8].typeId = PROP_ITEM_DATA;
	s_ParamArray[8].dataType = PROP_DATA_FLOAT;
	s_ParamArray[8].connectedPtr = &m_pitchDegree;
	s_ParamArray[8].comment = "设置俯仰角度";

	// 速度
	s_ParamArray[9].label = "速度设置";
	s_ParamArray[9].typeId = PROP_ITEM_GROUP;
	s_ParamArray[9].dataType = PROP_DATA_NONE;
	s_ParamArray[9].connectedPtr = NULL;
	s_ParamArray[9].comment = string();
	
	s_ParamArray[10].label = "前进速度";
	s_ParamArray[10].typeId = PROP_ITEM_DATA;
	s_ParamArray[10].dataType = PROP_DATA_FLOAT;
	s_ParamArray[10].connectedPtr = &m_speend;
	s_ParamArray[10].comment = "设置前进速度";

	s_ParamArray[11].label = "旋转速度";
	s_ParamArray[11].typeId = PROP_ITEM_DATA;
	s_ParamArray[11].dataType = PROP_DATA_FLOAT;
	s_ParamArray[11].connectedPtr = &m_turningSpeed;
	s_ParamArray[11].comment = "设置旋转速度";

	s_ParamArray[12].label = "俯仰速度";
	s_ParamArray[12].typeId = PROP_ITEM_DATA;
	s_ParamArray[12].dataType = PROP_DATA_FLOAT;
	s_ParamArray[12].connectedPtr = &m_pitchSpeed;
	s_ParamArray[12].comment = "设置俯仰速度";


	s_ParamArray[13].label = "上下速度";
	s_ParamArray[13].typeId = PROP_ITEM_DATA;
	s_ParamArray[13].dataType = PROP_DATA_FLOAT;
	s_ParamArray[13].connectedPtr = &m_upAndDownMultiply;
	s_ParamArray[13].comment = "设置上下速度";

	s_ParamArray[14].label = "碰撞检测";
	s_ParamArray[14].typeId = PROP_ITEM_GROUP;
	s_ParamArray[14].dataType = PROP_DATA_NONE;
	s_ParamArray[14].connectedPtr = NULL;
	s_ParamArray[14].comment = "设置碰撞检测椭圆包围体的轴半径长度";

	s_ParamArray[15].label = "X轴";
	s_ParamArray[15].typeId = PROP_ITEM_DATA;
	s_ParamArray[15].dataType = PROP_DATA_FLOAT;
	s_ParamArray[15].connectedPtr = &m_eillipX;
	s_ParamArray[15].comment = "设置椭圆X轴半径";

	s_ParamArray[16].label = "Y轴";
	s_ParamArray[16].typeId = PROP_ITEM_DATA;
	s_ParamArray[16].dataType = PROP_DATA_FLOAT;
	s_ParamArray[16].connectedPtr = &m_eillipY;
	s_ParamArray[16].comment = "设置椭圆Y轴半径";


	s_ParamArray[17].label = "Z轴";
	s_ParamArray[17].typeId = PROP_ITEM_DATA;
	s_ParamArray[17].dataType = PROP_DATA_FLOAT;
	s_ParamArray[17].connectedPtr = &m_eillipZ;
	s_ParamArray[17].comment = "设置椭圆Z轴半径";

	vgPropertyPage* propPage = vgUI::UIController::getSingleton().GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

	propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
	pageViewBar->AddTab("自动属性", propPage);

#else
	// 一般属性
	s_ParamArray[0].label = "General";
	s_ParamArray[0].typeId = PROP_ITEM_GROUP;
	s_ParamArray[0].dataType = PROP_DATA_NONE;
	s_ParamArray[0].connectedPtr = NULL;
	s_ParamArray[0].comment = "";

	s_ParamArray[1].label = "Name";
	s_ParamArray[1].typeId = PROP_ITEM_DATA;
	s_ParamArray[1].dataType = PROP_DATA_STR;
	s_ParamArray[1].connectedPtr = &m_sCaption;
	s_ParamArray[1].comment = "";

	// 坐标值
	s_ParamArray[2].label = "Location";
	s_ParamArray[2].typeId = PROP_ITEM_GROUP;
	s_ParamArray[2].dataType = PROP_DATA_NONE;
	s_ParamArray[2].connectedPtr = NULL;
	s_ParamArray[2].comment = "";

	s_ParamArray[3].label = "X";
	s_ParamArray[3].typeId = PROP_ITEM_DATA;
	s_ParamArray[3].dataType = PROP_DATA_FLOAT;
	s_ParamArray[3].connectedPtr = &m_eyePosX;
	s_ParamArray[3].comment = "";

	s_ParamArray[4].label = "Y";
	s_ParamArray[4].typeId = PROP_ITEM_DATA;
	s_ParamArray[4].dataType = PROP_DATA_FLOAT;
	s_ParamArray[4].connectedPtr = &m_eyePosY;
	s_ParamArray[4].comment = "";

	s_ParamArray[5].label = "Z";
	s_ParamArray[5].typeId = PROP_ITEM_DATA;
	s_ParamArray[5].dataType = PROP_DATA_FLOAT;
	s_ParamArray[5].connectedPtr = &m_eyePosZMinus/*m_eyePosZ*/;
	s_ParamArray[5].comment = "";

	// 角度
	s_ParamArray[6].label = "Angle";
	s_ParamArray[6].typeId = PROP_ITEM_GROUP;
	s_ParamArray[6].dataType = PROP_DATA_NONE;
	s_ParamArray[6].connectedPtr = NULL;
	s_ParamArray[6].comment = string();

	s_ParamArray[7].label = "Rotate";
	s_ParamArray[7].typeId = PROP_ITEM_DATA;
	s_ParamArray[7].dataType = PROP_DATA_FLOAT;
	s_ParamArray[7].connectedPtr = &m_turningDegree;
	s_ParamArray[7].comment = "";

	s_ParamArray[8].label = "Pitch";
	s_ParamArray[8].typeId = PROP_ITEM_DATA;
	s_ParamArray[8].dataType = PROP_DATA_FLOAT;
	s_ParamArray[8].connectedPtr = &m_pitchDegree;
	s_ParamArray[8].comment = "";

	// 速度
	s_ParamArray[9].label = "Speed";
	s_ParamArray[9].typeId = PROP_ITEM_GROUP;
	s_ParamArray[9].dataType = PROP_DATA_NONE;
	s_ParamArray[9].connectedPtr = NULL;
	s_ParamArray[9].comment = string();
	
	s_ParamArray[10].label = "Forward";
	s_ParamArray[10].typeId = PROP_ITEM_DATA;
	s_ParamArray[10].dataType = PROP_DATA_FLOAT;
	s_ParamArray[10].connectedPtr = &m_speend;
	s_ParamArray[10].comment = "";

	s_ParamArray[11].label = "Turning Speed";
	s_ParamArray[11].typeId = PROP_ITEM_DATA;
	s_ParamArray[11].dataType = PROP_DATA_FLOAT;
	s_ParamArray[11].connectedPtr = &m_turningSpeed;
	s_ParamArray[11].comment = "";

	s_ParamArray[12].label = "Pitch Speed";
	s_ParamArray[12].typeId = PROP_ITEM_DATA;
	s_ParamArray[12].dataType = PROP_DATA_FLOAT;
	s_ParamArray[12].connectedPtr = &m_pitchSpeed;
	s_ParamArray[12].comment = "";


	s_ParamArray[13].label = "Up down speed";
	s_ParamArray[13].typeId = PROP_ITEM_DATA;
	s_ParamArray[13].dataType = PROP_DATA_FLOAT;
	s_ParamArray[13].connectedPtr = &m_upAndDownMultiply;
	s_ParamArray[13].comment = "";

	s_ParamArray[14].label = "Collision detect";
	s_ParamArray[14].typeId = PROP_ITEM_GROUP;
	s_ParamArray[14].dataType = PROP_DATA_NONE;
	s_ParamArray[14].connectedPtr = NULL;
	s_ParamArray[14].comment = "";

	s_ParamArray[15].label = "X Axis";
	s_ParamArray[15].typeId = PROP_ITEM_DATA;
	s_ParamArray[15].dataType = PROP_DATA_FLOAT;
	s_ParamArray[15].connectedPtr = &m_eillipX;
	s_ParamArray[15].comment = "";

	s_ParamArray[16].label = "Y Axis";
	s_ParamArray[16].typeId = PROP_ITEM_DATA;
	s_ParamArray[16].dataType = PROP_DATA_FLOAT;
	s_ParamArray[16].connectedPtr = &m_eillipY;
	s_ParamArray[16].comment = "";


	s_ParamArray[17].label = "Z Axis";
	s_ParamArray[17].typeId = PROP_ITEM_DATA;
	s_ParamArray[17].dataType = PROP_DATA_FLOAT;
	s_ParamArray[17].connectedPtr = &m_eillipZ;
	s_ParamArray[17].comment = "";

	vgPropertyPage* propPage = vgUI::UIController::getSingleton().GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

	propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
	pageViewBar->AddTab("Auto Prop", propPage);
#endif

}

void vgCamMgrEntry::getData()
{
	vgKernel::Vec3 pos = vgCam::CamManager::getSingleton().getCurrentPosition();

	vgKernel::Vec3 aa = vgKernel::CoordSystem::getSingleton().getProjectionCoord();

	m_eyePosX = pos.x + aa.x;
	m_eyePosY = pos.y + aa.y;
	m_eyePosZ = pos.z + aa.z;

	m_speend		= vgCam::CamManager::getSingleton().getForwardVelocity();
	m_turningSpeed	= vgCam::CamManager::getSingleton().getTurningVelocity();
	m_pitchSpeed	= vgCam::CamManager::getSingleton().getPitchVelocity();
	m_turningDegree = vgCam::CamManager::getSingleton().getHeadingDegrees();
	m_pitchDegree	= vgCam::CamManager::getSingleton().getPitchDegrees();

	m_upAndDownMultiply = vgCam::CamManager::getSingleton().getUpAndDownMultiply();
	
	m_eyePosZMinus = - m_eyePosZ;
}
