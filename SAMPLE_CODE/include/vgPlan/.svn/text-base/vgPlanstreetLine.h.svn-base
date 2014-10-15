
#ifndef __VGPLANSTREETLINE__
#define __VGPLANSTREETLINE__

#include <vgVector/vgvLine.h>
#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_api.h>

#include <vgKernel/vgkVec2.h>
#include <vgKernel/vgkVec3.h>
// #include <vgAutoplan/vgPlanpolygon.h>
#include <vgVector/vgvLayer.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgshape/vgshLine.h>

namespace vgPlan
{
	using vgShape::RingStruct;

	class vgPlanstreetLine 
	{
		typedef std::vector<vgShape::RingStruct> RingStructVec;

	public:
		vgPlanstreetLine();

		vgPlanstreetLine( vgVector::vgvLayer* line, float _width );

		~vgPlanstreetLine();

		OGRGeometry* getGeometry(){ return geo;}

		// void setGeometry( OGRGeometry *pp){ geo = pp; }

		void render();

		void Updategeometrypoints();

		bool setStreetGemo(OGRGeometry *pGemo, const vgKernel::Mat4& mat);

		// 根据外部的shp提供的rings设置点数组  
		bool setLinePoints(const vgShape::RingStruct& ringStruct);
		bool setLinePoints(const vgShape::RingStruct& ringStruct, const vgKernel::Mat4& matrix);

		// 根据点数组生成渲染的poly，可能是凹多边形
		bool convertLineToPoly(int width);

	private:
		void genpolyvertexs( float _width );
		
		void genheadvertex();

		void genendvertex();
	
		vgKernel::Vec3 GalPoint(vgKernel::Vec2 &V1, vgKernel::Vec2 &V2,
								vgKernel::Vec2 &V3, float &y, float _width);
	
		float mathcal1(vgKernel::Vec2 &V1, vgKernel::Vec2 &V2);
	
		void gengeometry();
	
		void genpolyvertexfromgeo();
	
		bool readWkbData( uchar* buf , int buf_size, std::vector<vgShape::RingStruct>& out_rings );
	
		void clearRecoverableData();

		void converToCoordinate( bool isopenglCoord ,  uchar* buf ,  std::vector<vgShape::RingStruct>& rings, const bool convert_to_opengl);
	
		bool readWkbDatamulti(uchar* buf , int buf_size ,  std::vector<RingStructVec>& out_polyrings );

		deque<vgKernel::Vec3> polyvecs;

		vector<vgKernel::Vec3> linevecs;

		vgKernel::Vec3 tempvec;

		// 用于渲染
		OGRGeometry* geo;
		
		// 用于计算
		OGRGeometry* m_pStreetGeometry;

		int _wkbSize;
		
		uchar* _wkbBuffer;

		bool b_updatarender;

		std::vector<vgShape::RingStruct> _rings;

	private:
		RingStructVec rings;
// 
// 	private:
// 		OGRGeometry* m_pOrigGemo;

/////////////////////////////////////////////////////////////////////////
		void genpolyvertexfrommultipolygeo();

		void genpolyvertexfrompolygeo();

		void clearmultiRecoverableData();

		bool readmultiWkbData(uchar* buf , int buf_size ,  std::vector<RingStructVec>& out_polyrings );
		
		long  readSinglePolygonData(  uchar* buf , 
			RingStructVec& out_rings  );

		void convermultiToCoordinate( bool isopenglCoord ,
			uchar* buf , std::vector<RingStructVec>& polyrings,
			const bool convert_to_opengl );
	
		void renderpoly();

		void rendermultipoly();
	
		void renderRings( RingStructVec& ringstruct );

		std::vector<RingStructVec> _polygonRings;

		bool b_multipolygen;

	};

	typedef vgKernel::SharePtr<vgPlanstreetLine> vgPlanstreetLinePtr;
}




#endif