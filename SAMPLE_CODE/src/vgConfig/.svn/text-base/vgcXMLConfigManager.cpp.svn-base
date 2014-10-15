


#include <vgStableHeaders.h>
#include <vgConfig/vgcXMLConfigManager.h>
#include <vgConf/XMLProfile.h>

namespace vgConfig{

	//----------------------------------------------------------------
	XMLConfigManager::XMLConfigManager()
		: Singleton<XMLConfigManager>( VGK_SINGLETON_LEFE_XMLCONFIGMGR ) 
	{
		flag = 0;


		VGK_TRACE(_T("XMLConfigManager created."));
	}


	bool XMLConfigManager::LoadXmlDocument(CString filename)
	{
		//CString strFileName;
		//CString strExtension = _T(".xml");

		//char exebuf[512];
		//DWORD getret = GetModuleFileName( NULL , exebuf , 512 );

		//assert( getret < 512 );
		//assert( getret > 0 );

		//String exestr( exebuf );
		//String exepath = exestr.substr( 0 , 
		//	exestr.find_last_of("\\/")  + 1);

		//CString path;
		//path.Format("%s", exepath.c_str());
		//
		//strFileName = path + filename + strExtension ;

		if (filename.IsEmpty())
		{	
			flag = 0;
			return   false;
		}
		else
		{		
			BOOL rc = m_Profile.Load(filename);
			if (rc)
			{
				GetKeyValue(m_Profile);
				flag = 1;
				return true;	
			}
			else
			{
				flag = 0;
				return false;
			}			
		}

	}

	void XMLConfigManager::GetKeyValue(CXmlProfile& profile)
	{
		FileData	dataElement;
		CXmlSectionListElement *pSection = profile.m_Sections.GetFirst();

		if (!dataGroup.empty())
		{
			dataGroup.clear();
		}

		while (pSection != NULL && !pSection->IsRoot())
		{
			CXmlKeyListElement *pKey = pSection->GetEntry()->m_Keys.GetFirst();

			while (pKey != NULL && !pKey->IsRoot())
			{
				dataElement.section = pSection->GetEntry()->m_strName;
				dataElement.key = pKey->GetEntry()->m_strName;
				dataElement.keyvalue = pKey->GetEntry()->m_strValue;
				pKey = pKey->GetNext();		

				dataGroup.push_back(dataElement);
			}
			pSection = pSection->GetNext();
		}
	}

 SectionData XMLConfigManager::GetCurrentValue(CString section)
	{		
		
		if (!sectiondata._Currentkey.empty())
		{
			sectiondata._Currentkey.clear();
			sectiondata._Currentkeyvalue.clear();
		}
		for (int i = 0; i < dataGroup.size(); i ++ )
		{
			if (section == dataGroup[i].section)
			{
				sectiondata._Currentkey.push_back(dataGroup[i].key);
				sectiondata._Currentkeyvalue.push_back(dataGroup[i].keyvalue);		
			}
		}		return sectiondata;
	}

	float XMLConfigManager::GetFloatValue(CString section, CString  key)
	{
		int  flag = 0;
		for (int i =0; i < sectiondata._Currentkey.size(); i++)
		{
			if (sectiondata._Currentkey[i] == key)
			{
				flag = 1;
				float ValueOfKey = atof(sectiondata._Currentkeyvalue[i]);
				return ValueOfKey;
			}
		}
			if (!flag)
			{
				throw Error("The key is not found");
			}
			
	}

	int XMLConfigManager::GetIntValue(CString section, CString  key)
	{
		int flag = 0;
		for (int i =0; i < sectiondata._Currentkey.size(); i++)
		{
			if (sectiondata._Currentkey[i] == key)
			{
				flag = 1;
				int ValueOfKey = atoi(sectiondata._Currentkeyvalue[i]);
				return ValueOfKey;
			}
		}
		if (!flag)
		{
			throw Error("The key is not found");
		}
	}

	bool XMLConfigManager::FindSection(CString section)
	{
		CXmlSectionListElement * pSection = m_Profile.FindSection(section);

		if (pSection)
		{
			return true;
		}
		else
		{			
			return false;
		}
	}

	void XMLConfigManager::RemoveSection(CString section)
	{
		CXmlSectionListElement * pSection = m_Profile.FindSection(section);

		if (pSection)
		{
			m_Profile.SetKey(section, NULL, NULL);
		}
	}

	void XMLConfigManager::RemoveKeys(CString section, CString key)
	{
		CXmlKeyListElement *pKey = m_Profile.SetKey(section, key, NULL);
	}

	void XMLConfigManager::AddKeys(CString section, CString key, CString keyvalue)
	{		
		CXmlKeyListElement *pKey = m_Profile.SetKey(section, key, keyvalue);
	}

	CString XMLConfigManager::SetIntToCtrValue( int  intvalue)
	{
		CString keyvalue;
		keyvalue.Format("%d", intvalue);	
		return keyvalue;
	}

	CString XMLConfigManager::SetFloatToCtrValue(float  floatvalue)
	{
		CString keyvalue;
		keyvalue.Format("%f", floatvalue);		
		return keyvalue;
	}

	void XMLConfigManager::SaveXML( CString filename)
	{
		BOOL rc;
		if (!flag)
		{
			/*CString strFileName;			
			CString strExtension = _T(".xml");

			char exebuf[512];
			DWORD getret = GetModuleFileName( NULL , exebuf , 512 );

			assert( getret < 512 );
			assert( getret > 0 );

			String exestr( exebuf );
			String exepath = exestr.substr( 0 , 
				exestr.find_last_of("\\/")  + 1);

			CString path;
			path.Format("%s", exepath.c_str());

			strFileName = path + filename + strExtension ;	*/

			rc = m_Profile.Save(filename);
			
		}
		else
		{
			rc = m_Profile.Save();			

			if (rc)
			{
#if VGK_LANG_CHS
				AfxMessageBox("参数已经保存！");
#else
				AfxMessageBox("The parameter is saved!");
#endif
			}
			else
			{
#if VGK_LANG_CHS
				AfxMessageBox("保存Xml文件失败！");
#else
				AfxMessageBox("Failed to save Xml Document!");
#endif
			}
		}
	}
	

}