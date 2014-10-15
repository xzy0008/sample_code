
#include <vgStableHeaders.h>
#include "vgVectorLayerEntry.h"
#include "vgPropertyPage.h"

#include <vgKernel/vgkConvertUtility.h>


PropertiesParam vgVectorLayerEntry::s_ParamArray[s_NumOfParam];

vgVectorLayerEntry::vgVectorLayerEntry(vgVector::vgvLayer*	pLayer) 
	:vgBaseEntry( VG_ENTRY_2DLAYER , pLayer)
{
	m_strConstShapeCount= vgKernel::ConvertUtility::textCast<String>(pLayer->count());
	this->OnChanged(vgKernel::VG_OBS_PROPCHANGED, NULL);
}
vgVectorLayerEntry::~vgVectorLayerEntry(void)
{
	m_Renderer->unregisterObserver( this );
}

void vgVectorLayerEntry::OnPropertyChanged(string paramName)
{
	//vgVector::vgvLayer*	pLayer = (vgVector::vgvLayer*)m_Renderer;
	m_Renderer->setvisible(m_bIsLayerVisible);
	// 更新TREEITEM
	vgUIController::GetInstance()->GetWorkSpaceBar()->SetItemText(hTreeItem, GetName());
}

void vgVectorLayerEntry::OnChanged(int eventId, void *param)
{
	if (eventId == vgKernel::VG_OBS_PROPCHANGED)
	{
		//vgVector::vgvLayer*	pLayer = (vgVector::vgvLayer*)m_Renderer;
		m_LayerCenterPoint	= m_Renderer->getBoundingBox().getCenter();
		
		m_LayerCenterPoint	+= vgKernel::Vec3(
			vgCore::vgCoordinate::getSingleton().GetSceneCood().x,
			vgCore::vgCoordinate::getSingleton().GetSceneCood().y,
			vgCore::vgCoordinate::getSingleton().GetSceneCood().z);
		
		m_bIsLayerVisible	= m_Renderer->getvisible();

		
		if (this == vgUIController::GetInstance()->GetCurrentSelectedNode())
		{
			s_ParamArray[1].pProp->SetValue(m_LayerCenterPoint.x);
			s_ParamArray[2].pProp->SetValue(m_LayerCenterPoint.y);
			m_posZMinus	= -m_LayerCenterPoint.z;
			s_ParamArray[3].pProp->SetValue(m_posZMinus);
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
}

void vgVectorLayerEntry::AddNodeTabs()
{
	vgUIController::GetInstance()->RemoveAllPages();

	vgPropertiesViewBar* pageViewBar = vgUIController::GetInstance()->GetPropertiesViewBar();

	s_ParamArray[0].label = "层中心坐标值设置";
	s_ParamArray[0].typeId = PROP_ITEM_GROUP;
	s_ParamArray[0].dataType = PROP_DATA_NONE;
	s_ParamArray[0].connectedPtr = NULL;
	s_ParamArray[0].comment = "设置层中心坐标值";

	s_ParamArray[1].label = "X 坐标";
	s_ParamArray[1].typeId = PROP_ITEM_DATA;
	s_ParamArray[1].dataType = PROP_DATA_FLOAT;
	s_ParamArray[1].connectedPtr = &m_LayerCenterPoint.x;
	s_ParamArray[1].comment = "设置X坐标";

	s_ParamArray[2].label = "Y 坐标";
	s_ParamArray[2].typeId = PROP_ITEM_DATA;
	s_ParamArray[2].dataType = PROP_DATA_FLOAT;
	s_ParamArray[2].connectedPtr = &m_LayerCenterPoint.y;
	s_ParamArray[2].comment = "设置Y坐标";

	m_posZMinus = - m_LayerCenterPoint.z;
	s_ParamArray[3].label = "Z 坐标";
	s_ParamArray[3].typeId = PROP_ITEM_DATA;
	s_ParamArray[3].dataType = PROP_DATA_FLOAT;
	s_ParamArray[3].connectedPtr = &m_posZMinus;
	s_ParamArray[3].comment = "设置Z坐标";

	s_ParamArray[4].label = "其他设置";
	s_ParamArray[4].typeId = PROP_ITEM_GROUP;
	s_ParamArray[4].dataType = PROP_DATA_NONE;
	s_ParamArray[4].connectedPtr = NULL;
	s_ParamArray[4].comment = string();

	s_ParamArray[5].label = "物体名称";
	s_ParamArray[5].typeId = PROP_ITEM_DATA;
	s_ParamArray[5].dataType = PROP_DATA_STR;
	s_ParamArray[5].connectedPtr = m_Renderer->getNamePtr();
	s_ParamArray[5].comment = "物体的名称";

	s_ParamArray[6].label = "可见标记";
	s_ParamArray[6].typeId = PROP_ITEM_DATA;
	s_ParamArray[6].dataType = PROP_DATA_BOOL;
	s_ParamArray[6].connectedPtr = &m_bIsLayerVisible;
	s_ParamArray[6].comment = "层可见性标记";
	
	s_ParamArray[7].label = "图元数目";
	s_ParamArray[7].typeId = PROP_ITEM_DATA;
	s_ParamArray[7].dataType = PROP_DATA_CONST_STR;
	s_ParamArray[7].connectedPtr = &m_strConstShapeCount;
	s_ParamArray[7].comment = "层内包含图元的总数";
	
	vgPropertyPage* propPage = vgUIController::GetInstance()->GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

	propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
	pageViewBar->AddTab("自动属性", propPage);
}
