/*----------------------------------------------------------------------*
 |
 |	FILE: Collector.h
 |	AUTH: Harry Denholm, Kinetix
 |		  Copyright (c) 1998, All Rights Reserved.
 |
 *----------------------------------------------------------------------*/

#ifndef __COLLECTOR__H
#define __COLLECTOR__H

#include "vgStableHeaders.h"


class CMtlEnum;
class Collection;


class CMtlEnum {
public:

	virtual void  proc(MtlBase *m);

	void CreateNewFilename(TCHAR * name, TCHAR * newFile);

	bool IsDynamicDxMaterial(MtlBase * newMtl);

	CMtlEnum(UtilityObj* uti)
		:_utiObj(uti)	{	}

public:
	void	setUtilityObj(UtilityObj* uti);

private:
	UtilityObj* _utiObj;
};


class Collection : public UtilityObj {
public:
	IUtil *iu;
	Interface *ip;
	HWND hPanel;

	char WZPath[255];
	BOOL WZisHere;

	Collection();
	~Collection();

	NameTab mapPaths;

	void BeginEditParams(Interface *ip,IUtil *iu);
	void EndEditParams(Interface *ip,IUtil *iu);
	void DeleteThis() {}

	void Init(HWND hWnd);
	void Destroy(HWND hWnd);
	void NodeEnum(INode *root);
	void CEnumMtlTree(MtlBase *mb, CMtlEnum &tenum);

	CMtlEnum	mtlEnum;

	friend	static INT_PTR CALLBACK CollectionDlgProc(
		HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};


class CollectionClassDesc:public ClassDesc {
public:
	int 			IsPublic() {return 1;}
	void *			Create(BOOL loading = FALSE);// {return &theCollection;}
	const TCHAR *	ClassName() ;//{return GetString(IDS_RESOURCE_COLLECTOR);}
	SClass_ID		SuperClassID() {return UTILITY_CLASS_ID;}
	Class_ID		ClassID();// {return CL_CLASSID;}
	const TCHAR* 	Category() ;
	
	UtilityObj*		GetCollectionUtility();
private:
	UtilityObj*		_utilityObj;
};

#endif
