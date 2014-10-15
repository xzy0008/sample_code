
//#include "vgStableHeaders.h"
#include "stdafx.h"
#include "OceanInputHandler.h"
#include <vgKernel/vgkInputCodeDef.h>

#include <vgKernel/vgkMath.h>
#include <vgKernel/vgkCoordSystem.h>
#include "CRenderer.hpp"

namespace VR_Ocean {


	//----------------------------------------------------------------
	COceanInputHandler::COceanInputHandler(int a )
	{
		SetHandleStatus( VG_INPUT_OCEAN );
		vgKernel::InputSystem::getSingleton().registerHandle( this );
	}



	//----------------------------------------------------------------
	COceanInputHandler::~COceanInputHandler()
	{
		vgKernel::InputSystem::getSingleton().setDefaultStatus();
		vgKernel::InputSystem::getSingleton().removeHandle( this );

	}

	// ÊäÈëÄ£¿é ---------------------------------------------------
	void COceanInputHandler::OnLButtonDown(UINT nFlags, CPoint position)
	{
		if (CRenderer::getSingleton().m_bPointAddStart)
		{
			vgKernel::Vec3 tempVec=vgKernel::Math::trans2DPointTo3DVec(position.x, position.y);
			Ocean_Vec3 vec3(tempVec.x,tempVec.y,tempVec.z);
			VR_Ocean::CRenderer::getSingleton().m_PointArray.Add(vec3);

			VR_Ocean::CRenderer::getSingleton().calculateRounding();	// Add By FengYK @2010-01-26 14:22
		}
	}
	void COceanInputHandler::OnKeyDown(int keyCode)
	{
		if(keyCode==59&&!(GetKeyState(VK_RSHIFT) & 0x8000))
		{//F1
			VR_Ocean::CRenderer::getSingleton().m_WaterHeight+=0.2;
		}
		if(keyCode==60&&!(GetKeyState(VK_RSHIFT) & 0x8000))
		{//F2
			VR_Ocean::CRenderer::getSingleton().m_WaterHeight-=0.2;
		}
		if(keyCode==61&&!(GetKeyState(VK_RSHIFT) & 0x8000))
		{//F3
			VR_Ocean::CRenderer::getSingleton().m_TexScale*=1.1;
		}
		if(keyCode==62&&!(GetKeyState(VK_RSHIFT) & 0x8000))
		{//F4
			//if (m_renderer.m_WaterScale>0.1)
			{
				VR_Ocean::CRenderer::getSingleton().m_TexScale/=1.1;
			}
		}
		if(keyCode==63&&!(GetKeyState(VK_RSHIFT) & 0x8000))
		{//F5
			VR_Ocean::CRenderer::getSingleton().m_Opacity+=0.01;
		}
		if(keyCode==64&&!(GetKeyState(VK_RSHIFT) & 0x8000))
		{//F6
			//if (m_renderer.m_WaterScale>0.1)
			{
				VR_Ocean::CRenderer::getSingleton().m_Opacity-=0.01;
			}
		}
	}
}
