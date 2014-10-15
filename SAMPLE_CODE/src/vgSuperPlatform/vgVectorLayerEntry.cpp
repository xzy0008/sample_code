
#include <vgStableHeaders.h>
#include "vgVectorLayerEntry.h"
#include "vgPropertyPage.h"
#include <vgKernel/vgkSelectManager.h>
#include <vgKernel/vgkConvertUtility.h>
#include <vgKernel/vgkRendererManager.h>



//PropertiesParam vgVectorLayerEntry::s_ParamArray[s_NumOfParam];
vector<PropertiesParam> vgVectorLayerEntry::s_ParamArray;

vgVectorLayerEntry::vgVectorLayerEntry(vgVector::vgvLayer*	pLayer) 
:vgBaseEntry( VG_ENTRY_2DLAYER , pLayer)
{
	m_strConstShapeCount= vgKernel::ConvertUtility::textCast<String>(pLayer->count());
	this->onChanged(vgKernel::VG_OBS_PROPCHANGED, NULL);
} 
vgVectorLayerEntry::~vgVectorLayerEntry(void)
{
	m_Renderer->unregisterObserver( this );
}

//void vgVectorLayerEntry::OnPropertyChanged(string paramName)
//{
//	//vgVector::vgvLayer*	pLayer = (vgVector::vgvLayer*)m_Renderer;
//	m_Renderer->setvisible(m_bIsLayerVisible);
//	// 更新TREEITEM
//	vgUIController::GetInstance()->GetWorkSpaceBar()->SetItemText(hTreeItem, GetName());
//}
void vgVectorLayerEntry::OnPropertyChanged(string paramName)
{
	this->getRender()->setVisible(m_bIsLayerVisible);

	m_LayerCenterPoint.z	= -m_posZMinus;

	Vector3 aa = vgCore::vgCoordinate::getSingleton().GetSceneCood();

	// undo redo ==============================================
	Vector3 offset = (Vector3)m_LayerCenterPoint
		- this->getRender()->getBoundingBox().getCenter() - aa;

	vgKernel::SelectManager::getSingleton().setsumtrans\
		(vgKernel::Vec3(offset.x,offset.y,offset.z));

	// ========================================================
	vgVector::vgvLayer* pLayer = dynamic_cast<vgVector::vgvLayer*>(this->getRender());
	//pLayer->setRenderType(vgVector::vgRenderNormal);
	this->getRender()->moveTo(m_LayerCenterPoint.x - aa.x, 
		m_LayerCenterPoint.y - aa.y, m_LayerCenterPoint.z - aa.z);
	pLayer->setRenderType( vgVector::RenderType(!m_bIsEdit) );

	vgKernel::SelectManager::getSingleton().updateBox();



	// 更新TREEITEM
	vgUIController::GetInstance()->GetWorkSpaceBar()->SetItemText(hTreeItem, GetName());
}


void vgVectorLayerEntry::onChanged(int eventId, void *param)
{
	if (eventId == vgKernel::VG_OBS_PROPCHANGED)
	{
		m_LayerCenterPoint	= m_Renderer->getBoundingBox().getCenter();

		m_LayerCenterPoint	+= vgKernel::Vec3(
			vgCore::vgCoordinate::getSingleton().GetSceneCood().x,
			vgCore::vgCoordinate::getSingleton().GetSceneCood().y,
			vgCore::vgCoordinate::getSingleton().GetSceneCood().z);

		m_bIsLayerVisible	= m_Renderer->getVisible();

		vgVector::vgvLayer*	pLayer = (vgVector::vgvLayer*)m_Renderer;
		m_bIsEdit	= !pLayer->getRenderType();

		int	nShapeCount = pLayer->count();
		m_strConstShapeCount = vgKernel::ConvertUtility::textCast<String>(nShapeCount);			


		if (this == vgUIController::GetInstance()->GetCurrentSelectedNode())
		{
			s_ParamArray[1].pProp->SetValue(m_LayerCenterPoint.x);
			s_ParamArray[2].pProp->SetValue(m_LayerCenterPoint.y);
			m_posZMinus	= -m_LayerCenterPoint.z;
			s_ParamArray[3].pProp->SetValue(m_posZMinus);

			s_ParamArray[6].pProp->SetValue(m_bIsLayerVisible);
			s_ParamArray[7].pProp->SetValue(m_bIsEdit);
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

	s_ParamArray.clear();
	PropertiesParam param;


	// Item 0
	param.label = "层中心坐标值设置";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = "设置层中心坐标值";
	s_ParamArray.push_back( param );

	// Item 1
	param.label = "X 坐标";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &m_LayerCenterPoint.x;
	param.comment = "设置X坐标";
	s_ParamArray.push_back( param );

	// Item 2
	param.label = "Y 坐标";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &m_LayerCenterPoint.y;
	param.comment = "设置Y坐标";
	s_ParamArray.push_back( param );

	// Item 3
	m_posZMinus = - m_LayerCenterPoint.z;
	param.label = "Z 坐标";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &m_posZMinus;
	param.comment = "设置Z坐标";
	s_ParamArray.push_back( param );

	// Item 4
	param.label = "其他设置";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = string();
	s_ParamArray.push_back( param );

	// Item 5
	param.label = "物体名称";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_STR;
	param.connectedPtr = m_Renderer->getNamePtr();
	param.comment = "物体的名称";
	s_ParamArray.push_back( param );

	// Item 6
	param.label = "可见标记";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_BOOL;
	param.connectedPtr = &m_bIsLayerVisible;
	param.comment = "层可见性标记";
	s_ParamArray.push_back( param );

	// add by lss when 2008-12-16 9:19:11
	// Item 7
	param.label = "编辑标记";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_BOOL;
	param.connectedPtr = &m_bIsEdit;
	param.comment = "层编辑状态标记";
	s_ParamArray.push_back( param );

	// Item 8
	param.label = "图元数目";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_CONST_STR;
	param.connectedPtr = &m_strConstShapeCount;
	param.comment = "层内包含图元的总数";
	s_ParamArray.push_back( param );

	vgPropertyPage* propPage = vgUIController::GetInstance()->GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

	//propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
	propPage->ConnectNode(this, &s_ParamArray);

	pageViewBar->AddTab("自动属性", propPage);
}
