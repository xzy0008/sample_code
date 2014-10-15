
#include <vgStableHeaders.h>
#include <vgShape/vgshSpecialPolygon.h>
#include <vgShape/vgshLayer.h>
#include <vgShape/vgshShapeManager.h>
#include <vgShape/vgshGeometry.h>
#include <gdal/ogr_feature.h>
#include <gdal/ogr_geometry.h>

#include <algorithm>

#include <vgKernel/vgkRendererManager.h>

namespace vgShape {

#if 0
	const static int FLAT1_HOUSEHOLD = 1;
	const static int FLAT3_HOUSEHOLD = 6;
	const static int FLAT4_HOUSEHOLD = 8;
	const static int FLAT5_HOUSEHOLD = 10;

	//----------------------------------------------------------------
	void SpecialPolygon::renderOnceForDisplayList()
	{
		glDisable( GL_DEPTH_TEST );
		Polygon::renderOnceForDisplayList();
		glEnable( GL_DEPTH_TEST );
	}
	//----------------------------------------------------------------

	void SpecialPolygon::outputPointToScreen()
	{

  		OGRFeature *pFeature = this->getOGRFeature();
  		OGRGeometry *pGeometry = pFeature->GetGeometryRef();
		

		if( pGeometry != NULL )
		{
			if ( wkbFlatten( pGeometry->getGeometryType() ) != wkbPolygon )
			{
				assert(0);
				// 					return false;
			}

			assert( wkbFlatten( pGeometry->getGeometryType() )
				== wkbPolygon );

			OGRPolygon* poly = ( OGRPolygon* )pGeometry;		

			// do not delete pRings pointer 
			OGRLinearRing *pRings = poly->getExteriorRing();

			int nPointsCount =	pRings->getNumPoints();
			std::stringstream outString;
			
			VGK_SHOW("\n");

			if (nPointsCount != 0)
			{
				OGRRawPoint* pPoints2D = NULL;

				pPoints2D = new OGRRawPoint[nPointsCount];

				pRings->getPoints( pPoints2D);

				for (int i = 0; i < nPointsCount; i++)
				{
					Vector2 pos(pPoints2D[i].x,pPoints2D[i].y);

					outString << pos.x << " " << pos.y << "\n";				
					VGK_SHOW(outString.str());
					outString.str("");
				}

				delete [] pPoints2D;
			}
		}
		else
		{
			return ;
		}

		delete pFeature;
	}
	
	bool SpecialPolygon::constructInfoShp()
	{
		stringstream outString;

		OGRFeature *pFeature = this->getOGRFeature();
		OGREnvelope selfEve;

		OGRGeometry *pGeometry = pFeature->GetGeometryRef();
		OGRGeometry *resultGeom = pGeometry->clone();
		OGRGeometry *tmpGeometry = NULL;
		


		assert (pGeometry != NULL);
		
		// 遍历Layer中所有的poly
		
		vgShape::Layer *pOutline = vgShape::ShapeManager::getSingleton().getLayerByShortName("outline");

		if (pOutline == NULL)
		{
			return false;
		}
		else
		{
			vgShape::GeometryPointerVec layGemoVec = pOutline->getGeometriesRef();
 			string tmpStr;

 			pGeometry->getEnvelope(&selfEve);
			
			for (int i=0; i<layGemoVec.size(); i++)
			{

  				vgShape::Geometry* pTmpGeometry = layGemoVec[i];
  				
  				OGRFeature *pTmpFeature = pTmpGeometry->getOGRFeature();

				tmpStr = pTmpFeature->GetFieldAsString("Legend");
				
				if (tmpStr != "roads" && tmpStr != "sea" 
					&& tmpStr != "0400 Inland water" && tmpStr != "0000 Foreshore")
				{
					OGRFeature::DestroyFeature (pTmpFeature);
					continue ;
				}

	  			OGREnvelope eve1 = pTmpGeometry->getEnvelope2f();
				
				if (selfEve.Intersects(eve1) || selfEve.Contains(eve1))
				{
					OGRGeometry *pCurrentGeom = pTmpFeature->GetGeometryRef();

					resultGeom->flattenTo2D();
					pCurrentGeom->flattenTo2D();

					tmpGeometry = resultGeom->Difference(pCurrentGeom);

					delete resultGeom;

					resultGeom = tmpGeometry;

					if (tmpGeometry == NULL)
					{
						VGK_SHOW("Fixed \n");
						resultGeom = pGeometry->clone();
					}
				}

				OGRFeature::DestroyFeature (pTmpFeature);
 			} // end for

			assert(resultGeom != NULL);

			// 继续计算去掉building包围盒的地块
			vgKernel::RendererQueue *pModQueue = 
				vgKernel::RendererManager::getSingleton().getRendererQueueByType(vgCore::RENDERER_TYPE_MODOJBECT, false);

			if (pModQueue == NULL)
			{
				VGK_SHOW("Mod model no found. \n");
				return false;
			}

			/*vgKernel::Renderer *pRenderer;*/
			vgCore::ObjectNode *pObjectNode;

			vgKernel::RendererQueue::iterator iter = pModQueue->begin();
			vgKernel::RendererQueue::iterator iter_end = pModQueue->end();

			while (iter != iter_end)
			{
				pObjectNode = dynamic_cast<vgCore::ObjectNode*>(*iter);
			
				if (pObjectNode == NULL)
				{
					TRACE("类型错误 \n");
					continue;
				}
				
				pObjectNode->Initialize();
				vgKernel::Box box = pObjectNode->getBoundingBox();
				
				vgShape::Layer *pLayer = vgShape::ShapeManager::getSingleton().getLayerByShortName("Grid");
				
				if (pLayer == NULL)
				{
					return false;
				}

				vgKernel::Mat4 mat = pLayer->getMatrix();
				mat.inverse();

				box.matrixTranslation(mat);

				OGRLinearRing boxRing;
				
				Vector2 leftUp(box._minVertex.x, -box._minVertex.z);
				Vector2 leftDown(box._minVertex.x, -box._maxVertex.z);
				Vector2 rightUp(box._maxVertex.x, -box._minVertex.z);
				Vector2 rightDown(box._maxVertex.x, -box._maxVertex.z);
				
				boxRing.addPoint(leftUp.x, leftUp.y);
				boxRing.addPoint(rightUp.x, rightUp.y);
				boxRing.addPoint(rightDown.x, rightDown.y);
				boxRing.addPoint(leftDown.x, leftDown.y);
				
				boxRing.flattenTo2D();

				boxRing.closeRings();
				
				OGRPolygon boxPoly;
				boxPoly.addRing(&boxRing);

				OGREnvelope boxEnv;
				
				boxPoly.getEnvelope(&boxEnv);

				if (selfEve.Intersects(boxEnv) || selfEve.Contains(boxEnv))
				{
					// leven add
					_nowBuidingNum ++;

					TRACE("Box position LD %f %f\n", leftDown.x, leftDown.y);
					TRACE("Box position RU %f %f\n", rightUp.x, rightUp.y);
					
					TRACE("Box name %s \n", pObjectNode->getName().c_str());
					TRACE("Box position %f %f %f \n", pObjectNode->GetPosition().x, pObjectNode->GetPosition().y, pObjectNode->GetPosition().z);
 					
					if (leftDown.x > 1e-7 && leftDown.y > 1e-7)
					{
						if (resultGeom == NULL)
						{
							resultGeom = pGeometry->clone();
						}
						resultGeom->flattenTo2D();
						boxPoly.flattenTo2D();

						tmpGeometry = resultGeom->Difference(&boxPoly);

						if (tmpGeometry != NULL)
						{
							delete resultGeom;
							resultGeom = tmpGeometry;
						}
					}
				}

				iter ++;
			}
 		} // end else

		OGRFeature::DestroyFeature(pFeature);
	
		m_pResultGemo = resultGeom;

		calculateGrid(m_pResultGemo, vgVector::AutoBuildManager::ShpGridNum);

		return true;
	}

	bool SpecialPolygon::generateAutobuilding(vgVector::AutobuildNodeVec &autoNodeVec, int schem, int years/* int buildingCnt*/)
	{

		// 此处楼房数目应根据years对应的人口数据计算
		stringstream outStream;

		int buildingCnt = generateModelByYears(autoNodeVec, schem, years);

		m_modelList.clear();
		m_positionList.clear();

		// for tmp use.
		float longforscale = 0;
		int modelIndex = 0;
		int initVecSize = autoNodeVec.size();

		if (initVecSize == 0)
		{
			VGK_SHOW("无可用自动建模模型 \n");
			return false;
		}

		// 得到位移矩阵
		vgShape::Layer *pLayer = vgShape::ShapeManager::getSingleton().getLayerByShortName("Grid");
		vgKernel::Mat4 mat = pLayer->getMatrix();


		if (calculateBuildingPosition(buildingCnt, buildingCnt * 1.5, longforscale))
		{
			int buildingIndex = 0;
			
			for (int i =0; i<buildingCnt; i++)
			{
				if ( i >= m_positionList.size() )
				{
#if VGK_LANG_CHS
					AfxMessageBox("生成空位不足.");
#else
					AfxMessageBox("Not enough space.");
#endif
					return false;
				}
				// 新建模型应放到generateModelByYears中
				vgVector::AutoBuildNode *pNewBuilding = m_modelList[i];

				vgKernel::Box boundingBox = pNewBuilding->getBoundingBox();
				vgKernel::Vec3 center = boundingBox.getCenter();
				
				if (longforscale > 10)
				{
					longforscale = 10;
				}

				TRACE("Longforsacle %d\n", longforscale);
  				if (boundingBox.getSize().length() > longforscale)
  				{
  					float rat = longforscale / boundingBox.getSize().length() * 0.9;
  					pNewBuilding->scale( center.x, center.y, center.z, rat, rat, rat);
  				}
				
// 				outStream.str("");
// 				outStream <<"POS "<< m_positionList[i].x << " " << m_positionList[i].y << " "<<m_positionList[i].z<<"\n";
// 				VGK_SHOW(outStream.str());
// 
// 				outStream.str("");
// 				outStream <<"POS2 "<< pNewBuilding->GetPosition().x << " " <<  pNewBuilding->GetPosition().y << " "<< pNewBuilding->GetPosition().z<< "\n";
// 				VGK_SHOW(outStream.str());

// 				Vector3 offset = Vector3( m_positionList[i].x, m_positionList[i].y, m_positionList[i].z)
// 					- pNewBuilding->getPosition()/* - vgCore::vgCoordinate::getSingleton().GetSceneCood()*/;
// 				pNewBuilding->translate( offset.x, offset.y, offset.z );

				pNewBuilding->moveTo(m_positionList[i].x, m_positionList[i].y, m_positionList[i].z);
// 				outStream.str("");
// 				outStream <<"POS3 "<< pNewBuilding->GetPosition().x << " " <<  pNewBuilding->GetPosition().y << " "<< pNewBuilding->GetPosition().z<< "\n";
// 				VGK_SHOW(outStream.str());

				pNewBuilding->translate( mat.m[3][0], mat.m[3][1], mat.m[3][2] );


				// 自动贴地
				float elev = 0.f;

				vgKernel::Vec3 rendererpos = pNewBuilding->getBoundingBox().getCenter();
				
				float maxheight = pNewBuilding->getBoundingBox()._maxVertex.y;
				float halfheight = maxheight - rendererpos.y;
				assert( halfheight >= 0.0f );

				bool getok = vgTerritory::TerrainManager::getSingleton().getElevationByPosition(
					rendererpos , elev , true );

				pNewBuilding->moveTo( rendererpos.x , elev + halfheight, rendererpos.z );
			}
		}	

		return true;
	}

// 	bool SpecialPolygon::calculateBuildingPosition(int buildingCnt, int blockCnt, float& longForScale)
// 	{
// 		static int inerCnt = 0;
// 		
// 		if (blockCnt == 0)
// 		{
// 			return true;
// 		}
// 
// 		if (blockCnt < 16)
// 		{
// 			blockCnt = 16;
// 		}
// 
// 		stringstream outString;
// 		int findCnt = 0;
// 		
// 		if (m_pResultGemo == NULL)
// 		{
// 			return false;
// 		}
// 
// 		m_positionList.clear();
// 		
// 		OGRGeometry *poGeometry = m_pResultGemo->clone();
// 		poGeometry->flattenTo2D();
// 
// 		OGREnvelope evn;
// 		poGeometry->getEnvelope(&evn);
// 
// 		float wid = (evn.MaxX - evn.MinX);
// 		float hei = (evn.MaxY - evn.MinY);
// 		float widHeightRat =  wid / hei;
// 		
// 		int blockx, blocky;
// 
// 		blockx = ceil(sqrt(blockCnt / widHeightRat));
// 		blocky = ceil(blockx / widHeightRat);
// 
// 		float unitx = wid / blockx;
// 		float unity = hei / blocky;
// 
// 		float x,y;
// 
// 		for (int i=0; i<blockx; i++)
// 		{
// 			for (int j=0; j<blocky; j++)
// 			{
// 				x = evn.MinX + unitx*(2*i+1)/2.0;
// 				y = evn.MinY + unity*(2*j+1)/2.0;
// 
// // 				//判断该方格是否全部在地块内,是则加入队列，否则剔除
// // 				Vector2 rightdown(x+unitx/2, y+unity/2);	//右下
// // 				Vector2 rightup(x+unitx/2, y-unity/2);		//右上
// // 				Vector2 leftup(x-unitx/2, y-unity/2);		//左上
// // 				Vector2 leftdown(x-unitx/2, y+unity/2);		//左下
// // 
// // 				OGRLineString rings;
// // 				rings.addPoint(leftup.x, leftup.y);
// // 				rings.addPoint(rightup.x, rightup.y);
// // 				rings.addPoint(rightdown.x, rightdown.y);
// // 				rings.addPoint(leftdown.x, leftdown.y);
// // 
// // 				rings.closeRings();
// // 
// // 				rings.flattenTo2D();
// 		
// // 				if (poGeometry->Contains(&rings))
// // 				{
// // 					m_positionList.push_back(vgKernel::Vec3(x, 0, -y));
// // 					findCnt ++;
// // 				}
// 
//  				OGRPoint rightdown(x+unitx/2, y+unity/2);	//右下
//  				OGRPoint rightup(x+unitx/2, y-unity/2);		//右上
//  				OGRPoint leftup(x-unitx/2, y-unity/2);		//左上
//  				OGRPoint leftdown(x-unitx/2, y+unity/2);		//左下
// 				OGRPoint center(x,y);
// 
// 				rightup.flattenTo2D();
// 				rightdown.flattenTo2D();
// 				leftdown.flattenTo2D();
// 				leftup.flattenTo2D();
// 				center.flattenTo2D();
// 
// 				if (poGeometry->Contains(&leftdown) && poGeometry->Contains(&rightup) 
// 					&& poGeometry->Contains(&leftup) && poGeometry->Contains(&rightdown) && poGeometry->Contains(&center))
// 				{
// 					m_positionList.push_back(vgKernel::Vec3(x, 0, -y));
// 					findCnt ++;
// 				}
// 			}
// 		}
// 
// 		longForScale = unitx ? unity : unitx < unity;
// 
// // 		if (findCnt != 0)
// // 		{
// // 			return false;
// // 		}
// 
// 		//if (findCnt < buildingCnt )
// 		if (findCnt == 0)
// 		{
// 			outString.str("");
// 
// 			outString << "进入递归 " << inerCnt++ << " " << blockCnt * 1.5 << "\n";
// 
// 			VGK_SHOW(outString.str()); 			
// 
// 			return calculateBuildingPosition(buildingCnt, blockCnt * 1.5, longForScale);
// 		}
// 
// 		inerCnt =  0;
// 		return true;
// 	}

	bool SpecialPolygon::calculateBuildingPosition(int buildingCnt, int blockCnt, float& longForScale)
	{
		// 新版本calulate position 根据缓存在shp中的栅格数据计算

		if (buildingCnt == 0)
		{
			return true;
		}

		stringstream outString;

		vector<Vector2> tmpPosVec;

		int increaseFlag = 1;
	
// 		outString.str("");
// 		outString << "Total available grid: " << m_availPosition.size() << "\n"; 
// 		VGK_SHOW(outString.str());

		if (m_availPosition.size() == 0)
			return false;

		// 如果空位不够用
		int   currentSize = m_availPosition.size(); 
		float currentUnitX = m_gridSizeX;
		float currentUnitY = m_gridSizeY;

		tmpPosVec.clear();

		// while (currentSize < buildingCnt)

		// 保证有足够的空位选择
		while (currentSize < buildingCnt * 2)
		{
			increaseFlag ++;

			tmpPosVec.clear();
 
			for (int k=0; k<m_availPosition.size(); k++)
			{
				Vector2 orgiPoint(m_availPosition[k].x - currentUnitX / 2, m_availPosition[k].y - currentUnitY / 2);

				currentUnitX = m_gridSizeX / increaseFlag;
				currentUnitY = m_gridSizeY / increaseFlag;

				Vector2 newPoint = orgiPoint;

				for (int i=0; i<increaseFlag; i++)
				{
					for (int j=0; j<increaseFlag; j++)
					{
						newPoint.x = orgiPoint.x + currentUnitX * i + currentUnitX / 2;
						newPoint.y = orgiPoint.y + currentUnitY * j + currentUnitY / 2;

						tmpPosVec.push_back(newPoint);
					}
				}

				currentSize = tmpPosVec.size();
			}
		}
		
		// 如果重新计算过空位
		if (tmpPosVec.size() != 0)
		{
			m_availPosition.clear();
			m_availFlagList.clear();

			for (int i=0; i<tmpPosVec.size(); i++)
			{
				m_availPosition.push_back(tmpPosVec[i]);
				m_availFlagList.push_back(true);
			}	
		}

		m_gridSizeX = currentUnitX;
		m_gridSizeY = currentUnitY;

		longForScale = m_gridSizeX ? m_gridSizeY : m_gridSizeX < m_gridSizeY;
		
		//TRACE("Long for scale in spoly : %f \n\n", longForScale);
		// 所有可用空位均在avail Vector中
		// 随机生成可用的空位

		m_positionList.clear();
		m_availFlagList.clear();
		
		random_shuffle(m_availPosition.begin(), m_availPosition.end());

 		for (int i=0; i<buildingCnt; i++)
		{
 			vgKernel::Vec3 position(m_availPosition[i].x, 0, -m_availPosition[i].y);
 			m_positionList.push_back(position);
		}

// 		for (int i=0; i<m_availPosition.size(); i++)
// 		{
// 			m_availFlagList.push_back(true);
// 		}
// 		
// 		int index=0, flag=3, indexArray[] = {1, 3, 5, 7}; //=0, jmpFlag = ceil(m_availPosition.size() / buildingCnt);
// 		
// 		for (int i=0; i<buildingCnt; i++)
// 		{	
// 			vgKernel::Vec3 position(m_availPosition[index].x, 0, -m_availPosition[index].y);
// 			m_positionList.push_back(position);
// 			m_availFlagList[index] = false;
// 
// 			index += indexArray[flag];
// 			if (index >= m_availPosition.size())
// 			{	
// 				index = 0;
// 				flag --;
// 				if (flag < 0)
// 				{
// 					AfxMessageBox("index error");
// 					return false;
// 				}
// 			}
// 
// 			while (m_availFlagList[index] == false)
// 			{
// 				index ++;
// 				if (index > m_availPosition.size())
// 				{
// 					index = 0;
// 				}
// 			}
// 		}

		return true;
	}

	int SpecialPolygon::getRPs(int schem, int year)
	{
		if (m_pInfoFeature == NULL)
		{
			return 0;
		}

		stringstream ousString;

		ousString << vgVector::AutoBuildManager::scheStr[schem] << "_" << year;

		int numberInFile = m_pInfoFeature->GetFieldAsInteger(ousString.str().c_str());
	
		// 可根据用户的需求更改计算公式.
		return numberInFile / 2;
	}	

	int SpecialPolygon::generateModelByYears(vgVector::AutobuildNodeVec &autoNodeVec, int schem, int years)
	{
		// 根据年份数据clone autonode 返回所构造的模型数量

		// 从feature中读取schem对应年份的household
		stringstream outString;
		
		m_modelList.clear();

		if (autoNodeVec.size() == 0)
		{
			VGK_SHOW("无可用自动建模模型 \n");
			return 0;
		}

		OGRFeature *pFeature = this->getOGRFeature();

		string sid = pFeature->GetFieldAsString("ID");

		OGRFeature::DestroyFeature(pFeature);

		// int  num = vgVector::AutoBuildManager::getSingleton().getRPS(sid, schem, years);
		
		int num = getRPs(schem, years);
		
// 		outString << "RPs: "<< num <<"\n";
// 		VGK_SHOW(outString.str());
// 		outString.str("");

		int flat1 = 0, 
			flat3 = 0, 
			flat4 = 0, 
			flat5 = 0;
	
		if ( num < 10)
		{
			// houseHold就是房子数目
			flat1 = num;

			makeNewBuilding(autoNodeVec, flat1, 1);
		}
		else if ( num < 30 )
		{
			flat3 = ( num - FLAT1_HOUSEHOLD ) / FLAT3_HOUSEHOLD;
			flat1 = num - flat3 * FLAT3_HOUSEHOLD;
			
			makeNewBuilding(autoNodeVec, flat3, 3);
			makeNewBuilding(autoNodeVec, flat1, 1);
		}
		else if ( num < 50 )
		{
			flat4 = ( num - FLAT1_HOUSEHOLD - FLAT3_HOUSEHOLD ) / FLAT4_HOUSEHOLD;
			num = num - flat4 * FLAT4_HOUSEHOLD;

			flat3 = ( num - FLAT1_HOUSEHOLD ) / FLAT3_HOUSEHOLD;
			num = num - flat3 * FLAT3_HOUSEHOLD;

			flat1 = num;

			makeNewBuilding(autoNodeVec, flat4, 4);
			makeNewBuilding(autoNodeVec, flat3, 3);
			makeNewBuilding(autoNodeVec, flat1, 1);
		}
		else
		{
			flat5 = ( num - FLAT5_HOUSEHOLD - FLAT4_HOUSEHOLD - FLAT3_HOUSEHOLD - FLAT1_HOUSEHOLD) / FLAT5_HOUSEHOLD;
			num = num - flat5 * FLAT5_HOUSEHOLD;

			flat4 = ( num - FLAT1_HOUSEHOLD - FLAT3_HOUSEHOLD ) / FLAT4_HOUSEHOLD;
			num = num - flat4 * FLAT4_HOUSEHOLD;

			flat3 = ( num - FLAT1_HOUSEHOLD ) / FLAT3_HOUSEHOLD;
			num = num - flat3 * FLAT3_HOUSEHOLD;

			flat1 = num;

			makeNewBuilding(autoNodeVec, flat5, 5);
			makeNewBuilding(autoNodeVec, flat4, 4);
			makeNewBuilding(autoNodeVec, flat3, 3);
			makeNewBuilding(autoNodeVec, flat1, 1);
		}

		return flat1 + flat3 + flat4 + flat5;
	}

	void SpecialPolygon::makeNewBuilding(vgVector::AutobuildNodeVec &autoBuildVec, int number, int size)
	{
		stringstream outString;

		int buildingIndex = 0;

		for (int i=0; i<number; i++)
		{
			buildingIndex =  rand() % autoBuildVec.size();

			vgVector::AutoBuildNode *pNewBuilding = new vgVector::AutoBuildNode;

			pNewBuilding->cloneFromAutobuildNode(autoBuildVec[buildingIndex]);

			pNewBuilding->setSize(size);

			vgVector::AutoBuildManager::getSingleton().addPlanNode(pNewBuilding);

			m_modelList.push_back(pNewBuilding);

			// leven add
			_autoBuilds.push_back( pNewBuilding );

		}

	}

	void SpecialPolygon::calculateGrid(OGRGeometry *pGemo, int gridNum)
	{
		stringstream outString;

		VGK_SHOW("Calculate Grid. \n");
		OGRGeometry *poGeometry = pGemo;

		m_availPosition.clear();
		m_availFlagList.clear();

		poGeometry->flattenTo2D();

		OGREnvelope evn;
		poGeometry->getEnvelope(&evn);

		float wid = (evn.MaxX - evn.MinX);
		float hei = (evn.MaxY - evn.MinY);
		float widHeightRat =  wid / hei;

		int blockx, blocky;

		blockx = ceil(sqrt(gridNum / widHeightRat));
		blocky = ceil(blockx / widHeightRat);

		float unitx = wid / blockx;
		float unity = hei / blocky;

		m_gridSizeX = unitx;
		m_gridSizeY = unity;

		float x,y;

		for (int i=0; i<blockx; i++)
		{
			for (int j=0; j<blocky; j++)
			{
				x = evn.MinX + unitx*(2*i+1)/2.0;
				y = evn.MinY + unity*(2*j+1)/2.0;

//  				Vector2 rightdown(x+unitx/2, y+unity/2);	
//  				Vector2 rightup(x+unitx/2, y-unity/2);		
//  				Vector2 leftup(x-unitx/2, y-unity/2);		
//  				Vector2 leftdown(x-unitx/2, y+unity/2);		

  				Vector2 rightdown(x+unitx/2, y-unity/2);	
  				Vector2 rightup(x+unitx/2, y+unity/2);		
  				Vector2 leftup(x-unitx/2, y+unity/2);		
  				Vector2 leftdown(x-unitx/2, y-unity/2);		

				OGRLinearRing rings;
				rings.addPoint(leftup.x, leftup.y);
				rings.addPoint(rightup.x, rightup.y);
				rings.addPoint(rightdown.x, rightdown.y);
				rings.addPoint(leftdown.x, leftdown.y);
				
// 				OGRPoint startPoint;
// 				OGRPoint endPoint;

				rings.closeRings();
				rings.flattenTo2D();

				OGRPolygon poly;
				poly.addRing(&rings);
				poly.flattenTo2D();

// 				rings.StartPoint(&startPoint);
// 				rings.EndPoint(&endPoint);

// 				assert(endPoint.x == startPoint.x);
// 				assert(endPoint.y == startPoint.y);
// 				assert(startPoint.x == leftup.x && startPoint.y == leftup.y);

				//if (poGeometry->Contains(&rings))
				if (poGeometry->Contains(&poly))
				{
					m_availPosition.push_back(Vector2(x,y));
					m_availFlagList.push_back(true);
				}
							
// 				for (int i=0; i<pModQueue->size(); i++)
// 				{
// 					pObjectNode = dynamic_cast<vgCore::ObjectNode*>(pModQueue->);
// 				}
			}
		}

		
		outString <<  "Avail position : " <<  m_availPosition.size() << "\n";
		VGK_SHOW(outString.str());

		return ;
	}


	void SpecialPolygon::setAutoInfo(OGRFeature *pFeature, OGRGeometry *pGemo)
	{
		stringstream outString;

		m_availPosition.clear();
		m_availFlagList.clear();

		m_pResultGemo = pGemo;
		m_pInfoFeature = pFeature;	
	
		int gridCnt = pFeature->GetFieldAsInteger("AvailGridN");
	
		// TRACE("Available grid number: %d \n", gridCnt);
		for (int i=0; i<gridCnt; i++)
		{
			outString.str("");
			outString << "Grid_" << i<< "_x";
			double x = pFeature->GetFieldAsDouble(outString.str().c_str());
			
			outString.str("");
			outString << "Grid_"<< i << "_y";
			double y = pFeature->GetFieldAsDouble(outString.str().c_str());

			Vector2 point(x, y);
			m_availPosition.push_back(point);
		}

		m_gridSizeX = pFeature->GetFieldAsDouble("GridSizeX");
		m_gridSizeY = pFeature->GetFieldAsDouble("GridSizeY");
	}

	void SpecialPolygon::renderInSelectedMode()
	{
		// red
		glColor3f( 1, 0, 0 );
		glDisable( GL_TEXTURE_2D );
		//glPointSize( 5.0f );

		glLineWidth( 3.0f );
		glPushMatrix();

		glDisable( GL_DEPTH_TEST );

		glBegin( GL_LINE_STRIP );
		for ( int i = 0 ; i < _rings.size() ; ++ i )
		{

			for(int j = 0; j < _rings[i]._numPoints; j++)
			{
				GLdouble* addr = _rings[i]._pointsBeginAddr + 3 * j;

				//double x = *(addr);
				//double y = *(addr+1);
				//double z = *(addr+2);

				glVertex3dv( addr );
			}

		}
		glEnd();


		glEnable( GL_DEPTH_TEST );

		glPopMatrix();
	}

	int SpecialPolygon::getNowBuildingNum()
	{
		
		int buiding_num = 0;

		// 继续计算去掉building包围盒的地块
		vgKernel::RendererQueue *pModQueue = 
			vgKernel::RendererManager::getSingleton().getRendererQueueByType(vgCore::RENDERER_TYPE_MODOJBECT, false);

		if (pModQueue == NULL)
		{
			VGK_SHOW("Mod model no found. \n");
			return false;
		}

		/*vgKernel::Renderer *pRenderer;*/
		vgCore::ObjectNode *pObjectNode;

		vgKernel::Box selfbox = getEnvelope3f();

		selfbox.matrixTranslation( getFatherLayer()->getMatrix() );

		vgKernel::RendererQueue::iterator iter = pModQueue->begin();
		vgKernel::RendererQueue::iterator iter_end = pModQueue->end();

		while (iter != iter_end)
		{
			pObjectNode = dynamic_cast<vgCore::ObjectNode*>(*iter);

			if (pObjectNode == NULL)
			{
				TRACE("类型错误 \n");
				continue;
			}

			vgKernel::Box box = pObjectNode->getBoundingBox();


			bool inside = false;


			bool testx =  (selfbox._maxVertex.x < box._minVertex.x || 
				selfbox._minVertex.x > box._maxVertex.x );

			bool testz =  (selfbox._maxVertex.z < box._minVertex.z || 
				selfbox._minVertex.z > box._maxVertex.z );

			if ( testx == true || testz == true )
			{
				inside = false;
			}
			else
			{
				inside = true;
			}


			if ( inside == true )
			{
				buiding_num++;
			}

			iter ++;
		}

		return buiding_num;
	} // end else

	float SpecialPolygon::getArea()
	{
		vgKernel::Box box = getEnvelope3f();

		vgKernel::Vec3 v = box.getSize();
		
		return sqrt( v.x * v.x + v.z * v.z );
	}


#endif

	//bool SpecialPolygon::addUIAutoBuildNode( AutoBuildNode* pNode )
	//{
	//	assert( pNode != NULL );
	//	//------------------------------------------
	//	// 检查是否已经在队列中
	//	// 并且插入
	//	//------------------------------------------
	//	if (find(m_modelList.begin(), m_modelList.end(), pNode) == m_modelList.end())
	//	{
	//		m_modelList.push_back(pNode);
	//	}
	//	else
	//	{
	//		assert(0);
	//	}


	//	pNode->setName(pNode->m_pMidNode->GetName());
	//	//pNode->SetName(pNode->m_pMidNode->GetName());

	//	vgKernel::RendererManager::getSingleton().addRenderer(pNode);

	//	// 自动建模节点在规划中不向树视图添加节点.


	//	HTREEITEM	hRootGpu = vgUI::UIController::getSingleton().GetRootGpu(vgCore::IMG_AUTOBUILD);

	//	vgBaseEntry* entry = vgEntryFactory::createEntryFromRenderer( pNode );
	//	vgUI::UIController::getSingleton().AddNode( hRootGpu, entry );

	//	vgUI::UIController::getSingleton().SelectNode(entry);
	//	pNode->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
	//	// vgKernel::SelectManager::getSingleton().updateSelectedItem();


	//	if (find(m_autoBuildNodeRenderList.begin(), m_autoBuildNodeRenderList.end(), pNode) == m_autoBuildNodeRenderList.end())
	//	{
	//		m_autoBuildNodeRenderList.push_back(pNode);

	//		return true;
	//	}
	//	else
	//	{
	//		return false;
	//	}
	//}
}// end of namespace vgShape
