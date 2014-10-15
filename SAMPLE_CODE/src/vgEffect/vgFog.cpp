
#include <vgStableHeaders.h>
#include "vgeffect/vgFog.h"


// class vgFog
namespace vgMod
{
	
	
	VGK_RENDERER_IMPLEMENT( vgFog,RENDERER_TYPE_PARTICLE )
	// 雾由远及近密度变化模式，指数、指数平方、线性3种
	static vgFog::FOGMODE fogModeConst[3]= 
	{ vgFog::typeExp,vgFog::typeExp2,vgFog::typeLine };
	
	// 雾的颜色
	static GLfloat	fogColorConst[][4] = {	{0.8f,0.8f,0.75f,0.9f},
	{0.5f ,0.5f ,0.5f, 1.0f}, 
	{1.0f ,1.0f ,1.0f, 1.0f},
	{0.25f,0.25f,0.25f,1.0f}  };
	
	vgFog::vgFog()
	{
		fogColorIndex	= /*1*/0;
		fogModeIndex	= 2;
		
		fogColorVar[0]		= fogColorConst[fogColorIndex][0] ;
		fogColorVar[1]		= fogColorConst[fogColorIndex][1] ;
		fogColorVar[2]		= fogColorConst[fogColorIndex][2] ;
		fogColorVar[3]		= fogColorConst[fogColorIndex][3] ;
		
		fogModeVar			= fogModeConst[fogModeIndex];
		
		fogDensity			= 0.35/*0.35f*/;
		fogBound.start		= 0.1f;
		fogBound.end		= 5000.0f/*5.0f*/;
		
		bfogOpen			= FALSE;
	}
	
	vgFog::~vgFog()
	{
		
	}
	
	void vgFog::SetMode( FOGMODE fogMode )
	{
		fogMode = fogMode;
	}
	
	void vgFog::SetMode( GLuint fogModeIndex )
	{
		fogModeIndex = fogModeIndex;
	}
	
	void vgFog::SetColor( float r, float g, float b ,float a)
	{
		fogColorVar[0] = r;
		fogColorVar[1] = g;
		fogColorVar[2] = b;
		fogColorVar[3] = a;
	}
	
	void vgFog::SetColor( GLuint fogColorIndex )
	{
		fogColorIndex = fogColorIndex;	
	}
	
	void vgFog::SetDensity( GLfloat fogDensity )
	{
		fogDensity = fogDensity;	
	}
	
	void vgFog::SetBound( FOGBOUND fogBound )
	{
		fogBound.start  = fogBound.start;
		fogBound.end	= fogBound.end;
	}
	
	void vgFog::SetBound( GLfloat fogStart, GLfloat fogEnd )
	{
		fogBound.start  = fogStart;
		fogBound.end	= fogEnd;	
	}
	
	void vgFog::Initialize()
	{			
		// 设置背景色为雾的颜色
//		glClearColor(fogColorVar[0], fogColorVar[1], 
//				fogColorVar[2], fogColorVar[3]);	
		glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
// 		
// 			glClearColor(0.5f,0.5f,0.5f,1.0f);					// We'll Clear To The Color Of The Fog
// 		 	glClearDepth(1.0f);									// Depth Buffer Setup
// 		 	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
// 		 	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
		
		
		// 设置雾的密度变化模式
		glFogi(GL_FOG_MODE, fogModeVar );			// Fog Mode
		
		// 设置雾的颜色
		glFogfv(GL_FOG_COLOR, fogColorVar );		// Set Fog Color
		
		// 设置雾的密度
		glFogf(GL_FOG_DENSITY, fogDensity);						// How Dense Will The Fog Be
		glHint(GL_FOG_HINT, GL_DONT_CARE);					// Fog Hint Value
		
		// 设置雾的远近面Z值
		glFogf(GL_FOG_START, fogBound.start);							// Fog Start Depth
		glFogf(GL_FOG_END, fogBound.end);							// Fog End Depth
		
		// 初始化化开启雾
		//	glEnable(GL_FOG);									// Enables GL_FOG
	}// void vgFog::Init()
	
	void vgFog::Render()
	{
		if (!m_bStopSE)
		{
			glEnable(GL_FOG);
			glClearColor(fogColorVar[0], fogColorVar[1], 
				fogColorVar[2], fogColorVar[3]);	

		}
		else
		{
			glDisable(GL_FOG);
			glClearColor(0.5f,0.6f,0.8f,1.0f);
		}
	}// void vgFog::Render()
		
	
}	//namespace vgCore
