


#ifndef __VGMO_MESHRENDERWAYVBO_H__
#define __VGMO_MESHRENDERWAYVBO_H__
#include <vgModel/vgmoDefinition.h>
#include <vgKernel/vgkForward.h>


	
namespace vgModel {


	class KeyFrameControl;

	#define  VG_NULL_VBO_ID	-1

	/**
		used for ModelRenderWayVbo only
	*/
	class  VGMO_EXPORT VboMetaFaceStruct
	{
	public:
		VboMetaFaceStruct();
		~VboMetaFaceStruct();
	
		int		_numberOfTexture;
		String* _texFileName;

		TexObsPointer* _texObserver;

		GLuint _elementBufferObjectID;

		// 注意,这里是int类型的原子数目.即3的倍数
		long _numOfElements;
	};


	class ModelRenderWayVertexArray;

	/**
		@date 	2008/07/17  15:23	
		@author  leven
	
		@brief 	注意,只能在主线程中创建,因为构造函数中含有创建
		vbo的命令
	
		@see    
	*/
	class  VGMO_EXPORT ModelRenderWayVbo : public ModelRenderWay
	{
	public:
		ModelRenderWayVbo( ModelRenderWayVertexArray* vertexarray );
		virtual ~ModelRenderWayVbo();

		virtual void render(const int& lod, int force_render_in_num_layers ,
			RgbaQuad* colorval );

		std::pair<bool, float> testIntersection(const vgKernel::Ray* ray);

		virtual bool testIntersection(const vgKernel::Segment3* segment);

		
		virtual void invalidateTextures();
		
		virtual bool initialiseInMainThread();


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

		void requireTexObserverByLod( const int& lod );

		bool generateVbo( ModelRenderWayVertexArray* vertexarray );

	private:

		int _shadowVolume;
		int		_renderType;

		// 上一个lod的参数.用于比较lod是否需要更新
		int _preLod;

		long _layersOfTexture;


		bool _isReadyForVBORender;

		GLuint _vertexBufferObjectID;

		long	_numberOfMetaFaces;
		VboMetaFaceStruct* _metaFaces;



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
	};
	
	
}// end of namespace vgModel
	


#endif // end of __VGMO_MESHRENDERWAYVBO_H__