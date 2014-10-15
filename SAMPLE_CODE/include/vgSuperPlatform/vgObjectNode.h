#pragma once
#include "vgBaseEntry.h"
#include "vgObjectPropPage.h"


#if 0 


class vgObjectNode :
	public vgBaseEntry
{
	friend class vgObjectPropPage;

public:
	vgObjectNode(String nameID);
	virtual ~vgObjectNode(void);

	void AddNodeTabs();
	int GetSelectedImage() { return 1; }
	int GetUnSelectedImage() { return 2; }

	void Render() {}

protected:
	vgObjectPropPage* m_pPropPage;

	float m_posX;
	float m_posY;
	float m_posZ;

	long m_near;
	long m_far;

	float m_rotX;
	float m_rotY;
	float m_rotZ;

	long m_scaleX;
	long m_scaley;
	long m_scaleZ;

	bool m_visable;
};


#endif