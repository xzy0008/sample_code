#include <vgStableHeaders.h>

#include <vgGIS3D/vggiOgrUtility.h>

#include <vgGis3d/vggiGisDataManager.h>
#include <vgGis3d/vggiLayer.h>
#include <vgGis3d/vggiGeometry.h>
#include <gdal/ogr_core.h>
#include <gdal/ogr_geometry.h>
#include <gdal/ogr_feature.h>
#include <vgGis3d/vggiLine.h>
#include <vgGis3d/vggiMultiLine.h>
#include <vgGis3d/vggiOGRRouteMap.h>
#include <vgGIS/vgGisManager.h>
#include <vgKernel/vgkVec2.h>

#include <limits>
#include <utility>
#include <map>
using std::map;
using std::make_pair;

namespace vgGIS3D
{

	OGRRouteMap::OGRRouteMap()
	{
		m_enableResultRender = false;
	}

	OGRRouteMap::~OGRRouteMap()
	{

	}

	bool OGRRouteMap::intersection(Vec2 pt0, Vec2 pt1, Vec2 pt2, Vec2 pt3, Vec2& re)
	{
		float t0, t1;

		// (1-t0)*pt0+t0*pt1=(1-t1)*pt2+t1*pt3
		// 两个方程，两个未知数，求解t0和t1
		t0 = pt2.y*(pt3.x-pt2.x)-pt2.x*(pt3.y-pt2.y)-(pt0.y*(pt3.x-pt2.x)-pt0.x*(pt3.y-pt2.y));
		t0 /= ((pt1.y-pt0.y)*(pt3.x-pt2.x)-(pt1.x-pt0.x)*(pt3.y-pt2.y));
		t1 = pt0.x+t0*(pt1.x-pt0.x)-pt2.x;
		t1 /= (pt3.x-pt2.x);

		// 检查t0和t1以判断交点是否在线段上
		if ( t0<0 || t0>1 || t1<0 || t1>1 )
			return false;

		re.x = (1-t0)*pt0.x+t0*pt1.x;
		re.y = (1-t0)*pt0.y+t0*pt1.y;

		return true;
	}

	int OGRRouteMap::constructFromBreakShapeLayer(string layerName)
	{
		vgKernel::Vec2 p1(0, 0);
		vgKernel::Vec2 p2(1, 1);
		vgKernel::Vec2 p3(0.5 ,0);
		vgKernel::Vec2 p4(1, 0.2);

		vgKernel::Vec2 re;

		if (intersection(p1,p2,p3,p4,re))
		{
			TRACE("intersection %f %f \n", re.x, re.y);
		}

		m_layerName = layerName;

		long totalPoint = 0;

// 		if (layerName.substr(layerName.length()-4, 4) == ".shp")
// 		{
// 			layerName = layerName.substr(0, layerName.length()-4);
// 		}

		Layer *pLayer 
			= GisDataManager::getSingleton().getLayerByShortName(layerName);
		
		
		if (pLayer == NULL)
		{
			AfxMessageBox("图层不存在");

			return 0;
		}

		GeometryPointerVec *pGeomPtrVec = pLayer->getGeometries();
		
		TRACE("%d \n", pGeomPtrVec->size());

		vector<vgKernel::Vec3> pointVec;
		vector<int>	jointIndexVec;

		map<float, vgKernel::Vec3> tmpMap;
		
		vgGIS3D::GisManager::getSingleton().showProcessingDlg(true);
		vgGIS3D::GisManager::getSingleton().setProcessingInfo("开始处理道路拓扑...");

		for (int i=0; i<pGeomPtrVec->size(); i++)
		{
			vgGIS3D::GisManager::getSingleton().setProcessingProgress((int)((float)i/pGeomPtrVec->size()*100));

			Geometry *pGeom = pGeomPtrVec->at(i);

			LineString *pLineString 
				= dynamic_cast<LineString*>(pGeom);
			
			MultiLine *pMultiLine 
				= dynamic_cast<MultiLine*>(pGeom);

			int lastJointIndex = -1;

			if (pLineString != NULL)
			{
				// AfxMessageBox("LineString");

				RingStruct ringsRef = pLineString->getRing();
				totalPoint += ringsRef._numPoints;

				pointVec.clear();
				jointIndexVec.clear();

				pointVec.reserve(ringsRef._numPoints + 32);

				for (int l=1; l<ringsRef._numPoints; l++)
				{
					pointVec.push_back(vgKernel::Vec3(ringsRef._pointsBeginAddr[(l-1)*3], 
						ringsRef._pointsBeginAddr[(l-1)*3+1],
						ringsRef._pointsBeginAddr[(l-1)*3+2]));
				    jointIndexVec.push_back(pointVec.size()-1);

					tmpMap.clear();

					vgKernel::Vec2 p0(ringsRef._pointsBeginAddr[(l-1)*3 + 0],
						ringsRef._pointsBeginAddr[(l-1)*3 + 2]);

					vgKernel::Vec2 p1(ringsRef._pointsBeginAddr[l*3 + 0],
						ringsRef._pointsBeginAddr[l*3 + 2]);

					for (int j=0; j<pGeomPtrVec->size(); j++)
					{
						// 单线情况
						LineString *pOtherLineString 
							= dynamic_cast<LineString*>(pGeomPtrVec->at(j));

						if (pOtherLineString == NULL)
						{
							continue;
						}
					
						if (j==i || !pOtherLineString->getEnvelope3d().intersectsIn2D(pLineString->getEnvelope3d()))
						{
							if (j==i || !pOtherLineString->getEnvelope3d().intersectsIn2D(pLineString->getEnvelope3d()))
							{
								continue;
							}

							RingStruct otherRingsRef = pOtherLineString->getRing();

							for (int k=1; k<otherRingsRef._numPoints; k++)
							{
								vgKernel::Vec2 p2(otherRingsRef._pointsBeginAddr[(k-1)*3 + 0],
									otherRingsRef._pointsBeginAddr[(k-1)*3 + 2]);

								vgKernel::Vec2 p3(otherRingsRef._pointsBeginAddr[k*3 + 0],
									otherRingsRef._pointsBeginAddr[k*3 + 2]);

								vgKernel::Vec2 result;

								if (intersection(p0, p1, p2, p3, result))
								{
									vgKernel::Vec3 enp(result.x,
										(otherRingsRef._pointsBeginAddr[(k-1)*3 + 1]+ringsRef._pointsBeginAddr[(l-1)*3 + 1]) / 2, 
										result.y);

									tmpMap.insert(make_pair(pointVec[pointVec.size()-1].distance(enp), enp));
									//TRACE("insert to map %d %d %d mapsize %d \n", j, k, k-1,tmpMap.size());
								}
							}
						}
						
						// multiline 情况
						MultiLine *pOtherMultiLine = dynamic_cast<MultiLine*>(pGeomPtrVec->at(j));
						if (pOtherMultiLine != NULL)
						{
							if (j==i || !pOtherMultiLine->getEnvelope3d().intersectsIn2D(pLineString->getEnvelope3d()))
							{
								continue;
							}
							
							RingStructVec ringsVec = pOtherMultiLine->getRings();
							for (int w=0; w<ringsVec.size(); w++)
							{
								RingStruct otherRingsRef = ringsVec.at(w);

								for (int k=1; k<otherRingsRef._numPoints; k++)
								{
									vgKernel::Vec2 p2(otherRingsRef._pointsBeginAddr[(k-1)*3 + 0],
										otherRingsRef._pointsBeginAddr[(k-1)*3 + 2]);

									vgKernel::Vec2 p3(otherRingsRef._pointsBeginAddr[k*3 + 0],
										otherRingsRef._pointsBeginAddr[k*3 + 2]);

									vgKernel::Vec2 result;

									if (intersection(p0, p1, p2, p3, result))
									{
										vgKernel::Vec3 enp(result.x,
											(otherRingsRef._pointsBeginAddr[(k-1)*3 + 1]+ringsRef._pointsBeginAddr[(l-1)*3 + 1]) / 2, 
											result.y);

										tmpMap.insert(make_pair(pointVec[pointVec.size()-1].distance(enp), enp));
										//TRACE("insert to map %d %d %d mapsize %d \n", j, k, k-1,tmpMap.size());
									}
								}
							}
						}

					}

					map<float,vgKernel::Vec3>::iterator iter = tmpMap.begin();
					map<float,vgKernel::Vec3>::iterator iter_end = tmpMap.end();
				
					while (iter != iter_end)
					{
						pointVec.push_back(iter->second);
						jointIndexVec.push_back(pointVec.size()-1);

						iter ++;
					}
				}

				pointVec.push_back(vgKernel::Vec3(ringsRef._pointsBeginAddr[(ringsRef._numPoints-1)*3 + 0], 
					ringsRef._pointsBeginAddr[(ringsRef._numPoints-1)*3 + 1],
					ringsRef._pointsBeginAddr[(ringsRef._numPoints-1)*3 + 2]));
				jointIndexVec.push_back(pointVec.size()-1);
				
				for (int index=1; index<jointIndexVec.size(); index++)
				{
					vgKernel::Vec3 np1 = pointVec[jointIndexVec[index-1]];
					vgKernel::Vec3 np2 = pointVec[jointIndexVec[index]];

					int npIndex1 = checkExist(np1);
					if (npIndex1 == -1)
					{
						JointPointPtr jointPoint(new JointPoint(np1));

						m_jointArray.push_back(jointPoint);
						npIndex1 = m_jointArray.size() - 1;
					}

					int npIndex2 = checkExist(np2);
					if (npIndex2 == -1)
					{
						JointPointPtr jointPoint(new JointPoint(np2));

						m_jointArray.push_back(jointPoint);
						npIndex2 = m_jointArray.size() - 1;
					}

					double distance = np1.distance(np2);

					m_jointArray[npIndex1]->addRoute(JointDist(npIndex2, distance));
					m_jointArray[npIndex2]->addRoute(JointDist(npIndex1, distance));
				}

				
				//TRACE("Connect %d  -  %d \n", npIndex1, npIndex2);

			}
			if (pMultiLine != NULL)
			{
				RingStructVec ringsVec = pMultiLine->getRings();
				
				for (int x=0; x<ringsVec.size(); x++)
				{
					RingStruct ringsRef = ringsVec.at(x);
					totalPoint += ringsRef._numPoints;

					pointVec.clear();
					jointIndexVec.clear();

					pointVec.reserve(ringsRef._numPoints + 32);

					for (int l=1; l<ringsRef._numPoints; l++)
					{
						pointVec.push_back(vgKernel::Vec3(ringsRef._pointsBeginAddr[(l-1)*3], 
							ringsRef._pointsBeginAddr[(l-1)*3+1],
							ringsRef._pointsBeginAddr[(l-1)*3+2]));
						jointIndexVec.push_back(pointVec.size()-1);

						tmpMap.clear();

						vgKernel::Vec2 p0(ringsRef._pointsBeginAddr[(l-1)*3 + 0],
							ringsRef._pointsBeginAddr[(l-1)*3 + 2]);

						vgKernel::Vec2 p1(ringsRef._pointsBeginAddr[l*3 + 0],
							ringsRef._pointsBeginAddr[l*3 + 2]);

						for (int j=0; j<pGeomPtrVec->size(); j++)
						{
							// 单线情况
							LineString *pOtherLineString 
								= dynamic_cast<LineString*>(pGeomPtrVec->at(j));

							if (pOtherLineString != NULL)
							{
								if (j==i || !pOtherLineString->getEnvelope3d().intersectsIn2D(pMultiLine->getEnvelope3d()))
								{
									continue;
								}

								RingStruct otherRingsRef = pOtherLineString->getRing();

								for (int k=1; k<otherRingsRef._numPoints; k++)
								{
									vgKernel::Vec2 p2(otherRingsRef._pointsBeginAddr[(k-1)*3 + 0],
										otherRingsRef._pointsBeginAddr[(k-1)*3 + 2]);

									vgKernel::Vec2 p3(otherRingsRef._pointsBeginAddr[k*3 + 0],
										otherRingsRef._pointsBeginAddr[k*3 + 2]);

									vgKernel::Vec2 result;

									if (intersection(p0, p1, p2, p3, result))
									{
										vgKernel::Vec3 enp(result.x,
											(otherRingsRef._pointsBeginAddr[(k-1)*3 + 1]+ringsRef._pointsBeginAddr[(l-1)*3 + 1]) / 2, 
											result.y);

										tmpMap.insert(make_pair(pointVec[pointVec.size()-1].distance(enp), enp));
										//TRACE("insert to map %d %d %d mapsize %d \n", j, k, k-1,tmpMap.size());
									}
								}
							}

							// multiline 情况
							MultiLine *pOtherMultiLine = dynamic_cast<MultiLine*>(pGeomPtrVec->at(j));
							if (pOtherMultiLine != NULL)
							{
								if (j==i || !pOtherMultiLine->getEnvelope3d().intersectsIn2D(pMultiLine->getEnvelope3d()))
								{
									continue;
								}

								RingStructVec ringsVec = pOtherMultiLine->getRings();
								for (int l=0; l<ringsVec.size(); l++)
								{
									RingStruct otherRingsRef = ringsVec.at(l);

									for (int k=1; k<otherRingsRef._numPoints; k++)
									{
										vgKernel::Vec2 p2(otherRingsRef._pointsBeginAddr[(k-1)*3 + 0],
											otherRingsRef._pointsBeginAddr[(k-1)*3 + 2]);

										vgKernel::Vec2 p3(otherRingsRef._pointsBeginAddr[k*3 + 0],
											otherRingsRef._pointsBeginAddr[k*3 + 2]);

										vgKernel::Vec2 result;

										if (intersection(p0, p1, p2, p3, result))
										{
											vgKernel::Vec3 enp(result.x,
												(otherRingsRef._pointsBeginAddr[(k-1)*3 + 1]+ringsRef._pointsBeginAddr[(l-1)*3 + 1]) / 2, 
												result.y);

											tmpMap.insert(make_pair(pointVec[pointVec.size()-1].distance(enp), enp));
											//TRACE("insert to map %d %d %d mapsize %d \n", j, k, k-1,tmpMap.size());
										}
									}
								}
							}

						}

						map<float,vgKernel::Vec3>::iterator iter = tmpMap.begin();
						map<float,vgKernel::Vec3>::iterator iter_end = tmpMap.end();

						while (iter != iter_end)
						{
							pointVec.push_back(iter->second);
							jointIndexVec.push_back(pointVec.size()-1);

							iter ++;
						}
					}

					pointVec.push_back(vgKernel::Vec3(ringsRef._pointsBeginAddr[(ringsRef._numPoints-1)*3 + 0], 
						ringsRef._pointsBeginAddr[(ringsRef._numPoints-1)*3 + 1],
						ringsRef._pointsBeginAddr[(ringsRef._numPoints-1)*3 + 2]));
					jointIndexVec.push_back(pointVec.size()-1);

					for (int index=1; index<jointIndexVec.size(); index++)
					{
						vgKernel::Vec3 np1 = pointVec[jointIndexVec[index-1]];
						vgKernel::Vec3 np2 = pointVec[jointIndexVec[index]];

						int npIndex1 = checkExist(np1);
						if (npIndex1 == -1)
						{
							JointPointPtr jointPoint(new JointPoint(np1));

							m_jointArray.push_back(jointPoint);
							npIndex1 = m_jointArray.size() - 1;
						}

						int npIndex2 = checkExist(np2);
						if (npIndex2 == -1)
						{
							JointPointPtr jointPoint(new JointPoint(np2));

							m_jointArray.push_back(jointPoint);
							npIndex2 = m_jointArray.size() - 1;
						}

						double distance = np1.distance(np2);

						m_jointArray[npIndex1]->addRoute(JointDist(npIndex2, distance));
						m_jointArray[npIndex2]->addRoute(JointDist(npIndex1, distance));
					}
				}
			}
		}// end for 

		vgGIS3D::GisManager::getSingleton().showProcessingDlg(false);

		// 开始进行平移
		vgKernel::Mat4 mat = pLayer->getMatrix();

		for (int i=0; i<m_jointArray.size(); i++)
		{
			// TRACE("TOP : %f %f %f \n", m_jointArray[i]->getPos().x, m_jointArray[i]->getPos().y, m_jointArray[i]->getPos().z);
			
			vgKernel::Vec3 pos = vgKernel::Math::translateVec3(mat, m_jointArray[i]->getPos());
			
			m_jointArray[i]->setPos(pos);
		}

		TRACE("构造拓扑图，点数: %d \n", m_jointArray.size());
		AfxMessageBox("构建完成");

		return 0;
	}

	int OGRRouteMap::checkExist(vgKernel::Vec3 point)
	{
		for (int i=0; i<m_jointArray.size(); i++)
		{
			//if (m_jointArray[i]->getPos() == point)
			if (abs(m_jointArray[i]->getPos().x -point.x) < 1e-2 &&
				/* abs(m_jointArray[i]->getPos().y -point.y) < 1e-2 &&*/
				 abs(m_jointArray[i]->getPos().z -point.z) < 1e-2)
			{
				if (
					abs(m_jointArray[i]->getPos().y -point.y) > 1e-2 

					)
				{
					TRACE("It will rise a bug \n");
				}
				return i;
			}
		}

		return -1;
	}

	void OGRRouteMap::setStartPoint(vgKernel::Vec3 point)
	{
		double distMax = std::numeric_limits<double>::infinity();
		m_startPointIndex = -1;

		for (int i=0;i<m_jointArray.size(); i++)
		{
			if (point.distance(m_jointArray[i]->getPos()) < distMax)
			{
				distMax = point.distance(m_jointArray[i]->getPos());
				m_startPointIndex = i;
			}
		}
	}

	void OGRRouteMap::setEndPoint(vgKernel::Vec3 point)
	{
		double distMax = std::numeric_limits<double>::infinity();
		m_endPointIndex = -1;

		for (int i=0;i<m_jointArray.size(); i++)
		{
			if (point.distance(m_jointArray[i]->getPos()) < distMax)
			{
				distMax = point.distance(m_jointArray[i]->getPos());
				m_endPointIndex = i;
			}
		}
		
		programWithDijkstra();

		m_enableResultRender = true;
	}

	void OGRRouteMap::render()
	{
		if (m_enableResultRender)
		{
			if (m_startPointIndex < 0 || m_endPointIndex < 0)
			{
				return ;
			}
			glDisable(GL_TEXTURE_2D);
			glColor3f(0.f, 0.f, 1.f);	
			glPointSize(5);

			vgKernel::Vec3 sp = m_jointArray[m_startPointIndex]->getPos();
			vgKernel::Vec3 ep = m_jointArray[m_endPointIndex]->getPos();

			glBegin(GL_POINTS);
				glVertex3f(sp.x, sp.y, sp.z);
				glVertex3f(ep.x, ep.y, ep.z);
// 				for (int i=0; i<m_pointInRoad.size(); i++)
// 				{
// 					vgKernel::Vec3 p = m_jointArray[m_pointInRoad[i]]->getPos();
// 					glVertex3f(p.x, p.y, p.z);
// 				}
			glEnd();
			
			glColor3f(0.f, 0.0f, 1.f);	
#if 0
			glBegin(GL_LINES);

			for (int i=0; i<m_pointInRoad.size(); i++)
			{
				//vgKernel::Vec3 p = m_jointArray[m_pointInRoad[i]]->getPos();
				//glVertex3f(p.x, p.y+1, p.z);
				vgKernel::Vec3 pos, pos1;
				vector<vgKernel::Vec3> *pVec = m_routeArray[m_pointInRoad[i]].getPointVecPtr();
				for (int j=pVec->size()-2; j>=0; j--)
				{
					pos = pVec->at(j);
					pos1 = pVec->at(j+1);

					glVertex3f(pos.x, pos.y+1, pos.z);
					glVertex3f(pos1.x, pos1.y+1, pos1.z);
				}
			}
			glEnd();
#endif
			glLineWidth(2.0);

			glDisable(GL_DEPTH_TEST);
			glBegin(GL_LINE_STRIP);

			for (int i=0; i<m_pointInRoad.size(); i++)
			{
				vgKernel::Vec3 pos = m_jointArray[m_pointInRoad[i]]->getPos();
			
				glVertex3f(pos.x, pos.y + 2, pos.z);
			}
			glEnd();
			glEnable(GL_DEPTH_TEST);

		}
#if 0
		// For debug Render Joint Point and Route way.
		for (int i=0; i<m_routeArray.size(); i++)
		{
			vector<vgKernel::Vec3>* pointVec = m_routeArray[i].getPointVecPtr();
			glColor3f(0.f, 1.f, 1.f);
			glBegin(GL_LINE_STRIP);
			for (int j=0; j<pointVec->size(); j++)
			{
				glVertex3f( pointVec->at(j).x, pointVec->at(j).y, pointVec->at(j).z );
			}
			glEnd();
		}
#endif
#if 0
		for (int i=0; i<m_jointArray.size(); i++)
		{
			glColor3f(1.f, 0.f, 0.f);
			glPointSize(5);
			glBegin(GL_POINTS);

			glVertex3f(m_jointArray[i]->getPos().x, m_jointArray[i]->getPos().y, m_jointArray[i]->getPos().z);
			glEnd();
		}

#endif
	}


	int OGRRouteMap::saveToFile(string path)
	{
		FILE *fp = fopen(path.c_str(), "wb+");

		if (fp == NULL)
		{
			AfxMessageBox("文件打开失败");
		
			return 0;
		}

		int nameLen = m_layerName.length();

		fwrite(&nameLen, sizeof(nameLen), 1, fp);
		fwrite(m_layerName.c_str(), nameLen, 1, fp);

		int arrayLen = m_jointArray.size();	
		fwrite(&arrayLen, sizeof(arrayLen), 1, fp);
		
		TRACE("Write From File %d point \n", arrayLen);

		for (int i=0; i<m_jointArray.size(); i++)
		{
			vgKernel::Vec3 pos = m_jointArray[i]->getPos();
			fwrite(&pos.x, sizeof(pos.x), 1, fp);
			fwrite(&pos.y, sizeof(pos.y), 1, fp);
			fwrite(&pos.z, sizeof(pos.z), 1, fp);

			//TRACE("Point %f %f %f \n", pos.x, pos.y, pos.z);

			vector<JointDist> *pVec = m_jointArray[i]->getJointVecPointer();
			arrayLen = pVec->size();

			fwrite(&arrayLen, sizeof(arrayLen), 1, fp);
		
			for (int j=0; j<arrayLen; j++)
			{
				JointDist jd = (*pVec)[j];

				fwrite(&jd, sizeof(jd), 1, fp);
			}
		}

		// 写入Route Info
		int routeNum = m_routeArray.size();
		fwrite(&routeNum, sizeof(routeNum), 1, fp);

		for (int i=0;i <routeNum; i++)
		{
			RouteInfo rf = m_routeArray[i];
			
			vector<vgKernel::Vec3>* ptVecPtr = rf.getPointVecPtr();
			int vecSize = ptVecPtr->size();
			TRACE("Write Size %d \n", vecSize);

			fwrite(&vecSize, sizeof(vecSize), 1, fp);

			for (int j=0; j<vecSize; j++)
			{
				vgKernel::Vec3 pos = ptVecPtr->at(j);
				fwrite(&pos.x, sizeof(pos.x), 1, fp);
				fwrite(&pos.y, sizeof(pos.y), 1, fp);
				fwrite(&pos.z, sizeof(pos.z), 1, fp);
			}

		}	
		fclose(fp);

		AfxMessageBox("完成导出.");

		return 1;
	}

	int OGRRouteMap::readFromFile(string path)
	{
		FILE *fp = fopen(path.c_str(), "rb");

		if (fp == NULL)
		{
			AfxMessageBox("文件打开失败");

			return 0;
		}

		int nameLen;

		char buffer[512];

		fread(&nameLen, sizeof(nameLen), 1, fp);
		fread(buffer, nameLen, 1, fp);
		
		buffer[nameLen] = '\0';
		
		m_layerName = buffer;

		if (m_layerName != buffer)
		{
			AfxMessageBox("导入的拓扑文件与矢量文件不匹配");
			return 0;
		}

		int arrayLen;
		fread(&arrayLen, sizeof(arrayLen), 1, fp);
		

		for (int i=0; i<arrayLen; i++)
		{
			vgKernel::Vec3 pos;;
			fread(&pos.x, sizeof(pos.x), 1, fp);
			fread(&pos.y, sizeof(pos.y), 1, fp);
			fread(&pos.z, sizeof(pos.z), 1, fp);
			
			//TRACE("Point %f %f %f \n", pos.x, pos.y, pos.z);

			JointPointPtr jp(new JointPoint(pos));
			m_jointArray.push_back(jp);

			vector<JointDist> *pVec = m_jointArray[i]->getJointVecPointer();
			
			int jdLen;
			fread(&jdLen, sizeof(jdLen), 1, fp);
			
			for (int j=0; j<jdLen; j++)
			{
				JointDist jd;

				fread(&jd, sizeof(jd), 1, fp);
				pVec->push_back(jd);
			}
		}

		// 读入Route Info
		int routeNum;
		fread(&routeNum, sizeof(routeNum), 1, fp);

		for (int i=0;i <routeNum; i++)
		{
			RouteInfo rf;
			int vecSize;

			fread(&vecSize, sizeof(vecSize), 1, fp);

			for (int j=0; j<vecSize; j++)
			{
				vgKernel::Vec3 pos;;
				fread(&pos.x, sizeof(pos.x), 1, fp);
				fread(&pos.y, sizeof(pos.y), 1, fp);
				fread(&pos.z, sizeof(pos.z), 1, fp);
				rf.addPoint(pos);
			}
			
			m_routeArray.push_back(rf);
		}	

		fclose(fp);

		TRACE("Read From File %d point \n", m_jointArray.size());

		TRACE("Route Array Size %d \n", m_routeArray.size());
		
		for (int i=0; i<m_routeArray.size(); i++)
		{
			TRACE("\t %d point \n", m_routeArray[i].getPointVecPtr()->size() );
		}
		AfxMessageBox("完成导入.");
		
		int cnt = 0;
#if 0
		// 后期处理

		int needUpdate = true;
		while (needUpdate)
		{
			vector<JointPointPtr>::iterator iter = m_jointArray.begin();
			vector<JointPointPtr>::iterator iter_end = m_jointArray.end();

			needUpdate = false;
			int index = 0;
			while (iter != iter_end)
			{
				if ((*iter)->getJointVecPointer()->size() == 2)
				{
					TRACE("Remove index %d \n", index);
					int beginIndex = (*iter)->getJointVecPointer()->at(0).pointIndex;
					int endIndex = (*iter)->getJointVecPointer()->at(1).pointIndex;

					double dist = (*iter)->getJointVecPointer()->at(0).dist
						+ (*iter)->getJointVecPointer()->at(1).dist;

					JointDist dt;
					dt.pointIndex = endIndex;
					dt.dist = beginIndex;

					m_jointArray[beginIndex]->removeRoute(index);
					m_jointArray[beginIndex]->addRoute(dt);

					dt.pointIndex = beginIndex;
					m_jointArray[endIndex]->removeRoute(index);
					m_jointArray[endIndex]->addRoute(dt);

					m_jointArray.erase(iter);
					needUpdate = true;
					break;
				}
		
				index ++;
				iter ++;
			}
		}
#endif
// 		for (int i=0; i<m_jointArray.size(); i++)
// 		{
// // 			if (m_jointArray[i]->getJointVecPointer()->size() == 1 || m_jointArray[i]->getJointVecPointer()->size() == 2)
// // 			{
// // 				cnt ++;
// // 			}
// 			if (m_jointArray[i])
// 			{
// 			}
// 		}

		TRACE("Remain point %d \n",cnt,m_jointArray.size());

		return 1;
	}

	bool OGRRouteMap::programWithDijkstra()
	{
		//float *way = new float[][];
		
		std::multimap<double, int> m_openTable;

		if (m_startPointIndex < 0 || m_endPointIndex < 0)
		{
			AfxMessageBox("路径端点错误.");
			
			return false;
		}

		int pointCnt = m_jointArray.size();
		
		struct Rd_t
		{
			int byPassIndex;
			double dist;

			bool final;
		};

		Rd_t *pRd = new Rd_t[pointCnt];
		
		for (int i=0; i<pointCnt; i++)
		{
			pRd[i].final = false;
			double dist = m_jointArray[m_startPointIndex]->connectWith(i);
			if (dist > 0)
			{
				pRd[i].dist = dist;
				pRd[i].byPassIndex = m_startPointIndex;

				m_openTable.insert(std::make_pair(dist, i));
			}
			else
			{
				pRd[i].dist = std::numeric_limits<double>::infinity();
				pRd[i].byPassIndex = -1;
			}
		}	

		double minDist;
		int w;

		for (int i=0; i<pointCnt; i++)
		{
			minDist = std::numeric_limits<double>::infinity();
			w = -1;
			// 改进点 排序Table

			std::multimap<double, int>::iterator iter;

PICK_POINT:
			iter = m_openTable.begin();
			
			if (iter == m_openTable.end())
			{
				break;
			}
			
			w = (*iter).second;
			minDist = pRd[w].dist;
			m_openTable.erase(iter);
			if (pRd[w].final)
			{
				goto PICK_POINT;
			}

			if (w == -1)
			{
				TRACE("No way to find.");
				break;
			}
			else
			{
				TRACE("Extra way No %d - %f \n", w, minDist);
			}

			pRd[w].final = true; 
			vector<JointDist> *pVec = m_jointArray[w]->getJointVecPointer();
			for (int k=0; k<pVec->size(); k++)
			{
				if (!pRd[pVec->at(k).pointIndex].final)
				{
					double newW = pVec->at(k).dist;
					if (newW + minDist < pRd[pVec->at(k).pointIndex].dist)
					{
 						pRd[pVec->at(k).pointIndex].dist = newW + minDist;
 						pRd[pVec->at(k).pointIndex].byPassIndex = w;

						m_openTable.insert(std::make_pair(newW + minDist, pVec->at(k).pointIndex));
					}
				}
			}
		}

		for (int l=0; l<m_routeArray.size(); l++)
		{
			TRACE("%f %f %f - %f %f %f \n", 
				m_routeArray[l].getStartPoint().x, m_routeArray[l].getStartPoint().y, m_routeArray[l].getStartPoint().z,
				m_routeArray[l].getEndPoint().x, m_routeArray[l].getEndPoint().y, m_routeArray[l].getEndPoint().z);

		}

		// 路径追踪
		if (pRd[m_endPointIndex].final)
		{
			TRACE("We Found a Route. Distance : %f \n", pRd[m_endPointIndex].dist);
			
			char buffer[1024];

			sprintf(buffer, "搜索到路径. 路径总长：%.3f 米", pRd[m_endPointIndex].dist);

			::MessageBox(NULL, buffer, "路径信息", MB_OK);

			m_pointInRoad.clear();

//			int index = m_endPointIndex;
// 			while (index != m_startPointIndex)
// 			{
// 				TRACE("%d -> ", index);
// 				m_pointInRoad.push_back(index);
// 				index = pRd[index].byPassIndex;
// 			}
			
			int lastIndex = m_endPointIndex;
			int index = pRd[m_endPointIndex].byPassIndex;	

			while (lastIndex != m_startPointIndex)
			{
				m_pointInRoad.push_back(lastIndex);
				lastIndex = pRd[lastIndex].byPassIndex;
			}
			m_pointInRoad.push_back(m_startPointIndex);

#if 0 
			// 去点式路径追踪，效率较低
			while (lastIndex != m_startPointIndex)
			{
			 	// TRACE("%d -> ", index);
			 	bool find = false;
				TRACE("%f %f %f - %f %f %f \n",  
					m_jointArray[index]->getPos().x, m_jointArray[index]->getPos().y, m_jointArray[index]->getPos().z,
					m_jointArray[lastIndex]->getPos().x, m_jointArray[lastIndex]->getPos().y, m_jointArray[lastIndex]->getPos().z);

				for (int l=0; l<m_routeArray.size(); l++)
				{
					if ((m_jointArray[lastIndex]->getPos() == m_routeArray[l].getEndPoint()
						&& m_jointArray[index]->getPos() == m_routeArray[l].getStartPoint())
						|| (m_jointArray[index]->getPos() == m_routeArray[l].getEndPoint()
						&& m_jointArray[lastIndex]->getPos() == m_routeArray[l].getStartPoint())
						)
					{
						m_pointInRoad.push_back(l);
						break;
					}
				}
				
	
				lastIndex = index;
			 	index = pRd[index].byPassIndex;
			}
#endif

			// m_pointInRoad.push_back(m_startPointIndex);
		}
		else
		{
			AfxMessageBox("未找到路径");
		}

		return true;

	}

	double JointPoint::connectWith(int index) 
	{
		if (m_pJointVec == NULL)
		{
			return false;
		}

		for (int i=0; i<m_pJointVec->size(); i++)
		{
			if (m_pJointVec->at(i).pointIndex == index)
			{
				return m_pJointVec->at(i).dist;
			}
		}

		return -1;
	}

	bool JointPoint::addRoute(JointDist dst)
	{
		for (int i=0; i<m_pJointVec->size(); i++)
		{
			if (m_pJointVec->at(i).pointIndex == dst.pointIndex)
			{
				if (dst.dist < m_pJointVec->at(i).dist)
				{
					m_pJointVec->at(i).dist = dst.dist;
				}

				return true;
			}
		}

		m_pJointVec->push_back(dst);

		return true;
	}

	bool JointPoint::removeRoute(int index)
	{
		vector<JointDist>::iterator iter = m_pJointVec->begin();
		vector<JointDist>::iterator iter_end = m_pJointVec->end();

		while (iter != iter_end)
		{
			if ((*iter).pointIndex == index)
			{
				// assert( abs((*iter).dist - dst.dist) < 1e-2 );
				m_pJointVec->erase(iter);

				return true;
			}
			iter ++;
		}

		return false;
	}

}
