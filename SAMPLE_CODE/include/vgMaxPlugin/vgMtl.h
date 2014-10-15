
#ifndef _VGMTL_H_INCLUDED_
#define _VGMTL_H_INCLUDED_
/**********************************************************************
*<
vgMtl.h:	与模型材质信息相关的数据结构及其相关操作声明
主要内容是： struct SMtl  和
			 class MeshMtlList;
*>	
**********************************************************************/
#include "Max.h"
#include "istdplug.h"
#include "stdmat.h"
#include "decomp.h"
#include "helpsys.h"
#include "buildver.h"

#include "vgMod.h"
//#include "bakeShell.h"

#define NMAPTYPES 8
#define Ntex 0
#define Ntex2 1
#define Nopac 2
#define Nbump 3
#define Nspec 4
#define Nshin 5
#define Nselfi 6
#define Nrefl 7

typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned int uint;

//////////////////////////////////////////////////////////////////////////
// struct SMtl 定义
typedef struct color_24
{
	uchar r;
	uchar g;
	uchar b;
} Color_24;

typedef struct color_f
{
	float r;
	float g;
	float b;
} Color_f;

struct SMtl { // 材质的精简信息
	char		name[255];				// 名称 	
	bool		bHasTexture;			// 是否有纹理标志
	bool		bHasAlpha;				// 是否有透明纹理标志

	Color_24	diffColor;			// 颜色
	char		diffuseBitmap[255];	// 纹理
	char		opacityBitmap[255];	// 透贴纹理

	//uv重复
	float		uTile;
	float		vTile;
};
/////////////////////////////////////////////////////////// struct SMtl 定义
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// struct SMtl 相关操作
int IsStdMulti(Mtl *m) ;
bool IsShellMtl(Mtl *m);
////////////////////////////////////////////////	 struct SMtl 相关操作
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//	材质接口类	//////////////////////////////////////////////////////////
struct MEntry { SMtl *sm; Mtl *m; };

class MeshMtlList: public Tab<MEntry> 
{
public:
	void AddMtl(Mtl *m);
	void ReallyAddMtl(Mtl *m);
	int FindMtl(Mtl *m);
	int FindSName(char *nam);
	void ConvertMaxMtlToSMtl( SMtl *s, Mtl *m);
	MeshMtlList( bool bAppendSuffix, bool bToDDS,
		TSTR& exportFilePath, TSTR& maxFilePath,TSTR prefix )
		:m_bAppendSuffix( bAppendSuffix )
		,m_bToDDS(bToDDS)
	{
		m_strExportFilePath = exportFilePath;
		m_strExportFilePath.remove(m_strExportFilePath.last('\\'));
		if (!maxFilePath.isNull())
		{
			m_strMaxFilePath = maxFilePath;
			m_strMaxFilePath.remove(m_strMaxFilePath.last('\\'));
		}
		else
		{ 
			m_strMaxFilePath = _T("");
		}
		m_prefix = prefix;
	}
	~MeshMtlList() {
		for (int i=0; i<Count(); i++) 
		{			
			delete (*this)[i].sm;
		}
	}

protected:
	void	Jpgplapla2dds(TSTR& name);
	bool	getFlagAppendSuffix();
	bool	isNeedAppendSuffix( std::string ext );

private:
	TSTR	m_strExportFilePath, m_strMaxFilePath;
	TSTR	m_prefix;
	
	bool	m_bAppendSuffix, m_bToDDS;
};			
////////////////////////////////////////////////////////////	材质接口类	
//////////////////////////////////////////////////////////////////////////


#endif	//_VGMTL_H_INCLUDED_