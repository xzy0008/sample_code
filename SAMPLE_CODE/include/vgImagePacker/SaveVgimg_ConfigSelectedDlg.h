
#include <vgStableHeaders.h>
#include "afxwin.h"



// CSaveVgimg_ConfigSelectedDlg dialog

class CSaveVgimg_ConfigSelectedDlg : public CDialog
{
	DECLARE_DYNAMIC(CSaveVgimg_ConfigSelectedDlg)

public:
	CSaveVgimg_ConfigSelectedDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSaveVgimg_ConfigSelectedDlg();

// Dialog Data
	enum { IDD = IDD_SAVEVGIMG_CONFIGSELECTEDDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_AimFileComboBox;
	virtual BOOL OnInitDialog();
	CString m_AimFileFormat;
	CStatic m_ConfigPos;

	//////////////////////////////////////////////////////////////////////////
	int NUM;
	CDialog* m_ConfigDlg[5];
	CRect m_DlgLargeRect;
	CRect m_DlgSmallRect;

	void setToLargeRect()
	{
		SetWindowPos( NULL , 0 , 0 , m_DlgLargeRect.Width() , m_DlgLargeRect.Height() ,
			SWP_NOMOVE | SWP_NOZORDER );

	}

	void setToSmallRect()
	{
		SetWindowPos( NULL , 0 , 0 , m_DlgSmallRect.Width() , m_DlgSmallRect.Height() ,
			SWP_NOMOVE | SWP_NOZORDER );
	}
	//////////////////////////////////////////////////////////////////////////
	afx_msg void OnBnClickedSavevgimgSelconClipsel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCbnSelchangeComboAimfileFormat();
};
