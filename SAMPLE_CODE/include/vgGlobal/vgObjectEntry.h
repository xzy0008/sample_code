

#pragma once

#include <vgEntry/vgBaseEntry.h>
#include <vgKernel/vgkUniqueID.h>

#include "vgMod/vgObjNode.h"
#include <vgEffect/vgAviNode.h>

#include <vgKernel/vgkRendererObserver.h>
#include <vgUIController/vgPropertyPage.h>
#include <vgEntry/vgDatabaseEntry.h>

namespace vgMod{



class  VGGL_EXPORT vgObjectEntry :	public vgDatabaseEntry
{
public:
// 	const static int s_NumOfParam = 6;
// 	static PropertiesParam s_ParamArray[s_NumOfParam];

public:
	vgObjectEntry(  ObjectNode* pObject );

	virtual ~vgObjectEntry(void)
	{
		((ObjectNode*)m_Renderer)->unregisterObserver( this );
	}

// 	void AddNodeTabs();

	void AddSingleTabPage();
	
	void AddGroupTabPage(); //  {}

	void OnSinglePropertyChanged(string paramName);

	void OnGroupPropertyChanged(string paramName);// {};

	int GetSelectedImage() { return 1; }

	int GetUnSelectedImage() { return 2; }

	// 继承自vgBasedNode修改Node后重新设置Object 和TreeItem
//	void OnPropertyChanged(string paramName);// { //TRACE("Camera Property Changed \n");}

	// 继承自Changed，用于Object修改后更新Node
	void onChanged(int eventId, void *param);

	void UpDataProp() {}

	CMenu* GetContextMenu();
	
private:

	void getData();

	//add by KingHJ 2010.03.17
	void getGroupData();

	// 被修改数据的副本
	GLfloat m_posX;
	GLfloat m_posY;
	GLfloat m_posZ, m_posZMinus;

	bool	m_bOpacity;
	bool   *m_pbUnderWater;
	bool	m_bDoubleFaceRender;

	bool	m_bVisible;
	bool  m_bAviPlay;
	String* m_aviName;
	//string m_sCaption;

	int    m_startTime;
	int    m_endTime;

	COLORREF _colorRef;
	float	m_fColorRatio;
	bool	m_enableCollision;

	bool m_bgroupOpacity;	
	bool m_bGroupDbFaceRender;
	bool m_bGroupVisible;

	int    m_groupStartTime;
	int    m_groupEndTime;

	bool m_bGroupHaveAvi;
	bool m_bGroupAviPlay;
	string m_GroupAviName;

private:
	static bool ms_collisionEnable;
};


}//namespace vgCore
