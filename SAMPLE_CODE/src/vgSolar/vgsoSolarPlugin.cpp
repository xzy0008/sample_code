


#include <vgStableHeaders.h>
#include <vgSolar/vgsoSolarPlugin.h>

#include <vgSolar/vgsoSolarManager.h>


namespace vgSolar {
	
	
	
	

	bool SolarPlugin::initInOpenGL()
	{

		return true;
	}

	void SolarPlugin::render()
	{

	}

	bool SolarPlugin::uninitInOpenGL()
	{
		vgSolar::SolarManager::getSingleton().uninitBeforeOpenGLDestroy();
		return true;
	}

	void SolarPlugin::reset()
	{

	}

	void SolarPlugin::readProject( const String& projpath , const String& projname )
	{
		vgSolar::SolarManager::getSingleton().readProject();
	}

	void SolarPlugin::saveProject( const String& projpath , const String& projname )
	{
		vgSolar::SolarManager::getSingleton().saveProject();
	}

	void SolarPlugin::renderEnd()
	{
		SolarManager::getSingleton().renderEnd();
	}
}// end of namespace vgSolar
