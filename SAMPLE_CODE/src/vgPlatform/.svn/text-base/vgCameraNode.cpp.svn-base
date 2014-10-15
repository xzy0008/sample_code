#include <vgStableHeaders.h>
#include "vgCameraNode.h"
#include "vgPropertyPage.h"

PropertiesParam vgCameraNode::s_ParamArray[s_NumOfParam];

vgCameraNode::vgCameraNode(string cameraName):vgBasedNode(cameraName)
{
	m_eyePosX = 0.f;
	m_eyePosY = 0.f;
	m_eyePosZ = 0.f;

	m_tarPosX = 0.f;
	m_tarPoxY = 0.f;
	m_tarPoxZ = 0.f;

	m_upPosX = 0.f;
	m_upPosY = 1.f;
	m_upPoxZ = 0.f;

	m_hAngle = 0.f;
	m_vAngle = 0.f;
}

vgCameraNode::~vgCameraNode(void)
{

}

void vgCameraNode::AddNodeTabs()
{
	vgUIController::GetInstance()->RemoveAllPages();

	vgPropertiesViewBar* pageViewBar = vgUIController::GetInstance()->GetPropertiesViewBar();

	s_ParamArray[0].label = "坐标值设置";
	s_ParamArray[0].typeId = PROP_ITEM_GROUP;
	s_ParamArray[0].dataType = PROP_DATA_NONE;
	s_ParamArray[0].connectedPtr = NULL;
	s_ParamArray[0].comment = "设置相机的坐标";

	s_ParamArray[1].label = "X 坐标";
	s_ParamArray[1].typeId = PROP_ITEM_DATA;
	s_ParamArray[1].dataType = PROP_DATA_FLOAT;
	s_ParamArray[1].connectedPtr = &m_eyePosX;
	s_ParamArray[1].comment = "设置X坐标";


	s_ParamArray[2].label = "Y 坐标";
	s_ParamArray[2].typeId = PROP_ITEM_DATA;
	s_ParamArray[2].dataType = PROP_DATA_FLOAT;
	s_ParamArray[2].connectedPtr = &m_eyePosY;
	s_ParamArray[2].comment = "设置Y坐标";

	s_ParamArray[3].label = "Z 坐标";
	s_ParamArray[3].typeId = PROP_ITEM_DATA;
	s_ParamArray[3].dataType = PROP_DATA_FLOAT;
	s_ParamArray[3].connectedPtr = &m_eyePosZ;
	s_ParamArray[3].comment = "设置Z坐标";

	//s_ParamArray[4].label = "其他设置";
	//s_ParamArray[4].typeId = PROP_ITEM_GROUP;
	//s_ParamArray[4].dataType = PROP_DATA_NONE;
	//s_ParamArray[4].connectedPtr = NULL;
	//s_ParamArray[4].comment = string();

	//s_ParamArray[5].label = "物体名称";
	//s_ParamArray[5].typeId = PROP_ITEM_DATA;
	//s_ParamArray[5].dataType = PROP_DATA_STR;
	//s_ParamArray[5].connectedPtr = &m_sCaption;
	//s_ParamArray[5].comment = "物体的名称";

	//s_ParamArray[6].label = "物体可见";
	//s_ParamArray[6].typeId = PROP_ITEM_DATA;
	//s_ParamArray[6].dataType = PROP_DATA_BOOL;
	//s_ParamArray[6].connectedPtr = &m_bEnable;
	//s_ParamArray[6].comment = "物体是否可见";

	//s_ParamArray[7].label = "物体大小";
	//s_ParamArray[7].typeId = PROP_ITEM_DATA;
	//s_ParamArray[7].dataType = PROP_DATA_INT;
	//s_ParamArray[7].connectedPtr = &m_nSiz;
	//s_ParamArray[7].comment = "设置物体的缩放大小";

	//s_ParamArray[8].label = "选项测试";
	//s_ParamArray[8].typeId = PROP_ITEM_DATA;
	//s_ParamArray[8].dataType = PROP_DATA_OPTION_START;
	//s_ParamArray[8].connectedPtr = &m_sOptionOne;
	//s_ParamArray[8].comment = "选项测试注释";

	//s_ParamArray[9].label = "选项1";
	//s_ParamArray[9].typeId = PROP_ITEM_DATA;
	//s_ParamArray[9].dataType = PROP_DATA_OPTION_ITEM;
	//s_ParamArray[9].connectedPtr = NULL;
	//s_ParamArray[9].comment = "选项1 注释";

	//s_ParamArray[10].label = "选项2";
	//s_ParamArray[10].typeId = PROP_ITEM_DATA;
	//s_ParamArray[10].dataType = PROP_DATA_OPTION_ITEM;
	//s_ParamArray[10].connectedPtr = NULL;
	//s_ParamArray[10].comment = "选项2 注释";

	//s_ParamArray[11].label = "选项3";
	//s_ParamArray[11].typeId = PROP_ITEM_DATA;
	//s_ParamArray[11].dataType = PROP_DATA_OPTION_ITEM;
	//s_ParamArray[11].connectedPtr = NULL;
	//s_ParamArray[11].comment = "选项3 注释";

	//s_ParamArray[12].label = string();
	//s_ParamArray[12].typeId = PROP_ITEM_DATA;
	//s_ParamArray[12].dataType = PROP_DATA_OPTION_END;
	//s_ParamArray[12].connectedPtr = NULL;
	//s_ParamArray[12].comment = string();

	
	vgPropertyPage* propPage = vgUIController::GetInstance()->GetPropPage();
	propPage->Create(IDD_PROPERTY, pageViewBar->GetTabControl());

	propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
	pageViewBar->AddTab("自动属性", propPage);
}

void vgCameraNode::SetPosX(float posX)
{
	m_eyePosX = posX;

	if (this == vgUIController::GetInstance()->GetCurrentSelectedNode())
	{
		s_ParamArray[1].pProp->SetValue(posX);
	}
}

void vgCameraNode::SetPosY(float posY)
{
	m_eyePosY = posY;

	if (this == vgUIController::GetInstance()->GetCurrentSelectedNode())
	{
		s_ParamArray[2].pProp->SetValue(posY);
	}
}

void vgCameraNode::SetPosZ(float posZ)
{
	m_eyePosZ = posZ;

	if (this == vgUIController::GetInstance()->GetCurrentSelectedNode())
	{
		s_ParamArray[3].pProp->SetValue(posZ);
	}
}