

#pragma once

#include <vgEntry/vgBaseEntry.h>
#include <vgKernel/vgkUniqueID.h>

#include <vgEffect/vgDynamicBillboardNode.h>

#include <vgKernel/vgkRendererObserver.h>
#include <vgUIController/vgPropertyPage.h>
#include <vgKernel/vgkCoordSystem.h>


namespace vgMod{

using namespace vgCore;

class vgDynamicBillboardEntry :	public vgBaseEntry
{
public:
	const static int s_NumOfParam = 8;
	static PropertiesParam s_ParamArray[s_NumOfParam];

public:
	vgDynamicBillboardEntry(  DynamicBillboardNode* pObject = NULL)
		: vgBaseEntry( pObject )
	{
		assert( pObject != NULL );

		m_Positionx = pObject->m_Position.x + vgKernel::CoordSystem::getSingleton().getProjectionCoord().x;
		m_Positiony = pObject->m_Position.y + vgKernel::CoordSystem::getSingleton().getProjectionCoord().y;
		m_Positionz = pObject->m_Position.z + vgKernel::CoordSystem::getSingleton().getProjectionCoord().z;
		m_PositionzMinus = - m_Positionz;
		m_height = pObject->m_height;
		m_width = pObject->m_width;

		vgKernel::CoordSystem::getSingleton().registerObserver(this);

	}

	virtual ~vgDynamicBillboardEntry(void)
	{
		((DynamicBillboardNode* )m_Renderer)->unregisterObserver( this );
	}

	void AddNodeTabs();

	int GetSelectedImage() { return 1; }

	int GetUnSelectedImage() { return 2; }

	// 继承自vgBasedNode修改Node后重新设置Object 和TreeItem
	void OnPropertyChanged(string paramName);// { //TRACE("Camera Property Changed \n");}

	// 继承自Changed，用于Object修改后更新Node
	void onChanged(int eventId, void *param);

	void UpDataProp() {}

	CMenu* GetContextMenu();


private:
	//vgCore::ObjectNode* m_pObject;

	// 被修改数据的副本
	float m_Positionx;
	float m_Positiony;
	float m_Positionz, m_PositionzMinus;

	float m_height;
	float m_width;

	string m_sCaption;
};


}//namespace vgCore
