#pragma once

#include "vgBaseEntry.h"
#include "vgUIController.h"
#include <vgKernel/vgkRendererObserver.h>


class vgCoordinateEntry :	public vgBaseEntry
{
public:
	const static int s_NumOfParam = 6;
	static PropertiesParam s_ParamArray[s_NumOfParam];

public:
	vgCoordinateEntry();

	void getData();
	virtual ~vgCoordinateEntry(void);

	void AddNodeTabs();

	virtual String GetName()
	{
#if VGK_LANG_CHS
		return "场景原点";
#else
		return "Scene Origin";
#endif
	}

	int GetSelectedImage() { return 1; }

	int GetUnSelectedImage() { return 2; }

	// 继承自vgBasedNode修改Node后重新设置Object 和TreeItem
	void OnPropertyChanged(string paramName);// { //TRACE("Camera Property Changed \n");}

	// 继承自Changed，用于Object修改后更新Node
	void onChanged(int eventId, void *param);

	void UpDataProp() {}

	CMenu* GetContextMenu()
	{
		return NULL;
	}

private:


	// 被修改数据的副本
	GLfloat m_PosX;
	GLfloat m_PosY;
	GLfloat m_PosZ, m_PosZMinus;

	String m_sCaption;
};
