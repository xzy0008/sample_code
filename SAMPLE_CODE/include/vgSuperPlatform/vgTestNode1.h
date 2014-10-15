#pragma once
#include "vgBaseEntry.h"
#include "vgTestNode1TabOne.h"
#include "vgTestNode1PropertiesTab.h"
#include "vgPropertyPage.h"




#if 0


class vgTestNode1 : public vgBaseEntry
{
public:
	const static int s_NumOfParam = 13;
	static PropertiesParam s_ParamArray[s_NumOfParam];

public:

	friend class PropertiesTab;
	friend class TabOne;

	vgTestNode1(string name);
	virtual ~vgTestNode1(void);

	// extends from vgBaseEntry
	string GetName();

	// extends from vgBaseEntry
	void AddNodeTabs();

	int GetSelectedImage() { return 1; }
	int GetUnSelectedImage() { return 2; }

	void SetPosX(float posX);
	void SetPosY(float posY);
	void SetPosZ(float posZ);
	void SetCaption(string caption);
	void SetSize(int siz);
	void SetEnable(bool enable);

	void Render();

	float GetPosX();
	float GetPosY();
	float GetPosZ();
	string GetCaption();
	int	GetSize();
	bool GetEnable();

private:
	float m_posX;
	float m_posY;
	float m_posZ;

	string m_sCaption;
	int    m_nSiz;
	bool   m_bEnable;	
	string m_sOptionOne;

	PropertiesParam* paramArray;
	int				 numOfParam;

	TabOne *m_tabOne;
	PropertiesTab *m_pTab;
};

inline void vgTestNode1::Render()
{
	if (m_bEnable)
	{
		glColor3f(1.f, 1.f, 1.f);

		glPushMatrix();

		glTranslated(m_posX, m_posY, m_posZ);

		//glutSolidSphere(m_nSiz, 20.0, 20.0);

		glPopMatrix();
	}
	
}
#endif