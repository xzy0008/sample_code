
#include <vgStableHeaders.h>
#include <vgGlobal/vggVgterrainUtility.h>

#include <vgTerritory/vgtFileWriterVtr.h>
#include <vgTerritory/vgtElevationManager.h>
#include <vgTerritory/vgtElevationBound.h>

#include <vgKernel/vgkSystemUtility.h>
#include <vgKernel/vgkPluginManager.h>

namespace vgGlobal{


	//----------------------------------------------------------------
	TerrainUtility::TerrainUtility()
	{
		
	}
	
	//----------------------------------------------------------------
	TerrainUtility::~TerrainUtility()
	{

	}
	
	//----------------------------------------------------------------
	bool TerrainUtility::saveVtrAndVgi( String folderpath )
	{
		using namespace vgKernel;
		using namespace vgTerritory;

		Plugin* plg = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );
		assert( plg != NULL );

		if ( plg == NULL )
		{
			String msg = "保存vtr及vgi失败！没有加载地形模块！";
			vgKernel::SystemUtility::showModelDialog( msg );
			return false;
		}
		
		// 检测是否有地形数据，没有则直接返回
		VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, hasTerrainData, pfnHasData );
		if ( pfnHasData == NULL )
		{
			return false;
		}

		if ( !(*pfnHasData)() )
		{
			return false;
		}

		VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, saveSelectVtrAndVgi, pfnSave );
		if ( (*pfnSave)( folderpath ) )
		{
			return true;
		}
		else
		{
			String msg = "保存vtr及vgi失败！";
			vgKernel::SystemUtility::showModelDialog( msg );
			return false;
		}
	}

	//----------------------------------------------------------------
	void TerrainUtility::setSaveMode( bool bMode )
	{
		using namespace vgKernel;
		using namespace vgTerritory;

		Plugin* plg = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );
		//assert( plg != NULL );

		if ( plg == NULL )
		{
			String msg = "没有加载地形DLL!";
			vgKernel::SystemUtility::showModelDialog( msg );
			return;
		}

		// 检测是否有地形数据，没有则直接返回
		VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, hasTerrainData, pfnHasData );
		if ( pfnHasData == NULL )
		{
			return;
		}

		if ( !(*pfnHasData)() )
		{
			return;
		}

		VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, setSaveMode, pfnSetMode );
		assert( pfnSetMode != NULL );

		(*pfnSetMode)( bMode );
	}

	//----------------------------------------------------------------

	//----------------------------------------------------------------

	//----------------------------------------------------------------

	//----------------------------------------------------------------

	//----------------------------------------------------------------

	//----------------------------------------------------------------

	//----------------------------------------------------------------

	//----------------------------------------------------------------

}//namespace vgXXX