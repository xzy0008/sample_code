


#ifndef __VGMO_MESHRENDERWAYVERTEXARRAY_H__
#define __VGMO_MESHRENDERWAYVERTEXARRAY_H__


#include <vgModel/vgmoDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgImage/vgiTextureObserver.h>
#include <vgModel/vgmoFileDefinitionVmd.h>
#include <vgModel/vgmoModelRenderWay.h>
#include <vgImage/vgiTextureManager.h>
#include <vgModel/vgmoTimer.h>



namespace vgModel {

	using namespace vgImage;

	class ModelRenderWayVertexArray;
	class KeyFrameControl;

	/**
		used for ModelRenderWayVertexArray only.
		注意这个类的主要目的:从buffer中获得相应的指针指向,
		并不负责buffer的删除.
		这也是为什么把VmdMetaFaceStruct又复制了一份的原因
	*/
	struct  VGMO_EXPORT MetaFaceStruct
	{
		MetaFaceStruct();
		~MetaFaceStruct();


		long getInfoFromBuffer( char* buf );


	private:

		void setDefault();

	public:

		unsigned char _colorRGBA[4];

		// 指向的纹理数_numberOfTexture
		// 文件名长度VMD_TEXTURE_NAME_LENGTH
		int		_numberOfTexture;

		String* _texFileName;

		TexObsPointer* _texObserver;

		long _numberOfFaceIndex;
		long _sizeOfFaceIndex;
		VmdFaceIndex* _faceIndex;

		ModelRenderWayVertexArray* _fatherVAWay;
	};


	class ModelRenderWayVbo;
	class ModelDataPlus;

	/**
		@date 	2008/07/17  15:08	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGMO_EXPORT ModelRenderWayVertexArray : public ModelRenderWay
	{
		friend class ModelRenderWayVbo;
		friend class ModelRenderWayDisplayList;
		friend class ModelDataPlus;
	public:

		ModelRenderWayVertexArray(  char* buf , long bufsize  );
		virtual ~ModelRenderWayVertexArray();
	
	public:
	
		virtual void invalidateTextures();

		virtual void render(const int& lod, int force_render_in_num_layers ,
			RgbaQuad* colorval );


		std::pair<bool, float> testIntersection(const vgKernel::Ray* ray);

		virtual bool testIntersection(const vgKernel::Segment3* segment);


		void destroy();

		bool initialise();

		virtual bool initialiseInMainThread();

		// 用于保存纹理所用
		// 本类所包含的texture全部输入到ptexturelist中
		void dumpTextureNameList( vgKernel::StringVectorPtr ptexturelist ) const;
	
		// shadow相关
		virtual void turnOnShadowImpl( const vgKernel::Vec3& light_dir );
		virtual void turnOffShadowImpl();
		virtual void changeLightDirectionImpl(  const vgKernel::Vec3& light_dir );
		virtual void renderInShadowModeImpl();

		virtual KeyFrameControl* getKeyFrameControlRef()
		{
			return _keyframeCtrl;
		}

		// take ownership
		virtual void setKeyFrameControl( KeyFrameControl* newctrl );

	private:

		void	buildShadowVolume(const vgKernel::Vec3& lightdir);

		void calcuateForShadow( const vgKernel::Vec3& lightDir );

		void renderInOneLayer();

		void renderInTwoLayer();

		// 将2层的bake只渲染一层
		void renderTwoLayerInOneLayer();

		void requireTextureObservers();

		// 注意,这里从buffer取数据,直接指向buffer数据区.
		// 即,不能删除buf,否则会报错
		bool getInfoFromBuffer( char* buf , long bufsize );

		void setDefault();

		void requireTexObserverByLod( const int& lod );


		

	private:

		int		_shadowVolume;

		bool _inited;

		bool _hasGotTexObserver;

		long _wholeChunkSize;
		char*	_wholeChunkOfData;

		// 上一个lod的参数.用于比较lod是否需要更新
		int _preLod;

		int		_renderType;

		// 几层纹理,用于bake
		// 暂时只支持1和2
		long _layersOfTexture;

		// 顶点存放
		long	_numberOfVertexElements;
		long	_sizeOfVertexElements;
		void*	_vertexElements;

		// 面索引
		long _numberOfMetaFaces;
		MetaFaceStruct* _metaFaces;

		//------------------------------------------
		// dataplus
		//------------------------------------------
		int		_shadowNumberOfFaces;
		Vec3*	_shadowNormalOfFaces;
		int		_shadowNumberOfVertices;
		Vec3*	_shadowVerticesOfFaces;
		ShadowFaceIndex*	_shadowIndicesOfFaces;

		// keyframe
		KeyFrameControl* _keyframeCtrl;
		



		TextureManager* _texMgr;

		// 包围盒
		Box		_staticBoundingBox;
	};
	
	
}// end of namespace vgModel
	


#endif // end of __VGMO_MESHRENDERWAYVERTEXARRAY_H__