#pragma once


#include "resource.h"
#include "gdal/ogr_spatialref.h"
// CdlgCoordTransform 对话框

class CdlgCoordTransform : public CDialog
{
	DECLARE_DYNAMIC(CdlgCoordTransform)

public:
	CdlgCoordTransform(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CdlgCoordTransform();

// 对话框数据
	enum { IDD = IDD_DLG_COORD_TRANS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString strSourceCoordPath;
	CString strTargetCoordPath;

	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnSourcePath();
	afx_msg void OnBnClickedBtnTargetPath();
	afx_msg void OnBnClickedOk();
public:
	OGRSpatialReference vg_SourceSPF;
	OGRSpatialReference vg_TargetSPF;

	CString strSourceParam;
	CString strTargetParam;
};
