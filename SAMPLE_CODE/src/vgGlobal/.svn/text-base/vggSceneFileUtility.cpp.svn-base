


#include <vgStableHeaders.h>
#include <vgGlobal/vggSceneFileUtility.h>

#include <vgGlobal/vggGlobalConsole.h>
#include <vgGlobal/vggGlobalUtility.h>
#include <vgGlobal/vggVgmodUtility.h>
#include <vgGlobal/vggVgshpUtility.h>
#include <vgGlobal/vggVgcamUtility.h>
#include <vgGlobal/vggVgmeshUtility.h>
#include <vgGlobal/vggVgterrainUtility.h>

#include <vgKernel/vgkRendererManager.h>
#include <vgKernel/vgkPluginManager.h>
#include <vgKernel/vgkPluginLoaderOnString.h>
#include <vgKernel/vgkSelectManager.h>

#include <vgConf/vgcoProjectConfig.h>
#include <vgConf/vgcoExeConfig.h>

#include <DlgSelectFlash.h>
#include <AutoLoadDialog.h>
#include <vgMovingManager.h>

#include <vgMesh/vgmMeshManager.h>
#include <vgTerritory/vgtDefinition.h>

#define VGDLL_PROJCONF			"ProjDllConfig"

#define VGDLL_PROJCONF_NAMES	"ProjDllNames"
#define VGDLL_PROJCONF_PATH		"ProjDllPath"

#define VGDATA_PATHCONF					"DataPathConfig"
#define VGDATA_PATHCONF_FLASH_PATH		"FlashPath"

#define VGDATA_FILECONF					"DataFileConfig"
#define VGDATA_FILECONF_USERFLASH_NAME	"UserFlashName"


namespace vgGlobal{
	

	String SceneFileUtility::apptitle = "";
	String SceneFileUtility::dllnames = "";
	String SceneFileUtility::dllpath = "\\ProjectPlugin\\";

	/************************************************************************/
	/* 静态全局变量初始化                                                   */
	/************************************************************************/

	bool          SceneFileUtility::_sceneOpened = false;
	String        SceneFileUtility::_currentScenePath = "";
	String		  SceneFileUtility::_currentVgimgPath = "";
	String		  SceneFileUtility::_currentVgPath = "";

	unsigned int  SceneFileUtility::_uiUpdateTime = 0;
	bool          SceneFileUtility::_isCutBlock = false;
	
	/************************************************************************/
	/* 对外公共接口                                                         */
	/************************************************************************/

	//----------------------------------------------------------------
	bool SceneFileUtility::openSceneFile()
	{
		vgKernel::StringVector strExts;
		strExts.push_back("vg");

		 vgKernel::StringVector filePaths = vgKernel::SystemUtility::getFilesOpenByDialog(strExts);

  		if(filePaths.empty())
  		{
  			return false;
  		}

		LARGE_INTEGER nStartTime;
		LARGE_INTEGER nEndTime;
		LARGE_INTEGER nFrenquece;

		QueryPerformanceCounter(&nStartTime);

//   		string path;
//    		path = "\\\\211.64.136.16\\vg\\VRGIS_普陀\\普陀.vg";
// 		  		string path;
// 		   		path = "\\\\211.64.136.16\\vg\\VRGIS_emei2\\emei2.vg";

		vgGlobal::SceneFileUtility::setUpdateTime( 1 );
		vgGlobal::SceneFileUtility::openScene( filePaths[0] /*path*/);

		QueryPerformanceCounter(&nEndTime);
		QueryPerformanceFrequency(&nFrenquece);

		int time = (nEndTime.QuadPart - nStartTime.QuadPart) * 1000 / nFrenquece.QuadPart;

		char result[256];

		sprintf(result, "load time %f \n", (float)time / 1000);

		VGK_SHOW(result);


		return true;
	}

	//----------------------------------------------------------------
	bool SceneFileUtility::saveSceneFile( bool bSaveMode /* = false */ )
	{
		vgKernel::StringVector strExts;
		strExts.push_back("vg");

		String strSavePath = vgKernel::SystemUtility::getFileSaveByDialog(strExts);

		if ( strSavePath.empty() )
		{
			return  false;
		}
		
		// 用于切块保存场景而加入的类型参数， 此步重要
		vgGlobal::ModUtility::setSaveMode( bSaveMode );
		vgGlobal::MeshUtility::setSaveMode( bSaveMode );
		vgGlobal::TerrainUtility::setSaveMode( bSaveMode );

		vgGlobal::SceneFileUtility::setUpdateTime( 1 );
		
		vgGlobal::SceneFileUtility::saveScene( strSavePath );

		return true;
	}

	//----------------------------------------------------------------
	bool SceneFileUtility::importFiles()
	{
		vgKernel::StringVector strExts;
		strExts.push_back("vgm");
		strExts.push_back("vgi");
		strExts.push_back("mod");
		strExts.push_back("ms3d");
		strExts.push_back("vcr");
		strExts.push_back("shp");
		strExts.push_back("vmd");

		vgKernel::StringVector strVec = vgKernel::SystemUtility::getFilesOpenByDialog(strExts);

		if ( strVec.empty() )
		{
			return false;
		}

		vgGlobal::SceneFileUtility::importFiles( strVec );
	
		return true;
	}

	//----------------------------------------------------------------
	bool SceneFileUtility::exportFile()
	{
		vgKernel::StringVector strExts;
		strExts.push_back("vgm");
		String filePath = vgKernel::SystemUtility::getFileSaveByDialog(strExts);

		if ( filePath.empty() )
		{
			return false;
		}

		vgGlobal::SceneFileUtility::exportFile( filePath );

		return true;
	}

	//----------------------------------------------------------------
	bool SceneFileUtility::importMs3dFile()
	{
		vgKernel::StringVector strExts;
		strExts.push_back("ms3d");
		vgKernel::StringVector strVec = vgKernel::SystemUtility::getFilesOpenByDialog(strExts);

		vgGlobal::SceneFileUtility::importFiles( strVec );

		return true;
	}

	/************************************************************************/
	/* 以下为私有静态成员部分                                               */
	/************************************************************************/

	//----------------------------------------------------------------
	unsigned int SceneFileUtility::getUpdateTime()
	{
		return _uiUpdateTime;
	}

	//----------------------------------------------------------------
	void SceneFileUtility::setUpdateTime( unsigned uiUpdateTime )
	{
		_uiUpdateTime = uiUpdateTime;
	}

	//----------------------------------------------------------------
	bool SceneFileUtility::getSceneOpenedFlag()
	{
		return _sceneOpened;
	}

	//----------------------------------------------------------------
	void SceneFileUtility::setSceneOpenedFlag( const bool& opened )
	{
		_sceneOpened = opened;
	}

	//----------------------------------------------------------------
	bool SceneFileUtility::openScene( const String& vg_filepath )
	{
		_currentScenePath = 
			vgKernel::StringUtility::getPathFromAbsoluteFilename(vg_filepath);

		_currentVgPath = vg_filepath;

		int index = vg_filepath.find_first_of('.');

		if (index != string::npos)
		{
			_currentVgimgPath = vg_filepath.substr(0, index+1);
			_currentVgimgPath += "vgimg";
		}


		if ( !openSceneBegin(vg_filepath) )
		{
			return false;
		}

		if ( !openSceneImpl(vg_filepath) )
		{
			return false;
		}

		//////////////////////////////////////////////////////////////////////////
		string skypath = _currentScenePath + "Data\\Texture\\sky.MOD";
		string originpath = _currentScenePath + "Data\\Texture\\negx.jpg";
		string dustpath =  _currentScenePath + "Data\\Texture\\negx2.jpg";
		string lastsunpath =  _currentScenePath + "Data\\Texture\\negx3.jpg";

		vgCore::MovingManager::getSingleton().Initdustsun(skypath,  originpath, dustpath, lastsunpath );
		//////////////////////////////////////////////////////////////////////////

		return openSceneEnd(vg_filepath);
	}

	//----------------------------------------------------------------
	bool SceneFileUtility::openSceneBegin( const String& vg_filepath )
	{
		if ( getSceneOpenedFlag() )
		{
#if VGK_LANG_CHS
			AfxMessageBox("无法多次重复打开场景, 请重置后重新打开！");
#else
			AfxMessageBox("Can not reopen the same scene!");
#endif
			return false;
		}

		String ext = vgKernel::StringUtility::getFileExtension(vg_filepath);
		if ( ext != String("vg") )
		{
#if VGK_LANG_CHS
			AfxMessageBox("不是场景文件, 请重新打开vg文件！");
#else
			AfxMessageBox("Please open file whose extention is vg!");
#endif
			return false;
		}


		// 从配置文件读取DLL插件模块的配置信息
		invalidateUserConfig( vg_filepath );
		
		// 从配置文件读取其他模块的配置信息
		vgGlobal::GlobalConsole::getSingleton().readProject( vg_filepath );


		std::ostringstream o;
		o	<< "\n-----------------------------------------------------------\n"; 
#if VGK_LANG_CHS
		o << "\t\t正在执行 打开VG操作:\n";
#else
		o << "\t\tOpenning Scene:\n";
#endif
		o	<< "-----------------------------------------------------------\n" ;
		VGK_SHOW( o.str() );
		o.str("");

		return true;
	}

	//----------------------------------------------------------------
	bool SceneFileUtility::openSceneImpl( const String& vg_filepath )
	{

		_currentScenePath = 
			vgKernel::StringUtility::getPathFromAbsoluteFilename(vg_filepath);

	
		// Part 0：数据库配置文件 *.vgp	
		// 		String	filePath = vgKernel::StringUtility::getPathFromAbsoluteFilename(vg_filepath);
		// 		vgDatabase::ProfileManager::getSingleton().loadRenderProfile(filePath);

		// Part 1：vg、vgimg
		bool bStatus = false;
		bool bReadDirectly = vgMod::ModUtility::getFlagReadDirectly();
		if ( bReadDirectly )
		{
			bStatus = vgGlobal::ModUtility::importVgFileDirectly( vg_filepath );
		}
		else
		{
			bStatus = vgGlobal::ModUtility::importVgFile( vg_filepath );
		}
		if( bStatus )
		{
			std::ostringstream o;
#if VGK_LANG_CHS
			o << "\t成功打开文件:"<< vg_filepath << " \n";
#else
			o << "\tSuccess: "<< vg_filepath << " \n";
#endif
			VGK_SHOW( o.str() );
		}
		else
		{
			std::ostringstream oEnd;
#if VGK_LANG_CHS
			oEnd << "\t打开文件:"<< vg_filepath << " 失败\n";
#else
			oEnd << "\tFail: "<< vg_filepath << " \n";
#endif
			VGK_SHOW( oEnd.str() );

			return false;
		}


		// Part 2：vgm、vgi
		//vgGlobal::GlobalFacade::getSingleton().importModelAndImage(vg_filepath);
		vgGlobal::MeshUtility::importModelAndImage(vg_filepath);


		// Part 3: plugin
		//invalidatePluginConfig(vg_filepath);


		return true;
	}

	//----------------------------------------------------------------
	bool SceneFileUtility::openSceneEnd( const String& vg_filepath )
	{
		// Part 3：重新构树
		vgGlobal::GlobalConsole::getSingleton().readProjectEnd( vg_filepath );

		vgKernel::RendererManager::getSingleton().invalidate();

		setSceneOpenedFlag( true );

		std::ostringstream o;

#if VGK_LANG_CHS
		o << "...\n" << "成功打开场景"  << " \n";
#else
		o << "...\nSuccess: " << "\n";
#endif			
		VGK_SHOW( o.str() );
		o.str("");


		o<< "-----------------------------------------------------------\n"; 
#if VGK_LANG_CHS
		o<< "\t\t完成执行 打开VG操作\n";
#else
		o<< "\t\tOpen Scene Completed!\n";
#endif
		o<< "-----------------------------------------------------------\n" ;
		VGK_SHOW( o.str() );
		o.str("");




		vgKernel::SystemUtility::setCurrentDirectory(vg_filepath);

		//----------progress position------------------//
		CAutoLoadDialog::SetPos(100);
		//---------------------------------------------//

		return true;
	}

	//----------------------------------------------------------------
	bool SceneFileUtility::saveScene( const String& save_vg_path )
	{
		if ( !saveSceneBegin(save_vg_path) )
		{
			return false;
		}

		if ( !saveSceneImpl(save_vg_path ) )
		{
			return false;
		}

		saveSceneEnd(save_vg_path);

		return true;
	}

	//----------------------------------------------------------------
	bool SceneFileUtility::saveSceneBegin( const String &save_vg_path )
	{

		String ext = vgKernel::StringUtility::getFileExtension(save_vg_path);
		if ( ext != String("vg") )
		{
#if VGK_LANG_CHS
			AfxMessageBox("不是场景文件, 请保存为vg文件！");
#else
			AfxMessageBox("Please save file whose extention is vg!");
#endif
			return false;
		}


		std::ostringstream o;

#if VGK_LANG_CHS
		o	<< "-----------------------------------------------------------\n" 
			<< "\t\t正在执行 保存场景操作:\n"
			<< "-----------------------------------------------------------\n" ;
#else
		o	<< "-----------------------------------------------------------\n" 
			<< "\t\tSaving Scene:\n"
			<< "-----------------------------------------------------------\n" ;
#endif
		VGK_SHOW( o.str() );
		o.str("");

#if VGK_LANG_CHS
		o << "\n开始保存场景文件... \n";
#else
		o << "\nBegin to save scene files... \n";
#endif
		VGK_SHOW( o.str() );
		o.str("");

		return true;
	}

	//----------------------------------------------------------------
	bool SceneFileUtility::saveSceneImpl( const String& save_vg_path )
	{
		String folderpath = 
			vgKernel::StringUtility::getPathFromAbsoluteFilename( save_vg_path ) + 
			"\\VRGIS_" + 
			vgKernel::StringUtility::getFilenameWithoutExtFromAbsPath( save_vg_path ) + 
			"\\" + vgKernel::StringUtility::getFilenameFromAbsolutePath( save_vg_path );

		// Part 1：vg、vgimg
		if( vgGlobal::ModUtility::exportVgFile( save_vg_path ) )
		{
			std::ostringstream o;
#if VGK_LANG_CHS
			o << "\t成功保存文件:"<< folderpath << " \n";
#else
			o << "\tSuccess: "<< strSavePath << " \n";
#endif
			VGK_SHOW( o.str() );
		}
		else
		{
			std::ostringstream oEnd;
#if VGK_LANG_CHS
			oEnd << "\t保存文件:"<< folderpath << " 失败\n";
#else
			oEnd << "\tFail: "<< strSavePath << " \n";
#endif
			VGK_SHOW( oEnd.str() );

			return false;
		}


		vgGlobal::GlobalConsole::getSingleton().saveProject( folderpath );

		//	Part 2：vgm、vgi
		vgGlobal::MeshUtility::saveModelAndImage( folderpath );
		
		// 如果是切块保存模式保存地形
		if ( vgGlobal::ModUtility::getSaveMode() )
		{
			vgGlobal::TerrainUtility::saveVtrAndVgi( folderpath );
		}

		//	Part 3：城市规划数据写入vg、MOD地形
		//vgGlobal::GlobalFacade::getSingleton().writeExtraDataToVG( strSavePath );

		//	Part 4：数据库配置文件 *.vgp		
		//		String	filePathVgp = vgKernel::StringUtility::getPathFromAbsoluteFilename(strSavePath);
		//		vgDatabase::ProfileManager::getSingleton().SaveRendererProfile(filePathVgp);


		//	Part 5: 矢量数据写 *.vsg
		//String filePathVsg = strSavePath.substr( 0 , strSavePath.find_last_of(".") );
		//filePathVsg += ".vsg";	
		//vgVector::VectorManager::getSingleton().writeLayersToVSGFile(filePathVsg);

		return true;
	}

	//----------------------------------------------------------------
	void SceneFileUtility::saveSceneEnd( const String& save_vg_path )
	{
#if VGK_LANG_CHS
		MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd , 
			"保存场景操作成功!" , "提示" , MB_OK );
#else
		MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd , 
			"Save scene successful!" , "Tips" , MB_OK );
#endif



		std::ostringstream o;
#if VGK_LANG_CHS
		o << "...\n" << "成功保存场景"  << " \n";
#else
		o << "...\nSuccess: " << "\n";
#endif			
		VGK_SHOW( o.str() );
		o.str("");



#if VGK_LANG_CHS
		o	<< "-----------------------------------------------------------\n" 
			<< "\t\t完成执行 保存场景操作:\n"
			<< "-----------------------------------------------------------\n" ;
#else
		o	<< "-----------------------------------------------------------\n" 
			<< "\t\tSave Scene Completed!\n"
			<< "-----------------------------------------------------------\n" ;
#endif
		VGK_SHOW( o.str() );

		vgKernel::SystemUtility::setCurrentDirectory(save_vg_path);
	}

	//----------------------------------------------------------------
	bool SceneFileUtility::importFiles( const vgKernel::StringVector& strvec, bool bSpecial/* = false*/)
	{
		//------------------------------------------
		// 开始导入
		//------------------------------------------
		if( strvec.empty() )
			return false;

		String ext = vgKernel::StringUtility::getFileExtension( strvec[0] );

		std::ostringstream o;
		o	<< "-----------------------------------------------------------\n"; 
#if VGK_LANG_CHS
		o << "\t\t正在执行 导入" << ext << "操作:\n";
#else
		o << "\t\tImporting "<< ext << ":\n";
#endif
		o	<< "-----------------------------------------------------------\n" ;
		VGK_SHOW( o.str() );


		bool ret = true;

		vgKernel::StringVector::const_iterator iter = strvec.begin();
		vgKernel::StringVector::const_iterator iter_end = strvec.end();


		for ( ; iter != iter_end ; ++ iter )
		{
			if ( importGivenFile( *iter , bSpecial) == false )
			{
				ret = false;
			}

		}// for

		// 重新构树
		vgKernel::RendererManager::getSingleton().invalidate();


		std::ostringstream oEnd;
		oEnd<< "-----------------------------------------------------------\n"; 
#if VGK_LANG_CHS
		oEnd<< "\t\t完成执行 导入"<< ext << "操作!\n";
#else
		oEnd<< "\t\tImport "<< ext << " Completed!\n";
#endif
		oEnd<< "-----------------------------------------------------------\n" ;
		VGK_SHOW( oEnd.str() );

		vgKernel::SystemUtility::setCurrentDirectory( strvec[0] );

		return ret;
	}

	//----------------------------------------------------------------
	bool SceneFileUtility::importGivenFile( const String& impFile, bool bSpecial/* = false*/ )
	{
		if ( importFileImpl( impFile , bSpecial) == true )
		{	
			std::ostringstream oEnd;
			oEnd << "\t成功导入文件:"<< impFile << " \n";
			VGK_SHOW( oEnd.str() );
			return true;
		}
		else
		{
			std::ostringstream oEnd;
			oEnd << "\t导入文件:"<< impFile << " 失败\n";
			VGK_SHOW( oEnd.str() );
			return false;
		}
	}	

	//----------------------------------------------------------------
	bool SceneFileUtility::importFileImpl( const String& filename, bool bSpecial/* = false*/ )
	{
		String	fileExt = vgKernel::StringUtility::getFileExtension( filename );

		vgKernel::StringUtility::toLowerCase(fileExt);

		if ( fileExt == "vgm")
		{
			//return vgGlobal::GlobalFacade::getSingleton().importModelFileOnly( filename );
			return vgGlobal::MeshUtility::importModelFileOnly( filename );
		}/*
		else if ( fileExt == "vg" )
		{
			return openScene( filename );
		}*/
		else if ( fileExt == "vgi" )
		{
			//return vgGlobal::GlobalFacade::getSingleton().importImageFileOnly( filename );
			return vgGlobal::MeshUtility::importImageFileOnly( filename );
		}
		else if ( fileExt == "mod" )
		{
			return vgGlobal::ModUtility::importModFile( filename );
		}
		else if ( fileExt == "ms3d" )
		{
			return vgCore::MovingManager::getSingleton().addSkelecton( filename );
		}
		else if ( fileExt == "vcr" )
		{
			return vgGlobal::CamUtility::importVcrAni( filename );
		}
		else if ( fileExt == "vtr" )
		{
			//return vgGlobal::GlobalFacade::getSingleton().importVtrFile( filename );
			return vgGlobal::GlobalUtility::importVtrFile( filename );
		}/*
		else if ( fileExt == "wav" )
		{
			return vgGlobal::GlobalFacade::getSingleton().import3DMusicFile( filename );
		}
		else if ( fileExt == "mp3" )
		{
			return vgGlobal::GlobalFacade::getSingleton().importBackgroundMusicFile( filename );
		}*/
		else if ( fileExt == "vmd" )
		{
			//return vgGlobal::GlobalFacade::getSingleton().importVmdFileOnly( filename );
			return vgGlobal::GlobalUtility::importVmdFileOnly( filename );
		}
		else if ( fileExt == "shp" )
		{
			return vgGlobal::ShapeUtility::importShpFile( filename ,bSpecial);
		}

		return false;
	}

	//----------------------------------------------------------------
	bool SceneFileUtility::exportFile( const String& impFile )
	{
		if ( exportFileImpl( impFile ) == true )
		{	
			std::ostringstream oEnd;
			oEnd << "\t成功导出文件:"<< impFile << " \n";
			VGK_SHOW( oEnd.str() );

			vgKernel::SystemUtility::setCurrentDirectory(impFile);

			return true;
		}
		else
		{
			std::ostringstream oEnd;
			oEnd << "\t导出文件:"<< impFile << " 失败\n";
			VGK_SHOW( oEnd.str() );
			return false;
		}
	}	

	//----------------------------------------------------------------
	bool SceneFileUtility::exportFileImpl( const String& filename )
	{
		String	fileExt = vgKernel::StringUtility::getFileExtension( filename );

		vgKernel::StringUtility::toLowerCase(fileExt);

		//目前文件--导出功能只支持支出vgm文件
		if ( fileExt == "vgm")
		{
			//return vgGlobal::GlobalFacade::getSingleton().saveModelAndImage( filename );
			return vgGlobal::MeshUtility::saveModelAndImage( filename );
		}/*
		else if ( fileExt == "vgi" )
		{
			return vgGlobal::GlobalFacade::getSingleton().importImageFileOnly( filename );
		}
		else if ( fileExt == "mod" )
		{
			//return vgMod::ModUtility::AddModelToScene( filename );
		}
		else if ( fileExt == "ms3d" )
		{
			return vgCore::MovingManager::getSingleton().addSkelecton( filename );
		}
		else if ( fileExt == "vcr" )
		{
			return vgGlobal::CamUtility::exportVcrAni( filename );
		}
		else if ( fileExt == "shp" )
		{
			//vgShape::DataSourcePtr psource = 
			//	vgShape::ShapeManager::getSingleton().openShapeFileWithUpdateUI(filename );

			//return !psource.isNull();

			assert(0);

			//return vgVector::VectorManager::getSingleton().open( filename );
		}*/

		return false;
	}

	//----------------------------------------------------------------
	bool SceneFileUtility::openSceneDirectly( const String& vg_filepath )
	{
		_currentScenePath = 
			vgKernel::StringUtility::getPathFromAbsoluteFilename(vg_filepath);

		//	Part 1：配置信息
		//vgGlobal::GlobalConsole::getSingleton().readProject( vg_filepath );

		// Part 2：vg、vgimg
		if( !vgGlobal::ModUtility::importVgFileDirectly( vg_filepath ) )
		{
			return false;
		}
#if 0
		// Part 3：vgm、vgi（无改变，暂时无需转换）
		vgGlobal::GlobalFacade::getSingleton().importModelAndImage(vg_filepath);
#endif
		return true;
	}

	//----------------------------------------------------------------
	bool SceneFileUtility::saveSceneDirectly( const String& save_vg_path )
	{
		String folderpath = 
			vgKernel::StringUtility::getPathFromAbsoluteFilename( save_vg_path ) + 
			"\\VRGIS_" + 
			vgKernel::StringUtility::getFilenameWithoutExtFromAbsPath( save_vg_path ) + 
			"\\" + vgKernel::StringUtility::getFilenameFromAbsolutePath( save_vg_path );

		// Part 1：vg、vgimg
		if( !vgGlobal::ModUtility::exportVgFileDirectly( save_vg_path ) )
		{
			return false;
		}

		//	Part 2：配置信息
		//vgGlobal::GlobalConsole::getSingleton().saveProject( folderpath );
#if 0
		//	Part 3：vgm、vgi（无改变，暂时无需转换）
		vgGlobal::GlobalFacade::getSingleton().saveModelAndImage( folderpath );
#endif
		return true;

	}

	//----------------------------------------------------------------
	bool SceneFileUtility::resetScene()
	{

		vgCore::ArchiveManager::getSingleton().reset();
		vgCore::TextureManager::getSingleton().reset();
		vgMod::NodeManager::getSingleton().reset();
		vgCore::MovingManager::getSingleton().reset();


		//vgkernel

		//vgKernel::SingletonManager::reset();

		vgKernel::PluginManager::getSingleton().resetAllPlugins();


		//		vgMesh::MeshManager::getSingleton().reset();
		// 
		// 		vgShape::ShapeManager::getSingleton().reset();
		// 
		// 		vgDatabase::DatabaseManager::getSingleton().reset();
		// 		//vgDatabase::ProfileManager::getSingleton().reset(); need to rewrite
		// 
		//  		vgKernel::SelectManager::getSingleton().reset();
		// // 
		// // 		vgTerritory::TerrainManager::getSingleton().dropTerrianData();
		// 		vgFont::FontManager::getSingleton().reset();
		// 
		// 		vgKernel::CoordSystem::getSingleton().reset();
		// 
		// 		vgImage::TextureManager::getSingleton().reset();
		// 
		// 		vgImage::ImageManager::getSingleton().reset();
		// 
		// 		vgCam::CamManager::getSingleton().reset();
		// 
		// 		vgSound::SoundManager::getSingleton().reset();
		// 
		// 		vgKernel::RendererManager::getSingleton().reset();
		// 
		// 		vgScript::ScriptManager::getSingleton().reset();
		// 
		// 		//vgLogo::LogoManager::getSingleton().reset();
		// 
		// 		vgKernel::InputSystem::getSingleton().reset();
		// 
		// 		vgMod::ModMisc::getSingleton().reset();

		//vgUIController

		//vgUI::UIController::getSingleton().reset();


		return true;
	}
	//----------------------------------------------------------------
	bool SceneFileUtility::publishScene( const String& publish_vg_path, const String& publish_UI_path )
	{
		//////////////////////////////////////////////////////////////////////////
		// 1、定位并新建打包目录
		String FilePathName = publish_vg_path;

		String FileName = vgKernel::StringUtility::getFilenameFromAbsolutePath(publish_vg_path);

		String FileFolderPath = vgKernel::StringUtility::getPathFromAbsoluteFilename(publish_vg_path);

		String FileNameWithoutExt =  vgKernel::StringUtility::getFilenameWithoutExtension(FileName); 
		
		char tempSystemPath[MAX_PATH]; 
		GetTempPath(MAX_PATH,tempSystemPath);
		
		String currentDirectory = tempSystemPath;

		String currentProcessName = vgKernel::SystemUtility::getCurrentProcessName();

		String processDirectory = vgKernel::SystemUtility::getCurrentProcessPath();

		String vgExeFileName = "VRGIS_" + FileNameWithoutExt;

		String tempFolder =  currentDirectory + vgExeFileName;

		std::ostringstream o;

		// 定位并新建打包目录
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// 2、新建临时目录并保存vg文件

		String saveFileName = currentDirectory + FileNameWithoutExt + ".vg"; 

		if (!saveSceneImpl(saveFileName))
		{
			MessageBox(NULL,"保存vg文件出错，结束打包操作！","",MB_OK | MB_TOPMOST );
			return false;
		}

		// 保存vg文件
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// 3、在临时目录新建并保存打包配置文件（sescript、data.ini等）

		FILE* iniFile;
		String fileName = processDirectory + "sescript" ;
		String strLine;
		if( !_tfopen_s( &iniFile, fileName.c_str() , _T("wt") ) )
		{
			strLine =  "Silent=1" ;
			_ftprintf( iniFile,  _T("%s%c")  , strLine.c_str(), '\n' );
			strLine =  "Overwrite=1" ;
			_ftprintf( iniFile,  _T("%s%c")  , strLine.c_str(), '\n' );
			strLine =  "TempMode" ;
			_ftprintf( iniFile,  _T("%s%c")  , strLine.c_str(), '\n' );
			strLine = "Setup=" + vgExeFileName + "\\" + currentProcessName;
			_ftprintf( iniFile,  _T("%s")  , strLine.c_str() );
			fclose( iniFile );
		}
		else
		{
			fclose( iniFile );
		}

		fileName = tempFolder + "\\data.ini" ;
		if( !_tfopen_s( &iniFile, fileName.c_str() , _T("wt") ) )
		{
			strLine = FileNameWithoutExt + ".vg";
			_ftprintf( iniFile,  _T("%s%c")  , strLine.c_str(), '\n' );
			fclose( iniFile );
		}
		else
		{
			fclose( iniFile );
		}
		// 新建并保存打包配置文件（sescript、data.ini等）
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// 4、复制其它文件（路径动画、背景音效、数据库文件、打包必需文件等）至临时目录
#if VGK_LANG_CHS
		o << "\n开始复制文件，请稍侯... \n";
#else
		o << "\nBegin to copy files... \n";
#endif
		VGK_SHOW( o.str() );
		o.str("");

		String flashPath =  VG_EXECONF_GET_STRING( 
			VGDATA_PATHCONF,  
			VGDATA_PATHCONF_FLASH_PATH);

		String UIFileName = vgKernel::StringUtility::getFilenameFromAbsolutePath(publish_UI_path);
		String destFile = tempFolder + "\\" + flashPath + UIFileName;
		String srcFile  = publish_UI_path;
		vgKernel::SystemUtility::copyFile(srcFile, destFile);

		VG_EXECONF_SET( 
			VGDATA_FILECONF,
			VGDATA_FILECONF_USERFLASH_NAME,
			UIFileName);

		VG_EXECONF_SAVE();

		String destDirectory = tempFolder;
		String srcDirectory  = processDirectory;
		vgKernel::SystemUtility::copyDirectory(destDirectory, srcDirectory);

		// 复制其它文件（路径动画、背景音效、数据库文件、打包必需文件等）
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// 5、打包临时目录开始...

#if VGK_LANG_CHS
		o << "\n开始执行打包过程.此过程可能需要几分钟，请稍侯... \n";
#else
		o << "\nBegin to pack files... \n";
#endif
		VGK_SHOW( o.str() );
		o.str("");

		String sourceDir = processDirectory + "Default.SFX";
		String destinDir = currentDirectory + "Default.SFX";
		vgKernel::SystemUtility::copyFile(sourceDir, destinDir);

		sourceDir = processDirectory + "VRGIS.ico";
		destinDir = currentDirectory + "VRGIS.ico";
		vgKernel::SystemUtility::copyFile(sourceDir, destinDir);

		sourceDir = processDirectory + "sescript";
		destinDir = currentDirectory + "sescript";
		vgKernel::SystemUtility::copyFile(sourceDir, destinDir);


		String zipParameter = String("a -m0 -inul -idp -sfxDefault.SFX -ibck -iiconVRGIS.ico -zsescript ")
			+ vgExeFileName + " "
			+ vgExeFileName;

		CFile fp;
		String dllFileName = processDirectory + "mfcm80chs.dll";
		if (!fp.Open( dllFileName.c_str()  , CFile::modeRead))
		{
			MessageBox(NULL,"没有找到打包软件，失败！","",MB_OK | MB_TOPMOST );
			fp.Close();
			return false;
		}
		fp.Close();

		String zipFileName = processDirectory + "vgZip.exe";
		vgKernel::SystemUtility::moveFile( dllFileName, zipFileName );

		if (!fp.Open( zipFileName.c_str()  , CFile::modeRead))
		{
			MessageBox(NULL,"没有找到打包软件，失败！","",MB_OK | MB_TOPMOST );
			fp.Close();
			return false;
		}
		fp.Close();

		SHELLEXECUTEINFO ShExecInfo = {0};
		ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
		ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
		ShExecInfo.hwnd = NULL;
		ShExecInfo.lpVerb = NULL;
		ShExecInfo.lpFile = zipFileName.c_str();             
		ShExecInfo.lpParameters = zipParameter.c_str();     
		ShExecInfo.lpDirectory = currentDirectory.c_str();
		ShExecInfo.nShow = SW_SHOWNORMAL;
		ShExecInfo.hInstApp = NULL;       
		ShellExecuteEx(&ShExecInfo);

		long waitStatus = WaitForSingleObject(ShExecInfo.hProcess,INFINITE);

		if ( waitStatus )
		{
			MessageBox(NULL,"打包失败！","",MB_OK | MB_TOPMOST );
			vgKernel::SystemUtility::moveFile( zipFileName, dllFileName );
			vgKernel::SystemUtility::removeDirectory( tempFolder );
			return false;
		}

		vgKernel::SystemUtility::moveFile( zipFileName, dllFileName );

		// 打包结束
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// 6、拷贝exe包至目的目录，删除临时目录 及 exe包

#if VGK_LANG_CHS
		o << "\n正在删除临时文件... \n";
#else
		o << "\ndeleting temp files... \n";
#endif
		VGK_SHOW( o.str() );
		o.str("");

		String srcFileName = currentDirectory + vgExeFileName + ".exe";

		String desFileName = FileFolderPath + vgExeFileName + ".exe";

		vgKernel::SystemUtility::copyFile( srcFileName, desFileName );

		vgKernel::SystemUtility::removeFile( srcFileName, false );

		vgKernel::SystemUtility::removeDirectory( tempFolder );
		
		String filename = currentDirectory + "Default.SFX";
		vgKernel::SystemUtility::removeFile(filename,false);
		filename = currentDirectory + "VRGIS.ico";
		vgKernel::SystemUtility::removeFile(filename,false);
		filename = currentDirectory + "sescript";
		vgKernel::SystemUtility::removeFile(filename,false);

		//拷贝exe包至目的目录，删除临时目录 及 exe包
		//////////////////////////////////////////////////////////////////////////

#if VGK_LANG_CHS
		o	<< "-----------------------------------------------------------\n" 
			<< "\t\t打包成功\n"
			<< "-----------------------------------------------------------\n" ;
#else
		o	<< "-----------------------------------------------------------\n" 
			<< "\t\tPacking succeed\n"
			<< "-----------------------------------------------------------\n" ;
#endif
		VGK_SHOW( o.str() );
		o.str("");

		MessageBox(
			AfxGetApp()->m_pMainWnd->m_hWnd ,"打包成功！","提示",MB_OK | MB_TOPMOST );

		return true;
	}

	//----------------------------------------------------------------
	bool SceneFileUtility::publishScene()
	{
		VGK_DLL_RES_SWITCH_NAME( VGDEP_DLL_NAME );

		CDlgSelectFlash dlg; 
		if (IDOK == dlg.DoModal())
		{
			String UIPath = dlg.getUserInterfacePath();
			String filePath = dlg.getPackFilePath();

			// 用于切块保存场景而加入的类型参数，此处修改成非切块状态
			vgGlobal::ModUtility::setSaveMode( false );
			vgGlobal::MeshUtility::setSaveMode( false );
			vgGlobal::TerrainUtility::setSaveMode( false );

			publishScene( filePath, UIPath );

			//VGK_DLL_RES_SWITCH();
			return true;
		}

		//VGK_DLL_RES_SWITCH();
		return false;
	}
	//----------------------------------------------------------------
	bool SceneFileUtility::invalidateUserConfig( const String& vg_filepath )
	{
		//------------------------------------------
		String	projpath = vgKernel::StringUtility::getPathFromAbsoluteFilename(vg_filepath);
		String	projname = vgKernel::StringUtility::getFilenameWithoutExtFromAbsPath( vg_filepath );

		vgConf::ProjectConfig::getSingleton().setProfilePath( 
			projpath + projname + ".xml" );


		dllnames = VG_PROJCONF_GET_STRING( 
			VGDLL_PROJCONF,  
			VGDLL_PROJCONF_NAMES);

		dllpath = VG_PROJCONF_GET_STRING( 
			VGDLL_PROJCONF,  
			VGDLL_PROJCONF_PATH);

		String falseDLLs;

		if ( !dllpath.empty() )
		{
			falseDLLs += vgKernel::PluginLoaderOnString::load(dllnames, projpath + dllpath);
		}

		if ( !falseDLLs.empty() )
		{
#if VGK_LANG_CHS
			falseDLLs += "无法导入！";//请核对场景配置文件中的插件路径设置是否正确。";
			falseDLLs += "\n出错原因:可能是因为该DLL所依赖的底层DLL无法找到，请核查！";
#else
			falseDLLs += "missing！";
#endif
			//AfxMessageBox( falseDLLs.c_str() );
			vgKernel::SystemUtility::showModelDialog( falseDLLs );
		}

#if 0
		vgKernel::StringVector dllvec  =
			vgKernel::StringUtility::tokenize( dllnames , ";" ,false );


		vgKernel::StringVector::iterator iter = dllvec.begin();
		vgKernel::StringVector::iterator iter_end= dllvec.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			vgKernel::StringUtility::trim( *iter );

			String& onedll = *iter;

#if _DEBUG
			onedll += "_Debug.dll";
#else
			onedll += "_Release.dll";
#endif

			if ( onedll.empty() == false )
			{
				VGK_DLL_LOAD( onedll.c_str() );
			}
		}
		//------------------------------------------
#endif

		return true;
	}

#if 0
	//----------------------------------------------------------------
	bool SceneFileUtility::invalidatePluginConfig( const String& vg_filepath)
	{
		
		String xmlFilePathDes = vgKernel::SystemUtility::getCurrentProcessPath();
			
		String xmlName = vgKernel::SystemUtility::getCurrentProcessName();

		xmlName = vgKernel::StringUtility::getFilenameWithoutExtension(xmlName);
		xmlName += ".xml";


		xmlFilePathDes += xmlName;


		String xmlFilePathSrc;
		

		xmlFilePathSrc = vgKernel::StringUtility::
			getPathFromAbsoluteFilename(vg_filepath);

		xmlFilePathSrc += "\\plugins\\";


		xmlFilePathSrc += xmlName;

		if ( vgKernel::SystemUtility::checkFileExist(xmlFilePathSrc) )
		{
			vgKernel::SystemUtility::copyFile( xmlFilePathSrc, xmlFilePathDes );
			
			String falseDLLs = VG_EXECONF_INVALIDATE( true );
			if ( !falseDLLs.empty() )
			{
#if VGK_LANG_CHS
				falseDLLs += "无法找到！";
#else
				falseDLLs += "missing！";
#endif
				//AfxMessageBox( falseDLLs.c_str() );
				vgKernel::SystemUtility::showModelDialog( falseDLLs );

			}
		}

		
		return true;
	}

	//----------------------------------------------------------------
	bool SceneFileUtility::resetPluginConfig()
	{

		String xmlFilePathDes = vgKernel::SystemUtility::getCurrentProcessPath();

		String xmlName = vgKernel::SystemUtility::getCurrentProcessName();

		xmlName = vgKernel::StringUtility::getFilenameWithoutExtension(xmlName);
		xmlName += ".xml";


		xmlFilePathDes += xmlName;


		String xmlFilePathSrc;


		xmlFilePathSrc = vgKernel::SystemUtility::
			getCurrentProcessPath();

		xmlFilePathSrc += "\\plugins\\basic\\";


		xmlFilePathSrc += xmlName;

		if ( vgKernel::SystemUtility::checkFileExist(xmlFilePathSrc) )
		{
			vgKernel::SystemUtility::copyFile( xmlFilePathSrc, xmlFilePathDes );
			
			VG_EXECONF_INVALIDATE( false );
		}


		return true;
	}
#endif
	//----------------------------------------------------------------
	void SceneFileUtility::saveProject( const String& projpath , const String& projname )
	{
		VG_PROJCONF_SET( VGDLL_PROJCONF , 
			VGDLL_PROJCONF_PATH , 
			dllpath);

		// 拷贝插件
		String srcpath = getCurrentScenePath() + dllpath;
		String despath = projpath + "\\" + dllpath;

		vgKernel::SystemUtility::createDirectory(despath);
		vgKernel::SystemUtility::copyDirectory(despath, srcpath);

		return;
	}

	//----------------------------------------------------------------
	void SceneFileUtility::saveCutSceneFile()
	{
		using namespace vgKernel;

		// 检查是否开启了切块操作
		if ( !_isCutBlock )
		{
			String msg = "切块保存失败！请先点击菜单中的“开始切块”";
			SystemUtility::showModelDialog( msg );
			return;
		}

		Plugin* plg = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );
		if ( plg == NULL )
		{
			_isCutBlock = false;
			SelectManager::getSingleton().setPolygonMode( false );

			return;
		}

		// 检查是否有切块选区
		VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, hasCutArea, pfnHasArea );
		assert( pfnHasArea != NULL );
		
		if ( !(*pfnHasArea)() )  // 有地形但没有切块
		{
			String msg = "切块保存失败！请先选定切块区域！";
			vgKernel::SystemUtility::showModelDialog( msg );

			VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, setCutAreaFlag, pfnSetFlag );
			assert( pfnSetFlag != NULL );
			(*pfnSetFlag)( false );

			SelectManager::getSingleton().setEnableRenderBoundingBox( true );
			SelectManager::getSingleton().setPolygonMode( false );

			_isCutBlock = false;
			return;
		}

		SelectManager::getSingleton().uncolorbleSelectedRender( 
			SelectManager::getSingleton().getCurrentSelectedItems() );

		saveSceneFile( true );

		// 清空用于保存vg的模型列表
		vgMod::NodeManager::getSingleton().clearNodeIndexList( 
			vgMod::NodeManager::getSingleton().getSelectNodeItemIndexList() );

		// 清空用于保存vgimg的纹理列表
		vgCore::TextureManager::getSingleton().clearTextureNameMap();

		// 清空用于保存vgm对应的vgi的纹理列表
		vgMesh::MeshManager::getSingleton().clearSelectItemMap();


		VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, setCutAreaFlag, pfnSetFlag );
		assert( pfnSetFlag != NULL );
		(*pfnSetFlag)( false );

		SelectManager::getSingleton().setEnableRenderBoundingBox( true );
		SelectManager::getSingleton().setPolygonMode( false );

		_isCutBlock = false;
	}

	//----------------------------------------------------------------
	void SceneFileUtility::setCutSceneBeginState()
	{
		using namespace vgKernel;
		Plugin* plg = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );

		if ( plg == NULL )
		{
			return;
		}
		
		VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, setCutAreaFlag, pfnSetFlag );
		assert( pfnSetFlag != NULL );
		(*pfnSetFlag)( true );

		SelectManager::getSingleton().setEnableRenderBoundingBox( false );
		SelectManager::getSingleton().setPolygonMode( true );

		_isCutBlock = true;
	}

	//----------------------------------------------------------------

	
}//namespace vgXXX
