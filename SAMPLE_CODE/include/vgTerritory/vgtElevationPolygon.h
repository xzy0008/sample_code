




#ifndef __VGTELEVATIONPOLYGON_H__
#define __VGTELEVATIONPOLYGON_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkVec2.h>
#include <vgTerritory/vgtElevationBound.h>
#include <vgTerritory/vgtElevationItem.h>
#include <vgKernel/vgkSharePtr.h>

	
namespace vgTerritory {


	using namespace vgKernel;

	typedef std::vector<Vec2> Vec2Vector;
	typedef SharePtr< Vec2Vector > Vec2VectorPtr;

	/**
		@date 	2008/11/04  15:25	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGT_EXPORT ElevationPolygon
	{
	public:
		// 注意,一旦构造,本类负责点的释放.
		// 还要注意!!输入的vertices是已经除以cellsize之后的值!
		ElevationPolygon( Vec2Vector* vertices , float height )
		{
			assert( vertices != NULL );
			_polyPoints = vertices;

			_bound = calculateBound( vertices );

			_height = height;
		}
		~ElevationPolygon()
		{
			if ( _polyPoints != NULL )
			{
				delete _polyPoints;
				_polyPoints  =NULL;
			}
		}
	
	public:
		


		bool testIntersectWithItem( ElevationItem* item );

		/**
			过滤item, 不管是否是在内存中, 直接判断是否相交,然后对buffer区域
			进行修改保存操作.
			成功过滤,返回为true.反之,返回false
		*/
		bool filterElevationItem( ElevationItem* item , 
			void* buffer , const long& buffersize );

		/**
			通过某一个点来过滤.
			pos_x 和pos_z分别是在图中的位置.
		*/
		bool filterElevationItemPoint( ElevationItem* item , 
			float& out_height , int pos_x , int pos_y );

	private:

		/**
			得到下一级的polygon
		*/
		//ElevationPolygon* getNextLevelPolygon()
		//{
		//	Vec2Vector* tmp = new Vec2Vector;

		//	for ( int i = 0 ; i < _polyPoints->size() ; ++ i )
		//	{
		//		tmp->push_back( (*_polyPoints)[i] );
		//	}

		//	return new ElevationPolygon( tmp );
		//}

		Vec2Vector* getCopyAndMappingPoints( ElevationItem* item );

		Vec2Vector* getCopyOfPoints()
		{
			Vec2Vector* ret = new Vec2Vector;
			ret->assign( _polyPoints->begin() , _polyPoints->end() );
			
			return ret;
		}

		static ElevationBound calculateBound( const Vec2Vector* const vertices );

	private:
	

		ElevationBound _bound;
		
		Vec2Vector* _polyPoints;

		float _height;
	
		static ElevationBound s_uvTestBound;
	};

	typedef std::vector<ElevationPolygon*> ElevationPolygonPtrVector;
	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTELEVATIONPOLYGON_H__