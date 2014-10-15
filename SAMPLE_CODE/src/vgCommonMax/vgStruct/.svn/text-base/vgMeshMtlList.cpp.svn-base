
#include "vgStableHeaders.h"
#include <vgStruct/vgMeshMtlList.h>

#include <vgKernel/vgkStringUtility.h>

#if	IMPORT_MAX_LIB

int MeshMtlList::FindMtl(Mtl *m) {
	for (int i=0; i<size(); i++) 
		if  ( (*this)[i].m == m ) return i;
	return -1;
}


int MeshMtlList::IsStdMulti(Mtl *m) 
{
	return (m->ClassID()==Class_ID(MULTI_CLASS_ID,0))?1:0; 
}

void MeshMtlList::AddMtl(Mtl *m) 
{
	if (m==NULL) return;
	Interval v;
	m->Update(0,v);

	{

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

	}

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
	push_back(me);
}								

void MeshMtlList::ConvertMaxMtlToSMtl(SMtl *s, Mtl *m) {
#if	IMPORT_MAX_LIB

	Mapping *mp;
	Interval v;
	m->Update(0,v);
	s->amb = C24Format(m->GetAmbient());
	s->diff = C24Format(m->GetDiffuse());
	s->spec = C24Format(m->GetSpecular());
	s->shading = 3;
	s->shininess = Pcnt(m->GetShininess());
	s->shin2pct = Pcnt(m->GetShinStr());
	s->shin3pct = 0;
	s->transparency = Pcnt(m->GetXParency());
	s->wiresize = m->WireSize();

	// Step 1: 获取材质全局唯一的名称
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

	// Step 2: 获取材质的颜色值
	s->diffColor.b	= ( int )( 0.5f + 255.0f * m->GetDiffuse().b ) ;
	s->diffColor.g	= ( int )( 0.5f + 255.0f * m->GetDiffuse().g );
	s->diffColor.r	= ( int )( 0.5f + 255.0f * m->GetDiffuse().r );


	if (m->ClassID()==Class_ID(DMTL_CLASS_ID,0)) {
		StdMat* std = (StdMat *)m;
		switch(std->GetShading()) {
			case SHADE_CONST: s->shading = 1; break;
			case SHADE_PHONG: s->shading = 3; break;
			case SHADE_METAL: s->shading = 4; break;
		}	
		s->xpfall = Pcnt(std->GetOpacFalloff(0));		
		s->selfipct = Pcnt(std->GetSelfIllum(0));		
		if (std->GetTwoSided()) s->flags |= MF_TWOSIDE;
		if (std->GetWire()) s->flags |= MF_WIRE;
		if (!std->GetFalloffOut()) s->flags |= MF_XPFALLIN;
		if (std->GetFaceMap()) s->flags |= MF_FACEMAP;
		if (std->GetSoften()) s->flags |= MF_PHONGSOFT;
		if (std->GetWireUnits()) s->flags |= MF_WIREABS;
		switch (std->GetTransparencyType()) {
			case TRANSP_FILTER:
			case TRANSP_SUBTRACTIVE: break;
			case TRANSP_ADDITIVE: s->flags |= MF_ADDITIVE;
		}

		for (int i=0; i<8; i++) {
			if (i==Ntex2) continue;
			int n = MAXMapIndex(i);
			Texmap *tx;
			if ((tx=std->GetSubTexmap(n))==NULL) 
				continue;
			if (i==Nrefl) {
#ifndef NO_MAPTYPE_REFLECTREFRACT // orb 01-07-2001
				if (tx->ClassID()==Class_ID(ACUBIC_CLASS_ID,0)) {
					StdCubic *stdcub = (StdCubic*)tx;
					s->map[i] = mp = NewMapping(i,0);
					mp->amt.pct = Pcnt(std->GetTexmapAmt(n,0));			
					mp->use = std->MapEnabled(n);
					AutoCubicParams &ac = mp->map.p.ref.acb;
					ac.flags=AC_ON;
					if (!stdcub->GetDoNth()) ac.flags |= AC_FIRSTONLY;
					ac.nth = stdcub->GetNth();
					ac.size = stdcub->GetSize(0);
					continue;
				}
				else 
#endif // NO_MAPTYPE_REFLECTREFRACT
#ifndef NO_MAPTYPE_FLATMIRROR // orb 01-07-2001
					if (tx->ClassID()==Class_ID(MIRROR_CLASS_ID,0)) {
						StdMirror *stdmir = (StdMirror*)tx;
						s->map[i] = mp = NewMapping(i,0);
						mp->amt.pct = Pcnt(std->GetTexmapAmt(n,0));			
						mp->use = std->MapEnabled(n);
						AutoCubicParams &ac = mp->map.p.ref.acb;
						if (!stdmir->GetDoNth()) ac.flags |= AC_FIRSTONLY;
						ac.nth = stdmir->GetNth();
						ac.flags= AC_MIRROR|AC_ON;
						continue;
					}
#endif // NO_MAPTYPE_FLATMIRROR
			}
			// just do bitmap textures for now
			if (tx->ClassID()!=Class_ID(BMTEX_CLASS_ID,0))
				continue;					
			BitmapTex *bmt = (BitmapTex*)tx;
			s->map[i] = mp = NewMapping(i,0);
			mp->amt.pct = Pcnt(std->GetTexmapAmt(n,0));			
			if (i==Nbump) 
				mp->amt.pct = abs(mp->amt.pct)/100;
			mp->use = std->MapEnabled(n);
#if 1
			string filename(bmt->GetMapName());
			filename = vgKernel::StringUtility::getFilenameFromAbsolutePath(filename);
#else
			TSTR filename;
			SplitPathFile(TSTR(),NULL,&filename);
#endif
			
			string name(filename);

			// gdf convert bitmap filename to 8.3
//			EightDotThreeName(name);

			// gdf convert to Uppercase
			//name.toUpper();
			transform( name.begin() , name.end() , name.begin() , toupper);

			strncpy_s(mp->map.name, 13, name.data(),12);

			// 图片名字
			if ( ID_DI == n )
			{// Diffuse of Maps
				_tcsncpy_s( s->diffuseBitmap, 255, filename.c_str(),filename.size());
				s->bHasTexture	= true;
			}
			else
			{// Opacity of Maps
				_tcsncpy_s( s->opacityBitmap, 255, filename.c_str(),filename.size());
				s->bHasAlpha	= true;
			}

			// uv重复度
			StdUVGen *uv = bmt->GetUVGen();
			s->uTile	= uv->GetUScl(0);
			s->vTile	= uv->GetVScl(0);


			if (i==Nrefl) {

			}
			else {
				StdUVGen *uv = bmt->GetUVGen();
				MapParams &par = mp->map.p.tex;
				par.type = MAP_TYPE_UV;
				par.uoffset = uv->GetUOffs(0); 
				par.voffset = -uv->GetVOffs(0); 
				par.uscale = uv->GetUScl(0); 
				par.vscale = uv->GetVScl(0); 
				float ang = uv->GetAng(0);
				par.ang_sin = -(float)sin(ang);
				par.ang_cos = (float)cos(ang);
				par.texblur	 = uv->GetBlur(0)-1.0f;
				int tile = uv->GetTextureTiling();
				if (tile&(U_MIRROR|V_MIRROR))
					par.texflags|= TEX_MIRROR;
				if (tile&(U_WRAP|V_WRAP))
					par.texflags &= ~TEX_NOWRAP;
				else
					par.texflags |= TEX_NOWRAP;
				TextureOutput* texout = bmt->GetTexout();
				if (texout->GetInvert()) 
					par.texflags |= TEX_INVERT;
				if (bmt->GetFilterType()==FILTER_SAT)
					par.texflags |= TEX_SAT;
			}
		}
	}
#endif
}

#endif

SMtl* MeshMtlList::FindMtl( string mtlName )
{
	for (int i=0; i<size(); i++) 
	{
		SMtl* smtl = (*this)[i] ;
		if  ( string(smtl->name) == mtlName ) 
			return smtl;
	}
	return NULL;
}
int  MeshMtlList::FindSName(char *name) 
{
	for (int i=0; i<size(); i++) 
		if  ( strcmp(name,(*this)[i]->name)==0) return i;
	return -1;
}
int MeshMtlList::MAXMapIndex(int i) {
	
#if	IMPORT_MAX_LIB
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
#endif
   return 0;
}

int Pcnt(float f) { return (int)(f*100.0f+.5f); }


void MeshMtlList::IncrName(char *name, char *inm, int n) {
	char buf[LENGTH_MTL_NAME];
	strncpy_s(buf, LENGTH_MTL_NAME, name,13);
	buf[13] = 0;
	sprintf_s(inm, LENGTH_MTL_NAME, "%s%d\0",buf,n);
}

// import
void MeshMtlList::ResetMapData(MapData *md, int n, int ismask) {
	memset(md,0,sizeof(MapData));
	if ((!ismask)&&(n==Nrefl)) {
		md->kind = 1;
		md->p.ref.acb.shade = REND_METAL;
		md->p.ref.acb.aalevel = 0;
		md->p.ref.acb.flags = 0;
		md->p.ref.acb.size = 100;
		md->p.ref.acb.nth = 1;
	}
	else {
		md->p.tex.texblur = PctToTexBlur(10 /*P.texture_blur_default*/);
		md->p.tex.uscale = 1.0f;
		md->p.tex.vscale = 1.0f;
		md->p.tex.uoffset = 0.0f;
		md->p.tex.voffset = 0.0f;
		md->p.tex.ang_sin = 0.0f;
		md->p.tex.ang_cos = 1.0f;
		md->p.tex.col1 = blackcol;
		md->p.tex.col2 = whitecol;
		md->p.tex.rcol = 	md->p.tex.gcol = 	md->p.tex.bcol = blackcol;
		md->p.tex.rcol.r = 255;
		md->p.tex.gcol.g = 255;
		md->p.tex.bcol.b = 255;
	}
}

void MeshMtlList::InitMappingValues(Mapping *m, int n, int isRmtl) {
	if (isRmtl) m->amt.f = 1.0f;
	else m->amt.pct = 100;
	ResetMapData(&m->map,n,0);
	ResetMapData(&m->mask,n,1);
}


void MeshMtlList::FreeMapDataRefs(MapData *md) {
	//	Cubmap *cm,*nextcm;
	switch(md->kind) {
		case 0:
			MemeryHandler::XMFreeAndZero(&md->p.tex.sxp_data);
			break;
		case 1:
#if 0
			if (md->p.ref.acb.flags&AC_ON) {
				for (cm =(Cubmap *)md->p.ref.bm; cm!=NULL; cm=nextcm) {
					nextcm = cm->next;
					XMFree(cm);
				}
			}
			else{
				char ext[5];
				split_fext(md->name,NULL,ext);
				if(stricmp(ext,".CUB")==0) {
					if (md->p.ref .bm!=NULL)
						XMFree(md->p.ref.bm);
				}
			}
#endif
			break;
	}	
}

void MeshMtlList::FreeMatRefs(SMtl *m) {
	int k;
	if (m->appdata) MemeryHandler::XMFreeAndZero(&m->appdata);
	for (k=0; k<NMAPTYPES; k++) {
		if (m->map[k]) {
			FreeMapDataRefs(&m->map[k]->map);
			FreeMapDataRefs(&m->map[k]->mask);
			MemeryHandler::XMFreeAndZero((void **)&m->map[k]);
		}
	}
}


void MeshMtlList::ResetMapping(Mapping *m, int n, int isRmtl) {
	FreeMapDataRefs(&m->map);
	FreeMapDataRefs(&m->mask);
	memset(m,0,sizeof(Mapping));
	InitMappingValues(m,n,isRmtl);
}

Mapping *MeshMtlList::NewMapping(int n,int isRmtl) {
	Mapping *m;
	m = (Mapping*)MemeryHandler::XMAllocZero(sizeof(Mapping));
	if (m==NULL) return(NULL);
	InitMappingValues(m,n,isRmtl);
	return(m);
}


void MeshMtlList::init_mtl_struct(SMtl *mtl) {
	memset(mtl,0,sizeof(SMtl));
	mtl->shininess=50;
	mtl->shin2pct = 255; /* undefined */
	mtl->transparency=0;
	mtl->shading=3;
	mtl->wiresize = 1.0f;
}

void MeshMtlList::set_mtl_decal(SMtl *mtl) {
	int i;
	Mapping *m;
	for (i=0; i<NMAPTYPES; i++) {
		if ((m=mtl->map[i])!=NULL) {
			if (m->map.kind==0)
				m->map.p.tex.texflags |= TEX_DECAL|TEX_NOWRAP;
			if (m->mask.kind==0)
				m->mask.p.tex.texflags |= TEX_DECAL|TEX_NOWRAP;
		}
	}
}


//===========================================================
int MeshMtlList::load_app_data(FILE *stream,void **pdata, int size) {
	ULONG *plong;
	if (*pdata!=NULL) 
		MemeryHandler::XMFreeAndZero(pdata);
	*pdata = (void *)MemeryHandler::XMAlloc(size+4);
	if (*pdata==NULL) {
		//MtlError();
		return(0);	
	}		
	plong = (ULONG *)(*pdata);
	plong[0] = size;
	RDERR((void *)&plong[1],size);
	return(1);
}



int
MeshMtlList::get_mapdata_chunk(FILE *stream, int tag, MapData *md) 
{
	switch (tag) 
	{
	case MAT_MAPNAME:
		strlimit=13;
		if (!get_mtlchunk(stream,md->name)) 
		{
			return(0);
		}
#ifdef DBGLDMLI
		if (dbgldmli)
			printf("  get_map : mapname: %s \n",md->name);
#endif
		return(1);
	case MAT_MAP_TILING: 
		return(get_mtlchunk(stream,&md->p.tex.texflags));
	case MAT_MAP_TILINGOLD: 
		if (!get_mtlchunk(stream,&md->p.tex.texflags)) 
		{
			return(0);
		}
		if (md->p.tex.texflags&TEX_DECAL)
			md->p.tex.texflags|=TEX_NOWRAP;				
		return(1);
	case MAT_MAP_TEXBLUR: 
		return(get_mtlchunk(stream,&md->p.tex.texblur));
	case MAT_MAP_TEXBLUR_OLD: 
		return(get_mtlchunk(stream,&md->p.tex.texblur));
	case MAT_MAP_USCALE: 
		return(get_mtlchunk(stream,&md->p.tex.uscale));
	case MAT_MAP_VSCALE: 
		return(get_mtlchunk(stream,&md->p.tex.vscale));
	case MAT_MAP_UOFFSET: 
		return(get_mtlchunk(stream,&md->p.tex.uoffset));
	case MAT_MAP_VOFFSET: 
		return(get_mtlchunk(stream,&md->p.tex.voffset));
	case MAT_MAP_ANG: 
		return(get_mtlchunk(stream,&md->p.tex));
	case MAT_MAP_COL1: 
		return(get_mtlchunk(stream,&md->p.tex.col1));
	case MAT_MAP_COL2: 
		return(get_mtlchunk(stream,&md->p.tex.col2));
	case MAT_MAP_RCOL: 
		return(get_mtlchunk(stream,&md->p.tex.rcol));
	case MAT_MAP_GCOL: 
		return(get_mtlchunk(stream,&md->p.tex.gcol));
	case MAT_MAP_BCOL: 
		return(get_mtlchunk(stream,&md->p.tex.bcol));
	default:
		return(FileChunkHandler::skip_chunk(stream));
	}
}

int MeshMtlList::get_map(FILE *stream, int n, int size) 
{
	uint nexttag;
	Chunk_hdr nxt;
	Mapping *m = loadmtl->map[n];
#ifdef DBGLDMLI
	if (dbgldmli)
		printf(" GET_MAP: n = %d\n",n);
#endif
	if (m==NULL) {
		m = NewMapping(n,0);
		if (m==NULL) {
			//MtlError();
			return(0);
		}
		loadmtl->map[n] = m;
	}
	m->use = 1;
	while(size) {
		if(FileChunkHandler::get_next_chunk(stream,&nxt)==0)
			return(0);
		nexttag = nxt.tag;
		switch(nexttag) {
			case INT_PERCENTAGE:
			case FLOAT_PERCENTAGE:
				if(get_mtlchunk(stream,NULL)==0)
					return(0);
				m->amt.pct = ipct; 
				if (n==Nbump) 
					m->amt.pct = (ipct<=20)?4*ipct:100;  /* for old files */

#ifdef DBGLDMLI
				if (dbgldmli)
					printf("  get_map %d : pct: %d \n",n,ipct);
#endif
				break;
			case MAT_BUMP_PERCENT:
				if(get_mtlchunk(stream,NULL)==0)
					return(0);
				m->amt.pct = ipct; /* for version 3+ files */
				break;
			default:
				if (!get_mapdata_chunk(stream,nexttag,&m->map)) {
#ifdef DBGLDMLI
					if (dbgldmli)
						printf(" Error in get_mapdata_chunk, nexttag = %X\n",nexttag);
#endif
					//MtlError();
					return(0);
				}
				break;
		}
		size-=nxt.size;
	}

#ifdef DBGLDMLI
	if (dbgldmli)
		printf(" EXIT GET_MAP: n = %d\n",n);
#endif
	return(1);
}

int MeshMtlList::get_mask(FILE *stream, int n, int size) {
	uint nexttag;
	Chunk_hdr nxt;
	Mapping *m = loadmtl->map[n];
	if (m==NULL) {
		m = NewMapping(n,0);
		if (m==NULL) {
			//MtlError();
			return(0);
		}
		loadmtl->map[n] = m;
	}
	m->use = 1;
	while(size) {
		if(FileChunkHandler::get_next_chunk(stream,&nxt)==0)
			return(0);
		nexttag = nxt.tag;
#ifdef DBGLDMLI
		if (dbgldmli)
			printf("  get_MASK loop: nexttag = %X \n",nexttag);
#endif
		if (!get_mapdata_chunk(stream,nexttag,&m->mask)) return(0);

		size-=nxt.size;
	}
	return(1);
}

int MeshMtlList::get_sxp_data(FILE *stream, int n, int size, int isMask) {
	ULONG **pp,*ptr;
	Mapping *m = loadmtl->map[n];
#ifdef DBGLDMLI
	if (dbgldmli)
		printf("GET_SXP_DATA: n=%d, size = %d, isMask = %d, m=%X\n",
		n,size,isMask,m);
#endif
	if (size==0) return(1);
	if (m==NULL) {
		m = NewMapping(n,0);
		if (m==NULL) {
			//MtlError();
			return(0);
		}
		loadmtl->map[n] = m;
	}
	if (isMask)
		pp = (ULONG **)&m->mask.p.tex.sxp_data;
	else 
		pp = (ULONG **)&m->map.p.tex.sxp_data;
	if (*pp!=NULL) MemeryHandler::XMFreeAndZero((void **)pp);
	ptr = (ULONG *)MemeryHandler::XMAlloc(size+4);
	if (ptr==NULL)  {
		//MtlError();
		return(0);   
	}
	ptr[0] = size;

#ifdef DBGLDMLI
	if (dbgldmli)
		printf("  sxp_data: addr = %X,  size = %X\n", ptr, ptr[0]);
#endif
	RDERR(&ptr[1],size);
	*pp = ptr;
	return(1);
}       

int MeshMtlList::TexBlurToPct(float tb) {
	return((int)(tb*100.0+.5));	
}

float MeshMtlList::PctToTexBlur(int p) {
	return((float)p/100.0f);	
}




#define GET_SXP(num,type) if (!get_sxp_data(stream,num,chunk.size,type)) return(0); chunk.size=0;      
#define GET_MAP(num) if (!get_map(stream,num,chunk.size)) return(0); chunk.size=0;      
#define GET_MASK(num) if (!get_mask(stream,num,chunk.size)) return(0); chunk.size=0;      

int
MeshMtlList::get_mtlchunk(FILE *stream,void *data)
{
	/* Grab a chunk from the file and process all its subsets */
	Chunk_hdr chunk;
	Chunk_hdr nxt;
	uint thistag,nexttag;
	char *string;
	short *pshort;

	RDERR(&chunk,6);

	thistag=chunk.tag;

#ifdef DBGLDMLI
	if (dbgldmli)
		printf("          get_mtlchunk: tag=%X, size=%d \n",thistag,chunk.size);
#endif

	/* Update chunk size to account for header */

	chunk.size-=6L;

	/* Find chunk type and go process it */
	os << "Mtl Chunk ID = " 
		<< std::hex << std::setw(10) << std::setiosflags(std::ios::left)
		<< chunk.tag;
	switch(thistag)
	{
	case MLIBMAGIC:
		while(chunk.size)
		{
			if(FileChunkHandler::get_next_chunk(stream,&nxt)==0)
				return(0);
			nexttag=nxt.tag;
			switch(nexttag)
			{
			case MAT_ENTRY:
				loadmtl= new SMtl;//&inmtl;
				/* Zero out data structure first */
				init_mtl_struct(loadmtl);

				if(get_mtlchunk(stream,NULL)==0)
					return(0);
				/*if(put_lib_mtl(loadmtl)==0)
				return(0);*/
				break;     
			default:
				if(FileChunkHandler::skip_chunk(stream)==0){
					//MtlError();
					return(0);
				}
				break;
			}
			chunk.size-=nxt.size;
		}
		break;
	case MAT_ENTRY:
	case MATMAGIC:
		while(chunk.size)
		{
			if(FileChunkHandler::get_next_chunk(stream,&nxt)==0)
				return(0);
			nexttag=nxt.tag;
			switch(nexttag)
			{
			case MAT_NAME:
				strlimit=17;
				if(get_mtlchunk(stream,loadmtl->name)==0)
					return(0);
#ifdef DBGLDMLI
				if (dbgldmli)
					printf(" **** Loading material : %s \n", loadmtl->name);
#endif
				if(just_name) /* If all we need is the name, return */
					return(1);
				break;     
			case MAT_AMBIENT:
				if(get_mtlchunk(stream,&loadmtl->amb)==0)
					return(0);
				break;     
			case MAT_DIFFUSE:
				if(get_mtlchunk(stream,&loadmtl->diff)==0)
					return(0);
				break;     
			case MAT_SPECULAR:
				if(get_mtlchunk(stream,&loadmtl->spec)==0)
					return(0);
				break;     
			case MAT_ACUBIC:
				{
					Mapping *m = loadmtl->map[Nrefl];
					if (m==NULL) goto	skip_mtl_chunk;
					if (get_mtlchunk(stream,&m->map.p.ref.acb)==0)
						return(0);
				}
				break;     

			case MAT_SXP_TEXT_DATA:       
			case MAT_SXP_TEXT2_DATA: 
			case MAT_SXP_OPAC_DATA:  
			case MAT_SXP_BUMP_DATA:  
			case MAT_SXP_SPEC_DATA:  
			case MAT_SXP_SELFI_DATA: 
			case MAT_SXP_SHIN_DATA:  

			case MAT_SXP_TEXT_MASKDATA:  
			case MAT_SXP_TEXT2_MASKDATA: 
			case MAT_SXP_OPAC_MASKDATA:  
			case MAT_SXP_BUMP_MASKDATA:  
			case MAT_SXP_SPEC_MASKDATA:  
			case MAT_SXP_SELFI_MASKDATA: 
			case MAT_SXP_SHIN_MASKDATA:  
			case MAT_SXP_REFL_MASKDATA:  
				if(get_mtlchunk(stream,NULL)==0)
					return(0);
				break;

			case MAT_TEXMAP:   
			case MAT_TEX2MAP:  
			case MAT_OPACMAP:  
			case MAT_BUMPMAP:  
			case MAT_SPECMAP:  
			case MAT_SHINMAP:  
			case MAT_SELFIMAP: 
			case MAT_REFLMAP:  

			case MAT_TEXMASK:   
			case MAT_TEX2MASK:  
			case MAT_OPACMASK:  
			case MAT_BUMPMASK:  
			case MAT_SPECMASK:  
			case MAT_SHINMASK:  
			case MAT_SELFIMASK: 
			case MAT_REFLMASK:  
				if(get_mtlchunk(stream,NULL)==0)
					return(0);
				break;

			case MAT_SHININESS:
			case MAT_SHIN2PCT:
			case MAT_TRANSPARENCY:
			case MAT_XPFALL:
			case MAT_REFBLUR:
			case MAT_SELF_ILPCT:
			case MAT_SHADING:
			case MAT_TWO_SIDE:
			case MAT_SUPERSMP:
			case MAT_SELF_ILLUM:
			case MAT_DECAL:
			case MAT_ADDITIVE:
			case MAT_WIRE:
			case MAT_FACEMAP:
			case MAT_XPFALLIN:
			case MAT_PHONGSOFT:
			case MAT_WIREABS:
			case MAT_USE_XPFALL:
			case MAT_USE_REFBLUR:
			case MAT_WIRESIZE:
				if(get_mtlchunk(stream,NULL)==0)
					return(0);
				break;
			case APP_DATA:
				if(get_mtlchunk(stream,&loadmtl->appdata)==0)
					return(0);
				break;
			default:
skip_mtl_chunk:
				if(FileChunkHandler::skip_chunk(stream)==0) 
				{
					//MtlError();
					return(0);
				}
				break;
			}
			chunk.size-=nxt.size;
		}// MAT_ENTRY/MATMAGIC

#ifdef DBGLDMLI
		if (dbgldmli)
			printf("  finished loading mtl %s, flags = %X\n",
			loadmtl->name, loadmtl->flags);
#endif
		/* convert old data formats to new */
		if (loadmtl->shading==REND_WIRE) 
		{
			loadmtl->shading = REND_FLAT;
			loadmtl->flags |= MF_WIRE;
			loadmtl->flags |= MF_TWOSIDE;
			loadmtl->shininess=0;
			loadmtl->shin2pct=0;
			loadmtl->transparency=0;
		}

		if (loadmtl->xpfall<0.0) 
		{
			loadmtl->flags|= MF_XPFALLIN;
			loadmtl->xpfall = -loadmtl->xpfall;
		}
		if (loadmtl->flags&MF_DECAL) 
		{
			set_mtl_decal(loadmtl);
			loadmtl->flags &= ~MF_DECAL;
		}
		if (loadmtl->shin2pct==255) 
		{
			float shin = (((float)(loadmtl->shininess))/100.0f);
			float atten = (float)sin(1.5707*shin);
			loadmtl->shin2pct = (int)((atten)*100.0f+0.5f);
		}

		break;

	case MAT_SXP_TEXT_DATA:  GET_SXP(Ntex,0); break;     
	case MAT_SXP_TEXT2_DATA: GET_SXP(Ntex2,0);  break;     
	case MAT_SXP_OPAC_DATA:  GET_SXP(Nopac,0);  break;
	case MAT_SXP_BUMP_DATA:  GET_SXP(Nbump,0);  break; 
	case MAT_SXP_SPEC_DATA:  GET_SXP(Nspec,0);  break;
	case MAT_SXP_SELFI_DATA: GET_SXP(Nselfi,0);  break;
	case MAT_SXP_SHIN_DATA:  GET_SXP(Nshin,0);  break;

	case MAT_SXP_TEXT_MASKDATA:  GET_SXP(Ntex,1);  break;     
	case MAT_SXP_TEXT2_MASKDATA: GET_SXP(Ntex2,1);  break;     
	case MAT_SXP_OPAC_MASKDATA:  GET_SXP(Nopac,1);  break;
	case MAT_SXP_BUMP_MASKDATA:  GET_SXP(Nbump,1);  break; 
	case MAT_SXP_SPEC_MASKDATA:  GET_SXP(Nspec,1);  break;
	case MAT_SXP_SELFI_MASKDATA: GET_SXP(Nselfi,1);  break;
	case MAT_SXP_SHIN_MASKDATA:  GET_SXP(Nshin,1);  break;
	case MAT_SXP_REFL_MASKDATA:  GET_SXP(Nrefl,1);  break;

	case MAT_TEXMAP:   GET_MAP(Ntex);  break;     
	case MAT_TEX2MAP:  GET_MAP(Ntex2);  break;     
	case MAT_OPACMAP:  GET_MAP(Nopac);  break;     
	case MAT_BUMPMAP:  GET_MAP(Nbump);  break;     
	case MAT_SPECMAP:  GET_MAP(Nspec);  break;     
	case MAT_SHINMAP:  GET_MAP(Nshin);  break;     
	case MAT_SELFIMAP: GET_MAP(Nselfi);  break;     
	case MAT_REFLMAP:  GET_MAP(Nrefl);  break;     

	case MAT_TEXMASK:   GET_MASK(Ntex);  break;     
	case MAT_TEX2MASK:  GET_MASK(Ntex2);  break;     
	case MAT_OPACMASK:  GET_MASK(Nopac);  break;     
	case MAT_BUMPMASK:  GET_MASK(Nbump);  break;     
	case MAT_SPECMASK:  GET_MASK(Nspec);  break;     
	case MAT_SHINMASK:  GET_MASK(Nshin);  break;     
	case MAT_SELFIMASK: GET_MASK(Nselfi);  break;     
	case MAT_REFLMASK:  GET_MASK(Nrefl);  break;     

	case MAT_AMBIENT:
	case MAT_DIFFUSE:
	case MAT_SPECULAR:
		{
			int got_lin,got_gam;
			got_lin = got_gam = 0;
			while(chunk.size)
			{
				if(FileChunkHandler::get_next_chunk(stream,&nxt)==0)
					return(0);
				nexttag=nxt.tag;
				switch(nexttag)	
				{
				case COLOR_F:
				case COLOR_24:
					got_gam = 1;
					if(get_mtlchunk(stream,NULL)==0) return(0);
					break;     
				case LIN_COLOR_24:
					got_lin = 1;
					if(get_mtlchunk(stream,NULL)==0)	return(0);
					break;     
				default:
					if(FileChunkHandler::skip_chunk(stream)==0) 
					{
						//MtlError();
						return(0);
					}
					break;
				}
				chunk.size-=nxt.size;
			}

			if (got_lin) 
			{
				memcpy((char *)data,(char *)&LC24,sizeof(Color_24));
			}
			else 
			{ 
				if (!got_gam) 
				{
					//MtlError();
					return(0);
				}

#if	IMPORT_MAX_LIB

				if (gammaMgr.enable) 
				{
					Color_24 gc;
					gc.r = gammaMgr.file_in_degamtab[C24.r]>>8;
					gc.g = gammaMgr.file_in_degamtab[C24.g]>>8;
					gc.b = gammaMgr.file_in_degamtab[C24.b]>>8;
					memcpy((char *)data,(char *)&gc,sizeof(Color_24));
				}
				else 
				{ 
					memcpy((char *)data,(char *)&C24,sizeof(Color_24));
				}
#endif
			}
		}
		break;
	case MAT_SELF_ILLUM:	
		loadmtl->flags |= MF_SELF;	  
		loadmtl->selfipct = 100;				
		break;
	case MAT_TWO_SIDE:	loadmtl->flags |= MF_TWOSIDE;	break;
	case MAT_SUPERSMP:	loadmtl->flags |= MF_SUPERSMP;	break;
	case MAT_ADDITIVE:	loadmtl->flags |= MF_ADDITIVE;break;
	case MAT_DECAL:   loadmtl->flags |= MF_DECAL;  	break;
	case MAT_WIRE:	loadmtl->flags |= MF_WIRE; break;
	case MAT_FACEMAP:	loadmtl->flags |= MF_FACEMAP; break;
	case MAT_XPFALLIN:	loadmtl->flags |= MF_XPFALLIN; break;
	case MAT_PHONGSOFT:	loadmtl->flags |= MF_PHONGSOFT; break;
	case MAT_WIREABS:	loadmtl->flags |= MF_WIREABS; break;
	case MAT_USE_XPFALL:	loadmtl->use |= MATUSE_XPFALL; break;
	case MAT_USE_REFBLUR:	loadmtl->use |= MATUSE_REFBLUR;	break;

	case MAT_SHININESS:
		pshort = &loadmtl->shininess;
		goto get_int_float_chunk;

	case MAT_SHIN2PCT:
		pshort = &loadmtl->shin2pct;
		goto get_int_float_chunk;

	case MAT_TRANSPARENCY:
		pshort = &loadmtl->transparency;
		goto get_int_float_chunk;

	case MAT_XPFALL:
		pshort = &loadmtl->xpfall;
		goto get_int_float_chunk;

	case MAT_REFBLUR:
		pshort = &loadmtl->refblur;
		goto get_int_float_chunk;

	case MAT_SELF_ILPCT:
		pshort = &loadmtl->selfipct;
		goto get_int_float_chunk;

get_int_float_chunk:
		while(chunk.size)
		{
			if(FileChunkHandler::get_next_chunk(stream,&nxt)==0)
				return(0);
			nexttag=nxt.tag;
			switch(nexttag)
			{
			case INT_PERCENTAGE:
			case FLOAT_PERCENTAGE:
				if(get_mtlchunk(stream,NULL)==0)
					return(0);
#ifdef DBGLDMLI
				if (dbgldmli)
					printf(" get_int_float_chunk: val = %d \n",ipct);
#endif 

				*pshort=ipct;
				break;
			default:
				if(FileChunkHandler::skip_chunk(stream)==0) {
					//MtlError();
					return(0);
				}
				break;
			}
			chunk.size-=nxt.size;
		}
		break;
	case MAT_SHADING:
		RDERR(&loadmtl->shading,2);
		chunk.size-=2L;
		goto skiprest;
	case MAT_MAP_TILING: 
	case MAT_MAP_TILINGOLD: 
		RDERR(data,2);
		chunk.size-=2L;
		goto skiprest;
	case MAT_MAP_TEXBLUR_OLD: {
		float foo;
		RDERR(&foo,sizeof(float));
		foo = (foo-1.0f)/7.0f;
		if (foo<0.0f) foo = 0.0f;
		if (foo>1.0f) foo = 1.0f;
		memmove(data,&foo,4);
		chunk.size -=4L;
							  }
							  goto skiprest;
	case MAT_MAP_TEXBLUR: 
	case MAT_MAP_USCALE: 
	case MAT_MAP_VSCALE: 
	case MAT_MAP_UOFFSET: 
	case MAT_MAP_VOFFSET: 
		RDERR(data,sizeof(float));
		chunk.size -=4L;
		goto skiprest;
	case MAT_MAP_ANG: {
		MapParams *mp = (MapParams *)data;
		float ang;
		RDERR(&ang,4);
		ang = DegToRad(ang);
		mp->ang_sin = (float)sin(ang);
		mp->ang_cos = (float)cos(ang);
		chunk.size -=4L;
		goto skiprest;
					  }

	case MAT_MAP_COL1: 
	case MAT_MAP_COL2: 
	case MAT_MAP_RCOL: 
	case MAT_MAP_GCOL: 
	case MAT_MAP_BCOL: 
		{
			Color_24 *pcol = (Color_24 *)data;
			RDERR(pcol,3);
		}
		chunk.size-=3L;
		goto skiprest;
	case COLOR_F:
		RDERR(&Cf,12);
		chunk.size-=12L;
		C24.r=(uchar)(Cf.r*255.0f);
		C24.g=(uchar)(Cf.g*255.0f);
		C24.b=(uchar)(Cf.b*255.0f);
		goto skiprest;
	case COLOR_24:
		RDERR(&C24,3);
		Cf.r=(float)C24.r/255.0f;
		Cf.g=(float)C24.g/255.0f;
		Cf.b=(float)C24.b/255.0f;
		chunk.size-=3L;
		goto skiprest;
	case LIN_COLOR_24:
		RDERR(&LC24,3);
		LCf.r=(float)LC24.r/255.0f;
		LCf.g=(float)LC24.g/255.0f;
		LCf.b=(float)LC24.b/255.0f;
		chunk.size-=3L;
		goto skiprest;
	case MAT_NAME:  /* Simple strings */
	case MAT_MAPNAME:
		string=(char *)data;
		if(FileChunkHandler::read_string(string,stream,strlimit)==0) {
			//MtlError();
			return(0);
		}
		chunk.size-=(long)(strlen(string)+1);
		goto skiprest;


	case MAT_ACUBIC: 
		{
			AutoCubicParams *ac = (AutoCubicParams *)data;
			RDERR(&ac->shade,1);
			RDERR(&ac->aalevel,1);
			RDERR(&ac->flags,2);
			RDERR(&ac->size,4);
			RDERR(&ac->nth,4);
			chunk.size-=12;
		}
		goto skiprest;
	case INT_PERCENTAGE:
		RDERR(&ipct,2);
		fpct=(float)ipct/100.0f;
		chunk.size-=2L;
		goto skiprest;
	case MAT_WIRESIZE:
		RDERR(&loadmtl->wiresize,4);
		chunk.size-=4L;
		goto skiprest;
	case MAT_BUMP_PERCENT:
		RDERR(&ipct,2);
		fpct=(float)ipct/100.0f;
		chunk.size-=2L;
		goto skiprest;
	case FLOAT_PERCENTAGE:
		RDERR(&fpct,4);
		ipct=(short)(fpct*100.0f);
		chunk.size-=4;
		goto skiprest;
	case APP_DATA:
		//			if (!load_app_data(stream, (void **)data, chunk.size))
		//				return(0);
		//			chunk.size = 0;
		goto skiprest;

		/* The following routine is used to dump any sub-chunks */
		/* in the current chunk.    */
skiprest:
		while(chunk.size)
		{
			if(FileChunkHandler::get_next_chunk(stream,&nxt)==0)
				return(0);
			if(FileChunkHandler::skip_chunk(stream)==0) {
				//MtlError();
				return(0);
			}
			chunk.size-=nxt.size;
		}  
		break;
	}
	//done:
	return(1);
}

void MeshMtlList::setDefault()
{

	blackcol.r = blackcol.g = blackcol.b = 0;
	whitecol.r = whitecol.g = whitecol.b = 255;

	just_name = false;

	dbgldmli = 0;
}

MeshMtlList::MeshMtlList()
{
	setDefault();
}

// export
#define DMP_MATCHUNK(id,data)  { if(dump_mtlchunk((ushort)id,stream,data)==0) return(0);}

#define DMP_IFNOT_NULL(id,ptr)  if (ptr) DMP_MATCHUNK(id,&ptr)


static ULONG map_chunks[8] = {
	MAT_TEXMAP,MAT_TEX2MAP,MAT_OPACMAP,MAT_BUMPMAP,
	MAT_SPECMAP,MAT_SHINMAP,MAT_SELFIMAP,MAT_REFLMAP
};
static ULONG mask_chunks[8] = {
	MAT_TEXMASK,MAT_TEX2MASK,MAT_OPACMASK,MAT_BUMPMASK,
	MAT_SPECMASK,MAT_SHINMASK,MAT_SELFIMASK,MAT_REFLMASK
};
static ULONG map_sxp_chunks[8] = {
	MAT_SXP_TEXT_DATA,MAT_SXP_TEXT2_DATA,MAT_SXP_OPAC_DATA,MAT_SXP_BUMP_DATA,
	MAT_SXP_SPEC_DATA,MAT_SXP_SHIN_DATA,MAT_SXP_SELFI_DATA,0	
};
static ULONG mask_sxp_chunks[8] = {
	MAT_SXP_TEXT_MASKDATA,MAT_SXP_TEXT2_MASKDATA,MAT_SXP_OPAC_MASKDATA,MAT_SXP_BUMP_MASKDATA,
	MAT_SXP_SPEC_MASKDATA,MAT_SXP_SHIN_MASKDATA,MAT_SXP_SELFI_MASKDATA,MAT_SXP_REFL_MASKDATA	
};

int
MeshMtlList::dump_mtlchunk(ushort tag,FILE *stream,void *data)
{
	long chunkptr,chunkbase,curpos,chunksize;
	Color_f *cf;
	Color_24 *c24;
	char *string;
	Mmtllist *ml;
	//	Mliblist *mlb;

	chunkbase=ftell(stream);
	WRTERR(&tag,2);
	chunkptr=ftell(stream);  /* Save file ptr for chunk size */
	WRTERR(&chunkptr,4);
	switch(tag)
	{
	case MLIBMAGIC:
		switch(libtype)
		{
		case 0:
			//					if(mlib)
			//						{
			//						mlb=mlib;
			//						while(mlb)
			//							{
			//							savemtl= &mlb->material;
			//							if(dump_mtlchunk(MAT_ENTRY,stream,NULL)==0)
			//								return(0);
			//							mlb=mlb->next;
			//							}
			//						}
			break;
		case 1:
			if(mmtl)
			{
				//						tag_used_mmtls(); // for our purposes, they're ALL used
				ml=mmtl;
				while(ml)
				{
					//							if(ml->flags & MMTLUSED)
					{
						savemtl= &ml->material;
						if(dump_mtlchunk(MAT_ENTRY,stream,NULL)==0)
							return(0);
					}
					ml=ml->next;
				}
			}
			break;
		}
		break;
	case MAT_ENTRY:
	case MATMAGIC:
		{
			if(dump_mtlchunk(MAT_NAME,stream,savemtl->name)==0) return(0);
			if(dump_mtlchunk(MAT_AMBIENT,stream,&savemtl->amb)==0) return(0);
			if(dump_mtlchunk(MAT_DIFFUSE,stream,&savemtl->diff)==0) return(0);
			if(dump_mtlchunk(MAT_SPECULAR,stream,&savemtl->spec)==0)return(0);
			if(dump_mtlchunk(MAT_SHININESS,stream,NULL)==0)	return(0);
			if(dump_mtlchunk(MAT_SHIN2PCT,stream,NULL)==0) return(0);
			if(dump_mtlchunk(MAT_TRANSPARENCY,stream,NULL)==0)	return(0);
			if(dump_mtlchunk(MAT_XPFALL,stream,NULL)==0)	return(0);
			if(dump_mtlchunk(MAT_REFBLUR,stream,NULL)==0) return(0);
			if(dump_mtlchunk(MAT_SHADING,stream,NULL)==0) return(0);
			if(dump_mtlchunk(MAT_SELF_ILPCT,stream,NULL)==0) return(0);

			if(savemtl->use&MATUSE_XPFALL)  {
				if(dump_mtlchunk(MAT_USE_XPFALL,stream,NULL)==0)
					return(0);
			}
			if(savemtl->use&MATUSE_REFBLUR)  {
				if(dump_mtlchunk(MAT_USE_REFBLUR,stream,NULL)==0)
					return(0);
			}
			if(savemtl->flags & MF_TWOSIDE)  {
				if(dump_mtlchunk(MAT_TWO_SIDE,stream,NULL)==0)
					return(0);
			}
			if(savemtl->flags & MF_ADDITIVE) {
				if(dump_mtlchunk(MAT_ADDITIVE,stream,NULL)==0)
					return(0);
			}
			if(savemtl->flags & MF_WIRE) {
				if(dump_mtlchunk(MAT_WIRE,stream,NULL)==0)
					return(0);
			}
			if(savemtl->flags & MF_FACEMAP) {
				if(dump_mtlchunk(MAT_FACEMAP,stream,NULL)==0)
					return(0);
			}

			if(savemtl->flags & MF_XPFALLIN) {
				if(dump_mtlchunk(MAT_XPFALLIN,stream,NULL)==0)
					return(0);
			}

			if(savemtl->flags & MF_PHONGSOFT) {
				if(dump_mtlchunk(MAT_PHONGSOFT,stream,NULL)==0)
					return(0);
			}

			if(savemtl->flags & MF_WIREABS) {
				if(dump_mtlchunk(MAT_WIREABS,stream,NULL)==0)
					return(0);
			}

			if(dump_mtlchunk(MAT_WIRESIZE,stream,&savemtl->wiresize)==0)
				return(0);

			/* Save out any texture maps, masks, sxp's */
			for (int k=0; k<NMAPTYPES; k++) {
				Mapping *mp = savemtl->map[k];
				if (mp==NULL) continue;
				if (mp->use) {
					DMP_MATCHUNK(map_chunks[k],NULL);
					if (k!=Nrefl) {
						if (isSXPMap(&mp->map)) 
							DMP_MATCHUNK(map_sxp_chunks[k],mp->map.p.tex.sxp_data);
					}
					if (mp->mask.name[0]!=0) {
						DMP_MATCHUNK(mask_chunks[k],NULL);
						if (isSXPMap(&mp->mask)) 
							DMP_MATCHUNK(mask_sxp_chunks[k],mp->mask.p.tex.sxp_data);
					}
				}
			}
			/* dump auto-cubic chunk */
			{
				Mapping *rm = savemtl->map[Nrefl];
				if (rm&&rm->use&&rm->map.p.ref.acb.flags & AC_ON) DMP_MATCHUNK(MAT_ACUBIC,&rm->map.p.ref.acb);
			}
			if (savemtl->appdata) 
				if(dump_mtlchunk(APP_DATA,stream,savemtl->appdata)==0)
					return(0);
		}				
		break;

	case APP_DATA:
		{
			ULONG *plong = (ULONG *)data;
			WRTERR(&plong[1],plong[0]);
		}
		break;
	case MAT_AMBIENT:
	case MAT_DIFFUSE:
	case MAT_SPECULAR:

#if	IMPORT_MAX_LIB
		if (gammaMgr.enable) {
			Color_24 gc;
			c24 = (Color_24 *)data;
			gc.r = gammaMgr.file_in_gamtab[c24->r];
			gc.g = gammaMgr.file_in_gamtab[c24->g];
			gc.b = gammaMgr.file_in_gamtab[c24->b];
			if(dump_mtlchunk(COLOR_24,stream,&gc)==0)	return(0);
			if(dump_mtlchunk(LIN_COLOR_24,stream,data)==0)return(0);
		}
		else 
#endif
		{
			if(dump_mtlchunk(COLOR_24,stream,data)==0) return(0);
		}
		break;
	case MAT_SHININESS:
		if(dump_mtlchunk(INT_PERCENTAGE,stream,&savemtl->shininess)==0)
			return(0);
		break;
	case MAT_SHIN2PCT:
		if(dump_mtlchunk(INT_PERCENTAGE,stream,&savemtl->shin2pct)==0)
			return(0);
		break;
	case MAT_SHIN3PCT:
		if(dump_mtlchunk(INT_PERCENTAGE,stream,&savemtl->shin3pct)==0)
			return(0);
		break;
	case MAT_TRANSPARENCY:
		if(dump_mtlchunk(INT_PERCENTAGE,stream,&savemtl->transparency)==0)
			return(0);
		break;
	case MAT_XPFALL:
		if(dump_mtlchunk(INT_PERCENTAGE,stream,&savemtl->xpfall)==0)
			return(0);
		break;
	case MAT_REFBLUR:
		if(dump_mtlchunk(INT_PERCENTAGE,stream,&savemtl->refblur)==0)
			return(0);
		break;
	case MAT_SELF_ILPCT:
		if(dump_mtlchunk(INT_PERCENTAGE,stream,&savemtl->selfipct)==0)
			return(0);
		break;
	case MAT_SHADING:
		WRTERR(&savemtl->shading,2);
		break;

	case MAT_TEXMAP:   if (!dmp_map(stream,Ntex)) return(0); break;
	case MAT_TEX2MAP:  if (!dmp_map(stream,Ntex2)) return(0); break;
	case MAT_OPACMAP:  if (!dmp_map(stream,Nopac)) return(0); break;
	case MAT_BUMPMAP:  if (!dmp_map(stream,Nbump)) return(0); break;
	case MAT_SPECMAP:  if (!dmp_map(stream,Nspec)) return(0); break;
	case MAT_SHINMAP:  if (!dmp_map(stream,Nshin)) return(0); break;
	case MAT_SELFIMAP: if (!dmp_map(stream,Nselfi)) return(0); break;
	case MAT_REFLMAP:  if (!dmp_map(stream,Nrefl)) return(0); break;

	case MAT_TEXMASK:  if (!dmp_mask(stream,Ntex)) return(0); break;
	case MAT_TEX2MASK: if (!dmp_mask(stream,Ntex2)) return(0); break;
	case MAT_OPACMASK: if (!dmp_mask(stream,Nopac)) return(0); break;
	case MAT_BUMPMASK: if (!dmp_mask(stream,Nbump)) return(0); break;
	case MAT_SPECMASK: if (!dmp_mask(stream,Nspec)) return(0); break;
	case MAT_SHINMASK: if (!dmp_mask(stream,Nshin)) return(0); break;
	case MAT_SELFIMASK:if (!dmp_mask(stream,Nselfi)) return(0); break;
	case MAT_REFLMASK: if (!dmp_mask(stream,Nrefl)) return(0); break;

	case MAT_MAP_TILING: 
		WRTERR(data,2);
		break;
	case MAT_MAP_TEXBLUR: 
	case MAT_MAP_USCALE: 
	case MAT_MAP_VSCALE: 
	case MAT_MAP_UOFFSET: 
	case MAT_MAP_VOFFSET: 
		WRTERR(data,4);
		break;
	case MAT_MAP_COL1:
	case MAT_MAP_COL2:
	case MAT_MAP_RCOL:
	case MAT_MAP_GCOL:
	case MAT_MAP_BCOL:
		c24=(Color_24 *)data;
		WRTERR(c24,3);
		break;
	case MAT_MAP_ANG:
		{
			MapParams *mp = (MapParams *)data;
			float ang,dang;
			ang = (float)atan2(mp->ang_sin,mp->ang_cos);
			dang = RadToDeg(ang);
#if 0
			printf("Saving MAT_MAP_ANG sin = %.4f , cos = %.4f, ang = %.4f \n",
				mp->ang_sin, mp->ang_cos, ang);
#endif
			WRTERR(&dang,4);
		}
		break;

	case COLOR_F:
		cf=(Color_f *)data;
		WRTERR(cf,12);
		break;
	case COLOR_24:
		c24=(Color_24 *)data;
		WRTERR(c24,3);
		break;
	case LIN_COLOR_24:
		c24 = (Color_24 *)data;
		WRTERR(c24,3);
		break;
	case MAT_NAME:  /* Simple strings */
	case MAT_MAPNAME:
		string=(char *)data;
		WRTERR(string,strlen(string)+1);
		break;
	case MAT_BUMP_PERCENT:
	case INT_PERCENTAGE:
		WRTERR(data,2);
		break;
	case MAT_WIRESIZE:
		WRTERR(data,4);
		break;
	case MAT_TWO_SIDE:
	case MAT_SUPERSMP:
	case MAT_ADDITIVE:
	case MAT_WIRE:
	case MAT_FACEMAP:
	case MAT_XPFALLIN:
	case MAT_USE_XPFALL:
	case MAT_USE_REFBLUR:
	case MAT_PHONGSOFT:
	case MAT_WIREABS:
	case DUMMY:
		break;
	case MAT_ACUBIC: {
		AutoCubicParams *ac = (AutoCubicParams *)data;
		WRTERR(&ac->shade,1);
		WRTERR(&ac->aalevel,1);
		WRTERR(&ac->flags,2);
		WRTERR(&ac->size,4);
		WRTERR(&ac->nth,4);
					 }
					 break;
	case MAT_SXP_TEXT_DATA:
	case MAT_SXP_TEXT2_DATA:
	case MAT_SXP_OPAC_DATA:
	case MAT_SXP_BUMP_DATA:
	case MAT_SXP_SPEC_DATA:
	case MAT_SXP_SHIN_DATA:
	case MAT_SXP_SELFI_DATA:

	case MAT_SXP_TEXT_MASKDATA:
	case MAT_SXP_TEXT2_MASKDATA:
	case MAT_SXP_OPAC_MASKDATA:
	case MAT_SXP_BUMP_MASKDATA:
	case MAT_SXP_SPEC_MASKDATA:
	case MAT_SXP_SHIN_MASKDATA:
	case MAT_SXP_SELFI_MASKDATA:
	case MAT_SXP_REFL_MASKDATA:
		{
			ULONG *plong = (ULONG *)data;
			if (plong!=NULL)
				WRTERR(&plong[1],plong[0]);
		}
		break;
	}

	/* Save file ptr */

	curpos=ftell(stream);

	/* Point back to chunk size location */

	fseek(stream,chunkptr,SEEK_SET);

	/* Calc & write chunk size */

	chunksize=curpos-chunkbase;
	WRTERR(&chunksize,4);

	/* Point back to file end */

	fseek(stream,curpos,SEEK_SET);
	return(1);
}






BOOL MeshMtlList::isSXPname(char *name) {
	char ext[5];
	strncpy_s(ext, 5, name+strlen(name)-4, 5);
	_strupr_s(ext, 5);
	return(strcmp(".SXP",ext)==0);
}


int MeshMtlList::dmp_map_params(FILE *stream,MapParams *mp) {
	DMP_MATCHUNK(MAT_MAP_TILING,&mp->texflags);
	DMP_MATCHUNK(MAT_MAP_TEXBLUR,&mp->texblur);
	if (mp->uscale!=1.0)
		DMP_MATCHUNK(MAT_MAP_USCALE,&mp->uscale);
	if (mp->vscale!=1.0)
		DMP_MATCHUNK(MAT_MAP_VSCALE,&mp->vscale);
	if (mp->uoffset!=0.0)
		DMP_MATCHUNK(MAT_MAP_UOFFSET,&mp->uoffset);
	if (mp->voffset!=0.0)
		DMP_MATCHUNK(MAT_MAP_VOFFSET,&mp->voffset);
	if (mp->ang_sin!=0.0) {
		DMP_MATCHUNK(MAT_MAP_ANG,mp);
	}
	if (mp->col1.r!=0||mp->col1.g!=0||mp->col1.b!=0) 
		DMP_MATCHUNK(MAT_MAP_COL1,&mp->col1);
	if (mp->col2.r!=255||mp->col2.g!=255||mp->col2.b!=255) 
		DMP_MATCHUNK(MAT_MAP_COL2,&mp->col2);
	if (mp->rcol.r!=255||mp->rcol.g!=0  ||mp->rcol.b!=0  ) 
		DMP_MATCHUNK(MAT_MAP_RCOL,&mp->rcol);
	if (mp->gcol.r!=0  ||mp->gcol.g!=255||mp->gcol.b!=0  ) 
		DMP_MATCHUNK(MAT_MAP_GCOL,&mp->gcol);
	if (mp->bcol.r!=0  ||mp->bcol.g!=0  ||mp->bcol.b!=255) 
		DMP_MATCHUNK(MAT_MAP_BCOL,&mp->bcol);
	return(1);
}

int MeshMtlList::dmp_map(FILE *stream, int i) {
	Mapping *m = savemtl->map[i];
	if (i==Nbump) {
		int t = m->amt.pct/4;      /* for old versions */
		DMP_MATCHUNK(INT_PERCENTAGE,&t);
		DMP_MATCHUNK(MAT_MAPNAME,m->map.name);
		DMP_MATCHUNK(MAT_BUMP_PERCENT,&m->amt.pct); /* new version of bump percent*/
	}
	else {
		DMP_MATCHUNK(INT_PERCENTAGE,&m->amt.pct);
		DMP_MATCHUNK(MAT_MAPNAME,m->map.name);
	}
	if (m->map.kind==0) 
		return(dmp_map_params(stream,&m->map.p.tex));
	else 
		return(1);
}


int MeshMtlList::dmp_mask(FILE *stream, int i) {
	Mapping *m = savemtl->map[i];
	DMP_MATCHUNK(MAT_MAPNAME,m->mask.name);
	if (m->mask.kind==0) 
		return(dmp_map_params(stream,&m->mask.p.tex));
	else 
		return(1);
}

int MeshMtlList::isSXPMap(MapData *md) {
	return(md->kind==0&&md->p.tex.sxp_data!=NULL);
} 
#if	IMPORT_MAX_LIB
bool MeshMtlList::IsShellMtl(Mtl *m)
{
	unsigned long mtlClassID = m->ClassID().PartA();
	if( mtlClassID == BAKE_SHELL_CLASS_ID )
		return true;
	else
		return false;
}

void MeshMtlList::ConvertSMtlToMaxMtl( SMtl *smtl, Mtl **mtl )
{

	StdMat *m;
	Mesh *mesh = NULL;
	if (smtl==NULL) 
	{
		m = New3DSDefaultMtl();
		*mtl = m;
		return;
	}
	m = NewDefaultStdMat();
	m->SetName(smtl->name);
	int shade;
	switch(smtl->shading) 
	{
	case REND_FLAT:  shade = SHADE_CONST; break;
	case REND_METAL: shade = SHADE_METAL; break;
	default:		 shade = SHADE_PHONG; break;
	}
	m->SetShading(shade);
	m->SetAmbient(ColorFrom24(smtl->amb),0);
	m->SetDiffuse(ColorFrom24(smtl->diff),0);
	m->SetFilter(ColorFrom24(smtl->diff),0);
	m->SetSpecular(ColorFrom24(smtl->spec),0);
	m->SetShininess((float)smtl->shininess/100.0f,0);
	m->SetShinStr((float)smtl->shin2pct/100.0f,0);
	m->SetOpacity(1.0f-(float)smtl->transparency/100.0f,0);
	m->SetOpacFalloff((float)smtl->xpfall/100.0f, 0);		
	m->SetFalloffOut(smtl->flags&MF_XPFALLIN?0:1);  
	m->SetSelfIllum((float)smtl->selfipct/100.0f,0);
	m->SetWireSize(smtl->wiresize,0);
	m->SetFaceMap(smtl->flags&MF_FACEMAP?1:0);
	m->SetSoften(smtl->flags&MF_PHONGSOFT?1:0);
	m->SetWire(smtl->flags&MF_WIRE?1:0);
	m->SetTwoSided(smtl->flags&MF_TWOSIDE?1:0);
	m->SetTransparencyType(smtl->flags&MF_ADDITIVE ? TRANSP_ADDITIVE : TRANSP_FILTER);
	m->SetWireUnits(smtl->flags&MF_WIREABS?1:0);


	if (smtl->map) 
	{
		Texmap *txm;
		float amt,amt0;
		BOOL gotTex=0;
		BOOL dum;
		for (int i=0; i<8; i++) 
		{
			if (smtl->map[i]==NULL) 
				continue;
			Mapping &mp = *(smtl->map[i]);
			int n = MAXMapIndex(i);
			if (i==Nrefl) 
			{
				amt = (float)mp.amt.pct/100.0f;
				RMapParams &par = mp.map.p.ref;
				if (par.acb.flags&AC_ON) 
				{	
					// Mirror or Auto-cubic
					if (par.acb.flags&AC_MIRROR) 
					{
#ifndef NO_MAPTYPE_FLATMIRROR // orb 01-07-2001
						StdMirror *mir = NewDefaultStdMirror();
						txm = (Texmap *)mir;
						mir->SetDoNth(par.acb.flags&AC_FIRSTONLY?0:1);
						mir->SetNth(par.acb.nth);
#endif // NO_MAPTYPE_FLATMIRROR
					}
					else 
					{
#ifndef NO_MAPTYPE_REFLECTREFRACT // orb 01-07-2001
						StdCubic *cub = NewDefaultStdCubic();
						txm = (Texmap *)cub;
						cub->SetSize(par.acb.size,0);
						cub->SetDoNth(par.acb.flags&AC_FIRSTONLY?0:1);
						cub->SetNth(par.acb.nth);
#endif // NO_MAPTYPE_REFLECTREFRACT
					}
				}
				else 
				{	
					// Environment map
					txm = MakeTex(mp.map,smtl,dum);
				}

				if (strlen(mp.mask.name)>0) 
				{
					// make a Mask texmap.
					Texmap *masktex = (Texmap *)CreateInstance(TEXMAP_CLASS_ID, Class_ID(MASK_CLASS_ID,0));
					masktex->SetSubTexmap(1,MakeTex(mp.mask,smtl,dum));
					masktex->SetSubTexmap(0,txm);
					txm = masktex;
				}

				m->SetSubTexmap(n,txm);
				amt = (float)mp.amt.pct/100.0f;
				m->SetTexmapAmt(n, amt, 0);
			}// if (i==Nrefl)
			else 
			{

				// non-reflection maps
				amt = (float)mp.amt.pct/100.0f;

				// DS: 4/30/97 correct for new interpretation of the
				// amount sliders.
				switch(i) 
				{
				case Nopac:	 
					if (amt<1.0f) 
						m->SetOpacity(0.0f,0); 
					break;
				case Nselfi: 
					if (amt<1.0f) 
						m->SetSelfIllum(0.0f,0); 
					break;
				case Nshin:  
					// Shininess mapping in 3DS was really shininess strength mapping
					amt*= (float)smtl->shin2pct/100.0f;
					m->SetShinStr(0.0f,0);
					break;
				}

				BOOL wasSXP;
				txm = MakeTex(mp.map,smtl,wasSXP);
				if (n==ID_BU&&!wasSXP) amt *= 10.0f;
				m->SetTexmapAmt(n, amt, 0);
				if (strlen(mp.mask.name)>0) 
				{
					// make a Mask texmap.
					Texmap *masktex = (Texmap *)CreateInstance(TEXMAP_CLASS_ID, Class_ID(MASK_CLASS_ID,0));
					masktex->SetSubTexmap(1,MakeTex(mp.mask,smtl,dum));
					masktex->SetSubTexmap(0,txm);
					txm = masktex;
				}
				if (i==Ntex2) 
				{
					if (gotTex) 
					{
						// Make a Composite texmap
						MultiTex *comp = NewDefaultCompositeTex();
						comp->SetNumSubTexmaps(2);
						Texmap *tm0 = m->GetSubTexmap(ID_DI);
						comp->SetSubTexmap(0,tm0);
						comp->SetSubTexmap(1,txm);
						m->SetSubTexmap(ID_DI,comp);						
						if (tm0) 
							tm0->SetOutputLevel(0,amt0);
						if (txm)
							txm->SetOutputLevel(0,amt);
						m->SetTexmapAmt(ID_DI,1.0f,0);
					}
					else {
						m->SetSubTexmap(ID_DI,txm);						
						m->SetTexmapAmt(n,amt,0);
					}
				} 
				else 
					m->SetSubTexmap(n,txm);
				if (i==Ntex&&txm) 
				{
					gotTex=1;
					amt0 = amt;
				}
			}// else

			m->EnableMap(n,mp.use);

		}// for (8 maps)

	}//if (smtl->map) 

	*mtl = m;
	return;

}



StdMat *
MeshMtlList::New3DSDefaultMtl() 
{
	StdMat *m = NewDefaultStdMat();
	m->SetName(_T("Default"));
	m->SetAmbient(Color(.7f,.7f,.7f),0);
	m->SetDiffuse(Color(.7f,.7f,.7f),0);
	m->SetSpecular(Color(1.0f,1.0f,1.0f),0);
	m->SetShininess(0.5f,0);
	m->SetShinStr(.707f,0);
	return m;
}


Texmap* 
MeshMtlList::MakeTex(MapData& map, SMtl *smtl, BOOL &wasSXP) {
	Texmap *txm; 
	wasSXP = FALSE;
	if (map.kind==0) { 
		// Texture Map
		//		if (IsSXPName(map.name)&&(map.p.tex.sxp_data!=NULL)) {
		if (IsSXPName(map.name)) {	 // DS - 6/11/96
			Tex3D *t3d = GetSXPReaderClass(map.name);
			if (t3d) {
				if (map.p.tex.sxp_data) {
					ULONG *p = (ULONG *)map.p.tex.sxp_data;
					t3d->ReadSXPData(map.name, (void *)(p+1));
					wasSXP = TRUE;
				}
			}
			txm = t3d;							
		}
		else {
			BitmapTex *bmt = NewDefaultBitmapTex();
			bmt->SetMapName(map.name);
			MapParams &par = map.p.tex;
			bmt->SetAlphaAsMono((par.texflags&TEX_ALPHA_SOURCE)?1:0);
			bmt->SetAlphaSource((par.texflags&TEX_DONT_USE_ALPHA)?ALPHA_NONE:ALPHA_FILE);
			bmt->SetFilterType((par.texflags&TEX_SAT)?FILTER_SAT:FILTER_PYR);
			StdUVGen *uv = bmt->GetUVGen();
			uv->SetUOffs(par.uoffset,0);
			uv->SetVOffs(-par.voffset,0);
			uv->SetUScl(par.uscale,0);
			uv->SetVScl(par.vscale,0);
			uv->SetAng(-((float)atan2(par.ang_sin, par.ang_cos)),0);
			uv->SetBlur(par.texblur+1.0f,0);
			int tile=0;
			if (par.texflags&TEX_MIRROR) tile|= U_MIRROR|V_MIRROR;
			else {
				if (0==(par.texflags&TEX_NOWRAP)) tile|= U_WRAP|V_WRAP;
			}
			uv->SetTextureTiling(tile);
			TextureOutput *txout = bmt->GetTexout();
			txout->SetInvert(par.texflags&TEX_INVERT?1:0);
			txm = bmt;
		}
		if (map.p.tex.texflags&TEX_TINT) {
			// map.p.tex.col1, col2	: stuff into Mix	
			MultiTex* mix = NewDefaultMixTex();
			mix->SetColor(0,ColorFrom24(map.p.tex.col1));
			mix->SetColor(1,ColorFrom24(map.p.tex.col2));
			mix->SetSubTexmap(2, txm);
			txm = mix;			
		}
		else if (map.p.tex.texflags&TEX_RGB_TINT) {
			// map.p.tex.rcol,gcol,bcol : stuf into tint
#ifndef NO_MAPTYPE_RGBTINT // orb 01-07-2001
			MultiTex* mix = NewDefaultTintTex();
			mix->SetColor(0,ColorFrom24(map.p.tex.rcol));
			mix->SetColor(1,ColorFrom24(map.p.tex.gcol));
			mix->SetColor(2,ColorFrom24(map.p.tex.bcol));
			mix->SetSubTexmap(0, txm);
			txm = mix;			
#endif // NO_MAPTYPE_RGBTINT
		}
	}
	else {  
		// kind == 1 :  Reflection Map
		BitmapTex *bmt = NewDefaultBitmapTex();
		bmt->SetMapName(map.name);
		StdUVGen *uv = bmt->GetUVGen();

		// TBD: REFLECTION BLUR SETTING:
		uv->SetBlurOffs((float)smtl->refblur/400.0f+.001f,0);
		bmt->InitSlotType(MAPSLOT_ENVIRON);
		txm = bmt;
	}


	return txm;
}


Color 
MeshMtlList::ColorFrom24( Color_24 c )
{
	Color a;
	a.r = (float)c.r/255.0f;
	a.g = (float)c.g/255.0f;
	a.b = (float)c.b/255.0f;
	return a;
}
#endif
BOOL 
MeshMtlList::IsSXPName( char *name )
{
	char fname[30];
	char ext[5];
	_splitpath(name, NULL, NULL, fname, ext );
	return stricmp(ext,".sxp")==0?1:0;

}

void MeshMtlList::formatModMtl( SMtl* mtl )
{
	Mapping* pSubMap = NULL;
	
	for (int index = 0; index < NMAPTYPES; index ++ )
	{
		pSubMap = mtl->map[index];

		if (!pSubMap || !pSubMap->use)
		{
			continue;
		}

		MapData& mapData = pSubMap->map;
		string mapName(mapData.name);
		
		if ( !mapName.empty() )
		{
			if ( index == Ntex )
			{
				strcpy_s(mtl->diffuseBitmap, 255, mapData.name );
			}
			else if( index == Nopac )
			{
				strcpy_s(mtl->opacityBitmap, 255, mapData.name );
			}
		}

	}
}