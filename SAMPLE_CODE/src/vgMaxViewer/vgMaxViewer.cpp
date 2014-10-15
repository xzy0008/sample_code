/*----------------------------------------------------------------------*
 |
 |	FILE: Collector.cpp
 | 
 |	DESC: Resource Collection plugin
 |
 |	AUTH: Harry Denholm, Kinetix
 |		  Copyright (c) 1998, All Rights Reserved.
 |
 |	HISTORY: 27.2.98
 |
 *----------------------------------------------------------------------*/

#include "vgStableHeaders.h"

#include "vgMaxViewer.h"

#include "vgModViewerUtility.h"
#include "vgUtility/vgModCommonUtility.h"
#include "vgModViewer.h" 




// Callback class for retrieving light distribution files	
class EnumLightDistFileCallBack : public NameEnumCallback
{
public:

	NameTab fileList;
	int size;

	EnumLightDistFileCallBack() { size = 0; }

	void RecordName(TCHAR *name)
	{
		//convert to lower case
		//SS 3/17/2003 defect 490612: The size of the filename buffer in BitmapInfo is
		// MAX_PATH, or 260 characters. We need that same size here.
		TCHAR buf[MAX_PATH];
		_tcscpy_s(buf, MAX_PATH, name);
		int i = 0;
		while(buf[i] && i <100)	{
			buf[i] = _totlower(buf[i]);
			i++;
		}
		// check for distribution types before appending.
		if(_tcsstr(buf, ".ies") || 
			_tcsstr(buf, ".cibse") ||
			_tcsstr(buf, ".ltli"))		{
			if(fileList.FindName(name) < 0)	{
				fileList.AddName(name);
				size++;
			}
		}
			
	}
};

EnumLightDistFileCallBack distributionLister;
//-do the material enumeration----------------------------------------------------
void Collection::CEnumMtlTree(MtlBase *mb, CMtlEnum &tenum) {
	tenum.proc(mb);
	for (int i=0; i<mb->NumSubTexmaps(); i++) {
		Texmap *st = mb->GetSubTexmap(i); 
		if (st) 
			CEnumMtlTree(st,tenum);
		}
	if (IsMtl(mb)) {
		Mtl *m = (Mtl *)mb;
		for (int  i=0; i<m->NumSubMtls(); i++) {
			Mtl *sm = m->GetSubMtl(i);
			if (sm) 
				CEnumMtlTree(sm,tenum);
			}
		}
	}// Enumerate the scene
void Collection::NodeEnum(INode *root)
{
	for (int k=0; k<root->NumberOfChildren(); k++)
	{
		INode *node = root->GetChildNode(k);
		MtlBase* mat = (MtlBase*)node->GetMtl();
		if (mat)
			CEnumMtlTree(mat,mtlEnum);
		// enumerate light distribution files
		node->EnumAuxFiles(distributionLister, FILE_ENUM_ALL);
		if(node->NumberOfChildren()>0) NodeEnum(node);
	}
}


Collection::Collection()
:mtlEnum(this)
{
	iu = NULL;
	ip = NULL;	
	hPanel = NULL;
}

Collection::~Collection()
{
	
}

static BOOL CheckWinZip()
{
	HKEY	hKey;
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\classes\\WinZip", 0, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
		return FALSE;
	else
		return TRUE;
}
static void FindWinZipDir(TCHAR *Path)
{
	HKEY	hKey;
	long	kSize;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\classes\\WinZip\\shell\\open\\command", 0, KEY_ALL_ACCESS, &hKey);
	RegQueryValue(hKey,NULL,Path,&kSize);
}

void Collection::BeginEditParams(Interface *ip,IUtil *iu) 
{
	this->iu = iu;
	this->ip = ip;
	hPanel = ip->AddRollupPage(
		vgModUtility::getInstance(),
		MAKEINTRESOURCE(IDD_CL_PANEL),
		CollectionDlgProc,
		vgModUtility::GetString(IDS_PARAMETERS),
		0);

	mapPaths.ZeroCount();

	// Do a simple registry check for WinZip
	WZisHere = CheckWinZip();
	if(WZisHere) FindWinZipDir(WZPath);
		EnableWindow(GetDlgItem(hPanel,IDC_PACKUP),WZisHere);
		EnableWindow(GetDlgItem(hPanel,IDC_STATICPACK),WZisHere);
}
	
void Collection::EndEditParams(Interface *ip,IUtil *iu) 
{
	this->iu = NULL;
	ip->DeleteRollupPage(hPanel);
	hPanel = NULL;
}

void Collection::Init(HWND hWnd)
{
	// Set our defaults
#if 0
	SetCheckBox(hWnd,IDC_UPMAP,FALSE);
	SetCheckBox(hWnd,IDC_PACKMAX,FALSE);
	SetCheckBox(hWnd,IDC_PACKUP,FALSE);
	SetCheckBox(hWnd,IDC_TYPE2,FALSE);

	SetCheckBox(hWnd,IDC_PACKMAPS,TRUE);
	SetCheckBox(hWnd,IDC_TYPE,TRUE);
#endif
	SetCheckBox(hWnd,IDC_COLLECT_OPTION_PIC,TRUE);
	SetCheckBox(hWnd,IDC_COLLECT_OPTION_MOD,TRUE);
	SetCheckBox(hWnd,IDC_COLLECT_OPTION_MAX,FALSE);

	SetWindowText(GetDlgItem(hWnd,IDC_PATH),ip->GetDir(APP_SCENE_DIR));
}

void Collection::Destroy(HWND hWnd)
{
	vgModViewer::resetViewer();
}


//-----CollectionClassDesc--------------------------------------------------------
void * CollectionClassDesc::Create( BOOL loading /*= FALSE*/ )
{
	_utilityObj = new Collection;

	vgModViewerUtility::setCollectionUtility( (Collection*)_utilityObj );

	return _utilityObj;
}

Class_ID CollectionClassDesc::ClassID()
{
	return CL_CLASSID;
}

const TCHAR* CollectionClassDesc::Category()
{
	return vgModUtility::GetString(IDS_UTILITY_CATEGORY);
}

const TCHAR * CollectionClassDesc::ClassName()
{
#if _DEBUG
	return vgModUtility::GetString(IDS_MAX_VIEWER_D);
#else
	return vgModUtility::GetString(IDS_MAX_VIEWER);
#endif
}

UtilityObj* CollectionClassDesc::GetCollectionUtility()
{
	return _utilityObj;
}


//---CMtlEnum----------------------------------------------------------------------
void CMtlEnum::proc( MtlBase *m )
{
	Collection* exp = dynamic_cast<Collection*>( _utiObj );

	Interface *ip;
	ip = exp->ip;

	// Check for bitmaptex, and cast
	if(m->ClassID()==Class_ID(BMTEX_CLASS_ID,0)) {
		Texmap *bt = (Texmap*)m;
		BitmapTex *b = (BitmapTex*)bt;

		if(_stricmp(b->GetMapName(),"")!=0){

			// Use the very useful BMMGetFull.. to scan for existing files
			BitmapInfo bi(b->GetMapName());
			BMMGetFullFilename(&bi);

			char Bname[MAX_PATH];
			strcpy_s(Bname,MAX_PATH,bi.Name());

			// If our found file exists, add it to the list
			if(BMMIsFile(Bname)){
				char s[256];
				sprintf_s(s,256,"%s",Bname);

				// check for update, and do so if needed
				BOOL upd = GetCheckBox(exp->hPanel,IDC_UPMAP);
				if (upd) {
					char fnl[MAX_PATH];
					CreateNewFilename(Bname,fnl);
					b->SetMapName(fnl);
				}

				if(exp->mapPaths.FindName(Bname)==-1){
					exp->mapPaths.AddName(s);
				}
			}
		}
	}
	if(IsDynamicDxMaterial(m))
	{
		IDxMaterial * idxm = (IDxMaterial*)m->GetInterface(IDXMATERIAL_INTERFACE);
		int bitmapCount = idxm->GetNumberOfEffectBitmaps();
		for(int j=0; j<bitmapCount;j++)
		{
			PBBitmap* bmap = idxm->GetEffectBitmap(j);
			char Bname[MAX_PATH];
			strcpy_s(Bname,MAX_PATH, bmap->bi.Name());
			// add an entry in the data type index
			BOOL upd = GetCheckBox(exp->hPanel,IDC_UPMAP);
			if (upd) {
				char fnl[MAX_PATH];
				CreateNewFilename(Bname,fnl);
				PBBitmap newBitmap;
				newBitmap.bi.SetName(fnl);
				idxm->SetEffectBitmap(j,&newBitmap);
			}
			if(exp->mapPaths.FindName(Bname)==-1)
				exp->mapPaths.AddName(Bname);


		}
		PBBitmap * bm;
		bm = idxm->GetSoftwareRenderBitmap();
		if(bm)
		{
			char Bname[MAX_PATH];
			strcpy_s(Bname,MAX_PATH, bm->bi.Name());
			BOOL upd = GetCheckBox(exp->hPanel,IDC_UPMAP);
			if (upd) {
				char fnl[MAX_PATH];
				CreateNewFilename(Bname,fnl);
				PBBitmap newBitmap;
				newBitmap.bi.SetName(fnl);
				idxm->SetSoftwareRenderBitmap(&newBitmap);
			}
			if(exp->mapPaths.FindName(Bname)==-1)
				exp->mapPaths.AddName(Bname);

		}
		TCHAR * effectFile = idxm->GetEffectFilename();
		char Bname[MAX_PATH];
		strcpy_s(Bname, MAX_PATH, effectFile);
		BOOL upd = GetCheckBox( exp->hPanel,IDC_UPMAP);
		if (upd) {
			char fnl[MAX_PATH];
			CreateNewFilename(Bname,fnl);
			idxm->SetEffectFilename(fnl);
		}
		if(exp->mapPaths.FindName(Bname)==-1)
			exp->mapPaths.AddName(Bname);

	}
}

void CMtlEnum::CreateNewFilename( TCHAR * name, TCHAR * newFile )
{
	Collection* exp = dynamic_cast<Collection*>( _utiObj );

	Interface *ip;
	ip = exp->ip;

	TCHAR tfile[MAX_PATH];
	TCHAR textn[MAX_PATH];
	char to_path[255];
	GetWindowText(GetDlgItem(exp->hPanel,IDC_PATH),to_path,254);

	BMMSplitFilename(name, NULL, tfile, textn);
	BMMAppendSlash(to_path);
	sprintf_s(newFile,MAX_PATH,"%s%s%s",to_path,tfile,textn);

}

bool CMtlEnum::IsDynamicDxMaterial( MtlBase * newMtl )
{

	DllDir * lookup = GetCOREInterface()->GetDllDirectory();
	ClassDirectory & dirLookup = lookup->ClassDir();

	ClassDesc * cd = dirLookup.FindClass(MATERIAL_CLASS_ID,newMtl->ClassID());
	if(cd && cd->SubClassID() == DXMATERIAL_DYNAMIC_UI)
		return true;
	else
		return false;


}

void CMtlEnum::setUtilityObj( UtilityObj* uti )
{
	_utiObj = uti;
}


//---CollectionDlgProc-----------------------------------------------------------------
static INT_PTR CALLBACK CollectionDlgProc(
	HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//Interface *ip;
	//ip = theCollection.ip;
	Collection* exp = NULL; 
	Interface* ip = NULL;

	switch (msg) 
	{
		case WM_INITDIALOG:
			exp = vgModViewerUtility::getCollectionUtility() ;
			exp->Init(hWnd);
			break;

		case WM_DESTROY:
			exp = vgModViewerUtility::getCollectionUtility();
			exp->Destroy(hWnd);
			break;

		case WM_COMMAND:
			switch(HIWORD(wParam))
			{
			case EN_SETFOCUS :
				DisableAccelerators();
				break;
			case EN_KILLFOCUS :
				EnableAccelerators();
				break;
			}

			switch (LOWORD(wParam)) {

		case IDC_BROWSE:
			{
				TCHAR dir[256];
				TCHAR desc[256];
				_tcscpy_s(desc, sizeof(desc), vgModUtility::GetString(IDS_TARGET_DIRECTORY));

				exp = vgModViewerUtility::getCollectionUtility();

				exp->ip->ChooseDirectory(hWnd, vgModUtility::GetString(IDS_CHOOSE_OUTPUT), dir, desc);
				SetWindowText(GetDlgItem(hWnd,IDC_PATH),dir);
				break;
			}
			

		case IDC_EXPORT_MOD_EXP:
			{
				vgModViewerUtility::exportMODThenView();
			}

			break;

		case IDC_EXPORT_MOD_VIEW:
			{
				vgModViewerUtility::exportMODAndView();
			}
			break;

		case IDC_EXPORT_MOD_SAVE:
			{
				vgModViewerUtility::exportMODAndSave();
			}
			break;

		case IDC_EXPORT_MOD_COLLECT:
			{
				::MessageBox(NULL, "请设置好相关参数，然后执行收集！", "收集文件！", MB_OK);
			}
			break;

		case IDC_EXPORT_MOD_EXCUTE:
			{
				//vgModViewerUtility::exportMODAndCollect();
				exp = vgModViewerUtility::getCollectionUtility();
				ip = exp->ip;

				char to_path[255];
				char fnl[MAX_PATH];
				GetWindowText(GetDlgItem(hWnd,IDC_PATH),to_path,254);
				string destPath(to_path);
				
				if ( destPath.empty() )
				{
					::MessageBox(NULL, "输出路径为空，请重新设置！", "收集文件！", MB_OK);
					break;
				}
				


				UI_MAKEBUSY

				exp->mapPaths.ZeroCount();

				// Collect bitmaps
				BOOL doMAPS = GetCheckBox(hWnd,IDC_COLLECT_OPTION_PIC);

				if(doMAPS) 
				{
					INode *root = ip->GetRootNode();
					exp->NodeEnum(root);
				}

				// Check and store MAX File
				BOOL doMAX = GetCheckBox(hWnd,IDC_COLLECT_OPTION_MAX);
				if (doMAX)
				{
					string maxFilename = ip->GetCurFilePath().data();
					if ( !maxFilename.empty())
					{
						exp->mapPaths.AddName(ip->GetCurFilePath()); 

					}
					else
					{
						TSTR msg;
						msg.printf( vgModUtility::GetString(IDS_NO_VALID_FILE_PATH_MAX));
						MessageBox(NULL, msg, vgModUtility::GetString(IDS_WARNING), MB_OK);
					}
				}

				// Check and store MOD File
				BOOL doMOD = GetCheckBox(hWnd,IDC_COLLECT_OPTION_MOD);
				if (doMAX)
				{
					string maxFilename = vgModViewer::getFileNameMod();
					if ( !maxFilename.empty())
					{
						exp->mapPaths.AddName( MSTR(maxFilename.c_str()) ); 

					}
					else
					{
						TSTR msg;
						msg.printf(vgModUtility::GetString(IDS_NO_VALID_FILE_PATH_MOD));
						MessageBox(NULL, msg, vgModUtility::GetString(IDS_WARNING), MB_OK);
					}
				}



				// then do copy/move command
				for (int q=0; q<exp->mapPaths.Count(); q++)
				{
					TCHAR tfile[MAX_PATH];
					TCHAR textn[MAX_PATH];

					BMMSplitFilename(exp->mapPaths[q], NULL, tfile, textn);
					BMMAppendSlash(to_path);

					sprintf_s(fnl,MAX_PATH, "%s%s%s",to_path,tfile,textn);

					CopyFile(exp->mapPaths[q],fnl,FALSE);

				}

				UI_MAKEFREE

				ip->RedrawViews(ip->GetTime());

				::MessageBox(NULL, fnl, "保存完成！", MB_OK);

			}
			break;
			}
			break;

		default:
			return FALSE;
	}
	return TRUE;
}	

//----------------------------------------------------------------
