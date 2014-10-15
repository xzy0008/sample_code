



#include <vgStableHeaders.h>
#include <vgGis/vggisAnalysisHandle.h>

//#include <vgMod/vgObjNode.h>


#include <vgKernel/vgkInputCodeDef.h>

#include <vgKernel/vgkMath.h>
#include <vgKernel/vgkCoordSystem.h>
#include <vgKernel/vgkRendererManager.h>
#include <vgKernel/vgkSelectManager.h>
#include <gdal/ogr_geometry.h>


#include <vgGIS/vgGisManager.h>

#include <vgGIS3D/vggiDlgBufferParameter.h>
#include <vgGIS3D/vggiFaecherAnalysisDlg.h>

#include <vgGIS3D/vggiGisDataManager.h> 
#include <vgGIS3D/vggiContourCreateFacade.h>
#include <vgGIS3D/vggiDlgControlHeightAna.h>

namespace vgGIS3D {


	//----------------------------------------------------------------
	GisAnalysis::GisAnalysis( EGisState eType)
	{
		SetHandleStatus( VG_INPUTMODE_GIS );
		vgKernel::InputSystem::getSingleton().registerHandle( this );


		vgKernel::InputSystem::getSingleton().setCurrentStatus( 
			VG_INPUTMODE_GIS |
			VG_INPUTMODE_CAMERA | VG_INPUTMODE_UI );

		m_buffer = NULL;

		reset();

		m_eGisState	=	eType;
		m_bFirstClick = true;
		m_pFaecherAnalysisDlg = NULL;

	}



	//----------------------------------------------------------------
	GisAnalysis::~GisAnalysis()
	{
		vgKernel::InputSystem::getSingleton().removeHandle( this );
		vgKernel::InputSystem::getSingleton().setDefaultStatus();

		reset();

		if (m_pFaecherAnalysisDlg != NULL)
		{
			delete m_pFaecherAnalysisDlg;
			m_pFaecherAnalysisDlg = NULL;
		}
	}

	// 输入模块 ---------------------------------------------------
	void GisAnalysis::OnLButtonDown(UINT nFlags, CPoint position)
	{
		m_RedLinePt.clear();
		m_YellowLinePt.clear();

		switch(m_eGisState)
		{
		case GisDistance:

		case GisArea:

		case GisVolume:
			pickAndAppendPoint(position);
			break;

		case GisCoordinate:
			break;

		case GisEidtRoute:
			pickAndAppendPoint(position);
			break;

		case GisContourVtr:
			pickAndAppendPoint(position);
			break;

		case GisFaecher:
			if (m_PointsTemp.empty())
			{
				pickAndAppendPoint(position);
			}
					
			break;

		case GisVer_Hor_Slope:
			{
				getDynamicPoint(position);
				if ( m_bFirstClick )
				{
					m_pointsInLine.clear();
					m_bOperationDone = false;
					m_bFirstClick = false;
					pickAndAppendPoint(position);
				}
				else
				{
					m_bOperationDone = true;
					m_bFirstClick = true;
					pickAndAppendPoint(position);

					if ( m_pointsInLine.size() == 2 )
					{
						Vec3 vec3pt1( m_pointsInLine[0].x, m_pointsInLine[1].y, m_pointsInLine[0].z );
						m_RedLinePt.push_back( m_pointsInLine[0] );
						m_RedLinePt.push_back( vec3pt1 );

						m_YellowLinePt.push_back( vec3pt1 );
						m_YellowLinePt.push_back( m_pointsInLine[1]);
					}
					showResult();
				}// end if
			}//end case GisHorLength
			break;

		case GisControlHeight:
			if ( m_bFirstClick )
			{
				m_pointsInLine.clear();
				m_ControlHeightPts2.clear();
				m_bFirstClick = false;
			}
			pickAndAppendPoint(position);
			calculateMousePtRounding();
			break;

		default:
			break;
		}
	}

	//----------------------------------------------------------------
	void GisAnalysis::OnLButtonDbClick(UINT nFlags, CPoint position)
	{
		if (getGisState() == GisNone)
		{
			return ;
		}

		m_bOperationDone = true;

		switch(m_eGisState)
		{
		case GisCoordinate:
			m_pointsInLine.clear();
			pickAndAppendPoint(position);
			showResult();

			break;

		case GisDistance:

		case GisArea:

		case GisWaterArea:
			showResult();
			break;

		case GisVolume:
			break;

		case GisSelectRoutePoint:
			m_pointsInLine.clear();
			pickAndAppendPoint(position);
			if (vgGIS3D::GisManager::getSingleton().addRouteStarEndPoint(m_pointsInLine[0]) == 2)
			{
				showResult();
				m_bOperationDone = true;
				m_eGisState = GisNone;
				vgKernel::InputSystem::getSingleton().setDefaultStatus();
			}
			else
			{
				m_bOperationDone = false;
			}

			break;

		case GisEidtRoute:
			showResult();	
			break;

			/*case GisBuffer:
			genBuffer();
			break;*/

		case GisBufferShape:
			bufferShapeAnalysis();
			break;

		case GisBufferModel:
			bufferModelAnalysis();
			break;

		case GisContourVtr:
			// vgGIS3D::ContourCreateFacade::createFromGrdFile(m_pointsInLine);
			vgGIS3D::ContourCreateFacade::createFromVtrArea(m_pointsInLine);

			showResult();
			vgKernel::InputSystem::getSingleton().setDefaultStatus();

			break ;

		case GisFaecher:
			showResult();
			break;

			
		case GisControlHeight:
			{
				if ( m_pointsInLine.size() > 2 )
				{
					CWnd* pWnd = vgKernel::SystemUtility::getCurrentViewWnd();
					pWnd->SetTimer( 1, 150, NULL );

					vgGIS3D::vggiDlgControlHeight dlg;

					if (dlg.DoModal() == IDOK)
					{
						float fHeight = dlg.getControlHeight();

						if ( fHeight > 0 )
						{
							calculateControlHeight( fHeight );
							pWnd->SetTimer( 1, 15, NULL );
							m_bFirstClick = true;
							break;
						}
						else
						{
							AfxMessageBox("控制高度应该大于0!请重新输入.");
							m_bFirstClick = true;
							pWnd->SetTimer( 1, 15, NULL );
							break;
						}//end if
					}//end if					
				}//end if
			}
			break;

		default:
			break;
		}

		//m_eGisState = GisNone;
		//vgKernel::InputSystem::getSingleton().setDefaultStatus();

	}

	void GisAnalysis::OnRBottonUp(UINT nFlags, CPoint position)
	{
		//if (getGisState() == GisEidtRoute)
		//{
		//m_pointsInLine.clear();
		switch(getGisState()) // 修改 [5/9/2010 11:07:02 foryond]
		{
		case GisFaecher:
			{
				//m_PointsTemp.clear();
				//m_bOperationDone = false;
				SetbOperationDone(false);
				
				if(m_pFaecherAnalysisDlg != NULL)
				{
					delete m_pFaecherAnalysisDlg;
					m_pFaecherAnalysisDlg = NULL;
				}
				break;
			}
		default:
			m_pointsInLine.clear();
			break;
		}
		//}
			switch ( m_eGisState )
			{
			case GisVer_Hor_Slope:
				{
					m_RedLinePt.clear();
					m_YellowLinePt.clear();
					m_eGisState = GisNone;
					vgKernel::InputSystem::getSingleton().setDefaultStatus();					break;
				}
				break;

			}// End Switch
	}

	//----------------------------------------------------------------
	void GisAnalysis::OnMouseMove(UINT nFlags, CPoint position)
	{
		if (getGisState() == GisNone)
		{
			return ;
		}

		if ( !m_bOperationDone )
		{
			getDynamicPoint(position);

			switch(m_eGisState)
			{
			case GisVer_Hor_Slope:
				{
					if ( m_pointsInLine.size() >= 1 )
					{	
						m_RedLinePt.clear();
						m_YellowLinePt.clear();
						
						Vec3 mousePt(m_pointsInLine[0].x, m_pointDynamic.y, m_pointsInLine[0].z );
						m_RedLinePt.push_back( mousePt );
						m_RedLinePt.push_back(m_pointsInLine[0] );
					
						m_YellowLinePt.push_back( mousePt );
						m_YellowLinePt.push_back( m_pointDynamic );
					}
				}// end case GisVerLength
				break;

			}// end switch
		}// end if
	}


	//----------------------------------------------------------------
	void GisAnalysis::pickAndAppendPoint(CPoint point)
	{
		vgKernel::Vec3 tempVec = vgKernel::Math::
			trans2DPointTo3DVec(point.x, point.y);

		m_pointsInLine.push_back( tempVec );
	}

	//----------------------------------------------------------------
	void GisAnalysis::getDynamicPoint( CPoint point )
	{
		m_pointDynamic = vgKernel::Math::
			trans2DPointTo3DVec(point.x, point.y);
	}



	// 输出模块 ------------------------------------------------------
	void GisAnalysis::showResult()
	{

		std::ostringstream msg;
		int nStatus;
		float tempResult = 0.0f;

		switch(m_eGisState)
		{
		case GisCoordinate:
			{
				assert( !m_pointsInLine.empty() );
				m_pointsInLine[0] += vgKernel::CoordSystem::getSingleton().getProjectionCoord();
				float tempParam = - m_pointsInLine[0].z;	  //tempParam = - z
				m_pointsInLine[0].z = m_pointsInLine[0].y;    //
				m_pointsInLine[0].y = tempParam;
#if VGK_LANG_CHS				
				msg << "所测坐标是:" ;
#else				
				msg << "3D Coordinate equals:" ;
#endif
				char buffer[128];

				sprintf(buffer, "(%.3f, %.3f, %.3f)", m_pointsInLine[0].x, m_pointsInLine[0].y, m_pointsInLine[0].z);
				string posStr(buffer);

				msg << posStr;
				//msg << m_pointsInLine[0].getDetails() ;

				nStatus = MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd, msg.str().c_str(), "GIS分析", MB_OK );
				if ( IDOK == nStatus )
				{
					m_bOperationDone = false;
					m_pointsInLine.clear();
				}
			}
			break;

		case GisDistance:
			{
				tempResult = calculateDistance(m_pointsInLine);

#if VGK_LANG_CHS				
				msg << "所测空间距离是:" ;
				msg << "\n" << tempResult << "米";
#else				
				msg << "3D Distance equals" ;
				msg << "\n" << tempResult << "meters";
#endif

				nStatus = MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd, msg.str().c_str(), "GIS分析", MB_OK );
				if ( IDOK == nStatus )
				{
					m_bOperationDone = false;
					m_pointsInLine.clear();
				}
			}
			break;

		case GisArea:
			{
				tempResult = calculateArea(m_pointsInLine);

#if VGK_LANG_CHS				
				msg << "所测面积是:" ;
				msg << "\n" << tempResult << "平方米";
#else				
				msg << "3D Area equals" ;
				msg << "\n" << tempResult << "square meter";
#endif

				nStatus = MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd, msg.str().c_str(), "GIS分析", MB_OK );
				if ( IDOK == nStatus )
				{
					m_bOperationDone = false;
					m_pointsInLine.clear();
				}
			}
			break;

		case GisVolume:
			{
				tempResult = calculateVolume(m_pointsInLine);

#if VGK_LANG_CHS				
				msg << "所测体积是:" ;
				msg << "\n" << tempResult << "立方米";
#else				
				msg << "3D Volume equals" ;
				msg << "\n" << tempResult << "cubic meter";
#endif

				nStatus = MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd, msg.str().c_str(), "GIS分析", MB_OK );
				if ( IDOK == nStatus )
				{
					m_bOperationDone = false;
					m_pointsInLine.clear();
				}
			}
			break;
		case GisSelectRoutePoint:
			{
				m_bOperationDone = false;
				m_pointsInLine.clear();
				m_eGisState = GisNone;
			}
			break;

		case GisEidtRoute:
			m_bOperationDone = false;
			m_eGisState = GisEidtRoute;
			vgGIS3D::GisManager::getSingleton().addRouteToBuilder(m_pointsInLine);

			m_pointsInLine.clear();

			break;
		case GisFaecher:
			{
				showFaecher(m_pointsInLine);
				m_PointsTemp = m_pointsInLine;
				//m_pointsInLine.clear();
				//m_bOperationDone = false;
				
// 				if (m_pFaecherAnalysisDlg->isLineVisible == true)
// 				{
// 					m_bOperationDone = false;
// 					m_pointsInLine.clear();
// 				}

			}
			break;
		case GisContourVtr:
			m_bOperationDone = false;
			m_pointsInLine.clear();
			m_eGisState = GisNone;
			break;

		case GisVer_Hor_Slope:
			{
				float tempResultVer = calculateVerDistance(m_pointsInLine);
				float tempResultHor = calculateHorDistance(m_pointsInLine);
				float tempResultSlope = calculateSlope( m_pointsInLine[0], m_pointsInLine[1] );
#if VGK_LANG_CHS				
				msg << "所测垂直距离(高差)是: " ;
				msg << tempResultVer << "米" << "\n";
				msg << "\n";
				msg << "所测水平距离是: " ;
				msg << tempResultHor << "米" << "\n";
				msg << "\n";
				msg << "所测坡度是: " ;
				msg << tempResultSlope << "度" << "\n";
#else				
				msg << "Horizontal Distance equals" ;
				msg << "\n" << tempResultVer << "meters";
				msg << "\n";
				msg << "Horizontal Distance equals" ;
				msg << "\n" << tempResultHor << "meters";
				msg << "\n";
				msg << "Slope equals" ;
				msg << "\n" << tempResult << "degree";
#endif
				nStatus = MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd, msg.str().c_str(), "GIS分析", MB_OK );
				if ( IDOK == nStatus )
				{
					m_bOperationDone = true;
				}
			}
			break;

		default:
			break;
		}

	}


	// 计算模块 ------------------------------------------------------
	float GisAnalysis::calculateDistance(const PointsArray& points)
	{
		float fResult = 0.0f;

		for(PointsArray::const_iterator itr = points.begin();
			itr != points.end() - 1; itr ++)
		{
			fResult += itr->distance( *(itr+1) );
		}

		return fResult;
	}


	//----------------------------------------------------------------
	float GisAnalysis::calculateArea(const PointsArray& points)
	{
		float fResult = 0.0f;

		if ( points.size() < 3)
		{
			return fResult;
		}


		for(int  i = 0; i < points.size()-1; i++ )
		{
			fResult += 0.5 * ( points[i].x * points[i+1].z 
				- points[i+1].x * points[i].z );
		}

		fResult += 0.5 * ( points[points.size()-1].x * points[0].z 
			- points[0].x * points[points.size()-1].z );

		fResult = fabs(fResult);

		// 求解立体多边形（近似倾斜平面）与xz水平面夹角的cos值
		float angleElevationCos = calculateAngleCos(points);

		//fResult /= angleElevationCos;

		return	fResult;
	}


	//----------------------------------------------------------------
	float GisAnalysis::calculateAngleCos(const PointsArray& points)
	{
		float fResult = 0.0f;

		if ( points.size() < 3)
		{
			return fResult;
		}

		// 求解立体多边形（近似倾斜平面）与xz水平面夹角，即两平面的法线向量夹角
		vgKernel::Vec3 vector1 = points[0] - points[1];
		vgKernel::Vec3 vector2 = points[0] - points[2];

		vgKernel::Vec3 normalOfPolygon	= vector1.crossProduct(vector2);
		vgKernel::Vec3 normalOfPlane(0, 1, 0);

		// cos(theda) = (A*B)/|A|*|B|
		float angleElevationCos = normalOfPolygon.absDotProduct(normalOfPlane);
		angleElevationCos /= (normalOfPolygon.length() * normalOfPlane.length());

		return angleElevationCos;
	}

	//----------------------------------------------------------------
	float GisAnalysis::calculateVolume(const PointsArray& points)
	{
		float fResult = 0.0f;

		return fResult;
	}

	//---------------------------------------------------------------
	float GisAnalysis::calculateVerDistance(const PointsArray& points)
	{
		// 计算垂直距离
		float fResult = 0.0f;

		for(int  i = 0; i < points.size()-1; i++ )
		{
			if ( points[i].y >= points[i+1].y )
			{
				fResult += (points[i].y  -  points[i+1].y );
			}
			else
			{
				fResult += (points[i+1].y  -  points[i].y );
			}
		}

		return fResult;
	}

	//---------------------------------------------------------------
	float GisAnalysis::calculateHorDistance(const PointsArray& points)
	{
		// 计算水平距离
		float fResult = 0.0f;

		for(int  i = 0; i < points.size()-1; i++ )
		{
			fResult += sqrt((points[i].x  -  points[i+1].x ) * (points[i].x  -  points[i+1].x ) + 
				(points[i].z  -  points[i+1].z ) * (points[i].z  -  points[i+1].z ));
		}

		return fResult;
	}

	//--------------------------------------------------------------
	float GisAnalysis::calculateSlope(vgKernel::Vec3 pt1, vgKernel::Vec3 pt2)
	{
		vgKernel::Vec3 vect1;
		vgKernel::Vec3 vect2;

		if ( pt1.y < pt2.y )
		{
			vgKernel::Vec3 pt3( pt2.x, pt1.y, pt2.z );
			vect1 = pt2 - pt1;
			vect2 = pt3 - pt1;
		}
		else
		{
			vgKernel::Vec3 pt3( pt1.x, pt2.y, pt1.z );
			vect1 = pt1 - pt2;
			vect2 = pt3 - pt2;
		}
		vect1.normalise();
		vect2.normalise();

		float angleCos = vect1.absDotProduct( vect2 ) / ( vect1.length() * vect2.length() );
		float angle = acos(angleCos) * 180 / 3.1415926535898;

		return angle;
	}


	//----------------------------------------------------------------
	bool GisAnalysis::showFaecher(const PointsArray& points)
	{
		if (m_pFaecherAnalysisDlg != NULL)
		{
			delete m_pFaecherAnalysisDlg;
			m_pFaecherAnalysisDlg = NULL;
		}
		
		m_pFaecherAnalysisDlg = new FaecherAnalysisDlg;

		if ( points.size() < 3)
		{
			m_pointsInLine.clear();
			m_bOperationDone = false;
			return false;
		}
		vgKernel::RendererPackage* _culledRenderers = 
			RendererManager::getSingletonPtr()->getCulledRendererPackage();

		RendererPackage::iterator ipac = _culledRenderers->begin();
		RendererPackage::iterator ipac_end = _culledRenderers->end();

		// 1. 将选区构造为第一个OGRPoly
		OGRGeometry* pGeoLine1 = OGRGeometryFactory::createGeometry( wkbLinearRing );
		OGRLinearRing* pLinearRing1 = dynamic_cast<OGRLinearRing*>( pGeoLine1 );

		for ( int i = 0; i < points.size(); i++ )
		{
			pLinearRing1->addPoint( points[i].x, points[i].z );
		}
		pLinearRing1->addPoint( points[0].x, points[0].z );

		OGRGeometry* pGeoPoly1 = OGRGeometryFactory::createGeometry( wkbPolygon );
		OGRPolygon* pPolygon1 = dynamic_cast<OGRPolygon*>( pGeoPoly1 );

		pPolygon1->addRing( pLinearRing1 );

		// 2.循环Renderer,并测试相交、相离、包含
		for ( ; ipac != ipac_end; ++ ipac )
		{
			// 		RendererQueue* AllRendererQue =
			// 			vgKernel::RendererManager::getSingleton().getRendererQueueByType( 5010, false ); //5010为Mod类型
			// 		assert( AllRendererQue != NULL );
			// 
			// 		RendererQueue::iterator iter  = AllRendererQue->begin();
			// 		RendererQueue::iterator iter_end = AllRendererQue->end();
			if ((ipac->first == 5010) || (ipac->first == 5000))
			{
				RendererQueue* que = &ipac->second;
				assert( que != NULL );

				RendererQueue::iterator iter  = que->begin();
				RendererQueue::iterator iter_end = que->end();

				for ( ; iter != iter_end ; ++ iter )
				{
					Renderer* mi = *iter;

					if ( mi->isSelectable() == false || !mi->getVisible() )
					{
						continue;
					}

					Vec3 minPos = mi->getBoundingBox().getMinimum();
					Vec3 maxPos = mi->getBoundingBox().getMaximum();

					// 3. 构造第二个用于相交测试的OGRPloy
					OGRGeometry* pGeoLine2 = OGRGeometryFactory::createGeometry( wkbLinearRing );
					OGRLinearRing* pLinearRing2 = dynamic_cast<OGRLinearRing*>( pGeoLine2 );

					pLinearRing2->addPoint( minPos.x, minPos.z );
					pLinearRing2->addPoint( maxPos.x, minPos.z );
					pLinearRing2->addPoint( maxPos.x, maxPos.z );
					pLinearRing2->addPoint( minPos.x, maxPos.z );
					pLinearRing2->addPoint( minPos.x, minPos.z );

					OGRGeometry* pGeoPoly2 = OGRGeometryFactory::createGeometry( wkbPolygon );
					OGRPolygon* pPolygon2 = dynamic_cast<OGRPolygon*>( pGeoPoly2 );

					pPolygon2->addRing( pLinearRing2 );

					// 4. OGRPoly包含测试

					if (pPolygon1->Intersect(pPolygon2))
					{
						if (pPolygon1->Contains(pPolygon2))
						{
							m_pFaecherAnalysisDlg->m_ContainQue.push_back(*iter);
						}
						else
						{
							m_pFaecherAnalysisDlg->m_IntersectQue.push_back(*iter);
						}
					}
					else
					{
						m_pFaecherAnalysisDlg->m_DisjointQue.push_back(*iter);
					}
					// end if bIntersect

					OGRGeometryFactory::destroyGeometry( pGeoLine2 );
					OGRGeometryFactory::destroyGeometry( pPolygon2 );
					pGeoLine2 = NULL;
					pGeoPoly2 = NULL;

				} // end for iter
			}
			else 	continue;

		}
		m_pFaecherAnalysisDlg->Create(IDD_FAECHER_ANALYSIS_DIALOG);
		m_pFaecherAnalysisDlg->ShowWindow(SW_SHOWNORMAL);

		return true;

	}

	// 属性模块 -----------------------------------------------------
	vgGIS3D::EGisState GisAnalysis::getGisState()
	{
		return	m_eGisState;
	}



	//----------------------------------------------------------------
	bool GisAnalysis::setGisState( EGisState gisState )
	{
		reset();

		vgKernel::InputSystem::getSingleton().setCurrentStatus(VG_INPUTMODE_GIS);

		m_eGisState = gisState;

		return m_eGisState;
	}



	// 渲染模块 ------------------------------------------------------
	void  GisAnalysis::renderGisElements()
	{	
		if (getGisState() == GisNone)
		{
			return ;
		}

		switch( m_eGisState )
		{
		case GisCoordinate:
			renderPoint(m_pointsInLine);
			break;

		case GisVer_Hor_Slope:
			renderYellowLine( m_YellowLinePt );
			renderRedLine( m_RedLinePt, true );
			renderLine( m_pointsInLine );
			break;

		case GisDistance:
			renderLine(m_pointsInLine);
			break;

		case GisControlHeight:
			renderRedLine( m_ControlHeightPts, true);
			renderControlHeiPolygon();
			break;

		case GisArea:
			renderPolygon(m_pointsInLine);
			break;
		case GisSelectRoutePoint:
			renderPoint(m_pointsInLine);
			break;

		case GisEidtRoute :
			renderLine(m_pointsInLine);
			break;

			//case GisBuffer:
		case GisBufferShape:
		case GisBufferModel:
			renderBuffer();
			break;

		case GisContourVtr:
			renderPolygon(m_pointsInLine);
			break;

		case GisFaecher:
			renderPolygon(m_pointsInLine);
			break;
#if 0
		case GisVolume:
			{
				renderBody();
			}
			break;

		case GisWaterArea:
			{
				renderWaterSurface();
			}
			break;

		case GisWaterVolume:
			{
				renderWaterBody();
			}
			break;

		case GisP2PVisibility:
			{
				renderPoint2PointVisible();
			}
			break;

		case GisSection:
			{
				renderEqualHeightLine();
			}
			break;
#endif
		default:
			break;
		}

		// 鼠标点
		if (!m_bOperationDone)
		{
			PointsArray tempPts;
			tempPts.push_back(m_pointDynamic);
			renderPoint(tempPts);
		}


	}

	//----------------------------------------------------------------
	void GisAnalysis::reset()
	{		
		m_pointsInLine.clear();
		m_bOperationDone	= false;
		m_bCloseRing		= false;
		m_pointDynamic		= vgKernel::Vec3();

		m_bHasBuffer = false;

		if ( m_buffer != NULL )
		{
			delete m_buffer;
			m_buffer = NULL;
		}

		m_bFirstClick = true;
		m_RedLinePt.clear();
		m_YellowLinePt.clear();
		m_ControlHeightPts.clear();
		m_ControlHeightPts2.clear();

	}



	//----------------------------------------------------------------
	void GisAnalysis::renderPoint(const PointsArray& points)
	{
		// 红点
		glColor3f(100,0,0);
		renderPointsByMode(points, GL_POINTS, 
			m_bOperationDone, m_bCloseRing);
	}


	//----------------------------------------------------------------
	void GisAnalysis::renderLine(const PointsArray& points)
	{

		renderPoint(points);

		// 绿线
		glColor3f(0,100,0);
		renderPointsByMode(points, GL_LINE_STRIP, 
			m_bOperationDone, m_bCloseRing);

	}


	//----------------------------------------------------------------
	void GisAnalysis::renderPolygon(const PointsArray& points)
	{
		//m_bCloseRing = true;
		//renderLine(points);

		glColor3f(1,1,0);

		glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glPushAttrib(GL_CURRENT_BIT);
		glPointSize(3.0);


		glBegin(GL_LINE_LOOP);
		for(PointsArray::const_iterator itr = points.begin();
			itr != points.end(); itr ++)
		{
			glVertex3fv(itr->v);
		}

		glVertex3fv(m_pointDynamic.v);

		glEnd();

		glPopAttrib();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glPopMatrix();
	}


	//----------------------------------------------------------------
	void GisAnalysis::renderPointsByMode( const PointsArray& points, int nRenderMode,
		bool bOperationDone /*= false*/, bool bCloseRing /*= false*/)
	{
		glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glPushAttrib(GL_CURRENT_BIT);
		glPointSize(3.0);


		glBegin(nRenderMode);
		for(PointsArray::const_iterator itr = points.begin();
			itr != points.end(); itr ++)
		{
			glVertex3fv(itr->v);
		}

		if ( !bOperationDone )
		{
			glVertex3fv(m_pointDynamic.v);
		}
		else if( bCloseRing )
		{
			glVertex3fv(points[0].v);
		}

		glEnd();


		glPopAttrib();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glPopMatrix();
	}



	//----------------------------------------------------------------
	void GisAnalysis::renderBuffer()
	{
		if ( m_buffer != NULL )
		{
			m_buffer->render();
		}
	}

	PointsArray GisAnalysis::GetPoints()
	{
		return m_pointsInLine;
	}

	void GisAnalysis::SetbOperationDone(bool isDone)
	{
		m_bOperationDone = isDone; 
		if ( isDone == false )
		{
			m_pointsInLine.clear();
			m_PointsTemp.clear();
		}
	}
#if 0
	//----------------------------------------------------------------
	void GisAnalysis::genBuffer()
	{
		if ( !m_bHasBuffer )
		{
			vgKernel::RendererQueue& pSelectedItems = 
				vgKernel::SelectManager::getSingleton().getSelectedItems();

			if ( pSelectedItems.empty() )
			{
				string msg = " 请先选择准备生成缓冲区的矢量要素!";
				vgKernel::SystemUtility::showModelDialog( msg );
				return;
			}

			vgGIS3D::Layer*	pLayer = dynamic_cast<vgGIS3D::Layer*>(pSelectedItems[0]);
			assert( pLayer != NULL );

			// 获取Shape层中选择的对象
			GeometryPointerVec* pSelGeoVec = pLayer->getSelectedGeometry();
			assert( pSelGeoVec != NULL );

			if ( pSelGeoVec->empty() )
			{
				String msg = "请先选择准备生成缓冲区的矢量要素!";
				vgKernel::SystemUtility::showModelDialog( msg );
				return;
			}

			DlgBufferPara dlg;
			dlg.setEnableSelLayer( false );

			CWnd* pwnd = vgKernel::SystemUtility::getCurrentViewWnd();

			pwnd->SetTimer( 1, 150, NULL );
			int status = dlg.DoModal();
			pwnd->SetTimer( 1, 15, NULL );

			if ( status == IDOK )
			{
				assert( m_buffer == NULL );

				m_buffer = new vgGIS3D::Buffer();
				if ( dlg.isLeftRightBuffer() )
				{
					m_buffer->genLeftRightBuffer( pSelGeoVec, dlg.getLeftRadius(), dlg.getRightRadius(), 10 );
				}
				else
				{
					m_buffer->genBuffer( pSelGeoVec, dlg.getRadius(), 10 );
				}

				m_bHasBuffer = true;
			}
		}
	}
#endif
	//----------------------------------------------------------------

	void GisAnalysis::bufferShapeAnalysis()
	{
		if ( !m_bHasBuffer )
		{
			vgKernel::RendererQueue& pSelectedItems = 
				vgKernel::SelectManager::getSingleton().getSelectedItems();

			if ( pSelectedItems.empty() )
			{
				string msg = " 请先选择准备生成缓冲区的矢量要素!";
				vgKernel::SystemUtility::showModelDialog( msg );
				return;
			}

			vgGIS3D::Layer*	pLayer = dynamic_cast<vgGIS3D::Layer*>(pSelectedItems[0]);
			assert( pLayer != NULL );

			// 获取Shape层中选择的对象
			GeometryPointerVec* pSelGeoVec = pLayer->getSelectedGeometry();
			assert( pSelGeoVec != NULL );

			if ( pSelGeoVec->empty() )
			{
				String msg = "请先选择准备生成缓冲区的矢量要素!";
				vgKernel::SystemUtility::showModelDialog( msg );
				return;
			}


			DlgBufferParameter dlg;
			dlg.setEnableSelLayer( true );

			CWnd* pwnd = vgKernel::SystemUtility::getCurrentViewWnd();

			pwnd->SetTimer( 1, 150, NULL );
			int status = dlg.DoModal();
			pwnd->SetTimer( 1, 15, NULL );

			if ( status == IDOK )
			{
				assert( m_buffer == NULL );
				m_buffer = new vgGIS3D::Buffer();

				bool bGenBufferOk;

				if ( dlg.isLeftRightBuffer() )
				{
					bGenBufferOk = m_buffer->genLeftRightBuffer( pSelGeoVec, 
						dlg.getLeftRadius(), dlg.getRightRadius(), 10 );
				}
				else
				{
					bGenBufferOk = m_buffer->genBuffer( pSelGeoVec, dlg.getLeftRadius(), 10 );
				}

				//*****************矢量与缓冲区相交测试
				if ( bGenBufferOk )
				{
					String layerName = dlg.getSelLayerName();

					vgGIS3D::Layer *pAnalyLayer 
						= GisDataManager::getSingleton().getLayerByShortName( layerName );
					if ( pAnalyLayer == NULL )
					{
						return;
					}

					m_buffer->shapeAnalysis( pAnalyLayer );
				}

				m_bHasBuffer = true;
			}
		}
	}

	//----------------------------------------------------------------
	void GisAnalysis::bufferModelAnalysis()
	{
		if ( !m_bHasBuffer )
		{
			vgKernel::RendererQueue& pSelectedItems = 
				vgKernel::SelectManager::getSingleton().getSelectedItems();

			if ( pSelectedItems.empty() )
			{
				string msg = " 请先选择准备生成缓冲区的矢量要素!";
				vgKernel::SystemUtility::showModelDialog( msg );
				return;
			}

			vgGIS3D::Layer*	pLayer = dynamic_cast<vgGIS3D::Layer*>(pSelectedItems[0]);
			assert( pLayer != NULL );

			// 获取Shape层中选择的对象
			GeometryPointerVec* pSelGeoVec = pLayer->getSelectedGeometry();
			assert( pSelGeoVec != NULL );

			if ( pSelGeoVec->empty() )
			{
				String msg = "请先选择准备生成缓冲区的矢量要素!";
				vgKernel::SystemUtility::showModelDialog( msg );
				return;
			}

			DlgBufferParameter dlg;
			dlg.setEnableSelLayer( true );

			CWnd* pwnd = vgKernel::SystemUtility::getCurrentViewWnd();

			pwnd->SetTimer( 1, 150, NULL );
			int status = dlg.DoModal();
			pwnd->SetTimer( 1, 15, NULL );

			if ( status == IDOK )
			{
				assert( m_buffer == NULL );

				m_buffer = new vgGIS3D::Buffer();

				bool bGenBufferOk;

				if ( dlg.isLeftRightBuffer() )
				{
					bGenBufferOk = m_buffer->genLeftRightBuffer( pSelGeoVec, dlg.getLeftRadius(), 
						dlg.getRightRadius(), 10 );
				}
				else
				{
					bGenBufferOk = m_buffer->genBuffer( pSelGeoVec, dlg.getLeftRadius(), 10 );
				}

				//模型与缓冲区相交测试
				if ( bGenBufferOk )
				{
					String layerName = dlg.getSelLayerName();

					vgGIS3D::Layer *pAnalyLayer 
						= GisDataManager::getSingleton().getLayerByShortName( layerName );
					if ( pAnalyLayer == NULL )
					{
						return;
					}

					m_buffer->modelAnalysis(pAnalyLayer);
				}

				m_bHasBuffer = true;
			}

		}
	}

	//----------------------------------------------------------------

	void GisAnalysis::renderRedLine(const PointsArray& points, bool bDone /* = false */)
	{
		// 红色线
		glColor3f(200,0,0);
		renderPointsByMode(points, GL_LINE_STRIP, 
			bDone, m_bCloseRing);
	}

	//---------------------------------------------------------------
	void GisAnalysis::renderYellowLine(const PointsArray& points)
	{
		// 黄色线
		glColor3f(250,250,0);
		renderPointsByMode(points, GL_LINE_STRIP, 
			m_bOperationDone, m_bCloseRing);
	}

	//----------------------------------------------------------------
	void GisAnalysis::renderControlHeiPolygon()
	{
		glPushMatrix();
		glDisable( GL_TEXTURE_2D );
		glEnable(GL_BLEND);
		glPushAttrib(GL_CURRENT_BIT);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0f, 0.15f, 0.0f, 0.4f);

		glBegin(GL_QUADS);
		for(PointsArray::const_iterator itr = m_ControlHeightPts2.begin();
			itr != m_ControlHeightPts2.end(); itr ++)
		{
			glVertex3fv(itr->v);
		}
		glEnd();

		glPopAttrib();
		glDisable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
		glPopMatrix();
	}

	//----------------------------------------------------------------
	void GisAnalysis::calculateControlHeight( float fht )
	{
		m_ControlHeightPts2.clear();
		for(PointsArray::const_iterator itr = m_ControlHeightPts.begin();
			itr != m_ControlHeightPts.end(); itr ++)
		{
			vgKernel::Vec3 vecPt1( itr->x, fht + itr->y, itr->z );
			m_ControlHeightPts2.push_back( vecPt1 );
		}
		
		m_ControlHeightPts.clear();
	}

	void GisAnalysis::calculateMousePtRounding()
	{
		if ( m_pointsInLine.size() < 2 )
		{
			return;
		}

		double pointMinX = std::numeric_limits<double>::infinity();
		double pointMaxX = -(std::numeric_limits<double>::infinity());

		//double pointMaxY = -(std::numeric_limits<double>::infinity());
		double pointMinY = std::numeric_limits<double>::infinity();

		double pointMinZ = std::numeric_limits<double>::infinity();
		double pointMaxZ = -(std::numeric_limits<double>::infinity());

		for(PointsArray::const_iterator itr = m_pointsInLine.begin();
			itr != m_pointsInLine.end(); itr ++)
		{
			if ( itr->x < pointMinX )		// 求最小X
			{
				pointMinX = itr->x;
			}

			if ( itr->x > pointMaxX)		// 最大X
			{
				pointMaxX = itr->x;
			}

			//if ( itr->y > pointMaxY )		// 最大Y
			//{
			//	pointMaxY = itr->y;
			//}

			if ( itr->y < pointMinY )		// 最小Y
			{
				pointMinY = itr->y;
			}

			if ( itr->z < pointMinZ )		// 最小Z
			{
				pointMinZ = itr->z;
			}

			if ( itr->z > pointMaxZ )		// 最大Z
			{
				pointMaxZ = itr->z;
			}
		}

		if ( pointMinY < 0 )
		{
			pointMinY = 0;
		}
		vgKernel::Vec3 vecPt1( pointMinX, pointMinY, pointMinZ );
		vgKernel::Vec3 vecPt2( pointMaxX, pointMinY, pointMinZ );
		vgKernel::Vec3 vecPt3( pointMaxX, pointMinY, pointMaxZ );
		vgKernel::Vec3 vecPt4( pointMinX, pointMinY, pointMaxZ );

		m_ControlHeightPts.clear();
		m_ControlHeightPts.push_back( vecPt1 );
		m_ControlHeightPts.push_back( vecPt2 );
		m_ControlHeightPts.push_back( vecPt3 );
		m_ControlHeightPts.push_back( vecPt4 );
		m_ControlHeightPts.push_back( vecPt1 );
	}

}// end of namespace vgShape
