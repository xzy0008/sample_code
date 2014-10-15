

#include <vgKernel/vgkForward.h>

#include <vgKernel/vgkStringUtility.h>
#include <vgKernel/vgkStringPairVector.h>
#include <vgKernel/vgkProcessObserver.h>

#include "TaskProgressDlg.h"

#include "ReportCtrl.h"

using namespace vgKernel;

typedef vgKernel::SharePtr<StringPairVector> StringPairVectorPtr;



//struct fileItem 
//{
//	String _filepath;
//	bool _needToDeal;
//};
//
//std::vector<fileItem> fileItemVec;


// CSaveVgimgDlg dialog

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
	//////////////////////////////////////////////////////////////////////////
	CReportCtrl m_wndList;
	BOOL m_bSortable;

	int m_CurrentFileID;

	String getBasenameFromFilepath( const String& filepath );

	//////////////////////////////////////////////////////////////////////////

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedSavevgimgSavefilelist();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedSavevgimgSelectedall();
	afx_msg void OnBnClickedSavevgimgCancelselected();
	afx_msg void OnBnClickedSavevgimgInvertselected();
	afx_msg void OnBnClickedSavevgimgDeleteselected();
	afx_msg void OnBnClickedSavevgimgAimfileOpen();
	afx_msg void OnBnClickedSavevgimgImportfilelist();
	afx_msg void OnBnClickedSavevgimgConfigselected();
	afx_msg void OnBnClickedSavevgimgOnok();
	CString m_AimFilePath;
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedDdsSave();

	afx_msg void saveVgimgImplement();
	afx_msg void saveDDSImplement();
	int m_dxt_select;

	afx_msg void OnBnClickedSaveddsAndVgimg();
	afx_msg void OnBnClickedSaveVgimg();

	void saveVgimgOnly( StringVector &strVec );
	float _imgScaleRatio;

public:


	int						m_nPos;
	int						m_nTotalTasks;
	int						m_currentTaskID;
	CStringArray			m_sTaskList;
	CTaskProgressDialog		*m_pTaskDlg;

	virtual void onStart( const String& text , const int& range_lower , 
		const int& range_upper );

	// 显示进度.0到100之间
	virtual void onNotify( const String& msg , 
		const int& process_pos );

	virtual void onFinish( const String& msg );

protected:
	// 纹理名字添加后缀（原扩展名），为了避免*.jpg与*.tga转dds后重名。
	BOOL m_bAddNameSuffix;
	bool	getFlagAddNameSuffix();
public:
	BOOL m_bTga2Dtx3;
};
