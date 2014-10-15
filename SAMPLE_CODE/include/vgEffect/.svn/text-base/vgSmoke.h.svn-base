
#ifndef  _VGSMOKE_H_INCLUDED_
#define  _VGSMOKE_H_INCLUDED_
/************************************************************************/
/*    vgSmoke类的描述
功能：生成一个烟尘位置可调的烟尘景象
用法：  1，在opengl环境下实例化一个对象		vgSmoke pSmoke;
		2，在opengl初始化时设置参数         pSmoke.Set*();
		3，在opengl初始化时执行初始化       pSmoke.Init();
		4，在opengl渲染时执行				pSmoke.Render();
		5, 在任何时候还可控制				pSmoke.StopSpecialEffect() ;
注意： 
/************************************************************************/


//includes	
//#include <vgStableHeaders.h>							//含图形库	
#include <vgMath/vgfPrerequisites.h>		//含数学库
#include <vgEffect/vgParticle.h>

namespace vgMod
{
	//const CategoryType NODE_TYPE_SMOKE	= 33;

	// class    vgSmoke
	class    vgSmoke : public vgParticle
	{
		VGK_RENDERER_IN_DECLARE( vgSmoke )
	public:
		vgSmoke();
		~vgSmoke();
		void Initialize();
		void Render();

		void UpdatePos();
		
		void SetCount( int count=MAX_PARTICLES );
		void SetCenter(float x, float y, float z);    //  设置烟尘源点

		BoundingBox ComputeBoundBox();		

		//void WriteNodeToVG(CFile &fp); //写入文件;
		//	void StopSpecialEffect(BOOL m_bStopSE);							 //  控制烟尘开/关？
	public:
		
		typedef struct						// Create A Structure For Particle
		{
			bool	active;					// Active (Yes/No)
			float	life;					// Particle Life
			float	fade;					// Fade Speed
			
			float	r;						// Red Value
			float	g;						// Green Value
			float	b;						// Blue Value
			
			float	x;						// X Position
			float	y;						// Y Position
			float	z;						// Z Position
			
			float	xi;						// X Direction
			float	yi;						// Y Direction
			float	zi;						// Z Direction
			
			float	xg;						// X Gravity
			float	yg;						// Y Gravity
			float	zg;						// Z Gravity
			
			bool	point;
		} SmokeParticles;	
		
		SmokeParticles  *m_pSmoke;			//  定义指针指向 动态申请的保存烟尘粒子系统属性的 \
		// 二维数组所占内存空间
		GLUquadricObj *m_Sphere;
		enum	MAXNUMBER
		{
			MAX_PARTICLES	=1000
		};
		
//		GLuint  m_pTexture;	
		GLuint  colorIndex;
		GLuint  delay;
		GLfloat	xspeed;
		GLfloat	yspeed;
		GLfloat slowdown;
	public:
		float centerX, centerY, centerZ;
		
		TexturePtr m_pTexture ;	//m_pTexture
	};// class    vgSmoke
	

	VGK_RENDERER_OUT_DECLARE( vgSmoke )
	
}	//namespace vgCore

#endif // _VGSMOKE_H_INCLUDED_