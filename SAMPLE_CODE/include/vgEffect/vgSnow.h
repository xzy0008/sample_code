
#ifndef _VGSNOW_H_INCLUDED_
#define _VGSNOW_H_INCLUDED_
/************************************************************************/
/*    vgSnow类的描述
功能：生成一个始终遍布视点范围的满天飞雪景象
用法：  1，在opengl环境下实例化一个雪景对象 vgSnow psnow;
		2，在opengl初始化时设置参数         psnow.SetSnow();
		3，在opengl初始化时执行初始化       psnow.InitSnow();
		4，在opengl渲染时执行				psnow.DrawSnow();
		5, 在任何时候还可控制雪景			psnow.SetSnow()＆psnow.StopSnow() ;
注意：													*/
/************************************************************************/

//includes	
//#include <vgStableHeaders.h>							//含图形库	
#include <vgMath/vgfPrerequisites.h>		//含数学库
#include <vgEffect/vgParticle.h>

//namespace
namespace vgMod
{
	
	// class    vgSnow
	class    vgSnow  :  public  vgParticle
	{
		VGK_RENDERER_IN_DECLARE( vgSnow )
		// 构造、析构
	public:
		vgSnow();
		~vgSnow();
		
		// 从父类继承函数(关键部分)
	public:
		void Initialize();					  //  根据SetSnow设置好的参数初始化各粒子属性
		void Render();					  //  雪花粒子系统      渲染、更新、再生
	public:
//		vgBoundryBox ComputeBoundBox();			//计算包围盒
		
//		void Translate(Vector3 offset);			//平移
//		void Scale(Vector3 Scale);				//缩放
		
//		void WriteNodeToVG(CFile &fp);		//写入文件
//		unsigned long PositDataToNode(char *data , CFile &fp);  //从文件读取

//		void SetCenter(float x, float y, float z);		//  设置雪景中心坐标
//		void SetCenter(Vector3 pos) ;
//		void SetCount(GLuint count = PARTICLECOUNT); //  设置雪花数，雪景密度		
//		void StopSpecialEffect(BOOL m_bStopSE);					    //  控制雪景开/关？
//		void SetHeight(float height) ;
//		void SetWidth (float width ) ;
//		void SetSpeed (float speed ) ;		
		
		// 从父类继承变量
	public:
		//		vgMaterial *pMats;
		//		Vector3     m_Position; 
		//		int TYPE;
		//		vgBoundryBox m_vgBoundryBox;													// 二维数组所占内存空间
		
		//	int		  m_nParticleCount;						//粒子数
		//	BOOL      m_bStopSE;							//隐藏标记
		//	BOOL      m_bSwitchSE;							//隐藏/显示模式切换
		//	enum   CONST
		//	{
		//		PARTICLECOUNT = 2000
		//	};
		//	string m_texturename;			// 材质名字	
		//	float	m_height;
		//	float	m_width;
		//	float	m_speed;
		
		// 自定义接口变量
	public:
		// struct	SNOW	雪花粒子结构体
		typedef struct tagSNOW 
		{
			Vector3	position;		//  世界坐标系(x , y, z)				
			Vector3 rotation;		//  自转角度
		
			float dropSpeed;		//   降落速度			
			float rotSpeed;			//	 翻转速度
			
			int     nIndexTexture;  //   材质索引
		} tagSNOW, * LPSNOW;          // struct	SNOW  雪花粒子结构体
		
		tagSNOW  *m_psnow;					  //  指向雪花粒子结构的指针，将指向待申请的粒子系统的动态内存空间
		
		string m_texturename[3];			// 材质名字	
		//GLuint  m_pTexture[3];
		TexturePtr m_pTexture[3];
		
	};
	


	VGK_RENDERER_OUT_DECLARE( vgSnow )
} // namespace vgCore

#endif  // _VGSNOW_H_INCLUDED_