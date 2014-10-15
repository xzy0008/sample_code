
#ifndef   _VGMOD_H_INCLUDED_
#define   _VGMOD_H_INCLUDED_	
/**********************************************************************
*<
vgMod.h:	与模型几何信息相关的数据结构声明
主要内容是： 点、面、模型等结构体
*>	
**********************************************************************/
#include "Max.h"
#include "istdplug.h"
#include "stdmat.h"
#include "decomp.h"
#include "helpsys.h"
#include "buildver.h"
#include "maxtypes.h"

#include "vgMtl.h"
#include "vgModelExpres.h"

#include <vector>
#include <algorithm>
#include <string>
#include <map>
using namespace std;


//#define	VERSION_MOD(year, updateTime)		(	( (year)<<16 )	+	(updateTime)	)
/************************************************************************/
/* MOD版本更新记录                                                        
/*																		
/*	版本号	|	更新时间					|	更新者	|	更新原因				 
/*          |                           |           |      	
/*	2009.1	|	2009年2月5日14:20:22		|	lss		|	物体类型由枚举(互斥) 改为 宏属性项	          
/*	6		|	2008年10月17日20:58:54	|	lss		|	vgm写文件 vgObjFrameNode写vg增加内容	          
/*	5		|	2008年10月9日10:11:06	|	lss		|	vgm写文件 由合并改为不合并	          
/*	4		|	2008年6月26日14:01:41	|	lss		|	vrgis2.0  vg文件的基础版本	          
/*                                                         
/************************************************************************/
#define		YEAR_LAST		2008
#define		YEAR		2009

//#define		UPDATA_TIME	4// 2008年6月23日15:59:28	add		by lss
//#ifdef	_MOD
#define		UPDATA_TIME_LAST 5// 2008年6月27日10:19:43	update	by lss
//#else
//	#define		UPDATA_TIME 6// 2008年8月1日11:13:01		update	by yx	
//#endif

#define		UPDATA_TIME 1// 2009年2月5日14:20:22		update	by lss	

#define	VERSION_MOD(year, updateTime)		(	( (year)<<16 )	+	(updateTime) )
#define VERSION_MOD_CURRENT	VERSION_MOD(YEAR, UPDATA_TIME)
#define VERSION_MOD_LAST	VERSION_MOD(YEAR_LAST, UPDATA_TIME_LAST)

/* 物体各小块的ID定义 */
#define OBJECTS		0x1518
#define OBJECT_HEAD	0x1519
#define OBJECT_BODY	0x1520
#define OBJECT_MATINFO 0x4130

// 2008年3月5日16:39:57 添加
#define MAP_CHANNEL_ONE			1
#define MAP_CHANNEL_THREE		3
//#define MAP_CHANNEL_DEFAULT 0

#define MSG_BLOCK_LENGTH	24

#define OBJ_NAME_LENGTH		18


// 物体属性
#define 	MTL_STANDARD	(1<<0)
//#define 	MTL_SHELL		(MTL_STANDARD<<1)

#define 	OBJ_BAKED		(MTL_STANDARD<<2)
#define 	OBJ_KEYFRAME	(MTL_STANDARD<<3)

// 函数返回值类型
enum	E_Return_Type
{
	RETURN_FALSE,
	RETURN_TRUE,

	RETURN_MTL_MULTITEX_NEST,//多重纹理嵌套多重纹理
	RETURN_SCENE_EMPTY
};

class  MeshMtlList;
//////////////////////////////////////////////////////////////////////////
// 点结构
	// class CVector2
	// class CVector3
	// struct vgVertexTNP
	// struct Vert3D
struct CVector2
{
	float x,y;
};

struct Vert3D {
	Point3 pt;
	UVVert tv1;
	UVVert tv3;
};

//2008年3月5日16:36:25 添加
struct  Vert3DIndex {
	unsigned int vertIndex;
	unsigned int tvertIndex;
};

struct	CVector3
{
	union{
		struct{float x, y, z;};
		float vert[3];
	};
};
//class CVector3
//{
//public:
//	CVector3() 
//	{
//		x = y = z = 0.0f;
//	}
//	CVector3(float X, float Y, float Z) 
//	{ 
//		x = X; y = Y; z = Z;
//	}
//	CVector3(float X) 
//	{ 
//		x = X; y = X; z = X;
//	}
//	CVector3(Vert3D point) 
//	{ 
//		x = point.pt.x; 
//		y = point.pt.y; 
//		z = point.pt.z;
//	}
//	CVector3(CVector3 &point)
//	{
//		x = point.x;
//		y = point.y;
//		z = point.z;
//	}
//	inline CVector3 operator+(CVector3 vVector)
//	{
//		return CVector3(vVector.x + x, vVector.y + y, vVector.z + z);
//	}
//	inline CVector3 operator-(CVector3 vVector)
//	{
//		return CVector3(x - vVector.x, y - vVector.y, z - vVector.z);
//	}
//	inline CVector3 operator*(float num)
//	{
//		return CVector3(x * num, y * num, z * num);
//	}
//	//	2007/8/28 liangkai 新加： 重载‘*’、’==‘
//	inline int operator*(CVector3 &point)
//	{
//		return (x * point.x, y * point.x, z * point.x);
//	}
//	inline bool operator==(CVector3 &point)
//	{
//		return (x == point.x)&&(y == point.x)&&(z == point.x);
//	}
//	inline CVector3 operator/(float num)
//	{
//		return CVector3(x / num, y / num, z / num);
//	}
//
//	float x, y, z;						
//};

struct vgVertexTNP
{

public:	
	CVector2	texcoord2D;	
	CVector3	normal3D;	
	CVector3	postion3D;
};

struct vgVertexTNP2
{

public:	
	CVector2	texcoord2D;	
	CVector3	normal3D;	
	CVector3	postion3D;
	// 2008年3月6日15:25:01 添加
	CVector2	texcoord2DLit;
};

////////////////////////////////////////////////////////// 点结构
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// 面结构
	// struct tFace
	// struct tFace2
	// struct FaceMod
struct tFace
{
	int vertIndex[3];			// indicies for the verts that make up this triangle
	bool bHasTexture;
};

struct tFace2 
{
	int vertIndex[3];
};

struct FaceMod {
	int vNum[3];
	int flags;
};
////////////////////////////////////////////////////////////// 面结构
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//	其它
	// struct sw_FaceIndex
	// struct tMaterialInfo
	// struct tMatandFace
	// struct MeshAndTMAndNode
struct sw_FaceIndex
{
	int	p1;
	int p2;
	int p3;

	int	normal;

	int	p1p2AdjFaceIndex;
	int	p2p3AdjFaceIndex;
	int	p3p1AdjFaceIndex;

	bool faceVisible;

	bool p1p2Visible;
	bool p2p3Visible;
	bool p3p1Visible;

};

struct tMaterialInfo
{
	bool aphlatext;
	char  strName[255];			// The texture name
	char  strFile[255];			// The texture file name (If this is set it's a texture map)
	char  optexname[255];
	unsigned char  color[3];				// The color of the object (R, G, B)
	unsigned int   texureId;				// the texture ID

} ;

struct tMatandFace2 
{
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

};

struct tMatandFace3 
{
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

};

struct MeshAndTMAndNode{
	Matrix3 *tm;
	Mesh *mesh;
	INode *node;
} ;

struct ModKeyFrame
{
	int			m_fTime;		//	Time at which keyframe is started
	CVector3	key_translate;	//	Translation or Rotation values
	float		key_rotate[4];
	CVector3	key_scale;

	ModKeyFrame()
	{
		for (int index = 0 ; index < 4 ; index ++)
		{
			key_rotate[index] = 1.0f;
		}
	}
};
////////////////////////////////////////////////////////////// 其它
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// 模型结构
	// struct t3DObject
	// struct t3DModel
	// class SceneEntry
	// class ObjectEntry
#define OBTYPE_MESH 0
#define OBTYPE_CAMERA 1
#define OBTYPE_OMNILIGHT 2
#define OBTYPE_SPOTLIGHT 3
#define OBTYPE_DUMMY 5
#define OBTYPE_CTARGET 6
#define OBTYPE_LTARGET 7

class SceneEntry {
public:
	TSTR name;
	INode *node,*tnode;
	Object *obj;
	int type;		// See above
	int id;
	SceneEntry *next;
	SceneEntry(INode *n, Object *o, int t)
	{ 
		node = n; obj = o; type = t; next = NULL; 
		tnode = n->GetTarget();
	}
	void SetID(int id) { this->id = id; }
};

class ObjectEntry {
public:
	TriObject *tri;
	SceneEntry *entry;
	ObjectEntry *next;
	ObjectEntry(SceneEntry *e) { entry = e; next = NULL;  tri = NULL; }
};
///////////////////////////////////////////////////////// 模型结构
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//	模型命名类	/////////////////////////////////////////////////////////
class ObjName {
public:
	TSTR name;
	ObjName *next;
	ObjName(TSTR n) { name = n; next = NULL; }
};

class ObjNameList {
public:
	ObjName *head;
	ObjName *tail;
	int			count;
	ObjNameList() { head = tail = NULL; count = 0; }
	~ObjNameList();
	int			Count() { return count; }
	int			Contains(TSTR &n);
	void		Append(TSTR &n);
	void		MakeUnique(TSTR &n);
	TSTR createNewName(TSTR str, int id);
	string createPrefixName(TSTR str, int id);

private:
	typedef	map<string, int>	StrRepeatMap;
	typedef	map<string, int>::iterator	StrRepeatMapItr;
	typedef	pair<string, int>	StrRepeatPair;
	StrRepeatMap	strRepeat;

	bool	containPrefix(string& str);
	void	appendPrefix(string& str , int id);

};
///////////////////////////////////////////////////////////	   模型命名类	
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//	模型接口类	//////////////////////////////////////////////////////////
class SceneEnumProc : public ITreeEnumProc 
{
public:
	Interface	*i;
	SceneEntry *head;
	SceneEntry *tail;
	IScene		*theScene;
	int			count;
	MeshMtlList *mtlList;
	TimeValue	time;
	SceneEnumProc(IScene *scene, TimeValue t, Interface *i,
		MeshMtlList *ml,
		bool	bExportSelected);
	~SceneEnumProc();
	int			Count() { return count; }
	void		Append(INode *node, Object *obj, int type);
//	int			calleback( INode *node );
	Box3		Bound();
	SceneEntry *Find(INode *node);
	//		SceneEntry *operator[](int index);
	void BuildNames();

	int callback( INode *node );

private:
	bool exportSelected;
};
////////////////////////////////////////////////////////////	模型接口类	
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//	物体接口类	//////////////////////////////////////////////////////////
class ObjectList 
{
public:
	ObjectEntry *head;
	ObjectEntry *tail;
	int			count;
	ObjectList(SceneEnumProc &scene);
	~ObjectList();
	int			Count() { return count; }
	void		Append(SceneEntry *e);
	ObjectEntry *Contains(Object *obj);
	ObjectEntry *Contains(INode *node);
};

#endif	//_VGMOD_H_INCLUDED_	