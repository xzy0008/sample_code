


#include <vgStableHeaders.h>
#include <vgScript/vgscExportConf.h>

#include <vgConf/vgcoExeConfig.h>
#include <vgConf/vgcoProjectConfig.h>
#include <vgScript/vgscBoostPythonInclude.h>

namespace vgScript {
	
	using namespace boost::python;
	using namespace vgConf;

	class ConfigInterfaceWrapper 
		: public ConfigInterface ,
	    public wrapper<ConfigInterface>
	{
	public:
		ConfigInterfaceWrapper()
		{
			
		}
		virtual ~ConfigInterfaceWrapper()
		{
			
		}

		virtual String getConfigName()
		{
			return this->get_override("getConfigName")();
		}
	
	
	};

	//----------------------------------------------------------------
	void exportConf()
	{
		
		using namespace vgConf;

		class_<ConfigInterfaceWrapper ,boost::noncopyable >( "ConfigInterface" )
			.def("getConfigName", pure_virtual(&ConfigInterface::getConfigName) )

			.def( "registerKey", &ConfigInterface::registerKey )
			.def( "getConfig", &ConfigInterface::getConfig )
			.def( "setConfig", &ConfigInterface::setConfig )
			.def( "getDefaultValue", &ConfigInterface::getDefaultValue )
			.def( "checkExistFromDefaultMap", &ConfigInterface::checkExistFromDefaultMap )
			.def( "trace", &ConfigInterface::trace )
			;

		class_<ProjectConfig , bases<ConfigInterface>,boost::noncopyable  >( "ProjectConfig" , no_init )

			.def( "setProfilePath", &ProjectConfig::setProfilePath )

			.def( "saveProfileToPath", &ProjectConfig::saveProfileToPath )

			.def( "getSingleton", &ProjectConfig::getSingleton ,
			return_value_policy<reference_existing_object>() )
			.staticmethod( "getSingleton" )
			;

		class_<ExeConfig , bases<ConfigInterface> ,boost::noncopyable >( "ExeConfig" , no_init )
			.def( "getXmlFilePath", &ExeConfig::getXmlFilePath )

			.def( "getSingleton", &ExeConfig::getSingleton ,
			return_value_policy<reference_existing_object>() )
			.staticmethod( "getSingleton" )
			;


	}
	//----------------------------------------------------------------


}// end of namespace vgScript
