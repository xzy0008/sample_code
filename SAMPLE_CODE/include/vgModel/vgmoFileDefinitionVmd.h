


#ifndef __VGMO_FILEDEFINITIONVMD_H__
#define __VGMO_FILEDEFINITIONVMD_H__


#include <vgModel/vgmoDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgModel/vgmoFileDefinitionMod.h>
#include <vgKernel/vgkBox.h>
#include <vgKernel/vgkUniqueID.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgKernel/vgkStreamReader.h>
#include <vgKernel/vgkStreamWriter.h>
#include <vgKernel/vgkMat4.h>

#include <vgKernel/vgkRgbaQuad.h>

namespace vgModel {

	
	using namespace vgKernel;

	class ModelItem;
	class ModObject;


#define VMD_TEXTURE_NAME_LENGTH	64
#define VMD_MODEL_NAME_LENGTH	64


	//// 类型定义
	//// 客户端可以自己添加
	//const int VMD_BRIEFTYPE_MODEL = 0;
	//const int VMD_DATATYPE_MODEL = 0;


	struct  VGMO_EXPORT VmdHeader
	{
		VmdHeader()
		{
			setDefault();
		}
		~VmdHeader()
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

	struct VmdFaceIndex
	{
		int _point0;
		int _point1;
		int _point2;
	};

	/**
	顶点结构1
	*/
	struct VmdVertexElement1
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
	struct VmdVertexElement2
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
		sizeof( VmdBrief ) ==228;
	*/
	class  VGMO_EXPORT VmdBrief
	{
	public:
		VmdBrief();
		~VmdBrief()
		{

		}

		bool setClassName( const String& classname );

		void getInfoFromModObject( ModObject* mod );

	private:

		void setDefault();

	public:

		// 标识Class读取的字符串
		char	_className[VMD_MODEL_NAME_LENGTH];
		char	_modelName[VMD_MODEL_NAME_LENGTH];

		UniqueID _parentID;
		UniqueID _uniqueId;

		//目前来看_positionOfFile和_positionOfModelData表示一样
		// 但是如果有lod信息,二者就不会一样了
		long	_positionOfFile;
		long	_lengthOfFile;
		long _positionOfModelData;
		long _lengthOfModelData;


		// 下面的为了字节对齐
		bool	_isVisible;
		char	_reserved0;
		char  _reserved1;
		char  _reserved2; 

		// 这里存放的不是openGL列主序的matrix
		// 是行主序的matrix
		// 使用时调用glMultTransposeMatrixf即可
		vgKernel::Mat4	_multMatrix;
		Box _dynamicBoundingBox;
		Box _staticBoundingBox;

		long _numberOfFaces;

		//------------------------------------------
		// 不再使用
		// 作为reserved使用
		//------------------------------------------
		long _reservedData[ 16 ];


		// 第一级的lod参数.即离视点最清晰lod的范围
		float _squaredDistanceOfLodNear;
		// 第二级的lod参数.
		float _squaredDistanceOfLodFar;

		vgKernel::RgbaQuad _colorQuad;
		long	_reserved3;
		long	_reserved4;
		long	_reserved5;
		long	_reserved6;

		long	_reserved7[256];
	};

	typedef vgKernel::SharePtr<VmdBrief> VmdBriefPtr;

	typedef std::vector<VmdBriefPtr> VmdBriefPtrVec;




	struct VmdKeyFrame
	{
		int		m_fTime;		//	Time at which keyframe is started
		vgKernel::Mat4 _matrix;
	};

	/**
	@date 	2009/05/21  20:21	
	@author  leven

	@brief 	

	@see    
	*/
	class VmdKeyFrameInfo
	{
	public:
		VmdKeyFrameInfo()
		{
			_frameCount = 0;
			_startFrame = 0;
			_endFrame = 0;

			_play = true;
			_loop = true;

			_frames = NULL;
		}
		~VmdKeyFrameInfo()
		{
			if ( _frames != NULL )
			{
				delete[] _frames;
				_frames = NULL;
			}

		}

		VmdKeyFrameInfo* createCopy()
		{
			VmdKeyFrameInfo* ret = new VmdKeyFrameInfo;
			ret->_frameCount = _frameCount;
			ret->_startFrame = _startFrame;
			ret->_endFrame = _endFrame;

			ret->_play = _play;
			ret->_loop = _loop;

			ret->_frames = new VmdKeyFrame[ _frameCount ];
			memcpy( ret->_frames , _frames , sizeof( VmdKeyFrame ) * 
				_frameCount );

			return ret;
		}


	public:

		int _frameCount;
		int _startFrame;
		int _endFrame;

		bool _play;
		bool _loop;

		VmdKeyFrame* _frames;
	};

	/**
		单个face数据结构
	*/
	struct  VGMO_EXPORT VmdMetaFaceStruct
	{
		VmdMetaFaceStruct();
		~VmdMetaFaceStruct();

		long writeToStream( const vgKernel::StreamWriterPtr pwriter );

	private:
		void setDefault();
		void destroy();
	public:
		unsigned char _colorRGBA[4];


		// 指向的纹理数_numberOfTexture
		// 文件名长度VMD_TEXTURE_NAME_LENGTH
		int		_numberOfTexture;
		long	_sizeOfOneTexName;
		char **_textureFileName;

		// 注意!这里是被3除过的数,即使用时要乘以3
		long _numberOfFaceIndex;
		long _sizeOfFaceIndex;
		VmdFaceIndex* _faceIndex;

	};


	/**
		存放一个object的所有face
	*/
	struct  VGMO_EXPORT VmdDataStruct
	{
		VmdDataStruct();
		~VmdDataStruct();

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
		VmdMetaFaceStruct* _metaFaces;


		// DataPlus
		int		_shadowNumberOfFaces;
		Vec3*	_shadowNormalOfFaces;
		int		_shadowNumberOfVertices;
		Vec3*	_shadowVerticesOfFaces;
		ShadowFaceIndex*	_shadowIndicesOfFaces;

		// keyframe
		VmdKeyFrameInfo* _keyframeInfo;
	};


	typedef vgKernel::SharePtr<VmdDataStruct> VmdDataStructPtr;

	typedef std::vector<VmdDataStructPtr> VmdDataStructPtrVec;




	
}// end of namespace vgModel

#endif // end of __VGMO_FILEDEFINITIONVMD_H__