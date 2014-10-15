


#include <vgStableHeaders.h>
#include <vgTerritory/vgtDemHeader.h>


namespace vgTerritory {
	
	
	
	
	//----------------------------------------------------------------
	DemHeader::DemHeader()
	{
		_xNum = 0;
		_zNum = 0;

		_originX = 0.0;
		_originZ = 0.0;

		_cellSize = 0.0;
	}
	//----------------------------------------------------------------
	DemHeader::~DemHeader()
	{

	}
	//----------------------------------------------------------------
	bool DemHeader::readFromFile( const String& demfilename )
	{
		vgKernel::StreamReaderPtr pstream = 
			vgKernel::StreamReaderFactory::createFromFile( demfilename );

		if ( pstream.isNull() == true )
		{
			assert(0);
			return false;
		}

		//------------------------------------------
		// 读取文件头
		//------------------------------------------
		uint ncols			= 0;
		uint nrows			= 0;
		double xllcorner		= 0;
		double yllcorner 		= 0;
		float cellsize		= 0;

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
			return false;
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
			return false;
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
			return false;
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
			return false;
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
			return false;
		}
		stream >> cellsize;
		assert( cellsize != 0 );


		//------------------------------------------
		// 开始赋值 
		//------------------------------------------
		// 最后一位
		_xNum = ncols;
		_zNum = nrows;

		_originX = xllcorner;
		_originZ = -yllcorner;

		_cellSize = cellsize;

		_demFilename = demfilename;

		return true;
	}
	//----------------------------------------------------------------
	void DemHeader::errorMsgOutput( const String& errMsg /*= "" */ )
	{
		MessageBox(NULL , errMsg.c_str() , "Dem读取错误!" , MB_OK );
		return;
	}
	//----------------------------------------------------------------


}// end of namespace vgTerritory
