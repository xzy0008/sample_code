#include "vgStableHeaders.h"
#include <vgUtility/vgFileChunkHandler.h>


FileChunkHandler::FileChunkHandler()
{

}

FileChunkHandler::~FileChunkHandler()
{

}

//----------------------------------------------------------------------------
int
FileChunkHandler::skip_chunk(FILE *stream)
{
	Chunk_hdr chunk;

	RDERR(&chunk,sizeof(Chunk_hdr));

	chunk.size-=6L;
	return(1-fseek(stream,chunk.size,SEEK_CUR));
}



/* Skip the next n bytes in the file */
int
FileChunkHandler::SkipRead(FILE *stream,long bytes)
{
	return fseek(stream,bytes,SEEK_CUR);
}



/* Get next chunk ID and return it, repositioning file to old pos */
int
FileChunkHandler::get_next_chunk(FILE *stream,Chunk_hdr *hdr)
{
	long curpos;

	curpos=ftell(stream);
	RDERR(hdr,sizeof(Chunk_hdr));
	fseek(stream,curpos,SEEK_SET);

#ifdef DUMPING
	{
		TCHAR buf[256];
		_stprintf(buf,_T("Next chunk: %X, size:%d"),hdr->tag,hdr->size);
		MessageBox(NULL,buf,_T("3DSIMP"),MB_OK);
	}
#endif // DUMPING

	return(1);
}


//-Get a null-terminated string from the file---------------------------------
int
FileChunkHandler::read_string(char *string,FILE *stream,int maxsize)
{
	while(maxsize--)
	{
		RDERR(string,1);
		if(*(string++)==0)
			return(1);
	}
	return(0);	/* Too long */
}


//----------------------------------------------------------------------------
void
FileChunkHandler::split_fn(char *path,char *file,char *pf)
{
	int ix,jx,bs_loc,fn_loc;
	if(strlen(pf)==0) {
		if(path) *path=0;
		if(file) *file=0;
		return;
	}
	bs_loc=static_cast<int>(strlen(pf));	// SR DCAST64: Downcast to 2G limit.
	for(ix=bs_loc-1; ix>=0; --ix) {
		if(pf[ix]=='\\')  {
			bs_loc=ix;
			fn_loc=ix+1;
			goto do_split;
		}
		if(pf[ix]==':') {
			bs_loc=ix+1;
			fn_loc=ix+1;
			goto do_split;
		}
	}
	bs_loc= -1;
	fn_loc=0;

do_split:
	if(file)
		strcpy(file,&pf[fn_loc]);
	if(path) {
		if(bs_loc>0)  {
			for(jx=0; jx<bs_loc; ++jx)
				path[jx]=pf[jx];
			path[jx]=0;
		}
		else  path[0]=0;
	}
}


#if 0
//----------------------------------------------------------------------------
void FileChunkHandler::fin_degammify(Color_f *col, Color_f *gamcol) {
	if (gammaMgr.enable) {
		col->r = deGammaCorrect(gamcol->r, gammaMgr.fileInGamma);
		col->g = deGammaCorrect(gamcol->g, gammaMgr.fileInGamma);
		col->b = deGammaCorrect(gamcol->b, gammaMgr.fileInGamma);
	}
	else *col = *gamcol;
}
#endif
//----------------------------------------------------------------------------



void * MemeryHandler::XMAlloc( int size )
{
	return malloc(size);
}

void * MemeryHandler::XMAllocZero( int size )
{
	void *p = malloc(size);
	memset(p,0,size);
	return p;
}

void MemeryHandler::XMFree( void *p )
{
	if (p) 
		free(p);
}

void MemeryHandler::XMFreeAndZero( void **p )
{
	if (p) 
	{
		if (*p) 
		{
			free(*p);
			*p = NULL;
		}
	}
}

