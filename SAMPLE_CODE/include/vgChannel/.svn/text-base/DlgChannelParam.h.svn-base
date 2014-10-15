#pragma once

#include <vgChannelResource.h>
#include "afxwin.h"
#include "afxcmn.h"

// DlgChannelParam 对话框

class DlgChannelParam : public CDialog
{
	DECLARE_DYNAMIC(DlgChannelParam)

public:
	DlgChannelParam(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgChannelParam();

// 对话框数据
	enum { IDD = IDD_DIALOG9 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult);
private:
	DWORD m_ipAddress;
	CBCGPGridCtrl	m_wndGrid;

public:
	int m_serverPort;
	int m_clientPort;
	int m_leftEdge;
	int m_rightEdge;
	float m_hOffset;
	float m_vOffset;
	int m_cameraOffset;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
private:
	CStatic m_wndGridLocation;
	CBCGPGridRow *sLastRow;
	void updateClientInfo();

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
	afx_msg void OnBnClickedUpdateParam();
	afx_msg void OnDestroy();
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	DWORD dwIPServerAddres;
	//CIPAddressCtrl m_IPControl;
	afx_msg void OnIpnFieldchangedIpserv(NMHDR *pNMHDR, LRESULT *pResult);
private:
	float m_eyePosOffset;

public:
	afx_msg void OnBnClickedBtnSavechannel();

};
