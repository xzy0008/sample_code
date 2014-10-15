



#include <vgStableHeaders.h>
#include <vgKernel/vgkPluginLoaderOnString.h>

#include <vgKernel/vgkPluginManager.h>
#include <vgConf/vgcoProjectConfig.h>
#include <vgConf/vgcoProjectConfigRegProxy.h>
#include <vgConf/vgcoExeConfig.h>
#include <vgConf/vgcoExeConfigRegProxy.h>


#define VGDLL_EXECONF				"ExeDllConfig"
#define VGDLL_EXECONF_TITLE			"ExeDllTitle"

#define VGDLL_EXECONF_NAMES_STD		"ExeDllNamesStd"

#define VGDLL_EXECONF_NAMES_PRO		"ExeDllNamesPro"

#define VGDLL_EXECONF_NAMES_STATIC	"ExeDllNamesStatic"

#define VGDLL_EXECONF_ENABLEPACKAGE	"ExeDllEnablePackage"


#define VGDLL_PATHCONF				"ExePathConfig"

#define VGDLL_PATHCONF_PATH_STD		"DllPathStd"
#define VGDLL_PATHCONF_PATH_PRO		"DllPathPro"


/**
在这里创建exe config
*/
//vgConf::ExeConfigRegProxy _exe_reg1( 
//									VGDLL_EXECONF , VGDLL_EXECONF_TITLE , "VR-GIS企业版 Platform 2.0" );
//
//vgConf::ExeConfigRegProxy _exe_reg2( 
//									VGDLL_EXECONF , VGDLL_EXECONF_NAMES , "" );
////VGDLL_EXECONF , VGDLL_EXECONF_NAMES , "vgTerritoryDLL;vgScriptMFCDLL" );
//
//vgConf::ExeConfigRegProxy _exe_reg3( 
//									VGDLL_EXECONF , VGDLL_EXECONF_ENABLEPACKAGE , "1" );
////VGDLL_EXECONF , VGDLL_EXECONF_NAMES , "vgTerritoryDLL;vgScriptMFCDLL" );



namespace vgKernel {
	
	
	
	 String PluginLoaderOnString::_apptitle = "";
	 bool PluginLoaderOnString::_enablePack = true;

	 String PluginLoaderOnString::_dllNamesStd = "";
	 String PluginLoaderOnString::_dllPathStd = "";
	 
	 String PluginLoaderOnString::_dllNamesPro = "";
	 String PluginLoaderOnString::_dllPathPro = "";
	 
	 String PluginLoaderOnString::_dllNamesStatic = "";

	 //----------------------------------------------------------------
	 String PluginLoaderOnString::load( bool bForceReLoad/* = false*/)
	{
#if 0//_DEBUG
		vgKernel::SystemUtility::showModelDialog( "PluginLoaderOnString::load" );
#endif
		if ( bForceReLoad )
		{
			vgKernel::PluginManager::getSingleton().uninitBeforeOpenGLDestroy();
		}


		//---加载动态库---------------------------------
		_enablePack = VG_EXECONF_GET_BOOL( 
			VGDLL_EXECONF,  
			VGDLL_EXECONF_ENABLEPACKAGE);;

		//VG_EXECONF_SET( 
		//	VGDLL_EXECONF,  
		//	VGDLL_EXECONF_ENABLEPACKAGE , _enablePack );


		_apptitle = VG_EXECONF_GET_STRING( 
			VGDLL_EXECONF,  
			VGDLL_EXECONF_TITLE);



		_dllNamesStd = VG_EXECONF_GET_STRING( 
			VGDLL_EXECONF,  
			VGDLL_EXECONF_NAMES_STD);
			//"vgDatabaseDLL;vgGisDLL;vgPlanDLL;vgScriptMFCDLL;vgShapeDLL;vgSolarDLL;vgSoundDLL;vgTerritoryDLL";

		_dllNamesPro = VG_EXECONF_GET_STRING( 
			VGDLL_EXECONF,  
			VGDLL_EXECONF_NAMES_PRO);

		_dllNamesStatic = VG_EXECONF_GET_STRING( 
			VGDLL_EXECONF,  
			VGDLL_EXECONF_NAMES_STATIC);

		
		_dllPathStd =  VG_EXECONF_GET_STRING( 
			VGDLL_PATHCONF,  
			VGDLL_PATHCONF_PATH_STD);
			//"plugin\Default"

		_dllPathPro =  VG_EXECONF_GET_STRING( 
			VGDLL_PATHCONF,  
			VGDLL_PATHCONF_PATH_PRO);
		//"stdplug"

		VGK_TRACE( _dllNamesStd );

		VG_EXECONF_SET( 
			VGDLL_EXECONF,  
			VGDLL_EXECONF_NAMES_STD , _dllNamesStd );


		VG_EXECONF_SET( 
			VGDLL_EXECONF,  
			VGDLL_EXECONF_NAMES_STATIC , _dllNamesStatic );


		VG_EXECONF_SET( 
			VGDLL_EXECONF,  
			VGDLL_EXECONF_NAMES_PRO , _dllNamesPro );

		String falseDLLs;
		String exePath = vgKernel::SystemUtility::getCurrentProcessPath();

		falseDLLs += load(_dllNamesStatic, exePath);
		
		if ( !_dllPathStd.empty() )
		{
			falseDLLs += load(_dllNamesStd, exePath + _dllPathStd);
		}
		
		if ( !_dllPathPro.empty() )
		{
			falseDLLs += load(_dllNamesPro, exePath + _dllPathPro);
		}

		return falseDLLs;
	}

	 
	 //----------------------------------------------------------------
	 String PluginLoaderOnString::load( String& dllNames,
		 String dllPath)
	{
		String falseDLLs;

		if (dllNames.empty())
		{
			vgKernel::SystemUtility::getFilesFromDirectory( dllPath, dllNames);

			dllPath.clear();
		}

		vgKernel::StringVector dllvec  =
			vgKernel::StringUtility::tokenize( dllNames , ";" ,false );

		if ( dllNames.empty() )
		{
			//falseDLLs = "该场景的插件";
			return falseDLLs;
		}

		vgKernel::StringVector::iterator iter = dllvec.begin();
		vgKernel::StringVector::iterator iter_end= dllvec.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			vgKernel::StringUtility::trim( *iter );

			String onedll = *iter;
			
			if( !dllPath.empty() )
			{
				onedll = dllPath + onedll;
#if _DEBUG
				onedll += "_Debug.dll";
#else
				onedll += "_Release.dll";
#endif
			}

			if( !testExist( onedll ) )
			{
				continue;
			}

			if( !testExtension( onedll ) )
			{
				continue;
			}

			if( !testVersionMap( onedll ) )
			{
				continue;
			}

			VGK_TRACE_SHORT("---------------------");
			VGK_TRACE_SHORT( onedll );

			if ( onedll.empty() == false )
			{

				//onedll = dllPath + onedll;

				bool loadok = VGK_DLL_LOAD( onedll.c_str() );

				if ( loadok == false )
				{
					VGK_TRACE_SHORT( "load :" + onedll  + "失败" );
					VGK_SHOW( "\n\tload :" + onedll  + "失败, 找不到dll文件\n\n" );
					falseDLLs += onedll ;
					falseDLLs += '\n' ;

				}

			}

			VGK_TRACE_SHORT("---------------------");
		}

		return falseDLLs;

	}

	 //----------------------------------------------------------------
	 String& PluginLoaderOnString::getAppTitle()
	 {
		return _apptitle;
	 }

	 //----------------------------------------------------------------
	 bool PluginLoaderOnString::getEnablePack()
	 {
		return _enablePack;
	 }

	 //----------------------------------------------------------------
	 bool PluginLoaderOnString::testVersionMap( String dllName )
	 {
		
		 StringVector filters;
		 filters.push_back("debug");
		 filters.push_back("release");

		 String exeName = vgKernel::SystemUtility::getCurrentProcessName();
		 vgKernel::StringUtility::toLowerCase( exeName );

		 dllName = vgKernel::StringUtility::getFilenameFromAbsolutePath(dllName);
		 vgKernel::StringUtility::toLowerCase( dllName );

		 for ( StringVector::iterator itr = filters.begin();
			 itr != filters.end(); itr ++ )
		 {
			 int nIndexExe = exeName.find( *itr );
			 int nIndexDll = dllName.find( *itr );
			 if ( String::npos == nIndexExe )
			 {
				 continue;
			 }
			 else
			 {
				 if ( String::npos != nIndexDll )
				 {
					 return true;
				 }
				 else
				 {
					return false;
				 }
			 }

		 }

		 return true;
	 }

	 //----------------------------------------------------------------
	 bool PluginLoaderOnString::testExist( const String& filepath_abs_or_not )
	 {
		 if ( filepath_abs_or_not.empty() )
		 {
			 return false;
		 }

		 String dllName = filepath_abs_or_not;
		 String dllPath = 
			 vgKernel::StringUtility::getPathFromAbsoluteFilename(dllName);

		 if ( dllPath.empty() )
		 {
			 dllPath = vgKernel::SystemUtility::getCurrentProcessPath();
			 dllName = dllPath + dllName;
		 }

		 if ( !vgKernel::SystemUtility::checkFileExist( dllName ) )
		 {
			 std::ostringstream os;
			 os << "无法找到DLL:" 
				 << dllName.c_str();
			 //AfxMessageBox( os.str().c_str() );
			 vgKernel::SystemUtility::showModelDialog( os.str());

			 return false;
		 }

		 return true;
	 }

	 bool PluginLoaderOnString::testExtension( String dllName )
	 {
		 String ext = vgKernel::StringUtility::
			 getFileExtension(dllName);

		 vgKernel::StringUtility::
			 toLowerCase(ext);

		 if ( ext == String("dll"))
		 {
			 return true;
		 }
		 else
		 {
			 return false;
		 }
	 }
}// end of namespace vgKernel
