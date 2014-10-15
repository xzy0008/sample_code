


#include <vgStableHeaders.h>
#include <vgTerritory/vgtVgtrGenerator.h>
#include <vgTerritory/vgVgtrWriter.h>

namespace vgTerritory {
	
	
	
	
	//----------------------------------------------------------------
	VgtrFilePtrVec* VgtrGenerator::generateSpecificLayer( 
		const VgtrFilePtr wholevgtr , const long& layer)
	{
		assert( wholevgtr.isNull() == false );
		assert( wholevgtr->_headerPtr.isNull() == false );
		assert( wholevgtr->_dataLod[0] != NULL );
		assert( wholevgtr->_dataLod[1] != NULL );
		assert( wholevgtr->_dataLod[2] != NULL );
		assert( wholevgtr->_headerPtr->xNum == 
			wholevgtr->_headerPtr->zNum );

		assert( wholevgtr->_headerPtr->xNum != 0 );

		//------------------------------------------
		// 计算layer的总数
		//------------------------------------------
		long N = wholevgtr->_headerPtr->N;
		assert( N > 0 );
		long width = wholevgtr->_headerPtr->xNum;
		long meshnum = (long)pow( 2.0f , N );
		assert( width % meshnum == 0 );

		long worldwidth = width * wholevgtr->_headerPtr->cellsize;

		if ( width % meshnum != 0 )
		{
			return NULL;
		}

		long layernum = getLayerNum( wholevgtr , N );
		if ( layer >= layernum )
		{
			return NULL;
		}

		//------------------------------------------
		// 开始生成
		//------------------------------------------
		float* wholedata = wholevgtr->_dataLod[VGLOD_CLEAR];
		String prefix = wholevgtr->_headerPtr->name;// 不包含后面的".vgtr"
		float cellsize = wholevgtr->_headerPtr->cellsize;
		long w = wholevgtr->_headerPtr->xNum;
		long pow_2_layer = (long)pow( 2.0f , layer );
		long pow_2_N = (long)pow( 2.0f , N );

		long chunknum = width / meshnum / pow_2_layer; 
		long chunksize = pow_2_N * pow_2_layer;

		VgtrFilePtrVec* ret = new VgtrFilePtrVec;

		for ( int i = 0 ; i < chunknum ; ++ i )
		{
			for ( int j = 0 ; j < chunknum ; ++ j )
			{
				// 产生pow_2_N  + 1大小的数据,为了避免裂缝
				long datalen = ( pow_2_N  + 1 ) * (pow_2_N + 1);
				float* newdata = new float[datalen];
				memset( newdata , 0 , datalen * sizeof( float ) );

				for ( int x = 0 ; x < pow_2_N + 1 ; ++ x )
				{
					for ( int z = 0 ; z < pow_2_N + 1; ++ z )
					{
						// wholedata中长宽是一样的
						newdata[ z * (pow_2_N+1) + x ] = 
							getFromTable( wholedata , w , w ,
							chunksize * i + x * pow_2_layer,
							chunksize * j + z * pow_2_layer);
					}
				}// end x

				// 开始生成lod数据
				// !!!!!!!!测试使用!!先写成pow_2_N* pow_2_N / 4的大小!
				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

				float* newdatalod1 = new float[ pow_2_N * pow_2_N / 4 ];
				memset( newdatalod1 , 0 , pow_2_N * pow_2_N / 4 * sizeof( float ) );

				for ( int x = 0 ; x < pow_2_N / 2; ++ x )
				{
					for ( int z = 0 ; z < pow_2_N / 2; ++ z )
					{
						newdatalod1[ z * pow_2_N / 2 + x ] = 
							newdata[  z * (pow_2_N + 1) * 2 + x * 2];
					}
				}// end x

				float* newdatalod0 = new float[ pow_2_N * pow_2_N / 16 ];
				memset( newdatalod0 , 0 , pow_2_N * pow_2_N / 16 * sizeof( float ) );

				for ( int x = 0 ; x < pow_2_N / 4; ++ x )
				{
					for ( int z = 0 ; z < pow_2_N / 4; ++ z )
					{
						newdatalod0[ z * pow_2_N / 4 + x ] = 
							newdata[  z * (pow_2_N + 1)* 4 + x * 4];
					}
				}// end x

				//------------------------------------------
				// 开始赋值
				//------------------------------------------
				VgtrFilePtr tmp( new VgtrFile );
				tmp->_dataLod[VGLOD_CLEAR] = newdata;
				tmp->_dataLod[VGLOD_CLEAR-1] = newdatalod1;
				tmp->_dataLod[VGLOD_CLEAR-2] = newdatalod0;
				tmp->_headerPtr.bind( new VgtrHeader );

				// 计算scale和bias的值.
				float s = (float)width / (float)pow_2_N / (float)pow_2_layer;
				float disscale = s / worldwidth;
				float disbiasX = i;
				float disbiasZ = j;
				tmp->_headerPtr->displaceChunkScale = disscale;
				tmp->_headerPtr->displaceChunkBiasX = disbiasX;
				tmp->_headerPtr->displaceChunkBiasZ = disbiasZ;
					

				std::ostringstream o;
				o << prefix <<  "_level" << layer << "_" << i << "_" << j;
				String tmpname = o.str();
				assert( tmpname.size() < VG_VGTR_NAME_LENGTH );

				strcpy( tmp->_headerPtr->name , tmpname.c_str() );

				String tmptex = tmpname + ".dds";
				assert( tmptex.size() < VG_VGTR_NAME_LENGTH );
				strcpy( tmp->_headerPtr->texname , tmptex.c_str() );

				tmp->_headerPtr->N = wholevgtr->_headerPtr->N;	
				tmp->_headerPtr->cellTexSize = wholevgtr->_headerPtr->cellTexSize;	

				// 注意这里的长宽
				tmp->_headerPtr->xNum = pow_2_N + 1;	
				tmp->_headerPtr->zNum = pow_2_N + 1;	

				tmp->_headerPtr->cellsize = cellsize;	

				// 当前所处的位置
				tmp->_headerPtr->originX = 
					wholevgtr->_headerPtr->originX + cellsize * 
					( chunksize * i );
				tmp->_headerPtr->originY = wholevgtr->_headerPtr->originY;
				tmp->_headerPtr->originZ = 
					wholevgtr->_headerPtr->originY+ cellsize * 
					( chunksize * j );

				tmp->_headerPtr->displaceScaleY = wholevgtr->_headerPtr->displaceScaleY;

				// 注意这里是以字节为单位.
				tmp->_headerPtr->dataLen[VGLOD_CLEAR] = 
					datalen * sizeof( float );

				tmp->_headerPtr->dataLen[VGLOD_CLEAR-1] = 
					pow_2_N * pow_2_N * sizeof( float ) / 4;

				tmp->_headerPtr->dataLen[VGLOD_CLEAR-2] = 
					pow_2_N * pow_2_N * sizeof( float ) / 16;

				ret->push_back( tmp );
			}
		}


		return ret;
	}
	//----------------------------------------------------------------
	long VgtrGenerator::getLayerNum( const VgtrFilePtr vgtr , const long& N  )
	{
		assert( vgtr.isNull() == false );
		assert( vgtr->_headerPtr.isNull() == false );

		assert( vgtr->_dataLod[0] != NULL );
		assert( vgtr->_dataLod[1] != NULL );
		assert( vgtr->_dataLod[2] != NULL );


		assert( vgtr->_headerPtr->xNum == 
			vgtr->_headerPtr->zNum );

		assert( vgtr->_headerPtr->xNum != 0 );

		//------------------------------------------
		// 计算layer的总数
		//------------------------------------------
		long width = vgtr->_headerPtr->xNum;
		long meshnum = (long)pow( 2.0f , N );
		assert( width % meshnum == 0 );

		if ( width % meshnum != 0 )
		{
			return NULL;
		}

		long layernum = log( (float)width / meshnum ) / log( 2.0f );
		assert( layernum > 0 );


		return layernum;
	}
	//----------------------------------------------------------------
	vgKernel::StringVectorPtr VgtrGenerator::generateLayers( const VgtrFilePtr wholevgtr , 
		const String& output_path )
	{
		vgKernel::StringVectorPtr returnnames( new vgKernel::StringVector );

		long layernum = getLayerNum( wholevgtr , wholevgtr->_headerPtr->N );
		assert( layernum > 0 );

		for ( int i = 0 ; i < layernum ; ++ i )
		{
			VgtrFilePtrVec* ret = generateSpecificLayer( wholevgtr , i );
			assert( ret != NULL );

			vgKernel::SharePtr<VgtrFilePtrVec> vgtrs( ret );

			VgtrFilePtrVec::iterator iter  = ret->begin();
			VgtrFilePtrVec::iterator iter_end = ret->end();

			for ( ; iter != iter_end ; ++ iter )
			{
				VgtrFilePtr curptr = *iter;

				assert( curptr.isNull() == false );

				String outname = output_path + "\\" +  curptr->_headerPtr->name + ".vgtr";

				bool writeok = VgtrWriter::writeVgtrToFile( curptr , outname );

				assert( writeok == true );
				if ( writeok == false )
				{
					return vgKernel::StringVectorPtr();
				}

				returnnames->push_back( outname );
			}
		}

		return returnnames;
	}
	//----------------------------------------------------------------


}// end of namespace vgTerritory
