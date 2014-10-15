


#ifndef __VGTCUTSURFACELEVELLING_H__
#define __VGTCUTSURFACELEVELLING_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkInputSystem.h>
#include <vgTerritory/vgtElevationBound.h>
#include <vgKernel/vgkPointInPolygon.h>
#include <vgKernel/vgkRenderer.h>

namespace vgTerritory {

	class TerrainManager;

	using namespace vgKernel;


	//typedef std::vector< Vec3 > Vec3Vector;

	/**
	@date 	2008/10/31  9:10	
	@author  leven

	@brief 	

	@see    
	*/
	class  VGT_EXPORT CutSurfaceLevelling : public vgKernel::InputHandler
	{
	public:
		CutSurfaceLevelling();
		virtual ~CutSurfaceLevelling();


		virtual void OnMouseMove(UINT nFlags, CPoint position);
		virtual void OnLButtonDown(UINT nFlags, CPoint position);
		virtual void OnLButtonUp(UINT nFlags, CPoint position) {}
		virtual void OnLButtonDbClick(UINT nFlags, CPoint position);
		virtual void OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
		virtual void OnRBottonDown(UINT nFlags, CPoint position) ;

		virtual void OnKeyDown(int keyCode);

		void render();
		void renderExtra();

		bool getFlagButtonDown();
		float getHeight();

	protected://private:

		static void drawPoint( const Vec3& point );
		static void drawLines( const Vec3Vector& points , const Vec3& mousevec ,bool btm);
		static void drawHeight( Vec3Vector* points );
		static Vec3 get3dVecFrom2d( const CPoint& point_2d );

	protected://private:

		Vec3 _mouseVec;

		Vec3Vector _clickPoints;

		Vec3Vector* _heightRender;

		TerrainManager* _terrainMgr;

		ElevationBound _sceneBound;
		//  [11/10/2008 zhu]
	public:
		double **rect;
		bool btm;
		float avh;
		GLUtesselator *basetess;
		int getpointssize(){return _clickPoints.size();}

		vgKernel::RendererQueue* getNeedLevellingRenderer(Vec3Vector _clickPoints);

	};


}// end of namespace vgTerritory



#endif // end of __VGTCUTSURFACELEVELLING_H__