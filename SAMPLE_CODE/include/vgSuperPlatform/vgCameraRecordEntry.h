#pragma once

#include "vgBaseEntry.h"
#include <vgKernel/vgkUniqueID.h>
#include <vgCam/vgcaCameraRecord.h>
#include <vgKernel/vgkRendererObserver.h>
#include "vgPropertyPage.h"



class vgCameraRecordEntry : public vgBaseEntry
{
 public:
 	const static int s_NumOfParam = 6;
 	static PropertiesParam s_ParamArray[s_NumOfParam];

public:
	vgCameraRecordEntry( vgCam::CameraRecord* vcrpar );

	virtual ~vgCameraRecordEntry(void)
	{
		((vgCam::CameraRecord*)m_Renderer)->unregisterObserver( this );
	}

	void AddNodeTabs();

	int GetSelectedImage() { return 1; }

	int GetUnSelectedImage() { return 2; }

	// 继承自vgBasedNode,被vgUIController调用 修改Node后重新设置Object 和TreeItem
	void OnPropertyChanged(string paramName);// { TRACE("Camera Property Changed \n");}

	// 继承自Changed，用于Object修改后更新Node
	void onChanged(int eventId, void* param);

	void UpDataProp() {}

	CMenu* GetContextMenu();

private:

	// 被修改数据的副本
	GLfloat m_offX;
	GLfloat m_offY;
	GLfloat m_offZ;
};

