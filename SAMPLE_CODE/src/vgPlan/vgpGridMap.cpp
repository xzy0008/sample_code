#include <vgStableHeaders.h>
#include <vgPlan/vgpGridMap.h>

namespace vgPlan
{
	float GridStruct::s_sizex;
	float GridStruct::s_sizey;

	GridMap::GridMap()
	{
		m_blockXNum = 0;
		m_blockYNum = 0;
		
		m_gridVec = NULL;
		// m_oriGirdVec = NULL;
	}

	GridMap::GridMap(Vec2 leftDownPoint, Vec2 gridSize, float xResolve, float yResolve)
	{
		m_blockXNum = 0;
		m_blockYNum = 0;
		
		m_gridVec = NULL;
		// m_oriGirdVec = NULL;
		
		initialise(leftDownPoint, gridSize, xResolve, yResolve);
	}

	GridMap::~GridMap()
	{
		if (m_gridVec != NULL)
		{
			delete [] m_gridVec;
		}
// 
// 		if (m_oriGirdVec != NULL)
// 		{
// 			delete [] m_oriGirdVec;
// 		}
	}

	void GridMap::initialise(Vec2 leftDownPoint, Vec2 gridSize, float xResolve, float yResolve)
	{
		m_blockXNum = ceil(gridSize.x / xResolve);
		m_blockYNum = ceil(gridSize.y / yResolve);
		
		if (m_gridVec != NULL)
		{
			delete [] m_gridVec;
		}
		// m_gridVec.reserve(m_blockXNum * m_blockYNum + 1);
		m_gridVec = new GridStruct[m_blockXNum * m_blockYNum];
 		// m_oriGirdVec = new GridStruct[m_blockXNum * m_blockYNum];

		for (int i=0; i<m_blockXNum; i++)
		{
			for (int j=0; j<m_blockYNum; j++)
			{
				//GridStructSharedPtr pGrid(new GridStruct);
				GridStruct *pGrid = new GridStruct;

				pGrid->ix = i;
				pGrid->iy = j;
				pGrid->px = leftDownPoint.x + i*xResolve;
				pGrid->py = leftDownPoint.y + j*yResolve;
				
				pGrid->s_sizex = xResolve;
				pGrid->s_sizey = yResolve;

				// m_gridVec.push_back(pGrid);
				m_gridVec[array_index(i,j)] = *pGrid;
				// m_oriGirdVec[array_index(i, j)] = *pGrid;
				
				delete pGrid;
			}
		}
	}

	void GridMap::calculateAvailGrid(OGRGeometry *pGemo)
	{
		quadCompute(0, 0, m_blockXNum, m_blockYNum, pGemo);

		// memcpy(m_oriGirdVec, m_gridVec, m_blockXNum*m_blockYNum*sizeof(GridStruct));

		return ;
	}

	void GridMap::quadCompute(int ix, int iy, int blockCntX, int blockCntY, OGRGeometry* pGemo)
	{
		int qx = blockCntX / 2;
		int qy = blockCntY / 2;
		
		if (qx != 0 && qy != 0)
		{

			// ix, iy, qx, qy
			if (containGrid(ix, iy, qx, qy, pGemo))
			{
				// TRACE("Color %d %d \n", qx, qy);

				colorGrid(ix, iy, qx, qy, 1);
			}
			else if (! overlapeGrid(ix, iy, qx, qy, pGemo))
			{
				colorGrid(ix, iy, qx, qy, 0);
			}
			else
			{
				quadCompute(ix, iy, qx, qy, pGemo);
			}

			// ix+qx, iy, blockCntX-qx
			if (containGrid(ix+qx, iy, blockCntX-qx, qy, pGemo))
			{
				// TRACE("Color %d %d \n", blockCntX-qx, qy);

				colorGrid(ix+qx, iy, blockCntX-qx, qy, 1);
			}
			else if (! overlapeGrid(ix+qx, iy, blockCntX-qx, qy, pGemo))
			{
				colorGrid(ix+qx, iy, blockCntX-qx, qy, 0);
			}
			else
			{
				quadCompute(ix+qx, iy, blockCntX-qx, qy, pGemo);
			}

			// ix+qx, iy+qy, blockCntX-qx, blockCntY-qy
			if (containGrid(ix+qx, iy+qy, blockCntX-qx, blockCntY-qy, pGemo))
			{
				//TRACE("Color %d %d \n", blockCntX-qx, blockCntY-qy);

				colorGrid(ix+qx, iy+qy, blockCntX-qx, blockCntY-qy, 1);
			}
			else if (! overlapeGrid(ix+qx, iy+qy, blockCntX-qx, blockCntY-qy, pGemo))
			{
				colorGrid(ix+qx, iy+qy, blockCntX-qx, blockCntY-qy, 0);
			}
			else
			{
				quadCompute(ix+qx, iy+qy, blockCntX-qx, blockCntY-qy, pGemo);
			}

			// ix, iy+qy, qx, blockCntY-qy
			if (containGrid(ix, iy+qy, qx, blockCntY-qy, pGemo))
			{
				//TRACE("Color %d %d \n", qx, blockCntY-qy);

				colorGrid(ix, iy+qy, qx, blockCntY-qy, 1);
			}
			else if (! overlapeGrid(ix, iy+qy, qx, blockCntY-qy, pGemo))
			{
				colorGrid(ix, iy+qy, qx, blockCntY-qy, 0);
			}
			else
			{
				quadCompute(ix, iy+qy, qx, blockCntY-qy, pGemo);
			}
		}
		else
		{
			for (int i=0; i<blockCntX; i++)
			{
				for (int j=0; j<blockCntY; j++)
				{
					int index = array_index(ix+i, iy+j);

					OGRPoint point1(m_gridVec[index].px, m_gridVec[index].py);

					OGRPoint point2(m_gridVec[index].px + m_gridVec[index].s_sizex, m_gridVec[index].py);
					OGRPoint point3(m_gridVec[index].px + m_gridVec[index].s_sizex, m_gridVec[index].py + m_gridVec[index].s_sizey);
					OGRPoint point4(m_gridVec[index].px, m_gridVec[index].py + m_gridVec[index].s_sizey);

			
					pGemo->flattenTo2D();
		
					if (point1.Within(pGemo) && point2.Within(pGemo) && point3.Within(pGemo) && point4.Within(pGemo))
					{
						m_gridVec[index].availFlag = 1;
					}
				}
			}
		}
	}
	
	bool GridMap::containGrid(int ix, int iy, int blockCntX, int blockCntY, OGRGeometry* pGeom)
	{
		int index = array_index(ix, iy);
		// assert(index < m_gridVec.size());
		
		// GridStructSharedPtr pGrid = m_gridVec[index];
		GridStruct *pGrid = &m_gridVec[index];

		float x = pGrid->px;
		float y = pGrid->py;

		float gridSizeX = pGrid->s_sizex;
		float gridSizeY = pGrid->s_sizey;

		OGRPoint point1(m_gridVec[index].px, m_gridVec[index].py);
		OGRPoint point2(m_gridVec[index].px + m_gridVec[index].s_sizex*blockCntX, m_gridVec[index].py);
		OGRPoint point3(m_gridVec[index].px + m_gridVec[index].s_sizex*blockCntX, m_gridVec[index].py + m_gridVec[index].s_sizey*blockCntY);
		OGRPoint point4(m_gridVec[index].px, m_gridVec[index].py + m_gridVec[index].s_sizey*blockCntY);
		
		pGeom->flattenTo2D();

		return (point1.Within(pGeom) && point2.Within(pGeom) && point3.Within(pGeom) && point4.Within(pGeom));
	}

	bool GridMap::overlapeGrid(int ix, int iy, int blockCntX, int blockCntY, OGRGeometry* pGeom)
	{
		int index = array_index(ix, iy);
		//assert(index < m_gridVec.size());
		// GridStructSharedPtr pGrid = m_gridVec[index];
		GridStruct* pGrid = &m_gridVec[index];

		float x = pGrid->px;
		float y = pGrid->py;

		float gridSizeX = pGrid->s_sizex;
		float gridSizeY = pGrid->s_sizey;

		OGRPoint point1(m_gridVec[index].px, m_gridVec[index].py);
		OGRPoint point2(m_gridVec[index].px + m_gridVec[index].s_sizex*blockCntX, m_gridVec[index].py);
		OGRPoint point3(m_gridVec[index].px + m_gridVec[index].s_sizex*blockCntX, m_gridVec[index].py + m_gridVec[index].s_sizey*blockCntY);
		OGRPoint point4(m_gridVec[index].px, m_gridVec[index].py + m_gridVec[index].s_sizey*blockCntY);

		pGeom->flattenTo2D();

		return (point1.Within(pGeom) || point2.Within(pGeom) || point3.Within(pGeom) || point4.Within(pGeom));
	}

#if 0
	OGRLinearRing* GridMap::getRingsFormGrid(int ix, int iy, int blockCntX, int blockCntY)
	{
		OGRLinearRing *pRings = new OGRLinearRing;
		

		int index = array_index(ix, iy);
		assert(index < m_gridVec.size());
		GridStructSharedPtr pGrid = m_gridVec[index];

		float x = pGrid->px;
		float y = pGrid->py;
		
		float gridSizeX = pGrid->s_sizex;
		float gridSizeY = pGrid->s_sizey;

		pRings->addPoint(x, y);
		pRings->addPoint(x, y+blockCntY*gridSizeY);
		pRings->addPoint(x+blockCntX*gridSizeX, y+blockCntY*gridSizeY);
		pRings->addPoint(x+blockCntX*gridSizeX, y);

		pRings->closeRings();

		pRings->flattenTo2D();

		return pRings;
	}
#endif
	
//	void GridMap::prepareAvailGrid()
//	{
// 		vector<GridStructSharedPtr>::iterator iter = m_gridVec.begin();
// 		vector<GridStructSharedPtr>::iterator end_iter = m_gridVec.end();
// 
// 		// 初始化
// 		while (iter != end_iter)
// 		{
// 			if ((*iter)->availFlag == 1)
// 			{
// 				(*iter)->availOnXHorizon = 1;
// 				(*iter)->availOnYHorizon = 1;
// 				(*iter)->availOnXVertical = 1;
// 				(*iter)->availOnYVertical = 1;
// 			}
// 			else
// 			{
// 				(*iter)->availOnXHorizon = 0;
// 				(*iter)->availOnYHorizon = 0;
// 				(*iter)->availOnXVertical = 0;
// 				(*iter)->availOnYVertical = 0;
// 			}
// 		}
//	}

	void GridMap::prepareAvailGrid(int ix, int iy)
	{
		for (int i=ix; i>=0; i--)
		{
			for (int j=iy; j>=0; j--)
			{
				if ( m_gridVec[array_index(i, j)].availFlag == 1 ||  m_gridVec[array_index(i, j)].availFlag == 2)
				// if ( m_gridVec[array_index(i, j)].availFlag != 0)
				{
					m_gridVec[array_index(i, j)].availOnXHorizon = 1;
					m_gridVec[array_index(i, j)].availOnYHorizon = 1;
					m_gridVec[array_index(i, j)].availOnXVertical = 1;
					m_gridVec[array_index(i, j)].availOnYVertical = 1;

					m_gridVec[array_index(i, j)].followOnXHorizon = 1;
					m_gridVec[array_index(i, j)].followOnYHorizon = 1;
					m_gridVec[array_index(i, j)].followOnXVertical = 1;
					m_gridVec[array_index(i ,j)].followOnYVertical = 1;
				}
				else
				{
					m_gridVec[array_index(i, j)].availOnXHorizon = 0;
					m_gridVec[array_index(i, j)].availOnYHorizon = 0;
					m_gridVec[array_index(i, j)].availOnXVertical = 0;
					m_gridVec[array_index(i, j)].availOnYVertical = 0;


					m_gridVec[array_index(i, j)].followOnXHorizon = 0;
					m_gridVec[array_index(i, j)].followOnYHorizon = 0;
					m_gridVec[array_index(i, j)].followOnXVertical = 0;
					m_gridVec[array_index(i ,j)].followOnYVertical = 0;
				}
			}
		}
	}

	bool GridMap::colorGrid(int ix, int iy, int blockCntX, int blockCntY, int flag, int blockId)
	{

		for (int i=0; i<blockCntX; i++)
		{
			for (int j=0; j<blockCntY; j++)
			{
				m_gridVec[array_index(ix + i,iy+j)].availFlag = flag;
				m_gridVec[array_index(ix + i,iy+j)].usedBlockId = blockId;
			}
		}
		return true;
	}

	void GridMap::render()
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		
		glDisable(GL_TEXTURE_2D);


	//	for (int i=0; i<m_gridVec.size(); i++)
		for (int i=0; i<m_blockXNum*m_blockYNum; i++)
		{
			vgKernel::Vec3 point(m_gridVec[i].px, 0, -m_gridVec[i].py);
			float sizex = m_gridVec[i].s_sizex;
			float sizey = m_gridVec[i].s_sizey;
			if (m_gridVec[i].availFlag == 0)
			{
				glColor3f(0.0f, 0.f, 0.f);
			}
			else if (m_gridVec[i].availFlag == 3)
			{
				glColor3f(0.f, 0.f, 1.f);
			}
			else
			{
				glColor3f(1.f, 0.f, 0.f);
			}

			glBegin(GL_QUADS);
				glVertex3f(point.x, 10, point.z);	
				glVertex3f(point.x + sizex, 10, point.z);
				glVertex3f(point.x + sizex, 10, point.z - sizey);
				glVertex3f(point.x, 10, point.z - sizey);
			glEnd();
		}

		glPopMatrix();
	}

	// 更新ix 到 iy以上的方格
	bool GridMap::calculateGridBlock(int ix, int iy)
	{
		if (ix == -1 && iy == -1)
		{
			ix = m_blockXNum - 1;
			iy = m_blockYNum - 1;
		}

		if (ix >= m_blockXNum && iy >= m_blockYNum)
		{
			return false;
		}

		int ci, cj;

		prepareAvailGrid(ix, iy);

		//GridStructSharedPtr pGrid; 
		GridStruct* pGrid;

		for (int i=ix; i>=0; i--)
		{
			for (int j=iy; j>=0; j--)
			{
				pGrid = &m_gridVec[i * m_blockYNum +  j];

				// 当不能摆放或已经摆放上block的时候
				if (pGrid->availFlag == 0 || pGrid->availFlag == 3)
				{
					continue ;
				}

				ci = i + 1;
				cj = j + 1;

				// 有两个查找方向 xVertical and yHorizon.
				if (ci != m_blockXNum)
				{
					// 计算 ci，j
					pGrid->availOnXVertical = m_gridVec[ci*m_blockYNum + j].availOnXVertical + 1;
					
					// j+1 边界
					if ( (j+1 < m_blockYNum ) && (m_gridVec[i*m_blockYNum+ j+1].availOnXVertical >= pGrid->availOnXVertical) )
					{
						pGrid->availOnYVertical = m_gridVec[i*m_blockYNum + j+1].availOnYVertical + 1;
					}
					else
					{
						pGrid->availOnYVertical = 1;
					}

					if ( (j+1 < m_blockYNum) && (m_gridVec[i*m_blockYNum+ j+1].followOnXHorizon != 0) && (pGrid->availOnXVertical >= m_gridVec[i*m_blockYNum+ j+1].followOnXHorizon ) )
					{
						pGrid->followOnXVertical = m_gridVec[i*m_blockYNum+ j+1].followOnXHorizon;
						pGrid->followOnYVertical = m_gridVec[i*m_blockYNum+ j+1].followOnYHorizon + 1;
					}
				
				}

				if (cj != m_blockYNum)
				{
					// 计算 i, cj
					pGrid->availOnYHorizon = m_gridVec[i * m_blockYNum + cj].availOnYHorizon + 1;
					
					if ( (i+1 < m_blockXNum) && (m_gridVec[(i+1)*m_blockYNum + j].availOnYHorizon >= pGrid->availOnYHorizon) )
					{
						pGrid->availOnXHorizon = m_gridVec[(i+1)*m_blockYNum + j].availOnXHorizon + 1;
					}
					else
					{
						pGrid->availOnXHorizon = 1;
					}

					if ( (i+1 < m_blockXNum) && (m_gridVec[(i+1)*m_blockYNum + j].followOnYVertical != 0) && (pGrid->availOnYHorizon >= m_gridVec[(i+1)*m_blockYNum + j].followOnYVertical ) )
					{
						pGrid->followOnXHorizon = m_gridVec[(i+1)*m_blockYNum + j].followOnXVertical + 1;
						pGrid->followOnYHorizon = m_gridVec[(i+1)*m_blockYNum + j].followOnYVertical;
					}
				}

			}
		}

		// dumpToFile();

		return true;
	}

// 	bool GridMap::dumpToFile(string fileName /* = */ )
// 	{
// 		CFile dumpFile;
// 		stringstream outString;
// 
// 		if ( ! dumpFile.Open(fileName.c_str(), CFile::modeWrite | CFile::modeCreate | CFile::typeText) )
// 		{	
// 			AfxMessageBox("dump file open error.");
// 			return false;
// 		}
// 
// 		for (int i=0; i<m_blockXNum; i++)
// 		{
// 			outString.str("");
// 
// 			for (int j=0; j<m_blockYNum; j++)
// 			{
// 				GridStruct* pGrid = &m_gridVec[i*m_blockYNum+j];
// 
// 				outString << "(" << setw(3) << pGrid->availOnXVertical << ", " 
// 					             << setw(3) << pGrid->availOnYVertical << ")"
// 						  << "(" << setw(3) << pGrid->availOnXHorizon  << ", "
// 						         << setw(3) << pGrid->availOnYHorizon  << ")"
//  						  << "(" << setw(3) << pGrid->followOnXVertical << ","
//  								 << setw(3) << pGrid->followOnYVertical << ")"
//  						  << "(" << setw(3) << pGrid->followOnXHorizon  << ","
//  								 << setw(3) << pGrid->followOnYHorizon  << ")"
//                           << "\t";
// 
// 			}
// 			outString << "\r\n";
// 
// 			dumpFile.Write(outString.str().c_str(), outString.str().length());
// 
// 			// dumpFile.Write("\r\n", 2);
// 		}
// 		
// 		dumpFile.Close();
// 
// 		return true;
// 	}

	int GridMap::putBlockInGrid(int blockX, int blockY, int minAliasX, int minAliasY, int minAliasR)
	{	
		// memcpy(m_gridVec, m_oriGirdVec, m_blockXNum*m_blockYNum*sizeof(GridStruct));

		initGridBlockBeforePut();

		calculateGridBlock();

		m_blockGridVec.clear();

		int blockIdCnt = 0;

		bool findFlag = true;

		GridStruct *pGrid;

		while (findFlag)
		{
			findFlag = false;

			for (int i=0; i<m_blockXNum; i++)
			{
				for (int j=0; j<m_blockYNum; j++)
				{
					pGrid = &m_gridVec[array_index(i, j)];

					// 如果当前方格能摆放
					if (pGrid->availFlag == 1)
					{
						// 可摆放的范围大于体块大小
						if ( (pGrid->availOnXHorizon >= blockX && pGrid->availOnYHorizon >= blockY) 
								|| (pGrid->availOnXVertical >= blockX && pGrid->availOnYVertical >= blockY) 
								|| (pGrid->followOnXVertical >= blockX && pGrid->followOnYVertical >= blockY)
								|| (pGrid->followOnXHorizon >= blockX && pGrid->followOnYHorizon >= blockY)
						   )
						{
							// 与已经摆放的体块满足间距要求 可增加其它条件如日照分析
							if ( distanceAvail(i, j, blockX, blockY, minAliasX, minAliasY, minAliasR) )
							{
								colorGrid(i, j, blockX, blockY, 3, blockIdCnt);
								//calculateGridBlock(i+blockX, j+blockY);
								calculateGridBlock(i+blockX-1, j+blockY-1);
								findFlag = true;
								blockIdCnt ++;

								m_blockGridVec.push_back(*pGrid);
							}
						}
					}
				}
			}
		}

		return blockIdCnt;
	}

	void GridMap::initGridBlockBeforePut()
	{
		for (int i=m_blockXNum-1; i>=0; i--)
		{
			for (int j=m_blockYNum-1; j>=0; j--)
			{
				if ( m_gridVec[array_index(i, j)].availFlag != 0)
				{
					m_gridVec[array_index(i, j)].availOnXHorizon = 1;
					m_gridVec[array_index(i, j)].availOnYHorizon = 1;
					m_gridVec[array_index(i, j)].availOnXVertical = 1;
					m_gridVec[array_index(i, j)].availOnYVertical = 1;

					m_gridVec[array_index(i, j)].followOnXHorizon = 1;
					m_gridVec[array_index(i, j)].followOnYHorizon = 1;
					m_gridVec[array_index(i, j)].followOnXVertical = 1;
					m_gridVec[array_index(i ,j)].followOnYVertical = 1;

					m_gridVec[array_index(i ,j)].availFlag = 1;
				}
				else
				{
					m_gridVec[array_index(i, j)].availOnXHorizon = 0;
					m_gridVec[array_index(i, j)].availOnYHorizon = 0;
					m_gridVec[array_index(i, j)].availOnXVertical = 0;
					m_gridVec[array_index(i, j)].availOnYVertical = 0;


					m_gridVec[array_index(i, j)].followOnXHorizon = 0;
					m_gridVec[array_index(i, j)].followOnYHorizon = 0;
					m_gridVec[array_index(i, j)].followOnXVertical = 0;
					m_gridVec[array_index(i ,j)].followOnYVertical = 0;
				
					m_gridVec[array_index(i ,j)].availFlag = 0;
				}
			}
		}
	}

	bool GridMap::distanceAvail(int ix, int iy, int blockSizeX, int blockSizeY, int distInX, int distInY, int distInR)
	{

		int slice = blockSizeX ? blockSizeY : blockSizeX < blockSizeY;
		
		slice = slice / 2;
		
		int rightBottomIx = ix + blockSizeX - 1;
		int rightBottomIy = iy + blockSizeY - 1;

		int cntX = 0;
		int cntY = 0;

		int innerSlice;

		bool oncex = true;
		bool oncey = true;

		while (cntX < blockSizeX || cntY < blockSizeY)
		{
			if ( cntX < blockSizeX /*&& iy-distInY > 0 */)
			{
				innerSlice = 1;

				// 左边向左
				while (innerSlice < distInY && iy-innerSlice > 0)
				{
					assert (ix+cntX < m_blockXNum && iy-innerSlice > 0);

	 				if ( m_gridVec[array_index(ix+cntX, iy-innerSlice)].availFlag == 3 )
	 				{
	 					return false;
	 				}
					// innerSlice += slice;
					innerSlice += 1;
				}

 				if ( iy-distInY > 0 && m_gridVec[array_index(ix+cntX, iy-distInY)].availFlag == 3 )
 				{
 					return false;
 				}
			}


			if ( cntX < blockSizeX /*&& rightBottonIy+distInY < m_blockYNum && rightBottomIx-cntX > 0*/)
			{
				innerSlice = 1;

				while (innerSlice < distInY && rightBottomIy+innerSlice < m_blockYNum)
				{
					// 右边向右
					if ( m_gridVec[array_index(rightBottomIx-cntX, rightBottomIy+innerSlice)].availFlag == 3)
					// if ( m_gridVec[array_index(ix+cntX, rightBottonIy+innerSlice)].availFlag == 3)
					{
						return false;
					}
					//innerSlice += slice;
					innerSlice += 1;
				}

				if ( rightBottomIy+distInY < m_blockYNum && m_gridVec[array_index(rightBottomIx-cntX, rightBottomIy+distInY)].availFlag == 3)
				//if ( m_gridVec[array_index(ix+cntX, rightBottonIy+distInY)].availFlag == 3)
				{
					return false;
				}
			}


			if ( cntY < blockSizeY /*&& ix-distInX > 0*/ )
			{
				innerSlice = 1;

				while (innerSlice < distInX && ix-innerSlice > 0)
				{
					// 上边向上
					if (m_gridVec[array_index(ix-innerSlice, iy+cntY)].availFlag == 3)
					{
						return false;
					}

					//innerSlice += slice;
					innerSlice += 1;
				}

				if (ix-distInX > 0 && m_gridVec[array_index(ix-distInX, iy+cntY)].availFlag == 3)
				{
					return false;
				}
			}


			if ( cntY < blockSizeY /*&& rightBottomIx+distInX < m_blockXNum && rightBottonIy-cntY > 0*/)
			{
				innerSlice = 1;
				// 下边向下
				while (innerSlice < distInX && rightBottomIx+innerSlice < m_blockXNum)
				{
					if (m_gridVec[array_index(rightBottomIx+innerSlice, rightBottomIy-cntY)].availFlag == 3)
					{
						return false;
					}
					// innerSlice += slice;
					innerSlice += 1;
				}
				if (rightBottomIx+distInX < m_blockXNum && m_gridVec[array_index(rightBottomIx+distInX, rightBottomIy-cntY)].availFlag == 3)
				{
					return false;
				}
			}

// 
// 			cntX += slice;
// 			cntY += slice;


			cntX += 1;
			cntY += 1;
			// 计算左下和右上两个顶点
			if (cntX >= blockSizeX && oncex)
			{
				cntX = blockSizeX - 1;
				oncex = false;
			}

			if (cntY >= blockSizeY && oncey)
			{
				cntY = blockSizeY - 1;
				oncey = false;
			}
		}
	

		// 计算斜间距.
		for (int i=1; i<=distInR; i++)
		{
			// 左上向左上
			if (ix-i>=0 && iy-i>=0)
			{
				if (m_gridVec[array_index(ix-i, iy-i)].availFlag == 3)
				{
					return false;
				}
			}

			// 左下向左下
			if (rightBottomIx+i<m_blockXNum && iy-i>=0)
			{
				if (m_gridVec[array_index(rightBottomIx+i, iy-i)].availFlag == 3)
				{
					return false;
				}
			}

			// 右上向右上
			if (ix-i>=0 && rightBottomIy+i<m_blockYNum)
			{
				if (m_gridVec[array_index(ix-i, rightBottomIy+i)].availFlag == 3)
				{
					return false;
				}
			}

			// 右下向右下
			if (rightBottomIx+i<m_blockXNum && rightBottomIy+i<m_blockYNum)
			{
				if (m_gridVec[array_index(rightBottomIx+i, rightBottomIy+i)].availFlag == 3)
				{
					return false;
				}
			}
		}

		return true;
	}
}
