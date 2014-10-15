#ifndef _VGMESHMTLLIST_H_INCLUDED_
#define _VGMESHMTLLIST_H_INCLUDED_

#include "vgStableHeaders.h"


struct MEntry 
{ 
	SMtl *sm; 
	//Mtl *m; 
};

class MeshMtlList: public vector<SMtl *>  
{
public:
#if	IMPORT_MAX_LIB
	// max::Mtl
	void AddMtl(Mtl *m);
	void ReallyAddMtl(Mtl *m);
	int FindMtl(Mtl *m);
	int IsStdMulti(Mtl *m);
	bool IsShellMtl(Mtl *m);// ø«≤ƒ÷ ≈–∂®

	StdMat *	New3DSDefaultMtl();
	Texmap*		MakeTex(MapData& map, SMtl *smtl, BOOL &wasSXP);


public:
	// Mtl && SMtl
	void		ConvertMaxMtlToSMtl(SMtl *s, Mtl *m);
	void		ConvertSMtlToMaxMtl( SMtl *smtl, Mtl **mtl );
	inline Color_24 C24Format(Color c) 
	{
		Color_24 a;
		a.r = (int)(255.0f*c.r);
		a.g = (int)(255.0f*c.g);
		a.b = (int)(255.0f*c.b);
		return a;
	}
	Color		ColorFrom24(Color_24 c);
#endif

public:
	// SMtl
	SMtl* FindMtl(string mtlName);
	void init_mtl_struct(SMtl *mtl);
	void FreeMatRefs(SMtl *m);

	void	formatModMtl(SMtl* mtl);
public:
	// constructor/de~
	~MeshMtlList() 
	{
		for (int i=0; i<size(); i++) 
		{
			FreeMatRefs((*this)[i]);
			delete (*this)[i];
		}
	}
	MeshMtlList();

public:
	int MAXMapIndex(int i);
	//void EightDotThreeName(CStr& name);
	void IncrName(char *name, char *inm, int n);
	void setDefault();

	int FindSName(char *nam);

public:
	int get_mtlchunk(FILE *stream,void *data);
	int dump_mtlchunk(ushort tag,FILE *stream,void *data);

protected:
	// import
	int TexBlurToPct(float tb);
	float PctToTexBlur(int p);
	void ResetMapData(MapData *md, int n, int ismask);
	void InitMappingValues(Mapping *m, int n, int isRmtl);
	void FreeMapDataRefs(MapData *md);
	void ResetMapping(Mapping *m, int n, int isRmtl);
	Mapping *NewMapping(int n,int isRmtl);
	void set_mtl_decal(SMtl *mtl);
	int load_app_data(FILE *stream,void **pdata, int size);
	int get_sxp_data(FILE *stream, int n, int size, int isMask);
	int get_mapdata_chunk(FILE *stream, int tag, MapData *md);
	int get_map(FILE *stream, int n, int size);
	int get_mask(FILE *stream, int n, int size);
	
	// export
	BOOL isSXPname(char *name);
	int dmp_map_params(FILE *stream,MapParams *mp);
	int dmp_map(FILE *stream, int i);
	int dmp_mask(FILE *stream, int i);
	int isSXPMap(MapData *md);

public://import

protected:
	BOOL		IsSXPName(char *name);

public:

	Color_24 C24,LC24;
	Color_f Cf,LCf;

	int dbgldmli/*=0*/;

	SMtl *loadmtl/*,inmtl*/;

	Color_24 blackcol /*= {0,0,0}*/;
	Color_24 whitecol /*= {255,255,255}*/;

	int just_name/*=0*/,strlimit;

	short ipct;
	float fpct;

	// export
	Mmtllist *mmtl;
	SMtl *savemtl,*savemlist;
	int savecount;
	int libtype;


protected:
	std::ostringstream os;

};

#endif	//_VGMESHMTLLIST_H_INCLUDED_
