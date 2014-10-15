


#ifndef __VGSHMULTIPOLYGON_H__
#define __VGSHMULTIPOLYGON_H__



#include <vgShape/vgshDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgShape/vgshPolygon.h>

	
namespace vgShape {

	class Layer;
	/**
		@date 	2009/02/17  16:25	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGSH_EXPORT MultiPolygon : public Geometry
	{
	private:
		struct RingStruct
		{
			RingStruct( int points , double* addr )
			{
				_numPoints = points;
				_pointsBeginAddr = addr;
			}
			int _numPoints;
			double* _pointsBeginAddr;
		};

		typedef std::vector<RingStruct> RingStructVec;

	public:
		MultiPolygon( OGRFeature* feat , Layer* father )
			: Geometry( feat , father )
		{
			_wkbSize = -1;
			_wkbBuffer = NULL;
			_isOpenGLCoordinate = false;
			_callListId = 0;
			_box3d = Box3d::NULL_BOX;
		}
		virtual ~MultiPolygon()
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

	private:

		//bool readWkbData();

		static bool readWkbData( uchar* buf , int buf_size , 
			std::vector<RingStructVec>& out_polyrings );

		// 返回的是读取的字节数
		// 若返回-1, 表示出错
		static long readSinglePolygonData( uchar* buf , 
			RingStructVec& out_rings );

		// convert_to_opengl是目标coord
		static void converToCoordinate( bool& isopenglCoord , 
			uchar* buf , 
			std::vector<RingStructVec>& polyrings, const bool& convert_to_opengl );


		// 渲染单个的ring. 私用
		void renderRings( RingStructVec& ringstruct );

		// 得到shape坐标的wkb格式.注意,是3d,并且客户端负责删除
		uchar* getShapeCoordinateBuf();

		void clearDisplayListID();

	protected:
		//OGREnvelope _envelope;

	private:

		GLuint _callListId;

		bool _isOpenGLCoordinate;

		int _wkbSize;
		uchar* _wkbBuffer;
	
		// 存储每个polygon rings的数量和指针.
		std::vector<RingStructVec> _polygonRings;

		Box3d _box3d;

	};
	
	
}// end of namespace vgShape
	


#endif // end of __VGSHMULTIPOLYGON_H__