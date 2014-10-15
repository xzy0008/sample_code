#pragma once

#include <vgGis/vggisDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgGis3d/vggiGeometry.h>

	
namespace vgGIS3D {

	class Layer;
 

	class  VGG_EXPORT MultiPoint : public Geometry
	{

	public:
		MultiPoint( OGRFeature* feat , Layer* father );
		virtual ~MultiPoint()
		{
			clearRecoverableData();
		}
	
		GeomtryType getType() { return GEOMTRY_MULTIPOINT; }

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

		

	protected:

		static bool readWkbData( uchar* buf , int buf_size , 
			std::vector<double*> points );

		static long	readSinglePointData(  uchar* buf ,double** ppPoint);

		// convert_to_opengl是目标coord
		static void converToCoordinate( bool& isopenglCoord ,
			std::vector<double*> points,
			const bool& convert_to_opengl );

		// 得到shape坐标的wkb格式.注意,是3d,并且客户端负责删除
		uchar* getShapeCoordinateBuf();

		void clearDisplayListID();

	protected:

		GLuint _callListId;

		bool _isOpenGLCoordinate;

		int _wkbSize;
		uchar* _wkbBuffer;
	
		// 存储点坐标.
		std::vector<double*> _addrPoints;
		//Vec3d	_point;

		Box3d _box3d;
		
		//OGREnvelope _envelope;
	};
	
	
}// end of namespace vgShape
	

 