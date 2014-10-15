#ifndef _3DS_STRUCT_SHAPE_H_INCLUDED_
#define _3DS_STRUCT_SHAPE_H_INCLUDED_

#include <vgInclude/vgStlHeaders.h>
#include <vgStruct/3dsStruct_mtl.h>

#include <vgKernel/vgkVec3.h>


#pragma pack(1)


/* 3DS Shape point structure */

struct shppt
{
	float x;	/* Control point */
	float y;
	float z;
	float inx;	/* Incoming vector */
	float iny;
	float inz;
	float outx;	/* Outgoing vector */
	float outy;
	float outz;
	unsigned short flags;
};
typedef struct shppt Shppt;

#pragma pack()

struct Bkgrad {
	float midpct;
	Color_f botcolor;
	Color_f midcolor;
	Color_f topcolor;
};

struct Fogdata {
	float nearplane;
	float neardens;
	float farplane;
	float fardens;
	Color_f color;
};

struct LFogData {
	float zmin,zmax;
	float density;
	short type;
	short fog_bg;
	Color_f color;
};

struct Distcue {
	float nearplane;
	float neardim;
	float farplane;
	float fardim;
};

struct BGdata {
	int bgType;
	int envType;
	Color_f bkgd_solid;
	Color_f amb_light;
	Bkgrad bkgd_gradient;
	Fogdata fog_data;
	Distcue distance_cue;
	int fog_bg,dim_bg;
	char bkgd_map[81];
	LFogData lfog_data;
};

// Some 3DS structures

#pragma pack(1)
//typedef struct {
//	float r,g,b;
//	} Color_f;
//
//typedef struct {
//	unsigned char r,g,b;
//	} Color_24;

typedef struct {
	unsigned short tag;
	long size;
} Chunk_hdr;

typedef struct {
	float x;
	float y;
	float z;
	unsigned short flags;
} Verts;

typedef struct {
	float u;
	float v;
} Texverts;

typedef struct {
	unsigned short a;
	unsigned short b;
	unsigned short c;
	unsigned char material;
	unsigned char filler;
	unsigned long sm_group;
	unsigned short flags;
} Faces;

typedef struct {
	float x;
	float y;
	float z;
	float tx;
	float ty;
	float tz;
	float bank;
	float focal;
	unsigned short flags;
	float nearplane;
	float farplane;
	void *appdata;
} Camera3DS;

typedef struct dirlight{
	float x;
	float y;
	float z;
	float tx;
	float ty;
	float tz;
	unsigned short flags;
	Color_f color;
	float hotsize;
	float fallsize;
	float lo_bias;
	//	Object_list *exclude;
	int shadsize;
	float in_range,out_range;		/* Attenuation range */
	float shadfilter;	/* size of filter box*/
	char imgfile[13];
	float ray_bias;
	float bank,aspect;	/* Spotlight bank angle, aspect ratio */
	float mult;			/* Light multiplier */
	void *appdata;
	//NameTab excList;
	vector<string> excList;
} Dirlight;

typedef struct
{
	float lo_bias,hi_bias;
	short shadsize,shadsamp,shadrange;
} Locshad;

typedef struct {
	float bias,shadfilter;
	short shadsize;
} LocShad2;

#pragma pack()


// 3DS Key structures

#pragma pack(1)


#define KEYHDR  \
	int time;  \
	float tens,cont,bias; \
	float easeTo,easeFrom;


typedef struct { float p,ds,dd; } PosElem;
typedef struct {
	KEYHDR
		PosElem e[8]; /* enough to be bigger than the biggest key,
					  including RotKey */
} Key;

typedef struct {
	KEYHDR
		PosElem e[1];
} ScalarKey;

typedef struct {
	KEYHDR
		PosElem e[3];
} PosKey;	

typedef struct {
	KEYHDR
		float angle;	/* angle of rotation in radians (always >0) */
	float axis[3]; /* axis of rotation (unit vector) */
	float q[4];  	/* quaternion describing orientation */
	float b[4];		/* incoming tangent term */
	float a[4];		/* outgoing tangent term */
} RotKey;

#ifdef LATER
typedef struct {
	KEYHDR
		Namedobj *object;  
} MorphKey;	

typedef struct {
	KEYHDR
} HideKey;
#endif // LATER

typedef struct {
	KEYHDR
		FLOAT c[3];
} ColorKey;
#pragma pack()

#if	IMPORT_MAX_LIB
typedef struct {
	Matrix3 *tm;
	Mesh *mesh;
	INode *node;
} MeshAndTMAndNode;
#endif



struct ExclListSaver {
#if	IMPORT_MAX_LIB
	GenLight *lt;
#endif
	//NameTab nametab;
	vector<string> nametab;
};

// 3DS R4 IK joint data
typedef struct {
	int		freeJoints[6];
	float	jointMins[6];
	float	jointMaxs[6];
	float	precedence[6];
	float	damping[6];
	int		limited[6];
	int		ease[6];
	int		lastModified;
} JointData3DSR4;

struct Vert3ds 
{
	vgKernel::Vec3 pt;
	vgKernel::Vec3 tv;
};

struct Face3ds 
{
	int vNum[3];
	int flags;
};


struct fc_wrt
{
	unsigned short a;
	unsigned short b;
	unsigned short c;
	unsigned short flags;
} /*Fc_wrt*/;


#endif//_3DS_STRUCT_SHAPE_H_INCLUDED_