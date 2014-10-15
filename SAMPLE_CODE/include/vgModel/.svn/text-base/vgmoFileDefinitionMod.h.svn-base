


#ifndef __VGMO_FILEDEFINITION_H__
#define __VGMO_FILEDEFINITION_H__
#include <vgModel/vgmoDefinition.h>
#include <vgKernel/vgkForward.h>

	
namespace vgModel {



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
		ModIndex( int numofobjs );
		~ModIndex();
		uint		_numberOfObjects;
		long*	_objectsPos;
		bool*	_bakedFlag;

		bool* _keyframeFlag;
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
		int	 p1;
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


	
	
}// end of namespace vgModel
	


#endif // end of __VGMO_FILEDEFINITION_H__