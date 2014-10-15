// DynamicTexture.cpp: implementation of the DynamicTexture class.
//
//////////////////////////////////////////////////////////////////////

#include <vgStableHeaders.h>
#include <vgEffect/vgDynamicTexture.h>
//#include <vgMod/vgQuadtreeSceneManager.h>
#include <vgTex/tvgArchive.h>
#include <vgTex/tvgArchiveManager.h>


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

DynamicTexture::DynamicTexture(string FileName)
	:archmgr(ArchiveManager::getSingleton()),texmgr(TextureManager::getSingleton())
{
	szDtxFile=FileName;
}
//----------------------------------------------------------------
DynamicTexture::~DynamicTexture()
{

}
//----------------------------------------------------------------
int DynamicTexture::Update ()
{
	newTickCount = GetTickCount();	
	int milliseconds = newTickCount - lastTickCount;
	lastTickCount = newTickCount;
	next += milliseconds;											// Increase next Based On The Timer

	int cmp = next % totaltime;

	for (int i = 0; i < framecount; i++)
	{		
		if (cmp > sum)
		{
			sum += framevec.at(i).framelength;
			if (cmp < sum)
			{
				frame = i;
				sum = 0;
				break;
			}
		}
	}

	if (frame>=framecount)										// Are We At Or Past The Last Frame?
	{
		frame = 0;												// Reset The Frame Back To Zero (Start Of Video)
		next = 0;
	}

	return frame;
}
//----------------------------------------------------------------
void DynamicTexture::GetFrameTexture(int frame)
{
	TexturePtr ptex = 
		texmgr.getTexturePtr(framevec.at(frame).texturename);

	if ( ptex.isNull() == true )
	{
		MessageBox( NULL , "初始化动态贴图错误!" , "", MB_OK );
	}

	ptex->useBind();
	return;
}
//----------------------------------------------------------------
bool DynamicTexture::ReadFile()										
{
	// Opens The DTX Stream

	ifile.open(szDtxFile.c_str());
	
	if (ifile.bad())
	{
		return false;
	}

	texfilefolderpath = szDtxFile.substr(0, szDtxFile.find_last_of("\\/"));		//纹理贴图文件夹路径
	ifile >> framecount;	//总帧数
	ifile >> totaltime;		//单位为毫秒（millisecond）
	ifile >> timeratio;		//时间比例

	for (int i = 0; i < framecount; i++)
	{
		SingleFrame sframe;
		ifile >> sframe.frameid;	
		ifile >> sframe.framelength;
		ifile >> sframe.texturename;

		framevec.push_back(sframe);
	}

	ifile.close();

	//to be continue

	if (framevec.size() == 0)
	{
		return false;
	}

	return true;
	
}
//----------------------------------------------------------------
bool DynamicTexture::init()
{
	next = 0;
	frame = 0;
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
		archmgr.addArchive( weight , parch );
	}
	catch (Exception &e)
	{
		::MessageBox( NULL , e.getFullDescription().c_str() , "添加文件失败" , MB_OK );
	}

	for (int i = 0; i < framecount; i++)
	{
		string texname = framevec.at(i).texturename;
		texmgr.addTexturePtr( texname , false );
		string texfilepath = texfilefolderpath + "\\" +texname;
		texfilepathvec.push_back(texfilepath);
	}

	return true;
}
//----------------------------------------------------------------
vector<string> DynamicTexture::getTexfilePaths()
{
	return texfilepathvec;
}

vector<DynamicTexture::SingleFrame> DynamicTexture::getFrames()
{
	return framevec;
}
}//namespace