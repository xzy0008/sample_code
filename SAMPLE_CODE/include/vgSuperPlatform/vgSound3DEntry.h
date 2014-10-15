/*#pragma once*/
#ifndef __VGSOUND3DENTRY_H__
#define __VGSOUND3DENTRY_H__

#include "vgBaseEntry.h"

#include "vgUIController.h"
#include <vgKernel/vgkRendererObserver.h>

#include <vgSound/vgSound3D.h>

class vgSound3DEntry :	public vgBaseEntry
{
public:
	const static int s_NumOfParam = 7;
	static PropertiesParam s_ParamArray[s_NumOfParam];

public:
	vgSound3DEntry(vgCore::Sound3D* renderer);
	virtual ~vgSound3DEntry(void);

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

//	vgCore::Sound3D *sound;

	// 被修改数据的副本
	float x;
	float y;
	float z, zMinus;
    bool b_play;

	String m_sCaption;
};

#endif
