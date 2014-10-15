


#include <vgStableHeaders.h>
#include <vgTerritory/vgMeshChunkTop.h>
#include <vgMesh/vgmMeshManager.h>
#include <vgKernel/vgkOpenGLSupport.h>


namespace vgTerritory {
	
	
	GLvoid*** MeshChunkTopData::_indicesTable = NULL;
	GLsizei** MeshChunkTopData::_countTable = NULL;
	GLsizei*	MeshChunkTopData::_wholeCount = NULL;

	int MeshChunkTopData::_face2x2num = 0;

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

	//----------------------------------------------------------------
	MeshChunkTopData::MeshChunkTopData()
	{
		setDefault();

	}
	//----------------------------------------------------------------
	MeshChunkTopData::~MeshChunkTopData()
	{

	}
	//----------------------------------------------------------------
	void MeshChunkTopData::setDefault()
	{
		_initialised = false;

		__xnum = 0;
		__znum = 0;
		__xLength = 0.0f;
		__zLength = 0.0f;
		__beginx = 0.0f;
		__beginy = 0.0f;
		__beginz = 0.0f;


		__vertCount = 0;
		__vertices = NULL;
		__indexsCount = 0;
		__indexs = NULL;

		__vertexBufferID = 0;
		__indexBufferID = 0;

		__nx = 0;
		__nz = 0;

	}
	//----------------------------------------------------------------
	void MeshChunkTopData::destroy()
	{
		destroyMemData();

		destroyVboData();

		setDefault();
	}
	//----------------------------------------------------------------
	bool MeshChunkTopData::renderLargeArea(const int& texcenterx , 
		const int& texcenterz , 
		ElevationItem* leftup , 
		ElevationItem* leftdown ,
		ElevationItem* rightup ,
		ElevationItem* rightdown)
	{
		if( _initialised == false )
		{
			return false;
		}

		//------------------------------------------
		// 开始渲染
		//------------------------------------------
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, __vertexBufferID );

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
		if ( __indexBufferID != 0)
		{
			glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, __indexBufferID );

			//glDrawElements( GL_TRIANGLES, __indexsCount , GL_UNSIGNED_SHORT, 
			//	BUFFER_OFFSET(0));

			getDrawingDataFromTable( texcenterx, texcenterz,
				_drawingData[0] , 
				_drawingData[1] , 
				_drawingData[2] , 
				_drawingData[3] );

			// leftup
			if ( leftup != NULL )
			{
				leftup->useBindInGpuProgram();
			}
			_drawingData[0].draw();

			// rightup
			if ( rightup != NULL )
			{
				rightup->useBindInGpuProgram();
			}
			_drawingData[1].draw();

			// leftdown
			if ( leftdown != NULL )
			{
				leftdown->useBindInGpuProgram();
			}
			_drawingData[2].draw();

			// rightdown
			if ( rightdown != NULL )
			{
				rightdown->useBindInGpuProgram();
			}
			_drawingData[3].draw();
		}

		glDisableClientState( GL_TEXTURE_COORD_ARRAY );
		glDisableClientState( GL_NORMAL_ARRAY );
		glDisableClientState( GL_VERTEX_ARRAY );
		glDisableClientState( GL_INDEX_ARRAY );

		glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, NULL );
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, NULL );

		return true;
	}
	//----------------------------------------------------------------
	bool MeshChunkTopData::renderSmallPieces( const bool& renderinner , const bool& renderouter )
	{
		assert(0);

#if 0
		if( _initialised == false )
		{
			return false;
		}


		glBindBufferARB( GL_ARRAY_BUFFER_ARB, __vertexBufferID );


		const int nVertexStride = sizeof(MeshVertex);
		const int nOffsetForNormals = sizeof(float) * 2;
		const int nOffsetForVertices = sizeof(float) * 5;

		//glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		//glEnableClientState( GL_NORMAL_ARRAY );
		//glEnableClientState( GL_VERTEX_ARRAY );
		//glEnableClientState( GL_INDEX_ARRAY );

		//glTexCoordPointer( 2, GL_FLOAT, nVertexStride, BUFFER_OFFSET(0) );
		//glNormalPointer( GL_FLOAT, nVertexStride, BUFFER_OFFSET(nOffsetForNormals) );
		glVertexPointer( 3, GL_FLOAT, nVertexStride, BUFFER_OFFSET(nOffsetForVertices) );

		if ( __innerIndexID != 0 && renderinner == true )
		{
			glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, __innerIndexID );
			glDrawElements( GL_TRIANGLES, __innerCount , GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
		}
		else if ( __innerPlusID != 0 )
		{
			glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, __innerPlusID );
			glDrawElements( GL_TRIANGLES, __innerPlusCount , GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
		}


		if ( __outerIndexID != 0 && renderouter == true )
		{
			glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, __outerIndexID );
			glDrawElements( GL_TRIANGLES, __outerCount , GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
		}


		//glDisableClientState( GL_TEXTURE_COORD_ARRAY );
		//glDisableClientState( GL_NORMAL_ARRAY );
		//glDisableClientState( GL_VERTEX_ARRAY );
		//glDisableClientState( GL_INDEX_ARRAY );

		glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, NULL );
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, NULL );

#endif

		return true;
	}
	//----------------------------------------------------------------
	bool MeshChunkTopData::createFromParameters( 
		const int& xnum, const int& znum ,
		const float& xlength , const float& zlength, const float& centerx,
		const float& centery , const float& centerz )
	{
		__xnum = xnum;
		__znum = znum;
		__xLength = xlength;
		__zLength = zlength;

		__beginx = -__xLength / 2.0f + centerx;
		__beginy = centery;
		__beginz = -__zLength / 2.0f + centerz;



		//case CMMP_NORMAL:
		__vertCount = __xnum * __znum;

		assert( __vertCount != 0 );


		__vertices = new MeshVertex[ __vertCount ];
		//__indexsCount = (__xnum -1) * ( __znum -1 ) * 6 ;
		//assert( __vertCount != 0 );
		//__indexs = new int[ __indexsCount ];

		__nx = __xLength / (float)(__xnum-1);
		__nz = __zLength / (float)(__znum-1);

		if ( _face2x2num == 0 )
		{
			_face2x2num = (__xnum -1) / 2;
		}

		if ( _indicesTable == NULL )
		{
			assert(  _countTable == NULL );

			buildIndicesTables( _face2x2num , _indicesTable , _countTable );
		}


		createMeshImpl();


		_initialised = true;

		return true;
	}
	//----------------------------------------------------------------
	void MeshChunkTopData::createMeshImpl()
	{
		assert( _initialised == false);

		//------------------------------------------
		// 首先给vetices赋值
		//------------------------------------------
		const float ntu = (1.0f/(float)(__xnum-1));
		const float ntv = (1.0f/(float)(__znum-1));

		// 先把所有的参数设置为默认
		for ( int i = 0 ; i < __vertCount ; ++ i )
		{
			__vertices[i].x = 0;
			__vertices[i].y = __beginy;
			__vertices[i].z = 0;

			__vertices[i].tu = /*ntu * (i % __xnum)*/0;
			__vertices[i].tv = /*ntv * (i / __xnum)*/0;

			__vertices[i].nx = 0.0f;
			__vertices[i].ny = 1.0f;
			__vertices[i].nz = 0.0f;
		}

		// 开始设置重要参数
		for ( int i = 0 ; i < __xnum * __znum ; ++ i )
		{
			__vertices[i].x = __beginx + __nx * (i % __xnum);

			//if ( i % __xnum == 0 )
			//{
			//	__vertices[i].y = __beginy + __nx * 3.0f;

			//	if ( i == 0 )
			//	{
			//		__vertices[i].y = __beginy + __nx * 10.0f;
			//	}
			//}

			__vertices[i].z = __beginz + __nz * (i / __xnum);

			__vertices[i].tu = ntu * (i % __xnum);
			__vertices[i].tv = ntv * (i / __xnum);
		}


		//------------------------------------------
		// 创建索引
		//------------------------------------------
		std::vector<short unsigned int> tmpindexbuf;


		assert( __xnum == __znum );
		int facenum = __xnum - 1;

		assert( facenum %2 == 0 );
		int facenumhalf = facenum / 2;

		// 遍历每4个面, 注意,每4个小面一格.
		for ( int i = 0 ; i < facenumhalf * facenumhalf ; ++i )
		{
			if ( i == 0 )
			{
				// 插入左上角的特例
				insertLeftUpFaceindex( facenum , tmpindexbuf);
			}
			else if ( i / facenumhalf == 0 || i % facenumhalf == 0 )
			{
				// 插入up和left
				insertFaceindex( i , facenum , tmpindexbuf , true );
			}
			else
			{
				insertFaceindex( i , facenum , tmpindexbuf , false );
			}

		}
	
		// 复制到最终数据区
		// 复制主区域
		__indexsCount = tmpindexbuf.size();
		assert( __indexsCount % 3 == 0 );
		__indexs = new short unsigned int[ __indexsCount ];

		for ( unsigned int i = 0 ; i < __indexsCount ; ++i )
		{
			__indexs[i] = tmpindexbuf[i];
		}


		//------------------------------------------
		// begin VBO vertex buffer
		//------------------------------------------

		int nArrayObjectSize = sizeof(MeshVertex) * __vertCount;
		int nParam_ArrayObjectSize = 0;

		if ( nArrayObjectSize != 0 )
		{		
			glGenBuffersARB( 1, &__vertexBufferID );
			assert( __vertexBufferID != 0 );
			glBindBufferARB( GL_ARRAY_BUFFER_ARB, __vertexBufferID );
			glBufferDataARB( GL_ARRAY_BUFFER_ARB, nArrayObjectSize, __vertices, GL_STATIC_DRAW_ARB );

			glGetBufferParameterivARB( GL_ARRAY_BUFFER_ARB, GL_BUFFER_SIZE_ARB, &nParam_ArrayObjectSize );

			if( nParam_ArrayObjectSize <= 0 )
			{
				assert(0);
				::MessageBox(NULL,"glBufferDataARB failed to allocate any memory!",
					"ERROR",MB_OK|MB_ICONEXCLAMATION);
			}
			glBindBufferARB( GL_ARRAY_BUFFER_ARB, NULL );


#if _DEBUG
			//VGK_CHECK_OPENGL_ERROR();
#endif
		}

		//------------------------------------------
		// begin index buffer
		//------------------------------------------
		// 主区域
		{
			int nArrayObjectSize = __indexsCount * sizeof(short unsigned int);
			int nParam_ArrayObjectSize = 0;

			if ( nArrayObjectSize != 0 )
			{
				glGenBuffersARB( 1, &__indexBufferID );
				assert( __indexBufferID != 0 );
				glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, __indexBufferID );
				glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, nArrayObjectSize, __indexs, GL_STATIC_DRAW_ARB );

				glGetBufferParameterivARB( GL_ELEMENT_ARRAY_BUFFER_ARB, GL_BUFFER_SIZE_ARB, &nParam_ArrayObjectSize );

				if( nParam_ArrayObjectSize <= 0 )
				{
					MessageBox(NULL,"glBufferDataARB failed to allocate any memory!",
						"ERROR",MB_OK|MB_ICONEXCLAMATION);
				}
				glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, NULL );

			}
		}


		VGK_CHECK_OPENGL_ERROR();

		destroyMemData();

		return;
	}
	//----------------------------------------------------------------
	void MeshChunkTopData::destroyVboData()
	{
		VGK_CHECK_OPENGL_ERROR();

		if ( __vertexBufferID != 0 )
		{
			glDeleteBuffersARB( 1, &__vertexBufferID ); 
			__vertexBufferID = 0;
		}

		if ( __indexBufferID != 0 )
		{
			glDeleteBuffersARB( 1, &__indexBufferID);
			__indexBufferID = 0;
		}


		VGK_CHECK_OPENGL_ERROR();
	}
	//----------------------------------------------------------------
	void MeshChunkTopData::destroyMemData()
	{
		if ( __vertices != NULL )
		{
			delete[] __vertices;
			__vertices = NULL;
		}

		if ( __indexs != NULL )
		{
			delete[] __indexs;
			__indexs = NULL;
		}
	}
	//----------------------------------------------------------------
	void MeshChunkTopData::insertLeftUpFaceindex( int facexnum , 
		std::vector<short unsigned int>& outvec )
	{
		int facei[] = { 0 , 1 , facexnum , facexnum + 1 }; 

		// 遍历每一个面
		for ( int j = 0 ; j < 4 ; ++ j )
		{
			insertSingleFace(facei[j] , facexnum, outvec);
		}

		//------------------------------------------
		// 插入2个空的三角形
		//------------------------------------------
		for ( int k = 0 ; k < 2 ; ++ k )
		{
			outvec.push_back( 0 );
			outvec.push_back( 0 );
			outvec.push_back( 0 );
		}
	}
	//----------------------------------------------------------------
	void MeshChunkTopData::insertFaceindex( int facei2x2 , int facexnum , 
		std::vector<short unsigned int>& outvec , const bool& insertemptyindex)
	{
		int facehang = (facei2x2 * 2) / facexnum;
		int facelie = facei2x2 % ( facexnum /2 );

		int facebegin = facehang * facexnum * 2 + facelie * 2;

		int facei[] = { facebegin , facebegin + 1 , 
			facebegin + facexnum , facebegin + facexnum + 1 }; 

		for ( int j = 0 ; j < 4 ; ++ j )
		{
			insertSingleFace(facei[j] , facexnum, outvec);
		}

		if ( insertemptyindex == true )
		{
			//------------------------------------------
			// 插入1个空的三角形
			//------------------------------------------
			for ( int k = 0 ; k < 1 ; ++ k )
			{
				outvec.push_back( 0 );
				outvec.push_back( 0 );
				outvec.push_back( 0 );
			}
		}
	}
	//----------------------------------------------------------------
	void MeshChunkTopData::insertSingleFace( int i, int facexnum,
		std::vector<short unsigned int> &outvec )
	{
		int hang = i / facexnum;
		int next_hang = (i + facexnum) / facexnum;

		/*CMM_UP_LEFT_COARSER 的情况*/
		if ( i % facexnum == 0 )
		{
			// 插入左边一列coarser三角形序列
			if ( i % (facexnum*2) == 0 )
			{
				int next_next_hang = (i + facexnum + facexnum) / facexnum;
				//如果是偶数时,先插入大三角形
				// 0 ___ 
				//  |\  | 
				//  |__\|
				//  |  /|2
				//  |/__|
				//  1
				outvec.push_back( i + hang );
				outvec.push_back(  i + next_next_hang + facexnum +  facexnum);
				outvec.push_back(  i + next_hang + facexnum + 1 );

				if ( i == 0 )
				{
					// 插入靠右边的大三角形
					// 0 ___ ___1
					//  |\     /|
					//  |__\_/__|
					//      2
					outvec.push_back( i + hang );
					outvec.push_back(  i + hang + 2 );
					outvec.push_back(  i + next_hang + facexnum + 1 );
				}
				else
				{
					// 然后插入小三角形
					//  0___1
					//  |\  |
					//  |__\|
					//      2
					outvec.push_back( i + hang );
					outvec.push_back(  i + hang + 1);
					outvec.push_back(  i + next_hang + facexnum + 1 );
				}
			}
			else
			{
				// 奇数时,插入小三角形
				//   ___ 0
				//  |  /|
				//  |/__|
				// 1    2
				outvec.push_back( i + hang + 1 );
				outvec.push_back( i + next_hang + facexnum);
				outvec.push_back( i + next_hang + facexnum + 1 );
			}

			return;
		}

		if ( i < facexnum )
		{
			// 插入上面一行coarser三角形序列
			if ( i % 2 == 0 )
			{
				if ( i == 0 )
				{
					// 不管第一个小面的插入
					return;
				}

				//如果是偶数时,先插入大三角形
				// 0 ___ ___1
				//  |\     /|
				//  |__\_/__|
				//      2
				outvec.push_back( i + hang );
				outvec.push_back(  i + hang + 2 );
				outvec.push_back(  i + next_hang + facexnum + 1 );

				// 然后插入小三角形
				//  0___ 
				//  |\  |
				//  |__\|
				// 1    2
				outvec.push_back( i + hang );
				outvec.push_back(  i + next_hang + facexnum);
				outvec.push_back(  i + next_hang + facexnum + 1 );
			}
			else
			{
				// 奇数时,插入小三角形
				//   ___ 0
				//  |  /|
				//  |/__|
				// 1    2
				outvec.push_back( i + hang + 1 );
				outvec.push_back( i + next_hang + facexnum);
				outvec.push_back( i + next_hang + facexnum + 1 );
			}
			return;
		}

		// 0 ___ 1
		//  |  /|
		//  |/__|
		// 2

		outvec.push_back( i + hang );
		outvec.push_back(  i + hang + 1);
		outvec.push_back(  i + next_hang + facexnum);

		// Second triangle of the current quad
		//   ___ 0
		//  |  /|
		//  |/__|
		// 1    2

		outvec.push_back( i + hang + 1 );
		outvec.push_back( i + next_hang + facexnum);
		outvec.push_back( i + next_hang + facexnum + 1 );

		return;
	}
	//----------------------------------------------------------------
	void MeshChunkTopData::buildIndicesTables( const int& face2x2num ,
		GLvoid*** &outIndicesTable , GLsizei** &outCountTable  )
	{
		const int face_stride = 24;
		const int face_stride_in_char = 24 * sizeof( short unsigned int);

		//------------------------------------------
		// 处理Count
		//------------------------------------------
		_wholeCount = new GLsizei;
		*_wholeCount = face2x2num * face2x2num * face_stride;

		//------------------------------------------
		// 处理countTable
		//------------------------------------------
		outCountTable = new GLsizei*[face2x2num];

		for ( int k = 0 ; k < face2x2num ; ++ k )
		{
			outCountTable[k] = new GLsizei[face2x2num];
		}

		for ( int i = 0 ; i < face2x2num ; ++i )
		{
			for ( int j = 0 ; j < face2x2num ; ++j)
			{
				outCountTable[i][j] = i * face_stride;
			}
		}

		//------------------------------------------
		// 处理indicesTable
		//------------------------------------------

		outIndicesTable = new GLvoid**[face2x2num];


		for ( int k = 0 ; k < face2x2num ; ++k )
		{
			outIndicesTable[k] = new GLvoid*[face2x2num];
		}

		for ( int i = 0 ; i < face2x2num ; ++i )
		{
			for ( int j = 0 ; j < face2x2num ; ++j)
			{
				outIndicesTable[i][j] =
					BUFFER_OFFSET( ( i + j * face2x2num ) * face_stride_in_char);
			}
		}

		return;
	}
	//----------------------------------------------------------------
	void MeshChunkTopData::getDrawingDataFromTable( const int& in_x , 
		const int& in_y , MeshDrawingData& leftup , MeshDrawingData& rightup ,
		MeshDrawingData& leftdown , MeshDrawingData& rightdown )
	{
		assert( _indicesTable != NULL );
		assert( _countTable != NULL );
		
		static const int faceRowStride = 24 * _face2x2num;

		//------------------------------------------
		// 处理特殊的情况
		//------------------------------------------
		if ( in_x < 1 )
		{
			// 当X在左侧时
			if ( in_y < 1 )
			{
				rightdown._counts = _wholeCount;
				rightdown._indices = _indicesTable[ 0 ];
				rightdown._primcount = 1;

				leftup.setNull();
				rightup.setNull();
				leftdown.setNull();
			}
			else if( in_y > _face2x2num - 1 )
			{
				rightup._counts = _wholeCount;
				rightup._indices = _indicesTable[ 0 ];
				rightup._primcount = 1;

				leftup.setNull();
				rightdown.setNull();
				leftdown.setNull();
			}
			else
			{
				rightup._splitCount = faceRowStride * in_y;
				rightup._counts = &rightup._splitCount;
				rightup._indices = _indicesTable[ 0 ];
				rightup._primcount = 1;

				rightdown._splitCount = *_wholeCount - rightup._splitCount;
				rightdown._counts = &rightdown._splitCount;
				rightdown._indices = rightup._indices + in_y;
				rightdown._primcount = 1;

				leftup.setNull();
				leftdown.setNull();
			}

			return;
		}
		else if ( in_x > _face2x2num - 1)
		{
			// 当X在右侧时
			if ( in_y < 1 )
			{
				leftdown._counts = _wholeCount;
				leftdown._indices = _indicesTable[ 0 ];
				leftdown._primcount = 1;

				leftup.setNull();
				rightup.setNull();
				rightdown.setNull();
			}
			else if( in_y > _face2x2num - 1 )
			{
				leftup._counts = _wholeCount;
				leftup._indices = _indicesTable[ 0 ];
				leftup._primcount = 1;

				rightup.setNull();
				rightdown.setNull();
				leftdown.setNull();
			}
			else
			{
				leftup._splitCount = faceRowStride * in_y;
				leftup._counts = &leftup._splitCount;
				leftup._indices = _indicesTable[ 0 ];
				leftup._primcount = 1;

				leftdown._splitCount = *_wholeCount - leftup._splitCount;
				leftdown._counts = &leftdown._splitCount;
				leftdown._indices = leftup._indices + in_y;
				leftdown._primcount = 1;

				rightup.setNull();
				rightdown.setNull();
			}

			return;
		}
		else
		{
			// 但X夹在中间的时候
			// 当X在右侧时
			if ( in_y < 1 )
			{
				leftdown._counts = _countTable[ in_x ];
				leftdown._indices = _indicesTable[ 0 ] ;
				leftdown._primcount = _face2x2num;


				rightdown._counts = _countTable[ _face2x2num - in_x ];
				rightdown._indices = _indicesTable[ in_x ];
				rightdown._primcount = _face2x2num;
				
				leftup.setNull();
				rightup.setNull();
			}
			else if( in_y > _face2x2num - 1 )
			{
				leftup._counts = _countTable[ in_x ];
				leftup._indices = _indicesTable[ 0 ] ;
				leftup._primcount = _face2x2num;


				rightup._counts = _countTable[ _face2x2num - in_x ];
				rightup._indices = _indicesTable[ in_x ];
				rightup._primcount = _face2x2num;

				leftdown.setNull();
				rightdown.setNull();
			}
			else
			{
				leftup._counts = _countTable[ in_x ];
				leftup._indices = _indicesTable[ 0 ];
				leftup._primcount = in_y;

				leftdown._counts = leftup._counts;
				leftdown._indices = leftup._indices + in_y;
				leftdown._primcount = _face2x2num - in_y;


				rightup._counts = _countTable[ _face2x2num - in_x ];
				rightup._indices = _indicesTable[ in_x ];
				rightup._primcount = in_y;

				rightdown._counts = rightup._counts;
				rightdown._indices = rightup._indices + in_y;
				rightdown._primcount = _face2x2num - in_y;
			}

			return;
		}


		assert(0);

		return;

#if 0

		const int face_stride = 24;
		const int face_stride_in_char = 24 * sizeof( short unsigned int);

		//glDrawElements( GL_TRIANGLES, 64 * face_stride , GL_UNSIGNED_SHORT, 
		//	BUFFER_OFFSET(0));


		const int in_x = 2;
		const int in_y = 3;

		const int face2x2num = (__xnum - 1)/2;

		GLvoid** indices = new GLvoid*[ face2x2num ];

		for ( int i = 0 ; i < face2x2num ; ++i )
		{
			indices[i] = BUFFER_OFFSET( i * face2x2num * face_stride_in_char);
		}

		GLsizei* counts = new GLsizei[ face2x2num ];

		for ( int i = 0 ; i < face2x2num ; ++i )
		{
			counts[i] = in_x * face_stride;
		}

		glMultiDrawElements( GL_TRIANGLES, counts , GL_UNSIGNED_SHORT, 
			(const GLvoid**)indices , in_y );


		delete[] indices;
		delete[] counts;
#endif



		return;
	}
	//----------------------------------------------------------------


	
	//----------------------------------------------------------------
	MeshChunkTop::MeshChunkTop( MeshChunkTopDataPtr data , 
		float stepsize , 
		float offsetx , float offsetz ,
		float offset_unit, int rotate , 
		TerrainCenter* center,
		float* curposx , float* curposy , 
		float* curposz )
	{
		_pCurrentPosX = curposx;
		_pCurrentPosZ = curposz;
		_pCurrentPosY = curposy;

		_stepSize = stepsize;

		_viewFrustum = vgCam::CamManager::getSingleton().getCurrentFrustum();

		_sceneBound = ElevationManager::getSingleton().getValidSceneBound();

		_data = data;
		_offsetX = offsetx;
		_offsetZ = offsetz;
		_offsetUnit = offset_unit;
		_rotate = rotate;
		_terrainCenter = center;

		switch( _rotate )
		{
		case 0:
			_centerX = _data->_face2x2num - _terrainCenter->getLogicCenterX();
			_centerZ = _data->_face2x2num - _terrainCenter->getLogicCenterZ();
			_ppTexBlockLeftUp = &_terrainCenter->_pTexBlockLeftUp;
			_ppTexBlockLeftDown = &_terrainCenter->_pTexBlockLeftDown;
			_ppTexBlockRightUp = &_terrainCenter->_pTexBlockRightUp;
			_ppTexBlockRightDown = &_terrainCenter->_pTexBlockRightDown;
			break;
		case 90:
			_centerX = _data->_face2x2num + _terrainCenter->getLogicCenterZ();
			_centerZ = _data->_face2x2num - _terrainCenter->getLogicCenterX();
			_ppTexBlockLeftUp = &_terrainCenter->_pTexBlockLeftDown;
			_ppTexBlockLeftDown = &_terrainCenter->_pTexBlockRightDown;
			_ppTexBlockRightUp = &_terrainCenter->_pTexBlockLeftUp;
			_ppTexBlockRightDown = &_terrainCenter->_pTexBlockRightUp;
			break;
		case 180:
			_centerX = _data->_face2x2num + _terrainCenter->getLogicCenterX();
			_centerZ = _data->_face2x2num + _terrainCenter->getLogicCenterZ();
			_ppTexBlockLeftUp = &_terrainCenter->_pTexBlockRightDown;
			_ppTexBlockLeftDown = &_terrainCenter->_pTexBlockRightUp;
			_ppTexBlockRightUp = &_terrainCenter->_pTexBlockLeftDown;
			_ppTexBlockRightDown = &_terrainCenter->_pTexBlockLeftUp;
			break;
		case 270:
			_centerX = _data->_face2x2num - _terrainCenter->getLogicCenterZ();
			_centerZ = _data->_face2x2num + _terrainCenter->getLogicCenterX();
			_ppTexBlockLeftUp = &_terrainCenter->_pTexBlockRightUp;
			_ppTexBlockLeftDown = &_terrainCenter->_pTexBlockLeftUp;
			_ppTexBlockRightUp = &_terrainCenter->_pTexBlockRightDown;
			_ppTexBlockRightDown = &_terrainCenter->_pTexBlockLeftDown;
			break;
		default:
			assert(0);
			break;
		}
	}
	//----------------------------------------------------------------
	MeshChunkTop::~MeshChunkTop()
	{

	}
	//----------------------------------------------------------------
	void MeshChunkTop::update( const int& transX , const int& transZ )
	{
		switch( _rotate )
		{
		case 0:
			_centerX = _data->_face2x2num - transX - 
				floor( _terrainCenter->getLogicCenterX() / _stepSize );

			_centerZ = _data->_face2x2num - transZ -
				floor( _terrainCenter->getLogicCenterZ() / _stepSize );
			break;
		case 90:
			_centerX = _data->_face2x2num + transZ + 
				floor( _terrainCenter->getLogicCenterZ() / _stepSize );

			_centerZ = _data->_face2x2num - transX - 
				floor( _terrainCenter->getLogicCenterX() / _stepSize );
			break;
		case 180:
			_centerX = _data->_face2x2num + transX + 
				floor( _terrainCenter->getLogicCenterX() / _stepSize );
			_centerZ = _data->_face2x2num + transZ + 
				floor( _terrainCenter->getLogicCenterZ() / _stepSize );
			break;
		case 270:
			_centerX = _data->_face2x2num - transZ -
				floor( _terrainCenter->getLogicCenterZ() / _stepSize );
			_centerZ = _data->_face2x2num + transX +
				floor( _terrainCenter->getLogicCenterX() / _stepSize );
			break;
		default:
			assert(0);
			break;
		}

		return;
	}
	//----------------------------------------------------------------
	void MeshChunkTop::render( const int& transIntX , const int& transIntZ )
	{
		update( transIntX , transIntZ );


		if ( _viewFrustum->testBoxInFrustum(
			*_pCurrentPosX + _offsetX, 0.0f , 
			*_pCurrentPosZ + _offsetZ, _offsetUnit ) == false )
		{
			return;
		}

		_tmpBound.minPos.x = *_pCurrentPosX + _offsetX - _offsetUnit;
		_tmpBound.maxPos.x = *_pCurrentPosX + _offsetX + _offsetUnit;
		_tmpBound.minPos.y = *_pCurrentPosZ + _offsetZ - _offsetUnit;
		_tmpBound.maxPos.y = *_pCurrentPosZ + _offsetZ + _offsetUnit;

		if ( _sceneBound.testIntersection( _tmpBound ) == false )
		{
			return;
		}

		glPushMatrix();
		glRotatef( (GLfloat)_rotate , 0.0f , 1.0f , 0.0f ); 

		_data->renderLargeArea( 
			_centerX , 
			_centerZ , 
			*_ppTexBlockLeftUp,
			*_ppTexBlockLeftDown,
			*_ppTexBlockRightUp,
			*_ppTexBlockRightDown );

		glPopMatrix();

		return;
	}
	//----------------------------------------------------------------



}// end of namespace vgTerritory
