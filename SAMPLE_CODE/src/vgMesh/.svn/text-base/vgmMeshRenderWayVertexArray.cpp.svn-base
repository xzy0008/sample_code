


#include <vgStableHeaders.h>
#include <vgMesh/vgmMeshRenderWayVertexArray.h>
#include <vgImage/vgiTextureManager.h>
#include <vgKernel/vgkMath.h>
#include <vgKernel/vgkIntersectSegment3Triangle3.h>
#include <vgKernel/vgkOpenGLSupport.h>

namespace vgMesh {
	
	
	
	
	//----------------------------------------------------------------
	MeshRenderWayVertexArray::MeshRenderWayVertexArray(
		char* buf , long bufsize )
	{
		assert( buf != NULL );

		setDefault();

		_wholeChunkSize = bufsize;
		_wholeChunkOfData = buf;

	}
	//----------------------------------------------------------------
	MeshRenderWayVertexArray::~MeshRenderWayVertexArray()
	{
		destroy();
	}
	//----------------------------------------------------------------
	//----------------------------------------------------------------
	void MeshRenderWayVertexArray::destroy()
	{
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

		setDefault();
	}
	//----------------------------------------------------------------
	void MeshRenderWayVertexArray::setDefault()
	{
		_texMgr = NULL;

		_inited = false;

		_wholeChunkOfData = NULL;
		_wholeChunkSize = 0;

		_dataType = VGM_DATATYPE_OBJECT;
		_numberOfVertexElements = 0;
		_layersOfTexture = 0;
		_vertexElements = NULL;
		_numberOfMetaFaces = 0;
		_metaFaces = NULL;

		_preLod = VGLOD_COARSE;
		_hasGotTexObserver = false;
	}
	//----------------------------------------------------------------
	bool MeshRenderWayVertexArray::getInfoFromBuffer( char* buf , long bufsize )
	{
		assert( bufsize > 0 );
		assert( buf != NULL );

		long pos = 0;

		_dataType = *(VgmDataType*)( buf + pos );
		pos += sizeof( VgmDataType );

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

		assert( pos == bufsize );

		return true;
	}
	//----------------------------------------------------------------
	void MeshRenderWayVertexArray::render(
		const int& lod, int force_render_in_num_layers,
		RgbaQuad* colorval )
	{
		VGK_CHECK_OPENGL_ERROR();

		assert( _inited == true );
		assert(_hasGotTexObserver == true );

		requireTexObserverByLod( lod );

		assert( _vertexElements !=  NULL );


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
	void MeshRenderWayVertexArray::requireTextureObservers()
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
	void MeshRenderWayVertexArray::requireTexObserverByLod( 
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
	bool MeshRenderWayVertexArray::initialiseInMainThread()
	{
		assert( _inited == true );

		if ( _hasGotTexObserver == false )
		{
			requireTextureObservers();
		}

		return true;
	}
	//----------------------------------------------------------------
	void MeshRenderWayVertexArray::dumpTextureNameList( 
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
	bool MeshRenderWayVertexArray::initialise()
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
	void MeshRenderWayVertexArray::renderInOneLayer()
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
			assert( _sizeOfVertexElements == sizeof( VgmVertexElement1 ) );

			glInterleavedArrays( GL_T2F_N3F_V3F, 0 , _vertexElements );
			
			glDrawElements(GL_TRIANGLES, _metaFaces[i]._numberOfFaceIndex * 3,
				GL_UNSIGNED_INT , _metaFaces[i]._faceIndex );

		}
		glPopMatrix();
	}
	//----------------------------------------------------------------
	void MeshRenderWayVertexArray::renderInTwoLayer()
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
		assert( _sizeOfOneTexName == VGM_TEXTURE_NAME_LENGTH );
		pos += sizeof( long );

		_texFileName = new String[ _numberOfTexture ];
		for ( int i = 0 ; i < _numberOfTexture ; ++ i )
		{
			assert( _texFileName != NULL );
			char* filename = (char*)(buf + pos);
			assert( filename[VGM_TEXTURE_NAME_LENGTH-1] == 0 );
			_texFileName[i] = filename;
			pos += _sizeOfOneTexName;
		}

		_numberOfFaceIndex = *(long*)( buf + pos );
		pos += sizeof( long );

		_sizeOfFaceIndex = *(long*)( buf + pos );
		assert( _sizeOfFaceIndex == sizeof( VgmFaceIndex ) );
		pos += sizeof( long );

		assert( _faceIndex == NULL );
		_faceIndex = (VgmFaceIndex*)( buf + pos );
		pos += ( _numberOfFaceIndex * _sizeOfFaceIndex );

		return pos;
	}
	//----------------------------------------------------------------
	std::pair<bool, float> MeshRenderWayVertexArray::testIntersection(
		const vgKernel::Ray* ray)
	{
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
	bool MeshRenderWayVertexArray::testIntersection( const vgKernel::Segment3* segment )
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
	void MeshRenderWayVertexArray::reCalculateBoundingBox()
	{
		_staticBoundingBox = Box( (float)INT_MAX);
		for( int indexMetaFace = 0 ; indexMetaFace < _numberOfMetaFaces ; ++indexMetaFace )
		{
			MetaFaceStruct*	refMetaFaceStruct =	&_metaFaces[indexMetaFace];
			for( int indexFace = 0 ; indexFace < refMetaFaceStruct->_numberOfFaceIndex ; ++indexFace )
			{
				int vertIndex ;
				vgKernel::Vec3	tempVec;
				VgmVertexElement1* vertexArray = (VgmVertexElement1*)_vertexElements;

				vertIndex = refMetaFaceStruct->_faceIndex[indexFace]._point0;
				tempVec = vgKernel::Vec3(
					vertexArray[vertIndex].positionX,
					vertexArray[vertIndex].positionY,
					vertexArray[vertIndex].positionZ);
				_staticBoundingBox.merge( tempVec );

				vertIndex = refMetaFaceStruct->_faceIndex[indexFace]._point1;
				tempVec = vgKernel::Vec3(
					vertexArray[vertIndex].positionX,
					vertexArray[vertIndex].positionY,
					vertexArray[vertIndex].positionZ);
				_staticBoundingBox.merge( tempVec );

				vertIndex = refMetaFaceStruct->_faceIndex[indexFace]._point2;
				tempVec = vgKernel::Vec3(
					vertexArray[vertIndex].positionX,
					vertexArray[vertIndex].positionY,
					vertexArray[vertIndex].positionZ);
				_staticBoundingBox.merge( tempVec );
			}//for(Face)
		}//for(MetaFace)
	}
	//----------------------------------------------------------------
	void MeshRenderWayVertexArray::renderTwoLayerInOneLayer()
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
			assert( _sizeOfVertexElements == sizeof( VgmVertexElement2 ) );

			glInterleavedArrays( GL_T2F_N3F_V3F, 
				sizeof( VgmVertexElement2 ) , _vertexElements );

			glDrawElements(GL_TRIANGLES, _metaFaces[i]._numberOfFaceIndex * 3,
				GL_UNSIGNED_INT , _metaFaces[i]._faceIndex );

		}
		glPopMatrix();
	}
	//----------------------------------------------------------------


}// end of namespace vgMesh
