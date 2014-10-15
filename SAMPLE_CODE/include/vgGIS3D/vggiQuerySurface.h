#pragma once


#include <vgGis/vggisDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkInputSystem.h>


#include <vgGis3d/vggiLayer.h>

class	OGRPolygon;
class	OGRGeometry;


namespace vgGIS3D {

	//class TerrainManager;

	using namespace vgKernel;


	typedef std::vector< Vec3 > Vec3Vector;

 

	class VGG_EXPORT vgshQuerySurface	: public vgKernel::InputHandler
	//: public vgTerritory::CutSurfaceLevelling 
	{
	public:
		vgshQuerySurface(QueryType qType = QUERY_NONE, 
			String keyFieldName = "Floor");
		virtual ~vgshQuerySurface();
	
	
		virtual void OnMouseMove(UINT nFlags, CPoint position);
		virtual void OnLButtonDown(UINT nFlags, CPoint position);
		virtual void OnLButtonDbClick(UINT nFlags, CPoint position);
		
		virtual void OnLButtonUp(UINT nFlags, CPoint position) {}
//		virtual void OnRBottonDown(UINT nFlags, CPoint position){}
//		virtual void OnMouseWheel(UINT nFlags, short zDelta, CPoint pt){}
//		virtual void OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
// 		virtual void OnRBottonDown(UINT nFlags, CPoint position) ;

		void setDefault();

		void render();
		virtual	void renderExtra();

		void	onAnalysizeRatio(vgKernel::Polygon2D	*poly);
		float	calculateRatio(OGRPolygon* pPolySelector,
			Layer*	pLayer);

		float getAreaIntersected(OGRGeometry* poOGRGeo,
			Geometry*	pGeo, bool	bMultiWeight = false);
		

		void	setQueryType(QueryType qType);
		QueryType	getQueryType();

		void	setKeyFieldName(String fieldName);
		String	getFieldIndex();

	
	protected:
		QueryType	_queryType;

	/**
		@author  	lss
		@´æ´¢Â¥²ãÊýÄ¿µÄ×Ö¶Îname 
	*/
		String	_keyFieldName;

	protected://private:

		static void drawPoint( const Vec3& point );
		static void drawLines( const Vec3Vector& points , const Vec3& mousevec ,bool btm);
		static void drawHeight( Vec3Vector* points );
		//static Vec3 get3dVecFrom2d( const CPoint& point_2d );

	protected://private:

		Vec3 _mouseVec;

		Vec3Vector _clickPoints;

		Vec3Vector* _heightRender;

		//TerrainManager* _terrainMgr;

		//ElevationBound _sceneBound;
		//  [11/10/2008 zhu]
	public:
		double **rect;
		bool btm;
		float avh;
		GLUtesselator *basetess;
		int getpointssize(){return _clickPoints.size();}
	};
	
	
}// end of namespace  
	


 