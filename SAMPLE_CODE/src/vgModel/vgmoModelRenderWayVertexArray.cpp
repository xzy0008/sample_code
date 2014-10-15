


#include <vgStableHeaders.h>
#include <vgModel/vgmoModelRenderWayVertexArray.h>
#include <vgImage/vgiTextureManager.h>
#include <vgKernel/vgkMath.h>
#include <vgKernel/vgkIntersectSegment3Triangle3.h>
#include <vgModel/vgmoKeyFrameControl.h>
#include <vgKernel/vgkOpenGLSupport.h>

namespace vgModel {
	
	
	
	
	//----------------------------------------------------------------
	ModelRenderWayVertexArray::ModelRenderWayVertexArray(
		char* buf , long bufsize )
	{
		assert( buf != NULL );

		setDefault();

		_wholeChunkSize = bufsize;
		_wholeChunkOfData = buf;

	}
	//----------------------------------------------------------------
	ModelRenderWayVertexArray::~ModelRenderWayVertexArray()
	{
		destroy();
	}
	//----------------------------------------------------------------
	//----------------------------------------------------------------
	void ModelRenderWayVertexArray::destroy()
	{
		turnOffShadowImpl();

		if ( _wholeChunkOfData != NULL )
		{
			delete[] _wholeChunkOfData;
			_wholeChunkOfData = NULL;
		}

		if ( _metaFaces != NULL )
		{
			delete[] _metaFaces;
			_metaFaces = NULL;
		}


		if ( _keyframeCtrl != NULL )
		{
			delete _keyframeCtrl;
			_keyframeCtrl = NULL;
		}

		setDefault();
	}
	//----------------------------------------------------------------
	void ModelRenderWayVertexArray::setDefault()
	{
		_texMgr = NULL;

		_inited = false;

		_wholeChunkOfData = NULL;
		_wholeChunkSize = 0;

		_numberOfVertexElements = 0;
		_layersOfTexture = 0;
		_vertexElements = NULL;
		_numberOfMetaFaces = 0;
		_metaFaces = NULL;

		_preLod = VGLOD_COARSE;
		_hasGotTexObserver = false;

		_shadowNumberOfFaces = 0;
		_shadowNormalOfFaces = NULL;
		_shadowNumberOfVertices = 0;
		_shadowVerticesOfFaces = NULL;
		_shadowIndicesOfFaces = NULL;

		_shadowVolume = 0;



		_keyframeCtrl = 0;
	}
	//----------------------------------------------------------------
	bool ModelRenderWayVertexArray::getInfoFromBuffer( char* buf , long bufsize )
	{
		assert( bufsize > 0 );
		assert( buf != NULL );

		long pos = 0;


		_renderType = *(int*)( buf + pos );
		pos += sizeof( int );

		_layersOfTexture = *(long*)( buf + pos );
		pos += sizeof( long );

		_numberOfVertexElements = *(long*)( buf + pos );
		pos += sizeof( long );

		_sizeOfVertexElements = *(long*)( buf + pos );
		pos += sizeof( long );

		assert( _vertexElements == NULL );
		_vertexElements = (void*)( buf + pos );
		pos += (_sizeOfVertexElements * _numberOfVertexElements);

		_numberOfMetaFaces = *(long*)( buf + pos );
		pos += sizeof( long );

		assert( _metaFaces == NULL );
		_metaFaces = new MetaFaceStruct[_numberOfMetaFaces];
		for ( int i = 0 ; i < _numberOfMetaFaces ; ++i )
		{
			 _metaFaces[i]._fatherVAWay = this;

			long readsize = _metaFaces[i].getInfoFromBuffer( buf + pos );
			pos += readsize;
		}

		//------------------------------------------
		// dataplus
		//------------------------------------------
		_shadowNumberOfFaces = *(int*)( buf + pos );
		pos += sizeof( int );

		assert( _shadowNumberOfFaces > 0 );

		_shadowNormalOfFaces = (Vec3*)( buf + pos );
		pos += sizeof( Vec3 ) * _shadowNumberOfFaces;

		_shadowNumberOfVertices = *(int*)( buf + pos );
		pos += sizeof( int );

		_shadowVerticesOfFaces = (Vec3*)( buf + pos );
		pos += sizeof( Vec3 ) * _shadowNumberOfVertices;

		_shadowIndicesOfFaces = (ShadowFaceIndex*)( buf + pos );
		pos += sizeof( ShadowFaceIndex ) * _shadowNumberOfFaces;

		//------------------------------------------
		// keyframe
		//------------------------------------------
		int _frameCount = *(int*)( buf + pos );
		assert( _frameCount >= 0 );

		if ( _frameCount > 0 )
		{
			assert( _keyframeCtrl == NULL );
			_keyframeCtrl = new KeyFrameControl;
			long readnum = _keyframeCtrl->readBuf( buf + pos  );
			pos += readnum;
		}
		else
		{
			pos += sizeof(int);
		}

		assert( pos == bufsize );


		return true;
	}
	//----------------------------------------------------------------
	void ModelRenderWayVertexArray::render(
		const int& lod, int force_render_in_num_layers,
		RgbaQuad* colorval )
	{
		VGK_CHECK_OPENGL_ERROR();

		assert( _inited == true );
		assert(_hasGotTexObserver == true );

		requireTexObserverByLod( lod );

		assert( _vertexElements !=  NULL );

		//------------------------------------------
		// 计算关键帧信息
		//------------------------------------------
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


		VGK_CHECK_OPENGL_ERROR();

		if ( _layersOfTexture == 1 )
		{
			renderInOneLayer();
			VGK_CHECK_OPENGL_ERROR();
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


	}
	//----------------------------------------------------------------
	void ModelRenderWayVertexArray::requireTextureObservers()
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

				tex = _texMgr->getTextureObserver( 
					_metaFaces[i]._texFileName[j] , VGLOD_COARSE );

				if ( tex != NULL )
				{
					tex->addRef();
				}
			}

		}

		_hasGotTexObserver = true;
	}
	//----------------------------------------------------------------
	void ModelRenderWayVertexArray::requireTexObserverByLod( 
		const int& lod )
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
	bool ModelRenderWayVertexArray::initialiseInMainThread()
	{
		assert( _inited == true );

		if ( _hasGotTexObserver == false )
		{
			requireTextureObservers();
		}

		return true;
	}
	//----------------------------------------------------------------
	void ModelRenderWayVertexArray::dumpTextureNameList( 
		vgKernel::StringVectorPtr ptexturelist ) const	
	{
		assert( ptexturelist.isNull() == false );

		for ( int i = 0 ; i < _numberOfMetaFaces ; ++ i )
		{
			for ( int j = 0 ; j < _metaFaces[i]._numberOfTexture ; ++ j )
			{
				if (_metaFaces[i]._texFileName[j].empty() == false  )
				{
					ptexturelist->push_back( _metaFaces[i]._texFileName[j] );
				}
			}
		}

		return;
	}
	//----------------------------------------------------------------
	bool ModelRenderWayVertexArray::initialise()
	{
		_texMgr = vgImage::TextureManager::getSingletonPtr();
		assert( _texMgr != NULL );

		assert( _wholeChunkSize > 0 );

		assert( _wholeChunkOfData != NULL );

		_inited = getInfoFromBuffer( _wholeChunkOfData , _wholeChunkSize );

		//reCalculateBoundingBox(); 

		return _inited;
	}
	//----------------------------------------------------------------
	void ModelRenderWayVertexArray::renderInOneLayer()
	{
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
		glDisable( GL_LIGHTING );
		glColor3d(1, 1, 1);	

		glPushMatrix();

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

		for ( int i = 0 ; i < _numberOfMetaFaces ; ++ i )
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

			assert( _layersOfTexture == 1 );
			assert( _sizeOfVertexElements == sizeof( VmdVertexElement1 ) );

			glInterleavedArrays( GL_T2F_N3F_V3F, 0 , _vertexElements );
			
			glDrawElements(GL_TRIANGLES, _metaFaces[i]._numberOfFaceIndex * 3,
				GL_UNSIGNED_INT , _metaFaces[i]._faceIndex );

		}
		glPopMatrix();
	}
	//----------------------------------------------------------------
	void ModelRenderWayVertexArray::renderInTwoLayer()
	{
		//assert(0);
		assert( _layersOfTexture == 2);

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


		glPushMatrix();

		for ( int i = 0 ; i < _numberOfMetaFaces ; ++ i )
		{
				const GLsizei& nVertexStride = _sizeOfVertexElements; 
				VertexElementStruct2* element = 	(VertexElementStruct2*)_vertexElements;

				glActiveTexture( GL_TEXTURE0 );
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);	
				//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
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
				//glColor4f(0.5f, 0.5f, 0.5f, 1.0f);	

				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
				//glTexEnvi( GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE, GL_COMBINE );

				//glTexEnvi( GL_TEXTURE_ENV ,GL_COMBINE_RGB , GL_ADD_SIGNED );

				//glTexEnvi( GL_TEXTURE_ENV , GL_SOURCE0_RGB , GL_TEXTURE0 );
				//glTexEnvi( GL_TEXTURE_ENV, GL_OPERAND0_RGB , GL_SRC_COLOR );

				//glTexEnvi( GL_TEXTURE_ENV, GL_SOURCE1_RGB , GL_TEXTURE1 );
				//glTexEnvi( GL_TEXTURE_ENV, GL_OPERAND1_RGB , GL_SRC_COLOR );

				//glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE, 2.0f);

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



				glClientActiveTexture( GL_TEXTURE1 );
				glTexCoordPointer( 2, GL_FLOAT, nVertexStride, 
					&element[0].texCoorUForLit );
				glVertexPointer( 3, GL_FLOAT, nVertexStride,
					&element[0].positionX );
				glNormalPointer(  GL_FLOAT, nVertexStride, 
					&element[0].normalX );
				glEnableClientState( GL_VERTEX_ARRAY);
				glEnableClientState( GL_NORMAL_ARRAY);
				glEnableClientState( GL_INDEX_ARRAY );
				glEnableClientState( GL_TEXTURE_COORD_ARRAY);	


				glClientActiveTexture( GL_TEXTURE0 );
				glTexCoordPointer( 2, GL_FLOAT, nVertexStride, 
					&element[0].texCoorS );
				glVertexPointer( 3, GL_FLOAT, nVertexStride,
					&element[0].positionX );
				glNormalPointer(  GL_FLOAT, nVertexStride, 
					&element[0].normalX );
				glEnableClientState( GL_VERTEX_ARRAY);
				glEnableClientState( GL_NORMAL_ARRAY);
				glEnableClientState( GL_INDEX_ARRAY );
				glEnableClientState( GL_TEXTURE_COORD_ARRAY);	




				glDrawElements(GL_TRIANGLES, _metaFaces[i]._numberOfFaceIndex * 3,
					GL_UNSIGNED_INT , _metaFaces[i]._faceIndex );


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
		}

		glPopMatrix();

		VGK_CHECK_OPENGL_ERROR();

		if(  _renderType == 1 || _renderType == 2 )
		{
			glDisable( GL_ALPHA_TEST );
			glDisable( GL_BLEND );
		}


	}
	//----------------------------------------------------------------
	//----------------------------------------------------------------



	//----------------------------------------------------------------
	MetaFaceStruct::MetaFaceStruct()
	{
		setDefault();
	}
	//----------------------------------------------------------------
	MetaFaceStruct::~MetaFaceStruct()
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

		//setDefault();
	}
	//----------------------------------------------------------------
	void MetaFaceStruct::setDefault()
	{
		memset( _colorRGBA , 0 , 4 );
		_numberOfFaceIndex = 0;
		_faceIndex = NULL;
		_numberOfTexture = 0;
		_sizeOfFaceIndex = 0;
		

		_texObserver = NULL;

		_texFileName = NULL;
		_fatherVAWay = NULL;



	}
	//----------------------------------------------------------------
	long MetaFaceStruct::getInfoFromBuffer( char* buf )
	{
		assert( buf != NULL );

		long pos = 0;

		memcpy( _colorRGBA , buf + pos , sizeof( _colorRGBA ) );
		pos += sizeof( _colorRGBA );

		_numberOfTexture = *(int*)( buf + pos );
		pos += sizeof( int );

		//------------------------------------------
		// 创建Observers
		//------------------------------------------
		assert( _texObserver == NULL );
		_texObserver = 
			new vgImage::TextureObserver*[ VGLOD_N * _numberOfTexture ];

		for ( int i = 0 ; i < VGLOD_N * _numberOfTexture ; ++ i )
		{
			_texObserver[i] = NULL;
		}

		//------------------------------------------
		// TextureName
		//------------------------------------------
		long _sizeOfOneTexName = *(long*)( buf + pos );
		assert( _sizeOfOneTexName == VMD_TEXTURE_NAME_LENGTH );
		pos += sizeof( long );

		_texFileName = new String[ _numberOfTexture ];
		for ( int i = 0 ; i < _numberOfTexture ; ++ i )
		{
			assert( _texFileName != NULL );
			char* filename = (char*)(buf + pos);
			assert( filename[VMD_TEXTURE_NAME_LENGTH-1] == 0 );
			_texFileName[i] = filename;
			pos += _sizeOfOneTexName;
		}

		_numberOfFaceIndex = *(long*)( buf + pos );
		pos += sizeof( long );

		_sizeOfFaceIndex = *(long*)( buf + pos );
		assert( _sizeOfFaceIndex == sizeof( VmdFaceIndex ) );
		pos += sizeof( long );

		assert( _faceIndex == NULL );
		_faceIndex = (VmdFaceIndex*)( buf + pos );
		pos += ( _numberOfFaceIndex * _sizeOfFaceIndex );




		return pos;
	}
	//----------------------------------------------------------------
	std::pair<bool, float> ModelRenderWayVertexArray::testIntersection(
		const vgKernel::Ray* ray)
	{
		 //ASSERT(sizeof(VmdVertexElement1) == _sizeOfVertexElements);

		char* vertexArray = (char*)_vertexElements;
		std::pair<bool, float> bResult;

		bResult.first = false;
		bResult.second = 1e10;


		int v0Index;
		int v1Index;
		int v2Index;


		void* vp0 = NULL;
		void* vp1 = NULL;
		void* vp2 = NULL;

		// float vertextArray
		//TRACE("_numberOfMetaFaces is %d \n", _numberOfMetaFaces);
		for ( int i = 0 ; i < _numberOfMetaFaces ; i++)
		{
			for (int j=0; j < _metaFaces[i]._numberOfFaceIndex; j++)
			{
				v0Index = _metaFaces[i]._faceIndex[j]._point0;
				v1Index = _metaFaces[i]._faceIndex[j]._point1;
				v2Index = _metaFaces[i]._faceIndex[j]._point2;

				vp0 = vertexArray + _sizeOfVertexElements * v0Index + 
					sizeof( float ) * 5;
				vp1 = vertexArray + _sizeOfVertexElements * v1Index + 
					sizeof( float ) * 5;
				vp2 = vertexArray + _sizeOfVertexElements * v2Index + 
					sizeof( float ) * 5;


				Vec3* p0 =  (Vec3*)vp0;
				Vec3* p1 =  (Vec3*)vp1;
				Vec3* p2 =  (Vec3*)vp2;


				std::pair<bool, float> result = vgKernel::Math::intersects(
					*ray ,*p0 , *p1 , *p2 );

				if( result.first == true && result.second < bResult.second)
				{
					bResult.first = true;
					bResult.second = result.second;
// 					////TRACE();
// 					return true;
				}
			}
		}

		return bResult;
	}
	//----------------------------------------------------------------
	bool ModelRenderWayVertexArray::testIntersection( const vgKernel::Segment3* segment )
	{
		char* vertexArray = (char*)_vertexElements;

		int v0Index;
		int v1Index;
		int v2Index;

		void* vp0 = NULL;
		void* vp1 = NULL;
		void* vp2 = NULL;

		// float vertextArray
		//TRACE("_numberOfMetaFaces is %d \n", _numberOfMetaFaces);
		for ( int i = 0 ; i < _numberOfMetaFaces ; i++)
		{
			for (int j=0; j < _metaFaces[i]._numberOfFaceIndex; j++)
			{
				v0Index = _metaFaces[i]._faceIndex[j]._point0;
				v1Index = _metaFaces[i]._faceIndex[j]._point1;
				v2Index = _metaFaces[i]._faceIndex[j]._point2;

				using namespace vgKernel;

				if ( _layersOfTexture == 1 )
				{
					vp0 = vertexArray + sizeof( VertexElementStruct ) * v0Index + 
						sizeof( float ) * 5;
					vp1 = vertexArray + sizeof( VertexElementStruct ) * v1Index + 
						sizeof( float ) * 5;
					vp2 = vertexArray + sizeof( VertexElementStruct ) * v2Index + 
						sizeof( float ) * 5;
				}
				else
				{
					vp0 = vertexArray + sizeof( VertexElementStruct2 ) * v0Index + 
						sizeof( float ) * 5;
					vp1 = vertexArray + sizeof( VertexElementStruct2 ) * v1Index + 
						sizeof( float ) * 5;
					vp2 = vertexArray + sizeof( VertexElementStruct2 ) * v2Index + 
						sizeof( float ) * 5;
				}

				Vec3* p0 =  (Vec3*)vp0;
				Vec3* p1 =  (Vec3*)vp1;
				Vec3* p2 =  (Vec3*)vp2;


				Triangle3 tri( *p0 , *p1 , *p2	);


				IntrSegment3Triangle3 intr(  *segment , tri );

				bool result = intr.Test();
				if (result == true)
				{
					return true;
				}
			}
		}

		return false;
	}
	//----------------------------------------------------------------
	void ModelRenderWayVertexArray::renderTwoLayerInOneLayer()
	{
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
		glDisable( GL_LIGHTING );
		glColor3d(1, 1, 1);	

		glPushMatrix();

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

		for ( int i = 0 ; i < _numberOfMetaFaces ; ++ i )
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

			assert( _layersOfTexture == 2 );
			assert( _sizeOfVertexElements == sizeof( VmdVertexElement2 ) );

			glInterleavedArrays( GL_T2F_N3F_V3F, 
				sizeof( VmdVertexElement2 ) , _vertexElements );

			glDrawElements(GL_TRIANGLES, _metaFaces[i]._numberOfFaceIndex * 3,
				GL_UNSIGNED_INT , _metaFaces[i]._faceIndex );

		}
		glPopMatrix();
	}
	//----------------------------------------------------------------
	void ModelRenderWayVertexArray::turnOnShadowImpl( 
		const vgKernel::Vec3& light_dir )
	{
		assert( _shadowVolume == 0 );

		calcuateForShadow( light_dir );

		buildShadowVolume( light_dir );
	}
	//----------------------------------------------------------------
	void ModelRenderWayVertexArray::turnOffShadowImpl()
	{
		if( _shadowVolume != -1 && _shadowVolume != 0 )
		{
			glDeleteLists( _shadowVolume , 1 );
			_shadowVolume = 0;
		}
	}
	//----------------------------------------------------------------
	void ModelRenderWayVertexArray::changeLightDirectionImpl(
		const vgKernel::Vec3& light_dir )
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
	void ModelRenderWayVertexArray::renderInShadowModeImpl()
	{
		if ( _shadowVolume != 0 )
		{
			glCallList( _shadowVolume );
		}
	}
	//----------------------------------------------------------------
	void ModelRenderWayVertexArray::calcuateForShadow( const vgKernel::Vec3& lightDir )
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
	//----------------------------------------------------------------
	void ModelRenderWayVertexArray::buildShadowVolume( const vgKernel::Vec3& lightdir )
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
	void ModelRenderWayVertexArray::invalidateTextures()
	{
		_hasGotTexObserver = false;

		assert( _inited == true );


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

		_hasGotTexObserver = true;
	}

	void ModelRenderWayVertexArray::setKeyFrameControl( KeyFrameControl* newctrl )
	{
		if ( _keyframeCtrl != NULL )
		{
			delete _keyframeCtrl;
		}
		_keyframeCtrl = newctrl;
	}
	//----------------------------------------------------------------


}// end of namespace vgModel
