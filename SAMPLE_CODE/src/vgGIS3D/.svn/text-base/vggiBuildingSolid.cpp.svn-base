#include <vgStableHeaders.h>
#include <vgGis3D/vggiBuildingSolid.h>
#include <vgKernel/vgkMath.h>
#include <vgKernel/vgkOpenGLSupport.h>
#include <gdal/ogr_api.h>
#include <gdal/ogr_feature.h>

namespace vgGIS3D
{
	BuildingSolid::BuildingSolid(OGRFeature *feature, vgGIS3D::Layer *father_layer)
		: Geometry(feature, father_layer), m_innerPolygon(feature, father_layer)
	{
// 		m_floor = feature->GetFieldAsInteger("Floor");
// 		m_heightPerFloor = 3;
		
		m_innerPolygon.getDrawingDescriptor()->setNewFatherGeometry(this);
		
		DrawingDescriptor *pdes = m_innerPolygon.getDrawingDescriptor();
		// 边缘颜色
		pdes->setPenColor(0xa5a5a5);

		m_defaultColor.setAsColorRef(0xa5a5a5);

		// 上下底颜色
		//pdes->setFillColor(0xb4b4b4);
		pdes->setFillColor(0xafeeee80);

		TRACE("Floor : %d \n", m_floor);
	}

	void BuildingSolid::invalidateRendering()
	{
		if ( _callListId != 0 )
		{
			VGK_CHECK_OPENGL_ERROR();

			glDeleteLists( _callListId , 1 );
			_callListId = 0;

			VGK_CHECK_OPENGL_ERROR();
		}
	}

	void BuildingSolid::renderUsingDisplayList()
	{
		//assert(0);

		VGK_CHECK_OPENGL_ERROR();

		if ( _callListId == 0 )
		{
			_callListId = glGenLists( 1 );   
			assert( _callListId != 0 );

			glNewList( _callListId, GL_COMPILE );
			renderOnceForDisplayList();
			glEndList();	
		}
		VGK_CHECK_OPENGL_ERROR();

		assert( _callListId != 0 );

		glPushMatrix();
		glCallList( _callListId );
		glPopMatrix();
	}

	void BuildingSolid::renderOnceForDisplayList()
	{
		std::vector<RingStruct> rings = m_innerPolygon.getRings();

		TRACE("Floor : %d \n", m_floor);

		DrawingDescriptor* desc = m_innerPolygon.getDrawingDescriptor();

		TRACE("Floor : %d \n", m_floor);

		double penwidth = desc->getPenWidth();

		TRACE("Floor : %d \n", m_floor);

		if ( penwidth >= vgKernel::Math::ZERO_TOLERANCE )
		{
			VGK_CHECK_OPENGL_ERROR();

			glDisable( GL_TEXTURE_2D );
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			vgKernel::ColorVal col = desc->getPenColorVal();
			col.useBind();

			//// Green polygon
			//glColor3f(0.5f, 1.0f, 0.0f);			

			glLineWidth( penwidth );
			glPushMatrix();
			for ( int i = 0 ; i < rings.size() ; ++ i )
			{
				glBegin( GL_QUADS );
				for(int j = 1; j < rings[i]._numPoints; j++)
				{
					GLdouble* addr = rings[i]._pointsBeginAddr + 3 * j;
					
					// 绘制每一层
					for (int f=0; f<m_floor; f++)
					{
						vgKernel::ColorVal color1 = lookupColor(f, j);
						vgKernel::ColorVal color2 = lookupColor(f, j-1);
						
						// glEnable(GL_SMOOTH);

						glColor4f(color2.r, color2.g, color2.b, color2.a);
						glVertex3f( *(addr-3) , *(addr-3+1) + f * m_heightPerFloor, *(addr-3+2) );
						
						glColor4f(color1.r, color1.g, color1.b, color1.a);
						glVertex3f( *addr , *(addr+1) + f * m_heightPerFloor, *(addr+2) );
						glVertex3f( *addr, *(addr+1) + (f+1) * m_heightPerFloor, *(addr+2) );
						
						glColor4f(color2.r, color2.g, color2.b, color2.a);
						glVertex3f( *(addr-3), *(addr-3+1) + (f+1) * m_heightPerFloor, *(addr-3+2) );
					}

				}
				glEnd();
			}
			glPopMatrix();
			VGK_CHECK_OPENGL_ERROR();
		}

		// 绘制两面

		if ( desc->isDrawFilling() )
		{
			VGK_CHECK_OPENGL_ERROR();

			//glColor3f(0.3f, 0.3f, 0.3f); 
			//float randfloat = rand() *1.0 / RAND_MAX ;
			//glColor3f( randfloat, 0.3, 0.3f);
			vgKernel::ColorVal col = desc->getFillingColorVal();
			col.useBind();

			VGK_CHECK_OPENGL_ERROR();
			glDisable( GL_TEXTURE_2D );
			//线面三行 add by KingHJ  设置顶面和地面的颜色并半透
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(0.68f, 0.93f, 0.93f, 0.5f);
			//glPushAttrib(GL_CURRENT_BIT);
			
			glPushMatrix();
			{
				GLUtesselator *pTess = NULL;
				pTess = gluNewTess();
				gluTessCallback(pTess, GLU_BEGIN, (void(__stdcall*)())glBegin);
				gluTessCallback(pTess, GLU_END, (void(__stdcall*)())glEnd);
				gluTessCallback(pTess, GLU_VERTEX, (void(__stdcall*)())glVertex3dv);

				gluTessProperty(pTess, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_ODD);

				gluTessBeginPolygon(pTess, NULL); // No user data
#if 0

				for ( int i = 0 ; i < rings.size() ; ++ i )
				{
					if ( i == 0 )
					{
						double* addr;
						// 渲染exterior rings
						gluTessBeginContour(pTess);
						for(int j = 0; j < rings[i]._numPoints; j++)
						{
							addr = rings[i]._pointsBeginAddr + 3 * j;
							gluTessVertex( pTess, addr ,  addr );
						}
						gluTessEndContour(pTess);
					}
					else
					{
						double* addr;
						// 渲染exterior rings
						gluTessBeginContour(pTess);
						for(int j = 0; j < rings[i]._numPoints; j++)
						{
							addr = rings[i]._pointsBeginAddr + 3 * j;

							gluTessVertex( pTess, addr,  addr );
						}
						gluTessEndContour(pTess);
					}
				}

				// All done with polygon
				gluTessEndPolygon(pTess);
#endif 
				//glPushMatrix();
				gluTessBeginPolygon(pTess, NULL); // No user data

				glTranslatef(0, m_heightPerFloor * m_floor, 0);
				for ( int i = 0 ; i < rings.size() ; ++ i )
				{
					if ( i == 0 )
					{
						double* addr;
						// 渲染exterior rings
						gluTessBeginContour(pTess);
						for(int j = 0; j < rings[i]._numPoints; j++)
						{
							addr = rings[i]._pointsBeginAddr + 3 * j;
							gluTessVertex( pTess, addr ,  addr );
						}
						gluTessEndContour(pTess);
					}
					else
					{
						double* addr;
						// 渲染exterior rings
						gluTessBeginContour(pTess);
						for(int j = 0; j < rings[i]._numPoints; j++)
						{
							addr = rings[i]._pointsBeginAddr + 3 * j;

							gluTessVertex( pTess, addr,  addr );
						}
						gluTessEndContour(pTess);
					}
				}
				gluTessEndPolygon(pTess);

				//glPopMatrix();
				// No longer need tessellator object
				gluDeleteTess(pTess);            
			}
			// glEnable(GL_DEPTH_TEST);

			VGK_CHECK_OPENGL_ERROR();
			glDisable(GL_BLEND);
			glPopMatrix();
		}
	}

	vgKernel::ColorVal BuildingSolid::lookupColor(int floorNum, int pointIndex)
	{
		map<int, vgKernel::ColorVal>::iterator re = m_colorMap.find(pointIndex + floorNum * getNumOfPoints());
		if ( re  != m_colorMap.end() )
		{
			return (*re).second;
		}
		else
		{
			return m_defaultColor;
		}

#if 0
		map<int, vgKernel::ColorVal>::iterator iter = m_colorMap.begin();
		map<int, vgKernel::ColorVal>::iterator iter_end = m_colorMap.begin();
		
		while (iter != iter_end)
		{
			if ((*iter).first.floorNum == floorNum && (*iter).first.pointIndex == pointIndex)
			{
				return iter->second;
			}

			TRACE("color %d %d \n", iter->first.floorNum, iter->first.pointIndex);
			iter ++;
		}
		// TRACE("size %d \n",m_colorMap.size());
#endif
		return m_defaultColor;
	}

	void BuildingSolid::setColorByIndex(int floorNum, int pointIndex, vgKernel::ColorVal color, bool updateNow)
	{
		m_colorMapOld = m_colorMap;

		m_colorMap[pointIndex + floorNum * getNumOfPoints()] = color;
		invalidateRendering();
		renderOnceForDisplayList();

		if (updateNow)
		{
			invalidateRendering();
			renderOnceForDisplayList();
		}
	}	

	void BuildingSolid::setSolidColor(vgKernel::ColorVal color, bool updateNow)
	{
		m_colorMapOld = m_colorMap;

		SolidColorIndex si(0,0);

		for (int i=0; i<m_floor; i++)
		{
			for (int j=0; j<this->getNumOfPoints(); j++)
			{
				m_colorMap[j + i * getNumOfPoints()] = color;
			}
		}

		if (updateNow)
		{
			invalidateRendering();
			renderOnceForDisplayList();
		}

	}

	void BuildingSolid::setFloorColor(int floorNum, vgKernel::ColorVal color, bool updateNow)
	{
		m_colorMapOld = m_colorMap;

		for (int i=0; i<getNumOfPoints(); i++)
		{
			m_colorMap.insert(std::make_pair(i + getNumOfPoints() * floorNum, color));
		}
		
		if (updateNow)
		{
			invalidateRendering();
			renderOnceForDisplayList();
		}
	}

	void BuildingSolid::revertSolidColor()
	{
		m_colorMap = m_colorMapOld;

		invalidateRendering();
	}

	void BuildingSolid::colorSolidByHeight(bool bIfMultiColor)
	{
		vgKernel::ColorVal c1,c2;

		c1 = vgKernel::ColorVal::Red;
		c2 = vgKernel::ColorVal::Blue;

		c2.b = 0.05 * getFloor();

		float ri = (c2.r - c1.r) / getFloor();
		float gi = (c2.g - c1.g) / getFloor();
		float bi = (c2.b - c1.b) / getFloor();

		for (int i=0;i<getFloor(); i++)
		{
			vgKernel::ColorVal color;
			color.r = c1.r + i * ri;
			color.g = c1.g + i * gi;
			color.b = c1.b + i * bi;
			setFloorColor(i, color, false);
		}
		// 注意，在平时调用时，需要把layer也invalidateRendering一下
		// 因为Layer里面有显示列表的嵌套
		invalidateRendering();

		if (!bIfMultiColor)
		{
			setSolidColor(vgKernel::ColorVal(0.68f, 0.93f, 0.93f, 0.5f));
			invalidateRendering();
		}
	}

	double BuildingSolid::getPlaneArea()
	{
		OGRPolygon surf_polygon;
		OGRLinearRing poly_ring;
		surf_polygon.setCoordinateDimension(3);
		poly_ring.setCoordinateDimension(3);

		std::vector<RingStruct> rings = m_innerPolygon.getRings();

		for ( int i = 0 ; i < rings.size() ; ++ i )
		{
			double* addr;
			for(int j = 0; j < rings[i]._numPoints; j++)
			{
				addr = rings[i]._pointsBeginAddr + 3 * j;
				poly_ring.addPoint( *addr, *(addr+2), -*(addr+1) );
			}
		}

		poly_ring.closeRings();
		surf_polygon.addRing(&poly_ring);
		surf_polygon.flattenTo2D();

		return surf_polygon.get_Area();
	}

}