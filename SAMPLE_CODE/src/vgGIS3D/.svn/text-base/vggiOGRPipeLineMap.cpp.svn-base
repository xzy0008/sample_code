#include <vgStableHeaders.h>

#include <vgGIS3D/vggiOgrUtility.h>

#include <vgGis3d/vggiGisDataManager.h>
#include <vgGis3d/vggiGeometry.h>
#include <gdal/ogr_core.h>
#include <gdal/ogr_geometry.h>
#include <gdal/ogr_feature.h>
#include <vgGis3d/vggiLine.h>
#include <vgGis3d/vggiMultiLine.h>
#include <vgGis3d/vggiOGRPipeLineMap.h>
#include <vgGIS/vgGisManager.h>
#include <vgGis3d/vggiRay3d.h>
#include <vgGIS3D/vgPipeLayerAttriDlg.h>
#include <vgDatabase/vgdDatabaseManager.h>

#include <stack>
#include <limits>
#include <utility>

namespace vgGIS3D
{
	VGK_RENDERER_IMPLEMENT( OGRPipeLineMap , RENDERER_TYPE_PIPELINE_LAYER )

	OGRPipeLineMap::OGRPipeLineMap(vgKernel::Renderer *pInnerRenderer) : vgKernel::Renderer(RENDERER_TYPE_PIPELINE_LAYER)
	{
		m_pipeAnalysisEnable = false;
		m_enablePipeRender = false;
		m_enablePipeLineSection = false;
		m_decreasFlag = false;
		//_PipeListID = 0;
		//m_dRadius = 1.0;
		m_PipeLineSectionID = 0;
		m_PipeLineEditID = 0;
		m_pipeAnalysisID = 0;	

		_transX = 0.0f;
		_transY = 0.0f;
		_transZ = 0.0f;

		m_buildingLayer = NULL;
		m_player = NULL;

		//sourcePoint = 0;
		//pDlgPointAttri = NULL;

		m_uniqueID = vgKernel::UniqueIDFactory::getUniqueID();
		_dynamicBox = _staticBox = vgKernel::Box::NULL_BOX;
		_inEditMode = false;
		_inAnalysisMode = false;
		_matrix = vgKernel::Mat4::IDENTITY;

		//quadqiu= gluNewQuadric();											// 创建指向二次曲面的指针(new)
		quadyuanzhu= gluNewQuadric();									// 创建指向二次曲面的指针(new)
		yuanqiu= gluNewQuadric();
		yuanhuan = gluNewQuadric();	

		setPipeLineRadius(1.0);
	}

	OGRPipeLineMap::~OGRPipeLineMap()
	{
		if (!m_resultPolygon.empty())
		{
			for (int i = 0; i < m_resultPolygon.size(); i++)
			{				
				delete m_resultPolygon.at(i);
				m_resultPolygon.at(i) = NULL;
			}
		}
	}

	void OGRPipeLineMap::setPipeLineRadius(float Radius)
	{
		m_pipeLineRadius = Radius;
	}

	float OGRPipeLineMap::getPipeLineRadius()
	{
		return m_pipeLineRadius;
	}

	void OGRPipeLineMap::constructFromBreakShapeLayer(string layerName)
	{
		if (layerName.substr(layerName.length()-4, 4) == ".shp")
		{
			layerName = layerName.substr(0, layerName.length()-4);
		}

		m_player = GisDataManager::getSingleton().getLayerByShortName(layerName);
		if (m_player == NULL)
		{
			AfxMessageBox("图层不存在");
			return ;
		}

		GeometryPointerVec *pGeomPtrVec = m_player->getGeometries();

		TRACE("%d \n", pGeomPtrVec->size());

		for (int i=0; i<pGeomPtrVec->size(); i++)
		{
			Geometry *pGeom = pGeomPtrVec->at(i);

			LineString *pLineString 
				= dynamic_cast<LineString*>(pGeom);

			MultiLine *pMultiLine 
				= dynamic_cast<MultiLine*>(pGeom);	
			

			if (pLineString != NULL)
			{
				// AfxMessageBox("LineString");

				RingStruct ringsRef = pLineString->getRing();				

				vgKernel::Vec3 eachPos;

				for (int j = 0; j < ringsRef._numPoints; j++)
				{
					eachPos.x = ringsRef._pointsBeginAddr[3*j];
					eachPos.y = ringsRef._pointsBeginAddr[3*j + 1];
					eachPos.z = ringsRef._pointsBeginAddr[3*j + 2];

					if (findIfPointInArray(eachPos) == -1)
					{						
						JointPointPtr jointPoint(new JointPoint(eachPos));
						m_jointArray.push_back(jointPoint);
					}
				}
			}
			if (pMultiLine != NULL)
			{				
				AfxMessageBox("Unsupported MultiLine");
				return;
			}
		}

		vgGIS3D::GisManager::getSingleton().showProcessingDlg(true);
		vgGIS3D::GisManager::getSingleton().setProcessingInfo("开始处理道路拓扑...");

		for (int k = 0; k < m_jointArray.size(); k++)
		{
			vgGIS3D::GisManager::getSingleton().setProcessingProgress((int)((float)k/m_jointArray.size()*100));
			vgKernel::Vec3 posInArray = m_jointArray[k]->getPos();
			for (int i = 0; i < pGeomPtrVec->size(); i++)
			{
				Geometry *pGeom = pGeomPtrVec->at(i);

				LineString *pLineString 
					= dynamic_cast<LineString*>(pGeom);
				if (pLineString != NULL)
				{
					RingStruct rings = pLineString->getRing();
					vgKernel::Vec3 pos;
					for (int j = 0; j < rings._numPoints; j++)
					{
						pos.x = rings._pointsBeginAddr[3*j];
						pos.y = rings._pointsBeginAddr[3*j + 1];
						pos.z = rings._pointsBeginAddr[3*j + 2];

						if (pos != posInArray)
						{
							continue;
						}
						else
						{
							if (j > 0 && j < rings._numPoints -1)
							{
								vgKernel::Vec3 findPos1;
								findPos1.x = rings._pointsBeginAddr[3 * (j-1)];
								findPos1.y = rings._pointsBeginAddr[3 * (j-1) + 1];
								findPos1.z = rings._pointsBeginAddr[3 * (j-1) + 2];

								int pointIndex1 = findIfPointInArray(findPos1);
								if (pointIndex1 != -1)
								{
									double distance = findPos1.distance(posInArray);
									m_jointArray[k]->addRoute(JointDist(pointIndex1, distance)); 
								}

								vgKernel::Vec3 findPos2;
								findPos2.x = rings._pointsBeginAddr[3 * (j+1)];
								findPos2.y = rings._pointsBeginAddr[3 * (j+1) +1];
								findPos2.z = rings._pointsBeginAddr[3 * (j+1) +2];
								int pointIndex2 = findIfPointInArray(findPos2);
								if (pointIndex2 != -1)
								{
									double distance = findPos2.distance(posInArray);
									m_jointArray[k]->addRoute(JointDist(pointIndex2, distance));
								}
							}
							else if(j == 0)
							{
								vgKernel::Vec3 findPos;
								findPos.x = rings._pointsBeginAddr[3 * (j+1)];
								findPos.y = rings._pointsBeginAddr[3 * (j+1) +1];
								findPos.z = rings._pointsBeginAddr[3 * (j+1) +2];
								int pointIndex = findIfPointInArray(findPos);
								if (pointIndex != -1)
								{
									double distance = findPos.distance(posInArray);
									m_jointArray[k]->addRoute(JointDist(pointIndex, distance));
								}
							}
							else if (j == rings._numPoints - 1)
							{
								vgKernel::Vec3 findPos;
								findPos.x = rings._pointsBeginAddr[3 * (j-1)];
								findPos.y = rings._pointsBeginAddr[3 * (j-1) +1];
								findPos.z = rings._pointsBeginAddr[3 * (j-1) +2];
								int pointIndex = findIfPointInArray(findPos);
								if (pointIndex != -1)
								{
									double distance = findPos.distance(posInArray);
									m_jointArray[k]->addRoute(JointDist(pointIndex, distance));
								}
							}
							else
							{
								assert(0);
							}
						}
					}
				}
				else
				{
					assert(0);
					//这里不应该出现这种错误
				}
			}
		}
		// 开始进行平移
		vgKernel::Mat4 mat = m_player->getMatrix();

		for (int i=0; i<m_jointArray.size(); i++)
		{
			// TRACE("TOP : %f %f %f \n", m_jointArray[i]->getPos().x, m_jointArray[i]->getPos().y, m_jointArray[i]->getPos().z);

			vgKernel::Vec3 pos = vgKernel::Math::translateVec3(mat, m_jointArray[i]->getPos());

			m_jointArray[i]->setPos(pos);
		}

		vgGIS3D::GisManager::getSingleton().showProcessingDlg(false);
	}

	int  OGRPipeLineMap::findIfPointInArray(vgKernel::Vec3 point)
	{
		int index = -1;
		for (int i = 0; i < m_jointArray.size(); i++)
		{
			if (m_jointArray[i]->getPos() == point)
			{
				index = i;
				return index;
			}
			else
			{
				continue;
			}
		}
		return index;
	}

	int OGRPipeLineMap::convertShapeLayerToPipe(string layerName)
	{
		//constructFromBreakShapeLayer(layerName);      //构建邻接表，便于管线节点的无缝渲染
		//因为继承了OGRRouteMap，所以可以直接使用它的邻接表，所以将这一句注掉

		if (m_jointArray.size() == 0)
		{
			AfxMessageBox("请先构建管线拓扑网络或者导入相应的管线拓扑结构");
			return 0;
		}
		m_layerName = layerName;	

		long totalPoint = 0;

		if (layerName.substr(layerName.length()-4, 4) == ".shp")
		{
			layerName = layerName.substr(0, layerName.length()-4);
		}

		/*Layer **/m_player = GisDataManager::getSingleton().getLayerByShortName(layerName);
		
		
		if (m_player == NULL)
		{
			AfxMessageBox("图层不存在");

			return 0;
		}

		pushDataToDataBase(m_player);       //创建数据库并保存数据入库	

		GeometryPointerVec *pGeomPtrVec = m_player->getGeometries();

		TRACE("%d \n", pGeomPtrVec->size());

		for (int i=0; i<pGeomPtrVec->size(); i++)
		{

			Geometry *pGeom = pGeomPtrVec->at(i);

			LineString *pLineString 
				= dynamic_cast<LineString*>(pGeom);

			MultiLine *pMultiLine 
				= dynamic_cast<MultiLine*>(pGeom);

			int lastJointIndex = -1;

			layerMatrix = m_player->getMatrix();

			if (pLineString != NULL)
			{
				// AfxMessageBox("LineString");

				RingStruct ringsRef = pLineString->getRing();
				totalPoint += ringsRef._numPoints;

				vgKernel::Vec3 beginPos, endPos;

				beginPos.x = ringsRef._pointsBeginAddr[0];
				beginPos.y = ringsRef._pointsBeginAddr[1];
				beginPos.z = ringsRef._pointsBeginAddr[2];

				endPos.x = ringsRef._pointsBeginAddr[3*(ringsRef._numPoints-1)];
				endPos.y = ringsRef._pointsBeginAddr[3*(ringsRef._numPoints-1) + 1];
				endPos.z = ringsRef._pointsBeginAddr[3*(ringsRef._numPoints-1) + 2];

				vgKernel::Vec3 beginPosition, endPosition;
				beginPosition = vgKernel::Math::translateVec3(layerMatrix, beginPos);
				endPosition = vgKernel::Math::translateVec3(layerMatrix, endPos);

				ringsRef._beginPointID = getPointID(beginPosition);
				ringsRef._endPointID = getPointID(endPosition);

				m_pipeLineLayer.pipeLineVec.push_back(ringsRef);
				m_pipeLineLayer.count++;	

				pushGeometry(pLineString);
			}
			if (pMultiLine != NULL)
			{
				pushGeometry(pMultiLine);
				//AfxMessageBox("Unsupported MultiLine");
			}
		}		
		
		m_player->setVisible(false);
		setPipeLineVisible(true);		
		
		//下面注释部分为另一套画管线方案的控制，暂时没有使用
		//m_enablePipeLineSection = true;
		//m_lineObject.DrawPipeLine(m_pipeLineLayer);

		TRACE("构造管线拓扑，点数: %d \n",totalPoint);

//		TRACE("构造拓扑图，点数: %d \n", m_jointArray.size());
		//AfxMessageBox("构建完成");		


		return 1;
	}

	void OGRPipeLineMap::pushDataToDataBase(Layer *pLayer)
	{
		//add by KingHJ @2010-05-08   为shape图层连接数据库
		//////////////////////////////////////////////////////////////////////////
		// 连接数据库
		vgDatabase::DatabaseManager::getSingleton().CreateConnector( vgDatabase::VG_DATABASE_ACCESS );
		vgDatabase::BasedConnector *pConnector = vgDatabase::DatabaseManager::getSingleton().GetConnectorPtr();

		String exePath = vgKernel::SystemUtility::getCurrentProcessPath();

		String databasePath = _T("Data\\Database\\");
		String databaseName = _T("数据库.mdb");
		String dbPath = exePath + databasePath + databaseName; 

		pConnector->SetDataSource( dbPath );

		bool bOpenOk = vgDatabase::DatabaseManager::getSingleton().OpenDatabase();
		if ( !bOpenOk )
		{
			String msg = "打开数据库失败！";
			vgKernel::SystemUtility::showModelDialog( msg );

			return ;
		}
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		//每一个图层创建一个表
		CADODatabase* pAdoDatabase = vgDatabase::DatabaseManager::getSingleton().GetConnectorPtr()->GetCurDatabase();
		vgDatabase::BasedConnector* connectorptr = vgDatabase::DatabaseManager::getSingleton().GetConnectorPtr();
		std::vector<String>  tablelist = connectorptr->GetTablesName();

		//创建表
		bool haveTableAlready = false;

		String ColumnNameList = _T("INSERT INTO ");

		String tableCommandString = _T("Create Table ");

		tableCommandString += m_player->getName();
		ColumnNameList += m_player->getName();

		String tablename = m_player->getName();

		//transform(tablename.begin(), tablename.end(), tablename.begin(), toupper);

		for (int i =0 ;i < tablelist.size();i++ )
		{
			if (tablename==tablelist[i])
			{
				if(!vgDatabase::DatabaseManager::getSingleton().GetStatus())
				{
					haveTableAlready = true;

					//add by KingHJ @2010-05-08,发现图层对应的数据库属性表，直接使用不覆盖
					//int nStatus = ::MessageBox(NULL,
					//	"该图层对应的属性表已存在，是否覆盖？",
					//	"新建表", MB_YESNO );
					//if( IDNO == nStatus )
					//{
					//	return 0;
					//}
					//else if( IDYES == nStatus )
					//{
					//	vgDatabase::DatabaseManager::getSingleton().SetStatus(true);
					//}
				}

				//vgDatabase::DatabaseManager::getSingleton().DeleteTable(tablename);
				break;
			}
		}

		if (!haveTableAlready)
		{
			tableCommandString += _T("(");
			ColumnNameList += _T("(");

			OGRFeatureDefn  *m_poFeatureDefn = 
				m_player->getFeatureDefn();

			//==========================================================================//YXDBNAME

			tableCommandString += _T("PRIMARYID VARCHAR(100),");
			ColumnNameList += _T("PRIMARYID,");
			//==========================================================================		

			for(int  iField = 0; iField < m_poFeatureDefn->GetFieldCount(); iField++ )
			{
				OGRFieldDefn *m_poFieldDefn = m_poFeatureDefn->GetFieldDefn( iField );

				// Part 1：读取字段名称
				tableCommandString += m_poFieldDefn->GetNameRef();

				ColumnNameList += m_poFieldDefn->GetNameRef();

				tableCommandString += _T("  ");

				// Part 2：读取字段类型
				switch (m_poFieldDefn->GetType())
				{
				case OFTInteger:
					//tableCommandString += _T("FLOAT");
					tableCommandString += _T("INT");
					break;
				case OFTReal:
					tableCommandString += _T("REAL");
					break;
				case OFTString:
					tableCommandString += _T("VARCHAR");
					break;
				case OFTDate:
					tableCommandString += _T("DATE");
					break;		
				default:
					tableCommandString += _T("VARCHAR");
					break;	
				}

				if (m_poFieldDefn->GetType() != OFTReal 
					&& m_poFieldDefn->GetType() != OFTInteger
					&& m_poFieldDefn->GetType() != OFTDate)
				{
					tableCommandString += _T("(");

					// Part 3：读取字段宽度
					CString temp;
					temp.Format("%d",m_poFieldDefn->GetWidth());
					tableCommandString += temp.GetString();

					tableCommandString += _T(")");
				}

				if (iField != m_poFeatureDefn->GetFieldCount()-1)
				{
					tableCommandString+=_T(",\n");
					ColumnNameList += _T(",");
				}		
			}

			tableCommandString += _T(")");
			ColumnNameList += _T(")\nVALUES\n(");

			if (!pAdoDatabase->IsOpen())
			{
				AfxMessageBox("failed open database");
				return;
			}

			CString commandstring = tableCommandString.c_str();

			//AfxMessageBox(commandstring);		

			if (pAdoDatabase->Execute(commandstring))
			{
				//AfxMessageBox("execute success!");
			}
			else
			{
				AfxMessageBox("failed");
				return;
			}

			////////////////////////////
			//记录入库
			////////////////////////////
			String recordstring;
			int nRowNum = 0;
			std::ostringstream O;

			using namespace vgGIS3D;
			GeometryPointerVec* pGeometries = m_player->getGeometries();
			GeometryPointerVec::iterator iter = pGeometries->begin();
			GeometryPointerVec::iterator iter_end = pGeometries->end();	

			for ( ; iter != iter_end ; ++ iter )
			{
				Geometry* geo = *iter;

				OGRFeaturePtr pfeat = geo->getOGRFeaturePtr();

				recordstring.clear();
				recordstring += ColumnNameList;


				char szTempBuffer[40];
				char    szFormat[40];
				nRowNum++;
				O.str("");
				O << nRowNum;			


				//================================================================================//YXDBNAME
				recordstring += _T("'");
				recordstring += O.str();
				recordstring += _T("'");//m_geometry->getName();			
				//recordstring += _T(",");
				//================================================================================


				for (int fieldIndex = 0; fieldIndex < pfeat->GetFieldCount() ; fieldIndex++)
				{
					recordstring += _T(",");
					OGRFieldDefn *poFDefn = pfeat->GetFieldDefnRef( fieldIndex );

					OGRField*	pFieldValue = pfeat->GetRawFieldRef( fieldIndex );

					switch (poFDefn->GetType())
					{
					case OFTString:
						{
							if( pFieldValue->Set.nMarker1 == OGRUnsetMarker )
							{
								recordstring += "NULL"; 
							}
							else
							{
								recordstring += _T("'");
								recordstring += pFieldValue->String ;
								recordstring += _T("'");							
							}	

						}
						break;

					case OFTInteger:
						{
							if( pFieldValue->Set.nMarker1 == OGRUnsetMarker )
							{
								recordstring += "NULL"; 
							}
							else
							{
								snprintf( szFormat, 40, "%%%dd",
									poFDefn->GetWidth());	

								snprintf( szTempBuffer, 40,
									szFormat, pFieldValue->Integer );

								recordstring += szTempBuffer ;
							}	

						}				
						break;

					case OFTReal:
						{
							if( pFieldValue->Set.nMarker1 == OGRUnsetMarker )
							{
								recordstring += "NULL"; 
							}
							else
							{
								if( poFDefn->GetWidth() != 0 )
								{
									snprintf( szFormat, 40, "%%%d.%df",
										poFDefn->GetWidth(), poFDefn->GetPrecision() );
								}
								else
									strcpy( szFormat, "%.15g" );

								snprintf( szTempBuffer, 40,
									szFormat, pFieldValue->Real );							
								recordstring += szTempBuffer ;	

							}	

						}				
						break;


					case OFTDate:
						{
							if( pFieldValue->Set.nMarker1 == OGRUnsetMarker )
							{
								recordstring += "NULL"; 
							}
							else
							{
								snprintf( szTempBuffer, 40, "%04d-%02d月-%02d",
									pFieldValue->Date.Day,
									pFieldValue->Date.Month,
									pFieldValue->Date.Year);

								recordstring += szTempBuffer;
							}	

						}				
						break;

					default:
						recordstring += '\0';
						break;
					}//switch

				}//for

				recordstring += _T(")");

				CString commandrecord = recordstring.c_str();

				if ( pAdoDatabase->Execute(commandrecord))
				{
					//AfxMessageBox("insert record success!");
				}
				else
				{
					AfxMessageBox("insert record failed!");
					return;
				}
			}//for

			TRACE("%s", "CREATE TABLE SUCCESS!");
			//AfxMessageBox("CREATE TABLE SUCCESS!");
			///////////////////////////////////////////////////////////////////////////////////
		}


	}

	Layer *OGRPipeLineMap::getShapeLayer()
	{
		if (m_player != NULL)
		{
			return m_player;
		}
		else
		{
			assert(m_player != NULL);
			return NULL;
		}
	}

	void OGRPipeLineMap::addBuildingToAnalysis(string layerName)
	{
		if (layerName.substr(layerName.length()-4, 4) == ".shp")
		{
			layerName = layerName.substr(0, layerName.length()-4);
		}
		 
		m_buildingLayer = GisDataManager::getSingleton().getLayerByShortName(layerName);
	}

	bool OGRPipeLineMap::ifPipeLineInBreak(RingStruct m_ring)
	{
		if ((!m_blockPointsVec.empty()) || (!breakPointsVec.empty()))
		{	
			bool breakFlag = false;
			vector<int> ::iterator iter_beg = 
				find(m_blockPointsVec.begin(), m_blockPointsVec.end(), m_ring._beginPointID);
			vector<int> ::iterator iter_end = 
				find(m_blockPointsVec.begin(), m_blockPointsVec.end(), m_ring._endPointID);

			vector<int> ::iterator beg_iter = 
				find(breakPointsVec.begin(), breakPointsVec.end(), m_ring._beginPointID);
			vector<int> ::iterator end_iter = 
				find(breakPointsVec.begin(), breakPointsVec.end(), m_ring._endPointID);

			if (beg_iter != breakPointsVec.end() && end_iter != breakPointsVec.end())
			{
				breakFlag = true;
			}
			if (iter_beg != m_blockPointsVec.end() || iter_end != m_blockPointsVec.end() || breakFlag)
			{
				//testIntersectWithBuilding(m_ring);
				//glColor3f(0.0f, 0.0f, 1.0f);
				return true;
			}
			else
			{
				return false;
			}
		}
		else 
		{
			return false;
		}
	}

	void OGRPipeLineMap::testIntersectWithBuilding(RingStruct rings)
	{
		if (m_buildingLayer == NULL)
		{
			//AfxMessageBox("请为分析绑定一个建筑图层");
			return;
		}
		else
		{
			GeometryPointerVec *pGeomPtrVec = m_buildingLayer->getGeometries();

			TRACE("%d \n", pGeomPtrVec->size());
			
			OGRGeometry* pGeoLine = OGRGeometryFactory::createGeometry( wkbLineString );
			OGRLineString* pLineString = dynamic_cast<OGRLineString*>( pGeoLine );
			pLineString->setCoordinateDimension(3);

			for (int j = 0; j < rings._numPoints; j++)
			{
				vgKernel::Vec3 ptr;
				ptr.x = rings._pointsBeginAddr[3*j];
				ptr.y = rings._pointsBeginAddr[3*j + 1];
				ptr.z = rings._pointsBeginAddr[3*j + 2];

				vgKernel::Vec3  pos = vgKernel::Math::translateVec3(layerMatrix, ptr);
				pLineString->addPoint(pos.x, -pos.z, pos.y);					
			}

			if (pLineString == NULL)
			{
				assert (0);
			}

			for (int i=0; i<pGeomPtrVec->size(); i++)
			{
				Geometry *pGeom = pGeomPtrVec->at(i);

				//BuildingSolid *pBuilding
					//= dynamic_cast<BuildingSolid*>(pGeom);

				if (pGeom != NULL)
				{
					OGRFeature* ogrPtr = pGeom->getOGRFeature();
					OGRGeometry *pOgrGeo = ogrPtr->GetGeometryRef();

					if (pOgrGeo->Intersect(pLineString))
					{
						//注释掉的部分是与自动体块相交
/*						if (pBuilding != NULL)
						{
							GeometryPointerVec ::iterator iter_find = 
								       find(m_resultPolygon.begin(), m_resultPolygon.end(), pGeom);
							if (iter_find == m_resultPolygon.end())
							{
								m_resultPolygon.push_back(pGeom);
							}							
						}	*/	

						//与模型相交
						shapeModelAnalysis(pGeom, m_player);
					}
				}

			}
			delete pLineString;
			pLineString = NULL;

			//if (!m_resultPolygon.empty())
			//{
			//	renderBuildingAnalysisResult(m_resultPolygon);
			//}
		}
	}

	//--------------------------------------------------------------
	void OGRPipeLineMap::shapeModelAnalysis(Geometry *Geomertry,Layer* shapeLayer)
	{
		//得到渲染队列所有元素
		vgKernel::RendererPackage* pAllrenders = vgKernel::RendererManager::getSingleton().getAllRendererPackage();
		vgKernel::RendererPackage::iterator iter_pack = pAllrenders->begin();
		vgKernel::RendererPackage::iterator iter_pack_end = pAllrenders->end();

		//进行遍历
		for (; iter_pack != iter_pack_end; iter_pack++)
		{
			vgKernel::RendererQueue* render_queue = &iter_pack->second;

			vgKernel::RendererQueue::iterator iter = render_queue->begin();
			vgKernel::RendererQueue::iterator iter_end = render_queue->end();
			for (; iter != iter_end; iter++)
			{

				vgKernel::Renderer* ren = *iter;
				vgKernel::Box bouBox = ren->getBoundingBox();

				// 平移到原始shape坐标
				vgKernel::Mat4 mat = shapeLayer->getMatrix();
				mat.inverse();

				vgKernel::Vec3 boxCenter = vgKernel::Math::translateVec3(mat,bouBox.getCenter());

				//构造点
				OGRGeometry* pGeom = 
					OGRGeometryFactory::createGeometry( wkbPoint );
				OGRPoint* pPoint =  dynamic_cast<OGRPoint*>(pGeom);
				assert(pPoint);

				pPoint->setCoordinateDimension(2);
				pPoint->setX(boxCenter.x);
				pPoint->setY(-boxCenter.z);

				OGRFeature* ogrPtr = Geomertry->getOGRFeature();
				OGRGeometry *pOgrGeo = ogrPtr->GetGeometryRef();
				if (pOgrGeo->Intersect(pPoint))
				{
					m_resultModVec.push_back(ren);
				}

			}
		}
		return;
	}

	int OGRPipeLineMap::getPointID(vgKernel::Vec3 pos)
	{
		int res = -1;
		for (int i = 0; i < m_jointArray.size(); i++ )
		{
			if (pos == m_jointArray[i]->getPos())
			{				
				res = i;
				break;
			}
		}
		return res;
	}

	int OGRPipeLineMap::checkExist(vgKernel::Vec3 point)
	{
		return -1;
	}

	void OGRPipeLineMap::render()
	{
#if 0
		vgKernel::Vec3 ptTest1,ptTest2,ptTest3, ptTest4;
		ptTest1.x = 0.0;
		ptTest1.y = 0.0;
		ptTest1.z = 10.0;

		ptTest2.x = 10.0;
		ptTest2.y = 10.0;
		ptTest2.z = 10.0;

		ptTest3.x = 20.0;
		ptTest3.y = 20.0;
		ptTest3.z = 10.0;

		CString flag1 = "middle";
		m_lineObject.calContactVertexesNormal(ptTest1, ptTest2, 4.0);		
		m_lineObject.drawContactPipeLine(flag1, ptTest1, ptTest2, 4.0);

		CString flag2 = "front";
		m_lineObject.calContactVertexesNormal(ptTest2, ptTest3, 2.0);
		m_lineObject.drawContactPipeLine(flag2, ptTest2, ptTest3, 2.0);

		m_lineObject.drawContactPipeLine();  //用面片的方法实现管线接点处的无缝连接
#endif

		if (m_enablePipeLineSection)       //另一套画管线机制的控制
		{
			glRotatef(90.0, 1.0f, 0.0f, 0.0f);
			if (m_PipeLineSectionID == 0)
			{
				m_PipeLineSectionID = glGenLists(1);
				assert (m_PipeLineSectionID != 0);
				glNewList(m_PipeLineSectionID, GL_COMPILE);
				m_lineObject.DrawPipeSection();
				glEndList();
			}
			else 
			{
				glCallList(m_PipeLineSectionID);
			}
		}
        //上面部分是使用多边形拼接绘制管线的机制，暂时没有使用


		if (!getPipeLineVisible())
		{
			return;
		}	

		if (m_pipeLineLayer.pipeLineVec.empty())
		{
			AfxMessageBox ("没有可用的管线图层");
		}

		LightInit();
		renderSelectedPointsOnce();
		drawSelectPipeGeoBox();
		renderViewPipeLineBox();
		drawShortestPath();
		drawDecreasing(m_pipeLineRadius);
		
		_matrix._m[13] = _transY;

		//下面绘制管线		
		renderAllPipeGeo();  //绘制所有的阀门,三通和四通节点

		glPushMatrix();
		glMultMatrixf(_matrix._m);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);

		if (_selectedGeometries.empty())
		{
			glColor3f(0.0f, 1.0f, 1.0f);
			if (m_PipeLineEditID == 0)
			{
				m_PipeLineEditID = glGenLists(1);
				assert(m_PipeLineEditID != 0);

				glNewList(m_PipeLineEditID, GL_COMPILE);

				std::vector <RingStruct> ::iterator iter = m_pipeLineLayer.pipeLineVec.begin();
				std::vector <RingStruct> ::iterator iter_end = m_pipeLineLayer.pipeLineVec.end();
				for (; iter != iter_end; iter++)
				{				
					DrawEachPipeLine((*iter), m_pipeLineRadius);
				}

				renderContactPipeLine(m_pipeLineRadius);     //节点处的无缝渲染				

				glEndList();
			}

			glPushMatrix();
			glCallList(m_PipeLineEditID);
			glPopMatrix();
		}

		else
		{
			turnSelectLineToRing();

			if (m_PipeLineEditID == 0)
			{
				m_PipeLineEditID = glGenLists(1);
				assert (m_PipeLineEditID != 0);

				glNewList(m_PipeLineEditID, GL_COMPILE);

				std::vector <RingStruct> ::iterator iter = m_pipeLineLayer.pipeLineVec.begin();
				std::vector <RingStruct> ::iterator iter_end = m_pipeLineLayer.pipeLineVec.end();
				
				for (; iter != iter_end; iter++)
				{					
					std::vector<RingStruct> ::iterator selector = 
						std::find(m_selectedRing.begin(), m_selectedRing.end(), (*iter));

					if (selector == m_selectedRing.end())
					{
						glColor3f(0.0f, 1.0f, 1.0f);
						DrawEachPipeLine((*iter), m_pipeLineRadius);
					}
					else
					{
						glColor3f(1.0f, 0.0f, 0.0f);
						DrawEachPipeLine((*iter), m_pipeLineRadius);
					}
				}
			
				renderContactPipeLine(m_pipeLineRadius);     //节点处的无缝渲染				
				glEndList();
			}
			glPushMatrix();
			glCallList(m_PipeLineEditID);
			glPopMatrix();
		}

		glDisable(GL_DEPTH_TEST);
		glPopMatrix();
		glDisable(GL_LIGHTING);
	}

	void OGRPipeLineMap::turnSelectLineToRing()
	{
		GeometryPointerVec ::iterator iter = _selectedGeometries.begin();
		GeometryPointerVec ::iterator iter_end = _selectedGeometries.end();

		if (!m_selectedRing.empty())
		{
			m_selectedRing.clear();
		}
		for (; iter != iter_end; iter++)
		{
			LineString *lineString = dynamic_cast <LineString*> (*iter);

			RingStruct selectRing = lineString->getRing();
			m_selectedRing.push_back(selectRing);
		}
	}

	void OGRPipeLineMap::getPipeLineDrection(vgKernel::Vec3 ptr1, vgKernel::Vec3 ptr2)
	{
		drection.x = ptr2.x - ptr1.x;
		drection.y = ptr2.y - ptr1.y;
		drection.z = ptr2.z - ptr1.z;

		m_distance = sqrt(drection.x*drection.x + drection.z*drection.z
			+ drection.y*drection.y);

		if (drection.y == 0 && drection.z == 0)
		{
			if (drection.x > 0)
			{
				Tran_angle = 90.0;
			}
			else
			{
				Tran_angle = -90.0;
			}

			Axis[0] = 0.0;
			Axis[1] = 1.0;
			Axis[2] = 0.0;
		}
		if (drection.x == 0 && drection.z == 0)
		{
			if (drection.y > 0)
			{
				Tran_angle = -90.0;
			}
			else
			{
				Tran_angle = 90.0;
			}
			Axis[0] = 1.0;
			Axis[1] = 0.0;
			Axis[2] = 0.0;
		}
		if (drection.x == 0 && drection.y == 0)
		{
			if (drection.z > 0)
			{
				Tran_angle = 0.0;
			}
			else
			{
				Tran_angle = 180.0;
			}

		}
		if (drection.y == 0 && drection.x && drection.z)
		{
			float angle  = abs(drection.x/drection.z);
			if (drection.x > 0 && drection.z > 0)
			{
				Tran_angle = atanf(angle) / PI * 180;
			}
			if (drection.x > 0 && drection.z < 0)
			{
				Tran_angle = 180 - atanf(angle)/PI*180;
			}
			if (drection.x < 0 && drection.z > 0)
			{
				Tran_angle = -atanf(angle)/PI*180;
			}
			if (drection.x < 0 && drection.z < 0)
			{
				Tran_angle = -(180 - atanf(angle)/PI*180);
			}
			//Tran_angle = atanf(drection.x/drection.z)/3.1415926*180;
			Axis[0] = 0.0;
			Axis[1] = 1.0;
			Axis[2] = 0.0;
		}
		if (drection.x == 0 && drection.y && drection.z)
		{
			float angle  = abs(drection.y/drection.z);
			if (drection.y > 0 && drection.z > 0)
			{
				Tran_angle = - atanf(angle) / PI * 180;
			}
			if (drection.y > 0 && drection.z < 0)
			{
				Tran_angle = - (180 - atanf(angle)/PI*180);
			}
			if (drection.y < 0 && drection.z > 0)
			{
				Tran_angle = atanf(angle)/PI*180;
			}
			if (drection.y < 0 && drection.z < 0)
			{
				Tran_angle = 180 - atanf(angle)/PI*180;
			}
			//Tran_angle = -atanf(drection.y/drection.z)/3.1415926*180;
			Axis[0] = 1.0;
			Axis[1] = 0.0;
			Axis[2] = 0.0;
		}
		if (drection.z == 0 && drection.x && drection.y)
		{
			Tran_angle = -90.0;
			Axis[0] = drection.y;
			Axis[1] = -drection.x;
			Axis[2] = 0.0;
		}
		if (drection.x && drection.y && drection.z)
		{
			if (drection.z > 0)
			{
				float index = (sqrtf(drection.x*drection.x + drection.y*drection.y))/drection.z;
				Tran_angle = -atanf(index)/3.1415926*180;
				Axis[0] = drection.y;
				Axis[1] = -drection.x;
				Axis[2] = 0.0; 
			}
			if (drection.z < 0)
			{
				float index =-drection.z/(sqrtf(drection.x*drection.x + drection.y*drection.y));
				Tran_angle = -(90.0 + atanf(index)/3.1415926*180);
				Axis[0] = drection.y;
				Axis[1] = -drection.x;
				Axis[2] = 0.0;
			}
		}

	}

	void  OGRPipeLineMap::DrawEachPipeLine(RingStruct m_ring, double pipeRadius)
	{		
		glDisable( GL_TEXTURE_2D );
		

		if (m_decreasFlag)
		{
			double index = getEachMaxPress(m_ring);
			float rate = calColorRateOfPipeLine();
			glColor3f(1.0f - (maxPressure - index)*rate, 0.1f + (maxPressure - index)*rate, 0.0f);

			std::vector<RingStruct> ::iterator selector = 
				std::find(m_selectedRing.begin(), m_selectedRing.end(), (m_ring));
			if (selector != m_selectedRing.end())
			{
				glColor3f(0.0f, 0.0f, 1.0f);
			}
		}

		if (ifPipeLineInBreak(m_ring) == true)
		{
			glColor3f(0.0f, 0.0f, 1.0f);
		}

#if 1
		for (int i = m_ring._numPoints-2; i >= 0; i--)
		{
			vgKernel::Vec3 ptr1(
				m_ring._pointsBeginAddr[3*i],
				m_ring._pointsBeginAddr[3*i+1],
				m_ring._pointsBeginAddr[3*i+2]);

			vgKernel::Vec3 ptr2(
				m_ring._pointsBeginAddr[3*(i+1)],
				m_ring._pointsBeginAddr[3*(i+1)+1],
				m_ring._pointsBeginAddr[3*(i+1)+2]);

			vgKernel::Vec3 pos1 = vgKernel::Math::translateVec3(layerMatrix, ptr1);
			vgKernel::Vec3 pos2 = vgKernel::Math::translateVec3(layerMatrix, ptr2);

			getPipeLineDrection(pos1, pos2);

			glPushMatrix();
			glDisable(GL_BLEND);			
			gluQuadricDrawStyle(quadyuanzhu,GLU_FILL);
			gluQuadricNormals(quadyuanzhu,GL_FLAT);
			gluQuadricOrientation(quadyuanzhu,GLU_INSIDE);
			gluQuadricTexture(quadyuanzhu,GL_TRUE);
			glTranslatef(pos1.x, pos1.y, pos1.z);
			glRotatef(Tran_angle, Axis[0], Axis[1], Axis[2]);
			
			gluCylinder(quadyuanzhu, pipeRadius, pipeRadius, m_distance, 20, 20);
			
			glPopMatrix();
		}

		if (m_ring._numPoints > 2)
		{
			for (int i = 1; i < m_ring._numPoints - 1; i++)
			{
				vgKernel::Vec3 ptr(
					m_ring._pointsBeginAddr[3*i],
					m_ring._pointsBeginAddr[3*i+1],
					m_ring._pointsBeginAddr[3*i+2]);

				vgKernel::Vec3 pos = vgKernel::Math::translateVec3(layerMatrix, ptr);
				
				glPushMatrix();
				glDisable(GL_BLEND);				
				gluQuadricDrawStyle(yuanqiu,GLU_FILL);
				gluQuadricNormals(yuanqiu,GL_FLAT);
				gluQuadricOrientation(yuanqiu,GLU_INSIDE);
				gluQuadricTexture(yuanqiu,GL_TRUE);
				glTranslatef(pos.x, pos.y, pos.z);
				gluSphere(yuanqiu, pipeRadius, 20, 20);
				glPopMatrix();
			}
		}
#else
		for (int i = m_ring.PointArray.size() - 2; i >= 0; i--)
		{
			vgKernel::Vec3 ptr1 = m_ring.PointArray[i];
			vgKernel::Vec3 ptr2 = m_ring.PointArray[i + 1];

			getPipeLineDrection(ptr1, ptr2);

			glPushMatrix();
			glDisable(GL_BLEND);
			glColor3f(0.0f, 1.0f, 1.0f);
			glTranslatef(ptr1.x, ptr1.y, ptr1.z);
			glRotatef(Tran_angle, Axis[0], Axis[1], Axis[2]);

			//gluSphere(quadqiu, 0.5, 20, 20);
			gluCylinder(quadyuanzhu, 0.5, 0.5, m_distance, 20, 20);

			glPopMatrix();
		}

#endif

	}

	void OGRPipeLineMap::LightInit()
	{		
		GLfloat local_model_ambient[] = {0.2,0.2,0.2,1.0};
		GLfloat light0_ambient[] = {0.5,0.5,0.5,1.0};
		GLfloat light0_diffuse[] = {1.0,1.0,1.0,1.0};
		GLfloat light0_position[] = {-20.0,-20.0,10.0,1.0};

		glLightModelfv(GL_LIGHT_MODEL_AMBIENT,local_model_ambient);
		glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

		glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);

		glLightfv(GL_LIGHT0,GL_AMBIENT,light0_ambient);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,light0_diffuse);
		glLightfv(GL_LIGHT0,GL_POSITION,light0_position);

		glEnable(GL_COLOR_MATERIAL);	
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}

 	double OGRPipeLineMap::CalculateAngleBetweenTwoLines(vgKernel::Vec3 pt1, vgKernel::Vec3 pt2, vgKernel::Vec3 pt3)
 	{
 		double dCosAlfa;
 		double dN1[3],dN2[3];
 		dN1[0] = pt3.x - pt2.x; dN1[1] = pt3.y - pt2.y; dN1[2] = pt3.z - pt2.z;
 		dN2[0] = pt1.x - pt2.x; dN2[1] = pt1.y - pt2.y; dN2[2] = pt1.z - pt2.z;
 		double dS1 = sqrt(dN1[0]*dN1[0] + dN1[1]*dN1[1] +dN1[2]*dN1[2]);
 		double dS2 = sqrt(dN2[0]*dN2[0] + dN2[1]*dN2[1] +dN2[2]*dN2[2]);
 		dCosAlfa = (dN1[0]*dN2[0] + dN1[1]*dN2[1] + dN1[2]*dN2[2])/(dS1*dS2);
 		dCosAlfa = acos(dCosAlfa);
 		return dCosAlfa;
 
 	}

	void OGRPipeLineMap::renderAllPipeGeo()
	{
		if (m_pipeGeoPtrVec.size() == 0)
		{
			return;
		}
		else
		{
			assert (m_pipeGeoPtrVec.size());
			std::vector <PipeGeoPtr> ::iterator iter = m_pipeGeoPtrVec.begin();
			std::vector <PipeGeoPtr> ::iterator iter_end = m_pipeGeoPtrVec.end();

			for (iter; iter != iter_end; iter ++)
			{
				if ((*iter)->getType() == PIPEGEO_VALVES)
				{
					glPushMatrix();					 
					(*iter)->renderUsingDisplayList();
					glPopMatrix();
				}
				else if ((*iter)->getType() == PIPEGEO_TRIPLEHANDLING)
				{
					glPushMatrix();
					(*iter)->renderUsingDisplayList();
					glPopMatrix();
				}
				else if ((*iter)->getType() == PIPEGEO_FOURHANDLING)
				{
					glPushMatrix();
					(*iter)->renderUsingDisplayList();
					glPopMatrix();
				}
				else
				{
					assert(0);
				}
			}
		}
	}

	void OGRPipeLineMap::renderContactPipeLine(float pipeRadius)
	{
		assert (m_jointArray.size());		

		vector <JointPointPtr> ::iterator iter = m_jointArray.begin();
		vector <JointPointPtr> ::iterator iter_end = m_jointArray.end();	

		for (; iter != iter_end; iter++)
		{
			vector <JointDist>* jointVec = (*iter)->getJointVecPointer();

			vgKernel::Vec3 midPos = (*iter)->getPos();

			if (jointVec->size() == 3)
			{
				std::vector <vgKernel::Vec3> threeContactPVec;
				for (int i = 0; i < 3; i ++)
				{
					int index = jointVec->at(i).pointIndex;

					vgKernel::Vec3 pos = m_jointArray[index]->getPos();
					if (pos != midPos)
					{
						threeContactPVec.push_back(pos);
					}												

				}

				getPipeLineDrection(midPos, threeContactPVec[0]);
				double tran_ange1 = Tran_angle;
				vgKernel::Vec3 axis1;
				axis1.x = Axis[0];
				axis1.y = Axis[1];
				axis1.z = Axis[2];

				getPipeLineDrection(midPos, threeContactPVec[1]);
				double tran_ange2 = Tran_angle;
				vgKernel::Vec3 axis2;
				axis2.x = Axis[0];
				axis2.y = Axis[1];
				axis2.z = Axis[2];

				getPipeLineDrection(midPos, threeContactPVec[2]);
				double tran_ange3 = Tran_angle;
				vgKernel::Vec3 axis3;
				axis3.x = Axis[0];
				axis3.y = Axis[1];
				axis3.z = Axis[2];
#if 1
				PipeGeoPtr  pValvesGeo(new vgPipeValves(pipeRadius, midPos));
				m_pipeGeoPtrVec.push_back(pValvesGeo);	        //暂定每个三通画一个阀门,在此创建一个阀门的对象	

				if (!m_tranAngleVec.empty())
				{
					m_tranAngleVec.clear();
				}
				m_tranAngleVec.push_back(tran_ange1);
				m_tranAngleVec.push_back(tran_ange2);
				m_tranAngleVec.push_back(tran_ange3);

				if (!m_drecVec.empty())
				{
					m_drecVec.clear();
				}
				m_drecVec.push_back(axis1);
				m_drecVec.push_back(axis2);
				m_drecVec.push_back(axis3);

				PipeGeoPtr pTripleGeo(new vgTripleHandling(pipeRadius, midPos, m_drecVec, m_tranAngleVec));
				m_pipeGeoPtrVec.push_back(pTripleGeo);
#else

				glDisable( GL_TEXTURE_2D );	
				glEnable(GL_DEPTH_TEST);
				glPushMatrix();
				glTranslatef(midPos.x, midPos.y, midPos.z);	
				PipeGeoPtr  pValvesGeo(new vgPipeValves(pipeRadius, midPos));
				pValvesGeo->renderOnceForDisplayList();	                           //暂定每个三通画一个阀门					                                              
				glPopMatrix();
				

				glColor3f(0.0f, 0.0f, 1.0f);
				glPushMatrix();
				glTranslatef(midPos.x, midPos.y, midPos.z);				
				glRotatef(tran_ange1, axis1.x, axis1.y, axis1.z);
				gluCylinder(quadyuanzhu, 1.5*pipeRadius, 1.5*pipeRadius, 4*pipeRadius, 20, 20);

				glTranslatef(0.0f, 0.0f, 4*pipeRadius);					
				gluDisk(yuanhuan, 0.0, 1.5*pipeRadius, 20, 20);
				glPopMatrix();

				glPushMatrix();
				glTranslatef(midPos.x, midPos.y, midPos.z);
				glRotatef(tran_ange2, axis2.x, axis2.y, axis2.z);
				gluCylinder(quadyuanzhu, 1.5*pipeRadius, 1.5*pipeRadius, 4*pipeRadius, 20, 20);

				glTranslatef(0.0f, 0.0f, 4*pipeRadius);					
				gluDisk(yuanhuan, 0.0, 1.5*pipeRadius, 20, 20);
				glPopMatrix();


				glPushMatrix();
				glTranslatef(midPos.x, midPos.y, midPos.z);
				glRotatef(tran_ange3, axis2.x, axis3.y, axis3.z);
				gluCylinder(quadyuanzhu, 1.5*pipeRadius, 1.5*pipeRadius, 4*pipeRadius, 20, 20);

				glTranslatef(0.0f, 0.0f, 4*pipeRadius);					
				gluDisk(yuanhuan, 0.0, 1.5*pipeRadius, 20, 20);
				glPopMatrix();
#endif

			}

			if (jointVec->size() == 4)
			{
				std::vector <vgKernel::Vec3> fourContactPVec;
				for (int i = 0; i < 4; i ++)
				{
					int index = jointVec->at(i).pointIndex;

					vgKernel::Vec3 pos = m_jointArray[index]->getPos();
					if (pos != midPos)
					{					
						fourContactPVec.push_back(pos);
					}						
					
				}

				getPipeLineDrection(midPos, fourContactPVec[0]);
				double tran_ange1 = Tran_angle;
				vgKernel::Vec3 fourAxis1;
				fourAxis1.x = Axis[0];
				fourAxis1.y = Axis[1];
				fourAxis1.z = Axis[2];

				getPipeLineDrection(midPos, fourContactPVec[1]);
				double tran_ange2 = Tran_angle;
				vgKernel::Vec3 fourAxis2;
				fourAxis2.x = Axis[0];
				fourAxis2.y = Axis[1];
				fourAxis2.z = Axis[2];

				getPipeLineDrection(midPos, fourContactPVec[2]);
				double tran_ange3 = Tran_angle;
				vgKernel::Vec3 fourAxis3;
				fourAxis3.x = Axis[0];
				fourAxis3.y = Axis[1];
				fourAxis3.z = Axis[2];

				getPipeLineDrection(midPos, fourContactPVec[3]);
				double tran_ange4 = Tran_angle;
				vgKernel::Vec3 fourAxis4;
				fourAxis4.x = Axis[0];
				fourAxis4.y = Axis[1];
				fourAxis4.z = Axis[2];

#if 1
				if (!m_tranAngleVec.empty())
				{
					m_tranAngleVec.clear();
				}
				m_tranAngleVec.push_back(tran_ange1);
				m_tranAngleVec.push_back(tran_ange2);
				m_tranAngleVec.push_back(tran_ange3);
				m_tranAngleVec.push_back(tran_ange4);

				if (!m_drecVec.empty())
				{
					m_drecVec.clear();
				}
				m_drecVec.push_back(fourAxis1);
				m_drecVec.push_back(fourAxis2);
				m_drecVec.push_back(fourAxis3);
				m_drecVec.push_back(fourAxis4);

				PipeGeoPtr pFourGeo(new vgFourHandling(pipeRadius, midPos, m_drecVec, m_tranAngleVec));
				m_pipeGeoPtrVec.push_back(pFourGeo);
#else
				
				glColor3f(1.0f, 1.0f, 0.0f);
				glPushMatrix();
				glTranslatef(midPos.x, midPos.y, midPos.z);
				glRotatef(tran_ange1, fourAxis1.x, fourAxis1.y, fourAxis1.z);
				gluCylinder(quadyuanzhu, 1.5*pipeRadius, 1.5*pipeRadius, 4*pipeRadius, 20, 20);

				glTranslatef(0.0f, 0.0f, 4*pipeRadius);				
				gluDisk(yuanhuan, 0.0, 1.5*pipeRadius, 20, 20);
				glPopMatrix();

				glPushMatrix();
				glTranslatef(midPos.x, midPos.y, midPos.z);
				glRotatef(tran_ange2, fourAxis2.x, fourAxis2.y, fourAxis2.z);
				gluCylinder(quadyuanzhu, 1.5*pipeRadius, 1.5*pipeRadius, 4*pipeRadius, 20, 20);

				glTranslatef(0.0f, 0.0f, 4*pipeRadius);				
				gluDisk(yuanhuan, 0.0, 1.5*pipeRadius, 20, 20);
				glPopMatrix();

				glPushMatrix();
				glTranslatef(midPos.x, midPos.y, midPos.z);
				glRotatef(tran_ange3, fourAxis3.x, fourAxis3.y, fourAxis3.z);
				gluCylinder(quadyuanzhu, 1.5*pipeRadius, 1.5*pipeRadius, 4*pipeRadius, 20, 20);

				glTranslatef(0.0f, 0.0f, 4*pipeRadius);				
				gluDisk(yuanhuan, 0.0, 1.5*pipeRadius, 20, 20);
				glPopMatrix();

				glPushMatrix();
				glTranslatef(midPos.x, midPos.y, midPos.z);
				glRotatef(tran_ange4, fourAxis4.x, fourAxis4.y, fourAxis4.z);
				gluCylinder(quadyuanzhu, 1.5*pipeRadius, 1.5*pipeRadius, 4*pipeRadius, 20, 20);

				glTranslatef(0.0f, 0.0f, 4*pipeRadius);				
				gluDisk(yuanhuan, 0.0, 1.5*pipeRadius, 20, 20);
				glPopMatrix();
#endif
			}

		}

	}

	vgKernel::Box OGRPipeLineMap::getPipeLineBox(LineString* linString)
	{
		vgKernel::Box eachBox = linString->getPipeLineEnvelope3f(m_pipeLineRadius);
		vgKernel::Vec3 maxPos = eachBox.getMaximum();
		vgKernel::Vec3 minPos = eachBox.getMinimum();


		vgKernel::Vec3 maxPosition = vgKernel::Math::translateVec3(layerMatrix, maxPos);
		vgKernel::Vec3 minPosition = vgKernel::Math::translateVec3(layerMatrix, minPos);

		eachBox.setMaximum(maxPosition);
		eachBox.setMinimum(minPosition);

		return eachBox;

	}

	void OGRPipeLineMap::pushGeometry( Geometry* geo )
	{
		LineString *pLineString 
			= dynamic_cast<LineString*>(geo);

		//------------------------------------------
		// 计算包围盒信息
		//------------------------------------------
		if (pLineString != NULL)
		{
			_geometries.push_back( geo );

			_numOfPoints += geo->getNumOfPoints();

			//vgKernel::Box eachBox = pLineString->getPipeLineEnvelope3f(m_pipeLineRadius);
			//vgKernel::Vec3 maxPos = eachBox.getMaximum();
			//vgKernel::Vec3 minPos = eachBox.getMinimum();
			//

			//vgKernel::Vec3 maxPosition = vgKernel::Math::translateVec3(layerMatrix, maxPos);
			//vgKernel::Vec3 minPosition = vgKernel::Math::translateVec3(layerMatrix, minPos);

			//eachBox.setMaximum(maxPosition);
			//eachBox.setMinimum(minPosition);
			vgKernel::Box eachBox = getPipeLineBox(pLineString);
			_staticBox.merge(eachBox);

			//_staticBox.merge( pLineString->getPipeLineEnvelope3f(m_pipeLineRadius) );
			
			_dynamicBox = _staticBox;
		}
		else
		{
			AfxMessageBox ("管线不支持除了单线之外的格式");
			return;
		}


		return;
	}

	void OGRPipeLineMap::clearSelectedGeometry()
	{
		_selectedGeometries.clear();
	}

	void OGRPipeLineMap::clearSelectedPoint()
	{
		m_selectPointVec.clear();

		if (!m_pipeGeoPtrVec.empty())
		{
			for (int i = 0; i < m_pipeGeoPtrVec.size(); i++)
			{
				m_pipeGeoPtrVec[i]->revertSolidColor();
			}
		}
	}

	void OGRPipeLineMap::addSelectedGeometry( Geometry* add_geo )
	{
		if (m_PipeLineEditID != 0)
		{
			glPushMatrix();			
			glDeleteLists(m_PipeLineEditID, 1);
			m_PipeLineEditID = 0;
			glPopMatrix();
		}

		GeometryPointerVec::iterator findres = 
			std::find( _selectedGeometries.begin() , _selectedGeometries.end() , add_geo );

		if ( findres == _selectedGeometries.end() )
		{
			LineString *add_pipeLine = dynamic_cast<LineString*> (add_geo);
			
			if (add_pipeLine != NULL)
			{
				RingStruct rings = add_pipeLine->getRing();
				vector<RingStruct> ::iterator iter_find= 
					find(m_pipeLineLayer.pipeLineVec.begin(), m_pipeLineLayer.pipeLineVec.end(), rings);
				if (iter_find != m_pipeLineLayer.pipeLineVec.end())
				{
					add_pipeLine->_ring = (*iter_find);
				}			

				_selectedGeometries.push_back( add_pipeLine );
			}			
		}

		return;
	}

	Geometry* OGRPipeLineMap::testIntersectWithGeometry( const RayLine3d& rayline )
	{
		//------------------------------------------
		// 首先判断是否和layer的box相交
		//------------------------------------------
		std::pair<bool, float> result = vgKernel::Math::intersects( 
			rayline.getRay3d().getRayFloat(), _dynamicBox );

		if ( result.first == false )
		{
			return NULL;
		}


		//------------------------------------------
		// 计算转换的ray
		//------------------------------------------
		//Ray3d translatedRay = ray;
		RayLine3d transRayline;

		vgKernel::Mat4 mat = _matrix;
		mat.inverse();

		vgKernel::Vec3 p1 = vgKernel::Math::translateVec3( mat, rayline._pointStart.getVec3Float() );
		transRayline._pointStart = Vec3d( p1 );

		vgKernel::Vec3 p2 = vgKernel::Math::translateVec3( mat, rayline._pointEnd.getVec3Float() );
		transRayline._pointEnd = Vec3d( p2 );
#if 0
		//------------------------------------------
		// 然后遍历每一个geo, 判断是否相交
		//------------------------------------------
		GeometryPointerVec::iterator iter = _geometries.begin();
		GeometryPointerVec::iterator iter_end = _geometries.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			Geometry* geo = *iter;

			bool testok = geo->testIntersect( transRayline );

			if ( testok == true )
			{
				return geo;
			}
		}
#else
		//------------------------------------------
		// 然后遍历每一个geo, 判断是否相交
		//------------------------------------------
		GeometryPointerVec::iterator iter = _geometries.begin();
		GeometryPointerVec::iterator iter_end = _geometries.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			Geometry* geo = *iter;

			LineString *pLineString 
				= dynamic_cast<LineString*>(geo);

			if (pLineString == NULL)
			{
				return NULL;
			}
			else
			{
				//vgKernel::Box eachBox = pLineString->getPipeLineEnvelope3f(m_pipeLineRadius);
				vgKernel::Box eachBox = getPipeLineBox(pLineString);

				std::pair<bool, float> result = vgKernel::Math::intersects( 
					rayline.getRay3d().getRayFloat(), eachBox );

				if (result.first != false)
				{
					return geo;
				}

			}
		}

#endif

		return NULL;
	}

	void OGRPipeLineMap::setMatrix( const vgKernel::Mat4& matrix )
	{
		_matrix = matrix;
		_dynamicBox = _staticBox;
		_dynamicBox.matrixTranslation(_matrix);

		_transX = 	_matrix._m[12];
		_transY = _matrix._m[13];
		_transZ = _matrix._m[14];
	}

	void OGRPipeLineMap::addSelectPoints(PointStruct point)
	{
		std::vector<PointStruct> ::iterator findPoint= 
			std::find(m_selectPointVec.begin(), m_selectPointVec.end(), point);

		if (findPoint == m_selectPointVec.end()) 
		{
			for (int i = 0; i < m_jointArray.size(); i++)
			{
				if (m_jointArray[i]->getPos() == point.pos)
				{
					point.ID = i;
					point.pressValue = m_jointArray[i]->m_pressValue;
					break;
				}
			}

			m_selectPointVec.push_back(point);
		}		
	}

	void OGRPipeLineMap::drawPipeLineAnalysis()
	{
		for (int i = 0; i < m_jointArray.size(); i++)
		{
			vector<int> ::iterator iter = find(visitedVec.begin(), visitedVec.end(), i);
			if (iter == visitedVec.end())
			{
				m_jointArray.at(i)->m_pressValue = 1e-10;
				m_blockPointsVec.push_back(i);
			}
		}

		if (m_pipeAnalysisID != 0)
		{
			glPushMatrix();			
			glDeleteLists(m_pipeAnalysisID, 1);
			m_pipeAnalysisID = 0;
			glPopMatrix();
		}

		if (!m_resultModVec.empty())
		{
			unrenderModelAnalysisResult();
			m_resultModVec.clear();
		}

		std::vector <RingStruct> ::iterator iter = m_pipeLineLayer.pipeLineVec.begin();
		std::vector <RingStruct> ::iterator iter_end = m_pipeLineLayer.pipeLineVec.end();
		for (; iter != iter_end; iter++)
		{				
			bool inAnalysis = ifPipeLineInBreak(*iter);
			if (inAnalysis == true)
			{
				testIntersectWithBuilding(*iter);
				//shapeModelAnalysis(*iter, m_player);
			}
		}

		if (!m_resultModVec.empty())
		{
			//renderBuildingAnalysisResult(m_resultPolygon);
			renderModelAnalysisResult(m_resultModVec);
		}
	}

	//--------------------------------------------------------------
	void OGRPipeLineMap::renderModelAnalysisResult( vgKernel::RendererQueue& renderResult )
	{
		//与模型相交结果的渲染
		vgKernel::RendererQueue::iterator iter = renderResult.begin();
		vgKernel::RendererQueue::iterator iter_end = renderResult.end();
		for (; iter != iter_end; ++iter)
		{
			if ((*iter)->getType()==5000||(*iter)->getType()==5010)
			{
				vgKernel::ColorableObject* colorobj 
					= dynamic_cast<vgKernel::ColorableObject*>(*iter);

				RendererColor rendererColor;
				rendererColor.pRenderer = *iter;
				rendererColor.color = colorobj->getRgbaQuad();
				rendererColor.colorState = colorobj->isColorable();
				rendererColors.push_back(rendererColor);//备份原始颜色，以便恢复

				vgKernel::RgbaQuad color(0,255,255,255);
				colorobj->setColorableValue(color);
				colorobj->setColorable(true);
			}
		}
	}
	//--------------------------------------------------------------
	void OGRPipeLineMap::unrenderModelAnalysisResult()
	{
		//与模型相交的渲染结果的返回
		RenderColorVec::iterator iter = rendererColors.begin();
		RenderColorVec::iterator iter_end = rendererColors.end();
		for (; iter != iter_end; ++iter)
		{
			Renderer* pRender = (*iter).pRenderer;
			RgbaQuad oldColor = (*iter).color;
			bool     oldState = (*iter).colorState;

			vgKernel::ColorableObject* colorobj 
				= dynamic_cast<vgKernel::ColorableObject*>(pRender);

			colorobj->setColorableValue(oldColor);
			colorobj->setColorable(oldState);
		}
	}

	void OGRPipeLineMap::drawSelectPipeGeoBox()
	{
		if (m_selectPipeGeoVec.empty())
		{
			return;
		}
		else
		{	
			PipeGeoPtrVector::iterator iter = m_selectPipeGeoVec.begin();
			PipeGeoPtrVector::iterator iter_end = m_selectPipeGeoVec.end();

			for (; iter != iter_end; iter++)
			{
				//vgKernel::Box pipeGeoBox = (*iter)->getEnvelope3f();
				//pipeGeoBox.render();			

				
				vgKernel::Vec3 pos = (*iter)->getCenterPos();			    

				glPushMatrix();	
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_BLEND);				
				glTranslatef(pos.x, pos.y, pos.z);

				glBegin(GL_TRIANGLES);
				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex3f(-4.0f, 8.0f, 0.0f);
				glVertex3f(0.0f, 5.0f, 0.0f);
				glVertex3f(0.0f, 11.0f, 0.0f);
				glEnd();

				glBegin(GL_TRIANGLES);
				glColor3f(0.0f, 1.0f, 0.0f);
				glVertex3f(4.0f, 8.0f, 0.0f);
				glVertex3f(0.0f, 5.0f, 0.0f);
				glVertex3f(0.0f, 11.0f, 0.0f);
				glEnd();

				glBegin(GL_TRIANGLES);
				glColor3f(0.0f, 0.0f, 1.0f);
				glVertex3f(0.0f, 8.0f, 4.0f);
				glVertex3f(0.0f, 5.0f, 0.0f);
				glVertex3f(0.0f, 11.0f, 0.0f);
				glEnd();

				glBegin(GL_TRIANGLES);
				glColor3f(1.0f, 1.0f, 0.0f);
				glVertex3f(0.0f, 8.0f, -4.0f);
				glVertex3f(0.0f, 5.0f, 0.0f);
				glVertex3f(0.0f, 11.0f, 0.0f);
				glEnd();

				glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
				glColor3f(0.0f, 0.8f, 0.6f);
				gluCylinder(quadyuanzhu, 0.2, 0.2, 11.0, 10, 10);	

				glPopMatrix();
			}
		}		
	}

	void OGRPipeLineMap::renderSelectedPointsOnce()
	{
		glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		glColor3f(0.0f, 0.0f, 1.0f);
		if (!m_upstreamPtVec.empty())
		{
			for (int i = 0; i < m_upstreamPtVec.size(); i++)
			{
				int index = m_upstreamPtVec.at(i);
				vgKernel::Vec3 position = m_jointArray.at(index)->getPos();
				for (int i = 0; i < m_pipeGeoPtrVec.size(); i++)
				{
					if ((m_pipeGeoPtrVec[i]->getType() == PIPEGEO_VALVES) && (position == m_pipeGeoPtrVec[i]->getCenterPos()))
					{
						glPushMatrix();
						m_pipeGeoPtrVec[i]->setSolidColor(true);						
						glPopMatrix();
					}
					else
					{
						continue;
					}
				}
				//glVertex3f(position.x, position.y, position.z);
			}
		}		
		glPopMatrix();

		if (m_selectPointVec.empty())
		{
			return;
		}

		std::vector <PointStruct> ::iterator iter = m_selectPointVec.begin();
		std::vector <PointStruct> ::iterator iter_end = m_selectPointVec.end();

		glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		
		for (; iter != iter_end; iter++)
		{
			if (renderSelectPipeGeo((*iter)))
			{
				continue;
			}
/*			else
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				glPointSize(15.0f);	
				glBegin(GL_POINTS);
				glVertex3f((*iter).pos.x, (*iter).pos.y ,(*iter).pos.z);
				glEnd();
			}	*/		
		}		
		glPopMatrix();

		glEnable(GL_TEXTURE_2D);
	}

	bool OGRPipeLineMap::renderSelectPipeGeo(PointStruct potStruct)
	{
		bool result = false;
		for (int i = 0; i < m_pipeGeoPtrVec.size(); i++)
		{
			vgKernel::Vec3 pos = m_pipeGeoPtrVec[i]->getCenterPos();
			if ((pos == potStruct.pos) && ( m_pipeGeoPtrVec[i]->getType() != PIPEGEO_VALVES))
			{
				m_pipeGeoPtrVec[i]->setSolidColor(true);				
				result = true;				
			}
		}
		return result;		
	}

	void OGRPipeLineMap::calculatePressure(int index, vector<int> &visitedVec, float rate, double preValue)
	{	
#if 0
		vector <JointDist>* jointVec = m_jointArray.at(index)->getJointVecPointer();
		for (int i = 0; i< jointVec->size(); i++)
		{
			int tempIndex = jointVec->at(i).pointIndex;
			vector <int> ::iterator iter = find(visitedVec.begin(), visitedVec.end(), tempIndex);
			if (iter == visitedVec.end())
			{
				m_jointArray.at(tempIndex)->m_pressValue = 
					m_jointArray.at(index)->m_pressValue - rate * jointVec->at(i).dist;

				visitedVec.push_back(tempIndex);
				calculatePressure(tempIndex, visitedVec, rate);
			}

			if (visitedVec.size() == m_jointArray.size())
			{
				return;
			}
		}
		//上面部分是深度遍历，在这使用的应该是下面的广度遍历

#else
		vector<int> tempVec;
		vector<int> preVisitedVec;
		if (!visitedVec.empty())
		{
			vector<int> ::iterator iter = visitedVec.begin();
			vector<int> ::iterator iter_end = visitedVec.end();
			preVisitedVec.assign(iter, iter_end);
			visitedVec.clear();
		}

		visitedVec.push_back(index);
		tempVec.push_back(index);
		while (!tempVec.empty())
		{
			int temp = tempVec.at(0);
			vector<int> ::iterator iter= tempVec.begin();
			tempVec.erase(iter);

			vector <JointDist>* jointVec = m_jointArray.at(temp)->getJointVecPointer();

			for (int i = 0; i< jointVec->size(); i++)
			{
				int tempIndex = jointVec->at(i).pointIndex;				

				vector <int> ::iterator iter = find(visitedVec.begin(), visitedVec.end(), tempIndex);
				if (iter == visitedVec.end())
				{
					if (preVisitedVec.empty())
					{
						m_jointArray.at(tempIndex)->m_pressValue = 
							m_jointArray.at(temp)->m_pressValue - rate * jointVec->at(i).dist;

						visitedVec.push_back(tempIndex);
						tempVec.push_back(tempIndex);
					}
					else
					{
						bool nature = getDecreasDrection(temp, tempIndex, preVisitedVec);
						if (nature == true)
						{
							m_jointArray.at(tempIndex)->m_pressValue += 
								m_jointArray.at(temp)->m_pressValue - rate * jointVec->at(i).dist;
						}
						else
						{
							m_jointArray.at(tempIndex)->m_pressValue -= 
								m_jointArray.at(temp)->m_pressValue - rate * jointVec->at(i).dist;
						}

						visitedVec.push_back(tempIndex);
						tempVec.push_back(tempIndex);
					}
				}
			}			
		}
		m_jointArray.at(index)->m_pressValue += preValue;  //反算结束后再在原来基础上将新压力源的压力值累加

		//createDigraphAdjList();
#endif
	}

	void OGRPipeLineMap::createDigraphAdjList()
	{
		//设置压力源之后建立有向图邻接表
		vector<JointPointPtr> ::iterator iter = m_jointArray.begin();
		vector<JointPointPtr> ::iterator iter_end = m_jointArray.end();
		m_digraphAdjList.assign(iter, iter_end);

		for (int i = 0; i < m_digraphAdjList.size(); i++)
		{
			vector<JointDist> *adjVec = m_digraphAdjList[i]->m_pJointVec;

			vector<JointDist> ::iterator iter = adjVec->begin();	
			while (iter != adjVec->end())
			{
				int index = (*iter).pointIndex;
				if (m_digraphAdjList[index]->m_pressValue > m_digraphAdjList[i]->m_pressValue)
				{
					iter = adjVec->erase(iter);
				}
				else
				{
					++iter;
				}
			}
		}
	}

	bool OGRPipeLineMap::getDecreasDrection(int root, int leaves, vector<int> preVisitedVec)
	{
		int pre = -1;
		int follow = -1;
		for (int i = 0; i < preVisitedVec.size(); i++)
		{
			if (preVisitedVec.at(i) == root)
			{
				pre = i;
				break;
			}
		}

		for (int j = 0; j < preVisitedVec.size(); j++)
		{
			if (preVisitedVec.at(j) == leaves)
			{
				follow = j;
				break;
			}
		}

		if (pre < follow)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void OGRPipeLineMap::calEachPointPress(int id, double preValue)
	{
		float rate = 0.5;		
		assert (m_jointArray.size());
		m_sourceVec.push_back(id);

	    calculatePressure(id, visitedVec, rate, preValue);
		m_decreasFlag = true;
		calColorRateOfPipeLine();

		if (m_pipeAnalysisID != 0)
		{
			glPushMatrix();			
			glDeleteLists(m_pipeAnalysisID, 1);
			m_pipeAnalysisID = 0;
			glPopMatrix();
		}
	}

	float OGRPipeLineMap::calColorRateOfPipeLine()
	{
		//double maxPressure, minPressure;
		int firstBeg = m_pipeLineLayer.pipeLineVec.at(0)._beginPointID;
		int firstEnd = m_pipeLineLayer.pipeLineVec.at(0)._endPointID;
		if (m_jointArray.at(firstBeg)->m_pressValue > m_jointArray.at(firstEnd)->m_pressValue)
		{
			 maxPressure = m_jointArray.at(firstBeg)->m_pressValue;
			 minPressure = m_jointArray.at(firstEnd)->m_pressValue;
		}
		else
		{
			maxPressure = m_jointArray.at(firstEnd)->m_pressValue;
			minPressure = m_jointArray.at(firstBeg)->m_pressValue;
		}
		  
		std::vector <RingStruct> ::iterator iter = m_pipeLineLayer.pipeLineVec.begin();
		std::vector <RingStruct> ::iterator iter_end = m_pipeLineLayer.pipeLineVec.end();
		for (; iter != iter_end; iter++)
		{
			int beg = (*iter)._beginPointID;
			int end = (*iter)._endPointID;

			if (m_jointArray.at(beg)->m_pressValue > maxPressure)
			{
				maxPressure = m_jointArray.at(beg)->m_pressValue;
			}
			else if (m_jointArray.at(beg)->m_pressValue < minPressure)
			{
				minPressure = m_jointArray.at(beg)->m_pressValue;
			}

			if (m_jointArray.at(end)->m_pressValue > maxPressure)
			{
				maxPressure = m_jointArray.at(end)->m_pressValue;
			}
			else if (m_jointArray.at(end)->m_pressValue < minPressure)
			{
				minPressure = m_jointArray.at(end)->m_pressValue;
			}
		}

		float decreasRate = (1.0f - 0.1f)/(maxPressure - minPressure);
		return decreasRate;


	}

	double OGRPipeLineMap::getEachMaxPress(RingStruct m_ring)
	{
		int beg = m_ring._beginPointID;
		int end = m_ring._endPointID;

		if (m_jointArray.at(beg)->m_pressValue > m_jointArray.at(end)->m_pressValue)
		{
			return m_jointArray.at(beg)->m_pressValue;
		}
		else
		{
			return m_jointArray.at(end)->m_pressValue;
		}
	}

	void OGRPipeLineMap::drawDecreasing(float pipeRadius)
	{
		if (m_decreasFlag)
		{
			setPipeLineVisible(false);

			renderAllPipeGeo();  //绘制所有的阀门、三通和四通节点

			glPushMatrix();
			glDisable(GL_TEXTURE_2D);
			if (m_pipeAnalysisID == 0)
			{
				m_pipeAnalysisID = glGenLists(1);
				assert(m_pipeAnalysisID);
				glNewList(m_pipeAnalysisID, GL_COMPILE);

				std::vector <RingStruct> ::iterator iter = m_pipeLineLayer.pipeLineVec.begin();
				std::vector <RingStruct> ::iterator iter_end = m_pipeLineLayer.pipeLineVec.end();
				for (; iter != iter_end; iter++)
				{				
					DrawEachPipeLine((*iter), pipeRadius);
				}
				renderContactPipeLine(m_pipeLineRadius);     //节点处的无缝渲染
				
				glEndList();
			}
			else
			{
				glPushMatrix();
				glCallList(m_pipeAnalysisID);
				glPopMatrix();
			}
			
			glEnable(GL_TEXTURE_2D);
			glPopMatrix();
		}
		else
		{
			return;
		}	
	}

	void OGRPipeLineMap::reCalPointPressure(vector<int> breakVec)
	{		
		if (m_sourceVec.empty())
		{
			AfxMessageBox("请先为管线网络设置压力源");
			return;
		}

		int index = m_sourceVec.at(0);
		float rate = 0.5;
		vector<int> tempVec;
		int pointId = breakVec.at(0);
		breakPointsVec.push_back(pointId);

		if (!visitedVec.empty())
		{
			visitedVec.clear();
		}
		visitedVec.push_back(index);
		tempVec.push_back(index);
		while (!tempVec.empty())
		{
			int temp = tempVec.at(0);
			vector<int> ::iterator iter= tempVec.begin();
			tempVec.erase(iter);

			vector <JointDist>* jointVec = m_jointArray.at(temp)->getJointVecPointer();

			for (int i = 0; i< jointVec->size(); i++)
			{
				int tempIndex = jointVec->at(i).pointIndex;
				vector <int> ::iterator iter = find(visitedVec.begin(), visitedVec.end(), tempIndex);
				if (iter == visitedVec.end())
				{
					m_jointArray.at(tempIndex)->m_pressValue = 
						m_jointArray.at(temp)->m_pressValue - rate * jointVec->at(i).dist;

					visitedVec.push_back(tempIndex);

					vector <int> ::iterator iter_find = 
						               find(breakVec.begin(), breakVec.end(), tempIndex);
					if (iter_find == breakVec.end())
					{
						tempVec.push_back(tempIndex);
					}						
				}
			}
		}

		drawPipeLineAnalysis();
	}

	void OGRPipeLineMap::callUpstreamPoint(int begID, int endID)
	{
		if (!m_upstreamPtVec.empty())
		{
			m_upstreamPtVec.clear();
		}

		if (!m_selectPointVec.empty())
		{
			m_selectPointVec.clear();       //首先清空在选择状态下的点，以停止它们的渲染
		}

		if (!_selectedGeometries.empty())
		{
			turnSelectLineToRing();
		}

 		if (m_pipeAnalysisID != 0)
 		{
 			glPushMatrix();
 			glDeleteLists(m_pipeAnalysisID, 1);
 			m_pipeAnalysisID = 0; 
 			glPopMatrix();
 		}

		if (m_sourceVec.empty())
		{
			AfxMessageBox("请先为管线网络设置至少一个压力源");
			return;
		}

		if (m_jointArray.at(begID)->m_pressValue > m_jointArray.at(endID)->m_pressValue)
		{
			findUpstreamPoint(begID, endID);			
		}
		else
		{
			findUpstreamPoint(endID, begID);
		}
		//m_decreasFlag = false;
		//setPipeLineVisible(true);
		TRACE ("upstream point size %d \n", m_upstreamPtVec.size());
	}

	void OGRPipeLineMap::findUpstreamPoint(int upPoint, int downPoint)
	{
		vector <JointDist>* jointVec = m_jointArray.at(upPoint)->getJointVecPointer();
		if (jointVec->size() == 3)
		{
			m_upstreamPtVec.push_back(upPoint);
			return;
		}
		else
		{
			for (int i = 0; i < jointVec->size(); i++)
			{
				int tempIndex = jointVec->at(i).pointIndex;
				if (tempIndex == downPoint)
				{
					continue;
				}
				else if (m_jointArray.at(tempIndex)->m_pressValue > m_jointArray.at(upPoint)->m_pressValue)
				{
					findUpstreamPoint(tempIndex, upPoint);
				}
			}
		}
	}
	//--------------------------------------------------------------
	void OGRPipeLineMap::renderBuildingAnalysisResult(GeometryPointerVec& geoVec)
	{
		//与自动体块相交结果渲染
		GeometryPointerVec::iterator iter = geoVec.begin();
		GeometryPointerVec::iterator iter_end = geoVec.end();
		for (; iter!=iter_end; ++iter)
		{
			Geometry* pGeo = *iter;

			GeometryColor geocolor;
			geocolor.pGeometry = pGeo;
			geocolor.fillColor = pGeo->getDrawingDescriptor()->getFillColorRef();
			geocolor.penColor  = pGeo->getDrawingDescriptor()->getPenColorRef();
			geoColors.push_back(geocolor);//备份原始颜色，以便恢复			

			pGeo->getDrawingDescriptor()->setFillColor(RGB(0,255,255));
			pGeo->getDrawingDescriptor()->setPenColor(RGB(0,255,255));

			if (pGeo->getType()==GEOMTRY_BUILDING_SOLID)
			{
				BuildingSolid *pB
					= dynamic_cast<BuildingSolid*>(pGeo);

				pB->setSolidColor(vgKernel::ColorVal(1.0f,1.0f,0.0f,1.0f));
				//pB->renderOnceForDisplayList();
			}
		}

		m_buildingLayer->invalidateRendering();
	}

	//--------------------------------------------------------------
	void OGRPipeLineMap::unrenderBuildingAnalysisResult()
	{
		//与自动体块相交结果的返回
		GeomColorVec::iterator iter = geoColors.begin();
		GeomColorVec::iterator iter_end = geoColors.end();
		for (; iter!=iter_end; ++iter)
		{
			Geometry* pGeo = (*iter).pGeometry;

			pGeo->getDrawingDescriptor()->setFillColor((*iter).fillColor);
			pGeo->getDrawingDescriptor()->setPenColor((*iter).penColor);

			if (pGeo->getType() == GEOMTRY_BUILDING_SOLID)
			{
				BuildingSolid *pB
					= dynamic_cast<BuildingSolid*>(pGeo);

				pB->revertSolidColor();
				//pB->invalidateRendering();
			}
		}	

		m_buildingLayer->invalidateRendering();

	}

	void OGRPipeLineMap::restoreInitialRender()  
	{
		//退出编辑模式后还原到初始的渲染状态
		if (!m_selectPointVec.empty())
		{
			m_selectPointVec.clear();
		}

		if (!_selectedGeometries.empty())
		{
			_selectedGeometries.clear();
		}

		if (!m_upstreamPtVec.empty())
		{
			m_upstreamPtVec.clear();
		}

		if (!m_sourceVec.empty())
		{
			m_sourceVec.clear();

			for (int i = 0; i < m_jointArray.size(); i++)
			{
				m_jointArray.at(i)->m_pressValue = 0.0f;  //压力值还原
			}
		}

		if (!m_blockPointsVec.empty())
		{
			m_blockPointsVec.clear();
		}

		if (!breakPointsVec.empty())
		{
			breakPointsVec.clear();
		}

		if (_inAnalysisMode == true)
		{
			_inAnalysisMode = false;
		}

		if (_inEditMode == true)
		{
			_inEditMode = false;
		}

		if (m_decreasFlag == true)
		{
			m_decreasFlag = false;
		}

		if (!m_resultPolygon.empty())
		{
			unrenderBuildingAnalysisResult();	
			//unrenderModelAnalysisResult();
			m_resultPolygon.clear();
		}

		if (!m_pipeLineInView.empty())
		{
			m_pipeLineInView.clear();
		}

		if (!m_resultModVec.empty())
		{
			unrenderModelAnalysisResult();
			m_resultModVec.clear();
		}

		if (m_PipeLineEditID != 0)
		{
			glPushMatrix();
			glDeleteLists(m_PipeLineEditID, 1);
			m_PipeLineEditID =0;
			glPopMatrix();
		}

		if (getPipeLineVisible() == false)
		{
			setPipeLineVisible(true);
		}
	}

	PipeGeoPtr OGRPipeLineMap::testInterSectWithPipeGeo(RayLine3d rayline)
	{
		//------------------------------------------
		// 首先判断是否和layer的box相交
		//------------------------------------------
		std::pair<bool, float> result = vgKernel::Math::intersects( 
			rayline.getRay3d().getRayFloat(), _dynamicBox );

		if ( result.first == false )
		{
			return PipeGeoPtr();
		}
		//------------------------------------------
		// 计算转换的ray
		//------------------------------------------
		//Ray3d translatedRay = ray;
		RayLine3d transRayline;

		vgKernel::Mat4 mat = _matrix;
		mat.inverse();

		vgKernel::Vec3 p1 = vgKernel::Math::translateVec3( mat, rayline._pointStart.getVec3Float() );
		transRayline._pointStart = Vec3d( p1 );

		vgKernel::Vec3 p2 = vgKernel::Math::translateVec3( mat, rayline._pointEnd.getVec3Float() );
		transRayline._pointEnd = Vec3d( p2 );
		//------------------------------------------
		// 然后遍历每一个geo, 判断是否相交
		//------------------------------------------
		PipeGeoPtrVector::iterator iter = m_pipeGeoPtrVec.begin();
		PipeGeoPtrVector::iterator iter_end = m_pipeGeoPtrVec.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			PipeGeoPtr pipeGeo = *iter;

			//LineString *pLineString = dynamic_cast<LineString*>(geo);

			if (pipeGeo.isNull() == true)
			{
				return PipeGeoPtr();
			}
			else
			{				
				vgKernel::Box eachBox = getPipeGeoBox(pipeGeo);

				std::pair<bool, float> result = vgKernel::Math::intersects( 
					rayline.getRay3d().getRayFloat(), eachBox );

				if (result.first != false)
				{
					return pipeGeo;
				}
			}
		}
		return PipeGeoPtr();
	}

	vgKernel::Box OGRPipeLineMap::getPipeGeoBox(PipeGeoPtr pipeGeo)
	{		
		vgKernel::Box eachBox = pipeGeo->getEnvelope3f();
		//vgKernel::Vec3 maxPos = eachBox.getMaximum();
		//vgKernel::Vec3 minPos = eachBox.getMinimum();

		//vgKernel::Vec3 maxPosition = vgKernel::Math::translateVec3(layerMatrix, maxPos);
		//vgKernel::Vec3 minPosition = vgKernel::Math::translateVec3(layerMatrix, minPos);

		//eachBox.setMaximum(maxPosition);
		//eachBox.setMinimum(minPosition);

		return eachBox;
	}

	void OGRPipeLineMap::addSelectPipeGeo(PipeGeoPtr pipeGeo)
	{
		PipeGeoPtrVector::iterator iter_find = 
			std::find(m_selectPipeGeoVec.begin(), m_selectPipeGeoVec.end(), pipeGeo);

		if (iter_find == m_selectPipeGeoVec.end())
		{
			if (pipeGeo.isNull() == false && pipeGeo->getType() != PIPEGEO_VALVES)
			{
				m_selectPipeGeoVec.push_back(pipeGeo);
			}
		}
		else
		{
			m_selectPipeGeoVec.erase(iter_find);   //再点击一次已经在选择状态下的几何体就取消选择
		}
	}

	void OGRPipeLineMap::pipeRouteAnalysis()
	{
		if (m_sourceVec.empty())
		{
			AfxMessageBox("请先为管线网络设置压力源");
			return;
		}
		createDigraphAdjList();    //建立有向图的邻接表
		if (m_selectPipeGeoVec.size() != 2)
		{
			AfxMessageBox("只支持两个管线节点间的连通性分析");
			if (!m_selectPipeGeoVec.empty())
			{
				m_selectPipeGeoVec.clear();             //将此次选择的节点清空
			}
			return;
		}
		else
		{
			Vec3 point1 = m_selectPipeGeoVec[0]->getCenterPos();
			Vec3 point2 = m_selectPipeGeoVec[1]->getCenterPos();

			int index1 = -1;
			int index2 = -1;
			
			for (int i = 0; i < m_digraphAdjList.size(); i++)
			{
				if (m_digraphAdjList[i]->m_pos == point1)
				{
					index1 = i;
				}
				if (m_digraphAdjList[i]->m_pos == point2)
				{
					index2 = i;
				}

				if ((index1 != -1) && (index2 != -1))
				{
					break;
				}
			}

			if (m_digraphAdjList[index1]->m_pressValue > m_digraphAdjList[index2]->m_pressValue)
			{
				ifTheTwoGeoConnect(index1, index2);
			}
			else
			{
				ifTheTwoGeoConnect(index2, index1);
			}
		}

		if (!m_selectPipeGeoVec.empty())
		{
			m_selectPipeGeoVec.clear();             //分析完一次之后将此次选择的节点清空
		}
	}

	void OGRPipeLineMap::ifTheTwoGeoConnect(int upIndex, int downIndex)
	{
		std::vector <int> visitedGeoVec;
		std::vector <int> tempGeoVec;
		bool findFlag = false;
		
		visitedGeoVec.push_back(upIndex);
		tempGeoVec.push_back(upIndex);

		while (!tempGeoVec.empty())
		{
			int temp = tempGeoVec.at(0);
			vector<int> ::iterator iter= tempGeoVec.begin();
			tempGeoVec.erase(iter);

			vector<JointDist> *adjVec = m_digraphAdjList[temp]->m_pJointVec;
			for (int i = 0; i < adjVec->size(); i++)
			{
				std::vector<int> ::iterator iter_find = find(visitedGeoVec.begin(), visitedGeoVec.end(), adjVec->at(i).pointIndex);
				if ((iter_find == visitedGeoVec.end()) && (adjVec->at(i).pointIndex != downIndex))
				{
					visitedGeoVec.push_back(adjVec->at(i).pointIndex);
					tempGeoVec.push_back(adjVec->at(i).pointIndex);
				}
				else if (adjVec->at(i).pointIndex == downIndex)
				{
					findFlag =  true;
					break;
				}
				else
				{
					continue;
				}
			}
		}

		if (findFlag)
		{
			programWithDijkstra(upIndex, downIndex);   //计算最短路径
		}
		else
		{
			AfxMessageBox("所选节点不连通");
		}		
	}

	bool OGRPipeLineMap::programWithDijkstra(int startPotID, int endPotID)
	{
		std::multimap<double, int> m_openTable;

		if (startPotID < 0 || endPotID < 0)
		{
			AfxMessageBox("路径端点错误.");
			return false;
		}

		int pointCnt = m_digraphAdjList.size();

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
			double dist = m_digraphAdjList[startPotID]->connectWith(i);
			if (dist > 0)
			{
				pRd[i].dist = dist;
				pRd[i].byPassIndex = startPotID;

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
			vector<JointDist> *pVec = m_digraphAdjList[w]->getJointVecPointer();
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
		if (pRd[endPotID].final)
		{
			TRACE("We Found a Route. Distance : %f \n", pRd[endPotID].dist);

			char buffer[1024];

			sprintf(buffer, "所选节点联通，并搜索到最短路径. 路径总长：%.3f 米", pRd[endPotID].dist);

			::MessageBox(NULL, buffer, "路径信息", MB_OK);

			m_pointInRoad.clear();

			int lastIndex = endPotID;
			int index = pRd[endPotID].byPassIndex;	

			while (lastIndex != startPotID)
			{
				m_pointInRoad.push_back(lastIndex);
				lastIndex = pRd[lastIndex].byPassIndex;
			}
			m_pointInRoad.push_back(startPotID);			
		}
		else
		{
			AfxMessageBox("未找到路径");
		}
		return true;
	}

	PipeGeoPtr OGRPipeLineMap::getPipeGeoIndex(int ID)
	{
		vgKernel::Vec3 pos = m_jointArray.at(ID)->m_pos;	
		
		for (int i = 0; i < m_pipeGeoPtrVec.size(); i++)
		{
			if ((m_pipeGeoPtrVec.at(i)->getCenterPos() == pos) && (m_pipeGeoPtrVec[i]->getType() != PIPEGEO_VALVES))
			{
				return m_pipeGeoPtrVec[i];
			}
			else
			{
				continue;
			}
		}
		return PipeGeoPtr();
	}

	void OGRPipeLineMap::drawShortestPath()
	{
		if (m_pointInRoad.empty())
		{
			return;
		}
		std::stack <int>   m_AllPoint;

		std::vector <int> ::iterator iter = m_pointInRoad.begin();
		std::vector <int> ::iterator iter_end = m_pointInRoad.end();	

		for (; iter != iter_end; iter++)
		{
			if (m_AllPoint.empty())
			{
				m_AllPoint.push((*iter));
			}
			else
			{
				getPipeLineDrection(m_digraphAdjList[m_AllPoint.top()]->m_pos, m_digraphAdjList[*iter]->m_pos);			
				vgKernel::Vec3 pos = m_digraphAdjList[m_AllPoint.top()]->m_pos;				
				
				glPushMatrix();
				glDisable(GL_TEXTURE_2D);
				glColor3f(0.63f, 0.13f, 0.94f);
				glDisable(GL_BLEND);
				glTranslatef(pos.x, pos.y, pos.z);
				glRotatef(Tran_angle, Axis[0], Axis[1], Axis[2]);				
				gluCylinder(quadyuanzhu, 1.2*m_pipeLineRadius, 1.2*m_pipeLineRadius, m_distance, 20, 20);				
				glTranslatef(0.0f, 0.0f, m_distance);				
				gluSphere(yuanqiu, 1.2*m_pipeLineRadius, 20, 20);
				glEnable(GL_TEXTURE_2D);
				glPopMatrix();

				m_AllPoint.push((*iter));

			}	
		}
	}

	void OGRPipeLineMap::addPipeLineToView(LineString* pipeline)
	{
		if (!m_pipeLineInView.empty())
		{
			m_pipeLineInView.clear();
		}
		m_pipeLineInView.push_back(pipeline);
	}

	void OGRPipeLineMap::renderViewPipeLineBox()
	{
		if (m_pipeLineInView.empty())
		{
			return;
		}
		for (int i = 0; i < m_pipeLineInView.size(); i++)
		{
			if (m_pipeLineInView[i] != NULL)
			{
				vgKernel::Box pipeLinebox = getPipeLineBox(m_pipeLineInView[i]);
				pipeLinebox.render();
			}
		}
	}

	void OGRPipeLineMap::showPipeLayerAtrriList()
	{
		CWnd* pWnd = vgKernel::SystemUtility::getCurrentViewWnd();
		pWnd->SetTimer( 1, 150, NULL );
		vgPipeLayerAttriDlg dlg;
		if (dlg.DoModal() == IDOK)
		{
			return;
		}
		pWnd->SetTimer( 1, 15, NULL );
	}
}// end namespace vgGIS3D
