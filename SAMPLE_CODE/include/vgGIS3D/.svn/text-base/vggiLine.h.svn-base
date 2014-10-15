#pragma once

#include <vgGis/vggisDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgGis3d/vggiGeometry.h>
#include <vgKernel/vgkRay.h>
	
namespace vgGIS3D {



	class Layer;
 
	class  VGG_EXPORT LineString : public Geometry
	{
	protected:
// 		struct RingStruct
// 		{
// 			RingStruct( int points = 0, double* addr = NULL)
// 			{
// 				_numPoints = points;
// 				_pointsBeginAddr = addr;
// 			}
// 			int _numPoints;
// 			double* _pointsBeginAddr; //x y z
// 		};
		struct aRound_Point			//用于存储由每个线段求出的平面的四个点
		{
			vgKernel::Vec3 arPoint1;
			vgKernel::Vec3 arPoint2;
			vgKernel::Vec3 arPoint3;
			vgKernel::Vec3 arPoint4;

		};

	public:
		LineString( OGRFeature* feat , Layer* father );
		virtual ~LineString()
		{
			clearRecoverableData();
		}
	
		GeomtryType getType() { return GEOMTRY_LINE; }

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

		virtual const RingStruct& getRing()
		{
			return _ring;
		}
	public:

		vgKernel::Box getPipeLineEnvelope3f(double pipeRadius)
		{
			return _box3d.getPipeLineBoxFloat(pipeRadius);
		}

		// 测试 ray 是否穿过三角形
		virtual bool tri_Interect( const vgKernel::Ray& ray, vgKernel::Vec3 pt1, vgKernel::Vec3 pt2, vgKernel::Vec3 pt3 );

		virtual void setIntersectDis();		
	protected:

		static bool readWkbData( uchar* buf , int buf_size , 
			RingStruct& out_ring );



		// convert_to_opengl是目标coord
		static void converToCoordinate( bool& isopenglCoord , 
			RingStruct& ring, const bool& convert_to_opengl );

		// 得到shape坐标的wkb格式.注意,是3d,并且客户端负责删除
		uchar* getShapeCoordinateBuf();

		void clearDisplayListID();
		
	protected:

		GLuint _callListId;

		bool _isOpenGLCoordinate;

		int _wkbSize;
		uchar* _wkbBuffer;
	public:
		// 存储每个rings的数量和指针.
		RingStruct	_ring;

		Box3d _box3d;

		OGRGeometry* _envelope;
		//OGREnvelope _envelope;

		//vgKernel::Vec3 tempPt1;
		//vgKernel::Vec3 tempPt2;
		//vgKernel::Vec3 tempPt3;
		//vgKernel::Vec3 tempPt4;

		//----------------------------------------------
		// Edit By FengYK @2010-01-27 15:59
		// 使用"测试射线和每条线段的包围盒相交"的方法判断点选
		//----------------------------------------------
		//std::vector<aRound_Point> aroundingPoints;
		float m_dis;

	};
	
	
}// end of namespace  
	
 
