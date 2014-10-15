
#include <vgStableHeaders.h>

#include <vgKernel/vgkSelectManager.h>

#include <vgGlobal/vggVgshpUtility.h>

#include <vgGlobal/vggGlobalUtility.h>
//#include <vgShape/vgshShapeManager.h>
#include <vgKernel/vgkPluginManager.h>

#include <vgEntry/vgShapeDataSourceEntry.h>
#include <vgEntry/vgEntryFactory.h>
#include <vgUIController/vgUIController.h>

namespace vgGlobal{

	//----------------------------------------------------------------
	ShapeUtility::ShapeUtility()
	{
		
	}
	
	//----------------------------------------------------------------
	ShapeUtility::~ShapeUtility()
	{

	}

	/************************************************************************/
	/* 对外接口                                                             */
	/************************************************************************/

	//----------------------------------------------------------------
	bool ShapeUtility::importShpFile( const String& strFilePath, bool bSpecial/* = false*/ )
	{
		if( strFilePath.empty() )
		{
			return false;
		}
		
		vgShape::DataSource* psource;
		
		using namespace vgKernel;
		vgKernel::Plugin* plug = PluginManager::getSingleton().getPluginRef( VGSH_DLL_NAME );

		if ( plug == NULL )
		{
			return false;
		}

		if (!bSpecial)
		{
			VGK_DLL_DECLARE_CLASSFUNC( plug, ShapeManager, openShapeFile, pfn1 );

			psource = (vgShape::DataSource*)pfn1(strFilePath);
		} 
		else
		{
			VGK_DLL_DECLARE_CLASSFUNC( plug, ShapeManager, openShapeFileSpecially, pfn1 );
			psource = (vgShape::DataSource*)pfn1(strFilePath);
			//psource = vgShape::ShapeManager::getSingleton().openShapeFileSpecially( strFilePath );
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
	bool ShapeUtility::readProject( const String& strFilePath )
	{
		using namespace vgKernel;
		vgKernel::Plugin* plug = PluginManager::getSingleton().getPluginRef( VGSH_DLL_NAME );

		if ( plug == NULL )
		{
			return false;
		}

		VGK_DLL_DECLARE_CLASSFUNC( plug, ShapeManager, readProject, pfn1 );
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

		VGK_DLL_RUN_CLASSFUNC( VGSH_DLL_NAME, ShapeManager, readProjectExtra)(strFilePath);

#if 0
		VGK_DLL_RUN_CLASSFUNC( VGSH_DLL_NAME, ShapeManager, readProject)(strFilePath);

		//DataSourcePtrMap* pDataSources = 
		//	vgShape::ShapeManager::getSingleton().getDataSources();
		using namespace vgKernel;
		vgKernel::Plugin* plug = PluginManager::getSingleton().getPluginRef( VGSH_DLL_NAME );

		if ( plug == NULL )
		{
			return false;
		}

		VGK_DLL_DECLARE_CLASSFUNC( plug, ShapeManager, getDataSources, pfn1 );
		vgShape::DataSourcePtrMap *pDataSource  = (vgShape::DataSourcePtrMap*)pfn1( );

		for(DataSourcePtrMap::iterator itr = pDataSource->begin();
			itr != pDataSource->end(); itr ++ )
		{
			vgShape::DataSourcePtr psource = itr->second;
			addShpToUI(psource);
		}
#endif
		return true;
	}

	//----------------------------------------------------------------
	bool ShapeUtility::convertShpToEditState()
	{
		vgKernel::Renderer* pRenderer = vgKernel::SelectManager::getSingleton().
			getSelectedRendererByType(vgShape::RENDERER_TYPE_SHAPE_LAYER);

		if (!pRenderer)
		{
			return false;
		}

		//vgShape::ShapeManager::getSingleton().setSelectMode( pRenderer,
		//	!vgShape::ShapeManager::getSingleton().getSelectFlag() );
		using namespace vgKernel;
		vgKernel::Plugin* plug = PluginManager::getSingleton().getPluginRef( VGSH_DLL_NAME );

		if ( plug == NULL )
		{
			return false;
		}

		VGK_DLL_DECLARE_CLASSFUNC( plug, ShapeManager, setSelectMode, pfn1 );
		VGK_DLL_DECLARE_CLASSFUNC( plug, ShapeManager, getSelectFlag, pfn2 );

		assert( pfn1 != NULL && pfn2 != NULL );

		(*pfn1)( pRenderer, !(*pfn2)() );

		return true;
	}
	
	/************************************************************************/
	/* 私有成员                                                             */
	/************************************************************************/

	//----------------------------------------------------------------
	bool ShapeUtility::addShpToUI(vgShape::DataSource* psource)
	{
		using namespace vgKernel;
		vgKernel::Plugin* plug = PluginManager::getSingleton().getPluginRef( VGSH_DLL_NAME );

		if ( plug == NULL )
		{
			return false;
		}

		// 添加datasourceetnry
		VGK_DLL_DECLARE_FUNC( plug, createEntryFromRenderer, pfn1 );
		ShapeDataSourceEntry* ds = (ShapeDataSourceEntry*)pfn1();

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
			"Shape", ds );

		// 向UI中添加vgBaseEntry

		VGK_DLL_DECLARE_CLASSFUNC( plug, ShapeManager, getLayersFromDataSource, pfn2 );
		vgShape::LayerPtrVector* layers = (vgShape::LayerPtrVector*)pfn2( psource );
		
		assert( layers != NULL );
		if ( layers == NULL )
		{
			return false;
		}

		for ( int i = 0 ; i < layers->size() ; ++ i  )
		{
			vgShape::LayerPtr la = (*layers)[i];


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
	bool ShapeUtility::getSelectFlag()
	{
		//return vgShape::ShapeManager::getSingleton().getSelectFlag();
		using namespace vgKernel;
		vgKernel::Plugin* plug = PluginManager::getSingleton().getPluginRef( VGSH_DLL_NAME );

		if ( plug == NULL )
		{
			return false;
		}

		VGK_DLL_DECLARE_CLASSFUNC( plug, ShapeManager, getSelectFlag, pfn1 );

		return (*pfn1)() ;

	}
}//namespace vgXXX