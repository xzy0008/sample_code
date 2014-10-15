#pragma once


#include <vgKernel/vgkUniqueID.h>
#include <vgKernel/vgkRendererObserver.h>

#include <vgUIController/vgPropertyPage.h>
#include <vgEntry/vgBaseEntry.h>

#include <vgCam/vgcaViewCam.h>
//#include <vgCoordinate.h>
#include <vgKernel/vgkCoordSystem.h>

class  VGUI_EXPORT vgViewCamEntry : public vgBaseEntry
{
 public:
 	const static int s_NumOfParam = 6;
 	static PropertiesParam s_ParamArray[s_NumOfParam];

public:
	vgViewCamEntry( vgCam::ViewCam* viewcamitem )
		: vgBaseEntry( viewcamitem )
	{
		assert( viewcamitem != NULL );

		vgKernel::Vec3 pos = viewcamitem->getPosition();

		m_posX = pos.x + vgKernel::CoordSystem::getSingleton().getProjectionCoord().x;
		m_posY = pos.y + vgKernel::CoordSystem::getSingleton().getProjectionCoord().y;
		m_posZ = pos.z + vgKernel::CoordSystem::getSingleton().getProjectionCoord().z;
		m_posZMinus = - m_posZ;
		vgKernel::CoordSystem::getSingleton().registerObserver(this);

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

