


#ifndef __VGCOEXECONFIG_H__
#define __VGCOEXECONFIG_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>
#include <vgConf/vgcoConfigInterface.h>
#include <vgKernel/vgkSystemUtility.h>
	
namespace vgConf {




	/**
		@date 	2008/12/04  9:11	
		@author  xy
	
		@brief 	

			程序运行的配置类.

		使用方法:

		1.使用ExeConfigRegProxy类来注册默认的项.
		注意,要在cpp中声明这些实例.名字无关,只要保证没有重名即可.
		例如:
			// String类型.
			vgConf::ExeConfigRegProxy reg1( "section1" , "key1" , "value1" );

			// float类型
			vgConf::ExeConfigRegProxy reg2( "section1" , "key2" , "0.3" );

			// int类型
			vgConf::ExeConfigRegProxy reg6( "section1" , "key3" , "123" );

			// bool类型.注意!一定不要写true或者false,要用0或者1表示.
			vgConf::ExeConfigRegProxy reg652( "section2" , "key4" , "1" );


		2.然后开始得到配置项即可.
		得到配置的值时,可以使用宏,但是要注意,必须小心使用,如果转换有错误,可能崩溃
		(这里的崩溃指的是类型不匹配.比如一个"ffg"强行转化为bool这可能崩溃):

			String str = VG_EXECONF_GET_STRING( "section1" , "key2" );
			float f = VG_EXECONF_GET_FLOAT( "section1" , "key2" );
			int i = VG_EXECONF_GET_INT( "section1" , "key3"  );
			bool b = VG_EXECONF_GET_BOOL(  "section2" , "key4"  );

		要细致控制,使用下面的例子:

			// 首先得到字符串
			String str = vgConf::ExeConfig::getSingleton().getConfig( "section2" , "key3" );
			// 从字符串转换成相应的值.
			bool b = vgConf::ConfigUtility::stringToTarget<bool>(  str );


		@see    
	*/
	class VGK_EXPORT ExeConfig : public vgKernel::Singleton<ExeConfig>,
		public ConfigInterface
	{
	private:

		friend class vgKernel::Singleton<ExeConfig>;
	private:
		ExeConfig();

	public:
		virtual~ExeConfig();

	protected:

		virtual bool initialise();
		virtual bool shutdown();

	public:

		

		virtual void reset(){};

		virtual String getConfigName()
		{
			return "ExeConfig";
		}

		String getXmlFilePath() const
		{
			return _xmlFilePath;
		}

		String invalidate( bool bForceReLoad = false );

		bool saveXmlFile()
		{
			return shutdown();
		}

	protected:

		void init();

		virtual String getValueFromProfile( const String& section , 
			const String& key );

	private:


		String _xmlFilePath;

		bool _inited;

	};
	
	
	
}// end of namespace vgConf
	
#define VG_EXECONF_GET_STRING( section , key )	(  vgConf::ExeConfig::getSingleton().getConfig( section , key ) );

#define VG_EXECONF_GET_FLOAT( section , key )	( vgConf::ConfigUtility::stringToTarget<float>\
	( vgConf::ExeConfig::getSingleton().getConfig( section , key ) ) );

#define VG_EXECONF_GET_INT( section , key )	( vgConf::ConfigUtility::stringToTarget<int>\
	( vgConf::ExeConfig::getSingleton().getConfig( section , key ) ) );

#define VG_EXECONF_GET_BOOL( section , key )	( vgConf::ConfigUtility::stringToTarget<bool>\
	( vgConf::ExeConfig::getSingleton().getConfig( section , key ) ) );




#define VG_EXECONF_SET( section , key ,val )	 \
	( vgConf::ExeConfig::getSingleton().setConfig( section , key , \
	vgConf::ConfigUtility::targetToString( val ) ) );

#define VG_EXECONF_INVALIDATE( bForce )		(  vgConf::ExeConfig::getSingleton().invalidate( bForce ) );

#define VG_EXECONF_SAVE()	 \
	( vgConf::ExeConfig::getSingleton().saveXmlFile() );


#endif // end of __VGCOEXECONFIG_H__