#include <vgStableHeaders.h>
#include "vgTestNode1.h"
#include "vgTestNode1TabOne.h"
#include "vgTestNode1PropertiesTab.h"
#include "vgUIController.h"

PropertiesParam vgTestNode1::s_ParamArray[s_NumOfParam];

vgTestNode1::vgTestNode1(string name):vgBasedNode(name),
									  m_sCaption("默认物体"),
									  m_sOptionOne("选项1")
{
	m_posX = 0.f;
	m_posY = 0.f;
	m_posZ = 0.f;

	m_bEnable = false;
	m_nSiz  = 10;
}

vgTestNode1::~vgTestNode1(void)
{
}

string vgTestNode1::GetNameID()
{
	return nameId;
}

void vgTestNode1::AddNodeTabs()
{
	// vgUIController::GetInstance()->GetPropertiesViewBar()->GetTabControl()::m_bAutoDestoryWindow = true;
	vgUIController::GetInstance()->RemoveAllPages();
	
	vgPropertiesViewBar* pageViewBar = vgUIController::GetInstance()->GetPropertiesViewBar();
	
	m_tabOne = dynamic_cast<TabOne*> (vgUIController::GetInstance()->GetTabPage(TAB_TESTNODE_CTRL));
	m_tabOne->ConnectNode(this);
	m_tabOne->Create(IDD_TAB1, pageViewBar->GetTabControl());
	
	m_pTab = dynamic_cast<PropertiesTab*> (vgUIController::GetInstance()->GetTabPage(TAB_TESTNODE_PROP));
	m_pTab->ConnectNode(this);
	m_pTab->Create(IDD_PROP, pageViewBar->GetTabControl());
	

	s_ParamArray[0].label = "坐标值设置";
	s_ParamArray[0].typeId = PROP_ITEM_GROUP;
	s_ParamArray[0].dataType = PROP_DATA_NONE;
	s_ParamArray[0].connectedPtr = NULL;
	s_ParamArray[0].comment = "设置物体的坐标";

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
	s_ParamArray[3].connectedPtr = &m_posZ;
	s_ParamArray[3].comment = "设置Z坐标";

	s_ParamArray[4].label = "其他设置";
	s_ParamArray[4].typeId = PROP_ITEM_GROUP;
	s_ParamArray[4].dataType = PROP_DATA_NONE;
	s_ParamArray[4].connectedPtr = NULL;
	s_ParamArray[4].comment = string();

	s_ParamArray[5].label = "物体名称";
	s_ParamArray[5].typeId = PROP_ITEM_DATA;
	s_ParamArray[5].dataType = PROP_DATA_STR;
	s_ParamArray[5].connectedPtr = &m_sCaption;
	s_ParamArray[5].comment = "物体的名称";

	s_ParamArray[6].label = "物体可见";
	s_ParamArray[6].typeId = PROP_ITEM_DATA;
	s_ParamArray[6].dataType = PROP_DATA_BOOL;
	s_ParamArray[6].connectedPtr = &m_bEnable;
	s_ParamArray[6].comment = "物体是否可见";

	s_ParamArray[7].label = "物体大小";
	s_ParamArray[7].typeId = PROP_ITEM_DATA;
	s_ParamArray[7].dataType = PROP_DATA_INT;
	s_ParamArray[7].connectedPtr = &m_nSiz;
	s_ParamArray[7].comment = "设置物体的缩放大小";

	s_ParamArray[8].label = "选项测试";
	s_ParamArray[8].typeId = PROP_ITEM_DATA;
	s_ParamArray[8].dataType = PROP_DATA_OPTION_START;
	s_ParamArray[8].connectedPtr = &m_sOptionOne;
	s_ParamArray[8].comment = "选项测试注释";

	s_ParamArray[9].label = "选项1";
	s_ParamArray[9].typeId = PROP_ITEM_DATA;
	s_ParamArray[9].dataType = PROP_DATA_OPTION_ITEM;
	s_ParamArray[9].connectedPtr = NULL;
	s_ParamArray[9].comment = "选项1 注释";

	s_ParamArray[10].label = "选项2";
	s_ParamArray[10].typeId = PROP_ITEM_DATA;
	s_ParamArray[10].dataType = PROP_DATA_OPTION_ITEM;
	s_ParamArray[10].connectedPtr = NULL;
	s_ParamArray[10].comment = "选项2 注释";

	s_ParamArray[11].label = "选项3";
	s_ParamArray[11].typeId = PROP_ITEM_DATA;
	s_ParamArray[11].dataType = PROP_DATA_OPTION_ITEM;
	s_ParamArray[11].connectedPtr = NULL;
	s_ParamArray[11].comment = "选项3 注释";

	s_ParamArray[12].label = string();
	s_ParamArray[12].typeId = PROP_ITEM_DATA;
	s_ParamArray[12].dataType = PROP_DATA_OPTION_END;
	s_ParamArray[12].connectedPtr = NULL;
	s_ParamArray[12].comment = string();

	vgPropertyPage* propPage = vgUIController::GetInstance()->GetPropPage();
	propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);

	propPage->Create(IDD_PROPERTY, pageViewBar->GetTabControl());

	pageViewBar->AddTab("自动属性", propPage);
	pageViewBar->AddTab("高级", m_tabOne);
	pageViewBar->AddTab(m_pTab->GetTitle(), m_pTab);

	
}

void vgTestNode1::SetPosX(float posX)
{
	m_posX = posX;

	if (this == vgUIController::GetInstance()->GetCurrentSelectedNode())
	{
		s_ParamArray[1].pProp->SetValue(posX);
	}
}

void vgTestNode1::SetPosY(float posY)
{
	m_posY = posY;

	if (this == vgUIController::GetInstance()->GetCurrentSelectedNode())
	{
		s_ParamArray[2].pProp->SetValue(posY);
	}
}

void vgTestNode1::SetPosZ(float posZ)
{
	m_posZ = posZ;

	if (this == vgUIController::GetInstance()->GetCurrentSelectedNode())
	{
		s_ParamArray[3].pProp->SetValue(posZ);
	}
}

void vgTestNode1::SetCaption(string caption)
{
	m_sCaption = caption;

	if (this == vgUIController::GetInstance()->GetCurrentSelectedNode())
	{
		s_ParamArray[5].pProp->SetValue(caption.c_str());
	}
}

void vgTestNode1::SetSize(int size)
{
	m_nSiz = size;

	if (this == vgUIController::GetInstance()->GetCurrentSelectedNode())
	{
		s_ParamArray[7].pProp->SetValue((long)m_nSiz);
	}
}

void vgTestNode1::SetEnable(bool enable)
{
	m_bEnable = enable;

	if (this == vgUIController::GetInstance()->GetCurrentSelectedNode())
	{
		s_ParamArray[6].pProp->SetValue(m_bEnable);
	}
}

