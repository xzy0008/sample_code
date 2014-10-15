




#ifndef __VGSHMULTILINE_H__
#define __VGSHMULTILINE_H__



#include <vgShape/vgshDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgShape/vgshDefinition.h>
#include <vgShape/vgshGeometry.h>
	
namespace vgShape {

	class Layer;
	
	/**
		@action		creation
		@date 		2009/03/20  10:13	
		@author  	lss
	
		@brief 	
	
		@see    
		*/

	class  VGSH_EXPORT MultiLine : public Geometry
	{
// 		struct RingStruct
// 		{
// 			RingStruct( int points = 0, double* addr = NULL)
// 			{
// 				_numPoints = points;
// 				_pointsBeginAddr = addr;
// 			}
// 			int _numPoints;
// 			double* _pointsBeginAddr;
// 		};
		typedef std::vector<RingStruct> RingStructVec;

	public:
		MultiLine( OGRFeature* feat , Layer* father );
		virtual ~MultiLine()
		{
			clearRecoverableData();
		}
	

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

		virtual	RingStructVec& getRings()
		{
			return _rings;
		}

	protected:

		static bool readWkbData( uchar* buf , int buf_size , 
			RingStructVec& out_rings );

		// 返回的是读取的字节数
		// 若返回-1, 表示出错
		static long readSingleLineData( uchar* buf , 
			RingStruct& out_ring );

		// convert_to_opengl是目标coord
		static void converToCoordinate( bool& isopenglCoord , 
			RingStructVec& rings, const bool& convert_to_opengl );

		// 得到shape坐标的wkb格式.注意,是3d,并且客户端负责删除
		uchar* getShapeCoordinateBuf();

		void clearDisplayListID();

	protected:

		GLuint _callListId;

		bool _isOpenGLCoordinate;

		int _wkbSize;
		uchar* _wkbBuffer;
	
		// 存储每个rings的数量和指针.
		RingStructVec	_rings;

		Box3d _box3d;
		
		//OGREnvelope _envelope;
	};
	
	
}// end of namespace vgShape
	


#endif // end of __VGSHMULTILINE_H__