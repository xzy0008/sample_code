// DynamicTexture.h: interface for the DynamicTexture class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __VGDYNAYMICTEXTURE_H__
#define __VGDYNAYMICTEXTURE_H__

namespace vgCore
{

	/**
	@date 	2009/03/15  8:34	
	@author  YUXIN

	@brief 	

	@see    
	*/


class DynamicTexture  
{
public:
	DynamicTexture(string FileName);
	virtual ~DynamicTexture();

	struct SingleFrame;

	int Update ();	// Perform Motion Updates
	bool ReadFile();
	bool init();
	void GetFrameTexture(int frame);
	vector<string> getTexfilePaths();
	vector<SingleFrame> getFrames();

public:

	//**********************************
	//计算帧号所用变量
	int next;
	int frame;
	int lastTickCount;
	int newTickCount;

	long sum;				//用于计算时长
	//**********************************
	//文件信息及单帧信息
	struct  SingleFrame
	{
		long frameid;			//单帧帧号
		long framelength;		//单帧时长
		string texturename;		//纹理名称
	};

	vector<SingleFrame> framevec;
	vector<string> texfilepathvec;
	
	string texfilefolderpath;		//纹理贴图文件夹路径
	long framecount;		//总帧数
	long totaltime;			//总时长 单位为毫秒（millisecond）
	long timeratio;			//时间比例

	//**********************************
	ifstream ifile;			
	string szDtxFile;		//DTX文件路径

	TextureManager &texmgr;
	ArchiveManager &archmgr;
};

#endif // !defined(AFX_AVITEXTURE_H__7943A9A3_15D7_4FD7_8DC2_F245DA84E41A__INCLUDED_)

}