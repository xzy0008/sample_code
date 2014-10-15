
#include <vgStableHeaders.h>
#include "gismatchentry.h"
#include <vgKernel/vgkSelectManager.h>

#include "vgUIController.h"

/**
@date 	 9/23/2008 9:20
@author  YX

@brief 	

@see    
*/


namespace vgCore{

	PropertiesParam vgGisMatchEntry::s_ParamArray[s_NumOfParam];


	void vgGisMatchEntry::OnPropertyChanged(string paramName) 
	{
		vgUIController::GetInstance()->GetWorkSpaceBar()->SetItemText(hTreeItem, 
			GetName() );
		m_posZ = - m_posZMinus;

		vggismatch* pObject = ( vggismatch*) m_Renderer;
		
 		Vector3 offset = Vector3( m_posX, m_posY, m_posZ)
 			- pObject->GetPosition() - vgCore::vgCoordinate::getSingleton().GetSceneCood();
 		pObject->translate( offset.x, offset.y, offset.z );
		
		pObject->SetHeight(m_height);

//----------------------------------------------------------
		if ((m_width!= pObject->m_width)||(m_density!= pObject->m_texdensity)
								||(m_luya!= pObject->m_luya))
		{	
			pObject->SetWidth(m_width,pObject->GetPosition());

			pObject->SetDensity(m_density);

			pObject->SetLuyaHeight(m_luya);

			pObject->RenderPoints.clear();
			pObject->LuyaPoints1.clear();
			pObject->LuyaPoints2.clear();
			pObject->uv_u1.clear();
			pObject->uv_u2.clear();
		
			if (pObject->matchpath.size()>= 2)
			{
				pObject->ReGenRoadWithPoints();
			}
		}
		vgKernel::SelectManager::getSingleton().updateBox(); 
	}

	void vgGisMatchEntry::onChanged(int eventId, void *param)
	{
		if (eventId == vgKernel::VG_OBS_PROPCHANGED)
		{
			vggismatch *pObject = ( vggismatch*) m_Renderer;

			Vector3 pos = pObject->GetPosition();

			m_posX = pos.x + vgCore::vgCoordinate::getSingleton().GetSceneCood().x;
			m_posY = pos.y + vgCore::vgCoordinate::getSingleton().GetSceneCood().y;
			m_posZ = pos.z + vgCore::vgCoordinate::getSingleton().GetSceneCood().z;

// 			m_height = pObject->GetHeight();
// 			m_width  = pObject->GetWidth();
// 			m_luya   = pObject->GetLuyaHeight();

			if (this == vgUIController::GetInstance()->GetCurrentSelectedNode())
			{	

				s_ParamArray[1].pProp->SetValue(m_posX);
				s_ParamArray[2].pProp->SetValue(m_posY);
				m_posZMinus = - m_posZ;
				s_ParamArray[3].pProp->SetValue(m_posZMinus/*m_posZ*/);
				
				s_ParamArray[6].pProp->SetValue(m_height);
 				s_ParamArray[7].pProp->SetValue(m_width);
				s_ParamArray[8].pProp->SetValue(m_density);
 				s_ParamArray[9].pProp->SetValue(m_luya);
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

	void vgGisMatchEntry::AddNodeTabs()
	{
		vgUIController::GetInstance()->RemoveAllPages();

		vgPropertiesViewBar* pageViewBar = vgUIController::GetInstance()->GetPropertiesViewBar();

#if VGK_LANG_CHS

		s_ParamArray[0].label = "匹配道路坐标值设置";
		s_ParamArray[0].typeId = PROP_ITEM_GROUP;
		s_ParamArray[0].dataType = PROP_DATA_NONE;
		s_ParamArray[0].connectedPtr = NULL;
		s_ParamArray[0].comment = "设置相机的坐标";

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
		s_ParamArray[3].connectedPtr = &m_posZMinus/*m_posZ*/;
		s_ParamArray[3].comment = "设置Z坐标";

		s_ParamArray[4].label = "其他设置";
		s_ParamArray[4].typeId = PROP_ITEM_GROUP;
		s_ParamArray[4].dataType = PROP_DATA_NONE;
		s_ParamArray[4].connectedPtr = NULL;
		s_ParamArray[4].comment = string();

		s_ParamArray[5].label = "道路名称";
		s_ParamArray[5].typeId = PROP_ITEM_DATA;
		s_ParamArray[5].dataType = PROP_DATA_STR;
		s_ParamArray[5].connectedPtr = m_Renderer->getNamePtr();;
		s_ParamArray[5].comment = "道路的名称";

		s_ParamArray[6].label = "道路相对地面高度";
		s_ParamArray[6].typeId = PROP_ITEM_DATA;
		s_ParamArray[6].dataType = PROP_DATA_FLOAT;
		s_ParamArray[6].connectedPtr = &m_height;
		s_ParamArray[6].comment = "设置相对高度";

		s_ParamArray[7].label = "道路宽度";
		s_ParamArray[7].typeId = PROP_ITEM_DATA;
		s_ParamArray[7].dataType = PROP_DATA_FLOAT;
		s_ParamArray[7].connectedPtr = &m_width;
		s_ParamArray[7].comment = "设置道路的宽度";

		s_ParamArray[8].label = "纹理密度";
		s_ParamArray[8].typeId = PROP_ITEM_DATA;
		s_ParamArray[8].dataType = PROP_DATA_FLOAT;
		s_ParamArray[8].connectedPtr = &m_density;
		s_ParamArray[8].comment = "设置纹理的密度";

		s_ParamArray[9].label = "路丫高度";
		s_ParamArray[9].typeId = PROP_ITEM_DATA;
		s_ParamArray[9].dataType = PROP_DATA_FLOAT;
		s_ParamArray[9].connectedPtr = &m_luya;
		s_ParamArray[9].comment = "设置路丫的高度";




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
		s_ParamArray[1].connectedPtr = &m_posX;
		s_ParamArray[1].comment = "";


		s_ParamArray[2].label = "Y";
		s_ParamArray[2].typeId = PROP_ITEM_DATA;
		s_ParamArray[2].dataType = PROP_DATA_FLOAT;
		s_ParamArray[2].connectedPtr = &m_posY;
		s_ParamArray[2].comment = "";

		s_ParamArray[3].label = "Z";
		s_ParamArray[3].typeId = PROP_ITEM_DATA;
		s_ParamArray[3].dataType = PROP_DATA_FLOAT;
		s_ParamArray[3].connectedPtr = &m_posZMinus/*m_posZ*/;
		s_ParamArray[3].comment = "";

		s_ParamArray[4].label = "Others";
		s_ParamArray[4].typeId = PROP_ITEM_GROUP;
		s_ParamArray[4].dataType = PROP_DATA_NONE;
		s_ParamArray[4].connectedPtr = NULL;
		s_ParamArray[4].comment = string();

		s_ParamArray[5].label = "Name";
		s_ParamArray[5].typeId = PROP_ITEM_DATA;
		s_ParamArray[5].dataType = PROP_DATA_STR;
		s_ParamArray[5].connectedPtr = m_Renderer->getNamePtr();;
		s_ParamArray[5].comment = "";

		s_ParamArray[6].label = "Height";
		s_ParamArray[6].typeId = PROP_ITEM_DATA;
		s_ParamArray[6].dataType = PROP_DATA_FLOAT;
		s_ParamArray[6].connectedPtr = &m_height;
		s_ParamArray[6].comment = "";

		s_ParamArray[7].label = "Road width";
		s_ParamArray[7].typeId = PROP_ITEM_DATA;
		s_ParamArray[7].dataType = PROP_DATA_FLOAT;
		s_ParamArray[7].connectedPtr = &m_width;
		s_ParamArray[7].comment = "";

		s_ParamArray[8].label = "Texture Density";
		s_ParamArray[8].typeId = PROP_ITEM_DATA;
		s_ParamArray[8].dataType = PROP_DATA_FLOAT;
		s_ParamArray[8].connectedPtr = &m_density;
		s_ParamArray[8].comment = "";

		s_ParamArray[9].label = "Curb height";
		s_ParamArray[9].typeId = PROP_ITEM_DATA;
		s_ParamArray[9].dataType = PROP_DATA_FLOAT;
		s_ParamArray[9].connectedPtr = &m_luya;
		s_ParamArray[9].comment = "";




		vgPropertyPage* propPage = vgUIController::GetInstance()->GetPropPage();
		propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

		propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
		pageViewBar->AddTab("Auto Prop", propPage);
#endif
	}



	CMenu* vgGisMatchEntry::GetContextMenu()
	{
		CMenu *menu = new CMenu;

		VERIFY(menu->CreatePopupMenu());
		//VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_GOTO, _T("转到")));
		//VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_DELETE,_T("删除")));

		return menu;
	}

	vgGisMatchEntry::vgGisMatchEntry( vggismatch* gisMatch /*= NULL*/ ) : vgBaseEntry( VG_ENTRY_GISMATCH , gisMatch )
	{
		assert( gisMatch != NULL );

		Vector3 pos = gisMatch->GetPosition();
		m_posX = pos.x + vgCore::vgCoordinate::getSingleton().GetSceneCood().x;
		m_posY = pos.y + vgCore::vgCoordinate::getSingleton().GetSceneCood().y;
		m_posZ = pos.z + vgCore::vgCoordinate::getSingleton().GetSceneCood().z;
		m_posZMinus = - m_posZ;

		m_height = gisMatch->GetHeight();
		m_density = gisMatch->GetDensity();
		m_luya = gisMatch->GetLuyaHeight();
		m_width = gisMatch->GetWidth();

		vgCore::vgCoordinate::getSingleton().registerObserver(this);
	}

}//namespace vgCore