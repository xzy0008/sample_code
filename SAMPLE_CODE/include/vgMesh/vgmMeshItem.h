


#ifndef __VGMMESHITEM_H__
#define __VGMMESHITEM_H__


#include <vgMesh/vgmDefinition.h>
#include <vgKernel/vgkForward.h> 
#include <vgKernel/vgkBox.h>
#include <vgKernel/vgkUniqueID.h>
#include <vgAsyn/vgaIoRequest.h>
#include <vgMesh/vgmMeshData.h>
#include <vgMesh/vgmMesh.h>
#include <vgThreads/AutoEvent.h>
#include <vgKernel/vgkVec3.h>
#include <vgKernel/vgkRenderer.h>
#include <vgKernel/vgkMat4.h>
#include <vgKernel/vgkRendererObserver.h>
#include <vgKernel/vgkShadowCastObject.h>
#include <vgKernel/vgkTransparentObject.h>
#include <vgKernel/vgkColorableObject.h>


namespace vgMesh {

	using namespace vgKernel;

	class MeshData;
	class MeshDataPlus;
	class VgmBrief;

	class IoReqMeshItemDumpInfo;

	/*
	5010 -- 5030之间为QuadTreeSceneMananger的管辖范围之内
	*/
	const vgKernel::RendererType RENDERER_TYPE_MESH = 5000;


	/**
		@date 	2008/07/01  20:58	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGM_EXPORT MeshItem 
		: public vgKernel::Renderer, 
		public vgKernel::ShadowCastObject,
		public vgKernel::TransparentObject,
		public vgKernel::ColorableObject
	{
		VGK_RENDERER_IN_DECLARE( MeshItem )
	public:

		MeshItem();

		~MeshItem();
	
	public:

		bool initialise(  VgmBrief* vgmbrief , vgAsyn::FileHandle* filehandle );

		// 光影的方向在第一次的时候进行设置
		// 包括光的方向变更的时候，也使用此函数进行通知。
		virtual void onLightDirectionChanged( const vgKernel::Vec3& light_dir );

		// 渲染shadow的caster
		virtual void renderInShadowMode();

		virtual void turnOffShadowCast();

		virtual void turnOnShadowCast( const vgKernel::Vec3& light_dir,
			bool force_to_load );


		bool dumpInfoToVgmBrief( VgmBrief* vgmbrief );

		bool dumpFileInfoToBuffer( char*& whole_file , long& file_length );

		void destroy();

#if 0
		// 可用于一开始全部载入的情况.
		// 自增的同时,检查是否需要载入
		// 注意!暂时不用!
		inline void addReference( const int& lod )
		{
			assert( lod >= VG_LOD_COARSEST );
			assert( lod <= VG_LOD_CLEAREST );
			_meshLod[ _distanceLod ]->addRef();
		}

		inline void releaseReference( const int& lod )
		{
			assert( lod >= VG_LOD_COARSEST );
			assert( lod <= VG_LOD_CLEAREST );
			_meshLod[ _distanceLod ]->releaseRef();
		}
#endif


		void render();

		String getDetails() ;

		/**
			继承Renderer而来的接口
		*/
		virtual UniqueID getUniqueID()
		{
			return _uniqueID;
		}

		/**
			继承Renderer而来的接口
		*/
		virtual String getName()
		{
			return _meshName;
		}

		virtual String* getNamePtr()
		{
			return &_meshName;
		}
		/**
			继承Renderer而来的接口
		*/
		virtual void setName( const String& newname )
		{
			_meshName = newname;
		}


		Mesh* getMeshByLod( const int& lod )
		{
			assert( lod <= VGLOD_CLEAR );
			assert( lod >= VGLOD_COARSE );

			return _meshLod[ lod ];
		}

		/**
			继承Renderer而来的接口
		*/
		void translate(const float& x, const float& y, const float& z);

		/**
			继承Renderer而来的接口
		*/
		void rotateSelf(const float& angle, const float& x, const float& y, const float& z);

		/**
			继承Renderer而来的接口
		*/
		void scale(const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z);

		/**
			继承Renderer而来的接口
		*/
		void rotate(const float& angle, const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z); 

		inline float getSquaredDistanceToViewer() const
		{
			return _squaredDistanceToViewer;
		}

		inline int getDistanceLod() const
		{
			return _distanceLod;
		}

		inline const vgKernel::Mat4& getTranslationMaxtrix()
		{
			return _matrix;
		}
		/**
			继承Renderer而来的接口
		*/
		virtual vgKernel::Box getBoundingBox()
		{
			return _dynamicBox;
		}
		
		/**
			继承Renderer而来的接口
		*/
		virtual std::pair<bool, float> testIntersectWithTriangles( const vgKernel::Ray& ray );

		/**
			继承Renderer而来的接口
		*/
		virtual bool testIntersectWithTriangles( 
			const vgKernel::Segment3& segment );


		/**
			继承Renderer而来的接口
		*/
		virtual long getNumOfTriangles()
		{
			return _numberOfTriangles;
		}
		/**
			继承Renderer而来的接口
		*/
		virtual float setDistanceToViewer( const Vec3& viewer_pos  );

		virtual Vec3 getPosition()
		{
			return _dynamicBox.getCenter();
		}


		inline void setMeshName( const String& newname )
		{
			_meshName = newname;
		}

		/**
			客户端不能删除.若要拷贝,请使用clone
		*/
		vgAsyn::FileInfo* getFileInfoByLod( const int& lod )
		{
			return _meshLod[ lod ]->_meshDataFileInfo;
		}

		/**
			千万注意setDistanceToViewer和addViewRef的关系.
			setDistanceToViewer要在addViewRef之前执行.
			这样在addViewRef中有lod的变化.
		*/
		void addViewRef();

		void releaseViewRef();

		int getViewRef() const
		{
			return _viewReference;
		}

		bool getLodMeshFlag() const
		{
			return _isLodMesh;
		}

		// 还未经过测试!!!!选择编辑功能做完之后再测试!
		void setLodMeshFlag( const bool& islodmesh )
		{
			_isLodMesh = islodmesh;
		}

		//_squareDistNear get 和set函数待写
		//_squareDistFar get 和set函数待写

		void setSquareDistNear(float squareDistNear)
		{
			_squareDistNear = squareDistNear;
		}

		float getSquareDistNear()
		{
			return _squareDistNear;
		}

		void setSquareDistFar(float squareDistFar)
		{
			_squareDistFar = squareDistFar;
		}

		float getSquareDistFar()
		{
			return _squareDistFar;
		}

		// 继承TransparentObject的接口
		virtual bool isTransparent();

		// 继承TransparentObject的接口
		virtual void setTransparent( bool set_to_transp = true );

	private:

		void updateMeshLod();
		void setDefault();

	private:

		// 是否参与lod渲染.
		// 若为false,则只渲染最精细一级.
		// 默认为true
		bool _isLodMesh;

		float _squareDistNear;
		float _squareDistFar;


		// 视点的引用计数.
		// 物体进入视点时增加计数.
		// 离开视点时减少计数.
		int _viewReference;

		float _squaredDistanceToViewer;

		// 通过_distanceToViewer计算出来lod
		int		_distanceLod;


		// 当前的Lod,注意,当_currentLod与_distanceLod
		// 相当于_preLod
		// 相比发生变化时,才发生addRef和releaseRef操作 
		// 默认的为最不清晰一级,即_currentLod = 0;
		int		_currentLod;

		UniqueID _uniqueID;
	
		// 注意,最多64个字节长度.
		String _meshName;

		vgKernel::Box _dynamicBox;
		vgKernel::Box _staticBox;

		vgKernel::Mat4 _matrix;

		long	_numberOfTriangles;

		vgAsyn::FileInfo* _wholeFileInfo;

		
		Mesh* _meshLod[ VGLOD_N ];

		// 用于addRef和ReleaseRef的标记位
		// 注意,这里和Texture相同的原理,只是临时变量
		// 用以标记是否有addRef的请求.
		// 用来解决不同lod载入连续性的问题
		Mesh* _refMesh[ VGLOD_N ];

		bool _isTransparent;

	};
	

	typedef std::vector<MeshItem*> MeshItemPtrVec;

	typedef std::map<UniqueID, MeshItem*> MeshItemMap;
	typedef std::pair<MeshItemMap::iterator, bool> MeshItemInsertRes;

	/**
		同步IO请求,用于保存vgm文件
		注意,删除操作由外部完成
	*/
	class IoReqMeshItemDumpInfo : public vgAsyn::IoRequest
	{
	public:
		IoReqMeshItemDumpInfo( vgAsyn::FileInfo* fileinfo  );
		virtual ~IoReqMeshItemDumpInfo();
	
		// no dispatch to main thread
		virtual bool anotherThreadHandler();

		virtual bool mainThreadHandler();

	public:

	};

	VGK_RENDERER_OUT_DECLARE( MeshItem )
	
}// end of namespace vgMesh

#endif // end of __VGMMESHITEM_H__