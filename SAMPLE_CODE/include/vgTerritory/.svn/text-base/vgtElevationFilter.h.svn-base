



#ifndef __VGTELEVATIONFILTER_H__
#define __VGTELEVATIONFILTER_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>
#include <vgTerritory/vgtElevationItem.h>
#include <vgTerritory/vgtElevationPolygon.h>

	
namespace vgTerritory {

	/**
		@date 	2008/11/04  14:55	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGT_EXPORT ElevationFilter 
		: public vgKernel::Singleton<ElevationFilter>
	{
		friend class vgKernel::Singleton<ElevationFilter>;
	private:
		ElevationFilter();

		~ElevationFilter();

	protected:

		virtual bool initialise()
		{
			return true;
		}
		virtual bool shutdown()
		{
			clearPolygons();
			return true;
		}

	public:

		virtual void reset(){};

		bool getEnableFiltering() const
		{
			return _enableFiltering;
		}

		void setEnableFiltering( const bool& enable_it )
		{
			_enableFiltering = enable_it;
		}

		bool needToSave()
		{
			return !_polygons.empty();
		}

		void pushPolygon( ElevationPolygon* poly )
		{
			_polygons.push_back( poly );
		}

		void clearPolygons();

		/**
			用于加载Elevation的时候对数据区进行操作.
			若ElevationItem已在加载状态或者为空,则发出assert警告
			若成功改变了buffer数据,则返回true
		*/
		bool doFilter( ElevationItem* item , void* buffer , const long& buffersize );

		bool doFilterPoint( ElevationItem* item , 
			float& out_height , int pos_x , int pos_y );
		/**
			对内存中的TerrainCenter中的item进行过滤.
		*/
		void doFilterInMemory();


		/**
			将数据写入vtr文件.
			注意, 这个函数会在save之后把polygon都清空
		*/
		bool doFilterAndSave();


	private:


		bool testPolygonIntersectWithItem( ElevationItem* item );

	private:

		bool _enableFiltering;

		ElevationPolygonPtrVector _polygons;

	};

	
}// end of namespace vgTerritory
	


#endif // end of __VGTELEVATIONFILTER_H__