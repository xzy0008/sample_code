#include <vgStableHeaders.h>
#include "vgCameraRecordEntry.h"
#include <vgCam/vgcaViewCam.h>
#include <vgKernel/vgkSelectManager.h>


#include "vgUIController.h"
#include <vgCam/vgcaCameraRecord.h>

PropertiesParam vgCameraRecordEntry::s_ParamArray[s_NumOfParam];



void vgCameraRecordEntry::AddNodeTabs()
{

	using namespace vgCam;

	CameraRecord* rec = ( CameraRecord* )getRender();
	vgKernel::Vec3 vec = rec->offset_vcr;
	m_offX = vec.x;
	m_offY = vec.y;
	m_offZ = vec.z;


	vgUIController::GetInstance()->RemoveAllPages();

	vgPropertiesViewBar* pageViewBar = vgUIController::GetInstance()->GetPropertiesViewBar();


#if VGK_LANG_CHS


	s_ParamArray[0].label = "名称设置";
	s_ParamArray[0].typeId = PROP_ITEM_GROUP;
	s_ParamArray[0].dataType = PROP_DATA_NONE;
	s_ParamArray[0].connectedPtr = NULL;
	s_ParamArray[0].comment = "设置VCR名称";

	vgCam::CameraRecord *pViewCam = ( vgCam::CameraRecord*) m_Renderer;
	s_ParamArray[1].label = "物体名称";
	s_ParamArray[1].typeId = PROP_ITEM_DATA;
	s_ParamArray[1].dataType = PROP_DATA_STR;
	s_ParamArray[1].connectedPtr = m_Renderer->getNamePtr();
	s_ParamArray[1].comment = "物体的名称";



	// 坐标值
	s_ParamArray[2].label = "位置偏移";
	s_ParamArray[2].typeId = PROP_ITEM_GROUP;
	s_ParamArray[2].dataType = PROP_DATA_NONE;
	s_ParamArray[2].connectedPtr = NULL;
	s_ParamArray[2].comment = "设置VCR的偏移";

	s_ParamArray[3].label = "X 偏移";
	s_ParamArray[3].typeId = PROP_ITEM_DATA;
	s_ParamArray[3].dataType = PROP_DATA_FLOAT;
	s_ParamArray[3].connectedPtr = &m_offX;
	s_ParamArray[3].comment = "设置X偏移";

	s_ParamArray[4].label = "Y 偏移";
	s_ParamArray[4].typeId = PROP_ITEM_DATA;
	s_ParamArray[4].dataType = PROP_DATA_FLOAT;
	s_ParamArray[4].connectedPtr = &m_offY;
	s_ParamArray[4].comment = "设置Y偏移";

	s_ParamArray[5].label = "Z 偏移";
	s_ParamArray[5].typeId = PROP_ITEM_DATA;
	s_ParamArray[5].dataType = PROP_DATA_FLOAT;
	s_ParamArray[5].connectedPtr = &m_offZ;
	s_ParamArray[5].comment = "设置Z偏移";

	vgPropertyPage* propPage = vgUIController::GetInstance()->GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

	propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
	pageViewBar->AddTab("自动属性", propPage);


#else

	s_ParamArray[0].label = "Config";
	s_ParamArray[0].typeId = PROP_ITEM_GROUP;
	s_ParamArray[0].dataType = PROP_DATA_NONE;
	s_ParamArray[0].connectedPtr = NULL;
	s_ParamArray[0].comment = "";

	vgCam::CameraRecord *pViewCam = ( vgCam::CameraRecord*) m_Renderer;
	s_ParamArray[1].label = "name";
	s_ParamArray[1].typeId = PROP_ITEM_DATA;
	s_ParamArray[1].dataType = PROP_DATA_STR;
	s_ParamArray[1].connectedPtr = m_Renderer->getNamePtr();
	s_ParamArray[1].comment = "";



	// 坐标值
	s_ParamArray[2].label = "Offset";
	s_ParamArray[2].typeId = PROP_ITEM_GROUP;
	s_ParamArray[2].dataType = PROP_DATA_NONE;
	s_ParamArray[2].connectedPtr = NULL;
	s_ParamArray[2].comment = "";

	s_ParamArray[3].label = "X";
	s_ParamArray[3].typeId = PROP_ITEM_DATA;
	s_ParamArray[3].dataType = PROP_DATA_FLOAT;
	s_ParamArray[3].connectedPtr = &m_offX;
	s_ParamArray[3].comment = "";

	s_ParamArray[4].label = "Y";
	s_ParamArray[4].typeId = PROP_ITEM_DATA;
	s_ParamArray[4].dataType = PROP_DATA_FLOAT;
	s_ParamArray[4].connectedPtr = &m_offY;
	s_ParamArray[4].comment = "";

	s_ParamArray[5].label = "Z";
	s_ParamArray[5].typeId = PROP_ITEM_DATA;
	s_ParamArray[5].dataType = PROP_DATA_FLOAT;
	s_ParamArray[5].connectedPtr = &m_offZ;
	s_ParamArray[5].comment = "";

	vgPropertyPage* propPage = vgUIController::GetInstance()->GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

	propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
	pageViewBar->AddTab("Auto Prop", propPage);


#endif
	//	vgKernel::SelectManager::getSingleton().SetSelection(m_meshId);

}

void vgCameraRecordEntry::OnPropertyChanged(string paramName)
{
	// 更新TREEITEM

	//vgCam::CamManager::getSingleton().getCamRecordPtr()->offset_vcr=vgKernel::Vec3(m_offX,m_offY,m_offZ);
	// 	vgCam::CamManager::getSingleton().getCamRecordPtr()->translate(m_offX,m_offY,m_offZ);
	// 
	// 	vgUIController::GetInstance()->GetWorkSpaceBar()->SetItemText(hTreeItem, 
	// 		GetName() );
	vgUIController::GetInstance()->GetWorkSpaceBar()->SetItemText(hTreeItem, GetName() );

	vgCam::CameraRecord *pViewCam = ( vgCam::CameraRecord*) m_Renderer;
	pViewCam->translate(m_offX,m_offY,m_offZ);
}

void vgCameraRecordEntry::onChanged(int eventId, void* param)
{
	if (eventId == vgKernel::VG_OBS_PROPCHANGED)
	{
		using namespace vgCam;
		CameraRecord* rec = ( CameraRecord* )getRender();
		vgKernel::Vec3 vec = rec->offset_vcr;
		m_offX = vec.x;
		m_offY = vec.y;
		m_offZ = vec.z;

		////TRACE("New Camera Position %.2f %.2f %.2f \n", posPtr->x, posPtr->y, posPtr->z);
		if (this == vgUIController::GetInstance()->GetCurrentSelectedNode())
		{
			s_ParamArray[3].pProp->SetValue(m_offX);
			s_ParamArray[4].pProp->SetValue(m_offY);
			s_ParamArray[5].pProp->SetValue(m_offZ);

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



CMenu* vgCameraRecordEntry::GetContextMenu()
{
	CMenu *menu = new CMenu;

	VERIFY(menu->CreatePopupMenu());
	//  [11/4/2008 zhu]


#if VGK_LANG_CHS
	VERIFY(menu->AppendMenu(MF_STRING, NID_VCR_PLAY, _T("播放")));

	//VERIFY(menu->AppendMenu(MF_STRING, NID_VCR_STOP, _T("停止")));

	VERIFY(menu->AppendMenu(MF_STRING, NID_VCR_GOON, _T("暂停/继续")));
#else
	VERIFY(menu->AppendMenu(MF_STRING, NID_VCR_PLAY, _T("Play")));

	//VERIFY(menu->AppendMenu(MF_STRING, NID_VCR_STOP, _T("停止")));

	VERIFY(menu->AppendMenu(MF_STRING, NID_VCR_GOON, _T("Pause/continue")));

#endif

	//VERIFY(menu->AppendMenu(MF_STRING, NID_VCR_SHOW, _T("显示/隐藏")));

	//VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_DELETE,_T("删除")));

	return menu;
}

vgCameraRecordEntry::vgCameraRecordEntry( vgCam::CameraRecord* vcrpar ) : vgBaseEntry( VG_ENTRY_VCR , vcrpar )
{
	assert( vcrpar != NULL );
	vgKernel::Vec3 vec = vcrpar->offset_vcr;
	m_offX = vec.x;
	m_offY = vec.y;
	m_offZ = vec.z;
}
