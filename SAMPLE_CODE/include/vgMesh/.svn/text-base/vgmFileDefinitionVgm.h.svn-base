


#ifndef __VGMFILEDEFINITIONVGM_H__
#define __VGMFILEDEFINITIONVGM_H__


#include <vgMesh/vgmDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgMesh/vgmFileDefinitionMod.h>
#include <vgKernel/vgkBox.h>
#include <vgKernel/vgkUniqueID.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgKernel/vgkStreamReader.h>
#include <vgKernel/vgkStreamWriter.h>
#include <vgKernel/vgkMat4.h>

#include <vgKernel/vgkRgbaQuad.h>

namespace vgMesh {

	
	using namespace vgKernel;

	class ModObject;


#define VGM_TEXTURE_NAME_LENGTH	64
#define VGM_MESH_NAME_LENGTH	64

	enum VgmBriefType
	{
		VGM_BRIEFTYPE_MESH,
		VGM_BRIEFTYPE_GROUP
	};

	enum VgmDataType
	{
		VGM_DATATYPE_OBJECT
	};

	enum VgmDataPlusType
	{
		VGM_DATAPLUSTYPE_SHADOW
	};


	struct  VGM_EXPORT VgmHeader
	{
		VgmHeader()
		{
			setDefault();
		}
		~VgmHeader()
		{

		}

	private:

		void setDefault();

	public:

		char	_fourCC[4];
		int		_version;
		long	_sizeOfHeader;
		long	_sizeOfWholeFile;
		long	_numberOfBriefs;
		long	_lengthOfOneBrief;
		long	_positionOfBriefs;
		long	_reserved1;
		long	_reserved2;
		long	_reserved3;
		long	_reserved4;

	};

	struct VgmFaceIndex
	{
		int _point0;
		int _point1;
		int _point2;
	};

	/**
	顶点结构1
	*/
	struct VgmVertexElement1
	{
		float texCoorS;
		float texCoorT;

		float normalX;
		float normalY;
		float normalZ;

		float positionX;
		float positionY;
		float positionZ;

	};

	/**
	顶点结构2
	*/
	struct VgmVertexElement2
	{
		float texCoorS1;
		float texCoorT1;

		float normalX;
		float normalY;
		float normalZ;

		float positionX;
		float positionY;
		float positionZ;

		float texCoorS2;
		float texCoorT2;
	};

	/**
		注意,先没考虑直接对齐的问题
		sizeof( VgmBrief ) ==228;
	*/
	class  VGM_EXPORT VgmBrief
	{
	public:
		VgmBrief();
		~VgmBrief()
		{

		}

		void getInfoFromModObject( ModObject* mod );

	private:

		void setDefault();

	public:

		VgmBriefType _type;


		UniqueID _parentID;
		UniqueID _uniqueId;

		long	_positionOfFile;
		long	_lengthOfFile;
		char	_meshName[VGM_MESH_NAME_LENGTH];

		VgmDataType	_meshDataType;
		VgmDataPlusType _meshDataPlusType;

		bool	_isVisible;
		// 是否是lod的Mesh.
		// 默认为true.如果为false,只渲染最精细的一级.
		bool  _isLodMesh;
		char	_reserved0;
		char  _reserved1;

		// 这里存放的不是openGL列主序的matrix
		// 是行主序的matrix
		// 使用时调用glMultTransposeMatrixf即可
		vgKernel::Mat4	_multMatrix;
		Box _dynamicBoundingBox;
		Box _staticBoundingBox;
		long _numberOfFaces;

		//------------------------------------------
		// Lod0 is coarest.
		//------------------------------------------
		long _positionOfMeshData[ VGLOD_N ];
		long _lengthOfMeshData[ VGLOD_N ];
		long _positionOfMeshDataPlus[ VGLOD_N ];
		long _lengthOfMeshPlus[VGLOD_N ];


		// 第一级的lod参数.即离视点最清晰lod的范围
		float _squaredDistanceOfLodNear;
		// 第二级的lod参数.
		float _squaredDistanceOfLodFar;

		// 为以后标记做准备
		vgKernel::RgbaQuad _colorQuad;
		//long	_reserved3;
		long	_reserved4;
		long	_reserved5;
		long	_reserved6;
	};

	typedef vgKernel::SharePtr<VgmBrief> VgmBriefPtr;

	typedef std::vector<VgmBriefPtr> VgmBriefPtrVec;


	/**
		单个face数据结构
	*/
	struct  VGM_EXPORT VgmMetaFaceStruct
	{
		VgmMetaFaceStruct();
		~VgmMetaFaceStruct();

		long writeToStream( const vgKernel::StreamWriterPtr pwriter );

	private:
		void setDefault();
		void destroy();
	public:
		unsigned char _colorRGBA[4];


		// 指向的纹理数_numberOfTexture
		// 文件名长度VGM_TEXTURE_NAME_LENGTH
		int		_numberOfTexture;
		long	_sizeOfOneTexName;
		char **_textureFileName;

		// 注意!这里是被3除过的数,即使用时要乘以3
		long _numberOfFaceIndex;
		long _sizeOfFaceIndex;
		VgmFaceIndex* _faceIndex;

	};


	/**
		存放一个object的所有face
	*/
	struct  VGM_EXPORT VgmDataStruct
	{
		VgmDataStruct();
		~VgmDataStruct();

		void getInfoFromModObject( ModObject* mod );

		long writeToStream( const vgKernel::StreamWriterPtr pwriter );

		long getNumberOfTriangles();

#if 0
		// only for testing
		void render();
#endif

		void destroy();

	private:

		void setDefault();
	public:

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
		VgmMetaFaceStruct* _metaFaces;
	};


	typedef vgKernel::SharePtr<VgmDataStruct> VgmDataStructPtr;

	typedef std::vector<VgmDataStructPtr> VgmDataStructPtrVec;



	class  VGM_EXPORT VgmDataPlus
	{
	public:
		VgmDataPlus()
		{
			_type = VGM_DATAPLUSTYPE_SHADOW;
			_shadowNumberOfFaces = 0;
			_shadowNormalOfFaces = NULL;
			_shadowNumberOfVertices = 0;
			_shadowVerticesOfFaces = NULL;
			_shadowIndicesOfFaces = NULL;
		}
		~VgmDataPlus()
		{
			if ( _shadowNormalOfFaces != NULL )
			{
				delete[] _shadowNormalOfFaces;
				_shadowNormalOfFaces = NULL;
			}

			if ( _shadowVerticesOfFaces != NULL )
			{
				delete[] _shadowVerticesOfFaces;
				_shadowVerticesOfFaces = NULL;
			}
			if ( _shadowIndicesOfFaces != NULL )
			{
				delete[] _shadowIndicesOfFaces;
				_shadowIndicesOfFaces = NULL;
			}
		}
		
	
	private:
	
		VgmDataPlusType _type;

		// DataPlus
		int		_shadowNumberOfFaces;
		Vec3*	_shadowNormalOfFaces;
		int		_shadowNumberOfVertices;
		Vec3*	_shadowVerticesOfFaces;
		ShadowFaceIndex*	_shadowIndicesOfFaces;
	
	};

	
}// end of namespace vgMesh

#endif // end of __VGMFILEDEFINITIONVGM_H__