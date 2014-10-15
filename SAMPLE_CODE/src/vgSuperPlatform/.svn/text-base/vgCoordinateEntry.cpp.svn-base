#include <vgStableHeaders.h>
#include "vgCoordinateEntry.h"
#include "vgPropertyPage.h"


#include <vgCoordinate.h>



PropertiesParam vgCoordinateEntry::s_ParamArray[s_NumOfParam];

vgCoordinateEntry::vgCoordinateEntry() :
vgBaseEntry( VG_ENTRY_CAMMGR , NULL )
{
	//vgCore::vgCoordinate::getSingleton().registerObserver(this);
	
	getData();


	vgCore::vgCoordinate::getSingleton().registerObserver(this);
	
	this->onChanged(vgKernel::VG_OBS_PROPCHANGED, NULL);

}
vgCoordinateEntry::~vgCoordinateEntry(void)
{

}

void vgCoordinateEntry::OnPropertyChanged(string paramName)
{
		m_PosZ = -m_PosZMinus;
		vgCore::vgCoordinate::getSingleton().SetSceneCood(\
		Vector3(m_PosX, m_PosY, m_PosZ));	
		// 更新TREEITEM
		vgUIController::GetInstance()->GetWorkSpaceBar()->SetItemText(hTreeItem, m_sCaption);

		vgCore::vgCoordinate::getSingleton().notifyOberversOnEvent( vgKernel::VG_OBS_PROPCHANGED, NULL );
}

void vgCoordinateEntry::onChanged(int eventId, void *param)
{
	if (eventId == vgKernel::VG_OBS_PROPCHANGED)
	{
		m_PosX = vgCore::vgCoordinate::getSingleton().GetSceneCood().x;
		m_PosY = vgCore::vgCoordinate::getSingleton().GetSceneCood().y;
		m_PosZ = vgCore::vgCoordinate::getSingleton().GetSceneCood().z;

		////TRACE("New Camera Position %.2f %.2f %.2f \n", posPtr->x, posPtr->y, posPtr->z);
		if (this == vgUIController::GetInstance()->GetCurrentSelectedNode())
		{
			s_ParamArray[1].pProp->SetValue(m_PosX);
			s_ParamArray[2].pProp->SetValue(m_PosY);
			m_PosZMinus = -m_PosZ;
			s_ParamArray[3].pProp->SetValue(m_PosZMinus);
		}
	}

	/*if (eventId == vgKernel::VG_OBS_SELECTCHAGNED)
	{
		vgUIController::GetInstance()->SelectNode(this);
	}

	if (eventId == vgKernel::VG_OBS_ADDSELECTION)
	{
		vgUIController::GetInstance()->AddSelection(this);

		return ;
	}*/
}

void vgCoordinateEntry::AddNodeTabs()
{
	getData();

	vgUIController::GetInstance()->RemoveAllPages();

	vgPropertiesViewBar* pageViewBar = vgUIController::GetInstance()->GetPropertiesViewBar();

#if VGK_LANG_CHS
	s_ParamArray[0].label = "坐标值设置";
	s_ParamArray[0].typeId = PROP_ITEM_GROUP;
	s_ParamArray[0].dataType = PROP_DATA_NONE;
	s_ParamArray[0].connectedPtr = NULL;
	s_ParamArray[0].comment = "设置相机的坐标";

	s_ParamArray[1].label = "X 坐标";
	s_ParamArray[1].typeId = PROP_ITEM_DATA;
	s_ParamArray[1].dataType = PROP_DATA_FLOAT;
	s_ParamArray[1].connectedPtr = &m_PosX;
	s_ParamArray[1].comment = "设置X坐标";


	s_ParamArray[2].label = "Y 坐标";
	s_ParamArray[2].typeId = PROP_ITEM_DATA;
	s_ParamArray[2].dataType = PROP_DATA_FLOAT;
	s_ParamArray[2].connectedPtr = &m_PosY;
	s_ParamArray[2].comment = "设置Y坐标";

	s_ParamArray[3].label = "Z 坐标";
	s_ParamArray[3].typeId = PROP_ITEM_DATA;
	s_ParamArray[3].dataType = PROP_DATA_FLOAT;
	s_ParamArray[3].connectedPtr = &m_PosZMinus/*m_PosZ*/;
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

	
	vgPropertyPage* propPage = vgUIController::GetInstance()->GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

	propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
	pageViewBar->AddTab("自动属性", propPage);

#else
	s_ParamArray[0].label = "Coord";
	s_ParamArray[0].typeId = PROP_ITEM_GROUP;
	s_ParamArray[0].dataType = PROP_DATA_NONE;
	s_ParamArray[0].connectedPtr = NULL;
	s_ParamArray[0].comment = "";

	s_ParamArray[1].label = "X";
	s_ParamArray[1].typeId = PROP_ITEM_DATA;
	s_ParamArray[1].dataType = PROP_DATA_FLOAT;
	s_ParamArray[1].connectedPtr = &m_PosX;
	s_ParamArray[1].comment = "";


	s_ParamArray[2].label = "Y";
	s_ParamArray[2].typeId = PROP_ITEM_DATA;
	s_ParamArray[2].dataType = PROP_DATA_FLOAT;
	s_ParamArray[2].connectedPtr = &m_PosY;
	s_ParamArray[2].comment = "";

	s_ParamArray[3].label = "Z";
	s_ParamArray[3].typeId = PROP_ITEM_DATA;
	s_ParamArray[3].dataType = PROP_DATA_FLOAT;
	s_ParamArray[3].connectedPtr = &m_PosZMinus/*m_PosZ*/;
	s_ParamArray[3].comment = "";

	s_ParamArray[4].label = "Others";
	s_ParamArray[4].typeId = PROP_ITEM_GROUP;
	s_ParamArray[4].dataType = PROP_DATA_NONE;
	s_ParamArray[4].connectedPtr = NULL;
	s_ParamArray[4].comment = string();

	s_ParamArray[5].label = "Name";
	s_ParamArray[5].typeId = PROP_ITEM_DATA;
	s_ParamArray[5].dataType = PROP_DATA_STR;
	s_ParamArray[5].connectedPtr = &m_sCaption;
	s_ParamArray[5].comment = "";


	vgPropertyPage* propPage = vgUIController::GetInstance()->GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

	propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
	pageViewBar->AddTab("Auto Prop", propPage);
#endif

}

void vgCoordinateEntry::getData()
{
	m_PosX = vgCore::vgCoordinate::getSingleton().GetSceneCood().x;
	m_PosY = vgCore::vgCoordinate::getSingleton().GetSceneCood().y;
	m_PosZ = vgCore::vgCoordinate::getSingleton().GetSceneCood().z;
	m_PosZMinus = -m_PosZ;
#if VGK_LANG_CHS
	m_sCaption = "场景原点坐标";
#else
	m_sCaption = "Origin";
#endif
}