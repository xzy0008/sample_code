#include <vgstableheaders.h>
#include <vgDatabase/vgdProfileManager.h>
#include <cstdio>

#include <vgKernel/vgkStringUtility.h>
#include <vgKernel/vgkSystemUtility.h>
#include <vgDatabase/vgdDatabaseManager.h>


namespace vgDatabase
{
	ProfileManager::ProfileManager(): Singleton<ProfileManager>(VGK_SIGLETON_LEFE_PROFILEMANAGER)
	{
		
	}
	//---------------------------------------------------------------------	
	ProfileManager::~ProfileManager()
	{
		
	}
	//---------------------------------------------------------------------	
	bool ProfileManager::LoadFromFile(String filepath)
	{

		TiXmlDocument *doc  = new TiXmlDocument(filepath.c_str());

		if (!doc->LoadFile())
		{
			return false;
		}

		String temp;

		//获取根节点
		const TiXmlElement* root = doc->RootElement();	
		//TiXmlNode* pXml = doc->FirstChild("profilelist");

		if(NULL == root)
		{
			return false;
		}

		//循环获取该根节点下面的节点
		for(const TiXmlNode* child = root->FirstChild(); child; child = child->NextSibling())
		{
			//判断为元素类型并且是profile元素，Value()获取该标签的名称
			if((child->Type() == TiXmlNode::ELEMENT) && (!strcmp(child->Value(),"profile")))
			{	
				QueryProfile profile;

				const TiXmlElement* pProfile = (const TiXmlElement*) child;

				temp = pProfile->Attribute("name");

				profile.SetName(temp);

				//继续循环获取子节点相关数据   
				for(const TiXmlNode *sub_child = pProfile->FirstChild(); sub_child; sub_child = sub_child->NextSibling() )   
				{						
					if ((sub_child->Type() == TiXmlNode::ELEMENT) && !strcmp(sub_child->Value(),"tablelist"))
					{						
						for (const TiXmlElement *pTable = (const TiXmlElement*)sub_child->FirstChild(); pTable; pTable = pTable->NextSiblingElement())
						{
							temp = pTable->Attribute("name");

							profile.m_tableList.push_back(temp);	
						}
					}
					else if((sub_child->Type() == TiXmlNode::ELEMENT) && !strcmp(sub_child->Value(),"fieldlist"))
					{
						for (const TiXmlElement *pField = (const TiXmlElement*)sub_child->FirstChild(); pField; pField = pField->NextSiblingElement())
						{
							temp = pField->Attribute("name");
							profile.m_recordList.push_back(temp);

							temp = pField->Attribute("alias");
							profile.m_shownNameList.push_back(temp);
						}
					}
					else if((sub_child->Type() == TiXmlNode::ELEMENT) && !strcmp(sub_child->Value(),"connectlist"))
					{
						for (const TiXmlElement *pConnect = (const TiXmlElement*)sub_child->FirstChild(); pConnect; pConnect = pConnect->NextSiblingElement())
						{
							temp = pConnect->Attribute("name");
							profile.m_connectList.push_back(temp);
						}
					}
					else if((sub_child->Type() == TiXmlNode::ELEMENT) && !strcmp(sub_child->Value(),"primaryidlist"))
					{
						for (const TiXmlElement *pPrimaryid = (const TiXmlElement*)sub_child->FirstChild(); pPrimaryid; pPrimaryid = pPrimaryid->NextSiblingElement())
						{
							temp = pPrimaryid->Attribute("name");
							profile.m_primaryRecordList.push_back(temp);
						}
					}

				}

				this->m_profileList.push_back(profile);
				profile.PrintInfo();
			}
		}

		delete doc;
		return true;
	}
	//---------------------------------------------------------------------	
	bool ProfileManager::IsProfileLoaded()
	{
		if (m_profileList.size() == 0)
		{
			return false;
		}

		return true;
	}
	//---------------------------------------------------------------------	
	String ProfileManager::CreateQuery(String profileName, bool isSingleQuery)
	{
		String queryString;
		
		int i;

		for (i=0; i<m_profileList.size(); i++)
		{
			if (m_profileList[i].GetName() == profileName)
			{
				queryString = DatabaseManager::getSingleton().GetConnectorPtr()->CreateQueryFromProfile(&m_profileList[i], isSingleQuery);
				
				return queryString;
			}// end if
		}

		return queryString;
	}
	//---------------------------------------------------------------------	
	String ProfileManager::CreateQueryWithWhere( String profileName, bool isSingleQuery )
	{
		String queryString;

		int i, j;

		for (i=0; i<m_profileList.size(); i++)
		{
			if (m_profileList[i].GetName() == profileName)
			{
				queryString = "select * from ";				

				for (j=0; j<m_profileList[i].m_tableList.size(); j++)
				{
					queryString += m_profileList[i].m_tableList[j];
					if (j != m_profileList[i].m_tableList.size()-1)
					{
						queryString += ", ";
					}
				}

				if (m_profileList[i].m_connectList.size() > 0 || m_profileList[i].m_primaryRecordList.size() > 0)
				{
					queryString += " where ";

					for (j=0; j<m_profileList[i].m_connectList.size(); j++)
					{
						queryString += m_profileList[i].m_connectList[j];
						if (j != m_profileList[i].m_connectList.size()-1)
						{
							queryString += " and ";
						}
					}

					// 单个查询时 使用primary key确定唯一的行
					if (isSingleQuery)
					{
						if (m_profileList[i].m_connectList.size() > 0)
						{
							queryString += " and ";
						}

						for (j=0; j<m_profileList[i].m_primaryRecordList.size(); j++)
						{
							queryString += m_profileList[i].m_primaryRecordList[j];
							queryString += " = ";
						}
					}
				}// end if

			}
		}

		return queryString;
	}
	//---------------------------------------------------------------------	
	QueryProfile* ProfileManager::GetProfile(String profileName)
	{
		for (int i=0; i<m_profileList.size(); i++)
		{
			if (profileName == m_profileList[i].GetName())
			{
				return &m_profileList[i];
			}
		}

		return NULL;
	}
	//---------------------------------------------------------------------	
	QueryProfile* ProfileManager::GetProfile(int index)
	{
		if (m_profileList.size() > index)
		{
			return &m_profileList[index];
		}

		return NULL;
	}
	//---------------------------------------------------------------------	
	long ProfileManager::GetProfileIdByName(String profileName)
	{
		for (int i=0; i<m_profileList.size(); i++)
		{
			if (profileName == m_profileList[i].GetName())
			{
				return i;
			}
		}

		return NULL;
	}

	//---------------------------------------------------------------------	
	void QueryProfile::PrintInfo()
	{
		
	}
	//---------------------------------------------------------------------	
	CString QueryProfile::GetQueryNameFromShowName(CString shownName)
	{
		// 		String shownName = name.GetString();
		CString result;

		for (int i=0; i<m_shownNameList.size(); i++)
		{
			if (shownName.GetString() == m_shownNameList[i])
			{
				result =  m_recordList[i].c_str();
				return result;
			}
		}

		return shownName;
	}
	//---------------------------------------------------------------------	
	CString QueryProfile::GetShowNameFromQueryName(CString queryName)
	{
		CString result;

		for (int i=0; i<m_recordList.size(); i++)
		{
			if (queryName.GetString() == m_recordList[i])
			{
				result =  m_shownNameList[i].c_str();
				return result;
			}
		}

		return queryName;
	}
	//---------------------------------------------------------------------	
	CString QueryProfile::GetPrimaryId() 
	{
		CString str;
		str = m_primaryRecordList.front().c_str();
		return str;
	}
	//---------------------------------------------------------------------	
	long ProfileManager::SaveRendererProfile(String filepath)
	{
		String savePath = vgKernel::SystemUtility::getCurrentProcessPath();
		savePath = vgKernel::StringUtility::getPathFromAbsoluteFilename(savePath);
		String srcFilePath = savePath + "profile.xml";

		String desFilePath = filepath + "profile.xml";
		vgKernel::SystemUtility::copyFile(srcFilePath , desFilePath);

		int cnt = 0;
		int writeLen = 0;

		String filename = filepath + "profile.vgp";

		CFile	oCFile;
		if( ! oCFile.Open(filename.c_str(), CFile::modeWrite | CFile::modeCreate | CFile::typeBinary) )
		{
			return -1;
		}

		vgKernel::RendererPackage* pAllRenderer = vgKernel::RendererManager::getSingleton().getAllRendererPackage();

		vgKernel::RendererPackage::iterator	iter_pack = pAllRenderer->begin();
		vgKernel::RendererPackage::iterator	iter_packEnd = pAllRenderer->end();
		
		for (; iter_pack != iter_packEnd; iter_pack++)
		{
			vgKernel::RendererQueue*	pQuene = &iter_pack->second;

			vgKernel::RendererQueue::iterator	iter_quene = pQuene->begin();
			vgKernel::RendererQueue::iterator	iter_queneEnd = pQuene->end();

			for (; iter_quene != iter_queneEnd; iter_quene++)
			{
				vgKernel::Renderer*	pRenderer = *iter_quene;
				vgKernel::DatabaseRendererData *pData;

				if ((pData = (vgKernel::DatabaseRendererData*)(pRenderer->getRendererDataByType(vgKernel::RDT_DATABASE_PROFILE))) != NULL)
				{
					if (pData->profile.length() == 0)
					{
						continue;
					}

					unsigned long id1 = pRenderer->getUniqueID()._id1;
					unsigned long id2 = pRenderer->getUniqueID()._id2;
					unsigned long profileId = GetProfileIdByName(pData->profile);

					oCFile.Write( &id1, sizeof(unsigned long));
					oCFile.Write( &id2, sizeof(unsigned long));
					oCFile.Write( &profileId, sizeof(unsigned long));

					cnt ++;

				}
			}
		}
		oCFile.Close();

		return cnt;
	}
	//---------------------------------------------------------------------	
	long ProfileManager::loadRenderProfile(String filepath)
	{
		String profilePath = filepath + "profile.xml";

		if (!vgDatabase::ProfileManager::getSingleton().LoadFromFile(profilePath))
		{
			String profileInExeFolder = vgKernel::SystemUtility::getCurrentProcessPath();
			profileInExeFolder = vgKernel::StringUtility::getPathFromAbsoluteFilename(profileInExeFolder);

			profileInExeFolder += "profile.xml";

			bool flag;
			flag = vgDatabase::ProfileManager::getSingleton().LoadFromFile(profileInExeFolder);

			if (!flag)
			{
				assert(0 && "there is no profile in the process folder!");
			}
		}

		int cnt = 0;

		String filename = filepath + "profile.vgp";

		CFile	oCFile;
		if(! oCFile.Open(filename.c_str(), CFile::modeRead|CFile::typeBinary) )
		{
			return 0;
		}

		m_rendererProfileMap.clear();
		unsigned long id1, id2, profileId;

		while ( oCFile.Read( &id1, sizeof(unsigned long)) )
		{
			oCFile.Read( &id2, sizeof(unsigned long));
			oCFile.Read( &profileId, sizeof(unsigned long));

			vgKernel::UniqueID newId;
			newId._id1 = id1;
			newId._id2 = id2;

			m_rendererProfileMap[newId] = profileId;

			cnt ++;
		}

		oCFile.Close();

		return cnt;
	}
	//---------------------------------------------------------------------	
	bool ProfileManager::InitRendererProfile(vgKernel::Renderer* pRenderer)
	{
		std::map<vgKernel::UniqueID, long>::iterator itr =m_rendererProfileMap.find(/*.begin(),
																			   m_rendererProfileMap.end(),*/ pRenderer->getUniqueID() );

		long profileID;
		if (itr != m_rendererProfileMap.end() )
		{
			profileID = itr->second;
			vgKernel::DatabaseRendererData *pRendererData = new vgKernel::DatabaseRendererData;
			pRendererData->profile = GetProfile(profileID)->GetName();

			pRenderer->addRendererData(pRendererData);
			return true;
		}
		else
		{
			return false;
		}
	}
	//---------------------------------------------------------------------	
	TiXmlNode* ProfileManager::AppendXmlProfile(const String &fileName, const String &profileName)
	{
		doc = new TiXmlDocument(fileName.c_str());

		if (!doc->LoadFile())
		{
			return NULL;
		}

		int count = 0; 
		String temp;
		TiXmlElement *profileElement;

		TiXmlNode* profileListNode = doc->FirstChildElement("profilelist");

		for( profileElement = (TiXmlElement*)profileListNode->IterateChildren( 0 ); 
			profileElement; 
			profileElement = (TiXmlElement*)profileListNode->IterateChildren(profileElement) ) 
		{ 
			temp = profileElement->Attribute("name");

			if (profileName == temp)
			{				
				AfxMessageBox(_T("表项已存在"));

				return NULL;			
			}

			count++; 
		} 

		//TiXmlNode* profileListNode = doc->FirstChildElement("profilelist");
		//添加profile节点	
		TiXmlElement profile("profile");
		profile.SetAttribute("name",profileName.c_str());

		TiXmlNode *profileNode;
		profileNode = (TiXmlElement*)profileListNode->InsertEndChild(profile);

		//添加table列表
		TiXmlElement tableList("tablelist");
		profileNode->InsertEndChild(tableList);
		//添加field列表
		TiXmlElement fieldList("fieldlist");
		profileNode->InsertEndChild(fieldList);
		//添加connect列表
		TiXmlElement connectList("connectlist");
		profileNode->InsertEndChild(connectList);
		//添加primaryid列表
		TiXmlElement primaryidList("primaryidlist");
		profileNode->InsertEndChild(primaryidList);

		return profileNode;
	}
	//---------------------------------------------------------------------	
	void ProfileManager::InsertTable( const TiXmlNode *profileNode, const String &tableName )
	{
		TiXmlElement table("table");
		table.SetAttribute("name",tableName.c_str());

		TiXmlElement* tableList = (TiXmlElement*)profileNode->FirstChild("tablelist");
		tableList->InsertEndChild(table);

		return;
	}
	//---------------------------------------------------------------------	
	void ProfileManager::InsertFeild( const TiXmlNode *profileNode, const String &feildName, const String &aliasName)
	{
		TiXmlElement field("field");
		field.SetAttribute("name", feildName.c_str() );
		field.SetAttribute("alias", aliasName.c_str());

		TiXmlElement* fieldlist = (TiXmlElement*)profileNode->FirstChild("fieldlist");
		fieldlist->InsertEndChild(field);		

		return;
	}
	//---------------------------------------------------------------------	
	void ProfileManager::InsertConnect( const TiXmlNode *profileNode, const String &connectName)
	{
		TiXmlElement connect("connect");
		connect.SetAttribute("name",connectName.c_str());

		TiXmlElement* connectList = (TiXmlElement*)profileNode->FirstChild("connectlist");
		connectList->InsertEndChild(connect);

		return;
	}
	//---------------------------------------------------------------------	
	void ProfileManager::InsertPrimaryId( const TiXmlNode *profileNode, const String &primaryIdName )
	{
		TiXmlElement primaryId("connect");
		primaryId.SetAttribute("name",primaryIdName.c_str());

		TiXmlElement* primaryIdList = (TiXmlElement*)profileNode->FirstChild("primaryidlist");
		primaryIdList->InsertEndChild(primaryId);

		return;

	}
	//---------------------------------------------------------------------	
	void ProfileManager::IterateNode(String &profileName)
	{			
		int count = 0; 
		String temp;
		TiXmlElement *profileNode;

		TiXmlNode* profileListNode = doc->FirstChildElement("profilelist");

		for( profileNode = (TiXmlElement*)profileListNode->IterateChildren( 0 ); 
			profileNode; 
			profileNode = (TiXmlElement*)profileListNode->IterateChildren( profileNode ) ) 
		{ 
			temp = profileNode->Attribute("name");

			if (profileName == temp)
			{				
				AfxMessageBox(_T("表项已存在"));

				//profileListNode->RemoveChild(profileNode);			
			}

			count++; 
		} 

		return;

	}
	//---------------------------------------------------------------------	
	void ProfileManager::SetCurProfile( CString profileName )
	{
		std::vector<QueryProfile>::iterator iter = GetProfiles().begin();	

		for (;iter != GetProfiles().end();iter++)
		{
			CString name = iter->GetName().c_str();
			if (name == profileName) 
			{
				m_curentprofile = *iter;
				return;
			}
		}
		return;
	}
	//---------------------------------------------------------------------	
	String ProfileManager::GetProfileNameByIndex( int index )
	{
		return m_profileList[index].GetName();
	}
	//---------------------------------------------------------------------	
	int ProfileManager::GetProfileListSize()
	{
		return m_profileList.size();
	}
	//---------------------------------------------------------------------	
}