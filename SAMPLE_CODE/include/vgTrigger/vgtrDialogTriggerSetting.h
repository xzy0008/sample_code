#pragma once

#include <vgTriggerResource.h>
#include <vgTrigger/vgtrDefinition.h>
#include "afxwin.h"
// CDialogTriggerSetting 对话框

class VGTRI_EXPORT CDialogTriggerSetting : public CDialog
{
	DECLARE_DYNAMIC(CDialogTriggerSetting)

public:
	CDialogTriggerSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogTriggerSetting();

// 对话框数据
	enum { IDD = IDD_DLG_TRIGGER_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	CString m_attachName;
public:
	CComboBox m_attachType;
	// CString m_attachInfo;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CString m_triggerName;

private:
	void updateControlData();

private:

	CStatic m_tabLoc;

	CBCGPTabWnd	m_wndTab;

	CEdit		m_wndEntrance;
	CEdit		m_wndExit;
	CEdit		m_wndClick;
	CComboBox m_configComboBox;

public:
	afx_msg void OnBnClickedUpdate();
	afx_msg void OnCbnSelchangeConfigCombo();
private:
	CComboBox m_triggerNameCombo;
public:
	afx_msg void OnCbnSelchangeComboTiggername();
};
