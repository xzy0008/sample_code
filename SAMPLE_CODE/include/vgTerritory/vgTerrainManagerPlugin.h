
#ifndef __VGTERRAINMANAGERPLUGIN_H__
#define __VGTERRAINMANAGERPLUGIN_H__

#include <vgPlugin/vgplPlugin.h>
#include <vgTerritory/vgTerrainManagerAdapter.h>

namespace vgTerritory
{

	/** Plugin instance for BSPSceneManager */
	class VGT_EXPORT vgTerrainManagerPlugin : public vgPlugin::Plugin
	{
	public:
		vgTerrainManagerPlugin();


		/// @copydoc Plugin::getName
		const std::string& getName() const;

		/// @copydoc Plugin::install
		void install();

		/// @copydoc Plugin::initialise
		void initialise();

		/// @copydoc Plugin::shutdown
		void shutdown();

		/// @copydoc Plugin::uninstall
		void uninstall();


	};







}

#endif
