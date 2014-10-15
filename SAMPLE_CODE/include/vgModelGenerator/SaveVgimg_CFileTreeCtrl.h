
#include <vgStableHeaders.h>
#include "FileTreeCtrl.h"


// CSaveVgimg_CFileTreeCtrl

class CSaveVgimg_CFileTreeCtrl : public CFileTreeCtrl
{
	DECLARE_DYNAMIC(CSaveVgimg_CFileTreeCtrl)

public:
	CSaveVgimg_CFileTreeCtrl();
	virtual ~CSaveVgimg_CFileTreeCtrl();

	virtual bool MatchExtension(CString file);

protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnNMRclick(NMHDR *pNMHDR, LRESULT *pResult);
};


