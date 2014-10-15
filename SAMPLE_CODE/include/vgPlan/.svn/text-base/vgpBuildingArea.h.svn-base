#pragma once

#include <vgkernel/vgkSharePtr.h>
#include <vgPlan/vgpGridMap.h>
#include <vgPlan/vgpShpArea.h>
#include <vgPlan/vgpGridMap.h>
#include <vgPlan/vgPlanbox.h>
/*#include <vgPlan/vgPlanscene.h>*/
#include <vgPlan/vgpDefinition.h>

namespace vgPlan
{
	class vgBuildingArea;

	struct BlockParam_t
	{
		BlockParam_t()
		{
			blockX = 0;
			blockY = 0;

			maxHeight = 0;
			minHeight = 0;

			heightPerFloor = 0;

			aliasX = 0;
			aliasY = 0;
			aliasR = 0;

			floorAreaRatio = 0.f;
			rotateDgree = 0.f;
		}

		int blockX;
		int blockY;

		float maxHeight;
		float minHeight;
		float heightPerFloor;

		int aliasX;
		int aliasY;
		int aliasR;
		
		float rotateDgree;
		float floorAreaRatio;
	};

	struct SunlightParam_t
	{
		int year;
		int month;
		int day;

		float lat;
		int sunTime;
	};

	typedef struct BlockParam_t BlockParam;
	typedef struct SunlightParam_t SunlightParam;

	typedef vgKernel::SharePtr<vgBuildingArea> vgBuildingAreaPtr;

	// typedef vector<PlanBoxSharedPtr> PlanBoxPointerVec;
	typedef vector<vgPlanbox*> PlanBoxPointerVec;
 
	typedef map<int, PlanBoxPointerVec*> PlanSchemMap;

	/*!
		@date    2009/10/30  10:38
		@author  zzy
		@action  modify
		@brief   本类改为导出类，供菜单DLL调用 
	*/
	class VGP_EXPORT vgBuildingArea : public vgShpArea
	{
	public:
		vgBuildingArea();

		virtual ~vgBuildingArea();

		bool calculateGrid(int xResolve, int yResolve);
	
		void render();

		void renderShadow();

		void updateShadowData();

		// 根据体块和日照参数生成规划
		void generatePlan(BlockParam blockParam, SunlightParam sunlightParam);

		PlanSchemMap& getSchemMapRef();

		// 得到体块层数是floor的方案的建筑面积  用于计算容积率 
		// 数值=建筑层数×建筑每层面积×楼房个数
		float getSchemArea(int floor);

		// 得到优化后的当前总面积
		float getCurrentArea();

		// 得到体块层数是floor的方案的体块队列
		PlanBoxPointerVec* getBlockVecByFloor(int floor);

		// 得到当前的体块渲染队列
		PlanBoxPointerVec* getCurrentBlockVec()	{ return getBlockVecByFloor(m_currentSchemFloor); }

		int getNumOfBuilding(int floor);
		
		int getMinFloorNum() { return m_minFloor; }

		int getMaxFloorNum() { return m_maxFloor; }

		int getCurrentSchemFloor() { return m_currentSchemFloor; }

		// 设置当前渲染的方案层数
		void setCurrentSchemFloor(int floor);

		void matchFloorAreaRatio(int method, float delRat);

		bool onDeleteRenderer(vgKernel::Renderer *pRenderer);

		void updateGemoData();
	private:

		void matchFloorAreaRatioMatrix(float delRat);

		// void matchFloorAreaRatioRing(int floor, float delRat);

		void matchFloorAreaRatioRandom(float delRat);

	private:
		GridMap m_gridMap;

		// PlanBoxPointerVec m_currentBlockVec;
		
		PlanSchemMap m_schemMap;
			
		int m_minFloor;

		int m_maxFloor;

		int m_currentSchemFloor;
	};
}
