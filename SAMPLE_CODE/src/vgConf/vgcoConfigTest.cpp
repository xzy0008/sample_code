

#include <vgStableHeaders.h>
#include <vgConf/vgcoConfigTest.h>
#include <vgConf/vgcoExeConfig.h>
#include <vgConf/vgcoExeConfigRegProxy.h>

#include <vgConf/vgcoProjectConfig.h>
#include <vgConf/vgcoProjectConfigRegProxy.h>



#if VGCO_TEST





vgConf::ExeConfigRegProxy reg1( "section1" , "key1" , "value1" );

vgConf::ExeConfigRegProxy reg2( "section1" , "key2" , "0.3" );

vgConf::ExeConfigRegProxy reg6( "section1" , "key3" , "123" );

vgConf::ExeConfigRegProxy reg65( "section1" , "key4" , "8.555" );

vgConf::ExeConfigRegProxy reg75( "section2" , "key3" , "0" );

vgConf::ExeConfigRegProxy reg652( "section2" , "key4" , "1" );




// String类型.
vgConf::ProjectConfigRegProxy ggfeg1( "section1" , "key1" , "value1" );

vgConf::ProjectConfigRegProxy gg44feg1( "s" , "str" , "ssssssssss" );
// float类型
vgConf::ProjectConfigRegProxy reg5452( "section1" , "key2" , "0.3" );

// int类型
vgConf::ProjectConfigRegProxy reg34346( "section1" , "key3" , "123" );

// bool类型.注意!一定不要写true或者false,要用0或者1表示.
vgConf::ProjectConfigRegProxy reg6343452( "section2" , "key4" , "1" );



namespace vgConf {
	
	
	
	
	//----------------------------------------------------------------
	void ConfigTest::runTestOnce()
	{
		//////////////////////////////////////////////////////////////////////////


		using namespace vgConf;

		//bool res = ExeConfig::getSingleton().registerKey("ss" , "kk" , "asfasfd");

		//assert( res == true );

		//res = ExeConfig::getSingleton().registerKey("ss" , "kk" , "asfasfd");

		//assert( res == false );

		//res = ExeConfig::getSingleton().checkExistFromDefaultMap("ss" , "kk" );

		//assert( res == true );

		//String dd = ExeConfig::getSingleton().getDefaultValue( "ss" , "kk" );


#if 0

		String ddfasf = ExeConfig::getSingleton().getConfig( "ss" , "kk" );

		String dasfdasf = ExeConfig::getSingleton().getConfig( "section1" , "key1" );

		float ddd = VG_EXECONF_GET_FLOAT( "section1" , "key2" );

		int dddf = VG_EXECONF_GET_INT( "section1" , "key3"  );
		assert( dddf == 123 );


		String dfsdffff = vgConf::ExeConfig::getSingleton().getConfig( "section2" , "key3" );


		bool sfdsaf = vgConf::ConfigUtility::stringToTarget<bool>(  dfsdffff );


		assert( sfdsaf ==false );

		bool sadfDGA = VG_EXECONF_GET_BOOL(  "section2" , "key4"  );

		assert( sadfDGA == true );

		VG_EXECONF_SET( "section1" , "key4" , "-8.555" );

		VG_EXECONF_SET( "section2" , "key3" , true );

		VG_EXECONF_SET( "section2" , "key4" , false );


		String dfgg = VG_EXECONF_GET_STRING( "section2" , "key4" );

		assert( dfgg == "0" );

		ExeConfig::getSingleton().trace();


#endif
		//////////////////////////////////////////////////////////////////////////


		{
			//String dfsdffff = vgConf::ProjectConfig::getSingleton().getConfig( "section2" , "key3" );

			//String ddfasf = ProjectConfig::getSingleton().getConfig( "ss" , "kk" );

			//String dasfdasf = ProjectConfig::getSingleton().getConfig( "section1" , "key1" );


			vgConf::ProjectConfig::getSingleton().trace();


			String ddd = VG_PROJCONF_GET_STRING( "section1" , "key1" );

			VG_PROJCONF_SET( "section2" , "key4" , false );

			VG_PROJCONF_SET( "section1" , "key3" , 4343 );

			VG_PROJCONF_SET( "s" , "str"  , "hhhhhhhhhhhhhh" );


			ProjectConfig::getSingleton().trace();
		}
	}
	//----------------------------------------------------------------


}// end of namespace vgConf


#endif