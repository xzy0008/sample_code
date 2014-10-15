#include <vgStableHeaders.h>

#include <vgEntry/vgCoordinateEntry.h>

#include <vgUIController/vgPropertyPage.h>
#include <vgUIController/vgUIController.h>

#include <vgKernel/vgkCoordSystem.h>
//#include <vgCoordinate.h>



PropertiesParam vgCoordinateEntry::s_ParamArray[s_NumOfParam];

vgCoordinateEntry::vgCoordinateEntry(string name) 
: m_sCaption(name)
,vgBaseEntry(  NULL )
{
	//vgKernel::CoordSystem::getSingleton().registerObserver(this);
	
	getData();


	vgKernel::CoordSystem::getSingleton().registerObserver(this);
	
	this->onChanged(vgKernel::VG_OBS_PROPCHANGED, NULL);

}
vgCoordinateEntry::~vgCoordinateEntry(void)
{
	vgKernel::CoordSystem::getSingleton().unregisterObserver(this);

}

void vgCoordinateEntry::OnPropertyChanged(string paramName)
{
		m_PosZ = -m_PosZMinus;
		vgKernel::CoordSystem::getSingleton().setProjectionCoord(\
			vgKernel::Vec3(m_PosX, m_PosY, m_PosZ));	
		// 更新TREEITEM
		vgUI::UIController::getSingleton().GetWorkSpaceBar()->SetItemText(hTreeItem, m_sCaption);

		vgKernel::CoordSystem::getSingleton().notifyOberversOnEvent( vgKernel::VG_OBS_PROPCHANGED, NULL );
}

void vgCoordinateEntry::onChanged(int eventId, void *param)
{
	if (eventId == vgKernel::VG_OBS_PROPCHANGED)
	{
		m_PosX = vgKernel::CoordSystem::getSingleton().getProjectionCoord().x;
		m_PosY = vgKernel::CoordSystem::getSingleton().getProjectionCoord().y;
		m_PosZ = vgKernel::CoordSystem::getSingleton().getProjectionCoord().z;

		////TRACE("New Camera Position %.2f %.2f %.2f \n", posPtr->x, posPtr->y, posPtr->z);
		if (this == vgUI::UIController::getSingleton().GetCurrentSelectedNode())
		{
			s_ParamArray[1].pProp->SetValue(m_PosX);
			s_ParamArray[2].pProp->SetValue(m_PosY);
			m_PosZMinus = -m_PosZ;
			s_ParamArray[3].pProp->SetValue(m_PosZMinus);
		}
	}

	/*if (eventId == vgKernel::VG_OBS_SELECTCHAGNED)
	{
		vgUI::UIController::getSingleton().SelectNode(this);
	}

	if (eventId == vgKernel::VG_OBS_ADDSELECTION)
	{
		vgUI::UIController::getSingleton().AddSelection(this);

		return ;
	}*/
}

void vgCoordinateEntry::AddNodeTabs()
{
	getData();

	vgUI::UIController::getSingleton().RemoveAllPages();

	vgPropertiesViewBar* pageViewBar = vgUI::UIController::getSingleton().GetPropertiesViewBar();

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

	
	vgPropertyPage* propPage = vgUI::UIController::getSingleton().GetPropPage();
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


	vgPropertyPage* propPage = vgUI::UIController::getSingleton().GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

	propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
	pageViewBar->AddTab("Auto Prop", propPage);
#endif

}

void vgCoordinateEntry::getData()
{
	m_PosX = vgKernel::CoordSystem::getSingleton().getProjectionCoord().x;
	m_PosY = vgKernel::CoordSystem::getSingleton().getProjectionCoord().y;
	m_PosZ = vgKernel::CoordSystem::getSingleton().getProjectionCoord().z;
	m_PosZMinus = -m_PosZ;
#if VGK_LANG_CHS
	m_sCaption = "场景原点坐标";
#else
	m_sCaption = "Origin";
#endif
}