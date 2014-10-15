

#pragma once

#include <vgEntry/vgBaseEntry.h>
#include <vgUIController/vgPropertyPage.h>
#include <vgKernel/vgkUniqueID.h>

#include "vgEffect/vgWaterNode.h" 
#include "vgEffect/vgSkyboxNode.h" 
#include <vgEffect/vgMirrorNode.h>
#include <vgEffect/vgMetalNode.h>
#include <vgEffect/vgBrightfloorNode.h>
#include <vgEffect/vgAviNode.h>
#include <vgEffect/vgGlassNode.h>

//#include <vgMesh/vgmMeshItem.h>
//*#include "vgUIController.h"*/
#include <vgKernel/vgkRendererObserver.h>
#include <vgUIController/vgPropertyPage.h>


namespace vgCore{



	template< class T >
	class vgGPUSpecialEntry : public vgBaseEntry/*, public ChangedObserver*/
	{
	public:
		const static int s_NumOfParam = 5 ;
		static PropertiesParam s_ParamArray[s_NumOfParam];

	public:
		vgGPUSpecialEntry(  T* pObject = NULL)
			: vgBaseEntry( pObject )
		{
			assert( pObject != NULL );
			Vector3 vec = pObject->GetPosition();

			m_Positionx = vec.x + vgCore::vgCoordinate::getSingleton().GetSceneCood().x;
			m_Positiony = vec.y + vgCore::vgCoordinate::getSingleton().GetSceneCood().y;
			m_Positionz = vec.z + vgCore::vgCoordinate::getSingleton().GetSceneCood().z;
			m_PositionzMinus = - m_Positionz;

			vgCore::vgCoordinate::getSingleton().registerObserver(this);

		}

		virtual ~vgGPUSpecialEntry(void)
		{
			((T*)m_Renderer)->unregisterObserver( this );
		}

		void AddNodeTabs();

		int GetSelectedImage() { return 1; }

		int GetUnSelectedImage() { return 2; }

		// 继承自vgBasedNode修改Node后重新设置Object 和TreeItem
		void OnPropertyChanged(string paramName);// { TRACE("Camera Property Changed \n");}

		// 继承自Changed，用于Object修改后更新Node
		void onChanged(int eventId, void *param);

		void UpDataProp() {}

		CMenu* GetContextMenu();

	private:
		//vgCore::ObjectNode* m_pObject;

		// 被修改数据的副本
		float m_Positionx;
		float m_Positiony;
		float m_Positionz, m_PositionzMinus;



		string m_sCaption;
	};

	template< class T >
	PropertiesParam vgGPUSpecialEntry<T>::s_ParamArray[s_NumOfParam];

	template< class T >
	void vgGPUSpecialEntry<T>::OnPropertyChanged(string paramName)
	{
		//m_pCamera->setCurrentPosition(vgKernel::Vec3(m_eyePosX, m_eyePosY, m_eyePosZ));
		m_Positionz = - m_PositionzMinus;
		T *pObject = ( T*) m_Renderer;

		Vector3 offset = Vector3(m_Positionx, m_Positiony, m_Positionz) 
			- pObject->GetPosition() - vgCore::vgCoordinate::getSingleton().GetSceneCood();
		pObject->translate( offset );
		// 更新TREEITEM

		// 更新TREEITEM
		vgUI::UIController::getSingleton().GetWorkSpaceBar()->SetItemText(hTreeItem, pObject->getName());
	
		vgKernel::SelectManager::getSingleton().updateBox();

	}


	template< class T >
	void vgGPUSpecialEntry<T>::onChanged(int eventId, void *param)
	{
		if (eventId == vgKernel::VG_OBS_PROPCHANGED)
		{
			T *pObject = ( T*) m_Renderer;

			Vector3 pos = pObject->GetPosition();

			m_Positionx = pos.x + vgCore::vgCoordinate::getSingleton().GetSceneCood().x;
			m_Positiony = pos.y + vgCore::vgCoordinate::getSingleton().GetSceneCood().y;
			m_Positionz = pos.z + vgCore::vgCoordinate::getSingleton().GetSceneCood().z;


			//TRACE("New Camera Position %.2f %.2f %.2f \n", posPtr->x, posPtr->y, posPtr->z);
			if (this == vgUI::UIController::getSingleton().GetCurrentSelectedNode())
			{
				s_ParamArray[1].pProp->SetValue(m_Positionx);
				s_ParamArray[2].pProp->SetValue(m_Positiony);
				m_PositionzMinus = - m_Positionz;
				s_ParamArray[3].pProp->SetValue(m_PositionzMinus);
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


	template< class T >
	void vgGPUSpecialEntry<T>::AddNodeTabs()
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


		vgPropertyPage* propPage = vgUI::UIController::getSingleton().GetPropPage();
		propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

		propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
		pageViewBar->AddTab("自动属性", propPage);
	}



	template< class T >
	CMenu* vgGPUSpecialEntry<T>::GetContextMenu()
	{
		CMenu *menu = new CMenu;

		VERIFY(menu->CreatePopupMenu());
		VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_GOTO, _T("转到")));
		VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_DELETE,_T("删除")));

		return menu;
	}
}//namespace vgCore
