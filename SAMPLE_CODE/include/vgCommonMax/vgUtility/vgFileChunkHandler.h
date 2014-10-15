
#ifndef _VGFILECHUNK_HANDLER_H_INCLUDED_
#define _VGFILECHUNK_HANDLER_H_INCLUDED_
/**********************************************************************
*<
FileChunkHandler.h:	文件块处理类
主要内容是： class FileChunkHandler的声明及定义
*>	
**********************************************************************/

#include "vgStableHeaders.h"

//#include "3dsStruct.h"



#define RDERR(ptr,count) { if(!fread(ptr,count,1,stream)) return 0; }
#define RD3FLOAT(p) RDERR(p,3*sizeof(FLOAT))
#define RDFLOAT(p) 	RDERR(p,sizeof(FLOAT))
#define RDLONG(p) RDERR(p,sizeof(LONG))
#define RDSHORT(p) RDERR(p,sizeof(SHORT))


//////////////////////////////////////////////////////////////////////////
//		文件块处理类	//////////////////////////////////////////////////////
class FileChunkHandler
{
public:
	FileChunkHandler();
	~FileChunkHandler();

	static int skip_chunk(FILE *stream);
	static int get_next_chunk(FILE *stream,Chunk_hdr *hdr);
	static int SkipRead(FILE *stream,long bytes);
	static int read_string(char *string,FILE *stream,int maxsize);
	static int load_app_data(FILE *stream,void **pdata, int size);
	//static void fin_degammify(Color_f *col, Color_f *gamcol);
	static void split_fn(char *path,char *file,char *pf);


};

class MemeryHandler
{
public:
	static void *XMAlloc(int size);
	static void *XMAllocZero(int size);
	static void XMFree(void *p);
	static void XMFreeAndZero(void **p);

protected:
private:
};

//#define RDERR(ptr,sz) if (fread((void *)ptr,1,sz,stream)!=(sz)) return(0)
#define WRTERR(ptr,sz) if (fwrite((void *)ptr,1,sz,stream)!=(sz)) return(0)
#define GREAD(ptr,sz) ((fread((void *)ptr,1,sz,stream)!=(sz)) ? 0:1)
#define GWRITE(ptr,sz) ((fwrite((void *)ptr,1,sz,stream)!=(sz)) ? 0:1)

#define WRITEF(ptr,size) fwrite((char *)ptr,1,size,wstream)
#define WERR(ptr,sz) {if (WRITEF(ptr,(sz))!=(sz)) return(0);}
#define WRFLOAT(ptr) WERR(ptr,sizeof(FLOAT))
#define WR3FLOAT(ptr) WERR(ptr,3*sizeof(FLOAT))
#define WRLONG(ptr) WERR(ptr,sizeof(LONG))
#define WRSHORT(ptr) WERR(ptr,sizeof(SHORT))
#define WRSTRING(ptr) WERR(ptr,strlen(ptr)+1)


#endif// _VGFILECHUNK_HANDLER_H_INCLUDED_