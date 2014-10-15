


#ifndef __VGCOCONFIGINTERFACE_H__
#define __VGCOCONFIGINTERFACE_H__

#include <vgKernel/vgkForward.h>
#include <vgConf/XMLProfile.h>
#include <vgConf/vgcoConfigUtility.h>

	
namespace vgConf {

	/**
		@date 	2008/12/04  22:14	
		@author  xy
	
		@brief 	
	
		@see    
	*/
	class  VGK_EXPORT ConfigInterface
	{
	public:
		typedef std::map<String , String> StringMap;
		typedef std::pair<StringMap::iterator ,  bool> StringMapInsertRes;
		typedef std::map<String , StringMap > SectionKeyValueMap;
		typedef std::pair<SectionKeyValueMap::iterator, bool > SectionKeyValueMapInsertRes;

	public:

		ConfigInterface()
		{
			
		}
		virtual ~ConfigInterface()
		{
			
		}
	
	public:

		
		/**
			ע����Ӧ����.
			������ʱ,����Ϊfalse.
		*/
		bool registerKey( const String& section , const String& key ,
			const String& defaultValue );
		


		/**
			������Ӧ����.
			return_default_valueΪtrueʱ,���xml��û����Ӧ����,�᷵��Ĭ�ϵ���.
			Ȼ����һ�λ�д��xml��.
			����Ϊ�յ�Stringʱ,��ʾû�д���.
		*/
		String getConfig( const String& section , 
			const String& key , const bool& ret_default_val = true );

		bool setConfig( const String& section , 
			const String& key , const String& val );

		/**
			�õ�Ĭ�ϵĴ洢Ĭ��ֵ.
			����Ϊ�յĻ�,��ʾû�д���.
		*/
		String getDefaultValue( const String& section , const String& key  );

		/**
			 ��ע�����DefaultMap�в�����Ӧ�����Ƿ����.
		*/
		bool checkExistFromDefaultMap( const String& section , const String& key );


		/**
			����־�м�¼���е�Ĭ����.
		*/
		void trace();


		virtual String getConfigName() = 0;

	protected:

		/**
			��ʼ��profile,ExeConfig��ProjectConfig���̳д˽ӿ�
		*/
		virtual bool initProfile(  const String& profile_abs_path );

		/**
			ж�ص�ʱ�򱣴�xml�ļ�.
		*/
		virtual bool uninitProfile( const String& profile_abs_path );

		virtual String getValueFromProfile( const String& section , 
			const String& key );

		bool writeValueToProfile( const String& section , 
			const String& key , const String& val );


		void traceDefaultMap();

		void traceProfile();


	private:

		String		_xmlProfileName;
		CXmlProfile		_xmlProfile;

		SectionKeyValueMap _defaultMap;

	};
	
	
}// end of namespace vgConf
	


#endif // end of __VGCOCONFIGINTERFACE_H__