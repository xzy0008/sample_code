/*#pragma once*/
#ifndef __VGMS3DENTRY_H__
#define __VGMS3DENTRY_H__

#include <vgEntry/vgBaseEntry.h>

#include <vgUIController/vgUIController.h>
#include <vgKernel/vgkRendererObserver.h>
#include <vgMs3d/ms3d.h>

class  VGGL_EXPORT vgMs3dEntry : public vgBaseEntry
{
public:
	//const static int s_NumOfParam = 10;
	//static PropertiesParam s_ParamArray[s_NumOfParam];
	static vector<PropertiesParam> s_ParamArray;

public:
	vgMs3dEntry(vgMs3d::CMs3d* pObject);
	virtual ~vgMs3dEntry(void)
	{
		((vgMs3d::CMs3d*)m_Renderer)->unregisterObserver( this );
	};

	void AddNodeTabs();

	virtual String GetName()
	{
		return m_Renderer->getName();
	}

	int GetSelectedImage() { return 1; }

	int GetUnSelectedImage() { return 2; }

	void OnPropertyChanged(string paramName);// { TRACE("Camera Property Changed \n");}

	void onChanged(int eventId, void *param);

	void UpDataProp() {}

	CMenu* GetContextMenu();
	void getData();

private:
#if 0
	vgMs3d::CMs3d* m_pObject;

	// 被修改数据的副本
	float m_Positionx;
	float m_Positiony;
	float m_Positionz, m_PositionzMinus;
#else
	GLfloat m_posX;
	GLfloat m_posY;
	GLfloat m_posZ, m_posZMinus;
#endif

	float m_startframe;
	float m_endframe;
	bool b_play;
	bool b_loop;

	float m_speed;

	bool * m_pbUnderWater;

	//string m_sCaption;
};


#endif
