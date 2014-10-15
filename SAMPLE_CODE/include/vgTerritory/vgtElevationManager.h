


#ifndef __VGTERRITORY_TELEVATIONMANAGER_H__
#define __VGTERRITORY_TELEVATIONMANAGER_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgTerritory/vgtElevation.h>
#include <vgTerritory/vgtElevationItem.h>
#include <vgTerritory/vgtFileHandleVtr.h>
#include <vgImage/vgiFileHandleVgi.h>
#include <vgTerritory/vgtElevationBound.h>
#include <vgKernel/vgkSingleton.h>

	
namespace vgTerritory {

	using namespace vgImage;

	/**
		@date 	2008/09/08  21:01	
		@author  leven
	
		@brief 	对高度图进行管理.
		管理FileHandleVtr的生命周期
		FileHandleVgi的生命周期还是归ImageManger管理.
		保存的时候只要从ElevationManager中提取出高度图的纹理名称
		队列然后保存到一个vgi文件中即可.


		由于维护一个ElevationItemMap列表,而每个
		ElevationItem依赖于GpuProgram
		所以它的删除要在TerrainManager之前.
	
		@see    
	*/
	class  VGT_EXPORT ElevationManager : 
		public vgKernel::Singleton<ElevationManager>
	{
		friend class vgKernel::Singleton<ElevationManager>;
	private:
		ElevationManager();

	public:
		~ElevationManager();

	protected:
		virtual bool initialise()
		{
			return true;
		}
		virtual bool shutdown()
		{
			assert( _emptyElevItem  == NULL );
			assert( _vtrFileHandles.empty() == true );
			return true;
		}

	public:

		virtual void reset(){};

		bool clearData();


		FileHandleVtr* openVtrFile( const String& vtrfilename );

		

		bool uninitBeforeOpenGLDestroy()
		{	
			return clearData();
		}

		/**
			IoRequest的接口
		*/
		ElevationItem* getElevationItem( const String& itemname ,
			const bool& return_empty_item );

		ElevationItem* getElevationItem( const long& layer , 
			const long& chunkx, const long& chunkz , 
			const bool& return_empty_item );

		ElevationItem* getEmptyElevationItem()
		{
			assert( _emptyElevItem != NULL );
			return _emptyElevItem;
		}
		/**
			注意,客户端负责删除
			当level = -1 时,返回所有的ElevationItem队列.
		*/
		ElevationItemVector* getElevationItemsByLevel( const long& level );

		/**
			对所有的item进行addref, 以全部载入
		*/
		bool addRefToAllElevationItems();

		///**
		//	 客户端不能删除或者对其进行操作
		//*/
		//ElevationItemMap* getElevationItemMap()
		//{
		//	assert( _elevItems != NULL );
		//	return _elevItems;
		//}

		FileHandleVtr* getMainFileHandleVtr()
		{
			assert( _mainVtrFileHandle != NULL );
			return _mainVtrFileHandle;
		}

		vgImage::FileHandleVgi* getMainFileHandleVgi()
		{
			assert( _mainVgiFilehandle != NULL );
			return _mainVgiFilehandle;
		}

		/**
			 得到当前scene的bound.注意,是whole
			 比如, 整个场景是32768*32768的网格,这里返回的是
			 32768*cellsize的大小.
			 若要取实际的bound,请参考getValidSceneBound
			 原点是( 0.0f , 0.0f )
			 最大点是( out_x,  out_z )
		*/
		bool getWholeSceneBound( float& out_x , float& out_z );

		bool getValidSceneBound( 
			float& out_min_x , float& out_min_z , float& out_max_x , float& out_max_z );
		ElevationBound getValidSceneBound();

		/**
			通过bound得到相交的items.
			若无相交,返回为空.
		*/
		ElevationItemVectorPtr getIntersectedItemsByBound( 
			const ElevationBound& bound );

		/**
			通过polygon得到相交的items
			若无相交，返回为空
		*/
		ElevationItemVectorPtr getIntersectedItemsByPolygon(
			const Vec3Vector* pointsVec );


		vgImage::FileHandleVgi* openVgiFile( const String& vgifilename );

	private:

		// 特殊的vgi载入
		// 考虑到一半地形的纹理没有复用的需要
		bool importImageFileOnly( const String& VgiPathName);

		

		void insertToVtrMap( FileHandleVtr* vtrhandle )
		{
			FileHandleVtrPtrMapInsertRes insertres = 
				_vtrFileHandles.insert( std::make_pair( vtrhandle->getFilePath() , vtrhandle ) );

			assert( insertres.second == true );
		}

		bool calculateValidSceneBound();

	private:

		float _validSceneBoundMinX;
		float _validSceneBoundMinZ;
		float _validSceneBoundMaxX;
		float _validSceneBoundMaxZ;

		FileHandleVtr* _mainVtrFileHandle;

		FileHandleVtrPtrMap _vtrFileHandles;

		FileHandleVgi* _mainVgiFilehandle;

		ElevationItem* _emptyElevItem;
	};

	
	
}// end of namespace vgTerritory
	


#endif // end of __VGTERRITORY_TELEVATIONMANAGER_H__