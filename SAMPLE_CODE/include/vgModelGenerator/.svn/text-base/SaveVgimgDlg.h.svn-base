


#include "ReportCtrl.h"
#include "vgSmallOpenGLWindow.h"
#include <vgKernel/vgkSharePtr.h>
#include <vgKernel/vgkProcessObserver.h>

// CSaveVgimgDlg dialog


typedef std::pair<String,String> StringPair;
typedef std::vector< StringPair > StringPairList;
typedef vgKernel::SharePtr< StringPairList > StringPairListPtr;


class CSaveVgimgDlg : public CDialog, public vgKernel::ProcessObserver
{
	DECLARE_DYNAMIC(CSaveVgimgDlg)

public:
	CSaveVgimgDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSaveVgimgDlg();

// Dialog Data
	enum { IDD = IDD_SAVEVGIMGDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedImportFiles();

private:

	SmallOpenGLWindow m_oglWindow;
	//////////////////////////////////////////////////////////////////////////
	CReportCtrl m_wndList;
	BOOL m_bSortable;

	int m_CurrentFileID;

	CProgressCtrl _processBar;
	virtual void onStart( const String& text , const int& range_lower , 
		const int& range_upper );

	// 显示进度.0到100之间
	virtual void onNotify( const String& msg , 
		const int& process_pos );

	virtual void onFinish( const String& msg );


	String getBasenameFromFilepath( const String& filepath );

	//////////////////////////////////////////////////////////////////////////

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();

	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedSavevgimgSelectedall();
	afx_msg void OnBnClickedSavevgimgCancelselected();
	afx_msg void OnBnClickedSavevgimgInvertselected();
	afx_msg void OnBnClickedSavevgimgDeleteselected();
	afx_msg void OnBnClickedSavevgimgAimfileOpen();
	afx_msg void OnBnClickedSavevgimgImportfilelist();
	afx_msg void OnBnClickedSavevgimgConfigselected();

	CString m_AimFilePath;
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedDdsSave();


	int m_dxt_select;
	CString m_vgimg_filename;



	//void saveVgimgOnly( StringVector &strVec );
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	float _lod0_factor;
	float _lod1_factor;
	float _lodNear;
	float _lodFar;
	CString _progressMsg;
};
