


#ifndef __VGTSURFACE_AREA_SURVEY_H__
#define __VGTSURFACE_AREA_SURVEY_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkInputSystem.h>
#include <vgTerritory/vgtElevationBound.h>
#include <vgKernel/vgkPointInPolygon.h>
#include <vgKernel/vgkRenderer.h>

#include "vgTerritory/dlgSetCellSize.h"

namespace vgTerritory {

	class TerrainManager;

	using namespace vgKernel;


	//typedef std::vector< Vec3 > Vec3Vector;

	/**
	@date 	2009-12-24  9:50	
	@author  FengYK

	@brief 	地形表面积测量

	@see    
	*/
	class  VGT_EXPORT SurfaceAreaSurvey : public vgKernel::InputHandler
	{
	public:
		SurfaceAreaSurvey();
		virtual ~SurfaceAreaSurvey();


		virtual void OnMouseMove(UINT nFlags, CPoint position);
		virtual void OnLButtonDown(UINT nFlags, CPoint position);
		virtual void OnLButtonUp(UINT nFlags, CPoint position) {}
		virtual void OnLButtonDbClick(UINT nFlags, CPoint position);
		virtual void OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
		virtual void OnRBottonDown(UINT nFlags, CPoint position) ;

		virtual void OnKeyDown(int keyCode);

		void render();
		void renderExtra();
		void renderSelectedArea();
		//海伦公式计算三角形的面积
		float hailun(vgKernel::Vec3 a,vgKernel::Vec3 b,vgKernel::Vec3 c);

		bool getFlagButtonDown();

	protected://private:

		static void drawPoint( const Vec3& point );
		static void drawLines( const Vec3Vector& points , const Vec3& mousevec ,bool btm);
		static void drawHeight( Vec3Vector* points );
		static Vec3 get3dVecFrom2d( const CPoint& point_2d );

		static void drawPolygon( Vec3Vector* points );

	protected://private:

		Vec3 _mouseVec;

		Vec3Vector _clickPoints;

		Vec3Vector* _heightRender;
		Vec3Vector* _polyPoint;

		Vec3Vector _pointsInSelectArea;
		Vec3Vector _pointsInSelectArea1;
		Vec3Vector _pointsInSelectArea2;
		Vec3Vector _pointsInSelectArea3;

		//TerrainManager* _terrainMgr;

		ElevationBound _sceneBound;

	public:
		bool btm;					//判断鼠标是否按下
		float totalArea;
		GLuint _displayListID;

		int getpointssize(){return _clickPoints.size();}

		vgKernel::RendererQueue* getNeedSurveyingAreaRenderer(Vec3Vector _clickPoints);
	public:
		CdlgSetCellSize *m_dlgSetCellSize;
		
	};


}// end of namespace vgTerritory



#endif // end of __VGTSURF_AREA_SURVEY_H__