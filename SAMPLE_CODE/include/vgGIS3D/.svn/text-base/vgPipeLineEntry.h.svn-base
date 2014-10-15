#pragma once

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkRendererObserver.h>
#include <vgKernel/vgkVec3.h>
#include <vgKernel/vgkCoordSystem.h>
#include <vgGIS/vggisDefinition.h>

#include <vgEntry/vgBaseEntry.h>
#include <vgUIController/vgPropertyPage.h>
#include <vgEntry/vgGroupBasedEntry.h>
#include <vgUIController/vgDatabasePage.h>
#include <vgGIS3D/vggiOGRPipeLineMap.h>

class  VGG_EXPORT vgPipeLineEntry  : public vgGroupBasedEntry
{
public:

	static std::vector<PropertiesParam> _params;

public:
	vgPipeLineEntry(vgGIS3D::OGRPipeLineMap *pPipeLine)
		:vgGroupBasedEntry(pPipeLine)
	{		
		m_pOGRPipeLineMap = pPipeLine;
		getData();
	}

	void getData()
	{
		vgGIS3D::OGRPipeLineMap *pPipeLine = dynamic_cast<vgGIS3D::OGRPipeLineMap*>(m_pOGRPipeLineMap);

		if (pPipeLine != NULL)
		{ 

			vgKernel::Vec3 pos = pPipeLine->getPosition();

			m_posX = pos.x + vgKernel::CoordSystem::getSingleton().getProjectionCoord().x;
			m_posY = pos.y + vgKernel::CoordSystem::getSingleton().getProjectionCoord().y;
			m_posZ = pos.z + vgKernel::CoordSystem::getSingleton().getProjectionCoord().z;

			m_OGRPipeLineName = pPipeLine->getName();
			//m_enableTrigger = pPipeLine->getTriggerEnable();
			//m_innerVisible = pPipeLine->getInnerVisible();
		}
	}


	virtual ~vgPipeLineEntry(void)
	{
		((vgGIS3D::OGRPipeLineMap*)m_Renderer)->unregisterObserver( this );
	}

	virtual String GetName()
	{
		return m_OGRPipeLineName;
	}

	int GetSelectedImage() { return 7; }

	int GetUnSelectedImage() { return 8; }

	// 继承自Changed，用于Object修改后更新Node
	void onChanged(int eventId, void *param);

	void  showAttriList();

	virtual void AddSingleTabPage();
	virtual void OnSinglePropertyChanged(string paramName);
	virtual void AddGroupTabPage() {}
	virtual void OnGroupPropertyChanged(string paramName) {}
private:

	void updateData();
	CMenu* GetContextMenu();
	//void getData();

private:
	
	string m_OGRPipeLineName;
	
	float  m_posX;
	float  m_posY;
	float  m_posZ;
	float  m_posZMinus;

	bool   m_enableTrigger;
	bool   m_innerVisible;

	vgKernel::Renderer *m_pOGRPipeLineMap;	
};
