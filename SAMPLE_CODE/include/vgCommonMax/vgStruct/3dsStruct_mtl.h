#ifndef _3DS_STRUCT_MTL_H_INCLUDED_
#define _3DS_STRUCT_MTL_H_INCLUDED_

#include <vgStableHeaders.h>

typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned int uint;


typedef struct {
	uchar shade;		/* shading level for auto-cubic */
	uchar aalevel;		/* anti-alias level for auto-cubic */
	ushort flags;		/* auto cubic flags */
	int size;			/* bitmap size for auto-cubic */
	int nth;				/* do nth frame for auto-cubic */
} AutoCubicParams;



typedef struct cubmap	{
	//	Bitmap *mapptr[6];
	char mapname[6][13];
	short flags;
	short objnum;	/* for auto-cubic= point-of-view object: -1 for user defined*/
	short mtlobj; /* object referred to to find which face is mapped (morphing)*/
	struct cubmap *next;
	// Bitmap *blurmap;  
	int x,y;  /* location for mirrors */
} Cubmap;



typedef struct sxpent {
	char name[13];
	ULONG handle;
	void *pdata;
	struct sxpent *next;
} SXPentry;



#pragma pack(1)

struct	Color_f
{
	union
	{ 
		struct  
		{
			float r,g,b;
		};
		float f[3];
	};
} ;

typedef struct {
	unsigned char r,g,b;
} Color_24;

#pragma pack()

typedef struct {
	uchar type; /* MAP_TYPE_UV, MAP_TYPE_SXP */
	ushort texflags;
	void *sxp_data;
#if	IMPORT_MAX_LIB
	Bitmap *bm;
#endif
	float texblur;		/* texture blur  */
	float uscale,vscale;
	float uoffset,voffset;
	float ang_sin,ang_cos;
	Color_24 col1,col2;  /* tinting colors */
	Color_24 rcol,gcol,bcol;  /* RGB tinting colors */
} MapParams;

typedef struct {
	AutoCubicParams acb;  /* auto-cubic params */
#if	IMPORT_MAX_LIB
	Bitmap *bm;
	Bitmap *blurbm;
#endif
} RMapParams;


typedef struct {
	uchar ok; 
	uchar kind;		/* Texture(0) or Reflection map (1)*/
	char name[13];
	union {
		MapParams tex;	  /* kind == 0 */
		RMapParams ref;  /* kind == 1 */
	} p;
} MapData;

typedef struct {
	uchar use;
	union { float f; int pct;} amt;
	MapData map;
	MapData mask;
} Mapping;


struct MtlName{
	char s[20];
};

struct SMtl {
	char name[LENGTH_MTL_NAME];		 	/* Material's 16-char name		*/
	Color_24 amb;		 	/* 0-255 triplets			*/
	Color_24 diff;			 /* 0-255 triplets			*/
	Color_24 spec;		 	/* 0-255 triplets			*/
	short transparency;	/* 0-100	*/
	short shading;		 	/* 0=WIRE 1=FLAT 2=GOURAUD 3=PHONG 4=METAL	*/
	unsigned long flags;		 	/* Material flags	*/
	unsigned short use;   			/* Use  flags */

	/* Effect percent sliders */
	short shininess;	 	/* 0-100	   */
	short shin2pct;		/* 0-100    */
	short shin3pct;		/* 0-100    */
	short xpfall;			/* 0-100   	*/
	short refblur;			/* 0-100   	*/
	short selfipct;	  	/* 0-100    */
	float wiresize;   /* size of wire frame */

	Mapping *map[8];
	void *appdata;

	// Mod材质的精简信息
	//char		name[255];				// 名称 	
	bool		bHasTexture;			// 是否有纹理标志
	bool		bHasAlpha;				// 是否有透明纹理标志

	Color_24	diffColor;			// 颜色
	char		diffuseBitmap[255];	// 纹理
	char		opacityBitmap[255];	// 透贴纹理

	//uv重复
	float		uTile;
	float		vTile;
};

/* Material library in-memory list */
struct Mliblist	{
	SMtl material;
	Mliblist *next;
};

/* Current mesh's in-memory list */
struct Mmtllist	{
	SMtl material;
	Mmtllist *next;
	short flags;
};

#endif//_3DS_STRUCT_MTL_H_INCLUDED_