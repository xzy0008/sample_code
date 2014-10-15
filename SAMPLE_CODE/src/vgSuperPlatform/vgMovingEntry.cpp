#include <vgStableHeaders.h>
#include "vgMovingEntry.h"
#include "vgPropertyPage.h"

#include <vgKernel/vgkVec3.h>
#include <vgMesh/vgmMeshManager.h>
#include <vgMath/vgfVector3.h>




template< class T>
//PropertiesParam vgMovingEntry<T>::s_ParamArray[s_NumOfParam];
//vector<PropertiesParam> vgMovingEntry::s_ParamArray;

template< class T >
vgMovingEntry< T >::vgMovingEntry(T* pObject)
	:vgBaseEntry( VG_ENTRY_MOVING , pObject )
{
	assert( pObject != NULL );

	m_Positionx = pObject->m_Position.x;
	m_Positiony = pObject->m_Position.y;
	m_Positionz = pObject->m_Position.z;
	
	if (pObject)
	{
		m_pObject = pObject;
		
		m_sCaption = string( pObject->GetName() );

		//dynamic_cast<ObserverHandler*>
		m_pObject->registerObserver( this );
	}

}

//template< class T >
//void vgMovingEntry< T >::OnPropertyChanged()
//{
//	m_Positionz = - m_PositionzMinus;
//	m_pObject->SetPosition( Vector3(m_Positionx, m_Positiony, m_Positionz) );
//}
template< class T >
void vgMovingEntry< T >::OnChanged(int eventId, void *param)
{
	Vector3 pos = m_pObject->GetPosition();


	m_Positionx = pos.x;
	m_Positiony = pos.y;
	m_Positionz = pos.z;

	//TRACE("New Camera Position %.2f %.2f %.2f \n", posPtr->x, posPtr->y, posPtr->z);
	if (this == vgUIController::GetInstance()->GetCurrentSelectedNode())
	{
		s_ParamArray[1].pProp->SetValue(m_Positionx);
		s_ParamArray[2].pProp->SetValue(m_Positiony);
		m_PositionzMinus = - m_Positionz;
		s_ParamArray[3].pProp->SetValue(m_PositionzMinus);
	}
}
//template< class T >
//void vgMovingEntry< T >::AddNodeTabs()
//{
//	vgUIController::GetInstance()->RemoveAllPages();
//
//	vgPropertiesViewBar* pageViewBar = vgUIController::GetInstance()->GetPropertiesViewBar();
//
//	s_ParamArray[0].label = "坐标值设置";
//	s_ParamArray[0].typeId = PROP_ITEM_GROUP;
//	s_ParamArray[0].dataType = PROP_DATA_NONE;
//	s_ParamArray[0].connectedPtr = NULL;
//	s_ParamArray[0].comment = "设置物体坐标";
//
//	s_ParamArray[1].label = "X 坐标";
//	s_ParamArray[1].typeId = PROP_ITEM_DATA;
//	s_ParamArray[1].dataType = PROP_DATA_FLOAT;
//	s_ParamArray[1].connectedPtr = &m_Positionx;
//	s_ParamArray[1].comment = "设置X坐标";
//
//
//	s_ParamArray[2].label = "Y 坐标";
//	s_ParamArray[2].typeId = PROP_ITEM_DATA;
//	s_ParamArray[2].dataType = PROP_DATA_FLOAT;
//	s_ParamArray[2].connectedPtr = &m_Positiony;
//	s_ParamArray[2].comment = "设置Y坐标";
//
//	s_ParamArray[3].label = "Z 坐标";
//	s_ParamArray[3].typeId = PROP_ITEM_DATA;
//	s_ParamArray[3].dataType = PROP_DATA_FLOAT;
//	s_ParamArray[3].connectedPtr = &m_PositionzMinus;
//	s_ParamArray[3].comment = "设置Z坐标";
//
//	s_ParamArray[4].label = "其他设置";
//	s_ParamArray[4].typeId = PROP_ITEM_GROUP;
//	s_ParamArray[4].dataType = PROP_DATA_NONE;
//	s_ParamArray[4].connectedPtr = NULL;
//	s_ParamArray[4].comment = string();
//
//	s_ParamArray[5].label = "物体名称";
//	s_ParamArray[5].typeId = PROP_ITEM_DATA;
//	s_ParamArray[5].dataType = PROP_DATA_STR;
//	s_ParamArray[5].connectedPtr = &m_sCaption;
//	s_ParamArray[5].comment = "物体的名称";
//
//	s_ParamArray[6].label = "起始帧";
//	s_ParamArray[6].typeId = PROP_ITEM_DATA;
//	s_ParamArray[6].dataType = PROP_DATA_INT;
//	s_ParamArray[6].connectedPtr = &m_startframe;
//	s_ParamArray[6].comment = "起始帧";
//
//	s_ParamArray[7].label = "结束帧";
//	s_ParamArray[7].typeId = PROP_ITEM_DATA;
//	s_ParamArray[7].dataType = PROP_DATA_INT;
//	s_ParamArray[7].connectedPtr = &m_endframe;
//	s_ParamArray[7].comment = "结束帧";
//
//	s_ParamArray[8].label = "播放";
//	s_ParamArray[8].typeId = PROP_ITEM_DATA;
//	s_ParamArray[8].dataType = PROP_DATA_BOOL;
//	s_ParamArray[8].connectedPtr = &b_play;
//	s_ParamArray[8].comment = "播放";
//
//	vgPropertyPage* propPage = vgUIController::GetInstance()->GetPropPage();
//	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());
//
//	propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
//
//	pageViewBar->AddTab("自动属性", propPage);
//}
//
//
