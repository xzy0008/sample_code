


#include <vgStableHeaders.h>
#include <vgConf/vgcoExeConfig.h>

#include <vgKernel/vgkPluginLoaderOnString.h>

namespace vgConf {
	
	
	
	//----------------------------------------------------------------
	bool ExeConfig::shutdown()
	{
		return uninitProfile( _xmlFilePath );
	}
	//----------------------------------------------------------------
	bool ExeConfig::initialise()
	{

		//registerKey(  "Default" , "placeholder" , "1" );

		//setConfig( "Default" , "placeholder" , "0" );

		return true;
	}

	ExeConfig::ExeConfig() : Singleton<ExeConfig>( VGK_SINGLETON_LEFE_VGCO_EXEMGR )
	{
		_inited = false;
		VGK_TRACE(_T("ExeConfig created."));
	}
	ExeConfig::~ExeConfig()
	{
		VGK_TRACE(_T("ExeConfig destroyed."));
	}

	void ExeConfig::init()
	{
		using namespace vgKernel;

		String exepath = vgKernel::SystemUtility::getCurrentProcessPath() +
			vgKernel::SystemUtility::getCurrentProcessName();

		exepath = exepath.substr( 0 , exepath.find_last_of(".") );
		_xmlFilePath = exepath + ".xml";

		bool initok = initProfile( _xmlFilePath );
		//return true;

		if ( initok == false )
		{
			VGK_TRACE( "ExeConfig::init() failed!!" );
			return;
		}


		_inited = true;

		return;
	}

	String ExeConfig::getValueFromProfile( const String& section , const String& key )
	{
		if ( _inited == false )
		{
			init();
			_inited = true;
			VGK_TRACE( "ExeConfig::getValueFromProfile initProfile ok " );
		}
		
		
		assert( _inited == true );
		return __super::getValueFromProfile( section , key );
	}

	String ExeConfig::invalidate( bool bForceReLoad/* = false*/ )
	{
		init();
		if ( bForceReLoad)
		{
			return vgKernel::PluginLoaderOnString::load( bForceReLoad );
		}

		return String();
	}
	//----------------------------------------------------------------


}// end of namespace vgConf
