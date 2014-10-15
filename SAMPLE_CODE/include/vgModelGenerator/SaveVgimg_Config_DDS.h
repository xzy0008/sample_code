#pragma once


// CSaveVgimg_Config_DDS dialog

class CSaveVgimg_Config_DDS : public CDialog
{
	DECLARE_DYNAMIC(CSaveVgimg_Config_DDS)

public:
	CSaveVgimg_Config_DDS(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSaveVgimg_Config_DDS();

// Dialog Data
	enum { IDD = IDD_SAVEVGIMG_CONFIG_DDS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
