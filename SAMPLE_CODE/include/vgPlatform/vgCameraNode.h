#pragma once
#include "vgbasednode.h"
#include <cmath>
#include "vgUIController.h"

#define KEY_DOWN(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define PI 3.1415926535

class vgCameraNode :
	public vgBasedNode
{
public:
	const static int s_NumOfParam = 4;
	static PropertiesParam s_ParamArray[s_NumOfParam];

public:
	vgCameraNode(string cameraName);
	virtual ~vgCameraNode(void);

	void AddNodeTabs();//{}

	void Render();

	int GetSelectedImage() { return 1; }

	int GetUnSelectedImage() { return 2; }

	void SetPosX(float posX);

	void SetPosY(float posY);

	void SetPosZ(float posZ);

private:
	GLfloat m_eyePosX;
	GLfloat m_eyePosY;
	GLfloat m_eyePosZ;

	GLfloat m_tarPosX;
	GLfloat m_tarPoxY;
	GLfloat m_tarPoxZ;

	GLfloat m_upPosX;
	GLfloat m_upPosY;
	GLfloat m_upPoxZ;

	GLfloat m_hAngle;
	GLfloat m_vAngle;
};

inline void vgCameraNode::Render()
{
	
 	//glPushMatrix();
	glLoadIdentity();
	// TRACE("Camera here \n");
	if (KEY_DOWN(VK_LEFT))
	{
		m_hAngle += 1.f;
	}

	if (KEY_DOWN(VK_RIGHT))
	{	
		m_hAngle -= 1.f;
	}

	if (KEY_DOWN(VK_HOME))
	{
		SetPosY(m_eyePosY + 0.1f);
	}

	if (KEY_DOWN(VK_END))
	{
		SetPosY(m_eyePosY - 0.1f);
	}

	if (KEY_DOWN(VK_NEXT))
	{
		m_vAngle -= 0.5f;
		if (m_vAngle < -90)
			m_vAngle = -90.f;
	}

	if (KEY_DOWN(VK_PRIOR))
	{
		m_vAngle += 0.5f;
		if (m_vAngle > 90)
			m_vAngle = 90.f;
	}
	
	if (KEY_DOWN(VK_UP))
	{
		SetPosX(m_eyePosX + sin(m_hAngle * PI / 180) * 0.8);
		SetPosZ(m_eyePosZ + cos(m_hAngle * PI / 180) * 0.8);
	}

	if (KEY_DOWN(VK_DOWN))
	{
		SetPosX(m_eyePosX - sin(m_hAngle * PI / 180) * 0.8);
		SetPosZ(m_eyePosZ - cos(m_hAngle * PI / 180) * 0.8);
	}

	m_tarPosX = m_eyePosX + sin(m_hAngle * PI / 180);
	m_tarPoxZ = m_eyePosZ + cos(m_hAngle * PI / 180);
	m_tarPoxY = m_eyePosY + sin(m_vAngle * PI / 180);

	// gluLookAt(0,0,0, 10, 10, 10, 0, 1, 0);
	gluLookAt(m_eyePosX, m_eyePosY, m_eyePosZ, m_tarPosX, m_tarPoxY, m_tarPoxZ, m_upPosX, m_upPosY, m_upPoxZ);
	// TRACE("Look at %f, %f, %f \n", m_tarPosX, m_tarPoxY, m_tarPoxZ);
	// glPopMatrix();	
}