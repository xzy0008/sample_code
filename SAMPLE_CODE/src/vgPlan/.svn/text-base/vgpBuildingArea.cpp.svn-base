#include "vgStableHeaders.h"
#include <vgPlan/vgpBuildingArea.h>
#include <vgplan/vgpSunAngle.h>
#include <vgTerritory/vgtTerrainManager.h>
#include <algorithm>
#include <vgPlan/vgPlanmanager.h>
#include <vgkernel/vgkRendererManager.h>
#include <vgkernel/vgkSelectManager.h>
#include <vgUIController/vgUIController.h>
#include <vgPlan/vgBlockEntry.h>

namespace vgPlan
{
	vgBuildingArea::vgBuildingArea()
	{
		m_schemMap.clear();
		// m_pCurrentBlockVec = NULL;

		m_minFloor = 0;
		m_maxFloor = 0;

		m_currentSchemFloor = 0;

		m_schemMap.clear();
	}

	vgBuildingArea::~vgBuildingArea()
	{
		PlanSchemMap::iterator iter = m_schemMap.begin();
		PlanSchemMap::iterator iEnd = m_schemMap.end();

		while (iter != iEnd)
		{
			PlanBoxPointerVec* pVec = iter->second;
			
			if (pVec != NULL)
			{
				// new added code for edit version.
				for (int i=0; i<pVec->size(); i++)
				{
					if (pVec->at(i) != NULL)
					{
						delete pVec->at(i);
					}
				}

				delete pVec;
			}
			
			iter ++;
		}
	}

	void vgBuildingArea::setCurrentSchemFloor(int floor)
	{
		if (m_currentSchemFloor != 0)
		{
			PlanBoxPointerVec *pVec = getBlockVecByFloor(m_currentSchemFloor);
			for (int i=0; i<pVec->size(); i++)
			{
				if (pVec->at(i) != NULL)
				{
					pVec->at(i)->setVisible(false);
				}
			}
		}

		m_currentSchemFloor = floor;

		PlanBoxPointerVec *pVec = getBlockVecByFloor(m_currentSchemFloor);
		
		
		for (int i=0; i<pVec->size(); i++)
		{
			if (pVec->at(i) != NULL)
			{
				pVec->at(i)->setVisible(true);
			}
		}
	}

	void vgBuildingArea::matchFloorAreaRatio(int method, float delRat)
	{
		setCurrentSchemFloor(m_currentSchemFloor);

		if (method == 1)
		{
			matchFloorAreaRatioMatrix(delRat);
		}
		else if (method == 2)
		{
			matchFloorAreaRatioRandom(delRat);
		}

	}

	void vgBuildingArea::matchFloorAreaRatioMatrix(float delRat)
	{
		// m_pCurrentBlockVec = getBlockVecByFloor(m_currentSchemFloor);	
		
		PlanBoxPointerVec *pVec = this->getBlockVecByFloor(m_currentSchemFloor);

		// int slice = ceil((float)(pVec->size()) / pVec->size() * delRat);
		int slice = ceil(1.f / delRat);
		
		for (int i=0; i<pVec->size(); i++)
		{
			if (pVec->at(i) != NULL && i % slice != 0)
			{
				pVec->at(i)->setVisible(true);	
			}
			else
			{
				pVec->at(i)->setVisible(false);
			}
		}
	}

	void vgBuildingArea::matchFloorAreaRatioRandom(float delRat)
	{
		vector<int> pRandVec;

		PlanBoxPointerVec *pVec = this->getBlockVecByFloor(m_currentSchemFloor);


		for (int i=0; i<pVec->size(); i++)
		{
			if (pVec->at(i) != NULL)
			{
				pRandVec.push_back(i);
			}
		}

		random_shuffle(pRandVec.begin(), pRandVec.end());
		
		int delCnt = ceil((float)(pVec->size())* delRat);
		
		for (int i=0; i<delCnt; i++)
		{
			pVec->at(pRandVec[i])->setVisible(false);
		}
	}

	void vgBuildingArea::render()
	{
		vgShpArea::render();

//  		PlanBoxPointerVec *pVec = getBlockVecByFloor(m_currentSchemFloor);
//  	
//  		if (pVec == NULL)
//  		{
//  			return ;
//  		}
//  
//  		for (int i=0; i<pVec->size(); i++)
//  		{
// 			if (pVec->at(i) != NULL && pVec->at(i)->getVisible())
// 			{
// 				pVec->at(i)->render();
// 			}
//  		}
	}

	void vgBuildingArea::renderShadow()
	{
		PlanBoxPointerVec *pVec = getBlockVecByFloor(m_currentSchemFloor);

		if (pVec == NULL)
		{
			return ;
		}
		
		for (int i=0; i<pVec->size(); i++)
		{
			if (pVec->at(i) != NULL && pVec->at(i)->getVisible())
			{
				pVec->at(i)->drawshadow();
			}
		}
	}

	void vgBuildingArea::updateShadowData()
	{
// 		PlanSchemMap::iterator iter = m_schemMap.begin();
// 		PlanSchemMap::iterator iter_end = m_schemMap.end();
// 
// 		while (iter != iter_end)
// 		{
// 			PlanBoxPointerVec *pVec = iter->second;
// 			
// 			for (int i=0; i<pVec->size(); i++)
// 			{
// 				pVec->at(i)->onsunlightanalysis();
// 			}
// 			iter ++;
// 		}
// 		for (int i=m_minFloor; i<=m_maxFloor; i++)
// 		{
// 			PlanBoxPointerVec *pVec = getBlockVecByFloor(i);
// 			if (pVec != NULL)
// 			{
//  				for (int j=0; j<pVec->size(); j++)
//  				{
//  					pVec->at(j)->onsunlightanalysis();
//  				}
// 			}
// 		}
 	}

	void vgBuildingArea::updateGemoData()
	{
		PlanBoxPointerVec *pVec = getCurrentBlockVec();

		if (pVec == NULL)
		{
			return ;
		}

		for (int i=0; i<pVec->size(); i++)
		{
			if (pVec->at(i) != NULL)
			{
				pVec->at(i)->calculategeo();
			}
		}
	}


	bool vgBuildingArea::calculateGrid(int xResolve, int yResolve)
	{        
		//OGREnvelope envelope =  m_groundList[0]->getEnvelope();
		OGREnvelope envelope = this->getEnvelope();

		int sizex = envelope.MaxX - envelope.MinX;
		int sizey = envelope.MaxY - envelope.MinY;

		m_gridMap.initialise(Vec2(envelope.MinX, envelope.MinY), Vec2(sizex, sizey), xResolve, yResolve);

		// m_gridMap.caculateAvailGrid(m_groundList[0]->getGeometry());
		m_gridMap.calculateAvailGrid(this->getGeometry());

		// m_gridMap.initBlockPos();

		return true;
	}

#if 0
	int vgBuildingArea::generatePlan(int blockX, int blockY, int aliasX, int aliasY)
	{
		int blockCnt = m_gridMap.putBlockInGrid(blockX, blockY, aliasX, aliasY);
	
// 		
// 		for (int i=0; i<m_blockPointerVec.size(); i++)
// 		{
// 			if (m_blockPointerVec[i] != NULL)
// 			{
// 				delete m_blockPointerVec[i];
// 			}
// 		}
// 
// 		m_blockPointerVec.clear();
// 
// 		vector<GridStruct> gridVecRef = m_gridMap.getBlockGridVecRef();
// 
// 		for (int i=0; i<gridVecRef.size(); i++)
// 		{
// 			vgPlanbox* pblockBox = new vgPlanbox;
// 			
// 			vgKernel::Vec3 pos(gridVecRef[i].px+blockX/2, 0, (gridVecRef[i].py+blockY/2));
// 			
// 			pblockBox->setupboxdata(pos, blockX, blockY, 20, 0);
// 
// 			m_blockPointerVec.push_back(pblockBox);
// 		}

		return blockCnt;
	}


	void vgBuildingArea::generatePlan(int blockX, int blockY, float maxHeight, float minHeight
		, float heightPerFloor, int aliasX, int aliasY, float areaLat, int planYear, int planMonth, int planDay, int sunTime)
	{	
		if (sunTime % 2 != 0)
		{
			sunTime ++;
		}

		vgGIS3D::vgSunAngle sunangle;
		sunangle.SetDate(planYear, planMonth, planDay);

		sunangle.SetTime(12-(sunTime/2),0);
		
		sunangle.SetLat(areaLat);

		float heightAngle=sunangle.GetHeightOfSun();

		PlanSchemMap::iterator iter = m_schemMap.begin();
		PlanSchemMap::iterator eIter = m_schemMap.end();

		/*m_pCurrentBlockVec->clear();*/

		while (iter != eIter)
		{
			PlanBoxPointerVec* pVec = iter->second;
			delete pVec;

			iter ++;
		}
		
		m_schemMap.clear();
		
		int totalHeight = maxHeight / heightPerFloor;
		int startHeight = minHeight / heightPerFloor;

		PlanBoxPointerVec *pNewVec = NULL;

		for (int i=startHeight; i<=totalHeight; i++)
		{
			int currentAliasX = aliasX;
			int sunDist = (i*heightPerFloor-0.9)/tan(heightAngle) / GridStruct::s_sizey;

			int currentAliasY = aliasY ? sunDist : aliasY > sunDist; 

			int blockCnt = m_gridMap.putBlockInGrid(blockX, blockY, currentAliasX, currentAliasY);
			
			stringstream outString;

			outString << "间距 " << currentAliasX << " " << currentAliasY 
					  << " 高度 " << i << " 层"
					  << " 共生成 "<< blockCnt << "个\n";

			VGK_SHOW(outString.str());

			pNewVec = new PlanBoxPointerVec;
			
			vector<GridStruct> gridVecRef = m_gridMap.getBlockGridVecRef();

			for (int j=0; j<gridVecRef.size(); j++)
			{
				//vgPlanbox* pblockBox = new vgPlanbox;
				PlanBoxSharedPtr pBlockBox(new vgPlanbox);

				vgKernel::Vec3 pos(gridVecRef[j].px+blockX/2, 0, (gridVecRef[j].py+blockY/2));

				pBlockBox->setupboxdata(pos, blockX, blockY, i*heightPerFloor, 0);

				pNewVec->push_back(pBlockBox);
			}
			
			m_schemMap.insert(make_pair(i, pNewVec));
		}

		// 测试代码
 		if (pNewVec != NULL)
 		{
			m_pCurrentBlockVec = m_schemMap[totalHeight];
		}
	}

#endif

	void vgBuildingArea::generatePlan(BlockParam blockParam, SunlightParam sunlightParam)
	{
		// m_pCurrentBlockVec = NULL;

		if (sunlightParam.sunTime % 2 != 0)
		{
			sunlightParam.sunTime ++;
		}

		vgPlan::vgSunAngle sunangle;
		sunangle.SetDate(sunlightParam.year, sunlightParam.month, sunlightParam.day);

		sunangle.SetTime(12-(sunlightParam.sunTime/2), 0);

		sunangle.SetLat(sunlightParam.lat);

		float heightAngle=sunangle.GetHeightOfSun();

// 		PlanSchemMap::iterator iter = m_schemMap.begin();
// 		PlanSchemMap::iterator eIter = m_schemMap.end();
// 
// 		/*m_pCurrentBlockVec->clear();*/
// 
// 		while (iter != eIter)
// 		{
// 			PlanBoxPointerVec* pVec = iter->second;
// 			
// 			if (pVec == NULL)
// 			{
// 				continue;
// 				iter ++;
// 			}
// 
// 			for (int i=0; i<pVec->size(); i++)
// 			{
// 				if (pVec->at(i) != NULL)
// 				{
// 					// delete pVec[i];
// 					vgKernel::RendererManager::getSingleton().deleteRenderer(pVec->at(i));
// 				}
// 			}
// 
// 			delete pVec;
// 
// 			iter ++;
// 		}
		
		vgKernel::SelectManager::getSingleton().clearSelection();
// 		vgUIController::GetInstance()->GetPropertiesViewBar()->ShowControlBar(FALSE, FALSE, FALSE);
// 		vgUIController::GetInstance()->GetWorkSpaceBar()->ShowControlBar(FALSE, FALSE, FALSE);

		for (int i=m_minFloor; i<=m_maxFloor; i++)
		{
			PlanBoxPointerVec* pVec = getBlockVecByFloor(i);
			if (pVec != NULL)
			{
 				for (int j=0; j<pVec->size(); j++)
 				{
 					if (pVec->at(j) != NULL)
 					{
 						// delete pVec[i];
						TRACE("delete %s \n", pVec->at(j)->getName().c_str());
 						vgKernel::RendererManager::getSingleton().deleteRenderer(pVec->at(j));
 					}
 				}
			}

			delete pVec;
			m_schemMap[i] = NULL;
		}

		m_schemMap.clear();

		int totalHeight = blockParam.maxHeight / blockParam.heightPerFloor;
		int startHeight = blockParam.minHeight / blockParam.heightPerFloor;

		m_minFloor = startHeight;
		m_maxFloor = totalHeight;

		PlanBoxPointerVec *pNewVec = NULL;
		stringstream nameString;

		for (int i=startHeight; i<=totalHeight; i++)
		{
			int currentAliasX = blockParam.aliasX;

			int sunDist = (i*blockParam.heightPerFloor-0.9)/tan(heightAngle) / GridStruct::s_sizey;
				
			// 计算旋转衰减
			if (blockParam.rotateDgree > 15 && blockParam.rotateDgree < 30)
			{
				sunDist = sunDist * 0.9f;
			}
			else if (blockParam.rotateDgree >= 30 && blockParam.rotateDgree < 45)
			{
				sunDist = sunDist * 0.8f;
			}
			else if (blockParam.rotateDgree >= 45 && blockParam.rotateDgree <60)
			{
				sunDist = sunDist * 0.9f;
			}
			else if (blockParam.rotateDgree >= 60)
			{
				sunDist = sunDist * 0.95f;
			}

			int currentAliasY = blockParam.aliasY ? sunDist : blockParam.aliasY > sunDist; 

			int blockCnt = m_gridMap.putBlockInGrid(blockParam.blockX, blockParam.blockY, currentAliasX, currentAliasY, blockParam.aliasR);

			stringstream outString;

			outString << "日照间距 " << sunDist<< " 建筑间距 " << currentAliasX << " " << currentAliasY 
				<< " 高度 " << i << " 层"
				<< " 共生成 "<< blockCnt << "个\n";

			VGK_SHOW(outString.str());
			
			outString.str("");

			pNewVec = new PlanBoxPointerVec;

			vector<GridStruct> gridVecRef = m_gridMap.getBlockGridVecRef();
			int currentSceneId = vgPlan::vgPlanManager::getSingleton().getActiveSceneId();

			for (int j=0; j<gridVecRef.size(); j++)
			{
				//vgPlanbox* pblockBox = new vgPlanbox;
				// PlanBoxSharedPtr pBlockBox(new vgPlanbox);
				vgPlanbox *pBlockBox = new vgPlanbox;
				
				pBlockBox->setOrigiPositon(gridVecRef[j].px, gridVecRef[j].py);
// 				vgKernel::Vec3 pos(gridVecRef[j].px+blockParam.blockX/2, 0, (gridVecRef[j].py+blockParam.blockY/2));
// 				
// 				// 此处加入贴地代码
// 				float elevation;
// 				vgKernel::Vec3 openglPos = pos;
// 				// pos 使用的是 地理坐标，需要转换成OpenGL坐标贴地
// 				openglPos.z = -openglPos.z;
// 
// 				vgTerritory::TerrainManager::getSingleton().getElevationByPosition(openglPos, elevation, true);
// 				pos.y = elevation;
// 				
				//outString.str("");
				//outString << "POS:" << pos.x << " "<< pos.z 
				//		  <<" height "<< pos.y << "\n";

				//VGK_SHOW(outString.str());


				//pBlockBox->setupBoxData(pos, blockParam.blockX, blockParam.blockY, i*blockParam.heightPerFloor, blockParam.rotateDgree);
				pBlockBox->setupBoxData(/*pos,*/ blockParam.blockX, blockParam.blockY, i, blockParam.heightPerFloor, blockParam.rotateDgree);
// 				pBlockBox->setlayerheight(blockParam.heightPerFloor);
// 				pBlockBox->setLayerNum(i);

				pBlockBox->setSceneId(currentSceneId);
				pBlockBox->setVisible(false);

				nameString.str("");
				nameString<<"Block_"<<currentSceneId<<"_"<<i<<"_"<<j;
				pBlockBox->setName(nameString.str());

				pNewVec->push_back(pBlockBox);

				vgKernel::RendererManager::getSingleton().addRenderer(pBlockBox);

 				// vgBaseEntry *pEntry = vgEntryFactory::createEntryFromRenderer(pBlockBox);
				vgBlockEntry *pEntry = new vgBlockEntry(pBlockBox);
				vgUI::UIController::getSingleton().	addEntryToRootByName("规划", pEntry);
				
			}

			m_schemMap.insert(make_pair(i, pNewVec));
		}

// 		// 测试代码
// 		if (pNewVec != NULL)
// 		{
// 			m_pCurrentBlockVec = m_schemMap[totalHeight];
// 		}
		m_currentSchemFloor = 0;
	}

	PlanBoxPointerVec* vgBuildingArea::getBlockVecByFloor(int floor)
	{
		return m_schemMap[floor];
	}

	float vgBuildingArea::getSchemArea(int floor)
	{
		PlanBoxPointerVec *pVec = getBlockVecByFloor(floor);

		float area = 0.f;

		if (pVec == NULL)
		{
			return 0.f;
		}

		for (int i=0; i<pVec->size(); i++)
		{
			if (pVec->at(i) != NULL)
			{
				area += pVec->at(i)->getBuildTotalArea();
			}
		}

		return area;
	}

	float vgBuildingArea::getCurrentArea()
	{
		float area = 0.f;

		PlanBoxPointerVec *pVec = getBlockVecByFloor(m_currentSchemFloor);
		
		if (pVec == NULL)
		{
			return 0.f;
		}

		for(int i=0; i<pVec->size(); i++)
		{
			if (pVec->at(i) != NULL && pVec->at(i)->getVisible())
			{
				area += pVec->at(i)->getBuildTotalArea();
			}
		}

		return area;
	}

	int vgBuildingArea::getNumOfBuilding(int floor)
	{
		PlanBoxPointerVec *pVec = getBlockVecByFloor(floor);

		if (pVec != NULL)
		{
			return pVec->size();
		}

		return 0;
	}
	
	bool vgBuildingArea::onDeleteRenderer(vgKernel::Renderer *pRenderer)
	{
		PlanSchemMap::iterator iter = m_schemMap.begin();
		PlanSchemMap::iterator eIter = m_schemMap.end();

		/*m_pCurrentBlockVec->clear();*/

		while (iter != eIter)
		{
			PlanBoxPointerVec* pVec = iter->second;
			
			if (pVec == NULL)
			{
				iter ++;
				continue;
			}

			for (int i=0; i<pVec->size(); i++)
			{
				if (pVec->at(i) == pRenderer)
				{
 					delete pVec->at(i);
 					(*pVec)[i] = NULL;

					return true;
				}
			}

			iter ++;
		}
	
		return false;
	}

}


