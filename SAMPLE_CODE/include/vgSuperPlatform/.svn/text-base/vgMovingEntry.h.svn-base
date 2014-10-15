/*#pragma once*/
#ifndef __VGMOVINGENTRY_H__
#define __VGMOVINGENTRY_H__

#include "vgBaseEntry.h"

#include "vgUIController.h"
#include <vgKernel/vgkRendererObserver.h>


#include <vgKernel/vgkSelectManager.h>

#include <vgKernel/vgkRendererManager.h>


template< class T >
class vgMovingEntry : public vgBaseEntry
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

	virtual String GetName()
	{
		return m_sCaption;
	}

	int GetSelectedImage() { return 1; }

	int GetUnSelectedImage() { return 2; }

	void OnPropertyChanged(string paramName);// { TRACE("Camera Property Changed \n");}

	void onChanged(int eventId, void *param);

	void UpDataProp() {}


	CMenu* GetContextMenu();

private:
	T* m_pObject;

	// 被修改数据的副本
	float m_Positionx;
	float m_Positiony;
	float m_Positionz, m_PositionzMinus;;

	int m_startframe;

	int m_endframe;

	bool b_play;

	bool b_loop;

	// 测试
	float	m_fStartTime;
	//bool	b_reset;

	string m_sCaption;
};

template< class T >
vgMovingEntry< T >::vgMovingEntry(T* pObject)
: vgBaseEntry( VG_ENTRY_MOVING , pObject )
{
	assert( pObject != NULL );
	if (pObject)
	{
		m_Positionx = pObject->m_Position.x + vgCore::vgCoordinate::getSingleton().GetSceneCood().x;
		m_Positiony = pObject->m_Position.y + vgCore::vgCoordinate::getSingleton().GetSceneCood().y;
		m_Positionz = pObject->m_Position.z + vgCore::vgCoordinate::getSingleton().GetSceneCood().z;
		m_PositionzMinus = - m_Positionz;
		b_play = pObject->getPlayingState();
		m_startframe = pObject->getStartFrame();
		m_endframe = pObject->getEndFrame()	;
		b_loop = pObject->getLoopState();

		//b_reset = false;
		m_fStartTime = pObject->getTimeWithFrame(0);
		m_pObject = pObject;

		m_sCaption = string( pObject->getName() );

		vgCore::vgCoordinate::getSingleton().registerObserver(this);

	}

}


template< class T>
//PropertiesParam vgMovingEntry<T>::s_ParamArray[s_NumOfParam];
vector<PropertiesParam> vgMovingEntry<T>::s_ParamArray;



template< class T >
void vgMovingEntry< T >::OnPropertyChanged(string paramName)
{
	m_Positionz = - m_PositionzMinus;
	Vector3 offset = Vector3( m_Positionx, m_Positiony, m_Positionz)
		- m_pObject->GetPosition()  - vgCore::vgCoordinate::getSingleton().GetSceneCood();
	m_pObject->translate( offset );

	m_pObject->setPlayState( b_play );
	m_pObject->setStartFrame(m_startframe);	
	m_pObject->setEndFrame(m_endframe);
	m_pObject->setLoopState(b_loop);	

	vgUIController::GetInstance()->GetWorkSpaceBar()->SetItemText(hTreeItem, m_pObject->getName());
	m_pObject->SetName( (TCHAR*)m_Renderer->getName().c_str() );

	vgKernel::SelectManager::getSingleton().updateBox();




	//m_pObject->SetPosition( Vector3(m_Positionx, m_Positiony, m_Positionz) );
}
template< class T >
void vgMovingEntry< T >::onChanged(int eventId, void *param)
{
	if (eventId == vgKernel::VG_OBS_PROPCHANGED)
	{
		Vector3 pos = m_pObject->GetPosition();

		m_Positionx = pos.x + vgCore::vgCoordinate::getSingleton().GetSceneCood().x;
		m_Positiony = pos.y + vgCore::vgCoordinate::getSingleton().GetSceneCood().y;
		m_Positionz = pos.z + vgCore::vgCoordinate::getSingleton().GetSceneCood().z;


		//TRACE("New Camera Position %.2f %.2f %.2f \n", posPtr->x, posPtr->y, posPtr->z);
		if (this == vgUIController::GetInstance()->GetCurrentSelectedNode())
		{
			s_ParamArray[1].pProp->SetValue(m_Positionx);
			s_ParamArray[2].pProp->SetValue(m_Positiony);
			m_PositionzMinus = - m_Positionz;
			s_ParamArray[3].pProp->SetValue(m_PositionzMinus);
		}

	}
	if (eventId == vgKernel::VG_OBS_SELECTCHAGNED)
	{
		vgUIController::GetInstance()->SelectNode(this);

		return ;
	}

	if (eventId == vgKernel::VG_OBS_ADDSELECTION)
	{
		vgUIController::GetInstance()->AddSelection(this);

		return ;
	}
}
template< class T >
void vgMovingEntry< T >::AddNodeTabs()
{
	vgUIController::GetInstance()->RemoveAllPages();

	vgPropertiesViewBar* pageViewBar = vgUIController::GetInstance()->GetPropertiesViewBar();

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

	vgPropertyPage* propPage = vgUIController::GetInstance()->GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

	//propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
	propPage->ConnectNode(this, &s_ParamArray);

	pageViewBar->AddTab("自动属性", propPage);
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
