


#include <vgStableHeaders.h>
#if 0
#include <vgGlobal/vggSceneFilesHandler.h>

#include <vgKernel/vgkRendererManager.h>
#include <vgKernel/vgkSelectManager.h>



#include <vgDatabase/vgdDatabaseManager.h>


#include <vgImage/vgiImageManager.h>
#include <vgimage/vgiTextureManager.h>

#include <vgScript/vgscScriptManager.h>


#include <vgShape/vgshShapeManager.h>

#include <vgMovingManager.h>

#include <vgSound/vgSoundManager.h>

#include <vgFont/vgfFontManager.h>


#include <vgTerritory/vgtTerrainManager.h>
#include <vgGlobal/vggGlobalFacade.h>
#include <vgGlobal/vggGlobalConsole.h>

#include <vgGlobal/vggVgcamUtility.h>
#include <vgGlobal/vggVgmodUtility.h>
#include <vgGlobal/vggVgshpUtility.h>
#include <vgGlobal/vggGisUtility.h>

#include <vgMod/vgModMisc.h>
#include <vgMod/vgModUtility.h>

#include <vgKernel/vgkPluginManager.h>


#include <vgConf/vgcoExeConfigRegProxy.h>
#include <vgConf/vgcoExeConfig.h>
#include <vgConf/vgcoProjectConfig.h>
#include <vgConf/vgcoProjectConfigRegProxy.h>

#include <vgDeprecatedMFCDLL/AutoLoadDialog.h>

#define VGDLL_PROJCONF		"ProjDllConfig"
#define VGDLL_PROJCONF_TITLE "ProjDllTitle"
#define VGDLL_PROJCONF_NAMES	"ProjDllNames"

	///**
	//	在这里创建project config
	//*/
	//vgConf::ProjectConfigRegProxy _project_reg1( 
	//	VGDLL_PROJCONF , VGDLL_PROJCONF_TITLE , "VR-GIS Platform 2.0" );
	//
	//vgConf::ProjectConfigRegProxy _project_reg2( 
	//	VGDLL_PROJCONF , VGDLL_PROJCONF_NAMES , "" );









bool vgGlobal::SceneFilesHandler::_sceneOpened = false;

String vgGlobal::SceneFilesHandler::_currentScenePath = "";

unsigned int vgGlobal::SceneFilesHandler::_uiUpdateTime = 0;

namespace vgGlobal {
	
	
	//----------------------------------------------------------------
	bool SceneFilesHandler::importFiles( const vgKernel::StringVector& strvec,
		bool bSpecial/* = false*/)
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
			if ( importFile( *iter , bSpecial) == false )
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

		vgKernel::SystemUtility::setCurrentDirectory(strvec[0]);

		return ret;
	}
	
	//----------------------------------------------------------------
	bool SceneFilesHandler::importFile( const String& impFile,
		bool bSpecial/* = false*/ )
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
	bool SceneFilesHandler::importFileImpl( const String& filename,
		bool bSpecial/* = false*/ )
	{
		String	fileExt = vgKernel::StringUtility::getFileExtension( filename );

		vgKernel::StringUtility::toLowerCase(fileExt);

		if ( fileExt == "vgm")
		{
			return vgGlobal::GlobalFacade::getSingleton().importModelFileOnly( filename );
		}
		else if ( fileExt == "vg" )
		{
			return openScene( filename );
		}
		else if ( fileExt == "vgi" )
		{
			return vgGlobal::GlobalFacade::getSingleton().importImageFileOnly( filename );
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
			return vgGlobal::CamUtility::importVCRAnimation( filename );
		}
		else if ( fileExt == "vtr" )
		{
			return vgGlobal::GlobalFacade::getSingleton().importVtrFile( filename );
		}
		else if ( fileExt == "wav" )
		{
			return vgGlobal::GlobalFacade::getSingleton().import3DMusicFile( filename );
		}
		else if ( fileExt == "mp3" )
		{
			return vgGlobal::GlobalFacade::getSingleton().importBackgroundMusicFile( filename );
		}
		else if ( fileExt == "vmd" )
		{
			return vgGlobal::GlobalFacade::getSingleton().importVmdFileOnly( filename );
		}
		else if ( fileExt == "shp" )
		{
			return vgGlobal::ShapeUtility::importShpFile( filename ,bSpecial);
			//vgShape::DataSourcePtr psource = 
			//	vgShape::ShapeManager::getSingleton().openShapeFileWithUpdateUI(filename );

			//return !psource.isNull();

			assert(0);

			//return vgVector::VectorManager::getSingleton().open( filename );
		}

		return false;
	}
	
	//----------------------------------------------------------------
	bool SceneFilesHandler::exportFile( const String& impFile )
	{
		if ( exportFileImpl( impFile) == true )
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
	bool SceneFilesHandler::exportFileImpl( const String& filename )
	{
		String	fileExt = vgKernel::StringUtility::getFileExtension( filename );

		vgKernel::StringUtility::toLowerCase(fileExt);

		if ( fileExt == "vgm")
		{
			return vgGlobal::GlobalFacade::getSingleton().saveModelAndImage( filename );
		}
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
			return vgGlobal::CamUtility::exportVCRAnimation( filename );
		}
		else if ( fileExt == "shp" )
		{
			//vgShape::DataSourcePtr psource = 
			//	vgShape::ShapeManager::getSingleton().openShapeFileWithUpdateUI(filename );

			//return !psource.isNull();

			assert(0);

			//return vgVector::VectorManager::getSingleton().open( filename );
		}

		return false;
	}	//----------------------------------------------------------------
	
	//----------------------------------------------------------------
	bool SceneFilesHandler::exportModelFile( const String& vgm_filepath )
	{
		vgGlobal::GlobalFacade::getSingleton().saveModelAndImage( vgm_filepath );

		return true;
	}
	
	//----------------------------------------------------------------
	bool SceneFilesHandler::openScene( const String& vg_filepath )
	{
		_currentScenePath = 
			vgKernel::StringUtility::getPathFromAbsoluteFilename(vg_filepath);

		if ( !openSceneBegin(vg_filepath) )
		{
			return false;
		}

		if ( !openSceneImpl(vg_filepath) )
		{
			return false;
		}

		return openSceneEnd(vg_filepath);


	}
	
	//----------------------------------------------------------------
	bool SceneFilesHandler::saveScene( const String& save_vg_path )
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
	bool SceneFilesHandler::resetScene()
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
	bool SceneFilesHandler::getSceneOpenedFlag()
	{
		return _sceneOpened;
	}
	
	//----------------------------------------------------------------
	bool SceneFilesHandler::publishScene( const String& publish_vg_path )
	{
		//////////////////////////////////////////////////////////////////////////
		// 1、定位并新建打包目录
		String FilePathName = publish_vg_path;

		String FileName = vgKernel::StringUtility::getFilenameFromAbsolutePath(publish_vg_path);

		String FileFolderPath = vgKernel::StringUtility::getPathFromAbsoluteFilename(publish_vg_path);

		String FileNameWithoutExt =  vgKernel::StringUtility::getFilenameWithoutExtension(FileName); 

		String currentDirectory = vgKernel::SystemUtility::getCurrentProcessPath();

		String vgFolderName = "VRGIS_PACKAGE";

		String vgExeFileName = "VRGIS_" + FileNameWithoutExt;

		std::ostringstream o;

		// 定位并新建打包目录
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// 2、新建临时目录并保存vg文件
		String saveFileName = currentDirectory + FileNameWithoutExt + ".vg"; 

		if (!exportVgFileImpl(saveFileName))
		{
			MessageBox(NULL,"保存vg文件出错，结束打包操作！","",MB_OK | MB_TOPMOST );
			return false;
		}

		//此处更改文件夹名称，如VRGIS_11统一改成VRGIS_PACKAGE，
		//主要是为了自解压时LIBS.EXE能够找到自解压路径
		//此处并不占用复制时间，只是更改文件名
		String srcfolder = currentDirectory + vgExeFileName;
		String desfolder = currentDirectory + vgFolderName;
		vgKernel::SystemUtility::moveFile(srcfolder, desfolder);

		// 保存vg文件
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// 3、在临时目录新建并保存打包配置文件（sescript、data.ini等）

		FILE* iniFile;
		String fileName = currentDirectory + "sescript" ;
		String strLine;
		if( !_tfopen_s( &iniFile, fileName.c_str() , _T("wt") ) )
		{
			strLine =  "Silent=1" ;
			_ftprintf( iniFile,  _T("%s%c")  , strLine.c_str(), '\n' );
			strLine =  "Overwrite=1" ;
			_ftprintf( iniFile,  _T("%s%c")  , strLine.c_str(), '\n' );
			strLine =  "TempMode" ;
			_ftprintf( iniFile,  _T("%s%c")  , strLine.c_str(), '\n' );
			strLine = "Setup=" + vgFolderName + "\\LIBS.exe" ; 
			_ftprintf( iniFile,  _T("%s%c")  , strLine.c_str(), '\n' );
			strLine = "Setup=" + vgFolderName + "\\VRGIS.exe";
			_ftprintf( iniFile,  _T("%s")  , strLine.c_str() );
			fclose( iniFile );
		}
		else
		{
			fclose( iniFile );
		}

		fileName = currentDirectory + "Pack_Needed\\data.ini" ;
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


		String tempDirName =  currentDirectory + vgFolderName;

		String sourceDir = currentDirectory + "Pack_Needed";
		String destinDir = tempDirName;
		vgKernel::SystemUtility::copyDirectory( destinDir, sourceDir );

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

		String zipParameter = String("a -m0 -inul -idp -sfxDefault.SFX -ibck -iiconVRGIS.ico -zsescript ")
			+ vgExeFileName + " "
			+ vgFolderName ;

		CFile fp;
		String dllFileName = currentDirectory + "mfcm80chs.dll";
		if (!fp.Open( dllFileName.c_str()  , CFile::modeRead))
		{
			MessageBox(NULL,"没有找到打包软件，失败！","",MB_OK | MB_TOPMOST );
			fp.Close();
			return false;
		}
		fp.Close();

		String zipFileName = currentDirectory + "vgZip.exe";
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
			vgKernel::SystemUtility::removeDirectory( tempDirName );
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

		vgKernel::SystemUtility::removeDirectory( tempDirName );
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
	bool SceneFilesHandler::exportVgFileImpl( const String& save_vg_path )
	{
		if ( !saveSceneBegin(save_vg_path) )
		{
			return false;
		}

		if ( !saveSceneImpl(save_vg_path ) )
		{
			return false;
		}
		
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
			<< "\t\t继续执行后续打包操作:\n"
			<< "-----------------------------------------------------------\n" ;
#else
		o	<< "-----------------------------------------------------------\n" 
			<< "\t\tContinue PostPacking Process!\n"
			<< "-----------------------------------------------------------\n" ;
#endif
		VGK_SHOW( o.str() );

		vgKernel::SystemUtility::setCurrentDirectory(save_vg_path);

		return true;

	}

	
	//----------------------------------------------------------------
	bool SceneFilesHandler::openSceneBegin( const String& vg_filepath )
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

		//------------------------------------------
		String	projpath = vgKernel::StringUtility::getPathFromAbsoluteFilename(vg_filepath);
		String	projname = vgKernel::StringUtility::getFilenameWithoutExtFromAbsPath( vg_filepath );

		vgConf::ProjectConfig::getSingleton().setProfilePath( 
			projpath + projname + ".xml" );

		vgGlobal::GlobalConsole::getSingleton().readProject( vg_filepath );

		String apptitle;
		String dllnames;

		apptitle = VG_PROJCONF_GET_STRING( 
			VGDLL_PROJCONF,  
			VGDLL_PROJCONF_TITLE);

		dllnames = VG_PROJCONF_GET_STRING( 
			VGDLL_PROJCONF,  
			VGDLL_PROJCONF_NAMES);

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
	bool SceneFilesHandler::openSceneEnd(const String& vg_filepath )
	{
		// Part 3：重新构树
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
	bool SceneFilesHandler::openSceneImpl( const String& vg_filepath )
	{

		_currentScenePath = 
			vgKernel::StringUtility::getPathFromAbsoluteFilename(vg_filepath);

		vgGlobal::GlobalConsole::getSingleton().readProjectEnd( vg_filepath );

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
		vgGlobal::GlobalFacade::getSingleton().importModelAndImage(vg_filepath);

		return true;
	}

	
	//----------------------------------------------------------------
	void SceneFilesHandler::saveSceneEnd( const String& save_vg_path )
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
	bool SceneFilesHandler::saveSceneBegin( const String &save_vg_path )
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
	bool SceneFilesHandler::saveSceneImpl( const String& save_vg_path )
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
		vgGlobal::GlobalFacade::getSingleton().saveModelAndImage( folderpath );

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
	unsigned int SceneFilesHandler::getUpdateTime()
	{
		return _uiUpdateTime;
	}

	
	//----------------------------------------------------------------
	void SceneFilesHandler::setUpdateTime( unsigned uiUpdateTime )
	{
		_uiUpdateTime = uiUpdateTime;
	}

	
	//----------------------------------------------------------------
	bool SceneFilesHandler::saveSceneDirectly( const String& save_vg_path )
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
	bool SceneFilesHandler::openSceneDirectly( const String& vg_filepath )
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
}// end of namespace vgGlobal
#endif