


#include <vgStableHeaders.h>
#include <vgConf/vgcoProjectConfigRegProxy.h>
#include <vgConf/vgcoProjectConfig.h>

namespace vgConf {
	

	//----------------------------------------------------------------
	ProjectConfigRegProxy::ProjectConfigRegProxy( String section , String key , String defaultvalue )
	{
		bool registerok = ProjectConfig::getSingleton().registerKey( section , key , defaultvalue );

		assert( registerok == true && "可能存在相同的项!" );

	}
	//----------------------------------------------------------------
	
	
}// end of namespace vgConf
