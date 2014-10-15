#include <vgStableHeaders.h>
#include "vgSound3DEntry.h"
#include "vgPropertyPage.h"

#include <vgKernel/vgkVec3.h>
#include <vgMesh/vgmMeshManager.h>
#include <vgMath/vgfVector3.h>
#include <vgKernel/vgkSelectManager.h>


PropertiesParam vgSound3DEntry::s_ParamArray[s_NumOfParam];

vgSound3DEntry::vgSound3DEntry(vgCore::Sound3D* renderer) 
	:vgBaseEntry( VG_ENTRY_3DSOUND , renderer )
{

	
	vgCore::Sound3D *sound = (vgCore::Sound3D *)renderer;

	if (sound)
	{
		m_sCaption = sound->getName();

		b_play = sound->getPlayFlag();

		x = sound->getSoundPos().x + vgCore::vgCoordinate::getSingleton().GetSceneCood().x;
		y = sound->getSoundPos().y + vgCore::vgCoordinate::getSingleton().GetSceneCood().y;
		z = sound->getSoundPos().z + vgCore::vgCoordinate::getSingleton().GetSceneCood().z;
		zMinus = -z;
		sound->registerObserver( this );

		vgCore::vgCoordinate::getSingleton().registerObserver(this);

	}

}
vgSound3DEntry::~vgSound3DEntry(void)
{

}

void vgSound3DEntry::OnPropertyChanged(string paramName)
{
	z = - zMinus;
	vgCore::Sound3D *sound = (vgCore::Sound3D *)m_Renderer;

	Vector3 aa = vgCore::vgCoordinate::getSingleton().GetSceneCood();

	sound->setAbsolutePos( x - aa.x, y - aa.y ,z - aa.z);

/*	sound->GenBoundaryBox(sound->getSoundPos());*/

	sound->setPlayFlag( b_play );

	if (b_play)
	{
		sound->startPlaying( true );
	}
	else
		sound->stopPlaying();

	// 更新TREEITEM
	vgUIController::GetInstance()->GetWorkSpaceBar()->SetItemText(hTreeItem, m_Renderer->getName());

	vgKernel::SelectManager::getSingleton().updateBox();

}

void vgSound3DEntry::onChanged(int eventId, void *param)
{
	if (eventId == vgKernel::VG_OBS_PROPCHANGED)
	{
		vgCore::Sound3D *sound = (vgCore::Sound3D *)m_Renderer;


		vgCore::Vector3 xx = sound->getSoundPos();

		x = xx.x + vgCore::vgCoordinate::getSingleton().GetSceneCood().x;
		y = xx.y + vgCore::vgCoordinate::getSingleton().GetSceneCood().y;
		z = xx.z + vgCore::vgCoordinate::getSingleton().GetSceneCood().z;


		//TRACE("New Camera Position %.2f %.2f %.2f \n", posPtr->x, posPtr->y, posPtr->z);
		if (this == vgUIController::GetInstance()->GetCurrentSelectedNode())
		{
			s_ParamArray[1].pProp->SetValue(x);
			s_ParamArray[2].pProp->SetValue(y);
			zMinus = -z;
			s_ParamArray[3].pProp->SetValue(zMinus);
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

void vgSound3DEntry::AddNodeTabs()
{
	vgUIController::GetInstance()->RemoveAllPages();

	vgPropertiesViewBar* pageViewBar = vgUIController::GetInstance()->GetPropertiesViewBar();

	s_ParamArray[0].label = "坐标值设置";
	s_ParamArray[0].typeId = PROP_ITEM_GROUP;
	s_ParamArray[0].dataType = PROP_DATA_NONE;
	s_ParamArray[0].connectedPtr = NULL;
	s_ParamArray[0].comment = "设置相机的坐标";

	s_ParamArray[1].label = "X 坐标";
	s_ParamArray[1].typeId = PROP_ITEM_DATA;
	s_ParamArray[1].dataType = PROP_DATA_FLOAT;
	s_ParamArray[1].connectedPtr = &x;
	s_ParamArray[1].comment = "设置X坐标";


	s_ParamArray[2].label = "Y 坐标";
	s_ParamArray[2].typeId = PROP_ITEM_DATA;
	s_ParamArray[2].dataType = PROP_DATA_FLOAT;
	s_ParamArray[2].connectedPtr = &y;
	s_ParamArray[2].comment = "设置Y坐标";

	s_ParamArray[3].label = "Z 坐标";
	s_ParamArray[3].typeId = PROP_ITEM_DATA;
	s_ParamArray[3].dataType = PROP_DATA_FLOAT;
	s_ParamArray[3].connectedPtr = &zMinus;
	s_ParamArray[3].comment = "设置Z坐标";

	s_ParamArray[4].label = "其他设置";
	s_ParamArray[4].typeId = PROP_ITEM_GROUP;
	s_ParamArray[4].dataType = PROP_DATA_NONE;
	s_ParamArray[4].connectedPtr = NULL;
	s_ParamArray[4].comment = string();


	s_ParamArray[5].label = "音效名称";
	s_ParamArray[5].typeId = PROP_ITEM_DATA;
	s_ParamArray[5].dataType = PROP_DATA_STR;
	s_ParamArray[5].connectedPtr = m_Renderer->getNamePtr();
	s_ParamArray[5].comment = "物体的名称";

	s_ParamArray[6].label = "是否播放";
	s_ParamArray[6].typeId = PROP_ITEM_DATA;
	s_ParamArray[6].dataType = PROP_DATA_BOOL;
	s_ParamArray[6].connectedPtr = &b_play;
	s_ParamArray[6].comment = "是否播放";

	vgPropertyPage* propPage = vgUIController::GetInstance()->GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

	propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
	pageViewBar->AddTab("自动属性", propPage);
}


CMenu* vgSound3DEntry::GetContextMenu()
{
	CMenu *menu = new CMenu;

	VERIFY(menu->CreatePopupMenu());
//	VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_GOTO, _T("转到")));
	VERIFY(menu->AppendMenu(MF_STRING, NID_MESH_DELETE,_T("删除")));

	return menu;
}

