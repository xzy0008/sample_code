#include <vgStableHeaders.h>
/**********************************************************************
*<
vgMtl.h:	与模型材质信息相关的数据结构及其相关操作定义
主要内容是： struct SMtl  和
			 class MeshMtlList;
*>	
**********************************************************************/
#include "vgMtl.h"
#include "vgModelExpres.h"
//#include "ModExport.h"

#include "Max.h"
#include <stdio.h>
#include <direct.h>
#include <commdlg.h>
#include "splshape.h"
#include "imtl.h"
#include "dummy.h"
#include "gamma.h"

//////////////////////////////////////////////////////////////////////////
// 全局函数声明与定义
TCHAR* GetString(int id);

// 标准材质判定
int IsStdMulti(Mtl *m) 
{
	//return (m->ClassID()==Class_ID(MULTI_CLASS_ID,0))?1:0; 
	//2008-2-29 9:43:13 刘寿生 修改：测试 待返原
	unsigned long mtlClassID = m->ClassID().PartA();
	if( mtlClassID == MULTI_CLASS_ID )
		return 1;
	else
		return 0;
}

// 壳材质判定
bool IsShellMtl(Mtl *m)
{
	unsigned long mtlClassID = m->ClassID().PartA();
	if( mtlClassID == BAKE_SHELL_CLASS_ID )
		return true;
	else
		return false;
}

// maps索引
static int MAXMapIndex(int i) 
{
	switch(i) {
case Ntex:  return ID_DI;
case Ntex2: return ID_DI;
case Nopac: return ID_OP;
case Nbump: return ID_BU;
case Nspec: return ID_SP;
case Nshin: return ID_SH;
case Nselfi:return ID_SI; 
case Nrefl: return ID_RL;
default:    return ID_DI;
	}
}

// jpg、tga等图片扩展名转dds
void	MeshMtlList::Jpgplapla2dds(TSTR& name) 
{
	// filename.ext -> filename_ext.dds , 2008-10-24 8:50:23 update by lss
	int  dotPosition ;
	dotPosition = name.last('.');
	assert(dotPosition != -1);

	if ( -1 != dotPosition )
	{
		TSTR	_ext = name.Substr(dotPosition+1, 3);
		TSTR	dotDDS = _T(".DDS");
		name.remove(dotPosition);

		if ( isNeedAppendSuffix( string(_ext.data()) ) )
		{
			name.Append( _T("_") );
			name.Append(_ext);
		}
		name.Append( dotDDS );
	}
}

// 图片名加前缀
static void	AddPrefix(TSTR& name, TSTR prefix) 
{
	// filename.ext -> filename_ext.dds , 2008-10-24 8:50:23 update by lss
	TSTR tempStr(prefix);
	tempStr.Append(name);
	name = tempStr;
}
//static void	Jpgplapla2dds(TSTR& name) 
//{
//	int  dotPosition ;
//	dotPosition = name.last('.');
//	assert(dotPosition != -1);
//
//	if ( -1 != dotPosition )
//	{
//		name.remove(dotPosition);
//		name.Append(TSTR(".DDS"));
//	}
//}

// 生成唯一材质名
static void IncrName(char *name, char *inm, int n) 
{
	char buf[17], num[5];
	memset(buf, 0, sizeof(buf) );
	memset(num, 0, sizeof(num) );

	_tcsncpy_s(buf, 17, name, 12);
	buf[16] = 0;
	sprintf_s( num, 5, "%d", n);
	strcat_s( buf, 17, num);
	strcpy_s( inm, 17, buf);
	//_stprintf_s( inm, sizeof(inm), "%s%d\0",buf,n);
} 
//////////////////////////////////////////////////	全局函数声明与定义
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//	class MeshMtlList;
int MeshMtlList::FindMtl(Mtl *m) 
{
	for (int i=0; i<Count(); i++) 
		if  ( (*this)[i].m == m ) return i;
	return -1;
}

int  MeshMtlList::FindSName(char *name) 
{
	for (int i=0; i<Count(); i++) 
		if  ( strcmp(name,(*this)[i].sm->name)==0) 
			return i;
	return -1;
}

void MeshMtlList::AddMtl(Mtl *m) 
{
	if (m==NULL) return;
	Interval v;
	m->Update(0,v);

	Mtl *sub=NULL;
	
	unsigned long mtlClassID = m->ClassID().PartA();
	switch( mtlClassID )
	{
	case	DMTL_CLASS_ID :
		{// 标准材质
			if (FindMtl(m)<0) 
				ReallyAddMtl(m);
		}
		break;
	case	MULTI_CLASS_ID :
		{// 多维子材质
			for (int i=0; i<m->NumSubMtls(); i++) 
			{
				sub = m->GetSubMtl(i);
				if ( sub ) 
					AddMtl(sub);
			}
		}
		break;
	case	BAKE_SHELL_CLASS_ID :
		{// 壳材质
			sub= m->GetSubMtl(0);
			if ( sub )
				AddMtl( sub );

			sub = m->GetSubMtl(1);
			if ( sub )
				AddMtl( sub );
		}
		break;
	default:
		break;
	} // switch( mtlClassID )	材质分类
	
} // void MeshMtlList::AddMtl(Mtl *m)

void MeshMtlList::ConvertMaxMtlToSMtl( SMtl *s, Mtl *m) 
{
	Interval v;
	m->Update(0,v);

	// 获取材质全局唯一的名称
	char buf[17]; // 17->27
	memset(buf, 0, sizeof(buf) );
	_tcsncpy_s(buf, 17, m->GetName(),16);
	if (strlen(buf)==0) _tcscpy_s(buf, 17, _T("Matl") );
	buf[16] = 0;
	_tcscpy_s(s->name,17, buf );
	int n=0;
	while (FindSName(s->name)>=0) 
		IncrName(buf,s->name,++n); 
	buf[16] = 0;

	// 获取材质的颜色值
	s->diffColor.b	= ( int )( 0.5f + 255.0f * m->GetDiffuse().b ) ;
	s->diffColor.g	= ( int )( 0.5f + 255.0f * m->GetDiffuse().g );
	s->diffColor.r	= ( int )( 0.5f + 255.0f * m->GetDiffuse().r );

	// ################################################################
	// Standard Material 标准材质
	unsigned long mtlClassID = m->ClassID().PartA();
	if( mtlClassID == DMTL_CLASS_ID)    
	{
		StdMat* std = (StdMat *)m;
		// 贴图
		for (int i=0; i<8; i++) 
		{
			if (i==Ntex2) continue;
			int n = MAXMapIndex(i);
			Texmap *tx;

			// 贴图通道为空，返回
			if ((tx=std->GetSubTexmap(n))==NULL) 
				continue;

			// 通道不是位图，返回
			if (tx->ClassID()!=Class_ID(BMTEX_CLASS_ID,0))  // 除BitmapTex外，其它Texmap不支持
				continue;	

			// 获取位图的文件路径和文件名
			BitmapTex *bmt = (BitmapTex*)tx;				// Bitmap Texmap
			TSTR filename, path;
			SplitPathFile(  (TSTR)(bmt->GetMapName()) ,&path,&filename);

			// 文件名全部转成大写
			filename.toUpper();

			//  扩展名转dds
			if (!filename.isNull())
			{		
			    if ( m_bToDDS )
			    {
					Jpgplapla2dds(filename);
				}
//#ifdef	_ADDPREFIX
//				AddPrefix(filename, m_prefix);
//#endif
			}

			if ( ID_DI == n )
			{// Diffuse of Maps
				_tcsncpy_s( s->diffuseBitmap, 255, filename.data(),filename.Length());
				s->bHasTexture	= true;
			}
			else
			{// Opacity of Maps
				_tcsncpy_s( s->opacityBitmap, 255, filename.data(),filename.Length());
				s->bHasAlpha	= true;
			}

			// uv重复度
			StdUVGen *uv = bmt->GetUVGen();
			s->uTile	= uv->GetUScl(0);
			s->vTile	= uv->GetVScl(0);

		}// for (int i=0; i<8; i++) 8个常用maps，diffuse、opacity等
	} //if( mtlClassID == DMTL_CLASS_ID) Standard Material 标准材质
	// ###############################################################

}


void MeshMtlList::ReallyAddMtl(Mtl *m) 
{
	MEntry me ;
	SMtl *s;

 	me.sm	= NULL;
	s		= new SMtl;
	memset(s,0,sizeof(SMtl));

	me.sm	= s;
	me.m	= m;

	ConvertMaxMtlToSMtl( s,m);
	Append(1,&me ,20);

}//void MeshMtlList::ReallyAddMtl(Mtl *m) 

bool MeshMtlList::getFlagAppendSuffix()
{
	return m_bAppendSuffix;
}

bool MeshMtlList::isNeedAppendSuffix( string ext )
{
	if ( !m_bAppendSuffix )
	{
		return false;
	}

	if ( ext == "DDS" || ext == "dds")
	{
		return false;
	}

	return true;
}
//////////////////////////////////////////////////	class MeshMtlList;
//////////////////////////////////////////////////////////////////////////
