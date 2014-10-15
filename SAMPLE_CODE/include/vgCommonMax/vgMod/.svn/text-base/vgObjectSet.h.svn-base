
#ifndef _VGOBJECTSET_H_INCLUDED_
#define _VGOBJECTSET_H_INCLUDED_


#include <vgMod/vgStruct_Mod.h>
#include <vgMod/vgObjectNode.h>

//	t3DModel
class t3DModel 
{
public:// 属性数据
	TCHAR				m_sFormat[32];
	unsigned int		m_nVersionMod;


public:// 原始数据
	vector<t3DObject*>	m_vObject;


public:// 衍生数据
	int					m_nTotalFaceCount;	// 总面数
	
	vector<int>			m_vObjectType;		// 模型类型队列（新）
	vector<bool>		m_vIsBaked;			// 模型类型队列（旧）

	CVector3			m_oSceneCenter;
	CBox3				m_boundingBox;


private:// 临时数据
	FILE*			m_pFile;
	MeshMtlList*	m_pTheMtls ;
	//Interface*		m_pMaxInterface;
	t3DObject*		newobj ;			//	当前物体指针

#if	IMPORT_MAX_LIB
	SceneEnumProc*	m_pTheSceneEnum ;		//	全局场景接口
	ObjectList*		m_pTheObjects ;		//	全局物体接口

	Matrix3			m_TransformMatrix;
#endif
	float			m_fScale;
	bool			m_bFilterBaked;
	bool			m_bSwapUVChannel;

	BOOL			m_bEnableTexture;

	unsigned int*	m_puObjPos ;		//	各个物体在文件中的偏移数组
	unsigned int	m_uiObjPosPos ;		//	物体偏移数组在文件中的位置
	unsigned int	m_uiObjChunkSize;

public:
#if	IMPORT_MAX_LIB
	t3DModel(std::string name, MeshMtlList* pMtls, Interface* pMaxInterface);
#endif
	
	~t3DModel();

	t3DModel(std::string name, MeshMtlList* pMtls);

public:
	void	push_back(t3DObject* pObject);
	int		size();

public:
	//Write To Mod File	
	bool	Write(FILE* pFile, 
		TCHAR* pFormat, int nVersionMod = VERSION_MOD_CURRENT);
	//Reset all data member
	bool	reset();
	//Set default value for data member
	bool	setDefault();

public:
	void	setModName(const std::string& name);
	std::string	getModName();

	CBox3&	getBoundingBox();
	

	MeshMtlList*	getMeshMtlList()	{return m_pTheMtls;}
	//Interface*		getMaxInterface()	{return m_pMaxInterface;}

	void dumpObjListProcessNoUI();
	

public:
	void	setFlagFilterBaked(bool filter);
	bool	getFlagFilterBaked();

	void	setFlagSwapChannel(bool swap);
	bool	getFlagSwapChannel();

	void	setFlagEnableTexture(bool texture);
	bool	getFlagEnableTexture();

	void	setScale(float scale);
	float	getScale();

	void		setSceneCenter(CVector3 pos);
	CVector3	getSceneCenter();

#if	IMPORT_MAX_LIB
	SceneEnumProc*	getSceneEnumProc()	{return m_pTheSceneEnum; }		//	全局场景接口
	ObjectList*		getObjectList()		{return m_pTheObjects; }		//	全局物体接口


	void	setSceneEnumProc(SceneEnumProc*pProc)	{m_pTheSceneEnum = pProc; }		//	全局场景接口
	void	setObjectList(ObjectList*pObs)		{m_pTheObjects = pObs; }		//	全局物体接口
	void	setTransformMatrix(Matrix3 *transform) { m_TransformMatrix = *transform; }
	
	E_Return_Type collectGeoDataForEachObjNoUI( ObjectEntry *oe );
	bool	filterFaultyObject(INode* pNode, E_Return_Type status);

	Box3	getObjectBox(ObjectEntry* oe);
#endif

private:


private:
	bool	writeFormat();
	bool	writeHeader();
	bool	writeObjects();
	bool	writeChange();
	class TraverseVecForWriteObjectTypeInt
	{
	public:
		inline void operator() ( int nObjectType) 
		{
			fwrite( &nObjectType, sizeof(int), 1,  m_pFile);
		}

	public:
		TraverseVecForWriteObjectTypeInt(FILE* pFile)
			:m_pFile(pFile)	{}
	private:
		FILE*	m_pFile;		
	};

	class TraverseVecForWriteObjectTypeBool
	{
	public:
		inline void operator() ( bool bIsBaked) 
		{
			fwrite( &bIsBaked, sizeof(bool), 1,  m_pFile);
		}

	public:
		TraverseVecForWriteObjectTypeBool(FILE* pFile)
			:m_pFile(pFile)	{}
	private:
		FILE*	m_pFile;		
	};

	template< class T >
	class TraverseVecForWriteObjectType
	{
	public:
		template< class T >
		inline void operator() ( T nObjectType) 
		{
			fwrite( &nObjectType, sizeof(T), 1,  m_pFile);
		}

	public:
		TraverseVecForWriteObjectType(FILE* pFile)
			:m_pFile(pFile)	{}
	private:
		FILE*	m_pFile;		
	};
};

#endif//_VGOBJECTSET_H_INCLUDED_