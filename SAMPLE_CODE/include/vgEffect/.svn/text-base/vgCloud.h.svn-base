
#ifndef  _VGCLOUD_H_INCLUDED_
#define  _VGCLOUD_H_INCLUDED_

//includes	
//#include <vgStableHeaders.h>							//含图形库	
#include <vgMath/vgfPrerequisites.h>		//含数学库
#include <vgEffect/vgParticle.h>

/************************************************************************/
/*    vgCloud类的描述
功能：生成一个雾景象
用法：  1，在opengl环境下实例化一个对象 vgCloud pCloud;
		2，在opengl初始化时设置参数         pCloud.Set*();
		3，在opengl初始化时执行初始化       pCloud.Init();
		4，在opengl渲染时执行				pCloud.Render();
		5, 在任何时候还可控制雪景			pCloud.Open() ;
注意：      
/************************************************************************/

namespace vgMod
{
	
	
	class    vgCloud : public vgParticle
	{
	public:
		vgCloud();
		~vgCloud();
		void Init();
		void Render();
		void Open( BOOL bfogOpen=TRUE);
		
	public:
		
		typedef struct   
		{
			GLfloat width;
			GLfloat	height;
		} CLOUDBOUND;	

		// 设置云彩的位置
	    void SetCenter(float x = 0.0f, float y = 0.0f, float z = 0.0f) ;
		void SetCenter(Vector3 pos) ;

		// 设置云彩的大小
		void SetBound( CLOUDBOUND cloudBound);
		void SetBound( GLfloat width, GLfloat height );
		
	public:

		CLOUDBOUND cloudBound;		
		BOOL	bcloudOpen;
		TexturePtr	m_pTexture;
	};
	
}	//namespace vgCore


#endif // _VGCLOUD_H_INCLUDED_