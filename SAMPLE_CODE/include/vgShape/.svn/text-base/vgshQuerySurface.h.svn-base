


#ifndef __VGSHQUERYSURFACE_H__
#define __VGSHQUERYSURFACE_H__



#include <vgShape/vgshDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkInputSystem.h>


#include <vgShape/vgshLayer.h>

class	OGRPolygon;
class	OGRGeometry;


namespace vgShape {

	//class TerrainManager;

	using namespace vgKernel;


	typedef std::vector< Vec3 > Vec3Vector;

	/**
		@date 	2009-2-17 9:35:37	
		@author  lss
	
		@brief 	
	
		@see    
	*/

	class VGSH_EXPORT vgshQuerySurface	: public vgKernel::InputHandler
	//: public vgTerritory::CutSurfaceLevelling 
	{
	public:
		vgshQuerySurface(vgShape::QueryType qType = vgShape::QUERY_NONE, 
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
			vgShape::Layer*	pLayer);

		float getAreaIntersected(OGRGeometry* poOGRGeo,
			vgShape::Geometry*	pGeo, bool	bMultiWeight = false);
		

		void	setQueryType(vgShape::QueryType qType);
		vgShape::QueryType	getQueryType();

		void	setKeyFieldName(String fieldName);
		String	getFieldIndex();

	
	protected:
		vgShape::QueryType	_queryType;

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
	
	
}// end of namespace vgShape
	


#endif // end of __VGSHQUERYSURFACE_H__