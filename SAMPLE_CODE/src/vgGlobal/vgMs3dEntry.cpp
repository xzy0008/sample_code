


#include <vgStableHeaders.h>
#include "vgMs3dEntry.h"
#include <vgKernel/vgkSelectManager.h>

#include <vgKernel/vgkRendererManager.h>

vgMs3dEntry::vgMs3dEntry(vgMs3d::CMs3d* pObject)
: vgBaseEntry(  pObject )
{
	assert( pObject != NULL );

	getData();

	vgKernel::CoordSystem::getSingleton().registerObserver(this);
}


//PropertiesParam vgMs3dEntry::s_ParamArray[s_NumOfParam];
vector<PropertiesParam> vgMs3dEntry::s_ParamArray;

void vgMs3dEntry::OnPropertyChanged(string paramName)
{
	m_posZ = - m_posZMinus;
	vgMs3d::CMs3d* m_pObject = ( vgMs3d::CMs3d*) m_Renderer;

	vgKernel::Vec3 temp=m_pObject->getPosition();
	Vector3 tmp=Vector3(temp.x,temp.y,temp.z);
	Vector3 offset = Vector3( m_posX, m_posY, m_posZ)
		- tmp  - vgKernel::CoordSystem::getSingleton().getProjectionCoord();
	
	if(fabs(m_posX)>0.00001||fabs(m_posY)>0.00001||fabs(m_posZ)>0.00001)
	{
		m_pObject->translate( offset );
	}


	m_pObject->SetPlayState( b_play );
	m_pObject->SetStartFrame(m_startframe);	
	m_pObject->SetEndFrame(m_endframe);
	m_pObject->SetLoopState(b_loop);		

	m_pObject->setSpeed(m_speed);

	vgUI::UIController::getSingleton().GetWorkSpaceBar()->SetItemText(hTreeItem, m_pObject->getName());

	vgKernel::SelectManager::getSingleton().updateBox();

}

void vgMs3dEntry::onChanged(int eventId, void *param)
{
	if (eventId == vgKernel::VG_OBS_PROPCHANGED)
	{
		getData();

		//TRACE("New Camera Position %.2f %.2f %.2f \n", posPtr->x, posPtr->y, posPtr->z);
		if (this == vgUI::UIController::getSingleton().GetCurrentSelectedNode())
		{
			s_ParamArray[1].pProp->SetValue(m_posX);
			s_ParamArray[2].pProp->SetValue(m_posY);
			//m_PositionzMinus = - m_posZ;
			s_ParamArray[3].pProp->SetValue(m_posZMinus);
			s_ParamArray[6].pProp->SetValue(m_startframe);
			s_ParamArray[7].pProp->SetValue(m_endframe);

			s_ParamArray[10].pProp->SetValue(m_speed);
			s_ParamArray[11].pProp->SetValue(*m_pbUnderWater);
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
void vgMs3dEntry::AddNodeTabs()
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
		param.connectedPtr = &m_posX;
		param.comment = "设置X坐标";
		s_ParamArray.push_back(param);


		param.label = "Y 坐标";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_FLOAT;
		param.connectedPtr = &m_posY;
		param.comment = "设置Y坐标";
		s_ParamArray.push_back(param);

		param.label = "Z 坐标";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_FLOAT;
		param.connectedPtr = &m_posZMinus;
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
		param.dataType = PROP_DATA_FLOAT;
		param.connectedPtr = &m_startframe;
		param.comment = "起始帧";
		s_ParamArray.push_back(param);

		param.label = "结束帧";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_FLOAT;
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


		param.label = "速度";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_FLOAT;
		param.connectedPtr = &m_speed;
		param.comment = "速度";
		s_ParamArray.push_back(param);

		//ocean set -- livenson 20091229
		param.label = "海底渲染";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_BOOL;
		param.connectedPtr = m_pbUnderWater;
		param.comment = "速度";
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
		param.connectedPtr = &m_posX;
		param.comment = "Set X Coordinate";
		s_ParamArray.push_back(param);


		param.label = "Y Coordinate";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_FLOAT;
		param.connectedPtr = &m_posY;
		param.comment = "Set Y Coordinate";
		s_ParamArray.push_back(param);

		param.label = "Z Coordinate";
		param.typeId = PROP_ITEM_DATA;
		param.dataType = PROP_DATA_FLOAT;
		param.connectedPtr = &m_posZ;
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

	}
#endif


	vgPropertyPage* propPage = vgUI::UIController::getSingleton().GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

	//propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
	propPage->ConnectNode(this, &s_ParamArray);

	pageViewBar->AddTab("自动属性", propPage);
}


CMenu* vgMs3dEntry::GetContextMenu()
{
	CMenu *menu = new CMenu;

	VERIFY(menu->CreatePopupMenu());
	VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_GOTO, _T("转到")));
	VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_DELETE,_T("删除")));

	return menu;
}


void vgMs3dEntry::getData()
{
	vgMs3d::CMs3d *pObject = ( vgMs3d::CMs3d*) m_Renderer;

	Vector3 pos = pObject->getPosition();

	m_posX = pos.x + vgKernel::CoordSystem::getSingleton().getProjectionCoord().x;
	m_posY = pos.y + vgKernel::CoordSystem::getSingleton().getProjectionCoord().y;
	m_posZ = pos.z + vgKernel::CoordSystem::getSingleton().getProjectionCoord().z;
	m_posZMinus = - m_posZ;


	b_play = pObject->GetPlayState();
	m_startframe = pObject->GetStartFrame();
	m_endframe = pObject->GetEndFrame()	;
	b_loop = pObject->GetLoopState();

	m_speed = pObject->getSpeed();
	m_pbUnderWater=&pObject->bUnderWater;
}
