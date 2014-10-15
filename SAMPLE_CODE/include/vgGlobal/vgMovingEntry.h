/*#pragma once*/
#ifndef __VGMOVINGENTRY_H__
#define __VGMOVINGENTRY_H__

#include <vgEntry/vgBaseEntry.h>

#include <vgUIController/vgUIController.h>

#include <vgKernel/vgkRendererObserver.h>
#include <vgKernel/vgkSelectManager.h>
#include <vgKernel/vgkRendererManager.h>
#include <vgKernel/vgkCoordSystem.h>

template< class T >
class  VGGL_EXPORT vgMovingEntry : public vgBaseEntry	
{
public:
	//const static int s_NumOfParam = 11;
	//static PropertiesParam s_ParamArray[s_NumOfParam];
	// 单个Node属性
	static vector<PropertiesParam> s_ParamArray;

public:
	vgMovingEntry(T* pObject);
	virtual ~vgMovingEntry<T>(void)
	{
		m_pObject->unregisterObserver( this );
	};

	void AddNodeTabs();	

	//add by KingHJ 2010.03.17
	void AddGroupTabPage();

	void AddSingleTabPage();

	virtual String GetName()
	{
		return m_sCaption;
	}

	void getGroupData();

	int GetSelectedImage() { return 1; }

	int GetUnSelectedImage() { return 2; }

	void OnPropertyChanged(string paramName);

	//add by KingHJ 2010.03.17
	void OnSinglePropertyChanged(string paramName);// { TRACE("Camera Property Changed \n");}

	void OnGroupPropertyChanged(string paramName);

	void onChanged(int eventId, void *param);

	void UpDataProp() {}

	CMenu* GetContextMenu();

public:
	 vector<vgGroupBasedEntry*> s_group_list;
	 //vector<PropertiesParam> s_GroupPramArray;

private:
	T* m_pObject;

	// 被修改数据的副本
	float m_Positionx;
	float m_Positiony;
	float m_Positionz, m_PositionzMinus;

	int m_startframe;

	int m_endframe;

	bool b_play;

	bool b_loop;

	bool m_bGroupPlay;
	bool m_bGroupLoop;

	// 测试
	float	m_fStartTime;
	//bool	b_reset;	

	string m_sCaption;
};

template< class T >
vgMovingEntry< T >::vgMovingEntry(T* pObject)
: vgBaseEntry( pObject )
{
	assert( pObject != NULL );
	if (pObject)
	{
		m_Positionx = pObject->m_Position.x + vgKernel::CoordSystem::getSingleton().getProjectionCoord().x;
		m_Positiony = pObject->m_Position.y + vgKernel::CoordSystem::getSingleton().getProjectionCoord().y;
		m_Positionz = pObject->m_Position.z + vgKernel::CoordSystem::getSingleton().getProjectionCoord().z;
		m_PositionzMinus = - m_Positionz;
		b_play = pObject->getPlayingState();
		m_startframe = pObject->getStartFrame();
		m_endframe = pObject->getEndFrame()	;
		b_loop = pObject->getLoopState();

		//b_reset = false;
		m_fStartTime = pObject->getTimeWithFrame(0);
		m_pObject = pObject;

		m_sCaption = string( pObject->getName() );

		vgKernel::CoordSystem::getSingleton().registerObserver(this);

	}

}


template< class T>
//PropertiesParam vgMovingEntry<T>::s_ParamArray[s_NumOfParam];
vector<PropertiesParam> vgMovingEntry<T>::s_ParamArray;



template< class T >
void vgMovingEntry< T >::OnSinglePropertyChanged(string paramName)
{
	m_Positionz = - m_PositionzMinus;
	Vector3 offset = Vector3( m_Positionx, m_Positiony, m_Positionz)
		- m_pObject->GetPosition()  - vgKernel::CoordSystem::getSingleton().getProjectionCoord();
	m_pObject->translate( offset );

	m_pObject->setPlayState( b_play );
	m_pObject->setStartFrame(m_startframe);	
	m_pObject->setEndFrame(m_endframe);
	m_pObject->setLoopState(b_loop);	


	vgUI::UIController::getSingleton().GetWorkSpaceBar()->SetItemText(hTreeItem, m_pObject->getName());
	m_pObject->SetName( (TCHAR*)m_Renderer->getName().c_str() );

	vgKernel::SelectManager::getSingleton().updateBox();
}

template< class T>
void vgMovingEntry< T >::OnPropertyChanged(string paramName)
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

template< class T >
void vgMovingEntry< T >::OnGroupPropertyChanged(string paramName)
{
	vgMovingEntry* pObjectEntry;
	T*  pObjInGroup;

	//vgDatabaseEntry::OnGroupPropertyChanged(paramName);

	for (int i = 0; i < s_group_list.size(); i++)
	{
		pObjectEntry = ((vgMovingEntry*)s_group_list[i]);
		pObjInGroup = (T*)(pObjectEntry->getRender());

		pObjectEntry->b_play = m_bGroupPlay;
		pObjInGroup->setPlayState(m_bGroupPlay);

		pObjectEntry->b_loop = m_bGroupLoop;
		pObjInGroup->setLoopState(m_bGroupLoop);	

		vgUI::UIController::getSingleton().GetWorkSpaceBar()->SetItemText(hTreeItem, pObjInGroup->getName());
		pObjInGroup->SetName( (TCHAR*)m_Renderer->getName().c_str() );

		vgKernel::SelectManager::getSingleton().updateBox();
	}

	//return;
}

template< class T >
void vgMovingEntry< T >::onChanged(int eventId, void *param)
{
	if (eventId == vgKernel::VG_OBS_PROPCHANGED && s_group_list.size() < 2)
	{
		Vector3 pos = m_pObject->GetPosition();

		m_Positionx = pos.x + vgKernel::CoordSystem::getSingleton().getProjectionCoord().x;
		m_Positiony = pos.y + vgKernel::CoordSystem::getSingleton().getProjectionCoord().y;
		m_Positionz = pos.z + vgKernel::CoordSystem::getSingleton().getProjectionCoord().z;


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

		return ;
	}

	if (eventId == vgKernel::VG_OBS_ADDSELECTION)
	{
		vgUI::UIController::getSingleton().AddSelection(this);

		return ;
	}
}

template< class T >
void vgMovingEntry< T >::AddSingleTabPage()
{
	vgUI::UIController::getSingleton().RemoveAllPages();

	vgPropertiesViewBar* pageViewBar = vgUI::UIController::getSingleton().GetPropertiesViewBar();

	s_ParamArray.clear();
	PropertiesParam param;


#if	VGK_LANG_CHS	
	{
		param.label = "坐标值设置";
		param.typeId = PROP_ITEM_GROUP;
		param.dataType = PROP_DATA_NONE;
		param.connectedPtr = NULL;
		param.comment = "设置物体坐标";
		s_ParamArray.push_back(param);

		param.label = "X 坐标";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_FLOAT;
		param.connectedPtr = &m_Positionx;
		param.comment = "设置X坐标";
		s_ParamArray.push_back(param);


		param.label = "Y 坐标";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_FLOAT;
		param.connectedPtr = &m_Positiony;
		param.comment = "设置Y坐标";
		s_ParamArray.push_back(param);

		param.label = "Z 坐标";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_FLOAT;
		param.connectedPtr = &m_PositionzMinus;
		param.comment = "设置Z坐标";
		s_ParamArray.push_back(param);

		param.label = "其他设置";
		param.typeId = PROP_ITEM_GROUP;
		param.dataType = PROP_DATA_NONE;
		param.connectedPtr = NULL;
		param.comment = string();
		s_ParamArray.push_back(param);

		param.label = "物体名称";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_STR;
		param.connectedPtr = m_Renderer->getNamePtr();
		param.comment = "物体的名称";
		s_ParamArray.push_back(param);

		param.label = "起始帧";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_INT;
		param.connectedPtr = &m_startframe;
		param.comment = "起始帧";
		s_ParamArray.push_back(param);

		param.label = "结束帧";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_INT;
		param.connectedPtr = &m_endframe;
		param.comment = "结束帧";
		s_ParamArray.push_back(param);

		param.label = "播放";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_BOOL;
		param.connectedPtr = &b_play;
		param.comment = "播放";
		s_ParamArray.push_back(param);

		param.label = "循环";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_BOOL;
		param.connectedPtr = &b_loop;
		param.comment = "循环";
		s_ParamArray.push_back(param);

		param.label = "起始时间";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_FLOAT;
		param.connectedPtr = &m_fStartTime;
		param.comment = "起始时间";
		s_ParamArray.push_back(param);
	}
#else//VGK_LANG_ENG
	{
		param.label = "3D Coordinate";
		param.typeId = PROP_ITEM_GROUP;
		param.dataType = PROP_DATA_NONE;
		param.connectedPtr = NULL;
		param.comment = "Set Position Of Object";
		s_ParamArray.push_back(param);

		param.label = "X Coordinate";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_FLOAT;
		param.connectedPtr = &m_Positionx;
		param.comment = "Set X Coordinate";
		s_ParamArray.push_back(param);


		param.label = "Y Coordinate";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_FLOAT;
		param.connectedPtr = &m_Positiony;
		param.comment = "Set Y Coordinate";
		s_ParamArray.push_back(param);

		param.label = "Z Coordinate";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_FLOAT;
		param.connectedPtr = &m_PositionzMinus;
		param.comment = "Set Z Coordinate";
		s_ParamArray.push_back(param);

		param.label = "More Settings";
		param.typeId = PROP_ITEM_GROUP;
		param.dataType = PROP_DATA_NONE;
		param.connectedPtr = NULL;
		param.comment = string();
		s_ParamArray.push_back(param);

		param.label = "Name";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_STR;
		param.connectedPtr = m_Renderer->getNamePtr();
		param.comment = "Name Of Object";
		s_ParamArray.push_back(param);

		param.label = "Start Frame";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_INT;
		param.connectedPtr = &m_startframe;
		param.comment = "Start Frame";
		s_ParamArray.push_back(param);

		param.label = "End Frame";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_INT;
		param.connectedPtr = &m_endframe;
		param.comment = "End Frame";
		s_ParamArray.push_back(param);

		param.label = "Play";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_BOOL;
		param.connectedPtr = &b_play;
		param.comment = "Play";
		s_ParamArray.push_back(param);

		param.label = "Loop";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_BOOL;
		param.connectedPtr = &b_loop;
		param.comment = "Loop";
		s_ParamArray.push_back(param);

		param.label = "Start Time";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_FLOAT;
		param.connectedPtr = &m_fStartTime;
		param.comment = "Start Time in Millisecond";
		s_ParamArray.push_back(param);
	}
#endif

	vgPropertyPage* propPage = vgUI::UIController::getSingleton().GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

	//propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
	propPage->ConnectNode(this, &s_ParamArray);

	pageViewBar->AddTab("自动属性", propPage);

}

template< class T >
void vgMovingEntry< T >::AddGroupTabPage()
{
	vgUI::UIController::getSingleton().RemoveAllPages();

	getGroupData();

	vgPropertiesViewBar* pageViewBar = vgUI::UIController::getSingleton().GetPropertiesViewBar();

	s_ParamArray.clear();
	PropertiesParam param;

#if VGK_LANG_CHS
	{
		param.label = "组属性";
		param.typeId = PROP_ITEM_GROUP;
		param.dataType = PROP_DATA_NONE;
		param.connectedPtr = NULL;
		param.comment = string();
		s_ParamArray.push_back(param);

		param.label = "播放";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_BOOL;
		param.connectedPtr = &m_bGroupPlay;
		param.comment = "播放";
		s_ParamArray.push_back(param);

		param.label = "循环";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_BOOL;
		param.connectedPtr = &m_bGroupLoop;
		param.comment = "循环";
		s_ParamArray.push_back(param);
	}
#else
	{
		param.label = "Group Propertys";
		param.typeId = PROP_ITEM_GROUP;
		param.dataType = PROP_DATA_NONE;
		param.connectedPtr = NULL;
		param.comment = string();
		s_ParamArray.push_back(param);

		param.label = "Play";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_BOOL;
		param.connectedPtr = &b_play;
		param.comment = "Play";
		s_ParamArray.push_back(param);

		param.label = "Loop";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_BOOL;
		param.connectedPtr = &b_loop;
		param.comment = "Loop";
		s_ParamArray.push_back(param);
	}
#endif

	vgPropertyPage* propPage = vgUI::UIController::getSingleton().GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

	//propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
	propPage->ConnectNode(this, &s_ParamArray);

	pageViewBar->AddTab("自动属性", propPage);

}

template< class T >
void vgMovingEntry< T >::getGroupData()
{
	vgMovingEntry* pObjectEntry;	

	//暂时取组中第一个对象的属性作为组的显示属性
	pObjectEntry = ((vgMovingEntry*)s_group_list[0]);	

	m_bGroupPlay = pObjectEntry->b_play;
	m_bGroupLoop = pObjectEntry->b_loop;
}

template< class T >
void vgMovingEntry< T >::AddNodeTabs()
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

template< class T >
CMenu* vgMovingEntry< T >::GetContextMenu()
{
	CMenu *menu = new CMenu;

	VERIFY(menu->CreatePopupMenu());
	VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_GOTO, _T("转到")));
	VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_DELETE,_T("删除")));

	return menu;
}
#endif
