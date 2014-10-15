
#include <vgStableHeaders.h>
#include "vgVectorGeometryEntry.h"
#include "vgPropertyPage.h"

#include <vgKernel/vgkConvertUtility.h>
#include <vgDatabaseEntry.h>

//PropertiesParam vgVectorGeometryEntry::s_ParamArray[s_NumOfParam];

vgVectorGeometryEntry::vgVectorGeometryEntry(vgVector::vgvGeometry*	pGeometry) 
	:vgDatabaseEntry( VG_ENTRY_2DGEOMETRY , pGeometry)
{
	this->OnChanged(vgKernel::VG_OBS_PROPCHANGED, NULL);
}

vgVectorGeometryEntry::~vgVectorGeometryEntry(void)
{
	m_Renderer->unregisterObserver( this );
	m_strFieldPtrArray.clear();
}

//void vgVectorGeometryEntry::OnPropertyChanged(string paramName)
//{
//
//}

void vgVectorGeometryEntry::OnChanged(int eventId, void *param)
{
	if (eventId == vgKernel::VG_OBS_PROPCHANGED)
	{
		//vgVector::vgvLayer*	pLayer = (vgVector::vgvLayer*)m_Renderer;
		m_CenterPoint	= m_Renderer->getBoundingBox().getCenter();
		
		m_CenterPoint	+= vgKernel::Vec3(
			vgCore::vgCoordinate::getSingleton().GetSceneCood().x,
			vgCore::vgCoordinate::getSingleton().GetSceneCood().y,
			vgCore::vgCoordinate::getSingleton().GetSceneCood().z);
		
		m_bIsVisible	= m_Renderer->getvisible();

		
		if (this == vgUIController::GetInstance()->GetCurrentSelectedNode())
		{
			_params[1].pProp->SetValue(m_CenterPoint.x);
			_params[2].pProp->SetValue(m_CenterPoint.y);
			m_posZMinus	= -m_CenterPoint.z;
			_params[3].pProp->SetValue(m_posZMinus);
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

//void vgVectorGeometryEntry::AddNodeTabs()
//{
////	vgUIController::GetInstance()->RemoveAllPages();
////
////	vgPropertiesViewBar* pageViewBar = vgUIController::GetInstance()->GetPropertiesViewBar();
////
////	m_strFieldPtrArray.clear();
////	_params.clear();
////	PropertiesParam param;
////
////	param.label = "层中心坐标值设置";
////	param.typeId = PROP_ITEM_GROUP;
////	param.dataType = PROP_DATA_NONE;
////	param.connectedPtr = NULL;
////	param.comment = "设置层中心坐标值";
////	_params.push_back( param );
////
////	param.label = "X 坐标";
////	param.typeId = PROP_ITEM_DATA;
////	param.dataType = PROP_DATA_FLOAT;
////	param.connectedPtr = &m_CenterPoint.x;
////	param.comment = "设置X坐标";
////	_params.push_back( param );
////
////	param.label = "Y 坐标";
////	param.typeId = PROP_ITEM_DATA;
////	param.dataType = PROP_DATA_FLOAT;
////	param.connectedPtr = &m_CenterPoint.y;
////	param.comment = "设置Y坐标";
////	_params.push_back( param );
////
////	m_posZMinus = - m_CenterPoint.z;
////	param.label = "Z 坐标";
////	param.typeId = PROP_ITEM_DATA;
////	param.dataType = PROP_DATA_FLOAT;
////	param.connectedPtr = &m_posZMinus;
////	param.comment = "设置Z坐标";
////	_params.push_back( param );
////
////	param.label = "其他设置";
////	param.
////
////	param.label = "数据库记录";
////	param.typeId = PROP_ITEM_GROUP;
////	param.dataType = PROP_DATA_NONE;
////	param.connectedPtr = NULL;
////	param.comment = string();
////	_params.push_back( param );
////
////	vgVector::vgvGeometry*	pGeometry = dynamic_cast<vgVector::vgvGeometry*>(m_Renderer);
////	if (!pGeometry)
////	{
////		return;
////	}
////
////	vgVector::vgvAttribute*	pAttribute = pGeometry->getAttributePtr();
////
////	if (pAttribute)
////	{
////		int iField = 0;
////#ifndef	TEMP_BUFFER_SIZE
////#define TEMP_BUFFER_SIZE 80
////		char	szTempBuffer[TEMP_BUFFER_SIZE];
////		String	strRecord;
////		for (vgVector::FieldValueArrayItr itr = pAttribute->getFieldValueArrayPtr()->begin() ;
////			itr != pAttribute->getFieldValueArrayPtr()->end(); itr++ )
////		{
////			OGRFieldDefn        *poFDefn = pAttribute->getFeatureDefn()->GetFieldDefn( iField++ );
////			char    szFormat[TEMP_BUFFER_SIZE];
////
////			switch (poFDefn->GetType())
////			{
////			case OFTString:
////				{
////					if( 
////						( (*itr)->String == NULL )
////						|| ( (*itr)->Set.nMarker1 == OGRUnsetMarker ) 
////						)
////					{
////						snprintf( szTempBuffer, TEMP_BUFFER_SIZE -1,
////							"%s", "NULL" );
////					}
////					else
////					{
////						snprintf( szTempBuffer, TEMP_BUFFER_SIZE -1,
////							"%s", (*itr)->String );
////					}
////				}
////				break;
////
////			case OFTInteger:
////				{
////					snprintf( szTempBuffer, TEMP_BUFFER_SIZE -1,
////						"%d", (*itr)->Integer );
////				}				
////				break;
////
////			case OFTReal:
////				{
////					if( poFDefn->GetWidth() != 0 )
////					{
////						snprintf( szFormat, TEMP_BUFFER_SIZE -1, "%%-%d.%df",
////							poFDefn->GetWidth(), poFDefn->GetPrecision() );
////					}
////					else
////						strcpy( szFormat, "%.15g" );
////
////					snprintf( szTempBuffer, TEMP_BUFFER_SIZE -1,
////						szFormat, (*itr)->Real );
////				}				
////				break;
////
////			default:
////				{
////					snprintf( szTempBuffer, TEMP_BUFFER_SIZE -1,
////						"%s", "NULL" );
////				}
////				break;
////
////			}//switch
////			String	*pString = new String(szTempBuffer);
////			
////			m_strFieldPtrArray.push_back( ShareShringPtr(pString) );
////
////			param.label = poFDefn->GetNameRef();
////			param.typeId = PROP_ITEM_DATA;
////			param.dataType = PROP_DATA_STR;
////			param.connectedPtr = pString;
////			param.comment = poFDefn->GetNameRef();
////
////			_params.push_back( param );
////
////		}//for
////
////#endif//TEMP_BUFFER_SIZE
////	}
////	/*s_ParamArray[7].label = "图元数目";
////	s_ParamArray[7].typeId = PROP_ITEM_DATA;
////	s_ParamArray[7].dataType = PROP_DATA_CONST_STR;
////	s_ParamArray[7].connectedPtr = &m_strConstShapeCount;
////	s_ParamArray[7].comment = "层内包含图元的总数";*/
////
////	vgPropertyPage* propPage = vgUIController::GetInstance()->GetPropPage();
////	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());
////
////	propPage->ConnectNode(this, &_params[0],  _params.size() );
////	pageViewBar->AddTab("自动属性", propPage);
//}

void vgVectorGeometryEntry::AddSingleTabPage()
{
	vgUIController::GetInstance()->RemoveAllPages();

	vgPropertiesViewBar* pageViewBar = vgUIController::GetInstance()->GetPropertiesViewBar();

	s_ParamArray.clear();
	PropertiesParam param;

	param.label = "层中心坐标值设置";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = "设置层中心坐标值";
	s_ParamArray.push_back( param );

	param.label = "X 坐标";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &m_CenterPoint.x;
	param.comment = "设置X坐标";
	s_ParamArray.push_back( param );

	param.label = "Y 坐标";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &m_CenterPoint.y;
	param.comment = "设置Y坐标";
	s_ParamArray.push_back( param );

	m_posZMinus = - m_CenterPoint.z;
	param.label = "Z 坐标";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &m_posZMinus;
	param.comment = "设置Z坐标";
	s_ParamArray.push_back( param );

	param.label = "其他设置";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = string();
	s_ParamArray.push_back( param );

	param.label = "物体名称";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_STR;
	param.connectedPtr = m_Renderer->getNamePtr();
	param.comment = "物体的名称";
	s_ParamArray.push_back( param );

	param.label = "可见标记";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_BOOL;
	param.connectedPtr = &m_bIsVisible;
	param.comment = "层可见性标记";
	s_ParamArray.push_back( param );

	// 数据库profile配置 ========================================================

	param.label = "数据库";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = string();
	s_ParamArray.push_back(param);

	param.label = "数据库配置";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_OPTION_START;
	param.connectedPtr = &m_profileName;
	s_ParamArray.push_back(param);

	vector<vgDatabase::QueryProfile> profiles = vgDatabase::ProfileManager::getSingleton().GetProfile();

	for (INT i=0; i<profiles.size(); i++)
	{
		if (profiles[i].GetName() != m_profileName)
		{
			param.label = profiles[i].GetName();
			param.typeId = PROP_ITEM_DATA;
			param.dataType = PROP_DATA_OPTION_ITEM;
			s_ParamArray.push_back(param);
		}
	}

	if (m_profileName != "")
	{
		param.label = "";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_OPTION_ITEM;
		s_ParamArray.push_back(param);
	}

	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_OPTION_END;
	s_ParamArray.push_back(param);

	// ===========================================================================
	vgPropertyPage* propPage = vgUIController::GetInstance()->GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

	//propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
	propPage->ConnectNode(this, &s_ParamArray);

	pageViewBar->AddTab("自动属性", propPage);

	// 调用父类生成Database属性的Tab页
	vgDatabaseEntry::AddSingleTabPage();

	vgUIController::GetInstance()->SetCurrentSelectedNode(this);
}

void vgVectorGeometryEntry::AddGroupTabPage()
{
	vgUIController::GetInstance()->RemoveAllPages();

	vgPropertiesViewBar* pageViewBar = vgUIController::GetInstance()->GetPropertiesViewBar();

	s_GroupParamArray.clear();
	PropertiesParam param;

	param.label = "层中心坐标值设置";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = "设置层中心坐标值";
	s_GroupParamArray.push_back( param );

	param.label = "X 坐标";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &m_CenterPoint.x;
	param.comment = "设置X坐标";
	s_GroupParamArray.push_back( param );

	param.label = "Y 坐标";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &m_CenterPoint.y;
	param.comment = "设置Y坐标";
	s_GroupParamArray.push_back( param );

	m_posZMinus = - m_CenterPoint.z;
	param.label = "Z 坐标";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_FLOAT;
	param.connectedPtr = &m_posZMinus;
	param.comment = "设置Z坐标";
	s_GroupParamArray.push_back( param );

	param.label = "其他设置";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = string();
	s_GroupParamArray.push_back( param );

	param.label = "物体名称";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_STR;
	param.connectedPtr = m_Renderer->getNamePtr();
	param.comment = "物体的名称";
	s_GroupParamArray.push_back( param );

	param.label = "可见标记";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_BOOL;
	param.connectedPtr = &m_bIsVisible;
	param.comment = "层可见性标记";
	s_GroupParamArray.push_back( param );

	// Database ==========================================================
	param.label = "数据库";
	param.typeId = PROP_ITEM_GROUP;
	param.dataType = PROP_DATA_NONE;
	param.connectedPtr = NULL;
	param.comment = "数据库参数设置";
	s_GroupParamArray.push_back(param);

	s_groupProfileName = "";

	param.label = "数据库配置";
	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_OPTION_START;
	param.connectedPtr = &s_groupProfileName;
	s_GroupParamArray.push_back(param);

	vector<vgDatabase::QueryProfile> profiles = vgDatabase::ProfileManager::getSingleton().GetProfile();

	for (int i=0; i<profiles.size(); i++)
	{
		param.label = profiles[i].GetName();
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_OPTION_ITEM;
		s_GroupParamArray.push_back(param);
	}

	param.typeId = PROP_ITEM_DATA;
	param.dataType = PROP_DATA_OPTION_END;
	s_GroupParamArray.push_back(param);


	vgPropertyPage* propPage = vgUIController::GetInstance()->GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());
	propPage->ConnectNode(this, &s_GroupParamArray);

	//propPage->ConnectNode(this, s_GroupParamArray, s_NumOfGroupParam);
	pageViewBar->AddTab("Group属性", propPage);

	vgUIController::GetInstance()->SetCurrentSelectedNode(this);
}

void vgVectorGeometryEntry::OnSinglePropertyChanged( string paramName )
{
	//vgVector::vgvGe*	pLayer = (vgVector::vgvLayer*)m_Renderer;
	m_Renderer->setvisible(m_bIsVisible);
	// 更新TREEITEM
	vgUIController::GetInstance()->GetWorkSpaceBar()->SetItemText(hTreeItem, GetName());
}

void vgVectorGeometryEntry::OnGroupPropertyChanged( string paramName )
{
	if (paramName == "数据库配置")
	{
		//AfxMessageBox("In here");
		for (int i=0; i<s_group_list.size(); i++)
		{
			((vgVectorGeometryEntry*)s_group_list[i])->m_profileName = s_groupProfileName;
		}

		return ;
	}
}

void vgVectorGeometryEntry::OnGroupChanged( float sdx, float sdy, float sdz )
{
	return;
}