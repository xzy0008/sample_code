#ifndef _VGVIEWERMOD_H_INCLUDED_
#define _VGVIEWERMOD_H_INCLUDED_
/**********************************************************************
*<
vgModViewer.h:	mod浏览类头文件
主要内容是： class vgViewerMOD的声明及定义
*>	
**********************************************************************/

#include "vgStableHeaders.h"


//////////////////////////////////////////////////////////////////////////
//		MOD浏览类	//////////////////////////////////////////////////////
class vgModViewer 
{
public:
	static	bool openMODByVGViewer();
	static	std::string configVGViewerINIFile();
	static	std::string getVGViewerPath();
	static	bool hasVGViewerSetup();

	static	CBox3 getSceneBox();
	static	bool  writeBox3Text();
	static	void  setSceneBox(CBox3& box );
	static	void  formatBox(CBox3& box );

	static	bool	resetViewer();


public:
	static	void setFileNameMod(std::string name)
	{
		_strFileNameMod = name;
	}
	static	std::string getFileNameMod()
	{
		return	_strFileNameMod;
	}
	static	void setFileNameConfig(std::string name)
	{
		_strFileNameConfig = name;
	}
	static	std::string getFileNameConfig()
	{
		return	_strFileNameConfig;
	}


public:
	static	std::string		_strFileNameMod;
	static	std::string		_strFileNameConfig;

	static	FILE*	_iniFile;
	static	CBox3	_sceneBox;

};//class vgModClassDesc
/////////////////////////////////////////////////////////	MOD浏览类
//////////////////////////////////////////////////////////////////////////

#endif	//_VGVIEWERMOD_H_INCLUDED_
