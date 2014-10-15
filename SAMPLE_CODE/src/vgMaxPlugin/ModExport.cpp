#include <vgStableHeaders.h>

//#include <vgModel/vgmoFileWriterModToVmd.h>

#include <vgKernel/vgkStringUtility.h>
/**********************************************************************
*<
vgModelExp.cpp:	.MOD格式 场景导出插件接口及功能设计

主要内容是：
1、DLL入口DLLMain函数实现
2、插件的5个接口函数实现
3、插件功能类class vgModExportor 定义及其实现
4、插件描述类class vgModClassDesc 定义及其实现
*>	
**********************************************************************/
#include "ModExport.h"
#include "vgModelExpres.h"

//////////////////////////////////////////////////////////////////////////
//  DLL入口	  ///////////////////////////////////////////////////////////
BOOL WINAPI DllMain(HINSTANCE hinstDLL,ULONG fdwReason,LPVOID lpvReserved) 
{
	if( fdwReason == DLL_PROCESS_ATTACH )
	{
		hInstance = hinstDLL;
		DisableThreadLibraryCalls(hInstance);
	}

	return (TRUE);
}
/////////////////////////////////////////////////////////////////// DLL入口	  
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//	插件的5个接口函数 	//////////////////////////////////////////////////
//  特别地，3ds max调用插件导出功能的过程如下: 
//          3ds max
//			->接口函数	LibClassDesc
//          ->插件描述类vgModClassDesc
//          ->插件功能类vgModExportor
//          ->插件功能	DoExport
static vgModClassDesc m_gModDesc;

__declspec( dllexport ) const TCHAR *
LibDescription() { return GetString(IDS_TH_VGMODEXPORTDLL); }

__declspec( dllexport ) int
LibNumberClasses() { return 1; }

__declspec( dllexport ) ClassDesc *
LibClassDesc(int i) {
	switch(i) {
	case 0: return &m_gModDesc; break;
	default: return 0; break;
	}
}

__declspec( dllexport ) ULONG 
LibVersion() { return VERSION_3DSMAX; }

__declspec( dllexport ) ULONG CanAutoDefer()
{
	return 1;
}
////////////////////////////////////////////////////	插件的5个接口函数	
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//  插件功能类定义：
vgModExportor::vgModExportor()   
{
	//	Part 1: 版本
	m_nVersionMod	= VERSION_MOD_CURRENT;
	//m_nVersionMod	= VERSION_MOD_LAST;


	////	Part 2: 文件位置
	//puObjPos		= NULL ;	//	各个物体在文件中的偏移数组
	//uiObjPosPos		= 0 ;		//	物体偏移数组在文件中的位置
	//uiObjChunkSize	= 0 ;		//	数据块大小
	//uiFilePos		= 0 ;		//	文件指针所在的位置

	//	Part 3: 全局变量
	pStream			= NULL ;	//	文件指针
	pTheModels		= NULL ;	//	场景指针
	pTheSceneEnum	= NULL ;	//	全局场景接口
	pTheMtls		= NULL ;	//	全局材质接口
	pTheObjects		= NULL ;	//	全局物体接口

	//	Part 4: 临时变量
	newobj			= NULL;		//	当前物体指针
	newmat			= NULL;		//	当前材质指针
	newrender		= NULL;		//	当前材质面索引指针
	newmesh			= NULL;		//	当前网格指针
	savemtl			= NULL;		//	当前标准材质指针

	//  其他
#if 0
	m_fScale		= 1.1f;
	m_oSceneCenter.x = 220000;
	m_oSceneCenter.y = 100000;
	m_oSceneCenter.z = 0;
#endif	

	
}

vgModExportor::~vgModExportor() 
{
	reset();
}

void vgModExportor::reset()
{
	if (pTheModels)
	{
		delete pTheModels;
		pTheModels = NULL;
	};

	if (pTheSceneEnum)
	{
		delete pTheSceneEnum;
		pTheSceneEnum = NULL;
	};

	if (pTheMtls)
	{
		delete pTheMtls;
		pTheMtls = NULL;
	};

	if (pTheObjects)
	{
		delete pTheObjects;
		pTheObjects = NULL;
	};

	newobj = NULL;newmat =NULL; newrender = NULL;newmesh = NULL;savemtl = NULL;
}

int			 vgModExportor::ExtCount() {	
	return 1;
}

const TCHAR *vgModExportor::Ext(int n) 
{		
	switch(n) {
case 0:
//#ifdef	_MOD
	return _T("MOD");
// #else
// 	return _T("KFM");
// #endif
	}
	return _T("");
}

const TCHAR *vgModExportor::LongDesc() 
{			
	return GetString(IDS_TH_MODSCENEFILE);
}

const TCHAR *vgModExportor::ShortDesc() 
{		
#ifdef _DEBUG
	return GetString(IDS_TH_MODFILE_D)  ;

#else
	return GetString(IDS_TH_MODFILE_R)  ;

#endif
}

const TCHAR *vgModExportor::AuthorName()  
{
	return GetString(IDS_TH_LIANG_KAI);
}

const TCHAR *vgModExportor::CopyrightMessage() 
{	
	return GetString(IDS_TH_COPYRIGHT_VRGIS_GROUP);
}

const TCHAR *vgModExportor::OtherMessage1() 
{	 
	return _T("");
}

const TCHAR *vgModExportor::OtherMessage2() 
{ 
	return _T("");
}

unsigned int vgModExportor::Version() 
{				
	return 200;
}

BOOL		 vgModExportor::SupportsOptions(int ext, DWORD options) 
{
	assert(ext == 0);	
	return(options == SCENE_EXPORT_SELECTED) ? TRUE : FALSE;
}

void		 vgModExportor::ShowAbout(HWND hWnd){ }

//  插件功能类核心成员函数定义：
//	包括ComputerVerts、ComputerBound、ComputerNormal、
//		DoExport、_mod_save、ExportModel、WriteModel、WriteObjChunk


// ############################################################################################################################3

//	Level 1: 
int		vgModExportor::DoExport(const TCHAR *filename,ExpInterface *ei,Interface *gi, BOOL suppressPrompts, DWORD options) 
{//	所有场景导出插件的执行入口

	ip = gi;

	// 设置一个全局变量，开关导出场景时的提示消息
#if 0
	showPrompts = !suppressPrompts ;
	exportSelected = options & SCENE_EXPORT_SELECTED ;
#else
	// 配置导出选项
	bool bForceDefault = !suppressPrompts;//suppressPrompts:=false
	configExportFlag( options, bForceDefault);//options:=0
#endif

	// 初始化 模型保存过程中的相关消息 的存储队列
	msgList.SetCount(0);

	// 导出 .VGMOD 格式的模型文件
	int	status = _mod_save(filename, ei, this);

	// 列表形式 输出 保存模型过程中的相关消息
	if( exportFlags[PROMPT_RESULT] )
		CreateDialog(hInstance, MAKEINTRESOURCE(IDD_ERROR_MSGS), 
		GetActiveWindow(), (DLGPROC)MsgListDlgProc);

	ClearMsgList();

	// 导出场景过程完成后返回 结果值   (1 表示成功 0 表示失败)

	if ( status == 0 )
	{
		return(status);
	}

#if 0
	_vmd_save(filename);
#endif

	return(status);
}
int		vgModExportor::_mod_save(const TCHAR *filename, ExpInterface *ei, 
								 vgModExportor* exp) 
{

	// 用户自定义设置，包括是否导出UV坐标、中心坐标设置
	if( exportFlags[PROMPT_SETTING] ) 
	{
		int result = DialogBoxParam(hInstance,
			MAKEINTRESOURCE(IDD_EXPORTOPTIONS1),
			ip->GetMAXHWnd(),
			ExportOptionsDlgProc,
			(LPARAM) exp);
		if (result <= 0) 
			return 0;
	}
	else 
	{	// Set default parameters here
		//g_bZeroVert = TRUE;
		//g_bMulti2Text = TRUE;
		//g_bCadFace = TRUE;
		//g_bOtherType = TRUE;
#if 0
		g_strCenterX=	"220000.0f";
		g_strCenterY=	"100000.0f";
		g_strCenterZ=	"0.0f";
		g_strScale	= "1.0f";
#endif
		g_strPrefix	="";//"Plan_i";

		m_eElementFilter.getFilterFlag(MTL_EXT_TO_DDS_ELEMENT) = false;
		setCoordinateSystem( XZminusY_COORDINATE );
	}
	//m_oSceneCenter.x	= atof( g_strCenterX.data() );
	//m_oSceneCenter.y	= atof( g_strCenterY.data() );
	//m_oSceneCenter.z	= atof( g_strCenterZ.data() );

	// 这样改后,输入场景原点坐标(x,y,z)后的导出结果,就等于在平台中整体平移(x,y,z)后的结果
	m_oSceneCenter.x	= -atof( g_strCenterX.data() );
	m_oSceneCenter.y	= atof( g_strCenterZ.data() );
	m_oSceneCenter.z	= -atof( g_strCenterY.data() );

	m_fScale			= atof( g_strScale.data() );

	bool	bAppendSuffix		= m_eElementFilter.getFilterFlag(MTL_NAME_SUFFIX_ELEMENT);

	bool	bToDDS		= m_eElementFilter.getFilterFlag(MTL_EXT_TO_DDS_ELEMENT);

	// 获取MAX的材质和模型管理接口
	pTheModels = new t3DModel;
	

	pTheMtls		= new MeshMtlList( bAppendSuffix, bToDDS, 
		TSTR(filename), ip->GetCurFilePath(), g_strPrefix);


	pTheSceneEnum	= new SceneEnumProc(ei->theScene, ip->GetTime(), ip, pTheMtls
		, exportFlags[FILTER_SELECTED]);
	pTheSceneEnum->BuildNames();

	// 判断场景是否为空
	if(!pTheSceneEnum->Count()) {
		if( exportFlags[PROMPT_WARNING] )
			Alert(IDS_TH_NODATATOEXPORT);
		return 1;
	}

	pTheObjects = new ObjectList(*pTheSceneEnum);



	// 准备写入文件
	WorkFile theFile(filename,_T("wb"));
	//WorkFile theFile(filename,"wt");

	pStream = theFile.Stream();		
	if(!pStream) {
		if( exportFlags[PROMPT_WARNING] )
			Alert(IDS_TH_CANTCREATE);
		return(0);
	}

	//	获取数据，写入缓存	
	CollectDataForObjects();//ExportModel(OBJECTS,NULL);	

	//	计算各个几何物体信息块的位置和大小 写文件...
	pTheModels->Write(pStream, pTheMtls, ip, GetString(IDS_FORMAT), m_nVersionMod);//WriteModel( );

	//	整个导出成功，释放内存
	pTheModels->reset();

	//////////////////////////////////////////////////////////////////////////
	// 返回写文件结果信息 (1成功 0失败)	
	int error=0;
	if(theFile.Close())
		error=1;	
	if(error) {
		if( exportFlags[PROMPT_WARNING] )
			Alert(IDS_TH_WRITEERROR);
		remove((char *)filename);
		return(0);
	}	
	return 1;	
}

//	Level 2:
bool vgModExportor::CollectDataForObjects()
{
	//  Part 1：输出材质信息提示
	DumpMtlListBegin();	
	//	逐个获取并提取材质信息
	DumpMtlListProcess();
	DumpMtlListEnd();


	//  Part 2：开始输出物体信息
	ip->ProgressStart(GetString(IDS_PROGRESSEXPORT), TRUE, fn, NULL);// 启动显示进度

	DumpObjListBegin();
	//	逐个获取并保存所有几何物体信息到结构体
	DumpObjListProcess();
	DumpObjListEnd();


	ip->ProgressEnd();// 进度完成

	return	true;
}

E_Return_Type vgModExportor::CollectGeoDataForEachObj( ObjectEntry *oe )
{
	// Part 1:物体名字
	CStr name(oe->entry->name); 
	if(name.Length()>20)
		name.Resize(20);
	_tcsncpy_s(newobj->strName,20, name.data(),19);

	INode*	node = oe->entry->node;			
	Matrix3 ident(TRUE);
	Matrix3 mat = node->GetObjTMAfterWSM(pTheSceneEnum->time);

	Point3 pos = mat.GetRow(3);
	if (pos.x==0.0f && pos.y==0.0f && pos.z==0.0f) {
		pos.x = 0.001f;
		pos.y = 0.001f;
		pos.z = 0.001f;
		mat.SetTrans(pos);
	}

	Object*	obj = oe->entry->obj;

	newmesh = &(oe->tri->GetMesh());

	MeshAndTMAndNode mt;
	mt.tm = &mat;				// 已获取转换矩阵 mat
	mt.mesh = newmesh;			// 已获取网格信息 mesh
	mt.node = node;				// 已获取节点信息 node

	if ( node->GetMtl() )
	{
		bTexture = TRUE;
		
		if ( IsShellMtl( node->GetMtl() ) )
		{
			newobj->m_nObjectType	|= OBJ_BAKED;
			newobj->m_bIsBaked		= true;
		}
		else
		{
			newobj->m_nObjectType	|= MTL_STANDARD;
			newobj->m_bIsBaked		= false;
		}
	}
	else
	{
		bTexture = FALSE;
		newobj->m_nObjectType |= MTL_STANDARD;
		newobj->m_bIsBaked		= false;
	}

	//////////////////////////////////////////////////////////////////////////
	//    计算物体的最终点线面信息

	//  计算每个物体的点和面信息
	ComputerVerts( &mt, newobj );	

	//  计算每个物体的包围盒
	ComputerBound(newobj);

	//  计算每个物体所有点的法向量
	ComputerNormal( newobj);

	//  计算阴影结构体sw_faces
	ComputerSWFaces( newobj );

	//////////////////////////////////////////////////////////////////////////
	//  写入每个物体的材质及其相关面信息
	Mtl *mtl = node->GetMtl() ;
	mtlNumMap.SetCount(1);
	mtlNumMap[0] = pTheMtls->FindMtl(mtl);
	mtlnum	= 0;
	bakedMtlNo = -1;

	multiMtl	= FALSE;

	bFaceOfMatAll.SetSize( newobj->numOfFaces );
	bFaceOfMatAll.ClearAll();
	totleFaceWithMat = 0;

	// 按材质整理物体的所有渲染接口
	if ( bTexture )
	{
		E_Return_Type	ret = CollectMtlDataForEachObj(mtl);/*ExportModel(OBJECT_MATINFO, mtl )*/
		if ( RETURN_MTL_MULTITEX_NEST == ret)
			return ret;
	}

	// 无材质面索引
	newobj->numOfFaceNoMaterail = newobj->numOfFaces - totleFaceWithMat;

	if ( newobj->numOfFaceNoMaterail )
	{					
		newobj->pFaceNoMaterail = new tFace2[newobj->numOfFaceNoMaterail];
		newobj->numOfFaceNoMaterail = 0;

		for (int i=0; i< newobj->numOfFaces; i++)
		{
			if ( !bFaceOfMatAll[i])
			{
				newobj->pFaceNoMaterail[newobj->numOfFaceNoMaterail].
					vertIndex[0] = newmesh->faces[i].v[0];
				newobj->pFaceNoMaterail[newobj->numOfFaceNoMaterail].
					vertIndex[1] = newmesh->faces[i].v[1];
				newobj->pFaceNoMaterail[newobj->numOfFaceNoMaterail].
					vertIndex[2] = newmesh->faces[i].v[2];							
				newobj->numOfFaceNoMaterail ++;
			}
		}// for ( newobj->numOfFaces )
	}// if ( newobj->numOfFaceNoMaterail )


	return	RETURN_TRUE;
}

E_Return_Type vgModExportor::CollectMtlDataForEachObj( Mtl*mtl )
{
	Mtl *sub;
	unsigned long mtlClassID =0;
	if( mtl )
	{
		mtlClassID = mtl->ClassID().PartA();
	}
	// #########################################################################################
	// 材质分类
	switch( mtlClassID )
	{
	case	DMTL_CLASS_ID :	
		{	// 标准材质
			/*mtlNumMap.SetCount(0);	
			mtlnum = 0;*/
			int numOfFace = newobj->numOfFaces;
			int numOfVert = newobj->numOfVertexs;
			int numOfFaceWithMat =0;

			bFaceOfMatOne.SetSize( numOfFace );
			bFaceOfMatOne.ClearAll();
			vertFlag.SetSize( numOfVert );
			vertFlag.ClearAll();

			/*mtlNumMap[0] = pTheMtls->FindMtl(mtl) ;*/

			SMtl *smtl;
			smtl = (*pTheMtls)[ mtlNumMap[mtlnum] ].sm;
			assert(smtl);

			newrender = new  tMatandFace;
			//memset( newrender, 0 , sizeof(tMatandFace) );

			// 使用了该材质的面数统计							
			if (multiMtl)
			{			// 多维子材质情况
				for ( int ix=0; ix< newobj->numOfFaces; ix++ )
				{
					if ( !bFaceOfMatAll[ix] )
					{				
						int mtlIndex = newmesh->getFaceMtlIndex( ix );//m->faces[ix].getMatID();
						if (mtlnum == mtlIndex)
						{
							numOfFaceWithMat ++;
							bFaceOfMatOne.Set(ix,1); 
							bFaceOfMatAll.Set(ix,1);
						}	//if								
					} //if
				}//for(newobj->numOfFaces)

			} //if(multiMtl)
			else
			{			// 单材质情况
				numOfFaceWithMat = newmesh->numFaces;
				bFaceOfMatOne.SetAll();
				bFaceOfMatAll.SetAll();
			}
			newrender->numOfFace = numOfFaceWithMat;
			totleFaceWithMat += numOfFaceWithMat;

			if ( (fabsf(smtl->uTile - 1.0f) < 1.0e-4 )&&
				(fabsf(smtl->vTile - 1.0f) < 1.0e-4 )	)
			{//假如uv重复度为1，则不用调整uv
				vertFlag.SetAll();
			}

			// 使用了该材质的面ID及面索引生成
			if ( numOfFaceWithMat )
			{	
				newrender->FaceID = new	short[numOfFaceWithMat];
				memset( newrender->FaceID, 0, sizeof(short) * numOfFaceWithMat );
				newrender->RenderFace = new tFace2[numOfFaceWithMat];
				memset( newrender->RenderFace, 0, sizeof(struct tFace2)* numOfFaceWithMat );

				numOfFaceWithMat = 0;
				float	tempTile = 1.0f;
				float	deltaTileU = 0.0f, deltaTileV = 0.0f;
				int  vertIndex1;
				for (int ix=0; ix< newobj->numOfFaces ; ix++) 
				{
					if ( bFaceOfMatOne[ix] )
					{
						newrender->FaceID[numOfFaceWithMat] = ix;
						newrender->RenderFace[numOfFaceWithMat].vertIndex[0] = newobj->pFaces[ix].vertIndex[0];
						newrender->RenderFace[numOfFaceWithMat].vertIndex[1] = newobj->pFaces[ix].vertIndex[1];
						newrender->RenderFace[numOfFaceWithMat].vertIndex[2] = newobj->pFaces[ix].vertIndex[2];
						numOfFaceWithMat ++;

						deltaTileU	=	0.0f;
						deltaTileV	=	0.0f;
						// 假如材质uv有重复，则须调整使用了该材质的面片对应的uv坐标
						for ( int j =0; j < 3; j++)
						{
							vertIndex1 = newobj->pFaces[ix].vertIndex[j] ;

							if ( !vertFlag[ vertIndex1 ] ) 
							{
								tempTile	=	newobj->texcoord2D[ vertIndex1 ].x * smtl->uTile /*-0.001f*/;
								//tempTile	-=	int(tempTile);
								newobj->texcoord2D[ vertIndex1 ].x = tempTile;

								tempTile	=	newobj->texcoord2D[ vertIndex1 ].y * smtl->vTile;
								//tempTile	-=	int(tempTile);
								newobj->texcoord2D[ vertIndex1 ].y = tempTile;

								vertFlag.Set( vertIndex1, 1 );

							}//if (点未标记)

						}//for (面的三点)

					}//if (面未标记)

				}//for (每个面） 

			}//if (该材质的关联面数)

			// 该材质的名字 颜色 ID 
			_tcscpy_s(newrender->strName ,/*255,*/ smtl->name);

			newrender->red   = smtl->diffColor.r;
			newrender->green = smtl->diffColor.g;
			newrender->blue  = smtl->diffColor.b;
			newrender->textureId = mtlnum;

			if ( smtl->diffuseBitmap[0] )
			{
				newrender->bHasTexture	= TRUE;
			}

			// 2008年3月6日15:58:51 添加
			if ( (newobj->m_nObjectType  & OBJ_BAKED) && ( bakedMtlNo > 0) )
			{
				smtl = (*pTheMtls)[ bakedMtlNo ].sm;
				_tcscpy_s(newrender->strNameBaked ,/*255,*/ smtl->name);
				//newrender->bHasTexture	= TRUE;
			}
			else
			{
				newrender->strNameBaked[0] = '\0';
			}

			if ( numOfFaceWithMat )
			{
				newobj->RenderInterface.push_back( newrender );
				newobj->numOfRenderInterface ++;
				newrender = NULL;
			}
			else
			{
				delete newrender;
				newrender = NULL;
			}
		}// case	DMTL_CLASS_ID :
		break;

		//////////////////////////////////////////////////////////////////////////
	case	MULTI_CLASS_ID :
		{   // 多维子材质
			multiMtl = TRUE;
			mtlNumMap.SetCount(mtl->NumSubMtls());
			int mtlIndex = 0;
			for (int i = 0; i < mtl->NumSubMtls(); i++) 
			{
				Mtl* sub  = mtl->GetSubMtl(i);
				if (sub)
				{
					mtlNumMap[i] = pTheMtls->FindMtl(sub);
				}
				else
				{
					mtlNumMap[i] = 0;
				}
				mtlIndex = mtlNumMap[i];
			}

			for (int i = 0; i < mtl->NumSubMtls(); i++) 
			{
				Mtl* sub  = mtl->GetSubMtl(i);
				if (sub)
				{
					mtlnum = i ;//% (mtl->NumSubMtls());

					if (sub->NumSubMtls())
					{
						return RETURN_MTL_MULTITEX_NEST;
					}

					E_Return_Type	ret = CollectMtlDataForEachObj(sub);
					if ( RETURN_MTL_MULTITEX_NEST == ret)
						return ret;

				}
			}

		}//case	MULTI_CLASS_ID :
		break;

	case	BAKE_SHELL_CLASS_ID :
		{   // 壳材质
			sub = mtl->GetSubMtl(1);
			if ( sub )
				bakedMtlNo = pTheMtls->FindMtl(sub);

			sub= mtl->GetSubMtl(0);
			mtlNumMap[0] = pTheMtls->FindMtl(sub) ;
			if ( sub )
			{
				E_Return_Type	ret = CollectMtlDataForEachObj(sub);
				if ( RETURN_MTL_MULTITEX_NEST == ret)
					return ret;
			}
		}//case	BAKE_SHELL_CLASS_ID
		break;

	default:
		break;
	}//switch( mtlClassID )

	return	RETURN_TRUE;
}



int		vgModExportor::ComputerVerts(  MeshAndTMAndNode *mt ,t3DObject *newobj )
{
	// 搜集物体网格的基本信息 包括空间点坐标、空间面索引、纹理UV点坐标、纹理UV面索引
	// 以及空间点数目、纹理UV点数目、空间面数目、纹理UV面数目（与空间面数相同）
	Mesh		*newmesh  = NULL;			// 网格 对象

	Matrix3		*mat  = NULL;				// 网格 变换矩阵

	int		numOfVerts  ;			// 网格 空间点数目
	Point3		*pVerts  = NULL;			// 网格 空间点坐标
	int		numOfFaces  ;			// 网格 空间面数目
	Face		*pFaces  = NULL;			// 网格 空间面索引

	MeshMap		*mapChannel1 = NULL;		// 第一 贴图通道 
	int		numOfTvert1 ;			// 第一 纹理UV点数目
	UVVert		*pTVerts1  = NULL;			// 第一 纹理UV点数组
	TVFace		*pTFaces1  = NULL;			// 第一 纹理UV面索引

	MeshMap		*mapChannel3 = NULL ;		// 第三 贴图通道 
	UVVert		*pTVerts3 = NULL;			// 第三 纹理UV点数组
	TVFace		*pTFaces3 = NULL ;			// 第三 纹理UV面索引

	//bool	bIsBaked;				// 烘焙标记
	int	eObjectType;
	// #############################################################################
	// 各map channel 通用数据接口
	newmesh		= mt->mesh ;
	mat			= mt->tm ;

	pVerts		= newmesh->verts ;
	numOfVerts	= newmesh->getNumVerts() ;

	pFaces		= newmesh->faces  ;
	numOfFaces	= newmesh->getNumFaces() ;

	newobj->numOfVerts	=	numOfVerts ;
	newobj->numOfFaces	=	numOfFaces ;

	//bIsBaked	= newobj->bIsBacked ;

	// #############################################################################
	// 2008年3月6日8:50:05 添加 
	// map channel 1 UV数据接口
	mapChannel1 = newmesh->maps + MAP_CHANNEL_ONE  ;
	pTVerts1	=  mapChannel1->tv;
	pTFaces1 =  mapChannel1->tf;  

	numOfTvert1	= mapChannel1->getNumVerts();

	// map channel 3 UV数据接口
	//assert(newmesh->numMaps>4);
	if (newmesh->numMaps >=4)
	{
		mapChannel3 = newmesh->maps + MAP_CHANNEL_THREE  ;
		pTVerts3	=  mapChannel3->tv;
		pTFaces3 =  mapChannel3->tf;  
	}
	else
	{
		newobj->m_nObjectType	&= ~OBJ_BAKED;
		newobj->m_nObjectType	|= MTL_STANDARD;
		newobj->m_bIsBaked		= false;
	}

	//numOfTvert3	= mapChannel3->getNumVerts();
	eObjectType	= newobj->m_nObjectType;

	{
		// #############################################################################
		// 通过 网格面索引 和 第一、三贴图通道UV面索引 遍历所有不同的可渲染点（坐标、UV1、UV3三项任一不同则不同）
		vertFlag.SetSize( numOfVerts );
		vertFlag.ClearAll();

		Tab<Vert3D> verts ;			
		Tab<tFace2> faces ,faces2;		// 2007/8/27 liangkai 新加faces2、tmpFace2
		verts.SetCount( numOfVerts );
		faces.SetCount( numOfFaces );
		faces2.SetCount( numOfFaces );
		Vert3D	tmpVert ;
		tFace2  tmpFace ,tmpFace2;
		memset( &tmpVert, 0, sizeof(Vert3D) );
		memset( &tmpFace, 0, sizeof(tFace2) );
		memset( &tmpFace, 0, sizeof(tFace2) );


		for (int i = 0; i < numOfFaces; i++) 
		{
			Face   face   = pFaces[i];		// 网格面索引

			TVFace tvFace1( 0,0,0 ) ;
			if ( pTFaces1 )
			{
				tvFace1 = pTFaces1[i];	// 第一贴图通道UV面索引
			}

			TVFace tvFace3( 0,0,0 ) ;
			if ( eObjectType & OBJ_BAKED )
			{
				tvFace3 = pTFaces3[i];	// 第三贴图通道UV面索引
			}


			// 逐个获取面索引值				
			for (int k = 0; k < 3; k++) 
			{
				tmpFace.vertIndex[k] = face.v[k];
				tmpFace2.vertIndex[k] = face.v[k];
			}

			// 遍历该面的各个点 获取新点的位置坐标和纹理坐标
			for (int j = 0; j < 3; j++) 
			{
				UVVert tVert1(0.0f, 0.0f,0.0f) ;
				if ( pTVerts1 )
				{
					tVert1 = pTVerts1[tvFace1.t[j]];
				}

				UVVert tVert3(0.0f, 0.0f,0.0f)  ;
				if (  eObjectType  & OBJ_BAKED  )
				{
					tVert3 = pTVerts3[tvFace3.t[j]];
				}

				Point3 vert  = pVerts[face.v[j]];

				vert = vert * (*mat); 

				tmpVert.pt = vert;
				tmpVert.tv1 = tVert1;
				tmpVert.tv3 = tVert3;

				if ( vertFlag[face.v[j]] ) 
				{ // 该点已标记  
					if ( bTexture && !(eObjectType & OBJ_BAKED) )
					{// 只有 map channel 1
						if( verts[face.v[j]].tv1 != tmpVert.tv1 )
						{
							tmpFace.vertIndex[j] = verts.Count();
							verts.Insert(verts.Count(), 1, &tmpVert);
						}
					}
					else if ( bTexture &&  (eObjectType & OBJ_BAKED)   ) 
					{// 含有 map channel 1&&3
						if( ( verts[face.v[j]].tv1 != tmpVert.tv1 ) || (verts[face.v[j]].tv3 != tmpVert.tv3 ) )
						{
							tmpFace.vertIndex[j] = verts.Count();
							verts.Insert(verts.Count(), 1, &tmpVert);
						}				
					}
					else 
						continue ;
				}
				else
				{ // 该点未标记 加入并标记
					verts[face.v[j]] = tmpVert;
					vertFlag.Set( face.v[j], 1 );
					if (44==face.v[j])
					{
						verts[face.v[j]] = tmpVert;
					}
				}
			}//for (int j = 0; j < 3; j++) 三角面的三点
			faces[i] = tmpFace;
			faces2[i] = tmpFace2;
		}//for (int i = 0; i < numOfFaces; i++)  所有网格面



		// ############################################################################# 
		//  填充newobj结构体
		newobj->numOfVerts = numOfVerts;
		newobj->pVerts		= new  CVector3[numOfVerts];					// 纯点坐标
		memset( newobj->pVerts, 0, sizeof(CVector3) * numOfVerts );

		numOfVerts = verts.Count();
		newobj->numOfVertexs = numOfVerts;

		newobj->normal3D	= new CVector3[ numOfVerts ];
		newobj->postion3D	= new CVector3[ numOfVerts ];
		newobj->texcoord2D	= new CVector2[ numOfVerts ];
		if (  eObjectType  & OBJ_BAKED  )
		{
			newobj->texcoord2DLit	= new CVector2[ numOfVerts ];
			memset( newobj->texcoord2DLit, 0, sizeof(CVector2) * numOfVerts );
		}
		memset( newobj->normal3D, 0, sizeof(CVector3) * numOfVerts );
		memset( newobj->postion3D, 0, sizeof(CVector3) * numOfVerts );
		memset( newobj->texcoord2D, 0, sizeof(CVector2) * numOfVerts );


		numOfFaces = faces.Count();
		newobj->numOfFaces = numOfFaces;
		newobj->pFaces = new  tFace[numOfFaces];							// 面索引
		memset( newobj->pFaces, 0, sizeof(tFace) * numOfFaces );

		newobj->pFacesForSW = new  tFace2[numOfFaces];						// 阴影面索引
		memset( newobj->pFacesForSW, 0, sizeof(tFace2) * numOfFaces );


		vertFlag.SetSize( numOfVerts );
		vertFlag.ClearAll();
		for ( int i=0 ;i< numOfFaces ;i++ )
		{
			for (int k = 0; k < 3; k++) 
			{
				newobj->pFaces[i].vertIndex[k] = faces[i].vertIndex[k];
				newobj->pFacesForSW[i].vertIndex[k] = faces2[i].vertIndex[k];
			}
			for ( int j =0; j < 3; j++)
			{
				int  vertIndex1 = faces[i].vertIndex[j] ;
				int  vertIndex2 = faces2[i].vertIndex[j] ;

				if ( !vertFlag[ vertIndex1 ] ) 
				{

					vertFlag.Set( vertIndex1, 1 );
					
					// 新点的交错数组 (点向量待下一步计算)
					if (vertIndex1 == 44)
					{
						verts[ vertIndex1 ].pt	= verts[ vertIndex1 ].pt;
					}

					newobj->texcoord2D[ vertIndex1 ].x = verts[ vertIndex1 ].tv1.x;
					newobj->texcoord2D[ vertIndex1 ].y = verts[ vertIndex1 ].tv1.y;

					// 交错数组 灯光阴影UV
					if (  eObjectType  & OBJ_BAKED  )
					{
						newobj->texcoord2DLit[ vertIndex1 ].x = verts[ vertIndex1 ].tv3.x;
						newobj->texcoord2DLit[ vertIndex1 ].y = verts[ vertIndex1 ].tv3.y;
					}					
					
					if ( isNeedTranlateCoordinateSystem() )
					{
						newobj->postion3D[ vertIndex1 ].x =  (verts[ vertIndex1 ].pt.x - m_oSceneCenter.x)*m_fScale;
						newobj->postion3D[ vertIndex1 ].y =  (verts[ vertIndex1 ].pt.z - m_oSceneCenter.z)*m_fScale;
						newobj->postion3D[ vertIndex1 ].z = -(verts[ vertIndex1 ].pt.y - m_oSceneCenter.y)*m_fScale;
						
						newobj->pVerts[ vertIndex2 ].x =  (verts[ vertIndex2 ].pt.x - m_oSceneCenter.x)*m_fScale;
						newobj->pVerts[ vertIndex2 ].y =  (verts[ vertIndex2 ].pt.z - m_oSceneCenter.z)*m_fScale;
						newobj->pVerts[ vertIndex2 ].z = -(verts[ vertIndex2 ].pt.y - m_oSceneCenter.y)*m_fScale;
					}
					else
					{
						newobj->postion3D[ vertIndex1 ].x =  (verts[ vertIndex1 ].pt.x - m_oSceneCenter.x)*m_fScale;
						newobj->postion3D[ vertIndex1 ].y =  (verts[ vertIndex1 ].pt.y - m_oSceneCenter.y)*m_fScale;
						newobj->postion3D[ vertIndex1 ].z =  (verts[ vertIndex1 ].pt.z - m_oSceneCenter.z)*m_fScale;
						
						newobj->pVerts[ vertIndex2 ].x =  (verts[ vertIndex2 ].pt.x - m_oSceneCenter.x)*m_fScale;
						newobj->pVerts[ vertIndex2 ].y =  (verts[ vertIndex2 ].pt.y - m_oSceneCenter.y)*m_fScale;
						newobj->pVerts[ vertIndex2 ].z =  (verts[ vertIndex2 ].pt.z - m_oSceneCenter.z)*m_fScale;
					}

					
				} 

			}//for ( int j =0; j < 3; j++) 遍历面的三点
		}//for ( int i=0 ;i< numOfFaces ;i++ ) 遍历所有面
		// 通过 网格面索引 和 第一、三贴图通道UV面索引 遍历所有不同的可渲染点（坐标、UV1、UV3三项任一不同则不同）
		// #############################################################################
	}


	return 1;
}

int		vgModExportor::ComputerBound( t3DObject* pObject)
{
	//CVector3	maxPoint = pObject->m_maxPoint;
	//CVector3	minPoint = pObject->m_minPoint;

	float	FloatMax	= (float)INT_MAX;

	pObject->m_maxPoint.x = pObject->m_maxPoint.y = pObject->m_maxPoint.z = -FloatMax;
	pObject->m_minPoint.x = pObject->m_minPoint.y = pObject->m_minPoint.z =  FloatMax;

	float	minx =	pObject->m_minPoint.x;
	float	miny =	pObject->m_minPoint.y;
	float	minz =	pObject->m_minPoint.z;
	float	maxx =	pObject->m_maxPoint.x;
	float	maxy =	pObject->m_maxPoint.x;
	float	maxz =	pObject->m_maxPoint.z;

	for (int indexFace = 0; indexFace < pObject->numOfFaces; indexFace ++)
	{
		for (int indexVert = 0; indexVert<3; indexVert ++)
		{
			int index = pObject->pFacesForSW[indexFace].vertIndex[indexVert];

			// maxPoint
			if( maxx < pObject->pVerts[ index ].x )
			{
				maxx = pObject->pVerts[ index ].x;
			}

			if (maxy < pObject->pVerts[ index ].y)
			{
				maxy = pObject->pVerts[ index ].y;

			}	
			if( maxz < pObject->pVerts[ index ].z )
			{
				maxz = pObject->pVerts[ index ].z;
			}

			// minPoint
			if( minx > pObject->pVerts[ index ].x )
			{
				minx = pObject->pVerts[ index ].x;
			}
			if (miny > pObject->pVerts[ index ].y)
			{
				miny = pObject->pVerts[ index ].y;

			}
			if( minz > pObject->pVerts[ index ].z )
			{
				minz = pObject->pVerts[ index ].z;
			}
		}
	}

	pObject->m_minPoint.x =	minx;
	pObject->m_minPoint.y =	miny;
	pObject->m_minPoint.z =	minz;
	pObject->m_maxPoint.x =	maxx;
	pObject->m_maxPoint.y =	maxy;
	pObject->m_maxPoint.z =	maxz;
	return true;
}

int		vgModExportor::ComputerNormal( t3DObject * pObject)
{
	//Mesh &mesh = oe->tri->GetMesh();
	int count = pObject->numOfFaces;
	CVector3 vVector1, vVector2, vNormal, vPoly[3];

	newobj->pNormalOfFaces		= new CVector3 [count];
	CVector3 *pTempNormals	= new CVector3 [count];
	for(int i=0; i < count; i++)
	{												
		vPoly[0] = pObject->postion3D[ pObject->pFaces[i].vertIndex[0] ];
		vPoly[1] = pObject->postion3D[ pObject->pFaces[i].vertIndex[1] ];
		vPoly[2] = pObject->postion3D[ pObject->pFaces[i].vertIndex[2] ];
		vVector1 = SubVector(vPoly[2], vPoly[1]);
		vVector2 = SubVector(vPoly[0], vPoly[2]);
		vNormal  = Cross(vVector1, vVector2);
		pTempNormals[i] = vNormal;
		vNormal= Normalize(vNormal);
		newobj->pNormalOfFaces[i] = vNormal;
	}

	CVector3 vSum;
	memset(&vSum, 0, sizeof(CVector3) );
	CVector3 vZero;
	memset(&vZero, 0, sizeof(CVector3) );
	int shared=0;
	for (int i = 0; i < pObject->numOfVertexs; i++)
	{
		for (int j = 0; j < pObject->numOfFaces; j++)	
		{												
			if (pObject->pFaces[j].vertIndex[0] == i || 
				pObject->pFaces[j].vertIndex[1] == i || 
				pObject->pFaces[j].vertIndex[2] == i)
			{
				//vSum = vSum + newobj->pNormalOfFaces[j];
				for(int index=0 ;index<3; index++)
					vSum.vert[index] += newobj->pNormalOfFaces[j].vert[index];
				shared++;								// Increase the number of shared triangles
			}
		}      
		//vSum = vSum/float(shared);
		vSum = Normalize(vSum);

		pObject->normal3D[i].x = vSum.x;
		pObject->normal3D[i].y = vSum.y;
		pObject->normal3D[i].z = vSum.z;

		pObject->normal3D[i].x = vSum.x;
		pObject->normal3D[i].y = vSum.y;
		pObject->normal3D[i].z = vSum.z;

		vSum = vZero;
		shared = 0;
	}

	return 1;
}








int		vgModExportor::ComputerSWFaces(  t3DObject * pObject)
{
	// 2007/8/27 liangkai 新加 以下至return的内容
	//	numOfVerts = verts2.Count();
	int numOfFaces = pObject->numOfFaces;
	newobj->shadowFace = new sw_FaceIndex[numOfFaces];
	//CVector3	lightDir( 0.1f , -0.5f , 0.1f ); 
	CVector3	lightDir;
	lightDir.vert[0] = 0.1f; 
	lightDir.vert[1] = -0.5f;
	lightDir.vert[2] = 0.1f;
	// 首先填充每个sw_FaceIndex的三个顶点并计算normal
	for ( int i=0 ;i<numOfFaces ;i++ )
	{
		// 从每个面生成一个sw_FaceIndex
		sw_FaceIndex &newSWFace = newobj->shadowFace[i];

		// 得到三个定点	
		tFace2 &face = pObject->pFacesForSW[i];
		int &point1 = newSWFace.p1;
		int &point2 = newSWFace.p2;
		int &point3 = newSWFace.p3;
		point1= face.vertIndex[0];
		point2= face.vertIndex[1];
		point3= face.vertIndex[2];

		newSWFace.normal = i;
		i*=1;

	}
	//////////////////////////////////// 首先填充每个面的三个顶点并计算normal
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// 其次更新sw_FaceIndex的其他值
	for ( int i=0 ;i<numOfFaces ;i++ )
	{
		// 从每个面生成一个sw_FaceIndex
		sw_FaceIndex &pSWFace = newobj->shadowFace[i];
		// 赋值
		int& point1 = pSWFace.p1;
		int& point2 = pSWFace.p2;
		int& point3 = pSWFace.p3;

		// 计算临边

		int	face_index1 = sw_searchForAdjacent( newobj, i , point1 , point2 );
		int face_index2 = sw_searchForAdjacent( newobj, i , point2 , point3 );
		int face_index3 = sw_searchForAdjacent( newobj, i , point3 , point1 );

		pSWFace.p1p2AdjFaceIndex = face_index1;
		pSWFace.p2p3AdjFaceIndex = face_index2;
		pSWFace.p3p1AdjFaceIndex = face_index3;

		if ( DotProduct(newobj->pNormalOfFaces[ pSWFace.normal ], lightDir )<=0 )
		{
			// 黑暗时，什么也不投射。
			pSWFace.faceVisible = false;

			// 2007/8/30 liangkai 新加：
			// 			pSWFace.p1p2AdjNormal = face_index1;
			// 			pSWFace.p2p3AdjNormal = face_index2;
			// 			pSWFace.p3p1AdjNormal = face_index3;
			continue;
		}
		else 
		{
			pSWFace.faceVisible = true;

			// 更新p1p2Visible
			if ( face_index1 != -1 )
			{
				//				int& _normal2 = newobj->shadowFace[face_index1].normal;
				//				pSWFace.p1p2AdjNormal = face_index1;

				float dot_result2 = DotProduct(newobj->pNormalOfFaces[ face_index1 ], lightDir) ;

				if ( dot_result2 > 0 )
				{
					pSWFace.p1p2Visible = false;
				}
				else
				{
					pSWFace.p1p2Visible = true;
				}
			}
			else
			{
				pSWFace.p1p2Visible = true;
			}

			// 更新p2p3Visible
			if ( face_index2 != -1 )
			{
				//				int& _normal2 = newobj->shadowFace[face_index1].normal;
				//				pSWFace.p2p3AdjNormal = face_index2;

				float dot_result2 =  DotProduct(newobj->pNormalOfFaces[ face_index2 ],lightDir );

				if ( dot_result2 > 0 )
				{
					pSWFace.p2p3Visible = false;
				}
				else
				{
					pSWFace.p2p3Visible = true;
				}
			}
			else
			{
				pSWFace.p2p3Visible = true;
			}

			// 更新p3p1Visible
			if ( face_index3 != -1 )
			{
				//				int& _normal2 = newobj->shadowFace[face_index1].normal;
				//				pSWFace.p3p1AdjNormal = face_index3;

				float dot_result2 =  DotProduct(newobj->pNormalOfFaces[ face_index3 ],lightDir );

				if ( dot_result2 > 0 )
				{
					pSWFace.p3p1Visible = false;
				}
				else
				{
					pSWFace.p3p1Visible = true;
				}
			}
			else
			{
				pSWFace.p3p1Visible = true;
			}
		}
	}
	//////////////////////////////////// 其次更新sw_FaceIndex的其他值
	//////////////////////////////////////////////////////////////////////////

	return 1;
}

int		vgModExportor::sw_searchForAdjacent( t3DObject *newobj, int faceid , int& point1 , int& point2 )
{
	// 2007/8/28 liangkai 新加 以下至return的内容
	int	numOfFaces = newobj->numOfFaces;
	for (int face = 0; face < numOfFaces; face++)
	{
		if ( face == faceid )
		{
			continue;
		}
		// 得到三个定点
		int& p1 = newobj->shadowFace[ face ].p1;
		int& p2 = newobj->shadowFace[ face ].p2;
		int& p3 = newobj->shadowFace[ face ].p3;

		if ( point1 == p1 )
		{
			if ( point2 == p2 || point2 == p3 )
			{
				return face ;
			}
		}
		else if ( point1 == p2 )
		{
			if ( point2 == p1 || point2 == p3 )
			{
				return face ;
			}
		}
		else if ( point1 == p3 )
		{
			if ( point2 == p1 || point2 == p2 )
			{
				return face ;
			}
		}

	}

	// 没有找到
	return -1;
}

//BOOL	vgModExportor::ComputerKeyFrames(
//	INode* node )
//{
//	Point3 pval;
//	AngAxis rval;
//	ScaleValue sval;
//	Interval valid;
//
//	int i;
//	Matrix3 tm;
//	TimeValue t;
//	AffineParts parts;
//	Quat q, qLast;
//	Point3 s, sLast, p;
//	AngAxis a;
//
//	// Tables of keyframe values
//	Tab<TimeValue>  pFrames;
//
//	//Tab<ModKeyFrame>	vKeyFrames;
//	Tab<Point3>     pKeys;
//	Tab<AngAxis>    rKeys;
//	Tab<Point3>     sKeys;
//
//
//	TimeValue	start = pTheSceneEnum->i->GetAnimRange().Start();
//	TimeValue	end   = pTheSceneEnum->i->GetAnimRange().End();
//	newobj->m_nKeyFramesCount = (end - start)/GetTicksPerFrame();
//	newobj->m_nKeyFramesCount++;
//
//	//vKeyFrames.SetCount(newobj->m_nKeyFramesCount);
//	pKeys.SetCount(newobj->m_nKeyFramesCount);
//	rKeys.SetCount(newobj->m_nKeyFramesCount);
//	sKeys.SetCount(newobj->m_nKeyFramesCount);
//
//	pFrames.SetCount(newobj->m_nKeyFramesCount);
//
//	qLast = IdentQuat();
//	// Sample the control at every frame
//	for (i = 0, t = start; i < newobj->m_nKeyFramesCount; i++, t += GetTicksPerFrame()) 
//	{
//		tm = GetLocalNodeTM(node, t);
//		decomp_affine(tm, &parts);
//		s = ScaleValue(parts.k, parts.u).s;
//		if (parts.f < 0.0f) s = - s;
//		p = parts.t;
//		q = parts.q;
//		a = AngAxis(q );
//
//		{
//			Point3 pkey = parts.t;
//			if (!node->GetParentNode()->IsRootNode()) 
//			{
//				if (!(node->GetParentNode()->GetObjOffsetRot() == IdentQuat())) 
//				{
//					Quat q;
//					UndoParentsOffset(node, pkey, q);
//				}
//			}
//			pKeys[i] = pkey;
//			pFrames[i] = t*1000/4800; // millisecond unit
//		}//pos
//
//		{
//			sKeys[i] = s;
//		}//scl
//
//		{
//			if (i) 
//			{
//				rKeys[i] = a;
//			} 
//			else 
//			{
//				AngAxis aa;
//				Quat qkey = parts.q;
//				// remove the pivot's rotation
//				Quat qOff = qkey / Inverse(node->GetObjOffsetRot());
//				// remove the parents rotation
//				if (!node->GetParentNode()->IsRootNode()) 
//				{
//					if (!(node->GetParentNode()->GetObjOffsetRot() == IdentQuat())) 
//					{
//						Point3 p;
//						UndoParentsOffset(node, p, qOff);
//					}
//				}
//				AngAxisFromQ(qOff, &aa.angle, aa.axis);
//				rKeys[i] = aa;
//			}
//		}//rot
//	}//for(frame)
//
//
//	//	判断关键帧数据是否有效，无效则表示没有关键帧信息，帧数置为0
//	for (i = 0; i < newobj->m_nKeyFramesCount; i++) 
//	{
//		if (	pKeys[1] != pKeys[i]
//		//	update by lss when 2009-1-5 9:43:50
//		/*&&	rKeys[1].angle != rKeys[i].angle
//		&&	sKeys[1] != sKeys[i]*/
//		||	rKeys[1].angle != rKeys[i].angle
//			||	sKeys[1] != sKeys[i]
//		)
//		{
//			break;
//		}
//	}
//	//if (1)//i == newobj->m_nKeyFramesCount)
//	if ( i == newobj->m_nKeyFramesCount)
//	{
//		newobj->m_nKeyFramesCount = 0;
//	}
//	else
//	{
//		newobj->m_nObjectType	|=	OBJ_KEYFRAME;
//	}
//
//	newobj->m_pKeyFrames	=	new	ModKeyFrame[newobj->m_nKeyFramesCount];
//	//ModKeyFrame		tempKeyFrame;
//
//	for (i = 0; i < newobj->m_nKeyFramesCount; i++) 
//	{
//		//	帧时
//		newobj->m_pKeyFrames[i].m_fTime	=	pFrames[i];
//
//		//	平移
//		newobj->m_pKeyFrames[i].key_translate.x	=	pKeys[i].x;
//		newobj->m_pKeyFrames[i].key_translate.y	=	pKeys[i].z;
//		newobj->m_pKeyFrames[i].key_translate.z	=  -pKeys[i].y;
//
//		//	旋转
//		newobj->m_pKeyFrames[i].key_rotate[0]		=	rKeys[i].axis.x;
//		newobj->m_pKeyFrames[i].key_rotate[1]		=	rKeys[i].axis.z;
//		newobj->m_pKeyFrames[i].key_rotate[2]		=  -rKeys[i].axis.y;
//		newobj->m_pKeyFrames[i].key_rotate[3]		=	rKeys[i].angle ;
//
//		//	缩放
//		newobj->m_pKeyFrames[i].key_scale.x		=	sKeys[i].x;
//		newobj->m_pKeyFrames[i].key_scale.y		=	sKeys[i].z;
//		newobj->m_pKeyFrames[i].key_scale.z		=  -sKeys[i].y;
//
//	}//nNumOfFrames
//
//	// 旋转量初始化，（0 0 0 0）->（1 0 0 0）
//	for (i = 0; i < newobj->m_nKeyFramesCount; i++) 
//	{
//		for (int coordIndex = 0; coordIndex<3 ;coordIndex ++)
//		{
//			if( newobj->m_pKeyFrames[i].key_rotate[coordIndex] > 1.0e-6 )
//				break;
//		}
//	}
//	if ( i == newobj->m_nKeyFramesCount)
//	{
//		for (i = 0; i < newobj->m_nKeyFramesCount; i++) 
//		{
//			for (int coordIndex = 0; coordIndex<3 ;coordIndex ++)
//			{
//				newobj->m_pKeyFrames[i].key_rotate[coordIndex] = 1.0f;
//			}
//		}
//	}
//
//	return TRUE;
//}
//
//
//
bool vgModExportor::HasKeyFrames(INode* node)
{
	// case 1:
	Class_ID cid;
	cid = node->GetTMController()->ClassID();
	
	if (cid != Class_ID(PRS_CONTROL_CLASS_ID, 0)) 
		return false;

	
	// case 2:
	Control* cpos = node->GetTMController()->GetPositionController();
	Control* crot = node->GetTMController()->GetRotationController();
	Control* cscl = node->GetTMController()->GetScaleController();
	
	if ( !(cpos || crot || cscl) )
		return false;

	
	// case 3:
	if( !(cpos->NumKeys() || crot->NumKeys() || cscl->NumKeys()))
		return false;

	newobj->m_nObjectType	|=	OBJ_KEYFRAME;

	return	true;
} 

BOOL	vgModExportor::ComputerKeyFrames(
	INode* node )
{
	if( !m_eElementFilter.getFilterFlag( OBJ_KEYFRAME_ELEMENT ) || !HasKeyFrames(node) )
	{
		newobj->m_nKeyFramesCount = 0;
		newobj->m_pKeyFrames	=	new	ModKeyFrame[newobj->m_nKeyFramesCount];
		return FALSE;
	}

	Point3 pval;
	AngAxis rval;
	ScaleValue sval;
	Interval valid;

	int i;
	Matrix3 tm;
	TimeValue t;
	AffineParts parts;
	Quat q, qLast;
	Point3 s, sLast, p;
	AngAxis a;

	// Tables of keyframe values
	Tab<TimeValue>  pFrames;

	//Tab<ModKeyFrame>	vKeyFrames;
	Tab<Point3>     pKeys;
	Tab<AngAxis>    rKeys;
	Tab<Point3>     sKeys;


	TimeValue	start = pTheSceneEnum->i->GetAnimRange().Start();
	TimeValue	end   = pTheSceneEnum->i->GetAnimRange().End();
	newobj->m_nKeyFramesCount = (end - start)/GetTicksPerFrame();
	newobj->m_nKeyFramesCount++;

	//vKeyFrames.SetCount(newobj->m_nKeyFramesCount);
	pKeys.SetCount(newobj->m_nKeyFramesCount);
	rKeys.SetCount(newobj->m_nKeyFramesCount);
	sKeys.SetCount(newobj->m_nKeyFramesCount);

	pFrames.SetCount(newobj->m_nKeyFramesCount);

	qLast = IdentQuat();
	// Sample the control at every frame
	for (i = 0, t = start; i < newobj->m_nKeyFramesCount; i++, t += GetTicksPerFrame()) 
	{
		tm = GetLocalNodeTM(node, t);
		decomp_affine(tm, &parts);
		s = ScaleValue(parts.k, parts.u).s;
		if (parts.f < 0.0f) s = - s;
		p = parts.t;
		q = parts.q;
		a = AngAxis(q );

		{
			Point3 pkey = parts.t;
			if (!node->GetParentNode()->IsRootNode()) 
			{
				if (!(node->GetParentNode()->GetObjOffsetRot() == IdentQuat())) 
				{
					Quat q;
					UndoParentsOffset(node, pkey, q);
				}
			}
			pKeys[i] = pkey;
			pFrames[i] = t*1000/4800; // millisecond unit
		}//pos

		{
			sKeys[i] = s;
		}//scl

		{
#if 1
			rKeys[i] = a;
#else
			if (i) 
			{
				rKeys[i] = a;
			} 
			else 
			{
				AngAxis aa;
				Quat qkey = parts.q;
				// remove the pivot's rotation
				Quat qOff = qkey / Inverse(node->GetObjOffsetRot());
				// remove the parents rotation
				if (!node->GetParentNode()->IsRootNode()) 
				{
					if (!(node->GetParentNode()->GetObjOffsetRot() == IdentQuat())) 
					{
						Point3 p;
						UndoParentsOffset(node, p, qOff);
					}
				}
				AngAxisFromQ(qOff, &aa.angle, aa.axis);
				rKeys[i] = aa;
			}
#endif

		}//rot
	}//for(frame)


	newobj->m_pKeyFrames	=	new	ModKeyFrame[newobj->m_nKeyFramesCount];

	for (i = 0; i < newobj->m_nKeyFramesCount; i++) 
	{
		//	帧时
		newobj->m_pKeyFrames[i].m_fTime	=	pFrames[i];

		if ( 1/*isNeedTranlateCoordinateSystem()*/ )
		{
			//	平移
			newobj->m_pKeyFrames[i].key_translate.x	=	pKeys[i].x;
			newobj->m_pKeyFrames[i].key_translate.y	=	pKeys[i].z;
			newobj->m_pKeyFrames[i].key_translate.z	=  -pKeys[i].y;

			//	旋转
			newobj->m_pKeyFrames[i].key_rotate[0]	=	rKeys[i].axis.x;
			newobj->m_pKeyFrames[i].key_rotate[1]	=	rKeys[i].axis.z;
			newobj->m_pKeyFrames[i].key_rotate[2]	=  -rKeys[i].axis.y;
			newobj->m_pKeyFrames[i].key_rotate[3]	=	rKeys[i].angle ;

			//	缩放
			newobj->m_pKeyFrames[i].key_scale.x		=	sKeys[i].x;
			newobj->m_pKeyFrames[i].key_scale.y		=	sKeys[i].z;
			newobj->m_pKeyFrames[i].key_scale.z		=  -sKeys[i].y;
		}
		else
		{

			//	平移
			newobj->m_pKeyFrames[i].key_translate.x	=	pKeys[i].x;
			newobj->m_pKeyFrames[i].key_translate.y	=	pKeys[i].y;
			newobj->m_pKeyFrames[i].key_translate.z	=   pKeys[i].z;

			//	旋转
			newobj->m_pKeyFrames[i].key_rotate[0]	=	rKeys[i].axis.x;
			newobj->m_pKeyFrames[i].key_rotate[1]	=	rKeys[i].axis.y;
			newobj->m_pKeyFrames[i].key_rotate[2]	=   rKeys[i].axis.z;
			newobj->m_pKeyFrames[i].key_rotate[3]	=	rKeys[i].angle ;

			//	缩放
			newobj->m_pKeyFrames[i].key_scale.x		=	sKeys[i].x;
			newobj->m_pKeyFrames[i].key_scale.y		=	sKeys[i].y;
			newobj->m_pKeyFrames[i].key_scale.z		=   sKeys[i].z;
		}

	}//nNumOfFrames


#if 1
	// 旋转量初始化，（0 0 0 0）->（1 0 0 0）
	for (i = 0; i < newobj->m_nKeyFramesCount; i++) 
	{
		if( newobj->m_pKeyFrames[i].key_rotate[3] > 1.0e-6 )
			break;
	}

	if ( i != newobj->m_nKeyFramesCount)
		return TRUE;

	for (i = 0; i < newobj->m_nKeyFramesCount; i++) 
	{
		newobj->m_pKeyFrames[i].key_rotate[0] = 1.0f; 

	}

#endif

	return TRUE;
}




//////////////////////  插件功能类核心成员函数定义：
//////////////////////	包括DoExport、_mod_save、ExportModel、
//////////////////////		ComputerVerts、ComputerBound、ComputerNormal
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//	导出结构信息输出处理
void	vgModExportor::AddToMsgList(Tab<TSTR*>& mList, TCHAR* msg)
{
	TCHAR buf[SCHAR_MAX];
	strncpy_s((char *)buf, SCHAR_MAX,(char *)msg, SCHAR_MAX-1);
	buf[SCHAR_MAX - 1] = '\0';
	TSTR* errStr = new TSTR(buf);
	mList.Insert(mList.Count(), 1, &errStr);
}

void	vgModExportor::AddLineToListDlg(HWND hDlg, const TCHAR* buf) {
	SendDlgItemMessage(hDlg, IDC_ERROR_MSG_LIST, LB_ADDSTRING, NULL, (LPARAM) buf);
}

void	vgModExportor::BuildMsgList(HWND hDlg)
{
	AddLineToListDlg(hDlg, GetString(IDS_START));

	// Part1：全局信息
	for (int i = 0; i < msgListHead.Count(); i++) {
		AddLineToListDlg(hDlg,  msgListHead[i]->data() );
	}

	// Part2、3、4、5：滤除模型列表
	if (msgListZeroFace.Count() > 4)
	{
		for (int i = 0; i < msgListZeroFace.Count(); i++) {
			AddLineToListDlg(hDlg,  msgListZeroFace[i]->data() );
		}	
	}

	if (msgListMulti2.Count() > 4)
	{
		for (int i = 0; i < msgListMulti2.Count(); i++) {
			AddLineToListDlg(hDlg,  msgListMulti2[i]->data() );
		}	
	}

	if (msgListCadFace.Count() > 4)
	{
		for (int i = 0; i < msgListCadFace.Count(); i++) {
			AddLineToListDlg(hDlg,  msgListCadFace[i]->data() );
		}
	}

	if (msgListOtherType.Count() > 4)
	{
		for (int i = 0; i < msgListOtherType.Count(); i++) {
			AddLineToListDlg(hDlg,  msgListOtherType[i]->data() );
		}	
	}


	// Part6：导出模型列表
	for (int i = 0; i < msgListObject.Count(); i++) {
		AddLineToListDlg(hDlg,  msgListObject[i]->data() );
	}

	// Part7：材质列表
	for (int i = 0; i < msgListTexture.Count(); i++) {
		AddLineToListDlg(hDlg,  msgListTexture[i]->data() );
	}
	//for (int i = 0; i < msgList.Count(); i++) {
	//	AddLineToListDlg(hDlg,  msgList[i]->data() );
	//}

	AddLineToListDlg(hDlg, GetString(IDS_END));
}

void	vgModExportor::ClearMsgList()
{
	for (int i = 0; i < msgList.Count(); i++) 
	{
		delete msgList[i];
		msgList[i] = NULL;
	}
	msgList.Delete(0, msgList.Count());

	// Part1：全局信息
	for (int i = 0; i < msgListHead.Count(); i++) 
	{
		delete msgListHead[i];
		msgListHead[i] = NULL;
	}
	msgListHead.Delete(0, msgListHead.Count());


	// Part2、3、4、5：滤除模型列表msgListZeroFace msgListMulti2 msgListCadFace msgListOtherType
	for (int i = 0; i < msgListZeroFace.Count(); i++) 
	{
		delete msgListZeroFace[i];
		msgListZeroFace[i] = NULL;
	}
	msgListZeroFace.Delete(0, msgListZeroFace.Count());
	for (int i = 0; i < msgListMulti2.Count(); i++) 
	{
		delete msgListMulti2[i];
		msgListMulti2[i] = NULL;
	}
	msgListMulti2.Delete(0, msgListMulti2.Count());
	for (int i = 0; i < msgListCadFace.Count(); i++) 
	{
		delete msgListCadFace[i];
		msgListCadFace[i] = NULL;
	}
	msgListCadFace.Delete(0, msgListCadFace.Count());

	for (int i = 0; i < msgListOtherType.Count(); i++) 
	{
		delete msgListOtherType[i];
		msgListOtherType[i] = NULL;
	}
	msgListOtherType.Delete(0, msgListOtherType.Count());

	// Part6：导出模型列表msgListObject
	for (int i = 0; i < msgListObject.Count(); i++) 
	{
		delete msgListObject[i];
		msgListObject[i] = NULL;
	}
	msgListObject.Delete(0, msgListObject.Count());

	// Part7：材质列表msgListTexture
	for (int i = 0; i < msgListTexture.Count(); i++) 
	{
		delete msgListTexture[i];
		msgListTexture[i] = NULL;
	}
	msgListTexture.Delete(0, msgListTexture.Count());

}

void vgModExportor::DumpMtlListBegin()
{
	TCHAR	buf[ UCHAR_MAX ]="";
	wsprintf( buf, "%c", '\n');
	AddToMsgList( msgListTexture, buf );
	wsprintf( buf, "%s%s%s",  "\n\n",
		"\t\t\t--------------------------------------------------",
		"<导出的材质列表>--------------------------------------------------");
	AddToMsgList( msgListTexture, buf );

	TCHAR  strTemp0[25]="序号",strTemp1[25]="序号",strTemp2[25]="颜色/纹理",
		strTemp3[35]="RGB/文件名",strTemp4[25]="透明通道" ;
	wsprintf( buf, "%20s%20s%20s%20s%20s", 
		"序号", "材质名","颜色/纹理","RGB/文件名", "透明通道" );

	AddToMsgList( msgListTexture, buf );

}

void vgModExportor::DumpMtlListProcess()
{
	int	realNumOfMtls = 0;
	
	TCHAR	buf[ UCHAR_MAX ]="", format[ 50 ]="", strFmt[10];
	memset( buf, 0,sizeof(buf));
	memset( format, 0,sizeof(format));
	memset( strFmt, 0,sizeof(strFmt));

	wsprintf( strFmt, "%%%ds", MSG_BLOCK_LENGTH);
	wsprintf( format, "%s%s%s%s%s", strFmt,strFmt,strFmt,strFmt,strFmt  );
	
	TCHAR  strTemp0[25]="序号",strTemp1[25]="序号",strTemp2[25]="颜色/纹理",
		strTemp3[35]="RGB/文件名",strTemp4[25]="透明通道" ;

	int	count = pTheMtls->Count();
	for (int ix=0; ix< count; ix++)  
	{

		savemtl = (*pTheMtls)[ix].sm ;
		// 材质信息输出提示
		wsprintf( strTemp0, "%d", ++realNumOfMtls );
		_tcsncpy_s( strTemp1, 25, savemtl->name, 24 );
		if ( '\0'== savemtl->diffuseBitmap[0] )
		{
			wsprintf( strTemp2, "%s", "颜色");
			wsprintf( strTemp3, "(%d, %d, %d)" , 
				savemtl->diffColor.r, savemtl->diffColor.g, savemtl->diffColor.b );
		}
		else
		{
			wsprintf( strTemp2, "%s", "纹理");
			_tcsncpy_s( strTemp3, 35, savemtl->diffuseBitmap, 34 );
		}
		if ( '\0'== savemtl->opacityBitmap[0] )
		{
			wsprintf( strTemp4, strFmt, "无");
		}
		else
		{
			_tcsncpy_s( strTemp4, 25, savemtl->opacityBitmap, 24 );
		}

		wsprintf( buf, format, strTemp0, strTemp1, strTemp2, strTemp3, strTemp4);
		AddToMsgList( msgListTexture, buf );	

		savemtl = NULL;

	} // for ( count )	标准材质数目

	return;
}

void vgModExportor::DumpMtlListEnd()
{
	TCHAR	buf[ UCHAR_MAX ]="";
	wsprintf( buf, "%s%s",  
		"\t\t\t--------------------------------------------------",
		"<导出的材质列表>--------------------------------------------------");
	AddToMsgList( msgListTexture, buf );
	wsprintf( buf, "%c", '\n');
	AddToMsgList( msgListTexture, buf );

}

void vgModExportor::DumpObjListBegin()
{
	TCHAR	buf[ UCHAR_MAX ]="", format[ 50 ]="", strFmt[10];
	wsprintf( strFmt, "%%%ds", MSG_BLOCK_LENGTH);
	wsprintf( format, "%s%s%s%s%s", strFmt,strFmt,strFmt,strFmt,strFmt  );

	wsprintf( buf, "%c", '\n');
	AddToMsgList( msgListObject, buf );
	wsprintf( buf, "%s%s%s", "\n\n",  
	"\t\t\t-----------------------------------------------",
	"<导出的模型列表>-----------------------------------------------");
	AddToMsgList( msgListObject, buf );


	//过滤模型开始
	wsprintf( buf, "%c", '\n');
	AddToMsgList( msgListZeroFace, buf );
	wsprintf( buf, "%s%s%s", "\n\n",  
	"\t\t\t-----------------------------------------------",
	"<被滤除的仅有零个面的物体列表>------------------------");
	AddToMsgList( msgListZeroFace, buf );

	wsprintf( buf, "%c", '\n');
	AddToMsgList( msgListMulti2, buf );
	wsprintf( buf, "%s%s%s", "\n\n",  
	"\t\t\t-----------------------------------------------",
	"<被滤除的存在材质嵌套的物体列表>------------------------");
	AddToMsgList( msgListMulti2, buf );

	wsprintf( buf, "%c", '\n');
	AddToMsgList( msgListCadFace, buf );
	wsprintf( buf, "%s%s%s", "\n\n",  
	"\t\t\t-----------------------------------------------",
	"<被滤除的疑由CAD底图生成的物体列表>--------------------");
	AddToMsgList( msgListCadFace, buf );

	wsprintf( buf, "%c", '\n');
	AddToMsgList( msgListOtherType, buf );
//#ifndef _MOD			
//	wsprintf( buf, "%s%s%s", "\n\n",  
//	"\t\t\t-----------------------------------------------",
//	"<被滤除的非关键帧物体列表>------------------------");
//#else
	wsprintf( buf, "%s%s%s", "\n\n",  
	"\t\t\t-----------------------------------------------",
	"<被滤除的关键帧物体或普通物体列表>------------------------");
//#endif
	AddToMsgList( msgListOtherType, buf );


	//字段设置
	wsprintf( format, "%s%s%s%s", strFmt, strFmt, strFmt, strFmt );
	wsprintf( buf, "%22s%22s%22s%22s", 
	"序号", "物体名","三角面数","顶点数" );
	wsprintf( buf, format, "序号", "物体名", "三角面数", "顶点数" );
	AddToMsgList( msgListObject, buf );
	AddToMsgList( msgListZeroFace, buf );
	AddToMsgList( msgListMulti2, buf );
	AddToMsgList( msgListCadFace, buf );
	AddToMsgList( msgListOtherType, buf );
}
void vgModExportor::DumpObjListProcess()
{
	TCHAR	buf[ UCHAR_MAX ]="", format[ UCHAR_MAX ]="", strFmt[UCHAR_MAX];
	memset( buf, 0,UCHAR_MAX);
	memset( format, 0,UCHAR_MAX);
	memset( strFmt, 0,UCHAR_MAX);

	wsprintf( strFmt, "%%%ds", MSG_BLOCK_LENGTH);
	wsprintf( format, "%s%s%s%s", strFmt,strFmt,strFmt,strFmt  );

	TCHAR  strTemp0[25]="序号",strTemp1[25]="序号",strTemp2[25]="颜色/纹理",
		strTemp3[35]="RGB/文件名",strTemp4[25]="透明通道" ;

	int ox = 0,ix=1;
	ObjectEntry*	oe = pTheObjects->head;
	SceneEntry*		se = pTheSceneEnum->head;
	Object *obj;

	for (; 
		oe != NULL; 
		oe = oe->next,ox++,ix++, se = se->next) 
	{
		// 新建一个 t3DObject newobj 结构体
		newobj = new t3DObject;
		obj = oe->entry->obj;
		oe->tri = (TriObject *)obj->ConvertToType(pTheSceneEnum->i->GetTime(), triObjectClassID);

		if(!oe->tri)
		{
			delete newobj;
			newobj = NULL;
			continue;
		}

		// 获取一个物体的信息暂存至内存对象newobj
		E_Return_Type status = CollectGeoDataForEachObj(oe);//ExportModel(OBJECT_HEAD,oe); 

		// 过滤有缺陷的模型或根据具体条件筛选
		if( FilterFaultyObject(se->node, status) )
			continue;

			
		pTheModels->push_back(newobj);

		wsprintf( strTemp0, "%d", pTheModels->size() );
		_tcsncpy_s( strTemp1, 25, newobj->strName, 19 );
		wsprintf( strTemp2, "%d", newobj->numOfFaces );
		wsprintf( strTemp3, "%d%c", newobj->numOfVerts, '\0' );
		wsprintf( buf, format, strTemp0, strTemp1, strTemp2, strTemp3 );
		AddToMsgList( msgListObject, buf );

		pTheModels->m_nTotalFaceCount += newobj->numOfFaces;
		newobj = NULL;

		// 更新进度显示
		ip->ProgressUpdate((int)((float)pTheModels->size()/pTheObjects->count * 100.0f)); 				
	}
}

void vgModExportor::DumpObjListEnd()
{
	// 模型导出列表显示结束
	TCHAR	buf[ UCHAR_MAX ]="";
	wsprintf( buf, "%s%s",  
		"\t\t\t-----------------------------------------------",
		"<导出的模型列表>-----------------------------------------------");
	AddToMsgList( msgListObject, buf );
	wsprintf( buf, "%c", '\n');
	AddToMsgList( msgListObject, buf );

	// 滤除零面模型结束
	wsprintf( buf, "%s%s%s", "\n\n",  
		"\t\t\t-----------------------------------------------",
		"<被滤除的仅有零个面的物体列表>------------------------");
	AddToMsgList( msgListZeroFace, buf );

	// 滤除材质嵌套结束
	wsprintf( buf, "%s%s%s", "\n\n",  
		"\t\t\t-----------------------------------------------",
		"<被滤除的存在材质嵌套的物体列表>------------------------");
	AddToMsgList( msgListMulti2, buf );

	// 滤除CAD底图结束
	wsprintf( buf, "%s%s%s", "\n\n",  
		"\t\t\t-----------------------------------------------",
		"<被滤除的疑由CAD底图生成的物体列表>--------------------");
	AddToMsgList( msgListCadFace, buf );

	// 滤除其他类型物体结束
#ifndef _MOD
	wsprintf( buf, "%s%s%s", "\n\n",  
		"\t\t\t-----------------------------------------------",
		"<被滤除的非关键帧物体列表>--------------------");
#else
	wsprintf( buf, "%s%s%s", "\n\n",  
		"\t\t\t-----------------------------------------------",
		"<被滤除的关键帧物体或普通物体列表>--------------------");
#endif
	AddToMsgList( msgListOtherType, buf );

	wsprintf( buf, "%c", '\n');
	AddToMsgList( msgListHead, buf );
	TSTR cstrTemp;
	int nFilterObject = msgListZeroFace.Count() + msgListMulti2.Count() + msgListCadFace.Count() 
		+ msgListOtherType.Count() - 4*4;
	cstrTemp.printf( "\t\t场景导出成功!  共滤除模型:%d个   共导出模型:%d个,材质:%d个,三角面:%d个" ,
		nFilterObject, pTheModels->size() , pTheMtls->Count(),  pTheModels->m_nTotalFaceCount );
	AddToMsgList( msgListHead, cstrTemp.data() );

	wsprintf( buf, "%c", '\n');
	AddToMsgList( msgListHead, buf );
	sprintf_s( buf, UCHAR_MAX, 
		"\t\t场景中心坐标(X0,   Y0,   Z0) = (%e,   %e,   %e)" ,
		m_oSceneCenter.x,  m_oSceneCenter.y,  m_oSceneCenter.z );
	AddToMsgList( msgListHead, buf );
	wsprintf( buf, "%c", '\n');
	AddToMsgList( msgListHead, buf );

}

bool vgModExportor::FilterFaultyObject(INode* pNode, E_Return_Type status)
{
	TCHAR	buf[ UCHAR_MAX ]="", format[ UCHAR_MAX ]="", strFmt[UCHAR_MAX];
	memset( buf, 0,UCHAR_MAX);
	memset( format, 0,UCHAR_MAX);
	memset( strFmt, 0,UCHAR_MAX);

	wsprintf( strFmt, "%%%ds", MSG_BLOCK_LENGTH);
	wsprintf( format, "%s%s%s%s", strFmt,strFmt,strFmt,strFmt  );

	TCHAR  strTemp0[25]="序号",strTemp1[25]="序号",strTemp2[25]="颜色/纹理",
		strTemp3[35]="RGB/文件名",strTemp4[25]="透明通道" ;

	_tcsncpy_s( strTemp1, 25, newobj->strName, 19 );
	wsprintf( strTemp2, "%d", newobj->numOfFaces );
	wsprintf( strTemp3, "%d%c", newobj->numOfVerts,'\0' );

	//  过滤模型case1：点数或面数为零, 如果点数或面数为零，则滤除该物体
	if (
		((newobj->numOfVerts == 0)
		||(newobj->numOfFaces == 0))
		//&& g_bZeroVert 默认滤除
		) 
	{
		wsprintf( strTemp0, "%d", msgListZeroFace.Count()-2 );
		wsprintf( buf, format, strTemp0, strTemp1, strTemp2, strTemp3 );
		AddToMsgList(msgListZeroFace, buf);

		delete newobj;
		newobj = NULL;
		return true;
	}

	//	过滤模型case2：多维子嵌套
	if ( RETURN_MTL_MULTITEX_NEST == status /*&& g_bMulti2Text*/) //默认滤除
	{
		wsprintf( strTemp0, "%d", msgListMulti2.Count()-2 );
		wsprintf( buf, format, strTemp0, strTemp1, strTemp2, strTemp3 );
		AddToMsgList(msgListMulti2, buf);

		delete newobj;
		newobj = NULL;
		return true;
	}

	//	过滤模型case3：去除CAD底图 即cad导入的面片或线框, 厚度小于 0.5
	float fltObjectHeight = newobj->m_maxPoint.y - newobj->m_minPoint.y ;
	if (
		(fltObjectHeight < 0.08f)
		&& !m_eObjectFilter.getFilterFlag(FACE_FROM_CAD)
		)
	{
		wsprintf( strTemp0, "%d", msgListCadFace.Count()-2 );
		//wsprintf( strTemp3, "%3.3f", fltObjectHeight );

		wsprintf( buf, format, strTemp0, strTemp1, strTemp2, strTemp3 );
		AddToMsgList(msgListCadFace, buf);

		delete newobj;
		newobj = NULL;
		return true;
	}
	//////////////////////////////////////////////////////////////////////////


	//	获取每个物体的关键帧信息
	ComputerKeyFrames(pNode);

	//	过滤模型case4：滤除关键帧	物体			
	if ( 
		(0 == newobj->m_nKeyFramesCount)
		&& !m_eObjectFilter.getFilterFlag(OBJ_KEYFRAME_NO) 
		)
	{
		wsprintf( strTemp0, "%d", msgListOtherType.Count()-2 );
		wsprintf( buf, format, strTemp0, strTemp1, strTemp2, strTemp3 );
		AddToMsgList(msgListOtherType, buf);

		delete newobj;
		newobj = NULL;
		return true;
	}

	//	过滤模型case5：滤除非关键帧物体				
	if ( 
		(0 != newobj->m_nKeyFramesCount)
		&& !m_eObjectFilter.getFilterFlag(OBJ_KEYFRAME_HAS)
		)
	{
		wsprintf( strTemp0, "%d", msgListOtherType.Count()-2 );
		wsprintf( buf, format, strTemp0, strTemp1, strTemp2, strTemp3 );
		AddToMsgList(msgListOtherType, buf);

		delete newobj;
		newobj = NULL;
		return true;
	}


	return false;
}

bool vgModExportor::isNeedTranlateCoordinateSystem()
{
	return m_eCoordinateSystem == XZminusY_COORDINATE;
}

void vgModExportor::setCoordinateSystem( ECoordinateSystem eCoordinate )
{
	m_eCoordinateSystem = eCoordinate;
}

void vgModExportor::_vmd_save( const TCHAR * filename )
{
#if 0
	using namespace vgModel;
	using namespace vgKernel;


	StringPairVector res;
	String srcname = filename;
	String dstname = StringUtility::getPathFromAbsoluteFilename( srcname ) 
		+ StringUtility::getFilenameWithoutExtFromAbsPath(srcname ) + ".vmd";

	res.push_back( std::make_pair( srcname,  dstname ) );

	FileWriterModToVmd vmd;

	float _lodNear = 500.0f;
	float _lodFar = 1000.0f;

	bool ret = vmd.writeToVmdFromStringPairs( res , 0.0f , 0.0f , 
		_lodNear * _lodNear , _lodFar * _lodFar );


	if(showPrompts)
	{
		if ( ret == false )
		{
			std::ostringstream o;
			o << "导出到:" << dstname << "失败.";
			MessageBox(NULL , o.str().c_str() , "提示" , MB_OK );
		}
	}
#endif
}

void vgModExportor::configExportFlag( DWORD options, bool bForceDfault /*= false*/ )
{
	exportFlags.assign(EXPORT_OPTION_COUNT, false);

	if ( ip->GetSelNodeCount() )
	{
		exportFlags[FILTER_SELECTED]	= (bool)(options & FILTER_SELECTED);
	}
	else
	{
		exportFlags[FILTER_SELECTED]	= false;
	}

	if ( bForceDfault )
	{
		exportFlags[PROMPT_SETTING] = true;
		exportFlags[PROMPT_RESULT]	= true;
		exportFlags[PROMPT_WARNING] = true;
	}
	else
	{
		exportFlags[PROMPT_SETTING]		= (bool)(options & PROMPT_SETTING);
		exportFlags[PROMPT_RESULT]		= (bool)(options & PROMPT_RESULT);
		exportFlags[PROMPT_WARNING]		= (bool)(options & PROMPT_WARNING);
	}
}
//  vgModExportor的友元函数
INT_PTR	CALLBACK MsgListDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static vgModExportor* exp;

	int tabs[3] = {24,24,24};
	switch (iMsg)
	{
	case WM_INITDIALOG:
		exp = (vgModExportor*) lParam;
		CenterWindow(hDlg, GetWindow(hDlg, GW_OWNER));
		SendDlgItemMessage(hDlg, IDC_ERROR_MSG_LIST, LB_RESETCONTENT, 0, 0);
		SendDlgItemMessage(hDlg, IDC_ERROR_MSG_LIST, LB_SETTABSTOPS, (WPARAM) 3,(LPARAM) tabs);
		exp->BuildMsgList(hDlg);
		return TRUE;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:	
			EndDialog(hDlg, TRUE); 
			break;
		}
		break;

	case WM_DESTROY:
		EndDialog(hDlg, TRUE);
		return FALSE;

	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_CLOSE) 
		{
			EndDialog(hDlg, TRUE);
			return FALSE;
		}

	}
	return FALSE;
}




INT_PTR CALLBACK ExportOptionsDlgProc(HWND hDlg, UINT message,	WPARAM wParam, LPARAM lParam) 
{
	static vgModExportor* exp;

	switch(message) 
	{
	case WM_INITDIALOG:
		//	SetWindowContextHelpId(hDlg, idh_3dsexp_export);
		exp = (vgModExportor*) lParam;
		CenterWindow(hDlg,GetParent(hDlg));
		SetFocus(hDlg); // For some reason this was necessary.  DS-3/4/96


		// 模型过滤 - 复选框
		CheckDlgButton(hDlg, IDC_CAD_REF_FACE, 
			exp->m_eObjectFilter.getFilterFlag(FACE_FROM_CAD) );
		
		CheckDlgButton(hDlg, IDC_OBJ_TYPE_NO_KEY, 
			exp->m_eObjectFilter.getFilterFlag(OBJ_KEYFRAME_NO) );
		
		CheckDlgButton(hDlg, IDC_OBJ_TYPE_HAS_KEY, 
			exp->m_eObjectFilter.getFilterFlag(OBJ_KEYFRAME_HAS) );
		

		// 元素过滤 - 复选框
		CheckDlgButton(hDlg, IDC_OBJ_KEYFRAME, 
			exp->m_eElementFilter.getFilterFlag(OBJ_KEYFRAME_ELEMENT) );
		
		CheckDlgButton(hDlg, IDC_MTL_NAME_SUFFIX, 
			exp->m_eElementFilter.getFilterFlag(MTL_NAME_SUFFIX_ELEMENT) );

		CheckDlgButton(hDlg, IDC_MTL_TO_DDS, 
			exp->m_eElementFilter.getFilterFlag(MTL_EXT_TO_DDS_ELEMENT) );


		// 参数输入 - 文本
		SetDlgItemText(hDlg, IDC_EDIT_X0, g_strCenterX.data() );
		SetDlgItemText(hDlg, IDC_EDIT_Y0, g_strCenterY.data() );
		SetDlgItemText(hDlg, IDC_EDIT_Z0, g_strCenterZ.data() );

		SetDlgItemText(hDlg, IDC_NAME_PREFIX, g_strPrefix.data() );
		SetDlgItemText(hDlg, IDC_COORD_SCALE, g_strScale.data() );


		// 参数选择	- 单选框
		CheckRadioButton(hDlg,IDC_RADIO1,IDC_RADIO2,IDC_RADIO2);


		return FALSE;

	case WM_DESTROY:
		return FALSE;

	case WM_COMMAND:
		switch(LOWORD(wParam)) 
		{
		case IDOK:
			//MaxUVs = IsDlgButtonChecked(hDlg, IDC_MAX_UVS);
			//g_bZeroVert = IsDlgButtonChecked(hDlg, IDC_ZERO_VERT_FACE);
			//g_bMulti2Text = IsDlgButtonChecked(hDlg, IDC_TEXTURE_MULTI2);
			exp->m_eObjectFilter.getFilterFlag(FACE_FROM_CAD) = 
				IsDlgButtonChecked(hDlg, IDC_CAD_REF_FACE);
			
			exp->m_eObjectFilter.getFilterFlag(OBJ_KEYFRAME_NO) = 
				IsDlgButtonChecked(hDlg, IDC_OBJ_TYPE_NO_KEY);
			
			exp->m_eObjectFilter.getFilterFlag(OBJ_KEYFRAME_HAS) = 
				IsDlgButtonChecked(hDlg, IDC_OBJ_TYPE_HAS_KEY);


			GetDlgItemText(hDlg, IDC_EDIT_X0, g_strCenterX.data() ,20);
			GetDlgItemText(hDlg, IDC_EDIT_Y0, g_strCenterY.data() ,20);
			GetDlgItemText(hDlg, IDC_EDIT_Z0, g_strCenterZ.data() ,20);


			g_strPrefix.Resize(20);			
			GetDlgItemText(hDlg, IDC_NAME_PREFIX, g_strPrefix.data() ,20);
			GetDlgItemText(hDlg, IDC_COORD_SCALE, g_strScale.data() ,20);
			//GetDlgItemText(hDlg, IDC_EDIT_SCALE, g_strScale.data() ,20);

			//exp->m_keyframeInfo = IsDlgButtonChecked(hDlg, IDC_RADIO1);


			exp->m_eElementFilter.getFilterFlag(OBJ_KEYFRAME_ELEMENT) = 
				IsDlgButtonChecked(hDlg, IDC_OBJ_KEYFRAME);
			
			exp->m_eElementFilter.getFilterFlag(MTL_NAME_SUFFIX_ELEMENT) = 
				IsDlgButtonChecked(hDlg, IDC_MTL_NAME_SUFFIX);

			if( IsDlgButtonChecked(hDlg, IDC_RADIO1) )
			{
				exp->setCoordinateSystem( XYZ_COORDINATE );
			}
			else
			{
				exp->setCoordinateSystem( XZminusY_COORDINATE );
			}

			exp->m_eElementFilter.getFilterFlag(MTL_EXT_TO_DDS_ELEMENT) = 
				IsDlgButtonChecked(hDlg, IDC_MTL_TO_DDS);


			EndDialog(hDlg, 1);
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		}

	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_CONTEXTHELP) 
		{
			//		DoHelp(HELP_CONTEXT, idh_3dsexp_export);
			return FALSE;
		}

	}
	return FALSE;
}//ExportOptionsDlgProc



////////////////////////////////////////////////////	导出结构信息输出处理	

BOOL	ApproxEqual(float a, float b)
{
	float eps = float(1.0e-5);
	float d = (float) fabs(a-b);
	return d < eps;
}


Matrix3	GetLocalNodeTM(INode* node, TimeValue t)
{
	Matrix3 tm(TRUE);
	if (node) {
		tm = node->GetNodeTM(t);
		if (!node->GetParentNode()->IsRootNode()) {
			Matrix3 ip = Inverse(node->GetParentNode()->GetNodeTM(t));
			tm = tm * ip;
		}
	}
	return tm;
}



BOOL	UndoParentsOffset(INode* node, Point3& pt, Quat& rOff)
{
	INode* parent;
	Matrix3 mat(TRUE);
	Quat pOff;
	if (node && pt && rOff) {
		if (!node->GetParentNode()->IsRootNode()) {
			parent = node->GetParentNode();
			pOff   = parent->GetObjOffsetRot();
			if (pOff == IdentQuat()) return FALSE;
			pOff.MakeMatrix(mat);
			mat   = Inverse(mat);
			pt    = VectorTransform(mat, pt);
			rOff  = rOff/pOff;
			return TRUE;
		}
	}
	return FALSE;
}



////////////////////////////////////////////////////	导出结构信息输出处理	
//////////////////////////////////////////////////////////////////////////

void ObjectFilter::initializeFilterMsgList()
{
	m_strFilterMsgList.assign(COUNT_FILTER_OBJECT, StrVec());
	// 待完善...
}

BOOL& ObjectFilter::getFilterFlag( EObjectFilter filter )
{
	return m_bFilterFlag[filter];
}

BOOL& ElementFilter::getFilterFlag( EElementFilter filter )
{
	return m_bFilterFlag[filter];
}
