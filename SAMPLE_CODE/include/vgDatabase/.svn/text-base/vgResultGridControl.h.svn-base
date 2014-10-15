#pragma once

#include <vgDatabase/vgdDefinition.h>

#ifdef VGD_DLL
#include <vgDatabaseDLL/vgDatabaseResource.h>
#else
#include <vgLibraryResource.h>
#endif

#include "AdoImport.h"

#include "ado.h"


#include <BCGPADOGridCtrl.h>

class  VGD_EXPORT ResultGridControl : public CBCGPADOGridCtrl
{
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);

	void OnMenuDelete();
	
	afx_msg void OnPopupToobject();
	afx_msg void OnMenuInsert();
};