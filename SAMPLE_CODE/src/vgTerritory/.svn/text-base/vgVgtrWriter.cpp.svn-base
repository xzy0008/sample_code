


#include <vgStableHeaders.h>
#include <vgTerritory/vgVgtrWriter.h>
#include <vgImage/vgiImageUtility.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgKernel/vgkTrace.h>



namespace vgTerritory {
	
	//----------------------------------------------------------------
	VgtrFilePtr VgtrWriter::convertDemBlocksToVgtr( const String& vgtrname , 
		const DemBlockVectorPtr pdemblocks,
		const int& cell_tex_size , const long& N )
	{

		String filename = vgtrname;
		vgKernel::StringUtility::trim( filename );

		if ( pdemblocks.isNull() == true )
		{
			MessageBox(NULL , "转换dem到vgtr出错",  "error" , MB_OK );
			return VgtrFilePtr();
		}

		if ( filename.empty() == true )
		{
			MessageBox(NULL , "转换dem到vgtr出错,名字为空",  "error" , MB_OK );
			return VgtrFilePtr();
		}

		if ( filename.size() >= VG_VGTR_NAME_LENGTH -1 )
		{
			MessageBox(NULL , "转换dem到vgtr出错,名字过长",  "error" , MB_OK );
			return VgtrFilePtr();
		}


		double minOriginX = 0;
		double minOriginZ = 0;
		double minOriginY = 0;
		double maxTopY = 0;
		float scale = 1;
		float tmpcellsize = 0;
		int celltexsize = cell_tex_size;

		vgKernel::ImageRect vgtr_rect;

		//------------------------------------------
		// 检查cellsize都是一样的,并找出最小原点
		//------------------------------------------
		{
			if ( pdemblocks->empty() == true )
			{
				errorMsgOutput("无输入dem文件");
				return VgtrFilePtr();
			}

			tmpcellsize = (*pdemblocks->begin())->_cellSize;
			minOriginX = (*pdemblocks->begin())->_originX;
			minOriginZ = (*pdemblocks->begin())->_originZ;
			minOriginY = (*pdemblocks->begin())->_originY;
			maxTopY =  (*pdemblocks->begin())->_topY;

			DemBlockVector::iterator iter = pdemblocks->begin();
			DemBlockVector::iterator iter_end = pdemblocks->end();

			for ( ; iter != iter_end ; ++iter )
			{
				assert( (*iter).isNull() == false );

				if( (*iter)->_cellSize != tmpcellsize)
				{
					errorMsgOutput("cellsize不满足一致条件");
					return VgtrFilePtr();
				}

				if ( (*iter)->_originX < minOriginX  )
				{
					minOriginX = (*iter)->_originX;
				}

				if ( (*iter)->_originZ < minOriginZ )
				{
					minOriginZ = (*iter)->_originZ;
				}

				if ( (*iter)->_originY < minOriginY )
				{
					minOriginY = (*iter)->_originY;
				}

				if ( (*iter)->_topY > maxTopY )
				{
					maxTopY = (*iter)->_topY;
				}
			}
		}

		//------------------------------------------
		// 求出逻辑非浮点大小
		//------------------------------------------
		{
			DemBlockVector::iterator iter = pdemblocks->begin();
			DemBlockVector::iterator iter_end = pdemblocks->end();

			for ( ; iter != iter_end ; ++iter )
			{
				(*iter)->_imgRect.minPos.x = 
					( (*iter)->_originX - minOriginX ) / tmpcellsize;

				(*iter)->_imgRect.minPos.y = 
					( (*iter)->_originZ - minOriginZ ) / tmpcellsize;
				
				(*iter)->_imgRect.maxPos.x = 
					(*iter)->_imgRect.minPos.x + (*iter)->_xNum - 1 ;

				(*iter)->_imgRect.maxPos.y = 
					(*iter)->_imgRect.minPos.y + (*iter)->_zNum - 1 ;

				vgtr_rect.merge( (*iter)->_imgRect );
			}
		}

#if 1
		//------------------------------------------
		// 打印blocks信息
		//------------------------------------------
		{
			DemBlockVector::iterator iter = pdemblocks->begin();
			DemBlockVector::iterator iter_end = pdemblocks->end();

			for ( ; iter != iter_end ; ++iter )
			{
				VGK_TRACE_SHORT( (*iter)->getDetails() );				
			}
		}
#endif

		assert( vgtr_rect.minPos.x == 0 );
		assert( vgtr_rect.minPos.y == 0 );

		const float	VGTR_NODATA_VALUE = 0.0f;

		int vgtr_width = 
			vgImage::ImageUtility::getBiggerPowerOfTwoNumber( vgtr_rect.getWidth() + 1 );

		int vgtr_height =
			vgImage::ImageUtility::getBiggerPowerOfTwoNumber( vgtr_rect.getHeight() + 1 );

		int vgtr_data_size_in_float = vgtr_width * vgtr_height;

		float* vgtr_data = new float[ vgtr_data_size_in_float ];

		for ( int i = 0 ; i < vgtr_data_size_in_float ; ++ i )
		{
			vgtr_data[i] = minOriginY;
		}

		//------------------------------------------
		// 写入data
		//------------------------------------------
		{
			DemBlockVector::iterator iter = pdemblocks->begin();
			DemBlockVector::iterator iter_end = pdemblocks->end();

			for ( ; iter != iter_end ; ++iter )
			{
				setVgtrData( vgtr_data , vgtr_width , *iter );			
			}
		}

		//------------------------------------------
		// 目前存储的是原始数据,此时需要将这些数据
		// 缩放到0到1范围内.
		// 并计算scale
		//------------------------------------------
		float length_between_minY_maxY = (maxTopY - minOriginY);
		scale = length_between_minY_maxY;
		{
			for ( int i = 0 ; i < vgtr_data_size_in_float ; ++ i )
			{
				vgtr_data[i] -= minOriginY;
				vgtr_data[i] /= scale;
			}
		}

		//------------------------------------------
		// 返回最终数据
		//------------------------------------------

		VgtrFile* retfile = new VgtrFile;
		VgtrHeaderPtr header(new VgtrHeader);

		header->cellsize	= tmpcellsize;
		header->dataLen[VGLOD_CLEAR]	=
			vgtr_data_size_in_float * sizeof( float );

		header->dataLen[VGLOD_CLEAR-1]	=
			vgtr_data_size_in_float * sizeof( float ) / 4;

		header->dataLen[VGLOD_CLEAR-2]	=
			vgtr_data_size_in_float * sizeof( float ) / 16;

		assert( header->dataLen[VGLOD_CLEAR-2] != 0 );
		assert( header->dataLen[VGLOD_CLEAR-1] != 0 );
		assert( header->dataLen[VGLOD_CLEAR] != 0 );

		assert( vgtr_width == vgtr_height );
		header->xNum		= vgtr_width;
		header->zNum		= vgtr_height;
		header->originX		= minOriginX;
		header->originZ		= minOriginZ;
		header->originY		= minOriginY;
		header->displaceScaleY		= scale;
		header->cellTexSize = celltexsize;
		header->N				= N;
		header->displaceChunkScale = 1.0f;
		header->displaceChunkBiasX = 0.0f;
		header->displaceChunkBiasZ = 0.0f;

		strcpy( header->name , filename.c_str() );

		assert( celltexsize > 0 );

		retfile->_dataLod[VGLOD_CLEAR]		= vgtr_data;
		retfile->_headerPtr	= header;

		//------------------------------------------
		// 开始生成其他的lod
		//------------------------------------------
		float* datalod1 = new float[ vgtr_data_size_in_float / 4 ];
		memset( datalod1 , 0 , vgtr_data_size_in_float / 4 * sizeof( float ) );

		for ( int i = 0 ; i < vgtr_width / 2 ; ++i )
		{
			for ( int j = 0 ; j < vgtr_width / 2 ; ++ j )
			{
				datalod1[i + vgtr_width / 2 * j ] = 
					vgtr_data[ i * 2 + vgtr_width * j * 2 ];
			}
		}

		float* datalod0 = new float[ vgtr_data_size_in_float / 16 ];
		memset( datalod1 , 0 , vgtr_data_size_in_float / 16 * sizeof( float ) );

		for ( int i = 0 ; i < vgtr_width / 4 ; ++i )
		{
			for ( int j = 0 ; j < vgtr_width / 4 ; ++ j )
			{
				datalod0[i + vgtr_width / 4 * j ] = 
					vgtr_data[ i * 4 + vgtr_width * j * 4 ];
			}
		}


		//------------------------------------------
		// 赋值
		//------------------------------------------
		retfile->_dataLod[VGLOD_CLEAR-1]		= datalod1;
		retfile->_dataLod[ VGLOD_COARSE]		= datalod0;

		return VgtrFilePtr(retfile);
	}
	//----------------------------------------------------------------
	bool VgtrWriter::writeVgtrToFile( const VgtrFilePtr vgtr , const String& outputfilename )
	{
		long writenum =  vgtr->writeToStream( 
			vgKernel::StreamWriterFactory::createFromFile( outputfilename ) );

		return writenum != 0;
	}

	void VgtrWriter::errorMsgOutput( const String& errMsg /*= "" */ )
	{
		MessageBox(NULL , errMsg.c_str() , "转换Dem发生错误" , MB_OK );
		return;
	}
	//----------------------------------------------------------------
	bool VgtrWriter::setVgtrData( float* data ,
		 const int& data_width , const DemBlockPtr pdem )
	{
		
		assert( pdem.isNull() == false );

		vgKernel::ImageRect& rect = pdem->_imgRect;
		
		float* demdata = pdem->_zData;

		int offset;

		for ( int i = 0 ; i < (pdem->_xNum * pdem->_zNum) ; ++ i )
		{
			offset =
				(rect.minPos.y + i / ( pdem->_xNum) )* data_width + rect.minPos.x + i % pdem->_xNum ;

			data[ offset ] = demdata[i];
		}

		return true;
	}
	//----------------------------------------------------------------

	
}// end of namespace vgTerritory


