#pragma once

#include "vgTerritoryResource.h"
// CdlgSetCellSize 对话框

class CdlgSetCellSize : public CDialog
{
	DECLARE_DYNAMIC(CdlgSetCellSize)

public:
	CdlgSetCellSize(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CdlgSetCellSize();

// 对话框数据
	enum { IDD = IDD_DLG_SET_CELLSIZE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float cellSize;
	afx_msg void OnEnChangeEditcellsize();
};
