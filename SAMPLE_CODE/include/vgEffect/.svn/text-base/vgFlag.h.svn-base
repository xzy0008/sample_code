//vgFlag.h

//#include <windows.h>
#ifndef  _VGFLAG_H_INCLUDED_
#define  _VGFLAG_H_INCLUDED_

//includes	
//#include <vgStableHeaders.h>							//含图形库	
#include <vgMath/vgfPrerequisites.h>		//含数学库
#include <vgEffect/vgParticle.h>

//defines
#define XN 15  //旗帜在X方向的节点数
#define YN 10  //旗帜在Y方向的节点数


//namespace
namespace vgMod
{
	//const CategoryType NODE_TYPE_FLAG	= 34;

	//////////////////////////////////////////////////////////////////////////
	// vgFlag 旗帜类定义
	class vgFlag  : public vgParticle
	{
		VGK_RENDERER_IN_DECLARE( vgFlag )
		// 构造、析构
	public:
		vgFlag();
		~vgFlag();

		// 从父类继承函数
	public:
		void Initialize(void);		
		void Render(void);
		BoundingBox ComputeBoundBox();

		void UpdatePos();

//		void SetCenter(float x = 0.0f, float y = 0.0f, float z = 0.0f) ;
//		void SetCenter(Vector3 pos) ;
//		void SetHeight(float height);
//		Void SetWidth (float width );
		
		// 自定义接口函数
	private:	
		void update();
		void render2();
	
		void fixlen(Vector3 a,Vector3 b,float L,Vector3 *d);
		void straighten(Vector3 a,Vector3 b,
			Vector3 c,Vector3 *d1,Vector3 *d2,Vector3 *d3);
		void strtangl(Vector3 a,Vector3 b,
			Vector3 c,Vector3 *d1,Vector3 *d2,Vector3 *d3);
		void wind(Vector3 w,Vector3 n,Vector3 *dd);

		// 自定义接口变量
	public:
		float	deltaX;
		float	deltaY;
//		BoundingBox m_vgBoundryBox;

	public:
		void ReadDataFromSc(CFile &fp);
			
	protected:
		Vector3 cloth[XN][YN];
		Vector3 normal[XN][YN];
		Vector3 d[XN][YN];
		Vector3 dd[XN][YN];
		Vector3 w;
//		float t;
		

	};	//class vgFlag
	
	VGK_RENDERER_OUT_DECLARE( vgFlag )
	
}	//namespace vgCore

#endif // _VGFLAG_H_INCLUDED_
