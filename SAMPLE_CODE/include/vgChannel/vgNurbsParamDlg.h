#pragma once
#include <vgChannelResource.h>
#include <vgConfig/vgcXMLConfigManager.h>
#include "vgchNurbsCorrectImpl.h"

// vgNurbsParamDlg 对话框

class vgNurbsParamDlg : public CDialog
{
	DECLARE_DYNAMIC(vgNurbsParamDlg)

public:
	vgNurbsParamDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~vgNurbsParamDlg();

// 对话框数据
	enum { IDD = IDD_DLG_NURBS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	
	void updateToNurbs();

private:
	int m_comboX;
	int m_comboY;
	float m_x;
	float m_y;
	float m_z;
	float m_w; 
	float m_right;
	float m_top;
	float m_bottom;
	float m_left;
public:
	float m_ctrlcorrect;
	float m_clipplane;

public:
	afx_msg void OnCbnSelchangeComboX();
	afx_msg void OnCbnSelchangeComboY();
	afx_msg void OnEnChangeEditX();
	afx_msg void OnEnChangeEditY();
	afx_msg void OnEnChangeEditZ();
	afx_msg void OnEnChangeEditW();
	afx_msg void OnEnChangeEditLeft();
	afx_msg void OnEnChangeEditRight();
	afx_msg void OnEnChangeEditTop();
	afx_msg void OnEnChangeEditBottom();
	afx_msg void OnEnChangeEditCtrlCorrect();
	afx_msg void OnEnChangeEditClipplane();


	afx_msg void OnDestroy();

	virtual BOOL OnInitDialog();

protected:
	virtual void OnOK();
	virtual void OnCancel();
private:
	CString Xmlfilename;
	CString Xmlsectionname;	

};
