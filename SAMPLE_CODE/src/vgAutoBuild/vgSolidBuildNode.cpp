#include <vgStableHeaders.h>
#include <vgAutoBuild/vgSolidBuildNode.h>
#include <vgKernel/vgkMath.h>
#include <vgKernel/vgkOpenGLSupport.h>

namespace vgAutoBuild
{
	VGK_RENDERER_IMPLEMENT( SolidBuildNode , RENDERER_TYPE_AUTOSOLIDBUILD )

	SolidBuildNode::SolidBuildNode(PointsArray polygon)
		: _uniqueID( vgKernel::UniqueIDFactory::getUniqueID() )
	{
		_meshName = "Autobuild";
		m_innerPolygon = polygon;

 		m_floor = 5;
 		m_heightPerFloor = 3;
		
		m_defaultColor = vgKernel::ColorVal(0.68f, 0.93f, 0.93f, 0.5f);

		initialise();
	}

	void SolidBuildNode::invalidateRendering()
	{
		if ( _callListId != 0 )
		{
			VGK_CHECK_OPENGL_ERROR();

			glDeleteLists( _callListId , 1 );
			_callListId = 0;

			VGK_CHECK_OPENGL_ERROR();
		}
	}

	void SolidBuildNode::renderUsingDisplayList()
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

	void SolidBuildNode::renderOnceForDisplayList()
	{

		VGK_CHECK_OPENGL_ERROR();

		glDisable( GL_TEXTURE_2D );
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glPushMatrix();
		{

		glBegin( GL_QUADS );

		for (int j = 1; j < m_innerPolygon.size(); j++)
		{
			vgKernel::Vec3 point = m_innerPolygon.at(j);
			vgKernel::Vec3 point_pre = m_innerPolygon.at(j-1);

			//绘制每一层
			for (int f = 0; f < m_floor; f++)
			{

				vgKernel::ColorVal color1 = lookupColor(f, j);
				vgKernel::ColorVal color2 = lookupColor(f, j-1);


				glColor4f(color2.r, color2.g, color2.b, color2.a);
				glVertex3f(point_pre.x, point_pre.y + f * m_heightPerFloor, point_pre.z);

				glColor4f(color1.r, color1.g, color1.b, color1.a);
				glVertex3f(point.x, point.y + f * m_heightPerFloor, point.z);
				glVertex3f(point.x, point.y + (f+1) * m_heightPerFloor, point.z);

				glColor4f(color2.r, color2.g, color2.b, color2.a);
				glVertex3f(point_pre.x, point_pre.y + (f+1) * m_heightPerFloor, point_pre.z);


			}

		}

		{   //第一个点和最后一个点连接闭合
			vgKernel::Vec3 point = m_innerPolygon.at(m_innerPolygon.size()-1);
			vgKernel::Vec3 point_pre = m_innerPolygon.at(0);

			//绘制每一层
			for (int f = 0; f < m_floor; f++)
			{

				vgKernel::ColorVal color1 = lookupColor(f, m_innerPolygon.size()-1);
				vgKernel::ColorVal color2 = lookupColor(f, 0);


				glColor4f(color2.r, color2.g, color2.b, color2.a);
				glVertex3f(point_pre.x, point_pre.y + f * m_heightPerFloor, point_pre.z);

				glColor4f(color1.r, color1.g, color1.b, color1.a);
				glVertex3f(point.x, point.y + f * m_heightPerFloor, point.z);
				glVertex3f(point.x, point.y + (f+1) * m_heightPerFloor, point.z);

				glColor4f(color2.r, color2.g, color2.b, color2.a);
				glVertex3f(point_pre.x, point_pre.y + (f+1) * m_heightPerFloor, point_pre.z);


			}

		}
		glEnd();

		}
		glPopMatrix();

		// 绘制两面
		VGK_CHECK_OPENGL_ERROR();
		{
		vgKernel::ColorVal col = lookupColor(m_floor-1, 0);
		col.useBind(true);

		VGK_CHECK_OPENGL_ERROR();
		glDisable( GL_TEXTURE_2D );
		//设置顶面的颜色并半透
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		glPushMatrix();
		{
			GLUtesselator *pTess = NULL;
			pTess = gluNewTess();
			gluTessCallback(pTess, GLU_BEGIN, (void(__stdcall*)())glBegin);
			gluTessCallback(pTess, GLU_END, (void(__stdcall*)())glEnd);
			gluTessCallback(pTess, GLU_VERTEX, (void(__stdcall*)())glVertex3dv);

			gluTessProperty(pTess, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_ODD);

			//glPushMatrix();
			gluTessBeginPolygon(pTess, NULL); // No user data

			glTranslatef(0, m_heightPerFloor * m_floor, 0);

			double* addr = new double[3*m_innerPolygon.size()];

			for (int i= 0; i < m_innerPolygon.size(); i++)
			{
					addr[3*i+0] = m_innerPolygon.at(i).x;
					addr[3*i+1] = m_innerPolygon.at(i).y;
					addr[3*i+2] = m_innerPolygon.at(i).z;
			}

			        double* addr_cur;

					// 渲染exterior rings
					gluTessBeginContour(pTess);
					for(int j = 0; j < m_innerPolygon.size(); j++)
					{
						addr_cur = addr + 3*j;
						gluTessVertex( pTess, addr_cur ,  addr_cur );
					}
					gluTessEndContour(pTess);


			gluTessEndPolygon(pTess);
			delete [] addr;

 			// No longer need tessellator object
			gluDeleteTess(pTess);            
		}
		glPopMatrix();

		}
		VGK_CHECK_OPENGL_ERROR();
	}

	void SolidBuildNode::initialise()
	{
		colorSolidByHeight(false);
		computeBoundingBox();
	}

	vgKernel::ColorVal SolidBuildNode::lookupColor(int floorNum, int pointIndex)
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

		return m_defaultColor;
	}

	void SolidBuildNode::setColorByIndex(int floorNum, int pointIndex, vgKernel::ColorVal color, bool updateNow)
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

	void SolidBuildNode::setSolidColor(vgKernel::ColorVal color, bool updateNow)
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

	void SolidBuildNode::setFloorColor(int floorNum, vgKernel::ColorVal color, bool updateNow)
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

	void SolidBuildNode::revertSolidColor()
	{
		m_colorMap = m_colorMapOld;

		invalidateRendering();
	}

	void SolidBuildNode::colorSolidByHeight(bool bIfMultiColor)
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
			setSolidColor(m_defaultColor);
			invalidateRendering();
		}
	}

	void SolidBuildNode::translate( const float& x, const float& y, const float& z )
	{
		return;

		vgKernel::Mat4 tran;
		vgKernel::Mat4 tmp;

		vgKernel::Math::createTranslationMatrix(x, y, z, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		//TRACE("translate Matrix \n");


		_dynamicBox = _staticBox;
		_dynamicBox.matrixTranslation(_matrix);

		this->notifyOberversOnEvent(VG_OBS_PROPCHANGED, NULL);

	}

	void SolidBuildNode::rotateSelf( const float& angle, const float& x, const float& y, const float& z )
	{
		return;

		vgKernel::Mat4 tran;
		vgKernel::Mat4 tmp;

		vgKernel::Math::createTranslationMatrix(-_dynamicBox.getCenter().x, -_dynamicBox.getCenter().y, -_dynamicBox.getCenter().z, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		vgKernel::Math::createRotationMatrix(angle, x, y, z, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		vgKernel::Math::createTranslationMatrix(_dynamicBox.getCenter().x, _dynamicBox.getCenter().y, _dynamicBox.getCenter().z, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		_dynamicBox = _staticBox;
		_dynamicBox.matrixTranslation(_matrix);
	}

	void SolidBuildNode::rotate( const float& angle, const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z )
	{
		return;

		vgKernel::Mat4 tran;
		vgKernel::Mat4 tmp;

		vgKernel::Math::createTranslationMatrix(-cx, -cy, -cz, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		vgKernel::Math::createRotationMatrix(angle, x, y, z, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		vgKernel::Math::createTranslationMatrix(cx, cy,cz, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		_dynamicBox = _staticBox;
		_dynamicBox.matrixTranslation(_matrix);

	}

	void SolidBuildNode::scale( const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z )
	{
		return;

		vgKernel::Mat4 tran;
		vgKernel::Mat4 tmp;


		vgKernel::Math::createTranslationMatrix(-cx, -cy, -cz, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		vgKernel::Math::createScaleMatrix(x, y, z, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		vgKernel::Math::createTranslationMatrix(cx, cy,cz, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		_dynamicBox = _staticBox;
		_dynamicBox.matrixTranslation(_matrix);

	}

	float SolidBuildNode::setDistanceToViewer( const vgKernel::Vec3& viewer_pos )
	{
		//------------------------------------------
		// 1.首先通过包围盒计算与视点的距离.
		//------------------------------------------
		float delta[3];

		for ( int i = 0 ; i < 3 ; ++ i )
		{
			float _cur = viewer_pos[i];
			float _max = _dynamicBox._maxVertex.v[i];
			float _min = _dynamicBox._minVertex.v[i];

			if ( _cur > _max )
			{
				delta[i] = _cur - _max;
			}
			else if ( _cur < _min )
			{
				delta[i] = _min - _cur;
			}
			else
			{
				delta[i] = 0.0f;
			}
		}

		_squaredDistanceToViewer = 
			delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2];

		// 2.更新_distanceLod

		return _squaredDistanceToViewer;

	}

	void SolidBuildNode::render()
	{
		if( getVisible() == false )
		{
			return;
		}

		renderUsingDisplayList();

	}

	void SolidBuildNode::computeBoundingBox()
	{
		_staticBox = vgKernel::Box(m_innerPolygon.at(0), m_innerPolygon.at(0));

		for (int i = 0; i < m_innerPolygon.size(); i++)
		{
			_staticBox._minVertex.makeFloor(m_innerPolygon.at(i));
			_staticBox._maxVertex.makeCeil(m_innerPolygon.at(i));

			vgKernel::Vec3 vceil = vgKernel::Vec3(m_innerPolygon.at(i).x,
				m_innerPolygon.at(i).y+m_floor*m_heightPerFloor,
				m_innerPolygon.at(i).z);

			_staticBox._minVertex.makeFloor(vceil);
			_staticBox._maxVertex.makeCeil(vceil);
		}

		_dynamicBox = _staticBox;
	}

	void SolidBuildNode::setFloor( int f )
	{
		m_floor = f; 

		initialise();
		this->notifyOberversOnEvent(VG_OBS_PROPCHANGED, NULL);
	}

	void SolidBuildNode::setHeightPerLayer( float height )
	{
		m_heightPerFloor = height;

		initialise();
	}

	void SolidBuildNode::writeToFile( CFile &fp )
	{
		fp.Write(&_uniqueID, sizeof(vgKernel::UniqueID));

		int length= _meshName.size();
		fp.Write(&length,  sizeof(int));//文件名长度
		fp.Write(_meshName.c_str(), length);//文件名

		fp.Write(&m_floor, sizeof(int));
		fp.Write(&m_heightPerFloor, sizeof(float));

		fp.Write(&m_defaultColor, sizeof(vgKernel::ColorVal));

		int i = m_innerPolygon.size();
		fp.Write(&i, sizeof(int));

		for (int m = 0; m < i; m++)
		{
			vgKernel::Vec3 point= m_innerPolygon.at(m);
			fp.Write(&point, sizeof(vgKernel::Vec3));
		}

	}

	bool SolidBuildNode::readFromFile( CFile &fp )
	{
		fp.Read(&_uniqueID, sizeof(vgKernel::UniqueID));

		int length;
		char tempBuffer[255];
		fp.Read(&length , sizeof(int));
		fp.Read(tempBuffer, length);//文件名
		tempBuffer[length] = '\0';
		_meshName = tempBuffer;

		fp.Read(&m_floor, sizeof(int));
		fp.Read(&m_heightPerFloor, sizeof(float));

		fp.Read(&m_defaultColor, sizeof(vgKernel::ColorVal));

		int i = 0;
		fp.Read(&i, sizeof(int));

		for (int m = 0; m < i; m++)
		{
			vgKernel::Vec3 point;
			fp.Read(&point, sizeof(vgKernel::Vec3));
			m_innerPolygon.push_back(point);
		}

		return true;
	}

	void SolidBuildNode::setColor( vgKernel::ColorVal val )
	{
		m_defaultColor = val;
		initialise();
	}

	vgKernel::ColorVal SolidBuildNode::getColor()
	{
		return m_defaultColor;
	}
}
