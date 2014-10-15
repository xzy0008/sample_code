#pragma once

#include <vgKernel/vgkSharePtr.h>
#include <vgKernel/vgkVec2.h>
#include <vgKernel/vgkVec3.h>

#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_api.h>

//#define array_index(i, j, line) ( i*line + j)
using namespace vgKernel;

namespace vgPlan
{
	 
	struct GridStruct  
	{
		GridStruct()
		{
			ix = 0;
			iy = 0;
			px = 0;
			py = 0;
			s_sizex = 0;
			s_sizey = 0;

			availFlag = 0;
			
			availOnXHorizon = 0;
			availOnYHorizon = 0;
			availOnXVertical = 0;
			availOnYVertical = 0;

			usedBlockId = -1;
		}

		int ix;
		int iy;

		float px;
		float py;

		/*  
			0 - 当前网格不在区域内，不可用
			1 - 当前网格在区域内，需对当前block需计算日照决定是否能够摆放
			2 - 当前网格在区域内，已计算过日照无法摆放
			3 - 当前网格在区域内，已摆放其他block
		*/
		int availFlag;

		int availOnXHorizon;
		int availOnYHorizon;
	
		int availOnXVertical;
		int availOnYVertical;

		int followOnXHorizon;
		int followOnYHorizon;

		int followOnXVertical;
		int followOnYVertical;

		int usedBlockId;

		static float s_sizex;
		static float s_sizey;
	};

	typedef vgKernel::SharePtr<GridStruct> GridStructSharedPtr;

	class GridMap
	{
	public:
		// 根据栅格左上角点，栅格大小，水平数值分辨率初始化GridMap
		GridMap();

		GridMap(Vec2 leftUpPoint, Vec2 gridSize, float xResolve, float yResolve);
		
		~GridMap();

		void initialise(Vec2 leftUpPoint, Vec2 gridSize, float xResolve, float yResolve);

		// 使用前根据区域计算可用的栅格，设定0-1 flag
		void calculateAvailGrid(OGRGeometry *pGemo);


		// 在栅格上摆放block
		int putBlockInGrid(int blockX, int blockY, int minAliasX, int minAliasY, int minAliasR);

		bool dumpToFile(string fileName = "d:\\GridDump.txt");

 		GridStruct* getGrid(int ix, int iy)
 		{
 			int index = array_index(ix, iy);
 
 			// assert (index < m_gridVec.size());
 			
 			return &m_gridVec[index];
 		}
		// 渲染可用栅格，做正确性检查
		void render();

		vector<GridStruct>& getBlockGridVecRef()
		{
			return m_blockGridVec;
		}

	private:
		// 在摆放前初始化，恢复所有栅格状态，删除当前结果等
		void initGridBlockBeforePut();

		// 恢复ix iy以上没被使用的栅格标志，被calculateGridBlock调用.
		void prepareAvailGrid(int ix, int iy);

		// 使用动态规划计算网格的摆放范围
		bool calculateGridBlock(int ix=-1, int iy=-1);

		void cntAvailGrid();

		void quadCompute(int ix, int iy, int blockCntX, int blockCntY, OGRGeometry* pGemo);
		
		bool containGrid(int ix, int iy, int blockCntX, int blockCntY, OGRGeometry* pGemo);

		bool overlapeGrid(int ix, int iy, int blockCntX, int blockCntY, OGRGeometry* pGemo);
		
		inline int array_index(int i, int j)
		{
			return i * m_blockYNum + j;
		}

		// 用户负责删除返回的Geometry.
		// inline OGRLinearRing* getRingsFormGrid(int ix, int iy, int blockCntX, int blockCntY);
		
		inline bool colorGrid(int ix, int iy, int blockCntX, int blockCntY, int flag, int blockId=-1);

		inline bool distanceAvail(int ix, int iy, int blockSizeX, int blockSizeY, int distInX, int distInY, int distInR);

	private:
		// vector<GridStructSharedPtr> m_gridVec;
		GridStruct *m_gridVec;
		
/*		GridStruct *m_oriGirdVec;*/

		int m_blockXNum;
		int m_blockYNum;

		vector<GridStruct> m_blockGridVec;
	};
}


