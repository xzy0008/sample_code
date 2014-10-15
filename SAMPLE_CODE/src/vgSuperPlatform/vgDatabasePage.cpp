#include <vgStableHeaders.h>
#include "vgDatabasePage.h"

void vgDatabasePage::ConnectNode(vgBaseEntry* node, vector<DatabaseProperties>& propParamList)
{
	CBCGPProp*	pGroup = NULL;
	CBCGPProp*  prop = NULL;
	CBCGPProp*	option = NULL;

	m_pNode = node;

	//  测试决定是否打开
	//	m_wndPropList.RemoveAll();
	pGroup = new CBCGPProp("数据库属性");
	for (int i = 0; i< propParamList.size(); i++)
	{
		// 单独处理时间日期
		if (propParamList[i].data.vt == VT_DATE)
		{
			COleDateTime date = COleDateTime::GetCurrentTime ();
			
			pGroup->AddSubItem (new CBCGPDateTimeProp (CString(propParamList[i].label.c_str()), propParamList[i].data,
				_T("Set a date"), 0, CBCGPDateTimeCtrl::DTM_DATE));
		}
		else
		{
			prop = 	new CBCGPProp(propParamList[i].label.c_str(),
				propParamList[i].data
				/*propParam[i].comment.c_str()*/);
			pGroup->AddSubItem(prop);
			propParamList[i].pProp = prop;
		}


// 		switch (propParamList[i].typeId)
// 		{
// 		case PROP_ITEM_GROUP: 
// 			if (pGroup != NULL)
// 				m_wndPropList.AddProperty(pGroup);
// 			pGroup = new CBCGPProp(propParamList[i].label.c_str());
// 			propParamList[i].pProp = pGroup;
// 
// 			break;
// 		case PROP_ITEM_DATA:
// 			if (pGroup != NULL)
// 			{
// 				switch (propParamList[i].dataType)
// 				{
// 				case PROP_DATA_BOOL:
// 					/*ptrBool = (bool*)propParam[i].connectedPtr;*/
// 					prop = 	new CBCGPProp(propParamList[i].label.c_str(),
// 						propParamList[i].data
// 						/*propParam[i].comment.c_str()*/);
// 					pGroup->AddSubItem(prop);
// 					propParamList[i].pProp = prop;
// 
// 					break;
// 
// 				case PROP_DATA_INT:
// 					/*ptrInt = (long*)propParam[i].connectedPtr;*/
// 
// 					prop  = new CBCGPProp(propParamList[i].label.c_str(), 
// 						propParamList[i].data
// 						/*propParam[i].comment.c_str() */);
// 					// prop->EnableSpinControl(TRUE, LONG_MIN, LONG_MAX);
// 
// 					pGroup->AddSubItem(prop);
// 					propParamList[i].pProp = prop;
// 
// 					break;
// 
// 				case PROP_DATA_FLOAT:
// 					/*ptrFloat = (float*)propParam[i].connectedPtr;*/
// 					prop = new CBCGPProp(propParamList[i].label.c_str(),
// 						propParamList[i].data
// 						/*propParam[i].comment.c_str()*/);
// 
// 					pGroup->AddSubItem(prop);
// 					propParamList[i].pProp = prop;
// 
// 					break;
// 
// 				case PROP_DATA_DOUBLE:
// 					/*ptrDouble = (double*)propParam[i].connectedPtr;*/
// 					prop = new CBCGPProp(propParamList[i].label.c_str(),
// 						propParamList[i].data
// 						/*propParam[i].comment.c_str()*/);
// 					pGroup->AddSubItem(prop);
// 					propParamList[i].pProp = prop;
// 
// 					break;
// 
// 				case PROP_DATA_STR:
// 					/*ptrStr = (string*)propParam[i].connectedPtr;*/
// 					prop = new CBCGPProp(propParamList[i].label.c_str(),
// 						propParamList[i].data
// 						/*propParam[i].comment.c_str()*/);
// 
// 					pGroup->AddSubItem(prop);
// 					propParamList[i].pProp = prop;
// 
// 					break;

// 				case PROP_DATA_OPTION_START:
// 					ptrStr = (string*)propParam[i].connectedPtr;
// 					option = new CBCGPProp (propParam[i].label.c_str(),
// 						(*ptrStr).c_str(),
// 						propParam[i].comment.c_str());
// 					propParam[i].pProp = option;
// 
// 					break;
// 
// 				case PROP_DATA_OPTION_ITEM:
// 					option->AddOption(propParam[i].label.c_str());
// 					break;
// 
// 				case PROP_DATA_OPTION_END:
// 					option->AllowEdit (FALSE);
// 					pGroup->AddSubItem(option);
// 
// 					break;
// 
// 				case PROP_DATA_CONST_STR:
// 
// 					ptrStr = (string*)propParam[i].connectedPtr;
// 					prop = new CBCGPProp(propParam[i].label.c_str(),
// 						(*ptrStr).c_str(), 
// 						propParam[i].comment.c_str());
// 
// 					prop->AllowEdit(false);
// 					pGroup->AddSubItem(prop);
// 					propParam[i].pProp = prop;
// 
// 					break;

// 				default:
// 					//TRACE("Unknow Data Type \n");
// 					break;
// 				} // end inner switch

//			} // end if 
// 			break;
// 
// 		default:
// 			//TRACE("Unknow Item Type \n");
// 			break;
		//}
	}

	if (pGroup != NULL)
		m_wndPropList.AddProperty(pGroup);
}

LRESULT vgDatabasePage::OnPropertyChanged(WPARAM w, LPARAM l)
{
	CBCGPProp	*pProp = (CBCGPProp*)l;
	_variant_t	var = pProp->GetValue(); 
	string		name(pProp->GetName());

	m_pNode->OnDatabasePropertyChanged(name, var);

	return 0;
}