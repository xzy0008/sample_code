#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vgDatabase/vgdDefinition.h>

#include <afxole.h>

#ifdef VGD_DLL
#include <vgDatabaseDLL/vgDatabaseResource.h>
#else
#include <vgLibraryResource.h>
#endif


#include <BCGPTabWnd.h>
#include <vgDatabase/vgResultGridControl.h>  
#include <vgDatabase/explorer1.h>
#include <afxhtml.h>
// DBConditionTab3 对话框


class  VGD_EXPORT DBConditionTab3 : public CDialog
{
	DECLARE_DYNAMIC(DBConditionTab3)

public:
	DBConditionTab3(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DBConditionTab3();

// 对话框数据
	enum { IDD = IDD_DB_CDTAB3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

protected:
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();

	CWnd* m_pParent;	
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	CExplorer1 m_htmlControl;

	afx_msg void OnBnClickedButton1();//  [12/4/2008 yuxin]

};
