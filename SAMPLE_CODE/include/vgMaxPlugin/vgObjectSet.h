
#ifndef _VGOBJECTSET_H_INCLUDED_
#define _VGOBJECTSET_H_INCLUDED_


#include "vgMod.h"
#include "vgObjectNode.h"

//	t3DModel
class t3DModel 
{
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

public:
	int  m_nObjectCount, m_nTotalFaceCount;
	char m_strModelName[255];		// 模型的名称
	char m_strFileName[255];			// 模型文件的名称

	vector<t3DObject*> m_vObject;
	vector<int> m_vObjectType;
	vector<bool> m_vIsBaked;

public:
	t3DModel();
	~t3DModel();

public:
	void	push_back(t3DObject* pObject);
	int		size();

public:
	//Write To Mod File	
	bool	Write(FILE* pFile, MeshMtlList* pMeshList, Interface* pMaxInterface, 
		TCHAR* pFormat, int nVersionMod = VERSION_MOD_CURRENT);
	//Reset all data member
	bool	reset();
	//Set default value for data member
	bool	initilize();

private:
	bool	writeFormat();
	bool	writeHeader();
	bool	writeObjects();
	bool	writeChange();

public:// Write To Mod File
	FILE*	m_pFile;
	MeshMtlList*	m_pTheMtls ;
	Interface*		m_pMaxInterface;

	TCHAR			m_sFormat[32];
	unsigned int	m_nVersionMod;
	CVector3		m_oSceneCenter;

	unsigned int*	m_puObjPos ;		//	各个物体在文件中的偏移数组
	unsigned int	m_uiObjPosPos ;		//	物体偏移数组在文件中的位置
	unsigned int	m_uiObjChunkSize;
};

#endif//_VGOBJECTSET_H_INCLUDED_