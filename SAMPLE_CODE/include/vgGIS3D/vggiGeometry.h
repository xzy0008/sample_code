#pragma once


#include <vgGis/vggisDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgGis3d/vggiPrerequisite.h>

#include <gdal/ogr_feature.h>
	
namespace vgGIS3D {


	class Layer;

	enum GeomtryType
	{
		GEOMTRY_NON,
		GEOMTRY_POINT,
		GEOMTRY_MULTIPOINT,
		GEOMTRY_LINE,
		GEOMTRY_MULTILINE,
		GEOMTRY_POLY,
		GEOMTRY_MULTIPOLY,
		GEOMTRY_BUILDING_SOLID,
		GEOMTRY_TOTAL_CNT
	};

	class  VGG_EXPORT Geometry
	{
	public:
		Geometry( OGRFeature* feature, 
			Layer* father_layer );
		virtual ~Geometry()
		{
			
		}
	
		
		//------------------------------------------
		// 得到每个field的信息要
		//------------------------------------------
		//getFieldInfo
	public:
		virtual GeomtryType getType() { return GEOMTRY_NON; }

	public:
		// 拓扑关系运算
		virtual OGRBoolean 	Intersects (Geometry *geom);

		virtual OGRBoolean 	Equals (Geometry *geom);

		virtual OGRBoolean 	Disjoint (Geometry *geom);

		virtual OGRBoolean 	Touches (Geometry *geom);

		virtual OGRBoolean 	Crosses (Geometry *geom);

		virtual OGRBoolean 	Within (Geometry *geom);

		virtual OGRBoolean 	Contains (Geometry *geom);

		virtual OGRBoolean 	Overlaps (Geometry *geom);

		virtual OGRGeometry* getBoundary ();
			
		virtual double 	Distance (Geometry *geom);
		
		virtual OGRGeometry * 	ConvexHull () ;

		virtual OGRGeometry * 	Buffer (double dfDist, int nQuadSegs=30) ;
	
		virtual OGRGeometry * 	Intersection (Geometry *geom) ;
			
		virtual OGRGeometry * 	Union (Geometry *geom) ;

		virtual OGRGeometry * 	Difference (Geometry *geom) ;

		virtual OGRGeometry * 	SymmetricDifference (Geometry *geom) ;

	public:
	
		// 使用display list来创建
		virtual void renderUsingDisplayList() = 0;


		virtual OGRFeaturePtr getOGRFeaturePtr();

		// 注意, 客户端负责删除.
		virtual OGRFeature* getOGRFeature();

		// 注意, 参数要客户端删除.
		virtual void setFeature( OGRFeature* feature );

		virtual int getNumOfPoints() = 0;

		virtual vgKernel::Box getEnvelope3f() = 0;

		virtual Box3d getEnvelope3d() = 0;

		// 渲染一次. 为了创建display list
		virtual void renderOnceForDisplayList() = 0;

		// 通过OGRFeature来读取数据
		virtual bool readDataFromOGRFeature() = 0;


		// 删除临时数据.
		// 注意, 可以再读取的.
		virtual void clearRecoverableData() = 0;

		virtual bool testIntersect( const RayLine3d& rayline ) = 0;

		virtual void renderInSelectedMode() = 0;

		virtual bool attachToTerrain() = 0;

		virtual void invalidateRendering() = 0;

		virtual Layer* getFatherLayer()
		{
			assert( _fatherLayer != NULL );
			return _fatherLayer;
		}

		virtual DrawingDescriptor* getDrawingDescriptor()
		{
			return &_drawing;
		}

		//virtual OGREnvelope getEnvelope2f() = 0;

	protected:
	
		long _ogrFeatureFID;
		Layer* _fatherLayer;
	
		OGRFeature *m_pFeature;

		DrawingDescriptor _drawing;
	};


	typedef std::vector<Geometry*> GeometryPointerVec;


	
}// end of namespace vgShape
	

