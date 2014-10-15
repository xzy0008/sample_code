



#ifndef __VGTERRITORY_TELEVATIONITEM_H__
#define __VGTERRITORY_TELEVATIONITEM_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgTerritory/vgtElevation.h>
#include <vgKernel/vgkVec2.h>
#include <vgKernel/vgkImagePos.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgTerritory/vgtElevationBound.h>
#include <vgImage/vgiTextureObserver.h>

#include <gdal/ogr_geometry.h>

	
namespace vgTerritory {

	using namespace vgKernel;

	class FileHandleVtr;
	class TerrainGpuProgram;
	class Elevation;

	/**
		@date 	2008/09/08  19:25	
		@author  leven
	
		@brief 	相当于vgMesh中的MeshItem类
		在每一帧当中update,对需要的addRef
	
		@see    
	*/
	class  VGT_EXPORT ElevationItem
	{
		friend class Elevation;
	public:
		ElevationItem( VtrBrief* brief , FileHandleVtr* vtrfilehandle );
		~ElevationItem();
	
	
	public:

		bool testIntersection( const ElevationBound& bound );

		// 首先从内存中判断,如果存在,则在内存中读入
		// 反之,则在外存中读入.
		bool getElevationByPos( const Vec3& pos , float& out_elevation );

		// 注意,这里的过滤也可能会有问题,而且由于平整的原因可能和外存的数据存在出入.
		bool getElevationByPosInMemory( const Vec3& pos , float& out_elevation );

		// 注意!!这个时候可能没有别过滤!
		bool getElevationByPosInDisk( const Vec3& pos , float& out_elevation );

		
		/**
			千万注意setDistanceToViewer和addViewRef的关系.
			setDistanceToViewer要在addViewRef之前执行.
			这样在addViewRef中有lod的变化.
		*/
		void addViewRef();

		int getViewRef() const
		{
			return _refCount;
		}

		void releaseViewRef();

		String getName() const
		{
			return _metaFilename;
		}

		String getTextureName() const
		{
			return _metaTexFilename;
		}

		long getHeightMapWidth()
		{
			return _heightMapWidth;
		}

		bool isLoaded()
		{
			if ( _texObs != NULL )
			{
				return _texObs->getTextureID( false ) != VG_NULL_TEXTURE_ID;
			}

			return true;
		}
	
		/**
			客户端不负责删除
		*/
		Elevation* getElevationByLod( const int& lod )
		{
			return _elevLod[lod];
		}

		/**
			注意,客户端负责删除
		*/
		vgAsyn::FileInfo* getMetaFileInfoClone()
		{
			assert( _metaFileInfo != NULL );
			return _metaFileInfo->clone();
		}

		float getDisplaceScaleY() const 
		{
			return _displaceScaleY;
		}


		void useBindInGpuProgram();

		long getLevel() const 
		{
			return _level;
		}

		void getBlockNumber( long& out_blockx , long& out_blockz )
		{
			out_blockx = _blockX;
			out_blockz = _blockZ;
		}

		long getBlockNumberX() const
		{
			return _blockX;
		}

		long getBlockNumberZ() const
		{
			return _blockZ;
		}

		// 取得displace的参数.
		// 注意,param要保证是float[4]
		void getDisplaceParams( float* param )
		{
			assert( param != NULL );
			memcpy( param , _displaceParams , sizeof( float ) * 4 );
		}

		//  将一个世界坐标绝对地址映射到当前的uv值.
		//  map_height 是否折算world_vertex的y值到0~1
		Vec3 mappingVertexToUV( const Vec3& world_vertex , 
			const bool& map_height );

		Vec2 mappingVertexToUV( const Vec2& world_vertex );

		// 映射世界坐标到0~256的Grid坐标,注意,返回的是float变量.
		Vec2 mappingVertexToGrid( const Vec2& world_vertex );

		// 映射世界坐标到0~256的Image坐标,注意,返回的是long变量.
		ImagePos mappingVertexToImagePos( const Vec2& world_vertex );

		// 映射世界坐标的高度值到0~1的Grid坐标,注意,显存中只能存放0~1的高程值.
		float mappingHeightToGrid( const float& height )
		{
			return height / _displaceScaleY;
		}

		inline bool isEmptyItem() const
		{
			return _isEmptyItem;
		}

		String getMetaFilename()
		{
			return _metaFilename;
		}

		void setStateWithInPolygon( bool bState )
		{
			_bWithInSelectPolygon = bState;
		}

		bool getStateWithInPolygon() 
		{
			return _bWithInSelectPolygon;
		}

		void setOgrGeoPtr( OGRGeometry* pGeo )
		{
			_pOgrGeo = pGeo;
		}

		OGRGeometry* getOgrPtr()
		{
			return _pOgrGeo;
		}

	private:

		void createEmptyTextureId();
		void deleteEmptyTextureId();

		void createEmptyElevationTextureId();
		void deleteEmptyElevationTextureId();

	private:
	
		static GLuint s_emptyElevationTextureId;
		static GLuint s_emptyTextureId;

		bool _isEmptyItem;

		// 当前块的level
		long _level;

		// 当前块的block number
		long _blockX;
		long _blockZ;

		FileHandleVtr* _vtrFilehandle;


		int _refCount;

		vgTerritory::TerrainGpuProgram* _gpuProgram;

		vgAsyn::FileInfo* _metaFileInfo;

		String _metaFilename;


		/**
			和视点的位置
		*/
		//float _squaredDistanceToViewer;
	

		/**
			需要header中的信息
		*/
		String _metaTexFilename;

		long _heightMapWidth;	// X轴方向上网格的数量.N=8时,此值是256.和Z轴是一样的

		union
		{
			struct
			{ 
				float _displaceScaleY;	// Y轴的放大值
				float _displaceChunkScale;	// 本小块相对于大图的放大值
				float _displaceChunkBiasX;	// 本小块相对于大图的偏移, x 方向
				float _displaceChunkBiasZ;	// 本小块相对于大图的偏移, z 方向
			};

			float _displaceParams[4];
		};

		vgImage::TexObsPointer _texObs;

		Elevation* _elevLod[ VGLOD_N ];

		// 用于addRef和ReleaseRef的标记位
		// 注意,这里和Texture相同的原理,只是临时变量
		// 用以标记是否有addRef的请求.
		// 用来解决不同lod载入连续性的问题
		Elevation* _refElev[ VGLOD_N ];

		/**
			add by ZhouZY 2010-1-14  20:28
			用于切块保存
		*/
		bool _bWithInSelectPolygon; // 标识此Item的Bound是否落在Polygon之中

		OGRGeometry* _pOgrGeo;      // 此Item与Polygon的相交区域( OGRPolygon )
	};
	

	typedef std::map<String, ElevationItem*> ElevationItemMap;

	typedef std::vector<ElevationItem*> ElevationItemVector;

	typedef vgKernel::SharePtr<ElevationItemVector> ElevationItemVectorPtr;
	
}// end of namespace vgTerritory
	


#endif // end of __VGTERRITORY_TELEVATIONITEM_H__