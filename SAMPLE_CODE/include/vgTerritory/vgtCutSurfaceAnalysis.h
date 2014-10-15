


#ifndef __VGTCUTSURFACEANALYSIS_H__
#define __VGTCUTSURFACEANALYSIS_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkInputSystem.h>
#include <vgTerritory/vgtElevationBound.h>

#include "vgTerritory/dlgCutSuface.h"	

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
	class  VGT_EXPORT CutSurfaceAnalysis : public vgKernel::InputHandler
	{
	public:
		CutSurfaceAnalysis();
		virtual ~CutSurfaceAnalysis();
	
	
		virtual void OnMouseMove(UINT nFlags, CPoint position);
		virtual void OnLButtonDown(UINT nFlags, CPoint position);
		virtual void OnLButtonUp(UINT nFlags, CPoint position) {}
		virtual void OnLButtonDbClick(UINT nFlags, CPoint position);


		void render();

	private:

		static void drawPoint( const Vec3& point );
		static void drawLines( const Vec3Vector& points , const Vec3& mousevec );
		static void drawHeight( Vec3Vector* points );
		static Vec3 get3dVecFrom2d( const CPoint& point_2d );

	private:

		Vec3 _mouseVec;
		

		Vec3Vector _clickPoints;

		Vec3Vector* _heightRender;

		TerrainManager* _terrainMgr;


		ElevationBound _sceneBound;
	public:
		CdlgCutSuface *m_dlgCutSurf;

	};

	
}// end of namespace vgTerritory
	


#endif // end of __VGTCUTSURFACEANALYSIS_H__