#pragma once
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkInputSystem.h>
#include <vgTerritory/vgtElevationBound.h>
#include <vgKernel/vgkPlane.h>
#include <vgTerritory/vgtTerrainManager.h>

namespace vgPlan
{

	using namespace vgKernel;
	using namespace vgTerritory;

	typedef std::vector< Vec3 > Vec3Vector;

	class AreaSelector : public vgKernel::InputHandler
	{
	public:
		AreaSelector();
		virtual ~AreaSelector();


		virtual void OnMouseMove(UINT nFlags, CPoint position);
		virtual void OnLButtonDown(UINT nFlags, CPoint position);
		virtual void OnLButtonUp(UINT nFlags, CPoint position) {}
		virtual void OnLButtonDbClick(UINT nFlags, CPoint position);
		virtual void OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
		virtual void OnRBottonDown(UINT nFlags, CPoint position) ;

		virtual void OnKeyDown(int keyCode);

		Vec3Vector getResultVec() { return _resultVec; }

		void render();
		void renderExtra();

	protected://private:

		static void drawPoint( const Vec3& point );
		static void drawLines( const Vec3Vector& points , const Vec3& mousevec ,bool btm);
		static void drawHeight( Vec3Vector* points );
		static Vec3 get3dVecFrom2d( const CPoint& point_2d );

	protected://private:

		Vec3 _mouseVec;

		Vec3Vector _clickPoints;

		Vec3Vector* _heightRender;
		
		Vec3Vector _resultVec;

		//TerrainManager* _terrainMgr;

		ElevationBound _sceneBound;
		//  [11/10/2008 zhu]
	public:
		double **rect;
		bool btm;
		float avh;
		GLUtesselator *basetess;

		int getpointssize(){return _clickPoints.size();}

	};

}