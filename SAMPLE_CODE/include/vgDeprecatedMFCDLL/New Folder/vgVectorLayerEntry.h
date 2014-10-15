#pragma once

#include "vgBaseEntry.h"
#include "vgUIController.h"
#include <vgKernel/vgkChangedObserver.h>

#include <vgVector/vgvLayer.h>

class vgVectorLayerEntry :	public vgBaseEntry
{
public:
	const static int s_NumOfParam = 8;
	static PropertiesParam s_ParamArray[s_NumOfParam];

public:
	vgVectorLayerEntry(vgVector::vgvLayer*	pLayer);
	virtual ~vgVectorLayerEntry(void);

	void AddNodeTabs();

	int GetSelectedImage() { return 1; }

	int GetUnSelectedImage() { return 2; }

	// 继承自vgBasedNode修改Node后重新设置Object 和TreeItem
	void OnPropertyChanged(string paramName);// { //TRACE("Camera Property Changed \n");}

	// 继承自Changed，用于Object修改后更新Node
	void OnChanged(int eventId, void *param);

	void UpDataProp() {} 

	CMenu* GetContextMenu()
	{
		return NULL;
	}

private:

	// 被修改数据的副本
	vgKernel::Vec3	m_LayerCenterPoint;
	bool	m_bIsLayerVisible;

	float	m_posZMinus;

	String	m_strConstShapeCount;
};
