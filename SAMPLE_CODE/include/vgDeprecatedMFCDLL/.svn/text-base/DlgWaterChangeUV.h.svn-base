#pragma once
#include "afxcmn.h"

#include <vgEffect/vgWaterNode.h>
#include "vgDeprecatedMFCDLL/Resource.h"
// DlgWaterChangeUV 对话框

class DlgWaterChangeUV : public CDialog
{
	DECLARE_DYNAMIC(DlgWaterChangeUV)

public:
	DlgWaterChangeUV( std::vector<vgMod::WaterNode*> _NodeList, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgWaterChangeUV();

// 对话框数据
	enum { IDD = IDD_WATER_UV };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//std::vector<vgCore::WaterNode*> _nodeList;
	std::vector<vgMod::WaterNode*> _nodeList;

	vgMod::WaterNode* _currentNode;

public:
	int floatNumRound( float fNum ); // 自定义四舍五入取整函数

public:
	CSliderCtrl m_Cslide_angle;
	CSliderCtrl m_Cslider_rate;
	float fChange_angle;
	float fChange_rate;

	float fRes_angle;

	float m_utimeline;
	float m_vtimeline;

	virtual BOOL OnInitDialog();

	afx_msg void OnEnChangeEditWaterUv();
	afx_msg void OnEnChangeEditWaterRate();
	afx_msg void OnNMCustomdrawSliderWateruv(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderWaterrate(NMHDR *pNMHDR, LRESULT *pResult);
};
