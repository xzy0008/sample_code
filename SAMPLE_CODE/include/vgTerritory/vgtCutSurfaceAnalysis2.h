


#ifndef __VGTCUTSURFACEANALYSIS2_H__
#define __VGTCUTSURFACEANALYSIS2_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkInputSystem.h>
#include <vgTerritory/vgtElevationBound.h>
#include <vgKernel/vgkPlane.h>

	
namespace vgTerritory {

	class TerrainManager;

	using namespace vgKernel;


	//typedef std::vector< Vec3 > Vec3Vector;

	/**
		@date 	2008/10/31  9:10	
		@author  leven
	
		@brief 	要注意,要确认在opengl环境卸载之前进行析构函数.
	
		@see    
	*/

	enum sectionType	//剖面的类型
	{
		SECT_VERTICAL,	//垂直剖面分析
		SECT_HORIZONTAL,	//水平剖面分析
		SECT_INCLINE,	//倾斜剖面分析
		SECT_NONE,		//无
	};

	class  VGT_EXPORT CutSurfaceAnalysis2 : public vgKernel::InputHandler
	{
	public:
		CutSurfaceAnalysis2();
		virtual ~CutSurfaceAnalysis2();
	
	
		virtual void OnMouseMove(UINT nFlags, CPoint position);
		virtual void OnLButtonDown(UINT nFlags, CPoint position);
		virtual void OnLButtonUp(UINT nFlags, CPoint position) {}
		virtual void OnLButtonDbClick(UINT nFlags, CPoint position);
		virtual void OnRBottonDown(UINT nFlags, CPoint position);

		void render();

		float* getUserClipPlaneParam()
		{
			if ( _plane == NULL )
			{
				return NULL;
			}

			return _clipPlaneParam;
		}

	private:

		static void drawPoint( const Vec3& point );
		static void drawLines( const Vec3Vector& points , const Vec3& mousevec );
		static void drawHeight( Vec3Vector* points );
		static Vec3 get3dVecFrom2d( const CPoint& point_2d );


	private:

		Vec3 _mouseVec;
		

		Vec3Vector _clickPoints;


		TerrainManager* _terrainMgr;

		ElevationBound _sceneBound;

		vgKernel::Plane* _plane;

		TerrainGpuProgram* _gpuProgram;

		float _clipPlaneParam[4];

	public:
		sectionType _cutSufSecType;

		void setCutSurfAnaType( sectionType secType ){ _cutSufSecType = secType; }
		sectionType getCutSurfAnaType(){ return _cutSufSecType; }

	};
	
	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTCUTSURFACEANALYSIS2_H__