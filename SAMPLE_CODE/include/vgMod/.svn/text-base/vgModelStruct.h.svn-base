#ifndef _MODLESTRUCT_H_
#define _MODLESTRUCT_H_


#include <vgTex/tvgTexture.h>
#include <vgImage/vgiTextureObserver.h>


namespace vgCore {

#pragma pack(push,1) 

	///obj材质中最基本的信息，若需要支持材质球中的调整，需重新加入一些成员
	struct MaterialInfoStruct
	{
		int aphlatext;
		char  strName[255];			// The texture name
		char  strFile[255];			// The texture file name (If this is set it's a texture map)

		char  alphaFile[255];
		unsigned char  color[3];				// The color of the object (R, G, B)
		unsigned int   texureId;				// the texture ID

	} ;


	// 新材质信息结构体（支持烘焙）
	struct MaterialInfoStruct2
	{
		int aphlatext;
		char  strName[255];			// The texture name
		char  strFile[255];			// The texture file name (If this is set it's a texture map)

		char  alphaFile[255];
		unsigned char  color[3];				// The color of the object (R, G, B)
		unsigned int   texureId;				// the texture ID

		char  strFileBaked[255];  
	} ;

	struct MaterialDataStruct 
	{
		int width;
		int length;
		long size;
		char *data;
	};
	struct MaterialStruct
	{
		MaterialInfoStruct materialinfo;

		long fileoffset;

		TexturePtr pTexture;
		vgImage::TextureObserver* pTexObserver;

		vgImage::TextureObserver* ptestObs;

		MaterialStruct()
		{
			pTexObserver = NULL;
			ptestObs = NULL;
		}
		~MaterialStruct()
		{
			if ( pTexObserver != NULL )
			{
				delete pTexObserver;
				pTexObserver = NULL;
			}

			if ( ptestObs != NULL )
			{
				delete ptestObs;
				ptestObs = NULL;
			}
		}



	};


	// 新材质结构体（支持烘焙）
	struct MaterialStruct2
	{
		MaterialInfoStruct2 materialinfo;

		long fileoffset;

		TexturePtr pTexture;
		TexturePtr pTexture2;



	};

#pragma  pack(pop)

	///交错数组中用到的点的结构体
	struct VertexElementStruct
	{
	public:
		float texCoorS;
		float texCoorT;

		float normalX;
		float normalY;
		float normalZ;

		float positionX;
		float positionY;
		float positionZ;
	};

	// 2008年3月6日17:05:43 lss 添加：
	// 新交错数组（支持烘焙）
	struct VertexElementStruct2
	{
	public:
		float texCoorS;
		float texCoorT;

		float normalX;
		float normalY;
		float normalZ;

		float positionX;
		float positionY;
		float positionZ;

		float texCoorUForLit;
		float texCoorVForLit;
	};

	struct FaceIndex
	{
		int x;
		int y;
		int z;
	};

	struct ObjectRenderControl2
	{
		bool b_hastexture;

		int m_numOfFace;


		GLuint _elementBufferObjectID;
		//char *pFace;

		ObjectRenderControl2()
		{
			b_hastexture = false;
			m_numOfFace = 0;
			_elementBufferObjectID = -1;
			pFace = NULL;
		}
		~ObjectRenderControl2() {}


		FaceIndex *pFace;


	};
	struct ObjectRenderControl 
	{
		bool b_hastexture;

		int m_numOfFace;

		FaceIndex *pFace;

		int m_numOfFace2;//////////////////////////////////////////2008.6.26

		vector<FaceIndex> tempface;

		FaceIndex *pFace2;


		GLuint _elementBufferObjectID;
		GLuint _elementBufferObjectID2;
	

		ObjectRenderControl()
		{
			b_hastexture = false;
			m_numOfFace = 0;

			_elementBufferObjectID = -1;
			_elementBufferObjectID2 = -1;
		
			pFace	= NULL;
			pFace2	= NULL;
		}
		~ObjectRenderControl() {}




	};

	struct ShadowFaceIndex
	{
		//int	p1;
		//int p2;
		//int p3;
		union
		{
			struct
			{	int p1 , p2 , p3;  };
			
			int vertIndex[3];
		};

		int	normal;

		int	p1p2AdjFaceIndex;
		int	p2p3AdjFaceIndex;
		int	p3p1AdjFaceIndex;

		bool faceVisible;

		bool p1p2Visible;
		bool p2p3Visible;
		bool p3p1Visible;	
	};


	// 2008年5月7日16:49:51 add by lss
	typedef		Vector3			VetexRaw;
	typedef		unsigned int	IndexType;

	class vgQuad
	{
	public:
		vgQuad()
		{
			index[0] = index[1] = index[2] = index[3] = -1;
		}
		vgQuad(vgQuad &quad)
		{
			index[0]	= quad.index[0];
			index[1]	= quad.index[1];
			index[2]	= quad.index[2];
			index[3]	= quad.index[3];
		}
		vgQuad& operator=(const vgQuad& quad)
		{
			index[0]	= quad.index[0];
			index[1]	= quad.index[1];
			index[2]	= quad.index[2];
			index[3]	= quad.index[3];
			return *this;
		}
		vgQuad(IndexType indexOne)
		{
			index[0] = index[1] = index[2] = index[3] = indexOne;
		}
		vgQuad(IndexType index0, IndexType index1, IndexType index2, IndexType index3 )
		{
			this->index[0]	= index0;
			this->index[1]	= index1;
			this->index[2]	= index2;
			this->index[3]	= index3;
		}
		// 获取第0，1，2个点索引
		IndexType	GetQuadIndex(IndexType i)	
		{
			return	index[i];
		}

	private:
		// 线段的二点索引
		IndexType	index[4];	
	};//class vgLine
	typedef	vector<vgQuad>  QuadVector ;
	typedef vgQuad*			QuadPointer;
	typedef	vgQuad			QuadRaw;

}

#define		VERSION_MOD(year, updateTime)	(	( (year)<<16 )	+	(updateTime)	)
#define		VERSION_1						VERSION_MOD(0,		100	)
#define		VERSION_4						VERSION_MOD(2008,	4	)
#define		VERSION_6						VERSION_MOD(2008,	6	)
#define		VERSION_LATEST					VERSION_6	


//	MOD节点类型枚举
enum	E_OBJECT_TYPE
{
	OBJECT_MODEL,
	OBJECT_STANDARD,
	OBJECT_BAKED		=7,
	OBJECT_KEYFRAME
};
// MOD属性
#define 	MTL_STANDARD	(1<<0)
#define 	MTL_SHELL		(MTL_STANDARD<<1)

#define 	OBJ_BAKED		(MTL_STANDARD<<2)
#define 	OBJ_KEYFRAME	(MTL_STANDARD<<3)

//////////////////////////////////////////////////////////////////////////
// 为新树MagicTree定义的枚举类型
enum	E_DIVIDE_TYPE
{
	DIVIDE_NONE,
	DIVIDE_BINARY,
	DIVIDE_QUAD,	
	DIVIDE_OCT
};

enum	E_TREENODE_TYPE
{	
	TREENODE_QUAD1,
	TREENODE_QUAD2,
	TREENODE_QUAD3,
	TREENODE_QUAD4,
	TREENODE_PARENT,
	TREENODE_QUAD12,
	TREENODE_QUAD1234,
	TREENODE_ANYSON,
	TREENODE_LEAF
};

enum	E_RETURN_TYPE
{
	RETURN_FALSE,
	RETURN_TRUE,
	RETURN_SUCCESS,
	RETURN_FAIL,
	RETURN_ABORT
};
//////////////////////////////////////////////////////////////////////////

typedef	std::vector<vgKernel::Vec3*>	Vec3PtrArray;

#define VG_MODEL		    0
#define VG_OBJECT		    1
#define VG_BILLBOARD		2

#define VG_CAMERA		    4
#define VG_LIGHT		    5
#define VG_PARTICLE			6

#define VG_OBJECT_BAKED		7
#define VG_OBJECT_BAKED_KEY	8
#define VG_OBJECT_KEYFRAME	9

#define VG_WATER			10
#define VG_GLASS			11
#define VG_METAL			12
#define VG_MIRROR			13	

#define VG_SKYBOX			14	
#define VG_BRIGHTFLOOR		15

#define VG_AVINODE			16
#define VG_DYNAMICTEXNODE	17
#define VG_DYNAMICBILLBOARDNODE 18

#define VG_AUTOBUILD		19

#endif