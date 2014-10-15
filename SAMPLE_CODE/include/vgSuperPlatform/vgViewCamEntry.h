#pragma once

#include "vgBaseEntry.h"
#include <vgKernel/vgkUniqueID.h>
#include <vgCam/vgcaViewCam.h>
#include <vgKernel/vgkRendererObserver.h>
#include "vgPropertyPage.h"
#include <vgCoordinate.h>


class vgViewCamEntry : public vgBaseEntry
{
 public:
 	const static int s_NumOfParam = 6;
 	static PropertiesParam s_ParamArray[s_NumOfParam];

public:
	vgViewCamEntry( vgCam::ViewCam* viewcamitem )
		: vgBaseEntry( VG_ENTRY_VIEWCAM , viewcamitem )
	{
		assert( viewcamitem != NULL );

		vgKernel::Vec3 pos = viewcamitem->getPosition();

		m_posX = pos.x + vgCore::vgCoordinate::getSingleton().GetSceneCood().x;
		m_posY = pos.y + vgCore::vgCoordinate::getSingleton().GetSceneCood().y;
		m_posZ = pos.z + vgCore::vgCoordinate::getSingleton().GetSceneCood().z;
		m_posZMinus = - m_posZ;
		vgCore::vgCoordinate::getSingleton().registerObserver(this);

	}

	virtual ~vgViewCamEntry(void)
	{
		((vgCam::ViewCam*)m_Renderer)->unregisterObserver( this );
	}

	void AddNodeTabs();

	int GetSelectedImage() { return 1; }

	int GetUnSelectedImage() { return 2; }

	// 继承自vgBasedNode,被vgUIController调用 修改Node后重新设置Object 和TreeItem
	void OnPropertyChanged(string paramName);// { //TRACE("Camera Property Changed \n");}

	// 继承自Changed，用于Object修改后更新Node
	void onChanged(int eventId, void* param);

	void UpDataProp() {}



	CMenu* GetContextMenu();

private:

	// 被修改数据的副本
	GLfloat m_posX;
	GLfloat m_posY;
	GLfloat m_posZ, m_posZMinus;
};

