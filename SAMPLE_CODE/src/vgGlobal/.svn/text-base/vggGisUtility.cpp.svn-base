
#include <vgStableHeaders.h>

#include <vgGlobal/vggGisUtility.h>

#include <vgGis/vgGisManager.h>
#include <vgKernel/vgkPluginManager.h>



#include <vgGlobal/vggVgshpUtility.h>

#include <vgGlobal/vggGlobalUtility.h>
#include <vgKernel/vgkPluginManager.h>

#include <vgEntry/vgGisDataSourceEntry.h>
#include <vgEntry/vgEntryFactory.h>
#include <vgUIController/vgUIController.h>

namespace vgGlobal{

	using namespace	vgGIS3D;

	//----------------------------------------------------------------
	GisUtility::GisUtility()
	{
		
	}
	
	//----------------------------------------------------------------
	GisUtility::~GisUtility()
	{

	}

	
	//----------------------------------------------------------------
	bool GisUtility::renderGisElements()
	{
		if ( !VGK_DLL_CHECK_LOAD( VGG_DLL_NAME ) )
		{
			return false;
		}

		VGK_DLL_RUN_CLASSFUNC( VGG_DLL_NAME ,
			GisManager, renderGisElements )();

		return true;
	}
	
	//----------------------------------------------------------------
	bool GisUtility::measureGisPoint()
	{
		return setGisAnalysis( GisCoordinate );
	}

	
	//----------------------------------------------------------------
	bool GisUtility::measureGisLength()
	{
		return setGisAnalysis(GisDistance);
	}
	
	//----------------------------------------------------------------
	bool GisUtility::measureGisArea()
	{
		return setGisAnalysis(GisArea);
	}

	
	//----------------------------------------------------------------
	bool GisUtility::measureGisVolume()
	{
		return setGisAnalysis(GisVolume);
	}
	
	//----------------------------------------------------------------
	bool GisUtility::FaecherAnalysis()
	{
		return setGisAnalysis(GisFaecher);
	}

	//----------------------------------------------------------------
	bool GisUtility::setGisAnalysis( vgGIS3D::EGisState eType )
	{
		if ( !VGK_DLL_CHECK_LOAD( VGG_DLL_NAME ) )
		{
			return false;
		}

		VGK_DLL_RUN_CLASSFUNC( VGG_DLL_NAME ,
			GisManager, setGisAnalysis )(eType);

		return true;
	}

	//----------------------------------------------------------------
	bool GisUtility::updateStateGisPoint()
	{
		return updateGisState(GisCoordinate);
	}
	
	//----------------------------------------------------------------
	bool GisUtility::updateStateGisLength()
	{
		return updateGisState(GisDistance);
	}
	
	//----------------------------------------------------------------
	bool GisUtility::updateStateGisArea()
	{
		return updateGisState(GisArea);
	}

	//----------------------------------------------------------------
	bool GisUtility::updateStateGisFaecher()
	{
		return updateGisState(GisFaecher);
	}
	
	//----------------------------------------------------------------
	bool GisUtility::updateGisState( vgGIS3D::EGisState eType )
	{
		using namespace vgKernel;
		Plugin* plg = PluginManager::getSingleton().getPluginRef( VGG_DLL_NAME );

		if ( plg == NULL )
		{
			//::MessageBox(NULL , "没载入GIS模块dll!" , "Error" , MB_OK );
			return false;
		}

		VGK_DLL_DECLARE_CLASSFUNC( plg, GisManager, getGisAnalysis, pfn1 );
		VGK_DLL_DECLARE_CLASSFUNC( plg, GisManager, getAnalysisType, pfn2 );

		assert( pfn1 != NULL && pfn2 != NULL );

		bool bGis = ( *pfn2 )();

		EGisState eCurrentType = ( *pfn2 )();

		bool bType = (eCurrentType == eType);

		bGis = bGis && bType;

		return bGis;

	}

	
	//----------------------------------------------------------------
	void GisUtility::reset()
	{
		if ( !VGK_DLL_CHECK_LOAD( VGG_DLL_NAME ) )
		{
			return ;
		}

		VGK_DLL_RUN_CLASSFUNC( VGG_DLL_NAME ,
			GisManager, reset )();
	}

	
	//----------------------------------------------------------------
	void GisUtility::uninitBeforeOpenGLDestroy()
	{
		if ( !VGK_DLL_CHECK_LOAD( VGG_DLL_NAME ) )
		{
			return ;
		}

		VGK_DLL_RUN_CLASSFUNC( VGG_DLL_NAME ,
			GisManager, uninitBeforeOpenGLDestroy )();
	}



	//----------------------------------------------------------------
	bool GisUtility::importShpFile( const String& strFilePath, bool bSpecial/* = false*/ )
	{
		if( strFilePath.empty() )
		{
			return false;
		}

		vgGIS3D::DataSource* psource;

		using namespace vgKernel;
		vgKernel::Plugin* plug = PluginManager::getSingleton().getPluginRef( VGG_DLL_NAME );

		if ( plug == NULL )
		{
			return false;
		}

		if (!bSpecial)
		{
			VGK_DLL_DECLARE_CLASSFUNC( plug, GisDataManager, openShapeFile, pfn1 );

			psource = (vgGIS3D::DataSource*)pfn1(strFilePath);
		} 
		else
		{
			VGK_DLL_DECLARE_CLASSFUNC( plug, GisDataManager, openShapeFileSpecially, pfn1 );
			psource = (vgGIS3D::DataSource*)pfn1(strFilePath);
			//psource = vgGIS3D::GisDataManager::getSingleton().openShapeFileSpecially( strFilePath );
		}

		if ( !psource )
		{
			return false;
		}

		addShpToUI( psource );

		// 重新构树
		vgKernel::RendererManager::getSingleton().invalidate();

		vgKernel::SystemUtility::setCurrentDirectory( strFilePath );

		return true;
	}

	//----------------------------------------------------------------
	bool GisUtility::readProject( const string& strFilePath )
	{
		using namespace vgKernel;
		vgKernel::Plugin* plug = PluginManager::getSingleton().getPluginRef( VGG_DLL_NAME );

		if ( plug == NULL )
		{
			return false;
		}

		VGK_DLL_DECLARE_CLASSFUNC( plug, GisDataManager, readProject, pfn1 );
		char* pNames = (char*)(pfn1(strFilePath));
		String strShpNames  = String(pNames);
		delete pNames;
		pNames = NULL;

		//------------------------------------------
		// 首先分辨shps
		//------------------------------------------
		const String tok = ";";
		StringVector shpvec = vgKernel::StringUtility::tokenize( strShpNames , tok , true);

		StringVector::iterator iter = shpvec.begin();
		StringVector::iterator iter_end = shpvec.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			// 开始读取shp
			const String tok2 = ",";
			StringVector strs = vgKernel::StringUtility::tokenize( *iter , tok2 , true );
			if ( strs.size() > 2 || strs.size() == 0 )
			{
				continue;
			}

			String abspath = strFilePath + "\\" + strs[0];
			bool bSpecial = strs.size()==2? true:false;

			importShpFile(abspath, bSpecial);
		}

		VGK_DLL_RUN_CLASSFUNC( VGG_DLL_NAME, GisDataManager, readProjectExtra)(strFilePath);

#if 0
		VGK_DLL_RUN_CLASSFUNC( VGG_DLL_NAME, GisDataManager, readProject)(strFilePath);

		//DataSourcePtrMap* pDataSources = 
		//	vgGIS3D::GisDataManager::getSingleton().getDataSources();
		using namespace vgKernel;
		vgKernel::Plugin* plug = PluginManager::getSingleton().getPluginRef( VGG_DLL_NAME );

		if ( plug == NULL )
		{
			return false;
		}

		VGK_DLL_DECLARE_CLASSFUNC( plug, GisDataManager, getDataSources, pfn1 );
		vgGIS3D::DataSourcePtrMap *pDataSource  = (vgGIS3D::DataSourcePtrMap*)pfn1( );

		for(DataSourcePtrMap::iterator itr = pDataSource->begin();
			itr != pDataSource->end(); itr ++ )
		{
			vgGIS3D::DataSourcePtr psource = itr->second;
			addShpToUI(psource);
		}
#endif
		return true;
	}

	//----------------------------------------------------------------
	bool GisUtility::convertShpToEditState()
	{
		vgKernel::Renderer* pRenderer = vgKernel::SelectManager::getSingleton().
			getSelectedRendererByType(vgGIS3D::RENDERER_TYPE_GIS_LAYER);

		if (!pRenderer)
		{
			return false;
		}

		//vgGIS3D::GisDataManager::getSingleton().setSelectMode( pRenderer,
		//	!vgGIS3D::GisDataManager::getSingleton().getSelectFlag() );
		using namespace vgKernel;
		vgKernel::Plugin* plug = PluginManager::getSingleton().getPluginRef( VGG_DLL_NAME );

		if ( plug == NULL )
		{
			return false;
		}

		VGK_DLL_DECLARE_CLASSFUNC( plug, GisDataManager, setSelectMode, pfn1 );
		VGK_DLL_DECLARE_CLASSFUNC( plug, GisDataManager, getSelectFlag, pfn2 );

		assert( pfn1 != NULL && pfn2 != NULL );

		(*pfn1)( pRenderer, !(*pfn2)() );

		return true;
	}

	/************************************************************************/
	/* 私有成员                                                             */
	/************************************************************************/

	//----------------------------------------------------------------
	bool GisUtility::addShpToUI(vgGIS3D::DataSource* psource)
	{
		using namespace vgKernel;
		vgKernel::Plugin* plug = PluginManager::getSingleton().getPluginRef( VGG_DLL_NAME );

		if ( plug == NULL )
		{
			return false;
		}

		// 添加datasourceetnry
		VGK_DLL_DECLARE_FUNC( plug, createEntryFromRenderer, pfn1 );
		GisDataSourceEntry* ds = (GisDataSourceEntry*)pfn1();

		if ( !ds )
		{
			VGK_WARN(Warning::WARN_INVALID_STATE ,
				Warning::BUTTON_OK ,
				"ShapeDataSourceEntry* ds = NULL" ,
				"ShapeUtility::addShpToUI)");
		}

		//ShapeDataSourceEntry* ds = 
		//new ShapeDataSourceEntry( psource );

		vgUI::UIController::getSingleton().addEntryToRootByName(
			"GIS Layer", ds );

		// 向UI中添加vgBaseEntry

		VGK_DLL_DECLARE_CLASSFUNC( plug, GisDataManager, getLayersFromDataSource, pfn2 );
		vgGIS3D::LayerPtrVector* layers = (vgGIS3D::LayerPtrVector*)pfn2( psource );

		assert( layers != NULL );
		if ( layers == NULL )
		{
			return false;
		}

		for ( int i = 0 ; i < layers->size() ; ++ i  )
		{
			vgGIS3D::LayerPtr la = (*layers)[i];


			vgBaseEntry* entry = vgEntryFactory::createEntryFromRenderer( la.getPointer() );

			if (entry)
			{
				vgUI::UIController::getSingleton().AddNode(ds , entry );
			}

			//------------------------------------------
			// 向RendererManager中添加renderer
			//------------------------------------------
			vgKernel::RendererQueue* queue = 
				vgKernel::RendererManager::getSingleton().addRenderer( la.getPointer() );

			assert( queue != NULL );
		}

		return true;

	}

	//----------------------------------------------------------------
	bool GisUtility::getSelectFlag()
	{
		//return vgGIS3D::GisDataManager::getSingleton().getSelectFlag();
		using namespace vgKernel;
		vgKernel::Plugin* plug = PluginManager::getSingleton().getPluginRef( VGG_DLL_NAME );

		if ( plug == NULL )
		{
			return false;
		}

		VGK_DLL_DECLARE_CLASSFUNC( plug, GisDataManager, getSelectFlag, pfn1 );

		return (*pfn1)() ;

	}
	
	//----------------------------------------------------------------

	bool GisUtility::measureGisVer_Hor_Slope()
	{
		return setGisAnalysis( GisVer_Hor_Slope );
	}

	//----------------------------------------------------------------
	bool GisUtility::updateGisVer_Hor_Slope()
	{
		return updateGisState(GisVer_Hor_Slope);
	}	

	//----------------------------------------------------------------

}//namespace vgXXX