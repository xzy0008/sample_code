
#include <vgStableHeaders.h>
#include "vgBillboardEntry.h"
#include <vgKernel/vgkSelectManager.h>

#include <vgUIController/vgUIController.h>



namespace vgMod{

	PropertiesParam vgBillboardEntry::s_ParamArray[s_NumOfParam];


	void vgBillboardEntry::OnPropertyChanged(string paramName)
	{
		//m_pCamera->setCurrentPosition(vgKernel::Vec3(m_eyePosX, m_eyePosY, m_eyePosZ));
		m_Positionz = - m_PositionzMinus;
		BillboardNode *pObject = ( BillboardNode*) m_Renderer;
		Vector3 offset = Vector3(m_Positionx, m_Positiony, m_Positionz) 
			- pObject->GetPosition() - vgKernel::CoordSystem::getSingleton().getProjectionCoord();
		pObject->translate( offset );
		// 更新TREEITEM

		pObject->mBillboard.setHeight( m_height );
		pObject->mBillboard.setWidth( m_width );
		
		vgUI::UIController::getSingleton().GetWorkSpaceBar()->SetItemText(hTreeItem, pObject->getName());
		pObject->SetName( (TCHAR*)m_Renderer->getName().c_str() );
		
		vgKernel::SelectManager::getSingleton().updateBox();

	
	}

	void vgBillboardEntry::onChanged(int eventId, void *param)
	{
		if (eventId == vgKernel::VG_OBS_PROPCHANGED)
		{
			BillboardNode *pObject = ( BillboardNode*) m_Renderer;

			Vector3 pos = pObject->GetPosition();

			m_Positionx = pos.x + vgKernel::CoordSystem::getSingleton().getProjectionCoord().x;
			m_Positiony = pos.y + vgKernel::CoordSystem::getSingleton().getProjectionCoord().y;
			m_Positionz = pos.z + vgKernel::CoordSystem::getSingleton().getProjectionCoord().z;


			m_height = pObject->GetHeight();
			m_width = pObject->GetWidth();


			////TRACE("New Camera Position %.2f %.2f %.2f \n", posPtr->x, posPtr->y, posPtr->z);
			if (this == vgUI::UIController::getSingleton().GetCurrentSelectedNode())
			{
				s_ParamArray[1].pProp->SetValue(m_Positionx);
				s_ParamArray[2].pProp->SetValue(m_Positiony);
				m_PositionzMinus = - m_Positionz;
				s_ParamArray[3].pProp->SetValue(m_PositionzMinus);

				s_ParamArray[5].pProp->SetValue(m_height);
				s_ParamArray[6].pProp->SetValue(m_width);
			}
		}

		if (eventId == vgKernel::VG_OBS_SELECTCHAGNED)
		{
			vgUI::UIController::getSingleton().SelectNode(this);
		}

		if (eventId == vgKernel::VG_OBS_ADDSELECTION)
		{
			vgUI::UIController::getSingleton().AddSelection(this);

			return ;
		}
	}

	void vgBillboardEntry::AddNodeTabs()
	{
		vgUI::UIController::getSingleton().RemoveAllPages();

		vgPropertiesViewBar* pageViewBar = vgUI::UIController::getSingleton().GetPropertiesViewBar();

		s_ParamArray[0].label = "坐标值设置";
		s_ParamArray[0].typeId = PROP_ITEM_GROUP;
		s_ParamArray[0].dataType = PROP_DATA_NONE;
		s_ParamArray[0].connectedPtr = NULL;
		s_ParamArray[0].comment = "设置粒子坐标";

		s_ParamArray[1].label = "X 坐标";
		s_ParamArray[1].typeId = PROP_ITEM_DATA;
		s_ParamArray[1].dataType = PROP_DATA_FLOAT;
		s_ParamArray[1].connectedPtr = &m_Positionx;
		s_ParamArray[1].comment = "设置X坐标";


		s_ParamArray[2].label = "Y 坐标";
		s_ParamArray[2].typeId = PROP_ITEM_DATA;
		s_ParamArray[2].dataType = PROP_DATA_FLOAT;
		s_ParamArray[2].connectedPtr = &m_Positiony;
		s_ParamArray[2].comment = "设置Y坐标";

		s_ParamArray[3].label = "Z 坐标";
		s_ParamArray[3].typeId = PROP_ITEM_DATA;
		s_ParamArray[3].dataType = PROP_DATA_FLOAT;
		s_ParamArray[3].connectedPtr = &m_PositionzMinus;
		s_ParamArray[3].comment = "设置Z坐标";

		s_ParamArray[4].label = "其他设置";
		s_ParamArray[4].typeId = PROP_ITEM_GROUP;
		s_ParamArray[4].dataType = PROP_DATA_NONE;
		s_ParamArray[4].connectedPtr = NULL;
		s_ParamArray[4].comment = string();

		s_ParamArray[5].label = "高度";
		s_ParamArray[5].typeId = PROP_ITEM_DATA;
		s_ParamArray[5].dataType = PROP_DATA_FLOAT;
		s_ParamArray[5].connectedPtr = &m_height;
		s_ParamArray[5].comment = "设置高度";

		s_ParamArray[6].label = "宽度";
		s_ParamArray[6].typeId = PROP_ITEM_DATA;
		s_ParamArray[6].dataType = PROP_DATA_FLOAT;
		s_ParamArray[6].connectedPtr = &m_width;
		s_ParamArray[6].comment = "设置宽度";

		s_ParamArray[7].label = "树木名称";
		s_ParamArray[7].typeId = PROP_ITEM_DATA;
		s_ParamArray[7].dataType = PROP_DATA_STR;
		s_ParamArray[7].connectedPtr = m_Renderer->getNamePtr();
		s_ParamArray[7].comment = "设置树木的名称";

		vgPropertyPage* propPage = vgUI::UIController::getSingleton().GetPropPage();
		propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

		propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);

		pageViewBar->AddTab("自动属性", propPage);
	}



	CMenu* vgBillboardEntry::GetContextMenu()
	{
		CMenu *menu = new CMenu;

		VERIFY(menu->CreatePopupMenu());
		VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_GOTO, _T("转到")));
		VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_DELETE,_T("删除")));

		return menu;
	}
}//namespace vgCore