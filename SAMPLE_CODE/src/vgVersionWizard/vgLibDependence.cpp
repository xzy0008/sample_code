#include <vgStableHeaders.h>
#include <vgLibDependence.h>

DependenceMap	 gs_libMap;
VersionInfoVec	 gs_versionVec;

int vgInitDependenceVec()
{
	string fileName;

	char   pathbuf[512];   
	int   pathlen   =   ::GetModuleFileName(NULL, pathbuf, 512);   

	while(TRUE)   
	{   
		if   (pathbuf[--pathlen]=='\\')   
			break;   
	}   
	pathbuf[++pathlen]   =   0x0;    

	fileName = pathbuf;
	fileName += "vgLibDependence.ini";

	ifstream inFile(fileName.c_str());

	if (! inFile.is_open())
	{
		AfxMessageBox("INI文件打开错误.");
		return -1;
	}

	string libName;
	string depName;
	int depCnt;

	while (inFile >> libName)
	{
		if (libName == "=VersionInfo=")
		{
			break;
		}

		inFile >> depCnt;
		TRACE("%s %d\n", libName.c_str(), depCnt);

		DependenceVec* pVec = new DependenceVec;

		for (int i=0; i<depCnt; i++)
		{
			inFile >> depName;
			pVec->push_back(depName);		
			TRACE("%s\n", depName.c_str());
		}
		
		gs_libMap[libName] = pVec;
	}

	string versionName;
	int libCnt;

	TRACE("=============== Version Info ==================\n");
	VersionDef versionInfo;
	
	char buffer[256];

	while (inFile.getline(buffer, 256) != 0)
	{
		if (strlen(buffer) > 1)
		{
	 		inFile >> libCnt;
	 
	 		TRACE("%s %d \n", versionName.c_str(), libCnt);
	 
	 		versionInfo.versionTitleName = buffer;
	 		versionInfo.incld = new LibStrVec;
	 
	 		for (int i=0; i<libCnt; i++)
	 		{
	 			inFile >> libName; 
	 			versionInfo.incld->push_back(libName);
	 			
	 			TRACE("%s \n", libName.c_str());
	 		}
	 
	 		gs_versionVec.push_back(versionInfo);
		}
	}
// 
// 	while (inFile >> versionName)
// 	{
// 		inFile >> libCnt;
// 
// 		TRACE("%s %d \n", versionName.c_str(), libCnt);
// 
// 		versionInfo.versionTitleName = versionName;
// 		versionInfo.incld = new LibStrVec;
// 
// 		for (int i=0; i<libCnt; i++)
// 		{
// 			inFile >> libName; 
// 			versionInfo.incld->push_back(libName);
// 			
// 			TRACE("%s \n", libName.c_str());
// 		}
// 
// 		gs_versionVec.push_back(versionInfo);
// 	}

	inFile.close();

	return 0;
}

int vgCleanUpDependenceVec()
{
	DependenceMap::iterator iter = gs_libMap.begin();
	DependenceMap::iterator end  = gs_libMap.end();

	while (iter != end)
	{
		if (iter->second != NULL)
		{
			delete iter->second;
		}
		iter ++;
	}
	
	for (int i=0; i<gs_versionVec.size(); i++)
	{
		if (gs_versionVec[i].incld != NULL)
		{
			delete gs_versionVec[i].incld;
		}
	}
	return 0;
}

int vgInitDependenceGrid(CCellTypesGridCtrl &gridCtrl)
{

	DependenceMap::iterator iter = gs_libMap.begin();
	DependenceMap::iterator end  = gs_libMap.end();

	while (iter != end)
	{
		CBCGPGridRow* pRow = gridCtrl.CreateNewRow ();

		pRow->ReplaceItem (0, new CBCGPGridCheckItem(FALSE) );
		pRow->GetItem(0)->Enable(TRUE);
		pRow->GetItem (1)->SetValue ((iter->first).c_str());
		pRow->Enable(TRUE);
		gridCtrl.AddRow(pRow,FALSE);

		iter ++;
	}
	gridCtrl.LoadState (_T("CellTypesGrid"));
	gridCtrl.AdjustLayout();

	return 0;
}

int vgCheckVersionGrid(int curSel, CCellTypesGridCtrl &gridCtrl)
{
	// 设置各个版本的默认参数
	if (curSel != gs_versionVec.size())
	{
		for (int j=0; j<gridCtrl.GetRowCount(); j++)
		{
			CBCGPGridCheckItem* pCheck = dynamic_cast<CBCGPGridCheckItem*>(gridCtrl.GetRow(j)->GetItem(0));
			_variant_t bVal = pCheck->GetValue();
			bVal.boolVal = FALSE;

			pCheck->SetValue(bVal);
		}
		
		for (int i=0; i<gs_versionVec[curSel].incld->size(); i++)
		{
			vgCheckLibItem(gs_versionVec[curSel].incld->at(i), gridCtrl);
		}
	}

	return 0;
}

int vgCheckLibItem(string libName, CCellTypesGridCtrl &gridGtrl)
{
	DependenceVec *pDepVec = gs_libMap[libName];

	if (pDepVec == NULL)
	{
		return -1;
	}

	for (int j=0; j<gridGtrl.GetRowCount(); j++)
	{
		_variant_t val = gridGtrl.GetRow(j)->GetItem(1)->GetValue();
		_variant_t bVal;
		
		string dllName = _com_util::ConvertBSTRToString(val.bstrVal);
		CBCGPGridCheckItem* pCheck = dynamic_cast<CBCGPGridCheckItem*>(gridGtrl.GetRow(j)->GetItem(0));
		bVal = pCheck->GetValue();

		if (dllName == libName)
		{
			bVal = true;
			pCheck->SetValue(bVal);
		}
	}

	for (int i=0; i<pDepVec->size(); i++)
	{
		vgCheckLibItem(pDepVec->at(i), gridGtrl);
	}

	return 0;
}


bool isDef(string libA, string libB)
{
	DependenceVec *pVec = gs_libMap[libA];

	if (pVec == NULL || pVec->size() == 0)
	{
		return false;
	}

	for (int i=0; i<pVec->size(); i++)
	{
		if (pVec->at(i) == libB || isDef(pVec->at(i), libB))
		{
			return true;
		}
	}

	return false;
}

vector<string> searchDep(string libB)
{
	vector<string> re;

	DependenceMap::iterator iter = gs_libMap.begin();
	DependenceMap::iterator end  = gs_libMap.end();

	while (iter != end)
	{
		if (isDef(iter->first, libB))
		{
			re.push_back(iter->first);
		}
		iter ++;
	}

	return re;

}

int vgUnCheckLibItem(string libName, CCellTypesGridCtrl &gridGtrl)
{
	vector<string> depVec = searchDep(libName);

	for (int j=0; j<gridGtrl.GetRowCount(); j++)
	{
		_variant_t val = gridGtrl.GetRow(j)->GetItem(1)->GetValue();
		_variant_t bVal;

		string dllName = _com_util::ConvertBSTRToString(val.bstrVal);
		CBCGPGridCheckItem* pCheck = dynamic_cast<CBCGPGridCheckItem*>(gridGtrl.GetRow(j)->GetItem(0));
		bVal = pCheck->GetValue();

		if (find(depVec.begin(), depVec.end(), dllName) != depVec.end())
		{
			bVal = false;
			pCheck->SetValue(bVal);
		}
	}

	return -1;
}

