


#ifndef __VGMMESHRENDERWAYVERTEXARRAY_H__
#define __VGMMESHRENDERWAYVERTEXARRAY_H__


#include <vgMesh/vgmDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgImage/vgiTextureObserver.h>
#include <vgMesh/vgmFileDefinitionVgm.h>
#include <vgMesh/vgmMeshRenderWay.h>
#include <vgImage/vgiTextureManager.h>


namespace vgMesh {

	using namespace vgImage;

	class MeshRenderWayVertexArray;

	/**
		used for MeshRenderWayVertexArray only.
		注意这个类的主要目的:从buffer中获得相应的指针指向,
		并不负责buffer的删除.
		这也是为什么把VgmMetaFaceStruct又复制了一份的原因
	*/
	struct  VGM_EXPORT MetaFaceStruct
	{
		MetaFaceStruct();
		~MetaFaceStruct();


		long getInfoFromBuffer( char* buf );


	private:

		void setDefault();

	public:

		unsigned char _colorRGBA[4];

		// 指向的纹理数_numberOfTexture
		// 文件名长度VGM_TEXTURE_NAME_LENGTH
		int		_numberOfTexture;

		String* _texFileName;

		TexObsPointer* _texObserver;

		long _numberOfFaceIndex;
		long _sizeOfFaceIndex;
		VgmFaceIndex* _faceIndex;

		MeshRenderWayVertexArray* _fatherVAWay;
	};


	class MeshRenderWayVbo;
	class MeshDataPlus;

	/**
		@date 	2008/07/17  15:08	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGM_EXPORT MeshRenderWayVertexArray : public MeshRenderWay
	{
		friend class MeshRenderWayVbo;
		friend class MeshRenderWayDisplayList;
		friend class MeshDataPlus;
	public:

		MeshRenderWayVertexArray(  char* buf , long bufsize  );
		virtual ~MeshRenderWayVertexArray();
	
	public:
	
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


	private:

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

		void reCalculateBoundingBox();

		

	private:

		bool _inited;

		bool _hasGotTexObserver;

		long _wholeChunkSize;
		char*	_wholeChunkOfData;

		// 上一个lod的参数.用于比较lod是否需要更新
		int _preLod;

	public:
		// 原始数据
		VgmDataType _dataType;

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

	private:
		TextureManager* _texMgr;

		// 包围盒
		Box		_staticBoundingBox;
	};
	
	
}// end of namespace vgMesh
	


#endif // end of __VGMMESHRENDERWAYVERTEXARRAY_H__