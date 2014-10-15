


#include <vgStableHeaders.h>

#include <vgKernel/vgkVec3.h>
#include <vgLogo/vgloLogoManager.h>




bool LogoManager_getRenderstate()
{
	using namespace vgLogo;

	//return LogoManager::getSingleton().getRenderState( );
	//return LogoManager::getSingleton().getCorpLogoPtr()->getRenderState();
	return true;
}

void LogoManager_setRenderstate( bool _render )
{
	using namespace vgLogo;

	//LogoManager::getSingleton().setRenderState( _render );
	//LogoManager::getSingleton().getCorpLogoPtr()->setRenderState( _render );
}


extern VGL_EXPORT  void LogoManager_OutPutHawkeyeMapInSky(String _filename )
{
	using namespace vgLogo;

	LogoManager::getSingleton().OutPutHawkeyeMapInSky( _filename );
}

extern VGL_EXPORT  bool  LogoManager_getcompassrendersign()
{
	using namespace vgLogo;

	return LogoManager::getSingleton().getcompassrendersign();
}

extern VGL_EXPORT  void LogoManager_setcompassrendersign( bool _render )
{
	using namespace vgLogo;

	LogoManager::getSingleton().setcompassrendersign( _render );
}

extern VGL_EXPORT  bool LogoManager_getsmallmaprendersign()
{
	using namespace vgLogo;

	return LogoManager::getSingleton().getsmallmaprendersign();
}

extern VGL_EXPORT  void LogoManager_setsmallmaprendersign( bool _render )
{
	using namespace vgLogo;

	LogoManager::getSingleton().setsmallmaprendersign( _render );
}

extern VGL_EXPORT  bool LogoManager_getsmallmapdatasign()
{
	using namespace vgLogo;

	return LogoManager::getSingleton().getsmallmapdatasign( );
}