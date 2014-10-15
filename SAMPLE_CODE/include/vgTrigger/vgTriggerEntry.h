#pragma once

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkRendererObserver.h>
#include <vgKernel/vgkVec3.h>
#include <vgKernel/vgkCoordSystem.h>

#include <vgEntry/vgBaseEntry.h>
#include <vgUIController/vgPropertyPage.h>
#include <vgEntry/vgGroupBasedEntry.h>
#include <vgUIController/vgDatabasePage.h>
#include <vgTrigger/vgtrTrigger.h>
#include <vgTrigger/vgtrDefinition.h>

class   VGTRI_EXPORT vgTriggerEntry  : public vgGroupBasedEntry
{
public:

	static std::vector<PropertiesParam> _params;

public:
	vgTriggerEntry(vgTrigger::Trigger *pTrigger)
		:vgGroupBasedEntry(pTrigger)
	{		
		m_pTrigger = pTrigger;
		getData();
	}

	void getData()
	{
		vgTrigger::Trigger *pTrigger = dynamic_cast<vgTrigger::Trigger*>(m_pTrigger);

		if (pTrigger != NULL)
		{ 

			vgKernel::Vec3 pos = pTrigger->getPosition();

			m_posX = pos.x + vgKernel::CoordSystem::getSingleton().getProjectionCoord().x;
			m_posY = pos.y + vgKernel::CoordSystem::getSingleton().getProjectionCoord().y;
			m_posZ = pos.z + vgKernel::CoordSystem::getSingleton().getProjectionCoord().z;

			m_triggerName = pTrigger->getName();
			m_enableTrigger = pTrigger->getTriggerEnable();
			m_innerVisible = pTrigger->getInnerVisible();
		}
	}


	virtual ~vgTriggerEntry(void)
	{
		((vgTrigger::Trigger*)m_Renderer)->unregisterObserver( this );
	}

	virtual String GetName()
	{
		return m_triggerName;
	}

	int GetSelectedImage() { return 7; }

	int GetUnSelectedImage() { return 8; }

	// 继承自Changed，用于Object修改后更新Node
	void onChanged(int eventId, void *param);

	virtual void AddSingleTabPage();
	virtual void OnSinglePropertyChanged(string paramName);
	virtual void AddGroupTabPage() {}
	virtual void OnGroupPropertyChanged(string paramName) {}
private:

	void updateData();
	//void getData();

private:
	
	string m_triggerName;
	
	float  m_posX;
	float  m_posY;
	float  m_posZ;
	float  m_posZMinus;

	bool   m_enableTrigger;
	bool   m_innerVisible;

	vgKernel::Renderer *m_pTrigger;	
};
