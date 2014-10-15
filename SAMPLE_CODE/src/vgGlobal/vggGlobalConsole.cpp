


#include <vgStableHeaders.h>

#include <vgGlobal/vggGlobalConsole.h>

#include <vgAsyn/vgaIoServer.h>
#include <vgAsyn/vgaMainThreadMessageManager.h>
//#include <vgCam/vgcaCamManager.h>
#include <vgImage/vgiImageManager.h>
#include <vgImage/vgiTextureIoRequestDispatcher.h>
#include <vgImage/vgiTextureManager.h>
#include <vgKernel/vgkGpuManager.h>
#include <vgKernel/vgkRendererManager.h>
#include <vgMesh/vgmMeshManager.h>
//#include <vgTerritory/vgtElevationManager.h>
//#include <vgTerritory/vgtTerrainCenterManager.h>
//#include <vgTerritory/vgtTerrainManager.h>
#include <vgVisualEffects/vgviBackgroundManager.h>
#include <vgVisualEffects/vgviFogManager.h>

#include <vgConf/vgcoExeConfig.h>
#include <vgConf/vgcoProjectConfig.h>

#include <vgVisualEffects/vgviBackgroundManager.h>
#include <vgVisualEffects/vgviFogManager.h>
//#include <vgScript/vgscScriptManager.h>
//#include <vgShape/vgshShapeManager.h>
#include <vgKernel/vgkPluginManager.h>

//#include <vgSolar/vgsoSolarManager.h>

// #include <vgLogo/vgloLogoManager.h>
#include <vgPlan/vgPlanmanager.h>
#include <vgTree/vgtTreeFactory.h>

#include <vgKernel/vgkPluginManager.h>

#include <vgKernel/vgkCoordSystem.h>
//#include <vgSound/vgSoundManager.h>
#include <vgSound/vgSoundDefinition.h>
#include <vgKernel/vgkPluginManager.h>

#include <vgModel/vgmoModelManager.h>

#include <vgMod/vgNodeManager.h>

#include "gdal/ogrsf_frmts.h"
#include "gdal/ogr_api.h"


#include <vgUIController/vgUIController.h>

#include <sys/timeb.h>

//#include <vgPlugin/vgplTerritoryUtility.h>
#include <vgGlobal/vggVgshpUtility.h>
#include <vgGlobal/vggGisUtility.h>
#include <vgGlobal/vggSceneFileUtility.h>

#include <vgKernel/vgkAbstractTreeFacMgr.h>

#include <vgGlobal/vgEntryReg.h>

#include <vgEntry/vgEntryFactory.h>

#include <vgDeprecatedMFCDLL/AutoLoadDialog.h>

#include <vgKernel/vgkCommandManager.h>

#include <vgMod/vgModMisc.h>
#include <vgGlobal/vggVgmodUtility.h>
#include <vgGIS/vggis_api.h>
#include <vgTrigger/vgtrDefinition.h>

namespace vgGlobal {
	
	GlobalConsole::GlobalConsole() 
		: Singleton<GlobalConsole>( VGK_SINGLETON_LEFE_GLOBALCONSOLE ) 
	{
		setDefault();

		m_pRenderPrimitivesCmd = new ConsoleRenderPrimitives;
		m_pRenderEnd = new ConsoleRenderEnd;

		vgKernel::RenderCommandFacade::AddCommand(m_pRenderPrimitivesCmd);
		vgKernel::RenderCommandFacade::AddCommand(m_pRenderEnd);

		assert( _hasInited == false );
		assert( _hasUninited == false );


		VGK_TRACE(_T("GlobalConsole created."));
	}

	GlobalConsole::~GlobalConsole()
	{
		vgKernel::RenderCommandFacade::RemoveCommand(m_pRenderEnd);
		vgKernel::RenderCommandFacade::RemoveCommand(m_pRenderPrimitivesCmd);

		assert( _hasUninited == true );

		VGK_TRACE(_T("GlobalConsole destroyed."));
	}

	bool GlobalConsole::initialise()
	{

		return true;
	}

	bool GlobalConsole::shutdown()
	{
		return true;
	}
	//----------------------------------------------------------------
	bool GlobalConsole::initAfterOpenGLSetup()
	{

		//------------------------------------------
		// 注意，这里需要改变的
		//------------------------------------------

		vgEntryFactory::registerRendererToEntry( new EntriesReg );



		//------------------------------------------
		// 配置各个单件类的初始化程序
		//------------------------------------------
		//vgConfig::ConfigManager::getSingleton();

		vgKernel::AbstractTreeFacMgr::getSingleton();

		vgTree::TreeFactory* tree_fac = new vgTree::TreeFactory;

		vgKernel::RendererManager::getSingleton();

		vgMesh::MeshManager::getSingleton();

		vgKernel::AbstractTreeFacMgr::getSingleton();


		vgKernel::RendererManager::getSingleton().initAfterOpenGLSetup();



		vgMod::NodeManager::getSingleton().initAfterOpenGLSetup();




		bool gpuinit = vgKernel::GpuManager::getSingleton().initAfterOpenGLSetup();
		assert( gpuinit == true );

		vgAsyn::IoServer::getSingleton();
		vgAsyn::MainThreadMessageManager::getSingleton();

		vgImage::ImageManager::getSingleton();
		vgImage::TextureManager::getSingleton();
		vgImage::TextureIoRequestDispatcher::getSingleton();


		


		vgMesh::MeshManager::getSingleton().initAfterOpenGLSetup();

		/*bool gpuinit = vgKernel::GpuManager::getSingleton().initAfterOpenGLSetup();
		assert( gpuinit == true );*/

#if 1
		//vgPlugin::TerritoryUtility::initAfterOpenGLSetup();
#else
		vgTerritory::TerrainManager::getSingleton().initAfterOpenGLSetup();
#endif
		
		//vgShape::ShapeManager::getSingleton().initAfterOpenGLSetup();
		VGK_DLL_RUN_CLASSFUNC( VGSH_DLL_NAME, ShapeManager, initAfterOpenGLSetup)();

		//vgScript::ScriptManager::getSingleton().initAfterOpenGLSetup();

		_hasInited = true;

		//VGK_DLL_LOAD( VGG_DLL_NAME );

		return true;
	}
	//----------------------------------------------------------------
	bool GlobalConsole::uninitBeforeOpenGLDestroy()
	{
		//------------------------------------------
		// 卸载必要的数据
		// 注意先后顺序
		//------------------------------------------
		vgMod::NodeManager::getSingleton().uninitBeforeOpenGLDestroy();
		vgKernel::PluginManager::getSingleton().uninitBeforeOpenGLDestroy();
		
		//vgSolar::SolarManager::getSingleton().uninitBeforeOpenGLDestroy();


		//vgScript::ScriptManager::getSingleton().uninitBeforeOpenGLDestroy();

		//vgTerritory::ElevationManager::getSingleton().uninitBeforeOpenGLDestroy();

		//vgTerritory::TerrainManager::getSingleton().uninitBeforeOpenGLDestroy();
		//vgTerritory::TerrainCenterManager::getSingleton().uninitBeforeOpenGLDestroy();
		//vgShape::ShapeManager::getSingleton().uninitBeforeOpenGLDestroy();

		//vgLogo::LogoManager::getSingleton().unloadData();

		//vgSound::SoundManager::getSingleton().unloadData();

		vgAsyn::MainThreadMessageManager::getSingleton().clearAllData();

		vgMesh::MeshManager::getSingleton().unloadAllMeshItems();

		vgModel::ModelManager::getSingleton().unloadAllModelItems();

		vgImage::TextureManager::getSingleton().unloadAllTextureData();



		bool gpuuninit = 
			vgKernel::GpuManager::getSingleton().uninitBeforeOpenGLDestroy();
		assert( gpuuninit == true );

		_hasUninited = true;

		return true;
	}

	//----------------------------------------------------------------
	void GlobalConsole::renderBegin()
	{
		assert( _hasInited == true );

		//  已经移入vgviRenderCommand.h
// 		vgVisualEffects::BackgroundManager::getSingleton().renderBegin();
// 		vgVisualEffects::FogManager::getSingleton().renderBegin();

// 
// 		/*第一：视景体 设定好投影矩阵和模型观察矩阵，为绘制作准备****************/
// 		vgCam::CamManager::getSingleton().setupViewFrustum();
// 		/*第二：相机 ************************************************************/
// 		vgCam::CamManager::getSingleton().setupCamera();
// 		vgCam::CamManager::getSingleton().updateCurrentFrustum();

		VGK_CHECK_OPENGL_ERROR();

		//vgScript::ScriptManager::getSingleton().renderBegin();

	//	vgCam::CamManager::getSingleton().renderVcr();

		VGK_CHECK_OPENGL_ERROR();

		// vgImage::TextureIoRequestDispatcher::getSingleton().dealWithUpdateInfoEveryFrame();


		VGK_CHECK_OPENGL_ERROR();
// 		vgAsyn::MainThreadMessageManager::getSingleton().renderBegin();
// 
// 		vgAsyn::MainThreadMessageManager::getSingleton().doRequests();
		VGK_CHECK_OPENGL_ERROR();

	    //vgKernel::RendererManager::getSingleton().renderBegin();

		// 在这里计算collision detect.
	//	vgCam::CamManager::getSingleton().renderBegin();

// 		vgLogo::LogoManager::getSingleton().renderBegin();
	}
	//----------------------------------------------------------------
	void GlobalConsole::renderPrimitives()
	{
		VGK_CHECK_OPENGL_ERROR();

		assert( _hasInited == true );

		this->checkHasBBNodeAddToUI();


 		vgKernel::RendererPackage*	pRenderersCulled = 
 			vgKernel::RendererManager::getSingleton().getCulledRendererPackage();
 
 		vgKernel::RendererPackage::iterator icu = pRenderersCulled->begin();
 		vgKernel::RendererPackage::iterator icu_end = pRenderersCulled->end();
 
 		for ( ; icu != icu_end ; ++ icu )
 		{
 			if ( vgMesh::RENDERER_TYPE_MESH == icu->first)
 			{
 				continue;
 			}
 
 			vgKernel::RendererQueue* curqueue = &icu->second;
 			vgKernel::RendererQueue::iterator  itr = curqueue->begin();
 			vgKernel::RendererQueue::iterator  itr_end = curqueue->end();
 			for ( ; itr != itr_end ; ++ itr )
 			{
 				(*itr)->render();
 			}
 		}

		VGK_CHECK_OPENGL_ERROR();

		// vgTerritory::TerrainManager::getSingleton().render();
		// vgPlugin::TerritoryUtility::render();

		// vgKernel::PluginManager::getSingleton().renderAllPlugins();

		//绘制字体
		/*if (vgTerritory::TerrainManager::getSingleton().getLevellingClassPtr()!=NULL)
		{
			if(vgTerritory::TerrainManager::getSingleton().getLevellingClassPtr()->btm)
				vgFont::FontManager::getSingleton().drawNumber(vgTerritory::TerrainManager::getSingleton().getLevellingClassPtr()->avh+ vgCore::vgCoordinate::getSingleton().GetSceneCood().y);
		}*/
	}

	//----------------------------------------------------------------
	void GlobalConsole::renderEnd()
	{
		VGK_CHECK_OPENGL_ERROR();

		if ( _firstOpenScene )
		{
			_firstOpenScene  = false;

			vgAsyn::MainThreadMessageManager::getSingleton().forceToSynModeAndDealWithAllRequests();

			// 先设置同步模式
			vgImage::TextureIoRequestDispatcher::getSingleton().setAsynMode( false );

			// 提交修改,创建纹理
			vgImage::TextureIoRequestDispatcher::getSingleton().dealWithUpdateInfoEveryFrame();

			// 设置异步模式
			vgImage::TextureIoRequestDispatcher::getSingleton().setAsynMode( true );

			vgAsyn::MainThreadMessageManager::getSingleton().forceToSynModeAndDealWithAllRequests();
		}
		
	}
	//----------------------------------------------------------------
	void GlobalConsole::setDefault()
	{
		_firstOpenScene = false;
		_hasInited = false;
		_hasUninited = false;
	}
	//----------------------------------------------------------------
	bool GlobalConsole::readProject( const String& file_path )
	{
		//vgConf::ProjectConfig::getSingleton().trace();
		String	projpath = vgKernel::StringUtility::getPathFromAbsoluteFilename(file_path);
		String	projname = vgKernel::StringUtility::getFilenameWithoutExtFromAbsPath( file_path );

		vgConf::ProjectConfig::getSingleton().setProfilePath( 
			projpath + projname + ".xml" );

		//vgConf::ProjectConfig::getSingleton().trace();

		/**
			其实这里可以使用ProjectConfigChangedObserver来变更各个属性.
			但是现在读取project还是比较简单的.
			以后复杂之后可以考虑使用Observer方案.
		*/

		vgKernel::PluginManager::getSingleton().readProjectUsingPlugins(  projpath , projname  );

		vgKernel::CoordSystem::getSingleton().readProject( projpath , projname );

		vgKernel::RendererManager::getSingleton().readProject(projpath, projname) ;

		vgMesh::MeshManager::getSingleton().readProject( projpath, projname );

		vgImage::TextureManager::getSingleton().readProject( projpath, projname );

		//vgSolar::SolarManager::getSingleton().readProject();

		vgVisualEffects::BackgroundManager::getSingleton().readProject();

		//vgTerritory::TerrainManager::getSingleton().readProject();

		vgVisualEffects::FogManager::getSingleton().readProject();

		//vgShape::ShapeManager::getSingleton().readProject( projpath );
		// vgGlobal::ShapeUtility::readProject( projpath );
		vgGlobal::GisUtility::readProject(projpath);

		return true;
	}
	//----------------------------------------------------------------
	bool GlobalConsole::saveProject( const String& file_path )
	{
		String	projpath = vgKernel::StringUtility::getPathFromAbsoluteFilename(file_path);
		String	projname = vgKernel::StringUtility::getFilenameWithoutExtFromAbsPath( file_path );

		vgGlobal::SceneFileUtility::saveProject(projpath , projname );

		vgKernel::PluginManager::getSingleton().saveProjectUsingPlugins( 
			projpath , projname );

		vgKernel::CoordSystem::getSingleton().saveProject();

		vgKernel::RendererManager::getSingleton().saveProject();


		vgMesh::MeshManager::getSingleton().saveProject();
		vgImage::TextureManager::getSingleton().saveProject();

		//vgSolar::SolarManager::getSingleton().saveProject();

		//vgScript::ScriptManager::getSingleton().saveProject();

		//vgTerritory::TerrainManager::getSingleton().saveProject();

		vgVisualEffects::FogManager::getSingleton().saveProject();

		// vgShape::ShapeManager::getSingleton().saveProject( projpath );
		// VGK_DLL_RUN_CLASSFUNC( VGG_DLL_NAME, GisDataManager, saveProject)(projpath);

		vgConf::ProjectConfig::getSingleton().saveProfileToPath( 
			projpath + projname + ".xml" );

		string vgeName = projpath + projname;
		vgeName += ".vge";

		Plugin* plg = PluginManager::getSingleton().getPluginRef( VGTRI_DLL_NAME );

		if ( NULL != plg )
		{
			VGK_DLL_DECLARE_CLASSFUNC( plg, TriggerManager, writeToVgFile, pfn1);

			if (pfn1 != NULL)
			{
				(*pfn1)(vgeName);
			}
		}


		return true;
	}
	//----------------------------------------------------------------
	bool GlobalConsole::readProjectEnd( const String& file_path )
	{
		String	projpath = vgKernel::StringUtility::getPathFromAbsoluteFilename(file_path);
		String	projname = vgKernel::StringUtility::getFilenameWithoutExtFromAbsPath( file_path );

		//------------------------------------------
		// 注意,这个放在这里
		//------------------------------------------
		//vgScript::ScriptManager::getSingleton().readProjectEnd();

		string vgeName = projpath + projname;
		vgeName += ".vge";
		Plugin* plg = PluginManager::getSingleton().getPluginRef( VGTRI_DLL_NAME );

		if ( NULL != plg )
		{
			VGK_DLL_DECLARE_CLASSFUNC( plg, TriggerManager, readFromVgFile, pfn1);

			if (pfn1 != NULL)
			{
				(*pfn1)(vgeName);
			}
		}


		_firstOpenScene = true;

		return true;
	}
	//----------------------------------------------------------------
	void GlobalConsole::showFps()
	{

		//------------------------------------------
		// FPS相关
		//------------------------------------------


		static bool  g_bFirstRendering = true;
		static timeb g_lastTime;
		static float g_fTimeSinceLastReport = 0.0;
		static int   g_nFrameCount = 0;
		//RenderScene();
		timeb currentTime;
		float fElapsed = 0.0f;

		if( g_bFirstRendering == true )
		{
			ftime( &g_lastTime );
			currentTime = g_lastTime;
			g_bFirstRendering = false;
		}
		else
		{
			ftime( &currentTime );

			// This is accurate to one second
			fElapsed  = (float)(currentTime.time - g_lastTime.time);
			// This gets it down to one ms
			fElapsed += (float)((currentTime.millitm - g_lastTime.millitm) / 1000.0f);
		}

		static char fpsString[50];

		++g_nFrameCount;


		if( fElapsed - g_fTimeSinceLastReport > 1.0f )
		{

			vgUI::UIController::getSingleton().SetFrameSpeed( g_nFrameCount );


			g_fTimeSinceLastReport = fElapsed;
			g_nFrameCount = 0;
		}




	}

	//----------------------------------------------------------------
	void GlobalConsole::checkHasBBNodeAddToUI()
	{
		//检测是否有植树，是--向UI加节点
		if ( vgMod::ModMisc::getSingleton().getDlgTreeDis()->getIsClickOK() )
		{
			vgMod::NodePtrVec* pNodeList = vgMod::NodeManager::getSingleton().getPlantTreeList();
			if ( !pNodeList->empty() )
			{
				vgMod::CategoryType nCat = ( pNodeList->at(0) )->getCategory();
				vgGlobal::ModUtility::addNodeToUI( nCat, pNodeList, "" );

				//清空节点数组
				vgMod::NodeManager::getSingleton().getPlantTreeList()->clear();

				//清空TreeDis对话框类坐标数组
				vgMod::ModMisc::getSingleton().clearTreeDisPosVec();
			}

			vgMod::ModMisc::getSingleton().getDlgTreeDis()->setIsClickOK( false );
		}
	}

}// end of namespace vgGlobal
