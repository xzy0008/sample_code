


#ifndef __VGMFILEDEFINITION_H__
#define __VGMFILEDEFINITION_H__


#include <vgMesh/vgmDefinition.h>
#include <vgKernel/vgkForward.h>

	
namespace vgMesh {



#define		VERSION_MOD(year, updateTime)	(	( (year)<<16 )	+	(updateTime)	)
#define		VERSION_1						VERSION_MOD(0,		100	)
#define		VERSION_4						VERSION_MOD(2008,	4	)



	/**
		@date 	2008/07/01  19:33	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class ModHeader
	{
	public:
		ModHeader()
		{
			
		}
		~ModHeader()
		{
			
		}
	
	
	public:
		char	_headerFourCC[32];
		unsigned int		_version;
		int		_numberOfObjects;
	
	

	};
	
	class ModIndex
	{
	public:
		ModIndex( int numofobjs )
		{
			assert( numofobjs != 0 );
			_numberOfObjects = numofobjs;
			_objectsPos = new long[_numberOfObjects];
			_bakedFlag = new bool[_numberOfObjects];
		}
		~ModIndex()
		{
			if ( _objectsPos != NULL )
			{
				delete _objectsPos;
				_objectsPos = NULL;
			}

			if ( _bakedFlag != NULL )
			{
				delete _bakedFlag;
				_bakedFlag = NULL;
			}
		}
		uint		_numberOfObjects;
		long*	_objectsPos;
		bool*	_bakedFlag;
	};

#pragma pack(push,1) 

	struct MaterialInfoStruct
	{
		int aphlatext;
		char  strName[255];			// The texture name
		char  strFile[255];			// The texture file name (If this is set it's a texture map)

		char  alphaFile[255];
		unsigned char  color[3];				// The color of the object (R, G, B)
		unsigned int   texureId;				// the texture ID
	};

	struct MaterialInfoStruct2 
	{
		int aphlatext;
		char  strName[255];			// The texture name
		char  strFile[255];			// The texture file name (If this is set it's a texture map)

		char  alphaFile[255];
		unsigned char  color[3];				// The color of the object (R, G, B)
		unsigned int   texureId;				// the texture ID

		char  strFileBaked[255];  
		//char  byteReserved;
	};

	struct MaterialStruct
	{
		MaterialInfoStruct materialinfo;

		long fileoffset;
	};

	struct MaterialStruct2
	{
		MaterialInfoStruct2 materialinfo;

		long fileoffset;
	};

#pragma  pack(pop)

	struct FaceIndex
	{
		int x;
		int y;
		int z;
	};

	struct MaterialFaces 
	{
		bool b_hastexture;
		int m_numOfFace;
		FaceIndex *pFace;
	};



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

	struct ShadowFaceIndex
	{
		int	p1;
		int p2;
		int p3;

		int	normal;

		int	p1p2AdjFaceIndex;
		int	p2p3AdjFaceIndex;
		int	p3p1AdjFaceIndex;

		bool faceVisible;

		bool p1p2Visible;
		bool p2p3Visible;
		bool p3p1Visible;	
	};


	
	
}// end of namespace vgMesh
	


#endif // end of __VGMFILEDEFINITION_H__