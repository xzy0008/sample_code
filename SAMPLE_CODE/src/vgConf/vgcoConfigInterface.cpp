


#include <vgStableHeaders.h>
#include <vgConf/vgcoConfigInterface.h>
#include <vgKernel/vgkSystemUtility.h>


namespace vgConf {
	


	//----------------------------------------------------------------
	bool ConfigInterface::initProfile( const String& profile_abs_path )
	{
		_xmlProfile.Load(profile_abs_path.c_str() );

		return true;
	}
	//----------------------------------------------------------------
	bool ConfigInterface::registerKey( const String& section ,
		const String& key , const String& defaultValue )
	{
		// 直接插入section
		SectionKeyValueMapInsertRes res = 
			_defaultMap.insert( std::make_pair( section , StringMap() ) );

		assert( res.first != _defaultMap.end() );
		// 如果插入成功
		if ( res.first != _defaultMap.end() )
		{
			StringMapInsertRes res2 = 
				res.first->second.insert( std::make_pair( key , defaultValue ) );

			if ( res2.second == false )
			{
				return false;
			}
		}

//#if _DEBUG
//		std::ostringstream o;
//		o << "ConfigInterface::registerKey: [ " << section << " ][ " << key << " ] -- [ " 
//			<< defaultValue << " ] succeed. ";
//		VGK_TRACE( o.str() );
//#endif

		return true;
	}
	//----------------------------------------------------------------
	bool ConfigInterface::checkExistFromDefaultMap( const String& section , const String& key )
	{
		String getres = 
			getDefaultValue( section , key );

		return !getres.empty();
	}
	//----------------------------------------------------------------
	String ConfigInterface::getDefaultValue( const String& section , const String& key )
	{
		SectionKeyValueMap::iterator sectionfind = 
			_defaultMap.find( section );

		// 倘若不存在
		if ( sectionfind == _defaultMap.end() )
		{
			return String();
		}

		StringMap::iterator keyfind = 
			sectionfind->second.find( key );

		// 如果没有找到
		if ( keyfind == sectionfind->second.end() )
		{
			return String();
		}

		return keyfind->second;
	}
	//----------------------------------------------------------------
	String ConfigInterface::getConfig( const String& section , const String& key ,
		const bool& ret_default_val /*== true */ )
	{
		String getfromprofile = 
			getValueFromProfile( section , key );

		// 如果从profile中没有得到
		// 此时需要把默认值写入profile.这样可以实现保存.
		if ( getfromprofile.empty() == true )
		{
			if ( ret_default_val == true )
			{
				String defulatval = getDefaultValue( section , key );

				if ( defulatval.empty() == false )
				{
					writeValueToProfile( section , key , defulatval );
				}

				return defulatval;
			}
		}

		return getfromprofile;
	}
	//----------------------------------------------------------------
	String ConfigInterface::getValueFromProfile( const String& section , const String& key )
	{
		CString ret = _xmlProfile.GetProfileString(section.c_str(), key.c_str(), NULL );

		return ret.GetBuffer(0);
	}
	//----------------------------------------------------------------
	void ConfigInterface::traceDefaultMap()
	{
		std::ostringstream o;

		o << "======== "
			<< getConfigName() << " traceDefaultMap =========\n";


		SectionKeyValueMap::iterator sectiter = _defaultMap.begin();
		SectionKeyValueMap::iterator sectiter_end= _defaultMap.end();

		for ( ; sectiter != sectiter_end ; ++ sectiter )
		{
			o << "[ section: " << sectiter->first << " ] \n";

			StringMap::iterator mapiter = sectiter->second.begin();
			StringMap::iterator mapiter_end = sectiter->second.end();

			for ( ; mapiter != mapiter_end ; ++ mapiter )
			{
				o << "    [ key: " << mapiter->first << " ] [ value: "
					<< mapiter->second << " ]\n";
			}
		}

		VGK_TRACE( o.str() );

		return;
	}
	//----------------------------------------------------------------
	bool ConfigInterface::writeValueToProfile( const String& section , const String& key , const String& val )
	{
		BOOL writeok = _xmlProfile.WriteProfileString( section.c_str() , key.c_str() , val.c_str() );

		assert( writeok == TRUE );

		return writeok == TRUE;
	}
	//----------------------------------------------------------------
	bool ConfigInterface::setConfig( const String& section , const String& key , const String& val )
	{
		return writeValueToProfile( section , key , val );
	}
	//----------------------------------------------------------------
	void ConfigInterface::traceProfile()
	{
		std::ostringstream o;

		o << "======== "
			<< getConfigName() << " traceProfile =========\n";

		CXmlProfile& profile = _xmlProfile;

		CXmlSectionListElement *pSection = profile.m_Sections.GetFirst();
		while (pSection != NULL && !pSection->IsRoot())
		{
			o << "[ section: " << pSection->GetEntry()->m_strName << " ] \n";


			CXmlKeyListElement *pKey = pSection->GetEntry()->m_Keys.GetFirst();

			while (pKey != NULL && !pKey->IsRoot())
			{
				o << "    [ key: " << pKey->GetEntry()->m_strName << " ] [ value: "
					<< pKey->GetEntry()->m_strValue << " ]\n";

				pKey = pKey->GetNext();
			}

			pSection = pSection->GetNext();
		}

		VGK_TRACE( o.str() );

		return;
	}
	//----------------------------------------------------------------
	bool ConfigInterface::uninitProfile( const String& profile_abs_path )
	{
		//_xmlProfile.Dump();
		//_xmlProfile.Close(TRUE);

		_xmlProfile.Save( profile_abs_path.c_str() );

		return true;
	}
	//----------------------------------------------------------------
	void ConfigInterface::trace()
	{
		traceDefaultMap();
		traceProfile();
	}
	//----------------------------------------------------------------
	
	
}// end of namespace vgConf
