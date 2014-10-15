#include <vgStableHeaders.h>
#include "vgentry/vgSoundBackgroundEntry.h"
#include <vgUIController/vgPropertyPage.h>
#include <vgUIController/vgUIController.h>

#include <vgKernel/vgkVec3.h>
#include <vgMesh/vgmMeshManager.h>
//#include <vgMath/vgfVector3.h>

#include <vgSound/vgSoundManager.h>


PropertiesParam vgSoundBackgroundEntry::s_ParamArray[s_NumOfParam];

vgSoundBackgroundEntry::vgSoundBackgroundEntry(vgSound::SoundBackground* renderer) 
	:vgBaseEntry( renderer)
{

	if ( vgSound::SoundManager::getSingleton().getCurrentBackgroundMusic() != NULL )
	{
		b_play = vgSound::SoundManager::getSingleton().getCurrentBackgroundMusic()->getPlayFlag();
	}


#if VGK_LANG_CHS
	m_sCaption = "背景音效";
#else
	m_sCaption = "Background Music";
#endif
	
	if ( vgSound::SoundManager::getSingleton().getCurrentBackgroundMusic() != NULL )
	{
		vgSound::SoundManager::getSingleton().getCurrentBackgroundMusic()->registerObserver( this );
	}


}
vgSoundBackgroundEntry::~vgSoundBackgroundEntry(void)
{
	if ( vgSound::SoundManager::getSingleton().getCurrentBackgroundMusic() != NULL )
	{
		vgSound::SoundManager::getSingleton().getCurrentBackgroundMusic()->unregisterObserver( this );
	}
}

void vgSoundBackgroundEntry::OnPropertyChanged(string paramName)
{
/*	sound->GenBoundaryBox(sound->GetSoundPos());*/
	if ( vgSound::SoundManager::getSingleton().getCurrentBackgroundMusic() == NULL )
	{
		return;
	}

	if (b_play)
	{
		vgSound::SoundManager::getSingleton().getCurrentBackgroundMusic()->startPlaying();
	}
	else
		vgSound::SoundManager::getSingleton().getCurrentBackgroundMusic()->stopPlaying();

	vgSound::SoundManager::getSingleton().getCurrentBackgroundMusic()->setPlayFlag( b_play );
	// 更新TREEITEM
	//vgUI::UIController::getSingleton().GetWorkSpaceBar()->SetItemText(hTreeItem, m_Renderer->getName()/*m_sCaption*/);
}

void vgSoundBackgroundEntry::onChanged(int eventId, void *param)
{
	if (eventId == vgKernel::VG_OBS_PROPCHANGED)
	{
		if ( vgSound::SoundManager::getSingleton().getCurrentBackgroundMusic() != NULL )
		{
			b_play = vgSound::SoundManager::getSingleton().getCurrentBackgroundMusic()->getPlayFlag();
		}
		if (this == vgUI::UIController::getSingleton().GetCurrentSelectedNode())
		{
			s_ParamArray[1].pProp->SetValue(m_Renderer->getName().c_str());
			s_ParamArray[2].pProp->SetValue(b_play);
		}
	}
}

void vgSoundBackgroundEntry::AddNodeTabs()
{
	vgUI::UIController::getSingleton().RemoveAllPages();

	vgPropertiesViewBar* pageViewBar = vgUI::UIController::getSingleton().GetPropertiesViewBar();

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

	vgPropertyPage* propPage = vgUI::UIController::getSingleton().GetPropPage();
	propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

	propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);
#if VGK_LANG_CHS
	pageViewBar->AddTab("自动属性", propPage);
#else
	pageViewBar->AddTab("Auto Prop", propPage);
#endif
}

