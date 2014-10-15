


#ifndef __VGMMESHRENDERWAYVBO_H__
#define __VGMMESHRENDERWAYVBO_H__


#include <vgMesh/vgmDefinition.h>
#include <vgKernel/vgkForward.h>


	
namespace vgMesh {


	#define  VG_NULL_VBO_ID	-1

	/**
		used for MeshRenderWayVbo only
	*/
	class  VGM_EXPORT VboMetaFaceStruct
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


	class MeshRenderWayVertexArray;

	/**
		@date 	2008/07/17  15:23	
		@author  leven
	
		@brief 	注意,只能在主线程中创建,因为构造函数中含有创建
		vbo的命令
	
		@see    
	*/
	class  VGM_EXPORT MeshRenderWayVbo : public MeshRenderWay
	{
	public:
		MeshRenderWayVbo( MeshRenderWayVertexArray* vertexarray );
		virtual ~MeshRenderWayVbo();

		virtual void render(const int& lod, int force_render_in_num_layers ,
			RgbaQuad* colorval );

		std::pair<bool, float> testIntersection(const vgKernel::Ray* ray);

		virtual bool testIntersection(const vgKernel::Segment3* segment);

		virtual bool initialiseInMainThread();
	
	private:

		void renderInOneLayer();
		void renderInTwoLayer();

		// 将2层的bake只渲染一层
		void renderTwoLayerInOneLayer();

		void requireTexObserverByLod( const int& lod );

		bool generateVbo( MeshRenderWayVertexArray* vertexarray );

	private:

		int		_renderType;

		// 上一个lod的参数.用于比较lod是否需要更新
		int _preLod;

		long _layersOfTexture;


		bool _isReadyForVBORender;

		GLuint _vertexBufferObjectID;

		long	_numberOfMetaFaces;
		VboMetaFaceStruct* _metaFaces;

		TextureManager* _texMgr;
	};
	
	
}// end of namespace vgMesh
	


#endif // end of __VGMMESHRENDERWAYVBO_H__