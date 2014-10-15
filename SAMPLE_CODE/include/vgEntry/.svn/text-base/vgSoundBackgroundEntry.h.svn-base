/*#pragma once*/
#ifndef __VGSOUNDBACKGROUNDENTRY_H__
#define __VGSOUNDBACKGROUNDENTRY_H__

#include <vgSound/vgSoundDefinition.h>
#include <vgEntry/vgBaseEntry.h>
#include <vgUIController/vgPropertyPage.h>

#include <vgKernel/vgkRendererObserver.h>

#include <vgSound/vgSoundBackground.h>

class  VGSOUND_EXPORT vgSoundBackgroundEntry :	public vgBaseEntry
{
public:
	const static int s_NumOfParam = 3;
	static PropertiesParam s_ParamArray[s_NumOfParam];

public:
	vgSoundBackgroundEntry(vgSound::SoundBackground* renderer);
	virtual ~vgSoundBackgroundEntry(void);

	void AddNodeTabs();

	virtual String GetName()
	{
#if VGK_LANG_CHS
		return "背景音效";
#else
		return "Background Music";
#endif
	}

	int GetSelectedImage() { return 1; }

	int GetUnSelectedImage() { return 2; }

	void OnPropertyChanged(string paramName);// { TRACE("Camera Property Changed \n");}

	void onChanged(int eventId, void *param);

	void UpDataProp() {}


private:

	// 被修改数据的副本
    bool b_play;

	String m_sCaption;
};

#endif
