#pragma once


#include <vgGis/vggisDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgGis3d/vggiGeometry.h>

	
namespace vgGIS3D {

	class Layer;
 
	class  VGG_EXPORT Polygon : public Geometry
	{
	public:
		Polygon( OGRFeature* feat , Layer* father );
		virtual ~Polygon()
		{
			clearRecoverableData();
		}
	
		GeomtryType getType() { return GEOMTRY_POLY; }

	public:

		virtual void clearRecoverableData();

		virtual void renderUsingDisplayList();

		virtual int getNumOfPoints();

		virtual vgKernel::Box getEnvelope3f()
		{
			return _box3d.getBoxFloat();
		}

		virtual Box3d getEnvelope3d()
		{
			return _box3d;
		}
		
		//virtual OGREnvelope getEnvelope2f()
		//{
		//	return _envelope;
		//}

		// 开始读取数据.
		virtual bool readDataFromOGRFeature();
	
		virtual void renderOnceForDisplayList();

		virtual bool testIntersect( const RayLine3d& rayline );


		virtual void renderInSelectedMode();

		virtual bool attachToTerrain();

		virtual void invalidateRendering();

		virtual std::vector<RingStruct>& getRings()
		{
			return _rings;
		}

	protected:

		static bool readWkbData( uchar* buf , int buf_size , 
			std::vector<RingStruct>& out_rings );



		// convert_to_opengl是目标coord
		static void converToCoordinate( bool& isopenglCoord , 
			uchar* buf , 
			std::vector<RingStruct>& rings, const bool& convert_to_opengl );

		// 得到shape坐标的wkb格式.注意,是3d,并且客户端负责删除
		uchar* getShapeCoordinateBuf();

		void clearDisplayListID();

	protected:

		GLuint _callListId;

		bool _isOpenGLCoordinate;

		int _wkbSize;
		uchar* _wkbBuffer;
	
		// 存储每个rings的数量和指针.
		std::vector<RingStruct> _rings;

		Box3d _box3d;
		
		//OGREnvelope _envelope;
	};
	
	
}// end of namespace  
	

 