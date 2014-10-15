


#include <vgStableHeaders.h>
#include <vgTerritory/vgMeshChunkSlit.h>
#include <vgKernel/vgkOpenGLSupport.h>

namespace vgTerritory {

#define BUFFER_OFFSET(i) ((char *)NULL + (i))


	//----------------------------------------------------------------
	MeshChunkSlitData::MeshChunkSlitData(const int& n , const float& cellsize)
	{
		setDefault();

		_N = n - 1;
		_cellSize = cellsize * 2.0f;

		createMeshImpl();
	}
	//----------------------------------------------------------------
	MeshChunkSlitData::~MeshChunkSlitData()
	{
		destroyVboData();
	}
	//----------------------------------------------------------------
	//----------------------------------------------------------------
	void MeshChunkSlitData::render( const bool& render_up , 
		const bool& render_left,
		const int& texcenterx , 
		const int& texcenterz , 
		ElevationItem* leftup , 
		ElevationItem* leftdown ,
		ElevationItem* rightup ,
		ElevationItem* rightdown  )
	{
		//------------------------------------------
		// 这里为什么这么做?不知道
		//------------------------------------------
		_centerX = texcenterx * 2  - _face2x2num;
		_centerZ = texcenterz * 2  - _face2x2num;
		_centerX *= (-1);
		_centerZ *= (-1);

		_pTexBlockLeftUp = leftup;
		_pTexBlockLeftDown = leftdown;
		_pTexBlockRightUp = rightup;
		_pTexBlockRightDown = rightdown;


		//------------------------------------------

		if ( render_up == true )
		{
			if ( render_left == false)
			{
				renderUp();
			}
			else
			{
				renderLeftUp();
			}
		}
		else
		{
			if ( render_left == true )
			{
				renderLeft();
			}
		}

	}
	//----------------------------------------------------------------
	void MeshChunkSlitData::destroyVboData()
	{
		VGK_CHECK_OPENGL_ERROR();

		if ( _upVertexBufID != 0 )
		{
			glDeleteBuffersARB( 1, &_upVertexBufID ); 
			_upVertexBufID = 0;
		}

		if ( _upIndexBufID != 0 )
		{
			glDeleteBuffersARB( 1, &_upIndexBufID);
			_upIndexBufID = 0;
		}
		//----------------------------------------------------------------

		if ( _leftVertexBufID != 0 )
		{
			glDeleteBuffersARB( 1, &_leftVertexBufID ); 
			_leftVertexBufID = 0;
		}

		if ( _leftIndexBufID != 0 )
		{
			glDeleteBuffersARB( 1, &_leftIndexBufID);
			_leftIndexBufID = 0;
		}

		VGK_CHECK_OPENGL_ERROR();
	}
	//----------------------------------------------------------------
	void MeshChunkSlitData::setDefault()
	{
		_upVertexBufID = 0;
		_upIndexBufID = 0;
		_leftVertexBufID = 0;
		_leftIndexBufID = 0;
		//_leftUpVertexBufID = 0;
		//_leftUpIndexBufID = 0;

		_pTexBlockLeftUp = NULL;
		_pTexBlockLeftDown = NULL;
		_pTexBlockRightUp = NULL;
		_pTexBlockRightDown = NULL;

		_upIndexStride = 0;
		_upIndexStrideUnit = 0;
	}
	//----------------------------------------------------------------
	void MeshChunkSlitData::renderUp()
	{
		//------------------------------------------
		// up上的separate
		//------------------------------------------
		if ( _centerX < 1 )
		{
			_upSeparated = 0;
		}
		else if ( _centerX > _face1x1num - 1 )
		{
			_upSeparated = _upIndexStride;
		}
		else
		{
			_upSeparated = _centerX * _upIndexStrideUnit;
		}

		if ( _centerZ < 1 )
		{
			_upSeparatedTexFlag = false;
		}
		else
		{
			_upSeparatedTexFlag = true;
		}


		if ( _upIndexBufID == 0 )
		{
			assert(0);
			return;
		}

		//------------------------------------------
		// 开始渲染
		//------------------------------------------
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, _upVertexBufID );

		const int nVertexStride = sizeof(MeshVertex);
		const int nOffsetForNormals = sizeof(float) * 2;
		const int nOffsetForVertices = sizeof(float) * 5;

		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glEnableClientState( GL_NORMAL_ARRAY );
		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_INDEX_ARRAY );

		glTexCoordPointer( 2, GL_FLOAT, nVertexStride, BUFFER_OFFSET(0) );
		glNormalPointer( GL_FLOAT, nVertexStride, BUFFER_OFFSET(nOffsetForNormals) );
		glVertexPointer( 3, GL_FLOAT, nVertexStride, BUFFER_OFFSET(nOffsetForVertices) );

		// draw elements
		if ( _upIndexBufID != 0)
		{
			glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, _upIndexBufID );

			if ( _upSeparated == 0 )
			{
				if ( _upSeparatedTexFlag == true )
				{
					_pTexBlockRightUp->useBindInGpuProgram();
				}
				else
				{
					_pTexBlockRightDown->useBindInGpuProgram();
				}

				glDrawElements( GL_TRIANGLES, _upIndexStride, GL_UNSIGNED_SHORT, 
					BUFFER_OFFSET( 0 ));
			}
			else if ( _upSeparated == _upIndexStride )
			{
				if ( _upSeparatedTexFlag == true )
				{
					_pTexBlockLeftUp->useBindInGpuProgram();
				}
				else
				{
					_pTexBlockLeftDown->useBindInGpuProgram();
				}

				glDrawElements( GL_TRIANGLES, _upIndexStride, GL_UNSIGNED_SHORT, 
					BUFFER_OFFSET( 0 ));
			}
			else
			{

				if ( _upSeparatedTexFlag == true )
				{
					_pTexBlockLeftUp->useBindInGpuProgram();
					glDrawElements( GL_TRIANGLES, _upSeparated , GL_UNSIGNED_SHORT, 
						BUFFER_OFFSET(0));
					_pTexBlockRightUp->useBindInGpuProgram();
					glDrawElements( GL_TRIANGLES, _upIndexStride - _upSeparated , GL_UNSIGNED_SHORT, 
						BUFFER_OFFSET( _upSeparated * sizeof( short unsigned int) ));
				}
				else
				{
					_pTexBlockLeftDown->useBindInGpuProgram();
					glDrawElements( GL_TRIANGLES, _upSeparated , GL_UNSIGNED_SHORT, 
						BUFFER_OFFSET(0));
					_pTexBlockRightDown->useBindInGpuProgram();
					glDrawElements( GL_TRIANGLES, _upIndexStride - _upSeparated , GL_UNSIGNED_SHORT, 
						BUFFER_OFFSET( _upSeparated * sizeof( short unsigned int) ));
				}
			}
		}

		glDisableClientState( GL_TEXTURE_COORD_ARRAY );
		glDisableClientState( GL_NORMAL_ARRAY );
		glDisableClientState( GL_VERTEX_ARRAY );
		glDisableClientState( GL_INDEX_ARRAY );

		glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, NULL );
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, NULL );

	}
	//----------------------------------------------------------------
	void MeshChunkSlitData::renderLeftUp()
	{

		if ( _centerX < 1 )
		{
			_upSeparated = 0;
		}
		else if ( _centerX > _face1x1num )
		{
			_upSeparated = _upIndexStride + 6;
		}
		else
		{
			_upSeparated = _centerX * _upIndexStrideUnit;
		}

		if ( _centerZ < 1 )
		{
			_upSeparatedTexFlag = false;
		}
		else
		{
			_upSeparatedTexFlag = true;
		}
		//////////////////////////////////////////////////////////////////////////

		if ( _centerZ < 2 )
		{
			_leftSeparated = 0;
		}
		else if ( _centerZ > _face1x1num )
		{
			_leftSeparated = _leftIndexStride;
		}
		else
		{
			_leftSeparated = (_centerZ - 1) * _leftIndexStrideUnit;
		}

		if ( _centerX < 1 )
		{
			_leftSeparatedTexFlag = false;
		}
		else
		{
			_leftSeparatedTexFlag = true;
		}



		if ( _upIndexBufID == 0 || _leftIndexBufID == 0 )
		{
			assert(0);
			return;
		}

		//------------------------------------------
		// 开始渲染
		//------------------------------------------
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, _upVertexBufID );

		const int nVertexStride = sizeof(MeshVertex);
		const int nOffsetForNormals = sizeof(float) * 2;
		const int nOffsetForVertices = sizeof(float) * 5;

		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glEnableClientState( GL_NORMAL_ARRAY );
		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_INDEX_ARRAY );

		glTexCoordPointer( 2, GL_FLOAT, nVertexStride, BUFFER_OFFSET(0) );
		glNormalPointer( GL_FLOAT, nVertexStride, BUFFER_OFFSET(nOffsetForNormals) );
		glVertexPointer( 3, GL_FLOAT, nVertexStride, BUFFER_OFFSET(nOffsetForVertices) );

		// draw elements
		glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, _upIndexBufID );
		//glDrawElements( GL_TRIANGLES, _upIndexStride + 6 , GL_UNSIGNED_SHORT, 
		//		BUFFER_OFFSET(0));


		if ( _upSeparated == 0 )
		{
			if ( _upSeparatedTexFlag == true )
			{
				_pTexBlockRightUp->useBindInGpuProgram();
			}
			else
			{
				_pTexBlockRightDown->useBindInGpuProgram();
			}

			glDrawElements( GL_TRIANGLES, _upIndexStride + 6, GL_UNSIGNED_SHORT, 
				BUFFER_OFFSET( 0 ));
		}
		else if ( _upSeparated == (_upIndexStride + 6) )
		{
			if ( _upSeparatedTexFlag == true )
			{
				_pTexBlockLeftUp->useBindInGpuProgram();
			}
			else
			{
				_pTexBlockLeftDown->useBindInGpuProgram();
			}

			glDrawElements( GL_TRIANGLES, _upIndexStride + 6, GL_UNSIGNED_SHORT, 
				BUFFER_OFFSET( 0 ));
		}
		else
		{
			if ( _upSeparatedTexFlag == true )
			{
				_pTexBlockLeftUp->useBindInGpuProgram();
				glDrawElements( GL_TRIANGLES, _upSeparated , GL_UNSIGNED_SHORT, 
					BUFFER_OFFSET(0));
				_pTexBlockRightUp->useBindInGpuProgram();
				glDrawElements( GL_TRIANGLES, _upIndexStride + 6 - _upSeparated , GL_UNSIGNED_SHORT, 
					BUFFER_OFFSET( _upSeparated * sizeof( short unsigned int) ));
			}
			else
			{
				_pTexBlockLeftDown->useBindInGpuProgram();
				glDrawElements( GL_TRIANGLES, _upSeparated , GL_UNSIGNED_SHORT, 
					BUFFER_OFFSET(0));
				_pTexBlockRightDown->useBindInGpuProgram();
				glDrawElements( GL_TRIANGLES, _upIndexStride + 6 - _upSeparated , GL_UNSIGNED_SHORT, 
					BUFFER_OFFSET( _upSeparated * sizeof( short unsigned int) ));
			}
		}



		glBindBufferARB( GL_ARRAY_BUFFER_ARB, _leftVertexBufID );
		glTexCoordPointer( 2, GL_FLOAT, nVertexStride, BUFFER_OFFSET(0) );
		glNormalPointer( GL_FLOAT, nVertexStride, BUFFER_OFFSET(nOffsetForNormals) );
		glVertexPointer( 3, GL_FLOAT, nVertexStride, BUFFER_OFFSET(nOffsetForVertices) );
		// draw elements
		glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, _leftIndexBufID );
		//glDrawElements( GL_TRIANGLES, _leftIndexStride  , GL_UNSIGNED_SHORT, 
		//	BUFFER_OFFSET( 12 ));

		if ( _leftSeparated == 0 )
		{
			if ( _leftSeparatedTexFlag == true )
			{
				_pTexBlockLeftDown->useBindInGpuProgram();
			}
			else
			{
				_pTexBlockRightDown->useBindInGpuProgram();
			}

			glDrawElements( GL_TRIANGLES, _leftIndexStride, GL_UNSIGNED_SHORT, 
				BUFFER_OFFSET( 12 ));
		}
		else if ( _leftSeparated == _leftIndexStride )
		{
			if ( _leftSeparatedTexFlag == true )
			{
				_pTexBlockLeftUp->useBindInGpuProgram();
			}
			else
			{
				_pTexBlockRightUp->useBindInGpuProgram();
			}

			glDrawElements( GL_TRIANGLES, _leftIndexStride, GL_UNSIGNED_SHORT, 
				BUFFER_OFFSET( 12 ));
		}
		else
		{
			if ( _leftSeparatedTexFlag == true )
			{
				_pTexBlockLeftUp->useBindInGpuProgram();
				glDrawElements( GL_TRIANGLES, _leftSeparated , GL_UNSIGNED_SHORT, 
					BUFFER_OFFSET( 12 ));
				_pTexBlockLeftDown->useBindInGpuProgram();
				glDrawElements( GL_TRIANGLES, _leftIndexStride - _leftSeparated , GL_UNSIGNED_SHORT, 
					BUFFER_OFFSET( 12 + _leftSeparated * sizeof( short unsigned int) ));
			}
			else
			{
				_pTexBlockRightUp->useBindInGpuProgram();
				glDrawElements( GL_TRIANGLES, _leftSeparated , GL_UNSIGNED_SHORT, 
					BUFFER_OFFSET( 12 ));
				_pTexBlockRightDown->useBindInGpuProgram();
				glDrawElements( GL_TRIANGLES, _leftIndexStride - _leftSeparated , GL_UNSIGNED_SHORT, 
					BUFFER_OFFSET( 12 + _leftSeparated * sizeof( short unsigned int) ));
			}
		}

		glDisableClientState( GL_TEXTURE_COORD_ARRAY );
		glDisableClientState( GL_NORMAL_ARRAY );
		glDisableClientState( GL_VERTEX_ARRAY );
		glDisableClientState( GL_INDEX_ARRAY );

		glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, NULL );
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, NULL );
	}
	//----------------------------------------------------------------
	void MeshChunkSlitData::createMeshImpl()
	{
		//assert(0);
		assert( _N != 0 );
		assert( _N >= 0 );

		const int face1x1num = pow( 2.0f , _N );
		const float beginx = _cellSize * face1x1num / -2.0f;
		const float beginy = 0.0f;
		const float beginz = _cellSize * face1x1num / -2.0f;

		_face1x1num = face1x1num;
		_face2x2num = face1x1num / 2;

		_leftIndexStrideUnit = _upIndexStrideUnit = 6;
		_leftIndexStride = _upIndexStride = _upIndexStrideUnit * face1x1num;


		createUpMeshImpl(face1x1num, beginx, beginy, beginz);
		createLeftMeshImpl(face1x1num, beginx, beginy, beginz);
	}
	//----------------------------------------------------------------
	void MeshChunkSlitData::renderLeft()
	{
		//------------------------------------------
		// up上的separate
		//------------------------------------------
		if ( _centerZ < 1 )
		{
			_leftSeparated = 0;
		}
		else if ( _centerZ > _face1x1num - 1 )
		{
			_leftSeparated = _leftIndexStride;
		}
		else
		{
			_leftSeparated = _centerZ * _leftIndexStrideUnit;
		}

		if ( _centerX < 1 )
		{
			_leftSeparatedTexFlag = false;
		}
		else
		{
			_leftSeparatedTexFlag = true;
		}


		if ( _leftIndexBufID == 0 )
		{
			assert(0);
			return;
		}

		//------------------------------------------
		// 开始渲染
		//------------------------------------------
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, _leftVertexBufID );

		const int nVertexStride = sizeof(MeshVertex);
		const int nOffsetForNormals = sizeof(float) * 2;
		const int nOffsetForVertices = sizeof(float) * 5;

		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glEnableClientState( GL_NORMAL_ARRAY );
		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_INDEX_ARRAY );

		glTexCoordPointer( 2, GL_FLOAT, nVertexStride, BUFFER_OFFSET(0) );
		glNormalPointer( GL_FLOAT, nVertexStride, BUFFER_OFFSET(nOffsetForNormals) );
		glVertexPointer( 3, GL_FLOAT, nVertexStride, BUFFER_OFFSET(nOffsetForVertices) );

		// draw elements
		if ( _leftIndexBufID != 0)
		{
			glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, _leftIndexBufID );

			if ( _leftSeparated == 0 )
			{
				if ( _leftSeparatedTexFlag == true )
				{
					_pTexBlockLeftDown->useBindInGpuProgram();
				}
				else
				{
					_pTexBlockRightDown->useBindInGpuProgram();
				}

				glDrawElements( GL_TRIANGLES, _leftIndexStride, GL_UNSIGNED_SHORT, 
					BUFFER_OFFSET( 0 ));
			}
			else if ( _leftSeparated == _leftIndexStride )
			{
				if ( _leftSeparatedTexFlag == true )
				{
					_pTexBlockLeftUp->useBindInGpuProgram();
				}
				else
				{
					_pTexBlockRightUp->useBindInGpuProgram();
				}

				glDrawElements( GL_TRIANGLES, _leftIndexStride, GL_UNSIGNED_SHORT, 
					BUFFER_OFFSET( 0 ));
			}
			else
			{
				if ( _leftSeparatedTexFlag == true )
				{
					_pTexBlockLeftUp->useBindInGpuProgram();
					glDrawElements( GL_TRIANGLES, _leftSeparated , GL_UNSIGNED_SHORT, 
						BUFFER_OFFSET(0));
					_pTexBlockLeftDown->useBindInGpuProgram();
					glDrawElements( GL_TRIANGLES, _leftIndexStride - _leftSeparated , GL_UNSIGNED_SHORT, 
						BUFFER_OFFSET( _leftSeparated * sizeof( short unsigned int) ));
				}
				else
				{
					_pTexBlockRightUp->useBindInGpuProgram();
					glDrawElements( GL_TRIANGLES, _leftSeparated , GL_UNSIGNED_SHORT, 
						BUFFER_OFFSET(0));
					_pTexBlockRightDown->useBindInGpuProgram();
					glDrawElements( GL_TRIANGLES, _leftIndexStride - _leftSeparated , GL_UNSIGNED_SHORT, 
						BUFFER_OFFSET( _leftSeparated * sizeof( short unsigned int) ));
				}
			}


		}

		glDisableClientState( GL_TEXTURE_COORD_ARRAY );
		glDisableClientState( GL_NORMAL_ARRAY );
		glDisableClientState( GL_VERTEX_ARRAY );
		glDisableClientState( GL_INDEX_ARRAY );

		glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, NULL );
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, NULL );
	}
	//----------------------------------------------------------------
	void MeshChunkSlitData::createUpMeshImpl( const int face1x1num, 
		const float beginx, const float beginy, const float beginz )
	{
		//------------------------------------------
		// 1.首先创建队列
		//------------------------------------------
		const int vertexCount = 2 * (face1x1num + 2);
		//MeshVertex* vertexsUp = new MeshVertex[vertexCount];
		std::vector<MeshVertex> vertexVec;

		for ( int i = 0 ; i < face1x1num + 2 ; ++ i )
		{
			// 0 ___2___4...
			//  |  /|  /|
			//  |/__|/__|
			//  1   3   5...
			{
				MeshVertex tmp;
				tmp.tu = 1.0f;
				tmp.tv = 0.0f;

				tmp.nx = 0.0f;
				tmp.ny = 1.0f;
				tmp.nz = 0.0f;

				tmp.x = beginx + _cellSize * i;
				tmp.y = beginy;
				tmp.z = beginz;

				vertexVec.push_back( tmp );
			}

			{
				MeshVertex tmp;
				tmp.tu = 1.0f;
				tmp.tv = 0.0f;

				tmp.nx = 0.0f;
				tmp.ny = 1.0f;
				tmp.nz = 0.0f;

				tmp.x = beginx + _cellSize * i;
				tmp.y = beginy;
				tmp.z = beginz + _cellSize * 1.0f;

				vertexVec.push_back( tmp );
			}
		}

		assert( vertexVec.size() == vertexCount );
		MeshVertex* vertexsUp = new MeshVertex[vertexCount];

		memcpy( vertexsUp , &vertexVec[0] , vertexCount * sizeof( MeshVertex ) );

		std::vector<short unsigned int> indicesVec;

		for ( int i = 0 ; i < (face1x1num + 1) * 2 ; ++ i )
		{
			indicesVec.push_back( 0 + i );
			indicesVec.push_back( 1 + i );
			indicesVec.push_back( 2 + i );
		}

		assert( indicesVec.size() == (face1x1num + 1) * 2 * 3 );
		const int indicesUpCount = indicesVec.size();
		short unsigned int* indicesUp = new short unsigned int[ indicesUpCount ];

		memcpy( indicesUp , &indicesVec[0] , indicesUpCount * sizeof( short unsigned int));


		//------------------------------------------
		// 2.begin VBO vertex buffer
		//------------------------------------------
		{
			int nArrayObjectSize = sizeof(MeshVertex) * vertexCount;
			int nParam_ArrayObjectSize = 0;

			if ( nArrayObjectSize != 0 )
			{		
				glGenBuffersARB( 1, &_upVertexBufID );
				assert( _upVertexBufID != 0 );
				glBindBufferARB( GL_ARRAY_BUFFER_ARB, _upVertexBufID );
				glBufferDataARB( GL_ARRAY_BUFFER_ARB, nArrayObjectSize, vertexsUp, GL_STATIC_DRAW_ARB );

				glGetBufferParameterivARB( GL_ARRAY_BUFFER_ARB, GL_BUFFER_SIZE_ARB, &nParam_ArrayObjectSize );

				if( nParam_ArrayObjectSize <= 0 )
				{
					assert(0);
					::MessageBox(NULL,"glBufferDataARB failed to allocate any memory!",
						"ERROR",MB_OK|MB_ICONEXCLAMATION);
				}
				glBindBufferARB( GL_ARRAY_BUFFER_ARB, NULL );

				VGK_CHECK_OPENGL_ERROR();
			}
		}

		//------------------------------------------
		// begin index buffer
		//------------------------------------------
		// 主区域
		{
			int nArrayObjectSize = indicesUpCount * sizeof(short unsigned int);
			int nParam_ArrayObjectSize = 0;

			if ( nArrayObjectSize != 0 )
			{
				glGenBuffersARB( 1, &_upIndexBufID );
				assert( _upIndexBufID != 0 );
				glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, _upIndexBufID );
				glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, nArrayObjectSize, indicesUp, GL_STATIC_DRAW_ARB );

				glGetBufferParameterivARB( GL_ELEMENT_ARRAY_BUFFER_ARB, GL_BUFFER_SIZE_ARB, &nParam_ArrayObjectSize );

				if( nParam_ArrayObjectSize <= 0 )
				{
					MessageBox(NULL,"glBufferDataARB failed to allocate any memory!",
						"ERROR",MB_OK|MB_ICONEXCLAMATION);
				}
				glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, NULL );

			}
		}


		//------------------------------------------
		// 3.释放所有的内存
		//------------------------------------------

		delete[] vertexsUp;
		vertexsUp = NULL;

		delete[] indicesUp;
		indicesUp = NULL;
	}
	//----------------------------------------------------------------
	void MeshChunkSlitData::createLeftMeshImpl( const int face1x1num, 
		const float beginx, const float beginy, const float beginz )
	{
		//------------------------------------------
		// 1.首先创建队列
		//------------------------------------------
		const int vertexCount = 2 * (face1x1num + 2);
		std::vector<MeshVertex> vertexVec;

		for ( int i = 0 ; i < face1x1num + 2 ; ++ i )
		{
			// 0 ___1
			//  |  /| 
			//  |/__|
			// 2|  /|3
			//  |/__|
			// 4     5
			{
				MeshVertex tmp;
				tmp.tu = 1.0f;
				tmp.tv = 0.0f;

				tmp.nx = 0.0f;
				tmp.ny = 1.0f;
				tmp.nz = 0.0f;

				tmp.x = beginx;
				tmp.y = beginy;
				tmp.z = beginz+ _cellSize * i;

				vertexVec.push_back( tmp );
			}

			{
				MeshVertex tmp;
				tmp.tu = 1.0f;
				tmp.tv = 0.0f;

				tmp.nx = 0.0f;
				tmp.ny = 1.0f;
				tmp.nz = 0.0f;

				tmp.x = beginx + _cellSize * 1.0f;
				tmp.y = beginy;
				tmp.z = beginz + _cellSize * i;

				vertexVec.push_back( tmp );
			}
		}

		assert( vertexVec.size() == vertexCount );
		MeshVertex* vertexs = new MeshVertex[vertexCount];

		memcpy( vertexs , &vertexVec[0] , vertexCount * sizeof( MeshVertex ) );

		std::vector<short unsigned int> indicesVec;

		for ( int i = 0 ; i < (face1x1num + 1 ) * 2 ; ++ i )
		{
			indicesVec.push_back( 0 + i );
			indicesVec.push_back( 1 + i );
			indicesVec.push_back( 2 + i );
		}

		assert( indicesVec.size() == (face1x1num + 1)* 2 * 3 );
		const int indicesCount = indicesVec.size();
		short unsigned int* indicesUp = new short unsigned int[ indicesCount ];

		memcpy( indicesUp , &indicesVec[0] , indicesCount * sizeof( short unsigned int));


		//------------------------------------------
		// 2.begin VBO vertex buffer
		//------------------------------------------
		{
			int nArrayObjectSize = sizeof(MeshVertex) * vertexCount;
			int nParam_ArrayObjectSize = 0;

			if ( nArrayObjectSize != 0 )
			{		
				glGenBuffersARB( 1, &_leftVertexBufID );
				assert( _leftVertexBufID != 0 );
				glBindBufferARB( GL_ARRAY_BUFFER_ARB, _leftVertexBufID );
				glBufferDataARB( GL_ARRAY_BUFFER_ARB, nArrayObjectSize, vertexs, GL_STATIC_DRAW_ARB );

				glGetBufferParameterivARB( GL_ARRAY_BUFFER_ARB, GL_BUFFER_SIZE_ARB, &nParam_ArrayObjectSize );

				if( nParam_ArrayObjectSize <= 0 )
				{
					assert(0);
					::MessageBox(NULL,"glBufferDataARB failed to allocate any memory!",
						"ERROR",MB_OK|MB_ICONEXCLAMATION);
				}
				glBindBufferARB( GL_ARRAY_BUFFER_ARB, NULL );

				VGK_CHECK_OPENGL_ERROR();

			}
		}

		//------------------------------------------
		// begin index buffer
		//------------------------------------------
		// 主区域
		{
			int nArrayObjectSize = indicesCount * sizeof(short unsigned int);
			int nParam_ArrayObjectSize = 0;

			if ( nArrayObjectSize != 0 )
			{
				glGenBuffersARB( 1, &_leftIndexBufID );
				assert( _leftIndexBufID != 0 );
				glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, _leftIndexBufID );
				glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, nArrayObjectSize, indicesUp, GL_STATIC_DRAW_ARB );

				glGetBufferParameterivARB( GL_ELEMENT_ARRAY_BUFFER_ARB, GL_BUFFER_SIZE_ARB, &nParam_ArrayObjectSize );

				if( nParam_ArrayObjectSize <= 0 )
				{
					MessageBox(NULL,"glBufferDataARB failed to allocate any memory!",
						"ERROR",MB_OK|MB_ICONEXCLAMATION);
				}
				glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, NULL );

			}
		}


		//------------------------------------------
		// 3.释放所有的内存
		//------------------------------------------

		delete[] vertexs;
		vertexs = NULL;

		delete[] indicesUp;
		indicesUp = NULL;
	}
	//----------------------------------------------------------------



	//----------------------------------------------------------------
	MeshChunkSlit::MeshChunkSlit( MeshChunkSlitDataPtr data, 
		TerrainCenter* center ,
		float stepsize, 
		float scale , float* curposx , float* curposy , float* curposz )
	{
		_stepSize = stepsize;
		assert( _stepSize > 0 );

		//_texCenter = texcenter;
		_terrainCenter = center;

		_ppTexBlockLeftUp = NULL;
		_ppTexBlockLeftDown = NULL;
		_ppTexBlockRightUp = NULL;
		_ppTexBlockRightDown = NULL;

		_ppTexBlockLeftUp = &_terrainCenter->_pTexBlockLeftUp;
		_ppTexBlockLeftDown = &_terrainCenter->_pTexBlockLeftDown;
		_ppTexBlockRightUp = &_terrainCenter->_pTexBlockRightUp;
		_ppTexBlockRightDown = &_terrainCenter->_pTexBlockRightDown;

		_data = data;

		_pCurrentPosX = curposx;
		_pCurrentPosZ = curposz;
		_pCurrentPosY = curposy;

		_scale = scale;

		_renderUp = false;
		_renderLeft = false;
	}
	//----------------------------------------------------------------
	void MeshChunkSlit::render(const int& transXint , const int& transZint )
	{
		update( transXint , transZint );

		//glPushMatrix();
		//	glPointSize( 10.0f );
		//	glDisable(GL_TEXTURE_2D );
		//	glColor3f(1,0,0);
		//	glBegin( GL_POINTS );
		//		glVertex3f( _centerX , 150.0f , _centerZ );
		//	glEnd();
		//glPopMatrix();

		glPushMatrix();
		glScalef( _scale , 1.0f , _scale );


		_data->render( 
			_renderUp,
			_renderLeft,
			_centerX , 
			_centerZ , 
			*_ppTexBlockLeftUp,
			*_ppTexBlockLeftDown,
			*_ppTexBlockRightUp,
			*_ppTexBlockRightDown );

		glPopMatrix();
	}

	void MeshChunkSlit::update( const int& transXint , const int& transZint )
	{
		_centerX = transXint + floor( _terrainCenter->getLogicCenterX() / _stepSize );
		_centerZ = transZint + floor( _terrainCenter->getLogicCenterZ() / _stepSize );
	}
	//----------------------------------------------------------------


}// end of namespace vgTerritory
