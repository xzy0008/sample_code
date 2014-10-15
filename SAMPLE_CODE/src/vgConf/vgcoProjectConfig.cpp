


#include <vgStableHeaders.h>
#include <vgConf/vgcoProjectConfig.h>
#include <vgKernel/vgkTrace.h>


namespace vgConf {
	
	
	
	
	//----------------------------------------------------------------
	bool ProjectConfig::initialise()
	{
		return true;
	}
	//----------------------------------------------------------------
	bool ProjectConfig::setProfilePath( const String& proj_abs_path )
	{
		return initProfile( proj_abs_path );
	}
	//----------------------------------------------------------------
	bool ProjectConfig::saveProfileToPath( const String& save_path )
	{
		return uninitProfile( save_path );
	}

	ProjectConfig::ProjectConfig() : Singleton<ProjectConfig>( VGK_SINGLETON_LEFE_VGCO_PROJMGR )
	{
		VGK_TRACE(_T("ProjectConfig created."));
	}

	ProjectConfig::~ProjectConfig()
	{
		VGK_TRACE(_T("ProjectConfig destroyed."));
	}
	//----------------------------------------------------------------


}// end of namespace vgConf
