#include <vgStableHeaders.h>
#include <vgEntry/vgDatabaseEntry.h>
#include <vgUIController/vgUIController.h>

vgDatabasePage vgDatabaseEntry::s_databasePage;

vector<DatabaseProperties> vgDatabaseEntry::s_databaseParam; 

String vgDatabaseEntry::s_groupProfileName = "";

// void vgDatabaseEntry::AddNodeTabs()
// {
// 	vgGroupBasedEntry::AddNodeTabs();
// }

vgDatabaseEntry::vgDatabaseEntry( vgKernel::Renderer* renderer ) : vgGroupBasedEntry(renderer)
{
	vgKernel::DatabaseRendererData* pRendererData = (vgKernel::DatabaseRendererData*)(m_Renderer->getRendererDataByType(vgKernel::RDT_DATABASE_PROFILE));

	if (pRendererData == NULL)
	{
		pRendererData = new vgKernel::DatabaseRendererData();
		pRendererData->profile = "";

		m_Renderer->addRendererData(pRendererData);
	}

	m_profileName = pRendererData->profile;
}

void vgDatabaseEntry::AddSingleTabPage()
{
	vgPropertiesViewBar* pageViewBar = vgUI::UIController::getSingleton().GetPropertiesViewBar();

	initDatabaseParam();
	if (s_databaseParam.size() > 0)
	{
		s_databasePage.Create(NIDD_PROPERTY, pageViewBar->GetTabControl());
		s_databasePage.ConnectNode(this, s_databaseParam);
		pageViewBar->AddTab("数据库属性", &s_databasePage);
	}
};

void vgDatabaseEntry::initDatabaseParam()
{
	s_databaseParam.clear();

	if (! vgDatabase::DatabaseManager::getSingleton().IsOpen())
	{
		return ;
	}

	vector<vgDatabase::QueryProfile> profiles = vgDatabase::ProfileManager::getSingleton().GetProfiles();

	for (INT i=0; i<profiles.size(); i++)
	{
		if (profiles[i].GetName() == m_profileName)
		{
			m_queryString = vgDatabase::ProfileManager::getSingleton().CreateQuery(m_profileName.c_str());
			m_queryString += "'";
			m_queryString += m_Renderer->getName();//this->getSearchName();//YXDBNAME
			m_queryString += "'";

			// AfxMessageBox(m_queryString.c_str());

			CADORecordset* recordSet = vgDatabase::DatabaseManager::getSingleton().GetConnectorPtr()->Execute(m_queryString);
			
			if (recordSet == NULL)
			{
				AfxMessageBox("查询未能成功执行 请检查Profile是否正确");
				return ;
			}
			
			CADOFieldInfo fieldInfo;
			DatabaseProperties param;
			vgDatabase::QueryProfile *pProfile = vgDatabase::ProfileManager::getSingleton().GetProfile(m_profileName);

			if (pProfile != NULL && recordSet->GetRecordCount() > 0)
			{
				for (int i=0; i<recordSet->GetFieldCount(); i++)
				{
					recordSet->GetFieldValue(i, param.data);
					recordSet->GetFieldInfo(i, &fieldInfo);

					// decimal 不被BCG PorpList所支持
					if (param.data.vt == VT_DECIMAL)
					{
						param.data.vt = VT_I4;
					}
					param.label = fieldInfo.m_strName;

					for (int j=0; j<pProfile->m_shownNameList.size(); j++)
					{
						if (pProfile->m_shownNameList[j] == param.label)
						{
							param.recordLable = pProfile->m_recordList[j];
						}
					}
					s_databaseParam.push_back(param);

				}
			}

			recordSet->Close();

			//return ;
		}
	}
	return ;
}

void vgDatabaseEntry::OnDatabasePropertyChanged(String paraName, _variant_t dataValue)
{
	CString outString(dataValue);

	CADORecordset* recordSet = vgDatabase::DatabaseManager::getSingleton().GetConnectorPtr()->Execute(m_queryString);
	
	if (recordSet == NULL)
	{
		AfxMessageBox("查询未能成功执行 请检查Profile");
		
		return ;
	}

	CADOFieldInfo fieldInfo;

	if(recordSet->GetRecordCount() > 0)
	{
		for (int i=0; i<recordSet->GetFieldCount(); i++)
		{
			recordSet->GetFieldInfo(i, &fieldInfo);
			if (fieldInfo.m_strName == paraName)
			{
				// 与初始化对应 因为BCG不支持DECIMAL
				if (dataValue.vt == VT_I4)
				{
					dataValue.vt = VT_DECIMAL;
				}

				recordSet->Edit();
				recordSet->SetFieldValue(i, dataValue);
				if (! recordSet->Update())
					AfxMessageBox("更新失败");

				recordSet->Close();

				return ;
			}
		}

	}

	AfxMessageBox("未知字段.");
	return ;
}


void vgDatabaseEntry::OnSinglePropertyChanged(String paramName)
{
	//AfxMessageBox("Single Profile Changed !");

	if (paramName == "数据库配置")
	{
		vgKernel::DatabaseRendererData* pRendererData = (vgKernel::DatabaseRendererData*)(m_Renderer->getRendererDataByType(vgKernel::RDT_DATABASE_PROFILE));

		ASSERT(pRendererData != NULL);

		pRendererData->profile = m_profileName;
	}
}

void vgDatabaseEntry::OnGroupPropertyChanged(String paramName)
{
	if (paramName == "数据库配置")
	{
		AfxMessageBox("Group profile changed! ");

		for (int i=0; i<s_group_list.size(); i++)
		{
			((vgDatabaseEntry*)s_group_list[i])->m_profileName = s_groupProfileName;
			vgKernel::DatabaseRendererData* pRendererData = 
				(vgKernel::DatabaseRendererData*)(s_group_list[i]->getRender()->getRendererDataByType(vgKernel::RDT_DATABASE_PROFILE));

			ASSERT(pRendererData != NULL);

			pRendererData->profile = s_groupProfileName;
		}

		return ;
	}
}