
#include <vgStableHeaders.h>
#include "vgParticleEntry.h"

#include <vgKernel/vgkSelectManager.h>
#include <vgKernel/vgkCoordSystem.h>

#include <vgUIController/vgUIController.h>



namespace vgMod{

	PropertiesParam vgParticleEntry::s_ParamArray[s_NumOfParam];


	void vgParticleEntry::OnSinglePropertyChanged(string paramName)
	{
		//m_pCamera->setCurrentPosition(vgKernel::Vec3(m_eyePosX, m_eyePosY, m_eyePosZ));
		m_Positionz = - m_PositionzMinus;

		vgParticle *pParticle = ( vgParticle*) m_Renderer;
		
		Vector3 offset = Vector3(m_Positionx, m_Positiony, m_Positionz) 
			- pParticle->GetPosition()  - vgKernel::CoordSystem::getSingleton().getProjectionCoord();
		pParticle->translate( offset );
		
		pParticle->SetHeight( m_height );
		pParticle->SetWidth( m_width );
		pParticle->SetSpeed( m_speed );

		// 更新TREEITEM
	
		vgUI::UIController::getSingleton().GetWorkSpaceBar()->SetItemText(hTreeItem, pParticle->getName());
		pParticle->SetName( (TCHAR*)m_Renderer->getName().c_str() );

		vgKernel::SelectManager::getSingleton().updateBox();

	}

	void vgParticleEntry::OnGroupPropertyChanged(string paramName)
	{
		vgParticleEntry* pParticleEntry;
		vgParticle*  pParInGroup;

		//vgDatabaseEntry::OnGroupPropertyChanged(paramName);
		TRACE("%f\n", m_GroupHeight);

		for (int i = 0; i < s_group_list.size(); i++)
		{
			pParticleEntry = ((vgParticleEntry*)s_group_list[i]);
			pParInGroup = (vgParticle*)(pParticleEntry->getRender());

			pParticleEntry->m_height = m_GroupHeight;
			pParInGroup->SetHeight(m_GroupHeight);

			pParticleEntry->m_width = m_GroupWidth;
			pParInGroup->SetWidth(m_GroupWidth);	

			pParticleEntry->m_speed = m_GroupSpeed;
			pParInGroup->SetSpeed(m_GroupSpeed);	

			vgUI::UIController::getSingleton().GetWorkSpaceBar()->SetItemText(hTreeItem, pParInGroup->getName());
			pParInGroup->SetName( (TCHAR*)m_Renderer->getName().c_str() );

			vgKernel::SelectManager::getSingleton().updateBox();
		}

	}

	void vgParticleEntry::OnPropertyChanged(string paramName)
	{
		if (s_group_list.size() > 0)
		{
			OnGroupPropertyChanged(paramName);
		}
		else
		{
			OnSinglePropertyChanged(paramName);
		}
	}

	void vgParticleEntry::onChanged(int eventId, void *param)
	{
		if (eventId == vgKernel::VG_OBS_PROPCHANGED)
		{
			vgParticle *pParticle = ( vgParticle*) m_Renderer;

			Vector3 pos = pParticle->GetPosition();


			m_Positionx = pos.x + vgKernel::CoordSystem::getSingleton().getProjectionCoord().x;
			m_Positiony = pos.y + vgKernel::CoordSystem::getSingleton().getProjectionCoord().y;
			m_Positionz = pos.z + vgKernel::CoordSystem::getSingleton().getProjectionCoord().z;


			m_height	= pParticle->m_height;
			m_width		= pParticle->m_width;
			m_speed		= pParticle->m_speed;

			//TRACE("New Camera Position %.2f %.2f %.2f \n", posPtr->x, posPtr->y, posPtr->z);
			if (this == vgUI::UIController::getSingleton().GetCurrentSelectedNode())
			{
				s_ParamArray[1].pProp->SetValue(m_Positionx);
				s_ParamArray[2].pProp->SetValue(m_Positiony);
				m_PositionzMinus = - m_Positionz;
				s_ParamArray[3].pProp->SetValue(m_PositionzMinus);

				s_ParamArray[5].pProp->SetValue(m_height);
				s_ParamArray[6].pProp->SetValue(m_width);
				s_ParamArray[7].pProp->SetValue(m_speed);
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

	void vgParticleEntry::AddNodeTabs()
	{
		UINT numOfSelectedItem = vgKernel::SelectManager::getSingleton().getSelectedItems().size();
		TRACE("Selected number is %d \n",numOfSelectedItem);
		UINT treeCount = vgUI::UIController::getSingleton().GetWorkSpaceBar()->GetTree().GetSelectedCount();

		s_group_list.clear();

		// 判断是否选择的Renderer和树节点中选择的数量一致
		//if (treeCount == numOfSelectedItem && treeCount > 1)
		if (numOfSelectedItem > 1)
		{
			CEditTreeCtrlEx* pTree = &vgUI::UIController::getSingleton().GetWorkSpaceBar()->GetTree(); 
			list<HTREEITEM> selectedList = pTree->GetSelectedList();
			list<HTREEITEM>::iterator iter = selectedList.begin();
			list<HTREEITEM>::iterator end  = selectedList.end();

			TRACE("%d ", selectedList.size());
			while (iter != end)
			{
				//vgMeshEntry* pMeshEntry = (vgMeshEntry*)(pTree->GetItemData(*iter));
				vgGroupBasedEntry *pGroupEntry =  (vgGroupBasedEntry*)(pTree->GetItemData(*iter));

				// vgMeshEntry* pMeshEntry = (vgMeshEntry*)(pTree->GetItemData(*iter));
				// vgGroupBasedEntry *pGroupEntry =  (vgGroupBasedEntry*)(pTree->GetItemData(*iter));
				// 保证添加进Group的Renderer都是同一个类型
				if (pGroupEntry != NULL && pGroupEntry->getRender()->getType() == this->getRender()->getType())
				{
					s_group_list.push_back(pGroupEntry);
				}
				else
				{
					s_group_list.clear();
					vgUI::UIController::getSingleton().RemoveAllPages();

					// 需更改的goto语句
					goto singleTabs;
					return ;
					// assert(0);
				}

				iter ++;
			}
			AddGroupTabPage();

			return ;
		}

singleTabs:
		AddSingleTabPage();

	}

	void vgParticleEntry::AddGroupTabPage()
	{
		vgUI::UIController::getSingleton().RemoveAllPages();
		getGroupData();
		vgPropertiesViewBar* pageViewBar = vgUI::UIController::getSingleton().GetPropertiesViewBar();

#if VGK_LANG_CHS
		{
			s_ParamArray[0].label = "组属性";
			s_ParamArray[0].typeId = PROP_ITEM_GROUP;
			s_ParamArray[0].dataType = PROP_DATA_NONE;
			s_ParamArray[0].connectedPtr = NULL;
			s_ParamArray[0].comment = string();

			s_ParamArray[1].label = "高度";
			s_ParamArray[1].typeId = PROP_ITEM_DATA;
			s_ParamArray[1].dataType = PROP_DATA_FLOAT;
			s_ParamArray[1].connectedPtr = &m_GroupHeight;
			s_ParamArray[1].comment = string();


			s_ParamArray[2].label = "宽度";
			s_ParamArray[2].typeId = PROP_ITEM_DATA;
			s_ParamArray[2].dataType = PROP_DATA_FLOAT;
			s_ParamArray[2].connectedPtr = &m_GroupWidth;
			s_ParamArray[2].comment = string();

			s_ParamArray[3].label = "速度";
			s_ParamArray[3].typeId = PROP_ITEM_DATA;
			s_ParamArray[3].dataType = PROP_DATA_FLOAT;
			s_ParamArray[3].connectedPtr = &m_GroupSpeed;
			s_ParamArray[3].comment = string();
		}
#else
		{
			s_ParamArray[0].label = "Group Properties";
			s_ParamArray[0].typeId = PROP_ITEM_GROUP;
			s_ParamArray[0].dataType = PROP_DATA_NONE;
			s_ParamArray[0].connectedPtr = NULL;
			s_ParamArray[0].comment = string();

			s_ParamArray[1].label = "Height";
			s_ParamArray[1].typeId = PROP_ITEM_DATA;
			s_ParamArray[1].dataType = PROP_DATA_FLOAT;
			s_ParamArray[1].connectedPtr = &m_GroupHeight;
			s_ParamArray[1].comment = string();


			s_ParamArray[2].label = "Width";
			s_ParamArray[2].typeId = PROP_ITEM_DATA;
			s_ParamArray[2].dataType = PROP_DATA_FLOAT;
			s_ParamArray[2].connectedPtr = &m_GroupWidth;
			s_ParamArray[2].comment = string();

			s_ParamArray[3].label = "Speed";
			s_ParamArray[3].typeId = PROP_ITEM_DATA;
			s_ParamArray[3].dataType = PROP_DATA_FLOAT;
			s_ParamArray[3].connectedPtr = &m_GroupSpeed;
			s_ParamArray[3].comment = string();
		}
#endif

		vgPropertyPage* propPage = vgUI::UIController::getSingleton().GetPropPage();
		propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

		propPage->ConnectNode(this, s_ParamArray, 4);
		pageViewBar->AddTab("自动属性", propPage);
	}

	void vgParticleEntry::getGroupData()
	{
		vgParticleEntry* pParticleEntry;
		vgMod::vgParticle*    pParticle;	

		//暂时取组中第一个对象的属性作为组的显示属性
		pParticleEntry = ((vgParticleEntry*)s_group_list[0]);
		pParticle = (vgMod::vgParticle*)(pParticleEntry->getRender());

		m_GroupHeight = pParticle->m_height;
		m_GroupWidth = pParticle->m_width;
		m_GroupSpeed = pParticle->m_speed;
	}

	void vgParticleEntry::AddSingleTabPage()
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
		s_ParamArray[5].comment = string();

		s_ParamArray[6].label = "宽度";
		s_ParamArray[6].typeId = PROP_ITEM_DATA;
		s_ParamArray[6].dataType = PROP_DATA_FLOAT;
		s_ParamArray[6].connectedPtr = &m_width;
		s_ParamArray[6].comment = string();

		s_ParamArray[7].label = "速度";
		s_ParamArray[7].typeId = PROP_ITEM_DATA;
		s_ParamArray[7].dataType = PROP_DATA_FLOAT;
		s_ParamArray[7].connectedPtr = &m_speed;
		s_ParamArray[7].comment = string();

		s_ParamArray[8].label = "特效名称";
		s_ParamArray[8].typeId = PROP_ITEM_DATA;
		s_ParamArray[8].dataType = PROP_DATA_STR;
		s_ParamArray[8].connectedPtr = m_Renderer->getNamePtr();
		s_ParamArray[8].comment = "设置特效的名称";

		vgPropertyPage* propPage = vgUI::UIController::getSingleton().GetPropPage();
		propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

		propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
		pageViewBar->AddTab("自动属性", propPage);
	}

	CMenu* vgParticleEntry::GetContextMenu()
	{
		CMenu *menu = new CMenu;

		VERIFY(menu->CreatePopupMenu());
		VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_GOTO, _T("转到")));
		VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_DELETE,_T("删除")));

		return menu;
	}
}//namespace vgCore