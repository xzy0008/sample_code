
#ifndef _VGOBJECTNODE_H_INCLUDED_
#define _VGOBJECTNODE_H_INCLUDED_

#include "vgMod.h"

class tMatandFace;

class t3DObject 
{
public:
	// 物体标识
	char strName[20];			// 名称

	// 纯空间坐标点
	int	numOfVerts;				// 数目
	CVector3	 *pVerts;		// 坐标

	// 纯网格面
	int	numOfFaces;				// 数目
	tFace2	  *pFacesForSW;		// 索引

	// 最终渲染网格点
	int	numOfVertexs;			// 数目
	CVector2	*texcoord2D;	// 第一通道纹理坐标
	CVector3	*normal3D;		// 法线
	CVector3	*postion3D;		// 坐标
	CVector2	*texcoord2DLit;	// 第三通道纹理坐标（支持烘焙的灯光纹理图）

	// 临时数据
	CVector3  *pNormalOfFaces;	// 面法线	
	tFace	*pFaces;			// 索引

	// 衍生数据
	sw_FaceIndex	*shadowFace;// 阴影面索引

	int numOfFaceNoMaterail;    // 无材质面数目
	tFace2 *pFaceNoMaterail;	// 无材质面索引

	int	numOfRenderInterface;	// 渲染接口数目
	vector<tMatandFace*>	RenderInterface;// 渲染接口索引（按材质）

	//float maxx,minx,maxz,minz , maxy ,miny;   // 包围盒
	CVector3	m_maxPoint;
	CVector3	m_minPoint;

	// 其它...
	bool			m_bIsBaked;
	int				m_nObjectType;
	int				m_nKeyFramesCount;
	ModKeyFrame*	m_pKeyFrames;

public:
	t3DObject();
	~t3DObject();

public:
	//Write To Mod File	
	bool	Write(FILE* pFile, MeshMtlList* pMeshList, int nVersionMod);
	//Reset all data member
	bool	reset();
	//Set default value for data member
	bool	initilize();

private:
	//	Part 1: 物体属性
	bool	writeHeader();
	//	Part 2: 材质信息
	bool	writeMaterial();
	//	Part 3: 点数据
	bool	writeVetex();
	//	Part 4: 面数据
	bool	writeFace();
	//	Part 5: 阴影数据
	bool	writeShadow();
	//	Part 6: 关键帧数据
	bool	writeKeyFrame();
	//  Part 7: 变更数据
	bool	writeChange();

private:
	FILE*	m_pFile;
	MeshMtlList*	m_pTheMtls ;
	int		m_nPosRenderType;
	int		m_nRenderType;
	unsigned int	m_nVersionMod;
};

//	tMatandFace
class tMatandFace 
{
public:
	char strName[255];
	int numOfFace;
	tFace2 *RenderFace;
	unsigned int textureId;
	short *FaceID;
	bool bHasTexture;			// This is TRUE if there is a texture map for this object
	unsigned char red;
	unsigned char green;
	unsigned char blue;

	// 2008年3月6日15:52:08 添加
	char strNameBaked[255];

public:
	tMatandFace();
	~tMatandFace();
};

#endif//_VGOBJECTNODE_H_INCLUDED_
