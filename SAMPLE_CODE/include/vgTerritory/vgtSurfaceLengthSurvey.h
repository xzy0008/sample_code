


#ifndef __VGTSURFACE_LENGTH_SURVEY_H__
#define __VGTSURFACE_LENGTH_SURVEY_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkInputSystem.h>
#include <vgTerritory/vgtElevationBound.h>


namespace vgTerritory {

	class TerrainManager;

	using namespace vgKernel;


	//typedef std::vector< Vec3 > Vec3Vector;

	/**
		@date 	2009/12/23  19:44	
		@author  FengYK
	
		@brief 	
	
		@see    
	*/
	class  VGT_EXPORT SurfaceLengthSurvey : public vgKernel::InputHandler
	{
	public:
		SurfaceLengthSurvey();
		virtual ~SurfaceLengthSurvey();
	
	
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

	};

	
}// end of namespace vgTerritory
	


#endif // end of __VGTSURFACE_LENGTH_SURVEY_H__