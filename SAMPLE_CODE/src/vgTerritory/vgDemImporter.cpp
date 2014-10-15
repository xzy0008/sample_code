


#include <vgStableHeaders.h>
#include <vgTerritory/vgDemImporter.h>
#include <vgImage/vgiImageUtility.h>
#include <vgKernel/vgkStreamReader.h>
#include <vgKernel/vgkStreamWriter.h>

namespace vgTerritory{



	//----------------------------------------------------------------
	DemBlockPtr DemImporter::readDemFile( const String& dem_file )
	{
		vgKernel::StreamReaderPtr pstream = 
			vgKernel::StreamReaderFactory::createFromFile( dem_file );
		
		if ( pstream.isNull() == true )
		{
			errorMsgOutput("Dem file is not exist!");
			return DemBlockPtr();
		}

		String basename =
			vgImage::ImageUtility::findFilenameFromAbsolutePath( dem_file );

		//------------------------------------------
		// 读取文件头
		//------------------------------------------
		uint ncols			= 0;
		uint nrows			= 0;
		double xllcorner		= 0;
		double yllcorner 		= 0;
		float cellsize		= 0;
		int NODATA_value	= 0;

		String bufferstr;

		//------------------------------------------
		// 读所有数据到stringstream
		//------------------------------------------
		int filesize = pstream->size();
		char *buf = new char[ filesize ];
		pstream->read( buf , filesize );
		std::stringstream stream(buf);
		delete[] buf;

		//------------------------------------------
		// read ncols
		//------------------------------------------
		stream >> bufferstr;
		if ( bufferstr != "ncols" )
		{
			errorMsgOutput("DEM file is corrupted!");
			return DemBlockPtr();
		}
		stream >> ncols;
		assert( ncols != 0 );

		//------------------------------------------
		// read nrows
		//------------------------------------------
		stream >> bufferstr;
		if ( bufferstr != "nrows" )
		{
			errorMsgOutput("DEM file is corrupted!");
			return DemBlockPtr();
		}
		stream >> nrows;
		assert( nrows != 0 );

		//------------------------------------------
		// read xllcorner
		//------------------------------------------
		stream >> bufferstr;
		if ( bufferstr != "xllcorner" )
		{
			errorMsgOutput("DEM file is corrupted!");
			return DemBlockPtr();
		}
		stream >> xllcorner;
		assert( xllcorner != 0 );


		//------------------------------------------
		// read yllcorner
		//------------------------------------------
		stream >> bufferstr;
		if ( bufferstr != "yllcorner" )
		{
			errorMsgOutput("DEM file is corrupted!");
			return DemBlockPtr();
		}
		stream >> yllcorner;
		assert( yllcorner != 0 );

		//------------------------------------------
		// read cellsize
		//------------------------------------------
		stream >> bufferstr;
		if ( bufferstr != "cellsize" )
		{
			errorMsgOutput("DEM file is corrupted!");
			return DemBlockPtr();
		}
		stream >> cellsize;
		assert( cellsize != 0 );

		//------------------------------------------
		// read NODATA_value
		//------------------------------------------
		stream >> bufferstr;
		if ( bufferstr != "NODATA_value" )
		{
			errorMsgOutput("DEM file is corrupted!");
			return DemBlockPtr();
		}
		stream >> NODATA_value;
		assert( NODATA_value != 0 );


		//------------------------------------------
		// begin to read the block data
		//------------------------------------------

		float* realdata = new float[ ncols * nrows ];

		for ( int i = 0 ; i <  ncols * nrows ; ++ i )
		{
			// 注意,矩阵转置操作,由于坐标轴的不一致
			//stream >> realdata[ (i % ncols)*nrows + i / ncols ];
			//stream >> realdata[i];
			stream >> realdata[ (ncols - 1 - i % ncols) * nrows + i / ncols ];
		}

		//------------------------------------------
		// 得到最小高度值和最大高度值
		//------------------------------------------
		assert( ncols != 0 );
		assert( nrows != 0 );
		float origin_y = NODATA_value;
		float top_y = NODATA_value;
		bool tmpfirsttime = true;
		for ( int i = 0 ; i <  ncols * nrows ; ++ i )
		{
			if ( NODATA_value == realdata[i] )
			{
				continue;
			}

			if ( tmpfirsttime == true )
			{
				tmpfirsttime = false;
				origin_y = realdata[i];
				top_y = realdata[i];
			}

			if ( origin_y > realdata[i] )
			{
				origin_y = realdata[i];
			}

			if ( top_y < realdata[i] )
			{
				top_y = realdata[i];
			}
		}

		//------------------------------------------
		// 赋值给nodata区域
		// 注意,这里效率非常低,但考虑是一次性操作
		// 暂时这样
		//------------------------------------------
		for ( int i = 0 ; i <  ncols * nrows ; ++ i )
		{
			if (  NODATA_value == realdata[i]  )
			{
				realdata[i] = origin_y;
			}
		}

		//------------------------------------------
		// 赋值给Demblock并返回
		//------------------------------------------
		DemBlock* retblock = new DemBlock;

		//------------------------------------------
		// 由于dem坐标轴x向下,故这里取反
		//------------------------------------------
		retblock->setData( basename , 
			ncols , nrows , xllcorner , -yllcorner , origin_y ,top_y ,
			cellsize , realdata );

		//VG_TRACE( retblock->getDetails() );

		return DemBlockPtr(retblock);
	}
	//----------------------------------------------------------------
	void DemImporter::errorMsgOutput( const String& errMsg /*= "" */ )
	{
		MessageBox(NULL , errMsg.c_str() , "Dem读取错误!" , MB_OK );
		return;
	}
	//----------------------------------------------------------------

	//----------------------------------------------------------------

}