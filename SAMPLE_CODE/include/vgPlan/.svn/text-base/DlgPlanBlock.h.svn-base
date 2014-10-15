#pragma once

#include "resource.h"
#include <vgPlan/vgpSunAngle.h>
// DlgPlanBlock 对话框

#include <vgPlan/vgPlanscene.h>
#include <vgPlan/vgpDefinition.h>

namespace vgPlan
{
	/*!
		@date    2009/10/30  10:38
		@author  zzy
		@action  modify
		@brief   本类改为导出类，供菜单DLL调用 
	*/
	class VGP_EXPORT DlgPlanBlock : public CDialog
	{
		DECLARE_DYNAMIC(DlgPlanBlock)

	public:
		DlgPlanBlock(CWnd* pParent = NULL);   // 标准构造函数
		virtual ~DlgPlanBlock();

		// 对话框数据
		enum { IDD = IDD_PLAN_BLOCKIN };

		int getBlockX()
		{
			return m_blockX;
		}

		int getBlockY()
		{
			return m_blockY;
		}

		int getAliasX()
		{
			return m_aliasX;
		}

		int getAliasY()
		{
			return m_aliasY;
		}

		float getMaxHeight()
		{
			return m_maxHeight;
		}

		float getMinHeight()
		{
			return m_minHeight;
		}

		float getHeightPerFloor()
		{
			return m_heightPerFloor;
		}

		float getRotateDgree()
		{
			return m_rotateDgree;
		}

		float getAreaLat()
		{
			return m_areaLat;
		}

		int getPlanYear()
		{
			return m_planYear;
		}

		int getPlanMonth()
		{
			return m_planMonth;
		}

		int getPlanDay()
		{
			return m_planDay;
		}

		int getSunTime()
		{
			return m_sumTime;
		}

		int getAliasR()
		{
			return m_aliasR; 
		}

		float getFloorAreaRatio()
		{
			return m_floorArea;
		}

		vgPlan::BlockParam getBlockParam()
		{
			vgPlan::BlockParam blockParam;

			blockParam.blockX = m_blockX;
			blockParam.blockY = m_blockY;

			blockParam.aliasX = m_aliasX;
			blockParam.aliasY = m_aliasY;
			blockParam.aliasR = m_aliasR;

			blockParam.floorAreaRatio = m_floorArea;

			blockParam.maxHeight = m_maxHeight;
			blockParam.minHeight = m_minHeight;
			blockParam.heightPerFloor = m_heightPerFloor;

			blockParam.rotateDgree = m_rotateDgree;

			return blockParam;
		}

		vgPlan::SunlightParam getSunlightParam()
		{
			vgPlan::SunlightParam sunlightParam;

			sunlightParam.day = m_planDay;
			sunlightParam.month = m_planMonth;
			sunlightParam.year = m_planYear;

			sunlightParam.sunTime = m_sumTime;
			sunlightParam.lat = m_areaLat;

			return sunlightParam;
		}

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

		DECLARE_MESSAGE_MAP()
	private:
		int m_blockX;
		int m_blockY;
		int m_aliasX;
		int m_aliasY;
		float m_maxHeight;
		float m_minHeight;
		float m_heightPerFloor;
		float m_rotateDgree;
		float m_areaLat;
		int m_planYear;
		int m_planMonth;
		int m_planDay;
		int m_sumTime;
		int m_aliasR;
		float m_floorArea;
	public:
		virtual BOOL OnInitDialog();
	private:
		CString m_schemName;
	public:
		afx_msg void OnCbnSelchangeCombo2();
	};
}

