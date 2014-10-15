
#ifndef _MODEXPORT_H_INCLUDED_
#define _MODEXPORT_H_INCLUDED_
/**********************************************************************
*<
ModExport.h:	.MOD格式 场景导出插件头文件
主要内容是： 全局变量、全局函数、文件类的声明及定义
*>	
**********************************************************************/

#include "Max.h"
#include "istdplug.h"
#include "stdmat.h"
#include "decomp.h"
#include "helpsys.h"
#include "buildver.h"

#include <stdarg.h>

#include "vgModelExpres.h"
#include "vgMod.h"
#include "vgMtl.h"
#include "vgObjectSet.h"

#include "vgMaxPlugin/vgMaxPrerequisite.h"

//////////////////////////////////////////////////////////////////////////
//		全局变量	//////////////////////////////////////////////////////

HINSTANCE hInstance;

//static BOOL showPrompts;

//extern BOOL	exportSelected;

static Tab<TSTR*> msgList, msgListHead, msgListTexture, msgListObject;
static Tab<TSTR*> msgListZeroFace,msgListMulti2,msgListCadFace,msgListOtherType;

BitArray	bFaceOfMatOne;
BitArray	bFaceOfMatAll;
BitArray	vertFlag;
long		totleFaceWithMat;

Tab<int> mtlNumMap;
int mtlnum;
int bakedMtlNo ;
BOOL multiMtl;


static BOOL bTexture;

static	TSTR	g_strCenterX="0.0f", g_strCenterY="0.0f", g_strCenterZ=	"0.0f";
static	TSTR	g_strScale= "1.0f";
static	TSTR	g_strPrefix;//"Plan_i";

////////////////////////////////////////////////////////////	全局变量
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//   全局函数  ///////////////////////////////////////////////////////
TCHAR* GetString(int id)
{
	static TCHAR stBuf[SCHAR_MAX];
	if (hInstance)
		return LoadString(hInstance, id, stBuf, SCHAR_MAX) ? stBuf : NULL;
	return NULL;
}

static void MessageBox(int s1, int s2) {
	TSTR str1(GetString(s1));
	TSTR str2(GetString(s2));
	MessageBox(GetActiveWindow(), str1.data(), str2.data(), MB_OK);
}

static int MessageBox(int s1, int s2, int option = MB_OK) {
	TSTR str1(GetString(s1));
	TSTR str2(GetString(s2));
	return MessageBox(GetActiveWindow(), str1, str2, option);
}

static int Alert(int s1, int s2 = IDS_TH_VGMODEXP, int option = MB_OK) {
	return MessageBox(s1, s2, option);
}


DWORD WINAPI fn(LPVOID arg)
{
	return(0);
}

// 向量辅助操作：求模、相等、点乘、叉乘、单位化
#define Mag(V) (sqrtf(V.x*V.x + V.y*V.y + V.z*V.z))

BOOL operator==(const Matrix3 &m1, const Matrix3 &m2) 
{
	for (int i=0; i<4; i++) {
		if (m1.GetRow(i) != m2.GetRow(i)) return FALSE;
	}
	return TRUE;
}

CVector3 SubVector(CVector3 vPoint1, CVector3 vPoint2)
{
	CVector3 vVector;

	vVector.x = vPoint1.x - vPoint2.x;
	vVector.y = vPoint1.y - vPoint2.y;
	vVector.z = vPoint1.z - vPoint2.z;
	return vVector;
}

float DotProduct(CVector3 vVector1, CVector3 vVector2)
{
	float resultDot = 0.0f;
	for(int index =0; index<3; index++)
		resultDot += vVector1.vert[index] * vVector2.vert[index]  ;
	return resultDot;
}

CVector3 Cross(CVector3 vVector1, CVector3 vVector2)
{
	CVector3 vCross;
	vCross.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));
	vCross.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));
	vCross.z = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));
	return vCross;
}

CVector3 Normalize(CVector3 vNormal)
{
	double Magnitude;							

	Magnitude = Mag(vNormal);

	vNormal.x /= (float)Magnitude;				
	vNormal.y /= (float)Magnitude;				
	vNormal.z /= (float)Magnitude;				

	return vNormal;								
}

BOOL	UVVertEqual(UVVert tv0, UVVert tv1) 
{
	return (tv0.x == tv1.x &&
		tv0.y == tv1.y &&
		tv0.y == tv1.y);
}

//INT_PTR CALLBACK MsgListDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
//void AddToMsgList(Tab<TSTR*>& mList, TCHAR* msg);
//void	ClearMsgList();

inline BOOL		ApproxEqual(float a, float b);
inline Matrix3	GetLocalNodeTM(INode* node, TimeValue t);
inline BOOL		UndoParentsOffset(INode* node, Point3& pt, Quat& rOff);




///////////////////////////////////////////////////////////		全局函数
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//  文件操作类  //////////////////////////////////////////////////////////
class WorkFile {
private:
	FILE *stream;

public:
	WorkFile(const TCHAR *filename,const TCHAR *mode) 
	{ 
		stream = NULL; 
		Open(filename, mode); 
	};
	~WorkFile() { Close(); };

	FILE *	Stream() { return stream; };

	int		Close() 
	{ 
		int result=0; 
		if(stream) 
			result=fclose(stream); 
		stream = NULL; 
		return result; 
	}
	void	Open(const TCHAR *filename,const TCHAR *mode) 
	{ 
		Close(); 
		_tfopen_s( &stream, filename, mode); 
	}
};
//////////////////////////////////////////////////////////////	文件操作类
//////////////////////////////////////////////////////////////////////////

typedef
enum	_enumCoordinateSystem
{
	XYZ_COORDINATE,
	XZminusY_COORDINATE,
	COUNT_COORDINATE
} ECoordinateSystem;


typedef 
enum	_enumObjectFilter	//  ___________________________________
{							//	|滤除类型		|判别标准			|
							//	|				|					|
	FACE_ZERO,				//	|空物体			|点数为0 或 面数为0	|
	MTL_MULTITEX_NEST,		//	|多维子嵌套		|子材质不是STANDARD	|
							//	|				|					|
	FACE_FROM_CAD,			//	|Cad 底图面片	|厚度为0 且 无材质	|
	OBJ_KEYFRAME_NO,		//	|含关键帧		|帧数不为0			|
	OBJ_KEYFRAME_HAS,		//	|不含关键帧		|帧数为0			|
							//	|-----------------------------------|
	COUNT_FILTER_OBJECT		//	|过滤器数目							|
} EObjectFilter;			//	|___________________________________|

typedef 
enum	_enumElementFilter	//  ___________________________________
{							//	|滤除类型		|判别标准			|
							//	|				|					|
	OBJ_KEYFRAME_ELEMENT,	//	|关键帧信息		|帧数不为0			|
	MTL_NAME_SUFFIX_ELEMENT,//	|纹理名后缀信息	|界面设置			|
	MTL_EXT_TO_DDS_ELEMENT,	//	|纹理扩展名转dds|界面设置			|
							//	|---------------|-------------------|
	COUNT_FILTER_ELEMENT	//	|过滤器数目							|
} EElementFilter;			//	|___________________________________|

class	ObjectFilter
{
	//typedef	Tab<TSTR*>	MaxStrVec;
	//typedef	vector<MaxStrVec>	FilterMsgList;
	typedef	vector<string>		StrVec;
	typedef	vector<StrVec>		FilterMsgList;

public:
	FilterMsgList	m_strFilterMsgList;
	vector<BOOL>	m_bFilterFlag;
	
	ObjectFilter()
	{
		m_bFilterFlag.assign(COUNT_FILTER_OBJECT, FALSE);
		m_bFilterFlag[FACE_ZERO]			= FALSE;
		m_bFilterFlag[MTL_MULTITEX_NEST]	= FALSE;
	
		m_bFilterFlag[FACE_FROM_CAD]	= TRUE;
		m_bFilterFlag[OBJ_KEYFRAME_NO]	= TRUE;
		m_bFilterFlag[OBJ_KEYFRAME_HAS] = TRUE;

		initializeFilterMsgList();
	}

	BOOL&	getFilterFlag( EObjectFilter filter);
	void	initializeFilterMsgList();
	
};//ObjectFilter

class	ElementFilter
{
public:
	vector<BOOL>	m_bFilterFlag;

	ElementFilter()
	{
		m_bFilterFlag.assign(COUNT_FILTER_ELEMENT, FALSE);
		m_bFilterFlag[OBJ_KEYFRAME_ELEMENT]	= TRUE;
		m_bFilterFlag[MTL_NAME_SUFFIX_ELEMENT]	= TRUE;
		m_bFilterFlag[MTL_EXT_TO_DDS_ELEMENT]	= TRUE;
	}

	BOOL&	getFilterFlag( EElementFilter filter);

};//ObjectFilter

//static	tagObjectFilterFlag g_tagObjectFilterFlag;


//////////////////////////////////////////////////////////////////////////
//		插件功能类	//////////////////////////////////////////////////////
class	vgModExportor : public SceneExport 
{

	friend INT_PTR CALLBACK ExportOptionsDlgProc(HWND hDlg, UINT message, 
		WPARAM wParam, LPARAM lParam);
	friend INT_PTR	CALLBACK MsgListDlgProc(HWND hDlg, UINT iMsg, 
		WPARAM wParam, LPARAM lParam);


public:
	void	reset();
	vgModExportor();
	~vgModExportor();


	//  Part ０: 重载基类SceneExport的纯虚函数
	int				ExtCount();					// 支持文件扩展名数量
	const TCHAR *	Ext(int n);					// 文件扩展名
	const TCHAR *	LongDesc();					// 文件长描述
	const TCHAR *	ShortDesc();				// 文件短描述
	const TCHAR *	AuthorName();				// 插件作者
	const TCHAR *	CopyrightMessage();			// 插件版权所有者
	const TCHAR *	OtherMessage1();			// 其它 #1
	const TCHAR *	OtherMessage2();			// 其它 #2
	unsigned int	Version();					// 版本*100
	void			ShowAbout(HWND hWnd);		// 关于
	BOOL			SupportsOptions(int ext, DWORD options);
	int				DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, 
		BOOL suppressPrompts = FALSE, DWORD options = 0);	// Export file

	void _vmd_save( const TCHAR * filename );

	//  Part 1: 场景数据获取过程
public:
	int		_mod_save(const TCHAR *filename, ExpInterface *ei, vgModExportor* exp);
	bool	CollectDataForObjects();
	E_Return_Type	CollectGeoDataForEachObj(ObjectEntry *oe);
	E_Return_Type	CollectMtlDataForEachObj(Mtl*mtl);

	int		ComputerVerts(  MeshAndTMAndNode *mt ,t3DObject *newobj );
	int		ComputerBound( t3DObject* pObject);
	int		ComputerNormal( t3DObject * pObject);
	int		ComputerSWFaces(  t3DObject * pObject);
	int		sw_searchForAdjacent( t3DObject *newobj, int faceid , 
		int& point1 , int& point2 );
	BOOL	ComputerKeyFrames(INode* node );
	bool	HasKeyFrames(INode* node);
	bool	FilterFaultyObject(INode* pNode, E_Return_Type status);

	
	//	Part 2: 导出结构信息输出处理
protected:
	void	AddToMsgList(Tab<TSTR*>& mList, TCHAR* msg);
	void	AddLineToListDlg(HWND hDlg, const TCHAR* buf);
	void	BuildMsgList(HWND hDlg);
	void	ClearMsgList();
	void	DumpMtlListBegin();
	void	DumpObjListBegin();
	void	DumpMtlListProcess();
	void	DumpObjListProcess();
	void	DumpMtlListEnd();
	void	DumpObjListEnd();

private:
	// 坐标系
	bool	isNeedTranlateCoordinateSystem();
	void	setCoordinateSystem(ECoordinateSystem eCoordinate);

private:
	// 导出选项配置
	void	configExportFlag(DWORD options, bool bForceDfault = false);

protected:	// 临时数据
	unsigned int	m_nVersionMod;			
	//float			m_fltCenterX, m_fltCenterY, m_fltCenterZ;
	CVector3		m_oSceneCenter;
	float			m_fScale;
	//  场景接口
	Interface *ip;

	ObjectFilter	m_eObjectFilter;		//	模型过滤 标记结构体
	ElementFilter	m_eElementFilter;	//	模型内数据元素过滤 标记结构体
	//bool	m_keyframeInfo;
	ECoordinateSystem	m_eCoordinateSystem;

protected:
	FILE*			pStream ;			//	全局文件指针
	t3DModel*		pTheModels ;		//	全局模型指针
	SceneEnumProc*	pTheSceneEnum ;		//	全局场景接口
	MeshMtlList*	pTheMtls ;			//	全局材质接口
	ObjectList*		pTheObjects ;		//	全局物体接口


private:	//	常用临时变量
	t3DObject*		newobj ;			//	当前物体指针
	tMaterialInfo*	newmat ;			//	当前材质指针
	tMatandFace*	newrender ;			//	当前材质面索引指针
	Mesh*			newmesh ;			//	当前网格指针
	SMtl*			savemtl ;			//	当前标准材质指针

	vector<bool>	exportFlags;

};//class	vgModExportor
//////////////////////////////////////////////////////////		插件功能类
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//		插件描述类	//////////////////////////////////////////////////////
class vgModClassDesc : public ClassDesc 
{
public:
	int 			IsPublic() { return 1; }
	void *			Create(BOOL loading = FALSE) { return new	vgModExportor; }
	const TCHAR *	ClassName() { return GetString(IDS_TH_VGMOD); }
	SClass_ID		SuperClassID() { return SCENE_EXPORT_CLASS_ID; }
	Class_ID		ClassID() 
	{ 
#ifdef _DEBUG
		return	CLASS_ID_MOD_MAXPLUGIN_JPG_DEBUG;

#else
		return	CLASS_ID_MOD_MAXPLUGIN_JPG_RELEASE;
		
#endif//_DEBUG
	}
	const TCHAR* 	Category() { return GetString(IDS_TH_SCENEEXPORT);  }

};//class vgModClassDesc
/////////////////////////////////////////////////////////	插件描述类
//////////////////////////////////////////////////////////////////////////

#endif	//_MODEXPORT_H_INCLUDED_