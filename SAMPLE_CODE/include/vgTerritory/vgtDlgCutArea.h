#pragma once


#include <vgTerritory/vgtDefinition.h>
#include <bcgpedit.h>

#ifdef VGT_DLL
#include <vgTerritoryResource.h>
#else
#include <vgLibraryResource.h>
#endif


// vgtDlgCutArea dialog

class vgtDlgCutArea : public CDialog
{
	DECLARE_DYNAMIC(vgtDlgCutArea)

public:
	vgtDlgCutArea(CWnd* pParent = NULL);   // standard constructor
	virtual ~vgtDlgCutArea();

// Dialog Data
	enum { IDD = IDD_VGT_CUTAREA_DLG };

	CBCGPEdit	m_wndFileEdit;

	CString _abspath;

	String getPath();

	String getMetaName();

	String getAbsName();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
};
