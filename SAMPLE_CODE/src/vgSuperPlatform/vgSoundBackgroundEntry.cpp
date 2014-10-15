#include <vgStableHeaders.h>
#include "vgSoundBackgroundEntry.h"
#include "vgPropertyPage.h"

#include <vgKernel/vgkVec3.h>
#include <vgMesh/vgmMeshManager.h>
#include <vgMath/vgfVector3.h>

#include <vgSound/vgSoundManager.h>


PropertiesParam vgSoundBackgroundEntry::s_ParamArray[s_NumOfParam];

vgSoundBackgroundEntry::vgSoundBackgroundEntry(vgCore::SoundBackground* renderer) 
	:vgBaseEntry( VG_ENTRY_BACKSOUND , renderer)
{

	b_play = vgCore::SoundManager::getSingleton().getCurrentBackgroundMusic().getPlayFlag();

#if VGK_LANG_CHS
	m_sCaption = "背景音效";
#else
	m_sCaption = "Background Music";
#endif
	
	vgCore::SoundManager::getSingleton().getCurrentBackgroundMusic().registerObserver( this );

}
vgSoundBackgroundEntry::~vgSoundBackgroundEntry(void)
{

}

void vgSoundBackgroundEntry::OnPropertyChanged(string paramName)
{
/*	sound->GenBoundaryBox(sound->GetSoundPos());*/

	if (b_play)
	{
		vgCore::SoundManager::getSingleton().getCurrentBackgroundMusic().startPlaying();
	}
	else
		vgCore::SoundManager::getSingleton().getCurrentBackgroundMusic().stopPlaying();

	vgCore::SoundManager::getSingleton().getCurrentBackgroundMusic().setPlayFlag( b_play );
	// 更新TREEITEM
	//vgUIController::GetInstance()->GetWorkSpaceBar()->SetItemText(hTreeItem, m_Renderer->getName()/*m_sCaption*/);
}

void vgSoundBackgroundEntry::onChanged(int eventId, void *param)
{
	if (eventId == vgKernel::VG_OBS_PROPCHANGED)
	{
		b_play = vgCore::SoundManager::getSingleton().getCurrentBackgroundMusic().getPlayFlag();
		if (this == vgUIController::GetInstance()->GetCurrentSelectedNode())
		{
			s_ParamArray[1].pProp->SetValue(m_Renderer->getName().c_str());
			s_ParamArray[2].pProp->SetValue(b_play);
		}
	}
}

void vgSoundBackgroundEntry::AddNodeTabs()
{
	vgUIController::GetInstance()->RemoveAllPages();

	vgPropertiesViewBar* pageViewBar = vgUIController::GetInstance()->GetPropertiesViewBar();

#if VGK_LANG_CHS
	s_ParamArray[0].label = "其他设置";
	s_ParamArray[0].typeId = PROP_ITEM_GROUP;
	s_ParamArray[0].dataType = PROP_DATA_NONE;
	s_ParamArray[0].connectedPtr = NULL;
	s_ParamArray[0].comment = string();


	s_ParamArray[1].label = "音乐文件";
	s_ParamArray[1].typeId = PROP_ITEM_DATA;
	s_ParamArray[1].dataType = PROP_DATA_STR;
	s_ParamArray[1].connectedPtr = m_Renderer->getNamePtr()/*&m_sCaption*/;
	s_ParamArray[1].comment = "物体的名称";

	s_ParamArray[2].label = "是否播放";
	s_ParamArray[2].typeId = PROP_ITEM_DATA;
	s_ParamArray[2].dataType = PROP_DATA_BOOL;
	s_ParamArray[2].connectedPtr = &b_play;
	s_ParamArray[2].comment = "是否播放";
#else
	s_ParamArray[0].label = "Others";
	s_ParamArray[0].typeId = PROP_ITEM_GROUP;
	s_ParamArray[0].dataType = PROP_DATA_NONE;
	s_ParamArray[0].connectedPtr = NULL;
	s_ParamArray[0].comment = string();


	s_ParamArray[1].label = "Music file";
	s_ParamArray[1].typeId = PROP_ITEM_DATA;
	s_ParamArray[1].dataType = PROP_DATA_STR;
	s_ParamArray[1].connectedPtr = m_Renderer->getNamePtr()/*&m_sCaption*/;
	s_ParamArray[1].comment = "";

	s_ParamArray[2].label = "Play";
	s_ParamArray[2].typeId = PROP_ITEM_DATA;
	s_ParamArray[2].dataType = PROP_DATA_BOOL;
	s_ParamArray[2].connectedPtr = &b_play;
	s_ParamArray[2].comment = "";
#endif

	vgPropertyPage* propPage = vgUIController::GetInstance()->GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

	propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
#if VGK_LANG_CHS
	pageViewBar->AddTab("自动属性", propPage);
#else
	pageViewBar->AddTab("Auto Prop", propPage);
#endif
}

