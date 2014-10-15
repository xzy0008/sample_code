/*
** Created by Lesky Zhou
** 
*/
#if 0
#pragma once
#include <vgShape/vgshShapeManager.h>

typedef std::map<UINT, UINT>				CommandToMessage;


extern CWnd *								s_CommandWnd ;
extern CBCGPMenuBar*						s_pMenuBar;

extern CommandToMessage					s_CommandToMessage ;

// CCommandWnd 响应窗口事件
class CCommandWnd : public CWnd
{
	DECLARE_DYNAMIC(CCommandWnd)

public:
	CCommandWnd();
	virtual ~CCommandWnd();

protected:
	afx_msg LRESULT OnShpLoad( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnShpLoadGrid( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnShpModeEdit( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnShpSave( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnShpTraslateToOrigin( WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnShpAttachTerrain( WPARAM wParam, LPARAM lParam ) ;


	DECLARE_MESSAGE_MAP()

protected:
	bool importFiles( const vgKernel::StringVector& strvec , 
		bool bSpecial = false);

	bool importFile( const String& impFile , bool bSpecial = false );

	bool importFileImpl( const String& filename , bool bSpecial  );
	bool addShpToUI(vgShape::DataSourcePtr psource);
};


#endif