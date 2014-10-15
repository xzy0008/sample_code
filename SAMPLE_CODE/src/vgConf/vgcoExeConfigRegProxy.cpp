


#include <vgStableHeaders.h>
#include <vgConf/vgcoExeConfigRegProxy.h>
#include <vgConf/vgcoExeConfig.h>

namespace vgConf {
	
	
	
	
	//----------------------------------------------------------------
	ExeConfigRegProxy::ExeConfigRegProxy( String section , String key , String defaultvalue )
	{
		bool registerok = ExeConfig::getSingleton().registerKey( section , key , defaultvalue );

		assert( registerok == true && "可能存在相同的项!" );

	}
	//----------------------------------------------------------------
}// end of namespace vgConf
