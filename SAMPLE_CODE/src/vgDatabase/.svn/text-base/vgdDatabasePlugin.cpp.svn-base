


#include <vgStableHeaders.h>
#include <vgDatabase/vgdDatabasePlugin.h>
#include <vgDatabase/vgdDatabaseManager.h>
#include <vgDatabase/vgdProfileManager.h>

//#include <vgEntry/vgBaseEntry.h>
//#include <vgEntry/vgDatabaseEntry.h>
namespace vgDatabase {



	bool DatabasePlugin::initInOpenGL()
	{
		return true;
	}


	void DatabasePlugin::render()
	{
	}

	bool DatabasePlugin::uninitInOpenGL()
	{
		return true;
	}

	void DatabasePlugin::reset()
	{
	}

	void DatabasePlugin::readProject( const String& projpath , const String& projname )
	{
		ProfileManager::getSingleton().loadRenderProfile(projpath);
	}

	void DatabasePlugin::saveProject( const String& projpath , const String& projname )
	{
		ProfileManager::getSingleton().SaveRendererProfile(projpath);
	}

}// end of namespace vgDatabase
