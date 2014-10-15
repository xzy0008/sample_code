


#ifndef __VGTCUTSURFACEVISIBILITY2_H__
#define __VGTCUTSURFACEVISIBILITY2_H__



#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkInputSystem.h>
#include <vgTerritory/vgtElevationBound.h>
#include <vgKernel/vgkSegment3.h>
#include "vgTerritory/Dlg_VisibleAnalyst.h"
	
namespace vgTerritory {

#define  VGT_VISIBILITY_DRAW_HEIGHT	0


	class TerrainManager;

	using namespace vgKernel;


	//typedef std::vector< Vec3 > Vec3Vector;

	/**
		@date 	2008/10/31  9:10	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGT_EXPORT CutSurfaceVisibility2 : public vgKernel::InputHandler
	{
	public:
		CutSurfaceVisibility2();
		virtual ~CutSurfaceVisibility2();
	
	
		virtual void OnMouseMove(UINT nFlags, CPoint position);
		virtual void OnLButtonDown(UINT nFlags, CPoint position);

		
		virtual void OnLButtonUp(UINT nFlags, CPoint position) {}
		virtual void OnLButtonDbClick(UINT nFlags, CPoint position);


		void render();

	private:

		bool testRenderersIntersect( const Segment3& seg );


		static void drawPoint( const Vec3& point );
		static void drawLines( const Vec3Vector& points , const Vec3& mousevec );
		static void drawHeight( Vec3Vector* points );
		static Vec3 get3dVecFrom2d( const CPoint& point_2d );

		/*static */void alert( const Vec3& p1 , const Vec3& p2 , const bool& visible );

	private:

		Vec3 _mouseVec;
		
		Vec3Vector _clickPoints;

		Vec3Vector* _heightRender;

		TerrainManager* _terrainMgr;

		ElevationBound _sceneBound;

		bool bFirst;
	public:
		Vec3Vector vecLinePoints;
		CDlg_VisibleAnalyst *pDlgVisiAna;
		std::vector <CString> vecDisVisiName;

	};
	
}// end of namespace vgTerritory
		


#endif // end of __VGTCUTSURFACEVISIBILITY2_H__