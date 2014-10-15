



#include <vgStableHeaders.h>
#include <vggis3d/vggiQuerySurface.h>


//#include "vgDlgPlaneLevel.h"

#include <vgKernel/vgkMath.h>
#include <vgKernel/vgkSelectManager.h>
#include <vgGis3d/vggiShapeManager.h>
#include <vgGis3d/vggiPolygon.h>

#include "gdal/ogrsf_frmts.h"
#include "gdal/ogr_api.h"

namespace vgGIS3D {
	

	//----------------------------------------------------------------
	vgshQuerySurface::vgshQuerySurface(vgShape::QueryType qType /*= QUERY_NONE*/,
		String keyFieldName /*= ""*/)
		:_queryType(qType)
		,_keyFieldName(keyFieldName)
	{
		SetHandleStatus( VG_INPUT_VECTOR_ANALYSIS_GREEN );
		vgKernel::InputSystem::getSingleton().registerHandle( this );


		vgKernel::InputSystem::getSingleton().setCurrentStatus( 
			VG_INPUT_VECTOR_ANALYSIS_GREEN |
			VG_INPUTMODE_CAMERA | VG_INPUTMODE_UI );

		//add by zzy 2009/10/28 
		btm = false;
	}

	//----------------------------------------------------------------
	void vgshQuerySurface::setDefault()
	{

	}
	//----------------------------------------------------------------
	vgshQuerySurface::~vgshQuerySurface()
	{
		vgKernel::InputSystem::getSingleton().removeHandle( this );
		vgKernel::InputSystem::getSingleton().setDefaultStatus();

		/*if ( _heightRender != NULL )
		{
			delete _heightRender;
			_heightRender = NULL;
		}*/
	}
	//----------------------------------------------------------------
	void vgshQuerySurface::OnMouseMove( UINT nFlags, CPoint position )
	{
		_mouseVec = vgKernel::Math::trans2DPointTo3DVec(position.x, position.y);
		//_mouseVec = get3dVecFrom2d( position );

	}
	void vgshQuerySurface::OnLButtonDbClick( UINT nFlags, CPoint position )
	{
		//------------------------------------------
		// 这个时候,显示结果,并且重置当前状态
		//------------------------------------------

		if ( _clickPoints.size() < 3 )
		{
			_clickPoints.clear();
			return;
		}

		if (btm==false)//  [11/10/2008 zhu]
		{
			btm=true;


			int size = _clickPoints.size();

			rect=new double*[size];
			for(int i=0;i<size;i++)
				rect[i]=new double[3];

			Vec2Vector* vec2s = new Vec2Vector;

			for ( int i = 0 ; i < size; ++ i )
			{
				Vec3 p1 = _clickPoints[ i ];

				vec2s->push_back( Vec2(  p1.x, p1.z ) );
				rect[i][0]=p1.x;
				rect[i][1]=p1.y;//avh;//p1.y + 10.0f;
				rect[i][2]=p1.z;
			}
			return;
		}
		else
		{
			int size = _clickPoints.size();

			vgKernel::Vec2Vector* vec2s = new vgKernel::Vec2Vector;

			for ( int i = 0 ; i < size; ++ i )
			{
				Vec3 p1 = _clickPoints[ i ];

				vec2s->push_back( Vec2( p1.x , p1.z ) );
			}

			//vgPolygon2D	poly = vgPolygon2D(vec2s);
			vgKernel::Polygon2D	poly = vgKernel::Polygon2D(vec2s);

			onAnalysizeRatio(&poly);

			
			_clickPoints.clear();

			btm=false;//  [11/10/2008 zhu]
		}


	}
	void vgshQuerySurface::OnLButtonDown( UINT nFlags, CPoint position )
	{
		//MessageBox( NULL , _mouseVec.getDetails().c_str() , "" , MB_OK );

		if (btm==false)
		{
			//if ( _sceneBound.testInside( Vec2( _mouseVec.x , _mouseVec.z) ) )
			{
				_clickPoints.push_back( _mouseVec );
			}
		}

	}
	/*void vgshQuerySurface::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
	{
		if ( _clickPoints.size() < 3 )
		{
			_clickPoints.clear();
			return;
		}

		if(zDelta>0)

			avh+=1;
		else if(zDelta<0)
			avh-=1;
		if (btm==true)
		{

			int num=_clickPoints.size();
			for(int dnum=0;dnum<num;dnum++)
			{
				rect[dnum][1]=avh;
			}

		}


	}*/
	/*void vgshQuerySurface::OnRBottonDown(UINT nFlags, CPoint position) 
	{
		CWnd *pwnd=AfxGetApp()->m_pMainWnd;
		if(btm==TRUE)
		{
			CPlaneLevel *dlg=new CPlaneLevel;
			dlg->m_plane_level=avh;	
			dlg->Create(IDD_WATER_LEVEL,NULL);			
			dlg->SetWindowPos(pwnd,400,300,NULL,NULL,SWP_NOSIZE);
			dlg->ShowWindow(SW_SHOW);
		}	

	}*/

	//----------------------------------------------------------------
	//void vgshQuerySurface::render()
	//{
	//	//------------------------------------------
	//	// 绘制这个点
	//	//------------------------------------------
	//	glDisable( GL_DEPTH_TEST );

	//	
	//	drawPoint( _mouseVec );
	//	drawLines( _clickPoints , _mouseVec,btm);

	//	/*if ( _heightRender != NULL )
	//	{
	//		drawHeight( _heightRender );
	//	}*/

	//	glEnable( GL_DEPTH_TEST );
	//	renderExtra();
	//}
	//void vgshQuerySurface::renderExtra()//  [11/10/2008 zhu]
	//----------------------------------------------------------------
	void vgshQuerySurface::render()
	{
		//------------------------------------------
		// 绘制这个点
		//------------------------------------------
		glDisable( GL_DEPTH_TEST );

		drawPoint( _mouseVec );
		drawLines( _clickPoints , _mouseVec,btm);

		//modified by zzy 2009110/28 没有找到向_heightRender添加数据
		//保留它会报错
		/*if ( _heightRender != NULL )
		{
			drawHeight( _heightRender );
		}*/

		glEnable( GL_DEPTH_TEST );
		renderExtra();
	}
	void vgshQuerySurface::renderExtra()//  [11/10/2008 zhu]
	{

		glEnable( GL_BLEND );

		if(btm==TRUE)
		{
			glPushAttrib(GL_CURRENT_BIT);
			glPushMatrix();				
			glColor4f(0,0,10,0.5);
			//glEnable(GL_DEPTH_TEST);
			glDisable( GL_DEPTH_TEST );
			
			// 绘制模拟面 [11/5/2008 zhu]
			basetess = gluNewTess();
			gluTessCallback(basetess, GLU_BEGIN, (void(__stdcall*)())glBegin);
			gluTessCallback(basetess, GLU_VERTEX,(void(__stdcall*)())glVertex3dv);
			gluTessCallback(basetess, GLU_END, glEnd);
			glShadeModel(GL_FLAT); 
			
			//绘制路径
			gluTessBeginPolygon(basetess, (GLvoid *)0);
			gluTessBeginContour(basetess);
			for(int dnum=0;dnum<_clickPoints.size();dnum++)
			{		
				gluTessVertex(basetess, rect[dnum], rect[dnum]);
			}
			gluTessEndContour(basetess);
			gluTessEndPolygon(basetess);
			gluDeleteTess(basetess);

			// 绘制模拟边界 [11/5/2008 zhu]
			Vec3Vector::iterator iter = _clickPoints.begin();
			Vec3Vector::iterator iter_end = _clickPoints.end();
			glBegin(GL_LINE_LOOP);
			for ( ;iter != iter_end ; ++ iter)
			{
				glVertex3f((*iter).x, (*iter).y, (*iter).z);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
			}
			glEnd();
			
			glEnable(GL_DEPTH_TEST);				
			glPopMatrix();
			glPopAttrib();
		}

		glDisable( GL_BLEND );

		return;
	}

	//----------------------------------------------------------------
	void vgshQuerySurface::onAnalysizeRatio( vgKernel::Polygon2D *poly )
	{
		float fSelectorArea  = 0.0f;//= poly->getArea();
		float fEffectiveArea = 0.0f;

		vgKernel::Vec2Vector*	pVec2 = poly->getPoints();
		OGRGeometry* geo = 
			OGRGeometryFactory::createGeometry( wkbLinearRing );

		OGRLinearRing* pRing =  dynamic_cast<OGRLinearRing*>(geo);
		assert(pRing);
		for (vgKernel::Vec2Vector::iterator itr = pVec2->begin();
			itr != pVec2->end();
			itr ++)
		{
			pRing->addPoint(itr->x, -itr->y);//水平面:x_-z
		}
		pRing->addPoint((*pVec2)[0].x, -(*pVec2)[0].y);//水平面:x_-z


		geo = OGRGeometryFactory::createGeometry( wkbPolygon );

		OGRPolygon* pPolySelector =  dynamic_cast<OGRPolygon*>(geo);
		assert(pPolySelector);

		pPolySelector->addRingDirectly(pRing);
		
		fSelectorArea = pPolySelector->get_Area();
		// 以上通过多选框生成一个OGRPolygon，用来选择图层内的图元并统计其面积
		vgKernel::RendererQueue&	pSelectedItems = vgKernel::SelectManager
			::getSingleton().getSelectedItems();

		vgShape::Layer*	pLayer = dynamic_cast<vgShape::Layer*>(pSelectedItems[0]);
		assert(pLayer);

		fEffectiveArea = calculateRatio(pPolySelector, pLayer);


		std::ostringstream queryTypeInfo;
		switch (_queryType)
		{
		case vgShape::GREEN_RATIO://绿化率
			queryTypeInfo << "绿化率" ;
			break;

		case vgShape::PLOT_RATIO://容积率
			queryTypeInfo << "容积率" ;
			break;

		default:
			break;
		}
		std::ostringstream o;
		o << queryTypeInfo.str() << " = " << fEffectiveArea/fSelectorArea;
		
		//MessageBox( NULL , o.str().c_str() , queryTypeInfo.str().c_str() , MB_OK );
		MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd , o.str().c_str() , queryTypeInfo.str().c_str() , MB_OK );

		OGRGeometryFactory::destroyGeometry(pPolySelector);
		return;
	}
	//----------------------------------------------------------------
	float vgshQuerySurface::calculateRatio(OGRPolygon* pPolySelector,
		vgShape::Layer*	pLayer)
	{
		float fGreenArea =0.0f;
		vgShape::GeometryPointerVec* pShapeItems = pLayer->getGeometries();
		vgShape::GeometryPointerVec::iterator iter = pShapeItems->begin();
		vgShape::GeometryPointerVec::iterator iter_end = pShapeItems->end();

		for ( ; iter != iter_end ; ++ iter )
		{
			//vgShape::Polygon* pPolyItem = dynamic_cast<vgShape::Polygon*>(*iter);
			//if (!pPolyItem)
			//{
			//	//assert(0);
			//	continue;
			//}

			//bool bDisjoint = false;
			////------------------------------------------
			//// 首先判断是否和envelope相交.
			////------------------------------------------
			//OGREnvelope	pPolyEnvelope;
			//pPolySelector->getEnvelope(&pPolyEnvelope);

			//vgShape::Box3d _box3dShapeItem = pPolyItem->getEnvelope3d();
			//vgShape::Box3d _box3dPoly(
			//	pPolyEnvelope.MaxX, 0.0f, -pPolyEnvelope.MinY,
			//	pPolyEnvelope.MinX, 0.0f, -pPolyEnvelope.MaxY);

			//bDisjoint = !_box3dPoly.intersects(_box3dShapeItem);
			//if ( bDisjoint )
			//{
			//	continue;
			//}

			switch (_queryType)
			{
			case vgShape::GREEN_RATIO://绿化率
				fGreenArea += getAreaIntersected(pPolySelector, *iter, false);
				break;

			case vgShape::PLOT_RATIO://容积率
				fGreenArea += getAreaIntersected(pPolySelector, *iter, true);
				break;

			default:
				break;
			}
			// 计算重叠面积
		}
		return	fGreenArea;
	}
	//----------------------------------------------------------------
	float vgshQuerySurface::getAreaIntersected(OGRGeometry* poOGRGeo,
		vgShape::Geometry*	pGeo, bool	bMultiWeight/* = false*/)
	{
		OGRFeature* poFeature = pGeo->getOGRFeature();

		OGRGeometry* poOGRGeo2 = poFeature->GetGeometryRef();

		if ( !(wkbPolygon25D == poOGRGeo2->getGeometryType()
			 ||wkbMultiPolygon25D == poOGRGeo2->getGeometryType() ) )
		{
			return false;//assert(0);
		}

		poOGRGeo->flattenTo2D();
		poOGRGeo2->flattenTo2D();
		
		bool isContained = false;
		float	areaPoly = 0.0f;
		int		floorCount = 1;

		floorCount = poFeature->GetFieldAsInteger(_keyFieldName.c_str());
		//floorCount = poFeature->GetFieldAsInteger("layer");
		//floorCount = poFeature->GetFieldAsInteger("floor_count");
		if (floorCount<1)
		{
			floorCount = 1;
		}
		
		//switch (_selectMode)
		//{
		//case Disjoint:
		//	isContained = poOGRGeo->Disjoint(poOGRGeo2);		
		//	break;
		//case Touches:
		//	isContained = poOGRGeo->Touches(poOGRGeo2);		
		//	break;
		//case Contains:
		//	isContained = poOGRGeo->Contains(poOGRGeo2);		
		//	break;
		//case Intersects:
		//	isContained = poOGRGeo->Intersects(poOGRGeo2);		
		//	break;
		//case Overlaps:
		//	isContained = poOGRGeo->Overlaps(poOGRGeo2);		
		//	break;
		//case Within:
		//	isContained = poOGRGeo->Within(poOGRGeo2);		
		//	break;
		//default: 
		//	break;
		//}//switch
		if (poOGRGeo->Contains(poOGRGeo2))
		{
			areaPoly = ((OGRPolygon*)poOGRGeo2)->get_Area();
		}

		else if (poOGRGeo->Overlaps(poOGRGeo2))
		{
			OGRGeometry* polyIntersect = poOGRGeo->Intersection(poOGRGeo2);
			areaPoly = ((OGRPolygon*)polyIntersect)->get_Area();
			OGRGeometryFactory::destroyGeometry(polyIntersect);
		}

		else if (poOGRGeo->Within(poOGRGeo2))
		{
			areaPoly = ((OGRPolygon*)poOGRGeo)->get_Area();
		}

		OGRFeature::DestroyFeature( poFeature );

		if (bMultiWeight)
		{
			areaPoly *= floorCount;
		}
		return	areaPoly;
	}

	//----------------------------------------------------------------
	void vgshQuerySurface::setQueryType( vgShape::QueryType qType )
	{
		_queryType = qType;
	}

	//----------------------------------------------------------------
	QueryType vgshQuerySurface::getQueryType()
	{
		return _queryType;
	}

	//----------------------------------------------------------------
	void vgshQuerySurface::setKeyFieldName( String fieldName )
	{
		_keyFieldName = fieldName;
	}

	//----------------------------------------------------------------
	String vgshQuerySurface::getFieldIndex()
	{
		return	_keyFieldName;
	}

	
	//----------------------------------------------------------------
	void vgshQuerySurface::drawHeight( Vec3Vector* points )
	{
		assert( points != NULL );

		Vec3Vector::iterator iter = points->begin();
		Vec3Vector::iterator iter_end = points->end();

		glDisable( GL_TEXTURE_2D );
		glLineWidth( 2.0f );
		glColor3f( 1.0f , 0 , 0 );

		glPushMatrix();
		glBegin( GL_LINE_STRIP );

		for ( ; iter != iter_end ; ++ iter )
		{
			glVertex3fv( iter->v );
		}

		glEnd();
		glPopMatrix();

		return;
	}
	//----------------------------------------------------------------
	void vgshQuerySurface::drawLines( const Vec3Vector& points , const Vec3& mousevec ,bool btm)
	{
		if ( points.size() < 1 )
		{
			return;
		}

		Vec3Vector::const_iterator iter = points.begin();
		Vec3Vector::const_iterator iter_end = points.end();

		glPushMatrix();

		glDisable( GL_TEXTURE_2D );
		glLineWidth(2.0f);

		glBegin( GL_LINE_LOOP );
		for ( ; iter != iter_end ; ++ iter )
		{	
			glVertex3fv( iter->v );
		}
		if (btm==false)
			glVertex3fv( mousevec.v );

		glEnd();

		glPopMatrix();
	}
	//----------------------------------------------------------------
	void vgshQuerySurface::drawPoint( const Vec3& point )
	{
		glDisable( GL_TEXTURE_2D );

		glColor3f( 1, 0.1f ,  0 );
		glPointSize( 3.0f );

		glPushMatrix();

		glBegin( GL_POINTS );
		glVertex3fv( point.v );
		glEnd();

		glPopMatrix();
	}
	//----------------------------------------------------------------

}// end of namespace 
