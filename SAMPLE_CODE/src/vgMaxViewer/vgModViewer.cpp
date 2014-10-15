
#include "vgStableHeaders.h"
#include "vgModViewer.h"

#include "vgUtility/vgModCommonUtility.h"

//#include "vgModClassDesc.h"
//#include "vgModExportor.h"

std::string	vgModViewer::_strFileNameMod = "";
std::string	vgModViewer::_strFileNameConfig = "";
FILE*	vgModViewer::_iniFile = NULL;
CBox3	vgModViewer::_sceneBox = CBox3();

//----------------------------------------------------------------------------
bool	vgModViewer::hasVGViewerSetup()
{
	//从注册表中获取安装目录
	bool result = false;

	HKEY      hRootKey;   
	TCHAR*	pRegItem = vgModUtility::GetString( IDS_REGISTER_VALUE_VRGIS );
	LPCTSTR   data_Set = pRegItem;//"vgFrameWork.Document";

	//打开注册表项,检查是否安装了Max 9.0程序
	long  ret0 = ( ::RegOpenKeyEx( REGISTER_ROOT, data_Set, 0, KEY_READ, &hRootKey ) );    

	if( ret0 != ERROR_SUCCESS )   
	{
		string msg("错误:无法打开有关的注册表项!请检查您是否已经安装了VRGIS浏览器！");

		::MessageBox(GetActiveWindow(), msg.c_str(), 
			"错误", MB_OK|MB_ICONASTERISK );     

		return false;
	} 

	return true;
}

//----------------------------------------------------------------------------
std::string vgModViewer::getVGViewerPath()
{
	if ( !hasVGViewerSetup() )
	{
		return std::string();
	}


	TCHAR*	pRegItem = vgModUtility::GetString( IDS_REGISTER_VALUE_VRGIS );
	LPCTSTR   data_Set = pRegItem;//"vgFrameWork.Document\\shell\\open\\command";
	HKEY hSubKey;
	::RegOpenKeyEx( REGISTER_ROOT, data_Set, 0, KEY_READ, &hSubKey ) ;

	char*   path_Get = new char[256];    
	DWORD    type = REG_SZ;
	DWORD    cbData = 256;  
	long ret1 = ::RegQueryValueEx( hSubKey, NULL, NULL, &type, (LPBYTE)path_Get, &cbData );  
	if ( ret1 != ERROR_SUCCESS )
	{
		return std::string();
	}

	return  std::string(path_Get);
#if 0
	exeFileName = exeFileName.substr(0, exeFileName.find_last_of(" ") );

	delete[] path_Get;
	return	exeFileName;
#endif
}

//----------------------------------------------------------------------------
std::string vgModViewer::configVGViewerINIFile()
{
	std::string exeVGViewer = getVGViewerPath();
	if ( exeVGViewer.empty() )
	{
		return false;
	}

	std::string exeFolder(exeVGViewer), fileName;
	exeFolder = exeFolder.substr(0, exeFolder.find_last_of("\\/")+1 );

	fileName = exeFolder + "\\data.ini" ;
	_iniFile = NULL;
	if( !_tfopen_s( &_iniFile, fileName.c_str() , _T("wt") ) )
	{
		_ftprintf( _iniFile,  _T("%s%c")  , getFileNameMod().c_str(), '\n' );
		
		writeBox3Text( );

		fclose( _iniFile );
	}
	else
	{
		fclose( _iniFile );
	}

	setFileNameConfig( fileName );
	return	fileName;
}

//----------------------------------------------------------------------------
bool	vgModViewer::openMODByVGViewer()
{
	std::string exeVGViewer = getVGViewerPath();
	if ( exeVGViewer.empty() )
	{
		return false;
	}

	configVGViewerINIFile();

	ShellExecute(NULL, "open",  exeVGViewer.c_str(), NULL, NULL, SW_SHOWNORMAL);

	return true;
}

//----------------------------------------------------------------
vgMath::CBox3 vgModViewer::getSceneBox()
{
	return	_sceneBox;
}

//----------------------------------------------------------------
bool vgModViewer::writeBox3Text()
{
	CBox3 box = getSceneBox().formatAsVGBox();

	CVector3& maxPoint = box.rightTop();
	CVector3& minPoint = box.leftBottom();

	for (int index = 0; index<3; index ++)
	{
		_ftprintf( _iniFile,  _T("%f%c")  , maxPoint.vert[index], '\n' );
	}
	for (int index = 0; index<3; index ++)
	{
		_ftprintf( _iniFile,  _T("%f%c")  , minPoint.vert[index], '\n' );
	}

	return true;
}

//----------------------------------------------------------------
void vgModViewer::setSceneBox( CBox3& box )
{
	_sceneBox = box;
}

//----------------------------------------------------------------
bool vgModViewer::resetViewer()
{
	bool bStatus1 = 0;

	if ( !_strFileNameMod.empty() )
	{
		bStatus1 = ::remove(_strFileNameMod.c_str());
		if ( bStatus1== -1 )
		{
			string msg("无法删除文件：");
			msg += _strFileNameMod;
			vgModUtility::MessageBox(msg);
		}

	}

	bool bStatus2 = 0;
	if ( !_strFileNameConfig.empty() )
	{
		bStatus2 = ::remove(_strFileNameConfig.c_str());
		if ( bStatus2== -1 )
		{
			string msg("无法删除文件：");
			msg += _strFileNameMod;
			vgModUtility::MessageBox(msg);
		}
	}

	return	(bStatus1+bStatus2)==0 ;
}
//----------------------------------------------------------------
