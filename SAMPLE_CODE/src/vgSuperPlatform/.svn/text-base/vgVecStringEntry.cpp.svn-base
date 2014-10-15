#include <vgStableHeaders.h>
#include "vgVecStringEntry.h"
#include <vgGIS3D/vgGIS3D.h>
#include <vgKernel/vgkSelectManager.h>

#include "vgUIController.h"
PropertiesParam vgVecStringEntry::s_ParamArray[s_NumOfParam];
vgVecStringEntry::vgVecStringEntry(vgGIS3D::VertexStringClass *vsc) :
vgBaseEntry( VG_ENTRY_VECSTRING , NULL )
{

	m_sCaption = "矢量";
	//s_group_item_name="noname";
	m_visible=TRUE;
	m_VecStringClass=vsc;

	//vgCam::CamManager::getSingleton().registerObserver(this);

	//this->onChanged(vgKernel::VG_OBS_PROPCHANGED, NULL);
	//vgCore::vgCoordinate::getSingleton().registerObserver(this);

	//this->onChanged(vgKernel::VG_OBS_PROPCHANGED, NULL);

}
vgVecStringEntry::~vgVecStringEntry(void)
{

}

// ==============================================================================


void vgVecStringEntry::OnPropertyChanged(string paramName)
{
	vgUIController::GetInstance()->GetWorkSpaceBar()->SetItemText(hTreeItem, 
		GetName() );
}

void vgVecStringEntry::onChanged(int eventId, void* param)
{
	if (eventId == vgKernel::VG_OBS_PROPCHANGED)
	{
		//vgCam::ViewCam *pViewCam = ( vgCam::ViewCam*) m_Renderer;

		//assert(pViewCam != NULL);

		//vgKernel::Vec3 pos = pViewCam->getPosition();

		//m_posX = pos.x + vgCore::vgCoordinate::getSingleton().GetSceneCood().x;
		//m_posY = pos.y + vgCore::vgCoordinate::getSingleton().GetSceneCood().y;
		//m_posZ = pos.z + vgCore::vgCoordinate::getSingleton().GetSceneCood().z;

		//////TRACE("New Camera Position %.2f %.2f %.2f \n", posPtr->x, posPtr->y, posPtr->z);
		//if (this == vgUIController::GetInstance()->GetCurrentSelectedNode())
		//{
		//	s_ParamArray[1].pProp->SetValue(m_posX);
		//	s_ParamArray[2].pProp->SetValue(m_posY);
		//	s_ParamArray[3].pProp->SetValue(m_posZ);
		//}

		return ;
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
}
void vgVecStringEntry::AddNodeTabs()
{
	vgUIController::GetInstance()->RemoveAllPages();

	vgPropertiesViewBar* pageViewBar = vgUIController::GetInstance()->GetPropertiesViewBar();

	// 一般属性
	s_ParamArray[0].label = "一般属性";
	s_ParamArray[0].typeId = PROP_ITEM_GROUP;
	s_ParamArray[0].dataType = PROP_DATA_NONE;
	s_ParamArray[0].connectedPtr = NULL;
	s_ParamArray[0].comment = "设置一般属性";

	s_ParamArray[1].label = "物体名称";
	s_ParamArray[1].typeId = PROP_ITEM_DATA;
	s_ParamArray[1].dataType = PROP_DATA_STR;
	s_ParamArray[1].connectedPtr = &m_sCaption;
	s_ParamArray[1].comment = "物体的名称";


	s_ParamArray[2].label = "可见性";
	s_ParamArray[2].typeId = PROP_ITEM_DATA;
	s_ParamArray[2].dataType = PROP_DATA_BOOL;
	s_ParamArray[2].connectedPtr = &m_visible;
	s_ParamArray[2].comment = "是否隐藏";

	vgPropertyPage* propPage = vgUIController::GetInstance()->GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

	propPage->ConnectNode(this, s_ParamArray,  s_NumOfParam);
	pageViewBar->AddTab("自动属性", propPage);

	vgGIS3D::GIS3D::getSingleton().CurrentVertexStringPtr=m_VecStringClass->m_TypeVertexStringPtr.second;

	vgUIController::GetInstance()->SetCurrentSelectedNode(this);

}