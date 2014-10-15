
#include <vgStableHeaders.h>
#include <vgTerritory/vgTerrainManagerPlugin.h>

#include <vgPlugin/vgplManagerRoot.h>


namespace vgTerritory 
{
	const std::string sPluginName = "vgTerrainManager";
	//---------------------------------------------------------------------
	vgTerrainManagerPlugin::vgTerrainManagerPlugin()
	{

	}
	//---------------------------------------------------------------------
	const std::string& vgTerrainManagerPlugin::getName() const
	{
		return sPluginName;
	}
	//---------------------------------------------------------------------
	void vgTerrainManagerPlugin::install()
	{
		// Create new scene manager

		vgTerrainManagerAdapter *TerrainAdapter =
			new vgTerrainManagerAdapter();

		if ( vgPlugin::ManagerRoot::getSingleton().getTerrainManagerPtr() == NULL
					&& TerrainAdapter != NULL)
		{
			vgPlugin::ManagerRoot::getSingleton().setTerrainManagerPtr( dynamic_cast<vgPlugin::CoreTerrainManager*>(TerrainAdapter ));
		}
	}
	//---------------------------------------------------------------------
	void vgTerrainManagerPlugin::initialise()
	{


	}
	//---------------------------------------------------------------------
	void vgTerrainManagerPlugin::shutdown()
	{
		vgPlugin::CoreTerrainManager *TerrainAdapter =
			vgPlugin::ManagerRoot::getSingleton().getTerrainManagerPtr();

		delete TerrainAdapter;

		TerrainAdapter = NULL;
	}
	//---------------------------------------------------------------------
	void vgTerrainManagerPlugin::uninstall()
	{

	}


}
