// DynamicTexture.cpp: implementation of the DynamicTexture class.
//
//////////////////////////////////////////////////////////////////////

#include <vgStableHeaders.h>
#include <vgTex/tvgArchive.h>
#include <vgTex/tvgArchiveManager.h>
#include <vgTex/tvgDynamicBillboard.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

namespace vgCore
{


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DynamicBillboard::DynamicBillboard()
{
// 	setRenderType(RENDERTYPE_ROTATE_Y);
}
//----------------------------------------------------------------
DynamicBillboard::~DynamicBillboard()
{

}
//----------------------------------------------------------------
int DynamicBillboard::Update ()
{
	if (framevec.size() == 0)
	{
		return -1;
	}

	newTickCount = GetTickCount();	
	int milliseconds = newTickCount - lastTickCount;
	lastTickCount = newTickCount;
	next += milliseconds;											// Increase next Based On The Timer

	frameId = next/framevec.at(0).timelength;												// Calculate The Current Frame

	if (frameId >= header.framecount )										// Are We At Or Past The Last Frame?
	{
		frameId = 0;												// Reset The Frame Back To Zero (Start Of Video)
		next = 0;													// Reset The Animation Timer (next)
	}


	return frameId;
}
//----------------------------------------------------------------
void DynamicBillboard::GetFrameTexture(int frameId)
{

	if (frameId == -1)
	{
		return;
	}

	TextureManager &texmgr = TextureManager::getSingleton();

	TexturePtr ptex = texmgr.getTexturePtr(framevec.at(frameId).filename);
 

	if ( ptex->getTextureID() == 0 || 
		ptex->getTextureID() == -1 )
	{
		return;
	}

 	if ( ptex.isNull() == true )
 	{
 		MessageBox( NULL , "初始化动态贴图错误!" , "", MB_OK );
 	}

 	setTexturePtr(ptex);

	return;
}

//----------------------------------------------------------------
bool DynamicBillboard::ReadFile()										
{
	// Opens The DTX Stream

	if ( !vgKernel::SystemUtility::checkFileExist( szDtxFile) )
	{
		String errorMsg(szDtxFile);
		errorMsg += "丢失！";
		vgKernel::SystemUtility::showModelDialog( errorMsg );
		return false;
	}
	vgKernel::StreamReaderPtr preader = 
		vgKernel::StreamReaderFactory::createFromFile( szDtxFile.c_str() );

	if ( preader.isNull() || !preader->isValid())
	{
		return false;
	}


	texfilefolderpath = vgKernel::StringUtility::getPathFromAbsoluteFilename(szDtxFile);

	preader->read( &header, sizeof(DtxHeader) );


	for (int i = 0; i < header.framecount; i++)
	{
		SingleFrame sframe;
		preader->read( &sframe, sizeof(SingleFrame) );

		framevec.push_back(sframe);
	}

	preader->close();

	if (framevec.size() == 0)
	{
		return false;
	}

	return true;
}
//----------------------------------------------------------------
bool DynamicBillboard::init()
{
	next = 0;
	frameId = 0;
	sum = 0;
	lastTickCount = GetTickCount();

	bool ret = ReadFile();									// Open The DTX File

	if ( ret == false )
	{
		return false;
	}

	//------------------------------------------
	// 载入纹理
	//------------------------------------------
	static int weight = 97800;

	try
	{
		ArchivePtr parch( new FileSystemArchive( texfilefolderpath ,"filesystem") );

		parch->load();

		ArchiveManager &archmgr = ArchiveManager::getSingleton();
		archmgr.addArchive( weight , parch );
	}
	catch (Exception &e)
	{
		::MessageBox( NULL , e.getFullDescription().c_str() , "添加文件失败" , MB_OK );
	}

 	for (int i = 0; i < header.framecount; i++)
	{ 		
		String texname = framevec.at(i).filename;

  		String texfilepath = texfilefolderpath + "\\" +texname;
  
  		texfilepathvec.push_back(texfilepath);
 	}
	return true;
}
//----------------------------------------------------------------
vgKernel::StringVector DynamicBillboard::getTexfilePaths()
{
	return texfilepathvec;
}

FrameVector DynamicBillboard::getFrames()
{
	return framevec;
}

}//namespace