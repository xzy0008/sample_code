
#include <vgStableHeaders.h>
#include <vgMod/vgObjNodeBaked.h>


#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace vgMod
{

	using namespace vgMath;

	ObjectNodeBaked::ObjectNodeBaked( int nVersionMod /*= VERSION_1*/)
		:ObjFrameNode( nVersionMod)
	{

		pMaterialStruct2		= NULL;
		pVertexElementStruct2	= NULL;
	}//ObjectNodeBaked::ObjectNodeBaked()


	ObjectNodeBaked::~ObjectNodeBaked()
	{

		//vgThreads::ScopedLock locker(NodeAbstract::mCriticalSection);

		//------------------------------------------
		// 父类会负责vbo的释放
		//------------------------------------------
		if ( pMaterialStruct2 != NULL )
		{
			delete[] pMaterialStruct2;
			pMaterialStruct2 = NULL;	
		}

		if ( pVertexElementStruct2 != NULL )
		{
			delete[] pVertexElementStruct2;
			pVertexElementStruct2 = NULL;
		}


	}//ObjectNodeBaked::~ObjectNodeBaked()


	
	//	Part 4 :重载基类的纯虚函数

	void	ObjectNodeBaked::writeMaterialToVG(CFile &fp)
	{
		fp.Write(&m_numOfMat , sizeof(int));
		for (int i= 0 ; i < m_numOfMat ; i++)
		{
			fp.Write(&pMaterialStruct2[i].materialinfo, sizeof(MaterialInfoStruct2)/*-1 */);
			pMaterialStruct2[i].fileoffset = fp.GetPosition();
		}
	}

	void	ObjectNodeBaked::writeVertexToVG(CFile &fp)
	{

		mapVertexBuffer();


		fp.Write(&m_numOfVerts, sizeof(int));
		fp.Write(pVertexElementStruct2 , sizeof(VertexElementStruct2) * m_numOfVerts);


		unmapVertexBuffer();

	}



	void	ObjectNodeBaked::readMaterialFromVG( CFile &fp )
	{
		fp.Read(&m_numOfMat , sizeof(int));
		
		pMaterialStruct2 = new MaterialStruct2 [m_numOfMat];
		
		for (int i= 0 ; i < m_numOfMat ; i++)
		{
			fp.Read(&pMaterialStruct2[i].materialinfo, sizeof(MaterialInfoStruct2)/*-1 */);

			try
			{
				vgCore::TextureManager &mgr = vgCore::TextureManager::getSingleton();

				string aa(pMaterialStruct2[i].materialinfo.strFile);

				//QuadtreeSceneManager &scenemgr = QuadtreeSceneManager::getSingleton();

				pMaterialStruct2[i].pTexture = mgr.getTexturePtr(aa);

				// 2008年3月6日18:30:43 lss 添加
				string bb(pMaterialStruct2[i].materialinfo.strFileBaked );

				pMaterialStruct2[i].pTexture2 = mgr.getTexturePtr(bb);
			}
			catch (vgCore::Exception& e)
			{
				MessageBox( NULL , e.getFullDescription().c_str() ,"载入", MB_OK);
			}
		}
	}

	void	ObjectNodeBaked::readVertexFromVG( CFile &fp )
	{
		fp.Read(&m_numOfVerts, sizeof(int));
		pVertexElementStruct2 = new VertexElementStruct2[m_numOfVerts];
		fp.Read(pVertexElementStruct2 , sizeof(VertexElementStruct2) * m_numOfVerts);

		configureCommonData();
	}
	
	void	ObjectNodeBaked::translateVetexArray( Vector3 offset )
	{
		for (int i =0 ; i < m_numOfVerts ; i++)
		{
			pVertexElementStruct2[i].positionX += offset.x;
			pVertexElementStruct2[i].positionY += offset.y;
			pVertexElementStruct2[i].positionZ += offset.z;
		}
	}

	void	ObjectNodeBaked::rotateVetexArray( short axis, float angle ,Vector3 centerVec  )
	{
		for(int i =0 ; i < m_numOfVerts ; i++)
		{
			switch(axis)
			{
			case 0:
				RotatePoint(centerVec.y, centerVec.z, angle, 
					&pVertexElementStruct2[i].positionY, &pVertexElementStruct2[i].positionZ);
				break;

			case 1:
				RotatePoint(centerVec.z, centerVec.x, angle, 
					&pVertexElementStruct2[i].positionZ, &pVertexElementStruct2[i].positionX);
				break;

			default:
				RotatePoint(centerVec.x, centerVec.y, angle, 
					&pVertexElementStruct2[i].positionX, &pVertexElementStruct2[i].positionY);
				break;
			}//switch(axis)
		}//for(m_numOfVerts)	
	}

	void	ObjectNodeBaked::scaleVetexArray( Vector3 scale , Vector3 centerVec )
	{
		//Vector3		centerVec(m_BoundryBox.getCenter());
		for (int i =0 ; i < m_numOfVerts ; i++)
		{
			Vector3		tempVec(pVertexElementStruct2[i].positionX, 
				pVertexElementStruct2[i].positionY, 
				pVertexElementStruct2[i].positionZ );

			tempVec		-= centerVec;
			tempVec		*= scale;
			tempVec		+= centerVec;

			pVertexElementStruct2[i].positionX = tempVec.x;
			pVertexElementStruct2[i].positionY = tempVec.y;
			pVertexElementStruct2[i].positionZ = tempVec.z;
		}
	}



	
	//	接口testIntersection的底层执行细节
	Vector3	ObjectNodeBaked::getVertexElementPosition(int i)
	{
		Vector3	tempVec(pVertexElementStruct2[i].positionX, 
			pVertexElementStruct2[i].positionY, 
			pVertexElementStruct2[i].positionZ );
		return	tempVec;
	}


	
	
	//	Part 5 :重载父类的虚函数
	
	void	ObjectNodeBaked::configureCommonData()
	{
		TYPE					= VG_OBJECT_BAKED;

		m_nVertexStride				= sizeof(VertexElementStruct2);	
		m_nOffsetForNormals			= sizeof(GLfloat) * 2;
		m_nOffsetForVertices		= sizeof(GLfloat) * 5;
		m_nOffsetForTexCoorForLit	= sizeof(GLfloat) * 8;
	}
	
	void	ObjectNodeBaked::renderToDisplaylistOnce()
	{
		unsigned int m_nVertexStride = sizeof(VertexElementStruct2);

		if ( m_isVisible == true )
		{
			glPushMatrix();

			for (int i = 0; i < m_numOfMat; i++)
			{
				if(m_RenderTypeInt == 1)
				{
					glEnable(GL_ALPHA_TEST);

					glAlphaFunc(GL_GREATER, 0);

					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

					glEnable(GL_BLEND);

				}

				glDisable(GL_BLEND);
				// 绑定纹理
				glActiveTexture( GL_TEXTURE0 );

				if ( pMatRender[i].b_hastexture ==  true)
				{
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);	
				}
				else
					glColor4f (float(pMaterialStruct2[i].materialinfo.color[0]) / 255 ,
					float(pMaterialStruct2[i].materialinfo.color[1]) / 255, 
					float(pMaterialStruct2[i].materialinfo.color[2])/255,
					1.0f );

				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

				glEnable(GL_TEXTURE_2D);

				pMaterialStruct2[i].pTexture->useBind();

				glActiveTexture( GL_TEXTURE1 );

				if ( pMatRender[i].b_hastexture ==  true)
				{
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);	
				}
				else
					glColor4f (float(pMaterialStruct2[i].materialinfo.color[0]) / 255 ,
					float(pMaterialStruct2[i].materialinfo.color[1]) / 255, 
					float(pMaterialStruct2[i].materialinfo.color[2])/255,
					1.0f );


				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

				glEnable/*glDisable*/(GL_TEXTURE_2D);

				pMaterialStruct2[i].pTexture2->useBind();

				// 顶点指定
				glEnableClientState( GL_VERTEX_ARRAY);
				glEnableClientState( GL_NORMAL_ARRAY);
				glEnableClientState( GL_TEXTURE_COORD_ARRAY);

				glVertexPointer( 3, GL_FLOAT, m_nVertexStride, &pVertexElementStruct2[0].positionX );

				glNormalPointer(  GL_FLOAT, m_nVertexStride, &pVertexElementStruct2[0].normalX );


				glClientActiveTexture( GL_TEXTURE0 );

				glTexCoordPointer( 2, GL_FLOAT, m_nVertexStride, &pVertexElementStruct2[0].texCoorS );

				glClientActiveTexture( GL_TEXTURE1 );

				glTexCoordPointer( 2, GL_FLOAT, m_nVertexStride, &pVertexElementStruct2[0].texCoorUForLit );


				glDrawElements(GL_TRIANGLES, pMatRender[i].m_numOfFace * 3,
					GL_UNSIGNED_INT,pMatRender[i].pFace);


				glActiveTexture( GL_TEXTURE0 );

				glDisable(GL_TEXTURE_2D);

				glActiveTexture( GL_TEXTURE1 );

				glDisable(GL_TEXTURE_2D);

				if (m_RenderTypeInt == 1)
				{
					glDisable(GL_BLEND);

					glDisable(GL_ALPHA_TEST);
				}

				glDisableClientState( GL_VERTEX_ARRAY);
				glDisableClientState( GL_NORMAL_ARRAY);
				glDisableClientState( GL_TEXTURE_COORD_ARRAY);

			}// 含材质的所有渲染接口

			if (m_numOfNoMat != 0)
			{// 无材质面的渲染
				glDisable(GL_TEXTURE_2D);
				glColor3f(0.5, 0.5, 0.5);
				//glInterleavedArrays(GL_T2F_N3F_V3F, 0 , pVertex);			

				glEnableClientState( GL_VERTEX_ARRAY);

				glVertexPointer( 3, GL_FLOAT, m_nVertexStride, &pVertexElementStruct2[0].positionX );

				glDrawElements(GL_TRIANGLES, m_numOfNoMat * 3,
					GL_UNSIGNED_INT,pFaceNoMat);

				glDisableClientState( GL_VERTEX_ARRAY);

			}

			glPopMatrix();
		}//if (m_isVisable)
	}


	void	ObjectNodeBaked::sendVetexToVBOOnce()
	{
		int nArrayObjectSize = m_nVertexStride * m_numOfVerts;
		int nParam_ArrayObjectSize = 0;

		if ( nArrayObjectSize != 0 )
		{		
			glGenBuffersARB( 1, &_vertexBufferObjectID );
			glBindBufferARB( GL_ARRAY_BUFFER_ARB, _vertexBufferObjectID );
			glBufferDataARB( GL_ARRAY_BUFFER_ARB, nArrayObjectSize, pVertexElementStruct2, GL_STATIC_DRAW_ARB );

			glGetBufferParameterivARB( GL_ARRAY_BUFFER_ARB, GL_BUFFER_SIZE_ARB, &nParam_ArrayObjectSize );

			if( nParam_ArrayObjectSize <= 0 )
			{
				assert(0);
				::MessageBox(NULL,"glBufferDataARB failed to allocate any memory!",
					"ERROR",MB_OK|MB_ICONEXCLAMATION);
			}

#if _DEBUG
			VG_CHECK_OPENGL_ERROR();
#endif
		}//if ( nArrayObjectSize != 0 )

	}

	
	void	ObjectNodeBaked::clearUnvboDataExtra()
	{
		if ( pVertexElementStruct2 != NULL )
		{
			delete[] pVertexElementStruct2;
			pVertexElementStruct2 = NULL;
		}
	}

	
	void	ObjectNodeBaked::mapVertexBuffer()
	{
		if ( _vertexBufferObjectID == -1 )
		{
			return;
		}

		GLvoid *vertexbuf = NULL;
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, _vertexBufferObjectID );
		vertexbuf = glMapBufferARB(GL_ARRAY_BUFFER_ARB , GL_READ_WRITE_ARB);
		assert( vertexbuf != NULL) ;

#	if _DEBUG
		VG_CHECK_OPENGL_ERROR();
#	endif

		pVertexElementStruct2 = (VertexElementStruct2*)vertexbuf;
	}

	
	void	ObjectNodeBaked::unmapVertexBuffer()
	{
		if ( _vertexBufferObjectID == -1 )
		{
			return;
		}

#	if _DEBUG
		VG_CHECK_OPENGL_ERROR();
#	endif

		glUnmapBufferARB(GL_ARRAY_BUFFER_ARB);
		pVertexElementStruct2 = NULL;

		glBindBufferARB( GL_ARRAY_BUFFER_ARB, NULL );

#	if _DEBUG
		VG_CHECK_OPENGL_ERROR();
#	endif
	}


	void	ObjectNodeBaked::assignTexture(int i )
	{
		//特效优先级，淡入淡出>闪烁>颜色可编辑
		if (isColorable())
		{
			// 材质1（TEXTURE0）
			glActiveTexture( GL_TEXTURE0 );

			glColor4f(	getRgbaQuadRef()->red / 255.0f, 
						getRgbaQuadRef()->green / 255.0f , 
						getRgbaQuadRef()->blue / 255.0f,
						getDissolveAlpha());

			float ratio = getRgbaQuadRef()->alpha / 255.0f;

			float arg[4] = { ratio, ratio, ratio , ratio };

			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
			glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_INTERPOLATE);
			glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_PRIMARY_COLOR);
			glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);
			glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB, GL_TEXTURE);
			glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB, GL_SRC_COLOR);
			glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE2_RGB, GL_CONSTANT);
			glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND2_RGB, GL_SRC_COLOR);
			glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, arg);

			glEnable( GL_TEXTURE_2D );

			if ( pMaterialStruct2[i].pTexture.isNull() == false )
			{
				pMaterialStruct2[i].pTexture->useBind();
			}

			glClientActiveTexture( GL_TEXTURE0 );
			glEnableClientState( GL_TEXTURE_COORD_ARRAY );
			glEnableClientState( GL_NORMAL_ARRAY );
			glEnableClientState( GL_VERTEX_ARRAY );
			glEnableClientState( GL_INDEX_ARRAY );		

			glTexCoordPointer( 2, GL_FLOAT, m_nVertexStride, BUFFER_OFFSET(0) );

		}
		else//颜色不可编辑
		{
			// 材质1（TEXTURE0）
			glActiveTexture( GL_TEXTURE0 );
			glColor4f(1.0f, 1.0f, 1.0f, getDissolveAlpha());
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

			glEnable( GL_TEXTURE_2D );

			if ( pMaterialStruct2[i].pTexture.isNull() == false )
			{
				pMaterialStruct2[i].pTexture->useBind();
			}

			glClientActiveTexture( GL_TEXTURE0 );
			glEnableClientState( GL_TEXTURE_COORD_ARRAY );
			glEnableClientState( GL_NORMAL_ARRAY );
			glEnableClientState( GL_VERTEX_ARRAY );
			glEnableClientState( GL_INDEX_ARRAY );		

			glTexCoordPointer( 2, GL_FLOAT, m_nVertexStride, BUFFER_OFFSET(0) );

		}

		if (isFlickered())
		{
			// 材质1（TEXTURE0）
			glActiveTexture( GL_TEXTURE0 );

			glColor4f(	getCurrentColor().red / 255.0f, 
				getCurrentColor().green / 255.0f , 
				getCurrentColor().blue / 255.0f,
				getDissolveAlpha());

			float ratio = getCurrentColor().alpha / 255.0f;

			float arg[4] = { ratio, ratio, ratio , ratio };

			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
			glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_INTERPOLATE);
			glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_PRIMARY_COLOR);
			glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);
			glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB, GL_TEXTURE);
			glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB, GL_SRC_COLOR);
			glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE2_RGB, GL_CONSTANT);
			glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND2_RGB, GL_SRC_COLOR);
			glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, arg);

			glEnable( GL_TEXTURE_2D );

			if ( pMaterialStruct2[i].pTexture.isNull() == false )
			{
				pMaterialStruct2[i].pTexture->useBind();
			}

			glClientActiveTexture( GL_TEXTURE0 );
			glEnableClientState( GL_TEXTURE_COORD_ARRAY );
			glEnableClientState( GL_NORMAL_ARRAY );
			glEnableClientState( GL_VERTEX_ARRAY );
			glEnableClientState( GL_INDEX_ARRAY );		

			glTexCoordPointer( 2, GL_FLOAT, m_nVertexStride, BUFFER_OFFSET(0) );

		}

		// 材质2（TEXTURE1）
		glActiveTexture( GL_TEXTURE1 );
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
		glEnable( GL_TEXTURE_2D );

		if ( pMaterialStruct2[i].pTexture2.isNull() == false )
		{
			pMaterialStruct2[i].pTexture2->useBind();
		}

		glClientActiveTexture( GL_TEXTURE1 );
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glEnableClientState( GL_NORMAL_ARRAY );
		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_INDEX_ARRAY );	

		glTexCoordPointer( 2, GL_FLOAT, m_nVertexStride, BUFFER_OFFSET(m_nOffsetForTexCoorForLit) );

	}


	void	ObjectNodeBaked::resetTexture()
	{
		glClientActiveTexture( GL_TEXTURE1 );
		glDisableClientState( GL_TEXTURE_COORD_ARRAY );
		glDisableClientState( GL_NORMAL_ARRAY );
		glDisableClientState( GL_VERTEX_ARRAY );
		glDisableClientState( GL_INDEX_ARRAY );

		glClientActiveTexture( GL_TEXTURE0 );
		glDisableClientState( GL_TEXTURE_COORD_ARRAY );
		glDisableClientState( GL_NORMAL_ARRAY );
		glDisableClientState( GL_VERTEX_ARRAY );
		glDisableClientState( GL_INDEX_ARRAY );

		glActiveTexture( GL_TEXTURE1 );
		glDisable(GL_TEXTURE_2D);
		glActiveTexture( GL_TEXTURE0 );
		glDisable(GL_TEXTURE_2D);
	}


	void	ObjectNodeBaked::assignColor(int i)
	{
			glColor3f(	float(pMaterialStruct2[i].materialinfo.color[0]) / 255 ,
						float(pMaterialStruct2[i].materialinfo.color[1]) / 255 , 
						float(pMaterialStruct2[i].materialinfo.color[2]) / 255	);
	}
	
	
	long	ObjectNodeBaked::readMaterial(char *pBytes)
	{
		long	posRelative	= 0;
		m_numOfMat = *(int *) (pBytes + posRelative);
		posRelative += sizeof(int);

		pMaterialStruct2 = new MaterialStruct2 [m_numOfMat];
		for (int	i = 0; i <m_numOfMat ; i++)
		{
			//pMaterialStruct2[i].materialinfo =  *(MaterialInfoStruct2 *)(data + posRelative);
			memcpy(&pMaterialStruct2[i].materialinfo, /*sizeof(MaterialInfoStruct2),*/
				pBytes + posRelative, sizeof(MaterialInfoStruct2)/* -1*/);

			try
			{
				vgCore::TextureManager &mgr = vgCore::TextureManager::getSingleton();

				string aa(pMaterialStruct2[i].materialinfo.strFile);

				//QuadtreeSceneManager &scenemgr = QuadtreeSceneManager::getSingleton();

				pMaterialStruct2[i].pTexture = mgr.getTexturePtr(aa);
				
				// 2008年3月6日18:30:43 lss 添加
				string bb(pMaterialStruct2[i].materialinfo.strFileBaked );

				pMaterialStruct2[i].pTexture2 = mgr.getTexturePtr(bb);
			}
			catch (vgCore::Exception& e)
			{
				MessageBox( NULL , e.getFullDescription().c_str() ,"载入", MB_OK);
			}

			posRelative += sizeof(MaterialInfoStruct2)/* - 1*/;
		}
		return	posRelative;
	}//readMaterial


	long	ObjectNodeBaked::readVetex(char *pBytes)
	{
		long	posRelative	= 0;

		m_numOfVerts = *(int *)(pBytes + posRelative);
		posRelative += sizeof(int);

		pVertexElementStruct2 = new VertexElementStruct2[m_numOfVerts];

		memcpy(pVertexElementStruct2 , pBytes+posRelative , sizeof(VertexElementStruct2) * m_numOfVerts);
		posRelative += sizeof(VertexElementStruct2) * m_numOfVerts;

		return	posRelative;
	}

	bool	ObjectNodeBaked::doLevellingVertexArray( const vgKernel::Polygon2D& polygons , float level_height )
	{
		return false;
#if 0
		vgKernel::Vec2	point2DTemp;
		float	heightChange = 0.0f;

		for (int i =0 ; i < m_numOfVerts ; i++)
		{
			point2DTemp.x = pVertexElementStruct2[i].positionX;
			point2DTemp.y = pVertexElementStruct2[i].positionZ;
			if ( polygons.contains(point2DTemp) )
			{
				//pVertex[i].positionY = level_height;
				heightChange = getHeightChangeFromTerrain(
					vgKernel::Vec3(
					pVertexElementStruct2[i].positionX,
					pVertexElementStruct2[i].positionY,
					pVertexElementStruct2[i].positionZ), level_height);
				pVertexElementStruct2[i].positionY += heightChange;
			}
		}

		return	true;
#endif
	}



	void ObjectNodeBaked::flip( bool x, bool y, bool z )
	{
		if ( !( x | y | z) )
		{
			return;
		}

		mapVertexBuffer();


		for (int i =0 ; i < m_numOfVerts ; i++)
		{
			if (x)
			{
				pVertexElementStruct2[i].positionX *= -1.0f;
			}
			if (y)
			{
				pVertexElementStruct2[i].positionY *= -1.0f;
			}
			if (z)
			{
				pVertexElementStruct2[i].positionZ *= -1.0f;
			}
		}

		for (int i = 0; i < m_numOfVertexs; i++)
		{
			Vector3	factor(x,y,z);
			factor *= -1.0f;
			pVert[i] *= factor;
		}

		unmapVertexBuffer();


		ComputeBoundBox();

		UpdatePos();

		this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);

	}

	bool ObjectNodeBaked::cloneMtlFromObjectNode( ObjectNode* src_node )
	{
		ObjectNodeBaked* src_bakednode = dynamic_cast<ObjectNodeBaked*>(src_node);

		pMaterialStruct2 = new MaterialStruct2 [m_numOfMat];
		for (int	i = 0; i <m_numOfMat ; i++)
		{
			pMaterialStruct2[i].materialinfo =  src_bakednode->pMaterialStruct2[i].materialinfo;
#if 1
			try
			{
				vgCore::TextureManager &mgr = vgCore::TextureManager::getSingleton();

				string aa(pMaterialStruct2[i].materialinfo.strFile);

				//QuadtreeSceneManager &scenemgr = QuadtreeSceneManager::getSingleton();

				pMaterialStruct2[i].pTexture = mgr.getTexturePtr(aa);

				string bb(pMaterialStruct2[i].materialinfo.strFileBaked );

				pMaterialStruct2[i].pTexture2 = mgr.getTexturePtr(bb);
			}
			catch (vgCore::Exception& e)
			{
				MessageBox( NULL , e.getFullDescription().c_str() ,"载入", MB_OK);
			}
#endif
		}

		return true;
	}

	bool ObjectNodeBaked::cloneVertexFromObjectNode( ObjectNode* src_node )
	{
		ObjectNodeBaked* src_bakednode = dynamic_cast<ObjectNodeBaked*>(src_node);

		m_numOfVerts = src_bakednode->m_numOfVerts;

		pVertexElementStruct2 = new VertexElementStruct2[m_numOfVerts];

		memcpy(pVertexElementStruct2 , src_bakednode->pVertexElementStruct2, 
			sizeof(VertexElementStruct2) * m_numOfVerts);

		return true;
	}
}//namespace vgCore

