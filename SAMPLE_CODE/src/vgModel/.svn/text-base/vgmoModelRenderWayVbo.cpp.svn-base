


#include <vgStableHeaders.h>
#include <vgModel/vgmoModelRenderWayVertexArray.h>
#include <vgModel/vgmoModelRenderWayVbo.h>
#include <vgModel/vgmoFileDefinitionMod.h>
#include <vgImage/vgiTextureManager.h>
#include <vgKernel/vgkOpenGLSupport.h>

#include <vgKernel/vgkMath.h>
#include <vgKernel/vgkIntersectSegment3Triangle3.h>
#include <vgModel/vgmoKeyFrameControl.h>

namespace vgModel {
	
#define BUFFER_OFFSET(i) ((char *)NULL + (i))


	//----------------------------------------------------------------
	ModelRenderWayVbo::ModelRenderWayVbo( 
		ModelRenderWayVertexArray* vertexarray )
	{
		_shadowVolume = 0;

		_shadowNumberOfFaces = 0;
		_shadowNormalOfFaces = NULL;
		_shadowNumberOfVertices = 0;
		_shadowVerticesOfFaces = NULL;
		_shadowIndicesOfFaces = NULL;
		_keyframeCtrl =NULL;


		assert( vertexarray != NULL );
		_numberOfMetaFaces = 0;
		_metaFaces = NULL;
		_vertexBufferObjectID = VG_NULL_VBO_ID;

		_preLod = VGLOD_COARSE;

		_layersOfTexture = 0;

		_texMgr = vgImage::TextureManager::getSingletonPtr();
		assert( _texMgr != NULL );

		//------------------------------------------
		// 1.首先初始化必要的变量
		//------------------------------------------
		assert( vertexarray != NULL );
		_numberOfMetaFaces = vertexarray->_numberOfMetaFaces;
		assert( _numberOfMetaFaces > 0 );

		_renderType = vertexarray->_renderType;

		_metaFaces = new VboMetaFaceStruct[ _numberOfMetaFaces ];

		for ( int i = 0 ; i < _numberOfMetaFaces ; ++i )
		{
			_metaFaces[i]._numOfElements =
				vertexarray->_metaFaces[i]._numberOfFaceIndex * 3;
		}

		//------------------------------------------
		// 2.其次生成vbo
		//------------------------------------------
		_isReadyForVBORender = generateVbo( vertexarray );

		//------------------------------------------
		// 3.最后复制TextureObserver
		//------------------------------------------
		assert( _layersOfTexture == 0 );
		_layersOfTexture = vertexarray->_layersOfTexture;
		assert( _layersOfTexture != 0 );

		for ( int i = 0 ; i < _numberOfMetaFaces ; ++ i )
		{
			VboMetaFaceStruct& curface = _metaFaces[i];
			curface._numberOfTexture = vertexarray->_metaFaces[i]._numberOfTexture;

			assert( curface._texFileName == NULL );
			curface._texFileName = new String[ curface._numberOfTexture ];

			assert( curface._texObserver == NULL );
			curface._texObserver = 
				new TexObsPointer[VGLOD_N * curface._numberOfTexture];

			memset( curface._texObserver , NULL , 
				VGLOD_N * curface._numberOfTexture * sizeof( TexObsPointer ) );

			for ( int k = 0 ; k < curface._numberOfTexture ; ++ k )
			{
				_metaFaces[i]._texFileName[k] = 
					vertexarray->_metaFaces[i]._texFileName[k];
			}

			for ( int j = 0 ; j < VGLOD_N * curface._numberOfTexture; ++ j )
			{
				_metaFaces[i]._texObserver[j] = vertexarray->_metaFaces[i]._texObserver[j];
				if ( _metaFaces[i]._texObserver[j] != NULL )
				{
					_metaFaces[i]._texObserver[j]->addRef();
				}
			}
		}

		//------------------------------------------
		// 4.dataplus
		//------------------------------------------
		_shadowNumberOfFaces = vertexarray->_shadowNumberOfFaces;
		assert( _shadowNumberOfFaces > 0 );

		_shadowNormalOfFaces = new vgKernel::Vec3[_shadowNumberOfFaces];
		memcpy( _shadowNormalOfFaces, vertexarray->_shadowNormalOfFaces,
			sizeof( vgKernel::Vec3 ) * _shadowNumberOfFaces );

		_shadowNumberOfVertices = vertexarray->_shadowNumberOfVertices;

		_shadowVerticesOfFaces = new vgKernel::Vec3[_shadowNumberOfVertices];
		memcpy( _shadowVerticesOfFaces, vertexarray->_shadowVerticesOfFaces,
			sizeof( vgKernel::Vec3 ) * _shadowNumberOfVertices );


		_shadowIndicesOfFaces = new ShadowFaceIndex[_shadowNumberOfFaces];
		memcpy( _shadowIndicesOfFaces, vertexarray->_shadowIndicesOfFaces,
			sizeof( ShadowFaceIndex) * _shadowNumberOfFaces );


		if ( vertexarray->getKeyFrameControlRef() != NULL )
		{
			setKeyFrameControl( vertexarray->getKeyFrameControlRef()->createCopy() );
		}

	}
	//----------------------------------------------------------------
	ModelRenderWayVbo::~ModelRenderWayVbo()
	{
		turnOffShadowImpl();

		if ( _keyframeCtrl != NULL )
		{
			delete _keyframeCtrl;
			_keyframeCtrl = NULL;
		}

		if ( _shadowNormalOfFaces != NULL )
		{
			delete[] _shadowNormalOfFaces;
			_shadowNormalOfFaces = NULL;
		}

		if ( _shadowVerticesOfFaces != NULL )
		{
			delete[] _shadowVerticesOfFaces;
			_shadowVerticesOfFaces = NULL;
		}

		if ( _shadowIndicesOfFaces != NULL )
		{
			delete[] _shadowIndicesOfFaces;
			_shadowIndicesOfFaces = NULL;
		}

		if ( _isReadyForVBORender == false )
		{
			return;
		}

		if ( _vertexBufferObjectID != VG_NULL_VBO_ID )
		{
			glDeleteBuffersARB( 1, &_vertexBufferObjectID ); 
			_vertexBufferObjectID = VG_NULL_VBO_ID;
		}

		if ( _metaFaces != NULL )
		{
			assert( _numberOfMetaFaces > 0 );

			for ( int i = 0 ; i < _numberOfMetaFaces ; ++i )
			{
				if ( _metaFaces[i]._elementBufferObjectID != VG_NULL_VBO_ID )
				{
					glDeleteBuffersARB( 1, &_metaFaces[i]._elementBufferObjectID ); 
					_metaFaces[i]._elementBufferObjectID = VG_NULL_VBO_ID;
				}
			}

			delete[] _metaFaces;
			_metaFaces = NULL;
		}

	}
	
	//----------------------------------------------------------------
	bool ModelRenderWayVbo::generateVbo( 
		ModelRenderWayVertexArray* vertexarray )
	{
		assert( _metaFaces != NULL );

		assert( vertexarray != NULL );
		if ( vertexarray == NULL ||
			vertexarray->_wholeChunkOfData == NULL )
		{
			return false;
		}

#if _DEBUG
		VGK_CHECK_OPENGL_ERROR();
#endif

		//------------------------------------------
		// 1. create vertex buffer
		//------------------------------------------
		int nArrayObjectSize = vertexarray->_sizeOfVertexElements * 
			vertexarray->_numberOfVertexElements;

		int nParam_ArrayObjectSize = 0;

		if ( nArrayObjectSize != 0 )
		{		
			assert( _vertexBufferObjectID == VG_NULL_VBO_ID );

			glGenBuffersARB( 1, &_vertexBufferObjectID );
			glBindBufferARB( GL_ARRAY_BUFFER_ARB, _vertexBufferObjectID );
			glBufferDataARB( GL_ARRAY_BUFFER_ARB, nArrayObjectSize, 
				vertexarray->_vertexElements, GL_STATIC_DRAW_ARB );

			glGetBufferParameterivARB( GL_ARRAY_BUFFER_ARB, GL_BUFFER_SIZE_ARB, 
				&nParam_ArrayObjectSize );

			if( nParam_ArrayObjectSize <= 0 )
			{
				assert(0);
				::MessageBox(NULL,"glBufferDataARB failed to allocate any memory!",
					"ERROR",MB_OK|MB_ICONEXCLAMATION);
			}

#if _DEBUG
			VGK_CHECK_OPENGL_ERROR();
#endif
		}
		
		//------------------------------------------
		// 2.create element buffer
		//------------------------------------------
		for ( int i = 0; i < _numberOfMetaFaces ; ++i )
		{
			int nArrayObjectSize = sizeof(VmdFaceIndex) * vertexarray->_metaFaces[i]._numberOfFaceIndex;
			int nParam_ArrayObjectSize = 0;

			if ( nArrayObjectSize != 0 )
			{
				assert( _metaFaces[i]._elementBufferObjectID == VG_NULL_VBO_ID );

				glGenBuffersARB( 1, &_metaFaces[i]._elementBufferObjectID );
				glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, _metaFaces[i]._elementBufferObjectID );
				glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, nArrayObjectSize, 
					vertexarray->_metaFaces[i]._faceIndex, GL_STATIC_DRAW_ARB );

				glGetBufferParameterivARB( GL_ELEMENT_ARRAY_BUFFER_ARB, GL_BUFFER_SIZE_ARB, &nParam_ArrayObjectSize );

				if( nParam_ArrayObjectSize <= 0 )
				{
					assert(0);
					MessageBox(NULL,"glBufferDataARB failed to allocate any memory!",
						"ERROR",MB_OK|MB_ICONEXCLAMATION);
				}
			}
#if _DEBUG
			VGK_CHECK_OPENGL_ERROR();
#endif
		}

		return true;
	}
	//----------------------------------------------------------------
	//----------------------------------------------------------------
	void ModelRenderWayVbo::render(const int& lod, int force_render_in_num_layers,
		RgbaQuad* colorval )
	{
		if ( _isReadyForVBORender == false)
		{ 
			return;
		}

		requireTexObserverByLod( lod );

		assert( _vertexBufferObjectID !=VG_NULL_VBO_ID );

		if ( _keyframeCtrl != NULL )
		{
			_keyframeCtrl->multKeyFrameMatrix();
		}


		if(  _renderType == 1 || _renderType == 2 )
		{
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.5f);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
		}
		else
		{
			glDisable( GL_ALPHA_TEST );
			glDisable( GL_BLEND );
		}

		if ( _isTransparent )
		{
			glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
			glEnable(GL_BLEND);	
			glDisable(GL_DEPTH_TEST);
		}

		if ( colorval->alpha == 0 )
		{
			glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
			glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );	
		}
		else
		{
			//------------------------------------------
			// 开始混合颜色
			//------------------------------------------
			float ratio = colorval->alpha / 255.0f;

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

			glColor3f(	colorval->red / 255.0f, 
				colorval->green / 255.0f , 
				colorval->blue / 255.0f );
		}


		if ( _layersOfTexture == 1 )
		{
			renderInOneLayer();
		}
		else if ( _layersOfTexture == 2 )
		{
			if ( force_render_in_num_layers == 1 )
			{
				VGK_CHECK_OPENGL_ERROR();
				renderTwoLayerInOneLayer();
				VGK_CHECK_OPENGL_ERROR();
			}
			else
			{
				VGK_CHECK_OPENGL_ERROR();
				renderInTwoLayer();
				VGK_CHECK_OPENGL_ERROR();
			}
		}
		else
		{
			assert(0);
		}

		if ( _isTransparent )
		{
			glDisable(GL_BLEND);	
			glEnable(GL_DEPTH_TEST);
		}

		if(  _renderType == 1 || _renderType == 2 )
		{
			glDisable( GL_ALPHA_TEST );
			glDisable( GL_BLEND );
		}

	}
	//----------------------------------------------------------------
	void ModelRenderWayVbo::requireTexObserverByLod( const int& lod )
	{
		assert( lod <= VGLOD_CLEAR );
		assert( lod >= VGLOD_COARSE );

		if ( _preLod == lod )
		{
			return;
		}

		//------------------------------------------
		// 当lod有变化时,更新
		//------------------------------------------
		_preLod = lod;

		if ( lod == VGLOD_COARSE )
		{
			//------------------------------------------
			// 当为最不清晰的一层时,
			// 卸载其他级即可.
			//------------------------------------------
			for ( int i = 0 ; i < _numberOfMetaFaces ; ++i )
			{
				TexObsPointer*& observers = _metaFaces[i]._texObserver;
				const int& texNum = _metaFaces[i]._numberOfTexture;
				//const int& texNum = 1;

				for ( int j = 0 ; j < texNum * VGLOD_N; j+= VGLOD_N)
				{
					if ( observers[ VGLOD_COARSE + j ] == NULL )
					{
						continue;
					}

					for ( int k = 1 + j; k < VGLOD_N + j; ++ k )
					{
						if ( observers[k] != NULL )
						{
							observers[k]->releaseRef();
							observers[k] = NULL;
						}
					}
				}
			}// end for i
		}
		else if ( lod == VGLOD_CLEAR )
		{
			//------------------------------------------
			// 当为最清晰的一级时,只要确认
			// Clearest Observer 载入即可
			//------------------------------------------
			for ( int i = 0 ; i < _numberOfMetaFaces ; ++i )
			{
				TexObsPointer*& observers = _metaFaces[i]._texObserver;
				const int& texNum = _metaFaces[i]._numberOfTexture;
				//const int& texNum = 1;

				for ( int j = 0 ; j < texNum * VGLOD_N; j+= VGLOD_N)
				{
					if ( observers[ VGLOD_COARSE + j] == NULL )
					{
						continue;
					}

					if ( observers[ VGLOD_CLEAR + j] == NULL )
					{
						observers[ VGLOD_CLEAR + j]  = _texMgr->getTextureObserver(
							_metaFaces[i]._texFileName[j/VGLOD_N] , VGLOD_CLEAR );

						// coarest都得到了,那么最清晰的一级肯定也能得到.
						assert( observers[ VGLOD_CLEAR + j] != NULL );

						observers[ VGLOD_CLEAR + j]->addRef();
					}
					else
					{
						// 在最清晰一级已经载入的情况下,卸载第二级
						if ( observers[ VGLOD_COARSE + 1 + j] != NULL )
						{
							observers[ VGLOD_COARSE + 1 + j]->releaseRef();
							observers[ VGLOD_COARSE + 1 + j] = NULL;
						}
					}
				}
			} // end for
		}
		else
		{

			//------------------------------------------
			// 当为中间的一级时
			//------------------------------------------
			for ( int i = 0 ; i < _numberOfMetaFaces ; ++i )
			{
				TexObsPointer*& observers = _metaFaces[i]._texObserver;
				const int& texNum = _metaFaces[i]._numberOfTexture;
				//const int& texNum = 1;

				for ( int j = 0 ; j < texNum * VGLOD_N; j+= VGLOD_N)
				{
					if ( observers[ VGLOD_COARSE + j] == NULL )
					{
						continue;
					}

					// 检查最清晰的是否已经载入
					if ( observers[ VGLOD_CLEAR + j] != NULL &&
						observers[ VGLOD_COARSE + 1 + j] != NULL)
					{
						observers[ VGLOD_CLEAR + j]->releaseRef();
						observers[ VGLOD_CLEAR + j] = NULL;

					}
					//else if ( observers[ VGLOD_CLEAR ] != NULL && 
					//	observers[ VGLOD_COARSE + 1 ] == NULL )
					//{
					//	// do nothing.
					//}
					else if ( observers[ VGLOD_COARSE + 1 + j] == NULL )
					{
						// 检查中间级,没载入的话,将其载入.
						observers[ VGLOD_COARSE + 1 + j] = _texMgr->getTextureObserver(
							_metaFaces[i]._texFileName[j/VGLOD_N] , VGLOD_COARSE + 1 );

						assert( observers[ VGLOD_COARSE + 1 + j] != NULL );
						observers[ VGLOD_COARSE + 1 + j]->addRef();
					}

				}
			}
		}


		return;
	}
	//----------------------------------------------------------------
	bool ModelRenderWayVbo::initialiseInMainThread()
	{
		//------------------------------------------
		// 上面的生成vbo的操作其实可以放到这里
		//------------------------------------------
		return true;
	}
	//----------------------------------------------------------------
	void ModelRenderWayVbo::renderInOneLayer()
	{
		glPushMatrix();



		assert( _vertexBufferObjectID != VG_NULL_VBO_ID );

		glBindBufferARB( GL_ARRAY_BUFFER_ARB, _vertexBufferObjectID );

		for ( int i = 0 ; i < _numberOfMetaFaces ; ++i )
		{
			// 由于useBind会自动搜索最清晰的一级,所以只要
			// 关心最不清晰一级的observer即可.
			vgImage::TextureObserver*& cur_tex = 
				_metaFaces[i]._texObserver[ VGLOD_COARSE ];

			if ( cur_tex != NULL )
			{
				if ( cur_tex->isEmptyTexture() == true )
				{
					continue;
				}
				glEnable( GL_TEXTURE_2D );
				cur_tex->useBind();
			}
			else
			{
				glDisable( GL_TEXTURE_2D );
			}

			//glColor3f(1, 1, 1);	
			//glColor3f(0.8f, 0.8f, 0.8f);	


			assert( _metaFaces[i]._elementBufferObjectID != VG_NULL_VBO_ID);
			glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, 
				_metaFaces[i]._elementBufferObjectID );

			const int nVertexStride = sizeof(VertexElementStruct);
			const int nIndexStride = sizeof(GLubyte);
			const int nOffsetForNormals = sizeof(GLfloat) * 2;
			const int nOffsetForVertices = sizeof(GLfloat) * 5;

			glTexCoordPointer( 2, GL_FLOAT, nVertexStride, BUFFER_OFFSET(0) );
			glNormalPointer( GL_FLOAT, nVertexStride, BUFFER_OFFSET(nOffsetForNormals) );
			glVertexPointer( 3, GL_FLOAT, nVertexStride, BUFFER_OFFSET(nOffsetForVertices) );

			glEnableClientState( GL_TEXTURE_COORD_ARRAY );
			glEnableClientState( GL_NORMAL_ARRAY );
			glEnableClientState( GL_VERTEX_ARRAY );
			glEnableClientState( GL_INDEX_ARRAY );

			//glColor3d(1, 1, 1);	
			//glColor3f(0.8f, 0.8f, 0.8f);	

			glDrawElements( GL_TRIANGLES, 
				_metaFaces[i]._numOfElements , GL_UNSIGNED_INT, 
				BUFFER_OFFSET(0));

			glDisableClientState( GL_TEXTURE_COORD_ARRAY );
			glDisableClientState( GL_NORMAL_ARRAY );
			glDisableClientState( GL_VERTEX_ARRAY );
			glDisableClientState( GL_INDEX_ARRAY );

			glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, NULL );

		}


		glBindBufferARB( GL_ARRAY_BUFFER_ARB, NULL );

		glPopMatrix();
	}
	//----------------------------------------------------------------
	void ModelRenderWayVbo::renderInTwoLayer()
	{
		assert( _layersOfTexture == 2);

		glPushMatrix();

		assert( _vertexBufferObjectID != VG_NULL_VBO_ID );
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, _vertexBufferObjectID );

		for ( int i = 0 ; i < _numberOfMetaFaces ; ++i )
		{
			glActiveTexture( GL_TEXTURE0 );
			//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);	
			//glColor4f(0.8f, 0.8f, 0.8f, 1.0);	
			{
				TexObsPointer& cur_tex = _metaFaces[i]._texObserver[
					VGLOD_COARSE];

					if ( cur_tex != NULL && cur_tex->isEmptyTexture() == false)
					{
						glEnable( GL_TEXTURE_2D );
						cur_tex->useBind();
					}
					else
					{
						glDisable( GL_TEXTURE_2D );
						glActiveTexture( GL_TEXTURE0 );
						glDisable( GL_TEXTURE_2D );
						continue;
					}
			}

			glActiveTexture( GL_TEXTURE1 );
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
			{
				TexObsPointer& cur_tex = _metaFaces[i]._texObserver[
					VGLOD_COARSE  + VGLOD_N ];

					if ( cur_tex != NULL && cur_tex->isEmptyTexture() == false)
					{
						glEnable( GL_TEXTURE_2D );
						cur_tex->useBind();
					}
					else
					{
						glDisable( GL_TEXTURE_2D );
					}
			}


			assert( _metaFaces[i]._elementBufferObjectID != VG_NULL_VBO_ID );
			glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, 
				_metaFaces[i]._elementBufferObjectID );

			const int nVertexStride = sizeof(VertexElementStruct2);
			const int nIndexStride = sizeof(GLubyte);
			const int nOffsetForNormals = sizeof(GLfloat) * 2;
			const int nOffsetForVertices = sizeof(GLfloat) * 5;
			const int nOffsetForBake = sizeof( GLfloat ) * 8; 

			glClientActiveTexture( GL_TEXTURE1 );
			glTexCoordPointer( 2, GL_FLOAT, nVertexStride, BUFFER_OFFSET(nOffsetForBake) );
			glVertexPointer( 3, GL_FLOAT, nVertexStride,BUFFER_OFFSET(nOffsetForVertices));
			glNormalPointer(  GL_FLOAT, nVertexStride, BUFFER_OFFSET(nOffsetForNormals));

			glEnableClientState( GL_VERTEX_ARRAY);
			glEnableClientState( GL_NORMAL_ARRAY);
			glEnableClientState( GL_INDEX_ARRAY );
			glEnableClientState( GL_TEXTURE_COORD_ARRAY);	


			glClientActiveTexture( GL_TEXTURE0 );
			glTexCoordPointer( 2, GL_FLOAT, nVertexStride, BUFFER_OFFSET(0) );
			glVertexPointer( 3, GL_FLOAT, nVertexStride,BUFFER_OFFSET(nOffsetForVertices));
			glNormalPointer(  GL_FLOAT, nVertexStride, BUFFER_OFFSET(nOffsetForNormals));
			glEnableClientState( GL_VERTEX_ARRAY);
			glEnableClientState( GL_NORMAL_ARRAY);
			glEnableClientState( GL_INDEX_ARRAY );
			glEnableClientState( GL_TEXTURE_COORD_ARRAY);	


			glDrawElements( GL_TRIANGLES, 
				_metaFaces[i]._numOfElements , GL_UNSIGNED_INT, 
				BUFFER_OFFSET(0));


			glDisableClientState( GL_NORMAL_ARRAY);
			glDisableClientState( GL_VERTEX_ARRAY);
			glDisableClientState( GL_INDEX_ARRAY );
			glDisableClientState( GL_TEXTURE_COORD_ARRAY);

			glClientActiveTexture( GL_TEXTURE1 );
			glDisableClientState( GL_NORMAL_ARRAY);
			glDisableClientState( GL_VERTEX_ARRAY);
			glDisableClientState( GL_INDEX_ARRAY );
			glDisableClientState( GL_TEXTURE_COORD_ARRAY);

			glClientActiveTexture( GL_TEXTURE0 );
			glDisableClientState( GL_NORMAL_ARRAY);
			glDisableClientState( GL_VERTEX_ARRAY);
			glDisableClientState( GL_INDEX_ARRAY );
			glDisableClientState( GL_TEXTURE_COORD_ARRAY);


			glDisable( GL_TEXTURE_2D );
			glActiveTexture( GL_TEXTURE1 );
			glDisable(GL_TEXTURE_2D);
			glActiveTexture( GL_TEXTURE0 );
			glDisable(GL_TEXTURE_2D);


			glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, NULL );
		}

		glBindBufferARB( GL_ARRAY_BUFFER_ARB, NULL );

		glPopMatrix();


	}
	//----------------------------------------------------------------

	std::pair<bool, float> ModelRenderWayVbo::testIntersection(const vgKernel::Ray* ray)
	{
		GLvoid *vertexbuf = NULL;
		std::pair<bool, float>   bResult;

		bResult.first = false;
		bResult.second = 1e10;

		glBindBufferARB( GL_ARRAY_BUFFER_ARB, _vertexBufferObjectID );
		vertexbuf = glMapBufferARB(GL_ARRAY_BUFFER_ARB , GL_READ_WRITE_ARB);

		assert( vertexbuf != NULL) ;

		char* pVertex = (char*)vertexbuf;

		GLvoid* facemat = NULL;
		FaceIndex* pFaceIndex;
		int i, j;

		int v0Index;
		int v1Index;
		int v2Index;

		void* vp0 = NULL;
		void* vp1 = NULL;
		void* vp2 = NULL;

		for (i=0; i<_numberOfMetaFaces; i++)
		{

			glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, _metaFaces[i]._elementBufferObjectID);
			facemat = glMapBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB , GL_READ_WRITE_ARB);
			assert( facemat != NULL) ;

			pFaceIndex = (FaceIndex*)facemat;

			for (j=0; j<_metaFaces[i]._numOfElements / 3; j++)
			{
				v0Index = pFaceIndex[j].x;
				v1Index = pFaceIndex[j].y;
				v2Index = pFaceIndex[j].z;


				if ( _layersOfTexture == 1 )
				{
					vp0 = pVertex + sizeof( VertexElementStruct ) * v0Index + 
						sizeof( float ) * 5;
					vp1 = pVertex + sizeof( VertexElementStruct ) * v1Index + 
						sizeof( float ) * 5;
					vp2 = pVertex + sizeof( VertexElementStruct ) * v2Index + 
						sizeof( float ) * 5;
				}
				else
				{
					vp0 = pVertex + sizeof( VertexElementStruct2 ) * v0Index + 
						sizeof( float ) * 5;
					vp1 = pVertex + sizeof( VertexElementStruct2 ) * v1Index + 
						sizeof( float ) * 5;
					vp2 = pVertex + sizeof( VertexElementStruct2 ) * v2Index + 
						sizeof( float ) * 5;
				}

				Vec3* p0 =  (Vec3*)vp0;
				Vec3* p1 =  (Vec3*)vp1;
				Vec3* p2 =  (Vec3*)vp2;

				std::pair<bool, float> result = vgKernel::Math::intersects( *ray , *p0 , *p1 , *p2 );
				// 				if (result.first == TRUE)
				// 				{
				// 					bResult = true;
				// 					break;
				// 				}
				if (result.first && result.second < bResult.second)
				{
					bResult.first = true;
					bResult.second = result.second;
				}
			}

			glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, _metaFaces[i]._elementBufferObjectID);
			glUnmapBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB );

			// 			if (bResult == TRUE)
			// 			{
			// 				break;
			// 			}
		}


		glUnmapBufferARB(GL_ARRAY_BUFFER_ARB);
		pVertex = NULL;
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, NULL );

		return bResult;


	}
	//----------------------------------------------------------------
	bool ModelRenderWayVbo::testIntersection( const vgKernel::Segment3* segment )
	{
		GLvoid *vertexbuf = NULL;
		bool   bResult = false;

		glBindBufferARB( GL_ARRAY_BUFFER_ARB, _vertexBufferObjectID );
		vertexbuf = glMapBufferARB(GL_ARRAY_BUFFER_ARB , GL_READ_WRITE_ARB);

		assert( vertexbuf != NULL) ;

		char* pVertex = (char*)vertexbuf;

		GLvoid* facemat = NULL;
		FaceIndex* pFaceIndex;
		int i, j;

		int v0Index;
		int v1Index;
		int v2Index;

		void* vp0 = NULL;
		void* vp1 = NULL;
		void* vp2 = NULL;

		for (i=0; i<_numberOfMetaFaces; i++)
		{

			glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, _metaFaces[i]._elementBufferObjectID);
			facemat = glMapBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB , GL_READ_WRITE_ARB);
			assert( facemat != NULL) ;

			pFaceIndex = (FaceIndex*)facemat;

			for (j=0; j<_metaFaces[i]._numOfElements / 3; j++)
			{
				v0Index = pFaceIndex[j].x;
				v1Index = pFaceIndex[j].y;
				v2Index = pFaceIndex[j].z;

				if ( _layersOfTexture == 1 )
				{
					vp0 = pVertex + sizeof( VertexElementStruct ) * v0Index + 
						sizeof( float ) * 5;
					vp1 = pVertex + sizeof( VertexElementStruct ) * v1Index + 
						sizeof( float ) * 5;
					vp2 = pVertex + sizeof( VertexElementStruct ) * v2Index + 
						sizeof( float ) * 5;
				}
				else
				{
					vp0 = pVertex + sizeof( VertexElementStruct2 ) * v0Index + 
						sizeof( float ) * 5;
					vp1 = pVertex + sizeof( VertexElementStruct2 ) * v1Index + 
						sizeof( float ) * 5;
					vp2 = pVertex + sizeof( VertexElementStruct2 ) * v2Index + 
						sizeof( float ) * 5;
				}

				Vec3* p0 =  (Vec3*)vp0;
				Vec3* p1 =  (Vec3*)vp1;
				Vec3* p2 =  (Vec3*)vp2;


				Triangle3 tri( *p0 , *p1 , *p2 	);


				IntrSegment3Triangle3 intr(  *segment , tri );

				bool result = intr.Test();
				if (result == true)
				{
					bResult = true;
					break;
				}
			}

			glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, _metaFaces[i]._elementBufferObjectID);
			glUnmapBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB );

			if (bResult == true)
			{
				break;
			}
		}


		glUnmapBufferARB(GL_ARRAY_BUFFER_ARB);
		pVertex = NULL;
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, NULL );

		return bResult;
	}
	//----------------------------------------------------------------
	void ModelRenderWayVbo::renderTwoLayerInOneLayer()
	{

		assert( _layersOfTexture == 2);

		glPushMatrix();

		assert( _vertexBufferObjectID != VG_NULL_VBO_ID );
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, _vertexBufferObjectID );

		for ( int i = 0 ; i < _numberOfMetaFaces ; ++i )
		{
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);	
			//glColor4f(0.8f, 0.8f, 0.8f, 1.0);	
			{
				TexObsPointer& cur_tex = _metaFaces[i]._texObserver[
					VGLOD_COARSE];

					if ( cur_tex != NULL && cur_tex->isEmptyTexture() == false)
					{
						glEnable( GL_TEXTURE_2D );
						cur_tex->useBind();
					}
					else
					{
						glDisable( GL_TEXTURE_2D );
						glActiveTexture( GL_TEXTURE0 );
						glDisable( GL_TEXTURE_2D );
						continue;
					}
			}


			assert( _metaFaces[i]._elementBufferObjectID != VG_NULL_VBO_ID );
			glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, 
				_metaFaces[i]._elementBufferObjectID );

			const int nVertexStride = sizeof(VertexElementStruct2);
			const int nIndexStride = sizeof(GLubyte);
			const int nOffsetForNormals = sizeof(GLfloat) * 2;
			const int nOffsetForVertices = sizeof(GLfloat) * 5;
			const int nOffsetForBake = sizeof( GLfloat ) * 8; 


			glTexCoordPointer( 2, GL_FLOAT, nVertexStride, BUFFER_OFFSET(0) );
			glVertexPointer( 3, GL_FLOAT, nVertexStride,BUFFER_OFFSET(nOffsetForVertices));
			glNormalPointer(  GL_FLOAT, nVertexStride, BUFFER_OFFSET(nOffsetForNormals));
			glEnableClientState( GL_VERTEX_ARRAY);
			glEnableClientState( GL_NORMAL_ARRAY);
			glEnableClientState( GL_INDEX_ARRAY );
			glEnableClientState( GL_TEXTURE_COORD_ARRAY);	


			glDrawElements( GL_TRIANGLES, 
				_metaFaces[i]._numOfElements , GL_UNSIGNED_INT, 
				BUFFER_OFFSET(0));


			glDisableClientState( GL_NORMAL_ARRAY);
			glDisableClientState( GL_VERTEX_ARRAY);
			glDisableClientState( GL_INDEX_ARRAY );
			glDisableClientState( GL_TEXTURE_COORD_ARRAY);


			glDisable(GL_TEXTURE_2D);


			glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, NULL );
		}

		glBindBufferARB( GL_ARRAY_BUFFER_ARB, NULL );

		glPopMatrix();


	}

	void ModelRenderWayVbo::invalidateTextures()
	{
		for ( int i = 0 ; i < _numberOfMetaFaces ; ++i )
		{
			for ( int j = 0 ; j < _metaFaces[i]._numberOfTexture ; ++ j )
			{
				if ( _metaFaces[i]._texFileName[j].empty() == true )
				{
					continue;
				}

				TexObsPointer& tex = 	_metaFaces[i]._texObserver[
					VGLOD_COARSE + VGLOD_N * j ];

					if ( tex == NULL )
					{
						tex = _texMgr->getTextureObserver( 
							_metaFaces[i]._texFileName[j] , VGLOD_COARSE );

						if ( tex != NULL )
						{
							tex->addRef();
						}
					}
			}
		}

	}
	//----------------------------------------------------------------
	void ModelRenderWayVbo::turnOnShadowImpl( const vgKernel::Vec3& light_dir )
	{
		assert( _shadowVolume == 0 );

		calcuateForShadow( light_dir );

		buildShadowVolume( light_dir );
	}
	//----------------------------------------------------------------
	void ModelRenderWayVbo::turnOffShadowImpl()
	{
		if( _shadowVolume != -1 && _shadowVolume != 0 )
		{
			glDeleteLists( _shadowVolume , 1 );
			_shadowVolume = 0;
		}
	}
	//----------------------------------------------------------------
	void ModelRenderWayVbo::changeLightDirectionImpl( const vgKernel::Vec3& light_dir )
	{
		if( _shadowVolume != -1 && _shadowVolume != 0 )
		{
			glDeleteLists( _shadowVolume , 1 );
			_shadowVolume = 0;
		}

		calcuateForShadow( light_dir );

		buildShadowVolume( light_dir );
	}
	//----------------------------------------------------------------
	void ModelRenderWayVbo::renderInShadowModeImpl()
	{
		if ( _shadowVolume != 0 )
		{
			glCallList( _shadowVolume );
		}
	}
	//----------------------------------------------------------------
	void ModelRenderWayVbo::buildShadowVolume( const vgKernel::Vec3& lightdir )
	{
		if( _shadowVolume != -1 && _shadowVolume != 0 )
		{
			glDeleteLists( _shadowVolume , 1 );
			_shadowVolume = 0;
		}

		_shadowVolume = glGenLists(1);

		glNewList( _shadowVolume , GL_COMPILE );
		{
			glDisable( GL_LIGHTING );


			const vgKernel::Vec3& lightDir = lightdir;

			glPushMatrix();

			// 			float centerx,centery,centerz;
			// 			
			// 			centerx = (m_BoundryBox.maxPoint.x + m_BoundryBox.minPoint.x ) / 2;
			// 			centery = (m_BoundryBox.maxPoint.y + m_BoundryBox.minPoint.y ) / 2;
			// 			centerz = (m_BoundryBox.maxPoint.z + m_BoundryBox.minPoint.z ) / 2;
			// 			
			// 			glTranslatef(centerx , centery , centerz);
			// 			glRotatef(m_Rotation.x , 1, 0, 0);
			// 			glRotatef(m_Rotation.y , 0, 1, 0);
			// 			glRotatef(m_Rotation.z , 0, 0, 1);
			// 			glTranslatef(-centerx , -centery , -centerz);
			// 			
			// 			glTranslatef(centerx , centery , centerz);
			// 			glScalef(m_Scale.x , m_Scale.y , m_Scale.z);
			// 			glTranslatef(-centerx , -centery , -centerz);
			// 			
			// 			glTranslatef(m_Position.x , m_Position.y, m_Position.z);

			//glDisable( GL_TEXTURE_2D );


			//////////////////////////////////////////////////////////////////////////
			for ( int iface = 0 ; iface < _shadowNumberOfFaces ; ++ iface )
			{
				ShadowFaceIndex& cur_face = _shadowIndicesOfFaces[ iface ];

				assert( cur_face.p1 >= 0 );
				vgKernel::Vec3 &point1 = _shadowVerticesOfFaces[ cur_face.p1 ];
				assert( cur_face.p2 >= 0 );
				vgKernel::Vec3 &point2 = _shadowVerticesOfFaces[ cur_face.p2 ];
				assert( cur_face.p3 >= 0 );
				vgKernel::Vec3 &point3 = _shadowVerticesOfFaces[ cur_face.p3 ];


				vgKernel::Vec3 farpoint1;
				farpoint1 = point1 + lightDir * 10000;
				vgKernel::Vec3 farpoint2;
				farpoint2 = point2 + lightDir * 10000;
				vgKernel::Vec3 farpoint3;
				farpoint3 = point3 + lightDir * 10000;

				if ( cur_face.faceVisible == true )
				{
					//glBegin( GL_TRIANGLES );
					//{
					//	glVertex3fv( point1.v );
					//	glVertex3fv( point2.v );
					//	glVertex3fv( point3.v );
					//}
					//glEnd();

					//glColor4f( 1 , 0.5 , 1 , 0.3f);

					//glBegin( GL_LINES);
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
	//----------------------------------------------------------------
	void ModelRenderWayVbo::calcuateForShadow( const vgKernel::Vec3& lightDir )
	{
		int iface = 0;

		// 首先更新每个normal值
		for (  iface = 0 ; iface < _shadowNumberOfFaces ; ++ iface )
		{
			ShadowFaceIndex& cur_face = _shadowIndicesOfFaces[ iface ];

			assert( cur_face.normal >= 0 );
			vgKernel::Vec3 &curNormal = 
				_shadowNormalOfFaces[ cur_face.normal ];

			if ( curNormal.dotProduct( lightDir ) <= 0 )
			{
				cur_face.faceVisible = true;
			}
			else
			{
				// 黑暗时，什么也不投射。
				cur_face.faceVisible = false;
			}
		}

		// 更新visible的赋值
		for ( iface = 0 ; iface < _shadowNumberOfFaces ; ++ iface )
		{
			ShadowFaceIndex& cur_face = _shadowIndicesOfFaces[ iface ];

			//检查-1时

			if ( cur_face.faceVisible == true )
			{
				if ( cur_face.p1p2AdjFaceIndex != -1 )
				{
					const bool& linevisible =
						_shadowIndicesOfFaces[ cur_face.p1p2AdjFaceIndex ].faceVisible;
					cur_face.p1p2Visible = (linevisible == false ? true : false );
				}
				else
				{
					cur_face.p1p2Visible = true;
				}

				if ( cur_face.p2p3AdjFaceIndex != -1 )
				{
					const bool& linevisible =
						_shadowIndicesOfFaces[ cur_face.p2p3AdjFaceIndex ].faceVisible;
					cur_face.p2p3Visible = (linevisible == false ? true : false );
				}
				else
				{
					cur_face.p2p3Visible = true;
				}

				if ( cur_face.p3p1AdjFaceIndex != -1 )
				{
					const bool& linevisible =
						_shadowIndicesOfFaces[ cur_face.p3p1AdjFaceIndex ].faceVisible;
					cur_face.p3p1Visible = (linevisible == false ? true : false );
				}
				else
				{
					cur_face.p3p1Visible = true;
				}

			} // end of cur_face.faceVisible == true

		}
	}

	void ModelRenderWayVbo::setKeyFrameControl( KeyFrameControl* newctrl )
	{
		if ( _keyframeCtrl != NULL )
		{
			delete _keyframeCtrl;
		}
		_keyframeCtrl = newctrl;
	}
	//----------------------------------------------------------------
	VboMetaFaceStruct::VboMetaFaceStruct()
	{
		_texFileName = NULL;
		_texObserver = NULL;
		_elementBufferObjectID = VG_NULL_VBO_ID;
		_numOfElements = 0;
		_texObserver = NULL;

		_numberOfTexture = 0;
	}

	//----------------------------------------------------------------
	VboMetaFaceStruct::~VboMetaFaceStruct()
	{
		if ( _texObserver != NULL )
		{
			assert( _numberOfTexture != 0 );

			for ( int i = 0 ; i < VGLOD_N * _numberOfTexture ; ++ i )
			{
				if ( _texObserver[i] != NULL )
				{
					_texObserver[i]->releaseRef();
					_texObserver[i] = NULL;
				}
			}

			delete[] _texObserver;
			_texObserver = NULL;
		}

		if ( _texFileName != NULL )
		{
			delete[] _texFileName;
			_texFileName = NULL;
		}
	}
	//----------------------------------------------------------------



}// end of namespace vgModel
