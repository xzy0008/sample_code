

#pragma once

#include <vgEntry/vgGroupBasedEntry.h>
#include <vgKernel/vgkUniqueID.h>
#include <vgKernel/vgkRendererObserver.h>
#include <vgPlan/vgPlanbox.h>
#include <vgKernel/vgkCoordSystem.h>

class vgBlockEntry : public vgGroupBasedEntry
{
public:
	// 	const static int s_NumOfParam = 6;
	// 	static PropertiesParam s_ParamArray[s_NumOfParam];

public:
	vgBlockEntry(  vgPlan::vgPlanbox* pObject = NULL);

	virtual ~vgBlockEntry(void)
	{
		m_Renderer->unregisterObserver( this );
	}

	/*	void AddNodeTabs();*/

	void AddSingleTabPage();

	void AddGroupTabPage(); //  {}

	void OnSinglePropertyChanged(string paramName);

	void OnGroupPropertyChanged(string paramName);

	int GetSelectedImage() { return 1; }

	int GetUnSelectedImage() { return 2; }

	void onChanged(int eventId, void *param);

	void UpDataProp() {}

	CMenu* GetContextMenu();


private:

	void getData();

	//vgCore::ObjectNode* m_pObject;

	// 被修改数据的副本
	GLfloat m_posX;
	GLfloat m_posY;
	GLfloat m_posZ, m_posZMinus;

	int m_layer;
	float m_heightPerLayer;
	float m_length;
	float m_width;
	float m_angle;

	string m_sCaption;
};
