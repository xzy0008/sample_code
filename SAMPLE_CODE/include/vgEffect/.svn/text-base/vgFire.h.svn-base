
#ifndef  _VGFIRE_H_INCLUDED_
#define  _VGFIRE_H_INCLUDED_
/************************************************************************/
/*    vgFire类的描述
功能：生成一个火源位置可调的火焰景象
用法：  1，在opengl环境下实例化一个喷泉对象 vgFire pFire;
		2，在opengl初始化时设置参数         pFire.SetFountin();
		3，在opengl初始化时执行初始化       pFire.InitFountin();
		4，在opengl渲染时执行				pFire.DrawFountin();
		5, 在任何时候还可控制雪景			pFire.SetFountin()pFire.StopFountin() ;
注意： 火源位置暂时只能由类成员函数 SetFountin()设置， 不支持鼠标键盘实时编辑     */
/************************************************************************/


//#include <vgStableHeaders.h>
#include <vgMath/vgfPrerequisites.h>
#include <vgEffect/vgParticle.h>


namespace vgMod
{
	//const CategoryType NODE_TYPE_FIRE	= 32;

	class    vgFire : public vgParticle
	{
		VGK_RENDERER_IN_DECLARE( vgFire )
		// 构造、析构
	public:
		vgFire();
		~vgFire();
		

		void UpdatePos();


		// 从父类继承函数
		void Initialize();
		void Render();
		BoundingBox ComputeBoundBox();	

		//void WriteNodeToVG(CFile &fp); //写入文件;
		//		void SetCenter(float x = 0.0f, float y = 0.0f, float z = 0.0f) ;
		//		void SetCenter(Vector3 pos) ;
		//		void SetHeight(float height);
		//		Void SetWidth (float width );
		//		void SetSpeed (float speed );	
	
		// 定义新的接口变量
	public:

//		BoundingBox m_vgBoundryBox;
	
		typedef struct	tagFIRE					// Create A Structure For Particle
		{// 火花结构体 struct tagFIRE
			bool	active;					// Active (Yes/No)
			float	life;					// Particle Life
			float	fade;					// Fade Speed
			
			Vector3	color;
			
			Vector3 position;
			
			Vector3 velocity;
			
			Vector3 gravity;
			
		} tagFIRE;	
		
		tagFIRE  *m_pFire;	//  定义指针指向 动态申请的保存火焰粒子系统属性的 \
							// 二维数组所占内存空间
		TexturePtr m_pTexture;
		
		GLuint  colorIndex;
		
		GLuint  delay;
		GLfloat	xspeed;
		GLfloat	yspeed;
		GLfloat slowdown;
				
	};	//class vgFire
	

	VGK_RENDERER_OUT_DECLARE( vgFire )


}	//namespace vgCore

#endif // _VGFIRE_H_INCLUDED_