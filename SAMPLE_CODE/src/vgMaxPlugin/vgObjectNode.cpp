#include <vgStableHeaders.h>
#include "vgObjectNode.h"
 

//t3DObject //////////////////////////////////////////////////////////////////////////
t3DObject::t3DObject()
{
	pVerts =NULL;
	pFacesForSW =NULL;
	texcoord2D = NULL;normal3D =NULL; postion3D =NULL; texcoord2DLit =NULL; 
	pNormalOfFaces =NULL; pFaces =NULL; shadowFace =NULL; pFaceNoMaterail =NULL;
	m_pKeyFrames = NULL;

	m_nPosRenderType = m_nRenderType = m_nVersionMod = 0;
	m_pFile = NULL;
	m_pTheMtls = NULL;

	numOfVerts = numOfFaces = numOfVertexs = numOfFaceNoMaterail = 
		numOfRenderInterface= 0;

	m_bIsBaked = false;
	m_nObjectType = 0;
	m_nKeyFramesCount = 0;

	initilize();
}

t3DObject::~t3DObject()
{
	reset();
}

bool	t3DObject::reset()
{
	if (pVerts)
	{
		delete[] pVerts;
		pVerts = NULL;
	};

	if (pFacesForSW)
	{
		delete[] pFacesForSW;
		pFacesForSW = NULL;
	};

	if (texcoord2D)
	{
		delete[] texcoord2D;
		texcoord2D = NULL;
	};
	if (normal3D)
	{
		delete[] normal3D;
		normal3D = NULL;
	};

	if (postion3D)
	{
		delete[] postion3D;
		postion3D = NULL;
	};

	if (texcoord2DLit)
	{
		delete[] texcoord2DLit;
		texcoord2DLit = NULL;
	};

	if (pNormalOfFaces)
	{
		delete[] pNormalOfFaces;
		pNormalOfFaces = NULL;
	};

	if (pFaces)
	{
		delete[] pFaces;
		pFaces = NULL;
	};

	if (shadowFace)
	{
		delete[] shadowFace;
		shadowFace = NULL;
	};

	if (pFaceNoMaterail)
	{
		delete[] pFaceNoMaterail;
		pFaceNoMaterail = NULL;
	};

	if (m_pKeyFrames)
	{
		delete[] m_pKeyFrames;
		m_pKeyFrames = NULL;
	};

	vector<tMatandFace*>::iterator iter = RenderInterface.begin();
	vector<tMatandFace*>::iterator iterEnd = RenderInterface.end();
	for ( ; iter != iterEnd; iter++)
	{
		if (*iter)
		{
			delete *iter;
			*iter = NULL;
		}
	}

	return	true;
}
bool	t3DObject::initilize()
{
	//m_nVersionMod	= VERSION_MOD_CURRENT;//VERSION_MOD(year, updateTime);

	return	true;
}

bool	t3DObject::Write(FILE* pFile, MeshMtlList* pMeshList, int nVersionMod)
{
	m_pFile = pFile;
	m_pTheMtls = pMeshList;
	m_nVersionMod = nVersionMod;

	//	Part 1: 物体属性
	writeHeader();
	//	Part 2: 材质信息
	writeMaterial();
	//	Part 3: 点数据
	writeVetex();
	//	Part 4: 面数据
	writeFace();
	//	Part 5: 阴影数据
	writeShadow();

	if(	m_nVersionMod	>=	VERSION_MOD(2008, 6) )
	{
		//	Part 6: 关键帧数据
		writeKeyFrame();
	}

	//  Part 7: 变更数据
	writeChange();

	fseek( m_pFile, 0 , SEEK_END ) ;

	return true;
}

bool	t3DObject::writeHeader()
{
	int		intReserved = 0;
	float	fltReserved = 0.0f;
	char	strReserved[20] ;
	memset( strReserved, 0, 20);

	//	part 1: 最小点最大点
	fwrite(&m_minPoint , sizeof(CVector3) , 1, m_pFile);
	fwrite(&m_maxPoint , sizeof(CVector3) , 1, m_pFile);

	//	part 2: 中心点
	CVector3	centerPoint;
	centerPoint.x = (m_minPoint.x + m_maxPoint.x)*0.5f ;
	centerPoint.y = (m_minPoint.y + m_maxPoint.y)*0.5f;
	centerPoint.z = (m_minPoint.z + m_maxPoint.z)*0.5f ;
	fwrite(&centerPoint , sizeof(CVector3) , 1, m_pFile);


	//	part 3: 物体类型（为平台预留）
	fwrite(&m_nObjectType, sizeof(int), 1, m_pFile);

	//	part 4: 物体面数
	fwrite(&numOfFaces , sizeof(int), 1, m_pFile);

	//	part 5: 物体名字
	fwrite(strName,  sizeof(strName)  , 1, m_pFile);

	//	part 6: 渲染类型
	m_nPosRenderType = ftell( m_pFile );
	fwrite(&m_nRenderType, sizeof(int), 1, m_pFile);

	return true;
}

bool	t3DObject::writeMaterial( )
{
	int	k	= 0;

	fwrite(&numOfRenderInterface , sizeof(int), 1, m_pFile);

	int  objChunkPos,objChunkLength ;
	for (int i= 0 ; i < numOfRenderInterface ; i++)
	{
		objChunkPos = ftell( m_pFile );
		for (int j = 0; j < m_pTheMtls->Count() ; j++)
		{
			SMtl*savemtl = (*m_pTheMtls)[j].sm ;
			if ( strcmp( RenderInterface[i]->strName, savemtl->name ) == 0 )
			{
				if ( savemtl->bHasAlpha == true)
				{
					k = 1;
					// 2007/10/8 LIANGKAI 新加：
					m_nRenderType = 1;
				}
				else
					k = 0;
				fwrite(&k , sizeof(int), 1, m_pFile);

				//strcat_s( strTemp, savemtl->name );
				fwrite( savemtl->name ,  255  , 1, m_pFile);

				//strcat_s( strTemp, savemtl->diffuseBitmap );				
				fwrite( savemtl->diffuseBitmap ,  255  , 1, m_pFile);

				//strcat_s( strTemp, savemtl->opacityBitmap );
				fwrite( savemtl->opacityBitmap,  255  , 1, m_pFile);

				fwrite( &savemtl->diffColor , 3 , 1, m_pFile);
				unsigned int  tmpID = 0;
				fwrite( &tmpID , sizeof( unsigned int ) , 1, m_pFile);
				//				break;			
			}// if ( strcmp(RenderInterface[i].strName, mod.pMaterials[j].strName) == 0 )

			// 2008年3月6日16:10:03 添加
			char  strTemp1[255] = "", strTemp2[255] = "";
			strcat_s( strTemp1,  RenderInterface[i]->strNameBaked );				
			strcat_s( strTemp2,  savemtl->name );				

			if ( m_nObjectType & OBJ_BAKED
				&& ( strcmp(strTemp1, strTemp2) == 0 ) )
			{
				//strcat_s( strTemp, savemtl->diffuseBitmap );				
				fwrite( savemtl->diffuseBitmap  ,  255  , 1, m_pFile);
				break;
			}			
		}// for (int j = 0; j < mod.numOfMaterials ; j++)

		objChunkLength = ftell(m_pFile) - objChunkPos;
		objChunkLength = objChunkLength;
	}

	return true;
}

bool	t3DObject::writeVetex()
{
	fwrite(&numOfVertexs , sizeof(int) , 1, m_pFile);

	for ( int indexOfVertex=0; indexOfVertex < numOfVertexs ; indexOfVertex++ )
	{
		fwrite( &texcoord2D[ indexOfVertex ] , sizeof(CVector2) , 1, m_pFile );
		fwrite( &normal3D[ indexOfVertex ] ,   sizeof(CVector3) , 1, m_pFile );
		fwrite( &postion3D[ indexOfVertex ]  , sizeof(CVector3) , 1, m_pFile );
		if (  m_nObjectType & OBJ_BAKED  )
		{
			fwrite( &texcoord2DLit[ indexOfVertex ] , sizeof(CVector2)  , 1, m_pFile );
		}
	}

	return true;
}

bool	t3DObject::writeFace( )
{
	for (int i = 0; i < numOfRenderInterface; i++)
	{
		fwrite(&RenderInterface[i]->bHasTexture , sizeof(bool) , 1, m_pFile);
		fwrite(&RenderInterface[i]->numOfFace , sizeof(int) , 1, m_pFile);
		fwrite(RenderInterface[i]->RenderFace , sizeof(tFace2) * RenderInterface[i]->numOfFace , 1, m_pFile);
	}
	/////////////////////////////无材质面信息 面数和面索引数组
	fwrite(&numOfFaceNoMaterail , sizeof(int) , 1, m_pFile);

	fwrite(pFaceNoMaterail , sizeof(tFace2) * numOfFaceNoMaterail  , 1, m_pFile);

	return true;
}

bool	t3DObject::writeShadow( )
{
	fwrite(pNormalOfFaces, sizeof(CVector3) * numOfFaces, 1, m_pFile);

	fwrite(&numOfVerts , sizeof(int) , 1, m_pFile);
	fwrite(pVerts, sizeof(CVector3) * numOfVerts, 1, m_pFile);

	fwrite(shadowFace, sizeof(sw_FaceIndex) * numOfFaces, 1, m_pFile);

	return true;
}


bool	t3DObject::writeKeyFrame( )
{
	//	写入关键帧数据
	fwrite( &m_nKeyFramesCount, sizeof(int), 1, m_pFile);
	fwrite( m_pKeyFrames, sizeof(ModKeyFrame)*m_nKeyFramesCount, 1, m_pFile);

	return true;
}


bool	t3DObject::writeChange()
{
	//	改写物体头信息， 渲染方式RenderType
	fseek( m_pFile, m_nPosRenderType, SEEK_SET );
	fwrite(&m_nRenderType, sizeof(int) , 1, m_pFile);

	fseek( m_pFile, 0 , SEEK_END ) ;

	return true;
}


//class tMatandFace/////////////////////////////////////////////////////////////////

tMatandFace::tMatandFace()
{
	RenderFace = NULL;
	FaceID = NULL;
}
tMatandFace::~tMatandFace()
{
	if (RenderFace)
	{
		delete[] RenderFace;
		RenderFace = NULL;
	}
	if (FaceID)
	{
		delete[] FaceID;
		FaceID = NULL;
	}
}