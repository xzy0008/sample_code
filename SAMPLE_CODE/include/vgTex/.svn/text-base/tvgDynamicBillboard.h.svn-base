// DynamicBillboard.h: interface for the DynamicTexture class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __VGDYNAYMICBILLBOARD_H__  
#define __VGDYNAYMICBILLBOARD_H__

#include <vgTex/tvgBillboard.h>
#include <vgTex/vgDtxDeclaration.h>
#include <vgKernel/vgkStreamReader.h>
#include <vgkernel/vgkStringUtility.h>
#include <vgKernel/vgkStringVector.h>

namespace vgCore
{

	/**
	@date 	2009/03/15  8:34	
	@author  YUXIN

	@brief 	

	@see    
	*/


class VGDEP_EXPORT DynamicBillboard : public Billboard
{
public:
	DynamicBillboard();
	virtual ~DynamicBillboard();


	int Update ();	// Perform Motion Updates
	bool ReadFile();
	bool init();
	void GetFrameTexture(int frameId);
	vgKernel::StringVector getTexfilePaths();
	FrameVector getFrames();
	
	void setDtxFilePath(String & filepath){ szDtxFile = filepath; }

public:

	//**********************************
	//计算帧号所用变量
	int next;
	int frameId;
	int lastTickCount;
	int newTickCount;

	long sum;				//用于计算时长
	//**********************************

	DtxHeader header;
	FrameVector framevec;
	//**********************************
	String szDtxFile;		//DTX文件路径
	StringVector texfilepathvec;	
	string texfilefolderpath;		//纹理贴图文件夹路径

};

}
#endif // !defined(AFX_AVITEXTURE_H__7943A9A3_15D7_4FD7_8DC2_F245DA84E41A__INCLUDED_)
