
#include <vgStableHeaders.h>
#include <vgplan/vgPlanbox.h>
// #include <vgQuadtreeSceneManager.h>
/*#include <vgMath/vgfVector3.h>*/
// #include <vgSceneData.h>
#include <vgPlan/vgPlanscene.h>
#include <vgPlan/vgPlanmanager.h>
#include <vgSolar/vgsoSolarManager.h>
#include <vgKernel/vgkPluginManager.h>

namespace vgPlan
{
	int faceindex[30] = {1,0,4,   5,1,4,  2,1,5,   6,2,5,  3,2,6,
					7,3,6,  0,3,4,  3,7,4,  5,4,7,  6,5,7};
	
	vgPlanbox::vgPlanbox() : ShadowCastObject(), Renderer()
	{
		m_onEditMode = false;

		m_matrix = vgKernel::Mat4::IDENTITY;

		pVert = NULL;

		pNormalOfFaces = NULL;

		pShadowFaces = NULL;

		mShadowVolume = -1;

		m_geometry = NULL;

//		m_visiable = true;

		m_sceneId = 0;

		m_uid = vgKernel::UniqueIDFactory::getUniqueID();
	}	

	vgPlanbox::vgPlanbox(float _layernum, float _onelayerheight,
								float angle, float _length, float _width,
								vgKernel::Vec3 _pos) : vgKernel::ShadowCastObject()
	{
		m_onelayerheight = _onelayerheight;
		m_layerNum = _layernum;
		m_angle = angle;

//		boxpos = _pos;
		m_pos = _pos;

		m_length = _length;
		m_width = _width;
		m_boxArea = m_length * m_width;
		float temp = m_onelayerheight * m_layerNum;

		pVert = NULL;

		pNormalOfFaces = NULL;

		pShadowFaces = NULL;

		setupBoxData( m_pos, m_length, m_width, temp, m_angle);

		mShadowVolume = -1;

		m_sceneId = 0;

		m_uid = vgKernel::UniqueIDFactory::getUniqueID();
	}


	 void vgPlanbox::rotatevec(vgKernel::Vec2 &_result, vgKernel::Vec2 _vec, float angle )
	{

		vgKernel::Vec2 temp;

		// 角度转弧度
		float angle1 = angle *3.14 / 180.0;

		temp.x = _vec.x * cos( angle1 ) + _vec.y * sin( angle1 );
		temp.y = _vec.y * cos( angle1 ) - _vec.x * sin( angle1 );

		_result.x = temp.x;

		_result.y = temp.y;
		
		return ;

	}
// 
// 	void vgPlanbox::setuplayernum( int _num )
// 	{
// 		m_height = _num * m_heightPerLayer;
// 		m_layerNum = _num;
// 
// 		m_ceil[0] = vgKernel::Vec3( m_floor[0].x, m_pos.y  +m_height, m_floor[0].z );
// 		m_ceil[1] = vgKernel::Vec3( m_floor[1].x, m_pos.y  +m_height, m_floor[1].z );
// 		m_ceil[2] = vgKernel::Vec3( m_floor[2].x, m_pos.y  +m_height, m_floor[2].z );
// 		m_ceil[3] = vgKernel::Vec3( m_floor[3].x, m_pos.y  +m_height, m_floor[3].z );
// 
// 		setupshadowdata();
// 	}


	void vgPlanbox::setupBoxData(const vgKernel::Vec3 & pos, float _length, float _width, float _height, float _angle)
	{
// 		m_length = _length;
// 		m_width = _width;
// 		m_angle = _angle;
// 		m_height = _height;

/*		m_pos = pos; */

		assert( _length > 0 && _width > 0);
	
		vgKernel::Vec2 temp[4] , temp2[4];

		rotatevec(temp2[0], vgKernel::Vec2( -m_length/2,  -m_width/2), m_angle);

		rotatevec(temp2[1], vgKernel::Vec2(  m_length/2,  -m_width/2), m_angle);
		
		rotatevec(temp2[2], vgKernel::Vec2( m_length/2, m_width/2), m_angle);
		
		rotatevec(temp2[3], vgKernel::Vec2( -m_length/2, m_width/2), m_angle);

		temp[0] 
		= 	vgKernel::Vec2(m_pos.x, m_pos.z ) + temp2[0];
		temp[1] 
		= vgKernel::Vec2(m_pos.x, m_pos.z ) + temp2[1];
		temp[2] 
		= vgKernel::Vec2(m_pos.x, m_pos.z ) + temp2[2];
		temp[3] 
		= vgKernel::Vec2(m_pos.x, m_pos.z ) + temp2[3];

// 		for (int i =0 ; i < 4; i++)
// 		{
// 			// boundbox.merge( temp[i] );
// 			m_staticBox.merge(temp[i]);
// 		}

		m_floor[0] = vgKernel::Vec3( temp[0].x, m_pos.y, -temp[0].y );
		m_floor[1] = vgKernel::Vec3( temp[1].x, m_pos.y, -temp[1].y );
		m_floor[2] = vgKernel::Vec3( temp[2].x, m_pos.y, -temp[2].y );
		m_floor[3] = vgKernel::Vec3( temp[3].x, m_pos.y, -temp[3].y );

		m_ceil[0] = vgKernel::Vec3( m_floor[0].x, m_pos.y  +m_height, m_floor[0].z );
		m_ceil[1] = vgKernel::Vec3( m_floor[1].x, m_pos.y  +m_height, m_floor[1].z );
		m_ceil[2] = vgKernel::Vec3( m_floor[2].x, m_pos.y  +m_height, m_floor[2].z );
		m_ceil[3] = vgKernel::Vec3( m_floor[3].x, m_pos.y  +m_height, m_floor[3].z );

		// 计算新包围盒
		m_staticBox.setMaximum(m_ceil[0]);
		m_staticBox.setMinimum(m_ceil[0]);

		for (int i=0; i<4; i++)
		{
			m_staticBox.merge(m_ceil[i]);
			m_staticBox.merge(m_floor[i]);
		}

		m_dynamicBox = m_staticBox;
		
		// m_matrix = vgKernel::Mat4::IDENTITY;
		m_dynamicBox.matrixTranslation(m_matrix);

		m_boxArea = m_width * m_length;
		
		calculategeo();

		setupshadowdata();

// 	setupshadowdata();
// 	buildShadowVolume();
	}

	void vgPlanbox::setupBoxData(float length, float width, int layer, float heightPerLayer, float rotateAngle)
	{
		m_angle = rotateAngle;

		m_length = length;
		m_width = width;

		m_layerNum = layer;
		m_heightPerLayer = heightPerLayer;
		m_height = m_layerNum * m_heightPerLayer;

		vgKernel::Vec3 pos(m_oriX+length/2, 0, m_oriY+width/2);

		// 此处加入贴地代码
		float elevation;
		vgKernel::Vec3 openglPos = pos;
		// pos 使用的是 地理坐标，需要转换成OpenGL坐标贴地
		openglPos.z = -openglPos.z;


		using namespace vgKernel;
		vgKernel::Plugin* _terrainPlug = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );

		if ( _terrainPlug == NULL )
		{
			return;
		}

		VGK_DLL_DECLARE_CLASSFUNC( _terrainPlug, TerrainManager, hasTerrainData, pfn1 );

		assert( pfn1 != NULL);

		if ( pfn1() == false ) 
		{
			//vgTerritory::TerrainManager::getSingleton().getElevationByPosition(openglPos, elevation, true);
			VGK_DLL_RUN_CLASSFUNC( VGT_DLL_NAME , TerrainManager,
				getElevationByPosition )(openglPos, elevation, true);
		}
		else
		{
			elevation = 0.f;
		}

		pos.y = elevation;

		m_pos = pos;
		
		setupBoxData(m_pos, m_length, m_width, m_height, m_angle);
	}

	void vgPlanbox::computenormal()
	{
		delete pNormalOfFaces;

		vgKernel::Vec3 vertex[3], vVector1, vVector2, vNormal;

		pNormalOfFaces = new vgKernel::Vec3[m_facenum];

		for ( int i =0; i < m_facenum; i++ )
		{
			vertex[0] = pVert[faceindex[i*3]];
			vertex[1] = pVert[faceindex[i*3 + 1]];
			vertex[2] = pVert[faceindex[i*3 + 2]];

			vVector1 = vertex[2] - vertex[1];
			vVector2 = vertex[0] - vertex[2];

			vNormal = vVector1.crossProduct(vVector2);

			pNormalOfFaces[i] = -vNormal.normalisedRef() ;
		}
	}
 
 	void vgPlanbox::setupshadowdata()
 	{
 		m_facenum = 10;
 
 		m_numOfVertexs = 8;
 
 		delete[] pVert;
 
 		pVert = new vgKernel::Vec3[8];
 
 		for ( int i =0 ; i < 4; i++)
 		{
 			pVert[i] = m_floor[i];
 		}
 		for ( int i = 4; i < 8; i++)
 		{
 			pVert[i] = m_ceil[i-4];
 		}
 
 		delete[] pShadowFaces;
 
 		computenormal();
 
 		pShadowFaces = new ShadowFaceIndex[m_facenum];
 
 		for (int i = 0; i < m_facenum; i++)
 		{
 			pShadowFaces[i].p1 = faceindex[i*3];
 			pShadowFaces[i].p2 = faceindex[i*3 + 1];
 			pShadowFaces[i].p3 = faceindex[i*3 + 2];
 			pShadowFaces[i].normal = i;
 // 
 // 			tempvecforshadow.push_back( faceIndex(faceindex[i*3],\
 // 				faceindex[i*3 + 1], faceindex[i*3 + 2]));
 		}
 		for (int i = 0; i < m_facenum; i++)
 		{
 			int	face_index1 = sw_searchForAdjacent(  i , pShadowFaces[i].p1 , pShadowFaces[i].p2 );
 			int face_index2 = sw_searchForAdjacent( i , pShadowFaces[i].p2 , pShadowFaces[i].p3 );
 			int face_index3 = sw_searchForAdjacent( i , pShadowFaces[i].p3 , pShadowFaces[i].p1 );
 
 			pShadowFaces[i].p1p2AdjFaceIndex = face_index1;
 			pShadowFaces[i].p2p3AdjFaceIndex = face_index2;
 			pShadowFaces[i].p3p1AdjFaceIndex = face_index3;
 
 			pShadowFaces[i].faceVisible = false;
 			pShadowFaces[i].p1p2Visible = false;
 			pShadowFaces[i].p2p3Visible = false;
 			pShadowFaces[i].p3p1Visible = false;
 		}			
 	}

 	void vgPlanbox::onsunlightanalysis()
 	{
 		vgKernel::Vec3 sundir = m_sunLightDir;
//  		sundir.x = 
//  			vgCore::QuadtreeSceneManager::getSingleton().m_oCurrentScene.m_LightPosForShadow.x;
//  		sundir.y = 
//  			vgCore::QuadtreeSceneManager::getSingleton().m_oCurrentScene.m_LightPosForShadow.y;
//  		sundir.z = 
//  			vgCore::QuadtreeSceneManager::getSingleton().m_oCurrentScene.m_LightPosForShadow.z;
//  
 		for ( int i =0 ; i < m_facenum; i++ )
 		{
 			if ( pNormalOfFaces[ i ].dotProduct(sundir) <=0 )
 			{
 				pShadowFaces[ i ].faceVisible = false;
 
 				continue;
 			}
 			else 
 			{
 				pShadowFaces[ i ].faceVisible = true;
 
 				if ( pShadowFaces[i].p1p2AdjFaceIndex != -1 )
 				{
 
 					float dot_result2 = pNormalOfFaces[ pShadowFaces[i].p1p2AdjFaceIndex ].dotProduct(sundir)  ;
 
 					if ( dot_result2 > 0 )
 					{
 						pShadowFaces[i].p1p2Visible = false;
 					}
 					else
 					{
 						pShadowFaces[i].p1p2Visible = true;
 					}
 				}
 				else
 				{
 					pShadowFaces[i].p1p2Visible = true;
 				}
 
 				// 更新p2p3Visible
 				if ( pShadowFaces[i].p2p3AdjFaceIndex != -1 )
 				{
 					//				int& _normal2 = newobj->shadowFace[face_index1].normal;
 					//				pSWFace.p2p3AdjNormal = face_index2;
 
 					float dot_result2 =  pNormalOfFaces[ pShadowFaces[i].p2p3AdjFaceIndex ].dotProduct(sundir) ;
 
 					if ( dot_result2 > 0 )
 					{
 						pShadowFaces[i].p2p3Visible = false;
 					}
 					else
 					{
 						pShadowFaces[i].p2p3Visible = true;
 					}
 				}
 				else
 				{
 					pShadowFaces[i].p2p3Visible = true;
 				}
 
 				// 更新p3p1Visible
 				if ( pShadowFaces[i].p3p1AdjFaceIndex != -1 )
 				{
 					//				int& _normal2 = newobj->shadowFace[face_index1].normal;
 					//				pSWFace.p3p1AdjNormal = face_index3;
 
 					float dot_result2 =  pNormalOfFaces[ pShadowFaces[i].p3p1AdjFaceIndex ].dotProduct(sundir) ;
 
 					if ( dot_result2 > 0 )
 					{
 						pShadowFaces[i].p3p1Visible = false;
 					}
 					else
 					{
 						pShadowFaces[i].p3p1Visible = true;
 					}
 				}
 				else
 				{
 					pShadowFaces[i].p3p1Visible = true;
 				}
 			}
 
 		}
 
 		buildShadowVolume();
 
 	}

	int vgPlanbox::sw_searchForAdjacent( int faceid , 
		int& point1 , int& point2 )
	{

		for (int face = 0; face < m_facenum; face++)
		{
			if ( face == faceid )
			{
				continue;
			}
			// 得到三个定点
			int p1 = pShadowFaces[ face ].p1;
 			int p2 = pShadowFaces[ face ].p2;
 			int p3 = pShadowFaces[ face ].p3;

// 			int p1 = tempvecforshadow[face].x;
// 			int p2 = tempvecforshadow[face].y;
// 			int p3 = tempvecforshadow[face].z;

			if ( point1 == p1 )
			{
				if ( point2 == p2 || point2 == p3 )
				{
					return face ;
				}
			}
			else if ( point1 == p2 )
			{
				if ( point2 == p1 || point2 == p3 )
				{
					return face ;
				}
			}
			else if ( point1 == p3 )
			{
				if ( point2 == p1 || point2 == p2 )
				{
					return face ;
				}
			}

		}

		// 没有找到
		return -1;
	}


	OGRGeometry* vgPlanbox::getboxgeo()
	{
		return m_geometry;
	}

	void vgPlanbox::calculategeo()
	{
		if (m_geometry != NULL)
		{
			delete m_geometry;
		}

		m_geometry = 
			OGRGeometryFactory::createGeometry( wkbLinearRing );

		OGRLinearRing* pRing =  dynamic_cast<OGRLinearRing*>(m_geometry);
		assert(pRing);
		
		for ( int i =0 ; i < 4; i++)
		{
			vgKernel::Vec3 pos(m_floor[i].x, m_floor[i].y, m_floor[i].z);
			pos = vgKernel::Math::translateVec3(m_matrix, pos);

			pRing->addPoint(pos.x, -pos.z);//水平面:x_-z

		}
		// pRing->addPoint(tmpPos.x, -tmpPos.z);//水平面:x_-z
		// TRACE("%s %.2f %.2f \n", getName().c_str(), pos.x, -pos.z);

		// pRing->addPoint(floor[0].x, -floor[0].z);//水平面:x_-z
		pRing->closeRings();

		m_geometry = OGRGeometryFactory::createGeometry( wkbPolygon );

		OGRPolygon* pPolySelector =  dynamic_cast<OGRPolygon*>(m_geometry);
		assert(pPolySelector);

		pPolySelector->addRingDirectly(pRing);
	}

 	void vgPlanbox::buildShadowVolume()
 	{
 		if( mShadowVolume != -1 )
 		{
 			glDeleteLists( mShadowVolume , 0 );
 		}
 
 		mShadowVolume = glGenLists(1);
 
 		glNewList( mShadowVolume , GL_COMPILE );
 		{
 			glDisable( GL_LIGHTING );
 
 			//vgCore::Vector3 lightDir 
			vgKernel::Vec3 lightDir = m_sunLightDir; 
				//= vgCore::QuadtreeSceneManager::getSingleton().m_oCurrentScene.m_LightPosForShadow;
 			
 			//lightDir.z = - lightDir.z;
 			//lightDir.x = - lightDir.x;
 
 // 			vgKernel::Vec3* ve = vgSolar::SolarManager::getSingleton().getLightDirection();
 // 			lightDir.x = ve->x;
 // 			lightDir.y = ve->y;
 // 			lightDir.z = ve->z;
 
 			lightDir.normalise();
 			
 			glMatrixMode(GL_MODELVIEW);
 			glPushMatrix();
 			glMultMatrixf(m_matrix._m);
 
 			for ( int iface = 0 ; iface < m_facenum ; ++ iface )
 			{
 				ShadowFaceIndex& cur_face = pShadowFaces[ iface ];
 
 				assert( cur_face.p1 >= 0 );
 				vgKernel::Vec3 point1( pVert[ cur_face.p1 ] );
 				assert( cur_face.p2 >= 0 );
 				vgKernel::Vec3 point2( pVert[ cur_face.p2 ] );
 				assert( cur_face.p3 >= 0 );
 				vgKernel::Vec3 point3( pVert[ cur_face.p3 ] );
 
 
 				vgKernel::Vec3 farpoint1;
 				farpoint1 = point1 + lightDir * 10000;
 				vgKernel::Vec3 farpoint2;
 				farpoint2 = point2 + lightDir * 10000;
 				vgKernel::Vec3 farpoint3;
 				farpoint3 = point3 + lightDir * 10000;
 				
  				vgKernel::Vec3 offset(0.1f, 0.1f, 0.1f);
  
  				farpoint1 = farpoint1 - offset;
  				farpoint2 = farpoint2 - offset;
  				farpoint3 = farpoint3 - offset;
  				point1 = point1 - offset;
  				point2 = point2 - offset;
  				point3 = point3 - offset;
 
 				if ( cur_face.faceVisible == true )
 				{
 					glColor4f(1,0,1,0);
 
 					glBegin( GL_QUADS );
 					{
 						if ( cur_face.p1p2Visible )
 						{
 							glVertex3fv( point1.v );
 							glVertex3fv( farpoint1.v );
 							glVertex3fv( farpoint2.v );
 							glVertex3fv( point2.v );
 						}
 						if ( cur_face.p2p3Visible )
 						{
 
 							glVertex3fv( point2.v );
 							glVertex3fv( farpoint2.v );
 							glVertex3fv( farpoint3.v );
 							glVertex3fv( point3.v );
 						}
 						if ( cur_face.p3p1Visible )
 						{
 							glVertex3fv( point3.v );
 							glVertex3fv( farpoint3.v );
 							glVertex3fv( farpoint1.v );
 							glVertex3fv( point1.v );
 						}
 					}
 					glEnd();
 				}
 
 			}
 
 			glPopMatrix();
 
 		}
 		glEndList();
 
 
 	}

	void vgPlanbox::render()
	{
		if (! getVisible())
		{
			return ;
		}

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		glMultMatrixf(m_matrix._m);	

// 		glColor4f(1.0,1.0,1.0,1);		
		glDisable( GL_TEXTURE_2D );		
		glDisable(GL_LIGHTING);
		glDisable(GL_CULL_FACE);

 		glEnable( GL_BLEND );
		
		float red = vgPlan::vgPlanManager::getSingleton().getSceneById(m_sceneId)->getBlockRed();
		float blue = vgPlan::vgPlanManager::getSingleton().getSceneById(m_sceneId)->getBlockBlue();
		float green = vgPlan::vgPlanManager::getSingleton().getSceneById(m_sceneId)->getBlockGreen();
		float alpha = vgPlan::vgPlanManager::getSingleton().getSceneById(m_sceneId)->getBlockAlpha();

 		//glColor4f(0.0,0.0,0.2,.5);	
		glColor4f(red, green, blue, alpha);	

		glBegin( GL_QUADS );
		glVertex3f( m_floor[0].x, m_floor[0].y, m_floor[0].z );
		glVertex3f( m_floor[1].x, m_floor[1].y, m_floor[1].z ) ;
		glVertex3f( m_ceil[1].x, m_ceil[1].y, m_ceil[1].z ); 
		glVertex3f( m_ceil[0].x, m_ceil[0].y, m_ceil[0].z );
		glEnd();
		//glColor4f(0.1,0.0,0.4,1);	
		glBegin( GL_QUADS );
		glVertex3f( m_floor[1].x, m_floor[1].y, m_floor[1].z );
		glVertex3f( m_floor[2].x, m_floor[2].y, m_floor[2].z ) ;
		glVertex3f( m_ceil[2].x, m_ceil[2].y, m_ceil[2].z ); 
		glVertex3f( m_ceil[1].x, m_ceil[1].y, m_ceil[1].z );
		glEnd();
		//glColor4f(0.1,0.1,0.4,1);	
		glBegin( GL_QUADS );
		glVertex3f( m_floor[2].x, m_floor[2].y, m_floor[2].z );
		glVertex3f( m_floor[3].x, m_floor[3].y, m_floor[3].z ) ;
		glVertex3f( m_ceil[3].x, m_ceil[3].y, m_ceil[3].z ); 
		glVertex3f( m_ceil[2].x, m_ceil[2].y, m_ceil[2].z );
		glEnd();
		//glColor4f(0.1,0.2,0.4,1);	
		glBegin( GL_QUADS );
		glVertex3f( m_floor[3].x, m_floor[3].y, m_floor[3].z );
		glVertex3f( m_floor[0].x, m_floor[0].y, m_floor[0].z ) ;
		glVertex3f( m_ceil[0].x, m_ceil[0].y, m_ceil[0].z ); 
		glVertex3f( m_ceil[3].x, m_ceil[3].y, m_ceil[3].z );
		glEnd();

 		glBegin( GL_QUADS );
 		glVertex3f( m_ceil[0].x, m_ceil[0].y, m_ceil[0].z );
 		glVertex3f( m_ceil[1].x, m_ceil[1].y, m_ceil[1].z ) ;
 		glVertex3f( m_ceil[2].x, m_ceil[2].y, m_ceil[2].z ); 
 		glVertex3f( m_ceil[3].x, m_ceil[3].y, m_ceil[3].z );
 		glEnd();

		glDisable( GL_BLEND );

		glPopMatrix();

		// drawshadow();
	}

// 	PlanBoundboxAB vgPlanbox::calcuteABbox( float _length, float _width, float _angle )
// 	{
// 		PlanBoundboxAB tempboundbox;
// 		
// 		vgKernel::Vec2 temp[4];
// 
// 		 
// 		rotatevec(temp[0], vgKernel::Vec2( -_length/2,  -_width/2), _angle);
// 		
// 		rotatevec(temp[1] , vgKernel::Vec2(  _length/2,  -_width/2), _angle);
// 		 
// 		rotatevec(temp[2], vgKernel::Vec2( _length/2, _width/2), _angle);
// 		
// 		rotatevec(temp[3] ,vgKernel::Vec2( -_length/2, _width/2), _angle);
// 
// 		for (int i =0 ; i < 4; i++)
// 		{
// 			tempboundbox.merge( temp[i] );
// 		}	
// 
// 		return tempboundbox;
// 	}

	void vgPlanbox::drawshadow()
	{
		if (mShadowVolume >= 0)
		{
			glCallList( mShadowVolume );
		}
	}

	vgPlanbox::~vgPlanbox()
	{
		if (pVert != NULL )
		{
			delete[] pVert;
			pVert = NULL;
		}
		if (pNormalOfFaces != NULL)
		{
			delete[] pNormalOfFaces;
			pNormalOfFaces = NULL;
		}
		if (pShadowFaces != NULL)
		{
			delete[] pShadowFaces;
			pShadowFaces = NULL;
		}
	}

	vgPlanbuild * vgPlanbox::clone()
	{
		vgPlanbox *pp = new vgPlanbox();

		pp->setangle( _angle );
		pp->setcolor(_color );
		pp->setlayerheight( _layerheight );
		pp->setlength( _length );
		pp->setwidth( _width);

		return pp;
	}

	void vgPlanbox::setupposition( vgKernel::Vec3 &pos , int laynum)
	{
		setupBoxData( pos, _length,
			
			_width, _layerheight * laynum , _angle);
	}

	// Renderer 相关代码
	void vgPlanbox::moveTo(const float& x, const float& y, const float& z)
	{
// 		vgKernel::Vec3 pos(x, y, z);
// 		pos.z = -pos.z;
// 
// 		setupboxdata( pos, m_length, m_width, m_height,  m_angle);
		if (! vgPlanManager::getSingleton().getEditMode())
		{
			return ;
		}

		translate(x-getPosition().x, y-getPosition().y, z-getPosition().z);
	}

	void vgPlanbox::moveTo( const vgKernel::Vec3& newpos )
	{
		// moveTo(newpos.x, newpos.y, newpos.z);
		if (! vgPlanManager::getSingleton().getEditMode())
		{
			return ;
		}
		
		translate(newpos.x-getPosition().x, newpos.y-getPosition().y, newpos.z-getPosition().z);
	}

	void vgPlanbox::translate(const float& x, const float& y, const float& z)
	{
// 		m_pos.x += x;
// 		m_pos.y += y;
// 		m_pos.z += z;
// 
// 		moveTo(m_pos.x, m_pos.y, m_pos.z);

		if (! vgPlanManager::getSingleton().getEditMode())
		{
			return ;
		}

		vgKernel::Mat4 tran;
		vgKernel::Mat4 tmp;

		vgKernel::Math::createTranslationMatrix(x, y, z, tran);
		vgKernel::Math::multiplyMatrix(tran, m_matrix, tmp);
		m_matrix = tmp;

		//TRACE("translate Matrix \n")

		m_dynamicBox = m_staticBox;
		m_dynamicBox.matrixTranslation(m_matrix);
		
		// 没增加界面，暂时不显示
		this->notifyOberversOnEvent(VG_OBS_PROPCHANGED, NULL);
	}

	void vgPlanbox::rotate(const float& angle, const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z)
	{
		if (! vgPlanManager::getSingleton().getEditMode())
		{
			return ;
		}

		vgKernel::Mat4 tran;
		vgKernel::Mat4 tmp;

		vgKernel::Math::createTranslationMatrix(-cx, -cy, -cz, tran);
		vgKernel::Math::multiplyMatrix(tran, m_matrix, tmp);
		m_matrix = tmp;

		vgKernel::Math::createRotationMatrix(angle, x, y, z, tran);
		vgKernel::Math::multiplyMatrix(tran, m_matrix, tmp);
		m_matrix = tmp;

		vgKernel::Math::createTranslationMatrix(cx, cy,cz, tran);
		vgKernel::Math::multiplyMatrix(tran, m_matrix, tmp);
		m_matrix = tmp;

		m_dynamicBox = m_staticBox;
		m_dynamicBox.matrixTranslation(m_matrix);

		return ;
	}

	void vgPlanbox::rotateSelf(const float& angle, const float& x, const float& y, const float& z)
	{
		if (! vgPlanManager::getSingleton().getEditMode())
		{
			return ;
		}

		vgKernel::Mat4 tran;
		vgKernel::Mat4 tmp;

		vgKernel::Math::createTranslationMatrix(-m_dynamicBox.getCenter().x, -m_dynamicBox.getCenter().y, -m_dynamicBox.getCenter().z, tran);
		vgKernel::Math::multiplyMatrix(tran, m_matrix, tmp);
		m_matrix = tmp;

		vgKernel::Math::createRotationMatrix(angle, x, y, z, tran);
		vgKernel::Math::multiplyMatrix(tran, m_matrix, tmp);
		m_matrix = tmp;

		vgKernel::Math::createTranslationMatrix(m_dynamicBox.getCenter().x, m_dynamicBox.getCenter().y, m_dynamicBox.getCenter().z, tran);
		vgKernel::Math::multiplyMatrix(tran, m_matrix, tmp);
		m_matrix = tmp;

		m_dynamicBox = m_staticBox;
		m_dynamicBox.matrixTranslation(m_matrix);

		return ;
	}

	std::pair<bool, float> vgPlanbox::testIntersectWithTriangles( const vgKernel::Ray& ray )
	{
		if (vgPlanManager::getSingleton().getEditMode())
		{
			return vgKernel::Math::intersects( ray , getBoundingBox() );
		}
		else
		{
			return std::pair<bool, float>(false, 1e10);
		}
	}

	void vgPlanbox::attachToTerrain()
	{
		vgKernel::Vec3 pos = m_dynamicBox.getCenter();

		float elevation;

		//vgTerritory::TerrainManager::getSingleton().getElevationByPosition(pos, elevation, true);
		VGK_DLL_RUN_CLASSFUNC( VGT_DLL_NAME , TerrainManager,
			getElevationByPosition )( pos, elevation, true);

		elevation = elevation + m_dynamicBox.getHalfSize().y;
		moveTo(pos.x, elevation, pos.z);
	}

 	void vgPlanbox::turnOnShadowCast( const vgKernel::Vec3& light_dir, bool force_to_load )
 	{
//   		vgCore::QuadtreeSceneManager::getSingleton().m_oCurrentScene.m_LightPosForShadow =
//   			vgCore::Vector3( light_dir.x, light_dir.y, light_dir.z );
//   
		m_sunLightDir = light_dir;
  		__super::turnOnShadowCast( light_dir , force_to_load );
  
  		onsunlightanalysis();
 	}
 
 	void vgPlanbox::onLightDirectionChanged( const vgKernel::Vec3& light_dir )
 	{
//   		vgCore::QuadtreeSceneManager::getSingleton().m_oCurrentScene.m_LightPosForShadow =
//   			vgCore::Vector3( light_dir.x, light_dir.y, light_dir.z );
//   
		m_sunLightDir = light_dir;

  		__super::onLightDirectionChanged( light_dir );
  
  		onsunlightanalysis();
 	}
}



