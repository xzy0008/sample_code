
#ifndef    _VGRAIN_H_INCLUDED_
#define    _VGRAIN_H_INCLUDED_
/************************************************************************/
/*    vgRain类的描述
功能：生成一个始终遍布视点范围的满天飞雪景象
用法：  1，在opengl环境下实例化一个雪景对象 vgRain prain ;
		2，在opengl初始化时设置参数         prain.SetRain();
		3，在opengl初始化时执行初始化       prain.InitRain();
		4，在opengl渲染时执行				prain.DrawRain();
		5, 在任何时候还可控制雪景			prain.SetRain()＆prain.StopRain() ;
注意：													*/
/************************************************************************/


//includes	
//#include <vgStableHeaders.h>							//含图形库	
#include <vgMath/vgfPrerequisites.h>		//含数学库
#include <vgEffect/vgParticle.h>

//namespace
namespace vgMod
{
	
	class    vgRain :  public vgParticle
	{
		VGK_RENDERER_IN_DECLARE( vgRain )
		// 构造、析构
	public:
		vgRain();
		~vgRain();

		// 从父类继承函数(关键部分)
	public:
		void Initialize();					  //  根据SetRain设置好的参数初始化各粒子属性
		void Render();					  //  雨滴粒子系统      渲染、更新、再生

//		void SetCenter(float x = 0.0f, float y = 0.0f, float z = 0.0f) ;
//		void SetCenter(Vector3 pos) ;
//		void SetHeight(float height);
//		Void SetWidth (float width );
//		void SetSpeed (float speed );
//		void SetLength(float length);
			
		// 自定义接口变量
	public:
		// struct	tagRAIN	声明雨滴粒子结构体
		typedef struct tagRAIN 
		{
			Vector3	position;
			
			Vector3 gravity;
			
			float dropSpeed;
			float lineLength;
			float rotY;
		} tagRAIN, * LPRAIN;     // struct	tagRAIN  声明雨滴粒子结构体

		tagRAIN  *m_prain;		//  指向雨滴粒子结构的指针	
		TexturePtr m_pTexture;

	}; //class	vgRain


	VGK_RENDERER_OUT_DECLARE( vgRain )

}	//namespace	vgCore

#endif //_VGRAIN_H_INCLUDED_