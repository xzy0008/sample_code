

#include <vgKernel/vgkForward.h>
//#include "FileTreeCtrl.h"
#include "SaveVgimg_CFileTreeCtrl.h"

// CSaveVgimg_ImportFileDlg dialog

typedef std::vector<std::string> StringVector;

typedef vgKernel::SharePtr<StringVector> StringVectorPtr;


class CSaveVgimg_ImportFileDlg : public CDialog
{
	DECLARE_DYNAMIC(CSaveVgimg_ImportFileDlg)

public:
	CSaveVgimg_ImportFileDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSaveVgimg_ImportFileDlg();

// Dialog Data
	enum { IDD = IDD_SAVEVGIMG_IMPORTFILEDLG };

	//CFileTreeCtrl	m_FileTree;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CSaveVgimg_CFileTreeCtrl m_FileTree;
	afx_msg void OnBnClickedButton1();


	afx_msg void OnBnClickedOk();

	StringVectorPtr getSelectedFilesVector()
	{
		CString *files_names = NULL ;
		int files_num = m_FileTree.GetSelectedFiles( files_names );

		if ( files_num == 0 )
		{
			return StringVectorPtr();
		}

		StringVectorPtr ret( new StringVector() );
		ret->reserve( files_num );

		for ( int i = 0 ; i < files_num ; ++i )
		{
			ret->push_back( (files_names+i)->GetBuffer(0) );
		}

		delete[] files_names;
		return ret;
	}


};
