#include "vgStableHeaders.h"

#include <vgMod/vgObjectSet.h>

// t3DModel		//////////////////////////////////////////////////////////////////////
#if	IMPORT_MAX_LIB
t3DModel::t3DModel(std::string name, MeshMtlList* pMtls, Interface* pMaxInterface)
//:m_strModelName(name)
: m_pTheMtls(pMtls)
//, m_pMaxInterface(pMaxInterface)
{
	m_nTotalFaceCount = 0;

	m_pFile = NULL;
	m_puObjPos = NULL;
	m_uiObjPosPos = 0;

	setDefault();
}
#endif

t3DModel::t3DModel( std::string name, MeshMtlList* pMtls )
: m_pTheMtls(pMtls)
{
	m_nTotalFaceCount = 0;

	m_pFile = NULL;
	m_puObjPos = NULL;
	m_uiObjPosPos = 0;

	setDefault();
}

t3DModel::~t3DModel()
{
	reset();
}
void	t3DModel::push_back(t3DObject* pObject)
{
	m_vObject.push_back(pObject);
	m_vObjectType.push_back(pObject->m_nObjectType);
	m_vIsBaked.push_back(pObject->m_bIsBaked);

	m_boundingBox.merge( pObject->getBoundingBox() );
	m_nTotalFaceCount += pObject->m_nNumOfFaces;
}
int		t3DModel::size()
{
	return	(int)m_vObject.size();
}

bool	t3DModel::Write(FILE* pFile
						, TCHAR* pFormat, int nVersionMod/* = VERSION_MOD_CURRENT*/)
{
	m_pFile = pFile;

	_tcsncpy_s(m_sFormat, sizeof(m_sFormat), pFormat, sizeof(m_sFormat));
	m_nVersionMod = nVersionMod;

	//	Part 0: 物体属性
	writeFormat();
	
	//	Part 1: 物体属性
	writeHeader();

	//	Part 2: 模型数据
	writeObjects();

	//	Part 3: 更新数据
	writeChange();

	fseek( m_pFile, 0 , SEEK_END ) ;

	return true;
}

bool	t3DModel::reset()
{
	vector<t3DObject*>::iterator iter = m_vObject.begin();
	vector<t3DObject*>::iterator iterEnd = m_vObject.end();
	for ( ; iter != iterEnd; iter++)
	{
		if (*iter)
		{
			delete *iter;
			*iter = NULL;
		}
	}
	m_vObject.clear();

	if(m_puObjPos)
	{
		delete	m_puObjPos;
		m_puObjPos = NULL;
	}

	return true;
}

bool	t3DModel::setDefault()
{
	//m_nVersionMod	= VERSION_MOD_CURRENT;//VERSION_MOD(year, updateTime);
	m_fScale = 1.0f;
	m_bSwapUVChannel = false;
	m_bFilterBaked = false;

	return	true;
}

bool	t3DModel::writeFormat()
{
	// Part 1: 格式信息
	fwrite( m_sFormat, sizeof(m_sFormat), 1, m_pFile);

	// Part 2: 版本信息
	fwrite( &m_nVersionMod, sizeof(unsigned int), 1,m_pFile );
	return true;
}
bool	t3DModel::writeHeader()
{
	//	Part 1: 场景中心坐标
	fwrite( &m_oSceneCenter, sizeof(CVector3), 1, m_pFile);

	int	nObjectCount = (int)m_vObject.size();
	//	Part 1: 物体总数
	fwrite( &nObjectCount, sizeof(int), 1,  m_pFile);

	//	Part 2: 物体位置数组
	m_uiObjPosPos = ftell(m_pFile);   //该位置的内容要变化
	m_puObjPos = new unsigned int[nObjectCount];
	fwrite( m_puObjPos, sizeof(unsigned int) * nObjectCount, 1,  m_pFile);

	//	Part 3: 物体类型（标准、烘焙、关键帧）数组
	if (m_nVersionMod == VERSION_MOD_CURRENT)
	{
		static TraverseVecForWriteObjectTypeInt	vecWriter(m_pFile);
		for_each( m_vObjectType.begin() ,m_vObjectType.end() ,vecWriter );
	}
	else if (m_nVersionMod == VERSION_MOD_LAST)
	{
		//static TraverseVecForWriteObjectType<bool> vecWriter(m_pFile);
		static TraverseVecForWriteObjectTypeBool	vecWriter(m_pFile);
		for_each( m_vIsBaked.begin() ,m_vIsBaked.end() ,vecWriter );
	}
	//static TraverseVecForWriteObjectTypeInt vecWriter(m_pFile);
	//for_each( m_vObjectType.begin() ,m_vObjectType.end() ,vecWriter );

	
	return	true;
}

bool	t3DModel::writeObjects()
{
	int index=0;
	for ( vector<t3DObject*>::iterator iter = m_vObject.begin();
		iter != m_vObject.end(); iter++, index++)
	{
		m_puObjPos[index] = ftell(m_pFile);

		fwrite( &m_uiObjChunkSize , sizeof(unsigned int), 1, m_pFile);

		//	每个物体的静态网格信息
		(*iter)->Write(m_pFile, m_pTheMtls, m_nVersionMod);

		// 更新进度显示
		//m_pMaxInterface->ProgressUpdate((int)((float)index / m_vObject.size() * 100.0f)); 
	}

	return	true;
}

bool	t3DModel::writeChange()
{
	unsigned int	uiFilePos = ftell(m_pFile);
	int	nObjectCount = (int)m_vObject.size();

	//	Part 4: 改写文件头， 物体位置
	fseek( m_pFile, m_uiObjPosPos , SEEK_SET);
	fwrite( m_puObjPos , sizeof(unsigned int) * nObjectCount , 1, m_pFile);//写入每个文件块的起始位置；

	//	Part 5: 改写物体头， 每个物体的块大小
	for (int i = 0; i < nObjectCount -1 ; i++)
	{
		m_uiObjChunkSize = m_puObjPos[i+1] - m_puObjPos[i] -4;
		fseek( m_pFile, m_puObjPos[i] , SEEK_SET);
		fwrite( &m_uiObjChunkSize , sizeof(unsigned int) , 1, m_pFile);
	}													//写入前n-1个文件块的长度；

	m_uiObjChunkSize = uiFilePos - m_puObjPos[nObjectCount - 1] -4;
	fseek( m_pFile, m_puObjPos[nObjectCount - 1] , SEEK_SET);
	fwrite( &m_uiObjChunkSize , sizeof(unsigned int) ,1 , m_pFile);

	fseek( m_pFile, 0 , SEEK_END ) ;//写入最后一个文件块的长度；

	return	true;
}
#if 0
void t3DModel::setModName( const std::string& name )
{
	m_strModelName = name;
}

std::string t3DModel::getModName()
{
	return m_strModelName;
}
#endif
CBox3& t3DModel::getBoundingBox()
{
	return m_boundingBox;
}

void t3DModel::setFlagFilterBaked( bool filter )
{
	m_bFilterBaked = filter;
}

bool t3DModel::getFlagFilterBaked()
{
	return m_bFilterBaked;
}

void t3DModel::setFlagSwapChannel( bool swap )
{
	m_bSwapUVChannel = swap;
}

bool t3DModel::getFlagSwapChannel()
{
	return m_bSwapUVChannel;
}

void t3DModel::setFlagEnableTexture( bool texture )
{
	m_bEnableTexture = texture;
}

bool t3DModel::getFlagEnableTexture()
{
	return m_bEnableTexture;
}

void t3DModel::setScale( float scale )
{
	m_fScale = scale;
}

float	t3DModel::getScale()
{
	return m_fScale;
}

void t3DModel::setSceneCenter( CVector3 pos )
{
	m_oSceneCenter = pos;
}

vgMath::CVector3 t3DModel::getSceneCenter()
{
	return m_oSceneCenter;
}

#if	IMPORT_MAX_LIB

void 
t3DModel::dumpObjListProcessNoUI()
{
	int ox = 0,ix=1;
	ObjectEntry*	oe = m_pTheObjects->head;
	SceneEntry*		se = m_pTheSceneEnum->head;
	Object *obj;

	for (; 
		oe != NULL; 
		oe = oe->next,ox++,ix++, se = se->next) 
	{
		// 新建一个 t3DObject newobj 结构体
		newobj = new t3DObject(this);
		obj = oe->entry->obj;
		oe->tri = (TriObject *)obj->ConvertToType(m_pTheSceneEnum->i->GetTime(), triObjectClassID);

		if(!oe->tri)
		{
			delete newobj;
			newobj = NULL;
			continue;
		}

		// 获取一个物体的信息暂存至内存对象newobj
		E_Return_Type status = collectGeoDataForEachObjNoUI(oe);//ExportModel(OBJECT_HEAD,oe); 

		// 过滤有缺陷的模型或根据具体条件筛选
		if( filterFaultyObject(se->node, status) )
			continue;

		// 类型OBJ_BAKED用途供扩展，暂时用于版本兼容
		if ( newobj->isBakedType() )
		{
			newobj->m_nObjectType |= MTL_STANDARD;
			newobj->m_nObjectType |= MTL_SHELL;
		}

		this->push_back(newobj);

		newobj = NULL;
	}
}

E_Return_Type 
t3DModel::collectGeoDataForEachObjNoUI( ObjectEntry *oe )
{
	// Part 1:物体名字
	string name(oe->entry->name); 

	name = name.substr(0, 20);
	newobj->setObjectName( string(name.data()) );

	//  计算每个物体的点和面信息
	newobj->computerVerts( oe );

	//  计算每个物体的包围盒
	Box3 objBox = getObjectBox( oe );
	newobj->setBoundingBox(objBox);

#if SWITCH_MOD_EXPORT_NORMAL
	//  计算每个物体所有点的法向量
	newobj->computerNormal();
#endif

#if SWITCH_MOD_EXPORT_SHADOW
	//  计算阴影结构体sw_faces
	newobj->computerShadowFaces();
#endif


	//  衍生计算mod渲染接口
	if ( RETURN_MTL_MULTITEX_NEST == newobj->computerMatAndFace(oe) )
	{
		return RETURN_MTL_MULTITEX_NEST;
	}

	return	RETURN_TRUE;
}

bool t3DModel::filterFaultyObject( INode* pNode, E_Return_Type status )
{
	//  过滤模型case1：点数或面数为零, 如果点数或面数为零，则滤除该物体
	if (
		((newobj->m_nNumOfVerts == 0)
		||(newobj->m_nNumOfFaces == 0))
		) 
	{
		delete newobj;
		newobj = NULL;
		return true;
	}

	//	过滤模型case2：多维子嵌套
	if ( RETURN_MTL_MULTITEX_NEST == status /*&& g_bMulti2Text*/) //默认滤除
	{
		delete newobj;
		newobj = NULL;
		return true;
	}

	//	获取每个物体的关键帧信息
	//ComputerKeyFrames(pNode);

	//	过滤模型case4：滤除关键帧	物体			

	//	过滤模型case5：滤除非关键帧物体				
	if ( 
		(0 != newobj->m_nKeyFramesCount)
	)
	{
		delete newobj;
		newobj = NULL;
		return true;
	}
	return false;
}

Box3 t3DModel::getObjectBox( ObjectEntry* oe )
{
	Box3 bb;
	ViewExp *vpt = m_pTheSceneEnum->i->GetViewport(NULL);

	oe->tri->GetWorldBoundBox(m_pTheSceneEnum->i->GetTime(), 
		oe->entry->node, 
		vpt, 
		bb);

	return bb;
}
#endif
// t3DModel		//////////////////////////////////////////////////////////////////////
