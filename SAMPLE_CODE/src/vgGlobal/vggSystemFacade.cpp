


#include <vgStableHeaders.h>

#if 0

#include <vgGlobal/vggSystemFacade.h>

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

#include <vgKernel/vgkPluginManager.h>


#include <vgConf/vgcoExeConfigRegProxy.h>
#include <vgConf/vgcoExeConfig.h>
#include <vgConf/vgcoProjectConfig.h>
#include <vgConf/vgcoProjectConfigRegProxy.h>

#include <vgDeprecatedMFCDLL/AutoLoadDialog.h>

#define VGDLL_PROJCONF		"ProjDllConfig"
#define VGDLL_PROJCONF_TITLE "ProjDllTitle"
#define VGDLL_PROJCONF_NAMES	"ProjDllNames"

	/**
		在这里创建project config
	*/
	vgConf::ProjectConfigRegProxy _project_reg1( 
		VGDLL_PROJCONF , VGDLL_PROJCONF_TITLE , "VR-GIS Platform 2.0" );
	
	vgConf::ProjectConfigRegProxy _project_reg2( 
		VGDLL_PROJCONF , VGDLL_PROJCONF_NAMES , "" );









bool vgGlobal::SystemFacade::_sceneOpened = false;

String vgGlobal::SystemFacade::_currentScenePath = "";

namespace vgGlobal {
	

	//----------------------------------------------------------------
	bool SystemFacade::importFiles( const vgKernel::StringVector& strvec,
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
	bool SystemFacade::importFile( const String& impFile,
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
	bool SystemFacade::importFileImpl( const String& filename,
		bool bSpecial/* = false*/ )
	{
		String	fileExt = vgKernel::StringUtility::getFileExtension( filename );

		vgKernel::StringUtility::toLowerCase(fileExt);

		if ( fileExt == "vgm")
		{
			return vgGlobal::GlobalFacade::getSingleton().importModelFileOnly( filename );
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
	bool SystemFacade::exportFile( const String& impFile )
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
	bool SystemFacade::exportFileImpl( const String& filename )
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
	bool SystemFacade::exportModelFile( const String& vgm_filepath )
	{
		vgGlobal::GlobalFacade::getSingleton().saveModelAndImage( vgm_filepath );

		return true;
	}
	
	//----------------------------------------------------------------
	bool SystemFacade::openSceneFile( const String& vg_filepath )
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

#if VGK_LANG_CHS
		o << "\n开始打开场景文件... \n";
#else
		o << "\nBegin to open scene files... \n";
#endif
		VGK_SHOW( o.str() );
		o.str("");

		const String& strVGReadPath = vg_filepath;

		_currentScenePath = 
			vgKernel::StringUtility::getPathFromAbsoluteFilename(strVGReadPath);

		
		bool	returnStatus = false;

		vgGlobal::GlobalConsole::getSingleton().readProject( strVGReadPath );

		// Part 0：数据库配置文件 *.vgp	
// 		String	filePath = vgKernel::StringUtility::getPathFromAbsoluteFilename(strVGReadPath);
// 		vgDatabase::ProfileManager::getSingleton().loadRenderProfile(filePath);

		// Part 1：vg、vgimg
		returnStatus = vgGlobal::ModUtility::importVgFile( strVGReadPath );

		
		if(returnStatus)
		{
			std::ostringstream o;
#if VGK_LANG_CHS
			o << "\t成功打开文件:"<< strVGReadPath << " \n";
#else
			o << "\tSuccess: "<< strVGReadPath << " \n";
#endif
			VGK_SHOW( o.str() );
		}
		else
		{
			std::ostringstream oEnd;
#if VGK_LANG_CHS
			oEnd << "\t打开文件:"<< strVGReadPath << " 失败\n";
#else
			oEnd << "\tFail: "<< strVGReadPath << " \n";
#endif
			VGK_SHOW( oEnd.str() );
		}


		// Part 2：vgm、vgi
		vgGlobal::GlobalFacade::getSingleton().importModelAndImage(strVGReadPath);

		// Part 3：重新构树
		vgKernel::RendererManager::getSingleton().invalidate();

		
		setSceneOpenedFlag( true );


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


		vgGlobal::GlobalConsole::getSingleton().readProjectEnd( strVGReadPath );


		vgKernel::SystemUtility::setCurrentDirectory(vg_filepath);

	//----------progress position------------------//
		CAutoLoadDialog::SetPos(100);
	//---------------------------------------------//

		return true;
	}
	
	//----------------------------------------------------------------
	bool SystemFacade::resetScene()
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
	bool SystemFacade::getSceneOpenedFlag()
	{
		return _sceneOpened;
	}
	
	//----------------------------------------------------------------
	bool SystemFacade::saveScene( const String& save_vg_path )
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

		// Part 1：vg、vgimg
#if 0
		bool vgok =	vgCore::QuadtreeSceneManager::getSingleton().saveSceneToVG( save_vg_path );
#else
		//bool vgok = vgMod::ModUtility::saveSceneToVG( save_vg_path );
		bool vgok = vgGlobal::ModUtility::exportVgFile( save_vg_path );
#endif

		String folderpath = 
			vgKernel::StringUtility::getPathFromAbsoluteFilename( save_vg_path ) + 
			"\\VRGIS_" + 
			vgKernel::StringUtility::getFilenameWithoutExtFromAbsPath( save_vg_path ) + 
			"\\" + vgKernel::StringUtility::getFilenameFromAbsolutePath( save_vg_path );

		String strSavePath = folderpath;

		if(vgok)
		{
			std::ostringstream o;
#if VGK_LANG_CHS
			o << "\t成功保存文件:"<< strSavePath << " \n";
#else
			o << "\tSuccess: "<< strSavePath << " \n";
#endif
			VGK_SHOW( o.str() );
		}
		else
		{
			std::ostringstream oEnd;
#if VGK_LANG_CHS
			oEnd << "\t保存文件:"<< strSavePath << " 失败\n";
#else
			oEnd << "\tFail: "<< strSavePath << " \n";
#endif
			VGK_SHOW( oEnd.str() );
		}


		if (strSavePath.empty())
		{
			std::ostringstream oEnd;
#if VGK_LANG_CHS
			oEnd<< "-----------------------------------------------------------\n" 
				<< "\t\t退出执行 打开场景操作\n"
				<< "-----------------------------------------------------------\n" ;
#else
			oEnd<< "-----------------------------------------------------------\n" 
				<< "\t\tQuit\n"
				<< "-----------------------------------------------------------\n" ;

#endif
			VGK_SHOW( oEnd.str() );
			return	false;
		}

		vgGlobal::GlobalConsole::getSingleton().saveProject( strSavePath );

		//	Part 2：vgm、vgi
		vgGlobal::GlobalFacade::getSingleton().saveModelAndImage(strSavePath);
		
		//	Part 3：城市规划数据写入vg、MOD地形
		//vgGlobal::GlobalFacade::getSingleton().writeExtraDataToVG( strSavePath );

		//	Part 4：数据库配置文件 *.vgp		
//		String	filePathVgp = vgKernel::StringUtility::getPathFromAbsoluteFilename(strSavePath);
//		vgDatabase::ProfileManager::getSingleton().SaveRendererProfile(filePathVgp);


		//	Part 5: 矢量数据写 *.vsg
		//String filePathVsg = strSavePath.substr( 0 , strSavePath.find_last_of(".") );
		//filePathVsg += ".vsg";	
		//vgVector::VectorManager::getSingleton().writeLayersToVSGFile(filePathVsg);

#if VGK_LANG_CHS
		MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd , 
			"保存场景操作成功!" , "提示" , MB_OK );
#else
		MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd , 
			"Save scene successful!" , "Tips" , MB_OK );
#endif


//#if VGK_LANG_CHS
//		std::ostringstream oEnd;
//		oEnd<< "\t保存到场景:" << strSavePath/*
//			vgKernel::StringUtility::getPathFromAbsoluteFilename( save_vg_path ) 
//			<< "VRGIS_" << 
//			vgKernel::StringUtility::getFilenameWithoutExtFromAbsPath( save_vg_path )*/ 
//			<< "成功完成.\n";
//#else
//		std::ostringstream oEnd;
//		oEnd<< "\tSuccess: " << strSavePath/*
//			vgKernel::StringUtility::getPathFromAbsoluteFilename( save_vg_path ) 
//			<< "VRGIS_" << 
//			vgKernel::StringUtility::getFilenameWithoutExtFromAbsPath( save_vg_path )*/ 
//			<< " \n";
//
//#endif
//
//		VGK_SHOW( oEnd.str() );

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

		return true;
	}

	//----------------------------------------------------------------
	bool SystemFacade::translateRenderers(vgKernel::RendererQueue* queue ,
		const vgKernel::Vec3& trans_vec  )
	{
		using namespace vgKernel;

		if ( queue == NULL )
		{
			return false;
		}

		RendererQueue*	pQuene = queue;

		RendererQueue::iterator	iter_quene = pQuene->begin();
		RendererQueue::iterator	iter_queneEnd = pQuene->end();
		for (; iter_quene != iter_queneEnd; iter_quene++)
		{
			Renderer*	pRenderer = *iter_quene;
			if (pRenderer)
			{
				pRenderer->translate( trans_vec.x, trans_vec.y, trans_vec.z );
			}
		}

		return true;
	}
	
	
	//----------------------------------------------------------------
	bool SystemFacade::runVcr()
	{
		return CamUtility::runVcr();
	}

	//----------------------------------------------------------------
	bool SystemFacade::continueRunVcr()
	{
		return CamUtility::continueRunVcr();
	}
	
	//----------------------------------------------------------------
	bool SystemFacade::stopRunVcr()
	{
		return CamUtility::stopRunVcr();
	}
	
	//----------------------------------------------------------------
	bool SystemFacade::beginRecordingVcr()
	{
		return CamUtility::beginRecordVcr();
	}

	
	//----------------------------------------------------------------
	bool SystemFacade::switchViewCam()
	{
		return CamUtility::switchViewCam();
	}

	
	//----------------------------------------------------------------
	bool SystemFacade::positionViewCamToRenderer()
	{
		return CamUtility::positionViewCamToRenderer();
	}


	//----------------------------------------------------------------
	bool SystemFacade::responseLButtonDblClk(UINT nFlags, CPoint point, CWnd* pwnd )
	{
		vgKernel::InputSystem::getSingleton().OnLButtonDbClick(nFlags,point);

		vgGlobal::ModUtility::responseLButtonDblClk(nFlags, point, pwnd);

		return true;
	}

	
	//----------------------------------------------------------------
	bool SystemFacade::responseLButtonDown(UINT nFlags, CPoint point)
	{
		vgKernel::InputSystem::getSingleton().OnLButtonDown(nFlags, point);

		vgGlobal::ModUtility::responseLButtonDown(nFlags, point);

		return true;
	}

	
	//----------------------------------------------------------------
	bool SystemFacade::responseLButtonUp(UINT nFlags, CPoint point)
	{
		vgKernel::InputSystem::getSingleton().OnLButtonUp(nFlags,point);

		return true;
	}

	
	//----------------------------------------------------------------
	bool SystemFacade::convertSelectedObjectToEffectNode( int nEffectType )
	{
		return vgGlobal::ModUtility::convertSelectedObjectToEffectNode(nEffectType);
	}

	
	//----------------------------------------------------------------
	bool SystemFacade::convertShpToEditState()
	{
		return vgGlobal::ShapeUtility::convertShpToEditState();
	}

	
	//----------------------------------------------------------------
	bool SystemFacade::setSelectNodesToTransparent(bool bSet)
	{
		vgKernel::RendererQueue& selectedBuffer = vgKernel::SelectManager::
			getSingleton().getSelectedItems();
		if (selectedBuffer.empty())
		{
			AfxMessageBox("请选择需要半透明的模型！");
			return false;
		}

		vgKernel::RendererQueue::iterator iter = selectedBuffer.begin();
		vgKernel::RendererQueue::iterator end = selectedBuffer.end();
		for (; iter != end; iter++)
		{
			vgKernel::TransparentObject* pNode = 
				dynamic_cast<vgKernel::TransparentObject*>(*iter);

			if ( pNode == NULL )
			{
				continue;
			}
			assert( pNode != NULL );

			pNode->setTransparent( bSet );
		}

		return true;
	}


	//----------------------------------------------------------------
	bool SystemFacade::createViewCam()
	{
		return vgGlobal::CamUtility::createViewCam();
	}

	
	//----------------------------------------------------------------
	bool SystemFacade::importVCRAnimation( const String& file_name )
	{
		//return vgGlobal::CamUtility::importVCRAnimation(file_name);
		return vgGlobal::CamUtility::importVcrAni(file_name);

	}

	
	//----------------------------------------------------------------
	bool SystemFacade::exportVCRAnimation( const String& file_name )
	{
		//return vgGlobal::CamUtility::exportVCRAnimation(file_name);
		return vgGlobal::CamUtility::exportVcrAni( file_name );
	}


	
	//----------------------------------------------------------------
	bool SystemFacade::renderGisElements()
	{
		return vgGlobal::GisUtility::renderGisElements();
	}


	
	//----------------------------------------------------------------
	bool SystemFacade::measureGisPoint()
	{
		return vgGlobal::GisUtility::measureGisPoint();
	}


	
	//----------------------------------------------------------------
	bool SystemFacade::measureGisLength()
	{
		return vgGlobal::GisUtility::measureGisLength();
	}


	
	//----------------------------------------------------------------
	bool SystemFacade::measureGisArea()
	{
		return vgGlobal::GisUtility::measureGisArea();
	}


	
	//----------------------------------------------------------------
	bool SystemFacade::measureGisVolume()
	{
		return vgGlobal::GisUtility::measureGisVolume();
	}

	
	//----------------------------------------------------------------
	bool SystemFacade::updateStateGisPoint()
	{
		return vgGlobal::GisUtility::updateStateGisPoint();
	}


	
	//----------------------------------------------------------------
	bool SystemFacade::updateStateGisLength()
	{
		return vgGlobal::GisUtility::updateStateGisLength();
	}


	
	//----------------------------------------------------------------
	bool SystemFacade::updateStateGisArea()
	{
		return vgGlobal::GisUtility::updateStateGisArea();
	}


	//----------------------------------------------------------------
	bool SystemFacade::publishScene( const String& publish_vg_path )
	{
		String FilePathName = publish_vg_path;

		String FileName = vgKernel::StringUtility::getFilenameFromAbsolutePath(publish_vg_path);

		String FileFolderPath = vgKernel::StringUtility::getPathFromAbsoluteFilename(publish_vg_path);

		String FileNameWithoutExt =  vgKernel::StringUtility::getFilenameWithoutExtension(FileName); 

		String currentDirectory = vgKernel::SystemUtility::getCurrentProcessPath();

		String vgFolderName = "VRGIS_" + FileNameWithoutExt;

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

		// 保存vg文件
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		// 3、在临时目录新建并保存打包配置文件（sescript、data.ini等）

		FILE* iniFile;
		String fileName = currentDirectory + "sescript" ;
		String strLine;
		if( !_tfopen_s( &iniFile, fileName.c_str() , _T("wt") ) )
		{
			strLine =  "Silent=0" ;
			_ftprintf( iniFile,  _T("%s%c")  , strLine.c_str(), '\n' );
			strLine =  "Overwrite=1" ;
			_ftprintf( iniFile,  _T("%s%c")  , strLine.c_str(), '\n' );
			strLine =  "TempMode" ;
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
		o << "\n开始复制文件，此过程可能需要几分钟，请稍侯... \n";
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
		o << "\n开始执行打包过程... \n";
#else
		o << "\nBegin to pack files... \n";
#endif
		VGK_SHOW( o.str() );
		o.str("");

		String zipParameter = String("a -m0 -inul -idp -sfxDefault.SFX -ibck -iiconVRGIS.ico -zsescript ")
			+ vgFolderName + " "
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

		String srcFileName = currentDirectory + vgFolderName + ".exe";

		String desFileName = FileFolderPath + vgFolderName + ".exe";

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
	bool SystemFacade::exportVgFileImpl( const String& save_vg_path )
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

		// Part 1：vg、vgimg
#if 0
		bool vgok =	vgCore::QuadtreeSceneManager::getSingleton().saveSceneToVG( save_vg_path );
#else
		//bool vgok = vgMod::ModUtility::saveSceneToVG( save_vg_path );
		bool vgok = vgGlobal::ModUtility::exportVgFile( save_vg_path );
#endif

		String folderpath = 
			vgKernel::StringUtility::getPathFromAbsoluteFilename( save_vg_path ) + 
			"\\VRGIS_" + 
			vgKernel::StringUtility::getFilenameWithoutExtFromAbsPath( save_vg_path ) + 
			"\\" + vgKernel::StringUtility::getFilenameFromAbsolutePath( save_vg_path );

		String strSavePath = folderpath;

		if(vgok)
		{
			std::ostringstream o;
#if VGK_LANG_CHS
			o << "\t成功保存文件:"<< strSavePath << " \n";
#else
			o << "\tSuccess: "<< strSavePath << " \n";
#endif
			VGK_SHOW( o.str() );
		}
		else
		{
			std::ostringstream oEnd;
#if VGK_LANG_CHS
			oEnd << "\t保存文件:"<< strSavePath << " 失败\n";
#else
			oEnd << "\tFail: "<< strSavePath << " \n";
#endif
			VGK_SHOW( oEnd.str() );
		}


		if (strSavePath.empty())
		{
			std::ostringstream oEnd;
#if VGK_LANG_CHS
			oEnd<< "-----------------------------------------------------------\n" 
				<< "\t\t退出执行 打开场景操作\n"
				<< "-----------------------------------------------------------\n" ;
#else
			oEnd<< "-----------------------------------------------------------\n" 
				<< "\t\tQuit\n"
				<< "-----------------------------------------------------------\n" ;

#endif
			VGK_SHOW( oEnd.str() );
			return	false;
		}

		vgGlobal::GlobalConsole::getSingleton().saveProject( strSavePath );

		//	Part 2：vgm、vgi
		vgGlobal::GlobalFacade::getSingleton().saveModelAndImage(strSavePath);

		//	Part 3：城市规划数据写入vg、MOD地形
		//vgGlobal::GlobalFacade::getSingleton().writeExtraDataToVG( strSavePath );

		//	Part 4：数据库配置文件 *.vgp		
		//		String	filePathVgp = vgKernel::StringUtility::getPathFromAbsoluteFilename(strSavePath);
		//		vgDatabase::ProfileManager::getSingleton().SaveRendererProfile(filePathVgp);


		//	Part 5: 矢量数据写 *.vsg
		//String filePathVsg = strSavePath.substr( 0 , strSavePath.find_last_of(".") );
		//filePathVsg += ".vsg";	
		//vgVector::VectorManager::getSingleton().writeLayersToVSGFile(filePathVsg);


		//#if VGK_LANG_CHS
		//		std::ostringstream oEnd;
		//		oEnd<< "\t保存到场景:" << strSavePath/*
		//			vgKernel::StringUtility::getPathFromAbsoluteFilename( save_vg_path ) 
		//			<< "VRGIS_" << 
		//			vgKernel::StringUtility::getFilenameWithoutExtFromAbsPath( save_vg_path )*/ 
		//			<< "成功完成.\n";
		//#else
		//		std::ostringstream oEnd;
		//		oEnd<< "\tSuccess: " << strSavePath/*
		//			vgKernel::StringUtility::getPathFromAbsoluteFilename( save_vg_path ) 
		//			<< "VRGIS_" << 
		//			vgKernel::StringUtility::getFilenameWithoutExtFromAbsPath( save_vg_path )*/ 
		//			<< " \n";
		//
		//#endif
		//
		//		VGK_SHOW( oEnd.str() );

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

}// end of namespace vgGlobal

#endif