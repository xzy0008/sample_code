
#ifndef _VGOBJECTNODE_H_INCLUDED_
#define _VGOBJECTNODE_H_INCLUDED_

#include <vgMod/vgStruct_Mod.h>
#include <vgMod/vgModDefs.h>

class tMatandFace;
class t3DModel;
class t3DObject 
{
public:// 原始数据
	// 物体标识
	char		m_strName[20];			// 名称

	// 纯空间坐标点
	int			m_nNumOfVerts;			// 纯点数目
	CVector3*	m_pVertsOriginal;		// 纯点坐标

	// 纯网格面
	int			m_nNumOfFaces;			// 纯面数目
	tFace2*		m_pFacesForShadow;		// 纯面索引

	// 最终渲染网格点，交错数组
	int			m_nNumOfTVerts;			// 纹理点数目
	CVector2*	m_pTexcoord2D;			// 纹理点坐标，第一通道
	CVector3*	m_pVertNormal3D;		// 法线
	CVector3*	m_pPostion3D;			// 点坐标，交错数组
	CVector2*	m_pTexcoord2DLit;		// 纹理点坐标，第三通道（支持烘焙的灯光纹理图）

	// 临时数据
	CVector3*	m_pFaceNormal3D;		// 面法线	
	tFace*		m_pFacesAll;			// 所有面索引

public:// 衍生数据
	int			m_numOfFaceNoMaterail;	// 无材质面数目
	tFace2*		m_pFaceNoMaterail;		// 无材质面索引

	int	m_nNumOfRenderInterface;		// 有材质面片的渲染接口数目（按材质）
	vector<tMatandFace*>	m_vecRenderInterface;// 渲染接口索引（按材质）
	
	CBox3		m_boundingBox;			// 包围盒

	bool			m_bIsBaked;
	int				m_nObjectType;
	int				m_nKeyFramesCount;
	ModKeyFrame*	m_pKeyFrames;

	sw_FaceIndex	*m_shadowFace;// 阴影面索引

private:// 临时数据
	FILE*			m_pFile;
	MeshMtlList*	m_pTheMtls ;
	int				m_nPosRenderType;
	int				m_nRenderType;
	unsigned int	m_nVersionMod;


	t3DModel*		m_pParentScene;

public:
	t3DObject(t3DModel* pParentScene = NULL);
	~t3DObject();

public:
	//Write To Mod File	
	int	Write(FILE* pFile, MeshMtlList* pMeshList, int nVersionMod);
	//Reset all data member
	bool	reset();
	//Set default value for data member
	bool	initilize();


public:
	bool	isBakedType();
	void	setStandardType();
	void	setBakedType();

public:
	//bool	computerBound();
	CBox3&	getBoundingBox();

	void	setObjectName(string name);
	void	formatRenderData();

#if	IMPORT_MAX_LIB
	int		computerVerts( ObjectEntry *oe );
	E_Return_Type computerMatAndFace( ObjectEntry *oe );
	E_Return_Type collectMtlDataForEachObj( Mtl*mtl );
	void setMtlType( INode* node, MeshMtlList* pTheMtls );
	void	setBoundingBox(Box3 box);
#endif

	int		computerNormal();
	int		computerShadowFaces();
	void	computerMatandFaceEach(tMatandFace* newrender);



public:
	// 读写网格的点线面
	void			SetVertsCount(int count);
	void			SetTVertsCount(int count);
	void			SetFacesCount(int count);
	
	void			PutVertex(int index,Verts *v);
	void			PutTVertex(int index,CVector2 *v);
	void			PutFace(int index,Faces *f);
	
	//void			PutSmooth(int index,unsigned long smooth);
	//void 			PutFaceMtl(int index, int imtl);
	//void 			SetTVerts(int nf, Faces *f);

private:
	//  构造交错数组
	void	computerVertexArray();
	//	构造渲染接口，由材质索引面，再索引点
	void	computerRenderInterface();


	int sw_searchForAdjacent(int faceid , int& point1 , int& point2 );
	
	void setVertexArraySize( int nVertexArraySize );
	void setFaceCount(int nFaceCount);

	bool computerBound();

private:
	//	Part 1: 物体属性
	int	writeHeader();
	//	Part 2: 材质信息
	int	writeMaterial();
	//	Part 3: 点数据
	int	writeVetex();
	//	Part 4: 面数据
	int	writeFace();
	//	Part 5: 阴影数据
	int	writeShadow();
	//	Part 6: 关键帧数据
	int	writeKeyFrame();
	//  Part 7: 变更数据
	int	writeChange();
private:// 材质数据
	/*BitArray	bFaceOfMatOne;
	BitArray	bFaceOfMatAll;
	BitArray	vertFlag;*/
	vector<bool>	bFaceOfMatOne;
	vector<bool>	bFaceOfMatAll;
	vector<bool>	vertFlag;
	
	long		totleFaceWithMat;

	//Tab<int> mtlNumMap;
	vector<int> mtlNumMap;
	int mtlnum;
	int bakedMtlNo ;
	BOOL multiMtl;

	bool bTexture ;
#if	IMPORT_MAX_LIB
	Mesh* newmesh;
#endif
	tMatandFace*	newrender ;			//	当前材质面索引指针

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
