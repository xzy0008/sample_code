#include <vgStableHeaders.h>
#include "vgFrustrumEntry.h"
#include "vgPropertyPage.h"


#include <vgCoordinate.h>



PropertiesParam vgFrustrumEntry::s_ParamArray[s_NumOfParam];

vgFrustrumEntry::vgFrustrumEntry() :
vgBaseEntry( VG_ENTRY_CAMMGR , NULL )
{
	//vgCore::vgCoordinate::getSingleton().registerObserver(this);

	m_Near = vgCam::CamManager::getSingleton().getNear();
	m_Far = vgCam::CamManager::getSingleton().getFar();
	m_Fov = vgCam::CamManager::getSingleton().getFov();

#if VGK_LANG_CHS
	m_sCaption = "视景体";
#else
	m_sCaption = "Frustum";
#endif

	vgCam::CamManager::getSingleton().registerObserver(this);

	this->onChanged(vgKernel::VG_OBS_PROPCHANGED, NULL);

}
vgFrustrumEntry::~vgFrustrumEntry(void)
{

}

void vgFrustrumEntry::OnPropertyChanged(string paramName)
{

	vgCam::CamManager::getSingleton().setNear(m_Near);	
	vgCam::CamManager::getSingleton().setFar(m_Far);	
	vgCam::CamManager::getSingleton().setFov(m_Fov);	
	// 更新TREEITEM
	vgUIController::GetInstance()->GetWorkSpaceBar()->SetItemText(hTreeItem, m_sCaption);

	vgCam::CamManager::getSingleton().notifyOberversOnEvent( vgKernel::VG_OBS_PROPCHANGED, NULL );
}

void vgFrustrumEntry::onChanged(int eventId, void *param)
{
	if (eventId == vgKernel::VG_OBS_PROPCHANGED)
	{
		m_Near = vgCam::CamManager::getSingleton().getNear();
		m_Far = vgCam::CamManager::getSingleton().getFar();
		m_Fov = vgCam::CamManager::getSingleton().getFov();

		if (this == vgUIController::GetInstance()->GetCurrentSelectedNode())
		{
			s_ParamArray[1].pProp->SetValue(m_Near);
			s_ParamArray[2].pProp->SetValue(m_Far);
			s_ParamArray[3].pProp->SetValue(m_Fov);
		}
	}


}

void vgFrustrumEntry::AddNodeTabs()
{
	vgUIController::GetInstance()->RemoveAllPages();

	vgPropertiesViewBar* pageViewBar = vgUIController::GetInstance()->GetPropertiesViewBar();

#if VGK_LANG_CHS
	s_ParamArray[0].label = "视景体设置";
	s_ParamArray[0].typeId = PROP_ITEM_GROUP;
	s_ParamArray[0].dataType = PROP_DATA_NONE;
	s_ParamArray[0].connectedPtr = NULL;
	s_ParamArray[0].comment = "设置视景体的参数";

	s_ParamArray[1].label = "近裁减面";
	s_ParamArray[1].typeId = PROP_ITEM_DATA;
	s_ParamArray[1].dataType = PROP_DATA_FLOAT;
	s_ParamArray[1].connectedPtr = &m_Near;
	s_ParamArray[1].comment = "设置近裁减面";


	s_ParamArray[2].label = "远裁减面";
	s_ParamArray[2].typeId = PROP_ITEM_DATA;
	s_ParamArray[2].dataType = PROP_DATA_FLOAT;
	s_ParamArray[2].connectedPtr = &m_Far;
	s_ParamArray[2].comment = "设置远裁减面";

	s_ParamArray[3].label = "张角";
	s_ParamArray[3].typeId = PROP_ITEM_DATA;
	s_ParamArray[3].dataType = PROP_DATA_FLOAT;
	s_ParamArray[3].connectedPtr = &m_Fov;
	s_ParamArray[3].comment = "设置张角";

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
#else
	s_ParamArray[0].label = "Config";
	s_ParamArray[0].typeId = PROP_ITEM_GROUP;
	s_ParamArray[0].dataType = PROP_DATA_NONE;
	s_ParamArray[0].connectedPtr = NULL;
	s_ParamArray[0].comment = "";

	s_ParamArray[1].label = "Near";
	s_ParamArray[1].typeId = PROP_ITEM_DATA;
	s_ParamArray[1].dataType = PROP_DATA_FLOAT;
	s_ParamArray[1].connectedPtr = &m_Near;
	s_ParamArray[1].comment = "";


	s_ParamArray[2].label = "Far";
	s_ParamArray[2].typeId = PROP_ITEM_DATA;
	s_ParamArray[2].dataType = PROP_DATA_FLOAT;
	s_ParamArray[2].connectedPtr = &m_Far;
	s_ParamArray[2].comment = "";

	s_ParamArray[3].label = "Fov";
	s_ParamArray[3].typeId = PROP_ITEM_DATA;
	s_ParamArray[3].dataType = PROP_DATA_FLOAT;
	s_ParamArray[3].connectedPtr = &m_Fov;
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
#endif


	vgPropertyPage* propPage = vgUIController::GetInstance()->GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

	propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
#if VGK_LANG_CHS
	pageViewBar->AddTab("自动属性", propPage);
#else
	pageViewBar->AddTab("Properties", propPage);
#endif
}
