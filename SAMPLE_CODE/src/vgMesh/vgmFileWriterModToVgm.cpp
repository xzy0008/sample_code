


#include <vgStableHeaders.h>
#include <vgMesh/vgmFileDefinitionMod.h>

#include <vgMesh/vgmFileReaderMod.h>
#include <vgMesh/vgmFileWriterModToVgm.h>
#include <vgKernel/vgkCrcUtility.h>


namespace vgMesh {
	
	
	
	
	//----------------------------------------------------------------
	bool FileWriterModToVgm::writeToVgmFileFromModStream(
		const vgKernel::StreamReaderPtr preader ,
		const String& save_absolute_path, const float& lod0_factor , 
		const float& lod1_factor ,
		const float& squareDistNear , const float& squareDistFar )
	{
		assert( squareDistNear < squareDistFar );
		assert( squareDistFar > 0 );
		assert( squareDistNear > 0 );

		//------------------------------------------
		// 首先做检查
		//------------------------------------------
		if ( lod0_factor <= 0 || lod1_factor <= 0 ||
			lod0_factor >= 1.0f || lod1_factor >= 1.0f ||
			lod0_factor > lod1_factor )
		{
			MessageBox( NULL , "输入的参数不正确" , "Error" , MB_OK );
			return false;
		}

		vgKernel::StreamWriterPtr pwriter = 
			vgKernel::StreamWriterFactory::createFromFile( save_absolute_path );

		if ( pwriter.isNull() == true )
		{
			return false;
		}

		ModObjPtrVector* modobjs = 
			FileReaderMod::readFromStream( preader );

		if ( modobjs == NULL )
		{
			return false;
		}

		assert( pwriter.isNull() == false );


		size_t objnum = modobjs->size();
		long beginpos = pwriter->tell();
		long filesize = 0;

		assert( objnum > 0 );




		//------------------------------------------
		// 1.首先写Vgm头文件
		//------------------------------------------
		VgmHeader *vgmheader = new VgmHeader;
		VgmBrief *vgmbriefs = new VgmBrief[objnum];
		VgmDataStruct *vgmdatas = new VgmDataStruct[objnum];

		//------------------------------------------
		// 赋值lod的参数
		//------------------------------------------
		for ( size_t i = 0 ; i < objnum ; ++i )
		{
			vgmbriefs[i]._squaredDistanceOfLodFar = squareDistFar;
			vgmbriefs[i]._squaredDistanceOfLodNear = squareDistNear;
		}

		// 先写,之后重写以更改
		pwriter->write( (char*)vgmheader , sizeof( VgmHeader) );

		vgmheader->_positionOfBriefs = pwriter->tell();
		vgmheader->_numberOfBriefs = objnum;

		pwriter->write( (char*)vgmbriefs , sizeof( VgmBrief ) * objnum );

		// 分别拷贝数据,并清理mod数据
		for ( size_t i = 0 ; i < objnum ; ++i )
		{
			vgmbriefs[i].getInfoFromModObject( (*modobjs)[i].getPointer() );
			vgmdatas[i].getInfoFromModObject( (*modobjs)[i].getPointer() );

			(*modobjs)[i].setNull();
		}

		delete modobjs;

		//------------------------------------------
		// 2.写VgmData
		//------------------------------------------
		for ( size_t i = 0 ; i < objnum ; ++i )
		{


			//------------------------------------------
			// 在这里创建lod并写入文件
			//------------------------------------------
			VgmDataStruct* lod0 = 
				getVgmDataStructByLodParam( &vgmdatas[i] , lod0_factor , &vgmbriefs[i]);
			assert( lod0 != NULL );

			VgmDataStruct* lod1 = 
				getVgmDataStructByLodParam( &vgmdatas[i] , lod1_factor , &vgmbriefs[i]);
			assert( lod1 != NULL );

			long databegpos = pwriter->tell();
			long datalen = vgmdatas[i].writeToStream( pwriter );

			long lod1begpos = pwriter->tell();
			datalen += lod1->writeToStream( pwriter );

			long lod0begpos = pwriter->tell();
			datalen += lod0->writeToStream( pwriter );

			long dataendpos = pwriter->tell();
			assert( (databegpos + datalen ) == dataendpos );

			pwriter->flush();

			// update brief
			vgmbriefs[i]._positionOfFile		= databegpos;
			vgmbriefs[i]._lengthOfFile			= datalen;

			// 最清晰一级
			vgmbriefs[i]._positionOfMeshData[2]	= databegpos;
			vgmbriefs[i]._lengthOfMeshData[2]		= lod1begpos - databegpos;
			vgmbriefs[i]._positionOfMeshDataPlus[2] = lod1begpos;
			vgmbriefs[i]._lengthOfMeshPlus[2]		= 0;

			// 中间级
			vgmbriefs[i]._positionOfMeshData[1]	= lod1begpos;
			vgmbriefs[i]._lengthOfMeshData[1]		= lod0begpos - lod1begpos;
			vgmbriefs[i]._positionOfMeshDataPlus[1] = lod0begpos;
			vgmbriefs[i]._lengthOfMeshPlus[1]		= 0;

			// 最不清晰一级
			vgmbriefs[i]._positionOfMeshData[0]	= lod0begpos;
			vgmbriefs[i]._lengthOfMeshData[0]		= dataendpos - lod0begpos;
			vgmbriefs[i]._positionOfMeshDataPlus[0] = dataendpos;
			vgmbriefs[i]._lengthOfMeshPlus[0]		= 0;

			//------------------------------------------
			// 清空这些数据
			//------------------------------------------
			vgmdatas[i].destroy();
			if (&vgmdatas[i] != lod0)
			{
				delete lod0;
			}
			if (&vgmdatas[i] != lod1)
			{
				delete lod1;
			}
		}

		long endpos = pwriter->tell();


		// update header
		// 注意要加上校验码,4个字节
		vgmheader->_sizeOfWholeFile = endpos - beginpos + 4;
		assert( vgmheader->_sizeOfWholeFile > 4 );
		filesize = vgmheader->_sizeOfWholeFile - 4;

		//------------------------------------------
		// 3.重新写header 和 brief
		//------------------------------------------
		pwriter->seek( beginpos );
		pwriter->write( (char*)vgmheader , sizeof( VgmHeader) );
		pwriter->write( (char*)vgmbriefs , sizeof( VgmBrief ) * objnum );
		pwriter->seek( endpos );


		//------------------------------------------
		// 4.最后清理临时数据
		//------------------------------------------
		delete vgmheader;
		delete[] vgmbriefs;
		delete[] vgmdatas;

		//------------------------------------------
		// 5.最后写校验码
		//------------------------------------------
		// 校验码
		// 最后取反(手动校验码只要直接写到文件尾即可)
		// 写到文件末尾,这样使得vgm校验后都为0xFFFFFFFF
		DWORD crcCheckSum;

		CrcUtility::initCrc32Code( crcCheckSum );

		pwriter->close();

		vgKernel::StreamReaderPtr pvgmreader = 
			vgKernel::StreamReaderFactory::createFromFile( save_absolute_path );

		assert( pvgmreader->size() == filesize );
		char* buf = new char[filesize];
		pvgmreader->seek( beginpos );
		size_t readnum = pvgmreader->read( buf , filesize );
		assert( readnum == filesize );


		for ( int i = 0 ; i < filesize ; ++i )
		{
			byte* curbyte = i + (byte*)buf;
			CrcUtility::calculateCrc32Code( *curbyte , crcCheckSum );
		}

		//crcCheckSum = ~crcCheckSum;

		// 写到文件尾
		pvgmreader->close();

		pwriter = vgKernel::StreamWriterFactory::createFromFile( save_absolute_path );
		assert( pwriter.isNull() == false );

		pwriter->write( buf , filesize );

		pwriter->seek( endpos );
		pwriter->write( (char*)&crcCheckSum , sizeof( DWORD ) );

		delete[] buf;
		buf = NULL;




		return true;
	}
	//----------------------------------------------------------------
	VgmDataStruct* FileWriterModToVgm::getVgmDataStructByLodParam(
		VgmDataStruct* input_vgm ,
		const float& factor , VgmBrief* input_brief)
	{
		if ( input_vgm == NULL )
		{
			return  NULL;
		}

		if ( factor <= 0.0f || factor >= 1.0f )
		{
			MessageBox( NULL , "输入模型lod参数错误" , "Error" , MB_OK );
			return NULL;
		}


		vgMesh::VgmDataStruct* curvgm = input_vgm;

		vgMesh::VgmVertexElement1* vert_element = 
			(vgMesh::VgmVertexElement1*)curvgm->_vertexElements;

		int groupid = 0;
		int objid = 0;

		int inv = 0;
		int mode = GLOD_DISCRETE;
		int simp_mode = GLOD_METRIC_SPHERES;
		int edgeLock = GLOD_BORDER_UNLOCK;
		int build_op = GLOD_OPERATOR_HALF_EDGE_COLLAPSE;
		int queue_mode = GLOD_QUEUE_GREEDY;
		float pg_precision = 1.0f;


		//------------------------------------------
		// 第一部分:将送入GLOD
		// 1.首先初始化GLOD
		//------------------------------------------
		if ( glodInit() == 0 )
		{
			assert(0);
		}

		GLenum  errorcode = glodGetError();
		assert( errorcode == GLOD_NO_ERROR );

		glodNewGroup( groupid );

		glodNewObject( objid , groupid, mode );
		errorcode = glodGetError();
		assert( errorcode == GLOD_NO_ERROR );

		//------------------------------------------
		// 2.开始插入数据
		//------------------------------------------
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glEnableClientState( GL_NORMAL_ARRAY );
		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_INDEX_ARRAY );

		glTexCoordPointer( 2, GL_FLOAT, 
			curvgm->_sizeOfVertexElements, &vert_element->texCoorS);
		glNormalPointer( GL_FLOAT, 
			curvgm->_sizeOfVertexElements, &vert_element->normalX );
		glVertexPointer( 3, GL_FLOAT,
			curvgm->_sizeOfVertexElements, &vert_element->positionX );

		for ( int iface = 0 ; iface < curvgm->_numberOfMetaFaces ; ++ iface )
		{
			assert( curvgm->_metaFaces[iface]._numberOfFaceIndex > 0 );
			assert( curvgm->_metaFaces[iface]._faceIndex != NULL );

			glodInsertElements( objid , iface, 
				GL_TRIANGLES, curvgm->_metaFaces[iface]._numberOfFaceIndex * 3, 
				GL_UNSIGNED_INT, curvgm->_metaFaces[iface]._faceIndex,
				0,0.0);

			errorcode = glodGetError();
			assert( errorcode == GLOD_NO_ERROR );
		}

		//------------------------------------------
		// 3.设定参数
		//------------------------------------------
		glodObjectParameteri(objid , GLOD_BUILD_OPERATOR, build_op);
		glodObjectParameteri(objid , GLOD_BUILD_ERROR_METRIC,simp_mode);
		glodObjectParameteri(objid , GLOD_BUILD_BORDER_MODE, edgeLock);
		glodObjectParameteri(objid , GLOD_BUILD_QUEUE_MODE, queue_mode);

		glodObjectParameterf(objid , GLOD_BUILD_PERMISSION_GRID_PRECISION, pg_precision);

		errorcode = glodGetError();
		assert( errorcode == GLOD_NO_ERROR );

		glodBuildObject(objid);


		//------------------------------------------
		// 对这个group进行操作
		//------------------------------------------
		// 得到原始的三角形面数
		long prim_num_triangles = curvgm->getNumberOfTriangles();
		assert( prim_num_triangles > 0 );

		// 设置新的面数
		int s_Triangles = (int)(prim_num_triangles * factor ); 
		glodGroupParameteri(groupid, GLOD_MAX_TRIANGLES, s_Triangles);
		glodGroupParameteri(groupid, GLOD_ADAPT_MODE, GLOD_TRIANGLE_BUDGET);

		glodAdaptGroup(groupid);
		errorcode = glodGetError();
		assert( errorcode == GLOD_NO_ERROR );

		//------------------------------------------
		// 第二部分:从GLOD中读取数据
		// 1.开始ReadBack
		//------------------------------------------

		GLint npatches;
		glodGetObjectParameteriv(objid, GLOD_NUM_PATCHES, &npatches);

		int *dims = new int[ npatches * 2 ];
		glodGetObjectParameteriv( objid , GLOD_PATCH_SIZES, dims);
		errorcode = glodGetError();
		assert( errorcode == GLOD_NO_ERROR );

		assert( npatches == curvgm->_numberOfMetaFaces );

		// 用于存储各个临时数据
		std::vector<vgMesh::VgmVertexElement1> _elementList;
		std::vector<String>	_texNames;
		std::vector<vgMesh::VgmFaceIndex*> _indices;
		std::vector<int> _indices_num;

		for(int ipatch=0; ipatch < npatches; ipatch++) 
		{
			vgMesh::VgmFaceIndex* idx_buf;
			size_t numIndices,numVerts;

			numIndices = dims[ ipatch *2 ];
			numVerts   = dims[ ipatch*2 + 1];  

			assert( numIndices % 3 == 0 );
			idx_buf = new vgMesh::VgmFaceIndex[ numIndices / 3];

			if ( numVerts == 0 || numIndices == 0 )
			{
				continue;
			}

			vgMesh::VgmVertexElement1* readvertex = 
				new vgMesh::VgmVertexElement1[ numVerts ];

			memset( readvertex , 0  , sizeof(vgMesh::VgmVertexElement1) * numVerts);

			glEnableClientState( GL_TEXTURE_COORD_ARRAY );
			glEnableClientState( GL_NORMAL_ARRAY );
			glEnableClientState( GL_VERTEX_ARRAY );
			glEnableClientState( GL_INDEX_ARRAY );

			glTexCoordPointer( 2, GL_FLOAT, 
				sizeof(vgMesh::VgmVertexElement1), &readvertex->texCoorS);
			glNormalPointer( GL_FLOAT, 
				sizeof(vgMesh::VgmVertexElement1), &readvertex->normalX );
			glVertexPointer( 3, GL_FLOAT,
				sizeof(vgMesh::VgmVertexElement1), &readvertex->positionX );

			glodFillElements( objid , ipatch, GL_UNSIGNED_INT, idx_buf);

			//------------------------------------------
			// 插入到element队列,并修改index
			//------------------------------------------
			size_t _element_size = _elementList.size();

			for ( int i = 0 ; i < numIndices / 3 ; ++ i )
			{
				if ( _element_size == 0 )
				{
					break;
				}

				idx_buf[i]._point0 += _element_size;
				idx_buf[i]._point1 += _element_size;
				idx_buf[i]._point2 += _element_size;
			}

			for ( int i = 0 ; i < numVerts ; ++ i )
			{
				_elementList.push_back( readvertex[i] );
			}

			//------------------------------------------
			// 检查index的越界
			//------------------------------------------
			size_t tmpsize = _elementList.size();
			for ( size_t i = 0 ; i < numIndices / 3 ; ++ i )
			{
				assert( idx_buf[i]._point0 < tmpsize );
				assert( idx_buf[i]._point1 < tmpsize );
				assert( idx_buf[i]._point2 < tmpsize );
			}

			_indices_num.push_back( numIndices );
			_indices.push_back( idx_buf );

			_texNames.push_back( String( curvgm->_metaFaces[ ipatch ]._textureFileName[0] ) );
		}// end for ipatch



		assert( _texNames.size() == _indices.size() );
		assert( _texNames.size() == _indices_num.size() );
//		assert( _elementList.size() != 0 );
		if (_elementList.size() == 0 || _indices.size() == 0)
		{
			input_brief->_meshName;
			return input_vgm;
		}


		//------------------------------------------
		// 第三部分:创建vgm,并且写入数据
		// 开始创建vgm
		//------------------------------------------
		vgMesh::VgmDataStruct* tmpvgm = new vgMesh::VgmDataStruct();

		int _elementListSize = _elementList.size();

		// 从_elementList中拷贝出来顶点数据
		vgMesh::VgmVertexElement1* vertexs = 
			new vgMesh::VgmVertexElement1[ _elementList.size() ];

		memset( vertexs , 0 , _elementList.size() );

		memcpy( vertexs , &_elementList[0] ,
			sizeof( vgMesh::VgmVertexElement1) * _elementList.size() );

		_elementList.clear();

		tmpvgm->_renderType = input_vgm->_renderType;

		tmpvgm->_layersOfTexture = 1;
		tmpvgm->_numberOfVertexElements = _elementListSize;
		tmpvgm->_vertexElements = vertexs;
		tmpvgm->_sizeOfVertexElements = sizeof( vgMesh::VgmVertexElement1 );
		tmpvgm->_numberOfMetaFaces = _indices.size();
		tmpvgm->_metaFaces = 
			new vgMesh::VgmMetaFaceStruct[tmpvgm->_numberOfMetaFaces];

		for ( int iface = 0 ; iface < tmpvgm->_numberOfMetaFaces ; ++ iface )
		{
			tmpvgm->_metaFaces[ iface ]._numberOfFaceIndex = _indices_num[iface] / 3;
			tmpvgm->_metaFaces[ iface ]._sizeOfOneTexName = VGM_MESH_NAME_LENGTH;
			tmpvgm->_metaFaces[ iface ]._numberOfTexture = 1;

			tmpvgm->_metaFaces[ iface ]._sizeOfFaceIndex = sizeof( vgMesh::VgmFaceIndex );

			tmpvgm->_metaFaces[ iface ]._textureFileName = new char*[1];
			tmpvgm->_metaFaces[ iface ]._textureFileName[0] = 
				new char[ VGM_MESH_NAME_LENGTH ];

			memset( tmpvgm->_metaFaces[ iface ]._textureFileName[0] , 0 , 
				VGM_MESH_NAME_LENGTH );

			assert( _texNames[ iface ].size() < VGM_MESH_NAME_LENGTH);

			strcpy( tmpvgm->_metaFaces[ iface ]._textureFileName[0] ,
				_texNames[ iface ].c_str() );

			tmpvgm->_metaFaces[ iface ]._faceIndex = _indices[iface];
		}

		delete[] dims;


		//------------------------------------------
		// 最后关闭GLOD
		//------------------------------------------
		glodShutdown();


		return tmpvgm;
	}
	//----------------------------------------------------------------
	bool FileWriterModToVgm::writeToVgmFromStringPairs( 
		const vgKernel::StringPairVector& inputpairs, const float& lod0_factor , 
		const float& lod1_factor ,
		const float& squareDistNear , const float& squareDistFar  )
	{
		if ( inputpairs.empty() == true )
		{
			return false;
		}

		//------------------------------------------
		// 确定process的进度条
		//------------------------------------------
		int processCounter = 0;
		this->notifyProcessObserversStart( "开始生成读取mod文件..." ,0,inputpairs.size() - 1 );


		StringPairVector::const_iterator iter = inputpairs.begin();
		StringPairVector::const_iterator iter_end = inputpairs.end();

		bool sucess = true;

		for ( ; iter != iter_end ; ++iter )
		{
			String src = iter->first;
			String dst = iter->second;

			std::ostringstream o;
			o << "正在处理:" << src;
			notifyProcessObserversPos( o.str() , processCounter++);

			vgKernel::StreamReaderPtr preader = 
				vgKernel::StreamReaderFactory::createFromFile( src );

			assert( preader.isNull() == false );

			if ( preader.isNull() == true )
			{
				return false;
			}

			bool ret = vgMesh::FileWriterModToVgm::writeToVgmFileFromModStream(
				preader , dst , lod0_factor , lod1_factor , 
				squareDistNear , squareDistFar );

			assert( ret == true );
			if ( ret == false )
			{
				return false;
			}
		}

		std::ostringstream o;
		o << "操作成功完成,共" << inputpairs.size() << "个文件";

		notfiyProcessObserversFinish( o.str() );

		return true;
	}
}// end of namespace vgMesh
