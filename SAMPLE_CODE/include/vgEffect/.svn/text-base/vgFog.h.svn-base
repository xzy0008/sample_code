
#ifndef  _VGFOG_H_INCLUDED_
#define  _VGFOG_H_INCLUDED_

//includes	
//#include <vgStableHeaders.h>							//含图形库	
#include <vgMath/vgfPrerequisites.h>		//含数学库
#include <vgEffect/vgParticle.h>

/************************************************************************/
/*    vgFog类的描述
功能：生成一个雾景象
用法：  1，在opengl环境下实例化一个对象 vgFog pFog;
		2，在opengl初始化时设置参数         pFog.Set*();
		3，在opengl初始化时执行初始化       pFog.Init();
		4，在opengl渲染时执行				pFog.Render();
		5, 在任何时候还可控制雪景			pFog.Open() ;
注意：      
/************************************************************************/

namespace vgMod
{
	
	// class    vgFog
	class    vgFog : public vgParticle
	{
		VGK_RENDERER_IN_DECLARE( vgFog )

	public:
		vgFog();
		~vgFog();
		void Initialize();
		void Render();
//		void StopSpecialEffect(BOOL m_bStopSE);
		
	public:
		enum    FOGMODE
		{
			typeExp		= GL_EXP, 
			typeExp2	= GL_EXP2, 
			typeLine	= GL_LINEAR 
		};
		
		typedef struct   
		{
			GLfloat start;
			GLfloat	end;
		} FOGBOUND;	

		// 设置雾的密度变化模式
		void SetMode( FOGMODE fogMode );  //vgFog::typeExp、typeExp2、typeLine
		void SetMode( GLuint  fogModeIndex ); //0~2
		
		// 设置雾的颜色
		void SetColor(GLfloat r, GLfloat g, GLfloat b,float a=1.0f);
		void SetColor( GLuint fogColorIndex ); //0~1
			
		// 设置雾的密度
		void SetDensity(GLfloat fogDensity);
		
		// 设置雾的远近面Z值
		void SetBound( FOGBOUND fogBound);
		void SetBound( GLfloat fogStart, GLfloat fogEnd );
		
	public:
		GLuint	fogModeIndex;
		FOGMODE  fogModeVar;
		
		GLuint  fogColorIndex;
		GLfloat fogColorVar[4];
		
		GLfloat	fogDensity;
		FOGBOUND fogBound;
		
		BOOL	bfogOpen;
	};//class    vgFog
	

	VGK_RENDERER_OUT_DECLARE( vgFog )


}	//namespace vgCore


#endif // _VGFOG_H_INCLUDED_