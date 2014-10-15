
#ifndef _AutoLoadDialog_H
#define _AutoLoadDialog_H

#include "Resource.h"

#include <vgDeprecated/LoadProgressCtrl.h>
#include <vgDeprecated/ShockwaveFlashCtrl.h>



// CAutoLoadDialog 对话框


class VGDEP_EXPORT CAutoLoadDialog : public CDialog
{
	DECLARE_DYNAMIC(CAutoLoadDialog)

public:
	CAutoLoadDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAutoLoadDialog();

	// 对话框数据
	enum { IDD = IDD_DLG_AUTOLOAD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:


	static CLoadProgressCtrl m_ProgresssCtl;

	static int SetPos(int nPos);
	static int SetStep(int nStep);
	static void SetRange(int nLower, int nUpper);
	static int  SetPosWithRange(int nLower, int nUpper, float nStep);

	static bool isValid();
	virtual BOOL OnInitDialog();

private:
	int m_nLower, m_nUpper;
	int m_curpos;
	CShockwaveflash m_FlashPlayerCtrl;

	int _nAlphaValue;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
protected:
	virtual void OnOK();
	virtual void OnCancel();

};

#endif