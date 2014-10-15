


#include <vgStableHeaders.h>

#if 0

#include <vgMesh/vgmMeshRenderWayDisplayList.h>
#include <vgMesh/vgmFileDefinitionMod.h>
#include <vgImage/vgiTextureManager.h>
#include <vgKernel/vgkOpenGLSupport.h>

#include <vgKernel/vgkMath.h>

namespace vgMesh {

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

	//----------------------------------------------------------------
	MeshRenderWayDisplayList::~MeshRenderWayDisplayList()
	{
		if (_vertexarray != NULL )
		{
			for (int i =0 ; i <_vertexarray->_numberOfMetaFaces; i++)
			{
				glDeleteLists( _lists[i], 1);

				_lists[i] = 0;
			}
		}

		delete[] _lists;

		delete _vertexarray;
		

	}
	//----------------------------------------------------------------
	MeshRenderWayDisplayList::MeshRenderWayDisplayList( 
		MeshRenderWayVertexArray* vertexarray)
	{
		_lists = NULL;

		_vertexarray = NULL;

		_vertexarray = vertexarray;

		_lists = new GLint[vertexarray->_numberOfMetaFaces];

		memset( _lists, 0 , sizeof(GLint) * vertexarray->_numberOfMetaFaces );  

	}
	//----------------------------------------------------------------
	bool MeshRenderWayDisplayList::generateDisplaylist( 
		MeshRenderWayVertexArray* vertexarray )
	{

		if ( vertexarray->_layersOfTexture == 1 )
		{
			for ( int i = 0 ; i < vertexarray->_numberOfMetaFaces ; ++ i )
			{
				if (_lists[i] == 0)
				{
					_lists[i] = glGenLists( 1 );   
					glNewList(_lists[i], GL_COMPILE );

 					glInterleavedArrays( GL_T2F_N3F_V3F, 0 , vertexarray->_vertexElements );
 
 					glDrawElements(GL_TRIANGLES, vertexarray->_metaFaces[i]._numberOfFaceIndex * 3,
 						GL_UNSIGNED_INT , vertexarray->_metaFaces[i]._faceIndex );

					glEndList();					
				}
			}
		}
		else if ( vertexarray->_layersOfTexture == 2 )
		{	
		}
		else
		{
			assert(0);
		}




		return true;
	}
	//----------------------------------------------------------------
	//----------------------------------------------------------------
	void MeshRenderWayDisplayList::render(const int& lod)
	{

 		requireTexObserverByLod( lod );
 
 
 		if ( _vertexarray->_layersOfTexture == 1 )
 		{
 			renderInOneLayer();
 		}
 		else if ( _vertexarray->_layersOfTexture == 2 )
 		{
 			renderInTwoLayer();
 		}
 		else
 		{
 			assert(0);
 		}


	}
	//----------------------------------------------------------------
	void MeshRenderWayDisplayList::requireTexObserverByLod( const int& lod )
	{
		assert( lod <= VGLOD_CLEAR );
		assert( lod >= VGLOD_COARSE );

		if ( _vertexarray->_preLod == lod )
		{
			return;
		}

		//------------------------------------------
		// 当lod有变化时,更新
		//------------------------------------------
		_vertexarray->_preLod = lod;

		if ( lod == VGLOD_COARSE )
		{
			//------------------------------------------
			// 当为最不清晰的一层时,
			// 卸载其他级即可.
			//------------------------------------------
			for ( int i = 0 ; i < _vertexarray->_numberOfMetaFaces ; ++i )
			{
				TexObsPointer*& observers = _vertexarray->_metaFaces[i]._texObserver;
				const int& texNum =_vertexarray->_metaFaces[i]._numberOfTexture;
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
			for ( int i = 0 ; i < _vertexarray->_numberOfMetaFaces ; ++i )
			{
				TexObsPointer*& observers = _vertexarray->_metaFaces[i]._texObserver;
				const int& texNum = _vertexarray->_metaFaces[i]._numberOfTexture;
				//const int& texNum = 1;

				for ( int j = 0 ; j < texNum * VGLOD_N; j+= VGLOD_N)
				{
					if ( observers[ VGLOD_COARSE + j] == NULL )
					{
						continue;
					}

					if ( observers[ VGLOD_CLEAR + j] == NULL )
					{
						observers[ VGLOD_CLEAR + j]  = _vertexarray->_texMgr->getTextureObserver(
							_vertexarray->_metaFaces[i]._texFileName[j/VGLOD_N] , VGLOD_CLEAR );

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
			for ( int i = 0 ; i < _vertexarray->_numberOfMetaFaces ; ++i )
			{
				TexObsPointer*& observers = _vertexarray->_metaFaces[i]._texObserver;
				const int& texNum = _vertexarray->_metaFaces[i]._numberOfTexture;
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
					else if ( observers[ VGLOD_COARSE + 1 + j] == NULL )
					{
						// 检查中间级,没载入的话,将其载入.
						observers[ VGLOD_COARSE + 1 + j] = _vertexarray->_texMgr->getTextureObserver(
							_vertexarray->_metaFaces[i]._texFileName[j/VGLOD_N] , VGLOD_COARSE + 1 );

						assert( observers[ VGLOD_COARSE + 1 + j] != NULL );
						observers[ VGLOD_COARSE + 1 + j]->addRef();
					}

				}
			}
		}


		return;
	}
	//----------------------------------------------------------------
	bool MeshRenderWayDisplayList::initialiseInMainThread()
	{		
		generateDisplaylist( _vertexarray );
		return true;
	}
	//----------------------------------------------------------------
	void MeshRenderWayDisplayList::renderInOneLayer()
	{	
		glPushMatrix();

		if(  _vertexarray->_renderType == 1 || _vertexarray->_renderType == 2 )
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

		for ( int i = 0 ; i < _vertexarray->_numberOfMetaFaces ; ++ i )
		{
			// 由于useBind会自动搜索最清晰的一级,所以只要
			// 关心最不清晰一级的observer即可.
			vgImage::TextureObserver*& cur_tex = 
				_vertexarray->_metaFaces[i]._texObserver[ VGLOD_COARSE ];

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

			glColor3f(1, 1, 1);	
			//glColor3f(0.8, 0.8, 0.8);

			glCallList( _lists[i] );

		}
		glPopMatrix();
	}
	//----------------------------------------------------------------
	void MeshRenderWayDisplayList::renderInTwoLayer()
	{
		assert( _vertexarray->_layersOfTexture == 2);

		const GLsizei& nVertexStride = _vertexarray->_sizeOfVertexElements; 
		VertexElementStruct2* element = (VertexElementStruct2*)(_vertexarray->_vertexElements);


		glPushMatrix();

		for ( int i = 0 ; i < _vertexarray->_numberOfMetaFaces ; ++ i )
		{

			glActiveTexture( GL_TEXTURE0 );
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);	
			{
				TexObsPointer& cur_tex = _vertexarray->_metaFaces[i]._texObserver[
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
				TexObsPointer& cur_tex = _vertexarray->_metaFaces[i]._texObserver[
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


			glDrawElements(GL_TRIANGLES, _vertexarray->_metaFaces[i]._numberOfFaceIndex * 3,
				GL_UNSIGNED_INT , _vertexarray->_metaFaces[i]._faceIndex );

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

	}
	//----------------------------------------------------------------

	bool MeshRenderWayDisplayList::testIntersection(const vgKernel::Ray* ray)
	{
		return _vertexarray->testIntersection( ray );
	}

	bool MeshRenderWayDisplayList::testIntersection( const vgKernel::Segment3* segment )
	{
		return _vertexarray->testIntersection( segment );
	}


	//----------------------------------------------------------------


}// end of namespace vgMesh


#endif